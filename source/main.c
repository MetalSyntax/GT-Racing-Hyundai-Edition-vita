#include "utils/init.h"
#include "utils/glutil.h"
#include "utils/logger.h"
#include "utils/dialog.h"
#include "utils/input.h"
#include "reimpl/io.h"
#include "cached_jni_stubs.h"

#include <psp2/kernel/threadmgr.h>

#include <falso_jni/FalsoJNI.h>
#include <so_util/so_util.h>

int _newlib_heap_size_user = 192 * 1024 * 1024;

#ifdef USE_SCELIBC_IO
int sceLibcHeapSize = 4 * 1024 * 1024;
#endif

so_module so_mod;

/*
 * Watchdog de cuelgue en onDraw (pantalla blanca sin crash dump): el hilo
 * principal deja de volver de nativeOnDrawFrame y el log simplemente se
 * detiene. Este hilo avisa cada 10s con el tiempo colgado y el último frame
 * completado, para localizar el punto exacto en el próximo log de consola.
 * Solo lee (sin locks del juego): impacto nulo en la lógica.
 */
static volatile SceUInt64 g_onDraw_enter_us = 0;
static volatile unsigned g_onDraw_done = 0;

static int watchdog_thread(SceSize args, void *argp) {
    (void)args;
    (void)argp;
    unsigned last_done = 0;
    unsigned long long last_count = 0;
    for (;;) {
        sceKernelDelayThread(5 * 1000 * 1000);
        log_flush(); /* el logger ahora va con buffer: no perder más de ~5 s ante un crash */
        unsigned done = g_onDraw_done;
        if (done != last_done) {
            last_done = done;
            last_count = trace_count();
            continue;
        }
        if (g_onDraw_enter_us == 0)
            continue;
        SceUInt64 dt = sceKernelGetProcessTimeWide() - g_onDraw_enter_us;
        if (dt > 10 * 1000 * 1000) {
            unsigned long long now = (unsigned long long)sceKernelGetProcessTimeWide();
            unsigned long long last_age =
                (now > trace_last_us()) ? (now - trace_last_us()) / 1000000 : 0;
            unsigned long long rate = (trace_count() - last_count) / 5;
            last_count = trace_count();
            FILE *spin_fp = NULL;
            unsigned long long spin_zeros = 0;
            const char *spin_path = NULL;
            trace_stream_last(&spin_fp, &spin_zeros, &spin_path);
            l_error("[watchdog] onDraw sin retornar %llus (frame %u) -- última bridge: %s hace %llus, tid 0x%x, %llu llamadas/s -- stream E/S: %p (%s) con %llu retornos-0",
                    (unsigned long long)(dt / 1000000), done, trace_last_name(), last_age,
                    trace_last_tid(), rate, spin_fp, spin_path ? spin_path : "?", spin_zeros);
        }
    }
    return 0;
}

// Secuencia de arranque real (jadx GTRacing.java:569-629 + GameRenderer.java):
// setupPaths/setPaths -> nativeInit()*5 -> nativeOnCreate -> OnStart/OnResume ->
// SurfaceCreated/SizeChanged -> loop OnDrawFrame. Sin Activity real en Vita,
// se llama a los Java_* directamente con thiz/objetos NULL (un crash a la vez).
#define PKG "com.gameloft.android.ANMP.GloftGTHY"

typedef void (*jni_void_t)(void *env, void *thiz);
typedef void (*jni_setpaths_t)(void *env, void *thiz, void *a, void *b, void *c);
typedef void (*jni_surface_changed_t)(void *env, void *thiz, void *gl, int w, int h);
typedef void (*jni_size_changed_t)(void *env, void *thiz, int a, int b, int c, int d);
typedef void (*jni_focus_t)(void *env, void *thiz, int focused);
typedef int (*jni_key_t)(void *env, void *thiz, int code, void *event);

static void call_void(const char *name) {
    jni_void_t fn = (jni_void_t)so_symbol(&so_mod, name);
    if (fn) {
        l_success("Calling %s", name);
        fn(&jni, NULL);
    } else {
        l_error("Missing symbol %s", name);
    }
}

int main() {
    logger_init();
    l_info("=== GT Racing Hyundai Edition starting ===");
    soloader_init_all();

    int (* JNI_OnLoad)(void *jvm) = (void *)so_symbol(&so_mod, "JNI_OnLoad");
    if (!JNI_OnLoad)
        fatal_error("Error: JNI_OnLoad not found in %s.", SO_PATH);
    JNI_OnLoad(&jvm);
    l_success("JNI_OnLoad done.");

    // Strings estáticos que nativeOnCreate strcpy()ea sin NULL-check (Ghidra).
    hy_fields_init();

    int *os_screen_w = (int *)so_symbol(&so_mod, "OS_SCREEN_W");
    if (os_screen_w) *os_screen_w = 960;
    int *os_screen_h = (int *)so_symbol(&so_mod, "OS_SCREEN_H");
    if (os_screen_h) *os_screen_h = 544;
    int *screen_w = (int *)so_symbol(&so_mod, "SCREEN_W");
    if (screen_w) *screen_w = 960;
    int *screen_h = (int *)so_symbol(&so_mod, "SCREEN_H");
    if (screen_h) *screen_h = 544;
    l_info("Screen resolution initialized to 960x544.");

    gl_init();

    // GTRacing.onCreate (GTRacing.java:570-599, instalador omitido: datos ya colocados):
    // nativeInit() x5 -> setupPaths()/setPaths() -> nativeOnCreate -> OnStart/OnResume.
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_GameRenderer_nativeInit");
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_GameGLSurfaceView_nativeInit");
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_EditTextField_nativeInit");
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_CustomFilter_nativeInit");
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_GTRacing_nativeInit");

    // GTRacing.setupPaths(): setPaths(sDFolder, filesDir, cacheDir)
    jni_setpaths_t setPaths = (jni_setpaths_t)so_symbol(&so_mod, "Java_com_gameloft_android_ANMP_GloftGTHY_GTRacing_setPaths");
    if (setPaths) {
        void *sd = jni->NewStringUTF(&jni, DATA_PATH);
        void *home = jni->NewStringUTF(&jni, DATA_PATH "saves");
        void *tmp = jni->NewStringUTF(&jni, DATA_PATH "saves");
        setPaths(&jni, NULL, sd, home, tmp);
        l_success("setPaths done.");
    } else {
        l_error("Missing symbol setPaths");
    }

    // Activity: onCreate(NULL bundle) -> onStart -> onResume
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_GTRacing_nativeOnCreate");
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_GTRacing_nativeOnStart");
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_GTRacing_nativeOnResume");

    // Surface: created -> size 960x544 -> focus
    call_void("Java_com_gameloft_android_ANMP_GloftGTHY_GameRenderer_nativeOnSurfaceCreated");
    l_info("GameRenderer_nativeOnSurfaceCreated completed.");

    jni_size_changed_t onSize = (jni_size_changed_t)so_symbol(&so_mod, "Java_com_gameloft_android_ANMP_GloftGTHY_GameGLSurfaceView_nativeOnSizeChanged");
    if (onSize) {
        l_info("Calling GameGLSurfaceView_nativeOnSizeChanged(960, 544)");
        onSize(&jni, NULL, 960, 544, 960, 544);
    }
    jni_surface_changed_t onChanged = (jni_surface_changed_t)so_symbol(&so_mod, "Java_com_gameloft_android_ANMP_GloftGTHY_GameRenderer_nativeOnSurfaceChanged");
    if (onChanged) {
        l_info("Calling GameRenderer_nativeOnSurfaceChanged(960, 544)");
        onChanged(&jni, NULL, NULL, 960, 544);
    }
    jni_focus_t onFocus = (jni_focus_t)so_symbol(&so_mod, "Java_com_gameloft_android_ANMP_GloftGTHY_GameGLSurfaceView_nativeOnWindowFocusChanged");
    if (onFocus) {
        l_info("Calling GameGLSurfaceView_nativeOnWindowFocusChanged(1)");
        onFocus(&jni, NULL, 1);
    }

    jni_void_t onDraw = (jni_void_t)so_symbol(&so_mod, "Java_com_gameloft_android_ANMP_GloftGTHY_GameRenderer_nativeOnDrawFrame");
    if (!onDraw)
        fatal_error("Error: nativeOnDrawFrame not found.");

    fn_app_on_touch appOnTouch = (fn_app_on_touch)so_symbol(&so_mod, "appOnTouch");
    jni_key_t onKeyDown = (jni_key_t)so_symbol(&so_mod, "Java_com_gameloft_android_ANMP_GloftGTHY_GTRacing_nativeOnKeyDown");
    jni_key_t onKeyUp = (jni_key_t)so_symbol(&so_mod, "Java_com_gameloft_android_ANMP_GloftGTHY_GTRacing_nativeOnKeyUp");
    fn_sensor_evt onSensor = (fn_sensor_evt)so_symbol(&so_mod, "Java_com_gameloft_android_ANMP_GloftGTHY_GTRacing_nativeOnSensorChanged");

    input_init(appOnTouch, onKeyDown, onKeyUp, onSensor);

    l_info("Entering main render loop...");
    log_flush();

    SceUID watchdog = sceKernelCreateThread("hy_watchdog", watchdog_thread, 0x10000100, 0x4000, 0, SCE_KERNEL_CPU_MASK_USER_2, NULL);
    if (watchdog >= 0)
        sceKernelStartThread(watchdog, 0, NULL);
    else
        l_warn("No se pudo crear el hilo watchdog (0x%08X)", (unsigned)watchdog);

    static unsigned int frame_counter = 0;
    while (1) {
        input_poll(&jni);
        g_onDraw_enter_us = sceKernelGetProcessTimeWide();
        onDraw(&jni, NULL);
        g_onDraw_done++;
        gl_swap();
        // Vaciar línea pendiente del colapso (xN): si el proceso muere,
        // lo último queda en disco en vez de retenido en RAM
        if ((++frame_counter % 60) == 0)
            log_flush();
    }

    sceKernelExitDeleteThread(0);
    return 0;
}

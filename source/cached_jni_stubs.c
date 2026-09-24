/* Callbacks JNI que el .so resuelve por nombre vía GetMethodID (prefijo m* en
 * rodata: mMotionEvent_getX, mSoundPool_play, ...) y que el jni-analyze del
 * toolkit no generó (solo cubrió 10 clases). Curados contra jadx + firmas
 * reales de android.jar. FalsoJNI resuelve SOLO por nombre (sin clase). */
#include <falso_jni/FalsoJNI.h>
#include <falso_jni/FalsoJNI_Impl.h>
#include <falso_jni/FalsoJNI_Logger.h>
#undef fjni_logv_dbg
#define fjni_logv_dbg(fmt, ...) _fjni_log_debug(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "utils/input.h"
#include "utils/logger.h"
#include "cached_jni_stubs.h"

#ifndef DATA_PATH
#define DATA_PATH "ux0:data/gtracinghyundaiedition/"
#endif

static jobject xstr(const char *s) {
    return (jobject)jni->NewStringUTF(&jni, s);
}

/* ---- android.view.MotionEvent (estado de source/utils/input.c) ---- */
jint stubx_MotionEvent_getAction(jmethodID id, va_list args) { return input_touch_action(); }
jint stubx_MotionEvent_getPointerCount(jmethodID id, va_list args) { return input_touch_count(); }
jint stubx_MotionEvent_getPointerId(jmethodID id, va_list args) { return 0; }
jfloat stubx_MotionEvent_getX(jmethodID id, va_list args) { return input_touch_x(0); }
jfloat stubx_MotionEvent_getY(jmethodID id, va_list args) { return input_touch_y(0); }
jfloat stubx_MotionEvent_getRawX(jmethodID id, va_list args) { return input_touch_x(0); }
jfloat stubx_MotionEvent_getRawY(jmethodID id, va_list args) { return input_touch_y(0); }

/* ---- android.view.Display / WindowManager ---- */
jint stubx_Display_getWidth(jmethodID id, va_list args) { return 960; }
jint stubx_Display_getHeight(jmethodID id, va_list args) { return 544; }
jobject stubx_WindowManager_getDefaultDisplay(jmethodID id, va_list args) { return NULL; }

/* ---- java.lang.System ---- */
jlong stubx_System_currentTimeMillis(jmethodID id, va_list args) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (jlong)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
void stubx_System_exit(jmethodID id, va_list args) {
    jint code = (jint)va_arg(args, int);
    fjni_logv_dbg("[JNI] System.exit(%d): ignorado en triage", (int)code);
}

/* ---- android.media.SoundPool (sin backend aún: handles falsos) ---- */
jint stubx_SoundPool_load(jmethodID id, va_list args) { return 1; }
jint stubx_SoundPool_play(jmethodID id, va_list args) { return 1; }
void stubx_SoundPool_play_void(jmethodID id, va_list args) { stubx_SoundPool_play(id, args); }
void stubx_SoundPool_pause(jmethodID id, va_list args) {}
void stubx_SoundPool_resume(jmethodID id, va_list args) {}
void stubx_SoundPool_stop(jmethodID id, va_list args) {}
void stubx_SoundPool_unload(jmethodID id, va_list args) {}
void stubx_SoundPool_release(jmethodID id, va_list args) {}
void stubx_SoundPool_setVolume(jmethodID id, va_list args) {}
void stubx_SoundPool_setRate(jmethodID id, va_list args) {}

/* ---- android.media.MediaPlayer (sin backend aún) ---- */
jobject stubx_MediaPlayer_create(jmethodID id, va_list args) { return NULL; }
void stubx_MediaPlayer_setDataSource(jmethodID id, va_list args) {}
void stubx_MediaPlayer_prepare(jmethodID id, va_list args) {}
void stubx_MediaPlayer_start(jmethodID id, va_list args) {}
void stubx_MediaPlayer_pause(jmethodID id, va_list args) {}
void stubx_MediaPlayer_stop(jmethodID id, va_list args) {}
void stubx_MediaPlayer_reset(jmethodID id, va_list args) {}
void stubx_MediaPlayer_release(jmethodID id, va_list args) {}
void stubx_MediaPlayer_setLooping(jmethodID id, va_list args) {}
void stubx_MediaPlayer_setVolume(jmethodID id, va_list args) {}
jboolean stubx_MediaPlayer_isPlaying(jmethodID id, va_list args) { return JNI_FALSE; }

/* ---- android.hardware.SensorManager (sin sensores: offline) ---- */
jobject stubx_SensorManager_getDefaultSensor(jmethodID id, va_list args) { return NULL; }
jboolean stubx_SensorManager_registerListener(jmethodID id, va_list args) { return JNI_FALSE; }
void stubx_SensorManager_unregisterListener(jmethodID id, va_list args) {}
jint stubx_Sensor_getType(jmethodID id, va_list args) { return 1; }

/* ---- android.media.AudioManager / net / telephony ---- */
jint stubx_AudioManager_getRingerMode(jmethodID id, va_list args) { return 2; }
jint stubx_AudioManager_getStreamVolume(jmethodID id, va_list args) { return 5; }
void stubx_AudioManager_setStreamMute(jmethodID id, va_list args) {}
jobject stubx_ConnectivityManager_getActiveNetworkInfo(jmethodID id, va_list args) { return NULL; }
jint stubx_NetworkInfo_getType(jmethodID id, va_list args) { return 1; }
jboolean stubx_NetworkInfo_isConnected(jmethodID id, va_list args) { return JNI_FALSE; }
jobject stubx_Context_getSystemService(jmethodID id, va_list args) { return NULL; }

/* ---- android.app.Activity / view / window ---- */
void stubx_Activity_finish(jmethodID id, va_list args) {}
jobject stubx_Activity_getIntent(jmethodID id, va_list args) { return NULL; }
jobject stubx_Activity_getWindow(jmethodID id, va_list args) { return NULL; }
jobject stubx_Activity_getWindowManager(jmethodID id, va_list args) { return NULL; }
jboolean stubx_Activity_hasWindowFocus(jmethodID id, va_list args) { return JNI_TRUE; }
void stubx_Activity_moveTaskToBack(jmethodID id, va_list args) {}
jboolean stubx_Activity_requestWindowFeature(jmethodID id, va_list args) { return JNI_TRUE; }
void stubx_Activity_setContentView(jmethodID id, va_list args) {}
void stubx_Activity_setVolumeControlStream(jmethodID id, va_list args) {}
void stubx_Activity_startActivity(jmethodID id, va_list args) {}
void stubx_Window_setFlags(jmethodID id, va_list args) {}
jint stubx_View_getVisibility(jmethodID id, va_list args) { return 0; }
void stubx_View_setVisibility(jmethodID id, va_list args) {}
void stubx_View_setBackgroundColor(jmethodID id, va_list args) {}
void stubx_View_setLayoutParams(jmethodID id, va_list args) {}
void stubx_ViewGroup_addView(jmethodID id, va_list args) {}
void stubx_ViewGroup_removeView(jmethodID id, va_list args) {}
jobject stubx_TextView_getText(jmethodID id, va_list args) { return xstr(""); }
void stubx_TextView_setText(jmethodID id, va_list args) {}
void stubx_TextView_setGravity(jmethodID id, va_list args) {}
void stubx_TextView_setImeOptions(jmethodID id, va_list args) {}
void stubx_TextView_setInputType(jmethodID id, va_list args) {}
void stubx_TextView_setTextSize(jmethodID id, va_list args) {}
void stubx_TextView_setTypeface(jmethodID id, va_list args) {}
jobject stubx_EditText_getWindowToken(jmethodID id, va_list args) { return NULL; }
jboolean stubx_EditText_requestFocus(jmethodID id, va_list args) { return JNI_TRUE; }
void stubx_EditText_setFilters(jmethodID id, va_list args) {}
jboolean stubx_InputMethodManager_showSoftInput(jmethodID id, va_list args) { return JNI_FALSE; }
jboolean stubx_InputMethodManager_hideSoftInputFromWindow(jmethodID id, va_list args) { return JNI_FALSE; }

/* ---- android.os.Handler / Message ---- */
jobject stubx_Handler_obtainMessage(jmethodID id, va_list args) { trace_call("obtainMessage"); return NULL; }
jboolean stubx_Handler_sendEmptyMessage(jmethodID id, va_list args) { trace_call("sendEmptyMessage"); return JNI_FALSE; }
jboolean stubx_Handler_sendMessage(jmethodID id, va_list args) { trace_call("sendMessage"); return JNI_FALSE; }
jobject stubx_Message_obtain(jmethodID id, va_list args) { return NULL; }
void stubx_Message_sendToTarget(jmethodID id, va_list args) {}
void stubx_Message_setData(jmethodID id, va_list args) {}
void stubx_Message_setTarget(jmethodID id, va_list args) {}

/* ---- varios ---- */
void stubx_GL10_glClear(jmethodID id, va_list args) {}
jobject stubx_GL10_glGetString(jmethodID id, va_list args) { return xstr("VitaGL"); }
jobject stubx_Typeface_create(jmethodID id, va_list args) { return NULL; }
jobject stubx_Uri_parse(jmethodID id, va_list args) { return NULL; }
jobject stubx_URL_init(jmethodID id, va_list args) { return NULL; }
jobject stubx_URL_openConnection(jmethodID id, va_list args) { return NULL; }
void stubx_URLConnection_connect(jmethodID id, va_list args) {}
jobject stubx_CharSequence_toString(jmethodID id, va_list args) { return xstr(""); }
jobject stubx_FileInputStream_getFD(jmethodID id, va_list args) { return NULL; }
jobject stubx_Intent_addCategory(jmethodID id, va_list args) { return NULL; }
jint stubx_Intent_getIntExtra(jmethodID id, va_list args) { return 0; }
void stubx_Intent_removeExtra(jmethodID id, va_list args) {}
void stubx_Intent_setFlags(jmethodID id, va_list args) {}

/* ---- GTRacing extras que pide el nativo ---- */
jobject stubx_GTRacing_getDisplayAd(jmethodID id, va_list args) { return xstr(""); }
jobject stubx_GTRacing_getFeaturedApp(jmethodID id, va_list args) { return xstr(""); }
jboolean stubx_GTRacing_isAllowToReload(jmethodID id, va_list args) { return JNI_FALSE; }
void stubx_GTRacing_resetDisplayTimeStamp(jmethodID id, va_list args) {}
void stubx_GTRacing_testInAppBilling(jmethodID id, va_list args) {}
jobject stubx_GTRacing_getCrtTimeStr(jmethodID id, va_list args) { return xstr("0"); }
jboolean stubx_MyVideoView_isVideoCompleted(jmethodID id, va_list args) { return JNI_TRUE; }

/* ---- java.util.Locale (GetDeviceLanguage en nativo) ---- */
jobject stubx_Locale_getDefault(jmethodID id, va_list args) { return NULL; }
jobject stubx_Locale_getLanguage(jmethodID id, va_list args) { return xstr("en"); }
jobject stubx_String_toLowerCase(jmethodID id, va_list args) { return xstr("en"); }

/* Rellena FieldsObject de strings con objetos JavaString válidos creados por NewStringUTF
 * para evitar que strcpy() o GetStringUTFChars desreferencien punteros raw o NULL. */
void hy_fields_init(void) {
    extern FieldsObject fieldsObject[];
    extern size_t fieldsObject_size(void);
    size_t n = fieldsObject_size() / sizeof(FieldsObject);

    static const struct {
        int id;
        const char *val;
    } s_strings[] = {
        { FID_WINDOW_SERVICE, "window" },
        { FID_SERIAL, "0123456789ABCDEF" },
        { FID_m_sDeviceID, "123456789012345" },
        { FID_m_sPhoneName, "Sony_Vita" },
        { FID_m_sFirmware, "4.4" },
        { FID_m_sDeviceName, "Vita" },
        { FID_MANUFACTURER, "Sony" },
    };

    for (size_t s = 0; s < sizeof(s_strings) / sizeof(s_strings[0]); s++) {
        for (size_t i = 0; i < n; i++) {
            if (fieldsObject[i].id == s_strings[s].id) {
                fieldsObject[i].value = (jobject)jni->NewStringUTF(&jni, s_strings[s].val);
                break;
            }
        }
    }
}

/* Dummy object constructor and methods for Android UI/Media classes */
jobject stubx_dummy_NewObject(jmethodID id, va_list args) { return (jobject)0x4242; }
void stubx_dummy_void(jmethodID id, va_list args) {}

/* ---- android.media.AudioTrack (backend SceAudioOut para vox::DriverAndroid) ----
 *
 * Único backend de audio real del juego: SFX y música los mezcla Vox por software
 * (DriverCallbackInterface::_FillBuffer) en su hilo UpdateThreadedAT y los empuja con
 * AudioTrack.write(byte[4096]) = 1024 frames s16 estéreo @44100 (ver ANALYSIS_NOTES §3).
 * los mSoundPool_xxx y mMediaPlayer_xxx se resuelven en nativeInit pero nunca se llaman.
 *
 * Android: write() bloquea solo cuando el buffer del track está lleno, y DoCallbackAT
 * además duerme m_updateTime (~23 ms) tras cada write mientras vaya adelantado. Con un
 * sceAudioOutOutput bloqueante directo en write() esa siesta extra provocaba underruns
 * (audio entrecortado). Por eso: cola de AT_SLOTS bloques + hilo de salida propio que
 * rellena con silencio si la cola se vacía (pause/Suspend de Vox) y mantiene el ritmo.
 *
 * FalsoJNI resuelve por nombre, así que los GetMethodID de AudioTrack caen en IDs
 * compartidos: play→206, pause→207, stop→209 (SoundPool, sin uso real) y release→79
 * (SUtils.release, stub vacío: el track se libera con stop). */
#include <psp2/audioout.h>
#include <psp2/kernel/threadmgr.h>

#define AT_GRAIN  1024              /* frames por bloque = getMinBufferSize/4 */
#define AT_SLOTS  4                 /* ~93 ms de cola */
#define AT_BYTES  (AT_GRAIN * 4)

static int16_t s_at_ring[AT_SLOTS][AT_GRAIN * 2];
static int16_t s_at_silence[AT_GRAIN * 2];
static volatile int s_at_rd = 0, s_at_wr = 0;  /* índices de bloque */
static int s_at_fill = 0;                      /* bytes en el bloque de escritura parcial */
static volatile int s_at_playing = 0;
static volatile int s_at_drop = 0;             /* stop(): el hilo de salida vacía la cola */
static SceUID s_at_free = -1, s_at_used = -1;  /* semáforos: bloques libres / llenos */
static SceUID s_at_thread = -1;
static int s_at_port = -1;

static int at_output_thread(SceSize argc, void *argv) {
    for (;;) {
        if (s_at_drop) {
            while (sceKernelPollSema(s_at_used, 1) == 0) {
                s_at_rd = (s_at_rd + 1) % AT_SLOTS;
                sceKernelSignalSema(s_at_free, 1);
            }
            s_at_drop = 0;
        }
        const int16_t *buf = s_at_silence;
        int took = 0;
        if (s_at_playing && sceKernelPollSema(s_at_used, 1) == 0) {
            buf = s_at_ring[s_at_rd];
            took = 1;
        }
        sceAudioOutOutput(s_at_port, buf);   /* bloquea al ritmo del hardware */
        if (took) {
            s_at_rd = (s_at_rd + 1) % AT_SLOTS;
            sceKernelSignalSema(s_at_free, 1);
        }
    }
    return 0;
}

static void at_init(void) {
    if (s_at_port >= 0) return;
    s_at_port = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_BGM, AT_GRAIN, 44100, SCE_AUDIO_OUT_MODE_STEREO);
    if (s_at_port < 0) {
        l_error("[AudioTrack] sceAudioOutOpenPort falló: 0x%08X", (unsigned)s_at_port);
        return;
    }
    int vol[2] = { SCE_AUDIO_VOLUME_0DB, SCE_AUDIO_VOLUME_0DB };
    sceAudioOutSetVolume(s_at_port, SCE_AUDIO_VOLUME_FLAG_L_CH | SCE_AUDIO_VOLUME_FLAG_R_CH, vol);
    s_at_free = sceKernelCreateSema("hy_at_free", 0, AT_SLOTS, AT_SLOTS, NULL);
    s_at_used = sceKernelCreateSema("hy_at_used", 0, 0, AT_SLOTS, NULL);
    /* Speedhack (como Asphalt 5): audio fuera del Core 0, que queda para el motor/GL */
    s_at_thread = sceKernelCreateThread("hy_audio_out", at_output_thread, 0x10000100 - 10, 0x4000, 0,
                                        SCE_KERNEL_CPU_MASK_USER_1, NULL);
    if (s_at_free < 0 || s_at_used < 0 || s_at_thread < 0) {
        l_error("[AudioTrack] no se pudo crear sema/hilo (0x%08X 0x%08X 0x%08X)",
                (unsigned)s_at_free, (unsigned)s_at_used, (unsigned)s_at_thread);
        return;
    }
    sceKernelStartThread(s_at_thread, 0, NULL);
    l_info("[AudioTrack] SceAudioOut port %d abierto (44100 Hz estéreo, %d frames x %d bloques)",
           s_at_port, AT_GRAIN, AT_SLOTS);
}

jint stubx_AudioTrack_getMinBufferSize(jmethodID id, va_list args) {
    return AT_BYTES;
}

jobject stubx_AudioTrack_new(jmethodID id, va_list args) {
    jint stream = va_arg(args, jint), rate = va_arg(args, jint), chcfg = va_arg(args, jint);
    jint fmt = va_arg(args, jint), bufsz = va_arg(args, jint), mode = va_arg(args, jint);
    l_info("[AudioTrack] new(stream=%d rate=%d ch=0x%x fmt=%d buf=%d mode=%d)",
           stream, rate, chcfg, fmt, bufsz, mode);
    /* new() se llama desde vox::DriverAndroid::UpdateThreadedAT, el hilo que mezcla por
     * software todo el audio del juego: moverlo al Core 1 junto a hy_audio_out. */
    int aff = sceKernelChangeThreadCpuAffinityMask(0, SCE_KERNEL_CPU_MASK_USER_1);
    l_info("[AudioTrack] mezclador Vox -> Core 1 (0x%08X)", (unsigned)aff);
    at_init();
    return (jobject)0x4242;
}

void stubx_AudioTrack_play(jmethodID id, va_list args) {
    at_init();
    if (!s_at_playing) l_info("[AudioTrack] play()");
    s_at_playing = 1;
}

void stubx_AudioTrack_pause(jmethodID id, va_list args) {
    s_at_playing = 0;
}

void stubx_AudioTrack_stop(jmethodID id, va_list args) {
    s_at_playing = 0;
    s_at_fill = 0;      /* stop() llega desde el mismo hilo productor (UpdateThreadedAT) */
    s_at_drop = 1;
    l_info("[AudioTrack] stop()");
}

jint stubx_AudioTrack_write(jmethodID id, va_list args) {
    jobject obj = va_arg(args, jobject);
    jint offset = va_arg(args, jint);
    jint size = va_arg(args, jint);

    JavaDynArray *jda = (JavaDynArray *)obj;
    if (!jda || !jda->array || size <= 0) return 0;
    at_init();
    if (s_at_thread < 0) return size;   /* sin backend: descartar sin bloquear */

    static int s_logged = 0;
    if (!s_logged) { s_logged = 1; l_info("[AudioTrack] primer write(%d bytes)", size); }

    const uint8_t *src = (const uint8_t *)jda->array + offset;
    int left = size & ~3;
    while (left > 0) {
        if (s_at_fill == 0)
            sceKernelWaitSema(s_at_free, 1, NULL);   /* bloquea solo con la cola llena */
        int n = AT_BYTES - s_at_fill;
        if (n > left) n = left;
        memcpy((uint8_t *)s_at_ring[s_at_wr] + s_at_fill, src, n);
        s_at_fill += n; src += n; left -= n;
        if (s_at_fill == AT_BYTES) {
            s_at_fill = 0;
            s_at_wr = (s_at_wr + 1) % AT_SLOTS;
            sceKernelSignalSema(s_at_used, 1);
        }
    }
    return size;
}


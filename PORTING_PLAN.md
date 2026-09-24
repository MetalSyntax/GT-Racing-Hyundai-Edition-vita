# Plan de Port — GT Racing Hyundai Edition (PS Vita)

> Generado por psvita-port-toolkit el 2026-09-08. Punto de partida con lo detectado automáticamente --
confirmar todo con objdump/Ghidra/jadx a mano antes de asumirlo como cierto.

## 0. Contexto

- **Juego:** GT Racing Hyundai Edition
- **Paquete Java:** com.gameloft.android.ANMP.GloftGTHY
- **APK original:** `GT Racing Hyundai Edition 1.0.0_.apk`
- **TITLEID asignado:** `PSVGTRHE1`

**¿Motor conocido?** Revisar si algún port hermano (bajo la misma BASE_DIR) comparte motor antes de
reusar su código -- confirmar con símbolos JNI reales, no por analogía superficial.

## 1. Detección automática

- **ABI(s):** armeabi, armeabi-v7a
- **ABI elegida:** armeabi-v7a
- **Nota de arquitectura:** armeabi-v7a presente -> ARMv7 (hard-float/NEON disponible). El CPU de Vita (Cortex-A9) corre esto sin traducción. Hay más de una ABI (armeabi, armeabi-v7a) -- se eligió armeabi-v7a para el análisis.
- **Versión de GLES:** AndroidManifest.xml no declara glEsVersion -- usar heurística (GLES1 (pipeline fijo: glVertexPointer/glClearColorx/glTexParameterx))

## 2. .so encontrados (ABI armeabi-v7a)

- `gtracinghyundaiedition_extract/lib/armeabi-v7a/libGTRacing.so` (6581 KB)
- (ignorado: `._libGTRacing.so` de 4 KB — AppleDouble del Finder, no es un .so)


## 3. Exports JNI (convención `Java_*`) — verificados a mano 2026-09-22

`nm -D` sobre el .so real: **55 exports `Java_*` + `JNI_OnLoad` (`0x0013c5c4`)**.
(El texto anterior decía "no se encontraron" porque el toolkit había analizado el
AppleDouble `._libGTRacing.so`, no el .so real.)

- `JNI_OnLoad` — el loader SÍ debe llamarlo (a diferencia del port hermano Motor Academy).
- `GTRacing`: `nativeHandleMessage, nativeInit, nativeKeyboardEnabled, nativeOnAccuracyChanged, nativeOnCreate, nativeOnDestroy, nativeOnEditorAction, nativeOnKeyDown, nativeOnKeyUp, nativeOnPause, nativeOnRestart, nativeOnResume, nativeOnResumeSensor, nativeOnSensorChanged, nativeOnStart, nativeOnStop, nativeOnTouchEvent, nativeSetMotionEventHasSource, processTouchpadAsPointer, setPaths`
- `GameRenderer`: `nativeGameRenderer, nativeInit, nativeOnDrawFrame, nativeOnSurfaceChanged, nativeOnSurfaceCreated`
- `GameGLSurfaceView`: `nativeGameGLSurfaceView, nativeInit, nativeOnSizeChanged, nativeOnWindowFocusChanged, nativePause, nativeResume`
- `GLResLoader / GLiveMain / CustomFilter / EditTextField / IGPActivity / MyVideoView / FacebookGLSocialLib`: `nativeInit` (+ `nativeSetLogin`, `nativeOnKeyPreIme`, callbacks `nativeOnFB*`)
- `installer.GameInstaller / installer.GDRMPolicy`: `initNative, nativeStart, nativeGetDevID, getPublicKey, initNativeAP, nativeAllow, processServer, getConstString, setConst, setLongConst, setTime`


## 4. Checklist

- [x] Repo creado desde soloader-boilerplate, git init, .gitignore anti-DMCA.
- [x] APK decompilado (jadx) y .so decompilado(s) (Ghidra) -- ver sección 2/3.
- [x] Análisis del motor real (ciclo de vida nativo, reuso de otro port o boilerplate genérico). Ver §6.
- [x] Bootstrap del loader: so_file_load/so_relocate/so_resolve, primer build. Hecho 2026-09-22: `SO_PATH`→`libGTRacing.so`, `main.c` con secuencia jadx (JNI_OnLoad/setPaths/5×nativeInit/OnCreate/OnStart/OnResume/surface 960×544/loop OnDrawFrame), `build/eboot.bin` + `build/gtracinghyundaiedition.vpk` generados. Requiere `cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5` (vita.cmake pide CMake<3.5).
- [x] Tabla JNI (FalsoJNI): registrar exports + callbacks hacia "Java". Hecho 2026-09-22: 193 métodos cableados en `java.c` (generados desde `generated_jni_table.h` por script) + `generated_jni_stubs.c` en el build; curados paths/prefs (getSDFolder/getSaveFolder/getOBBFolder/getPathData/getPreferenceString/getVersionInstalled/getManufacture/isUseLowres/isWifiAlive). Resto de cuerpos = defaults pendientes de triage en hardware.
- [ ] Primer arranque en consola real.
- [ ] Gráficos (wrappers GL según versión detectada).
- [ ] Input, Audio, Assets, LiveArea/VPK.
- [ ] Pruebas en hardware real.

## 5. Herramientas

Este port se gestiona con **psvita-port-toolkit** (standalone, fuera de este repo). Desde el
toolkit: `Continuar con un port existente` → elegí esta carpeta (ya tiene `.psvita-toolkit.json`).

## Auto-detected lifecycle methods (psvita-toolkit)

Native methods whose name matches a well-known Android/GL app lifecycle hook --
these are the ones `main.c`/the loader most likely needs to call directly to
drive the game (there's no real Android `Activity`/`GLSurfaceView` calling them
for you).

- `com.gameloft.android.ANMP.GloftGTHY.CustomFilter.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.EditTextField.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnCreate(Bundle)`
- `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnDestroy(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnPause(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnResume(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnResumeSensor(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnStart(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnStop(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView.nativeOnWindowFocusChanged(boolean)`
- `com.gameloft.android.ANMP.GloftGTHY.GameRenderer.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.GameRenderer.nativeOnDrawFrame(GL10)`
- `com.gameloft.android.ANMP.GloftGTHY.GameRenderer.nativeOnSurfaceChanged(GL10, int, int)`
- `com.gameloft.android.ANMP.GloftGTHY.GameRenderer.nativeOnSurfaceCreated(GL10, EGLConfig)`
- `com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.KeyboardInput.nativeInit(void)`
- `com.gameloft.android.ANMP.GloftGTHY.KeyboardInput.nativeOnCreate(Bundle)`
- `com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib.nativeInit(void)`

## 6. Verificación manual (2026-09-22, `nm -D` + jadx — reemplaza la detección automática)

- **GLES1 confirmado:** 87 UND `gl*/egl*` (pipeline fijo + `*OES`: Framebuffer/Renderbuffer). Sin shaders propios en UND. Wrappers: vitaGL GLES1.
- **Audio nativo: ninguno** (sin OpenSL/OpenAL en UND) → el sonido pasa por callbacks Java (`GLMediaPlayer`); esos stubs FalsoJNI son load-bearing.
- **Ciclo de vida real (jadx `GTRacing.java`):** `setupPaths()` → `setPaths(sDFolder, filesDir, cacheDir)` con
  `sDFolder=/sdcard/Android/data/<pkg>/files/` y OBB en `/sdcard/Android/obb/<pkg>/`; `onCreate` →
  `GameRenderer.nativeInit() + GameGLSurfaceView.nativeInit() + EditTextField/CustomFilter.nativeInit() + GTRacing.nativeInit()` →
  `nativeOnCreate(bundle)` → `nativeOnStart/nativeOnResume` → loop `nativeOnDrawFrame` → `nativeOnPause/nativeOnStop/nativeOnDestroy`.
  `main.c` deberá replicar esa secuencia (hoy solo llama `JNI_OnLoad` + loop vacío).
- **Rutas cableadas al layout `ux0:data/gtracinghyundaiedition/`:** `source/reimpl/io.c:rewrite_android_path()`
  mapea `/sdcard/.../files/` → raíz de datos, `/sdcard/.../obb/<pkg>/` → carpeta OBB (602M, formato propietario
  `1024P600_cdVOXlQLw.FAK`, no zip), `/data/data/<pkg>` → `saves/` (`oconf.bar`, perfiles); `init.c` crea
  `saves/`, `logs/` y la carpeta del paquete al arrancar. Detalle en `port_progress.md`.
- **Port hermano Motor Academy:** misma familia Gameloft (5 clases GL iguales, GLES1-OES) pero generación
  anterior: 28 `Java_*`, SIN `JNI_OnLoad`, paquete `TBFV.GloftGTHP.ML`. No copiar su `main.c` 1:1 (allá no se
  llama `JNI_OnLoad`; aquí sí); sí reutilizar patrones (tabla FalsoJNI, wrappers GLES1-OES, input, assets).
- **Pendiente:** probar en consola real (un bug a la vez, skill `so-crash-triage`):
  desplegar `build/eboot.bin` + `ux0_data/gtracinghyundaiedition/` vía toolkit
  (`Continuar con un port existente`), leer log + `.psp2dmp` con `vita-parse-core`.
- **Notas de build (2026-09-22):** `lib/falso_jni` se trajo del port hermano Motor Academy
  (misma familia de boilerplate; `.gitmodules` pasado a HTTPS) + `converter.c` añadido al build;
  shim `fjni_logv_dbg(fmt,...)` con `##__VA_ARGS__` (igual que Motor Academy);
  `source/reimpl/egl.c` fuera del build — el vitaGL actual ya implementa todo EGL
  (los fake `eglInitialize/eglQueryString/...` daban multiple definition).

## 7. Avance sin consola (2026-09-22, todo estático + build verde)

- **Imports 100% cubiertos:** `nm -D` = 300 UND vs 741 en `dynlib.c` → solo faltaban
  `getuid` (→ret0), `inet_addr` y `modff` (reales de newlib). Sin audio nativo (0 imports):
  todo el sonido es `SoundManager` nativo + callbacks Java (`SoundPool`/`MediaPlayer`).
- **Contrato JNI real (rodata):** el .so cachea **110 method IDs** (`mMotionEvent_getX`,
  `mSoundPool_play`, `mMediaPlayer_*`, `mActivity_*`, `mDisplay_getWidth`, ...) en 30+
  clases Android — el jni-analyze solo cubrió 10. Añadidos **99 callbacks** como IDs
  193-291 en `source/cached_jni_stubs.c` (MotionEvent 7 con estado real, Display 960×544,
  System.currentTimeMillis real, SoundPool/MediaPlayer no-op con handles falsos,
  SensorManager→FALSE, NetworkInfo→desconectado, `MyVideoView.isVideoCompleted`→TRUE
  para no colgarse en vídeos). Total tabla: **292 métodos**.
- **Input:** `source/utils/input.c` (SceCtrl→keycodes DPAD/BACK/MENU despachados en el
  loop; táctil frontal→estado MotionEvent para los stubs). `nativeOnTouchEvent(MotionEvent)`
  queda latente: sin Activity real no hay objeto que pasar; el triage dirá si el nativo
  lo invoca solo.
- **Instalador omitido por diseño:** el flujo real pasa por `GameInstaller` (descarga OBB);
  con el OBB de 602M ya colocado se sigue la rama `sbStarted=true` (GTRacing.java:553-565).
  Nativos `GameInstaller_*`/`GDRMPolicy_*` sin llamar.
- **LiveArea OK:** icon0 128×128, pic0 960×544, startup 280×158, bg0 840×500, PNG indexados.
- **Orden corregido en `main.c`:** nativeInits → setPaths (era al revés; ver GTRacing.java:570-575).

## 8. Forense `decompiled/` (2026-09-22, sin consola)

- **OBB propietario, sin extraer:** header `AA 00 00 00 "1024P600_cdVOXlQLw.FAK"` + ZIP parcial
  al offset 453M con EOCD falso → el nativo lo lee con `vox::CZipReader::scanLocalHeader`
  (tolera el prefijo) vía `FileSystemInterface::SetArchive` + `SoundManager::SetArchivePack`.
  Los 29 paths `/sdcard/.../files/*` ausentes en `ux0_data/` son estado normal de primer
  arranque (en Android ese dir también empieza vacío; se puebla con perfiles). Nada que extraer.
- **Claves `getPreferenceString` reales (jadx):** SDFolder, mainFileName/MainFileName,
  PatchFileName/patchFileName, ExtraFile — todas cubiertas en el stub (nota el duplicado
  con distinta capitalización).
- **`nativeOnCreate` con Bundle=NULL es seguro** (Ghidra `out_ghidra.c:10016`): nunca toca
  param_3; usa thiz + fields estáticos. Pero exige 9 fields (`cGTRacing/cTypeface/4×iGTRacing_*`/
  `m_sPhoneName/m_sFirmware/m_sDeviceName`, IDs 2-10 en `java.c`) y `hy_fields_init()` antes
  (los 3 strings se `strcpy`ean sin NULL-check → crash si NULL). +3 métodos Locale
  (`getDefault/getLanguage/toLowerCase`→"en"). Total tabla: **295 métodos + 11 fields**.

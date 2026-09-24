1: # Plan de Port — GT Racing Hyundai Edition (PS Vita)
2: 
3: > Generado por psvita-port-toolkit el 2026-09-08. Punto de partida con lo detectado automáticamente --
4: confirmar todo con objdump/Ghidra/jadx a mano antes de asumirlo como cierto.
5: 
6: ## 0. Contexto
7: 
8: - **Juego:** GT Racing Hyundai Edition
9: - **Paquete Java:** com.gameloft.android.ANMP.GloftGTHY
10: - **APK original:** `GT Racing Hyundai Edition 1.0.0_.apk`
11: - **TITLEID asignado:** `PSVGTRHE1`
12: 
13: **¿Motor conocido?** Revisar si algún port hermano (bajo la misma BASE_DIR) comparte motor antes de
14: reusar su código -- confirmar con símbolos JNI reales, no por analogía superficial.
15: 
16: ## 1. Detección automática
17: 
18: - **ABI(s):** armeabi, armeabi-v7a
19: - **ABI elegida:** armeabi-v7a
20: - **Nota de arquitectura:** armeabi-v7a presente -> ARMv7 (hard-float/NEON disponible). El CPU de Vita (Cortex-A9) corre esto sin traducción. Hay más de una ABI (armeabi, armeabi-v7a) -- se eligió armeabi-v7a para el análisis.
21: - **Versión de GLES:** AndroidManifest.xml no declara glEsVersion -- usar heurística (GLES1 (pipeline fijo: glVertexPointer/glClearColorx/glTexParameterx))
22: 
23: ## 2. .so encontrados (ABI armeabi-v7a)
24: 
25: - `gtracinghyundaiedition_extract/lib/armeabi-v7a/._libGTRacing.so` (4 KB)
26: - `gtracinghyundaiedition_extract/lib/armeabi-v7a/libGTRacing.so` (6581 KB)
27: 
28: 
29: ## 3. Exports JNI (convención `Java_*`)
30: 
31: (no se encontraron exports `Java_*` -- confirmar a mano con objdump -T, puede que el motor registre con RegisterNatives en vez de convención de nombre)
32: 
33: 
34: ## 4. Checklist
35: 
36: - [x] Repo creado desde soloader-boilerplate, git init, .gitignore anti-DMCA.
37: - [x] APK decompilado (jadx) y .so decompilado(s) (Ghidra) -- ver sección 2/3.
38: - [ ] Análisis del motor real (ciclo de vida nativo, reuso de otro port o boilerplate genérico).
39: - [ ] Bootstrap del loader: so_file_load/so_relocate/so_resolve, primer build.
40: - [ ] Tabla JNI (FalsoJNI): registrar exports + callbacks hacia "Java".
41: - [ ] Primer arranque en consola real.
42: - [ ] Gráficos (wrappers GL según versión detectada).
43: - [ ] Input, Audio, Assets, LiveArea/VPK.
44: - [ ] Pruebas en hardware real.
45: 
46: ## 5. Herramientas
47: 
48: Este port se gestiona con **psvita-port-toolkit** (standalone, fuera de este repo). Desde el
49: toolkit: `Continuar con un port existente` → elegí esta carpeta (ya tiene `.psvita-toolkit.json`).
50: 
51: ## Auto-detected lifecycle methods (psvita-toolkit)
52: 
53: Native methods whose name matches a well-known Android/GL app lifecycle hook --
54: these are the ones `main.c`/the loader most likely needs to call directly to
55: drive the game (there's no real Android `Activity`/`GLSurfaceView` calling them
56: for you).
57: 
58: - `com.gameloft.android.ANMP.GloftGTHY.CustomFilter.nativeInit(void)`
59: - `com.gameloft.android.ANMP.GloftGTHY.EditTextField.nativeInit(void)`
60: - `com.gameloft.android.ANMP.GloftGTHY.GLUtils.Device.nativeInit(void)`
61: - `com.gameloft.android.ANMP.GloftGTHY.GLUtils.SUtils.nativeInit(void)`
62: - `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeInit(void)`
63: - `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnCreate(Bundle)`
64: - `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnDestroy(void)`
65: - `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnPause(void)`
66: - `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnResume(void)`
67: - `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnResumeSensor(void)`
68: - `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnStart(void)`
69: - `com.gameloft.android.ANMP.GloftGTHY.GTRacing.nativeOnStop(void)`
70: - `com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView.nativeInit(void)`
71: - `com.gameloft.android.ANMP.GloftGTHY.GameGLSurfaceView.nativeOnWindowFocusChanged(boolean)`
72: - `com.gameloft.android.ANMP.GloftGTHY.GameRenderer.nativeInit(void)`
73: - `com.gameloft.android.ANMP.GloftGTHY.GameRenderer.nativeOnDrawFrame(GL10)`
74: - `com.gameloft.android.ANMP.GloftGTHY.GameRenderer.nativeOnSurfaceChanged(GL10, int, int)`
75: - `com.gameloft.android.ANMP.GloftGTHY.GameRenderer.nativeOnSurfaceCreated(GL10, EGLConfig)`
76: - `com.gameloft.android.ANMP.GloftGTHY.IGPFreemiumActivity.nativeInit(void)`
77: - `com.gameloft.android.ANMP.GloftGTHY.KeyboardInput.nativeInit(void)`
78: - `com.gameloft.android.ANMP.GloftGTHY.KeyboardInput.nativeOnCreate(Bundle)`
79: - `com.gameloft.android.ANMP.GloftGTHY.glsociallib.facebook.FacebookAndroidGLSocialLib.nativeInit(void)`

---

## Estructura ux0_data/gtracinghyundaiedition (2026-09-22)

El port ahora trabaja contra esta estructura (carpeta `ux0_data/gtracinghyundaiedition/` del repo
= contenido de `ux0:data/gtracinghyundaiedition/` en la Vita):

- `libGTRacing.so` (6.4M, armeabi-v7a) — el .so real. `SO_PATH` apuntaba a `main.so`
  (inexistente) → corregido a `libGTRacing.so` en `CMakeLists.txt`.
- `assets/*.inject` (3 ficheros) — los sirve `AAssetManager_open` como `DATA_PATH + assets/`.
- `com.gameloft.android.ANMP.GloftGTHY/main.100...obb` (602M) — OBB propietario Gameloft
  (header `1024P600_cdVOXlQLw.FAK`, NO zip). El juego lo pide vía `getPathData()` como
  `/sdcard/Android/obb/<pkg>/<mainFileName>` → el rewrite lo mapea a esta carpeta.
- `res/...` — recursos del APK (se sirven vía stubs `GLResLoader`/FalsoJNI, no por path directo).
- `saves/` — destino de `/data/data/<pkg>` (`oconf.bar`, `Profile_Free`, QuestProfile.dat).
  Se crea al arrancar junto con `logs/` y la carpeta del paquete OBB (`init.c`).
- `logs/` — `vita_logs_dir` del toolkit (`ux0:/data/gtracinghyundaiedition/logs`).

### Rewrite Android→Vita (`source/reimpl/io.c:rewrite_android_path`, verificado en host)
Confirmado contra strings reales del .so (`/sdcard/.../files/AI.bin`, `.../UK.bar`,
`.../Profile_Free`, `/data/data/...`) y contra jadx (`GTRacing.getSDFolder/getPathData/setupPaths/setPaths`):

- `/sdcard/Android/data/<pkg>/files/` → `ux0:data/gtracinghyundaiedition/`
- `/sdcard/Android/obb/<pkg>/` → `ux0:data/gtracinghyundaiedition/<pkg>/`
- `/data/data/<pkg>` → `ux0:data/gtracinghyundaiedition/saves`
- `/sdcard/` (resto) → `ux0:data/gtracinghyundaiedition/` (fallback)

Aplicado en `fopen/open/stat/opendir_soloader`. Cubre tanto los ~30 paths hardcodeados
del .so como los que el nativo construya desde los `setPaths()` de Java.

Pendiente (requiere `git submodule update --init`, `lib/falso_jni` está vacío):
llamar `Java_..._GTRacing_setPaths(sDFolder, filesDir, cacheDir)` con los paths Vita
tras `JNI_OnLoad`, y build + prueba en consola real.

---

## Primer build (2026-09-22) — 5 de 8 checks en PORTING_PLAN.md

- **FalsoJNI:** traído del port hermano Motor Academy (misma familia, `so_util` idéntico) +
  `converter.c/jni.h` añadidos; `.gitmodules` pasado de SSH a HTTPS. `CMakeLists.txt` compila
  `FalsoJNI.c/ImplBridge/Logger/converter.c`.
- **Tabla JNI cableada:** `java.c` (448 líneas) generado por script desde `generated_jni_table.h`:
  193 métodos (object/boolean/void/int/float/long) + tablas byte/char/short/double vacías.
  `generated_jni_stubs.c` añadido al build + shim `fjni_logv_dbg` con `##__VA_ARGS__`
  (misma solución que Motor Academy).
- **Stubs curados contra jadx:** `getSDFolder×2`→`DATA_PATH`, `getSaveFolder`→`saves`,
  `getOBBFolder`→carpeta del paquete, `getPathData`→ruta `/sdcard/...obb` (la resuelve `io.c`),
  `getPreferenceString×2` (SDFolder/mainFileName/PatchFileName/ExtraFile/default),
  `getVersionInstalled/getCurrentVersion`→`1.0.0`, `getManufacture`→0, `isUseLowres`/
  `IsKeyboardEnabled`/`isWifiAlive`→FALSE (offline-safe en primer arranque),
  `getPreferenceBoolean/Int/Long`→default de Java, `getFreeSpace`→1024MB.
- **`main.c` reescrito** con la secuencia `GTRacing.onCreate`: `JNI_OnLoad` → `gl_init` →
  `setPaths()` con jstrings Vita → 5×`nativeInit` → `nativeOnCreate(NULL)`/`OnStart`/`OnResume` →
  `OnSurfaceCreated` + `OnSizeChanged(960,544)` + `OnSurfaceChanged(960,544)` + focus →
  loop `nativeOnDrawFrame` + `gl_swap()`. Thiz/objetos = NULL (triage dirá).
- **Fixes de build:** `reimpl/egl.c` fuera del build (el vitaGL actual implementa todo EGL —
  19 multiple definitions); `CMAKE_POLICY_VERSION_MINIMUM=3.5` para `vita.cmake`.
- **Resultado:** `build/eboot.bin` + `build/gtracinghyundaiedition.vpk` generados sin errores.
- **Siguiente (un bug a la vez):** desplegar eboot + `ux0_data/` en consola real vía toolkit,
  leer log + `.psp2dmp` (`vita-parse-core`), triage con skill `so-crash-triage`.

---

## Ronda estática sin consola (2026-09-22) — build verde con 292 métodos

- **UND vs dynlib:** 300 imports, 741 mapeos → añadidos `getuid/inet_addr/modff`. Cobertura 100%.
- **110 callbacks `m*` en rodata** (FalsoJNI resuelve por nombre): 99 nuevos en
  `source/cached_jni_stubs.c` (IDs 193-291) + `source/utils/input.c` (botones/táctil).
  Clases cubiertas: MotionEvent, Display, System, SoundPool, MediaPlayer, SensorManager,
  AudioManager, ConnectivityManager, Activity/View/TextView/EditText, Handler/Message,
  GL10, Typeface/Uri/URL, Intent + extras GTRacing/MyVideoView.
- **File-backed:** `SUtils.ReadFile(String)`/`ReadFileByte(String)` leen de verdad (vía
  `hy_rewrite_path` compartido en `utils.c`); `WriteFile×2` escriben con mkdirs (oconf.bar,
  perfiles); `ReadFile(int)`→`""`; Device/GTRacing IMEI/Mac/UniqueId→dummies estables.
- **`main.c`:** orden real (inits→setPaths), `input_init/poll`, despacho
  `nativeOnKeyDown/Up` con KeyEvent=NULL, loop con throttle por vsync (`gl_swap`).
- **LiveArea verificado** (dimensiones + PNG indexados). **Instalador omitido** (OBB pre-colocado).
- `build/eboot.bin` + `.vpk` regenerados sin errores tras cada cambio.
- Riesgos anotados para el triage: `nativeOnCreate(NULL bundle)`, `System.exit`→no-op,
  `obtainMessage/sendMessage`→NULL/FALSE, audio sin backend (handles falsos).

---

## Forense decompiled (2026-09-22)

- **OBB (602M): no se extrae.** `vox::CZipReader` + `SetArchive` lo leen directo; los 29
  assets `/sdcard/...` ausentes son estado normal de primer arranque. `copy.inject` sí es
  ZIP (UI del downloader); `adsimage/class.inject` van cifrados (instalador, omitido).
- **Prefs jadx:** 6 claves reales cubiertas (incl. `patchFileName` minúscula).
- **Ghidra `nativeOnCreate` (out_ghidra.c:10016):** Bundle=NULL seguro; requiere 9 fields
  nuevos (IDs 2-10) + `hy_fields_init()` (strcpy sin NULL-check) + Locale→"en".
  Tabla: **295 métodos + 11 fields**. VPK reconstruido verde.

---

## Fase: Diagnóstico de Menú, Audio y Pantalla Blanca en Carrera (2026-09-23)
- **Progreso en Consola Real:**
  - Menús del juego completamente navegables mediante pantalla táctil frontal a 960x544.
  - Mapeo de controles estilo consola analógico verificado: freno (L/Cuadrado), acelerador (R/Cruz).
  - `ControlsMenu::IsComboValid` parcheado a 1 para permitir cualquier combinación de botones.
  - Se alcanzó la selección de la prueba de licencia 350 (`006.log`).
- **Diagnóstico de Pantalla Blanca al Cargar:**
  - Tras liberar texturas de menús y cargar `LoadingMenuHD.swf`, el juego envía telemetría de red a `ets.gameloft.com`.
  - Posible bloqueo por FBO sin restaurar o espera síncrona de socket en `CAndroidSocket`.
- **Ingeniería Inversa del Sistema de Audio (`VoxEngine` / `AudioTrack`):**
  - `libGTRacing.so` utiliza un sintetizador C++ en un hilo POSIX en segundo plano (`DriverAndroid::UpdateThreadedAT`).
  - El hilo realiza mezcla por software con `_FillBuffer` y envía bloques PCM de 4096 bytes (1024 frames) vía `AudioTrack.write`.
  - Confirmado en desensamblado que la inicialización requería `VoxSetJavaVM` y resolución precisa de offsets en `JNINativeInterface` (FindClass, GetMethodID, GetStaticMethodID, NewByteArray, GetPrimitiveArrayCritical, CallNonvirtualIntMethod).
- **Documentación Técnica y Scripts:**
  - Creado [`ANALYSIS_NOTES.md`](file:///Volumes/Seagate/PSVITA%20Develop/GT-Racing-Hyundai-Edition-vita/ANALYSIS_NOTES.md) con todas las notas detalladas y 4 herramientas en Python desarrolladas para inspeccionar literales ARM, relocalizaciones GOT y offsets JNI.
---

## Bug: congelado tras elegir la primera opción del tutorial (011.log, 2026-09-24)

- **Síntoma:** pantalla blanca con restos de UI ("Drag Track / Braking 1 / Length"); watchdog
  `onDraw sin retornar` en frame 498 con ~900k llamadas/s a `fread`/`fwrite` y 0 bytes de avance,
  justo tras `fopen(tracking_data2.dat, rb)` + `fopen(tracking_data1.dat, wb)`.
- **Causa real (Ghidra out_ghidra.c:644178):** el TrackingManager copia el archivo de tracking con
  `fseek(END)` → `ftell` → `rewind` → `fseek(off, CUR)` y luego
  `for (left = size - off; left > 0; left -= fread(...))`. `rewind` estaba mapeado a la de **newlib**
  mientras los `FILE*` son de **SceLibcBridge** → la posición quedaba en EOF, `fread` devolvía 0 y
  el bucle nunca terminaba.
- **Fix:** `rewind_soloader`/`fseeko_soloader`/`ftello_soloader` en `source/reimpl/io.c` usando
  `sceLibcBridge_fseek/ftell`, mapeados en `dynlib.c` (antes `rewind`/`fseeko`/`ftello` de newlib).
- Estado: build verde, **pendiente de verificar en consola**.
- **Verificado en consola (012.log):** el congelamiento por `rewind` desapareció; se llega al tutorial.

---

## Ronda 2026-09-24 (012.log + dump 1790258054): crash FFP, pantalla blanca, audio

- **Crash (dump 1790258054):** data abort en `reload_ffp_shaders` (vitaGL `ffp.c:947`),
  `memcpy` con src=NULL (R1=0): `shark_compile_shader_extended` devolvió NULL (fallo de
  vitaShaRK) y upstream no lo comprueba. **Fix (vitaGL):** `ffp_compile_checked()` vuelca
  fuente+log a `ux0:data/shader_cache/ffp_fail_*.txt`, avisa al port (`vgl_ffp_compile_failed`
  → `l_error` con heap libre), reinicia el compilador y reintenta; si el fragment sigue fallando
  reintenta sin combiner (todo MODULATE) y como último recurso reutiliza el último shader del
  caché RAM. `HAVE_SHARK_LOG=1` para tener el error real del compilador en el próximo log.
- **Pantalla blanca (sospecha fuerte):** `LibEffects::saveTUStates/restoreTUSetup` guarda el estado
  de las 2 unidades de textura con `glGetTexEnviv`+`glGetTexEnvfv` y lo restaura con
  `glTexEnviv`+`glTexEnvfv`. `glTexEnviv` y `glGetTexEnvfv` estaban mapeados a `ret0` → el combiner
  del efecto de postproceso quedaba aplicado a todo lo dibujado después. **Fix:** ambas
  implementadas en vitaGL (`ffp.c`) y mapeadas en `dynlib.c`.
- **Audio (ANALYSIS_NOTES §3):** backend `AudioTrack` reescrito en `cached_jni_stubs.c`: cola de
  4×1024 frames + hilo `hy_audio_out` (SceAudioOut BGM 44100 estéreo) que rellena con silencio;
  `write()` bloquea solo con la cola llena (semántica Android; antes el write bloqueante + la
  siesta de `DoCallbackAT` producía underruns). `NewObject(AudioTrack)`, `play`(206),
  `pause`(207), `stop`(209) conectados (IDs compartidos con SoundPool, que el juego no usa).
  Logs `[AudioTrack]` a nivel info.
- Estado: build verde, **pendiente de probar en consola**.

---

## v0.1.0-beta (2026-09-24, 013.log) — speedhacks, diagnóstico de la pantalla de carga, release

- **013.log:** sin crash; audio vivo (`[AudioTrack] play()` + primer write); sin fallos de vitaShaRK.
- **Pantalla blanca = pantalla de carga** (captura de video de referencia): debería mostrar el fondo
  (auto + panel oscuro, Texture 162 vía `LoadETC`), pero en la Vita solo se ve el texto. Hipótesis:
  textura inválida en vitaGL → se dibuja sin textura (blanco). Diagnóstico agregado:
  wrappers `glCompressedTexImage2D/glTexImage2D_soloader` que loguean subidas ≥256x256 y marcan
  `textura SIN memoria` si `vglGetTexDataPointer` queda NULL.
- **Speedhacks seguros (estilo Asphalt 5):** logger con buffer de 32 KB (antes write+fsync por
  línea), pool de `FILE*` de lectura para `.obb`/`Sounds.pak` (hasta ~300 fopen/60 frames), mezclador
  Vox + `hy_audio_out` en Core 1, watchdog en Core 2 (y flush del log cada 5 s), `HY_RELEASE=ON`
  sin `l_debug`. No se agregaron flags *SPEEDHACK de vitaGL marcados "may cause crashes".
- **Release:** README estandarizado, `RELEASE_NOTES.md`, primer commit, paquete
  `release/GTRacingHyundaiEdition-Vita-v0.1.0-beta.zip` (VPK del build de release).

# Notas de Investigación Técnica — GT Racing Hyundai Edition (PS Vita)

Fecha: 23 de septiembre de 2026  
Autor: Antigravity & Pair Programmer  
Proyecto: Port de *GT Racing: Hyundai Edition* (Gameloft, 2012) a PlayStation Vita (`soLoader` + `FalsoJNI` + `vitaGL`)

---

## 1. Resumen Ejecutivo del Estado del Port

| Componente | Estado Actual | Observaciones |
| :--- | :--- | :--- |
| **Arranque / EBOOT** | ✅ Operativo | Carga `libGTRacing.so` a `0x98000000`, relocaliza e inicializa BSS/GOT sin crashes. |
| **Pantalla / Gráficos** | ⚠️ Parcial | Menús y SWF (Flash) renderizan correctamente a 960x544. Pantalla blanca tras pulsar "Iniciar Carrera/Licencia". |
| **Entrada / Controles** | ✅ Operativo | Pantalla táctil frontal (960x544), stick analógico y botones mapeados (L/Cuadrado freno, R/Cruz acelerador). Parches en `ControlsMenu::IsComboValid` y `ResetControls` aplicados. |
| **Sistema de Logs** | ✅ Operativo | Logs persistentes incrementales (`001.log` a `999.log`). Diseñado mecanismo de colapso de mensajes duplicados `(xN)`. |
| **Audio (SFX / Música)** | 🔍 Diagnosticado | Motor de sonido propietario de Gameloft (`VoxEngine` / `DriverAndroid`). Utiliza `AudioTrack` mediante hilos POSIX y callbacks JNI nativos. Silenciado en menús por dependencias JNI y nivel de log de FalsoJNI. |

---

## 2. Investigación Detallada de la Pantalla Blanca (Transición a Carrera / Licencia)

### 2.1. Trazabilidad del Log (`logs/006.log`)
Al pulsar sobre la prueba de licencia 350 (`ET_TUTORIAL_FIRST_STARTED`), el motor ejecuta la siguiente secuencia de eventos antes de quedar en blanco:
1. **Limpieza de Recursos de Menú:**
   ```
   Freeing texture 20980
   Freeing texture 36350
   Freeing object 342
   Freeing texture 11001
   Freeing texture 40950
   Freeing object 950
   Freeing texture 40951
   Freeing object 951
   ```
2. **Carga de Pantalla de Carga:**
   ```
   GetObfuscateFilename = /LoadingMenuHD.swf
   startPtr = 854x480_LoadingMenuHD.swf
   Texture::LoadETC()
   Texture Loaded: 162 (type 15001)
   Before loading game - Menu Cleaning not done
   Freeing texture 1000
   Freeing object 900
   !!!! DISABLE GYROSCOPE/ACCELEROMETER
   ```
3. **Intentos de Red y Telemetría Gameloft:**
   ```
   [libGLXPlayer] CAndroidSocket::ConnectByName(): GetHostByName() err = 0
   [libGLXPlayer] CAndroidSocket::CloseSocket() [3]
   fopen(saves/tracking_data2.dat, rb)
   fopen(saves/tracking_data1.dat, wb)
   ```
4. **Punto de Congelamiento / Pantalla Blanca:**
   - No se produce ningún crash dump (`.psp2dmp`), la consola no se bloquea a nivel de kernel y los hilos siguen vivos.
   - La pantalla se torna blanca debido a uno de dos motivos identificados en ports hermanos de Gameloft (*Asphalt 5* y *GT Racing: Motor Academy HD*):
     1. **Estado de FBO de vitaGL:** Durante la transición, GameSWF o el loader de texturas FBO cambia el render target. Si un FBO queda vinculado y `glBindFramebuffer(GL_FRAMEBUFFER, 0)` no se restaura antes del render 3D o `vglSwapBuffers()`, vitaGL dibuja un búfer vacío o no inicializado (blanco/transparente).
     2. **Bucle de Espera de Red (Tracking / Conexión):** El tracking intenta enviar paquetes vía `CAndroidSocket` de forma síncrona o espera una respuesta de confirmación de paquete que nunca llega al no haber servidores activos.
     3. **Falta de Escenas Render Target:** El juego utiliza múltiples escenas de FBO simultáneas (`OES_framebuffer_object`). Requiere `vglSetupRenderTargetScenesNum(8, 8)` y `vglSetupDisplayRenderTarget(8)` para que vitaGL no quede esperando sincronización de GPU.

---

## 3. Arquitectura e Investigación del Sistema de Audio (`VoxEngine`)

### 3.1. Estructura Interna del Motor de Audio
A diferencia de otros juegos de Android que usan exclusivamente `SoundPool` o `MediaPlayer` desde Java, *GT Racing: Hyundai Edition* implementa una arquitectura híbrida de bajo nivel:
1. **`vox::VoxEngine`:** Motor de audio en C++ contenido en `libGTRacing.so`.
2. **`vox::DriverAndroid`:** Controlador de salida de audio para la plataforma Android.
3. **`android.media.AudioTrack`:** Backend de streaming PCM a 44100 Hz, 16 bits estéreo.
4. **`SoundManager`:** Administrador de alto nivel del juego que empaqueta SFX (`Sounds.pak`) y música.

### 3.2. Cadena de Inicialización Nativa Identificada
Cruzando el desensamblado de `libGTRacing.so` con el código Ghidra (`out_ghidra.c`):

```
JNI_OnLoad(JavaVM *vm, void *reserved)
   ├── javaVM = vm
   ├── Facebook_setJavaVM(vm)
   ├── VoxSetJavaVM(vm) ──> DriverAndroid::s_javaVM = vm (0x006aa860)
   └── AndroidOS_JNIOnload(vm)

Game::InitAppData()
   └── SoundManager::init() [0x00255a78]
         ├── VoxEngine::GetVoxEngine()
         ├── VoxSetAndroidAPILevel(api_level)
         └── VoxEngine::Initialize() [0x004af500]
               └── VoxEngineInternal::Initialize() [0x004be154]
                     └── vox::CreateDriver() [0x004b6510]
                           └── DriverAndroid::DriverAndroid() [0x004b64cc]
                                 └── DriverAndroid::Init() [0x004b6408]
                                       └── DriverAndroid::_InitAT() [0x004b60d0]
```

### 3.3. Análisis de `DriverAndroid::_InitAT()` [0x004b60d0]
1. Verifica si `DriverAndroid::s_javaVM` (offset `0x006aa860`) es no nulo. Si es NULL, sale inmediatamente y no inicializa el audio.
2. Llama a `vm->GetEnv(&env, JNI_VERSION_1_2)`.
3. Invoca `env->FindClass("android/media/AudioTrack")` y almacena la referencia global con `NewGlobalRef`.
4. Resuelve los métodos JNI de `AudioTrack`:
   - Constructor: `GetMethodID("<init>", "(IIIIII)V")`
   - Búfer mínimo: `GetStaticMethodID("getMinBufferSize", "(III)I")`
   - Reproducción: `GetMethodID("play", "()V")`
   - Pausa: `GetMethodID("pause", "()V")`
   - Parada: `GetMethodID("stop", "()V")`
   - Liberación: `GetMethodID("release", "()V")`
   - Escritura de PCM: `GetMethodID("write", "([BII)I")`
5. Llama a `AudioTrack.getMinBufferSize(44100, CHANNEL_OUT_STEREO, ENCODING_PCM_16BIT)` (retorna 4096 bytes / 1024 frames).
6. Crea el hilo de actualización de audio con `pthread_create(&this->m_thread, NULL, DriverAndroid::UpdateThreadedAT, this)`.

### 3.4. Bucle del Hilo de Audio `UpdateThreadedAT()` [0x004b5d90]
El hilo se ejecuta en segundo plano con el siguiente flujo:
1. Llama a `vm->AttachCurrentThread(&env, NULL)`.
2. Llama a `env->PushLocalFrame(2)`.
3. Crea la instancia Java con `env->NewObject(AudioTrack_class, AudioTrack_init, 3, 44100, 12, 2, 4096, 1)`.
4. Inicia la pista con `CallNonvirtualVoidMethod(AudioTrack, "play")`.
5. Aloca un búfer de transferencia con `env->NewByteArray(4096)`.
6. Enciende el flag activo: `this->m_isActive = 1` (`[r4, #8] = 1`).
7. **Bucle de mezcla:**
   - Si `this->m_isActive == 0`, sale del hilo.
   - Invoca `DriverAndroid::DoCallbackAT()`:
     - `GetPrimitiveArrayCritical(env, jarray, NULL)` para obtener el puntero directo a los bytes PCM.
     - `DriverCallbackInterface::_FillBuffer(pcm_ptr, 1024)`: el sintetizador de software de Gameloft mezcla los sonidos activos en el búfer.
     - `ReleasePrimitiveArrayCritical(env, jarray, pcm_ptr, 0)`.
     - `CallNonvirtualIntMethod(AudioTrack, AudioTrack_write, jarray, 0, 4096)`.
   - Si la pista se encuentra en pausa, duerme con `usleep`.

### 3.5. Causas Diagnosticadas del Audio Mudo en Menús
1. **Nivel de Registro Silencioso en FalsoJNI:**
   - En `lib/falso_jni/FalsoJNI.h`, `FALSOJNI_DEBUGLEVEL` estaba configurado por defecto en `FALSOJNI_DEBUG_WARN`.
   - Las llamadas a `fjni_logv_dbg("[AudioTrack] Opened sceAudioOut...")` no emitían texto a `006.log`, ocultando si el puerto de audio `sceAudioOut` se abrió con éxito o falló silenciosamente.
2. **Firma de Retorno de `play` en FalsoJNI:**
   - En `source/java.c`, `play` figuraba como `METHOD_TYPE_INT` (ID 206 para SoundPool), pero `UpdateThreadedAT` invoca `CallNonvirtualVoidMethod`. En FalsoJNI, la búsqueda por tipo de método debe coincidir en las tablas `methodsVoid` y `methodsInt`.
3. **Dependencia del Flag `is_active` (`[r4, #8]`):**
   - Cuando el juego intenta reproducir un efecto con `DriverAndroid::CreateDriverSource()`, revisa `ldrb r3, [r4, #8]`. Si el hilo de audio falló al iniciar o salió inmediatamente (por ejemplo, si `NewObject` o `AttachCurrentThread` fallaron), retorna NULL y no reproduce ningún sonido.

---

## 4. Herramientas Utilizadas en la Investigación

1. **`arm-vita-eabi-objdump` (vitasdk / binutils 2.36):**
   - Desensamblado quirúrgico de secciones `.text` en modo ARM de 32 bits (`-d --start-address=... --stop-address=...`).
   - Identificación de prólogos, epílogos, llamadas a PLT (`pthread_create`, `usleep`, `malloc`) e instrucciones vectoriales VFP/NEON.
2. **`arm-vita-eabi-readelf`:**
   - Inspección de cabeceras ELF, tablas de secciones (`-S`), tabla de símbolos dinámicos (`-s`) y relocalizaciones de dynamic linking (`-r`).
   - Mapeo de entradas de la GOT (`_GLOBAL_OFFSET_TABLE_`) y tipos `R_ARM_RELATIVE`.
3. **`arm-vita-eabi-nm`:**
   - Extracción de símbolos dinámicos exportados e importados (`-D`) con desmanglado C++ (`-C`).
4. **Ghidra 11.x (Decompilador a Pseudo-C):**
   - Lectura contextual de funciones de alto nivel en `decompiled/libGTRacing_armeabi-v7a/ghidra/out_ghidra.c`.
5. **Jadx (Java Decompiler):**
   - Inspección de la lógica de ciclo de vida de Android en `decompiled/apk_jadx/`.
6. **Python 3:**
   - Scripts automatizados para lectura binaria de ELF, cálculo de offsets relativos a `PC`, resolución de la GOT y auditoría de firmas JNI.

---

## 5. Código Python Desarrollado y Utilizado

A continuación se registran los scripts en Python creados durante la sesión para el análisis binario del ejecutable compartido `libGTRacing.so` y las cabeceras de FalsoJNI.

### 5.1. Script 1: Inspección de Pools de Literales y Offsets Relativos a PC en ARM
Permite resolver a qué direcciones absolutas y entradas de la GOT apuntan instrucciones del tipo `ldr r3, [pc, #offset]` y `add r4, pc, r4`.

```python
#!/usr/bin/env python3
"""
arm_literal_inspector.py
Inspecciona literales en libGTRacing.so para reconstruir direcciones de la GOT
y cadenas de caracteres referenciadas mediante direccionamiento relativo al PC.
"""
import struct
import sys

SO_PATH = "ux0_data/gtracinghyundaiedition/libGTRacing.so"

def read_uint32(data: bytes, offset: int) -> int:
    return struct.unpack("<I", data[offset:offset + 4])[0]

def dump_literal_pool(start_addr: int, stop_addr: int):
    with open(SO_PATH, "rb") as f:
        data = f.read()

    print(f"=== Literal Pool [0x{start_addr:x} - 0x{stop_addr:x}] ===")
    for addr in range(start_addr, stop_addr, 4):
        val = read_uint32(data, addr)
        # Verificar si apunta a una cadena imprimible
        str_val = ""
        if 0 <= val < len(data):
            end = data.find(b"\0", val)
            if end != -1 and (end - val) < 128:
                candidate = data[val:end]
                if all(32 <= b < 127 for b in candidate):
                    str_val = f" -> \"{candidate.decode('ascii')}\""
        print(f"0x{addr:08x}: 0x{val:08x}{str_val}")

if __name__ == "__main__":
    # Rango del literal pool de DriverAndroid::_InitAT()
    dump_literal_pool(0x004b6380, 0x004b6408)
```

---

### 5.2. Script 2: Resolución de la GOT (`_GLOBAL_OFFSET_TABLE_`) y Relocalizaciones
Calcula dinámicamente la entrada de la GOT que utiliza una función ARM y extrae el símbolo final en la sección `.bss` o `.data`.

```python
#!/usr/bin/env python3
"""
arm_got_resolver.py
Calcula la dirección en la GOT generada por las secuencias:
   ldr r4, [pc, #offset_got]
   ldr r3, [pc, #offset_entry]
   add r4, pc, r4
   ldr r3, [r4, r3]
"""
import struct

SO_PATH = "ux0_data/gtracinghyundaiedition/libGTRacing.so"

def resolve_got_entry(pc_inst_addr: int, got_pc_offset: int, entry_offset: int):
    with open(SO_PATH, "rb") as f:
        data = f.read()

    # En ARM de 32 bits, PC = dirección de la instrucción + 8
    pc = pc_inst_addr + 8
    got_base = pc + got_pc_offset
    got_entry_addr = got_base + entry_offset
    target_ptr = struct.unpack("<I", data[got_entry_addr:got_entry_addr + 4])[0]

    print(f"Instrucción en:      0x{pc_inst_addr:08x}")
    print(f"Base de la GOT:      0x{got_base:08x}")
    print(f"Entrada en la GOT:   0x{got_entry_addr:08x}")
    print(f"Dirección apuntada:  0x{target_ptr:08x}")
    return target_ptr

if __name__ == "__main__":
    # Parámetros extraídos del desensamblado de _InitAT (4b60e4 - 4b60f0)
    # 4b60e4: ldr r4, [pc, #676]  (valor = 0x001a319c)
    # 4b60e8: ldr r3, [pc, #680]  (valor = 0x0000214c)
    print("--- Resolviendo DriverAndroid::s_javaVM ---")
    resolve_got_entry(0x004b60ec, 0x001a319c, 0x0000214c)
```

---

### 5.3. Script 3: Extracción de Nombres de Símbolos por Índice en `.dynsym`
Permite resolver nombres desmanganillados y tipos de símbolos directamente desde las tablas dinámicas del archivo ELF cuando `arm-vita-eabi-nm` no encuentra tabla estándar.

```python
#!/usr/bin/env python3
"""
elf_dynsym_lookup.py
Lee la cabecera ELF de 32 bits, localiza .dynsym y .dynstr, y busca el símbolo por índice.
"""
import struct
import sys

SO_PATH = "ux0_data/gtracinghyundaiedition/libGTRacing.so"

def get_symbol_by_index(index: int):
    with open(SO_PATH, "rb") as f:
        data = f.read()

    # Offsets de secciones dinámicas para libGTRacing.so (32 bits)
    dynsym_offset = 0x021aec
    dynstr_offset = 0x06817c
    sym_entry_size = 16  # sizeof(Elf32_Sym)

    entry_pos = dynsym_offset + (index * sym_entry_size)
    st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack(
        "<IIIBBH", data[entry_pos:entry_pos + 16]
    )

    name_start = dynstr_offset + st_name
    name_end = data.find(b"\0", name_start)
    symbol_name = data[name_start:name_end].decode("latin1", errors="replace")

    print(f"Símbolo #{index}:")
    print(f"  Nombre:     {symbol_name}")
    print(f"  Valor:      0x{st_value:08x}")
    print(f"  Tamaño:     {st_size} bytes")
    print(f"  Sección ID: {st_shndx}")

if __name__ == "__main__":
    target_idx = int(sys.argv[1]) if len(sys.argv) > 1 else 15015
    get_symbol_by_index(target_idx)
```

---

### 5.4. Script 4: Auditoría de Índices y Offsets en `struct JNINativeInterface`
Mapea línea a línea todos los punteros a función de la interfaz JNI estándar y FalsoJNI para validar desreferencias indirectas del tipo `ldr pc, [r3, #offset]`.

```python
#!/usr/bin/env python3
"""
jni_table_audit.py
Analiza jni.h para calcular los byte offsets exactos de cada función en JNINativeInterface.
"""
import re

JNI_H_PATH = "lib/falso_jni/jni.h"

def audit_jni_offsets():
    with open(JNI_H_PATH, "r") as f:
        content = f.read()

    match = re.search(r"struct JNINativeInterface \{(.*?)\};", content, re.DOTALL)
    if not match:
        print("Error: struct JNINativeInterface no encontrada en jni.h")
        return

    body = match.group(1)
    fields = []
    for line in body.split("\n"):
        line = line.strip()
        if not line or line.startswith("/*") or line.startswith("*") or line.startswith("//"):
            continue
        # Buscar punteros a función: (*NombreFuncion)
        m_func = re.search(r"\(\*([A-Za-z0-9_]+)\)", line)
        if m_func:
            fields.append(m_func.group(1))
        else:
            # Miembros simples (reserved0, etc.)
            m_var = re.search(r"([A-Za-z0-9_]+);", line)
            if m_var:
                fields.append(m_var.group(1))

    print(f"Total miembros encontrados en JNINativeInterface: {len(fields)}")
    print(f"{'Índice':<6} | {'Offset (Dec)':<12} | {'Offset (Hex)':<12} | {'Nombre de Función'}")
    print("-" * 55)

    critical_offsets = [24, 84, 132, 320, 452, 704, 888, 892]
    for idx, name in enumerate(fields):
        offset = idx * 4  # Punteros de 4 bytes en ARM32
        if offset in critical_offsets or idx < 10:
            print(f"{idx:<6} | {offset:<12} | 0x{offset:<10x} | {name}")

if __name__ == "__main__":
    audit_jni_offsets()
```

---

## 6. Próximos Pasos Recomendados

1. **Corrección del Bucle de Logs Duplicados (`source/utils/logger.c`):**
   - Integrar búfer de deduplicación que mantenga el último mensaje y añada ` (xN)` para reducir los cientos de llamadas idénticas de eventos y E/S.
   - ✅ **Implementado (24-sep-2026):** `_log_print` retiene el último mensaje y colapsa rachas idénticas con formato `mensaje (xN)` (mismo standard que Motor-Academy-HD-vita); `WARN/ERROR/FATAL` hacen flush inmediato, `log_write_raw` vacía lo pendiente primero, `log_flush()` se llama en `fatal_error` y cada 60 frames del main loop. Build verificado (`gtracinghyundaiedition.vpk` regenerado).
2. **Activación y Verificación del Audio Nativo:**
   - Asegurar que `JNI_OnLoad` inicialice `VoxSetJavaVM(&jvm)` y `DriverAndroid::s_javaVM`.
   - Modificar los logs de depuración en `stubx_AudioTrack_write` para usar `l_info` en vez de `fjni_logv_dbg` para verificar la salida de sonido por `sceAudioOut`.
   - Implementar las variantes vacías/seguras de `pause`, `stop`, `release` en `java.c` con sus tipos JNI correspondientes (`METHOD_TYPE_VOID`).
3. **Solución a la Pantalla Blanca en la Carga de Carrera:**
   - Forzar el reseteo de FBO en el render loop (`glBindFramebuffer(GL_FRAMEBUFFER, 0)`).
   - Configurar `vglSetupRenderTargetScenesNum(8, 8)` y `vglSetupDisplayRenderTarget(8)` para soportar la cantidad de texturas intermedias que usa el motor de carreras 3D.
   - Anular cualquier llamada bloqueante de tracking en `CAndroidSocket` para evitar bucles de sincronización esperando conexiones HTTP caídas.
   - ✅ **Parcial (24-sep-2026, build verificado):** el reseteo FBO en `gl_swap()` y `vglSetupRenderTargetScenesNum(8,8)` ya estaban; el log 006 prueba que el hilo principal se **cuelga dentro de `onDraw`** tras "Menu Cleaning not done" (último heartbeat: 540 frames, sin dump = cuelgue, no crash). Aplicado: `connect_soloader()` en `source/dynlib.c` (connect no-bloqueante + select 8s → fallo rápido; con fallback al connect original si fcntl falla) + hilo watchdog en `source/main.c` que reporta `onDraw sin retornar NNNs` cada 10s. Si el próximo log muestra el watchdog SIN líneas de timeout de connect, el cuelgue no es red → sospechar deadlock de loader (pthread_cond/mutex) o bucle infinito en teardown de flashes.
   - ✅ **Causa raíz confirmada (010.log, 24-sep-2026):** el hilo principal gira a ~1M `fread`+`fwrite`/s sobre `saves/tracking_data1.dat` + `tracking_data2.dat` (identificados vía mapa FILE*→path en el watchdog) en la pantalla de info de licencia. `glot::TrackingManager::LoadEvents()` (0x0047a0b4, ARM) no converge con servidores caídos. **Fix:** parche en `source/patch.c` → `mov r0,#0; bx lr` (retorna "sin eventos", igual que primer arranque). Build verificado, pendiente prueba en consola.
   - ✅ **Rewind (011/012.log, 24-sep-2026):** el bucle de `tracking_data` se debía a `rewind` de newlib sobre `FILE*` de SceLibcBridge; wrappers `rewind/fseeko/ftello_soloader`. Confirmado en consola: se llega al tutorial.
   - ✅ **Estado TexEnv (24-sep-2026, build verificado):** `LibEffects::restoreTUSetup` restaura el combiner con `glTexEnviv`/`glTexEnvfv`, y `glTexEnviv`/`glGetTexEnvfv` eran `ret0` → implementadas en vitaGL. Pendiente de confirmar en consola si era la pantalla blanca.
   - ✅ **Crash FFP (dump 1790258054):** vitaShaRK devolvía NULL y vitaGL hacía memcpy desde NULL; ahora se reintenta con fallback y se vuelca `ux0:data/shader_cache/ffp_fail_*.txt`.
4. **Audio (24-sep-2026, build verificado):** `AudioTrack` = cola de 4 bloques de 1024 frames + hilo SceAudioOut propio; `play/pause/stop` conectados a los IDs 206/207/209; logs `[AudioTrack]` en info. Pendiente de oír en consola.

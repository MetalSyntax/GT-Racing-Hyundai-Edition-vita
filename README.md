# GT RACING: HYUNDAI EDITION — PS Vita Port

<p align="center">
  <img src="extras/livearea/pic0.png" width="700" alt="GT Racing Hyundai Edition PS Vita Banner" />
</p>

<p align="center">
  <b>Native port of GT Racing: Hyundai Edition (Gameloft) for PlayStation Vita and PlayStation TV.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-PS%20Vita%20%7C%20PS%20TV-003791.svg?style=flat-square&logo=playstation" alt="Platform PS Vita" />
  <img src="https://img.shields.io/badge/Title%20ID-PSVGTRHE1-ff69b4.svg?style=flat-square" alt="Title ID PSVGTRHE1" />
  <img src="https://img.shields.io/badge/Engine-Gameloft%20Proprietary-brightgreen.svg?style=flat-square" alt="Engine" />
  <img src="https://img.shields.io/badge/Renderer-vitaGL%20%28GLES%201.1%29-orange.svg?style=flat-square" alt="Renderer" />
  <img src="https://img.shields.io/badge/Status-Public%20Beta-yellow.svg?style=flat-square" alt="Status: Public Beta" />
</p>

---

## 📖 Description

**GT Racing: Hyundai Edition** is Gameloft's free-to-play Hyundai-branded spin-off of *GT Racing: Motor Academy*: license tests, cornering/braking/drag challenges and races with licensed Hyundai cars. Originally released for Android as version **1.0.0** (`com.gameloft.android.ANMP.GloftGTHY`).

This port runs the compiled native ARM library (`libGTRacing.so`) from the Android release directly on the PS Vita's ARM Cortex-A9 processor, using a custom dynamic loader (*soloader*) and an Android environment emulation layer (*FalsoJNI*), with [vitaGL](https://github.com/Rinnegatamante/vitaGL) providing hardware-accelerated GLES 1.1 rendering.

### 🎮 Current Status: Public Beta

The game boots, the menus work with touch and buttons, and the first license test / tutorial can be started and driven. This is an **early public beta**. Expect bugs, and please report them with a log (see [Reporting bugs](#-reporting-bugs)).

---

### ✨ What Works

- **Native ARM Execution**: `libGTRacing.so` runs natively on the Vita's CPU, with no emulation of the game logic.
- **Android Lifecycle Bootstrap**: `JNI_OnLoad` → `setPaths` → `nativeInit` → `nativeOnCreate/OnStart/OnResume` → surface created/changed at 960x544 → `nativeOnDrawFrame` loop.
- **OBB read in place**: the 600 MB `main.100.*.obb` is read directly by the engine's ZIP reader, so there is no extraction step.
- **vitaGL Graphics Pipeline**: GLES 1.1 fixed-function rendering at the Vita's native 960x544, including the texture combiner state used by the race post-effects (`glTexEnviv` / `glGetTexEnvfv`).
- **Native Audio**: Gameloft's Vox engine mixes all SFX and music in software and streams them through an emulated `android.media.AudioTrack`, backed by `sceAudioOut` (44.1 kHz stereo) with a dedicated output thread.
- **Physical Controls**: analog stick / D-Pad steering, R/Cross accelerate, L/Square brake, Start pause, Circle back.
- **Offline-safe**: Gameloft tracking, ads and online services are neutralized or fail fast, so the game never waits on dead servers.
- **Performance tweaks**: CPU at 444 MHz, audio threads moved off the main core, a pooled file-handle cache for the OBB/`Sounds.pak`, buffered logging, and vitaGL `DRAW_SPEEDHACK=2`.

---

### 🕹️ Controls

| Vita Input | Action |
|---|---|
| **Left Analog Stick** / **D-Pad Left/Right** | Steer Left / Right |
| **R Trigger** / **Cross (❌)** / **D-Pad Up** | Accelerate |
| **L Trigger** / **Square (🟥)** / **D-Pad Down** | Brake / Reverse |
| **Start** | Pause / In-Game Menu |
| **Circle (⭕)** | Back |
| **Touchscreen** | Menu navigation (full 960x544 touch mapping) |

---

### ⚠️ Known Issues

- **UI rendering**: a white/incomplete loading screen was fixed in this beta (texture unit 1 without unit 0). Please report any screen that still looks white or is missing elements.
- **Framerate drops** during race loading and the first time each new material is drawn. vitaGL compiles those shaders at runtime and caches them in `ux0:data/shader_cache/`, so later sessions get faster.
- **Online features** (Facebook, leaderboards, store, ads) are unavailable by design.
- Only the English locale has been tested.

---

## 📋 Prerequisites

1. A PS Vita or PS TV running Custom Firmware (**HENkaku** / **h-encore** / **Enso**), 3.60 or 3.65 recommended.
2. [**kubridge**](https://github.com/TheOfficialFloW/kubridge/releases) and [**FdFix**](https://github.com/TheOfficialFloW/FdFix/releases) installed in `ur0:tai/config.txt` under `*KERNEL`.
3. [**libshacccg.suprx**](https://github.com/Rinnegatamante/ShaRKBR33D/releases/latest) installed in `ur0:data/`. **Required**: the GLES1 pipeline compiles shaders at runtime.
4. A legally obtained copy of **GT Racing: Hyundai Edition v1.0.0** for Android (`com.gameloft.android.ANMP.GloftGTHY`): the `.apk` **and** its OBB (`main.100.com.gameloft.android.ANMP.GloftGTHY.obb`, ~600 MB).
5. About **700 MB** of free space on `ux0:`.

---

## 📦 Installation Instructions

1. Install `gtracinghyundaiedition.vpk` on your PS Vita using **VitaShell**.
2. Open the `.apk` as a ZIP archive and extract `lib/armeabi/libGTRacing.so`.
3. Copy `libGTRacing.so` to `ux0:data/gtracinghyundaiedition/`.
4. Create `ux0:data/gtracinghyundaiedition/com.gameloft.android.ANMP.GloftGTHY/` and copy the OBB file into it, keeping its original name.
5. Launch the game from your LiveArea.

### Final File Structure in `ux0:data/gtracinghyundaiedition/`

```text
ux0:data/gtracinghyundaiedition/
├── libGTRacing.so                                    <- from lib/armeabi/ in the APK
├── com.gameloft.android.ANMP.GloftGTHY/
│   └── main.100.com.gameloft.android.ANMP.GloftGTHY.obb   <- game data (~600 MB)
├── saves/                                            <- created by the game
└── logs/                                             <- 001.log, 002.log, ... (created by the port)
```

---

## 🐞 Reporting bugs

Every launch writes a numbered log to `ux0:data/gtracinghyundaiedition/logs/` (`001.log`, `002.log`, ...). When reporting a problem, please attach:

- the **latest log** from that folder;
- the crash dump, if the game crashed (`ux0:data/*.psp2dmp`);
- any `ux0:data/shader_cache/ffp_fail_*.txt` files (written if a shader fails to compile);
- a short description of where it happened, plus a screenshot if it's a visual bug.

---

## 🛠️ Building from Source

### Build Prerequisites

- [VitaSDK](https://vitasdk.org/) (softfp toolchain).
- Vita portlibs: `vitashark`, `kubridge`, `pthread`.
- CMake and Make.

vitaGL is vendored in `lib/vitagl` with a few port-specific patches (FFP shader-compile fallback, `glTexEnviv`, `glGetTexEnvfv`) and is built automatically.

### Build Steps

```bash
# Development build (full debug logging)
cmake -S . -B build -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build -j8

# Release build (no per-call debug logging, as shipped in the beta)
cmake -S . -B build-release -DHY_RELEASE=ON -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build-release -j8
```

This generates `eboot.bin` and `gtracinghyundaiedition.vpk` in the build directory.

---

## 🏗️ Project Structure

- `source/`: native loader (lifecycle, JNI stubs, GL wrappers, AudioTrack backend, input, binary patches).
- `lib/`: auxiliary libraries (`so_util`, `falso_jni`, `libc_bridge`, `kubridge`, `fios`, `sha1`, `vitagl`).
- `extras/`: LiveArea assets and `/proc` stand-ins (`cpuinfo`, `meminfo`).
- `PORTING_PLAN.md`: living porting plan and engine notes.
- `ANALYSIS_NOTES.md`: reverse-engineering notes (audio engine, white screen, JNI offsets).
- `port_progress.md`: bug-by-bug development log.
- `RELEASE_NOTES.md`: changes per release.

---

## ⚖️ Disclaimer

**GT Racing** and **Hyundai** are registered trademarks of their respective owners (Gameloft and Hyundai Motor Company). This project is an unofficial port. It is not affiliated with, endorsed by, or produced by Gameloft or Hyundai.

This repository does **not** contain any copyrighted game assets, proprietary binaries, or media files. Users must provide their own legally acquired copy of the original Android release to play the game on PS Vita.

---

## 👥 Credits and Acknowledgements

- **Gameloft**: original developers of GT Racing: Hyundai Edition.
- **TheFloW**: for `so_util`, `kubridge`, `FdFix`, and the foundational Android soloader techniques.
- **Rinnegatamante**: for `vitaGL`, `vitaShaRK` and invaluable contributions to the PS Vita homebrew ecosystem.
- **v-atamanenko**: for `FalsoJNI` and the soloader boilerplate architecture.
- **Vita Community**: for continuous support, testing, and feedback.

---

## License

This software is distributed under the terms of the MIT License. See [LICENSE](LICENSE) for details.

# Release Notes — GT Racing: Hyundai Edition (PS Vita)

## v0.1.0-beta — First public beta (2026-09-24)

**Package:** `GTRacingHyundaiEdition-Vita-v0.1.0-beta.zip` → `gtracinghyundaiedition.vpk` (Title ID `PSVGTRHE1`, app version 01.00)
**Game version required:** Android v1.0.0 (`com.gameloft.android.ANMP.GloftGTHY`), `lib/armeabi/libGTRacing.so` + `main.100.*.obb`.
See [README.md](README.md) for requirements and installation.

### Highlights
- Boots to the main menu; touch and physical-button navigation work.
- Recommended scheme: the game's **on-screen controls**, driven by the physical buttons. The brake/accelerator pedal buttons are hidden (transparent) but keep working.
- The first license test / tutorial can be started and driven.
- Sound effects and music play through the game's own Vox engine (emulated `AudioTrack` → `sceAudioOut`).

### Fixes since internal builds
- **Freeze after the first mandatory tutorial choice**: `rewind`/`fseeko`/`ftello` were resolved to newlib while the game's `FILE*` come from SceLibc. The tracking-file copy loop never ended.
- **Crash during the tutorial** (data abort in vitaGL `reload_ffp_shaders`): vitaGL now handles runtime shader-compile failures instead of copying from a NULL program.
- **Texture-combiner state leaking after race post-effects**: implemented `glTexEnviv` and `glGetTexEnvfv`, which were no-ops.
- **Invalid FFP shader with texture unit 0 disabled** (`undeclared identifier 'texenv0'`): vitaGL built with `UNPURE_TEXCOORDS=1`, FFP shader cache version bumped. This did **not** fix the white loading screen.
- **Choppy / missing audio**: `AudioTrack` backend rewritten with a 4×1024-frame queue and its own output thread. `play`/`pause`/`stop` are now wired up.

### Performance (safe tweaks)
- Pooled read-only file handles for the OBB and `Sounds.pak` (the game reopened them up to ~300 times per second).
- Buffered log file (previously one write + fsync per line) and no debug-level logging in release builds.
- Vox mixer and audio output threads pinned to CPU core 1, watchdog on core 2; core 0 stays free for the game and GL.
- CPU 444 MHz / GPU 222 MHz, vitaGL `DRAW_SPEEDHACK=2`, runtime shader cache in `ux0:data/shader_cache/`.

### Known issues
- **Only known open issue: white loading screen before a race.** Only the track map and the yellow titles are drawn; the background image, the dark translucent panel and the other texts are missing. The race loads and plays normally afterwards. `UNPURE_TEXCOORDS` did not help, and no `ffp_fail_*.txt` shader dumps are written, so it is not a shader-compile failure.

### Reporting bugs
Please attach the latest `ux0:data/gtracinghyundaiedition/logs/NNN.log`, any `ux0:data/*.psp2dmp`, and any `ux0:data/shader_cache/ffp_fail_*.txt`.

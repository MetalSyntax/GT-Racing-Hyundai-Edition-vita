/*
 * Copyright (C) 2026 GT-Racing-Hyundai-Edition-vita contributors
 *
 * input.c - Mapeo de controles completos (estilo Asphalt 5) para PS Vita
 */
#include "utils/input.h"
#include "utils/logger.h"

#include <so_util/so_util.h>

#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <string.h>

#define INPUT_TARGET_W 960
#define INPUT_TARGET_H 544

// El panel frontal reporta en 1920x1088; se escala a 960x544.
#define TOUCH_PANEL_W 1920
#define TOUCH_PANEL_H 1088

// Slots 0..3: Dedos reales en pantalla táctil
// Slot 4: START (Pausa en pantalla x=35, y=35)
// Slot 5: Dirección cruceta/stick (x=180 o x=780, y=380)
// Slot 6: Freno L/Cuadrado/Abajo (pedal izquierdo x=95, y=440)
// Slot 7: Acelerador R/Cruz/Arriba (pedal derecho x=930, y=440)
#define MAX_REAL_TOUCH_SLOTS 4
#define FAKE_SLOT_START 4
#define FAKE_SLOT_STEER 5
#define FAKE_SLOT_BRAKE 6
#define FAKE_SLOT_GAS   7

// Keycodes Android (GTRacing.onKeyDown/onKeyUp)
#define KEY_DPAD_UP    19
#define KEY_DPAD_DOWN  20
#define KEY_DPAD_LEFT  21
#define KEY_DPAD_RIGHT 22
#define KEY_CENTER     23
#define KEY_BACK       4
#define KEY_MENU       82

static fn_app_on_touch s_app_on_touch = NULL;
static fn_key_evt s_key_down = NULL;
static fn_key_evt s_key_up = NULL;
static fn_sensor_evt s_sensor = NULL;

static uint32_t s_prev_buttons = 0;

static int s_real_slot_active[MAX_REAL_TOUCH_SLOTS];
static int s_real_slot_x[MAX_REAL_TOUCH_SLOTS];
static int s_real_slot_y[MAX_REAL_TOUCH_SLOTS];

static int s_fake_brake = 0;
static int s_fake_gas = 0;
static int s_fake_steer_dir = 0;
static int s_fake_start = 0;

// Legacy MotionEvent state
static int s_legacy_touch_action = 1;
static int s_legacy_touch_count = 0;
static float s_legacy_touch_x = 0.0f;
static float s_legacy_touch_y = 0.0f;

void input_init(fn_app_on_touch touch_fn, fn_key_evt key_down, fn_key_evt key_up, fn_sensor_evt sensor) {
    s_app_on_touch = touch_fn;
    s_key_down = key_down;
    s_key_up = key_up;
    s_sensor = sensor;

    s_prev_buttons = 0;
    memset(s_real_slot_active, 0, sizeof(s_real_slot_active));

    s_fake_brake = 0;
    s_fake_gas = 0;
    s_fake_steer_dir = 0;
    s_fake_start = 0;

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    l_info("Input initialized: Front Touch (960x544) + Analog Controls enabled.");
}

static void touch_to_target(int px, int py, int *ox, int *oy) {
    *ox = (px * INPUT_TARGET_W) / TOUCH_PANEL_W;
    *oy = (py * INPUT_TARGET_H) / TOUCH_PANEL_H;
    if (*ox < 0) *ox = 0;
    if (*ox >= INPUT_TARGET_W) *ox = INPUT_TARGET_W - 1;
    if (*oy < 0) *oy = 0;
    if (*oy >= INPUT_TARGET_H) *oy = INPUT_TARGET_H - 1;
}

static void poll_real_touch(void) {
    SceTouchData touch;
    if (sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1) < 0) return;

    int seen[MAX_REAL_TOUCH_SLOTS] = {0};
    int active_cnt = 0;

    for (int i = 0; i < (int)touch.reportNum && i < MAX_REAL_TOUCH_SLOTS; i++) {
        int x, y;
        touch_to_target(touch.report[i].x, touch.report[i].y, &x, &y);
        seen[i] = 1;
        active_cnt++;

        if (i == 0) {
            s_legacy_touch_x = (float)x;
            s_legacy_touch_y = (float)y;
        }

        if (!s_real_slot_active[i]) {
            s_real_slot_active[i] = 1;
            s_real_slot_x[i] = x;
            s_real_slot_y[i] = y;
            if (i == 0) s_legacy_touch_action = 0; // DOWN
            if (s_app_on_touch) {
                s_app_on_touch(1, x, y, i); // 1 = press
            }
        } else if (s_real_slot_x[i] != x || s_real_slot_y[i] != y) {
            s_real_slot_x[i] = x;
            s_real_slot_y[i] = y;
            if (i == 0) s_legacy_touch_action = 2; // MOVE
            if (s_app_on_touch) {
                s_app_on_touch(2, x, y, i); // 2 = drag
            }
        }
    }

    for (int i = 0; i < MAX_REAL_TOUCH_SLOTS; i++) {
        if (s_real_slot_active[i] && !seen[i]) {
            s_real_slot_active[i] = 0;
            if (i == 0) s_legacy_touch_action = 1; // UP
            if (s_app_on_touch) {
                s_app_on_touch(0, s_real_slot_x[i], s_real_slot_y[i], i); // 0 = release
            }
        }
    }

    s_legacy_touch_count = active_cnt;
}

static void key_edge(void *env, uint32_t now, uint32_t before, uint32_t mask, int code) {
    int was = (before & mask) != 0, is = (now & mask) != 0;
    if (is && !was && s_key_down) s_key_down(env, NULL, code, NULL);
    if (!is && was && s_key_up) s_key_up(env, NULL, code, NULL);
}

static void poll_pad_and_controls(void *env) {
    SceCtrlData pad;
    if (sceCtrlPeekBufferPositive(0, &pad, 1) < 0) return;
    uint32_t now = pad.buttons;

    // 1. Navegación en menús mediante eventos de teclas
    key_edge(env, now, s_prev_buttons, SCE_CTRL_UP, KEY_DPAD_UP);
    key_edge(env, now, s_prev_buttons, SCE_CTRL_DOWN, KEY_DPAD_DOWN);
    key_edge(env, now, s_prev_buttons, SCE_CTRL_LEFT, KEY_DPAD_LEFT);
    key_edge(env, now, s_prev_buttons, SCE_CTRL_RIGHT, KEY_DPAD_RIGHT);
    key_edge(env, now, s_prev_buttons, SCE_CTRL_CROSS, KEY_CENTER);
    key_edge(env, now, s_prev_buttons, SCE_CTRL_CIRCLE, KEY_BACK);
    key_edge(env, now, s_prev_buttons, SCE_CTRL_START, KEY_MENU);

    if (s_app_on_touch) {
        // 2. Freno: L Trigger o Botón Cuadrado o Abajo
        int brake_down = (now & (SCE_CTRL_LTRIGGER | SCE_CTRL_SQUARE | SCE_CTRL_DOWN)) != 0;
        if (brake_down != s_fake_brake) {
            s_fake_brake = brake_down;
            s_app_on_touch(brake_down ? 1 : 0, 95, 440, FAKE_SLOT_BRAKE);
        }

        // 3. Acelerador: R Trigger o Botón Cruz o Arriba
        int gas_down = (now & (SCE_CTRL_RTRIGGER | SCE_CTRL_CROSS | SCE_CTRL_UP)) != 0;
        if (gas_down != s_fake_gas) {
            s_fake_gas = gas_down;
            s_app_on_touch(gas_down ? 1 : 0, 930, 440, FAKE_SLOT_GAS);
        }

        // 4. Dirección: Cruceta Izquierda/Derecha o Stick Analógico Izquierdo
        int steer_dir = 0;
        float synth_accel_x = 0.0f;

        if (now & SCE_CTRL_LEFT) {
            steer_dir = -1;
            synth_accel_x = -7.0f;
        } else if (now & SCE_CTRL_RIGHT) {
            steer_dir = 1;
            synth_accel_x = 7.0f;
        } else if (pad.lx < 90) {
            steer_dir = -1;
            synth_accel_x = ((float)(pad.lx - 128) / 128.0f) * 8.0f;
        } else if (pad.lx > 165) {
            steer_dir = 1;
            synth_accel_x = ((float)(pad.lx - 128) / 128.0f) * 8.0f;
        }

        if (steer_dir != s_fake_steer_dir) {
            if (s_fake_steer_dir != 0) {
                int old_x = (s_fake_steer_dir < 0) ? 180 : 780;
                s_app_on_touch(0, old_x, 380, FAKE_SLOT_STEER);
            }
            s_fake_steer_dir = steer_dir;
            if (steer_dir != 0) {
                int new_x = (steer_dir < 0) ? 180 : 780;
                s_app_on_touch(1, new_x, 380, FAKE_SLOT_STEER);
            }
        }

        // 5. Alimentar acelerómetro sintético directamente desde D-Pad y Stick analógico
        if (s_sensor) {
            s_sensor(env, NULL, 1, synth_accel_x, 1.0f, 0.0f);
        }

        // 6. Botón START -> Toque en el botón de Pausa (x=35, y=35)
        int start_down = (now & SCE_CTRL_START) != 0;
        if (start_down != s_fake_start) {
            s_fake_start = start_down;
            s_app_on_touch(start_down ? 1 : 0, 35, 35, FAKE_SLOT_START);
        }
    }

    s_prev_buttons = now;
}

/*
 * Pedales en pantalla invisibles: los botones físicos ya accionan freno/acelerador
 * (toques simulados sobre btnBrake/btnAccel). Se usa alpha 0 y NO SetVisible(false)
 * porque gameswf descarta los caracteres invisibles en el hit-test y los toques
 * simulados dejarían de llegar. RenderFX del HUD en *(g_pMainGameClass) + 0x1b00
 * (Ghidra: RenderFX::SetVisible(*(RenderFX **)(g_pMainGameClass + 0x1b00), "HUD.AccelBrake", ...)).
 * SetAlpha es seguro si el caracter no existe (Find devuelve NULL).
 */
extern so_module so_mod;
typedef void (*fn_RenderFX_SetAlpha)(void *self, const char *name, float alpha);
static void **s_pMainGameClass = NULL;
static fn_RenderFX_SetAlpha s_RenderFX_SetAlpha = NULL;
static int s_hud_syms = 0;

static void hide_pedal_buttons(void) {
    if (!s_hud_syms) {
        s_hud_syms = 1;
        s_pMainGameClass = (void **)so_symbol(&so_mod, "g_pMainGameClass");
        s_RenderFX_SetAlpha = (fn_RenderFX_SetAlpha)so_symbol(&so_mod, "_ZN8RenderFX8SetAlphaEPKcf");
        l_info("input: pedales en pantalla ocultos (alpha 0) -- g_pMainGameClass=%p SetAlpha=%p",
               s_pMainGameClass, s_RenderFX_SetAlpha);
    }
    if (!s_pMainGameClass || !s_RenderFX_SetAlpha) return;
    uint8_t *game = (uint8_t *)*s_pMainGameClass;
    if (!game) return;
    void *hud = *(void **)(game + 0x1b00);
    if (hud)
        s_RenderFX_SetAlpha(hud, "HUD.AccelBrake", 0.0f);
}

void input_poll(void *env) {
    poll_real_touch();
    poll_pad_and_controls(env);
    hide_pedal_buttons();
}

int input_touch_action(void) { return s_legacy_touch_action; }
int input_touch_count(void) { return s_legacy_touch_count; }
float input_touch_x(int index) { (void)index; return s_legacy_touch_x; }
float input_touch_y(int index) { (void)index; return s_legacy_touch_y; }

int input_consume_key_down(void) { return -1; }
int input_consume_key_up(void) { return -1; }

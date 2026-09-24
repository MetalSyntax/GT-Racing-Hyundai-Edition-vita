/*
 * Copyright (C) 2026 GT-Racing-Hyundai-Edition-vita contributors
 *
 * input.h - Mapeo de controles completos (estilo Asphalt 5) para PS Vita
 */
#ifndef HY_INPUT_H
#define HY_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*fn_app_on_touch)(int action, int x, int y, int id);
typedef int (*fn_key_evt)(void *env, void *thiz, int code, void *event);
typedef void (*fn_sensor_evt)(void *env, void *thiz, int sensorType, float x, float y, float z);

void input_init(fn_app_on_touch touch_fn, fn_key_evt key_down, fn_key_evt key_up, fn_sensor_evt sensor);
void input_poll(void *env);

/* MotionEvent: action 0=DOWN 1=UP 2=MOVE (backward compatibility) */
int input_touch_action(void);
int input_touch_count(void);
float input_touch_x(int index);
float input_touch_y(int index);

int input_consume_key_down(void);
int input_consume_key_up(void);

#ifdef __cplusplus
};
#endif

#endif // HY_INPUT_H

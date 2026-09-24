/*
 * Copyright (C) 2022-2024 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/**
 * @file  logger.h
 * @brief Logging utilities.
 */

#ifndef SOLOADER_LOGGER_H
#define SOLOADER_LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#define LT_DEBUG   0
#define LT_INFO    1
#define LT_WARN    2
#define LT_ERROR   3
#define LT_FATAL   4
#define LT_SUCCESS 5
#define LT_WAIT    6

#define l_info(...)    _log_print(LT_INFO,    __VA_ARGS__)
#define l_warn(...)    _log_print(LT_WARN,    __VA_ARGS__)
#define l_error(...)   _log_print(LT_ERROR,   __VA_ARGS__)
#define l_fatal(...)   _log_print(LT_FATAL,   __VA_ARGS__)
#define l_success(...) _log_print(LT_SUCCESS, __VA_ARGS__)
#define l_wait(...)    _log_print(LT_WAIT,    __VA_ARGS__)

#if defined(DEBUG_SOLOADER) || defined(DEBUG) || !defined(NDEBUG)
#define l_debug(...)   _log_print(LT_DEBUG,   __VA_ARGS__)
#else
#define l_debug(...)
#endif

void logger_init(void);
void log_write_raw(const char* text);
void log_flush(void);

/*
 * Trazador de última llamada bridge (diagnóstico de cuelgues): los wrappers
 * de E/S, pthread y red registran aquí su nombre al entrar. El watchdog de
 * main.c lo vuelca si onDraw deja de retornar, indicando en qué primitiva
 * está atascado el hilo (p.ej. "fread" vs "pthread_cond_wait"). Punteros a
 * literales: sin copias, sin locks, seguro ante cuelgue.
 */
void trace_call(const char *name);
const char *trace_last_name(void);
unsigned long long trace_last_us(void);
int trace_last_tid(void);
unsigned long long trace_count(void);
void _log_print(int t, const char* fmt, ...)
                __attribute__ ((format (printf, 2, 3)));

#ifdef __cplusplus
};
#endif

#endif // SOLOADER_LOGGER_H

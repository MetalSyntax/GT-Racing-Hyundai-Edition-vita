/*
 * Copyright (C) 2022-2024 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "utils/logger.h"

#include <psp2/kernel/clib.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <string.h>

#include <stdbool.h>
#include <stdatomic.h>

#define COLOR_RED    "\x1B[38;5;196m"
#define COLOR_PINK   "\x1B[38;5;212m"
#define COLOR_ORANGE "\x1B[38;5;202m"
#define COLOR_BLUE   "\x1B[38;5;32m"
#define COLOR_GREEN  "\x1B[32m"
#define COLOR_CYAN   "\x1B[36m"

#define COLOR_END    "\033[0m"

static SceKernelLwMutexWork _log_mutex;
static atomic_bool _log_mutex_ready = ATOMIC_VAR_INIT(false);
static SceUID _log_fd = -1;

static char buffer_a[2048];

/*
 * Colapso de mensajes repetidos (ANALYSIS_NOTES.md §6.1, mismo formato que
 * el port hermano GT-Racing-Motor-Academy-HD-vita): el juego emite cientos
 * de líneas idénticas seguidas (p.ej. "============== OnEvent ============"
 * 21x en 006.log, o caracteres sueltos del log char-by-char 54x). En vez de
 * escribir cada una, se retiene la última y solo se emite cuando llega un
 * mensaje distinto (o un nivel grave), añadiendo " (xN)" si N > 1.
 * Todo ocurre bajo el LwMutex ya tomado por _log_print/log_write_raw.
 */
static char s_prev_msg[1536] = {0};
static int s_prev_type = -1;
static unsigned int s_repeat_count = 0;

static void _write_clean_to_file(const char* text);
static void _file_flush(int sync);

static void _emit_log_line(int t, const char *msg, unsigned int count) {
    char with_count[1600];
    if (count > 1)
        sceClibSnprintf(with_count, sizeof(with_count), "%s (x%u)", msg, count);
    else
        sceClibSnprintf(with_count, sizeof(with_count), "%s", msg);

    switch (t) {
        case LT_DEBUG:
            sceClibSnprintf(buffer_a, sizeof(buffer_a), " %s• debug%s    %s\n",
                            COLOR_PINK, COLOR_END, with_count); break;
        case LT_INFO:
            sceClibSnprintf(buffer_a, sizeof(buffer_a), " %sℹ info%s     %s\n",
                            COLOR_BLUE, COLOR_END, with_count); break;
        case LT_WARN:
            sceClibSnprintf(buffer_a, sizeof(buffer_a), " %s⚠ warning%s  %s\n",
                            COLOR_ORANGE, COLOR_END, with_count); break;
        case LT_ERROR:
            sceClibSnprintf(buffer_a, sizeof(buffer_a), " %s⨯ error%s    %s\n",
                            COLOR_RED, COLOR_END, with_count); break;
        case LT_FATAL:
            sceClibSnprintf(buffer_a, sizeof(buffer_a), " %s! fatal%s    %s\n",
                            COLOR_RED, COLOR_END, with_count); break;
        case LT_SUCCESS:
            sceClibSnprintf(buffer_a, sizeof(buffer_a), " %s! success%s  %s\n",
                            COLOR_GREEN, COLOR_END, with_count); break;
        case LT_WAIT:
            sceClibSnprintf(buffer_a, sizeof(buffer_a), " %s… waiting%s  %s\n",
                            COLOR_CYAN, COLOR_END, with_count); break;
        default:
            return;
    }

    // Consola
    sceClibPrintf("%s", buffer_a);

    // Archivo con sync inmediato
    _write_clean_to_file(buffer_a);
}

static void _log_flush_pending(void) {
    if (s_repeat_count == 0)
        return;
    _emit_log_line(s_prev_type, s_prev_msg, s_repeat_count);
    s_repeat_count = 0;
    s_prev_type = -1;
    s_prev_msg[0] = '\0';
}

void log_flush(void) {
    if (!atomic_load_explicit(&_log_mutex_ready, memory_order_relaxed)) return;
    sceKernelLockLwMutex(&_log_mutex, 1, NULL);
    _log_flush_pending();
    _file_flush(1);
    sceKernelUnlockLwMutex(&_log_mutex, 1);
}

static const char *volatile g_trace_name = "boot";
static volatile unsigned long long g_trace_us = 0;
static volatile int g_trace_tid = 0;
static volatile unsigned long long g_trace_count = 0;

void trace_call(const char *name) {
    g_trace_us = (unsigned long long)sceKernelGetProcessTimeWide();
    g_trace_name = name;
    g_trace_tid = sceKernelGetThreadId();
    g_trace_count++;
}

const char *trace_last_name(void) {
    return g_trace_name;
}

unsigned long long trace_last_us(void) {
    return g_trace_us;
}

int trace_last_tid(void) {
    return g_trace_tid;
}

unsigned long long trace_count(void) {
    return g_trace_count;
}

static void _ensure_log_file_open(void) {
    if (_log_fd >= 0) return;

    // Crear directorios padres de forma recursiva/segura para Vita
    sceIoMkdir("ux0:data", 0777);
    sceIoMkdir("ux0:data/gtracinghyundaiedition", 0777);
    sceIoMkdir(DATA_PATH "logs", 0777);

    // Búsqueda incremental desde 001.log hasta 999.log
    char path[256];
    for (int i = 1; i <= 999; i++) {
        sceClibSnprintf(path, sizeof(path), DATA_PATH "logs/%03d.log", i);
        SceIoStat stat;
        if (sceIoGetstat(path, &stat) < 0) {
            _log_fd = sceIoOpen(path, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
            if (_log_fd >= 0) {
                sceClibPrintf("[LOGGER] Log file created: %s (fd=0x%x)\n", path, _log_fd);
                return;
            } else {
                sceClibPrintf("[LOGGER] Failed to create log file: %s (ret=0x%x)\n", path, _log_fd);
            }
        }
    }

    // Fallback: si se alcanzaron los 999 logs, sobrescribir 999.log
    if (_log_fd < 0) {
        sceClibSnprintf(path, sizeof(path), DATA_PATH "logs/999.log");
        _log_fd = sceIoOpen(path, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
        if (_log_fd >= 0) {
            sceClibPrintf("[LOGGER] Fallback log file created: %s\n", path);
        }
    }
}

void logger_init(void) {
    if (!atomic_load_explicit(&_log_mutex_ready, memory_order_relaxed)) {
        int ret = sceKernelCreateLwMutex(&_log_mutex, "log_lock", 0, 0, NULL);
        if (ret < 0) {
            sceClibPrintf("[LOGGER] Error: failed to create log mutex: 0x%x\n", ret);
            return;
        }

        _ensure_log_file_open();
        atomic_store_explicit(&_log_mutex_ready, true, memory_order_relaxed);
    }
}

/*
 * Speedhack: antes cada línea hacía sceIoWrite + sceIoSyncByFd (fsync a la tarjeta) en el
 * hilo que loguea -- con cientos de fopen/fclose por segundo eso era E/S síncrona pura en
 * el hilo principal. Ahora se acumula en s_fbuf y se escribe cuando se llena, en cada
 * log_flush() (~1 vez/s desde el main loop) y de inmediato ante WARN/ERROR/FATAL, así que
 * lo importante antes de un crash sigue quedando en disco.
 */
static char s_fbuf[32 * 1024];
static int s_flen = 0;

static void _file_flush(int sync) {
    if (_log_fd < 0) { s_flen = 0; return; }
    if (s_flen > 0) {
        sceIoWrite(_log_fd, s_fbuf, s_flen);
        s_flen = 0;
    }
    if (sync)
        sceIoSyncByFd(_log_fd, 0);
}

static void _write_clean_to_file(const char* text) {
    if (_log_fd < 0) return;

    char clean_buf[2048];
    int j = 0;
    int in_color = 0;
    for (int i = 0; text[i] != '\0' && j < (int)(sizeof(clean_buf) - 1); i++) {
        if (text[i] == '\x1B') {
            in_color = 1;
        } else if (in_color && text[i] == 'm') {
            in_color = 0;
        } else if (!in_color) {
            clean_buf[j++] = text[i];
        }
    }
    clean_buf[j] = '\0';
    if (j > 0) {
        if (s_flen + j > (int)sizeof(s_fbuf))
            _file_flush(0);
        memcpy(s_fbuf + s_flen, clean_buf, j);
        s_flen += j;
    }
}

void log_write_raw(const char* text) {
    if (!text || !*text) return;
    logger_init();
    if (!atomic_load_explicit(&_log_mutex_ready, memory_order_relaxed)) return;

    sceKernelLockLwMutex(&_log_mutex, 1, NULL);
    _log_flush_pending(); // conservar el orden: lo pendiente sale antes que el raw
    _write_clean_to_file(text);
    _file_flush(1);
    sceKernelUnlockLwMutex(&_log_mutex, 1);
}

void _log_print(int t, const char* fmt, ...) {
    logger_init();
    if (!atomic_load_explicit(&_log_mutex_ready, memory_order_relaxed)) return;

    sceKernelLockLwMutex(&_log_mutex, 1, NULL);

    if (t < LT_DEBUG || t > LT_WAIT) {
        sceKernelUnlockLwMutex(&_log_mutex, 1);
        return;
    }

    char current_msg[1536];
    va_list list;
    va_start(list, fmt);
    sceClibVsnprintf(current_msg, sizeof(current_msg), fmt, list);
    va_end(list);

    // Quitar saltos de línea finales para que el mismo evento con/sin '\n' colapse igual
    size_t len = strlen(current_msg);
    while (len > 0 && (current_msg[len - 1] == '\n' || current_msg[len - 1] == '\r'))
        current_msg[--len] = '\0';

    if (s_repeat_count > 0 && s_prev_type == t && strcmp(current_msg, s_prev_msg) == 0) {
        s_repeat_count++;
        sceKernelUnlockLwMutex(&_log_mutex, 1);
        return;
    }

    // Mensaje distinto: emitir lo pendiente colapsado y retener el nuevo
    _log_flush_pending();
    s_prev_type = t;
    strncpy(s_prev_msg, current_msg, sizeof(s_prev_msg) - 1);
    s_prev_msg[sizeof(s_prev_msg) - 1] = '\0';
    s_repeat_count = 1;

    // Niveles graves se emiten de inmediato: si hay crash justo después,
    // la línea ya quedó en disco (el sync es por escritura en _emit_log_line)
    if (t == LT_ERROR || t == LT_FATAL || t == LT_WARN) {
        _log_flush_pending();
        _file_flush(1);
    }

    sceKernelUnlockLwMutex(&_log_mutex, 1);
}

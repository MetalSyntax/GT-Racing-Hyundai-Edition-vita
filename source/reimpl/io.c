/*
 * Copyright (C) 2021      Andy Nguyen
 * Copyright (C) 2022      Rinnegatamante
 * Copyright (C) 2022-2024 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "reimpl/io.h"

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdarg.h>
#include <psp2/kernel/threadmgr.h>

#ifdef USE_SCELIBC_IO
#include <libc_bridge/libc_bridge.h>
#endif

#include "utils/logger.h"
#include "utils/utils.h"

// Includes the following inline utilities:
// int oflags_musl_to_newlib(int flags);
// dirent64_bionic * dirent_newlib_to_bionic(struct dirent* dirent_newlib);
// void stat_newlib_to_bionic(struct stat * src, stat64_bionic * dst);
#include "reimpl/bits/_struct_converters.c"

// Mapa Android->Vita compartido en utils.c (hy_rewrite_path) para que los
// stubs JNI file-backed resuelvan igual que fopen/open/stat/opendir.
static void rewrite_android_path(const char * path, char * buf, size_t bufsz) {
    hy_rewrite_path(path, buf, (unsigned int)bufsz);
}

static void fopen_map_add(FILE *fp, const char *path);
static void fopen_map_del(FILE *fp);

/*
 * Speedhack: pool de FILE* de solo lectura para los paquetes grandes de assets.
 * 013.log: hasta ~300 fopen/fclose cada 60 frames sobre main.*.obb (602 MB, lo lee
 * vox::CZipReader) y Sounds.pak (Vox abre uno por sonido). Cada fopen a ux0 es E/S
 * síncrona en el hilo que lo pide. Aquí fclose() "estaciona" el handle abierto y el
 * próximo fopen del mismo path+modo lo reutiliza tras fseek(0) (que además limpia EOF).
 * Solo para modo lectura de esos dos archivos, nunca para saves.
 */
#define HY_POOL_N 8
typedef struct { FILE *fp; char path[160]; char mode[4]; int parked; } hy_pool_slot;
static hy_pool_slot s_pool[HY_POOL_N];
static SceKernelLwMutexWork s_pool_mtx;
static int s_pool_ready = 0;

static int pool_eligible(const char *path, const char *mode) {
    if (strcmp(mode, "rb") != 0 && strcmp(mode, "r") != 0) return 0;
    size_t n = strlen(path);
    if (n >= sizeof(s_pool[0].path)) return 0;
    if (n > 4 && strcmp(path + n - 4, ".obb") == 0) return 1;
    if (n > 10 && strcmp(path + n - 10, "Sounds.pak") == 0) return 1;
    return 0;
}

static void pool_lock(void) {
    if (!s_pool_ready) {
        sceKernelCreateLwMutex(&s_pool_mtx, "hy_fpool", 0, 0, NULL);
        s_pool_ready = 1;
    }
    sceKernelLockLwMutex(&s_pool_mtx, 1, NULL);
}

static void pool_unlock(void) {
    sceKernelUnlockLwMutex(&s_pool_mtx, 1);
}

/* Devuelve un handle estacionado para path+mode, o NULL. */
static FILE *pool_take(const char *path, const char *mode) {
    FILE *ret = NULL;
    pool_lock();
    for (int i = 0; i < HY_POOL_N; i++) {
        if (s_pool[i].fp && s_pool[i].parked && strcmp(s_pool[i].path, path) == 0 &&
            strcmp(s_pool[i].mode, mode) == 0) {
            s_pool[i].parked = 0;
            ret = s_pool[i].fp;
            break;
        }
    }
    pool_unlock();
    if (ret) {
#ifdef USE_SCELIBC_IO
        sceLibcBridge_fseek(ret, 0, SEEK_SET);
#else
        fseek(ret, 0, SEEK_SET);
#endif
    }
    return ret;
}

/* Registra un handle recién abierto si hay lugar (si no, se cierra normal). */
static void pool_track(FILE *fp, const char *path, const char *mode) {
    pool_lock();
    for (int i = 0; i < HY_POOL_N; i++) {
        if (!s_pool[i].fp) {
            s_pool[i].fp = fp;
            strcpy(s_pool[i].path, path);
            strncpy(s_pool[i].mode, mode, sizeof(s_pool[i].mode) - 1);
            s_pool[i].mode[sizeof(s_pool[i].mode) - 1] = '\0';
            s_pool[i].parked = 0;
            break;
        }
    }
    pool_unlock();
}

/* 1 si el handle quedó estacionado (no hay que cerrarlo). */
static int pool_park(FILE *fp) {
    int parked = 0;
    if (!s_pool_ready) return 0;
    pool_lock();
    for (int i = 0; i < HY_POOL_N; i++) {
        if (s_pool[i].fp == fp && !s_pool[i].parked) {
#ifdef USE_SCELIBC_IO
            int err = sceLibcBridge_ferror(fp);
#else
            int err = ferror(fp);
#endif
            if (err) {
                s_pool[i].fp = NULL;  /* con error: sacarlo del pool y cerrarlo de verdad */
            } else {
                s_pool[i].parked = 1;
                parked = 1;
            }
            break;
        }
    }
    pool_unlock();
    return parked;
}

FILE * fopen_soloader(const char * filename, const char * mode) {
    trace_call("fopen");
    if (strcmp(filename, "/proc/cpuinfo") == 0) {
        return fopen_soloader("app0:/cpuinfo", mode);
    } else if (strcmp(filename, "/proc/meminfo") == 0) {
        return fopen_soloader("app0:/meminfo", mode);
    }

    char realpath[1024];
    rewrite_android_path(filename, realpath, sizeof(realpath));
    filename = realpath;

    const int pooled = pool_eligible(filename, mode);
    if (pooled) {
        FILE *reused = pool_take(filename, mode);
        if (reused) {
            fopen_map_add(reused, filename);
            return reused;
        }
    }

#ifdef USE_SCELIBC_IO
    FILE* ret = sceLibcBridge_fopen(filename, mode);
#else
    FILE* ret = fopen(filename, mode);
#endif
    if (ret && pooled)
        pool_track(ret, filename, mode);

    if (!ret && strstr(filename, "oconf.bar")) {
        const char *alt_paths[] = {
            DATA_PATH "res/raw/oconf.bar",
            DATA_PATH "oconf.bar",
            "app0:res/raw/oconf.bar",
            "app0:oconf.bar"
        };
        for (unsigned i = 0; i < sizeof(alt_paths)/sizeof(alt_paths[0]); i++) {
#ifdef USE_SCELIBC_IO
            ret = sceLibcBridge_fopen(alt_paths[i], mode);
#else
            ret = fopen(alt_paths[i], mode);
#endif
            if (ret) {
                l_info("fopen(%s): resolved fallback to %s", filename, alt_paths[i]);
                break;
            }
        }
    }

    if (ret) {
        l_debug("fopen(%s, %s): %p", filename, mode, ret);
        fopen_map_add(ret, filename);
    } else
        l_warn("fopen(%s, %s): %p", filename, mode, ret);

    return ret;
}

int open_soloader(const char * path, int oflag, ...) {
    trace_call("open");
    if (strcmp(path, "/proc/cpuinfo") == 0) {
        return open_soloader("app0:/cpuinfo", oflag);
    } else if (strcmp(path, "/proc/meminfo") == 0) {
        return open_soloader("app0:/meminfo", oflag);
    }

    char realpath[1024];
    rewrite_android_path(path, realpath, sizeof(realpath));
    path = realpath;

    mode_t mode = 0666;
    if (((oflag & BIONIC_O_CREAT) == BIONIC_O_CREAT) ||
        ((oflag & BIONIC_O_TMPFILE) == BIONIC_O_TMPFILE)) {
        va_list args;
        va_start(args, oflag);
        mode = (mode_t)(va_arg(args, int));
        va_end(args);
    }

    oflag = oflags_bionic_to_newlib(oflag);
    int ret = open(path, oflag, mode);
    if (ret >= 0)
        l_debug("open(%s, %x): %i", path, oflag, ret);
    else
        l_warn("open(%s, %x): %i", path, oflag, ret);
    return ret;
}

int fstat_soloader(int fd, stat64_bionic * buf) {
    struct stat st;
    int res = fstat(fd, &st);

    if (res == 0)
        stat_newlib_to_bionic(&st, buf);

    l_debug("fstat(%i): %i", fd, res);
    return res;
}

int stat_soloader(const char * path, stat64_bionic * buf) {
    char realpath[1024];
    rewrite_android_path(path, realpath, sizeof(realpath));
    path = realpath;

    struct stat st;
    int res = stat(path, &st);

    if (res == 0)
        stat_newlib_to_bionic(&st, buf);

    l_debug("stat(%s): %i", path, res);
    return res;
}

int fclose_soloader(FILE * f) {
    trace_call("fclose");
    fopen_map_del(f);
    if (pool_park(f))
        return 0;
#ifdef USE_SCELIBC_IO
    int ret = sceLibcBridge_fclose(f);
#else
    int ret = fclose(f);
#endif

    l_debug("fclose(%p): %i", f, ret);
    return ret;
}

int close_soloader(int fd) {
    trace_call("close");
    int ret = close(fd);
    l_debug("close(%i): %i", fd, ret);
    return ret;
}

DIR* opendir_soloader(char* _pathname) {
    char realpath[1024];
    rewrite_android_path(_pathname, realpath, sizeof(realpath));
    _pathname = realpath;

    DIR* ret = opendir(_pathname);
    l_debug("opendir(\"%s\"): %p", _pathname, ret);
    return ret;
}

struct dirent64_bionic * readdir_soloader(DIR * dir) {
    static struct dirent64_bionic dirent_tmp;

    struct dirent* ret = readdir(dir);
    l_debug("readdir(%p): %p", dir, ret);

    if (ret) {
        dirent64_bionic* entry_tmp = dirent_newlib_to_bionic(ret);
        memcpy(&dirent_tmp, entry_tmp, sizeof(dirent64_bionic));
        free(entry_tmp);
        return &dirent_tmp;
    }

    return NULL;
}

int readdir_r_soloader(DIR * dirp, dirent64_bionic * entry,
                       dirent64_bionic ** result) {
    struct dirent dirent_tmp;
    struct dirent * pdirent_tmp;

    int ret = readdir_r(dirp, &dirent_tmp, &pdirent_tmp);

    if (ret == 0) {
        dirent64_bionic* entry_tmp = dirent_newlib_to_bionic(&dirent_tmp);
        memcpy(entry, entry_tmp, sizeof(dirent64_bionic));
        *result = (pdirent_tmp != NULL) ? entry : NULL;
        free(entry_tmp);
    }

    l_debug("readdir_r(%p, %p, %p): %i", dirp, entry, result, ret);
    return ret;
}

int closedir_soloader(DIR * dir) {
    int ret = closedir(dir);
    l_debug("closedir(%p): %i", dir, ret);
    return ret;
}

int fcntl_soloader(int fd, int cmd, ...) {
    l_warn("fcntl(%i, %i, ...): not implemented", fd, cmd);
    return 0;
}

int ioctl_soloader(int fd, int request, ...) {
    l_warn("ioctl(%i, %i, ...): not implemented", fd, request);
    return 0;
}

int fsync_soloader(int fd) {
    int ret = fsync(fd);
    l_debug("fsync(%i): %i", fd, ret);
    return ret;
}

size_t fread_soloader(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    trace_call("fread");
#ifdef USE_SCELIBC_IO
    size_t ret = sceLibcBridge_fread(ptr, size, nmemb, stream);
#else
    size_t ret = fread(ptr, size, nmemb, stream);
#endif
    trace_stream_progress(stream, (ret == 0 && size > 0 && nmemb > 0) ? 0 : 1);
    return ret;
}

size_t fwrite_soloader(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
    trace_call("fwrite");
#ifdef USE_SCELIBC_IO
    size_t ret = sceLibcBridge_fwrite(ptr, size, nmemb, stream);
#else
    size_t ret = fwrite(ptr, size, nmemb, stream);
#endif
    trace_stream_progress(stream, (ret == 0 && size > 0 && nmemb > 0) ? 0 : 1);
    return ret;
}

/*
 * rewind/fseeko/ftello: los FILE* vienen de SceLibcBridge (fopen_soloader), así que
 * las versiones newlib no pueden tocarlos. Con la rewind de newlib, el copiado de
 * tracking_data*.dat (fseek END -> ftell -> rewind -> fseek CUR) quedaba posicionado
 * más allá del EOF y el bucle `for (left = size - off; left > 0; left -= fread(...))`
 * giraba para siempre con fread()==0 (congelado tras el tutorial, 011.log).
 */
void rewind_soloader(FILE *stream) {
#ifdef USE_SCELIBC_IO
    sceLibcBridge_fseek(stream, 0, SEEK_SET);
#else
    rewind(stream);
#endif
}

int fseeko_soloader(FILE *stream, off_t offset, int whence) {
#ifdef USE_SCELIBC_IO
    return sceLibcBridge_fseek(stream, (long)offset, whence);
#else
    return fseeko(stream, offset, whence);
#endif
}

off_t ftello_soloader(FILE *stream) {
#ifdef USE_SCELIBC_IO
    return (off_t)sceLibcBridge_ftell(stream);
#else
    return ftello(stream);
#endif
}

/* Mapa FILE* -> path (para identificar el archivo de un bucle de E/S) */
#define FOPEN_MAP_N 32
static FILE *s_map_fp[FOPEN_MAP_N] = {0};
static char s_map_path[FOPEN_MAP_N][128] = {{0}};
static unsigned s_map_next = 0;

static void fopen_map_add(FILE *fp, const char *path) {
    if (!fp || !path) return;
    unsigned i = s_map_next % FOPEN_MAP_N;
    s_map_next++;
    s_map_fp[i] = fp;
    strncpy(s_map_path[i], path, sizeof(s_map_path[i]) - 1);
    s_map_path[i][sizeof(s_map_path[i]) - 1] = '\0';
}

static void fopen_map_del(FILE *fp) {
    if (!fp) return;
    for (unsigned i = 0; i < FOPEN_MAP_N; i++) {
        if (s_map_fp[i] == fp) {
            s_map_fp[i] = NULL;
            s_map_path[i][0] = '\0';
        }
    }
}

const char *fopen_map_lookup(FILE *fp) {
    if (!fp) return "(null)";
    for (unsigned i = 0; i < FOPEN_MAP_N; i++) {
        if (s_map_fp[i] == fp)
            return s_map_path[i];
    }
    return "(desconocido)";
}

/*
 * Detector de bucle de E/S sin avance: racha de fread/fwrite que retornan 0
 * (pidiendo >0) sobre el mismo stream. Un bucle así gira a ~1M iter/s sin
 * avanzar (visto en 009.log en la pantalla de info de licencia). Al superar
 * el umbral se reporta UNA vez con el stream y su path.
 */
static FILE *s_spin_fp = NULL;
static unsigned long long s_spin_zeros = 0;
static int s_spin_reported = 0;
#define SPIN_REPORT_AT (500000ULL)

void trace_stream_progress(FILE *fp, int progressed) {
    if (progressed) {
        if (fp != s_spin_fp) {
            s_spin_fp = fp;
            s_spin_zeros = 0;
        } else {
            s_spin_zeros = 0;
        }
        return;
    }
    if (fp != s_spin_fp) {
        s_spin_fp = fp;
        s_spin_zeros = 1;
        return;
    }
    s_spin_zeros++;
    if (!s_spin_reported && s_spin_zeros >= SPIN_REPORT_AT) {
        s_spin_reported = 1;
        l_error("[io] SPIN E/S sin avance: %llu ops con retorno 0 en stream %p (%s)",
                s_spin_zeros, fp, fopen_map_lookup(fp));
    }
}

void trace_stream_last(FILE **out_fp, unsigned long long *out_zeros, const char **out_path) {
    if (out_fp) *out_fp = s_spin_fp;
    if (out_zeros) *out_zeros = s_spin_zeros;
    if (out_path) *out_path = fopen_map_lookup(s_spin_fp);
}

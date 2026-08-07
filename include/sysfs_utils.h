#ifndef HWBUS_SYSFS_UTILS_H
#define HWBUS_SYSFS_UTILS_H

#include <stddef.h> // size_t y NULL
// #include <stdint.h> /* tipos enteros de ancho fijo uint16_t, etc */
#include <sys/types.h> /* tipos POSIX como off_t, etc*/
// #include <errno.h>     /* codigos de error estandar */

/* Lectura de enteros en hexadecimal */
int sysfs_read_uint(const char *path, unsigned int *val);

/* Lectura de cadenas de texto */
int sysfs_read_string(const char *path, char *buf, size_t size);

/* Lectura de registros binarios con offset */
int sysfs_read_binary(const char *path, off_t offset, void *buf, size_t count);

/* Auxiliar function to build paths*/
int sysfs_build_path(char *dest, size_t max_len, const char *subsys, const char *dev_id, const char *attr);

#endif
#ifndef HWBUS_ERROR_H
#define HWBUS_ERROR_H

#ifdef __KERNEL__
#include <linux/errno.h>
#include <linux/types.h>
#else
#include <errno.h>
#include <stddef.h>
#endif

#define HWBUS_SUCCESS 0
#define HWBUS_ERR_BASE 5000
#define HWBUS_ERR_PATH_TOO_LONG (HWBUS_ERR_BASE + 1)
#define HWBUS_ERR_INVALID_BDF (HWBUS_ERR_BASE + 2)
#define HWBUS_ERR_NOT_SUPPORTED (HWBUS_ERR_BASE + 3)

#ifndef __KERNEL__

/**
 * @brief Traduce códigos de error POSIX y de dominio HWBUS a una cadena legible.
 *        Solo disponible para utilidades y tests en Espacio de Usuario.
 *
 * @param errnum Código de error (entero positivo o negativo)
 * @return const char* Cadena estática con la descripción del error
 */
const char* hwbus_strerror(int errnum);
#endif

#endif /* HWBUS_ERROR_H */
#include <errno.h>
#include <stddef.h>

#define HWBUS_SUCCESS 0
#define HWBUS_ERR_BASE 5000
#define HWBUS_ERR_PATH_TOO_LONG (HWBUS_ERR_BASE + 1)
#define HWBUS_ERR_INVALID_BDF (HWBUS_ERR_BASE + 2)
#define HWBUS_ERR_NOT_SUPPORTED (HWBUS_ERR_BASE + 3)

/* Translating function */
const char *hwbus_strerror(int errnum);

/*
  Siguiente punto de discusión en la arquitectura
  - Por qué aparecen estas advertencias en hello.c ?
  - No hemos determinado si vamos a enfocar el desarrollo como una aplicaciónde usuario o como módulo del kernel. Esperaba, adoptar un enfoque de driver...



*/
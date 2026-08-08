#include "hwbus_error.h"
#include <string.h>

const char* hwbus_strerror(int errnum) {
  if (errnum < 0) {
    errnum = -errnum;
  }

  /*Rango de errores especificos de hwbus-io*/
  switch (errnum)
  {
  case HWBUS_SUCCESS:
    return "Success";
  case HWBUS_ERR_PATH_TOO_LONG:
    return "Path length exceeds maximum allowed buffer";
  case HWBUS_ERR_INVALID_BDF:
    return "Invalid PCI Bus:Device:Function identifier format";
  case HWBUS_ERR_NOT_SUPPORTED:
    return "Hardware operation or BAR mapping not supported";
  }

  if (errnum < HWBUS_ERR_BASE) {
    return strerror(errnum);
  }
  return "Unknown HWBUS error code";

}
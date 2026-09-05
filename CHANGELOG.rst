=====================
Historial de Cambios
=====================

Todos los cambios notables en este proyecto serán documentados en este archivo.

.. list-table:: Versión 1.1.0 (2026-09-04)
   :widths: 20 80
   :header-rows: 1

   * - Categoría
     - Descripción
   * - Added
     - Definición de cabeceras UAPI públicas (user/hwbus_io_uapi.h y hwbus_bdf_info) para desacoplar el espacio de usuario.
   * - Added
     - Implementación de comandos IOCTL atómicos (HWBUS_IOC_GET_BDF, HWBUS_IOC_READ_VENDOR, HWBUS_IOC_READ_DEVICE).
   * - Added
     - Suite completa de pruebas de estrés e integración LTP (hwbus_io01 a hwbus_io05) cubriendo concurrencia de subprocesos, mmap() y lseek().
   * - Changed
     - Transición de la interfaz de operaciones de archivo (fops) hacia un modelo puro basado en IOCTL.
   * - Changed
     - Estandarización de respuestas POSIX: rechazo explícito de mmap() devolviendo -ENODEV y de comandos IOCTL no válidos devolviendo -ENOTTY.
   * - Fixed
     - Corrección de condiciones de carrera en accesos concurrentes e integración del flag forks_child para pruebas multinúcleo.
   * - CI/CD
     - Incorporación de runner para módulos del kernel (ci-kmod-runner.sh), generación dinámica de manifiestos y soporte de ejecución LTP no privilegiada.

.. list-table:: Versión 1.0.0 (2026-08-20)
   :widths: 20 80
   :header-rows: 1

   * - Categoría
     - Descripción
   * - Added
     - Módulo de kernel básico (hwbus_io.ko) y nodo de dispositivo de carácter /dev/hwbusc con asignación Major 240.
   * - Added
     - Implementación de operaciones fops iniciales (hwbus_open, hwbus_release) y lectura básica de registros PCI.
   * - Added
     - Exposición de atributos en SysFS (/sys/class/hwbusc/) y gestión del parámetro de módulo hwbus_bdf_param.
   * - Added
     - Arnés de pruebas unitarias iniciales e integración de baterías externas (BUS_tests y PROC_tests).
   * - CI/CD
     - Infraestructura automatizada de orquestación (ci-runner, ci-runLauncher) y control del ciclo de vida de VMs (acme-sandbox, buildlab).
   * - Security
     - Licenciamiento GPL, ordenación e inspección de cabeceras (findBadFormatH.sh) y preparación de firma de módulo para Secure Boot.
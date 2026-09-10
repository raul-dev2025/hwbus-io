=========
Changelog
=========

.. list-table:: Version 1.2.0 (2026-09-10)
   :widths: 20 80
   :header-rows: 1

   * - Category
     - Description
   * - Added
     - Implementation of unit sub-test hwbus_io06 to validate the HWBUS_IOCRESET ioctl command.
   * - Added
     - Integration of the automated LTP orchestrator hwbus_io_suite00r managing process isolation and dynamic module reloading.
   * - Changed
     - Validation logic in is_valid_hwbus_cmd() to support _IO type commands without payload.
   * - Fixed
     - Resolution of ENOTTY errors during device reset in the cleanup phase of automated test execution.
   * - CI/CD
     - Tag v3.0.0-ci-integration marking 100% pass rate across the entire LTP test suite for /dev/hwbusc.


.. list-table:: Version 1.1.0 (2026-09-04)
   :widths: 20 80
   :header-rows: 1

   * - Category
     - Description
   * - Added
     - Definition of public UAPI headers (user/hwbus_io_uapi.h and hwbus_bdf_info) to decouple user space.
   * - Added
     - Implementation of atomic IOCTL commands (HWBUS_IOC_GET_BDF, HWBUS_IOC_READ_VENDOR, HWBUS_IOC_READ_DEVICE).
   * - Added
     - Complete suite of LTP stress and integration tests (hwbus_io01 to hwbus_io05) covering thread concurrency, mmap(), and lseek().
   * - Changed
     - Transition of the file operations (fops) interface toward a pure IOCTL-based model.
   * - Changed
     - Standardization of POSIX responses: explicit rejection of mmap() returning -ENODEV and invalid IOCTL commands returning -ENOTTY.
   * - Fixed
     - Fix for race conditions in concurrent access and integration of the forks_child flag for multi-core testing.
   * - CI/CD
     - Incorporation of kernel module runner (ci-kmod-runner.sh), dynamic manifest generation, and unprivileged LTP execution support.

.. list-table:: Version 1.0.0 (2026-08-20)
   :widths: 20 80
   :header-rows: 1

   * - Category
     - Description
   * - Added
     - Basic kernel module (hwbus_io.ko) and character device node /dev/hwbusc with Major 240 allocation.
   * - Added
     - Implementation of initial fops operations (hwbus_open, hwbus_release) and basic PCI register reading.
   * - Added
     - Exposure of SysFS attributes (/sys/class/hwbusc/) and management of the hwbus_bdf_param module parameter.
   * - Added
     - Initial unit test harness and integration of external test suites (BUS_tests and PROC_tests).
   * - CI/CD
     - Automated orchestration infrastructure (ci-runner, ci-runLauncher) and VM lifecycle management (acme-sandbox, buildlab).
   * - Security
     - GPL licensing, header sorting and inspection (findBadFormatH.sh), and module signing preparation for Secure Boot.
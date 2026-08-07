========
hwbus-io
========

**hwbus-io** is a modular Linux kernel driver and diagnostic framework designed for low-level I/O operations, PCI configuration space access, and hardware bus inspection.

-----

Overview
========

``hwbus-io`` provides a robust, low-level interface for inspecting and interacting with hardware devices on Linux systems. It combines kernel-space driver modules with remote automated testing and diagnostic capabilities to perform precise register operations, BAR mapping, and configuration space queries.

* **Kernel-Space Driver Core:** Operates as native Linux kernel modules (``.ko``) with direct hardware access capabilities.
* **Secure Boot Support:** Includes automated module signing via ``kmod-sign-file`` using local lab credentials.
* **PCI Configuration Space Inspection:** Read and write PCI configuration registers and BAR regions.
* **Standardized Error Handling:** Uses kernel/POSIX-compliant negative error codes (``-errno``) alongside a domain-specific error range (``>= 5000``).
* **Automated CI/Remote Testing:** Integrates remote compilation, automated module signing, loading, and ``dmesg`` assertion via custom CI scripts.

Project Structure
=================

.. code-block:: text

   hwbus-io/
   ├── include/          # Public driver & API headers
   ├── src/
   │   ├── driver/       # Kernel module implementation (.ko)
   │   └── core/         # Core helper functions and error handling
   ├── tests/            # Kernel module tests and Makefile harness
   ├── Scripts/          # Automation tools (test-runner.sh)
   ├── ci-runner.sh      # Remote CI integration and build script
   ├── Makefile          # Top-level build automation
   ├── LICENSE           # GNU General Public License v2.0
   └── README.rst


Prerequisites
=============

* Linux Kernel headers (``kernel-devel`` or ``linux-headers``) matching your target kernel version.
* GCC / Clang toolchain and standard ``make`` build utilities.
* Secure Boot certificates for module signing.
* Passwordless ``sudo`` privileges configured for kernel management utilities (``insmod``, ``rmmod``, ``kmod-sign-file``, ``dmesg``).

Building and Testing
====================

1. **Clone the repository:**

.. code-block:: bash

   git clone https://github.com/raul-dev2025/hwbus-io.git
   cd hwbus-io

2. **Local Compilation (Single Test Module):**

.. code-block:: bash

   make -C tests MODULE=hello.ko

3. **Manual Signing and Execution:**

.. code-block:: bash

   # Sign the compiled module
   sudo kmod-sign-file sha256 /path/to/key.priv /path/to/key.der tests/hello.ko

   # Load, inspect logs, and unload
   sudo insmod tests/hello.ko
   sudo dmesg | tail -n 15
   sudo rmmod hello

4. **Automated Remote Execution via CI Runner:**

Execute the local runner to handle remote buildlab synchronization, module signing, insertion, and log retrieval:

.. code-block:: bash

   ./ci-runner.sh

License
=======

This project is licensed under the **GNU General Public License v2.0 (GPL-2.0)**. See the LICENSE file for details.
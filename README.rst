========
hwbus-io
========


**hwbus-io** is a modular Linux kernel driver and diagnostic framework designed for low-level I/O operations, PCI configuration space access, and hardware bus inspection.

-----

Overview
========

``hwbus-io`` provides a robust, low-level interface for inspecting and interacting with hardware devices on Linux systems. It combines a kernel-space driver module with diagnostic capabilities to perform precise register operations, BAR mapping, and configuration space queries.

h1

* **Kernel-Space Driver Core:** Operates as a native Linux kernel module (`.ko`) with direct hardware access capabilities.
* **PCI Configuration Space Inspection:** Read and write PCI configuration registers and BAR regions.
* **Standardized Error Handling:** Uses kernel/POSIX-compliant negative error codes (`-errno`) alongside a domain-specific error range (`>= 5000`).
* **LTP Integration:** Built to work alongside continuous integration runners and Linux Test Project (LTP) test suites.

Project Structure
=================

.. code-block:: text

   hwbus-io/
   ├── include/          # Public driver & API headers
   ├── src/
   │   ├── driver/       # Kernel module implementation (.ko)
   │   └── core/         # Core helper functions and error handling
   ├── tests/            # Test suits and LTP-compatible test harnesses
   ├── Makefile          # Top-level build automation
   ├── LICENSE           # GNU General Public License v2.0
   └── README.md


Prerequisites
=============

* Linux Kernel headers (``kernel-devel`` or ``linux-headers``) matching your running kernel version.
* GCC / Clang toolchain and standard ``make`` build utilities.
* Root / ``sudo`` privileges for loading kernel modules.

Building and Installation
=========================


1. **Clone the repository:**

.. code-block:: bash

   git clone https://github.com/raul-dev2025/hwbus-io.git
   cd hwbus-io


2. **Compile the driver and utilities:**

.. code-block:: bash

   make


3. **Load the kernel module:**

.. code-block:: bash

   sudo insmod src/driver/hwbus_driver.ko


4. **Verify module loading:**

.. code-block:: bash

   dmesg | tail -n 10


License
=======

This project is licensed under the **GNU General Public License v2.0 (GPL-2.0)**. See the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.


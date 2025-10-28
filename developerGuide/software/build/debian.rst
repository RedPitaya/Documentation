.. _SW_build_os:

###################
Build Red Pitaya OS
###################

This guide explains how to build a Debian/Ubuntu based SD card image for Red Pitaya.

.. contents:: Table of contents
    :backlinks: top


Introduction
==============

Red Pitaya OS consists of two main components:

1. **Debian/Ubuntu OS** (Ext4 partition) - Contains the base operating system, applications, libraries, and services
2. **Ecosystem** (FAT32 partition) - Contains boot files, FPGA bitstreams, kernel, and user-space applications

Both components are required for a functional system. The OS provides the runtime environment, while the ecosystem 
provides the hardware interface and Red Pitaya specific applications.


Build Script Overview
======================

Main build scripts
-------------------

The following scripts are located in the ``debian`` directory and can be executed directly:

+---------------------+------------------------------------------------------------------------------+
| Script              | Description                                                                  |
+=====================+==============================================================================+
| ``image.sh``        | Full SD card image build procedure (creates and formats partitions)          |
+---------------------+------------------------------------------------------------------------------+
| ``image-update.sh`` | Update existing SD card image with new ``ecosystem_*.zip``                   |
+---------------------+------------------------------------------------------------------------------+
| ``image-fsck.sh``   | Run FSCK on SD card image partitions (for images created from used DS cards) |
+---------------------+------------------------------------------------------------------------------+
| ``image-clean.sh``  | Deprecated                                                                   |
+---------------------+------------------------------------------------------------------------------+


Chroot environment scripts
----------------------------

The following scripts are designed to run exclusively within a ``chroot`` environment:

.. warning::

    Do not execute these scripts directly on your host OS. They will modify system-level configuration and can cause serious damage to your host system.

+---------------------+---------------------------------------------------------------------------------------------------------------+
| Script              | Description                                                                                                   |
+=====================+===============================================================================================================+
| ``ubuntu.sh``       | Ubuntu bootstrap, locale, apt configuration, timezone, fake HW clock                                          |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``debian.sh``       | Debian bootstrap (**experimental**, WEB applications are not working)                                         |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``tools.sh``        | Tools for compiling software                                                                                  |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``zynq.sh``         | HW support for ZYNQ chip (U-Boot, I2C, EEPROM, dtc, IIO, NE10?, GPIO, groups with HW access rights)           |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``network.sh``      | ``systemd-networkd`` based wired/wireless network configuration and required tools (hostAP, supplicant)       |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``redpitaya.sh``    | Libraries required by the ecosystem applications (boost, jpeg, json), install and enable services             |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``jupyter.sh``      | Jupyter with NumPy and SciPy                                                                                  |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``cmake3.21.sh``    | The script builds cmake of the required version to build the ecosystem                                        |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``watchdog.sh``     | Configures the watchdog service                                                                               |
+---------------------+---------------------------------------------------------------------------------------------------------------+
| ``tft.sh``          | X-server and XFCE                                                                                             |
+---------------------+---------------------------------------------------------------------------------------------------------------+


Configuration files
--------------------

The ``overlay`` directory contains configuration files that are installed individually onto the OS by the build scripts.


Understanding the Build Process
=================================

OS image contents
------------------

A complete SD card image contains:

1. **Debian/Ubuntu OS** (Ext4 partition):

    * Base operating system files
    * Additional operating system applications and libraries
    * Systemd services
    * Most network configuration files
    * Jupyter workspace


2. **Ecosystem** (FAT32 partition):

    * **Bare metal components:**

        * ``boot.bin`` - Contains FSBL, FPGA bitstream and U-Boot
        * Linux kernel image and device tree files
        * Alternative FPGA bitstreams and corresponding device tree overlays

    * **User space components:**

        * Bazaar server (Nginx) and WEB applications
        * Red Pitaya API library
        * SCPI server


Bootstrap procedure
--------------------

In order to build a functional OS image, the ecosystem is required since without the ``boot.bin`` and the Linux kernel, 
the system will not start. Similarly, the OS image is required to build the ecosystem, since user-space applications are 
built inside a ``chroot`` environment with an emulated ARM CPU.

This creates a chicken-and-egg problem. The first-time build procedure is:

1. **Build the OS image without the ecosystem**
    
    This creates:
    
    * ``redpitaya_OS_*.img`` - A non-functional SD card image (missing boot files and kernel)
    * ``redpitaya_OS_*.tar.gz`` - Archive for creating the ``chroot`` environment

2. **Build the ecosystem inside the chroot environment**
    
    * Use the ``redpitaya_OS_*.tar.gz`` file to create a ``chroot`` environment
    * Execute the necessary scripts inside ``chroot`` to build the ecosystem
    * Generate the ``ecosystem_*.zip`` file

3. **Combine the OS image with the ecosystem**

    .. code-block:: shell-session

        OS/debian/image-update.sh redpitaya_OS_*.img ecosystem_*.zip


After completing the bootstrap procedure, you can build either component independently. The typical workflow is to build 
a new ecosystem in an existing ``chroot`` environment and update the SD card. Once an ``ecosystem_*.zip`` file exists in 
the project root directory, new OS images will automatically integrate it during the build process.


.. _SW_os_req:

Prerequisites
==============

Host system requirements
--------------------------

To build the Red Pitaya Debian/Ubuntu OS image, you need a host PC running Ubuntu.

+---------------------------------+---------------------------------+
| Red Pitaya OS version           | Host platform OS                |
+=================================+=================================+
| OS 2.0 and higher               | Ubuntu 22.04 LTS or higher      |
+---------------------------------+---------------------------------+
| OS 1.04                         | Ubuntu 18.04 LTS or higher      |
+---------------------------------+---------------------------------+

.. note::

    Vivado 2020 (required for FPGA assembly) cannot be installed on Ubuntu 18.04. Therefore, for OS 2.0 and higher, 
    Ubuntu 22.04 or higher is required.


Required packages
------------------

The following examples use Ubuntu 22.04 LTS, but the procedure is similar for other Ubuntu versions.

Install the required packages on your host PC:

.. code-block:: shell-session

    $ sudo apt-get install debootstrap qemu-user-static


Building the OS Image
=======================

Follow these steps to build a complete Red Pitaya OS image.

Step 1: Clone the GitHub repository
-------------------------------------

.. tabs::

    .. group-tab:: OS 1.04 or lower

        The OS build scripts are maintained in the main :rp-github:`Red Pitaya repository <RedPitaya>`:

        .. code-block:: shell-session

            $ git clone https://github.com/RedPitaya/RedPitaya.git
            cd RedPitaya


    .. group-tab:: OS 2.0 or higher

        The OS build scripts are maintained in a separate :rp-github:`Ubuntu repository <ubuntu>`:

        .. code-block:: shell-session

            $ git clone https://github.com/RedPitaya/ubuntu.git
            cd ubuntu


Step 2: Build the ecosystem
-----------------------------

Before building the OS image, you must build the ecosystem. Follow the instructions in the :ref:`Ecosystem <SW_build_ecosystem>` 
section to complete this step.

.. note::

    For the first-time bootstrap procedure, you can skip this step and build a non-functional OS image first, 
    then use it to create the ``chroot`` environment for building the ecosystem.


Step 3: Build the OS image
----------------------------

Execute the build script with root privileges:

.. tabs::

    .. group-tab:: OS 1.04 or lower

        .. code-block:: shell-session

            $ sudo OS/debian/image.sh

    .. group-tab:: OS 2.00 or higher

        .. code-block:: shell-session

            $ sudo build.sh

        The ``build.sh`` script calls :rp-github:`image.sh <ubuntu/blob/main/debian/image.sh>`, which performs the complete OS image build procedure.

.. warning::

    This script must be executed as the ``root`` user. If run with ``sudo`` without switching to root, 
    some configuration files will be placed in the wrong user's home directory.

.. note::

    If the ``ecosystem_*.zip`` file exists in the project root directory, it will be automatically integrated 
    into the OS image, creating a fully functional SD card image.


What happens during the build
-------------------------------

During the build process, the following steps are performed:

1. **Image creation**
    
    :rp-github:`image.sh <ubuntu/blob/main/debian/image.sh>` creates an SD card image with a timestamp in the filename. 
    Two partitions are created:
    
    * 1024 MB FAT32 partition for the ecosystem
    * Ext4 partition for the OS on the remaining SD Card space

2. **Base system installation**
    
    :rp-github:`image.sh <ubuntu/blob/main/debian/image.sh>` calls :rp-github:`ubuntu.sh <ubuntu/blob/main/debian/ubuntu.sh>`,
    which installs the base system and additional packages, and configures:

    * APT (Debian packaging system)
    * Locales
    * Hostname
    * Time zone
    * File system table
    * U-Boot
    * Users and UART console access

3. **Network configuration**
    
    :rp-github:`ubuntu.sh <ubuntu/blob/main/debian/ubuntu.sh>` executes :rp-github:`network.sh <ubuntu/blob/main/debian/network.sh>`,
    which creates a ``systemd-networkd`` based wired and wireless network setup.

4. **Red Pitaya specific configuration**
    
    :rp-github:`redpitaya.sh <ubuntu/blob/main/debian/redpitaya.sh>` installs additional Debian packages 
    (mostly libraries) required by Red Pitaya applications and extracts the ``ecosystem*.zip`` file 
    (if present) into the FAT partition.

5. **Optional components** (can be commented out)
    
    * :rp-github:`jupyter.sh <ubuntu/blob/main/debian/jupyter.sh>` - Installs Jupyter notebook
    * :rp-github:`tft.sh <ubuntu/blob/main/debian/tft.sh>` - Installs X-server and XFCE desktop environment


Updating an Existing Image
============================

If you need to update an existing OS image with a new ecosystem without modifying the Ext4 partition:


Update the ecosystem
---------------------

Execute the update script with the image and ecosystem files as arguments:

.. code-block:: shell-session

    $ sudo OS/debian/image-update.sh redpitaya_OS_*.img ecosystem_*.zip


Write to SD card
-----------------

After updating the image, write it to a micro SD card (minimum 16 GB):

.. code-block:: shell-session

    $ sudo dd bs=4M if=redpitaya_OS_*.img of=/dev/mmcblk0 status=progress


Image Maintenance
==================

File system check
------------------

If the image was created through multiple user-performed steps (for example, installation or setup procedures on a live Red Pitaya), 
the file system might become corrupted. The :rp-github:`image-fsck.sh <ubuntu/blob/main/debian/image-fsck.sh>` script performs 
a file system check without making any modifications.

Run this script on images prior to release:

.. code-block:: shell-session

    $ sudo OS/debian/image-fsck.sh redpitaya_OS_*.img


Reducing image size
--------------------

.. warning::

    Perform these steps only on a live Red Pitaya board. Executing them on the host OS will cause problems.

You can reduce the image size by performing cleanup operations:

* Remove unused software (may have been required only for compilation)
* Remove unused source files and repositories
* Remove temporary files
* Zero out empty space on the partition

Execute the following commands to remove APT temporary files and clear empty space:

.. code-block:: shell-session

    $ apt-get clean
    $ cat /dev/zero > zero.file
    $ sync
    $ rm -f zero.file
    $ history -c


Managing the Running System
=============================

Systemd services
-----------------

Red Pitaya uses ``systemd`` as the init system. Services control the startup and operation of Red Pitaya applications and servers.

Service files are located in: ``OS/debian/overlay/etc/systemd/system/*.service``

Available services
^^^^^^^^^^^^^^^^^^^

+-------------------------+----------------------------------------------------------------------------------------------------+
| Service                 | Description                                                                                        |
+=========================+====================================================================================================+
| ``jupyter``             | Jupyter notebook for Python development                                                            |
+-------------------------+----------------------------------------------------------------------------------------------------+
| ``redpitaya_scpi``      | SCPI server (disabled by default, conflicts with web applications)                                 |
+-------------------------+----------------------------------------------------------------------------------------------------+
| ``redpitaya_nginx``     | Nginx-based server for WEB applications                                                            |
+-------------------------+----------------------------------------------------------------------------------------------------+


Service commands
^^^^^^^^^^^^^^^^^

Start or stop a service:

.. code-block:: shell-session

    $ systemctl start {service_name}
    $ systemctl stop {service_name}

Enable or disable a service at boot:

.. code-block:: shell-session

    $ systemctl enable {service_name}
    $ systemctl disable {service_name}

Check the status of a service:

.. code-block:: shell-session

    $ systemctl status {service_name}


System debugging
-----------------

Analyze boot process and service dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Generate visual representations of the boot process:

.. code-block:: shell-session

    $ systemd-analyze plot > /opt/redpitaya/www/apps/systemd-plot.svg
    $ systemd-analyze dot | dot -Tsvg > /opt/redpitaya/www/apps/systemd-dot.svg

These commands create SVG files showing the boot timeline and service dependency graph, which can be viewed through the web interface.

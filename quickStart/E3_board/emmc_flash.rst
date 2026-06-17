.. _emmc_flash_e3:

Flashing the eMMC on the QSPI eMMC module
##########################################

This guide describes how to flash the eMMC storage on the Red Pitaya QSPI eMMC module. The procedure uses
U-boot's USB Mass Storage (UMS) emulation to expose the eMMC as a standard USB storage device, allowing it
to be written with a Red Pitaya OS image from a PC — the same way as a regular SD card.

.. contents::
    :local:
    :backlinks: none
    :depth: 1

|

.. _emmc_flash_watchdog_note:

Important: watchdog behaviour during U-boot autoboot stop
==========================================================

.. warning::

    Stopping the board during the U-boot autoboot countdown **will cause the QSPI eMMC module to reboot
    Red Pitaya**. At this point in the boot sequence, the Zynq processor has not yet started the Red Pitaya
    OS, so the watchdog kick signal on the E3 connector is absent. The E3 module firmware treats a missing
    watchdog signal as a system failure and triggers a power reset.

    **The watchdog must be disabled before attempting to stop autoboot and enter the U-boot console.**

Two options are available to disable the watchdog:

**Option 1 — Edit the E3 module firmware (currently supported)**

    Modify the E3 module firmware source code to disable the watchdog timer check, then re-flash the STM32
    microcontroller on the QSPI eMMC module before proceeding with the eMMC flashing steps.

    Refer to the :ref:`E3 QSPI eMMC module software guide <E3_QSPI_eMMC_module_SW>` for instructions on
    building and programming the E3 firmware.

**Option 2 — Send the watchdog disable command via I2C (available in a future OS version)**

    A future Red Pitaya OS version will include support for sending a watchdog disable command to the E3
    module via I2C before rebooting into U-boot. When this feature is available, the firmware modification
    in Option 1 will no longer be required.

    Refer to the :ref:`E3 I2C controller utility <e3_i2c_controller_util>` for information about I2C
    commands supported by the E3 module.

|

Prerequisites
=============

Before proceeding, ensure you have:

* A Red Pitaya board with the QSPI eMMC module attached (see :ref:`QSPI eMMC board connection <QSPI_eMMC_board>`).
* A USB to serial console cable connected to the Red Pitaya **CON** port.
* A terminal program (e.g. PuTTY, minicom, or screen) configured for **115200 baud, 8N1**.
* A PC running a disk image writing tool such as `balenaEtcher <https://etcher.balena.io/>`_.
* A USB cable to connect the Red Pitaya USB port to the PC (the eMMC will appear as a USB drive).
* The watchdog disabled on the QSPI eMMC module (see :ref:`emmc_flash_watchdog_note` above).

.. note::

    Official eMMC support requires a Red Pitaya OS that includes U-boot with eMMC UMS support. Ensure you
    are using OS version 2.00 or later. If full eMMC support is not yet included in the stable release,
    follow the :ref:`nightly build installation guide <nightly_build_installation>` to obtain a build that
    includes the required U-boot version.

|

Flashing procedure
==================

Follow these steps to flash the Red Pitaya OS onto the eMMC:

Step 1: Prepare the SD card
----------------------------

Flash a Red Pitaya OS 2.00 (or later) image to a microSD card. Follow the :ref:`SD card preparation guide <prepareSD>` for detailed instructions.

If eMMC support is not yet in the stable release, install the latest nightly build ecosystem on the SD card
following the :ref:`nightly build installation guide <nightly_build_installation>`.

|

Step 2: Boot and stop at U-boot
---------------------------------

.. important::

    The watchdog on the QSPI eMMC module must be disabled **before** this step. See
    :ref:`emmc_flash_watchdog_note` above.

1.  Insert the prepared SD card into the Red Pitaya and power on the board by pressing the **P-ON** button
    on the QSPI eMMC module.
#.  Open a serial terminal connected to the Red Pitaya **CON** serial console (115200 baud, 8N1).
#.  Watch the console output. When the following message appears, **press any key immediately** to stop
    the autoboot:

    .. code-block:: text

        Hit any key to stop autoboot:

#.  You should now see the U-boot command prompt:

    .. code-block:: text

        U-Boot>

|

Step 3: Start USB Mass Storage emulation
-----------------------------------------

At the U-boot prompt, enter the following command to expose the eMMC as a USB Mass Storage device:

.. code-block:: text

    ums 0 mmc 0

The eMMC will now appear on the PC as a removable USB drive. U-boot will print periodic status messages
to the console while the UMS session is active.

.. note::

    ``mmc 0`` refers to the eMMC device. On some board configurations the device index may differ.
    If the command fails, check the U-boot output for the correct device index.

|

Step 4: Flash the OS image to the eMMC
----------------------------------------

On the PC, use balenaEtcher (or an equivalent tool) to write the same Red Pitaya OS image to the
eMMC USB drive that appeared in the previous step. Follow the same procedure as for a standard SD card
described in the :ref:`SD card preparation guide <prepareSD>`.

.. note::

    If the nightly build ecosystem is required, write the Linux OS image first, then extract the
    ecosystem archive directly to the eMMC drive as described in the
    :ref:`nightly build installation guide <nightly_build_installation>`.

|

Step 5: Exit UMS mode and boot the full system
------------------------------------------------

1.  Once the image has been written, safely eject the USB drive on the PC.
#.  Press **Ctrl+C** in the serial terminal to stop the UMS session and return to the U-boot prompt.
#.  Type ``reset`` (or power-cycle the board using the P-ON button) to reboot into the full OS from the
    SD card:

    .. code-block:: text

        reset

|

Step 6: Write the boot loader to QSPI flash
--------------------------------------------

After Red Pitaya has booted from the SD card, log in to the Linux console using the default credentials
(**root / root**) and write the boot image to the QSPI flash memory:

.. code-block:: bash

    flashcp /opt/redpitaya/boot.bin /dev/mtd0

This programs the on-board QSPI flash with the latest boot loader, which is required for the board to
boot from the eMMC without an SD card present.

.. warning::

    Ensure the Red Pitaya OS has fully booted before running this command. Running ``flashcp`` on an
    incomplete or incorrect ``boot.bin`` file may leave the board unable to boot from QSPI/eMMC.

|

Step 7: Remove the SD card and boot from eMMC
-----------------------------------------------

1.  Power off the Red Pitaya by pressing and holding the **P-ON** button for 1 second.
#.  Remove the microSD card from the SD card slot.
#.  Turn on the switch on the QSPI eMMC module to enable eMMC boot.
#.  Press the **P-ON** button to power the board on. Red Pitaya will now boot from the eMMC.

|

Summary of steps
=================

1.  Disable the watchdog on the E3 module (firmware edit or I2C command).
#.  Prepare an SD card with Red Pitaya OS 2.00 or later (including nightly build if required).
#.  Boot the board, stop at U-boot autoboot, and run ``ums 0 mmc 0``.
#.  Flash the OS image to the eMMC from the PC.
#.  Reboot into the full OS from the SD card.
#.  Write ``boot.bin`` to QSPI flash with ``flashcp /opt/redpitaya/boot.bin /dev/mtd0``.
#.  Power off, remove the SD card, enable eMMC boot, and power on.

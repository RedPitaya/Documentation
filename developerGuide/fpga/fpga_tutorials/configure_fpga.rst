.. _fpga_tutorial_configure_fpga:

####################################
Tutorial Helper: configure_fpga.sh
####################################

.. warning::

    ``configure_fpga.sh`` is a **tutorial-only utility script**. It is not part of the official Red Pitaya software stack and is not supported for production use.

    For official FPGA loading on OS 2.07-43 or newer, use the ``overlay.sh`` script instead. See :ref:`fpga_reprogramming` for the full reference.

|

Overview
========

The tutorials in this series produce a compiled FPGA bitstream that must be loaded onto the Red Pitaya board to test and verify your design. The standard
official tool for this is ``overlay.sh``, which manages device tree overlays and is the correct approach for production workflows.

However, ``overlay.sh`` requires a matching device tree overlay (``.dtbo``) file alongside the bitstream. Custom tutorial projects do not ship with a
pre-built device tree overlay, which means using ``overlay.sh`` directly requires extra steps that are out of scope for these tutorials.

``configure_fpga.sh`` solves this by **directly replacing the active FPGA bitstream file** on the SD card before the next boot or reload, without
requiring a device tree overlay. The script does **not** modify the device tree — the device tree already loaded at boot (for the v0.94 image) remains
active. Tutorial projects are designed to be compatible with this device tree, so no changes are needed. This trades some safety and flexibility for
simplicity, making it appropriate for development and learning.

.. list-table:: configure_fpga.sh vs overlay.sh
    :header-rows: 1
    :widths: 30 35 35

    * - Property
      - ``configure_fpga.sh``
      - ``overlay.sh``
    * - Purpose
      - Tutorial development
      - Production / official use
    * - Device tree overlay required
      - No
      - Yes
    * - Automatic restore on reboot
      - No (disk write is persistent)
      - No (disk write is persistent, ``overlay.sh`` must be run manually)
    * - Backup of original image
      - Yes (``fpga_orig.*`` created automatically)
      - N/A (managed by the OS)
    * - Board model auto-detection
      - Yes
      - Yes
    * - OS version auto-detection
      - Yes (reads ``/root/.version``)
      - Yes

|

How It Works
============

The script performs the following steps:

1. Reads the OS version from ``/root/.version`` to determine the correct bitstream file extension (``.bin`` for OS 3.x, ``.bit.bin`` for OS 2.x).
2. Auto-detects the board model using ``/opt/redpitaya/bin/monitor -f``.
3. Remounts the FPGA filesystem partition as read/write.
4. On first run, creates a backup of the original bitstream as ``fpga_orig.*`` — **this backup is permanent and is not overwritten on subsequent runs**.
5. Replaces the active bitstream file with your custom one (or restores the original if no bitstream is provided).
6. Remounts the partition as read-only.

The new bitstream takes effect after FPGA reprogramming (e.g., on reboot or by manually triggering an FPGA reload). The simplest way is to reboot:

.. code-block:: bash

    reboot

|

Prerequisites
=============

* Red Pitaya board running OS 2.00 or newer (2.x or 3.x)
* :ref:`SSH access <ssh>` to the Red Pitaya board
* Root privileges on the board (the SSH session is root by default)
* A compiled bitstream (``.bin`` or ``.bit.bin``) transferred to the board

.. note::

    The bitstream must already be on the board before running the script. Use ``scp`` or the Red Pitaya web interface to transfer it. 
    See :ref:`Copy bitstream to board <fpga_copy_project>`.

|

Usage
=====

**Syntax**

.. code-block:: bash

    configure_fpga.sh [-h] [BITSTREAM] [PROJ]

**Arguments**

.. list-table::
    :header-rows: 1
    :widths: 20 80

    * - Argument
      - Description
    * - ``BITSTREAM``
      - Path to the custom bitstream file on the board. If omitted, the script restores the original bitstream.
    * - ``PROJ``
      - The FPGA project slot to target. Defaults to ``v0.94``, which is used by all tutorials in this series.

**Options**

.. list-table::
    :header-rows: 1
    :widths: 20 80

    * - Option
      - Description
    * - ``-h``, ``--help``
      - Print usage information and exit.

|

Examples
========

**Load a custom bitstream (most common during tutorial development)**

.. code-block:: bash

    configure_fpga.sh /root/my_project.bin

This loads ``my_project.bin`` into the ``v0.94`` project slot. The original bitstream is backed up automatically on the first run.

**Load a custom bitstream and specify a project slot explicitly**

.. code-block:: bash

    configure_fpga.sh /root/my_project.bin v0.94

**Restore the original bitstream**

.. code-block:: bash

    configure_fpga.sh

Calling the script with no arguments restores ``fpga_orig.*`` back to ``fpga.*``. This requires that a backup was already created by a previous run.

**Print help**

.. code-block:: bash

    configure_fpga.sh -h

|

Restoring the Original FPGA
============================

.. warning::

    Because ``configure_fpga.sh`` physically replaces the ``fpga.*`` bitstream file on the SD card, running ``overlay.sh v0.94`` will **not** restore the
    original image — it will simply reload the same custom bitstream that is now on disk. ``overlay.sh`` has no knowledge of the backup created by this script.

There are two ways to restore the factory FPGA image:

1. **Using the script** (requires a previous backup to exist):

   .. code-block:: bash

       configure_fpga.sh

   This restores ``fpga_orig.*`` back to ``fpga.*``. The backup is created automatically on the first run of the script and is never overwritten.

2. **Reflashing the SD card** (always works, removes all modifications):

   If the backup file no longer exists or you want a fully clean state, reflash the SD card with the official OS image.
   See :ref:`OS update <os_update>` for instructions.

|

Script Source
=============

The script is available in the Red Pitaya FPGA tutorials repository. Copy it to the Red Pitaya board via ``scp``:

.. code-block:: bash

    scp configure_fpga.sh root@<board_ip>:/root/

Then make it executable:

.. code-block:: bash

    chmod +x /root/configure_fpga.sh

.. seealso::

    - :ref:`fpga_reprogramming` — Official FPGA loading reference (``overlay.sh``, ``fpgautil``)
    - :ref:`fpga_copy_project` — How to transfer files to the Red Pitaya board

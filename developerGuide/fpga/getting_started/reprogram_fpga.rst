.. _fpga_reprogramming:

########################
FPGA Reprogramming Guide
########################

This guide covers the basics of loading FPGA bitstreams on Red Pitaya boards. Learn how to load pre-built FPGA projects, upload custom designs, verify configuration, and revert to factory settings.

.. seealso::

    **Advanced Topics:**
    
    - :ref:`fpga_boot_loading` - Make your FPGA load automatically at boot
    - :ref:`fpga_advanced_loading` - Custom bitstreams, device trees, practical workflows, and FAQ
    - :ref:`device_tree` - Device tree configuration for custom hardware
    - :ref:`signal_mapping` - Hardware signal connections and pinout

.. contents:: Table of Contents
    :local:
    :depth: 2
    :backlinks: top

|

**********************************
Overview
**********************************

Understanding FPGA Loading Methods
====================================

Red Pitaya uses different FPGA loading mechanisms depending on the OS version:

.. list-table::
    :header-rows: 1
    :widths: 20 40 40

    * - OS Version
      - Method
      - Key Features
    * - 1.04 or older
      - Direct ``/dev/xdevcfg`` access
      - Simple but no device tree management
    * - 2.00 to 2.05-37
      - ``fpgautil`` command
      - Linux FPGA Manager framework
    * - 2.07-43 or newer
      - ``overlay.sh`` script
      - Automated device tree handling, verification

.. note::

    Starting with OS 2.00, Red Pitaya adopted the Linux FPGA Manager framework, which provides better integration with the kernel and enables device tree overlay support.

|

When to Use This Guide
======================

Use this guide when you need to:

- Load a custom FPGA design you created
- Switch between different pre-built FPGA projects
- Test FPGA modifications during development
- Verify FPGA configuration
- Revert to factory FPGA settings

For advanced topics like boot loading, custom device trees, and partial reconfiguration, see the :ref:`Advanced FPGA Loading guide <fpga_advanced_loading>`.

|

Prerequisites
=============

Hardware and Access
-------------------

* Red Pitaya board :ref:`powered and connected to the local network <quickstart_connect>`
* :ref:`SSH access <ssh>` to the Red Pitaya device

File Requirements
-----------------

Depending on your use case, you'll need:

**For OS 2.00 or newer:**

* Binary bitstream file (``.bit.bin``)
* Device tree overlay file (``.dtbo``) - optional for custom peripherals (see :ref:`fpga_advanced_loading`)

**For OS 1.04 or older:**

* FPGA bitstream file (``.bit``)

**Command Line Notation**

Throughout this guide:

* **Commands with "redpitaya>" prefix** - Execute inside Red Pitaya Linux OS after establishing an :ref:`SSH <ssh>` connection
* **Commands without the prefix** - Execute in your computer's local terminal or command prompt

|

**********************************
Quick Start
**********************************

For experienced users who just need the commands:

.. tabs::

    .. tab:: OS 2.07-43 or newer

        .. code-block:: bash

            # Upload bitstream
            scp red_pitaya_top.bit.bin root@rp-xxxxxx.local:/root
            
            # Load FPGA
            ssh root@rp-xxxxxx.local
            redpitaya> fpgautil -b /root/red_pitaya_top.bit.bin
            
            # Or load pre-built project
            redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 v0.94

    .. tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            # Upload bitstream
            scp red_pitaya_top.bit.bin root@rp-xxxxxx.local:/root
            
            # Load FPGA
            ssh root@rp-xxxxxx.local
            redpitaya> fpgautil -b /root/red_pitaya_top.bit.bin

    .. tab:: OS 1.04 or older

        .. code-block:: bash

            # Upload bitstream
            scp red_pitaya_top.bit root@rp-xxxxxx.local:/root
            
            # Load FPGA
            ssh root@rp-xxxxxx.local
            redpitaya> cat /root/red_pitaya_top.bit > /dev/xdevcfg

|

**********************************
Preparing FPGA Files
**********************************

Converting .bit to .bit.bin
============================

If you have a ``.bit`` file from Vivado, convert it to ``.bit.bin`` format for OS 2.00+.

.. note::

    This conversion is only needed for Red Pitaya OS 2.00 or newer. OS 1.04 uses ``.bit`` files directly.

|

Navigate to .bit File Location
-------------------------------

Open your terminal and go to the directory containing your bitstream:

.. code-block:: bash

    cd <Path/to/RedPitaya/repository>/prj/<project_name>/project/redpitaya.runs/impl_1

.. note::

    On **Windows**, change forward slashes to backward slashes in paths.

|

Create .bif File and Generate .bit.bin
---------------------------------------

The ``bootgen`` tool converts the bitstream using a ``.bif`` (Boot Image Format) configuration file.

.. tabs::

    .. group-tab:: Linux

        .. code-block:: bash

            echo -n "all:{ red_pitaya_top.bit }" > red_pitaya_top.bif
            bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

    .. group-tab:: Windows (Vivado TCL Console)

        Open Vivado and use the TCL console, or use the Vivado HSL Command Prompt:

        .. code-block:: bash

            echo all:{ red_pitaya_top.bit } > red_pitaya_top.bif
            bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

.. tip::

    The difference between Linux and Windows is in the ``echo`` command:
    
    - **Linux:** Use ``echo -n`` to avoid newline characters
    - **Windows:** Standard ``echo`` without ``-n`` flag

|

Uploading Files to Red Pitaya
==============================

Transfer Bitstream via SCP
---------------------------

Use the ``scp`` command to copy files from your computer to Red Pitaya:

**For OS 1.04 or older (.bit file):**

.. code-block:: bash

    scp red_pitaya_top.bit root@rp-xxxxxx.local:/root

**For OS 2.00 or newer (.bit.bin file):**

.. code-block:: bash

    scp red_pitaya_top.bit.bin root@rp-xxxxxx.local:/root

.. tip::

    For graphical file transfer on Windows, use WinSCP or FileZilla.

|

Verify File Upload
------------------

Connect via SSH and check the files:

.. code-block:: bash

    redpitaya> cd
    redpitaya> ls -lh

You should see your uploaded files in the ``/root`` directory.

|

**********************************
Loading FPGA
**********************************

Choose the method appropriate for your Red Pitaya OS version.


OS 2.07-43 or Newer (Recommended)
==================================

For OS 2.07+, you can use either ``fpgautil`` (for bitstream only) or ``overlay.sh`` (for bitstream + device tree).

Loading Pre-Built FPGA Projects
--------------------------------

Red Pitaya includes pre-built FPGA images. Load them directly by name:

.. code-block:: bash

    # Load default v0.94 project
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 v0.94
    
    # Load streaming application
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 stream_app
    
    # Load logic analyzer
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 logic

Loading Custom Bitstream
-------------------------

For simple FPGA loading without device tree changes:

.. code-block:: bash

    # Load bitstream only (keeps current device tree)
    redpitaya> fpgautil -b /root/red_pitaya_top.bit.bin

For advanced custom configurations with device trees, see :ref:`fpga_advanced_loading`.

|

OS 2.00 to 2.05-37 (fpgautil Method)
=====================================

Starting with OS 2.00, Red Pitaya adopted the Linux FPGA Manager framework. Use the ``fpgautil`` command to load bitstreams.

Loading FPGA Bitstream
----------------------

1. Ensure the ``.bit.bin`` file is uploaded to Red Pitaya

2. Load using ``fpgautil``:

    .. code-block:: bash

        redpitaya> fpgautil -b red_pitaya_top.bit.bin

**Features:**

- Uses Linux FPGA Manager framework
- Validates bitstream compatibility
- Reports loading status

|

OS 1.04 or Older (Legacy Method)
=================================

This method uses direct access to the ``/dev/xdevcfg`` device for FPGA configuration.

Loading FPGA Bitstream
----------------------

1. Ensure the ``.bit`` file is uploaded to Red Pitaya

2. Load the bitstream:

    .. code-block:: bash

        redpitaya> cat red_pitaya_top.bit > /dev/xdevcfg

The FPGA is immediately reconfigured with your design.

**Limitations:**

- No device tree management
- No automatic verification

|

**********************************
Verification and Troubleshooting
**********************************

Confirming FPGA Configuration
==============================

There are several ways to confirm that the FPGA has been successfully reprogrammed.

|

Method 1: Check Status Files (OS 2.07+)
----------------------------------------

The overlay script creates verification files:

**Check loaded project identifier:**

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf

**Example outputs:**

.. code-block:: text

    v0.94                      # Standard project
    v0.94_my_project           # Custom bitstream
    v0.94_my_project_dtbo      # Custom bitstream + device tree

**Check detailed loading information:**

.. code-block:: bash

    redpitaya> cat /tmp/update_fpga.txt

**Example output:**

.. code-block:: text

    Commit a1b2c3d4
    FPGA md5sum: d41d8cd98f00b204e9800998ecf8427e  /opt/redpitaya/fpga/Z10/v0.94/fpga.bit.bin
    Tue Oct 24 10:30:45 UTC 2025

|

Method 2: Check FPGA Manager State
-----------------------------------

Verify the FPGA Manager successfully loaded the configuration:

.. code-block:: bash

    redpitaya> cat /sys/class/fpga_manager/fpga0/state

**Expected output:** ``operating``

**Other possible states:**

- ``unknown`` - FPGA Manager not initialized
- ``write init`` - Starting configuration
- ``write`` - Writing bitstream
- ``write complete`` - Bitstream written successfully
- ``write error`` - Configuration failed

|

Method 3: Check Custom Register
--------------------------------

If your FPGA design includes an ID register, verify it directly:

.. code-block:: bash

    redpitaya> /opt/redpitaya/bin/monitor 0x40300050

The command should return your expected register value (e.g., ``0xfeedbacc`` from the :ref:`Adding a custom component tutorial <fpga_tutorial_cust_comp>`).

|

Method 4: Test LED Patterns
----------------------------

For designs that control LEDs, observe the 8 yellow LEDs on the board to verify your custom pattern.

|

Common Issues and Solutions
============================

Error: "BIN FILE loading through FPGA manager failed"
-----------------------------------------------------

.. code-block:: bash

    sh: 1: echo: echo: I/O error
    BIN FILE loading through FPGA manager failed

**Possible causes and solutions:**

1. **Bitstream incompatible with board model**
    
    Check your Red Pitaya model and verify build flags:
    
    .. code-block:: bash
    
        redpitaya> /opt/redpitaya/bin/monitor -f
    
    Rebuild FPGA with :ref:`correct model flags <fpga_create_project>` (``MODEL=Z10``, ``MODEL=Z20``, etc.)

2. **Corrupted bitstream file**
    
    Verify file integrity:
    
    .. code-block:: bash
    
        redpitaya> ls -lh /root/red_pitaya_top.bit.bin
        redpitaya> md5sum /root/red_pitaya_top.bit.bin
    
    Re-generate and re-upload the file if sizes don't match (~2-4 MB typical)

3. **Wrong file path or filename**
    
    Ensure exact filename:
    
    .. code-block:: bash
    
        redpitaya> ls /opt/my_project/
        # Must show: fpga.bit.bin (case-sensitive!)

4. **Incorrect .bit to .bit.bin conversion**
    
    Verify bootgen command completed without errors and retry conversion

|

Error: "Device tree overlay not found"
---------------------------------------

**For standard device tree:**

Check that base project exists:

.. code-block:: bash

    redpitaya> MODEL=$(/opt/redpitaya/bin/monitor -f)
    redpitaya> ls /opt/redpitaya/fpga/$MODEL/v0.94/fpga.dtbo

**For custom device tree:**

Ensure file exists and has correct name:

.. code-block:: bash

    redpitaya> ls /opt/my_project/fpga.dtbo

|

FPGA Loads But Applications Don't Work
---------------------------------------

**Possible causes:**

1. **Device tree mismatch** - FPGA hardware doesn't match device tree description
    
    - Regenerate device tree from Vivado (see :ref:`device_tree`)
    - Verify register addresses match your FPGA design
    - Check that peripheral names and properties are correct

2. **Custom peripherals not accessible**
    
    Test register access:
    
    .. code-block:: bash
    
        # Try reading a register (use your address)
        redpitaya> /opt/redpitaya/bin/monitor 0x40000000
    
    If reads return 0 or fail, check device tree memory regions

3. **Incorrect clock configuration**
    
    - Verify PL clocks are enabled in FPGA design
    - Check clock frequencies match device tree specifications
    - Ensure AXI clock domains are correctly configured

For more troubleshooting guidance, see the comprehensive FAQ in :ref:`fpga_advanced_loading`.

|

**********************************
Reverting to Factory FPGA
**********************************

If you want to return to the official Red Pitaya FPGA, use these methods.

Method 1: Reload Factory FPGA (Simple)
=======================================

For OS 2.00 or newer, simply load the default project:

.. tabs::

    .. tab:: OS 2.07+ (overlay.sh)

        .. code-block:: bash

            redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 v0.94

    .. tab:: OS 2.00-2.05 (fpgautil)

        .. code-block:: bash

            redpitaya> fpgautil -b /opt/redpitaya/fpga/$(monitor -f)/v0.94/fpga.bit.bin

Or restart your Red Pitaya:

.. code-block:: bash

    redpitaya> reboot

.. note::

    This works unless you've configured boot loading (see :ref:`fpga_boot_loading`) or replaced the default FPGA image.

|

Method 2: Disable Boot Loading
===============================

If you set up automatic FPGA loading at boot, disable it:

**For startup.sh method:**

.. code-block:: bash

    redpitaya> rw
    redpitaya> nano /opt/redpitaya/sbin/startup.sh
    # Comment out or remove your FPGA loading line
    redpitaya> ro
    redpitaya> reboot

**For systemd service:**

.. code-block:: bash

    redpitaya> rw
    redpitaya> systemctl disable custom-fpga.service
    redpitaya> systemctl stop custom-fpga.service
    redpitaya> ro
    redpitaya> reboot

See :ref:`fpga_boot_loading` for complete boot loading management.

|

Method 3: Restore Replaced FPGA Image
======================================

If you used the replacement script to overwrite system files (advanced method):

.. code-block:: bash

    # Run the replacement script without parameters
    redpitaya> /root/replace_fpga.sh
    
    # Reboot to activate
    redpitaya> reboot

This restores the backup created when you first replaced the default image.

|

Method 4: Manual Revert (OS 1.04)
==================================

For OS 1.04, reboot to reload the factory FPGA:

.. code-block:: bash

    redpitaya> reboot

The factory FPGA loads automatically at boot on OS 1.04.

|

**********************************
Related Documentation
**********************************

**FPGA Documentation:**

- :ref:`fpga_boot_loading` - Make FPGA load automatically at boot
- :ref:`fpga_advanced_loading` - Advanced loading scenarios, workflows, and FAQ
- :ref:`device_tree` - Device tree configuration for custom hardware
- :ref:`signal_mapping` - Hardware signal connections and pinout

**Developer Guides:**

- :ref:`Red Pitaya FPGA Developer Guide <fpga_top>` - FPGA development overview
- :ref:`Adding a custom component <fpga_tutorial_cust_comp>` - FPGA tutorial
- :ref:`C and Python API <C&Py_API>` - Software interface

**Application Examples:**

- :rp-github:`Red Pitaya GitHub repository - Example designs <RedPitaya-Examples>`
- :rp-forum:`Red Pitaya forum - Community projects <>`

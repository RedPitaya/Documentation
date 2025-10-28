.. _overlay_util:

######################################
Overlay Utility (FPGA Configuration)
######################################

The ``overlay.sh`` script is the recommended method for loading FPGA images on Red Pitaya devices running OS 2.00 or newer. 
It provides a simple interface for managing FPGA configurations, including custom bitstreams and device tree overlays.

.. contents:: Table of Contents
    :backlinks: top

|


Overview
=========

The overlay script (``overlay.sh``) is a command-line tool that manages FPGA configuration on Red Pitaya boards. It handles:

- Loading FPGA bitstream files
- Applying device tree overlays
- Managing FPGA reconfiguration
- Tracking loaded FPGA images
- Supporting partial reconfiguration regions

Starting with Red Pitaya OS 2.00, the FPGA loading mechanism changed from direct ``/dev/xdevcfg`` access to the Linux FPGA Manager framework. 
The ``overlay.sh`` script provides:

- Compatibility with OS 2.00+ FPGA loading system
- Device tree management - automatically loads matching overlays
- Verification - tracks and validates loaded configurations
- Simplified workflow - one command instead of multiple steps
- Partial reconfiguration support for advanced users

.. note::

    For Red Pitaya OS 1.04 and older, use the legacy ``cat bitstream.bit > /dev/xdevcfg`` method instead. 
    See :ref:`FPGA Reprogramming Guide <fpga_reprogramming>` for details.

|


Basic Usage
============

Access via SSH
--------------

The overlay script requires :ref:`SSH access <ssh>` to the Red Pitaya device:

.. code-block:: bash

    ssh root@rp-xxxxxx.local

Loading Standard FPGA Projects
--------------------------------

Red Pitaya includes pre-built FPGA images in ``/opt/redpitaya/fpga/``. To load a standard project:

.. code-block:: bash

    redpitaya> overlay.sh v0.94

Other standard projects:

.. code-block:: bash

    # Load streaming application
    redpitaya> overlay.sh stream_app
    
    # Load logic analyzer
    redpitaya> overlay.sh logic

.. note::

    The script automatically detects your Red Pitaya model and loads the appropriate FPGA image.

|


Command Syntax
===============

Basic syntax:

.. code-block:: text

    overlay.sh <project> [custom_folder] [dtbo] [region]

Parameters:

- ``project`` - **Required.** Base project name (e.g., ``v0.94``, ``stream_app``, ``logic``)
- ``custom_folder`` - **Optional.** Name of custom directory in ``/opt/`` containing ``fpga.bit.bin``
- ``dtbo`` - **Optional.** Literal string ``dtbo`` to use custom device tree from custom folder
- ``region`` - **Optional.** Name of the FPGA reconfigurable region (default: ``Full``)

|


Usage Examples
===============

Example 1: Load Standard Project
----------------------------------

.. code-block:: bash

    redpitaya> overlay.sh v0.94

Loads bitstream and device tree from ``/opt/redpitaya/fpga/<model>/v0.94/``


Example 2: Load Custom Bitstream
----------------------------------

.. code-block:: bash

    # Create directory and copy bitstream
    redpitaya> mkdir -p /opt/my_project
    redpitaya> cp /root/custom.bit.bin /opt/my_project/fpga.bit.bin
    
    # Load with standard device tree
    redpitaya> overlay.sh v0.94 my_project

Loads bitstream from ``/opt/my_project/fpga.bit.bin`` and device tree from standard location.


Example 3: Load Custom Bitstream and Device Tree
--------------------------------------------------

.. code-block:: bash

    # Copy both files
    redpitaya> cp /root/custom.bit.bin /opt/my_project/fpga.bit.bin
    redpitaya> cp /root/custom.dtbo /opt/my_project/fpga.dtbo
    
    # Load both custom files
    redpitaya> overlay.sh v0.94 my_project dtbo

Loads both bitstream and device tree from ``/opt/my_project/``


Example 4: Partial Reconfiguration
------------------------------------

.. code-block:: bash

    redpitaya> overlay.sh v0.94 my_project dtbo Region0

Loads custom FPGA into specific reconfigurable region (Pblock).

|


Verification
=============

Check Loaded FPGA
------------------

View FPGA loading status:

.. code-block:: bash

    redpitaya> cat /tmp/update_fpga.txt

Example output:

.. code-block:: text

    Time taken to load BIN is 207.000000 Milli Seconds
    BIN FILE loaded through FPGA manager successfully
    FPGA md5sum: 7065fc8f7786967d7cc325727a6730ce  /opt/redpitaya/fpga/z20_125_v2/v0.94/fpga.bit.bin
    Wed Oct 22 11:47:27 AM EEST 2025

Check FPGA identifier:

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf
    # Example output: v0.94

Verify FPGA manager state:

.. code-block:: bash

    redpitaya> cat /sys/class/fpga_manager/fpga0/state
    # Expected output: operating

|


Common Issues
==============

BIN FILE Loading Failed
------------------------

**Error:** "BIN FILE loading through FPGA manager failed"

**Possible causes:**

1. Bitstream incompatible with board model - verify correct MODEL flag was used during build
2. Corrupted bitstream file - re-generate and re-upload
3. Wrong file path or filename - ensure file is named exactly ``fpga.bit.bin``

**Solution:**

.. code-block:: bash

    # Check your Red Pitaya model
    redpitaya> /opt/redpitaya/bin/monitor -f
    
    # Verify file exists and has reasonable size (2-4 MB)
    redpitaya> ls -lh /opt/my_project/fpga.bit.bin

Device Tree Not Found
----------------------

**Solution:** Ensure device tree file exists in the correct location:

.. code-block:: bash

    # For standard device tree
    redpitaya> ls /opt/redpitaya/fpga/<model>/v0.94/fpga.dtbo
    
    # For custom device tree
    redpitaya> ls /opt/my_project/fpga.dtbo

FPGA Loads But Doesn't Work
-----------------------------

**Possible causes:**

1. Device tree mismatch - FPGA hardware doesn't match device tree description
2. Incorrect register addresses
3. Custom peripherals not accessible

**Solution:** Verify with monitor tool:

.. code-block:: bash

    # Test reading a register (example address)
    redpitaya> monitor 0x40000000

|


File Structure
===============

Standard FPGA files location:

.. code-block:: text

    /opt/redpitaya/fpga/
    ├── Z10/              # STEMlab 125-10/14
    ├── Z20/              # SDRlab 122-16
    ├── Z20_125/          # STEMlab 125-14 (Z7020)
    ├── Z20_250/          # SIGNALlab 250-12
    └── Z20_4/            # STEMlab 125-14 4-Input
        ├── v0.94/
        │   ├── fpga.bit.bin
        │   ├── fpga.dtbo
        │   └── git_info.txt
        ├── stream_app/
        └── logic/

Custom FPGA files location:

.. code-block:: text

    /opt/<custom_folder>/
    ├── fpga.bit.bin      # Required
    └── fpga.dtbo         # Optional (if using custom device tree)

Status files:

.. code-block:: text

    /tmp/loaded_fpga.inf       # FPGA identifier
    /tmp/update_fpga.txt       # Loading status with MD5 and timestamp

|


Converting Bitstream Files
============================

The overlay script requires binary bitstream files (``.bit.bin``). If you have a ``.bit`` file from Vivado, convert it:

**Linux:**

.. code-block:: bash

    echo -n "all:{ red_pitaya_top.bit }" > red_pitaya_top.bif
    bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

**Windows (Vivado TCL Console):**

.. code-block:: bash

    echo all:{ red_pitaya_top.bit } > red_pitaya_top.bif
    bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

|


Related Documentation
======================

For comprehensive information about the overlay script, including advanced usage, automation examples, and detailed troubleshooting, see:

- :ref:`FPGA Reprogramming Guide <fpga_reprogramming>` - FPGA loading procedures for all OS versions and detailed overlay usage
- :ref:`FPGA Project Creation <fpga_create_project>` - Building custom FPGA projects


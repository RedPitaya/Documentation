.. _overlay_util:

######################################
Overlay Utility (FPGA Configuration)
######################################

The ``overlay.sh`` script is the recommended method for loading FPGA images on Red Pitaya devices running OS 2.07-43 or newer.
It is a specialized open source shell script used by the Red Pitaya ecosystem to select and load the correct FPGA image and matching device tree overlay for the detected board model.

.. contents:: Table of Contents
    :local:
    :backlinks: top
    :depth: 1

|


Overview
=========

The overlay script (``overlay.sh``) is a command-line tool that manages FPGA configuration on Red Pitaya boards. It handles:

- Loading FPGA bitstream files
- Applying device tree overlays
- Managing FPGA reconfiguration through the ``fpgautil`` utility
- Tracking loaded FPGA images
- Supporting partial reconfiguration regions
- Selecting the standard FPGA path from the detected board profile

It does not:

- Check bitstream byte order (assumes correct format)
- Interact directly with the FPGA Manager (delegates to ``fpgautil``)

Starting with Red Pitaya OS 2.00, the FPGA loading mechanism changed from direct ``/dev/xdevcfg`` access to the Linux FPGA Manager framework.
The ``overlay.sh`` script provides:

- Compatibility with the current Red Pitaya FPGA loading system
- Device tree management - automatically loads matching overlays
- Verification - tracks and validates loaded configurations
- Simplified workflow - one command instead of multiple steps
- Partial reconfiguration support for advanced users

For built-in FPGA projects, the script reads the board profile using ``/opt/redpitaya/bin/profiles -f`` and loads files from:

.. code-block:: text

    /opt/redpitaya/fpga/<detected-model>/<fpga_name>/fpga.bit.bin
    /opt/redpitaya/fpga/<detected-model>/<fpga_name>/fpga.dtbo

If custom paths are provided, the script uses those instead of the standard files while still keeping the detected board model as the selection anchor for the Red Pitaya ecosystem.

The upstream script is available in the Red Pitaya OS repository:
`overlay.sh <https://github.com/RedPitaya/RedPitaya/blob/master/OS/filesystem/sbin/overlay.sh>`_.

.. note::

    For Red Pitaya OS 1.04 and older, use the legacy ``cat bitstream.bit > /dev/xdevcfg`` method instead. 
    See :ref:`FPGA Reprogramming Guide <fpga_reprogramming>` for details.

|


Command Help
=============

Running ``overlay.sh`` without arguments displays the command help:

.. code-block:: console

    root@rp-f0ef2d:~# overlay.sh
    Usage: /opt/redpitaya/sbin/overlay.sh <fpga_name> [custom_fpga] [custom_devicetree] [overlay_name]
    
    Load FPGA bitstream and device tree overlay
    
    Parameters:
        <fpga_name>        - Name of FPGA configuration from /opt/redpitaya/fpga/$MODEL/
        [custom_fpga]      - Custom FPGA bitstream path (optional)
        [custom_devicetree]- Custom device tree overlay path (optional)
        [overlay_name]     - Custom overlay region name (optional, default: Full)
    
    Examples:
        /opt/redpitaya/sbin/overlay.sh mercury                                                              - Load a built-in FPGA project
        /opt/redpitaya/sbin/overlay.sh oscillator /path/to/custom.bit.bin                                   - Load custom FPGA bitstream
        /opt/redpitaya/sbin/overlay.sh sdr /path/to/custom.bit.bin /path/to/custom.dtbo                     - Load custom FPGA and device tree
        /opt/redpitaya/sbin/overlay.sh transmitter /path/to/fpga.bit.bin /path/to/fpga.dtbo CustomRegion    - Load with custom overlay name
    
    Available FPGA configurations:
        - barebones
        - logic
        - pyrpl
        - stream_app
        - v0.94

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

    The script automatically detects your Red Pitaya model and loads the matching ``fpga.bit.bin`` and ``fpga.dtbo`` files from the corresponding
    ``/opt/redpitaya/fpga/<model>/<project>/`` directory.

|


Command Syntax
===============

Basic syntax:

.. code-block:: text

    overlay.sh <fpga_name> [custom_fpga] [custom_devicetree] [overlay_name]

Parameters:

- ``fpga_name`` - **Required.** Project name under ``/opt/redpitaya/fpga/<model>/`` for standard Red Pitaya FPGA images
- ``custom_fpga`` - **Optional.** Full path to a custom ``fpga.bit.bin`` file
- ``custom_devicetree`` - **Optional.** Full path to a custom ``fpga.dtbo`` file
- ``overlay_name`` - **Optional.** Name of the FPGA reconfigurable region (default: ``Full``)

.. important::

    The overlay region name ``Led`` is reserved by the system and cannot be used for custom loads.

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

    # Copy bitstream to any accessible location
    redpitaya> cp /root/custom.bit.bin /root/custom.bit.bin
    
    # Load with standard device tree
    redpitaya> overlay.sh v0.94 /root/custom.bit.bin

Loads the custom bitstream from ``/root/custom.bit.bin`` and keeps the standard device tree from ``/opt/redpitaya/fpga/<model>/v0.94/``.


Example 3: Load Custom Bitstream and Device Tree
--------------------------------------------------

.. code-block:: bash

    # Copy both files
    redpitaya> cp /root/custom.bit.bin /root/custom.bit.bin
    redpitaya> cp /root/custom.dtbo /root/custom.dtbo
    
    # Load both custom files
    redpitaya> overlay.sh v0.94 /root/custom.bit.bin /root/custom.dtbo

Loads both files from the provided custom paths.


Example 4: Partial Reconfiguration
------------------------------------

.. code-block:: bash

    redpitaya> overlay.sh v0.94 /root/custom.bit.bin /root/custom.dtbo Region0

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

    /any/path/fpga.bit.bin    # Optional custom bitstream path
    /any/path/fpga.dtbo       # Optional custom device tree path

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


Advanced Usage - fpgautil
===========================

The ``fpgautil`` utility is the low-level tool that ``overlay.sh`` calls internally to load FPGA bitstreams. 
While ``overlay.sh`` is recommended for most users, advanced users may use ``fpgautil`` directly for finer control over the FPGA loading process.

Command Help
-------------

.. code-block:: console

    root@rp-f0ef2d:~# fpgautil
    
    fpgautil: FPGA Utility for Loading/reading PL Configuration
    
    Usage:  fpgautil -b <bin file path> -o <dtbo file path>
    
    Options: -b <binfile>           (Bin file path)
             -o <dtbofile>          (DTBO file path)
             -f <flags>             Optional: <Bitstream type flags>
                                       f := <Full | Partial >
             -n <Fpga region info>  FPGA Regions represent FPGA's
                                    and partial reconfiguration
                                    regions of FPGA's in the
                                    Device Tree
    
    Examples:
    (Load Full bitstream using Overlay)
    fpgautil -b top.bit.bin -o can.dtbo -f Full -n Full
    (Load Partial bitstream using Overlay)
    fpgautil -b rm0.bit.bin -o rm0.dtbo -f Partial -n PR0
    (Load Full bitstream using sysfs interface)
    fpgautil -b top.bit.bin -f Full
    (Load Partial bitstream using sysfs interface)
    fpgautil -b rm0.bit.bin -f Partial

Usage Notes
------------

**When to use fpgautil directly:**

- Custom automation scripts requiring direct control
- Debugging FPGA loading issues
- Advanced partial reconfiguration scenarios
- Integration with custom deployment workflows

**Key differences from overlay.sh:**

- ``overlay.sh`` - Simplified interface, automatic model detection, handles file paths for you
- ``fpgautil`` - Low-level control, requires explicit paths and parameters, direct FPGA Manager interface

.. note::

    Most users should use ``overlay.sh`` instead of ``fpgautil`` directly. The overlay script provides automatic model detection, 
    simplified paths, and better error handling.

|


Related Documentation
======================

For comprehensive information about the overlay script, including advanced usage, automation examples, and detailed troubleshooting, see:

- :ref:`FPGA Reprogramming Guide <fpga_reprogramming>` - FPGA loading procedures for all OS versions and detailed overlay usage
- :ref:`FPGA Project Creation <fpga_create_project>` - Building custom FPGA projects

|

Source Code
=====================

The overlay utility script source code is available on GitHub:

- :rp-github:`overlay.sh <RedPitaya/blob/master/OS/filesystem/sbin/overlay.sh>`
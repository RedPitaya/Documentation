.. _fpga_install_sdk:

#####################################
Installation of Xilinx SDK 2019.1
#####################################

This installation tutorial is intended for anyone who wants to develop FPGA projects that also require modifications to the software running on the ARM processor of the Red Pitaya board, such as creating custom device drivers or modifying the First Stage Boot Loader (FSBL).

.. contents:: Table of Contents
    :local:
    :depth: 2
    :backlinks: top

|

Overview
=========

**What is Xilinx SDK?**

Xilinx Software Development Kit (SDK) is an integrated development environment for creating embedded software applications. For Red Pitaya FPGA development, SDK is used for:

- Generating the First Stage Boot Loader (FSBL)
- Creating and modifying device tree files
- Developing custom Linux drivers
- Building bare-metal applications for the ARM processor
- Debugging hardware-software interfaces

**Why SDK 2019.1?**

Red Pitaya FPGA projects are configured to work with SDK 2019.1 specifically. Using a different version may cause compatibility issues with:

- Device tree generation scripts
- FSBL compilation
- Hardware handoff files from Vivado
- Build automation scripts

.. note::

    Xilinx has replaced SDK with Vitis starting from version 2019.2. However, Red Pitaya projects still use SDK 2019.1 for maximum stability and compatibility. Future versions will migrate to Vitis.

|

Prerequisites
==============

Before installing SDK, ensure you have:

**System Requirements**

- **Operating System:** 
  
  - Ubuntu 18.04/20.04/22.04/24.04
  - Windows 10 or later (with limitations, not recommended)
  
- **Disk Space:** Minimum 60 GB free space (100 GB recommended)
- **RAM:** Minimum 8 GB (16 GB recommended)
- **Internet Connection:** For downloading installer (~24 GB)

**Software Prerequisites**

- **Vivado 2020.1** must be installed first (see :ref:`Vivado Installation Guide <FPGA_install_vivado>`)
- **Git** command-line tools
- Required system libraries (Linux)

**User Account**

- AMD account (free registration at https://login.amd.com/)
- Download access to archived SDK versions

.. note::

    SDK 2019.1 is required for building the :ref:`Red Pitaya OS <SW_os_req>` and :ref:`ecosystem <SW_ecosys_req>`, both of which are supported only on Ubuntu Linux. 
    For best results in building SDK-based projects, use Ubuntu as the native platform.

|

Installation Steps
===================

Download SDK 2019.1 Installer
-------------------------------

1. **Create/Login to AMD Account**

    Visit the |AMD-login| and create a free account if you don't have one.

2. **Navigate to Vivado SDK Downloads**

    Go to the |Vivado-downloads-archive| (Vitis/SDK Archive page).

3. **Select Vivado 2019.1**

    - Scroll to find **2019.1** version
    - You will see multiple installer options, find the following version:
   
        - **Vivado Design Suite - HLx Editions - 2019.1  Full Product Installation**

4. **Download the Installer**

    - Download: ``Vivado HLx 2019.1: All OS installer Single-File Download``
    - File size: ~21.39 GB

    .. figure:: img/SDK-install/SDK-tar-file.png
        :align: center
        :width: 1000

.. note::

    **Important:** Since SDK web installers do not work anymore, please download the full Vivado 2019.1 installer from the archive which also includes the SDK 2019.1.

|

Install Required Libraries (Linux Only)
----------------------------------------

Before running the SDK installer on Linux, install required system libraries:

.. code-block:: bash

   # Update package list
   sudo apt update
   
   # Install required libraries for SDK
   sudo apt install -y \
       libxft2 \
       libxft2:i386 \
       lib32stdc++6 \
       libgtk2.0-0:i386 \
       dpkg-dev:i386 \
       libncurses5 \
       libtinfo5
   
   # Install additional dependencies for FSBL and device tree generation
   sudo apt install -y \
       libncurses-dev \
       libedit-dev \
       libxrender-dev \
       libxrender-dev:i386 \
       libxt6 \
       libxt6:i386

.. note::

   If you're using Ubuntu 22.04 or newer, some 32-bit libraries may not be available in default repositories. If you encounter missing package errors, you may need to enable i386 architecture:

   .. code-block:: bash

      sudo dpkg --add-architecture i386
      sudo apt update
      sudo apt install <package-name>:i386

|

Run the SDK Installer
-----------------------

Linux Installation
~~~~~~~~~~~~~~~~~~~

1. **Extract the installer:**

    - Navigate to your download directory
    - Extract the downloaded ``.tar.gz`` file:
    
    .. code-block:: bash
    
        tar -xvf Xilinx_Vivado_SDK_2019.1_0524_1430.tar.gz

2. **Make the installer executable:**

    .. code-block:: bash

        # Navigate to download directory
        cd ~/Downloads
        
        # Make installer executable
        chmod +x Xilinx_Vivado_SDK_2019.1_0524_1430.bin

3. **Handle OS Version Warning (Ubuntu 20.04/22.04):**

    Vivado SDK 2019.1 officially supports Ubuntu 18.04. If you're running a newer version and the installer gives an OS version warning, you can temporarily modify ``/etc/os-release``:

    .. code-block:: bash

        # Backup the original file
        sudo cp /etc/os-release /etc/os-release.backup
        
        # Edit the file
        sudo nano /etc/os-release

    Change the VERSION line to:

    .. code-block:: text

        VERSION="18.04.4 LTS (Bionic Beaver)"

    Save and exit (Ctrl+X, then Y, then Enter).

    .. figure:: img/Vivado-installer-linux-warning3.png
        :align: center
        :width: 800

3. **Run the installer:**

    .. code-block:: bash

        # Run installer
        sudo ./Xilinx_Vivado_SDK_2019.1_0524_1430.bin

    The graphical installer will launch.

4. **Restore os-release (Important!):**

    After installation completes, restore the original file:

    .. code-block:: bash

        sudo mv /etc/os-release.backup /etc/os-release

    **Failure to restore this file may cause issues with other software!**

Windows Installation
~~~~~~~~~~~~~~~~~~~~~

1. **Extract the installer:**

    - Navigate to your download directory
    - Extract the downloaded ``.tar.gz`` file using 7-Zip or similar tool.

1. **Run the installer executable:**

   - Open the extracted folder and run the ``xsetup.exe`` executable.
   - Windows may ask for administrator permissions - click "Yes"

2. **Follow the installer wizard:**

   The graphical installer will launch.

|

SDK Installation Wizard Steps
-------------------------------

1. **Welcome Screen**

    - Close the "newer version available" message if it appears.
    - Click **Next**

    .. figure:: img/SDK-install/SDK-installer-1.png
        :align: center
        :width: 1000

2. **Accept License Agreements**

    - Check all "I Agree" boxes
    - Click **Next**

    .. figure:: img/SDK-install/SDK-installer-2.png
        :align: center
        :width: 1000

3. **Select Edition**

    - Choose **Vivado HL Design Edition**
    - Click **Next**

    .. figure:: img/SDK-install/SDK-installer-3.png
        :align: center
        :width: 1000

    .. note::

        Vivado HL Design Edition also includes the SDK 2019.1.

4. **Select Installation Options**

   Check these components:

   - ✅ **Software Development Kit (SDK)**
   - ✅ **DocNav** (documentation browser - optional but recommended)

   Uncheck components you don't need to save space. See the figure below for reference.

    .. figure:: img/SDK-install/SDK-installer-4.png
        :align: center
        :width: 1000

5. **Choose Installation Location**

    **Default paths:**
    
    - **Linux:** ``/opt/Xilinx/SDK/2019.1`` or ``/tools/Xilinx/SDK/2019.1``
    - **Windows:** ``C:\Xilinx\SDK\2019.1``

    .. note::

        **Important for Linux:** If you installed Vivado in ``/opt/Xilinx/``, install SDK in the same parent directory (``/opt/Xilinx/SDK/2019.1``) to keep tools organized.

    Click **Next**

    .. figure:: img/SDK-install/SDK-installer-5.png
       :align: center
       :width: 1000

6. **Installation Summary**

    - Review your selections
    - Note the installation size (approximately 25 GB)
    - Click **Install**

    .. figure:: img/SDK-install/SDK-installer-6.png
        :align: center
        :width: 1000

7. **Installation Progress**

    - The installation may take 30-60 minutes depending on your system

8. **Installation Completed**

    - Click **Finish**
    - **Do NOT** launch SDK immediately; we need to configure environment variables first

9. **Delete Vivado 2019.1 Files (Optional)**

    Since we already have Vivado 2020.1 installed, you can delete the Vivado 2019.1 files to free up disk space:

    .. code-block:: bash

        sudo rm -rf /opt/Xilinx/Vivado/2019.1

10. **Restore os-release (Linux Only)**

    If you modified ``/etc/os-release`` earlier, ensure you have restored it to the original version as described in Step 4 of the Linux installation section.

|

Post-Installation Configuration
=================================

Environment Variables (Linux)
-------------------------------

After installation, you must configure environment variables so the system can find SDK executables.

**Temporary Configuration (Current Terminal Session Only)**

Run these commands in your terminal:

.. code-block:: bash

    # Source SDK settings script
    source /opt/Xilinx/SDK/2019.1/settings64.sh
    
    # Add SDK to PATH (may be necessary for some tools)
    export PATH=/opt/Xilinx/SDK/2019.1/bin:$PATH

.. note::

    Replace ``/opt/Xilinx/`` with your actual installation directory if different.

**Permanent Configuration (Recommended)**

Add the SDK settings to your ``.bashrc`` file so they're loaded automatically:

.. code-block:: bash

    # Open .bashrc in text editor
    nano ~/.bashrc

Add these lines at the end of the file:

.. code-block:: bash

    # Xilinx Vivado 2020.1 settings
    source /opt/Xilinx/Vivado/2020.1/settings64.sh
    
    # Xilinx SDK 2019.1 settings
    source /opt/Xilinx/SDK/2019.1/settings64.sh
    
    # Add SDK to PATH
    export PATH=/opt/Xilinx/SDK/2019.1/bin:$PATH

Save and exit (Ctrl+X, Y, Enter).

**Apply changes:**

.. code-block:: bash

    # Reload .bashrc
    source ~/.bashrc

Environment Variables (Windows)
---------------------------------

**Method 1: Automatic Setup**

The Windows installer typically adds environment variables automatically. Verify by opening a new Command Prompt and typing:

.. code-block:: batch

    echo %XILINX_SDK%

If it shows the SDK path, you're set. If not, proceed to Method 2.

**Method 2: Manual Configuration**

1. Right-click "This PC" or "My Computer" → **Properties**
2. Click **Advanced system settings**
3. Click **Environment Variables**
4. Under "System variables", click **New**

Add these variables:

- **Variable name:** ``XILINX_SDK``
  **Variable value:** ``C:\Xilinx\SDK\2019.1``

- **Variable name:** ``XILINX_VIVADO``
  **Variable value:** ``C:\Xilinx\Vivado\2020.1``

5. Edit the **Path** variable:
   
    - Select **Path** → Click **Edit**
    - Click **New**
    - Add: ``C:\Xilinx\SDK\2019.1\bin``
    - Add: ``C:\Xilinx\Vivado\2020.1\bin``

6. Click **OK** on all windows

7. **Restart your terminal** or computer for changes to take effect

For detailed Windows PATH instructions, see `this Windows PATH guide <https://www.computerhope.com/issues/ch000549.htm>`__.

|

Verify Installation
====================

Test SDK Command-Line Tools
-----------------------------

**Linux:**

.. code-block:: bash

    # Check SDK version
    which xsdk
    
    # Expected output: /opt/Xilinx/SDK/2019.1/bin/xsdk
    
    # Check HSI (Hardware Software Interface) tool
    which hsi
    
    # Expected output: /opt/Xilinx/SDK/2019.1/bin/hsi
    
    # Verify SDK is in PATH
    echo $PATH | grep SDK

**Windows:**

.. code-block:: batch

    # Check SDK installation
    where xsdk
    
    # Expected output: C:\Xilinx\SDK\2019.1\bin\xsdk.bat
    
    # Check environment variable
    echo %XILINX_SDK%

Launch SDK GUI (Optional Test)
--------------------------------

To verify the graphical interface works:

**Linux:**

.. code-block:: bash

    # Launch SDK
    xsdk &

**Windows:**

.. code-block:: batch

    # Launch SDK
    xsdk

SDK should open with a workspace selection dialog. You can close it after verifying it launches successfully.

|

Using SDK with Red Pitaya Projects
====================================

SDK Integration with Build System
-----------------------------------

Red Pitaya FPGA projects use SDK for:

1. **FSBL Generation:** Creates the First Stage Boot Loader
2. **Device Tree Generation:** Generates device tree files for Linux kernel
3. **Hardware-Software Interface:** Bridges FPGA hardware with ARM software

**Build Commands Using SDK:**

When you build Red Pitaya FPGA projects, SDK is invoked automatically by Make:

.. code-block:: bash

    # Build FPGA project (includes FSBL and device tree generation)
    make PRJ=v0.94 MODEL=Z10
    
    # Build only FSGA (skips SDK parts)
    make build PRJ=v0.94 MODEL=Z10

.. !! Check the make build above - does it exist?

SDK Components Used
--------------------

**HSI (Hardware Software Interface)**

The ``hsi`` command-line tool is used in TCL scripts to:

- Read hardware handoff files (``.hdf``) from Vivado
- Generate FSBL source code
- Generate device tree source files
- Configure processor settings

**XSCT (Xilinx Software Command-line Tool)**

Used for:

- Building FSBL executables
- Cross-compiling ARM applications
- Debugging via JTAG

**File Locations in Red Pitaya Build:**

.. code-block:: text

   fpga/
   ├── prj/v0.94/
   │   └── sdk/
   │       └── fsbl/           # FSBL source generated by HSI
   ├── hsi/
   │   ├── fsbl.elf            # Compiled FSBL binary
   │   └── dts/                # Device tree sources
   └── dts/
       └── system.dts          # Final device tree file

|

Common SDK Usage Scenarios
============================

Scenario 1: Building FPGA with FSBL
-------------------------------------

To build a complete FPGA project including FSBL:

.. code-block:: bash

    # Navigate to FPGA repository
    cd RedPitaya-FPGA
    
    # Source environment variables (if not in .bashrc)
    source /opt/Xilinx/Vivado/2020.1/settings64.sh
    source /opt/Xilinx/SDK/2019.1/settings64.sh
    
    # Build everything (bitstream, FSBL, device tree)
    make PRJ=v0.94 MODEL=Z10

SDK will be invoked during the build to generate FSBL and device tree.

Scenario 2: Generating Only FSBL
----------------------------------

To regenerate only the FSBL without rebuilding the entire FPGA:

.. code-block:: bash

    # Navigate to project directory
    cd RedPitaya-FPGA/prj/v0.94
    
    # Run FSBL TCL script
    hsi -source ../../red_pitaya_hsi_fsbl.tcl -tclargs v0.94 Z10

The FSBL binary will be generated in ``fpga/hsi/fsbl.elf``.

Scenario 3: Modifying Device Tree
-----------------------------------

To customize the device tree for your FPGA design:

1. **Generate initial device tree:**

    .. code-block:: bash

        make PRJ=v0.94 MODEL=Z10

2. **Edit device tree sources:**

    .. code-block:: bash

        nano fpga/dts/system.dts

3. **Compile device tree:**

    .. code-block:: bash

        # Compile DTS to DTB (device tree blob)
        dtc -I dts -O dtb -o system.dtb fpga/dts/system.dts

4. **Deploy to Red Pitaya:**

    .. code-block:: bash

        scp system.dtb root@rp-xxxxxx.local:/boot/devicetree.dtb

Scenario 4: Creating Custom Bare-Metal Application
----------------------------------------------------

To create a bare-metal application that runs on the ARM processor:

1. **Launch SDK:**

    .. code-block:: bash

        xsdk &

2. **Import Hardware Platform:**

    - File → New → Application Project
    - Select hardware platform from Vivado export (``.hdf`` file)

3. **Write your application:**

    - Select "Empty Application" template
    - Add your C source files

4. **Build and run:**

    - Right-click project → Build Project
    - Use JTAG to download and run on Red Pitaya

|

Troubleshooting
================

SDK Won't Start
----------------

**Problem:** ``xsdk`` command not found

**Solution:**

.. code-block:: bash

    # Check if SDK is in PATH
    echo $PATH | grep SDK
    
    # If not, source settings script
    source /opt/Xilinx/SDK/2019.1/settings64.sh
    
    # Add to .bashrc for permanent fix
    echo "source /opt/Xilinx/SDK/2019.1/settings64.sh" >> ~/.bashrc

HSI Command Fails
------------------

**Problem:** ``hsi: command not found`` during FPGA build

**Solution:**

.. code-block:: bash

    # Verify HSI is installed
    ls /opt/Xilinx/SDK/2019.1/bin/hsi
    
    # If file exists but command not found, add to PATH
    export PATH=/opt/Xilinx/SDK/2019.1/bin:$PATH
    
    # Add to .bashrc
    echo 'export PATH=/opt/Xilinx/SDK/2019.1/bin:$PATH' >> ~/.bashrc

FSBL Generation Fails
----------------------

**Problem:** Error during ``make``: "FSBL generation failed"

**Possible causes and solutions:**

1. **Missing .hdf file:**

    .. code-block:: bash

        # Verify hardware handoff exists
        ls prj/v0.94/project/redpitaya.sdk/
        
        # If missing, export from Vivado:
        # File → Export → Export Hardware (include bitstream)

2. **SDK version mismatch:**

    .. code-block:: bash

        # Check SDK version
        xsdk -version
        
        # Should show: Xilinx SDK 2019.1

3. **Corrupted SDK installation:**

    .. code-block:: bash

        # Reinstall SDK or run repair from installer

Missing Libraries (Linux)
---------------------------

**Problem:** SDK won't launch, shows library errors

**Solution:**

.. code-block:: bash

    # Install 32-bit library support
    sudo dpkg --add-architecture i386
    sudo apt update
    
    # Install missing libraries
    sudo apt install -y \
        libxft2:i386 \
        libncurses5 \
        libtinfo5 \
        libstdc++6:i386

Permission Denied Errors
--------------------------

**Problem:** Cannot write FSBL or device tree files

**Solution:**

.. code-block:: bash

    # Fix directory permissions
    sudo chown -R $USER:$USER RedPitaya-FPGA
    chmod -R u+w RedPitaya-FPGA
    
    # Or run make with sudo (not recommended)
    sudo make PRJ=v0.94 MODEL=Z10

Device Tree Compilation Fails
-------------------------------

**Problem:** ``dtc: command not found``

**Solution:**

.. code-block:: bash

    # Install device tree compiler
    sudo apt install device-tree-compiler
    
    # Verify installation
    dtc --version

|

Additional Resources
=====================

**Official Documentation:**

- `Xilinx SDK User Guide (UG1027) <https://docs.xilinx.com/v/u/en-US/ug1027-sdk-user-guide>`_
- `Xilinx HSI User Guide (UG1138) <https://docs.xilinx.com/v/u/en-US/ug1138-vivado-sw-hw-interface>`_
- `Device Tree Xilinx Repository <https://github.com/Xilinx/device-tree-xlnx>`_

**Red Pitaya Resources:**

- :ref:`Vivado Installation Guide <FPGA_install_vivado>`
- :ref:`FPGA Project Creation <fpga_create_project>`
- :ref:`Device Tree Configuration <device_tree>` (coming soon)
- :rp-forum:`Red Pitaya Forum <>`

**Community Support:**

- `AMD Xilinx Forums <https://adaptivesupport.amd.com/>`_
- :rp-forum:`Red Pitaya Forum <>`
- :rp-github:`GitHub Issues <RedPitaya-FPGA/issues>`

|

Next Steps
===========

Now that SDK is installed, you can proceed to:

1. :ref:`Create Your First FPGA Project <fpga_create_project>`
2. :ref:`Build FPGA Projects <fpga_create_project>`
3. :ref:`Generate Device Tree <device_tree>`
4. :ref:`Program FPGA via JTAG <fpga_jtag_programming>`

For a complete FPGA development workflow, see :ref:`FPGA Development Guide <build-fpga>`.

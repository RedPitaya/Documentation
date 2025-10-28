.. _fpga_advanced_loading:

##################################
Advanced FPGA Loading
##################################

This guide covers advanced FPGA loading scenarios including custom bitstreams, device tree overlays, partial reconfiguration, practical workflows, and troubleshooting.

.. seealso::

    **Prerequisites:**
    
    Before diving into advanced topics, familiarize yourself with:
    
    - :ref:`fpga_reprogramming` - Basic FPGA loading
    - :ref:`fpga_boot_loading` - Making FPGA load at boot
    - :ref:`device_tree` - Device tree configuration
    - :ref:`signal_mapping` - Hardware signal connections

.. contents:: Table of Contents
    :local:
    :depth: 2
    :backlinks: top

|

**********************************
Custom FPGA Loading
**********************************

Beyond loading Red Pitaya's built-in FPGA projects, you can load completely custom FPGA images with your own bitstreams, device tree overlays, and hardware configurations.

Loading Custom Bitstream Only
==============================

When you have a custom bitstream but want to use Red Pitaya's standard device tree:

.. tabs::

    .. tab:: OS 1.04 or older

        .. code-block:: bash

            # Direct bitstream loading to configuration device
            redpitaya> cat /path/to/your/custom.bit > /dev/xdevcfg

    .. tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            # Load using fpgautil (requires .bin format)
            redpitaya> fpgautil -b /path/to/your/custom.bit.bin

    .. tab:: OS 2.07-43 or newer

        .. code-block:: bash

            # Load bitstream only (keeps current device tree)
            redpitaya> fpgautil -b /path/to/your/custom.bit.bin

.. note::

    **For OS 2.07+:**
    
    - Use ``fpgautil -b`` to load bitstream without changing device tree
    - Use ``overlay.sh`` to load both bitstream and device tree together
    - Loading bitstream only is useful when hardware connections remain unchanged

Loading Custom Bitstream with Device Tree
==========================================

When your custom FPGA has different hardware configuration than the standard v0.94 design:

**Prerequisites:**

- Custom bitstream file (``fpga.bit.bin``)
- Custom device tree overlay (``fpga.dtbo``)
- Understanding of your hardware modifications

**Option 1: Using overlay.sh (OS 2.07+)**

.. code-block:: bash

    # Step 1: Create project directory
    redpitaya> mkdir -p /opt/redpitaya/fpga/$(monitor -f)/my_custom_project
    
    # Step 2: Copy files with exact names
    redpitaya> cp /path/to/custom_bitstream.bit.bin \
                  /opt/redpitaya/fpga/$(monitor -f)/my_custom_project/fpga.bit.bin
    redpitaya> cp /path/to/custom_devicetree.dtbo \
                  /opt/redpitaya/fpga/$(monitor -f)/my_custom_project/fpga.dtbo
    
    # Step 3: Load both together
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 my_custom_project

.. important::

    The files **must** be named:
    
    - ``fpga.bit.bin`` - FPGA bitstream
    - ``fpga.dtbo`` - Device tree overlay
    
    The overlay.sh script requires these exact names.

**Option 2: Manual loading (OS 2.00 to 2.05-37)**

.. code-block:: bash

    # Step 1: Load bitstream
    redpitaya> fpgautil -b /path/to/custom_bitstream.bit.bin
    
    # Step 2: Load device tree overlay
    redpitaya> mkdir -p /sys/kernel/config/device-tree/overlays/my_custom
    redpitaya> cat /path/to/custom_devicetree.dtbo > \
                   /sys/kernel/config/device-tree/overlays/my_custom/dtbo

**Option 3: Direct loading (OS 1.04 or older)**

.. code-block:: bash

    # Load bitstream directly
    redpitaya> cat /path/to/custom_bitstream.bit > /dev/xdevcfg

.. note::

    OS 1.04 and older do not support runtime device tree overlay loading. Device tree modifications require recompiling the device tree or using a custom kernel.

Partial FPGA Reconfiguration
=============================

Partial reconfiguration allows updating portions of the FPGA without reloading the entire design.

.. note::

    Partial reconfiguration support depends on your FPGA design. The Red Pitaya default design does not support partial reconfiguration. 
    You must design your FPGA project specifically for partial reconfiguration using Vivado's PR flow.

**Capabilities:**

- Update logic in specific FPGA regions
- Maintain state in unchanged regions
- Faster configuration than full reload
- Dynamic hardware adaptation

**Limitations:**

- Requires Vivado PR-capable license
- Complex design constraints
- Not all designs can use PR
- Red Pitaya default designs don't support PR

For details on implementing partial reconfiguration, see the 
`Vivado Design Suite User Guide: Dynamic Function eXchange (UG909) <https://docs.amd.com/v/u/2020.1-English/ug909-vivado-partial-reconfiguration>`_.

|

**********************************
Practical Examples and Workflows
**********************************

This section demonstrates real-world workflows for FPGA loading in various scenarios.

Example 1: Quick FPGA Project Switching
========================================

Rapidly switch between multiple pre-built FPGA projects during development:

**Setup:**

.. code-block:: bash

    # Organize projects in directories
    redpitaya> mkdir -p /root/fpga_projects/{adc_dac,scope,signal_gen}
    
    # Copy project files
    redpitaya> cp adc_dac_design/* /root/fpga_projects/adc_dac/
    redpitaya> cp scope_design/* /root/fpga_projects/scope/
    redpitaya> cp signal_gen_design/* /root/fpga_projects/signal_gen/

**Switching Script:**

.. code-block:: bash

    #!/bin/bash
    # save as /root/switch_fpga.sh
    
    PROJECT=$1
    MODEL=$(/opt/redpitaya/bin/monitor -f)
    
    if [ -z "$PROJECT" ]; then
        echo "Usage: $0 <project_name>"
        echo "Available projects:"
        ls -1 /root/fpga_projects/
        exit 1
    fi
    
    PROJ_DIR="/root/fpga_projects/$PROJECT"
    
    if [ ! -d "$PROJ_DIR" ]; then
        echo "Project not found: $PROJECT"
        exit 1
    fi
    
    # Load the project (OS 2.07+)
    /opt/redpitaya/sbin/overlay.sh v0.94 "../../root/fpga_projects/$PROJECT"
    
    # Verify
    echo "Loaded FPGA project: $PROJECT"
    cat /tmp/loaded_fpga.inf

**Usage:**

.. code-block:: bash

    # Make executable
    redpitaya> chmod +x /root/switch_fpga.sh
    
    # Switch to scope project
    redpitaya> ./switch_fpga.sh scope
    
    # Switch to signal generator
    redpitaya> ./switch_fpga.sh signal_gen

Example 2: Development Iteration Workflow
==========================================

Streamline the development cycle when frequently updating and testing FPGA designs:

**Development Script:**

.. code-block:: bash

    #!/bin/bash
    # save as /root/upload_fpga.sh
    
    # Configuration
    DEV_HOST="developer-pc"
    DEV_USER="username"
    DEV_PATH="/home/username/vivado_projects/red_pitaya/output"
    RP_PATH="/root/test_fpga"
    
    # Create directory if needed
    mkdir -p $RP_PATH
    
    # Download latest bitstream from development PC
    echo "Downloading latest FPGA files from $DEV_HOST..."
    scp ${DEV_USER}@${DEV_HOST}:${DEV_PATH}/red_pitaya_top.bit.bin \
        $RP_PATH/fpga.bit.bin
    
    scp ${DEV_USER}@${DEV_HOST}:${DEV_PATH}/devicetree.dtbo \
        $RP_PATH/fpga.dtbo
    
    # Load the new FPGA
    echo "Loading FPGA..."
    /opt/redpitaya/sbin/overlay.sh v0.94 "../../root/test_fpga"
    
    # Verify
    echo "FPGA loaded successfully:"
    cat /tmp/loaded_fpga.inf
    
    # Optional: Run automatic tests
    if [ -f "/root/test_fpga.sh" ]; then
        echo "Running automated tests..."
        /root/test_fpga.sh
    fi

**Usage:**

.. code-block:: bash

    # Make executable
    redpitaya> chmod +x /root/upload_fpga.sh
    
    # Run after each Vivado build
    redpitaya> ./upload_fpga.sh

**Development Flow:**

1. Modify FPGA design in Vivado
2. Build bitstream
3. Run ``upload_fpga.sh`` on Red Pitaya
4. Test functionality
5. Repeat

Example 3: Testing Custom FPGA Design
======================================

Systematically test a custom FPGA design with automated verification:

**Test Script:**

.. code-block:: bash

    #!/bin/bash
    # save as /root/test_custom_fpga.sh
    
    echo "======================================"
    echo "Custom FPGA Testing Script"
    echo "======================================"
    
    # Load custom FPGA
    echo "Loading custom FPGA..."
    /opt/redpitaya/sbin/overlay.sh v0.94 my_custom_project
    
    if [ $? -ne 0 ]; then
        echo "ERROR: FPGA loading failed"
        exit 1
    fi
    
    sleep 2
    
    # Verify device tree loaded
    echo "Checking device tree..."
    if [ ! -d "/sys/kernel/config/device-tree/overlays/my_custom_project" ]; then
        echo "ERROR: Device tree overlay not found"
        exit 1
    fi
    
    # Test memory-mapped registers
    echo "Testing register access..."
    /opt/redpitaya/bin/monitor 0x40000000
    
    if [ $? -ne 0 ]; then
        echo "ERROR: Cannot access FPGA registers"
        exit 1
    fi
    
    # Test specific functionality
    echo "Running functional tests..."
    
    # Example: Test LED control
    /opt/redpitaya/bin/monitor 0x40000030 0xFF  # Turn on LEDs
    sleep 1
    /opt/redpitaya/bin/monitor 0x40000030 0x00  # Turn off LEDs
    
    # Example: Test ADC/DAC loopback
    # (add your specific tests here)
    
    echo "======================================"
    echo "All tests passed!"
    echo "======================================"

Example 4: Managing Multiple Configurations
============================================

Maintain multiple FPGA configurations with easy selection:

**Configuration Manager:**

.. code-block:: bash

    #!/bin/bash
    # save as /root/fpga_manager.sh
    
    CONFIG_DIR="/opt/redpitaya/fpga/$(monitor -f)"
    
    case "$1" in
        list)
            echo "Available FPGA configurations:"
            ls -1 $CONFIG_DIR | grep -v "v0.94"
            ;;
        
        load)
            if [ -z "$2" ]; then
                echo "Usage: $0 load <config_name>"
                exit 1
            fi
            echo "Loading configuration: $2"
            /opt/redpitaya/sbin/overlay.sh v0.94 "$2"
            ;;
        
        info)
            echo "Currently loaded FPGA:"
            cat /tmp/loaded_fpga.inf
            echo ""
            echo "Available configurations:"
            ls -1 $CONFIG_DIR | grep -v "v0.94"
            ;;
        
        backup)
            if [ -z "$2" ]; then
                echo "Usage: $0 backup <config_name>"
                exit 1
            fi
            BACKUP_DIR="/root/fpga_backups/$(date +%Y%m%d_%H%M%S)_$2"
            mkdir -p "$BACKUP_DIR"
            cp -r "$CONFIG_DIR/$2"/* "$BACKUP_DIR/"
            echo "Backup created: $BACKUP_DIR"
            ;;
        
        *)
            echo "FPGA Configuration Manager"
            echo "Usage: $0 {list|load|info|backup} [config_name]"
            echo ""
            echo "Commands:"
            echo "  list           - List available configurations"
            echo "  load <name>    - Load a configuration"
            echo "  info           - Show current configuration and available options"
            echo "  backup <name>  - Backup a configuration"
            ;;
    esac

**Usage:**

.. code-block:: bash

    redpitaya> ./fpga_manager.sh list
    redpitaya> ./fpga_manager.sh load my_project
    redpitaya> ./fpga_manager.sh info
    redpitaya> ./fpga_manager.sh backup my_project

Example 5: Custom Device Tree Workflow
=======================================

Develop and test custom device tree overlays:

**Step 1: Create device tree source (.dts)**

.. code-block:: bash

    redpitaya> nano my_custom_overlay.dts

Example device tree source:

.. code-block:: dts

    /dts-v1/;
    /plugin/;
    
    / {
        fragment@0 {
            target = <&fpga_full>;
            __overlay__ {
                firmware-name = "my_custom_project/fpga.bit.bin";
            };
        };
        
        fragment@1 {
            target = <&amba>;
            __overlay__ {
                my_custom_device@40000000 {
                    compatible = "my-company,my-device";
                    reg = <0x40000000 0x10000>;
                    interrupt-parent = <&intc>;
                    interrupts = <0 29 4>;
                };
            };
        };
    };

**Step 2: Compile device tree overlay**

.. code-block:: bash

    # Install device tree compiler if needed
    redpitaya> apt-get update
    redpitaya> apt-get install device-tree-compiler
    
    # Compile .dts to .dtbo
    redpitaya> dtc -@ -I dts -O dtb -o my_custom_overlay.dtbo my_custom_overlay.dts

**Step 3: Test the overlay**

.. code-block:: bash

    # Copy to project directory
    redpitaya> cp my_custom_overlay.dtbo \
                  /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.dtbo
    
    # Load with overlay.sh
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 my_project
    
    # Verify device tree changes
    redpitaya> ls /sys/kernel/config/device-tree/overlays/

**Step 4: Verify hardware registration**

.. code-block:: bash

    # Check if device registered
    redpitaya> ls /sys/bus/platform/devices/
    
    # Check kernel messages
    redpitaya> dmesg | tail -20

Example 6: Automated CI/CD Integration
=======================================

Integrate FPGA testing into continuous integration/deployment pipelines:

**CI Test Script (for Jenkins, GitLab CI, etc.):**

.. code-block:: bash

    #!/bin/bash
    # ci_test_fpga.sh - Run on Red Pitaya hardware test station
    
    set -e  # Exit on any error
    
    # Configuration
    BITSTREAM_URL="$1"
    DEVICETREE_URL="$2"
    TEST_DIR="/root/ci_test_$$"
    
    echo "CI/CD FPGA Test Pipeline"
    echo "========================"
    
    # Cleanup function
    cleanup() {
        rm -rf "$TEST_DIR"
    }
    trap cleanup EXIT
    
    # Download artifacts
    echo "Downloading build artifacts..."
    mkdir -p "$TEST_DIR"
    wget -q "$BITSTREAM_URL" -O "$TEST_DIR/fpga.bit.bin"
    wget -q "$DEVICETREE_URL" -O "$TEST_DIR/fpga.dtbo"
    
    # Load FPGA
    echo "Loading FPGA..."
    /opt/redpitaya/sbin/overlay.sh v0.94 "../../root/ci_test_$$"
    
    # Verify loading
    if ! grep -q "ci_test_$$" /tmp/loaded_fpga.inf; then
        echo "FAIL: FPGA did not load correctly"
        exit 1
    fi
    
    # Run hardware tests
    echo "Running hardware tests..."
    python3 /root/hardware_tests.py
    
    # Check test results
    if [ $? -eq 0 ]; then
        echo "PASS: All tests successful"
        exit 0
    else
        echo "FAIL: Tests failed"
        exit 1
    fi

**GitLab CI configuration (.gitlab-ci.yml):**

.. code-block:: yaml

    stages:
      - build
      - test
    
    build_fpga:
      stage: build
      script:
        - vivado -mode batch -source build_script.tcl
      artifacts:
        paths:
          - output/red_pitaya_top.bit.bin
          - output/devicetree.dtbo
    
    test_hardware:
      stage: test
      script:
        - ssh root@redpitaya "bash ci_test_fpga.sh 
          http://ci-server/artifacts/fpga.bit.bin
          http://ci-server/artifacts/fpga.dtbo"
      dependencies:
        - build_fpga

Example 7: Multi-Region Partial Reconfiguration
================================================

Advanced workflow for designs with multiple reconfigurable regions:

.. note::

    This example requires an FPGA design specifically created with Vivado's Partial Reconfiguration flow. The standard Red Pitaya design does not support this.

**Partial Reconfiguration Manager:**

.. code-block:: bash

    #!/bin/bash
    # pr_manager.sh - Manage partial reconfiguration
    
    BASE_DIR="/root/pr_designs"
    STATIC_BIT="$BASE_DIR/static.bit.bin"
    
    load_static() {
        echo "Loading static design..."
        fpgautil -b "$STATIC_BIT"
        sleep 1
    }
    
    load_partial() {
        REGION=$1
        MODULE=$2
        PARTIAL_BIT="$BASE_DIR/partials/${REGION}_${MODULE}.bit.bin"
        
        if [ ! -f "$PARTIAL_BIT" ]; then
            echo "ERROR: Partial bitstream not found: $PARTIAL_BIT"
            return 1
        fi
        
        echo "Loading $MODULE into region $REGION..."
        fpgautil -b "$PARTIAL_BIT" -f Partial
        echo "Partial reconfiguration complete"
    }
    
    case "$1" in
        init)
            load_static
            ;;
        load)
            load_partial "$2" "$3"
            ;;
        *)
            echo "Usage: $0 {init|load <region> <module>}"
            echo ""
            echo "Examples:"
            echo "  $0 init              # Load static design"
            echo "  $0 load region0 fir  # Load FIR filter into region 0"
            echo "  $0 load region1 dds  # Load DDS into region 1"
            ;;
    esac

**Usage:**

.. code-block:: bash

    # Load static design first
    redpitaya> ./pr_manager.sh init
    
    # Dynamically load modules
    redpitaya> ./pr_manager.sh load region0 fir_filter
    redpitaya> ./pr_manager.sh load region0 iir_filter  # Replace FIR with IIR
    redpitaya> ./pr_manager.sh load region1 signal_gen

|

**********************************
Advanced Topics
**********************************

Using overlay.sh Script
========================

The ``overlay.sh`` script (OS 2.07+) is Red Pitaya's primary tool for loading FPGA projects with device tree overlays.

**Command Syntax:**

.. code-block:: bash

    /opt/redpitaya/sbin/overlay.sh <old_project> <new_project>

**Parameters:**

- ``old_project`` - Project currently loaded (typically ``v0.94``)
- ``new_project`` - Project to load (directory name in ``/opt/redpitaya/fpga/<model>/``)

**What overlay.sh Does:**

1. Unloads current device tree overlay
2. Removes current FPGA configuration
3. Loads new FPGA bitstream (``fpga.bit.bin``)
4. Loads new device tree overlay (``fpga.dtbo``)
5. Records loaded project in ``/tmp/loaded_fpga.inf``

**Common Usage Patterns:**

.. code-block:: bash

    # Load built-in project
    overlay.sh v0.94 v0.94
    
    # Load custom project
    overlay.sh v0.94 my_custom_project
    
    # Switch between projects
    overlay.sh my_project_a my_project_b
    
    # Reload current project
    CURRENT=$(cat /tmp/loaded_fpga.inf)
    overlay.sh $CURRENT $CURRENT

**Project Directory Structure:**

.. code-block:: text

    /opt/redpitaya/fpga/<model>/<project>/
    ├── fpga.bit.bin    # Required: FPGA bitstream
    └── fpga.dtbo       # Required: Device tree overlay

**Troubleshooting overlay.sh:**

.. code-block:: bash

    # Check script location
    ls -l /opt/redpitaya/sbin/overlay.sh
    
    # Run with verbose output
    bash -x /opt/redpitaya/sbin/overlay.sh v0.94 my_project
    
    # Check kernel messages
    dmesg | tail -20

File Locations and Directory Structure
=======================================

Understanding Red Pitaya's FPGA file organization:

**Standard FPGA Directory:**

.. code-block:: text

    /opt/redpitaya/fpga/
    ├── stemlab-125-14/          # STEMlab 125-14 (Z7020)
    │   └── v0.94/               # Default project
    │       ├── fpga.bit.bin
    │       └── fpga.dtbo
    ├── stemlab-125-14-z7020/    # Alternative naming
    ├── stemlab-122-16/          # STEMlab 122-16 (Z7020)
    ├── sdrlab-122-16/           # SDRlab 122-16 (Z7020)
    └── custom_projects/         # Your projects here

**Model Detection:**

.. code-block:: bash

    # Get current model automatically
    MODEL=$(/opt/redpitaya/bin/monitor -f)
    echo $MODEL  # Example: stemlab-125-14

**Important Files:**

.. code-block:: text

    /tmp/loaded_fpga.inf         # Currently loaded project name
    /dev/xdevcfg                 # FPGA configuration device (OS 1.04)
    /sys/class/fpga_manager/     # FPGA manager interface (OS 2.00+)
    /sys/kernel/config/device-tree/overlays/  # Device tree overlays

**Configuration Files:**

.. code-block:: text

    /boot/config.txt             # Boot configuration
    /boot/devicetree.dtb         # Base device tree
    /etc/profile.d/              # Login scripts
    /etc/systemd/system/         # systemd services

Internal FPGA Loading Operation
================================

Understanding how FPGA loading works internally:

**OS 1.04 and Older - Direct Loading:**

.. code-block:: bash

    # Direct write to configuration device
    cat bitstream.bit > /dev/xdevcfg

**Process:**

1. Kernel driver (xdevcfg) receives bitstream data
2. FPGA configuration engine processes bitstream
3. FPGA hardware reconfigures
4. Configuration complete when write finishes

**OS 2.00 to 2.05-37 - FPGA Manager:**

.. code-block:: bash

    # Load via FPGA manager framework
    fpgautil -b bitstream.bit.bin

**Process:**

1. fpgautil tool talks to FPGA manager kernel framework
2. FPGA manager validates bitstream
3. FPGA manager loads bitstream via appropriate driver
4. Configuration status available through sysfs

**OS 2.07+ - FPGA Manager + Device Tree Overlay:**

.. code-block:: bash

    # Load both bitstream and device tree
    overlay.sh v0.94 project_name

**Process:**

1. overlay.sh removes old device tree overlay
2. FPGA configuration cleared
3. New bitstream loaded via fpgautil
4. New device tree overlay applied
5. Kernel drivers probe new hardware
6. Project name recorded in /tmp/loaded_fpga.inf

**Device Tree Overlay Loading:**

.. code-block:: bash

    # Manual overlay loading
    mkdir /sys/kernel/config/device-tree/overlays/my_overlay
    cat my_overlay.dtbo > /sys/kernel/config/device-tree/overlays/my_overlay/dtbo

**Process:**

1. Create overlay directory in configfs
2. Write overlay binary to dtbo file
3. Kernel applies overlay to running device tree
4. New devices appear in /sys/bus/platform/devices/
5. Matching drivers probe and initialize

**Verification:**

.. code-block:: bash

    # Check FPGA manager status
    cat /sys/class/fpga_manager/fpga0/state
    
    # Check loaded overlays
    ls /sys/kernel/config/device-tree/overlays/
    
    # Check registered devices
    ls /sys/bus/platform/devices/

Best Practices
==============

**Development:**

- Keep FPGA source projects version controlled
- Document hardware modifications in device tree
- Test each change incrementally
- Maintain backup of working configurations
- Use meaningful project names
- Keep bitstream and device tree together

**File Management:**

- Store custom projects in ``/opt/redpitaya/fpga/<model>/``
- Use consistent naming: ``fpga.bit.bin`` and ``fpga.dtbo``
- Backup original v0.94 project before modifications
- Keep development projects separate from production
- Document project dependencies and requirements

**Safety:**

- Always backup before replacing system files
- Test new FPGA designs thoroughly before production
- Verify device tree matches hardware configuration
- Check for resource conflicts (memory addresses, interrupts)
- Validate bitstream compatibility with hardware model
- Use read-only filesystem (``ro``) when not making changes

**Production Deployment:**

- Use startup.sh for boot loading (most reliable)
- Test boot loading thoroughly before deployment
- Document custom FPGA functionality
- Provide rollback procedure
- Monitor FPGA loading in system logs
- Keep factory FPGA backup available

**Performance:**

- Use overlay.sh for fastest loading (OS 2.07+)
- Minimize device tree overlay complexity
- Cache frequently used bitstreams locally
- Avoid unnecessary FPGA reloads
- Profile loading times in production systems

|

**********************************
Frequently Asked Questions
**********************************

General Questions
=================

**Q: Which FPGA loading method should I use?**

A: It depends on your OS version:

- **OS 1.04 or older**: Use ``cat bitstream.bit > /dev/xdevcfg``
- **OS 2.00 to 2.05-37**: Use ``fpgautil -b bitstream.bit.bin``
- **OS 2.07+**: Use ``overlay.sh v0.94 project_name`` (recommended)

For most users on recent OS versions, ``overlay.sh`` is the simplest and most complete method.

**Q: What's the difference between .bit and .bit.bin files?**

A: Both contain FPGA configuration data, but in different formats:

- ``.bit`` - Vivado's default output format (includes header)
- ``.bit.bin`` - Binary format without header (required for OS 2.00+)

Convert with Vivado's ``write_cfgmem`` command or use ``dd`` to skip the header:

.. code-block:: bash

    dd if=input.bit of=output.bit.bin bs=1 skip=120

**Q: Can I load FPGA from Windows or Linux desktop?**

A: Yes, use SCP to copy files to Red Pitaya, then SSH to load:

.. code-block:: bash

    # Copy files (from desktop)
    scp my_fpga.bit.bin root@redpitaya-ip:/root/
    
    # Load FPGA (SSH session)
    ssh root@redpitaya-ip
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 my_project

Or use a single command:

.. code-block:: bash

    ssh root@redpitaya-ip "fpgautil -b /root/my_fpga.bit.bin"

**Q: How long does FPGA loading take?**

A: Typical loading times:

- Bitstream loading: 1-2 seconds
- Device tree overlay: < 1 second
- Total with overlay.sh: 2-3 seconds

Large bitstreams (multi-region PR) may take longer. Network transfer time is usually the bottleneck when loading remotely.

**Q: Can I use my own Vivado projects with Red Pitaya?**

A: Yes, but you must:

1. Use correct FPGA part number (XC7Z010 or XC7Z020)
2. Connect required signals to correct FPGA pins
3. Create compatible device tree overlay
4. Test thoroughly on target hardware

See the Red Pitaya FPGA Developer Guide for pinout and constraints.

**Q: Do I need to reboot after loading FPGA?**

A: No, FPGA loading takes effect immediately. Reboot is only needed when:

- Setting up boot loading (to test it works)
- Modifying system files
- Installing new kernel modules

**Q: How can I verify which FPGA is currently loaded?**

A: Check the loaded project:

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf

This shows the project name (e.g., "v0.94" or "my_custom_project").

Troubleshooting Questions
==========================

**Q: FPGA loading fails with "No such file or directory"**

A: Check these common issues:

.. code-block:: bash

    # Verify file exists
    ls -l /path/to/your/fpga.bit.bin
    
    # Check file permissions
    chmod 644 /path/to/your/fpga.bit.bin
    
    # Verify full path is correct
    realpath /path/to/your/fpga.bit.bin
    
    # For overlay.sh, check project directory structure
    ls -l /opt/redpitaya/fpga/$(monitor -f)/my_project/

**Q: FPGA loads but device doesn't work correctly**

A: Debug systematically:

.. code-block:: bash

    # 1. Verify FPGA actually loaded
    cat /tmp/loaded_fpga.inf
    
    # 2. Check for kernel errors
    dmesg | grep -i fpga
    
    # 3. Verify device tree loaded
    ls /sys/kernel/config/device-tree/overlays/
    
    # 4. Check if devices registered
    ls /sys/bus/platform/devices/
    
    # 5. Test memory-mapped register access
    /opt/redpitaya/bin/monitor 0x40000000

Common issues:

- Device tree doesn't match FPGA design
- Memory address conflicts
- Incorrect pin assignments
- Missing kernel drivers

**Q: "Device or resource busy" error when loading**

A: Something is using the current FPGA. Try:

.. code-block:: bash

    # Stop Red Pitaya services
    systemctl stop redpitaya_nginx
    
    # Check for running applications
    ps aux | grep monitor
    
    # Kill processes using FPGA
    killall monitor
    
    # Try loading again
    /opt/redpitaya/sbin/overlay.sh v0.94 my_project

Device Tree Questions
=====================

**Q: Do I need a device tree overlay for my custom FPGA?**

A: It depends:

- **No device tree needed** if:
  - Your FPGA uses same hardware configuration as v0.94
  - Only logic changes, no new hardware interfaces
  - Memory addresses and interrupts unchanged

- **Device tree needed** if:
  - Adding new hardware peripherals
  - Changing memory addresses
  - Adding interrupt handlers
  - Modifying pin assignments
  - Adding kernel drivers

**Q: How do I create a device tree overlay?**

A: See the comprehensive guide at :ref:`device_tree`. Basic steps:

1. Write device tree source (.dts)
2. Compile to overlay binary (.dtbo)
3. Place in project directory as ``fpga.dtbo``
4. Load with overlay.sh

**Q: Can I modify device tree without reloading FPGA?**

A: Yes, on OS 2.07+:

.. code-block:: bash

    # Load new overlay only
    mkdir /sys/kernel/config/device-tree/overlays/my_overlay
    cat new_overlay.dtbo > /sys/kernel/config/device-tree/overlays/my_overlay/dtbo

But typically it's easier to reload both together with overlay.sh.

**Q: Where can I find device tree examples?**

A: Look at Red Pitaya's built-in overlays:

.. code-block:: bash

    # View compiled overlays
    ls -l /opt/redpitaya/fpga/*/v0.94/fpga.dtbo
    
    # Decompile to source for reference
    dtc -I dtb -O dts -o example.dts fpga.dtbo

Persistence Questions
=====================

**Q: My custom FPGA doesn't load at boot. Why?**

A: Check your boot loading configuration:

.. code-block:: bash

    # Verify startup.sh has your command
    grep -i fpga /opt/redpitaya/sbin/startup.sh
    
    # Check for syntax errors
    bash -n /opt/redpitaya/sbin/startup.sh
    
    # View boot logs
    journalctl -b | grep -i fpga
    
    # Test command manually
    /opt/redpitaya/sbin/overlay.sh v0.94 my_project

See :ref:`fpga_boot_loading` for detailed boot loading setup.

**Q: Can I make different FPGAs load at each boot?**

A: Yes, use conditional logic in startup.sh:

.. code-block:: bash

    #!/bin/bash
    # In /opt/redpitaya/sbin/startup.sh
    
    # Load different FPGA based on external condition
    if [ -f "/root/use_project_a" ]; then
        /opt/redpitaya/sbin/overlay.sh v0.94 project_a
    else
        /opt/redpitaya/sbin/overlay.sh v0.94 project_b
    fi

Or use environment variables, configuration files, or network checks.

**Q: How do I revert to factory FPGA after setting up boot loading?**

A: See :ref:`fpga_reprogramming` for reverting to factory FPGA. Quick method:

.. code-block:: bash

    # Edit startup.sh
    rw
    nano /opt/redpitaya/sbin/startup.sh
    # Comment out or remove your FPGA loading line
    ro
    reboot

Advanced Questions
==================

**Q: Can I use partial reconfiguration with Red Pitaya?**

A: Technically yes, but:

- Red Pitaya default designs don't support it
- You must create a PR-capable design in Vivado
- Requires Vivado paid license (not available in WebPACK)
- Complex design constraints and flow
- Limited use cases for Red Pitaya

Most users should use full reconfiguration instead.

**Q: How can I load FPGA from a custom bootloader?**

A: Advanced topic. You would need to:

1. Modify U-Boot or create custom first-stage bootloader
2. Access FPGA configuration device from bootloader
3. Load bitstream before Linux kernel starts
4. Handle device tree initialization

This is beyond typical Red Pitaya usage. Contact Red Pitaya support for custom bootloader requirements.

**Q: Can I protect my FPGA bitstream from extraction?**

A: Several approaches:

- **Xilinx Bitstream Encryption**: Encrypt bitstream in Vivado (requires eFUSE key programming)
- **Obfuscation**: Make reverse engineering difficult (limited protection)
- **Readback Protection**: Disable readback in Vivado (prevents reading FPGA configuration)
- **Legal Protection**: Licensing, NDAs, patents

Note: Red Pitaya's FPGA is SRAM-based (configuration lost on power-off), making physical extraction difficult.

|

**********************************
Related Documentation
**********************************

**FPGA Documentation:**

- :ref:`fpga_reprogramming` - Basic FPGA loading guide
- :ref:`fpga_boot_loading` - Making FPGA load at boot
- :ref:`device_tree` - Device tree configuration
- :ref:`signal_mapping` - Hardware signal connections

**Developer Guides:**

- :ref:`Red Pitaya FPGA Developer Guide <fpga>` - FPGA development overview
- :ref:`C and Python API <runApp_api>` - Software interface
- Vivado Design Guide - Xilinx FPGA development

**Application Examples:**

- Red Pitaya GitHub repository - Example designs
- Red Pitaya forums - Community projects
- Red Pitaya application notes

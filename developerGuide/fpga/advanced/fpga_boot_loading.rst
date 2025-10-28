.. _fpga_boot_loading:

##################################
FPGA Boot Loading Configuration
##################################

This guide covers methods to make your custom FPGA load automatically at Red Pitaya boot. By default, FPGA configuration persists only until the device is powered off, reset, or a new FPGA image is loaded.

.. seealso::

    **Prerequisites:**
    
    Before setting up boot loading, you need a working FPGA bitstream. See:
    
    - :ref:`fpga_reprogramming` - Basic FPGA loading guide
    - :ref:`fpga_advanced_loading` - Custom FPGA configurations

.. contents:: Table of Contents
    :local:
    :depth: 2
    :backlinks: top

|

**********************************
Understanding Persistence
**********************************

FPGA Configuration Lifecycle
=============================

By default, FPGA configuration persists until one of these events occurs:

1. Device is powered off or reset
2. A new FPGA image is loaded (web applications, interface reload)
3. FPGA configuration is changed through software

This section covers methods to make your custom FPGA load automatically at boot.

When to Use Boot Loading
==========================

Set up automatic boot loading when you:

- Deploy a production system with custom FPGA
- Want the same FPGA to load after every power cycle
- Need consistent hardware configuration at startup
- Run headless systems without manual intervention
- Develop appliances with fixed FPGA functionality

|


Method 1: Using startup.sh Script (Recommended)
=================================================

The **startup.sh script** is Red Pitaya's recommended method for running commands at boot. The script runs exactly once after the system starts, making it ideal for FPGA loading and other initialization tasks.

.. seealso::

    For more details on the startup.sh script and running applications at boot, see the :ref:`C and Python API Documentation <runApp_api>`.

Why startup.sh?
-----------------

**Advantages:**

- Red Pitaya's official recommended method
- Simple to configure and maintain
- Runs exactly once at system boot
- Consistent with other Red Pitaya documentation
- Easy to enable/disable
- No complex service configuration needed

**Use this method for:**

- Most FPGA boot loading scenarios
- Production deployments
- Quick prototyping and testing
- When you want Red Pitaya standard practices

Basic Procedure
----------------

**Step 1: Enable read-write mode**

.. code-block:: bash

    redpitaya> rw

**Step 2: Copy your FPGA files (if needed)**

If your FPGA bitstream and device tree files are not already in ``/opt/redpitaya``, copy them:

.. code-block:: bash

    # Example: Copy from /root to /opt/redpitaya/fpga/<model>/my_project/
    redpitaya> mkdir -p /opt/redpitaya/fpga/$(monitor -f)/my_project
    redpitaya> cp /root/red_pitaya_top.bit.bin /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.bit.bin
    redpitaya> cp /root/devicetree.dtbo /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.dtbo

**Step 3: Edit the startup.sh script**

.. code-block:: bash

    redpitaya> nano /opt/redpitaya/sbin/startup.sh

**Step 4: Add your FPGA loading command at the end of the file**

The exact command depends on your OS version. Add **before** the final comment line:

.. tabs::

    .. tab:: OS 1.04 or older

        .. code-block:: bash

            #!/bin/bash
            
            # ... existing startup.sh content ...
            
            # Load custom FPGA at boot
            cat /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.bit > /dev/xdevcfg
            
            # Here you can specify commands for autorun at system startup

    .. tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            #!/bin/bash
            
            # ... existing startup.sh content ...
            
            # Load custom FPGA at boot
            fpgautil -b /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.bit.bin
            
            # Here you can specify commands for autorun at system startup

    .. tab:: OS 2.07-43 or newer

        .. code-block:: bash

            #!/bin/bash
            
            # ... existing startup.sh content ...
            
            # Load custom FPGA with device tree overlay
            /opt/redpitaya/sbin/overlay.sh v0.94 my_project
            
            # Here you can specify commands for autorun at system startup

.. note::

    For OS 2.07+, the ``overlay.sh`` command will automatically load both the FPGA bitstream (``fpga.bit.bin``) and device tree overlay (``fpga.dtbo``) from the specified project directory.

**Step 5: Save the file and return to read-only mode**

.. code-block:: bash

    # Press Ctrl+X, then Y, then Enter to save in nano
    redpitaya> ro

**Step 6: Reboot to test**

.. code-block:: bash

    redpitaya> reboot

**Step 7: Verify FPGA loaded correctly**

After reboot, check the loaded FPGA:

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf

To Disable or Modify
----------------------

To stop loading the custom FPGA at boot:

**Step 1: Enable read-write mode**

.. code-block:: bash

    redpitaya> rw

**Step 2: Edit the startup.sh script**

.. code-block:: bash

    redpitaya> nano /opt/redpitaya/sbin/startup.sh

**Step 3: Comment out or remove your FPGA loading line**

.. code-block:: bash

    #!/bin/bash
    
    # ... existing startup.sh content ...
    
    # Load custom FPGA at boot (disabled)
    # /opt/redpitaya/sbin/overlay.sh v0.94 my_project
    
    # Here you can specify commands for autorun at system startup

**Step 4: Save and reboot**

.. code-block:: bash

    redpitaya> ro
    redpitaya> reboot

|


Method 2: Using systemd Service (Alternative)
===============================================

For advanced users who prefer systemd services, you can create a custom service that runs at boot. This method provides more control over service dependencies and startup order.

.. note::

    The **startup.sh method** (Method 1) is simpler and recommended for most users. Use systemd services only if you need advanced features like service dependencies, restart policies, or logging.

When to Use systemd
--------------------

Use systemd services when you need:

- Fine-grained control over startup order
- Service dependencies (start after network, etc.)
- Automatic restart on failure
- Advanced logging and monitoring
- Integration with other systemd services
- Service-level resource limits

Create systemd Service
-----------------------

**Step 1: Create service file**

.. code-block:: bash

    redpitaya> rw
    redpitaya> nano /etc/systemd/system/custom-fpga.service

**Step 2: Add service configuration**

.. tabs::

    .. tab:: OS 1.04 or older

        .. code-block:: ini

            [Unit]
            Description=Load Custom FPGA at Boot
            After=network.target
            
            [Service]
            Type=oneshot
            ExecStart=/bin/bash -c 'cat /root/red_pitaya_top.bit > /dev/xdevcfg'
            RemainAfterExit=yes
            
            [Install]
            WantedBy=multi-user.target

    .. tab:: OS 2.00 to 2.05-37

        .. code-block:: ini

            [Unit]
            Description=Load Custom FPGA at Boot
            After=network.target
            
            [Service]
            Type=oneshot
            ExecStart=/usr/bin/fpgautil -b /root/red_pitaya_top.bit.bin
            RemainAfterExit=yes
            
            [Install]
            WantedBy=multi-user.target

    .. tab:: OS 2.07-43 or newer

        .. code-block:: ini

            [Unit]
            Description=Load Custom FPGA at Boot
            After=network.target
            
            [Service]
            Type=oneshot
            ExecStart=/opt/redpitaya/sbin/overlay.sh v0.94 my_project
            RemainAfterExit=yes
            
            [Install]
            WantedBy=multi-user.target

**Step 3: Enable and start the service**

.. code-block:: bash

    redpitaya> systemctl daemon-reload
    redpitaya> systemctl enable custom-fpga.service
    redpitaya> systemctl start custom-fpga.service
    redpitaya> ro

**Step 4: Verify service status**

.. code-block:: bash

    redpitaya> systemctl status custom-fpga.service

To Disable
-----------

.. code-block:: bash

    redpitaya> rw
    redpitaya> systemctl disable custom-fpga.service
    redpitaya> systemctl stop custom-fpga.service
    redpitaya> ro

|


Method 3: Using /etc/profile.d (Login Method)
==============================================

This method loads the FPGA when users log in via SSH. **Not recommended** for boot loading because:

- Only runs when someone logs in (not at system boot)
- Runs at every SSH login (can cause delays)
- Can interfere with automated scripts

Use this method **only** if you specifically want FPGA loading triggered by user login rather than system boot.

.. note::

    Since Red Pitaya automatically logs in the ``root`` user on boot, this method effectively runs at boot time for default setups. However, it still executes on every login.

Setup Procedure
-----------------

**Step 1: Create startup script**

.. code-block:: bash

    redpitaya> rw
    redpitaya> nano /etc/profile.d/custom_fpga.sh

**Step 2: Add load command**

.. tabs::

    .. tab:: OS 1.04 or older

        .. code-block:: bash

            #!/bin/bash
            cat /root/red_pitaya_top.bit > /dev/xdevcfg

    .. tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            #!/bin/bash
            fpgautil -b /root/red_pitaya_top.bit.bin

    .. tab:: OS 2.07-43 or newer

        .. code-block:: bash

            #!/bin/bash
            /opt/redpitaya/sbin/overlay.sh v0.94 my_project

**Step 3: Make executable**

.. code-block:: bash

    redpitaya> chmod +x /etc/profile.d/custom_fpga.sh
    redpitaya> ro

.. warning::

    This method runs at **every login**, not just at boot. This can cause:
    
    - FPGA reloading during active sessions
    - Login delays
    - Repeated initialization
    
    Use **Method 1 (startup.sh)** instead for boot loading.

|


Method 4: Replace Default FPGA Image (Advanced)
================================================

This method overwrites the default Red Pitaya FPGA image with your custom one, making it the system default.

.. warning::

    - This modifies system files. Keep backups!
    - Only works for OS 2.00 or newer
    - Applications expecting v0.94 behavior will use your custom FPGA
    - Use Method 1 unless you specifically need system-wide replacement

When to Use This Method
-------------------------

Replace the default FPGA when:

- You want all Red Pitaya applications to use your custom FPGA
- The standard v0.94 project is never needed
- You need system-wide FPGA replacement
- Your custom FPGA maintains v0.94 register compatibility

.. important::

    After using this method, commands like ``overlay.sh v0.94`` will load your custom FPGA instead of the factory default.

Replacement Script
-------------------

This script safely replaces the default FPGA with automatic backup:

**Step 1: Create the script**

.. code-block:: bash

    redpitaya> nano /root/replace_fpga.sh

**Step 2: Add script content**

.. code-block:: bash

    #!/bin/bash

    BITSTREAM=$1
    MODEL=$(/opt/redpitaya/bin/monitor -f)
    PROJ=v0.94

    # Enable read-write privileges
    mount -o rw,remount /opt/redpitaya

    # Check if backup already exists
    if [ ! -f "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin" ]; then
        # Create backup of original fpga.bit.bin
        cp "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin" \
           "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin"
    fi

    if [ $# -eq 0 ]; then
        # Restore original file
        cp -f "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin" \
              "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin"
        conf="Restored original fpga.bit.bin"
    else
        # Replace with custom image
        cp -f "$(realpath $1)" \
              "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin"
        conf="fpga.bit.bin overwritten with $BITSTREAM"
    fi

    mount -o ro,remount /opt/redpitaya
    echo "$conf"

**Step 3: Make executable**

.. code-block:: bash

    redpitaya> chmod +x /root/replace_fpga.sh

**Step 4: Replace default FPGA**

.. code-block:: bash

    redpitaya> ./replace_fpga.sh /root/red_pitaya_top.bit.bin

**Step 5: Reboot to activate**

.. code-block:: bash

    redpitaya> reboot

To Restore Original FPGA
-------------------------

.. code-block:: bash

    # Run the replacement script without parameters
    redpitaya> /root/replace_fpga.sh
    
    # Reboot to activate
    redpitaya> reboot

This restores the backup created when you first replaced the default image.

|


Deprecated Methods
======================

Using /etc/rc.local (Deprecated)
---------------------------------

.. warning::

    **This method is deprecated** in newer Linux distributions (Ubuntu 18.04+) and may not work on recent Red Pitaya OS versions. The ``rc.local`` service is no longer enabled by default in systemd-based systems.
    
    **Use Method 1 (startup.sh) or Method 2 (systemd service) instead.**

For older systems where ``rc.local`` is still available, you can add commands to ``/etc/rc.local``:

**Step 1: Check if rc.local exists and is enabled**

.. code-block:: bash

    redpitaya> systemctl status rc-local.service

If the service is not found or is disabled, use Method 1 or Method 2 instead.

**Step 2: Edit rc.local (if available)**

.. code-block:: bash

    redpitaya> rw
    redpitaya> nano /etc/rc.local

**Step 3: Add load command before** ``exit 0``

.. tabs::

    .. tab:: OS 1.04 or older

        .. code-block:: bash

            #!/bin/bash
            cat /root/red_pitaya_top.bit > /dev/xdevcfg
            exit 0

    .. tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            #!/bin/bash
            fpgautil -b /root/red_pitaya_top.bit.bin
            exit 0

    .. tab:: OS 2.07-43 or newer

        .. code-block:: bash

            #!/bin/bash
            /opt/redpitaya/sbin/overlay.sh v0.94 my_project
            exit 0

**Step 4: Make executable**

.. code-block:: bash

    redpitaya> chmod +x /etc/rc.local
    redpitaya> ro

**Step 5: Test by rebooting**

.. code-block:: bash

    redpitaya> reboot

|


Comparison of Methods
-----------------------

.. list-table::
    :header-rows: 1
    :widths: 25 35 40

    * - Method
      - Pros
      - Cons
    * - startup.sh script
      - **Recommended**, Red Pitaya standard, simple, runs once at boot, easy to manage
      - Requires file editing
    * - systemd service
      - Clean, manageable, advanced control, service dependencies
      - More complex, requires systemd knowledge
    * - /etc/profile.d
      - Easy to add/remove
      - Only loads on login (not boot), runs at every login
    * - Replace default
      - System-wide, affects all applications
      - Modifies system files, harder to revert
    * - /etc/rc.local (deprecated)
      - Simple, single file
      - **Deprecated**, not available on newer systems

**Recommendation:** Use **startup.sh script (Method 1)** for most use cases. Use systemd service (Method 2) only if you need advanced service control features.

|


Troubleshooting Boot Loading
===============================

FPGA Not Loading at Boot
-------------------------

**Check startup.sh syntax:**

.. code-block:: bash

    redpitaya> cat /opt/redpitaya/sbin/startup.sh
    # Look for your FPGA loading command

**Test the command manually:**

.. code-block:: bash

    # Try running the command directly
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 my_project
    
    # Check for errors
    echo $?

**Check file permissions:**

.. code-block:: bash

    redpitaya> ls -l /opt/redpitaya/sbin/startup.sh
    # Should be executable

**View boot logs:**

.. code-block:: bash

    redpitaya> journalctl -b | grep -i fpga
    redpitaya> dmesg | grep -i fpga

Service Won't Start (systemd)
-------------------------------

**Check service status:**

.. code-block:: bash

    redpitaya> systemctl status custom-fpga.service

**View service logs:**

.. code-block:: bash

    redpitaya> journalctl -u custom-fpga.service

**Verify service file syntax:**

.. code-block:: bash

    redpitaya> systemctl cat custom-fpga.service

**Reload systemd configuration:**

.. code-block:: bash

    redpitaya> systemctl daemon-reload

Wrong FPGA Loads at Boot
-------------------------

**Check loaded FPGA:**

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf

**Check startup.sh for conflicts:**

.. code-block:: bash

    redpitaya> grep overlay.sh /opt/redpitaya/sbin/startup.sh
    # Look for multiple FPGA loading commands

**Check for multiple services:**

.. code-block:: bash

    redpitaya> systemctl list-units | grep fpga

|


Related Documentation
======================

- :ref:`fpga_reprogramming` - Basic FPGA loading guide
- :ref:`fpga_advanced_loading` - Advanced FPGA configurations
- :ref:`C and Python API <runApp_api>` - startup.sh script details
- :ref:`device_tree` - Device tree configuration

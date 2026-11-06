.. _software_autostart:

###################################
Autostart and Boot Configuration
###################################

Use this guide to set up programs, services, and FPGA images to start or load automatically when Red Pitaya boots.

.. contents:: Contents
    :local:
    :depth: 2

|

1. Open apps in a browser
=========================

Red Pitaya applications such as Oscilloscope and Spectrum Analyzer are web-based applications served by the board. They are not separate measurement processes that 
``startup.sh`` can open. If you want an application page to appear automatically, configure the browser on the client computer or device to open the Red Pitaya web 
interface after the board is available. For measurements that must begin without a browser, use a C++/Python program or an application designed for boot-time operation, 
such as Record and Play.

Loading an FPGA image or device-tree overlay prepares the board's hardware; it does not open a web page or start a measurement. To configure an FPGA image at boot, see the 
:ref:`FPGA boot loading guide <fpga_boot_loading>`.

|

2. Run SCPI server at boot
==========================

To configure the SCPI server to start at boot, follow the :ref:`SCPI-specific instructions <scpi_boot_time>`. This selects the SCPI service instead of the web interface; they cannot run simultaneously.

|

3. Run a C++ or Python (API) program at boot
=============================================

For simple programs, Red Pitaya's ``startup.sh`` script runs commands once during system startup. For applications that need to be monitored or restarted automatically, use a 
``systemd`` service instead.

1.  Connect to Red Pitaya over SSH and enable write access:

    .. code-block:: console

        rw

2.  Copy the Python script or compiled C/C++ executable to ``/opt/redpitaya/bin/``. Make sure a Python script has a valid interpreter line (shebang) and is executable if you 
    plan to launch it directly.

3.  Edit the startup script:

    .. code-block:: console

        nano /opt/redpitaya/sbin/startup.sh

4.  Add the command for your program near the end of the file. Use the Python API path for Python scripts and run long-lived programs in the background so they do not block 
    the rest of startup:

    .. code-block:: bash

        export PYTHONPATH=/opt/redpitaya/lib/python/:$PYTHONPATH
        /opt/redpitaya/bin/my_measurement.py &
        /opt/redpitaya/bin/my_cpp_measurement &

    Keep only the command for the language you use. Replace the example filenames with the names of your installed program. Check the existing contents before editing and 
    do not remove commands already in ``startup.sh``, unless you are certain they are no longer needed.

5.  Save the file and reboot to test the change:

    .. code-block:: console

        reboot

The startup script runs on every boot. Removing a command prevents it from starting on future boots, but does not stop a copy that is already running.

|

Disable a program added to startup.sh
--------------------------------------

1.  Connect to Red Pitaya over SSH, enable write access, and open the startup script:

    .. code-block:: console

        rw
        nano /opt/redpitaya/sbin/startup.sh

2.  Remove or comment out the command that starts your program. If no other boot-time Python program needs it, also remove the ``PYTHONPATH`` export added for this program. 
    Leave unrelated startup commands unchanged.

3.  Save the ``startup.sh`` file. Reboot to stop the current process and confirm that it no longer starts automatically:

    .. code-block:: console

        reboot

To stop the current process without rebooting, terminate it separately. Use the command matching your program and replace the example name with its actual path:

.. code-block:: console

    # Python
    pkill -f /opt/redpitaya/bin/my_measurement.py
    # C++
    pkill -f /opt/redpitaya/bin/my_cpp_measurement

For a program managed by ``systemd``, disable and stop its service instead. See :ref:`Service Management <service_management>`.

|

Other considerations
---------------------

Use a ``systemd`` service for long-running programs that need service management, such as restart policies or dependencies. See :ref:`Service Management <service_management>`. The ``/etc/profile.d`` directory is for login-shell configuration, not a reliable system boot mechanism. The ``/etc/rc.local`` method is deprecated and is not recommended.

|

4. Load FPGA image and device-tree overlay at boot
===================================================

For loading an FPGA image and device-tree overlay at boot, refer to the :ref:`FPGA image loading <fpga_boot_loading>` section.

|

5. Stream at boot
=================

The :ref:`Streaming command-line utility <stream_util>` can run the streaming server in the background; configure its boot-time launch with the appropriate service or 
startup method.

|


6. Other boot-time tasks
=========================

* Consider ``systemd`` services for managing other custom boot-time tasks.
* The :ref:`Record and Play application <playback&record>` installs its own startup command for unattended recording and playback.
* For automatic PLL synchronisation on the SIGNALlab 250-12, see the :ref:`synchronisation instructions <top_250_12>`.

|

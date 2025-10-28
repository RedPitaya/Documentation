
Red Pitaya provides C and Python APIs that enable direct control of the board's hardware. You can write applications, 
compile them, and execute them directly on the Red Pitaya board. The APIs provide comprehensive control over signal 
generation and acquisition, digital I/O, and communication interfaces (I2C, SPI, UART, CAN).


.. contents:: Table of Contents
    :backlinks: top

|


Version compatibility
======================

.. tabs::

    .. group-tab:: OS 1.04 or lower

        .. warning::

            The API examples are included in the main :rp-github:`Red Pitaya GitHub repository <RedPitaya>`.
            Ensure your Red Pitaya OS version matches the downloaded :rp-github:`GitHub repository version <RedPitaya>`.
            Using incompatible versions can cause functionality issues.

        Use the **Tags** dropdown on GitHub to select the appropriate version.

        .. figure:: img/GitHub_branch_tags.png
            :align: center
            :width: 800

    .. group-tab:: OS 2.00 or higher

        .. warning::

            The API examples are located in the separate :rp-github:`Red Pitaya Examples GitHub repository <RedPitaya-Examples>`. Before running any examples, 
            ensure it is compatible with your Red Pitaya OS version by comparing the example information with your current OS version.

            Running a new example on an old OS can result in compatibility issues.

|


API overview
=============

There are two main APIs available for Red Pitaya:

- **C API** - Native C library for low-level hardware control
- **Python API** - Python wrappers around the C API for easier scripting and rapid development

.. note::

    Python API functions are only available on OS 2.00-23 or higher.


Return values
--------------

All API functions return an integer value:

* **0** (RP_OK) - Function executed successfully
* **Non-zero** - An error occurred

Python API functions are wrappers around the C API. They have identical names and return an array where:

* **First element** - C API function return value (success or error code)
* **Subsequent elements** - Expected return values from the function

For API usage examples, see the :ref:`Examples section <examples>`.

|


Working with C Applications
=============================

The Red Pitaya board includes a native C toolchain on the Debian system, allowing you to compile C applications 
directly on the target hardware.


Compiling example code
-----------------------

Step 1: Connect via SSH
^^^^^^^^^^^^^^^^^^^^^^^^^

Connect to your Red Pitaya board via :ref:`SSH <ssh>`. Replace ``192.168.0.100`` with your Red Pitaya's IP address:

.. code-block:: shell-session

    ssh root@192.168.0.100

Alternatively, use the ``.local`` address (replace 'xxxxxx' with the last 6 characters of your Red Pitaya's MAC address):

.. code-block:: shell-session

    ssh root@rp-xxxxxx.local

The default password is ``root``.


Step 2: Clone the repository
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Clone the Red Pitaya Git repository to access example code:

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: shell-session

                git clone https://github.com/RedPitaya/RedPitaya.git
                cd RedPitaya/Examples

    .. group-tab:: OS version 2.00 or higher

        .. code-block:: shell-session

            git clone https://github.com/RedPitaya/RedPitaya-Examples.git
            cd RedPitaya


Step 3: Compile the example
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Navigate to the C examples directory and compile:

.. code-block:: shell-session

    cd C
    make digital_led_blink

.. tabs::

    .. group-tab:: 1.04 or older

        Alternatively, compile manually using gcc:

        .. code-block:: shell-session

            cd C
            gcc digital_led_blink.c -o digital_led_blink

    .. group-tab:: 2.00 or higher

        Alternatively, compile manually using g++:

        .. code-block:: shell-session

            cd C
            g++ digital_led_blink.cpp -o digital_led_blink

        .. note::

            With the latest Red Pitaya OS versions (2.05-37 and higher), we are moving towards C++ for API examples.
            For C examples, please use the `.c` files and compile them with `gcc` as shown above.

.. note::

    The Makefile automatically links required libraries during compilation, eliminating the need to specify 
    library paths when executing the application.


Step 4: Load FPGA image
^^^^^^^^^^^^^^^^^^^^^^^^^

API applications require the v0.94 FPGA image:

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: shell-session

            cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    .. group-tab:: OS version 2.00 or higher

        .. code-block:: shell-session

            overlay.sh v0.94


Step 5: Execute the application
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Run the compiled application:

.. tabs::

    .. group-tab:: With Makefile

        If you compiled using the Makefile, libraries are already linked:
    
        .. code-block:: shell-session

            ./digital_led_blink

    .. group-tab:: Without Makefile

        If you compiled manually, provide the library path explicitly:

        .. code-block:: shell-session

            LD_LIBRARY_PATH=/opt/redpitaya/lib ./digital_led_blink

.. note::

    Press ``CTRL+C`` to stop applications running in continuous loops.


Compiling custom code
-----------------------

When developing custom C or C++ applications, follow these steps to transfer and compile your code on Red Pitaya.


Prerequisites
^^^^^^^^^^^^^^

.. note::

    Configure your code editor with the following settings:
    
    * **End of Line Sequence:** LF (not CRLF)
    * **Encoding:** UTF-8
   
    Using CRLF line endings will cause compiled programs to straightup fail with errors or do so after a reboot.


Step 1: Transfer code to Red Pitaya
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Copy your custom C or C++ code from your computer to Red Pitaya using the ``scp`` command. Here is an example of transferring a single C file to the ``/root`` directory:

.. code-block:: shell-session

    scp /path/to/custom_program.c root@rp-xxxxxx.local:/root

Alternatively, use a program like WinSCP for graphical file transfer.


Step 2: Connect via SSH
^^^^^^^^^^^^^^^^^^^^^^^^^

Connect to your Red Pitaya board via :ref:`SSH <ssh>`. Replace ``192.168.0.100`` with your Red Pitaya's IP address:

.. code-block:: shell-session

    ssh root@192.168.0.100

Alternatively, use the ``.local`` address (replace 'xxxxxx' with the last 6 characters of your Red Pitaya's MAC address):

.. code-block:: shell-session

    ssh root@rp-xxxxxx.local


Step 3: Create a Makefile
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Create a Makefile in the same directory as your C or C++ code to automate library linking. Add your program names 
to the ``PRGS`` variable.

Select the appropriate Makefile template for your OS version:

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: makefile

            MODEL ?= Z10

            CFLAGS  = -std=gnu11 -Wall
            CFLAGS += -I/opt/redpitaya/include -D$(MODEL)
            LDFLAGS = -L/opt/redpitaya/lib
            LDLIBS = -static -lrp
            
            ifeq ($(MODEL),Z20_250_12)
            INCLUDE += -I/opt/redpitaya/include/api250-12
            LDLIBS += -lrp-gpio -lrp-i2c
            endif
            
            LDLIBS += -lrp-hw -lm -lstdc++ -lpthread
            
            # List of programs to compile
            PRGS = digital_led_blink \
                   custom_program_1 \
                   custom_program_2

            OBJS := $(patsubst %,%.o,$(PRGS))

            all: $(PRGS)

            $(PRGS): %: %.c
                $(CC) $< $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

            clean:
                $(RM) *.o $(OBJS)

    .. group-tab:: OS version 2.00-15 to 2.00-23

        .. code-block:: makefile
    
            MODEL ?= Z10
    
            CFLAGS  = -std=gnu11 -Wall
            CFLAGS += -I/opt/redpitaya/include -D$(MODEL)
            LDFLAGS = -L/opt/redpitaya/lib
            LDLIBS = -static -lrp -lrp-hw-calib -lrp-hw-profiles
    
            INCLUDE += -I/opt/redpitaya/include/api250-12
            LDLIBS += -lrp-gpio -lrp-i2c
            LDLIBS += -lrp-hw -lm -lstdc++ -lpthread -li2c
    
            # List of programs to compile
            PRGS = digital_led_blink \
                   custom_program_1 \
                   custom_program_2
    
            OBJS := $(patsubst %,%.o,$(PRGS))

            all: $(PRGS)
    
            $(PRGS): %: %.c
                $(CC) $< $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@
    
            clean:
                $(RM) *.o $(OBJS)

    .. group-tab:: OS version 2.00-30 and higher

        .. code-block:: makefile

            CFLAGS  = -std=gnu11 -Wall
            CFLAGS += -I/opt/redpitaya/include
            LDFLAGS = -L/opt/redpitaya/lib
            LDLIBS = -static -lrp-hw-can -lrp -lrp-hw-calib -lrp-hw-profiles

            INCLUDE += -I/opt/redpitaya/include/api250-12
            LDLIBS += -lrp-gpio -lrp-i2c
            LDLIBS += -lrp-hw -lm -lstdc++ -lpthread -li2c -lsocketcan

            # List of programs to compile
            PRGS = digital_led_blink \
                   custom_program_1 \
                   custom_program_2

            OBJS := $(patsubst %,%.o,$(PRGS))

            all: $(PRGS)

            $(PRGS): %: %.c
                $(CC) $< $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

            clean:
                $(RM) *.o $(OBJS)

            clean_all: clean
                $(RM) $(PRGS)

    .. group-tab:: OS version 2.05-37 or higher

        With this OS version, C++ is the preferred language for API examples. Use the following Makefile template for C++ code:

        .. code-block::

            CFLAGS  = -Wall -std=c++20 ## -Werror
            CFLAGS += -I/opt/redpitaya/include
            LDFLAGS = -L/opt/redpitaya/lib
            LDLIBS = -static -lrp-hw-can -lrp -lrp-hw-calib -lrp-hw-profiles

            INCLUDE += -I/opt/redpitaya/include/api250-12
            LDLIBS += -lrp-gpio -lrp-i2c
            LDLIBS += -lrp-hw -lm -lstdc++ -lpthread -li2c -lsocketcan

            # List of programs to compile
            PRGS = digital_led_blink \
                   custom_program_1 \
                   custom_program_2

            OBJS := $(patsubst %,%.o,$(PRGS))
            SRC := $(patsubst %,%.cpp,$(PRGS))

            all: $(PRGS)

            $(PRGS): %: %.cpp
                $(CXX) $< $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

            clean:
                $(RM) *.o
                $(RM) $(OBJS)

            clean_all: clean
                $(RM) $(PRGS)


Step 4: Compile your program
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Compile using the program name without the .c or .cpp extension:

.. code-block:: shell-session

    make custom_program_1


Step 5: Load FPGA image
^^^^^^^^^^^^^^^^^^^^^^^^^

Load the required FPGA image:

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: shell-session

            cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    .. group-tab:: OS version 2.00 or higher

        .. code-block:: shell-session

            overlay.sh v0.94

.. note::

    When :ref:`uploading a custom FPGA image <>`, please note that some API functions may fail to work due to the changes in the FPGA.


Step 6: Execute your program
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Run the compiled application:

.. tabs::

    .. group-tab:: With Makefile

        Libraries are already linked:
    
        .. code-block:: shell-session

            ./custom_program_1

    .. group-tab:: Without Makefile

        Provide the library path explicitly:

        .. code-block:: shell-session

            LD_LIBRARY_PATH=/opt/redpitaya/lib ./custom_program_1

.. note::

    Press ``CTRL+C`` to stop applications running in continuous loops.

|


Working with Python Applications
==================================

Python applications can be executed from any directory on Red Pitaya, but we recommend storing code in the 
``/root`` (home) directory.

Python is pre-installed on Red Pitaya OS 2.00-23 and higher. The version depends on the OS version.

+-------------------------+-----------------------+
| Red Pitaya OS Version   | Python Version        |
+=========================+=======================+
| Pre 2.00-23             | Not available         |
+-------------------------+-----------------------+
| 2.00-23 and higher      | Python 3.10.          |
+-------------------------+-----------------------+


Prerequisites
--------------

.. note::

    Configure your code editor with the following settings:
    
    * **End of Line Sequence:** LF (not CRLF)
    * **Encoding:** UTF-8
   
    Using CRLF line endings will cause compiled programs to straightup fail with errors or do so after a reboot.


Creating and deploying Python code
------------------------------------

Step 1: Write your Python code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Create your Python application on your computer. Include the ``rp`` and any other necessary libraries. Use the available examples as reference:

.. code-block:: python

    #!/usr/bin/python3
    import rp


Step 2: Copy code to Red Pitaya
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Transfer a single file:

.. code-block:: shell-session

    scp /path/to/pythonAPI_example.py root@rp-xxxxxx.local:/root

Transfer an entire directory (use the ``-r`` flag):

.. code-block:: shell-session

    scp -r /path/to/python_project/ root@rp-xxxxxx.local:/root


Step 3: Make files executable
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Connect via :ref:`SSH <ssh>` and set executable permissions:

.. code-block:: shell-session

    ssh root@rp-xxxxxx.local
    chmod +x pythonAPI_example.py


Step 4: Execute the Python script
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Run your Python application:

.. code-block:: shell-session

   ./pythonAPI_example.py


Troubleshooting Python path
-----------------------------

If you encounter a ``ModuleNotFoundError: No module named 'rp'`` error, the Python path is not configured correctly.

Add the following lines to the end of the ``.bashrc`` file in your home directory:

.. code-block:: bash

    PYTHONPATH=/opt/redpitaya/lib/python/:$PYTHONPATH
    export PYTHONPATH

Apply the changes:

.. code-block:: shell-session

    source ~/.bashrc

Alternatively, reboot Red Pitaya for the changes to take effect.

|


Running applications at boot
=============================

There are several ways to make your C or Python applications run automatically at Red Pitaya startup:

1. **startup.sh script** (recommended) - Add your application commands to the ``/opt/redpitaya/sbin/startup.sh`` script.
2. **etc/profile.d directory** - Create a script in the ``/etc/profile.d/`` directory that runs your application.
3. **Other methods** - Use systemd services or cron jobs for more advanced startup configurations.


Startup.sh script
------------------

The ``startup.sh`` script is the recommended method for running applications at boot. The application will run exactly once after the system starts.

1. **Enable read-write mode**. Since we are modifying a system file, switch to read-write mode:

    .. code-block:: shell-session

        rw

2. **Copy files to system directory**. Copy your application files to a suitable system directory, e.g., ``/opt/redpitaya/bin/``:

    .. tabs::

        .. group-tab:: Python API

            .. code-block:: shell-session

                cp /root/pythonAPI_example.py /opt/redpitaya/bin/

        .. group-tab:: C API

            Make sure the C application is **compiled and executable**.

            .. code-block:: shell-session

                cp /root/CAPI_example /opt/redpitaya/bin/

3. **Open the startup.sh script for editing**:

    .. code-block:: shell-session

        nano /opt/redpitaya/sbin/startup.sh

4. **Append application startup command**. Add a line at the end of the file to execute your application:

    .. tabs::

        .. group-tab:: Python API

            .. code-block:: shell-session

                export PYTHONPATH=/opt/redpitaya/lib/python/:\$PYTHONPATH
                /opt/redpitaya/bin/pythonAPI_example.py

        .. group-tab:: C API

            .. code-block:: shell-session

                /opt/redpitaya/bin/CAPI_example

5. **Save and exit the editor**.

6. **Reboot**. Restart Red Pitaya to apply the changes: 

    .. code-block:: shell-session

        reboot

Stopping the application
^^^^^^^^^^^^^^^^^^^^^^^^^^

To stop a running application on Red Pitaya, you can use one of the following methods:

1. **Kill by process name** (temporary stop):

    .. tabs::

        .. group-tab:: Python API

            .. code-block:: shell-session

                pkill -f pythonAPI_example.py

        .. group-tab:: C API

            .. code-block:: shell-session

                pkill -f CAPI_example

2. **Remove startup command** (permanent stop):

    * First stop the application using the method above. 
    * Edit the startup.sh script to remove or comment out the line that starts your application.
    * Optionally, remove the application files from the system directory if no longer needed.
    * Reboot Red Pitaya to apply the changes.


Profile.d directory
----------------------

The ``/etc/profile.d/`` directory is used for system-wide environment variable settings and startup scripts. You can create a new script file in this directory to set environment variables for your application.
The script will run for all users at every shell login (once at Red Pitaya boot and at each new terminal session).

1. **Enable read-write mode**. Since we are modifying a system file, switch to read-write mode:

    .. code-block:: shell-session

        rw

#. **Copy files to system directory**. Copy your application files to a suitable system directory, e.g., ``/opt/redpitaya/bin/``:

    .. tabs::

        .. group-tab:: Python API

            .. code-block:: shell-session

                cp /root/pythonAPI_example.py /opt/redpitaya/bin/

        .. group-tab:: C API

            Make sure the C application is **compiled and executable**.

            .. code-block:: shell-session

                cp /root/CAPI_example /opt/redpitaya/bin/

#. **Create a new script file**. To prevent conflicts with existing scripts and variables, the file name should be last in alphabetical order. For example, create ``zzz_my_startup.sh``:

    .. code-block:: shell-session

        nano /etc/profile.d/zzz_my_startup.sh

#. **Add application startup command**. Add the command to run your application:

    .. tabs::

        .. group-tab:: Python API

            .. code-block:: shell-session

                #!/bin/bash
                export PYTHONPATH=/opt/redpitaya/lib/python/:\$PYTHONPATH
                /opt/redpitaya/bin/pythonAPI_example.py &

        .. group-tab:: C API

            .. code-block:: shell-session

                #!/bin/bash
                /opt/redpitaya/bin/CAPI_example &

#. **Make the script executable**:

    .. code-block:: shell-session

        chmod +x /etc/profile.d/zzz_my_startup.sh

#. **Reboot**. Restart Red Pitaya to apply the changes:

    .. code-block:: shell-session

        reboot


Stopping the application
^^^^^^^^^^^^^^^^^^^^^^^^^^

To stop a running application on Red Pitaya, you can use one of the following methods:

1. **Kill by process name** (temporary stop):

    .. tabs::

        .. group-tab:: Python API

            .. code-block:: shell-session

                pkill -f pythonAPI_example.py

        .. group-tab:: C API

            .. code-block:: shell-session

                pkill -f CAPI_example

#. **Remove startup command** (permanent stop):

    * First stop the application using the method above.
    * Remove the script file from the ``/etc/profile.d/`` directory.
    * Optionally, remove the application files from the system directory if no longer needed.
    * Reboot Red Pitaya to apply the changes.


Other methods
----------------------

You can also use other methods like creating a systemd service or using cron jobs to run applications at boot. These methods provide more advanced control over application startup and management.

.. note::

    The ``/etc/rc.local`` file method is deprecated in recent Red Pitaya OS versions and is not recommended for new setups.

To learn more about these methods, refer to the official Linux documentation or relevant online resources.

|


Available Libraries
======================

Red Pitaya provides several libraries for different functionalities. The core libraries available for C and Python APIs are listed below:

+------------------------+------------------------------------------------------------------------------+----------------+
| Library                | Description                                                                  | Available from |
+========================+==============================================================================+================+
| **rp**                 | Core API for initialization, LEDs, analog pins, GPIOs, generation,           | OS 2.00-23     |
|                        | acquisition, board control, and DMA. Required for most projects.             |                |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_hw**              | UART, SPI, I2C interfaces, and status LED control                            | OS 2.00-23     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_hw_calib**        | Calibration parameter configuration and settings                             | OS 2.00-23     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_hw_profiles**     | Hardware profile management                                                  | OS 2.00-23     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_dsp**             | Digital signal processing (FFT, window functions, dB conversion)             | OS 2.00-23     |
|                        | Used by the Spectrum analyzer application                                    |                |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_overlay**         | FPGA image management and switching                                          | OS 2.00-30     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_hw_can**          | CAN interface control                                                        | OS 2.00-30     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_formatter**       | Data format conversion (WAV, TDMS, CSV) for streamed data                    | OS 2.00-30     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_arb**             | Arbitrary waveform manager for uploading and configuring custom waveforms    | OS 2.00-30     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_sweep**           | Sweep mode control                                                           | OS 2.04-35     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_la**              | Logic analyzer and protocol decoding (UART, SPI, I2C, CAN)                   | OS 2.07-43     |
+------------------------+------------------------------------------------------------------------------+----------------+
| **rp_updater**         | Update Red Pitaya ecosystem remotely (Nightly Builds)                        | OS 2.07-43     |
+------------------------+------------------------------------------------------------------------------+----------------+

|

API Command Reference
======================

Complete documentation
-----------------------

The API functions and commands are documented in the :ref:`available commands list <command_list>`.

For complete API reference:

**C API:**

    * GitHub repository: :rp-github:`rp-api section <RedPitaya/tree/master/rp-api>`
    * Function declarations: :rp-github:`rp.h header file <RedPitaya/blob/master/rp-api/api/include/rp.h>`

**Python API:**

    * Connect via :ref:`SSH <ssh>` and explore: ``/opt/redpitaya/lib/python/``

**FPGA:**

    * :ref:`FPGA reprogramming guide <fpga_reprogramming>` for details on uploading custom FPGA images.


API Examples
=============

Comprehensive examples demonstrating API usage are available in the :ref:`Examples section <examples>`.

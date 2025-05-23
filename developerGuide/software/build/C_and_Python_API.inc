
You can write simple C and Python algorithms, make executables, and run them directly on the Red Pitaya board. A list of
built-in functions (APIs) are available providing full control over the Red Pitaya board (signal generation and
acquisition, digital I/O control, communication (I2C, SPI, UART, CAN) and more).

.. warning::

    Please make sure that your Red Pitaya OS and the downloaded GitHub ecosystem repository are compatible.
    We recommend using a GitHub ecosystem that is meant to run on your current Red Pitaya OS version:

    - 2.05-37 - Branch 2024.3
    - 2.04-35 - Branch 2024.2
    - 2.00-30 - Branch 2024.1
    - 2.00-23 - Branch 2023.3
    - 2.00-18 - Branch 2023.2
    - 2.00-15 - Branch 2023.1
    - 1.04-28 - Branch 2022.2
    - 1.04-18 - Branch 2022.1

    Using an old OS with a newer GitHub ecosystem can result in compatibility isses.

C and Python API functions
============================

.. note::

    Python API functions are only available on OS 2.00-23 or newer.

All API functions have an "int" return value. If the returned value is 0 (equal to *RP_OK*), then the function executed successfully.

The Python API functions are just wrappers that call the corresponding C API function. Consequently, they have exactly the same names, and always return an array where the first element is the C API function return value (successful or not), and the other elements represent the expected return values.


Examples on how to control Red Pitaya using APIs can be found :ref:`here <examples>`.


Compiling and running C applications
=====================================

When compiling on the target no special preparations are needed. A native toolchain is available directly on the Debian system.


Compiling and running Example code
-----------------------------------

1.  **First connect to your board over the** :ref:`SSH <ssh>` **connection** (replace the IP, the default password is `root`).

    .. code-block:: shell-session

        ssh root@192.168.0.100

    You can also use the .local address (not all computers support .local addresses) (replace 'xxxxxx' with the last 6 characters of the Red Pitaya's MAC address):

    .. code-block:: shell-session

        ssh root@rp-xxxxxx.local


2.  **Now make a clone of the Red Pitaya Git repository and enter the project directory.**

    .. code-block:: shell-session

        git clone https://github.com/RedPitaya/RedPitaya.git
        cd RedPitaya

    When you copy the source code from our repository you will also copy all available C API examples to your Red Pitaya board.


3.  **In order to compile one example just use the source file name without the `.c` extension.**

    .. code-block:: shell-session

        cd Examples/C
        gcc digital_led_blink.c -o digital_led_blink

    or

    .. code-block:: shell-session

        cd Examples/C
        make digital_led_blink


    To avoid the step of having to specify the library path explicitly everytime before executing a C API script,
    there is a **Makefile** script in the same folder as the Example APIs, which links the libraries during the compilation process.


4.  **Applications based on the API require a specific FPGA image (v0.94) to be loaded:**

    .. tabs::

        .. group-tab:: OS version 1.04 or older

            .. code-block:: shell-session

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

        .. group-tab:: OS version 2.00 or newer

            .. code-block:: shell-session

                redpitaya> overlay.sh v0.94


5. **Execute the application.**

    .. tabs::

        .. group-tab:: With Makefile

            Since the libraries were linked during the compilation process, the application can be executed normally.
        
            .. code-block:: shell-session

                ./digital_led_blink

        .. group-tab:: No Makefile
    
            The path to Red Pitaya shared libraries must be provided explicitly.

            .. code-block:: shell-session

                LD_LIBRARY_PATH=/opt/redpitaya/lib ./digital_led_blink


    Some of the applications run in a continuous loop - press `CTRL+C` to stop them.


Compiling and running custom code
-----------------------------------

.. note::

   When creating custom C API programs on your computer, please make sure that **End of Line Sequence** in your code editor is set to **LF**
   (*CRLF End of Line Sequence* causes already compiled C programs not to function after reboot). The recommended encoding is **UTF-8**.


1.  First, send the custom C code example from your computer to the Red Pitaya board. Here is an example of how to copy the code to */root* directory on the Red Pitaya.

    .. code-block:: shell-session

        scp /path/to/custom/c/api/ root@rp-xxxxxx.local:/root

2.  Then connect to your board over :ref:`SSH <ssh>` (replace the IP, the default password is `root`).

    .. code-block:: shell-session

        ssh root@192.168.0.100

    You can also use the .local address (not all computers support .local addresses) (replace 'xxxxxx' with the last 6 characters of the Red Pitaya's MAC address):

    .. code-block:: shell-session

        ssh root@rp-xxxxxx.local


3.  To avoid the step of having to specify the library path explicitly everytime before executing a C API script,
    create a **Makefile** script in the same folder as the APIs, which will link the libraries during the compilation process.
    Do not forget to include your C program under the *List of compiled object files* - **PRGS** variable.
    Here is an example:

    .. tabs::

        .. group-tab:: OS version 1.04 or older

            .. code-block:: shell-session

                MODEL ?= Z10

                CFLAGS  = -std=gnu11 -Wall ## -Werror
                CFLAGS += -I/opt/redpitaya/include -D$(MODEL)
                LDFLAGS = -L/opt/redpitaya/lib
                LDLIBS = -static -lrp
                
                ifeq ($(MODEL),Z20_250_12)
                INCLUDE += -I/opt/redpitaya/include/api250-12
                LDLIBS += -lrp-gpio -lrp-i2c
                endif
                
                LDLIBS += -lrp-hw -lm -lstdc++ -lpthread
                
                # List of compiled object files (not yet linked to executable)

                PRGS = digital_led_blink \
                       api_example_2 \
                       api_example_3 \
                       api_example_x

                OBJS := $(patsubst %,%.o,$(PRGS))
                SRC := $(patsubst %,%.c,$(PRGS))

                all: $(PRGS)

                $(PRGS): %: %.c
                	$(CC) $< $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

                clean:
                	$(RM) *.o
                	$(RM) $(OBJS)

        .. group-tab:: OS version between 2.00-15 and 2.00-23

            .. code-block:: shell-session
        
                MODEL ?= Z10
        
                CFLAGS  = -std=gnu11 -Wall ## -Werror
                CFLAGS += -I/opt/redpitaya/include -D$(MODEL)
                LDFLAGS = -L/opt/redpitaya/lib
                LDLIBS = -static -lrp -lrp-hw-calib -lrp-hw-profiles
        
                INCLUDE += -I/opt/redpitaya/include/api250-12
                LDLIBS += -lrp-gpio -lrp-i2c
                LDLIBS += -lrp-hw -lm -lstdc++ -lpthread -li2c
        
                # List of compiled object files (not yet linked to executable)
        
                PRGS = digital_led_blink \
                       api_example_2 \
                       api_example_3 \
                       api_example_x
        
                OBJS := $(patsubst %,%.o,$(PRGS))
                SRC := $(patsubst %,%.c,$(PRGS))
        
                all: $(PRGS)
        
                $(PRGS): %: %.c
                    $(CC) $< $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@
        
                clean:
                    $(RM) *.o
                    $(RM) $(OBJS)

        .. group-tab:: OS version 2.00-30 and newer

            .. code-block:: shell-session

                CFLAGS  = -std=gnu11 -Wall ## -Werror
                CFLAGS += -I/opt/redpitaya/include
                LDFLAGS = -L/opt/redpitaya/lib
                LDLIBS = -static -lrp-hw-can -lrp -lrp-hw-calib -lrp-hw-profiles

                INCLUDE += -I/opt/redpitaya/include/api250-12
                LDLIBS += -lrp-gpio -lrp-i2c
                LDLIBS += -lrp-hw -lm -lstdc++ -lpthread -li2c -lsocketcan

                # List of compiled object files (not yet linked to executable)

                PRGS = digital_led_blink \
                                       api_example_2 \
                                       api_example_3 \
                                       api_example_x
    
                OBJS := $(patsubst %,%.o,$(PRGS))
                SRC := $(patsubst %,%.c,$(PRGS))

                all: $(PRGS)

                $(PRGS): %: %.c
                	$(CC) $< $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

                clean:
                	$(RM) *.o
                	$(RM) $(OBJS)

                clean_all: clean
                	$(RM) $(PRGS)


4.  In order to compile one example, just use the source file name without the `.c` extension.

    .. code-block:: shell-session

        cd Examples/C
        make digital_led_blink


5.  Applications based on the API require a specific FPGA image (v0.94) to be loaded:

    .. tabs::

        .. group-tab:: OS version 1.04 or older

            .. code-block:: shell-session

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

        .. group-tab:: OS version 2.00 or higher

            .. code-block:: shell-session

                redpitaya> overlay.sh v0.94


6. Execute the application.

    .. tabs::

        .. group-tab:: With Makefile

            Since the libraries were linked during the compilation process, the application can be executed normally.
        
            .. code-block:: shell-session

                ./digital_led_blink

        .. group-tab:: No Makefile
    
            The path to Red Pitaya shared libraries must be provided explicitly.

            .. code-block:: shell-session

                LD_LIBRARY_PATH=/opt/redpitaya/lib ./digital_led_blink

    If an application is running in a continuous loop - press `CTRL+C` to stop them.



Running Python applications
==============================

The Python applications can be executed from anywhere inside the Red Pitaya directory system, 
but we do recommend using the **"Home" ("/root")** directory for code storeage.

.. note::

    Please make sure that **End of Line Sequence** in your code editor is set to **LF** (*CRLF End of Line Sequence* causes a **Bad Interpreter error**).
    The recommended encoding is **UTF-8**.


1.  The best way to create Python APIs is to write the code on your computer (use the available examples as a reference).
    Do not forget to include the **rp** library.


2.  Copy the code to Red Pitaya using the **scp** (secure copy) command:

    .. code-block:: shell-session

        scp "path/to/pythonAPI/file" root@rp-xxxxxx.local


3.  If copying a full directory do not forget to add the **-r** flag:

    .. code-block:: shell-session

        scp -r "path/to/pythonAPI/folder" root@rp-xxxxxx.local


4.  Connect to your Red Pitaya via :ref:`SSH <ssh>` and make the files executable:

    .. code-block:: shell-session

        chmod +x pythonAPI_example1.py pythonAPI_example2.py pythonAPI_example3.py


5.  Finally, run the code.

    .. code-block:: shell-session

       ./pythonAPI_example.py


.. note::

    If a **ModuleNotFoundError: No module named 'rp'** error pops-up, Python Path is not properly configured.
    Add the following two lines to the end of the **.bashrc** file (inside home directory).

    .. code-block:: shell-session

        PYTHONPATH=/opt/redpitaya/lib/python/:$PYTHONPATH
        export PYTHONPATH

    Then execute the **.bashrc** or restart Red Pitaya:

    .. code-block:: shell-session

        source ./.bashrc


Red Pitaya Python library list
-------------------------------

Here is a full list of Red Pitaya libraries with functionalities you can include into your projects:

+------------------------+------------------------------------------------------------------------------+-------------+
| Library                | Description                                                                  | Ecosystem   |
+========================+==============================================================================+=============+
| **rp**                 | API commands for API initialisation, controlling LEDs, Analog pins, GPIOs,   | 2.00-23     |
|                        | Generation, Acquisition, Board Control commands, and DMA.                    |             |
|                        | Default library, should be included in almost every project.                 |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_hw**              | API commands for UART, SPI, and I2C interface, and Status LED control.       | 2.00-23     |
|                        |                                                                              |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_hw_calib**        | API commands for configuring calibration parameters and settings.            | 2.00-23     |
|                        |                                                                              |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_hw_profiles**     | API commands for the CAN interface.                                          | 2.00-23     |
|                        |                                                                              |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_dsp**             | API commands for digital signal processing (FFT, window functions, convert   | 2.00-23     |
|                        | to dB, ...). Used by the Spectrum analyzer application.                      |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_overlay**         | Changing the current FPGA image.                                             | 2.00-30     |
|                        |                                                                              |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_hw_can**          | API commands for the CAN interface.                                          | 2.00-30     |
|                        |                                                                              |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_formatter**       | API commands for converting streamed data between wav, tdms and csv.         | 2.00-30     |
|                        |                                                                              |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_arb**             | API commands for uploading and configuring the arbitrary waveform manager.   | 2.00-30     |
|                        | Used by the Arbitrary waveform manager application.                          |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_sweep**           | API commands for controlling Sweep mode.                                     | 2.04-35     |
|                        |                                                                              |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+
| **rp_la**              | API commands for logic analyzer and decoding of UART, SPI, I2C and CAN data. | in dev      |
|                        |                                                                              |             |
|                        |                                                                              |             |
+------------------------+------------------------------------------------------------------------------+-------------+


C and Python API all available commands
========================================

The API functions/commands are written in the :ref:`available commands' list <command_list>`.
As of now the list does not include all possible options. If you want to check out all available API commands they are available here:
    
    - C - Check the `"rp-api" section of the GitHub repository <https://github.com/RedPitaya/RedPitaya/blob/master/rp-api>`_ section of the GitHub repository (`Function info <https://github.com/RedPitaya/RedPitaya/blob/master/rp-api/api/include/rp.h>`_).
    - Python - Establish an :ref:`SSH <ssh>` connection to your Red Pitaya and look into the "/opt/redpitaya/lib/python" directoy.


C and Python API examples
===========================

The examples are available :ref:`here <examples>`.

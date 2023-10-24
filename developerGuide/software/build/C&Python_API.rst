.. _C&Py_Api:

####################################
Running C and Python Applications
####################################

You can write simple C and Python algorithms, make executables, and run them directly on the Red Pitaya board. A list of
built-in functions (APIs) are available providing full control over the Red Pitaya board (signal generation and
acquisition, digital I/O control, communication (I2C, SPI, UART, CAN) and more).

.. warning::

    Please make sure that your Red Pitaya OS and the downloaded GitHub ecosystem repository are compatible.

    Using a 1.04 or older OS version together with 2023.1 or newer GitHub ecosystem will result in compatibility isses. To address this please:
    - Use the latest GitHub ecosystem (master branch) together with Red Pitaya OS 2.00 or higher.
    - Use branch 2022.2 or older GitHub ecosystem together with 1.04 or older Red Pitaya OS.


C and Python API functions
============================

.. note::

    Python API functions are only available on OS 2.00-23 or newer.

All API functions have an "int" return value. If the returned value is 0 (equal to *RP_OK*), then the function executed successfully.

The Python API functions are just wrappers that call the corresponding C API function. Consequently, they have exactly the same names, and always return an array where the first element is the C API function return value (successful or not), and the other elements represent the expected return values.

.. note::

    Please note that not all available API functions are in the :ref:`Available SCPI commands' list <scpi_command_list>`. If you want to check out all available API functions they are available here:
    - C - Check the |rp-api| section of the GitHub repository.
    - Python - Establish an :ref:`SSH <ssh>` connection to your Red Pitaya and look into the "/opt/redpitaya/lib/python" directoy.

.. |rp-api| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/rp-api" target="_blank">"rp-api" section of the GitHub repository</a>


Examples on how to control Red Pitaya using APIs can be found :ref:`here <examples>`.


.. _comC:

Compiling and running C applications
=====================================

.. note::

    When you copy the source code from our repository (following the instructions below) you will also copy all C examples to your Red Pitaya board. After that, only the compilation step is needed.


When compiling on the target no special preparations are needed. A native toolchain is available directly on the Debian system.

First connect to your board over :ref:`SSH <ssh>` (replace the IP, the default password is `root`).

.. code-block:: shell-session

    ssh root@192.168.0.100

You can also use the .local address (not all computers support .local addresses) (replace 'xxxxxx' with the last 6 characters of the Red Pitaya's MAC address):

.. code-block:: shell-session

    ssh root@rp-xxxxxx.local

Now make a clone of the Red Pitaya Git repository and enter the project directory.

.. code-block:: shell-session

    git clone https://github.com/RedPitaya/RedPitaya.git
    cd RedPitaya

In order to compile one example just use the source file name without the `.c` extension.

.. code-block:: shell-session

    cd Examples/C
    make digital_led_blink

Applications based on the API require a specific FPGA image (v0.94) to be loaded:

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: shell-session

            redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    .. group-tab:: OS version 2.00

        .. code-block:: shell-session

            redpitaya> overlay.sh v0.94

Execute the application.

Note that the path to Red Pitaya shared libraries must be provided explicitly.

.. code-block:: shell-session

    LD_LIBRARY_PATH=/opt/redpitaya/lib ./digital_led_blink

Some of the applications run in a continuous loop - press `CTRL+C` to stop them.


.. _comPython:

Running Python applications
==============================

The Python applications can be executed from anywhere inside the Red Pitaya directory system, but we do recommend using the **"Home" ("/root")** directory for code storeage.

1. The best way to create Python APIs is to write the code on your computer (use the available examples as a reference) and then copy the code to Red Pitaya using the **scp** (secure copy) command:

    .. code-block:: shell-session

        scp "path/to/pythonAPI/file" root@rp-xxxxxx.local

2. If copying a full directory do not forget to add the **-r** flag:

    .. code-block:: shell-session

        scp -r "path/to/pythonAPI/folder" root@rp-xxxxxx.local

3. Connect to your Red Pitaya via :ref:`SSH <ssh>` and make the files executable:

    .. code-block:: shell-session

        chmod +x pythonAPI_example1.py pythonAPI_example2.py pythonAPI_example3.py

4. Finally, run the code.

    .. code-block:: shell-session

       ./pythonAPI_example.py


C and Python API examples
===========================

The examples are available :ref:`here <examples>`. They are presented together with the SCPI example code.


.. _comC:

#######################################
Compiling and running C applications
#######################################

You can write simple C algorithms, make executables and run them on the Red Pitaya board. A list of
built-in functions (APIs) are available providing full control over the Red Pitaya board (signal generation and
acquisition, digital I/O control, communication: I2C, SPI, UART and other).
How to compile a C algorithm is shown in the instructions below, while a list of Examples is available
:ref:`here <examples>`.

.. note::

    When you copy the source code from our repository (following the instructions below) you will also copy all C examples to your Red Pitaya board. After that, only the compiling step is needed.

.. note::

    Here is a |rp.c| which contains most of the C functions used in the examples. For all available API function please check the next chapter.
    
.. |rp.c| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/rp-api/api/src/rp.c" target="_blank">link to rp.c</a>
    


**Compiling and running on Red Pitaya board**

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

.. warning::

    Using a 1.04 or older OS version together with 2023.1 or newer GitHub ecosystem will result in compatibility isses. To address this please:
    - Use the latest GitHub ecosystem (master branch) together with Red Pitaya OS 2.00 or higher.
    - Use branch 2022.2 or older GitHub ecosystem together with 1.04 or older Red Pitaya OS.

Applications based on the API require a specific FPGA image to be loaded:

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


C and Python API functions
============================

.. note::

    Python API functions are only available on OS 2.00-23 or newer.

All API functions have an "int" return value. If the returned value is 0 (equal to *RP_OK*), then the function executed successfully.

The Python API functions are just wrappers that call the corresponding C API function. Consequently, they have exactly the same names, and always return an array where the first element is the C API function return value (successful or not), and the other elements represent the expected return values.

.. note::

    Please note that not all available API functions are in the "Available SCPI commands' list". If you want to check out all available API functions they are available here:
    - C - Check the |rp-api| section of the GitHub repository.
    - Python - Establish an :ref:`SSH <ssh>` connection to your Red Pitaya and look into the "/opt/redpitaya/lib/python" directoy.

.. |rp-api| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/rp-api" target="_blank">"rp-api" section of the GitHub repository</a>


More examples on how to control Red Pitaya using APIs can be found :ref:`here <examples>`.

.. _comC:

####################################
Compiling and running C applications
####################################

You can write simple C algorithms, make executables and run them on the Red Pitaya board. A list of
built in functions (APIs) is available providing full control over Red Pitaya board (signal generation and
acquisition, digital I/O control, communication: I2C, SPI, UART and other).
How to compile a C algorithm is shown in the instructions below, while a list of Examples is available
:ref:`here <list-of-supported-scpi-commands>`.

Note: When you copy the source code from our repository (following instructions bellow) you will also
copy all C examples to your Red Pitaya board. After that only the compiling step is needed.


**Compiling and running on Red Pitaya board**

When compiling on the target no special preparations are needed. A native toolchain is available directly on the Debian system.

First connect to your board over :ref:`SSH <ssh>` (replace the IP, the default password is `root`).

.. code-block:: shell-session

    ssh root@192.168.0.100

Now make a clone of the Red Pitaya Git repository and enter the project directory.

.. code-block:: shell-session

    git clone https://github.com/RedPitaya/RedPitaya.git
    cd RedPitaya

In order to compile one example just use the source file name without the `.c` extension.

.. code-block:: shell-session

    cd Examples/C
    make digital_led_blink

.. warning::

    Currently, there are some issues with combining the new ecosystem (GitHub release 2023.1) with non-UNIFIED OS versions. If you are using an OS version that is not UNIFIED OS, please use the 2022.2 relase of the ecosystem.


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

More examples about how to control Red Pitaya using APIs can be found :ref:`here <examples>`.

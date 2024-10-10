################################
General purpose input output
################################

GPIOs
=====

This document introduces handling of GPIO signals that are conected to Zynq-7000 PS EMIO block
and is accesible as general purpose input / output pins on Extension conector E1 with Linux gpio subsystem userspace interfaces.

There are two interfaces legacy sysfs interface and new character device based one.


PINS
====

Pins connected to the PL block require FPGA code to function. If the pin signals are wired directly (in the FPGA sources) from PS based EMIO signals to the FPGA pads,
then they can be managed using Linux drivers intended for the PS block. This is currently done with two fpga projects: classic and mercury.

Apropriate fpga bitstream can be applied using bash command.

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: shell-session

            redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    .. group-tab:: OS version 2.00

        .. code-block:: shell-session

            redpitaya> overlay.sh v0.94


Although the Zynq SoC provides 118 GPIO lines, only 16 are accessible to the user. They can be found on the extension connector E1, as pins DIO0_P to DIO7_P and DIO0_N to DIO7_N. These pins can be identified by different numbering/naming schemes:

#. the “line number”, used by the gpiod tools, libgpiod, and the underlying character device interface
#. the “sysfs number”, used by the legacy sysfs interface: this is the line number offset by 906
#. the “EMIO signal name”, documented in the device tree
#. the “GPIO number”, also documented in the device tree
#. the “pin name”, used in the SCPI interface, in the APIs (prefixed with ``RP_``), and throughout the Red Pitaya documentation.

This is the mapping between all these numbering/naming schemes:

+-------------+--------------+-----------------+------------------+-----------------+
| line number | sysfs number | EMIO signal     | GPIO number      | pin name        |
+=============+==============+=================+==================+=================+
| 62 – 69     | 968 – 975    | EMIO8  – EMIO15 | GPIO 0 – GPIO 7  | DIO0_P – DIO7_P |
+-------------+--------------+-----------------+------------------+-----------------+
| 70 – 77     | 976 – 983    | EMIO16 – EMIO23 | GPIO 8 – GPIO 15 | DIO0_N – DIO7_N |
+-------------+--------------+-----------------+------------------+-----------------+

The command ``gpioinfo``, from the package ``gpiod``, can be used to list the available lines, with their line number, EMIO signal name and GPIO number:

.. code-block:: shell-session

    redpitaya> gpioinfo | grep GPIO
            line  62: "EMIO8  (GPIO 0)" unused input active-high
            line  63: "EMIO9  (GPIO 1)" unused input active-high
            ...


Linux access to GPIO
====================

SYSFS access
--------------

This document is used as reference:
`Linux+GPIO+Driver <http://www.wiki.xilinx.com/Linux+GPIO+Driver>`_


Bash example for writing to and reading from pin DIO0_P (sysfs number 968):

.. code-block:: shell-session

   #export pin 968
   $ echo "968" > /sys/class/gpio/export
   #set direction to output
   $ echo "out" > /sys/class/gpio/gpio968/direction
   #set pin to LOW
   $ echo "0" > /sys/class/gpio/gpio968/value
   #set pin to HIGH
   $ echo "1" > /sys/class/gpio/gpio968/value
   #set pin direction to input
   $ echo "in" > /sys/class/gpio/gpio968/direction
   #output pin value
   $ cat /sys/class/gpio/gpio968/value
   #when done with pin you should unexport it with
   $ echo 968 > /sys/class/gpio/unexport


SYSFS GPIO C example is available at github: https://github.com/RedPitaya/RedPitaya/tree/master/Examples/gpio_sysfs



Character device access
------------------------

Character device usersace access to gpio kernel subsystem is confirmed working on kernels newer and including 4.8.

References: `GPIO for Engineers and Maker <http://elinux.org/images/9/9b/GPIO_for_Engineers_and_Makers.pdf>`_

.. raw:: html

    <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;">
        <iframe src="https://www.youtube.com/embed/lQRCDl0tFiQ" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
    </div>


The Linux kernel contains GPIO utilities in its `tools <https://github.com/torvalds/linux/tree/master/tools/gpio>`_ directory.

We isolated the sources and created a library from ``gpio-utils.c`` and
executables from other source files.

https://github.com/RedPitaya/gpio-utils

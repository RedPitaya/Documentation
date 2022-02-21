These instructions show how to use a JTAG cable to program a Red Pitaya directly from Xilinx Vivado. 
To do so we use Red Pitaya STEMlab 125-14, Ubuntu 20.04, Vivado 2020.1, Digilent JTAG-HS3 cable with a 14 to 6 pin adapter and Digilent Adept 2 software.

To start, get an appropriate JTAG cable. In these instructions, we use a Digilent JTAG-HS3 cable with a 14 to 6 pin adapter.
Digilent JTAG-HS2 may be used as well and might be more appropriate, as it uses a 6 pin connector that can connect directly to Red Pitaya's JTAG.
For a complete list of JTAG cables, supported by Vivado, see Xilinx UG908 - Programming and Debugging, appendix D. 
https://www.xilinx.com/content/dam/xilinx/support/documentation/sw_manuals/xilinx2021_2/ug908-vivado-programming-debugging.pdf

See if the JTAG cable is detected. In Ubuntu, that is done with:

.. code-block:: shell-session
    $ lsusb

JTAG-HS3 is displayed as a FTDI device.

.. figure:: lsusb.jpg

Now, install Digilent Adept 2 software from https://digilent.com/reference/software/adept/start. 
You will need both Utilities and Runtime. These are both available as .deb packages. If installing from GUI does not work, they can be installed using:

.. code-block:: shell-session
    $ sudo dpkg -i <path to package>

Once these packages are installed, you can check if the driver detects your adapter (only applies to Digilent cables):

.. code-block:: shell-session
    $ djtgcfg enum


.. figure:: driver_check.jpg

Now, open Vivado 2020.1, click Program and Debug -> Open Target -> Auto Connect. 

.. figure:: program_menu.jpg

This will display a Xilinx compatible JTAG cable in the Hardware window, under localhost.

.. figure:: cable.jpg

Now plug your cable onto Red Pitaya's JTAG connector. The pins are marked on the bottom side of Red Pitaya's PCB.

.. figure:: JTAG_pins.jpg

A Xilinx device should now appear in Vivado (on the detected cable). In this case, it's a xc7z010_1. 

.. figure:: program.jpg

Now, you can click Program Device. 

.. figure:: connected.jpg

A bitfile selector prompt appears and when a valid file is selected, Red Pitaya can be programmed.

.. figure:: file_select.jpg


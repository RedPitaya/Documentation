What is Red Pitaya?
#####################

Red Pitaya is a software-defined multi-instrument, digitiser and open-source FPGA development platform. Out of the box, it can be used as multiple software-defined instruments such as oscilloscope, signal generator, spectrum analyser and many more, all accessible as applications through a web interface.

The main feature of Red Pitaya is two fast analog inputs and two fast analog outputs with 125 Msps and 14 bit resolution. The voltage ranges are +-1 V or +-20 V for the inputs (depending on jumper settings) and +-1 V for the outputs. The board also has additional low-speed analog inputs and outputs, 16 digital GPIO pins, I2C, SPI, UART and CAN digital interfaces and eight programmable LEDs. At the heart of the Red Pitaya is the AMD Xilinx Zynq 7010 SoC with a dual-core ARM Cortex A9 processor. The board runs on the Ubuntu Linux operating system, which is stored on the micro SD card.

.. figure:: img/125-14_perspektiva-002-1024x526.png
   :width: 1000
   :align: center

The board is compatible with any computer operating system (Windows, Linux, MacOS). Ethernet is used to transfer data between the board and the computer.

In addition, the board can be remotely controlled using SCPI commands with Python, MATLAB or LabVIEW code running on the computer. Access to the board via SSH allows control of the Linux operating system, as well as custom C and Python programs to run directly on the Red Pitaya. A deep dive into the FPGA code and complete reprogramming is also on the table.

The Red Pitaya has been used everywhere. From the `International Space Station <https://content.redpitaya.com/blog/red-pitaya-an-open-source-software-measurement-and-control-board-used-in-spacecraft-atmosphere-monitor-for-nasa>`_ to `sorting tomatoes <https://content.redpitaya.com/blog/when-picking-and-sorting-tomatoes-become-a-matter-for-tech>`_, which is why we call it the "Swiss Army Knife for Engineers".

**The question is, how will you use it?**

- :ref:`Connection <ConnectSTEMlab>`
- :ref:`Applications <all_apps>`
- :ref:`Programming <programming>`
- :ref:`FPGA <build-fpga>`
- :ref:`Customization <customization>`
- `Shop <https://redpitaya.com/shop/>`_

**GitHub source code:**

- `Ecosystem and applications <https://github.com/RedPitaya/RedPitaya>`_
- `FPGA <https://github.com/RedPitaya/RedPitaya-FPGA>`_

**Use cases:**

- `Red Pitaya blog <https://content.redpitaya.com/blog>`_
.. _intro:

What is Red Pitaya?
#####################

Red Pitaya accelerates industrial innovation with compact, open-source, high-speed signal acquisition and processing boards and services designed to 
help companies reduce time-to-market and focus on what really matters - building better products, faster.

It combines the functionality of a software-defined multi-instrument, a digitiser and an open-source FPGA development platform. Out of the box, 
it can be used as multiple software-defined instruments such as an oscilloscope, signal generator, spectrum analyser and more,
all accessible as applications via a web interface.

The main features of Red Pitaya are:

* Two fast analog inputs and two fast analog outputs with 125 MS/s and 14 bit resolution,
* Input voltage range ±1 V or ±20 V (depending on jumper settings) and ±1 V output voltage range,
* Low-speed analog inputs and outputs,
* Digital GPIOs,
* I2C, SPI, UART and CAN digital interfaces,
* Programmable LEDs.

At the heart of Red Pitaya is the AMD Xilinx Zynq 7010 SoC with a dual-core ARM Cortex A9 processor.

Red Pitaya runs on the Ubuntu Linux operating system, which is stored on the micro SD card.

.. figure:: img/125-14_perspektiva-002-1024x526.png
    :width: 1000
    :align: center

As Ethernet is used to transfer data between the board and the computer, it is compatible with any computer operating system (Windows, Linux, MacOS).

The board can be programmed in several ways:

* Remotely via SCPI commands (Python, MATLAB or LabVIEW),
* C++ and Python programs running directly on the board itself,
* Completely customisable FPGA firmware that can be programmed using the AMD Xilinx Vivado IDE.

The Red Pitaya is used everywhere from the `International Space Station <https://content.redpitaya.com/blog/red-pitaya-an-open-source-software-measurement-and-control-board-used-in-spacecraft-atmosphere-monitor-for-nasa>`_ 
to `sorting tomatoes <https://content.redpitaya.com/blog/when-picking-and-sorting-tomatoes-become-a-matter-for-tech>`_, which is why we call it the "Swiss Army Knife for Engineers".

**How can Red Pitaya help me?**

* **Speed to Market** - Reduce development time with ready-to-integrate solutions to get my products to market faster.
* **Integration & Scalability** - Designed to fit seamlessly into industrial applications, from prototyping to production.
* **Cost-Effective Innovation** - Powerful hardware without the high cost of proprietary systems.
* **Open & Flexible** - Open source technology that gives engineers full control and customisation.


**Resources**

* :ref:`Connection <quickstart_connect>`
* :ref:`Applications <all_apps>`
* :ref:`Programming <programming>`
* :ref:`FPGA <fpga_top>`
* :ref:`Customization <customization>`
* |redpitaya-store|

**GitHub source code:**

* :rp-github:`Ecosystem and applications <RedPitaya>`
* :rp-github:`FPGA <RedPitaya-FPGA>`

**Use cases:**

* `Industrial usecases <{redpitaya_website}>`__
* `Red Pitaya blog <https://content.redpitaya.com/blog>`_

**FPGA lessons and tutorials**

* `Knowledge Base FPGA tutorials <https://learn.redpitaya.com/>`_
* :ref:`FPGA section <fpga_top>`

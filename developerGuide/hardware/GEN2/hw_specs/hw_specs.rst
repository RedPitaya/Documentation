.. _hw_specs_gen2:

#######################################
Common hardware specifications (Gen 2)
#######################################

.. note::

    **This page is currently under construction.** All relevant information will be added before the official Gen 2 release.
    Please check back later for updates.

.. note::

    Looking for :ref:`Gen 1 hardware specifications? <hw_specs_gen1>`

.. TODO GEN 2 measurements and update text

In this section you can find common hardware specifications for all Red Pitaya board models. The measurements were performed on the **STEMlab 125-14 Gen2 Z7020 Pro** board and are the same for all Gen 2 board models (except where specifically stated). Any future measurements will be added to this section.

Please refer to the board model documentation for schematics, relevant components, mechanical specifications, and 3D models. Please note that the full hardware schematics for the Red Pitaya boards are not available. While Red Pitaya has open-source code, the hardware schematics are not open source. However, development schematics with information regarding hardware configuration, FPGA pin connections, and similar, are available.

.. note::

    The information provided by Red Pitaya d.o.o. is believed to be accurate and reliable. However, no liability is accepted for its use. Please note that the contents may be subject to change without prior notice. 


.. contents:: **Index**
   :local:
   :backlinks: none

|


Power Supply
===============

All Red Pitaya Gen2 boards use the same power supply:

* 5 V, 3 A USB-C power supply.


.. note::

    It is important to note that Red Pitaya boards should **not** be powered by a power supply that provides less power than specified above or has very thin power wires. Doing so may result in abnormal behaviour of the device, causing reboots and network disconnections.
    Similarly, the Red Pitaya board may malfunction if powered directly from a USB port on a PC (due to insufficient current supply) or hub that cannot provide sufficient power or if a faulty power cable is used.
    
    Furthermore, the use of an unapproved power supply may impair performance or cause damage to the product.

.. warning::

    Power supply precautions:

    * *STEMlab 125-14 Gen2*, *STEMlab 125-14 Gen2 Pro* and *STEMlab 125-14 Gen2 Z7020 Pro* may only be powered by an isolated external power supply of 5 Volts DC with a maximum current of 3 A.
      The recommended model is **Too be determined**. Any other external power supply used with Red Pitaya must comply with the relevant regulations and standards applicable in the country of use.

.. TODO add recommended Gen2 power supply model

SD card size
==============

We recommend using an SD card with a minimum of 32 GB of space for Red Pitaya Gen 2 boards. The SD card should be Class 10 or higher.


Compatible OS versions
=======================

Red Pitaya Gen 2 boards are compatible with OS versions **2.07-IN DEV** or higher and should not be used with older versions of the Red Pitaya OS.


Fast analog IO
===============

.. warning::

    All inputs and outputs available through SMA connectors share a common ground connected to the power supply ground.


.. toctree::
    :maxdepth: 3

    fastIO


Extension connectors
======================

.. toctree::
    :maxdepth: 3

    extent


Board operation notice
=======================

Operating temperature range
----------------------------

Red Pitaya devices have an operating temperature range from 0°C to +55°C and a storage temperature range of -20°C to +85°C. For industrial grade Gen 2 boards, with operating temperature range from -40°C to +85°C, please contact us on info@redpitaya.com.

* Should be operated in normal conditions and should not be covered.
* Are intended for indoor use at a maximum altitude of 2000 m, pollution severity 2 and relative humidity less than 90%.
* Are intended for use with low voltage power sources and signals and should not be used in direct connection with voltages exceeding 30 Volts.

.. note::

    The operating temperature range (0°C to +55°C) applies if the board is using the included heatsink. Replacing the heatsink with a larger one or implementing additional cooling solutions will increase the operating range of the board.
    
    When using custom cooling solutions, please note that the Zynq temperature must not exceed +85°C. Additionaly, the Red Pitaya OS has a software temperature protection that will shut down the board if it gets too hot. This is meant to protect the board from overheating and damage.
    If a custom cooling solution is used, please check that the software temperature protection is not preventing proper operation.



Required hardware
------------------

The following items are required for proper board operation. They are already included in each of the Red Pitaya kits available on our |WEBstore|:

* 16 GB (up to 32 GB) Class 10 micro SD card with pre-loaded Red Pitaya OS.
* Ethernet cable.
* USB-C power supply (5 V, 3 A).

Additional items required that are not included in the Red Pitaya kits:

* A computer with an internet browser (Google Chrome is recommended).
* Router with DHCP server enabled and access to the internet.


.. |WEBstore| raw:: html

   <a href="https://redpitaya.com/shop/" target="_blank">WEB store</a>


.. _status_leds_gen2:

Status LED Description
------------------------

+---------+--------------------------------------------------------------------------------------------------------------+
| Colour                                                                                                                 |
+=========+==============================================================================================================+
| blue    | FPGA bitstream status (in normal operation, this LED is lit, indicating that the FPGA bitstream              |
|         | has been successfully loaded).                                                                               |
+---------+--------------------------------------------------------------------------------------------------------------+
| green   | Power supply status (in normal operation, this LED is lit, indicating that all power supplies                |
|         | on Red Pitaya are working properly).                                                                         |
+---------+--------------------------------------------------------------------------------------------------------------+
| red     | Heartbeat blink pattern indicating CPU load (in normal operation, this LED will blink continuously).         |
+---------+--------------------------------------------------------------------------------------------------------------+
| orange  | | SD card access indicator (in normal operation, this LED will flash sporadically at slow intervals).        |
|         | | If the **E3 add-on board** is present, the internal watchdog timer is wired to the orange LED instead      |
|         | | (the LED will blink continuously).                                                                         |
+---------+--------------------------------------------------------------------------------------------------------------+

.. note::

    When the E3 add-on board is connected to a Gen 2 board the orange LED functionality will be switched to show the watchdog timer status instead of the SD card access.


Heating
--------

It is not uncommon for the board to reach temperatures of 60 degrees Celsius or above during operation (please refer to the :ref:`Cooling options <cooling_options_gen2>` section for further details).

.. note::

    Please note that some parts of the board, particularly the heatsink, may become hot during and after operation. To avoid injury, please do not touch them.

.. note::

    It is imperative that a heatsink is installed and that the board is operated on a flat surface devoid of any obstructions that could impede airflow.
    In order to mitigate the effects of elevated ambient temperatures and reduced pressure conditions within enclosures, it is necessary to implement an effective ventilation strategy.
    The product's operational functionality is automatically disabled at elevated temperatures to prevent any potential damage.

.. _cooling_options_gen2:

Cooling options
-----------------

For enhanced cooling, we suggest utilising a 30 mm or 25 mm fan. The board's power connector can be employed to power the fan, however, it is important to note that it provides a maximum of 5 V. The power connector is situated between the micro-SD socket and the host USB connector.

.. TODO add cooling options for Gen 2 boards.


Board dimensions
===================

Please refer to the technical drawings in the Red Pitaya board specifications for exact board dimensions.

* :ref:`STEMlab 125-14 Gen2 <schematics_125_14_gen2>`.
* :ref:`STEMlab 125-14 Gen2 Pro <schematics_125_14_gen2_pro>`.
* :ref:`STEMlab 125-14 Gen2 Z7020 Pro <schematics_125_14_gen2_z7020_pro>`.






.. _hw_specs_gen1:

#######################################
Common hardware specifications (Gen 1)
#######################################

.. note::

    Looking for :ref:`Gen 2 hardware specifications? <hw_specs_gen2>`

In this section you can find common hardware specifications for all Red Pitaya board models. The measurements were performed on the **STEMlab 125-14** (Gen 1) board, but are similar on the other board models (except where specifically stated). Any future measurements will be added to this section.

Please refer to the board model documentation for schematics, relevant components, mechanical specifications, and 3D models. Please note that the full hardware schematics for the Red Pitaya boards are not available. While Red Pitaya has open-source code, the hardware schematics are not open source. However, development schematics with information regarding hardware configuration, FPGA pin connections, and similar, are available.

.. note::

    The information provided by Red Pitaya d.o.o. is believed to be accurate and reliable. However, no liability is accepted for its use. Please note that the contents may be subject to change without prior notice. 


.. contents:: **Index**
   :local:
   :backlinks: none

|


Power Supply
===============

.. tabs::

    .. tab:: 125-14, 122-16, 125-14 4-Input, 125-14 Z7020, 125-10 (Discontinued)

        * 5 V / 2 A micro USB power supply.
      
    .. tab:: 250-12

        * 12 V / 1 A power adapter with jack connector.

.. note::

    It is important to note that Red Pitaya boards should **not** be powered by a power supply that provides less power than specified above or has very thin power wires. Doing so may result in abnormal behaviour of the device, causing reboots and network disconnections.
    Similarly, the Red Pitaya board may malfunction if powered directly from a USB port on a PC (due to insufficient current supply) or hub that cannot provide sufficient power or if a faulty power cable is used.
    
    Furthermore, the use of an unapproved power supply may impair performance or cause damage to the product.

.. warning::

    Power supply precautions:

    * STEMlab 125-14, STEMlab 125-14 Z7020, STEMlab 125-14 4-Input, SDRlab 122-16 and STEMlab 125-10 may only be powered by an isolated external power supply of 5 Volts DC with a maximum current of 2 A.
      The recommended model is KA23-0502000DES. Any other external power supply used with Red Pitaya must comply with the relevant regulations and standards applicable in the country of use.
    * SIGNALlab 250-12 may only be powered by an original KA2401A 24 V/1 A isolated power supply or via the RJ45 Ethernet connector (PoE version only).


SD card size
==============

We recommend a minimum of 16 GB SD card for Red Pitaya OS versions 2.00 and above. With OS versions 1.04, a minimum 8 GB card is recommended. For older OS versions (0.9) you may be able to get away with a 4 GB SD card.


Fast analog IO
===============

.. warning::

    All inputs and outputs available through SMA and BNC connectors share a common ground connected to the power supply ground.


.. toctree::
    :maxdepth: 3

    fastIO


Extension connectors
======================

.. toctree::
    :maxdepth: 3

    extent

.. _board_operation_gen1:

Board operation notice
=======================

Operating temperature range
----------------------------

Red Pitaya devices have an operating temperature range from 0°C to +55°C and a storage temperature range of -20°C to +85°C.

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

Additional items required that are not included in the Red Pitaya kits:

* A computer with an internet browser (Google Chrome is recommended).
* Router with DHCP server enabled and access to the internet.

.. note::

   We recommend a minimum of 16 GB SD card for Red Pitaya OS versions 2.00 and above. With OS versions 1.04, a minimum 8 GB card is recommended. For older OS versions (0.9) you may be able to get away with a 4 GB SD card.

.. |WEBstore| raw:: html

   <a href="https://redpitaya.com/shop/" target="_blank">WEB store</a>


.. _status_leds:

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
| orange  | SD card access indicator (in normal operation, this LED will flash sporadically at slow intervals).          |
+---------+--------------------------------------------------------------------------------------------------------------+


Heating
--------

It is not uncommon for the board to reach temperatures of 60°C or above during operation (please refer to the `Cooling options`_ section for further details).

.. note::

    Please note that some parts of the board, particularly the heatsink, may become hot during and after operation. To avoid injury, please do not touch them.

.. note::

    It is imperative that a heatsink is installed and that the board is operated on a flat surface devoid of any obstructions that could impede airflow.
    In order to mitigate the effects of elevated ambient temperatures and reduced pressure conditions within enclosures, it is necessary to implement an effective ventilation strategy.
    The product's operational functionality is automatically disabled at temperatures of 85°C to prevent any potential damage.



Cooling options
-----------------

For enhanced cooling, we suggest utilising one or more of the following options:

* :ref:`Gen 1 Aluminium case <alucase>` - to improve heat dissipation and protect the board from external factors.
* :ref:`Gen 1 Heatsink interface <heatsink>` - to improve heat dissipation and connect the board to an external heatsink.
* External cooling fan - to increase airflow around the board.

You can utilise a 30 mm or 25 mm fan. The board's power connector can be employed to power the fan, however, it is important to note that it provides a maximum of 5 V. The power connector is situated between the micro-SD socket and the host USB connector.

.. figure:: img/cooling/cooling-powerPin.jpg
    :align: center
    :width: 800

    Red Pitaya power connector. Image via `blog <https://rroeng.blogspot.com/2014/03/keep-your-red-pitaya-cool.html>`_ (with permission from Jacek Radzikowski).


.. note::

    Please be advised that the power connector is a standard 2-pin 0.1" connector, which supplies only 5 V.


Assembly
~~~~~~~~~~

1. Replace the fans' 0.05" plug with a standard 2-pin 0.1" connector.
 
#. Connect the black wire to the negative terminal and the red wire to the positive terminal. Markings are visible
   in the picture below.
    
#.  Attaching the fan to the heat sink using two screws as shown in the picture below. 
 
.. image:: img/cooling/cooling-screwon.jpg
   :align: center
   :width: 800

.. figure:: img/cooling/cooling-topdown.jpg 
   :align: center
   :width: 800

   Red Pitaya with an attached fan.


Measurements
~~~~~~~~~~~~~

.. figure:: img/cooling/cooling-result.png
   :align: center

   Temperature measured with the fan turned off and on combined with low and high CPU load.

Images via `blog <https://rroeng.blogspot.com/2014/03/keep-your-red-pitaya-cool.html>`_ (with permission from Jacek Radzikowski).



Board dimensions
===================

Please refer to the technical drawings in the Red Pitaya board specifications for exact board dimensions.

* :ref:`STEMlab 125-14 Gen 1 <schematics_125_14>`
* :ref:`STEMlab 125-14 Z7020 <schematics_125_14_Z7020>`
* :ref:`STEMlab 125-14 4-Input <schematics_125_14_4_IN>`
* :ref:`SDRlab 122-16 <schematics_122_16>`
* :ref:`STEMlab 125-10 <schematics_125_10>` (Discontinued)
* :ref:`SIGNALlab 250-12 <schematics_250_12>`



.. _qspi_chip:

External booting options
=========================

Red Pitaya Gen 1 boards can be booted from an on-board QSPI flash memory chip or from an external SD card. The QSPI flash memory chip is not populated by default on Red Pitaya boards, but it can be added later if needed. The QSPI flash memory chip is used for booting the board and can be used to store the operating system and other files.

Please note that the `QSPI chip <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_, located on the top layer of the board just to the right of TP1A under the heatsink (:ref:`STEMlab 125-14 schematics <schematics_125_14>`), is not populated by default on Red Pitaya boards. For further information on board modifications, please contact support@redpitaya.com or info@redpitaya.com.

.. warning::

    Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.




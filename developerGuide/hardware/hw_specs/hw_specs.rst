.. _hw_specs:

################################
Common hardware specifications
################################

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

    .. tab:: 125-14, 122-16, 125-14 4-Input, 125-10 (Discontinued)

        - 5 V / 2 A micro USB power supply,
      
    .. tab:: 250-12

        - 12 V / 1 A power adapter with jack connector,

.. note::

    It is important to note that Red Pitaya boards should not be powered by a power supply that provides less power than specified above or has very thin power wires. Doing so may result in abnormal behaviour of the device, causing reboots and network disconnections.
    Similarly, the Red Pitaya board may malfunction if powered directly from a USB port on a PC (due to insufficient current supply) or hub that cannot provide sufficient power or if a faulty power cable is used.
    
    Furthermore, the use of an unapproved power supply may impair performance or cause damage to the product.


Fast analog IO
===============

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

Required hardware
------------------

The following items are required for proper board operation. They are already included in each of the Red Pitaya kits available on our |WEBstore|:

* 16 GB (up to 32 GB) Class 10 micro SD card with pre-loaded Red Pitaya OS,
* Ethernet cable.

Additional items required that are not included in the Red Pitaya kits:

*  A computer with an internet browser (Google Chrome is recommended),
*  Router with DHCP server enabled and access to the internet.

.. note::

   We recommend a minimum of 16 GB SD card for Red Pitaya OS versions 2.00 and above. With OS versions 1.04, a minimum 8 GB card is recommended. For older OS versions (0.9) you may be able to get away with a 4 GB SD card.

.. |WEBstore| raw:: html

   <a href="https://redpitaya.com/shop/" target="_blank">WEB store</a>


.. _status_leds:

Status LED Description
------------------------

======  ===============================================================================================================
Colour
======  ===============================================================================================================
blue    FPGA bitstream status (in normal operation, this LED is turned on, indicating the FPGA bitstream
        was successfully loaded).
green   Power supply status (in normal operation, this LED is turned on, indicating that all power supplies
        on Red Pitaya are working properly).
red     The heartbeat blinking pattern should show CPU load (in normal operation, this LED is blinking constantly).
orange  SD card access indicator (In normal operation, this LED blinks sporadically in slow intervals).
======  ===============================================================================================================


Heating
--------

It is not uncommon for the board to reach temperatures of 60 degrees Celsius or above during operation (please refer to the `Cooling options` section for further details).

.. note::

    Please note that some parts of the board, particularly the heatsink, may become hot during and after operation. To avoid injury, please do not touch them.

.. note::

    It is imperative that a heatsink is installed and that the board is operated on a flat surface devoid of any obstructions that could impede airflow.
    In order to mitigate the effects of elevated ambient temperatures and reduced pressure conditions within enclosures, it is necessary to implement an effective ventilation strategy.
    The product's operational functionality is automatically disabled at elevated temperatures to prevent any potential damage.


Cooling options
-----------------

For enhanced cooling, we suggest utilising a 30 mm or 25 mm fan. The board's power connector can be employed to power the fan, however, it is important to note that it provides a maximum of 5 V. The power connector is situated between the micro-SD socket and the host USB connector.

.. figure:: img/cooling/cooling-powerPin.jpg
    :width: 50%
    :align: center

    Red Pitaya power connector. Image via `blog <https://rroeng.blogspot.com/2014/03/keep-your-red-pitaya-cool.html>`_ (with permission from Jacek Radzikowski).


.. note::

    Please be advised that the power connector is a standard 2-pin 0.1" connector, which supplies only 5 V.


.. toctree::
   :maxdepth: 2

   cooling


Board dimensions
===================

Please refer to the technical drawings in the Red Pitaya board specifications for exact board dimensions.

.. _qspi_chip:

QSPI 
========

Please note that the `QSPI chip <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_, located on the top layer of the board just to the right of TP1A under the heatsink (:ref:`STEMlab 125-14 schematics <schematics_125_14>`), is not populated by default on Red Pitaya boards. For further information on board modifications, please contact support@redpitaya.com or info@redpitaya.com.

.. warning::

    Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.




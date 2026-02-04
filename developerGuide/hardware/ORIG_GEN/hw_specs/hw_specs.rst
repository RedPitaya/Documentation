.. _hw_specs_orig_gen:

#################################################
Common hardware specifications (Original Gen)
#################################################

.. note::

    Looking for :ref:`Gen 2 hardware specifications? <hw_specs_gen2>`

This section contains information that applies to **all** Red Pitaya Original Generation boards. For board-specific specifications, measurements, power requirements, and 
detailed technical data, please refer to the individual product documentation pages.

Please note that the full hardware schematics for the Red Pitaya boards are not available. While Red Pitaya has open-source code, the hardware schematics are not open 
source. However, development schematics with information regarding hardware configuration, FPGA pin connections, and similar, are available.

.. note::

    The information provided by Red Pitaya d.o.o. is believed to be accurate and reliable. However, no liability is accepted for its use. Please note that the contents 
    may be subject to change without prior notice. 


.. contents:: **Index**
   :local:
   :backlinks: none

|


Power supply (varies by board model)
======================================

Original Generation boards have different power supply requirements depending on the model:

* **STEMlab 125-14, SDRlab 122-16, STEMlab 125-14 variants**: 5V, 2A Micro USB power supply
* **SIGNALlab 250-12**: 12V, 1A power adapter with jack connector (or PoE for PoE version)

.. note::

    It is important to note that Red Pitaya boards should **not** be powered by a power supply that provides less power than specified above or has very thin power wires. 
    Doing so may result in abnormal behaviour of the device, causing reboots and network disconnections. Similarly, the Red Pitaya board may malfunction if powered directly 
    from a USB port on a PC (due to insufficient current supply) or hub that cannot provide sufficient power or if a faulty power cable is used.
    
    Furthermore, the use of an unapproved power supply may impair performance or cause damage to the product.

.. warning::

    Power supply precautions:

    * STEMlab 125-14, STEMlab 125-14 Z7020, STEMlab 125-14 4-Input, SDRlab 122-16 and STEMlab 125-10 may only be powered by an isolated external power supply of 5 Volts DC 
      with a maximum current of 2 A. The recommended model is KA23-0502000DES.
    * SIGNALlab 250-12 may only be powered by an original KA2401A 24 V/1 A isolated power supply or via the RJ45 Ethernet connector (PoE version only).
    * Any other external power supply used with Red Pitaya must comply with the relevant regulations and standards applicable in the country of use.

|


SD card size (all Original Gen boards)
========================================

We recommend a minimum of **16 GB** SD card for Red Pitaya OS versions 2.00 and above. With OS versions 1.04, a minimum 8 GB card is recommended. For older OS versions (0.9) 
you may be able to get away with a 4 GB SD card.

|


Required hardware (all Original Gen boards)
=============================================

The following items are required for proper board operation. They are already included in each of the Red Pitaya kits available on our |WEBstore|:

* Micro SD card with pre-loaded Red Pitaya OS (recommended 16 GB Class 10 for OS 2.00+).
* Ethernet cable.
* Power supply (specifications vary by board model - see above).

Additional items required that are not included in the Red Pitaya kits:

* A computer with an internet browser (Google Chrome is recommended).
* Router with DHCP server enabled and access to the internet.

.. |WEBstore| replace:: :rp-store:`WEB store <>`


.. _status_leds:

Status LED description (all Original Gen boards)
==================================================

+---------+--------------------------------------------------------------------------------------------------------------+
| Colour  | Function                                                                                                     |
+=========+==============================================================================================================+
| Blue    | FPGA bitstream status (in normal operation, this LED is lit, indicating that the FPGA bitstream              |
|         | has been successfully loaded).                                                                               |
+---------+--------------------------------------------------------------------------------------------------------------+
| Green   | Power supply status (in normal operation, this LED is lit, indicating that all power supplies                |
|         | on Red Pitaya are working properly).                                                                         |
+---------+--------------------------------------------------------------------------------------------------------------+
| Red     | Heartbeat blink pattern indicating CPU load (in normal operation, this LED will blink continuously).         |
+---------+--------------------------------------------------------------------------------------------------------------+
| Orange  | SD card access indicator (in normal operation, this LED will flash sporadically at slow intervals).          |
+---------+--------------------------------------------------------------------------------------------------------------+

|


Operating temperature and safety
==================================

Operating temperature range
----------------------------

Red Pitaya Original Generation devices have an operating temperature range from 0°C to +55°C and a storage temperature range of -20°C to +85°C.

* Should be operated in normal conditions and should not be covered.
* Are intended for indoor use at a maximum altitude of 2000 m, pollution severity 2 and relative humidity less than 90%.
* Are intended for use with low voltage power sources and signals and should not be used in direct connection with voltages exceeding 30 Volts.

.. note::

    The operating temperature range (0°C to +55°C) applies if the board is using the included heatsink. Replacing the heatsink with a larger one or implementing additional cooling solutions will increase the operating range of the board.
    
    When using custom cooling solutions, please note that the Zynq temperature must not exceed +85°C. Additionally, the Red Pitaya OS has a software temperature protection that will shut down the board if it gets too hot. This is meant to protect the board from overheating and damage.
    If a custom cooling solution is used, please check that the software temperature protection is not preventing proper operation.


Heating and cooling
--------------------

It is not uncommon for Red Pitaya boards to reach temperatures of 60°C or above during operation.

.. note::

    Please note that some parts of the board, particularly the heatsink, may become hot during and after operation. To avoid injury, please do not touch them.

.. note::

    It is imperative that a heatsink is installed and that the board is operated on a flat surface devoid of any obstructions that could impede airflow.
    In order to mitigate the effects of elevated ambient temperatures and reduced pressure conditions within enclosures, it is necessary to implement an effective ventilation strategy.
    The product's operational functionality is automatically disabled at temperatures of 85°C to prevent any potential damage.


Cooling options
^^^^^^^^^^^^^^^^^

For enhanced cooling, we suggest utilising one or more of the following options:

* :ref:`Original Aluminium case <alucase>` - to improve heat dissipation and protect the board from external factors.
* :ref:`Original Heatsink interface <heatsink>` - to improve heat dissipation and connect the board to an external heatsink.
* External cooling fan - to increase airflow around the board.

You can utilise a 30 mm or 25 mm fan. The board's power connector can be employed to power the fan, however, it is important to note that it provides a maximum of 5 V. The power connector is situated between the micro-SD socket and the host USB connector.

.. figure:: img/cooling/cooling-powerPin.jpg
    :align: center
    :width: 800

    Red Pitaya power connector. Image via `blog <https://rroeng.blogspot.com/2014/03/keep-your-red-pitaya-cool.html>`_ (with permission from Jacek Radzikowski).


.. note::

    Please be advised that the power connector is a standard 2-pin 0.1" connector, which supplies only 5 V.


Fan assembly example
~~~~~~~~~~~~~~~~~~~~~

1. Replace the fans' 0.05" plug with a standard 2-pin 0.1" connector.
 
#. Connect the black wire to the negative terminal and the red wire to the positive terminal. Markings are visible
   in the picture below.
    
#. Attach the fan to the heat sink using two screws as shown in the picture below. 
 
.. image:: img/cooling/cooling-screwon.jpg
   :align: center
   :width: 800

.. figure:: img/cooling/cooling-topdown.jpg 
   :align: center
   :width: 800

   Red Pitaya with an attached fan.


Temperature measurements
~~~~~~~~~~~~~~~~~~~~~~~~~

.. figure:: img/cooling/cooling-result.png
   :align: center

   Temperature measured with the fan turned off and on combined with low and high CPU load.

Images via `blog <https://rroeng.blogspot.com/2014/03/keep-your-red-pitaya-cool.html>`_ (with permission from Jacek Radzikowski).

|


Fast analog inputs and outputs (all Original Gen boards)
==========================================================

.. warning::

    All inputs and outputs available through SMA and BNC connectors share a common ground connected to the power supply ground.

.. warning::
    
    The SMA connectors on the cables connected to Red Pitaya must comply with the MILC39012 standard. The centre pin must be of suitable length, otherwise the SMA connector installed in Red Pitaya will mechanically damage the SMA connector.
    The centre pin of the SMA connector on Red Pitaya will lose contact with the board and the board will not be repairable due to the mechanical damage (separation of the pad from the board).


Jumper settings
----------------

Voltage input ranges are set by jumpers located behind each input SMA connector. Gain can be adjusted independently for both input channels.

.. figure:: img/jumpers/Jumper_settings.png
    :align: center

    Jumper settings diagram

.. figure:: img/jumpers/Jumper_settings_photo.png
    :align: center

    Jumper setting positions:
    
    - **Left setting (LV)** adjusts to ±1 V full scale
    - **Right setting (HV)** adjusts to ±20 V full scale


.. warning::
    
    Please note that jumper settings are limited to the described positions. Any other configuration or use of different jumper types may damage the product and void the warranty.


Jumper orientation (important)
--------------------------------

**The position and orientation of the jumpers can significantly affect measurement accuracy.** The jumpers are internally connected to a small metal plate which acts as a capacitor and affects the overall capacitance, which in turn affects the input impedance.

If the jumpers are moved from an incorrect to a correct position, **calibration is strongly recommended** as the input capacitance depends on jumper settings and may vary between positions.


1. **The position of the jumper bumps must be as shown in the diagram.** Due to the non-symmetrical nature of the jumpers and their latches, we advise installing them with the latch on the outer side to avoid any issues with difficult-to-remove jumpers.

    .. figure:: img/jumpers/Jumper_position_Note.png
        :align: center


2. **Once installed, the jumpers should be positioned so that the metal part is not visible.** Please refer to the example of the STEMlab 125-14 4-Input in the pictures below for guidance.

    .. figure:: img/jumpers/Jumper_position_4IN_0.png
        :align: center
        :width: 700 px

    .. figure:: img/jumpers/Jumper_position_4IN_1.png
        :align: center
        :width: 700 px


**Impact of incorrect jumper placement:**

Incorrect jumper placement can cause the front part of acquired square wave signals to be overshot or undercut. This is shown in the figure below.

.. figure:: img/jumpers/Jumper_position_wrong_signal.jpg
    :align: center
    :width: 800

    If the jumpers are not set correctly, the step response will be under-compensated.

With the jumper pins correctly placed, the same waveform looks much better:

.. figure:: img/jumpers/Jumper_position_correct_signal.jpg
    :align: center
    :width: 800

    Correctly positioned jumpers result in proper step response.

|


Extension connectors (all Original Gen boards)
================================================

All Original Generation boards feature extension connectors (E1 and E2) using the same physical format:

**Physical specifications:**

* **Connector type**: 2 x 13 pins IDC 2.54 mm pitch
* **Digital I/O voltage levels**: 3.3V LVCMOS33
* **Power rails**: +5V, +3.3V, -3.4V

**Current limitations:**

* 500 mA for +5V (shared between extension module and USB devices)
* 500 mA for +3.3V (shared between extension module and USB devices)
* 50 mA for -3.4V supply

**Board-specific differences:**

Pin assignments, available features, and FPGA connections vary significantly by board model:

* **STEMlab 125-14**: 16 digital I/Os, 4 slow ADCs, 4 slow DACs, SPI/UART/I2C/CAN
* **SDRlab 122-16**: 22 digital I/Os, 4 slow ADCs, 4 slow DACs, SPI/UART/I2C/CAN
* **SIGNALlab 250-12**: 19 digital I/Os, 4 slow ADCs, 4 slow DACs, SPI/UART/I2C/CAN/USB
* **STEMlab 125-14 4-Input**: 22 digital I/Os, 4 slow ADCs, 4 slow DACs, SPI/UART/I2C/CAN
* **STEMlab 125-14 Z7020**: Similar to STEMlab 125-14 with different FPGA pin assignments

For complete pinout diagrams, FPGA pin numbers, and detailed specifications, please refer to your specific board's documentation page.

|


Optional features
==================

.. _qspi_chip:

External booting options
-------------------------

Red Pitaya original boards can be booted from an on-board QSPI flash memory chip or from an external SD card. The QSPI flash memory chip is not populated by default on Red Pitaya boards, but it can be added later if needed. The QSPI flash memory chip is used for booting the board and can be used to store the operating system and other files.

Please note that the `QSPI chip <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_, located on the top layer of the board just to the right of TP1A under the heatsink (:ref:`STEMlab 125-14 schematics <schematics_125_14>`), is not populated by default on Red Pitaya boards. For further information on board modifications, please contact support@redpitaya.com or info@redpitaya.com.

.. warning::

    Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.

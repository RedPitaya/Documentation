.. _click_shield:

##############
Click Shield
##############

.. figure:: img/red-pitaya-click-shield-banner.jpg
    :width: 900
    :align: center

The Red Pitaya Click Shield extension module enables users to extend Red Pitaya hardware with two |Click Boards| and power them and the Red Pitaya from either an external USB C power adapter or a 12-24 Volt external power supply. Using U.FL patch cables, the shield can also be utilised for high-performance clock and trigger synchronisation between multiple Red Pitaya units and/or other devices. An external reference clock can also be connected to the shield through the U.FL connector.


**Highlights:**

* Two |mikroBUS| sockets, allowing interface with more than 1500 |Click Boards| devices. 
* High-performance clock and trigger synchronisation between multiple Red Pitaya units or other devices.
* Powering Red Pitaya through an external power supply (12-24 V or via USB-C connector). 


|click_shield_front| |click_shield_back|

.. |click_shield_front| image:: img/red-pitaya-click-shield-front.png
    :width: 450

.. |click_shield_back| image:: img/red-pitaya-click-shield-back.png
    :width: 450

|

What is in the box?
=====================

* 1x Red Pitaya Click Shield.
* 3x U.FL to U.FL patch cable for trigger and clock synchronisation.


.. _click_shield_compatibility:

Compatibility
===============

.. note::

    Depending on which Red Pitaya board model you are using, some features of the Red Pitaya Click Shield might not be applicable.

The clock synchronisation is compatible only with the following board models:

* :ref:`STEMlab 125-14 PRO Gen 2 <top_125_14_pro_gen2>`.
* :ref:`STEMlab 125-14 PRO Z7020 Gen 2 <top_125_14_pro_z7020_gen2>`.
* :ref:`STEMlab 125-14 External Clock <top_125_14_EXT>` [#f1]_.
* :ref:`SDRlab 122-16 External Clock <top_122_16_EXT>`.
* :ref:`STEMlab 125-14 4-Input <top_125_14_4-IN>`.

Switching between the External and Internal clock is available only on the STEMlab 125-14 4-Input (CLK SEL pin) but will be compatible with all future Red Pitaya board redesigns.

Trigger synchronisation and |Click Boards| are compatible with all board models.

Here is a compatibility table:

.. table::
    :widths: 10 18 18
    :align: center

    +------------------------------------+--------------------------------------+--------------------------------------+
    | Click Shield Feature Compatibility Gen 2                                                                         |
    +====================================+======================================+======================================+
    |                                    | **STEMlab 125-14 Gen 2**             | **STEMlab 125-14 Pro Gen 2** |br|    |
    |                                    |                                      | **STEMlab 125-14 Pro Z7020 Gen 2**   |
    |                                    |                                      |                                      |
    +------------------------------------+--------------------------------------+--------------------------------------+
    | Click Boards (microBus)            | Yes                                  | Yes                                  |
    +------------------------------------+--------------------------------------+--------------------------------------+
    | High speed Clock Synchronisation   | No                                   | Yes                                  |
    +------------------------------------+--------------------------------------+--------------------------------------+
    | Powering options                   | Yes                                  | Yes                                  |
    +------------------------------------+--------------------------------------+--------------------------------------+
    | Clk Switch (Internal/External)     | No                                   | Yes                                  |
    +------------------------------------+--------------------------------------+--------------------------------------+

.. table::
    :widths: 10 18 18 18 18 18
    :align: center

    +------------------------------------+------------------------------+------------------------------+----------------------------------+------------------------------+------------------------------+
    | Click Shield Feature Compatibility Original Gen                                                                                                                                                   |
    +====================================+==============================+==============================+==================================+==============================+==============================+
    |                                    | **STEMlab 125-14** |br|      | **SDRlab 122-16**            | **STEMlab 125-14 ext. clk** |br| | **STEMlab 125-14 4-Input**   | **SIGNALlab 250-12**         |
    |                                    | **STEMlab 125-14 LN** |br|   |                              | **SDRlab 122-16 ext. clk**       |                              |                              |
    |                                    | **STEMlab 125-14-Z7020-LN**  |                              |                                  |                              |                              |
    +------------------------------------+------------------------------+------------------------------+----------------------------------+------------------------------+------------------------------+
    | Click Boards (microBus)            | Yes                          | Yes                          | Yes                              | Yes                          | Yes                          |
    +------------------------------------+------------------------------+------------------------------+----------------------------------+------------------------------+------------------------------+
    | High speed Clock Synchronisation   | No                           | No                           | Yes                              | Yes                          | No                           |
    +------------------------------------+------------------------------+------------------------------+----------------------------------+------------------------------+------------------------------+
    | Powering options                   | Yes                          | Yes                          | Yes                              | Yes                          | No                           |
    +------------------------------------+------------------------------+------------------------------+----------------------------------+------------------------------+------------------------------+
    | Clk Switch (Internal/External)     | No                           | No                           | No                               | Yes                          | No                           |
    +------------------------------------+------------------------------+------------------------------+----------------------------------+------------------------------+------------------------------+

|

What are Click Boards?
=======================

|Click Boards| by |MIKROE| are small add-on boards designed to simplify the process of developing electronic projects by providing a pre-built and tested module with specific functionality. Currently, over 1500 click boards are available in different categories, including communication, display, sensors, storage, motor control, mixed signals, and others.

.. figure:: img/click-boards-header-banner.jpg
    :width: 450

These Click Boards are an innovative and efficient way to develop hardware projects, whether for beginners or experienced developers. MikroElektronika Click Boards are very easy to use. They come with a standard |mikroBUS| socket connector that can be easily plugged into the Red Pitaya Click Shield.


Technical specifications
==========================

.. figure:: img/red-pitaya-click-shield-logo.jpg
    :width: 900
    :align: center

|

Connectors
-------------

.. image:: img/red-pitaya-click-shield-connectors.png
    :width: 500
    :align: center

+-------------------------+--------------------+----------------------------------------+
| **Click Shield Label**  | **Red Pitaya Pin** | **Notes**                              |
+-------------------------+--------------------+----------------------------------------+
| CLK IN+                 | ADC CLK+           | One-cable clock                        |
+-------------------------+--------------------+----------------------------------------+
| CLK IN-                 | ADC CLK-           |                                        |
+-------------------------+--------------------+----------------------------------------+
| CLK OUT+                | ADC CLK+           | One-cable clock                        |
+-------------------------+--------------------+----------------------------------------+
| CLK OUT-                | ADC CLK-           |                                        |
+-------------------------+--------------------+----------------------------------------+
| REF CLK IN              | DIO10_P            | Reference clock Input                  |
+-------------------------+--------------------+----------------------------------------+
| TRIG IN                 | DIO0_P             | External trigger Input                 |
+-------------------------+--------------------+----------------------------------------+
| TRIG OUT                | DIO0_N             | External trigger Output                |
+-------------------------+--------------------+----------------------------------------+

.. note::

    REF CLK IN connector is connected to the DIO10_P GPIO pin, which can act as a reference clock input, but the functionatlity is not included in the base FPGA image, so it must be added by the user.

|
 

Switches
---------

.. image:: img/red-pitaya-click-shield-switches.png
    :width: 500
    :align: center

+-------------------------+--------------------+------------------------------------------------------------+
| **Click Shield Label**  | **Red Pitaya Pin** | **Notes**                                                  |
+-------------------------+--------------------+------------------------------------------------------------+
| Clock Select            | ADC CLK Select     | External (LOW) or internal clock (HIGH)                    |
+-------------------------+--------------------+------------------------------------------------------------+
| CLK OSC                 | NA                 | Turn the 125 MHz Oscillator on the Click Shield ON/OFF     |
+-------------------------+--------------------+------------------------------------------------------------+
| VCC Select (2x)         | NA                 | Select the digital logic levels for mikroBUS™ 3V3/5V       |
+-------------------------+--------------------+------------------------------------------------------------+

|

**Click board logic:**
If a specific Click Board requires 5V logic levels, please switch the *VCC Select* switch to the **5V** position.


Jumpers
---------

.. image:: img/red-pitaya-click-shield-jumpers.png
    :width: 500
    :align: center

+-------------------------+-----------------------------------------------------------------+
| **Click Shield Label**  | **Notes**                                                       |
+-------------------------+-----------------------------------------------------------------+
| J1                      | Connect CLK IN- to Virtual GND (one-cable clock only)           |
+-------------------------+-----------------------------------------------------------------+
| J4                      | Connect Oscillator CLK- to CLK IN-                              |
+-------------------------+-----------------------------------------------------------------+
| J5                      | Connect Oscillator CLK+ to CLK IN+                              |
+-------------------------+-----------------------------------------------------------------+
| J6                      | Connect DIO0_N (EXT TRIG OUT) pin to TRIG IN                    |
+-------------------------+-----------------------------------------------------------------+
| J7                      | Trigger sync.: Connect DIO0_P (EXT TRIG IN) pin to TRIG OUT     |
+-------------------------+-----------------------------------------------------------------+
| VIN SEL                 | Select the external power between VEXT and VUSB                 |
+-------------------------+-----------------------------------------------------------------+

|



Power supply
--------------

The Click Shields provide two alternative ways to power the Red Pitaya: 

* USB-C external power supply.
* 12-24 V External Power Supply (2-pin screw Terminal Block).

.. note::

    Set the VIN SEL jumper into the correct position depending on whether the USB-C or External Power supply (Terminal Block) is used.

The external power supply powers both the Red Pitaya and the Red Pitaya Click Shield. The maximum power consumption of Red Pitaya is 10 W (5 V, 2 A). The power consumption of the Click Shield greatly depends on the type of Click Boards attached to it (we recommend leaving 5 W just in case).
Minimal requirements for the external power supplies:

* USB-C - 5 V, 3 A (15 W).
* External Power Supply - 12-24 V, 1.5 A (15 W).

The voltages must be in the specified range.

If the power is supplied through the Red Pitaya Click Shield, the microUSB power connector on the Red Pitaya board can be disconnected.
In short, you do not have to rely on the original Red Pitaya power supply but can use a better power supply if available.


**Power options**

#.  **USB-C or External power supply**

    .. image:: img/red-pitaya-power-01.png
        :width: 400

    When the USB type C connector or the External Power Supply is connected to the Click Shield, the PWR diode will **glow Blue**, and in this setup, the connected Red Pitaya baseboard and all mikroBUS™ sockets will be powered from it.

    |

#.  **Standard power supply**

    .. image:: img/red-pitaya-power-02.png
        :width: 400

    When the USB is connected to the Red Pitaya board, the PWR diode will **glow Green**, and in this setup, the Red Pitaya baseboard itself will be supplied, and it will provide power to the Click Shield, including all mikroBUS™ sockets.

    |

#.  **Standard and external power supply**
   
    .. image:: img/red-pitaya-power-03.png
        :width: 400

    When the USB type C connector is connected to the Click Shield, and the other USB is connected to the Red Pitaya board, the PWR diode will **glow Cyan**, and in this setup, the mikroBUS™ sockets are powered from the Click Shield side.



Pinout
--------

Here you will find the interconnections between Click Boards (|mikroBUS| pinout) and Red Pitaya pins.

.. figure:: img/mikrobus.png
    :width: 300

**Short pin descriptions:**

* Digital pins: *PWM, RST, INT*
* Analog pins: *AN*
* UART pins: *RX, TX*
* SPI pins: *CS, SCK, MISO, MOSI*
* I2C pins: *SCL, SDA*


.. note::

    Red Pitaya only has one set of UART and SPI pins, to achieve the functionality of two click boards, some of the digital pins are used for switching SPI and UART between the two click boards:

    * DIO1_N  ==  Chip Select 1 (Click board 1).
    * DIO3_N  ==  Chip Select 2 (Click board 2).
    * DIO5_N  ==  Switching between UART0 (Click board 1)/UART1 (Click board 2).


Click Board 1
~~~~~~~~~~~~~~~

Closer to **+CLK OUT- pins**.

+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
| **Notes**          | **mikroBUS Pin**   | **Red Pitaya Pin** | **Red Pitaya Pin** | **mikroBUS Pin**   | **Notes**          |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| Analog input       | 1    | AN          |  AIN0              | DIO1_P             | PWM          | 16  | PWM                |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| Reset              | 2    | RST         |  DIO2_N            | DIO2_P             | INT          | 15  | Interrupt          |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| SPI Chip select 1  | 3    | CS          |  DIO1_N            | RX                 | RX           | 14  | UART0 RX           |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| SPI Serial clock   | 4    | SCK         |  SCK               | TX                 | TX           | 13  | UART0 TX           |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| SPI MISO (SDO)     | 5    | MISO        |  MISO              | SCL                | SCL          | 12  | I2C Clock          |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| SPI MOSI (SDI)     | 6    | MOSI        |  MOSI              | SDA                | SDA          | 11  | I2C Data           |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| Power supply       | 7    | 3V3         |  3V3               | 5V                 | 5V           | 10  | Power supply       |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| Ground             | 8    | GND         |  GND               | GND                | GND          | 9   | Ground             |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+

|


Click Board 2
~~~~~~~~~~~~~~~

Closer to **+CLK IN- pins**.

+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
| **Notes**          | **mikroBUS Pin**   | **Red Pitaya Pin** | **Red Pitaya Pin** | **mikroBUS Pin**   | **Notes**          |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| Analog input       | 1    | AN          |  AIN1              | DIO3_P             | PWM          | 16  | PWM                |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| Reset              | 2    | RST         |  DIO4_N            | DIO4_P             | INT          | 15  | Interrupt          |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| SPI Chip select 2  | 3    | CS          |  DIO3_N            | RX                 | RX           | 14  | UART1 RX           |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| SPI Serial clock   | 4    | SCK         |  SCK               | TX                 | TX           | 13  | UART1 TX           |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| SPI MISO (SDO)     | 5    | MISO        |  MISO              | SCL                | SCL          | 12  | I2C Clock          |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| SPI MOSI (SDI)     | 6    | MOSI        |  MOSI              | SDA                | SDA          | 11  | I2C Data           |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| Power supply       | 7    | 3V3         |  3V3               | 5V                 | 5V           | 10  | Power supply       |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+
| Ground             | 8    | GND         |  GND               | GND                | GND          | 9   | Ground             |
+--------------------+------+-------------+--------------------+--------------------+--------------+-----+--------------------+

|


Logic Analyzer Connector
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. figure:: img/red-pitaya-click-shield-la.png
    :width: 500
    :align: center

Pin 1 is marked with a small white dot. On the bottom-left side of the connector when the shield is oriented according to the *LOGIC ANALYZER* text.

+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| **Notes**          | **LA Connector Pin**    | **Red Pitaya Pin** | **Red Pitaya Pin** | **LA Connector Pin**    | **Notes**          |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| Not Connected      | 1                       | NC                 | NC                 | 2                       | Not Connected      |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| Not Connected      | 3                       | NC                 | NC                 | 4                       | Not Connected      |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| DIN7               | 5                       | DIO7_P             | DIO3_P             | 6                       | DIN3               |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| DIN6               | 7                       | DIO6_P             | DIO2_P             | 8                       | DIN2               |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| DIN5               | 9                       | DIO5_P             | DIO1_P             | 10                      | DIN1               |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| DIN4               | 11                      | DIO4_P             | DIO0_P             | 12                      | DIN0               |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| Not Connected      | 13                      | NC                 | NC                 | 14                      | Not Connected      |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+
| Ground             | 15                      | GND                | GND                | 16                      | Ground             |
+--------------------+-------------------------+--------------------+--------------------+-------------------------+--------------------+

|


Other
~~~~~~~

Red Pitaya only has one set of UART pins, to achieve the functionality of two click boards, the following pins are used for switching UART between the two click boards:

+--------------------+------------------------------------------------------------+
| **Red Pitaya Pin** | **Notes**                                                  |
+--------------------+------------------------------------------------------------+
| DIO5_N             | Switching UART0/UART1 (output set to LOW/HIGH)             |
+--------------------+------------------------------------------------------------+
| DIO6_N             | Switching UART2/UART3 (Possible future expansion)          |
+--------------------+------------------------------------------------------------+

|



Components
===============

* |ZL40213| LVDS clock fanout buffer.
* |TXS0108| level-shifting voltage translators.


Schematics
================

* `Click_shield_for_Red_Pitaya_v103_Schematic.pdf <https://downloads.redpitaya.com/doc/Click_shield_for_Red_Pitaya_v103_Schematic.pdf>`_


.. note::

    E1 and E2 connector labels are mixed up in the schematics.

.. TODO E1 and E2 connectors mixed up and have reverse pin numbers
.. TODO should add a LDO after the DC/DC converter for both rails.



Mechanical Specifications and 3D Models
=========================================

* `red-pitaya-click-shield-2d-3d-files.zip <https://downloads.redpitaya.com/doc/red-pitaya-click-shield-2d-3d-files.zip>`_



External clock specifications
==============================

According to the datasheet the |ZL40213| fanout buffer supports a wide range of differential or single-ended input clock signals:

* LVPECL
* LVDS
* CML
* HSTL
* LVCMOS

For more information on the external clock signal, please check the |ZL40213| datasheet. The inputs are in the AC coupling configuration. The chip is powered by a 3V3 power supply.


Examples of use
================

Synchronisation options
-------------------------

For detailed guide on synchronisation options and Click Shield connection diagram, please refer to the :ref:`multiboard synchronisation section <multiboard_sync>`.


Synchronisation example
--------------------------

Here are examples for synchronising two external clock Red Pitaya units with Click Shields through SCPI commands.

* :ref:`Multiboard synchronisation examples <examples_multiboard_sync>`.


Click Boards
--------------

Here are some examples of how to use click boards together with Click Shield and Red Pitaya.

.. toctree::
  :maxdepth: 2

   ../../../../../../appsFeatures/examples/click_shield_examples/click_board_examples/click_examples




.. sustitutions

.. rubric:: Footnotes

.. [#f1] This also includes other variations of STEMlab 125-14 external clock boards, such as *STEMlab 125-14 Z7020 external clock*, *STEMlab 125-14 LN external clock*, etc.



.. |MIKROE| raw:: html

    <a href="https://www.mikroe.com/" target="_blank">MirkoElektronika</a>

.. |Click Boards| raw:: html

    <a href="https://www.mikroe.com/click" target="_blank">MIKROE Click Board™</a>

.. |mikroBUS| raw:: html

    <a href="https://www.mikroe.com/mikrobus" target="_blank">mikroBUS™</a>



.. |ZL40213| raw:: html

    <a href="https://ww1.microchip.com/downloads/en/DeviceDoc/ZL40213-Data-Sheet.pdf" target="_blank">ZL40213</a>

.. |TXS0108| raw:: html

    <a href="https://www.digikey.com/en/products/detail/texas-instruments/TXS0108ERGYR/1910182" target="_blank">TXS0108</a>

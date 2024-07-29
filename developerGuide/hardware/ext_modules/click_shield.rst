.. _click_shield:

##############
Click Shield
##############

.. figure:: img/click_shield/red-pitaya-click-shield-banner.jpg
    :width: 900
    :align: center

The Red Pitaya Click Shield extension module enables users to extend Red Pitaya hardware with two |Click Boards| and power them and the Red Pitaya from either an external USB C power adapter or a 12-24 Volt external power supply. Using U.FL patch cables, the shield can also be utilised for high-performance clock and trigger synchronisation between multiple Red Pitaya units and/or other devices. An external reference clock can also be connected to the shield through the U.FL connector.


**Highlights:**

- Two |mikroBUS| sockets, allowing interface with more than 1500 |Click Boards| devices. 
- High-performance clock and trigger synchronisation between multiple Red Pitaya units or other devices.
- Powering Red Pitaya through an external power supply (12-24 V or via USB-C connector). 


|click_shield_front| |click_shield_back|

.. |click_shield_front| image:: img/click_shield/red-pitaya-click-shield-front.png
    :width: 450

.. |click_shield_back| image:: img/click_shield/red-pitaya-click-shield-back.png
    :width: 450

|

What is in the box?
=====================

- 1x Red Pitaya Click Shield
- 3x U.FL to U.FL patch cable for trigger and clock synchronisation


.. _click_shield_compatibility:

Compatibility
===============

.. note::

   Depending on which Red Pitaya board model you are using, some features of the Red Pitaya Click Shield might not be applicable.

The clock synchronisation is compatible only with the following board models (and their Low-Noise versions):

- STEMlab 125-14 External Clock
- SDRlab 122-16 External Clock
- STEMlab 125-14 4-Input

Switching between the External and Internal clock is available only on the STEMlab 125-14 4-Input (CLK SEL pin) but will be compatible with all future Red Pitaya board redesigns.

Trigger synchronisation and |Click Boards| are compatible with all board models.

Here is a compatibility table:

.. table::
    :widths: 10 18 18 18 18 18
    :align: center

    +------------------------------------+--------------------------+--------------------------+------------------------------+--------------------------+--------------------------+
    | Click Shield Feature Compatibility                                                                                                                                            |
    +====================================+==========================+==========================+==============================+==========================+==========================+
    |                                    | STEMlab 125-14 |br|      | SDRlab 122-16            | STEMlab 125-14 ext. clk |br| | STEMlab 125-14 4-Input   | SIGNALlab 250-12         |
    |                                    | STEMlab 125-14 LN |br|   |                          | SDRlab 122-16 ext. clk       |                          |                          |
    |                                    | STEMlab 125-14-Z7020-LN  |                          |                              |                          |                          |
    +------------------------------------+--------------------------+--------------------------+------------------------------+--------------------------+--------------------------+
    | Click Boards (microBus)            | Yes                      | Yes                      | Yes                          | Yes                      | Yes                      |
    +------------------------------------+--------------------------+--------------------------+------------------------------+--------------------------+--------------------------+
    | High speed Clock Synchronisation   | No                       | No                       | Yes                          | Yes                      | No                       |
    +------------------------------------+--------------------------+--------------------------+------------------------------+--------------------------+--------------------------+
    | Powering options                   | Yes                      | Yes                      | Yes                          | Yes                      | No                       |
    +------------------------------------+--------------------------+--------------------------+------------------------------+--------------------------+--------------------------+
    | Clk Switch (Internal/External)     | No                       | No                       | No                           | Yes                      | No                       |
    +------------------------------------+--------------------------+--------------------------+------------------------------+--------------------------+--------------------------+

.. |br| raw:: html

    <br/>

|

What are Click Boards?
=======================

|Click Boards| by |MIKROE| are small add-on boards designed to simplify the process of developing electronic projects by providing a pre-built and tested module with specific functionality. Currently, over 1500 click boards are available in different categories, including communication, display, sensors, storage, motor control, mixed signals, and others.

.. figure:: img/click_shield/click-boards-header-banner.jpg
    :width: 450

These Click Boards are an innovative and efficient way to develop hardware projects, whether for beginners or experienced developers. MikroElektronika Click Boards are very easy to use. They come with a standard |mikroBUS| socket connector that can be easily plugged into the Red Pitaya Click Shield.


.. |MIKROE| raw:: html

  <a href="https://www.mikroe.com/" target="_blank">MirkoElektronika</a>

.. |Click Boards| raw:: html

  <a href="https://www.mikroe.com/click" target="_blank">MIKROE Click Board™</a>

.. |mikroBUS| raw:: html

  <a href="https://www.mikroe.com/mikrobus" target="_blank">mikroBUS™</a>


Technical specifications
==========================

.. figure:: img/click_shield/red-pitaya-click-shield-logo.jpg
    :width: 900
    :align: center

|

Connectors
-------------

.. image:: img/click_shield/red-pitaya-click-shield-connectors.png
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

.. image:: img/click_shield/red-pitaya-click-shield-switches.png
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

.. image:: img/click_shield/red-pitaya-click-shield-jumpers.png
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

- USB-C external power supply
- 12-24 V External Power Supply (2-pin screw Terminal Block)

.. note::

    Set the VIN SEL jumper into the correct position depending on whether the USB-C or External Power supply (Terminal Block) is used.

The external power supply powers both the Red Pitaya and the Red Pitaya Click Shield. The maximum power consumption of Red Pitaya is 10 W (5 V, 2 A). The power consumption of the Click Shield greatly depends on the type of Click Boards attached to it (we recommend leaving 5 W just in case).
Minimal requirements for the external power supplies:

- USB-C - 5 V, 3 A (15 W)
- External Power Supply - 12-24 V, 1.5 A (15 W)

The voltages must be in the specified range.

If the power is supplied through the Red Pitaya Click Shield, the microUSB power connector on the Red Pitaya board can be disconnected.
In short, you do not have to rely on the original Red Pitaya power supply but can use a better power supply if available.


**Power options**

#. **USB-C or External power supply**

   .. image:: img/click_shield/red-pitaya-power-01.png
       :width: 400

   When the USB type C connector or the External Power Supply is connected to the Click Shield, the PWR diode will **glow Blue**, and in this setup, the connected Red Pitaya baseboard and all mikroBUS™ sockets will be powered from it.

   |

#. **Standard power supply**

   .. image:: img/click_shield/red-pitaya-power-02.png
       :width: 400

   When the USB is connected to the Red Pitaya board, the PWR diode will **glow Green**, and in this setup, the Red Pitaya baseboard itself will be supplied, and it will provide power to the Click Shield, including all mikroBUS™ sockets.

   |

#. **Standard and external power supply**
   
   .. image:: img/click_shield/red-pitaya-power-03.png
       :width: 400

   When the USB type C connector is connected to the Click Shield, and the other USB is connected to the Red Pitaya board, the PWR diode will **glow Cyan**, and in this setup, the mikroBUS™ sockets are powered from the Click Shield side.



Pinout
--------

Here you will find the interconnections between Click Boards (|mikroBUS| pinout) and Red Pitaya pins.

.. figure:: img/click_shield/mikrobus.png
    :width: 300

**Short pin descriptions:**

- Digital pins: *PWM, RST, INT*
- Analog pins: *AN*
- UART pins: *RX, TX*
- SPI pins: *CS, SCK, MISO, MOSI*
- I2C pins: *SCL, SDA*


.. note::

   Red Pitaya only has one set of UART and SPI pins, to achieve the functionality of two click boards, some of the digital pins are used for switching SPI and UART between the two click boards:

   - DIO1_N  ==  Chip Select 1 (Click board 1)
   - DIO3_N  ==  Chip Select 2 (Click board 2)
   - DIO5_N  ==  Switching between UART0 (Click board 1)/UART1 (Click board 2)


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

.. image:: img/click_shield/red-pitaya-click-shield-la.png
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

- |ZL40213| LVDS clock fanout buffer.
- |TXS0108| level-shifting voltage translators.


.. |ZL40213| raw:: html

  <a href="https://www.digikey.si/en/htmldatasheets/production/1239190/0/0/1/zl40213" target="_blank">ZL40213</a>

.. |TXS0108| raw:: html

  <a href="https://www.digikey.com/en/products/detail/texas-instruments/TXS0108ERGYR/1910182" target="_blank">TXS0108</a>



Schematics
================

- `Click_shield_for_Red_Pitaya_v103_Schematic.pdf <https://downloads.redpitaya.com/doc/Click_shield_for_Red_Pitaya_v103_Schematic.pdf>`_



Mechanical Specifications and 3D Models
=========================================

- `red-pitaya-click-shield-2d-3d-files.zip <https://downloads.redpitaya.com/doc/red-pitaya-click-shield-2d-3d-files.zip>`_



Examples of use
================

Synchronisation
----------------

The Red Pitaya Click Shield can synchronise multiple Red Pitaya units together. As U.FL cables are used for clock and trigger synchronisation, other external clock devices can also be included in the chain.
The connection provides minimal clock signal delay between multiple Red Pitaya units, as there is only a single ZL40213 LVDS clock fanout buffer between two units.

To synchronise two or more Red Pitaya units, establish the following connections with U.FL cables between the primary board (transmitting clock and trigger signals) and the secondary board (receiving the clock and trigger signals). Use one of the two schemes depending on whether you want to connect an external clock or use the oscillator on the Red Pitaya Click Shields.


Oscillator
~~~~~~~~~~~~

.. figure:: img/click_shield/Click_Shield_Oscillator_Sync.png
    :width: 700
    :align: center

When using the oscillator, the first Red Pitaya Click Shield transmits the clock and trigger signals to all devices in the chain. Here are the most important things to check:

**Primary board:**

- Jumpers J4 and J5 connected. Connect the oscillator to the clocking transmission line.
- Jumpers J6 and J7 connected. Connect the Red Pitaya trigger to the trigger transmission line.
- Jumper J1 disconnected (unless using a single wire clock).
- CLK OSC switch in ON position.
- CLK SELECT switch in EXT position.

**Secondary board:**

- Jumper J6 connected. Connect the trigger to the Ext. Trigger pin.
- Jumper J1 disconnected (unless using a single wire clock).
- CLK OSC switch in OFF position.
- CLK SELECT switch in EXT position.

If an external trigger signal is used, copy the secondary board's trigger connections to the primary board (disconnect J7 and connect the external trigger U.FL cable). 
Otherwise, DIO0_N acts as external trigger output (on the primary board), and DIO0_P acts as external trigger input.


External Clock
~~~~~~~~~~~~~~~~

.. figure:: img/click_shield/Click_Shield_Ext_Clock_Sync.png
    :width: 700
    :align: center

When using an external clock and external trigger, the clock and trigger signals are transmitted to all devices in the chain. All the Click Shields share the same configuration:

**Primary and Secondary boards:**

- Jumper J6 connected. Connect the trigger to the Ext. Trigger pin.
- Jumper J1 disconnected (unless using a single wire clock).
- CLK OSC switch in OFF position.
- CLK SELECT switch in EXT position.


Synchronisation example
--------------------------

Here are examples for synchronising two Red Pitayas with Click Shields through SCPI commands.

- :ref:`Synchronised Click Shield Generation and Acquisition <click_shield_sync_exam1>`


Click Boards
--------------

Here are some examples of how to use click boards together with Click Shield and Red Pitaya.

.. toctree::
  :maxdepth: 2

   ../../../../../appsFeatures/examples/click_shield_examples/click_board_examples/click_examples



.. _click_shield_Q&A:

Click Shield Q&A
==================

Here is a special Q&A section regarding the Red Pitaya Click Shields and their comparison to the X-Channel System. For general Red Pitaya Q&A, please see the :ref:`FAQ section <faq>`.

Can I synchronise multiple different Red Pitaya board models with the Click Shields?
--------------------------------------------------------------------------------------

Yes, you can. There can be different board models in a Red Pitaya Click Shield daisy chain. For example, the primary device can be a STEMlab 125-14 4-Input board,
the first secondary device a STEMlab 125-14 ext. clk., and the second secondary device another 4-Input. We recommend daisy chaining only devices with the same base clock speed.

Please take into account that SDRlab 122-16 ext. clk. is meant to receive a 122.88 MHz clock signal, so although synchronisation with STEMlab 125-14 boards is possible, we do not recommend it.

While multiple different board models can be daisy chained, some features might be unavailable. See the :ref:`Click Shield compatibitily section <click_shield_compatibility>`.


What is the difference between Red Pitaya X-channel System and Red Pitaya Click Shield Synchronisation?
--------------------------------------------------------------------------------------------------------

In this section we will talk about the difference between the Red Pitaya X-channel System and Red Pitaya Click Shield Synchronisation. It might seem like these two are completely the same, but that is far from the truth.

More info on :ref:`Red Pitaya X-channel System <top_125_14_MULTI>`.

.. note::

    Please note that the limitations of the Streaming applications are the same for both systems (continuous streaming). More information is available :ref:`here <streaming_top>`.


+--------------------------------+--------------------------------------------+--------------------------------------------+
|                                | **X-Channel System**                       | **Click Shield Synchronisation**           |
+================================+============================================+============================================+
| **Clock & Sampling rate**                                                                                                |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| Recommended sampling rate      | up to 100 ksps                             | up to full sampling rate                   |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| Shared clock signal            | Primary device CLK                         | Click Shield Oscillator OR EXT CLK         |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| Clock signal delays            | | Slightly higher delay per unit           | 1x Clock buffer per unit - |ZL40213|       |
|                                | | (signal through each FPGA) [#f1]_        |                                            |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| Trigger signal delays          | | Slightly higher delay per unit           | 1x Trigger buffer per unit -               |
|                                | | (signal through each FPGA) [#f1]_        |  |74FCT38072DCGI|                          |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| **Pinout**                                                                                                               |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| GPIO access                    | Full access [#f2]_                         | Max 10 digital pins [#f3]_                 |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| Slow analog access             | Full access (4/4)                          | Max 2 pins (2/4) [#f3]_                    |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| Digital communication pins     | 1x UART, 1x SPI, 1x I2C, 1x CAN            | 2x UART, 2x SPI, 2xI2C (no CAN) [#f3]_     |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| **Units**                                                                                                                |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| | Compatible Red Pitaya board  | | Primary - STEMlab 125-14 LN              | | All units are the same:                  |
| | models                       | |                                          | | STEMlab 125-14 Ext Clk                   |
| |                              | | Secondary - STEMlab 125-14 LN Secondary  | | SDRlab 122-16 Ext Clk                    |
| |                              | |                                          | | STEMlab 125-14 4-Input                   |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| | Choosing between External    | No                                         | Yes (4-Input and future HW board           |
| | and Internal clock           |                                            | redesigns only)                            |
+--------------------------------+--------------------------------------------+--------------------------------------------+
| Aluminium case compatibility   | No                                         | Yes                                        |
+--------------------------------+--------------------------------------------+--------------------------------------------+

.. [#f1]
    Exact measurements will be provided in the future.

.. [#f2]
    Depending on the board model there can be either 16, 19, or 22 GPIO pins. Check the :ref:`Comparison table <rp-board-comp>` for more information.
 
.. [#f3]
    Through the microBUS connectors.

.. |74FCT38072DCGI| raw:: html

  <a href="  https://www.digikey.si/en/products/detail/renesas-electronics-corporation/74FCT38072DCGI/2017578" target="_blank"> 74FCT38072DCGI</a>


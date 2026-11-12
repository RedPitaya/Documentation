.. _hw_specs_gen2:

#######################################
Common hardware specifications (Gen 2)
#######################################

.. TODO - Board weight,
.. TODO - storage temperature and humidity add to the table
.. TODO - Link style (Heating and cooling) - update the link, cover the differences between OG and TI boards.


.. note::

    Looking for :ref:`Original Gen hardware specifications? <hw_specs_orig_gen>`

This section contains information that applies to **all** Red Pitaya Gen 2 boards.

.. note::

    For board-specific specifications, measurements, power requirements, connector pinouts, and detailed technical data, please refer to your board's documentation page:

    * :ref:`STEMlab 125-14 Gen 2 <top_125_14_gen2>`
    * :ref:`STEMlab 125-14 PRO Gen 2 <top_125_14_pro_gen2>`
    * :ref:`STEMlab 125-14 PRO Z7020 Gen 2 <top_125_14_pro_z7020_gen2>`
    * :ref:`STEMlab 125-14 TI <top_125_14_TI>`
    * :ref:`STEMlab 65-16 TI <top_65_16_TI>`

Please note that the full hardware schematics for the Red Pitaya boards are not available. While Red Pitaya has open-source code, the hardware schematics are not open source. 
However, development schematics with information regarding hardware configuration, FPGA pin connections, and similar, are available.

.. note::

    The information provided by Red Pitaya d.o.o. is believed to be accurate and reliable. However, no liability is accepted for its use. Please note that the contents may 
    be subject to change without prior notice. 


.. contents:: **Index**
   :local:
   :backlinks: none

|


.. _hw_gen2_power_supply:

1. Power supply (all Gen 2 boards)
===================================

.. TODO - measure power consumption (minimum and typical)

**All Red Pitaya Gen 2 boards use the same power supply:**

* **5 V, 3 A USB-C power supply**

We currently use the following switching power supply model for all Gen 2 boards: MKE2-P27WSFAD (5 V, 5 A, USB-C output). This power supply is included in all Red Pitaya Gen 2 kits 
available on the |redpitaya-store|.

Using a **low-noise linear power supply** (instead of the default switching power supply) is recommended for improved performance and reduced noise levels for applications where precision matters.

.. note::

    It is important to note that Red Pitaya boards should **not** be powered by a power supply that provides less power than specified above or has very thin power wires. 
    Doing so may result in abnormal behaviour of the device, causing reboots and network disconnections. Similarly, the Red Pitaya board may malfunction if powered directly 
    from a USB port on a PC (due to insufficient current supply) or hub that cannot provide sufficient power or if a faulty power cable is used.
    
    Furthermore, the use of an unapproved power supply may impair performance or cause damage to the product.

.. warning::

    Power supply precautions:

    * All Gen 2 boards may only be powered by an isolated external power supply of 5 Volts DC with a minimum current of 3 A delivered via USB-C connector.
      Any external power supply used with Red Pitaya must comply with the relevant regulations and standards applicable in the country of use.

|


.. _hw_gen2_sd_card:

2. SD card size (all Gen 2 boards)
===================================

We recommend using an SD card with a minimum of **32 GB** of space for Red Pitaya Gen 2 boards. The SD card should be **Class 10 or higher**.

|


3. Required hardware (all Gen 2 boards)
========================================

The following items are required for proper board operation. They are already included in each of the Red Pitaya kits available on the |redpitaya-store|:

* 32 GB Class 10 micro SD card with pre-loaded Red Pitaya OS.
* Ethernet cable.
* USB-C power supply (5 V, 3 A).

Additional items required that are not included in the Red Pitaya kits:

* A computer with an internet browser (Google Chrome is recommended).
* Router with DHCP server enabled (access to the internet is required for :ref:`Software update manager <software_update_manager>` and some 3rd party community projects).


|


4. Connectors and interfaces (all Gen 2 boards)
================================================

.. TODO add picture showing the main connectors and interfaces on the Red Pitaya Gen 2 boards.

All Gen 2 boards share the following main connectors and interfaces. The exact location of the connectors and the additional interfaces available on each model are 
described in the board-specific documentation.

* **IN1, IN2 (SMA)** - fast analog inputs (see :ref:`hw_gen2_analog_io`).
* **OUT1, OUT2 (SMA)** - fast analog outputs (see :ref:`hw_gen2_analog_io`).
* **E1, E2, E3** - extension connectors (see :ref:`hw_gen2_extension_connectors`).
* **Ethernet** - network connection (1 Gbit/s).
* **USB-C (power)** - 5 V power supply input (see :ref:`hw_gen2_power_supply`).
* **USB-C (console)** - serial console access.
* **USB-C host** - connection of USB peripherals (for example a Wi-Fi dongle).
* **microSD card slot** - OS and user data (see :ref:`hw_gen2_sd_card`).
* **J-TAG** - interface for programming and debugging the FPGA.

|

.. _status_leds_gen2:

5. Status LED description (all Gen 2 boards)
=============================================

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
| Orange  | | SD card access indicator (in normal operation, this LED will flash sporadically at slow intervals).        |
|         | | If the :ref:`QSPI eMMC module <E3_QSPI_eMMC_module_HW>` is present, the internal watchdog timer is wired   |
|         | | to the orange LED instead (the LED will blink continuously).                                               |
+---------+--------------------------------------------------------------------------------------------------------------+

.. note::

    When the :ref:`QSPI eMMC module <E3_QSPI_eMMC_module_HW>` is connected to a Gen 2 PRO board the orange LED functionality will be switched to show 
    the watchdog timer status instead of the SD card access.

|


6. Operating temperature and safety
===================================

Operating temperature range
----------------------------

Red Pitaya Gen 2 devices have an operating temperature range from 0 °C to +25 °C and a storage temperature range of -20 °C to +85 °C. Adding active cooling solutions, such as 
a small fan, increases the temperature range to 0 °C to +55 °C. Additional cooling methods, such as larger heatsinks or improved airflow, can further enhance the operating 
temperature range.

For industrial grade Gen 2 boards with operating temperature range from -40 °C to +85 °C, please contact us at info@redpitaya.com.

* Should be operated in normal conditions and should not be covered.
* Are intended for indoor use at a maximum altitude of 2000 m, pollution severity 2 and relative humidity less than 90 %.
* Are intended for use with low voltage power sources and signals and should not be used in direct connection with voltages exceeding 30 Volts.

.. note::

    The operating temperature range (0 °C to +55 °C) applies if the board is using the included heatsink. Replacing the heatsink with a larger one or implementing additional 
    cooling solutions will increase the operating range of the board.
    
    When using custom cooling solutions, please note that the Zynq temperature must not exceed +85 °C. Additionally, the Red Pitaya OS has a software temperature protection 
    that will shut down the board if it gets too hot. This is meant to protect the board from overheating and damage. If a custom cooling solution is used, please check that 
    the software temperature protection is not preventing proper operation.


.. _hw_gen2_heating_cooling:

Heating and cooling
--------------------

It is not uncommon for Red Pitaya boards to reach temperatures of 60 °C or above during operation. The thermal images below show expected temperatures during typical operation.

.. figure:: img/cooling/Thermal_images/with_heatsink_top.BMP
    :align: center
    :width: 600

    Thermal image of the board with heatsink attached (top view) - typical operating temperatures.

.. figure:: img/cooling/Thermal_images/with_heatsink_bottom.BMP
    :align: center
    :width: 600

    Thermal image of the board with heatsink attached (bottom view) - typical operating temperatures.


.. figure:: img/cooling/Thermal_images/without_heatsink_top.BMP
    :align: center
    :width: 600

    Thermal image of the board without heatsink attached (top view) - operation without heatsink is not recommended.

.. figure:: img/cooling/Thermal_images/without_heatsink_bottom.BMP
    :align: center
    :width: 600

    Thermal image of the board without heatsink attached (bottom view) - operation without heatsink is not recommended.

.. note::

    Please note that some parts of the board, particularly the heatsink, may become hot during and after operation. To avoid injury, please do not touch them.

.. note::

    It is imperative that a heatsink is installed and that the board is operated on a flat surface devoid of any obstructions that could impede airflow.
    In order to mitigate the effects of elevated ambient temperatures and reduced pressure conditions within enclosures, it is necessary to implement an effective ventilation 
    strategy. The product's operational functionality is automatically disabled at internal temperatures of 85°C to prevent any potential damage.


.. _hw_gen2_cooling_options:

Cooling options
^^^^^^^^^^^^^^^^^

For enhanced cooling, we suggest utilising one or more of the following options:

* :ref:`Gen 2 Aluminium case <alucase>` - to improve heat dissipation and protect the board from external factors.
* :ref:`Gen 2 Heatsink interface <heatsink>` (**not yet available**) - to improve heat dissipation and connect the board to an external heatsink.
* External cooling fan - to increase airflow around the board.

|

Symbols on the board
---------------------

The following symbols and warning signs are used on the board:

.. figure:: img/symbols/Danger_symbol.png
    :align: center
    :width: 200

    Danger symbol

.. figure:: img/symbols/Do_not_touch_symbol.png
    :align: center
    :width: 200

    Do not touch symbol

.. figure:: img/symbols/Hot_surface_symbol.png
    :align: center
    :width: 200

    Hot surface symbol

All three symbols warn the user about hot heatsink surface. As indicated in the :ref:`Heating and cooling section <hw_gen2_heating_cooling>` above, the boards can easily reach high 
temperatures during operation, so it is recommended to avoid touching the heatsink during or recently after operation. If necessary, pick the board up using the edges 
(E1 and E2 connectors) to avoid burning yourself on the hot surface of the heatsink.

|

Handling and ESD precautions
-----------------------------

* Red Pitaya boards contain electrostatic discharge (ESD) sensitive components. Handle the board by its edges and avoid touching the SMA centre pins, the extension 
  connector pins and the components on the board.
* Discharge yourself (for example by touching a grounded metal surface) before handling the board, and place it on a non-conductive, flat surface.
* Do not connect or disconnect extension modules, jumpers or cables while the board is powered.
* Do not place the board on conductive surfaces, as this can short-circuit the pins and components on the bottom side.

|

Regulatory information
-----------------------

Regulatory and compliance information (certificates and declarations of conformity) is available in the :ref:`Certificates <certificates>` section. The maximum 
input and output voltage ratings (damage thresholds) differ slightly between the board models and are listed in the documentation of each specific board.

|

.. _hw_gen2_analog_io:

7. Fast analog inputs and outputs (all Gen 2 boards)
=====================================================

.. warning::

    All inputs and outputs available through SMA connectors share a common ground connected to the power supply ground.

.. warning::
    
    The SMA connectors on the cables connected to Red Pitaya must comply with the MILC39012 standard. The centre pin must be of suitable length, otherwise the SMA 
    connector installed in Red Pitaya will mechanically damage the SMA connector. The centre pin of the SMA connector on Red Pitaya will lose contact with the board 
    and the board will not be repairable due to the mechanical damage (separation of the pad from the board).

|

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
    
    Please note that jumper settings are limited to the described positions. Any other configuration or use of different jumper types may damage the product and void 
    the warranty.

|

.. _hw_gen2_jumper_orientation:

Jumper orientation (important)
--------------------------------

**The position and orientation of the jumpers can significantly affect measurement accuracy.** The jumpers are internally connected to a small metal plate which acts as 
a capacitor and affects the overall capacitance, which in turn affects the input impedance.

If the jumpers are moved from an incorrect to a correct position, **calibration is strongly recommended** as the input capacitance depends on jumper settings and may vary 
between positions.


1.  **The position of the jumper bumps must be as shown in the diagram.** Due to the non-symmetrical nature of the jumpers and their latches, we advise installing them with 
    the latch on the outer side to avoid any issues with difficult-to-remove jumpers.

    .. figure:: img/jumpers/Jumper_position_Note.png
        :align: center


2.  **Once installed, the jumpers should be positioned so that the metal part is not visible.** Please refer to the example of the STEMlab 125-14 4-Input in the pictures 
    below for guidance.

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


.. _hw_gen2_extension_connectors:

8. Extension connectors (all Gen 2 boards)
===========================================

All Gen 2 boards feature extension connectors (E1 and E2) using the same physical format and electrical characteristics:

**Physical specifications:**

* **Connector type**: 2 x 13 pins IDC 2.54 mm pitch
* **Digital I/O voltage levels**: 3.3V LVCMOS33
* **Power rails**: +5V, -5V, +3.3V

**Current limitations:**

* 0.5 A for +5V (shared between extension module and USB devices)
* 0.1 A for -5V
* 0.5 A for +3.3V (shared between extension module and USB devices)

**Board-specific differences:**

Pin assignments, available features, and FPGA connections vary significantly by board model:

* **STEMlab 125-14 Gen 2**: 16 digital I/Os, 4 slow ADCs, 4 slow DACs, SPI/UART/I2C/CAN
* **STEMlab 125-14 PRO Gen 2**: 16 digital I/Os, 4 slow ADCs, 4 slow DACs, SPI/UART/I2C/CAN, **external clock input**
* **STEMlab 125-14 PRO Z7020 Gen 2**: **22 digital I/Os**, 4 slow ADCs, 4 slow DACs, SPI/UART/I2C/CAN, external clock input, **E3 connector** (16 additional GPIOs)
* **TI variants**: See individual board documentation for specific pinout

For complete pinout diagrams, FPGA pin numbers, and detailed specifications, please refer to your specific board's documentation page.

|


9. Mechanical specifications and power consumption (all Gen 2 boards)
======================================================================

The board dimensions, weight, mounting information and the typical and maximum power consumption depend on the board model (and on the connected extension modules and USB devices). 
Please refer to the documentation of your specific board for these values:

* :ref:`STEMlab 125-14 Gen 2 <top_125_14_gen2>`
* :ref:`STEMlab 125-14 PRO Gen 2 <top_125_14_pro_gen2>`
* :ref:`STEMlab 125-14 PRO Z7020 Gen 2 <top_125_14_pro_z7020_gen2>`
* :ref:`STEMlab 125-14 TI <top_125_14_TI>`
* :ref:`STEMlab 65-16 TI <top_65_16_TI>`

.. note::

    The power supply must be able to provide the power consumed by the board together with all connected extension modules and USB devices     (see :ref:`hw_gen2_power_supply` and 
        :ref:`hw_gen2_extension_connectors` for the current limits).

|


10. Improving performance (all Gen 2 boards)
=============================================

The default configuration of Red Pitaya is a good compromise between performance, cost and ease of use. For demanding measurements, the following steps can improve the noise level and 
accuracy of the board.

Power supply
-------------

The included switching power supply is a convenient and compact solution, but its switching noise can couple into the analog front end and appear as additional noise or spurious 
tones in the acquired and generated signals. Using a **low-noise linear power supply** instead can noticeably reduce the noise floor of the board.

* The replacement supply must still meet the power requirements of the board: 5 V DC, 3 A, delivered via the USB-C connector, and isolated. Computer power supplies with USB-C 
  negotiation are generally a good choice as they automatically provide the required voltage and current.
* Use a short, thick power cable to minimise the voltage drop and the pick-up of external interference.
* Do not power the board from a PC USB port or an unpowered hub - they usually cannot provide enough current (see the power supply notes above).

Grounding and cabling
----------------------

* All SMA inputs and outputs share a common ground connected to the power supply ground. Avoid ground loops by connecting the measured device to the same ground reference as Red Pitaya.
* Use good quality, short, shielded coaxial cables with SMA connectors that comply with the MILC39012 standard.
* Keep the signal cables away from the power supply, switching converters and other noise sources.


Input range and jumper settings
--------------------------------

* Use the **LV (±1 V)** input range for small signals. The best resolution (and the lowest relative noise) is achieved when the signal fills most of the selected input range.
* Make sure that the jumpers are correctly positioned (see :ref:`hw_gen2_jumper_orientation`) to avoid over- or under-compensated step response.
* :ref:`Calibrate <calibration_app>` the board if the accuracy is not sufficient for your application.

Temperature
------------

* Allow the board to warm up and reach a stable temperature before performing precise measurements.
* Keep the board away from drafts and sources of heat, and use the options listed in :ref:`hw_gen2_cooling_options` to keep the temperature stable.

Signal processing
------------------

* Averaging multiple acquisitions reduces random noise.
* Using higher decimation values averages consecutive samples in the FPGA, which increases the effective resolution at the cost of bandwidth.
* On the PRO models, an external low-jitter clock can be used instead of the internal clock (see the board-specific documentation).

|


11. What's different in Gen 2?
===============================

Gen 2 boards represent a significant hardware evolution from the original generation. Here are the key improvements:

**STEMlab 125-14 Gen 2 improvements:**

* Reduced noise and crosstalk on the fast analog inputs and outputs
* Increased fast analog output voltage range (±1 V @ 50 Ω load, ±2 V @ Hi-Z load)
* USB-C connectors (power and console) replacing Micro USB
* Crisp clean 50 Ω output impedance
* SFDR improvements
* No voltage glitching on the outputs when the board is powered on (see the :ref:`Gen 2 FAQ <faq_gen2>` section for full details)

**PRO model exclusive features:**

* Switching between internal and external clock with the *CLK SEL* pin
* E3 add-on board with an STM32 microcontroller providing control over Power, WDT and diverse booting options (QSPI, eMMC)

**STEMlab 125-14 PRO Z7020 Gen 2 exclusive features:**

* E3 connector with 8 fast differential pairs (16 GPIOs) and external eMMC and QSPI booting option
* 1 GB RAM (double the standard 512 MB)
* Zynq 7020 FPGA (double the logic capacity of Zynq 7010)

**Important compatibility notes:**

* Gen 2 boards require OS version **2.07-43 or higher**
* **TI board variants** are NOT backwards compatible with older OS versions - see :ref:`OS Version Compatibility <os_compatibility>` for details
* USB-C power supply: **5V, 3A** (vs Micro USB 5V, 2A on Original Gen)
* Different frontend architecture means analog performance characteristics differ from Original Gen

For detailed performance measurements and specifications, please refer to the individual product pages.

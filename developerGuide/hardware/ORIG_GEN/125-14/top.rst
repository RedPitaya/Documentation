.. _top_125_14:

################
STEMlab 125-14
################

The original Red Pitaya STEMlab 125-14.

.. figure:: img/STEMlab-125-14.jpg
    :width: 500


Pinout
========

.. figure:: img/Red_Pitaya_pinout.jpg
    :alt: Red Pitaya pinout
    :width: 700

|

Technical specifications
==========================

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Basic**                                                               |
    +====================================+====================================+
    | Processor                          | Dual core ARM Cortex-A9            |
    +------------------------------------+------------------------------------+
    | FPGA                               | FPGA Xilinx Zynq 7010 SoC          |
    +------------------------------------+------------------------------------+
    | RAM                                | 512 MB (4 Gb)                      |
    +------------------------------------+------------------------------------+
    | System memory                      | Micro SD up to 32 GB               |
    +------------------------------------+------------------------------------+
    | Console connector                  | Micro USB                          |
    +------------------------------------+------------------------------------+
    | Power connector                    | Micro USB                          |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Power consumption                  | 5 V, 2 A max                       |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40


    +------------------------------------+------------------------------------+
    | **Connectivity**                                                        |
    +====================================+====================================+
    | Ethernet                           | 1 Gbit                             |
    +------------------------------------+------------------------------------+
    | USB                                | USB-A 2.0                          |
    +------------------------------------+------------------------------------+
    | Wi-Fi                              | requires Wi-Fi dongle              |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **RF inputs**                                                           |
    +====================================+====================================+
    | RF input channels                  | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 125 MS/s                           |
    +------------------------------------+------------------------------------+
    | ADC resolution                     | 14 bit                             |
    +------------------------------------+------------------------------------+
    | Input impedance                    | 1 MΩ / 10 pF                       |
    +------------------------------------+------------------------------------+
    | Full scale voltage range           | ±1 V (LV) and ±20 V (HV)           |
    +------------------------------------+------------------------------------+
    | Input coupling                     | DC                                 |
    +------------------------------------+------------------------------------+
    | | **Absolute max.**                | | **LV ±6 V**                      |
    | | **Input voltage**                | | **HV ±30 V**                     |
    +------------------------------------+------------------------------------+
    | Input ESD protection               | Yes                                |
    +------------------------------------+------------------------------------+
    | Overload protection                | Protection diodes                  |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | DC - 60 MHz                        |
    +------------------------------------+------------------------------------+
    | Connector type                     | SMA                                |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **RF outputs**                                                          |
    +====================================+====================================+
    | RF output channels                 | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 125 MS/s                           |
    +------------------------------------+------------------------------------+
    | DAC resolution                     | 14 bit                             |
    +------------------------------------+------------------------------------+
    | Load impedance                     | 50 Ω                               |
    +------------------------------------+------------------------------------+
    | Voltage range                      | ±1 V                               |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Short circuit protection           | Yes                                |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | 2 V / 10 ns                        |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | DC - 50 MHz                        |
    +------------------------------------+------------------------------------+
    | Connector type                     | SMA                                |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Extension connector**                                                 |
    +====================================+====================================+
    | Digital IOs                        | 16                                 |
    +------------------------------------+------------------------------------+
    | Digital voltage levels             | 3.3 V                              |
    +------------------------------------+------------------------------------+
    | Analog inputs                      | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog input voltage range         | 0 - 3.5 V                          |
    +------------------------------------+------------------------------------+
    | Analog input resolution            | 12 bit                             |
    +------------------------------------+------------------------------------+
    | Analog input sample rate           | 100 kS/s                           |
    +------------------------------------+------------------------------------+
    | Analog outputs                     | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog output voltage range        | 0 - 1.8 V                          |
    +------------------------------------+------------------------------------+
    | Analog output resolution           | 8 bit                              |
    +------------------------------------+------------------------------------+
    | Analog output sample rate          | ≲ 3.2 MS/s                         |
    +------------------------------------+------------------------------------+
    | Analog output bandwidth            | ≈ 160 kHz                          |
    +------------------------------------+------------------------------------+
    | Communication interfaces           | I2C, SPI, UART, CAN                |
    +------------------------------------+------------------------------------+
    | Available voltages                 | +5 V, +3V3, -4 V                   |
    +------------------------------------+------------------------------------+
    | External ADC clock                 | No [#f1]_                          |
    +------------------------------------+------------------------------------+

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Synchronisation**                                                     |
    +====================================+====================================+
    | External trigger input             | E1 connector (DIO0_P)              |
    +------------------------------------+------------------------------------+
    | External trigger input impedance   | Hi-Z (digital input)               |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Trigger output [#f2]_              | E1 connector (DIO0_N)              |
    +------------------------------------+------------------------------------+
    | Daisy chain connection             | SATA connectors |br|               |
    |                                    | (up to 500 Mbps)                   |
    +------------------------------------+------------------------------------+
    | Ref. clock input                   | N/A                                |
    +------------------------------------+------------------------------------+


.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Boot options**                                                        |
    +====================================+====================================+
    | SD card                            | Yes                                |
    +------------------------------------+------------------------------------+
    | QSPI                               | Not populated                      |
    +------------------------------------+------------------------------------+
    | eMMC                               | N/A                                |
    +------------------------------------+------------------------------------+

.. note::

    For more information, please refer to the :ref:`Product comparison table <rp-board-comp-orig_gen>`.





Measurements
=================

You can find the measurements of the fast analog frontend here:

* :ref:`Original boards - STEMlab 125-14 <measurements_orig_gen>`.
* :ref:`Gen 2 - STEMlab 125-14 Gen 2 <measurements_gen2>`.


.. _schematics_125_14:

Schematics
============

    * `Schematics_STEM_125-14_v1.0.1.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_125-14_v1.0.1.pdf>`_.
    * `Schematics_STEM_125-14_v1.1.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_125-14_v1.1.pdf>`_.

.. note::

    FULL HW schematics for the Red Pitaya board are not available. Red Pitaya has open-source code but not open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connections, and similar.

Mechanical Specifications and 3D Models
========================================

    * `3D_STEM_125-14_v1.0.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_125-14_v1.0.zip>`_.


Components
===========

    * `ADC <https://www.analog.com/en/products/ltc2145-14.html>`_.
    * `DAC <https://www.analog.com/en/products/AD9767.html>`_.
    * `FPGA (Zynq 7010) <https://docs.xilinx.com/v/u/en-US/ds190-Zynq-7000-Overview>`_.
    * `DC-DC converter <https://www.analog.com/en/products/LTC3615.html>`_.
    * `Oscillator <https://eu.mouser.com/datasheet/2/417/bf-8746.pdf>`_.
    * `SRAM-DDR3 <https://www.digikey.com/en/products/detail/micron-technology-inc/MT41J256M16HA-125-E/4315785>`_.
    * `QSPI <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_ (NOT POPULATED - see :ref:`QSPI section <qspi_chip>` for more information).

.. note::

    STEMlab 125-14 Low Noise and STEMlab 125-14 4-Input feature Zynq 7020 instead of Zynq 7010.


Extension connector STEMlab 125-14
====================================

    * Connector: 2 x 26 pins IDC.

Power Supply
--------------

    * **Available voltages**: +5 V, +3.3 V, -3.4 V .
    * **Current limitations**:

        * 500 mA for +5 V (to be shared between extension module and USB devices).
        * 500 mA for +3V3 (to be shared between extension module and USB devices).
        * 50 mA for -3.4 V supply.


.. _E1_stem:

Extension connector E1
------------------------

    * +3V3 power source
    * 16 single ended or 8 differential digital I/Os with 3.3 V logic levels
    * 2 CAN busses

===  =====================  ===============  ========================  ==============
Pin  Description            FPGA pin number  FPGA pin description      Voltage levels
===  =====================  ===============  ========================  ==============
1    3V3
2    3V3
3    DIO0_P / EXT TRIG      G17              IO_L16P_T2_35             3.3V
4    DIO0_N                 G18              IO_L16N_T2_35             3.3V
5    DIO1_P                 H16              IO_L13P_T2_MRCC_35        3.3V
6    DIO1_N                 H17              IO_L13N_T2_MRCC_35        3.3V
7    DIO2_P                 J18              IO_L14P_T2_AD4P_SRCC_35   3.3V
8    DIO2_N                 H18              IO_L14N_T2_AD4N_SRCC_35   3.3V
9    DIO3_P                 K17              IO_L12P_T1_MRCC_35        3.3V
10   DIO3_N                 K18              IO_L12N_T1_MRCC_35        3.3V
11   DIO4_P                 L14              IO_L22P_T3_AD7P_35        3.3V
12   DIO4_N                 L15              IO_L22N_T3_AD7N_35        3.3V
13   DIO5_P                 L16              IO_L11P_T1_SRCC_35        3.3V
14   DIO5_N                 L17              IO_L11N_T1_SRCC_35        3.3V
15   DIO6_P / CAN1_RX       K16              IO_L24P_T3_AD15P_35       3.3V
16   DIO6_N / CAN1_TX       J16              IO_L24N_T3_AD15N_35       3.3V
17   DIO7_P / CAN0_RX       M14              IO_L23P_T3_35             3.3V
18   DIO7_N / CAN0_TX       M15              IO_L23N_T3_35             3.3V
19   NC
20   NC
21   NC
22   NC
23   NC
24   NC
25   GND
26   GND
===  =====================  ===============  ========================  ==============

.. note::

    To change the functionality of DIO6_P, DIO6_N, DIO7_P and DIO7_N from GPIO to CAN, please modify the **housekeeping** register value at **address 0x34**. For further details, please refer to the :ref:`FPGA register section <fpga_registers>`.

    The change can also be performed with the appropriate SCPI or API command. Please refer to the :ref:`CAN commands section <commands_can>` for further details.

All DIOx_y pins are LVCMOS33, with the following abs. max. ratings:

    * Min. -0.40 V
    * Max. 3.3 V + 0.55 V
    * < 8 mA drive strength


.. _E2_stem:

Extension connector E2
------------------------

    * +5 V, -3V4 power sources.
    * SPI, UART, I2C.
    * 4 slow ADCs.
    * 4 slow DACs.
    * Ext. clock for fast ADC.


===  ===========================  ===============  ==============================================  ==============
Pin  Description                  FPGA pin number  FPGA pin description                            Voltage levels
===  ===========================  ===============  ==============================================  ==============
1    +5 V
2    -3.3 V / -3.4 V [1]_
3    SPI (MOSI)                   E9               PS_MIO10_500                                    3.3 V
4    SPI (MISO)                   C6               PS_MIO11_500                                    3.3 V
5    SPI (SCK)                    D9               PS_MIO12_500                                    3.3 V
6    SPI (CS)                     E8               PS_MIO13_500                                    3.3 V
7    UART (TX)                    D5               PS_MIO8_500                                     3.3 V
8    UART (RX)                    B5               PS_MIO9_500                                     3.3 V
9    I2C (SCL)                    B13              PS_MIO50_501                                    3.3 V
10   I2C (SDA)                    B9               PS_MIO51_501                                    3.3 V
11   Ext com. mode                                                                                 GND (default)
12   GND
13   Analog Input 0               B19, A20         IO_L2P_T0_AD8P_35, IO_L2N_T0_AD8N_35            0-3.5 V
14   Analog Input 1               C20, B20         IO_L1P_T0_AD0P_35, IO_L1N_T0_AD0N_35            0-3.5 V
15   Analog Input 2               E17, D18         IO_L3P_T0_DQS_AD1P_35, IO_L3N_T0_DQS_AD1N_35    0-3.5 V
16   Analog Input 3               E18, E19         IO_L5P_T0_AD9P_35, IO_L5N_T0_AD9N_35            0-3.5 V
17   Analog Output 0              T10              IO_L1N_T0_34                                    0-1.8 V
18   Analog Output 1              T11              IO_L1P_T0_34                                    0-1.8 V
19   Analog Output 2              P15              IO_L24P_T3_34                                   0-1.8 V
20   Analog Output 3              U13              IO_L3P_T0_DQS_PUDC_B_34                         0-1.8 V
21   GND
22   GND
23   Ext Adc CLK+                                                                                  LVDS
24   Ext Adc CLK-                                                                                  LVDS
25   GND
26   GND
===  ===========================  ===============  ==============================================  ==============

.. [1] Red Pitaya Version 1.0 has -3.3 V on pin 2. Red Pitaya Version 1.1 has -3.4 V on pin 2.

.. note::

    **UART TX (PS_MIO08)** is an output only. It must be connected to GND or left floating at power-up (no external pull-ups)!


The pinout of the extension connectors is shown in the figure below.

.. figure:: img/Red_Pitaya_pinout.jpg
    :width: 700
    :align: center

|


Auxiliary analog input channels
--------------------------------

    * Number of channels: 4
    * Nominal sampling rate: 100 ksps (H)
    * ADC resolution 12 bits
    * Input voltage range: 0 - 3.5 V
    * Input coupling: DC
    * Connector: dedicated pins on IDC connector :ref:`E2 <E2_orig_gen>` (pins 13, 14, 15, 16)


Auxiliary analog output channels
---------------------------------

    * Number of channels: 4
    * Output type: Low pass filtered PWM (I)
    * PWM time resolution: 4 ns (1/250 MHz)
    * Analog output resolution: 8 bit
    * Analog output sample rate ≲ 3.2 MS/s
    * Analog output bandwidth ≈ 160 kHz
    * Analog outputs voltage range: 0 - 1.8 V
    * Output coupling: DC
    * Connector: dedicated pins on IDC connector :ref:`E2 <E2_orig_gen>` (pins 17, 18, 19, 20) V


General purpose digital input/output channels
----------------------------------------------

    * Number of digital input/output pins: 16
    * Voltage level: 3.3 V
    * Abs. min. voltage: -0.40 V
    * Abs. max. voltage: 3.3 V + 0.55 V
    * Current limitation: < 8 mA drive strength
    * Direction: configurable
    * Location: IDC connector :ref:`E1 <E1_orig_gen>`


Powering Red Pitaya through extension connector
================================================

The Red Pitaya can also be powered through pin 1 of the extension connector :ref:`E2 <E2_orig_gen>`, but in such a case, external protection must be provided by the user in order to protect the board!

.. figure:: img/schematics/Protection.png

|

Protection circuit between +5 V that is provided over the micro USB power connector and +5 VD that is connected to pin1 of the extension connector :ref:`E2 <E2_orig_gen>`.



.. _external_125_14:

External ADC clock
===================

The ADC clock can be provided by:

    * On board 125 MHz XO (default).
    * From an external source (through extension connector) - External clock :ref:`E2 <E2_orig_gen>`. (R25, R26 should be moved to location R23, R24).
    * From SATA connectors (directly from FPGA) - X-channel secondary/slave (R25, R26 should be relocated to R27, R28).

.. figure:: img/schematics/External_clk.png
    :align: center
    :width: 800

    Clock schematic


.. warning::

    We do not advise altering the board because users have reported problems after doing so. Every board made has undergone rigorous testing, which cannot be claimed for modified boards.
    Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.

**Instructions**

#. Remove R25 and R26 from the top side of the board.

    .. figure:: img/schematics/External_clock_top.png
        :alt: Top side schematic
        :align: center
        :width: 400

        Top side schematic

#. Relocate the desoldered resistors from R25 and R26 to:

    * R23 and R24 for external clock (Ext. ADC CLK+- pins).
    * R27 and R28 for X-channel secondary (SATA connectors).

    .. figure:: img/schematics/External_clock_bottom.png
        :alt: Bottom side schematic
        :align: center
        :width: 400

        Bottom side schematic

    .. figure:: img/schematics/External_clock_bottom_photo.png
        :alt: Bottom side photo
        :align: center
        :width: 400

        Bottom side photo

    .. figure:: img/schematics/External_clock_resistors.jpeg
        :alt: Bottom side all
        :align: center
        :width: 800

        Bottom side

QSPI
===========

The QSPI chip is by default not populated on Red Pitaya boards. For further information on board modifications, please contact support@redpitaya.com or info@redpitaya.com.

.. warning::

    Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.

Other specifications
=====================

For all other specifications please refer to the :ref:`Original Gen common hardware specifications <hw_specs_orig_gen>`.

|

.. rubric:: Footnotes

.. [#f1]  See the :ref:`STEMlab 125-14 External clock <top_125_14_EXT>` board for more information.
.. [#f2]  See the :ref:`Click Shield synchronisation section <click_shield>` and :ref:`Click Shield synchronisation examples <examples_multiboard_sync>`.



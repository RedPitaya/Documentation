.. _top_125_14_Z7020_LN:

########################
STEMlab 125-14 Z7020-LN
########################


.. figure:: ../125-14/img/STEMlab-125-14.jpg
    :width: 500


The STEMlab 125-14-Z7020-LN is a standard STEMlab 125-14 board that:


- comes with Zynq 7020 (rather than of 7010), which features 3 times more FPGA logic and more digital IOs on the E2 connector (for more information, see the board schematics).
- has populated additional linear analog power for analog power supplies to reduce RF inputs and outputs noise and consequently increase ENOB. To find out more about the performance of STEMlab 125-14 with DC analog power supplies, refer to Leonhard Neuhaus’s blog, |Red Pitaya DAC performance|.

.. |Red Pitaya DAC performance| raw:: html

    <a href="https://ln1985blog.wordpress.com/2016/02/07/red-pitaya-dac-performance/" target="_blank">Red Pitaya DAC performance</a>


Pinout
========

.. figure:: ../125-14/img/Red_Pitaya_pinout.jpg
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
    | FPGA                               | FPGA Xilinx Zynq 7020 SoC          |
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
    | Digital IOs                        | 22                                 |
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

.. note::

    Although we do not have specific measurements for the STEMlab 125-14 Z7020 LN board, the performance of the fast analog inputs is the same as for STEMlab 125-14. The output performance is covered in Leonhard Neuhaus's blog about |Red Pitaya DAC performance| (measurements with added linear power supplies).

You can find the measurements of the fast analog frontend here:

* :ref:`Original boards - STEMlab 125-14 <measurements_orig_gen>`.
* :ref:`Gen 2 - STEMlab 125-14 Gen 2 <measurements_gen2>`.



.. _schematics_125_14_Z7020:

Schematics
============

- `Schematics_STEM_125-14_v1.1_LN.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_125-14_v1.1_LN.pdf>`_
- `Schematics_STEM_125-14_v1.1_LN_Z7020.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_125-14_v1.1_LN_Z7020.pdf>`_

.. note::

    FULL HW schematics for the Red Pitaya board are not available. Red Pitaya has open-source code but not open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connections, and similar.


Mechanical Specifications and 3D Models
=========================================

- `3D_STEM_125-14_v1.0.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_125-14_v1.0.zip>`_


For all other specifications please refer to the standard :ref:`STEMlab 125-14 specs <top_125_14>`.


Extension connector STEMlab 125-14 Z7020-LN
=============================================

- Connector: 2 x 26 pins IDC (M)
- Power supply:
    - Available voltages: +5 V, +3.3 V, -4.2 V
    - Current limitations: 500 mA for +5 V and +3.3 V (to be shared between extension module and USB devices), 50 mA for -4.2 V supply.



.. _E1_14_Z20:

Extension connector E1
--------------------------

- 3V3 power source
- 22 single ended or 8 differential digital I/Os with 3.3 V logic levels
- 2 CAN busses

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
19   DIO8_P                 Y9               IO_L14P_T2_SRCC_13        3.3V
20   DIO8_N                 Y8               IO_L14N_T2_SRCC_13        3.3V
21   DIO9_P                 Y12              IO_L20P_T3_13             3.3V
22   DIO9_N                 Y13              IO_L20N_T3_13             3.3V
23   DIO10_P                Y7               IO_L13P_T2_MRCC_13        3.3V
24   DIO10_N                Y6               IO_L13N_T2_MRCC_13        3.3V
25   GND
26   GND
===  =====================  ===============  ========================  ==============


.. note::

   To switch the functionality of DIO6_P, DIO6_N, DIO7_P and DIO7_N from GPIO to CAN, please change the **Housekeeping** register value at address **0x34**. For more information, please reffer to the :ref:`FPGA register section <fpga_registers>` (this feature is currently under development).


All DIOx_y pins are LVCMOS33, with the following abs. max. ratings:
    - min. -0.40 V
    - max. 3.3 V + 0.55 V
    - <8 mA drive strength


.. _E2_14_Z20:

Extension connector E2
-------------------------

- +5 V, -3V4 power sources
- SPI, UART, I2C
- 4 slow ADCs
- 4 slow DACs
- Ext. clock for fast ADC

===  ======================  ===============  ==============================================  ==============
Pin  Description             FPGA pin number  FPGA pin description                            Voltage levels
===  ======================  ===============  ==============================================  ==============
1    +5V
2    -3V4
3    SPI (MOSI)              E9               PS_MIO10_500                                    3.3 V
4    SPI (MISO)              C6               PS_MIO11_500                                    3.3 V
5    SPI (SCK)               D9               PS_MIO12_500                                    3.3 V
6    SPI (CS)                E8               PS_MIO13_500                                    3.3 V
7    UART (TX)               D5               PS_MIO8_500                                     3.3 V
8    UART (RX)               B5               PS_MIO9_500                                     3.3 V
9    I2C (SCL)               B13              PS_MIO50_501                                    3.3 V
10   I2C (SDA)               B9               PS_MIO51_501                                    3.3 V
11   Ext com.mode                                                                             GND (default)
12   GND
13   Analog Input 0          B19, A20         IO_L2P_T0_AD8P_35, IO_L2N_T0_AD8N_35            0-3.5 V
14   Analog Input 1          C20, B20         IO_L1P_T0_AD0P_35, IO_L1N_T0_AD0N_35            0-3.5 V
15   Analog Input 2          E17, D18         IO_L3P_T0_DQS_AD1P_35, IO_L3N_T0_DQS_AD1N_35    0-3.5 V
16   Analog Input 3          E18, E19         IO_L5P_T0_AD9P_35, IO_L5N_T0_AD9N_35            0-3.5 V
17   Analog Output 0         T10              IO_L1N_T0_34                                    0-1.8 V
18   Analog Output 1         T11              IO_L1P_T0_34                                    0-1.8 V
19   Analog Output 2         P15              IO_L24P_T3_34                                   0-1.8 V
20   Analog Output 3         U13              IO_L3P_T0_DQS_PUDC_B_34                         0-1.8 V
21   GND
22   GND
23   Ext Adc CLK+                                                                             LVDS
24   Ext Adc CLK-                                                                             LVDS
25   GND
26   GND
===  ======================  ===============  ==============================================  ==============


.. note::

    **UART TX (PS_MIO08)** is an output only. It must be connected to GND or left floating at power-up (no external pull-ups)!


Other specifications
=====================

For all other specifications please refer  to the :ref:`Original Gen common hardware specifications <hw_specs_orig_gen>`.


|

.. rubric:: Footnotes

.. [#f1]  It is possible to convert the "STEMlab 125-14 Z7020 LN" board into an "STEMlab 125-14 Z7020 LN Ext. Clk" board. Please contact us for more information (info@redpitaya.com).
.. [#f2]  See the :ref:`Click Shield synchronisation section <click_shield>` and :ref:`Click Shield synchronisation examples <examples_multiboard_sync>`.

.. _top_125_14:

##############
STEMlab 125-14
##############

========
Pinout
========

.. figure:: img/Red_Pitaya_pinout.jpg
    :alt: Red Pitaya pinout
    :width: 700

==========================
Technical specifications
==========================

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Basic**                                                               |
    +====================================+====================================+
    | Processor                          | DUAL CORE ARM CORTEX A9            |
    +------------------------------------+------------------------------------+
    | FPGA                               | FPGA Xilinx Zynq 7010 SOC          |
    +------------------------------------+------------------------------------+
    | RAM                                | 512 MB (4 Gb)                      |
    +------------------------------------+------------------------------------+
    | System memory                      | Micro SD up to 32 GB               |
    +------------------------------------+------------------------------------+
    | Console connection                 | Micro USB                          |
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
    | USB                                | USB 2.0                            |
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
    | Absolute max. Input voltage range  | 30 V                               |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Input ESD protection               | Yes                                |
    +------------------------------------+------------------------------------+
    | Overload protection                | Protection diodes                  |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | DC - 60 MHz                        |
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
    | Connector type                     | SMA                                |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | 2 V / 10 ns                        |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | DC - 50 MHz                        |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Extension connector**                                                 | 
    +====================================+====================================+
    | Digital IOs                        | 16                                 |
    +------------------------------------+------------------------------------+
    | Analog inputs                      | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog input voltage range         | 0 – 3.5 V                          |
    +------------------------------------+------------------------------------+
    | Analog input resolution            | 12 bits                            |
    +------------------------------------+------------------------------------+
    | Analog input sample rate           | 100 kS/s                           |
    +------------------------------------+------------------------------------+
    | Analog outputs                     | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog output voltage range        | 0 – 1.8 V                          |
    +------------------------------------+------------------------------------+
    | Analog output resolution           | 8 bits                             |
    +------------------------------------+------------------------------------+
    | Analog output sample rate          | ≲ 3.2 MS/s                         |
    +------------------------------------+------------------------------------+
    | Analog output bandwidth            | ≈ 160 kHz                          |
    +------------------------------------+------------------------------------+
    | Communication interfaces           | I2C, SPI, UART, CAN                |
    +------------------------------------+------------------------------------+
    | Available voltages                 | +5 V, +3.3 V, -4 V                 |
    +------------------------------------+------------------------------------+
    | External ADC clock                 |  Yes                               |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Synchronisation**                                                     |
    +====================================+====================================+
    | Trigger input                      | Through extension connector        |
    +------------------------------------+------------------------------------+
    | Daisy chain connection             | Over SATA connection               |
    |                                    | (up to 500 Mbps)                   |
    +------------------------------------+------------------------------------+
    | Ref. clock input                   | N/A                                |
    +------------------------------------+------------------------------------+

.. note::
    
    For more information, please refer to the :ref:`Product comparison table <rp-board-comp>`.

.. _schematics_125_14:

============
Schematics
============

- `Red_Pitaya_Schematics_v1.0.1.pdf <https://downloads.redpitaya.com/doc//Red_Pitaya_Schematics_v1.0.1.pdf>`_

.. note::

    FULL HW schematics for the Red Pitaya board are not available. Red Pitaya has open-source code but not open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connections, and similar.

========================================
Mechanical Specifications and 3D Models
========================================

- `Red_Pitaya_3Dmodel_v1.0.zip <https://downloads.redpitaya.com/doc/Red_Pitaya_3Dmodel_v1.0.zip>`_


===========
Components
===========

- `ADC <https://www.analog.com/en/products/ltc2145-14.html>`_
- `DAC <https://www.analog.com/en/products/AD9767.html>`_
- `FPGA (Zynq 7010) <https://docs.xilinx.com/v/u/en-US/ds190-Zynq-7000-Overview>`_
- `DC-DC converter <https://www.analog.com/en/products/LTC3615.html>`_
- `Oscillator <https://eu.mouser.com/datasheet/2/417/bf-8746.pdf>`_
- `SRAM-DDR3 <https://www.digikey.com/en/products/detail/micron-technology-inc/MT41J256M16HA-125-E/4315785>`_
- `QSPI <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_ (NOT POPULATED - see :ref:`QSPI section <qspi_chip>` for more information)

.. note::

    STEMlab 125-14 Low Noise and STEMlab 125-14 4-Input feature Zynq 7020 instead of Zynq 7010.


====================================
Extension connector STEMlab 125-14
====================================

- Connector: 2 x 26 pins IDC (M) 

Power Supply
--------------

- **Available voltages**: +5 V, +3.3 V, -3.4 V 
- **Current limitations**:

    - 500 mA for +5 V (to be shared between extension module and USB devices)
    - 500 mA for +3V3 (to be shared between extension module and USB devices)
    - 50 mA for -3.4 V supply


.. _E1_stem:

Extension connector E1
------------------------

- +3V3 power source
- 16 single ended or 8 differential digital I/Os with 3.3 V logic levels
- 2x CAN

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
    - min. -0.40 V
    - max. 3.3 V + 0.55 V
    - < 8 mA drive strength


.. _E2_stem:

Extension connector E2
------------------------

- +5 V, -3V4 power supplies
- SPI, UART, I2C
- 4 x slow ADCs (100 kSps)
- 4 x slow DACs (100 kSps)
- Ext. clock for fast ADC
 
.. Table 6: Extension connector E2 pin description

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
9    I2C (SCL)                    B9               PS_MIO50_501                                    3.3 V         
10   I2C (SDA)                    B13              PS_MIO51_501                                    3.3 V         
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


The pinout of the extension connectors is shown in the figure below.

.. figure:: img/Red_Pitaya_pinout.jpg
    :width: 700
    :align: center

|

.. NEEDS CORRECTION - CHECK OTHER SOURCES FOR PROPER INFO

Auxiliary analog input channels
===============================

- Number of channels: 4 
- Nominal sampling rate: 100 ksps (H) 
- ADC resolution 12 bits 
- Connector: dedicated pins on IDC connector :ref:`E2 <E2>` (pins 13, 14, 15, 16) 
- Input voltage range: 0 to +3.5 V 
- Input coupling: DC 


Auxiliary analog output channels 
================================

- Number of channels: 4 
- Output type: Low pass filtered PWM (I) 
- PWM time resolution: 4 ns (1/250 MHz)
- Connector: dedicated pins on IDC connector :ref:`E2 <E2>` (pins 17, 18, 19, 20) v - Output voltage range: 0 to +1.8 V 
- Output coupling: DC 


General purpose digital input/output channels: (N) 
==================================================

- Number of digital input/output pins: 16 
- Voltage level: 3.3 V 
- Direction: configurable 
- Location: IDC connector :ref:`E1 <E1>` (pins 324) 


Powering Red Pitaya through extension connector
===============================================

The Red Pitaya can also be powered through pin 1 of the extension connector :ref:`E2 <E2>`, but in such a case, external protection must be provided by the user in order to protect the board!

.. figure:: img/schematics/Protection.png

|

Protection circuit between +5 V that is provided over the micro USB power connector and +5 VD that is connected to pin1 of the extension connector :ref:`E2 <E2>`.



.. _external_125_14:

===================
External ADC clock
===================

The ADC clock can be provided by:

    - On board 125 MHz XO (default)
    - From an external source/through extension connector :ref:`E2 <E2>` (R25, R26 should be moved to location R23, R24)
    - Directly from the FPGA (R25, R26 should be relocated to R27, R28) 

.. figure:: img/schematics/External_clk.png
    :alt: Schematic
    :align: center

    Schematic
    

.. warning::

    We do not advise altering the board because users have reported problems after doing so. Every board made has undergone rigorous testing, which cannot be claimed for modified boards. Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.


.. figure:: img/schematics/External_clock_top.png
    :alt: Top side schematic
    :align: center

    Top side schematic


.. figure:: img/schematics/External_clock_bottom.png
    :alt: Bottom side schematic
    :align: center

    Bottom side schematic

.. figure:: img/schematics/External_clock_bottom_photo.png
    :alt: Bottom side photo
    :align: center
    :width:  400px

    Bottom side photo

.. figure:: img/schematics/External_clock_resistors.jpeg
    :alt: Bottom side all
    :align: center

    Bottom side

===========
QSPI 
===========

The QSPI chip is by default not populated on Red Pitaya boards. For further information on board modifications, please contact support@redpitaya.com or info@redpitaya.com.

.. warning::

    Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.


.. _top_250_12:

#################
SIGNALlab 250-12
#################


.. figure:: img/Signal-Lab-250-12_full.jpg
    :width: 600

.. figure:: img/Signal-Lab-250-12.jpg
    :width: 600

.. note::

    The SIGNALlab 250-12 OEM board comes without the case, but includes the ribbed black heat sink that can be seen on the top of the first picture.
    The heatsink is mounted on the bottom side of the board.




Pinout
=========

.. figure:: ../125-14/img/Red_Pitaya_pinout.jpg
    :width: 700

|

Technical specifications
============================

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Basic**                                                               |
    +====================================+====================================+
    | Processor                          | Dual core ARM Cortex-A9            |
    +------------------------------------+------------------------------------+
    | FPGA                               | FPGA Xilinx Zynq 7020 SOC          |
    +------------------------------------+------------------------------------+
    | RAM                                | 1 GB (8 Gb)                        |
    +------------------------------------+------------------------------------+
    | System memory                      | Micro SD up to 32 GB               |
    +------------------------------------+------------------------------------+
    | Console connector                  | USB-C                              |
    +------------------------------------+------------------------------------+
    | Power connector                    | | Power Jack,                      |
    |                                    | | RJ45 (PoE version only)          |
    +------------------------------------+------------------------------------+
    | Power consumption                  | 24 V, 0.5 A max                    |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Connectivity**                                                        |
    +====================================+====================================+
    | Ethernet                           | 1 Gbit                             |
    +------------------------------------+------------------------------------+
    | USB                                | 2 x USB-A 2.0                      |
    +------------------------------------+------------------------------------+
    | Wi-Fi                              | Requires Wi-Fi dongle              |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **RF inputs**                                                           |
    +====================================+====================================+
    | RF input channels                  | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 250 MS/s                           |
    +------------------------------------+------------------------------------+
    | ADC resolution                     | 12 bit                             |
    +------------------------------------+------------------------------------+
    | Input impedance                    | 1 MΩ                               |
    +------------------------------------+------------------------------------+
    | Full scale voltage range           | ±1 V / ±20 V (SW selectable)       |
    +------------------------------------+------------------------------------+
    | Input coupling                     | AC / DC (SW selectable)            |
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
    | Connector type                     | BNC                                |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **RF outputs**                                                          |
    +====================================+====================================+
    | RF output channels                 | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 250 MS/s                           |
    +------------------------------------+------------------------------------+
    | DAC resolution                     | 14 bit                             |
    +------------------------------------+------------------------------------+
    | Load impedance                     | 50 Ω / Hi-Z                        |
    +------------------------------------+------------------------------------+
    | Voltage range                      | | ±2 V @ 50 Ω                      |
    |                                    | | ±10 V @ Hi-Z (SW selectable)     |
    +------------------------------------+------------------------------------+
    | Short circuit protection           | Yes                                |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | 10 V / 17 ns                       |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | DC - 60 MHz                        |
    +------------------------------------+------------------------------------+
    | Connector type                     | BNC                                |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Extension connector**                                                 | 
    +====================================+====================================+
    | Digital IOs                        | 19                                 |
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
    | Communication interfaces           | I2C, SPI, UART, CAN, USB           |
    +------------------------------------+------------------------------------+
    | Available voltages                 | +5 V, +3V3, -4 V                   |
    +------------------------------------+------------------------------------+
    | External ADC clock                 | Yes                                |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Synchronisation**                                                     |
    +====================================+====================================+
    | External trigger input             | BNC connector                      |
    +------------------------------------+------------------------------------+
    | External trigger input impedance   | | 10 kΩ (HW_rev 1.0-1.2a)          |
    |                                    | | 1 kΩ (HW_rev 1.2b)               |
    +------------------------------------+------------------------------------+
    | Trigger output [#f1]_              | E1 connector (DIO0_N)              |
    +------------------------------------+------------------------------------+
    | Daisy chain connection             | SATA connectors |br|               |
    |                                    | (up to 500 Mbps)                   |
    +------------------------------------+------------------------------------+
    | Ref. clock input                   | SMA connector (back)               |
    +------------------------------------+------------------------------------+

.. rubric:: Footnotes

.. [#f1]  See the :ref:`Click Shield synchronisation section <click_shield>` and :ref:`Click Shield synchronisation example <click_shield_sync_exam1>`.


.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Boot options**                                                        |
    +====================================+====================================+
    | SD card                            | Yes                                |
    +------------------------------------+------------------------------------+
    | QSPI                               | N/A                                |
    +------------------------------------+------------------------------------+
    | eMMC                               | N/A                                |
    +------------------------------------+------------------------------------+

.. note::
    
    For more information, please refer to the :ref:`Product comparison table <rp-board-comp>`.

.. |br| raw:: html

    <br/>


Schematics
============

- `STEM250-12_V1r1.pdf <https://downloads.redpitaya.com/doc/Customer-DOC_STEM250-12_V1r1.pdf>`_

.. note::

    Red Pitaya board HW FULL schematics are not available. Red Pitaya has an open-source code but not open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic has information on HW configuration, FPGA pin connection, and similar.



Mechanical Specifications and 3D Models
===========================================

- `SIGNALlab 250-12 V1r2 3D pdf <https://downloads.redpitaya.com/doc/SIGNAL250-12_V1r2_3Dpdf.zip>`_
- `SIGNALlab 250-12 V1r2 3D step <https://downloads.redpitaya.com/doc/SIGNAL250-12_V1r2_3Dstep.zip>`_


Components
==============

- `ADC <https://www.analog.com/en/products/AD9613.html>`_
- `DAC <https://www.analog.com/en/products/ad9746.html>`_
- `FPGA (Zynq 7020) <https://docs.xilinx.com/v/u/en-US/ds190-Zynq-7000-Overview>`_
- `Current Feedback 1.5 GHz Op. Amp. <https://www.analog.com/en/products/AD8000.html>`_
- `Voltage Feedback 1 GHz FastFET Op. Amp. <https://www.analog.com/en/products/ada4817-1.html>`_
- `Low Power Differential ADC Driver <https://www.analog.com/en/products/ada4817-1.html>`_

.. * `SRAM-DDR3 <https://www.digikey.com/en/products/detail/micron-technology-inc/MT41J256M16HA-125-E/4315785>`_
.. * `QSPI <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_



Extension connector SIGNALlab
================================

The SIGNALlab 250-12 board, with the exception of "bare OEM" boards, is enclosed in an aluminium housing which should be removed to allow access to the E1 and E2 extension connectors.

- Connector: 2 x 26 pins IDC (M) 
- Power supply: 
    - Available voltages: +5 V, +3.3 V, -5.4 V
    - Current limitations: 200 mA for +5 V, 50 mA  for +3.3 V (to be shared between extension module and USB devices), 10 mA for -5.4 V supply. 


.. _E1_signal:

Extension connector E1
--------------------------

- 3V3 power source
- 19 single ended or 9 differential digital I/Os with 3.3 V logic levels
- 2 CAN busses

===  =====================  ===============  ========================  ==============
Pin  Description            FPGA pin number  FPGA pin description      Voltage levels
===  =====================  ===============  ========================  ==============
1    3V3                                                                             
2    3V3                                                                             
3    DIO0_P                 W10              IO_L16P_T2_13             3.3V          
4    DIO0_N                 W9               IO_L16N_T2_13             3.3V          
5    DIO1_P                 T9               IO_L12P_T1_MRCC_13        3.3V          
6    DIO1_N                 U10              IO_L12N_T1_MRCC_13        3.3V          
7    DIO2_P                 Y9               IO_L14P_T2_SRCC_13        3.3V          
8    DIO2_N                 Y8               IO_L14N_T2_SRCC_13        3.3V          
9    DIO3_P                 U9               IO_L17P_T2_13             3.3V          
10   DIO3_N                 U8               IO_L17N_T2_13             3.3V          
11   DIO4_P                 V8               IO_L15P_T2_DQS_13         3.3V          
12   DIO4_N                 W8               IO_L15N_T2_DQS_13         3.3V          
13   DIO5_P                 V11              IO_L21P_T3_DQS_13         3.3V          
14   DIO5_N                 V10              IO_L21N_T3_DQS_13         3.3V          
15   DIO6_P / CAN1_RX       W11              IO_L18P_T2_13             3.3V          
16   DIO6_N / CAN1_TX       Y11              IO_L18N_T2_13             3.3V          
17   DIO7_P / CAN0_RX       Y12              IO_L20P_T3_13             3.3V          
18   DIO7_N / CAN0_TX       Y13              IO_L20N_T3_13             3.3V          
19   DIO8_P                 Y7               IO_L13P_T2_MRCC_13        3.3V          
20   DIO8_N                 Y6               IO_L13N_T2_MRCC_13        3.3V          
21   DIO9_P                 U5               IO_L19N_T3_VREF_13        3.3V          
22   +5VUSB3                                                                         
23   USB2_P                                                                          
24   USB2_N                                                                          
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


.. _E2_signal:

Extension connector E2
-------------------------

- +5 V, -5.4 V power sources
- SPI, UART, I2C
- 4 slow ADCs
- 4 slow DACs
- Ext. clock for fast ADC
        
.. Table 6: Extension connector E2 pin description
        
===  ======================  ===============  ==============================================  ==============
Pin  Description             FPGA pin number  FPGA pin description                            Voltage levels
===  ======================  ===============  ==============================================  ==============
1    +5V                                                                                                    
2    -5.4 V                                                                                                   
3    SPI (MOSI)              E9               PS_MIO10_500                                    3.3 V         
4    SPI (MISO)              C6               PS_MIO11_500                                    3.3 V         
5    SPI (SCK)               D9               PS_MIO12_500                                    3.3 V         
6    SPI (CS)                E8               PS_MIO13_500                                    3.3 V         
7    UART (TX)               D5               PS_MIO8_500                                     3.3 V         
8    UART (RX)               B5               PS_MIO9_500                                     3.3 V         
9    I2C (SCL)               B9               PS_MIO50_501                                    3.3 V         
10   I2C (SDA)               B13              PS_MIO51_501                                    3.3 V         
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

For all other specifications please refer to the schematics and the :ref:`common hardware specifications <hw_specs>`.

Please note that the measurements on inputs and outputs differ from the standard STEMlab 125-14.


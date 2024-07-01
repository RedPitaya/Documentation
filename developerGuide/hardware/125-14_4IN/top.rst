.. _top_125_14_4-IN:

#######################
STEMlab 125-14 4-Input
#######################

STEMlab 125-14 4-Input is a single-board RF signal acquisition platform that offers the same general hardware features as STEMlab 125-14. The main differences/benefits are that:

* There are 4 analog input channels @ 125 Msps & 14 bits (instead of 2 inputs and 2 outputs).
* RF inputs come with better performance (less crosstalk, noise, and distortions).
* Zynq 7020 (bigger FPGA that offers more processing capabilities and more digital IO pins available on the extension connector).
* Switching between internal and external clocks can be done using a jumper or control signal on the extension connector. Connect the CLK_SEL pin to GND for the board to switch to EXT clock and to 3V3 (Vcc) to use the internal clock.

.. note::

   **Booting without the external clock present?**
   When the CLK_SEL pin is driven to GND, the official Red Pitaya OS will not boot without providing an external clock as it relies on reading the FPGA register map, which is available if the ADC clock is present.
   However, by modifying the software, the Linux OS itself can boot even without the external clock present, but please note it will crash when trying to read from the FPGA without the external clock present.

Pinout
========

.. figure:: ../125-14/img/Red_Pitaya_pinout.jpg
    :width: 700


Technical specifications
===========================

.. table::
    :widths: 10 18

    +------------------------------------+------------------------------------+
    | **Basic**                                                               |
    +====================================+====================================+
    | Processor                          | DUAL CORE ARM CORTEX A9            |
    +------------------------------------+------------------------------------+
    | FPGA                               | FPGA Xilinx Zynq 7020 SOC          |
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
    :widths: 10 18

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
    :widths: 10 18

    +------------------------------------+------------------------------------+
    | **RF inputs**                                                           |
    +====================================+====================================+
    | RF input channels                  | 4                                  |
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
    :widths: 10 18

    +------------------------------------+------------------------------------+
    | **RF outputs**                                                          |
    +====================================+====================================+
    | RF output channels                 | N/A                                |
    +------------------------------------+------------------------------------+
    | Sample rate                        | N/A                                |
    +------------------------------------+------------------------------------+
    | DAC resolution                     | N/A                                |
    +------------------------------------+------------------------------------+
    | Load impedance                     | N/A                                |
    +------------------------------------+------------------------------------+
    | Voltage range                      | N/A                                |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Short circuit protection           | N/A                                |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Connector type                     | N/A                                |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | N/A                                |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | N/A                                |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 10 18

    +------------------------------------+------------------------------------+
    | **Extension connector**                                                 | 
    +====================================+====================================+
    | Digital IOs                        | 22                                 |
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
    :widths: 10 18

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

.. note::
  Jumper orientation can affect the measurements taken with Red Pitaya. Check the :ref:`Jumper Orientation <jumper_pos>` for more details.


Switching between internal and external clock
================================================

Driving the *CLK_SEL* pin to GND (logic 0) switches the board to external clock mode. When the pin is driven to 3V3 (logic 1) or left floating, the board operates in the internal clock mode (on-board oscillator).

When STEMlab 125-14 4-Input is in External clock mode the ADC clock must be provided from an external source clock. An external clock should be connected to the *Ext ADC CLK- and +* pins. According to the ADC spec, external clock signal levels should be LVDS in the range from 1 MHz to 125 MHz.

.. note::

    In the External clock mode, the OS will not boot without providing an external clock.


Schematics
==============

* `STEMlab_125-14-4_IN_V1r3.PDF <https://downloads.redpitaya.com/doc/Red_Pitaya_Schematics_STEM_125-14-4_IN_V1r3.PDF>`_


Mechanical Specifications and 3D Models
============================================

* `STEMlab_125-14-4_IN_V1r3.zip <https://downloads.redpitaya.com/doc/STEM125-14-4_IN_V1r3_3Dstep.zip>`_


Extension connector STEMlab 125-14 4-Input
=============================================

- Connector: 2 x 26 pins IDC (M) 
- Power supply: 
    - Available voltages: +5 V, +3.3 V, -3.3 V
    - Current limitations: 500 mA for +5 V and +3.3 V (to be shared between extension module and USB devices), 50 mA for -3.3 V supply. 


.. _E1_4-IN:

Extension connector E1
--------------------------

- 3V3 power source
- 22 single ended or 8 differential digital I/Os with 3.3 V logic levels


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


.. _E2_4-in:

Extension connector E2
-------------------------

- +5 V, -4V2 power source
- SPI, UART, I2C
- 4 x slow ADCs
- 4 x slow DACs
- Ext. clock for fast ADC


.. Table 6: Extension connector E2 pin description

===  ======================  ===============  ==============================================  ==============
Pin  Description             FPGA pin number  FPGA pin description                            Voltage levels
===  ======================  ===============  ==============================================  ==============
1    +5V                                                                                                    
2    -4V2                                                                                                   
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
21   CLK SEL                                                                                  3.3 V         
22   GND                                                                                                    
23   Ext Adc CLK+                                                                             LVDS          
24   Ext Adc CLK-                                                                             LVDS          
25   GND                                                                                                    
26   GND                                                                                                    
===  ======================  ===============  ==============================================  ==============


.. note::

    UART TX (PS_MIO08) is output only and must be low level at power-up (no external pull-ups)!


Other specifications
=====================

For all other specifications please refer to standard :ref:`STEMlab 125-14 specs <top_125_14>`.





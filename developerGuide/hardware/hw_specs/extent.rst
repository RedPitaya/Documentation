
######################
Extension connector
######################

- Connector: 2 x 26 pins IDC

.. figure:: img/Red_Pitaya_pinout.jpg
    :width: 800

|

Extension connector power supply
==================================

- **Available voltages**: +5 V, +3.3 V, -3.4 V 
- **Current limitations**:

    - 500 mA for +5 V (to be shared between extension module and USB devices)
    - 500 mA for +3V3 (to be shared between extension module and USB devices)
    - 50 mA for -3.4 V supply


.. _E1:

Extension connector E1
======================

Please note that there are differences in the FPGA pin numbers for different Red Pitaya board models. For precise configuration details, please refer to the board model documentation and schematics.

.. tabs::

    .. tab:: STEMlab 125-14

        - +3V3 power source
        - 16 single ended or 8 differential digital I/Os with 3.3 V logic levels
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
        19   NC                                                                              
        20   NC                                                                              
        21   NC                                                                              
        22   NC                                                                              
        23   NC                                                                              
        24   NC                                                                              
        25   GND                                                                             
        26   GND                                                                             
        ===  =====================  ===============  ========================  ==============

    .. tab:: SDRlab 122-16

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

    .. tab:: SIGNALlab 250-12

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

    .. tab:: STEMlab 125-14 4-Input

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
        
    To change the functionality of DIO6_P, DIO6_N, DIO7_P and DIO7_N from GPIO to CAN, please modify the **housekeeping** register value at **address 0x34**. For further details, please refer to the :ref:`FPGA register section <fpga_registers>`.
        
    The change can also be performed with the appropriate SCPI or API command. Please refer to the :ref:`CAN commands section <commands_can>` for further details.
        
All DIOx_y pins are LVCMOS33, with the following abs. max. ratings:
    - min. -0.40 V
    - max. 3.3 V + 0.55 V
    - < 8 mA drive strength

.. _E2:

Extension connector E2
======================

.. tabs::

    .. tab:: STEMlab 125-14

        - +5 V, -3V4 power sources
        - SPI, UART, I2C
        - 4 slow ADCs
        - 4 slow DACs
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

    .. tab:: SDRlab 122-16

        - +5 V power source
        - SPI, UART, I2C
        - 4 slow ADCs
        - 4 slow DACs
        - Ext. clock for fast ADC

        .. Table 6: Extension connector E2 pin description

        ===  ======================  ===============  ==============================================  ==============
        Pin  Description             FPGA pin number  FPGA pin description                            Voltage levels
        ===  ======================  ===============  ==============================================  ==============
        1    +5V                                                                                                    
        2    NC                                                                                                   
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

    .. tab:: SIGNALlab 250-12

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

    .. tab:: STEMlab 125-14 4-Input

        - +5 V, -3V4 power sources
        - SPI, UART, I2C
        - 4 slow ADCs
        - 4 slow DACs
        - Ext. clock for fast ADC

        .. Table 6: Extension connector E2 pin description

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

    **UART TX (PS_MIO08)** is an output only. It must be connected to GND or left floating at power-up (no external pull-ups)!

The pinout of the extension connectors is shown in the figure below.

.. figure:: img/Red_Pitaya_pinout.jpg
    :width: 700
    :align: center

|

Auxiliary analog input channels
===============================

- Number of channels: 4 
- Nominal sampling rate: 100 ksps [#]_ 
- ADC resolution 12 bits 
- Input voltage range: 0 - 3.5 V 
- Input coupling: DC 
- Connector: dedicated pins on IDC connector :ref:`E2 <E2>` (pins 13, 14, 15, 16) 

.. [#] The default software enables sampling at a CPU-dependent speed. To acquire data at a 100 ksps rate, additional FPGA processing must be implemented.


Auxiliary analog output channels 
================================

- Number of channels: 4 
- Output type: Low pass filtered PWM [#]_
- PWM time resolution: 4 ns (1/250 MHz)
- Analog output resolution: 8 bit
- Analog output sample rate ≲ 3.2 MS/s
- Analog output bandwidth ≈ 3.2 MS/s
- Analog outputs voltage range: 0 - 1.8 V
- Output coupling: DC 
- Connector: dedicated pins on IDC connector :ref:`E2 <E2>` (pins 17, 18, 19, 20) V

.. [#] The output is passed through a first-order low-pass filter. Should additional filtering be required, this can be applied externally in line with the specific requirements of the application.  



General purpose digital input/output channels 
==================================================

.. note::

    To ensure compliance with speed limitations on digital General Purpose Input/Output pins, these are directly connected to the FPGA.
    It is the responsibility of the user to address FPGA decoupling and pin protection within extension module designs. The user is also responsible for pin handling.

.. tabs::

    .. tab:: STEMlab 125-14

        - Number of digital input/output pins: 16
        - Voltage level: 3.3 V
        - Abs. min. voltage: -0.40 V
        - Abs. max. voltage: 3.3 V + 0.55 V
        - Current limitation: < 8 mA drive strength
        - Direction: configurable 
        - Location: IDC connector :ref:`E1 <E1>`

    .. tab:: SDRlab 122-16

        - Number of digital input/output pins: 22
        - Voltage level: 3.3 V 
        - Abs. min. voltage: -0.40 V
        - Abs. max. voltage: 3.3 V + 0.55 V
        - Current limitation: < 8 mA drive strength
        - Direction: configurable 
        - Location: IDC connector :ref:`E1 <E1>`

    .. tab:: SIGNALlab 250-12

        - Number of digital input/output pins: 19
        - Voltage level: 3.3 V 
        - Abs. min. voltage: -0.40 V
        - Abs. max. voltage: 3.3 V + 0.55 V
        - Current limitation: < 8 mA drive strength
        - Direction: configurable 
        - Location: IDC connector :ref:`E1 <E1>`

    .. tab:: STEMlab 125-14 4-Input

        - Number of digital input/output pins: 22
        - Voltage level: 3.3 V
        - Abs. min. voltage: -0.40 V
        - Abs. max. voltage: 3.3 V + 0.55 V
        - Current limitation: < 8 mA drive strength
        - Direction: configurable
        - Location: IDC connector :ref:`E1 <E1>`


Powering Red Pitaya through extension connector
===============================================

The Red Pitaya can also be powered through pin 1 of the extension connector :ref:`E2 <E2>`, but in such a case, external protection must be provided by the user in order to protect the board!

.. figure:: img/schematics/Protection.png

|

Protection circuit between +5 V that is provided over the micro USB power connector and +5 VD that is connected to pin1 of the extension connector :ref:`E2 <E2>`.

.. note::

    The information provided by Red Pitaya d.o.o. is believed to be accurate and reliable. However, no liability is accepted for its use. Please note that the contents may be subject to change without prior notice. 

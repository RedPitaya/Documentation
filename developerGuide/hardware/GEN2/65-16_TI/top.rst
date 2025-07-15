.. _top_65_16_TI_gen2:

#################################
STEMlab 65-16 TItanium Gen 2
#################################

.. note::

    **This page is currently under construction.** All relevant information will be added before the official Gen 2 release.
    Please check back later for updates.


.. TODO replace pictures

.. .. figure:: img/STEMlab-125-14.jpg
..     :width: 500


.. contents:: **Index**
    :local:
    :backlinks: none


Features
=============

* TI ADC3663 dual-channel 16-bit, 65 MSps SAR ADC with high SNR & low latency  
* TI DAC2904Y 14-bit, 125 MSps dual-channel DAC with low-jitter outputs  
* TI LMK03318 ultra-low-jitter clock generator (100 fs RMS @ >100 MHz)  
* Ultra-low RF output jitter: 5 ps RMS @ 40 MHz (same DAC/clock path as 125-14 TI)  
* All Gen 2 front-end improvements: improved ENOB, lower noise/jitter  



Pinout
========

.. TODO replace pinout

.. .. figure:: img/Red_Pitaya_pinout.jpg
..     :alt: Red Pitaya pinout
..     :width: 700

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
    | FPGA                               | FPGA AMD (Xilinx) Zynq 7020 SoC    |
    +------------------------------------+------------------------------------+
    | RAM                                | 1 GB (8 Gb)                        |
    +------------------------------------+------------------------------------+
    | Core clock frequency               | 125 MHz                            |
    +------------------------------------+------------------------------------+
    | System memory                      | Micro SD up to 32 GB               |
    +------------------------------------+------------------------------------+
    | Serial console connector           | USB-C                              |
    +------------------------------------+------------------------------------+
    | Power connector                    | USB-C                              |
    +------------------------------------+------------------------------------+
    | Power consumption                  | 5 V, 3 A max                       |
    +------------------------------------+------------------------------------+
    | |br|                                                                    |
    | **Connectivity**                                                        |
    +------------------------------------+------------------------------------+
    | Ethernet                           | 1 Gbit                             |
    +------------------------------------+------------------------------------+
    | USB                                | USB-C 2.0                          |
    +------------------------------------+------------------------------------+
    | Wi-Fi                              | requires Wi-Fi dongle              |
    +------------------------------------+------------------------------------+
    | |br|                                                                    |
    | **RF inputs**                                                           |
    +------------------------------------+------------------------------------+
    | RF input channels                  | 2                                  |
    +------------------------------------+------------------------------------+
    | Sampling rate                      | 62.5 MS/s                          |
    +------------------------------------+------------------------------------+
    | ADC resolution                     | 16 bit                             |
    +------------------------------------+------------------------------------+
    | Input impedance                    | 1 MΩ / 10 pF                       |
    +------------------------------------+------------------------------------+
    | Full scale voltage range           | | ±1 V (LV)                        |
    |                                    | | ±20 V (HV)                       |
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
    | Bandwidth                          | DC - 30 MHz                        |
    +------------------------------------+------------------------------------+
    | Connector type                     | SMA                                |
    +------------------------------------+------------------------------------+
    | |br|                                                                    |
    | **RF outputs**                                                          |
    +------------------------------------+------------------------------------+
    | RF output channels                 | 2                                  |
    +------------------------------------+------------------------------------+
    | Sampling rate                      | 125 MS/s                           |
    +------------------------------------+------------------------------------+
    | DAC resolution                     | 14 bit                             |
    +------------------------------------+------------------------------------+
    | Load impedance                     | 50 Ω / Hi-Z                        |
    +------------------------------------+------------------------------------+
    | Voltage range                      | | ±1 V @ 50 Ω                      |
    |                                    | | ±2 V @ Hi-Z Ω                    |
    +------------------------------------+------------------------------------+
    | Short circuit protection           | Yes                                |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | 2 V / 10 ns                        |
    +------------------------------------+------------------------------------+
    | RF Output Jitter @40 MHz           | 5 ps                               |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | DC - 30 MHz                        |
    +------------------------------------+------------------------------------+
    | Connector type                     | SMA                                |
    +------------------------------------+------------------------------------+
    | |br|                                                                    |
    | **Extension connectors**                                                |
    +------------------------------------+------------------------------------+
    | Digital GPIOs                      | 22                                 |
    +------------------------------------+------------------------------------+
    | Digital voltage levels             | 3.3 V                              |
    +------------------------------------+------------------------------------+
    | High-speed diff. pairs (E3)        | N/A                                |
    +------------------------------------+------------------------------------+
    | | High-speed diff. pair voltage    | N/A                                |
    | | levels (E3)                      |                                    |
    +------------------------------------+------------------------------------+
    | Analog inputs                      | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog input voltage range         | 0 - 3.5 V                          |
    +------------------------------------+------------------------------------+
    | Analog input resolution            | 12 bit                             |
    +------------------------------------+------------------------------------+
    | Analog input sampling rate         | 100 kS/s                           |
    +------------------------------------+------------------------------------+
    | Analog outputs                     | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog output voltage range        | 0 - 1.8 V                          |
    +------------------------------------+------------------------------------+
    | Analog output resolution           | 8 bit                              |
    +------------------------------------+------------------------------------+
    | Analog output sampling rate        | ≲ 3.2 MS/s                         |
    +------------------------------------+------------------------------------+
    | Analog output bandwidth            | ≈ 120 kHz                          |
    +------------------------------------+------------------------------------+
    | Communication interfaces           | I2C, SPI, UART, CAN                |
    +------------------------------------+------------------------------------+
    | Available voltages                 | ±5 V, +3V3                         |
    +------------------------------------+------------------------------------+
    | External ADC clock                 | Yes                                |
    +------------------------------------+------------------------------------+
    | E3 connector                       | No                                 |
    +------------------------------------+------------------------------------+
    | |br|                                                                    |
    | **Synchronisation**                                                     |
    +------------------------------------+------------------------------------+
    | External trigger input             | E1 connector (DIO0_P)              |
    +------------------------------------+------------------------------------+
    | External trigger input impedance   | Hi-Z (digital input)               |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Trigger output [#f1]_              | E1 connector (DIO0_N)              |
    +------------------------------------+------------------------------------+
    | Daisy chain connection             | | S1 and S2 USB-C connectors       |
    |                                    | | (up to 500 Mb/s)                 |
    +------------------------------------+------------------------------------+
    | Ref. clock input                   | N/A                                |
    +------------------------------------+------------------------------------+
    | |br|                                                                    |
    | **Boot options**                                                        |
    +------------------------------------+------------------------------------+
    | SD card                            | Yes                                |
    +------------------------------------+------------------------------------+
    | QSPI                               | No                                 |
    +------------------------------------+------------------------------------+
    | eMMC                               | No                                 |
    +------------------------------------+------------------------------------+


.. note::
    
    For more information, please refer to the |Gen 2 comparison table|.

.. |br| raw:: html

    <br/>


Measurements
=================

.. note::

    We do not have specific measurements for the STEMlab 65-16 TI board yet.
    
You can find the measurements of the fast analog frontend here:

* :ref:`Gen 1 - STEMlab 125-14 Gen 1 <measurements_gen1>`.
* :ref:`Gen 2 - STEMlab 125-14 Gen 2 <measurements_gen2>`.


.. _schematics_65_16_TI_gen2:

Schematics
============

.. TODO add schematics


.. note::

    Full hardware schematics for the Red Pitaya board are not available. Red Pitaya has open-source code but not open hardware schematics. Nonetheless, development schematics are available. This schematic will give you information about hardware configuration, FPGA pin connections, and similar.


Mechanical Specifications and 3D Models
========================================

.. TODO add schematics and 3D models


Components
===========

    * `ADC <https://www.ti.com/product/ADC3663>`_.
    * `DAC <https://www.ti.com/product/DAC2904>`_.
    * `FPGA (Zynq 7020) <https://docs.amd.com/v/u/en-US/ds190-Zynq-7000-Overview>`_ 667 MHz.
    * `Oscillator <https://support.epson.biz/td/api/doc_check.php?dl=brief_SG3225VAN&lang=en>`_.
    * `NB6L72`_.

Texas Instruments components
-----------------------------

    * TPD4E02B04DQA
    * CAHCT1G125QDCKRG4Q
    * SN74LVC1G86DCKR
    * TXS02612RTWR
    * LSF0102DTM
    * PCA9306DCUR
    * TPS25821
    * DAC2904Y
    * ADC3663IRSBR
    * THS4541QRGTR
    * OPA810IDBVR
    * OPA695IDBVR
    * LM393DGK
    * LMK03318
    * TPS62080ADSGT
    * LM27762DSSR

Analog Devices components
---------------------------

    * ADP7182ACPZ
    * ADP151ACPZ-3.3
    * ADM7170ACPZ-R7
    * AD8007AKS-R2 (Liner technologies)


Extension connectors
======================

    * E1 and E2 connectors: `2 x 13 pins IDC 2.54 mm pitch <https://www.digikey.com/en/products/detail/adam-tech/BHR-26-VUA/9832284>`_.

The pinout of the extension connectors is shown in the figure below.

.. .. figure:: img/Red_Pitaya_pinout.jpg
..     :width: 700
..     :align: center

.. note::

    When looking for mating connectors for custom Red Pitaya shields, `double height elevated sockets <https://www.digikey.com/en/products/detail/samtec-inc/ESW-113-33-T-D/6693225>`_ are needed to clear the heatsink and ethernet connector on the board.
    Any connectors with *insulation height* of 0.635" (16.13mm) or greater will work.


Power Supply
--------------

    * **Available voltages**: ±5 V, +3.3 V.
    * **Current limitations**:

        * 0.5 A for +5 V (to be shared between extension module and USB devices).
        * 0.5 A for -5 V (to be shared between extension module and USB devices).
        * 0.5 A for +3V3 (to be shared between extension module and USB devices).

.. TODO add voltage limitations


Extension connector E1
------------------------

The E1 extension connector features the following ports:

    * Two +3V3 power sources (max 0.5 A of current).
    * 22 single ended or 11 differential digital I/Os with 3.3 V logic levels.
    * Two CAN busses.

    .. TODO current limits!

All DIOx_y pins are LVCMOS33, with the following abs. max. ratings:

    * Min. -0.40 V.
    * Max. 3.3 V + 0.55 V.
    * < 8 mA drive strength.
        
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| Pin | Description           | FPGA pin number   | FPGA pin description                          | Voltage levels |
+=====+=======================+===================+===============================================+================+
| 1   | 3V3                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 2   | 3V3                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 3   | DIO0_P / EXT TRIG     | G17               | IO_L16P_T2_35                                 | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 4   | DIO0_N / TRIG OUT     | G18               | IO_L16N_T2_35                                 | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 5   | DIO1_P                | H16               | IO_L13P_T2_MRCC_35                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 6   | DIO1_N                | H17               | IO_L13N_T2_MRCC_35                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 7   | DIO2_P                | J18               | IO_L14P_T2_AD4P_SRCC_35                       | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 8   | DIO2_N                | H18               | IO_L14N_T2_AD4N_SRCC_35                       | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 9   | DIO3_P                | K17               | IO_L12P_T1_MRCC_35                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 10  | DIO3_N                | K18               | IO_L12N_T1_MRCC_35                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 11  | DIO4_P                | L14               | IO_L22P_T3_AD7P_35                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 12  | DIO4_N                | L15               | IO_L22N_T3_AD7N_35                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 13  | DIO5_P                | L16               | IO_L11P_T1_SRCC_35                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 14  | DIO5_N                | L17               | IO_L11N_T1_SRCC_35                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 15  | DIO6_P / CAN1_RX      | K16               | IO_L24P_T3_AD15P_35                           | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 16  | DIO6_N / CAN1_TX      | J16               | IO_L24N_T3_AD15N_35                           | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 17  | DIO7_P / CAN0_RX      | M14               | IO_L23P_T3_35                                 | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 18  | DIO7_N / CAN0_TX      | M15               | IO_L23N_T3_35                                 | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 19  | DIO8_P                | Y9                | IO_L14P_T2_SRCC_13                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 20  | DIO8_N                | Y8                | IO_L14N_T2_SRCC_13                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 21  | DIO9_P                | Y12               | IO_L20P_T3_13                                 | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 22  | DIO9_N                | Y13               | IO_L20N_T3_13                                 | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 23  | DIO10_P               | Y7                | IO_L13P_T2_MRCC_13                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 24  | DIO10_N               | Y6                | IO_L13N_T2_MRCC_13                            | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 25  | GND                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 26  | GND                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+

.. note::
        
    To change the functionality of DIO6_P, DIO6_N, DIO7_P and DIO7_N from GPIO to CAN, please modify the **housekeeping** register value at **address 0x34**. For further details, please refer to the :ref:`FPGA register section <fpga_registers>`.
        
    The change can also be performed with the appropriate SCPI or API command. Please refer to the :ref:`CAN commands section <commands_can>` for further details.



Extension connector E2
------------------------

The E2 extension connector features the following ports:

    * ±5 V power sources (max 3 A of current per port).
    * SPI, UART, I2C communication interfaces.
    * 4 slow ADCs.
    * 4 slow DACs (PWM).
    * External clock input.

+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| Pin | Description           | FPGA pin number   | FPGA pin description                          | Voltage levels |
+=====+=======================+===================+===============================================+================+
| 1   | +5V                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 2   | -5V                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 3   | SPI (MOSI)            | E9                | PS_MIO10_500                                  | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 4   | SPI (MISO)            | C6                | PS_MIO11_500                                  | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 5   | SPI (SCK)             | D9                | PS_MIO12_500                                  | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 6   | SPI (CS)              | E8                | PS_MIO13_500                                  | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 7   | UART (TX)             | D5                | PS_MIO8_500                                   | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 8   | UART (RX)             | B5                | PS_MIO9_500                                   | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 9   | I2C (SCL)             | B13               | PS_MIO50_501                                  | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 10  | I2C (SDA)             | B9                | PS_MIO51_501                                  | 3V3            |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 11  | Ext com. mode (AIN)   |                   |                                               | Ext. GND       |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 12  | GND                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 13  | Analog Input 0        | B19, A20          | IO_L2P_T0_AD8P_35, IO_L2N_T0_AD8N_35          | 0-3.5 V        |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 14  | Analog Input 1        | C20, B20          | IO_L1P_T0_AD0P_35, IO_L1N_T0_AD0N_35          | 0-3.5 V        |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 15  | Analog Input 2        | E17, D18          | IO_L3P_T0_DQS_AD1P_35, IO_L3N_T0_DQS_AD1N_35  | 0-3.5 V        |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 16  | Analog Input 3        | E18, E19          | IO_L5P_T0_AD9P_35, IO_L5N_T0_AD9N_35          | 0-3.5 V        |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 17  | Analog Output 0       | T10               | IO_L1N_T0_34                                  | 0-1.8 V        |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 18  | Analog Output 1       | T11               | IO_L1P_T0_34                                  | 0-1.8 V        |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 19  | Analog Output 2       | P15               | IO_L24P_T3_34                                 | 0-1.8 V        |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 20  | Analog Output 3       | U13               | IO_L3P_T0_DQS_PUDC_B_34                       | 0-1.8 V        |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 21  | ADC CLK Sel.          |                   |                                               | 3V3 [#f3]_     |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 22  | GND                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 23  | Ext. ADC Clk+ [#f2]_  | U18               | IO_L12P_T1_MRCC_34                            | LVDS [#f3]_    |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 24  | Ext. ADC Clk- [#f2]_  | U19               | IO_L12P_T1_MRCC_34                            | LVDS [#f3]_    |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 25  | GND                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+
| 26  | GND                   |                   |                                               |                |
+-----+-----------------------+-------------------+-----------------------------------------------+----------------+



Auxiliary analog input channels
--------------------------------

+--------------------------+----------------------------------+
| Number of channels       | 4                                |
+--------------------------+----------------------------------+
| ADC resolution           | 12 bits                          |
+--------------------------+----------------------------------+
| Sampling rate            | 100 kS/s [#f4]_                  |
+--------------------------+----------------------------------+
| Input filter bandwidth   | 120 kHz                          |
+--------------------------+----------------------------------+
| Input voltage range      | 0 - 3.5 V                        |
+--------------------------+----------------------------------+
| Input coupling           | DC                               |
+--------------------------+----------------------------------+
| Connector                | Pins 13, 14, 15, 16 on           |
|                          | |E2|                             |
+--------------------------+----------------------------------+



Auxiliary analog output channels 
---------------------------------

+--------------------------+----------------------------------+
| Number of channels       | 4                                |
+--------------------------+----------------------------------+
| Output resolution        | 8 bits                           |
+--------------------------+----------------------------------+
| Sampling rate            | ≲ 3.2 MS/s                       |
+--------------------------+----------------------------------+
| Output filter bandwidth  | 200 kHz                          |
+--------------------------+----------------------------------+
| Output voltage range     | 0 - 1.8 V                        |
+--------------------------+----------------------------------+
| Output coupling          | DC                               |
+--------------------------+----------------------------------+
| Output type              | Low pass filtered PWM [#f5]_     |
+--------------------------+----------------------------------+
| PWM time resolution      | 8 ns (1/125 MHz)                 |
+--------------------------+----------------------------------+
| Connector                | Pins 17, 18, 19, 20 on           |
|                          | |E2|                             |
+--------------------------+----------------------------------+



General purpose digital input/output channels
----------------------------------------------

+--------------------------+----------------------------------+
| Number of GPIOs          | 22                               |
+--------------------------+----------------------------------+
| Digital voltage level    | 3.3 V                            |
+--------------------------+----------------------------------+
| Abs. min. voltage        | -0.40 V                          |
+--------------------------+----------------------------------+
| Abs. max. voltage        | 3.3 V + 0.55 V                   |
+--------------------------+----------------------------------+
| Current limitation       | < 8 mA drive strength            |
+--------------------------+----------------------------------+
| Direction                | Configurable                     |
+--------------------------+----------------------------------+
| Time resolution          | 8 ns (1/125 MHz)                 |
+--------------------------+----------------------------------+
| Location                 | |E1|                             |
+--------------------------+----------------------------------+


Synchronisation connectors
---------------------------

The USB-C :ref:`S1 and S2 connectors <sync_connectors_gen2>` are used for daisy chaining multiple Red Pitaya boards together. The S1 connector is used exclusively for transmitting clock and trigger signals of the currnet board
to the next board in the chain while the S2 connector is used exclusively for receiving clock and trigger signals from the previous board in the chain.

.. note::

    The Connectors S1 and S2 are used only for interconnection between two Red Pitaya modules. Note that connection is not compliant with USB-C specification.
    Do not connect S1 or S2 to any other USB-C ports except Red Pitaya S1 and S2 connectors.


Powering Red Pitaya through extension connector
================================================

Red Pitaya boards can be powered through the +5V pin (pin 1) of the |E2|.

+--------------------------+-----------------------------+
| **External power specifications**                      |
+--------------------------+-----------------------------+
| Power supply voltage     | 5 V, 3.0 A (max)            |
+--------------------------+-----------------------------+
| Power supply type        | DC                          |
+--------------------------+-----------------------------+
| Abs. max. voltage        | 5.5 V (max)                 |
+--------------------------+-----------------------------+
| Abs. min. voltage        | 4.5 V (min)                 |
+--------------------------+-----------------------------+

The +5V pin features a 3.0 A PTC resetable fuse, which protects the board from overcurrent. The fuse is located on the PCB, near the extension connector |E2|.


External ADC clock
===================

The main FPGA CLK signal on |STEMlab 125-14 Pro Gen 2| and |STEMlab 125-14 Pro Z7020 Gen 2| boards can be supplied from an external source through the **Ext. ADC Clk±** ports.

Both the internal oscillator clock and the external clock signal are connected to the `NB6L72`_ Differential Crosspoint Switch.
The **CLK_SEL** pin is used to select the clock source:

* 3V3 (logic high) or unconnected - **Internal clock**.
* GND (logic low) - **External clock**.

The clock signal then travelles from the output of the `NB6L72`_ through the ADC to the FPGA.

**External clock specifications**
The external ADC clock should comply with `NB6L72`_ input specifications. The chip is powered by 3V3.

.. note::

    When synchronising multiple Red Pitaya *Pro Gen 2* boards, please keep in mind that:

    * :ref:`Click Shield synchronisation <click_shield>` works out-of-the-box.
    * :ref:`X-channel synchronisation <x-ch_streaming>` requires a hardware modification as secondary boards differ from the primary board.



Other specifications and measurements
=============================================

For all other specifications and measurements please refer to the common |Gen 2 hardware specs|.

.. note::

    The information provided by Red Pitaya d.o.o. is believed to be accurate and reliable. However, no liability is accepted for its use. Please note that the contents may be subject to change without prior notice. 


.. rubric:: Footnotes

.. [#f1] See the :ref:`Click Shield synchronisation section <click_shield>` and :ref:`Click Shield synchronisation examples <examples_multiboard_sync>`.

.. [#f2] The external ADC clock goes first to the `NB6L72`_ clock selector chip, then passes through the ADC to finally reach the FPGA pins.

.. [#f3] For exact voltage levels, please refer to the `NB6L72`_ datasheet.

.. [#f4] The default software enables sampling at a CPU-dependent speed. To acquire data at a 100 kS/s rate, additional FPGA processing must be implemented.

.. [#f5] The output is passed through a first-order low-pass filter. Should additional filtering be required, this can be applied externally in line with the specific requirements of the application.  


.. substitutions

.. |E1| replace:: :ref:`E1 connector <E1_gen2>`
.. |E2| replace:: :ref:`E2 connector <E2_gen2>`
.. |Gen 2 hardware specs| replace:: :ref:`Gen 2 hardware specifications <hw_specs_gen2>`
.. |Gen 2 comparison table| replace:: :ref:`Gen 2 board comparison table <rp-board-comp-gen2>`
.. |STEMlab 125-14 Pro Gen 2| replace:: :ref:`STEMlab 125-14 Pro Gen 2 <top_125_14_pro_gen2>`
.. |STEMlab 125-14 Pro Z7020 Gen 2| replace:: :ref:`STEMlab 125-14 Pro Z7020 Gen 2 <top_125_14_pro_z7020_gen2>`
.. _NB6L72: https://www.onsemi.com/pdf/datasheet/nb6l72-d.pdf


.. :xref:`NB6172_datasheet`
.. :xref:`NB6L72 <NB6172_datasheet>`

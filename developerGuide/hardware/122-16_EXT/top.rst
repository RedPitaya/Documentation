.. _top_122_16_EXT:

#############################
SDRlab 122-16 external clock
#############################

This version of the SDRlab is a standard SDRlab 122-16 which has been modified in such a way that the ADC, the DAC and the FPGA clock can be provided by an external clock source. An external clock should be connected to the Ext ADC CLK- and + pin

**External clock specifications:**

The Ext ADC CLK+ and - pins are connected to the ENC+ and ENC- pins of the ADC.

Acording to the ADC specifications, the ENC+ and ENC- inputs can be driven differentially or single-ended with a sine wave, PECL, LVDS, TTL or CMOS input.
An optional clock duty cycle stabiliser allows high performance at full speed over a wide range of clock duty cycles. 
The input voltage range for differentially driven ENC+ and ENC- is 0.2 to 3.6 V (towards GND) and 0 to 3.6 V (ENC+) for single-ended with a frequency between 1 MHz and 125 MHz according to the ADC specification.

The operating voltage of the Red Pitaya is 3V3.

.. note::

   **Booting without the external clock present?**
   The official Red Pitaya OS will not boot without providing an external clock as it relies on reading the FPGA register map, which is available if the ADC clock is present.
   However, by modifying the software, the Linux OS itself can boot even without the external clock present, but please note it will crash when trying to read from the FPGA without the external clock present.


Pinout
========

.. figure:: ../125-14/img/Red_Pitaya_pinout.jpg
    :width: 700



Technical specifications
==========================

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
    | RF input channels                  | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 122.88 MS/s                        |
    +------------------------------------+------------------------------------+
    | ADC resolution                     | 16 bit                             |
    +------------------------------------+------------------------------------+
    | Input impedance                    | 50 Ω                               |
    +------------------------------------+------------------------------------+
    | Full scale voltage range           | 0.5 Vpp/-2 dBm                     |
    +------------------------------------+------------------------------------+
    | Input coupling                     | AC                                 |
    +------------------------------------+------------------------------------+
    | Absolute max. Input voltage range  | | DC max 50 V (AC-coupled),        |
    |                                    | | 1 Vpp for RF                     |
    +------------------------------------+------------------------------------+
    | Input ESD protection               | Yes                                |
    +------------------------------------+------------------------------------+
    | Overload protection                | DC voltage protection              |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | 300 kHz - 550 MHz (undersampling)  |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 10 18

    +------------------------------------+------------------------------------+
    | **RF outputs**                                                          |
    +====================================+====================================+
    | RF output channels                 | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 122.88 MS/s                        |
    +------------------------------------+------------------------------------+
    | DAC resolution                     | 14 bit                             |
    +------------------------------------+------------------------------------+
    | Load impedance                     | 50 Ω                               |
    +------------------------------------+------------------------------------+
    | Voltage range                      | 0.5 Vpp/-2 dBm                     |
    |                                    | (50 Ω load)                        |
    +------------------------------------+------------------------------------+
    | Short circuit protection           | N/A, RF transformer                |
    |                                    | & AC-coupled                       |
    +------------------------------------+------------------------------------+
    | Connector type                     | SMA                                |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | N/A                                |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | 300 kHz - 60 MHz                   |
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


Schematics
=============

* `STEM122-16SDR_V1r1_Series1.PDF <https://downloads.redpitaya.com/doc/Customer_Schematics_STEM122-16SDR_V1r1%28Series1%29.PDF>`_

.. note::

    Red Pitaya board HW FULL schematics are not available. Red Pitaya has an open-source code but not open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connection and similar.


Mechanical Specifications and 3D Models
===========================================

* `STEM122-16SDR_V1r1_3Dpdf.zip <https://downloads.redpitaya.com/doc/STEM122-16SDR_V1r1_3Dpdf.zip>`_
* `STEM122-16SDR_V1r1_3Dstep.zip <https://downloads.redpitaya.com/doc/STEM122-16SDR_V1r1_3Dstep.zip>`_


ADC specifications
====================

* `Data sheets <https://www.analog.com/en/products/LTC2185.html>`_



RP clock wiring
==================

* :ref:`External ADC clock <external_122_16>`


Other specifications
=====================

For all other specifications please refer to standard :ref:`SDRlab 122-16 specs <top_122_16>`.



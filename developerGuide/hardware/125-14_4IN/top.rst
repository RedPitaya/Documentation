.. _top_125_14_4-IN:

STEMlab 125-14 4-Input
######################

STEMlab 125-14 4-Input is a single-board RF signal acquisition platform that offers the same general hardware features as STEMlab 125-14. The main differences/benefits are that:

* There are 4 analog input channels @ 125 Msps & 14 bits (instead of 2 inputs and 2 outputs).
* RF inputs come with better performance (less crosstalk, noise, and distortions).
* Zynq 7020 (bigger FPGA that offers more processing capabilities and more digital IO pins available on the extension connector).
* Switching between internal and external clocks can be done using a jumper or control signal on the extension connector.
* The internal ADC clock can be locked to an external reference clock via an extension connector (this feature is only available upon customer request).


******
Pinout
******

.. figure:: ../125-14/img/Red_Pitaya_pinout.jpg
    :width: 700

************************
Technical specifications
************************

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

.. table::
    :widths: 10 18


    +------------------------------------+------------------------------------+
    | **Connectivity**                                                        |
    +====================================+====================================+
    | Ethernet                           | 1 Gbit                             |
    +------------------------------------+------------------------------------+
    | USB                                | USB 2.0                            |
    +------------------------------------+------------------------------------+
    | WIFI                               | requires WIFI dongle               |
    +------------------------------------+------------------------------------+


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
    | Input impedance                    | 1 MOhm / 10 pF                     |
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
    | Short circut protection            | N/A                                |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Connector type                     | N/A                                |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | N/A                                |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | N/A                                |
    +------------------------------------+------------------------------------+



.. table::
    :widths: 10 18

    +------------------------------------+------------------------------------+
    | **Extension connector**                                                 | 
    +====================================+====================================+
    | Digital IOs                        | 20                                 |
    +------------------------------------+------------------------------------+
    | Analog inputs                      | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog inputs voltage range        | 0-3.5 V                            |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 100 kS/s                           |
    +------------------------------------+------------------------------------+
    | Resolution                         | 12 bit                             |
    +------------------------------------+------------------------------------+
    | Analog outputs                     | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog outputs voltage range       | 0-1.8 V                            |
    +------------------------------------+------------------------------------+
    | Communication interfaces           | I2C, SPI, UART                     |
    +------------------------------------+------------------------------------+
    | Available voltages                 | +5 V, +3.3 V, -4 V                 |
    +------------------------------------+------------------------------------+
    | external ADC clock                 |  yes                               |
    +------------------------------------+------------------------------------+

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


************************************************
Switching between internal and external clock
************************************************

Driving the *CLK_SEL* pin to GND (logic 0) switches the board to external clock mode. When the pin is driven to 3V3 (logic 1) or left floating, the board operates in the internal clock mode (on-board oscillator).

When STEMlab 125-14 4-Input is in External clock mode the ADC clock must be provided from an external source clock. An external clock should be connected to the *Ext ADC CLK- and +* pins. According to the ADC spec, external clock signal levels should be LVDS in the range from 1 MHz to 125 MHz.

.. note::

    In the External clock mode, the OS will not boot without providing an external clock.


**********
Schematics
**********

* `STEMlab_125-14-4_IN_V1r3.PDF <https://downloads.redpitaya.com/doc/Red_Pitaya_Schematics_STEM_125-14-4_IN_V1r3.PDF>`_

****************************************
Mechanical Specifications and 3D Models
****************************************

* `STEMlab_125-14-4_IN_V1r3.zip <https://downloads.redpitaya.com/doc/STEM125-14-4_IN_V1r3_3Dstep.zip>`_



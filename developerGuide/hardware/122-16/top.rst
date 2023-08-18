.. _top_122_16:

SDRlab 122-16
#############

.. figure:: SDRlab-122-16.jpg
    :width: 50%

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
    | RF input channels                  | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 122.88 MS/s                        |
    +------------------------------------+------------------------------------+
    | ADC resolution                     | 16 bit                             |
    +------------------------------------+------------------------------------+
    | Input impedance                    | 50 Ohm                             |
    +------------------------------------+------------------------------------+
    | Full scale voltage range           | 0.5 Vpp/-2 dBm                     |
    +------------------------------------+------------------------------------+
    | Input coupling                     | AC                                 |
    +------------------------------------+------------------------------------+
    | Absolute max. Input voltage range  | DC max 50 V (AC-coupled)           |
    |                                    | 1 Vpp for RF                       |
    +------------------------------------+------------------------------------+
    | Input ESD protection               | Yes                                |
    +------------------------------------+------------------------------------+
    | Overload protection                | DC voltage protection              |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | 300 kHz - 550 MHz (undersampling)  |
    +------------------------------------+------------------------------------+


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
    | Load impedance                     | 50 Ohm                             |
    +------------------------------------+------------------------------------+
    | Voltage range                      | 0.5 Vpp/ -2 dBm                    |
    |                                    | (50 Ohm load)                      |
    +------------------------------------+------------------------------------+
    | Short circut protection            | N/A, RF transformer                |
    |                                    | & AC-coupled                       |
    +------------------------------------+------------------------------------+
    | Connector type                     | SMA                                |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | N/A                                |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | 300 kHz - 60 MHz                   |
    +------------------------------------+------------------------------------+



.. table::
    :widths: 10 18

    +------------------------------------+------------------------------------+
    | **Extension connector**                                                 | 
    +====================================+====================================+
    | Digital IOs                        | 16                                 |
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


**********
Schematics
**********

* `STEM122-16SDR_V1r1_Series1.PDF <https://downloads.redpitaya.com/doc/Customer_Schematics_STEM122-16SDR_V1r1%28Series1%29.PDF>`_

.. note::

    Red Pitaya board HW FULL schematics are not available. Red Pitaya has an open-source code but not open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connection and similar.

****************************************
Mechanical Specifications and 3D Models
****************************************

* `STEM122-16SDR_V1r1_3Dpdf.zip <https://downloads.redpitaya.com/doc/STEM122-16SDR_V1r1_3Dpdf.zip>`_
* `STEM122-16SDR_V1r1_3Dstep.zip <https://downloads.redpitaya.com/doc/STEM122-16SDR_V1r1_3Dstep.zip>`_


**********
Components
**********

* `ADC <https://www.analog.com/en/products/LTC2185.html>`_
* `DAC <https://www.analog.com/en/products/AD9767.html>`_
* `FPGA (Zynq 7020) <https://docs.xilinx.com/v/u/en-US/ds190-Zynq-7000-Overview>`_
* `DC-DC converter <https://www.analog.com/en/products/LTC3615.html>`_
* `Oscillator <https://abracon.com/Precisiontiming/ABLNO.pdf>`_
* `SRAM-DDR3 <https://www.digikey.com/en/products/detail/micron-technology-inc/MT41J256M16HA-125-E/4315785>`_
* `QSPI <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_



.. _external_122_16:

******************
External ADC clock
******************

ADC clock can be provided by:

  * On board 122.88 MHz XO (default)
  * From external source / through extension connector (instructions provided below)

.. warning::

    We do not advise altering the board because users have reported problems after doing so. Every board made has undergone rigorous testing, which cannot be claimed for modified boards. Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.


* Remove: R37, R46
* Add: R34 = 0R, R35 = 0R


 .. figure:: External_img1.png
    :align: center


* Remove: FB11

 .. figure:: External_img2.png
    :align: center


* Remove: 0R on C64, R24
* Add: C64 = 100nF, C63 = 100nF, R36 = 100R

 .. figure:: External_img3.png
    :align: center


 .. figure:: External_shem.png
    :width: 50%
    :align: center

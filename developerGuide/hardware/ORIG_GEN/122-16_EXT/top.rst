.. _top_122_16_EXT:

#############################
SDRlab 122-16 external clock
#############################

.. figure:: ../122-16/img/SDRlab-122-16.jpg
    :width: 500


This version of the SDRlab is a standard SDRlab 122-16 which has been modified in such a way that the ADC, the DAC and the FPGA clock can be provided by an external clock source. An external clock should be connected to the Ext ADC CLK- and + pin

**External clock specifications:**

The Ext ADC CLK+ and - pins are connected to the ENC+ and ENC- pins of the ADC. The clock from the ADC is then passed to the FPGA.
The ports operate differentially and should be driven with **LVDS** clock with voltage levels similar to the one provided by the SDRlab 122-16 on-board `oscillator <https://abracon.com/Precisiontiming/ABLNO.pdf>`_.

The maximum and minimum clock frequencies are limited by the ADC specifications.

The operating voltage of the Red Pitaya is 3V3.

.. note::

    **Booting without the external clock present?**
    The official Red Pitaya OS will not boot without providing an external clock as it relies on reading the FPGA register map, which is available if the ADC clock is present.
    However, by modifying the software, the Linux OS itself can boot even without the external clock present, but please note it will crash when trying to read from the FPGA without the external clock present.

.. note::

    When synchronising multiple Red Pitaya boards, please keep in mind that:

    * :ref:`Click Shield synchronisation <click_shield>` requires external clock models.
    * :ref:`X-channel synchronisation <x-ch_streaming>` requires the X-channel system (master and slave boards) which differ from external clock models.


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
    | | **Absolute max.**                | | **DC max 50 V (AC-coupled)**     |
    | | **Input voltage**                | | **1 Vpp for RF**                 |
    +------------------------------------+------------------------------------+
    | Input ESD protection               | Yes                                |
    +------------------------------------+------------------------------------+
    | Overload protection                | DC voltage protection              |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | 300 kHz - 550 MHz (undersampling)  |
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
    | Sample rate                        | 122.88 MS/s                        |
    +------------------------------------+------------------------------------+
    | DAC resolution                     | 14 bit                             |
    +------------------------------------+------------------------------------+
    | Load impedance                     | 50 Ω                               |
    +------------------------------------+------------------------------------+
    | Voltage range                      | 0.5 Vpp/ -2 dBm                    |
    |                                    | (50 Ω load)                        |
    +------------------------------------+------------------------------------+
    | Short circuit protection           | N/A, RF transformer                |
    |                                    | & AC-coupled                       |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | N/A                                |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | 300 kHz - 60 MHz                   |
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
    | Analog inputs voltage range        | 0 - 3.5 V                          |
    +------------------------------------+------------------------------------+
    | Analog input resolution            | 12 bit                             |
    +------------------------------------+------------------------------------+
    | Analog input sample rate           | 100 kS/s                           |
    +------------------------------------+------------------------------------+
    | Analog outputs                     | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog outputs voltage range       | 0 - 1.8 V                          |
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
    | External ADC clock                 | Yes                                |
    +------------------------------------+------------------------------------+

|

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
    | Trigger output [#f1]_              | E1 connector (DIO0_N)              |
    +------------------------------------+------------------------------------+
    | Daisy chain connection             | SATA connectors |br|               |
    |                                    | (up to 500 Mbps)                   |
    +------------------------------------+------------------------------------+
    | Ref. clock input                   | N/A                                |
    +------------------------------------+------------------------------------+

.. rubric:: Footnotes

.. [#f1]  See the :ref:`Click Shield synchronisation section <click_shield>` and :ref:`Click Shield synchronisation examples <examples_multiboard_sync>`.


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

    We do not have explicit measurements for the SDRlab 122-16 board.

You can find the measurements of the fast analog frontend here:

* :ref:`Original boards - STEMlab 125-14 <measurements_orig_gen>`.
* :ref:`Gen 2 - STEMlab 125-14 Gen 2 <measurements_gen2>`.


Schematics
=============

* :download:`Schematics_STEM_122-16SDR_V1r1.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_122-16SDR_V1r1.pdf>`.

.. note::

    Full hardware schematics for the Red Pitaya board are not available. Red Pitaya has open-source code but not open hardware schematics. Nonetheless, development schematics are available. This schematic will give you information about hardware configuration, FPGA pin connections, and similar.


Mechanical Specifications and 3D Models
===========================================

* PDF :download:`3D_STEM_122-16SDR_V1r1.pdf.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_122-16SDR_V1r1.pdf.zip>`.
* STEP :download:`3D_STEM_122-16SDR_V1r1.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_122-16SDR_V1r1.zip>`.


ADC specifications
====================

* `Data sheets <https://www.analog.com/en/products/LTC2185.html>`_.



RP clock wiring
==================

* :ref:`External ADC clock <external_122_16>`.


Other specifications
=====================

For all other specifications please refer to standard :ref:`SDRlab 122-16 specs <top_122_16>`.

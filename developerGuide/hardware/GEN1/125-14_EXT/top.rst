.. _top_125_14_EXT:

#############################
STEMlab 125-14 external clock
#############################


.. figure:: ../125-14/img/STEMlab-125-14.jpg
    :width: 500


This version of the STEMlab is a standard STEMlab 125-14 which has been modified in such a way that the ADC, the DAC and the FPGA clock can be provided by an external clock source. An external clock should be connected to the Ext ADC CLK- and + pin

**External clock specifications:**

The Ext ADC CLK+ and - pins are connected to the ENC+ and ENC- pins of the ADC. The clock from the ADC is then passed to the FPGA.
The ports operate differentially and should be driven with **LVDS clock with voltage levels similar to the one provided by the STEMlab 125-14 on-board `Oscillator <https://eu.mouser.com/datasheet/2/417/bf-8746.pdf>`_**.

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
=======

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
    | FPGA                               | FPGA Xilinx Zynq 7010 SoC          |
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
    | Digital IOs                        | 16                                 |
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
    | External ADC clock                 | Yes                                |
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
    | Trigger output [#f1]_              | E1 connector (DIO0_N)              |
    +------------------------------------+------------------------------------+
    | Daisy chain connection             | SATA connectors |br|               |
    |                                    | (up to 500 Mbps)                   |
    +------------------------------------+------------------------------------+
    | Ref. clock input                   | N/A                                |
    +------------------------------------+------------------------------------+

.. rubric:: Footnotes

.. [#f1]  See the :ref:`Click Shield synchronisation section <click_shield>` and :ref:`Click Shield synchronisation examples <multiboard_sync_examples>`.


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

    For more information, please refer to the :ref:`Product comparison table <rp-board-comp-gen1>`.

.. |br| raw:: html

    <br/>


Schematics
============

- `Red_Pitaya_Schematics_v1.0.1.pdf <https://downloads.redpitaya.com/doc//Red_Pitaya_Schematics_v1.0.1.pdf>`_

.. note::

    FULL HW schematics for the Red Pitaya board are not available. Red Pitaya has open-source code but not open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connections, and similar.


Mechanical Specifications and 3D Models
========================================

- `Red_Pitaya_3Dmodel_v1.0.zip <https://downloads.redpitaya.com/doc/Red_Pitaya_3Dmodel_v1.0.zip>`_


ADC specifications
=====================

- `Data sheet <https://www.analog.com/media/en/technical-documentation/data-sheets/21454314fa.pdf>`_



Red Pitaya clock wiring
========================

- :ref:`External ADC clock <external_125_14>`


Other specifications
=====================

For all other specifications please refer to standard :ref:`STEMlab 125-14 specs <top_125_14>`.



.. _top_125_14_EXT:

#############################################
STEMlab 125-14 External Clock (Discontinued)
#############################################

.. figure:: ../125-14/img/STEMlab-125-14.jpg
    :width: 500
    :align: center

|

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

Overview
========

The STEMlab 125-14 External Clock is a hardware-modified version of the standard :ref:`STEMlab 125-14 <top_125_14>` that accepts an external clock source.
SMD resistors have been relocated at the factory to connect the Ext. ADC Clk± pins on the E2 connector directly to the ADC clock input, bypassing the on-board oscillator.

This variant is intended for applications requiring clock synchronisation with external equipment or operation at non-standard sampling rates.

|

Features
========

* 14-bit, 125 MS/s ADC and DAC (at 125 MHz clock)
* External clock input support (pre-modified hardware)
* Dual-core ARM Cortex-A9 processor
* FPGA Xilinx Zynq 7010 SoC
* 512 MB RAM
* 16 digital I/Os, 4 analog inputs, 4 analog outputs
* Multiple communication interfaces: I2C, SPI, UART, CAN
* Micro USB connectivity for power and console

|

Quick Reference
===============

.. table::
    :widths: 40 60

    +----------------------------+--------------------------------------------------+
    | **Category**               | **Key Specifications**                           |
    +============================+==================================================+
    | ADC                        | 2 channels, 14-bit, 125 MS/s, DC-50 MHz          |
    +----------------------------+--------------------------------------------------+
    | DAC                        | 2 channels, 14-bit, 125 MS/s, DC-50 MHz          |
    +----------------------------+--------------------------------------------------+
    | Processor                  | Dual-core ARM Cortex-A9                          |
    +----------------------------+--------------------------------------------------+
    | FPGA                       | Xilinx Zynq 7010 SoC                             |
    +----------------------------+--------------------------------------------------+
    | RAM                        | 512 MB                                           |
    +----------------------------+--------------------------------------------------+
    | Digital I/O                | 16 GPIOs @ 3.3V                                  |
    +----------------------------+--------------------------------------------------+
    | Analog I/O                 | 4 inputs (12-bit), 4 outputs (8-bit)             |
    +----------------------------+--------------------------------------------------+
    | Connectivity               | Ethernet, USB, Extension connectors              |
    +----------------------------+--------------------------------------------------+
    | Special Features           | External clock input (LVDS)                      |
    +----------------------------+--------------------------------------------------+

|

Differences from Standard STEMlab 125-14
==========================================

This board is electrically identical to the :ref:`STEMlab 125-14 <top_125_14>` with the following hardware changes already applied at the factory:

+--------------------------------------+---------------------------------------------+---------------------------------------------+
| **Parameter**                        | **STEMlab 125-14**                          | **STEMlab 125-14 External Clock**           |
+======================================+=============================================+=============================================+
| On-board 125 MHz oscillator          | Active (drives ADC, FPGA, DAC)              | Bypassed (disconnected from clock path)     |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| E2 pins 23-24 (Ext. ADC Clk±)        | Not connected                               | Active — must receive a valid LVDS clock    |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| External ADC clock                   | No (requires hardware modification)         | Yes (pre-modified, plug-and-use)            |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| Resistors R25, R26                   | In default position                         | Relocated to R23, R24                       |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| Operation without external clock     | Normal (uses onboard oscillator)            | FPGA non-functional; PS boots from 33 MHz   |
+--------------------------------------+---------------------------------------------+---------------------------------------------+

.. warning::

    The on-board oscillator is bypassed. The board **will not perform signal acquisition or generation** without a valid external
    LVDS clock on E2 pins 23-24 (Ext. ADC Clk±). Leaving these pins floating or supplying an incorrect signal will prevent FPGA operation.

    * **OS 2.07-48 or higher:** The Linux OS will still boot using an internal 33 MHz oscillator, but FPGA functionality will not be available.
    * **OS versions prior to 2.07-48:** The board will fail to boot without a valid external clock signal.

.. note::

    When using this board with synchronisation features:

    * :ref:`X-channel 2.0 (Click Shield) synchronisation <click_shield_sync>` is compatible with this board.
    * :ref:`X-channel synchronisation <x-ch_streaming>` requires the X-channel system (primary and secondary boards), which differ from external clock models.

|

Technical Specifications
=========================

The STEMlab 125-14 External Clock has the same specifications as the :ref:`standard STEMlab 125-14 <top_125_14>`, with the following addition:

* **External ADC clock:** Yes (hardware pre-modified for external clock input)
* **Hardware modification:** resistors R25, R26 relocated to R23, R24 to enable external clock input

For full technical specifications, please refer to the :ref:`STEMlab 125-14 specifications <top_125_14>`.

.. seealso::

    For more detailed information, please refer to the |Original Gen comparison table|.

|

Performance & Measurements
============================

You can find the measurements of the fast analog frontend here:

* :ref:`Original Gen - STEMlab 125-14 <measurements_orig_gen>`.

|

Schematics & 3D Models
========================

Schematics
----------

* :download:`Schematics_STEM_125-14_v1.1.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_125-14_v1.1.pdf>`.

.. note::

    The external clock variant uses the same PCB as the standard STEMlab 125-14. The only physical difference is the relocation of resistors R25, R26 to R23, R24.

Mechanical Specifications & 3D Models
--------------------------------------

* STEP :download:`3D_STEM_125-14_v1.0.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_125-14_v1.0.zip>`.

|

Advanced Features
==================

External ADC Clock
-------------------

.. include:: ../_specs_common/ext_adc_clk.inc

|

Additional Resources
====================

For additional specifications and measurements, please refer to:

* :ref:`STEMlab 125-14 <top_125_14>` - Standard STEMlab 125-14 specifications
* |Original Gen hardware specs| - Common Original Gen specifications
* |Original Gen comparison table| - Comparison across all Red Pitaya Original Gen models

|

Legal & Disclaimers
===================

.. include:: ../_specs_common/disclaimer.inc

|

.. substitutions

.. |E2| replace:: :ref:`E2 connector <E2_orig_gen>`
.. |Original Gen hardware specs| replace:: :ref:`Original Gen hardware specifications <hw_specs_orig_gen>`
.. |Original Gen comparison table| replace:: :ref:`Original Gen board comparison table <rp-board-comp-orig_gen>`
.. _NB6L72: https://www.onsemi.com/pdf/datasheet/nb6l72-d.pdf

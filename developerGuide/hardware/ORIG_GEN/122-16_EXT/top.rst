.. _top_122_16_EXT:

#############################
SDRlab 122-16 External Clock
#############################

.. figure:: ../122-16/img/SDRlab-122-16.jpg
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

The SDRlab 122-16 External Clock is a modified version of the standard SDRlab 122-16 that has been hardware-modified to accept an external clock source. 
This variant is optimized for SDR applications requiring clock synchronisation with external equipment.

|

Features
========

* 16-bit ADC and 14-bit DAC, 122.88 MS/s (at 122.88 MHz clock)
* AC-coupled 50 Ω RF inputs and outputs
* SDR-optimized clock frequency (122.88 MHz)
* External clock input support (pre-modified hardware)
* Dual-core ARM Cortex-A9 processor
* FPGA Xilinx Zynq 7020 SoC
* 512 MB RAM
* 22 digital I/Os, 4 analog inputs, 4 analog outputs
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
    | ADC                        | 2 channels, 16-bit, 122.88 MS/s                  |
    +----------------------------+--------------------------------------------------+
    | DAC                        | 2 channels, 14-bit, 122.88 MS/s                  |
    +----------------------------+--------------------------------------------------+
    | Processor                  | Dual-core ARM Cortex-A9                          |
    +----------------------------+--------------------------------------------------+
    | FPGA                       | Xilinx Zynq 7020 SoC                             |
    +----------------------------+--------------------------------------------------+
    | RAM                        | 512 MB                                           |
    +----------------------------+--------------------------------------------------+
    | Digital I/O                | 22 GPIOs @ 3.3V                                  |
    +----------------------------+--------------------------------------------------+
    | Analog I/O                 | 4 inputs (12-bit), 4 outputs (8-bit)             |
    +----------------------------+--------------------------------------------------+
    | Connectivity               | Ethernet, USB-C, Extension connectors            |
    +----------------------------+--------------------------------------------------+
    | Input Impedance            | 50 Ω (AC-coupled)                                |
    +----------------------------+--------------------------------------------------+
    | Special Features           | AC-coupling, External clock input (LVDS)         |
    +----------------------------+--------------------------------------------------+

|

Differences from Standard SDRlab 122-16
========================================

This board is electrically identical to the :ref:`SDRlab 122-16 <top_122_16>` with the following hardware changes already applied at the factory:

+--------------------------------------+---------------------------------------------+---------------------------------------------+
| **Parameter**                        | **SDRlab 122-16**                           | **SDRlab 122-16 External Clock**            |
+======================================+=============================================+=============================================+
| On-board 122.88 MHz oscillator       | Active (drives ADC, FPGA, DAC)              | Bypassed (disconnected from clock path)     |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| E2 pins 23-24 (Ext. ADC Clk±)        | Not connected                               | Active — must receive a valid LVDS clock    |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| External ADC clock                   | No (requires hardware modification)         | Yes (pre-modified, plug-and-use)            |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| Operation without external clock     | Normal (uses onboard oscillator)            | FPGA non-functional; PS boots from 33 MHz   |
+--------------------------------------+---------------------------------------------+---------------------------------------------+

.. warning::

    The onboard oscillator is bypassed. The board **will not perform signal acquisition or generation** without a valid external
    LVDS clock on E2 pins 23-24. Supplying the wrong signal level or leaving the pins floating will prevent FPGA operation.

.. note::

    When using this board with synchronisation features:

    * :ref:`X-channel 2.0 (Click Shield) synchronisation <click_shield_sync>` is compatible with this board.
    * :ref:`X-channel synchronisation <x-ch_streaming>` is **not** compatible.
    
|

Technical Specifications
=========================

The SDRlab 122-16 External Clock has the same specifications as the :ref:`standard SDRlab 122-16 <top_122_16>`, with the following addition:

* **External ADC clock:** Yes (hardware pre-modified for external clock input)
* **Hardware modification:** Resistors relocated to enable external clock input

For full technical specifications, please refer to the :ref:`SDRlab 122-16 specifications <top_122_16>`.

.. seealso::

    For more detailed information, please refer to the |Original Gen comparison table|.

|

Performance & Measurements
============================

.. note::

    We do not have explicit measurements for the SDRlab 122-16 board.

You can find the measurements of the fast analog frontend for similar boards here:

* :ref:`Original Gen - STEMlab 125-14 <measurements_orig_gen>`.

|

Schematics & 3D Models
========================

Schematics
----------

* :download:`Schematics_STEM_122-16SDR_V1r1.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_122-16SDR_V1r1.pdf>`.

.. note::

    The external clock variant uses the same PCB as the standard SDRlab 122-16. The only physical difference is the relocation of resistors R25, R26 to R23, R24.

Mechanical Specifications & 3D Models
--------------------------------------

* PDF :download:`3D_STEM_122-16SDR_V1r1.pdf.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_122-16SDR_V1r1.pdf.zip>`.
* STEP :download:`3D_STEM_122-16SDR_V1r1.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_122-16SDR_V1r1.zip>`.

|

Advanced Features
==================

External ADC Clock
-------------------

.. include:: ../_specs_common/ext_adc_clk.inc

|

Additional Resources
====================

For additional specifications, please refer to:

* :ref:`SDRlab 122-16 <top_122_16>` - Standard SDRlab 122-16 specifications
* |Original Gen hardware specs| - Common Original Gen specifications
* |Original Gen comparison table| - Comparison across all Red Pitaya Original Gen models

|

Legal & Disclaimers
===================

.. include:: ../_specs_common/disclaimer.inc

|

.. substitutions

.. |E2| replace:: :ref:`E2 connector <E2_sdr>`
.. |Original Gen hardware specs| replace:: :ref:`Original Gen hardware specifications <hw_specs_orig_gen>`
.. |Original Gen comparison table| replace:: :ref:`Original Gen board comparison table <rp-board-comp-orig_gen>`
.. _NB6L72: https://www.onsemi.com/pdf/datasheet/nb6l72-d.pdf

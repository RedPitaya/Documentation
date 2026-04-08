.. _top_125_14_LN:

#################################
STEMlab 125-14 LN (Discontinued)
#################################

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

The STEMlab 125-14 Low Noise (LN) is a variant of the standard :ref:`STEMlab 125-14 <top_125_14>` with populated linear analog power supply regulators.
Replacing the default switching regulators with linear ones reduces noise on the analog power rails, lowering the noise floor of the RF inputs and outputs and improving ENOB (Effective Number of Bits).

To find out more about the performance improvements, refer to Leonhard Neuhaus's blog: |Red Pitaya DAC performance|.

.. |Red Pitaya DAC performance| raw:: html

    <a href="https://ln1985blog.wordpress.com/2016/02/07/red-pitaya-dac-performance/" target="_blank">Red Pitaya DAC performance</a>

|

Features
========

* 14-bit, 125 MS/s ADC and DAC
* Linear analog power supplies for improved noise performance
* Dual-core ARM Cortex-A9 processor
* FPGA Xilinx Zynq 7010 SoC
* 512 MB RAM
* 16 digital I/Os, 4 analog inputs, 4 analog outputs
* Multiple communication interfaces: I2C, SPI, UART, CAN
* Micro USB connectivity for power and console
* SATA daisy-chain connectors for multi-board synchronisation

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
    | Special Features           | Linear power supplies, Low Noise                 |
    +----------------------------+--------------------------------------------------+

|

Differences from Standard STEMlab 125-14
==========================================

This board is electrically identical to the :ref:`STEMlab 125-14 <top_125_14>` with the following difference:

+--------------------------------------+---------------------------------------------+---------------------------------------------+
| **Parameter**                        | **STEMlab 125-14**                          | **STEMlab 125-14 LN**                       |
+======================================+=============================================+=============================================+
| Analog power supply regulators       | Switching regulators (not populated)        | Linear regulators (populated)               |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| Analog power supply noise            | Higher (switching artefacts present)        | Lower (clean linear supply)                 |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| RF output noise floor                | Standard                                    | Reduced                                     |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| Output ENOB                          | Standard                                    | Improved                                    |
+--------------------------------------+---------------------------------------------+---------------------------------------------+
| Power consumption                    | Lower                                       | Slightly higher (linear regulators)         |
+--------------------------------------+---------------------------------------------+---------------------------------------------+

|

Technical Specifications
=========================

The STEMlab 125-14 LN has the same specifications as the :ref:`standard STEMlab 125-14 <top_125_14>`, with the following enhancement:

* **Linear analog power supply regulators:** Populated linear regulators replace the default switching regulators, reducing noise on the analog rails and improving output ENOB.

For full technical specifications, please refer to the :ref:`STEMlab 125-14 specifications <top_125_14>`.

.. seealso::

    For more detailed information, please refer to the |Original Gen comparison table|.

|

Performance & Measurements
============================

.. note::

    Although we do not have specific measurements for the STEMlab 125-14 LN board, the performance of the fast analog inputs is the same as for STEMlab 125-14. 
    The output performance with linear power supplies is covered in Leonhard Neuhaus's blog about |Red Pitaya DAC performance|.
    
You can find the measurements of the fast analog frontend here:

* :ref:`Original Gen - STEMlab 125-14 <measurements_orig_gen>`.

|

Schematics & 3D Models
========================

Schematics
----------

* :download:`Schematics_STEM_125-14_v1.1_LN.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_125-14_v1.1_LN.pdf>`.

.. note::

    Full hardware schematics for the Red Pitaya board are not available. Red Pitaya has open-source code but not open hardware schematics. 
    Nonetheless, development schematics are available. This schematic will give you information about hardware configuration, FPGA pin connections, and similar.

Mechanical Specifications & 3D Models
--------------------------------------

* STEP :download:`3D_STEM_125-14_v1.0.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_125-14_v1.0.zip>`.

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

.. |Original Gen hardware specs| replace:: :ref:`Original Gen hardware specifications <hw_specs_orig_gen>`
.. |Original Gen comparison table| replace:: :ref:`Original Gen board comparison table <rp-board-comp-orig_gen>`

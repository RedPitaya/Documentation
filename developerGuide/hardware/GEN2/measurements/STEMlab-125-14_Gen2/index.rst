.. _measurements_gen2:

####################################
Gen 2 Performance & Measurements
####################################

This section contains comprehensive performance measurements and specifications for Red Pitaya Gen 2 boards' fast analog inputs and outputs.

.. note::

    **Test Conditions:**
    
    * **Tested Board:** STEMlab 125-14 PRO Z7020 Gen 2
    * **Applicability:** All STEMlab 125-14 Gen 2 boards share the same analog frontend specifications
    * **Environmental conditions:** Laboratory environment with controlled temperature (25°C ± 1°C) and humidity (45% ± 5%)
    * **Calibration:** Factory calibration applied

|

Quick Reference
================

Fast Analog Input Performance
-------------------------------

.. table::
    :widths: 30 20 20

    +------------------------------------+------------------------------------+------------------------------------+
    | **Parameter**                      | **LV Mode (±1 V)**                 | **HV Mode (±20 V)**                |
    +====================================+====================================+====================================+
    | Bandwidth (-3 dB)                  | 52.02 MHz                          | 52.77 MHz                          |
    +------------------------------------+------------------------------------+------------------------------------+
    | Bandwidth flatness                 | <0.05 dB (DC to full BW)           | \-                                 |
    +------------------------------------+------------------------------------+------------------------------------+
    | Crosstalk (up to 30 MHz)           | >70 dB                             | 40-55 dB                           |
    +------------------------------------+------------------------------------+------------------------------------+
    | Input coupling                     | DC                                 | DC                                 |
    +------------------------------------+------------------------------------+------------------------------------+
    | Input impedance                    | 1 MΩ ‖ 10 pF                       | 1 MΩ ‖ 10 pF                       |
    +------------------------------------+------------------------------------+------------------------------------+

Fast Analog Output Performance
-------------------------------

.. table::
    :widths: 30 20 20

    +------------------------------------+------------------------------------+------------------------------------+
    | **Parameter**                      | **50 Ω Load**                      | **High-Z Load**                    |
    +====================================+====================================+====================================+
    | Voltage range                      | ±1 V                               | ±2 V                               |
    +------------------------------------+------------------------------------+------------------------------------+
    | Bandwidth (-3 dB)                  | 54.3 MHz                           | 55.0 MHz                           |
    +------------------------------------+------------------------------------+------------------------------------+
    | Bandwidth flatness                 | Within -1 dB (DC to full BW)       | Within -1 dB (DC to full BW)       |
    +------------------------------------+------------------------------------+------------------------------------+
    | Output impedance                   | 50 Ω (crisp, clean)                | \-                                 |
    +------------------------------------+------------------------------------+------------------------------------+
    | SFDR (typical)                     | 44-58 dB (frequency dependent)     | \-                                 |
    +------------------------------------+------------------------------------+------------------------------------+

|

Detailed Measurements
======================

.. toctree::
   :maxdepth: 2

   fast_analog_inputs
   fast_analog_outputs

|

Gen 2 Improvements Over Original Generation
============================================

**Key analog frontend improvements:**

* **Reduced noise and crosstalk** - Cleaner signals with better channel isolation
* **Enhanced output range** - ±2 V @ Hi-Z load vs ±1 V on original boards
* **Crisp 50 Ω output impedance** - Better matching for RF applications
* **Improved SFDR** - Higher spurious-free dynamic range
* **No power-on glitching** - Outputs remain stable during boot (hardware-disabled until FPGA loads)

For complete comparison, see :ref:`What's different in Gen 2? <hw_specs_gen2>`.

|

Legal & Disclaimers
====================

.. include:: ../../_specs_common/disclaimer.inc


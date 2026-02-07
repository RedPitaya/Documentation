.. _measurements_orig_gen:

############################################
Original Gen Performance & Measurements
############################################

This section contains comprehensive performance measurements and specifications for Red Pitaya Original Generation boards' fast analog inputs and outputs.

.. contents::
   :local:
   :depth: 2
   :backlinks: none

|

Test Conditions
================

.. note::

    **Measurement Information:**
    
    * **Tested Board:** STEMlab 125-14 (Original Generation)
    * **Applicability:** Most measurements can be extended to other Original Gen board models, but may vary depending on the specific board
    * **Environmental conditions:** Laboratory environment with controlled temperature (25°C ± 1°C) and humidity (45% ± 5%)
    * **Calibration:** Factory calibration applied
    * Noise-controlled laboratory environment
    * Board grounded through SMA ground
    * Reference equipment: Agilent 33250A generator, Agilent E4404B spectrum analyzer

|

Quick Reference
================

Fast Analog Input Performance
-------------------------------

.. table::
    :widths: 35 30 30

    +------------------------------------+------------------------------------+------------------------------------+
    | **Parameter**                      | **LV Mode (±1 V)**                 | **HV Mode (±20 V)**                |
    +====================================+====================================+====================================+
    | Bandwidth (-3 dB)                  | 50 MHz                             | 50 MHz                             |
    +------------------------------------+------------------------------------+------------------------------------+
    | Crosstalk (up to 30 MHz)           | >55 dB                             | >50 dB                             |
    +------------------------------------+------------------------------------+------------------------------------+
    | Crosstalk (above 30 MHz)           | 40 dB                              | 35 dB                              |
    +------------------------------------+------------------------------------+------------------------------------+
    | SFDR                               | < -90 dBFS                         | \-                                 |
    +------------------------------------+------------------------------------+------------------------------------+
    | Noise (typ.)                       | <0.5 mV std                        | \-                                 |
    +------------------------------------+------------------------------------+------------------------------------+
    | Input coupling                     | DC                                 | DC                                 |
    +------------------------------------+------------------------------------+------------------------------------+
    | Input impedance                    | 1 MΩ ‖ 10 pF                       | 1 MΩ ‖ 10 pF                       |
    +------------------------------------+------------------------------------+------------------------------------+
    | DC gain accuracy (after cal.)      | 0.2%                               | 0.5%                               |
    +------------------------------------+------------------------------------+------------------------------------+

Fast Analog Output Performance
-------------------------------

.. table::
    :widths: 40 30

    +------------------------------------+------------------------------------+
    | **Parameter**                      | **Value (50 Ω Load)**              |
    +====================================+====================================+
    | Voltage range                      | ±1 V                               |
    +------------------------------------+------------------------------------+
    | Bandwidth (-3 dB)                  | 50 MHz                             |
    +------------------------------------+------------------------------------+
    | Full scale power                   | > 9 dBm                            |
    +------------------------------------+------------------------------------+
    | Output impedance                   | ~50 Ω                              |
    +------------------------------------+------------------------------------+
    | Slew rate limit                    | 200 V/μs                           |
    +------------------------------------+------------------------------------+
    | Harmonics @ 1 MHz                  | -51 dBc                            |
    +------------------------------------+------------------------------------+
    | DC gain accuracy (after cal.)      | 0.4%                               |
    +------------------------------------+------------------------------------+

|

Detailed Measurements
======================

.. toctree::
   :maxdepth: 2

   fast_analog_inputs
   fast_analog_outputs

|

Key Characteristics
===================

**Original Generation boards feature:**

* **50 MHz bandwidth** - Full-rate sampling up to 125 MS/s
* **14-bit resolution** - Both ADC and DAC
* **DC coupling** - Direct DC measurements without AC coupling limitations
* **Proven design** - Extensively tested and characterized
* **Multiple models** - Including SDRlab 122-16 (16-bit), SIGNALlab 250-12 (250 MS/s, BNC connectors)

**Important design considerations:**

* **Common ground** - All SMA/BNC connectors share common ground with power supply
* **50 Ω loads** - Outputs designed for 50 Ω termination
* **Calibration** - Factory calibrated with user-accessible calibration utilities
* **Jumper settings** - Hardware jumpers for LV (±1 V) or HV (±20 V) input ranges

|

Comparison with Gen 2
======================

**Gen 2 improvements over Original Gen:**

* **Lower noise and crosstalk** - Improved analog frontend design
* **Enhanced output range** - ±2 V @ Hi-Z vs ±1 V on Original Gen
* **Better SFDR** - Improved spurious-free dynamic range
* **Crisp 50 Ω output** - More precise impedance matching
* **No glitching** - Hardware-controlled outputs during boot
* **USB-C power** - 5V 3A vs Micro USB 5V 2A

For Gen 2 measurements, see :ref:`Gen 2 Performance & Measurements <measurements_gen2>`.

|

Legal & Disclaimers
====================

.. note::

    The information provided by Red Pitaya d.o.o. is believed to be accurate and reliable. However, no liability is accepted for its use. Please note that the contents may be subject to change without prior notice.


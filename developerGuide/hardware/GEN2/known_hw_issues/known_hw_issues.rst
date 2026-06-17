.. _known_hw_issues_gen2:

###############################
Known Hardware Issues (Gen 2)
###############################

This page lists known hardware issues with Red Pitaya Gen 2 platforms. Hardware issues require board modifications or workarounds and will be addressed in future hardware revisions.

Affected Boards and Models
===========================

* **Boards Covered:**

    * STEMlab 125-14 Gen 2
    * STEMlab 125-14 PRO Gen 2
    * STEMlab 125-14 PRO Z7020 Gen 2
    * STEMlab 65-16 TI
    * STEMlab 125-14 TI


Active Issues
=============

.. note::

    Currently, no hardware issues have been reported for the Red Pitaya Gen 2 platforms. If you encounter any issues, please report them to the :ref:`Red Pitaya support team <report_problem>`.

|

Hardware Design Notes
=====================

These are design characteristics that do not affect overall functionality but deviate from the original design intent.
These characteristics are shared with Original Generation boards and require no workaround.

|

.. _slow_analog_voltage_note_gen2:

Slow Analog Input Voltage Range
--------------------------------

* **Affected Hardware:** All Red Pitaya boards (Original Generation and Gen 2)
* **Affected Component:** Slow analog inputs AI0-AI3 on the E2 connector
* **Status:** By design — inherited from Original Generation boards

**Background**

During the original hardware design, the Zynq 7010 XADC unipolar input range was assumed to be **0-0.5 V**. The actual unipolar input range of the Zynq XADC is **0-1 V**.
The slow analog input voltage dividers were therefore designed to map a 0-3.5 V external signal down to what was believed to be the ADC's full-scale range.

**Consequence**

With the 30.0 kΩ / 4.99 kΩ voltage divider (ratio ≈ 0.143) and the actual XADC full-scale of 1.0 V:

.. math::

    range = \frac{1.0\ \text{V}}{0.143} = 7.00\ \text{V}

The actual full-scale input range of the slow analog inputs (AI0–AI3) is **0-7.0 V**, not the originally intended 0-3.5 V.

.. note::

    Bipolar mode is unaffected. The XADC bipolar input range of ±0.5 V was correctly assumed during design, so bipolar operation gives the expected ±3.5 V full-scale input range.

.. _acq_data_return_example:

Aquisition data return
######################

Description
============

This example shows how to acquire 16k samples of a signal on fast analog inputs. The signal will be acquired when the internal trigger condition is met. The time length of the acquired signal depends on the time scale of a buffer that can be set with a decimation factor. The decimations and time scales of a buffer are given in the :ref:`sample rate and decimation <s_rate_and_dec>`. Voltage and frequency ranges depend on the Red Pitaya model. 


Required hardware
==================

    -   Red Pitaya STEMlab 125-14 4-Input
    -   Signal (function) generator
    
Wiring example:

.. figure:: img/on_given_trigger_acquire_signal_on_fast_analog_input.png


Required software
==================

.. .. include:: ../sw_requirement.inc

- **2.05-37 or higher OS**

.. note::

    This code is written for **2.05-37 or higher OS**. For older OS versions, please check when specific commands were released (a note is added to each command introduced in 2.00 or higher verisons).


SCPI Code Examples
====================

.. include:: ../dec_factor_note.inc
    
Code - MATLAB®
---------------

.. include:: ../matlab.inc

.. code-block:: matlab
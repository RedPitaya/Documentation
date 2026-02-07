
.. _commands_daisy:

===============================
Daisy chain clocks and triggers
===============================

Functionality overview
------------------------

Daisy chain commands configure clock and trigger sharing between multiple Red Pitaya boards connected via extension connectors. This enables synchronized multi-board acquisition and generation for expanded channel counts and simultaneous measurements across multiple units.


Important notes
----------------

* Requires hardware daisy chain connections between boards.
* Proper cable length and impedance matching critical for signal integrity.
* Clock distribution affects maximum achievable synchronization accuracy.


Code examples
-----------------

Here are some examples of how to use daisy chain synchronization:

* :ref:`Multi-board synchronization examples <examples_multiboard_sync>`.


Parameters and command table
-----------------------------

**Parameter options:**

- ``<state> = {OFF, ON}``
- ``<mode> = {ADC, DAC}``
- ``<enable> = {true, false}``

**Available Jupyter and API macros:**

- Shared trigger source - ``OUT_TR_ADC, OUT_TR_DAC``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| SCPI                                      | API, Jupyter                                                                       | DESCRIPTION                                                                                                |  ECOSYSTEM                    |
+===========================================+====================================================================================+============================================================================================================+===============================+
| | ``DAISY:ENable <state>``                | | C: ``rp_SetEnableDaisyChainSync``                                                | | Enables clock and trigger sync over SATA daisy chain connectors.                                         | only 2.00-15                  |
| | Examples:                               | |                                                                                  | | Once the primary board will be triggered, the trigger will be forwarded to the secondary board over      |                               |
| | ``DAISY:ENable ON``                     | | Python: ~                                                                        | | the SATA connector where the trigger can be detected using rp_GenTriggerSource with EXT_NE selector.     |                               |
|                                           | |                                                                                  | | Noticed that the trigger that is received over SATA is ORed with the external trigger from GPIO.         |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:ENable?`` > ``<state>``         | | C: ``rp_GetEnableDaisyChainSync``                                                | Returns the current state of the SATA daisy chain mode.                                                    | only 2.00-15                  |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:ENable?`` > ``ON``              | | Python: ~                                                                        |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:SYNC:TRIG <state>``             | | C: ``rp_SetEnableDaisyChainTrigSync(bool enable)``                               | | Enables trigger sync over SATA daisy chain connectors. Once the primary board will be triggered,         | 2.00-18 and up                |
| | Examples:                               | |                                                                                  | | the trigger will be forwarded to the secondary board over the SATA connector                             |                               |
| | ``DAISY:SYNC:TRIG ON``                  | | Python:  ``rp_SetEnableDaisyChainTrigSync(<enable>)``                            | | where the trigger can be detected using EXT_NE selector.                                                 |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:SYNC:TRIG?`` > ``<state>``      | | C: ``rp_GetEnableDaisyChainTrigSync(bool *status)``                              | | Returns the current state of the trigger synchronization using Daisy Chain.                              | 2.00-18 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:SYNC:TRIG?`` > ``ON``           | | Python: ``rp_GetEnableDaisyChainTrigSync()``                                     |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:SYNC:CLK <state>``              | | C: ``rp_SetEnableDiasyChainClockSync(bool enable)``                              | | Enables clock sync over SATA daisy chain connectors.                                                     | 2.00-18 and up                |
| | Examples:                               | |                                                                                  | | The primary board will start generating a clock for the secondary unit and so on.                        |                               |
| | ``DAISY:SYNC:CLK ON``                   | | Python: ``rp_SetEnableDiasyChainClockSync(<enable>)``                            |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:SYNC:CLK?`` > ``<state>``       | | C: ``rp_GetEnableDiasyChainClockSync(bool *state)``                              | | Returns the current state of the SATA daisy chain mode.                                                  | 2.00-18 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:SYNC:CLK?`` > ``ON``            | | Python: ``rp_GetEnableDiasyChainClockSync()``                                    |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRIG_O:ENable <state>``         | | C: ``rp_SetDpinEnableTrigOutput(bool enable)``                                   | | Turns DIO0_N into trigger output for selected source - acquisition or generation.                        | 2.00-15 - 2.00-30             |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRIG_O:ENable ON``              | | Python: ``rp_SetDpinEnableTrigOutput(<enable>)``                                 |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRig:Out:ENable <state>``       | | C: ``rp_SetDpinEnableTrigOutput(bool enable)``                                   | | Turns DIO0_N into trigger output for selected source - acquisition or generation.                        | 2.04-35 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRig:Out:ENable ON``            | | Python: ``rp_SetDpinEnableTrigOutput(<enable>)``                                 |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRIG_O:ENable?`` > ``<state>``  | | C: ``rp_GetDpinEnableTrigOutput(bool *state)``                                   | | Returns the current mode state for DIO0_N. If true, then the pin mode works as a source.                 | 2.00-15 - 2.00-30             |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRIG_O:ENable?`` > ``ON``       | | Python: ``rp_GetDpinEnableTrigOutput()``                                         |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRig:Out:ENable?`` > ``<state>``| | C: ``rp_GetDpinEnableTrigOutput(bool *state)``                                   | | Returns the current mode state for DIO0_N. If true, then the pin mode works as a source.                 | 2.04-35 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRig:Out:ENable?`` > ``ON``     | | Python: ``rp_GetDpinEnableTrigOutput()``                                         |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRIG_O:SOUR <mode>``            | | C: ``rp_SetSourceTrigOutput(rp_outTiggerMode_t mode)``                           | | Sets the trigger source mode ADC/DAC.                                                                    | 2.00-15 - 2.00-30             |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRIG_O:SOUR DAC``               | | Python: ``rp_SetSourceTrigOutput(<mode>)``                                       |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRig:Out:SOUR <mode>``          | | C: ``rp_SetSourceTrigOutput(rp_outTiggerMode_t mode)``                           | | Sets the trigger source mode ADC/DAC.                                                                    | 2.04-35 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRig:Out:SOUR DAC``             | | Python: ``rp_SetSourceTrigOutput(<mode>)``                                       |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRIG_O:SOUR?`` > ``<mode>``     | | C: ``rp_GetSourceTrigOutput(rp_outTiggerMode_t *mode)``                          | | Returns the trigger source mode.                                                                         | 2.00-15 - 2.00-30             |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRIG_O:SOUR?`` > ``DAC``        | | Python: ``rp_GetSourceTrigOutput()``                                             |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRig:Out:SOUR?`` > ``<mode>``   | | C: ``rp_GetSourceTrigOutput(rp_outTiggerMode_t *mode)``                          | | Returns the trigger source mode.                                                                         | 2.04-35 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRig:Out:SOUR?`` > ``DAC``      | | Python: ``rp_GetSourceTrigOutput()``                                             |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+


.. note::

   The daisy chain commands are meant to work with the :ref:`X-channel system <x-ch_streaming>` and the :ref:`Red Pitaya Click Shields <click_shield>`.

.. note::

   The trigger signals from the SATA connector and the DIO0_P (External trigger pin) are OR-ed together in the software.
   The generation and acquisition trigger fronts apply after the signals have been combined and trigger either DAC or ADC depending on the ``DAISY:TRig:Out:SOUR <mode>`` command.

|

* :ref:`Back to top <commands_daisy>`
* :ref:`Back to command list <command_list>`

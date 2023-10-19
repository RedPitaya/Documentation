.. _scpi_command_list:



.. TODO Add parameters for API commands!!!!

*******************************
List of supported SCPI commands
*******************************

.. _scpi_common:

======================
Board control commands
======================

.. _scpi_board:

Parameter options:

* ``<year> = {1900,...}``
* ``<month> = {1,12}``
* ``<day> = {1,31}``
* ``<hours> = {0,23}``
* ``<minutes> = {0,59}``
* ``<seconds> = {0,59}``
* ``<log_mode> = {OFF,CONSOLE,SYSLOG}``
* ``<board_id> = {0,15}``

Table of correlated SCPI and API commands for the Red Pitaya.

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+------------------------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| SCPI                                                 | API                     | DESCRIPTION                                               |  ECOSYSTEM         |
+======================================================+=========================+===========================================================+====================+
| | ``RP:LOGmode <log_mode>``                          | -                       | Enables scpi-server log output mode.                      | 1.04-18 and up     |
| | Examples:                                          |                         |                                                           |                    |
| | ``RP:LOGmode SYSLOG``                              |                         |                                                           |                    |
+------------------------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:TIME <hours>,<minutes>,<seconds>``        | -                       | Sets the time on the board.                               | 2.00-18 and up     |
| | Examples:                                          |                         |                                                           |                    |
| | ``SYSTem:TIME 16,12,45``                           |                         |                                                           |                    |
| | ``SYST:TIME 11,23,01``                             |                         |                                                           |                    |
+------------------------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:TIME?`` > ``time``                        | -                       | Returns the current time on the board.                    | 2.00-18 and up     |
| | Examples:                                          |                         |                                                           |                    |
| | ``SYSTem:TIME?`` > ``16:12:45``                    |                         |                                                           |                    |
| | ``SYST:TIME?`` > ``11:23:01``                      |                         |                                                           |                    |
+------------------------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:DATE <year>,<month>,<day>``               | -                       | Sets the date on the board.                               | 2.00-18 and up     |
| | Examples:                                          |                         |                                                           |                    |
| | ``SYSTem:DATE 2023,4,4``                           |                         |                                                           |                    |
| | ``SYST:DATE 2002,12,29``                           |                         |                                                           |                    |
+------------------------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:DATE?`` > ``date``                        | -                       | Returns the current date on the board.                    | 2.00-18 and up     |
| | Examples:                                          |                         |                                                           |                    |
| | ``SYSTem:DATE?`` > ``2023-04-04``                  |                         |                                                           |                    |
| | ``SYST:DATE?`` > ``2002-12-29``                    |                         |                                                           |                    |
+------------------------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:BRD:ID?`` > ``<board_id>``                | ``rp_HPGetModel``       | Returns the board model from the values rp_HPeModels_t.   | 2.00-18 and up     |
| | Examples:                                          |                         |                                                           |                    |
| | ``SYSTem:BRD:ID?`` > ``1``                         |                         |                                                           |                    |
+------------------------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:BRD:Name?`` > ``board name``              | ``rp_HPGetModelName``   | Returns the name of the board.                            | 2.00-18 and up     |
| | Examples:                                          |                         |                                                           |                    |
| | ``SYSTem:BRD:Name?`` > ``STEMlab 125-14 v1.0``     |                         |                                                           |                    |
+------------------------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+

.. _scpi_digital:

==============
LEDs and GPIOs
==============

Parameter options:

* ``<dir> = {OUT,IN}``
* ``<gpio> = {{DIO0_P...DIO7_P}, {DIO0_N...DIO7_N}}``
* ``<led> = {LED0...LED8}``
* ``<pin> = {gpio, led}``
* ``<state> = {0,1}``

Table of correlated SCPI and API commands for the Red Pitaya.

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+---------------------------------------+-------------------------+-----------------------------------------------------------------------------------+--------------------+
| SCPI                                  | API                     | DESCRIPTION                                                                       |  ECOSYSTEM         |
+=======================================+=========================+===================================================================================+====================+
| | ``DIG:RST``                         | ``rp_DpinReset``        | | Sets digital pins to default values. Pins DIO1_P - DIO7_P,                      | 1.04-18 and up     |
| | Examples:                           |                         | | RP_DIO0_N - RP_DIO7_N are set all INPUT and to LOW. LEDs are set to LOW/OFF.    |                    |
| | ``DIG:RST``                         |                         |                                                                                   |                    |
+---------------------------------------+-------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN:DIR <dir>,<gpio>``        | ``rp_DpinSetDirection`` | Set the direction of digital pins to output or input.                             | 1.04-18 and up     |
| | Examples:                           |                         |                                                                                   |                    |
| | ``DIG:PIN:DIR OUT,DIO0_N``          |                         |                                                                                   |                    |
| | ``DIG:PIN:DIR IN,DIO1_P``           |                         |                                                                                   |                    |
+---------------------------------------+-------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN:DIR? <gpio>``             | ``rp_DpinGetDirection`` | Gets digital input output pin direction..                                         | 1.04-18 and up     |
| | Examples:                           |                         |                                                                                   |                    |
| | ``DIG:PIN:DIR? DIO0_N``             |                         |                                                                                   |                    |
| | ``DIG:PIN:DIR? DIO1_P``             |                         |                                                                                   |                    |
+---------------------------------------+-------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN <pin>,<state>``           | ``rp_DpinSetState``     | | Set the state of digital outputs to 1 (HIGH) or 0 (LOW).                        | 1.04-18 and up     |
| | Examples:                           |                         | | Returns a 1 (HIGH) if the pin is floating.                                      |                    |
| | ``DIG:PIN DIO0_N,1``                |                         |                                                                                   |                    |
| | ``DIG:PIN LED2,1``                  |                         |                                                                                   |                    |
+---------------------------------------+-------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN? <pin>`` > ``<state>``    | ``rp_DpinGetState``     | Get state of digital inputs and outputs.                                          | 1.04-18 and up     |
| | Examples:                           |                         |                                                                                   |                    |
| | ``DIG:PIN? DIO0_N``                 |                         |                                                                                   |                    |
| | ``DIG:PIN? LED2``                   |                         |                                                                                   |                    |
+---------------------------------------+-------------------------+-----------------------------------------------------------------------------------+--------------------+


.. _scpi_analog:

=========================
Analog Inputs and Outputs
=========================

Parameter options:

* ``<ain> = {AIN0, AIN1, AIN2, AIN3}``
* ``<aout> = {AOUT0, AOUT1, AOUT2, AOUT3}``
* ``<pin> = {ain, aout}``
* ``<value> = {value in Volts}``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+---------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| SCPI                                  | API                     | DESCRIPTION                                               |  ECOSYSTEM         |
+=======================================+=========================+===========================================================+====================+
| | ``ANALOG:RST``                      | ``rp_ApinReset``        | Sets analog outputs to default values (0V).               | 1.04-18 and up     |
| | Examples:                           |                         |                                                           |                    |
| | ``ANALOG:RST``                      |                         |                                                           |                    |
+---------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| | ``ANALOG:PIN <pin>,<value>``        | ``rp_ApinSetValue``     | | Set the analog voltage on the slow analog outputs.      | 1.04-18 and up     |
| | Examples:                           |                         | | The voltage range of slow analog outputs is: 0 - 1.8 V  |                    |
| | ``ANALOG:PIN AOUT2,1.34``           |                         |                                                           |                    |
+---------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+
| | ``ANALOG:PIN? <pin>`` > ``<value>`` | ``rp_ApinGetValue``     | | Read the analog voltage from the slow analog inputs.    | 1.04-18 and up     |
| | Examples:                           |                         | | The voltage range of slow analog inputs is: 0 - 3.3 V   |                    |
| | ``ANALOG:PIN? AOUT2`` > ``1.34``    |                         |                                                           |                    |
| | ``ANALOG:PIN? AIN1`` > ``1.12``     |                         |                                                           |                    |
+---------------------------------------+-------------------------+-----------------------------------------------------------+--------------------+

.. _scpi_daisy:

===============================
Daisy chain clocks and triggers
===============================

Parameter options:

* ``<state> = {OFF, ON}``
* ``<mode> = {ADC, DAC}``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| SCPI                                      | API                                | DESCRIPTION                                                                                                                               |  ECOSYSTEM         |
+===========================================+====================================+===========================================================================================================================================+====================+
| | ``DAISY:ENable <state>``                | ``rp_SetEnableDaisyChainSync``     | | Enables clock and trigger sync over SATA daisy chain connectors.                                                                        | only 2.00-15       |
| | Examples:                               |                                    | | Once the primary board will be triggered, the trigger will be forwarded to the secondary board over                                     |                    |
| | ``DAISY:ENable ON``                     |                                    | | the SATA connector where the trigger can be detected using rp_GenTriggerSource with EXT_NE selector.                                    |                    |
|                                           |                                    | | Noticed that the trigger that is received over SATA is ORed with the external trigger from GPIO.                                        |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:ENable?`` > ``<state>``         | ``rp_GetEnableDaisyChainSync``     | Returns the current state of the SATA daisy chain mode.                                                                                   | only 2.00-15       |
| | Examples:                               |                                    |                                                                                                                                           |                    |
| | ``DAISY:ENable?`` > ``ON``              |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:SYNC:TRig <state>``             | ``rp_SetEnableDaisyChainTrigSync`` | | Enables trigger sync over SATA daisy chain connectors. Once the primary board will be triggered,                                        | 2.00-18 and up     | 
| | Examples:                               |                                    | | the trigger will be forwarded to the secondary board over the SATA connector where the trigger can be detected using EXT_NE selector.   |                    |
| | ``DAISY:SYNC:TRig ON``                  |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:SYNC:TRig?`` > ``<state>``      | ``rp_GetEnableDaisyChainTrigSync`` | | Returns the current state of the trigger synchronization using Daisy Chain.                                                             | 2.00-18 and up     |
| | Examples:                               |                                    |                                                                                                                                           |                    |
| | ``DAISY:SYNC:TRig?`` > ``ON``           |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:SYNC:CLK <state>``              | ``rp_SetEnableDiasyChainClockSync``| | Enables clock sync over SATA daisy chain connectors. The primary board will start generating a clock for the secondary unit and so on.  | 2.00-18 and up     |
| | Examples:                               |                                    | |                                                                                                                                         |                    |
| | ``DAISY:SYNC:CLK ON``                   |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:SYNC:CLK?`` > ``<state>``       | ``rp_GetEnableDiasyChainClockSync``| | Returns the current state of the SATA daisy chain mode.                                                                                 | 2.00-18 and up     |
| | Examples:                               |                                    |                                                                                                                                           |                    |
| | ``DAISY:SYNC:CLK?`` > ``ON``            |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:TRIG_O:ENable <state>``         | ``rp_SetDpinEnableTrigOutput``     | | Turns GPION_0 into trigger output for selected source - acquisition or generation.                                                      | 2.00-15 and up     |
| | Examples:                               |                                    |                                                                                                                                           |                    |
| | ``DAISY:TRIG_O:ENable ON``              |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:TRIG_O:ENable?`` > ``<state>``  | ``rp_GetDpinEnableTrigOutput``     | | Returns the current mode state for GPION_0. If true, then the pin mode works as a source.                                               | 2.00-15 and up     |
| | Examples:                               |                                    |                                                                                                                                           |                    |
| | ``DAISY:TRIG_O:ENable?`` > ``ON``       |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:TRIG_O:SOUR <mode>``            | ``rp_SetSourceTrigOutput``         | | Sets the trigger source mode ADC/DAC.                                                                                                   | 2.00-15 and up     |
| | Examples:                               |                                    |                                                                                                                                           |                    |
| | ``DAISY:TRIG_O:SOUR DAC``               |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| | ``DAISY:TRIG_O:SOUR?`` > ``<mode>``     | ``rp_GetSourceTrigOutput``         | | Returns the trigger source mode.                                                                                                        | 2.00-15 and up     |
| | Examples:                               |                                    |                                                                                                                                           |                    |
| | ``DAISY:TRIG_O:SOUR?`` > ``DAC``        |                                    |                                                                                                                                           |                    |
+-------------------------------------------+------------------------------------+-------------------------------------------------------------------------------------------------------------------------------------------+--------------------+

.. note::

   The daisy chain commands only work for the X-channel system and the upcoming Mikro-E extension shields.

.. note::

   The trigger signals from the SATA connector and the DIO0_P (External trigger pin) are OR-ed together in the software.
   The generation and acquisition trigger fronts apply after the signals have been combined and trigger either DAC or ADC depending on the ``DAISY:TRIG_O:SOUR <mode>`` command.

.. _scpi_gen:

================
Signal Generator
================

Parameter options:

* ``<n> = {1,2}`` (set channel OUT1 or OUT2)
* ``<state> = {ON,OFF}`` Default: ``OFF``
* ``<frequency> = {0Hz...62.5e6Hz}`` Default: ``1000``
* ``<func> = {SINE, SQUARE, TRIANGLE, SAWU, SAWD, PWM, ARBITRARY, DC, DC_NEG}`` Default: ``SINE``
* ``<amplitude> = {-1V...1V}`` Default: ``1`` for SIGNALlab 250-12 this value {-5V...5V}
* ``<offset> = {-1V...1V}`` Default: ``0``
* ``<phase> = {-360deg ... 360deg}`` Default: ``0``
* ``<dcyc> = {0...1}`` Default: ``0.5`` Where 1 corresponds to 100%
* ``<array> = {value1, ...}`` max. 16384 values, floats in the range -1 to 1
* ``<burst> = {BURST , CONTINUOUS}`` Default: ``CONTINUOUS``
* ``<count> = {1...50000}`` , Default: ``1``
* ``<time> = {1µs-500s}`` Value in *µs*.
* ``<utime> = {value in us}``
* ``<trigger> = {EXT_PE, EXT_NE, INT, GATED}``

   - ``EXT`` = External
   - ``INT`` = Internal
   - ``GATED`` = gated busts

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                               | API                                    | DESCRIPTION                                                                                  |  ECOSYSTEM         |
+====================================================+========================================+==============================================================================================+====================+
| | ``OUTPUT:STATE <state>``                         | | ``rp_GenOutEnableSync``              | Runs or Stops both channels synchronously.                                                   | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``OUTPUT:STATE ON``                              |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``OUTPUT<n>:STATE <state>``                      | | ``rp_GenOutEnable``                  | | Disable or enable fast analog outputs.                                                     | 1.04-18 and up     |
| | Examples:                                        | | ``rp_GenOutDisable``                 | | The generator is waiting for the trigger.                                                  |                    |
| | ``OUTPUT1:STATE ON``                             |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``OUTPUT<n>:STATE?`` > ``<state>``               | ``rp_GenOutIsEnabled``                 | Gets value ON if the channel is enabled otherwise returns OFF.                               | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``OUTPUT1:STATE?`` > ``ON``                      |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FREQ:FIX <frequency>``                 | ``rp_GenFreq``                         | | Set the frequency of fast analog outputs.                                                  | 1.04-18 and up     |
| | Examples:                                        |                                        | | For ARBITRARY waveform this is the frequency of the whole buffer (16384 samples).          |                    |
| | ``SOUR2:FREQ:FIX 100000``                        |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FREQ:FIX?``                            | ``rp_GenGetFreq``                      | Gets channel signal frequency.                                                               | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR2:FREQ:FIX?`` > ``100000``                 |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FUNC <func>``                          | ``rp_GenWaveform``                     | Set the waveform of fast analog outputs.                                                     | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR2:FUNC TRIANGLE``                          |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FUNC?`` > ``<func>``                   | ``rp_GenGetWaveform``                  | Gets channel signal waveform.                                                                | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR2:FUNC?`` > ``TRIANGLE``                   |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:VOLT <amplitude>``                     | ``rp_GenAmp``                          | | Set the amplitude voltage of fast analog outputs in Volts.                                 | 1.04-18 and up     |
| | Examples:                                        |                                        | | Amplitude + offset value must be less than the maximum                                     |                    |
| | ``SOUR2:VOLT 0.5``                               |                                        | | output range ± 1V (depends on board model).                                                |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:VOLT?`` > ``<amplitude>``              | ``rp_GenGetAmp``                       | Gets channel signal peak to peak amplitude.                                                  | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR2:VOLT?`` > ``0.5``                        |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:VOLT:OFFS <offset>``                   | ``rp_GenOffset``                       | | Set the offset voltage of fast analog outputs in Volts                                     | 1.04-18 and up     |
| | Examples:                                        |                                        | | Amplitude + offset value must be less than the maximum                                     |                    |
| | ``SOUR1:VOLT:OFFS 0.2``                          |                                        | | output range ± 1V (depends on board model).                                                |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:VOLT:OFFS?`` > ``<offset>``            | ``rp_GenGetOffset``                    | Gets DC offset of the signal.                                                                | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:VOLT:OFFS?`` > ``0.2``                   |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:PHAS <phase>``                         | ``rp_GenPhase``                        | Set the phase of fast analog outputs.                                                        | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR2:PHAS 30``                                |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:PHAS?`` > ``<phase>``                  | ``rp_GenGetPhase``                     | Gets channel signal phase.                                                                   | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR2:PHAS?`` > ``30``                         |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:DCYC <par>``                           | ``rp_GenDutyCycle``                    | Set the duty cycle of the PWM waveform.                                                      | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:DCYC 0.2``                               |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:DCYC?`` > ``<par>``                    | ``rp_GenGetDutyCycle``                 | Gets duty cycle of PWM signal.                                                               | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:DCYC`` > ``0.2``                         |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRAC:DATA:DATA <array>``               | ``rp_GenArbWaveform``                  | | Import data for arbitrary waveform generation (should be 16384 samples).                   | 1.04-18 and up     |
| | Examples:                                        |                                        | | If fewer samples are provided the output frequency will be higher.                         |                    |
| | ``SOUR1:TRAC:DATA:DATA``                         |                                        |                                                                                              |                    |
| | ``1,0.5,0.2``                                    |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRAC:DATA:DATA?`` > ``<array>``        | ``rp_GenGetArbWaveform``               | Gets user defined waveform.                                                                  | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:TRAC:DATA:DATA?`` >                      |                                        |                                                                                              |                    |
| | ``1,0.5,0.2``                                    |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:STAT <burst>``                    | ``rp_GenMode``                         | | Enable or disable burst (pulse) mode.                                                      | 1.04-18 and up     |
| | Examples:                                        |                                        | | Red Pitaya will generate **R** bursts with **N** signal periods.                           |                    |
| | ``SOUR1:BURS:STAT BURST``                        |                                        | | **P** is the time between the start of one and the start of the next burst.                |                    |
| | ``SOUR1:BURS:STAT CONTINUOUS``                   |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:STAT?`` > ``<burst>``             | ``rp_GenGetMode``                      | Gets generation mode.                                                                        | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:BURS:STAT?`` > ``BURST``                 |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:NCYC <count>``                    | ``rp_GenBurstCount``                   | Set the number of cycles/periods in one burst (**N**).                                       | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:BURS:NCYC 3``                            |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:NCYC?`` > ``<count>``             | ``rp_GenGetBurstCount``                | Gets number of generated waveforms in a burst.                                               | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:BURS:NCYC`` > ``3``                      |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:NOR <count>``                     | ``rp_GenBurstRepetitions``             | Set the number of repeated bursts (**R**) (65536 == INF repetitions)                         | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:BURS:NOR 5``                             |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:NOR?`` > ``<count>``              | ``rp_GenGetBurstRepetitions``          | Gets number of burst repetitions.                                                            | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:BURS:NOR`` > ``5``                       |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+---------------------------+------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:INT:PER <time>``                  | ``rp_GenBurstPeriod``                  | | Set the duration of a single burst in microseconds (**P**).                                | 1.04-18 and up     |
| | Examples:                                        |                                        | | Time between the start of one and the start of the next burst.                             |                    |
| | ``SOUR1:BURS:INT:PER 1000000``                   |                                        | | The bursts will always have at least 1 us between them: If the period is                   |                    |
|                                                    |                                        | | shorter than the burst, the software will default to 1 us between bursts.                  |                    |
+----------------------------------------------------+----------------------------------------+---------------------------+------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:INT:PER?`` > ``<time>``           | ``rp_GenGetBurstPeriod``               | Gets the period of one burst in micro seconds.                                               | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:BURS:INT:PER?`` > ``1000000``            |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRig:SOUR <trigger>``                  | ``rp_GenTriggerSource``                | | Set the trigger source for the selected signal.                                            | 1.04-18 and up     |
| | Examples:                                        |                                        | | External trigger must be a 3V3 CMOS signal.                                                |                    |
| | ``SOUR1:TRig:SOUR EXT_PE``                       |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRig:SOUR?`` > ``<trigger>``           | ``rp_GenGetTriggerSource``             | Gets trigger source.                                                                         | 1.04-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:TRig:SOUR?`` > ``EXT_PE``                |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:LASTValue <amplitude>``           | ``rp_GenBurstLastValue``               | | Sets the value to be set at the end of the generated signal in burst mode.                 | 2.00-18 and up     |
| | Examples:                                        |                                        | | The output will stay on this value until a new signal is generated.                        |                    |
| | ``SOUR1:BURS:LASTValue 0.5``                     |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:LASTValue?`` > ``<amplitude>``    | ``rp_GenGetBurstLastValue``            | Gets the value to be set at the end of the generated signal in burst mode.                   | 2.00-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:BURS:LASTValue`` > ``0.5``               |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:INITValue <amplitude>``                | ``rp_GenSetInitGenValue``              | | The level of which is set by the generator after                                           | 2.00-18 and up     |
| | Examples:                                        |                                        | | the outputs are turned on, but before the signal is generated.                             |                    |
| | ``SOUR1:INITValue 0.5``                          |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:INITValue?`` > ``<amplitude>``         | ``rp_GenGetInitGenValue``              | Gets the value of the initial signal level.                                                  | 2.00-18 and up     |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:INITValue?`` > ``0.5``                   |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:TRig:INT``                                | ``rp_GenTrigger``                      | | Triggers both sources/channels immediately.                                                | 1.04-18 and up     |
| |                                                  |                                        |                                                                                              |                    |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR:TRig:INT``                                |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRig:INT``                             | ``rp_GenTrigger``                      | | Triggers the selected source immediately for the selected channel.                         | 1.04-18 and up     |
| |                                                  |                                        |                                                                                              |                    |
| | Examples:                                        |                                        |                                                                                              |                    |
| | ``SOUR1:TRig:INT``                               |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``GEN:RST``                                      | ``rp_GenReset``                        | Reset the generator to default settings.                                                     | 1.04-18 and up     |
|                                                    |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``PHAS:ALIGN``                                   | ``rp_GenSynchronise``                  | Align the output phases of both channels.                                                    | 1.04-18 and up     |
|                                                    |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:TRig:EXT:DEBouncer[:US] <utime>``         | ``rp_GenSetExtTriggerDebouncerUs``     | Sets ext. trigger debouncer for generation in Us (Value must be positive).                   | 2.00-15 and up     |
| | Example:                                         |                                        |                                                                                              |                    |
| | ``SOUR:TRig:EXT:DEBouncer 1``                    |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:TRig:EXT:DEBouncer[:US]?`` > ``<utime>``  | ``rp_GenGetExtTriggerDebouncerUs``     | Gets ext. trigger debouncer for generation in Us.                                            | 2.00-15 and up     |
| | Example:                                         |                                        |                                                                                              |                    |
| | ``SOUR:TRig:EXT:DEBouncer?`` > ``1``             |                                        |                                                                                              |                    |
+----------------------------------------------------+----------------------------------------+----------------------------------------------------------------------------------------------+--------------------+

.. note::

   For STEMlab 125-14 4-Input, these commands are not applicable.

.. _scpi_acq:

===========
Acquisition
===========

-------
Control
-------

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+----------------------------------+-----------------------------+------------------------------------------------------------------+--------------------+
| SCPI                             | API                         | DESCRIPTION                                                      |  ECOSYSTEM         |
+==================================+=============================+==================================================================+====================+
| ``ACQ:START``                    | ``rp_AcqStart``             | Start the acquisition.                                           | 1.04-18 and up     |
+----------------------------------+-----------------------------+------------------------------------------------------------------+--------------------+
| ``ACQ:STOP``                     | ``rp_AcqStop``              | Stop the acquisition.                                            | 1.04-18 and up     |
+----------------------------------+-----------------------------+------------------------------------------------------------------+--------------------+
| ``ACQ:RST``                      | ``rp_AcqReset``             | Stops the acquisition and sets all parameters to default values. | 1.04-18 and up     |
+----------------------------------+-----------------------------+------------------------------------------------------------------+--------------------+

.. _scpi_acq_dec:

--------------------------
Sampling rate & decimation
--------------------------

Parameter options:

* ``<decimation> = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536}`` Default: ``1``
* ``<average> = {OFF,ON}`` Default: ``ON``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+-----------------------------+----------------------------------------------------------------------+--------------------+
| SCPI                                | API                         | DESCRIPTION                                                          |  ECOSYSTEM         |
+=====================================+=============================+======================================================================+====================+
| | ``ACQ:DEC <decimation>``          | ``rp_AcqSetDecimation``     | | Set the decimation factor.                                         | 1.04-18 and up     |
| | Example:                          |                             | | Should be a power of 2.                                            |                    |
| | ``ACQ:DEC 4``                     |                             |                                                                      |                    |
+-------------------------------------+-----------------------------+----------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC?`` > ``<decimation>``   | ``rp_AcqGetDecimation``     | Get the decimation factor.                                           | 1.04-18 and up     |
| | Example:                          |                             |                                                                      |                    |
| | ``ACQ:DEC?`` > ``1``              |                             |                                                                      |                    |
+-------------------------------------+-----------------------------+----------------------------------------------------------------------+--------------------+
| | ``ACQ:AVG <average>``             | ``rp_AcqSetAveraging``      | | Enable/disable averaging.                                          | 1.04-18 and up     |
|                                     |                             | | Each sample is the average of skipped samples if decimation > 1.   |                    |
+-------------------------------------+-----------------------------+----------------------------------------------------------------------+--------------------+
| | ``ACQ:AVG?`` > ``<average>``      | ``rp_AcqGetAveraging``      | | Get the averaging status.                                          | 1.04-18 and up     |
| | Example:                          |                             | | Averages the skipped samples when ``DEC`` > 1                      |                    |
| | ``ACQ:AVG?`` > ``ON``             |                             |                                                                      |                    |
+-------------------------------------+-----------------------------+----------------------------------------------------------------------+--------------------+

.. _scpi_trigger:

=======
Trigger
=======

Parameter options:

* ``<n> = {1,2}`` (set channel IN1 or IN2)
* ``<source> = {DISABLED, NOW, CH1_PE, CH1_NE, CH2_PE, CH2_NE, EXT_PE, EXT_NE, AWG_PE, AWG_NE}``  Default: ``DISABLED``
* ``<status> = {WAIT, TD}``
* ``<time> = {value in ns}``
* ``<utime> = {value in us}``
* ``<count> = {value in samples}``
* ``<gain> = {LV, HV}``
* ``<level> = {value in V}``
* ``<mode> = {AC,DC}``

.. note::

   For STEMlab 125-14 4-Input ``<n> = {1,2,3,4}`` (set channel IN1, IN2, IN3 or IN4)

.. note::

   For STEMlab 125-14 4-Input ``<source> = {DISABLED, NOW, CH1_PE, CH1_NE, CH2_PE, CH2_NE, CH3_PE, CH3_NE, CH4_PE, CH4_NE, EXT_PE, EXT_NE, AWG_PE, AWG_NE}``  Default: ``DISABLED``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| SCPI                                               | API                                    | DESCRIPTION                                                                   |  ECOSYSTEM         |
+====================================================+========================================+===============================================================================+====================+
| | ``ACQ:TRig <source>``                            | ``rp_AcqSetTriggerSrc``                | Disable triggering, trigger immediately or set trigger source & edge.         | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig CH1_PE``                              |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:STAT?``                               | ``rp_AcqGetTriggerState``              | Get trigger status. If DISABLED -> TD else WAIT.                              | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:STAT?`` > ``WAIT``                    |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:FILL?``                               | ``rp_AcqGetBufferFillState``           | Returns 1 if the buffer is full of data. Otherwise returns 0.                 | 2.00-15 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:FILL?`` > ``1``                       |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:DLY <count>``                         | ``rp_AcqSetTriggerDelay``              | | Set the trigger delay in samples.                                           | 1.04-18 and up     |
| | Example:                                         |                                        | | Triggering moment is by default around 8192th sample                        |                    |
| | ``ACQ:TRig:DLY 2314``                            |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:DLY?`` > ``<count>``                  | ``rp_AcqGetTriggerDelay``              | Get the trigger delay in samples.                                             | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:DLY?`` > ``2314``                     |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:DLY:NS <time>``                       | ``rp_AcqSetTriggerDelayNs``            | Set the trigger delay in ns.                                                  | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:DLY:NS 128``                          |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:DLY:NS?`` > ``<time>``                | ``rp_AcqGetTriggerDelayNs``            | Get the trigger delay in ns.                                                  | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:DLY:NS?`` > ``128ns``                 |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:HYST level``                          | ``rp_AcqSetTriggerHyst``               | Sets the trigger threshold hysteresis value in volts.                         | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:HYST 0.005``                          |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:HYST?`` > ``level``                   | ``rp_AcqGetTriggerHyst``               | Gets currently set trigger threshold hysteresis value in volts.               | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:HYST?`` > ``0.005`` V                 |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:GAIN <gain>``                      | ``rp_AcqSetGain``                      | | Set the gain settings to HIGH or LOW.                                       | 1.04-18 and up     |
| |                                                  |                                        | | (For SIGNALlab 250-12 this is 1:20 and 1:1 attenuator).                     |                    |
| | Example:                                         |                                        | | This gain refers to jumper settings on Red Pitaya fast analog inputs.       |                    |
| | ``ACQ:SOUR1:GAIN LV``                            |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:GAIN?`` > ``<gain>``               | ``rp_AcqGetGain``                      | | Get the gain setting.                                                       | 1.04-18 and up     |
| |                                                  |                                        | | (For SIGNALlab 250-12 this is 1:20 and 1:1 attenuator).                     |                    |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:SOUR1:GAIN?`` > ``HV``                     |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:COUP <mode>``                      | ``rp_AcqSetAC_DC``                     | Sets the AC / DC modes of input.                                              | 1.04-18 and up     |
| | Example:                                         |                                        | (Only SIGNALlab 250-12)                                                       |                    |
| | ``ACQ:SOUR1:COUP AC``                            |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:COUP?`` > ``<mode>``               | ``rp_AcqGetAC_DC``                     | Get the AC / DC modes of input.                                               | 1.04-18 and up     |
| | Example:                                         |                                        | (Only SIGNALlab 250-12)                                                       |                    |
| | ``ACQ:SOUR1:COUP?`` > ``AC``                     |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:LEV <level>``                         | ``rp_AcqSetTriggerLevel``              | Set the trigger level in V.                                                   | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:LEV 0.125 V``                         |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:LEV?`` > ``level``                    | ``rp_AcqGetTriggerLevel``              | Get the trigger level in V.                                                   | 1.04-18 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:LEV?`` > ``0.123 V``                  |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:EXT:LEV <level>``                     | ``rp_AcqSetTriggerLevel``              | Set the external trigger level in V.                                          | 1.04-18 and up     |
| | Example:                                         |                                        | (Only SIGNALlab 250-12)                                                       |                    |
| | ``ACQ:TRig:EXT:LEV 1``                           |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:EXT:LEV?`` > ``level``                | ``rp_AcqGetTriggerLevel``              | Get the external trigger level in V.                                          | 1.04-18 and up     |
| | Example:                                         |                                        | (Only SIGNALlab 250-12)                                                       |                    |
| | ``ACQ:TRig:EXT:LEV?`` > ``1``                    |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:EXT:DEBouncer[:US] <utime>``          | ``rp_AcqSetExtTriggerDebouncerUs``     | Sets ext. trigger debouncer for acquisition in Us (Value must be positive).   | 2.00-15 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:EXT:DEBouncer 1``                     |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:TRig:EXT:DEBouncer[:US]?`` > ``<utime>``   | ``rp_AcqGetExtTriggerDebouncerUs``     | Gets ext. trigger debouncer for acquisition in Us.                            | 2.00-15 and up     |
| | Example:                                         |                                        |                                                                               |                    |
| | ``ACQ:TRig:EXT:DEBouncer?`` > ``1``              |                                        |                                                                               |                    |
+----------------------------------------------------+----------------------------------------+-------------------------------------------------------------------------------+--------------------+

.. _scpi_data_pointers:

=============
Data pointers
=============

The data is written into a circular buffer which is constantly being overwritten until the triggering moment. Consequently, the trigger position can be anywhere inside the circular buffer,
even though it is displayed to happen at approx. 8192nd sample in the acquired data (is affected by the ``ACQ:TRIG:DLY`` command).

Parameter options:

* ``<pos> = {position inside circular buffer}``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+---------------------------------+------------------------------------+--------------------------------------------------------+--------------------+
| SCPI                            | API                                | DESCRIPTION                                            |  ECOSYSTEM         |
+=================================+====================================+========================================================+====================+
| | ``ACQ:WPOS?`` > ``pos``       | ``rp_AcqGetWritePointer``          | Returns the current position of the write pointer.     | 1.04-18 and up     |
| | Example:                      |                                    |                                                        |                    |
| | ``ACQ:WPOS?`` > ``1024``      |                                    |                                                        |                    |
+---------------------------------+------------------------------------+--------------------------------------------------------+--------------------+
| | ``ACQ:TPOS?`` > ``pos``       | ``rp_AcqGetWritePointerAtTrig``    | Returns the position where the trigger event appeared. | 1.04-18 and up     |
| | Example:                      |                                    |                                                        |                    |
| | ``ACQ:TPOS?`` > ``512``       |                                    |                                                        |                    |
+---------------------------------+------------------------------------+--------------------------------------------------------+--------------------+

.. _scpi_data:

=========
Data read
=========

* ``<n> = {1,2}`` (set channel IN1 or IN2)
* ``<units> = {RAW, VOLTS}``
* ``<format> = {BIN, ASCII}`` Default ``ASCII``
* ``<start_pos> = {0,1,...,16384}``
* ``<stop_pos>  = {0,1,...,16384}``
* ``<m>  = {0,1,...,16384}``

.. note::

   For STEMlab 125-14 4-Input ``<n> = {1,2,3,4}`` (set channel IN1, IN2, IN3 or IN4)

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| SCPI                                     | API                          | DESCRIPTION                                                                            |  ECOSYSTEM         |
+==========================================+==============================+========================================================================================+====================+
| | ``ACQ:DATA:Units <units>``             | ``rp_AcqScpiDataUnits``      | Select units in which the acquired data will be returned.                              | 1.04-18 and up     |
| | Example:                               |                              |                                                                                        |                    |
| | ``ACQ:DATA:Units RAW``                 |                              |                                                                                        |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DATA:Units?`` > ``<units>``      | ``rp_AcqGetScpiDataUnits``   | Get units in which the acquired data will be returned.                                 | 1.04-18 and up     |
| | Example:                               |                              |                                                                                        |                    |
| | ``ACQ:DATA:Units?`` > ``RAW``          |                              |                                                                                        |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DATA:FORMAT <format>``           | ``rp_AcqScpiDataFormat``     | Select the format in which the acquired data will be returned.                         | 1.04-18 and up     |
| | Example:                               |                              |                                                                                        |                    |
| | ``ACQ:DATA:FORMAT ASCII``              |                              |                                                                                        |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:Start:End?``        | | ``rp_AcqGetDataPosRaw``    | | Read samples from start to stop position.                                            | 1.04-18 and up     |
| | ``<start_pos>,<end_pos>``              | | ``rp_AcqGetDataPosV``      | | ``<start_pos> = {0,1,...,16384}``                                                    |                    |
| | Example:                               |                              | | ``<stop_pos>  = {0,1,...,16384}``                                                    |                    |
| | ``ACQ:SOUR1:DATA:Start:End? 10,13`` >  |                              |                                                                                        |                    |
| | ``{123,231,-231}``                     |                              |                                                                                        |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:Start:N?``          | | ``rp_AcqGetDataRaw``       | | Read ``m`` samples from the start position onwards.                                  | 1.04-18 and up     |
| | ``<start_pos>,<m>``                    | | ``rp_AcqGetDataV``         |                                                                                        |                    |
| | Example:                               |                              |                                                                                        |                    |
| | ``ACQ:SOUR1:DATA:Start:N? 10,3`` >     |                              |                                                                                        |                    |
| | ``{1.2,3.2,-1.2}``                     |                              |                                                                                        |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA?``                  | | ``rp_AcqGetOldestDataRaw`` | | Read the full buffer.                                                                | 1.04-18 and up     |
| | Example:                               | | ``rp_AcqGetOldestDataV``   | | Starting from the oldest sample in the buffer (first sample after trigger delay).    |                    |
| | ``ACQ:SOUR2:DATA?`` >                  |                              | | The trigger delay is set to zero by default (in samples or in seconds).              |                    |
| | ``{1.2,3.2,...,-1.2}``                 |                              | | If the trigger delay is set to zero, it will read the full buffer size starting      |                    |
| |                                        |                              | | from the trigger.                                                                    |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:Old:N? <m>``        | | ``rp_AcqGetOldestDataRaw`` | | Read ``m`` samples after the trigger delay, starting from the oldest sample          | 1.04-18 and up     |
| | Example:                               | | ``rp_AcqGetOldestDataV``   | | in the buffer (first sample after trigger delay).                                    |                    |
| | ``ACQ:SOUR2:DATA:Old:N? 3`` >          |                              | | The trigger delay is set to zero by default (in samples or in seconds).              |                    |
| | ``{1.2,3.2,-1.2}``                     |                              | | If the trigger delay is set to zero, it will read m samples starting                 |                    |
| |                                        |                              | | from the trigger.                                                                    |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:Last:N? <m>``       | | ``rp_AcqGetLatestDataRaw`` | | Read ``m`` samples before the trigger delay.                                         | 1.04-18 and up     |
| | Example:                               | | ``rp_AcqGetLatestDataV``   | | The trigger delay is set to zero by default (in samples or in seconds).              |                    |
| | ``ACQ:SOUR1:DATA:Last:N? 3`` >         |                              | | If the trigger delay is set to zero, it will read m samples before the trigger.      |                    |
| | ``{1.2,3.2,-1.2}``                     |                              |                                                                                        |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:BUF:SIZE?`` > ``<size>``         | ``rp_AcqGetBufSize``         |  Returns the buffer size.                                                              | 1.04-18 and up     |
| | Example:                               |                              |                                                                                        |                    |
| | ``ACQ:BUF:SIZE?`` > ``16384``          |                              |                                                                                        |                    |
+------------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+


.. _scpi_acq_axi:

================
DMA mode for ACQ
================

* ``<n> = {1,2}`` (set channel IN1 or IN2)
* ``<units> = {RAW, VOLTS}``
* ``<decimation> = {1,2,4,8,16,17,18,19,...,65534,65535,65536}`` Default: ``1``
* ``<byte> = {0...}`` in byte
* ``<count> = {value in samples}``
* ``<pos> = {position inside circular buffer in samples}``
* ``<state> = {ON,OFF}`` Default: ``OFF``
* ``<start> = {byte}`` Address of reserved memory
* ``<size> = {byte}`` Size of buffer in bytes


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| SCPI                                               | API                               | DESCRIPTION                                                                            |  ECOSYSTEM         |
+====================================================+===================================+========================================================================================+====================+
| | ``ACQ:AXI:DATA:UNITS <units>``                   | -                                 | Select units in which the acquired data will be returned.                              | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:DATA:UNITS RAW``                       |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DATA:UNITS?`` > ``<units>``            | -                                 | Get units in which the acquired data will be returned.                                 | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:DATA:UNITS?`` > ``RAW``                |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC <decimation>``                     | ``rp_AcqAxiSetDecimationFactor``  | Sets the decimation used at acquiring signal for AXI.                                  | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:DEC 4``                                |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC?`` > ``<decimation>``              | ``rp_AcqAxiGetDecimationFactor``  | Get the decimation factor.                                                             | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:DEC?`` > ``1``                         |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:START?`` > ``<byte>``                  | ``rp_AcqAxiGetMemoryRegion``      | Get start address of reserved memory for DMA mode.                                     | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:START?`` > ``16777216``                |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SIZE?`` > ``<byte>``                   | ``rp_AcqAxiGetMemoryRegion``      | Get size of reserved memory for DMA mode.                                              | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:SIZE?`` > ``2097152``                  |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:ENable <state>``               | ``rp_AcqAxiEnable``               | Sets the AXI enable state.                                                             | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:SOUR1:ENable ON``                      |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:TRIG:FILL?``                   | ``rp_AcqAxiGetBufferFillState``   | Indicates whether the ADC AXI buffer was full of data.                                 | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:SOUR1:TRIG:FILL?`` > ``1``             |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Dly <count>``             | ``rp_AcqAxiSetTriggerDelay``      | Sets the number of decimated data after the trigger written into memory.               | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:SOUR1:Trig:Dly 2314``                  |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Dly?`` > ``<count>``      | ``rp_AcqAxiGetTriggerDelay``      | Gets the number of decimated data after trigger written into memory.                   | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:SOUR1:Trig:Dly?`` > ``2314``           |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Write:Pos?`` > ``pos``         | ``rp_AcqAxiGetWritePointer``      | Returns current position of AXI ADC write pointer.                                     | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:SOUR1:Write:Pos?`` > ``1024``          |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Pos?`` > ``pos``          | ``rp_AcqAxiGetWritePointerAtTrig``| Returns the position of AXI ADC write pointer at a time when trigger arrived.          | 2.00-18 and up     |
| | Example:                                         |                                   |                                                                                        |                    |
| | ``ACQ:AXI:SOUR1:Trig:Pos?`` > ``512``            |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:SET:Buffer <start>,<size>``    | ``rp_AcqAxiSetBufferBytes``       | | Sets the AXI ADC buffer address and size in bytes.                                   | 2.00-18 and up     |
| | Example:                                         |                                   | | Buffer size must be a multiple of 2.                                                 |                    |
| | ``ACQ:AXI:SOUR<n>:SET:Buffer 16777216,512``      |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:DATA:Start:N? <pos>,<count>``  | ``rp_AcqAxiGetDataV``             | | Read ``count`` samples from the ``pos`` position onwards.                            | 2.00-18 and up     |
| | Example:                                         |                                   | | Returns the value as a text array of values or a byte array.                         |                    |
| | ``ACQ:AXI:SOUR1:DATA:Start:N? 20,3`` >           |                                   | | Depending on the setting.                                                            |                    |
| | ``{1.2,3.2,-1.2}``                               |                                   |                                                                                        |                    |
+----------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------------------+--------------------+

.. _scpi_uart:

====
UART
====

Parameter options:

* ``<bits> = {CS6, CS7, CS8}``  Default: ``CS8``
* ``<stop> = {STOP1, STOP2}``  Default: ``STOP1``
* ``<parity> = {NONE, EVEN, ODD, MARK, SPACE}``  Default: ``NONE``
* ``<timeout> = {0...255} in (1/10 seconds)`` Default: ``0``
* ``<speed> = {1200,2400,4800,9600,19200,38400,57600,115200,230400,576000,921000,1000000,1152000,1500000,2000000,2500000,3000000,3500000,4000000}`` Default: ``9600``
* ``<data> = {XXX,... | #HXX,... | #QXXX,... | #BXXXXXXXX,... }`` Array of data separated comma

   - ``XXX`` = Dec format
   - ``#HXX`` = Hex format
   - ``#QXXX`` = Oct format
   - ``#BXXXXXXXX`` = Bin format


.. note::

    When establishing UART communication with Red Pitaya and another device, do not forget to connect the External Common Mode (GND) pin (in addition to the RX and TX pins). Otherwise, the communication might be unreliable.

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| SCPI                                | API                          | DESCRIPTION                                                                            |  ECOSYSTEM         |
+=====================================+==============================+========================================================================================+====================+
| | ``UART:INIT``                     | ``rp_UartInit``              | Initialises the API for working with UART.                                             | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:INIT``                     |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:RELEASE``                  | ``rp_UartRelease``           | Releases all used resources.                                                           | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:RELEASE``                  |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SETUP``                    | ``rp_UartSetSettings``       | | Applies specified settings to UART.                                                  | 1.04-18 and up     |
| | Example:                          |                              | | Should be executed after communication parameters are set                            |                    |
| | ``UART:SETUP``                    |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:BITS <bits>``              | ``rp_UartSetBits``           | Sets the character size in bits.                                                       | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:BITS CS7``                 |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:BITS?`` > ``<bits>``       | ``rp_UartGetBits``           | Gets the character size in bits.                                                       | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:BITS?`` > ``CS7``          |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SPEED <speed>``            | ``rp_UartSetSpeed``          | Sets the speed of the UART connection.                                                 | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:SPEED 115200``             |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SPEED?`` > ``<speed>``     | ``rp_UartGetSpeed``          | Gets the speed of the UART connection.                                                 | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:SPEED?`` > ``115200``      |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:STOPB <stop>``             | ``rp_UartSetStopBits``       | Sets the length of the stop bit.                                                       | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:STOPB STOP2``              |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:STOPB?`` > ``<stop>``      | ``rp_UartGetStopBits``       | Gets the length of the stop bit.                                                       | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:STOPB?`` > ``STOP2``       |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:PARITY <parity>``          | ``rp_UartSetParityMode``     | | Sets parity check mode.                                                              | 1.04-18 and up     |
| | Example:                          |                              | | - NONE  = Disable parity check                                                       |                    |
| | ``UART:PARITY ODD``               |                              | | - EVEN  = Set even mode for parity                                                   |                    |
|                                     |                              | | - ODD   = Set odd mode for parity                                                    |                    |
|                                     |                              | | - MARK  = Set Always 1                                                               |                    |
|                                     |                              | | - SPACE = Set Always 0                                                               |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:PARITY?`` > ``<parity>``   | ``rp_UartGetParityMode``     | Gets parity check mode.                                                                | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:PARITY?`` > ``ODD``        |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:TIMEOUT <timeout>``        | ``rp_UartSetTimeout``        | | Sets the timeout for reading from UART. 0 - Disable timeout. 1 = 1/10 sec.           | 1.04-18 and up     |
| | Example:                          |                              | | Example: 10 - 1 sec. Max timeout: 25.5 sec                                           |                    |
| | ``UART:TIMEOUT 10``               |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:TIMEOUT?`` > ``<timeout>`` | ``rp_UartGetTimeout``        | Gets the timeout.                                                                      | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:TIMEOUT?`` > ``10``        |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:WRITE<n> <data>``          | ``rp_UartWrite``             | Writes data to UART. ``<n>`` - the length of data sent to UART.                        | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:WRITE5 1,2,3,4,5``         |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:READ?<n>`` > ``<data>``    | ``rp_UartRead``              | Reads data from UART. ``<n>`` - the length of data retrieved from UART.                | 1.04-18 and up     |
| | Example:                          |                              |                                                                                        |                    |
| | ``UART:READ5?`` > ``{1,2,3,4,5}`` |                              |                                                                                        |                    |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+--------------------+

.. _scpi_spi:

====
SPI
====

Parameter options:

* ``<mode> = {LISL, LIST, HISL, HIST}``  Default: ``LISL``
* ``<cs_mode> = {NORMAL, HIGH}``  Default: ``NORMAL``
* ``<bits> = {7,..}``  Default: ``8``
* ``<speed> = {1,100000000}`` Default: ``50000000``
* ``<data> = {XXX,... | #HXX,... | #QXXX,... | #BXXXXXXXX,... }`` Array of data separated commas

   - ``XXX`` = Dec format
   - ``#HXX`` = Hex format
   - ``#QXXX`` = Oct format
   - ``#BXXXXXXXX`` = Bin format

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| SCPI                                       | API                            | DESCRIPTION                                                                        |  ECOSYSTEM         |
+============================================+================================+====================================================================================+====================+
| | ``SPI:INIT``                             | ``rp_SPI_Init``                | Initializes the API for working with SPI.                                          | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:INIT``                             |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:INIT:DEV <path>``                  | ``rp_SPI_InitDev``             | | Initializes the API for working with SPI. ``<path>`` - Path to the SPI device.   | 1.04-18 and up     |
| | Example:                                 |                                | | On some boards, it may be different from the standard: /dev/spidev1.0            |                    |
| | ``SPI:INIT:DEV "/dev/spidev1.0"``        |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:RELEASE``                          | ``rp_SPI_Release``             | Releases all used resources.                                                       | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:RELEASE``                          |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:DEF``                     | ``rp_SPI_SetDefault``          | Sets the settings for SPI to default values.                                       | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:SET:DEF``                          |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:SET``                     | ``rp_SPI_SetSettings``         | | Sets the specified settings for SPI.                                             | 1.04-18 and up     |
| | Example:                                 |                                | | Executed after specifying the parameters of communication.                       |                    |
| | ``SPI:SET:SET``                          |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:GET``                     | ``rp_SPI_GetSettings``         | Gets the specified SPI settings.                                                   | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:SET:GET``                          |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:MODE <mode>``             | ``rp_SPI_SetMode``             | | Sets the mode for SPI.                                                           | 1.04-18 and up     |
| | Example:                                 |                                | | - LISL = Low idle level, Sample on leading edge                                  |                    |
| | ``SPI:SET:MODE LIST``                    |                                | | - LIST = Low idle level, Sample on trailing edge                                 |                    |
| |                                          |                                | | - HISL = High idle level, Sample on leading edge                                 |                    |
| |                                          |                                | | - HIST = High idle level, Sample on trailing edge                                |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:MODE?`` > ``<mode>``      | ``rp_SPI_GetMode``             | Gets the specified mode for SPI.                                                   | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:SET:MODE?`` > ``LIST``             |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:CSMODE <cs_mode>``        | ``rp_SPI_SetCSMode``           | | Sets the mode for CS.                                                            | 2.00-18 and up     |
| | Example:                                 |                                | | - NORMAL = After the message is transmitted,                                     |                    |
| | ``SPI:SET:CSMODE NORMAL``                |                                | | the CS line is set to the HIGH state.                                            |                    |
| |                                          |                                | | - HIGH = After the message has been transmitted,                                 |                    |
| |                                          |                                | | the CS line is set to the LOW state.                                             |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:CSMODE?`` > ``<cs_mode>`` | ``rp_SPI_GetCSMode``           | Gets the specified CS mode for SPI.                                                | 2.00-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:SET:CSMODE?`` > ``NORMAL``         |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:SPEED <speed>``           | ``rp_SPI_SetSpeed``            | Sets the speed of the SPI connection.                                              | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:SET:SPEED 1000000``                |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETings:SPEED?`` > ``<speed>``     | ``rp_SPI_GetSpeed``            | Gets the speed of the SPI connection.                                              | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:SET:SPEED?`` > ``1000000``         |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:WORD <bits>``             | ``rp_SPI_SetWord``             | Specifies the length of the word in bits. Must be greater than or equal to 7.      | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:SET:WORD 8``                       |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:WORD?`` > ``<bits>``      | ``rp_SPI_GetWord``             | Returns the length of a word.                                                      | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:SET:WORD?`` > ``8``                |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG:CREATE <n>``                   | ``rp_SPI_CreateMessage``       | | Creates a message queue for SPI (reserves the space for data buffers)            | 1.04-18 and up     |
| | Example:                                 |                                | | Once created, they need to be initialized.                                       |                    |
| | ``SPI:MSG:CREATE 1``                     |                                | | ``<n>`` - The number of messages in the queue.                                   |                    |
|                                            |                                | | The message queue can operate within a single CS state switch.                   |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG:DEL``                          | ``rp_SPI_DestoryMessage``      | Deletes all messages and data buffers allocated for them.                          | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:MSG:DEL``                          |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG:SIZE?`` > ``<n>``              | ``rp_SPI_GetMessageLen``       | Returns the length of the message queue.                                           | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:MSG:SIZE?`` > ``1``                |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:TX<m> <data>``              | | ``rp_SPI_SetTX``             | | Sets data for the write buffer for the specified message.                        | 1.04-18 and up     |
| | ``SPI:MSG<n>:TX<m>:CS <data>``           | | ``rp_SPI_SetTXCS``           | | CS - Toggles CS state after sending/receiving this message.                      |                    |
| | Example:                                 |                                | | ``<n>`` - index of message 0 <= n < msg queue size.                              |                    |
| | ``SPI:MSG0:TX4 1,2,3,4``                 |                                | | ``<m>`` - TX buffer length.                                                      |                    |
| | ``SPI:MSG1:TX3:CS 2,3,4``                |                                | | Sends ``<m>`` 'bytes' from message ``<n>``. No data is received.                 |                    |
| |                                          |                                | |                                                                                  |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:TX<m>:RX <data>``           | | ``rp_SPI_SetTXRX``           | | Sets data for the read and write buffers for the specified message.              | 1.04-18 and up     |
| | ``SPI:MSG<n>:TX<m>:RX:CS <data>``        | | ``rp_SPI_SetTXRXCS``         | | CS - Toggles CS state after sending/receiving this message.                      |                    |
| | Example:                                 |                                | | ``<n>`` - index of message 0 <= n < msg queue size.                              |                    |
| | ``SPI:MSG0:TX4:RX 1,2,3,4``              |                                | | ``<m>`` - TX buffer length.                                                      |                    |
| | ``SPI:MSG1:TX3:RX:CS 2,3,4``             |                                | | The read buffer is also created with the same length and initialized with zeros. |                    |
| |                                          |                                | |                                                                                  |                    |
| |                                          |                                | | Sends ``<m>`` 'bytes' from message ``<n>`` and receives the same amount of data  |                    |
| |                                          |                                | |  from the dataline                                                               |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:RX<m>``                     | | ``rp_SPI_SetRX``             | | Initializes a buffer for reading the specified message.                          | 1.04-18 and up     |
| | ``SPI:MSG<n>:RX<m>:CS``                  | | ``rp_SPI_SetRXCS``           | | CS - Toggles CS state after receiving message.                                   |                    |
| | Example:                                 |                                | | ``<n>`` - index of message 0 <= n < msg queue size.                              |                    |
| | ``SPI:MSG0:RX4``                         |                                | | ``<m>`` - RX buffer length.                                                      |                    |
| | ``SPI:MSG1:RX5:CS``                      |                                | |                                                                                  |                    |
| |                                          |                                | | Receives ``<m>`` 'bytes' into message ``<n>``. No data is transmitted.           |                    |
| |                                          |                                | |                                                                                  |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:RX?`` > ``<data>``          | ``rp_SPI_GetRXBuffer``         | Returns a read buffer for the specified message.                                   | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:MSG1:RX?`` > ``{2,4,5}``           |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:TX?`` > ``<data>``          | ``rp_SPI_GetTXBuffer``         | Returns the write buffer for the specified message.                                | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:MSG1:TX?`` > ``{2,4,5}``           |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:CS?`` > ``ON|OFF``          | ``rp_SPI_GetCSChangeState``    | Returns the setting for CS mode for the specified message.                         | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:MSG1:CS?`` > ``ON``                |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:PASS``                             | ``rp_SPI_Pass``                | Sends the prepared messages to the SPI device.                                     | 1.04-18 and up     |
| | Example:                                 |                                |                                                                                    |                    |
| | ``SPI:PASS``                             |                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+

.. _scpi_i2c:

===
I2C
===

Parameter options:

* ``<mode>  = {OFF, ON}``  Default: ``OFF``
* ``<value> = {XXX | #HXX | #QXXX | #BXXXXXXXX}``
* ``<data>  = {XXX,... | #HXX,... | #QXXX,... | #BXXXXXXXX,... }`` Array of data separated comma

   - ``XXX`` = Dec format
   - ``#HXX`` = Hex format
   - ``#QXXX`` = Oct format
   - ``#BXXXXXXXX`` = Bin format

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| SCPI                                             | API                            | DESCRIPTION                                                           |  ECOSYSTEM         |
+==================================================+================================+=======================================================================+====================+
| | ``I2C:DEV<addr> <path>``                       | ``rp_I2C_InitDevice``          | | Initializes settings for I2C. ``<path>`` - Path to the I2C device   | 1.04-18 and up     |
| | Example:                                       |                                | | ``<addr>`` - Device address on the I2C bus in dec format.           |                    |
| | ``I2C:DEV80 "/dev/i2c-0"``                     |                                |                                                                       |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:DEV?`` > ``<addr>``                      | ``rp_I2C_getDevAddress``       | Returns the current address of the device.                            | 1.04-18 and up     |
| | Example:                                       |                                |                                                                       |                    |
| | ``I2C:DEV?`` > ``80``                          |                                |                                                                       |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:FMODE <mode>``                           | ``rp_I2C_setForceMode``        | Enables forced bus operation even if the device is in use.            | 1.04-18 and up     |
| | Example:                                       |                                |                                                                       |                    |
| | ``I2C:FMODE ON``                               |                                |                                                                       |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:FMODE?`` > ``<mode>``                    | ``rp_I2C_getForceMode``        | Gets the current forced mode setting.                                 | 1.04-18 and up     |
| | Example:                                       |                                |                                                                       |                    |
| | ``I2C:FMODE?`` > ``ON``                        |                                |                                                                       |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>?`` > ``<value>``         | ``rp_I2C_SMBUS_Read``          | | Reads 8 bit data from the specified register using                  | 1.04-18 and up     |
| | Example:                                       |                                | | the SMBUS protocol.                                                 |                    |
| | ``I2C:S:R2?`` > ``0``                          |                                | | ``<reg>`` - Register address in dec format.                         |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>:Word?`` > ``<value>``    | ``rp_I2C_SMBUS_ReadWord``      | | Reads 16 bit data from the specified register using                 | 1.04-18 and up     |
| | Example:                                       |                                | | the SMBUS protocol.                                                 |                    |
| | ``I2C:S:R2:W?`` > ``0``                        |                                | | ``<reg>`` - Register address in dec format.                         |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>:Buffer<size>?`` >        | ``rp_I2C_SMBUS_ReadBuffer``    | | Reads buffer data from the specified register using                 | 1.04-18 and up     |
| |  ``<data>``                                    |                                | | the SMBUS protocol.                                                 |                    |
| | Example:                                       |                                | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:S:R2:B2?`` > ``{0,1}``                   |                                | | ``<size>`` - Read data size.                                        |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg> <value>``               | ``rp_I2C_SMBUS_Write``         | | Writes 8-bit data to the specified register using                   | 1.04-18 and up     |
| |                                                |                                | | the SMBUS protocol.                                                 |                    |
| | Example:                                       |                                | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:S:W2 10``                                |                                |                                                                       |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg>:Word <value>``          | ``rp_I2C_SMBUS_WriteWord``     | | Writes 16-bit data to the specified register using                  | 1.04-18 and up     |
| |                                                |                                | | the SMBUS protocol.                                                 |                    |
| | Example:                                       |                                | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:S:W2:W 10``                              |                                |                                                                       |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg>:Buffer<size> <data>``   | ``rp_I2C_SMBUS_WriteBuffer``   | | Writes buffer data to the specified register using                  | 1.04-18 and up     |
| |                                                |                                | | the SMBUS protocol.                                                 |                    |
| | Example:                                       |                                | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:S:W2:B2 0,1``                            |                                | | ``<size>`` - Read data size.                                        |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:IOctl:Read:Buffer?<size>`` > ``<data>``  | ``rp_I2C_IOCTL_ReadBuffer``    | | Reads data from the I2C device through IOCTL.                       | 1.04-18 and up     |
| | Example:                                       |                                | | ``<size>`` - Read data size.                                        |                    |
| | ``I2C:IO:R:B2?`` > ``{0,1}``                   |                                | |                                                                     |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:IOctl:Write:Buffer<size> <data>``        | ``rp_I2C_IOCTL_WriteBuffer``   | | Writes data to the I2C device via IOCTL.                            | 1.04-18 and up     |
| | Example:                                       |                                | | ``<size>`` - Read data size.                                        |                    |
| | ``I2C:IO:W:B2  {0,1}``                         |                                | |                                                                     |                    |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+--------------------+


.. note::

   SMBUS is a standardized protocol for communicating with I2C devices. Information about this protocol can be found in this link: |SMBUS specs|. IOCTL writes and reads data directly from I2C.

.. |SMBUS specs| raw:: html

    <a href="http://smbus.org/specs/" target="_blank">SMBUS specifcations</a>


.. _scpi_leds:

=============
Specific LEDs
=============

Parameter options:

* ``<mode> = {OFF, ON}``  Default: ``ON``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| SCPI                                | API                            | DESCRIPTION                                                                        |  ECOSYSTEM         |
+=====================================+================================+====================================================================================+====================+
| | ``LED:MMC <mode>``                | ``rp_SetLEDMMCState``          | Turns the Orange LED on or off (responsible for indicating the read memory card).  | 1.04-18 and up     |
| | Example:                          |                                |                                                                                    |                    |
| | ``LED:MMC OFF``                   |                                |                                                                                    |                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:MMC?`` > ``<mode>``         | ``rp_GetLEDMMCState``          | Gets the state of the MMC indicator.                                               | 1.04-18 and up     |
| | Example:                          |                                |                                                                                    |                    |
| | ``LED:MMC?`` > ``ON``             |                                |                                                                                    |                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:HB <mode>``                 | ``rp_SetLEDHeartBeatState``    | Turns the Red LED on or off (responsible for indicating board activity).           | 1.04-18 and up     |
| | Example:                          |                                |                                                                                    |                    |
| | ``LED:HB OFF``                    |                                |                                                                                    |                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:HB?`` > ``<mode>``          | ``rp_GetLEDHeartBeatState``    | Gets the state of the HeartBeat indicator (Red LED).                               | 1.04-18 and up     |
| | Example:                          |                                |                                                                                    |                    |
| | ``LED:HB?`` > ``ON``              |                                |                                                                                    |                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:ETH <mode>``                | ``rp_SetLEDEthState``          | Turns the LED indicators on the Ethernet connector on or off.                      | 1.04-18 and up     |
| | Example:                          |                                |                                                                                    |                    |
| | ``LED:ETH OFF``                   |                                |                                                                                    |                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:ETH?`` > ``<mode>``         | ``rp_GetLEDEthState``          | Gets the state of the Ethernet indicators.                                         | 1.04-18 and up     |
| | Example:                          |                                |                                                                                    |                    |
| | ``LED:ETH?`` > ``ON``             |                                |                                                                                    |                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+--------------------+


===
CAN
===

.. note::

   FPGA v0.94 is required to work with CAN.

Parameter options:

* ``<n> = {0, 1}`` CAN interface
* ``<bool> = {OFF, ON}``
* ``<state> = {ERROR_ACTIVE, ERROR_WARNING, ERROR_PASSIVE, BUS_OFF, STOPPED, SLEEPING}``
* ``<mode> = {LOOPBACK, BERR_REPORTING}``
* ``<speed> = {1,10000000}``
* ``<sp> = {0,0.999}``
* ``<tq> = {unsigned integer}``
* ``<prop_seg> = {unsigned integer}``
* ``<phase_seg1> = {unsigned integer}``
* ``<phase_seg2> = {unsigned integer}``
* ``<sjw> = {unsigned integer}``
* ``<brp> = {unsigned integer}``
* ``<tseg1_min> = {unsigned integer}``
* ``<tseg2_min> = {unsigned integer}``
* ``<tseg2_min> = {unsigned integer}``
* ``<tseg2_max> = {unsigned integer}``
* ``<sjw_max> = {unsigned integer}``
* ``<brp_min> = {unsigned integer}``
* ``<brp_max> = {unsigned integer}``
* ``<brp_inc> = {unsigned integer}``
* ``<limits> = {<tseg1_min>,<tseg2_min>,<tseg2_min>,<tseg2_max>,<sjw_max>,<brp_min>,<brp_max>,<brp_inc>}``
* ``<clock> = {1,...,10000000}`` in Hz
* ``<tx_err> = {unsigned integer}``
* ``<rx_err> = {unsigned integer}``
* ``<rs_ms> = {unsigned integer}`` in milliseconds
* ``<can_id> = {unsigned integer}`` Destination address on CAN bus
* ``<buffer> = {XXX | XXX,XXX | XXX,XXX,XXX | XXX,...,XXX}`` Bytes for send from 0 to 8
* ``<timeout> = {unsigned integer}`` in Ms. 0 - timeout disabled
* ``<frame_header> = {unsigned integer}``
* ``<is_extended> = {0,1}``
* ``<is_error> = {0,1}``
* ``<is_rtr> = {0,1}``
* ``<frame> = {<can_id>,<frame_header>,<is_extended>,<is_error>,<is_rtr>,{<buffer>}}``
* ``<filter> = {unsigned integer}``
* ``<mask> = {unsigned integer}``


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                                                                   | API                                        | DESCRIPTION                                                                                   |  ECOSYSTEM         |
+========================================================================================+============================================+===============================================================================================+====================+
| | ``CAN:FPGA <bool>``                                                                  | ``rp_CanSetFPGAEnable``                    | Enables FPGA forwarding from CAN controller to GPIO.                                          | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN:FPGA ON``                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN:FPGA?`` > ``<bool>``                                                           | ``rp_CanGetFPGAEnable``                    | Gets the status from the FPGA of the CAN mode status.                                         | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN:FPGA?`` > ``ON``                                                               |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:START``                                                                     | ``rp_CanStart``                            | Sets the state of the specified interface to UP.                                              | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:START``                                                                       |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:STOP``                                                                      | ``rp_CanStop``                             | Sets the state of the specified interface to DOWN.                                            | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:STOP``                                                                        |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:RESTART``                                                                   | ``rp_CanRestart``                          | Restarts the specified interface.                                                             | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:RESTART``                                                                     |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:STATE?`` > ``<state>``                                                      | ``rp_CanGetState``                         | | Returns the current state of the CAN interface.                                             | in dev             |
| | Example:                                                                             |                                            | | ERROR_ACTIVE - RX/TX error count < 96                                                       |                    |
| | ``CAN0:STATE?`` > ``ERROR_ACTIVE``                                                   |                                            | | ERROR_WARNING - RX/TX error count < 128                                                     |                    |
| |                                                                                      |                                            | | ERROR_PASSIVE - RX/TX error count < 256                                                     |                    |
| |                                                                                      |                                            | | BUS_OFF - RX/TX error count >= 256                                                          |                    |
| |                                                                                      |                                            | | STOPPED - Device is stopped                                                                 |                    |
| |                                                                                      |                                            | | SLEEPING - Device is sleeping                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITRate <speed>``                                                           | ``rp_CanSetBitrate``                       | Sets the bitrate for the specified interface. Sample point is set automatically.              | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:BITRate 200000``                                                              |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITRate:SP <speed>,<sp>``                                                   | ``rp_CanSetBitrateAndSamplePoint``         | Sets the bitrate and sample point for the specified interface.                                | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:BITRate:SP 200000,0.8``                                                       |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITRate:SP?`` > ``<speed>,<sp>``                                            | ``rp_CanGetBitrateAndSamplePoint``         | | Shows the real bit-rate in bits/sec and the sample-point in the                             | in dev             |
| | Example:                                                                             |                                            | | range 0.000..0.999. If the calculation of bit-timing parameters                             |                    |
| | ``CAN0:BITRate:SP?`` > ``200000,0.8``                                                |                                            | | is enabled in the kernel (CONFIG_CAN_CALC_BITTIMING=y), the                                 |                    |
| |                                                                                      |                                            | | bit-timing can be defined by setting the "bitrate" argument.                                |                    |
| |                                                                                      |                                            | | Optionally the "sample-point" can be specified. By default it's                             |                    |
| |                                                                                      |                                            | | 0.000 assuming CIA-recommended sample-points.                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITTiming <tq>,<prop_seg>,<phase_seg1>,<phase_seg2>,<sjw>,<brp>``           | ``rp_CanSetBitTiming``                     | Set bittiming settings.                                                                       | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:BITTiming 1000,1,2,1,1,10``                                                   |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITTiming?`` > ``<tq>,<prop_seg>,<phase_seg1>,<phase_seg2>,<sjw>,<brp>``    | ``rp_CanGetBitTiming``                     | | Shows the time quanta in ns, propagation segment, phase buffer                              | in dev             |
| | Example:                                                                             |                                            | | segment 1 and 2 and the synchronisation jump width in units of                              |                    |
| | ``CAN0:BITTiming?`` > ``1000,1,2,1,1,10``                                            |                                            | | tq. They allow to define the CAN bit-timing in a hardware                                   |                    |
| |                                                                                      |                                            | | independent format as proposed by the Bosch CAN 2.0 spec (Chapter 8).                       |                    |
| |                                                                                      |                                            | |                                                                                             |                    |
| |                                                                                      |                                            | |                                                                                             |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITTiming:Limits?`` > `` <limits>``                                         | ``rp_CanGetBitTimingLimits``               | | Shows the bit-timing constants of the CAN controller, here the                              | in dev             |
| | Example:                                                                             |                                            | | "sja1000". The minimum and maximum values of the time segment 1                             |                    |
| | ``CAN0:BITTiming:Limits?`` > ``1,16,1,8,4,1,256,1``                                  |                                            | | and 2, the synchronisation jump width in units of tq, the                                   |                    |
| |                                                                                      |                                            | | bitrate pre-scaler and the CAN system clock frequency in Hz.                                |                    |
| |                                                                                      |                                            | | These constants could be used for user-defined (non-standard)                               |                    |
| |                                                                                      |                                            | | bit-timing calculation algorithms in user-space.                                            |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:CLOCK?`` > ``<clock>``                                                      | ``rp_CanGetClockFreq``                     | Returns the clock value in Hz.                                                                | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:CLOCK?`` > ``10000000``                                                       |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BUS:ERROR?`` > ``<tx_err>,<rx_err>``                                        | ``rp_CanGetBusErrorCounters``              | Returns the number of errors on the bus.                                                      | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:BUS:ERROR?`` > ``0,0``                                                        |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Restart:Time <rs_ms>``                                                      | ``rp_CanSetRestartTime``                   | | Automatic restart delay time. If set to a non-zero value, a                                 | in dev             |
| | Example:                                                                             |                                            | | restart of the CAN controller will be triggered automatically                               |                    |
| | ``CAN0:Restart:Time 10``                                                             |                                            | | in case of a bus-off condition after the specified delay time                               |                    |
| |                                                                                      |                                            | | in milliseconds. By default it's off.                                                       |                    |
| |                                                                                      |                                            | |                                                                                             |                    |
| |                                                                                      |                                            | |                                                                                             |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Restart:Time?`` > ``<rs_ms>``                                               | ``rp_CanGetRestartTime``                   | Returns current settings for restart-ms.                                                      | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:Restart:Time?`` > ``10``                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:MODE <mode>,<bool>``                                                        | ``rp_CanSetControllerMode``                | Sets the controller mode.                                                                     | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:MODE LOOPBACK,ON``                                                            |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:MODE? <mode>`` > ``<bool>``                                                 | ``rp_CanGetControllerMode``                | Checks the status of the selected mode.                                                       | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:MODE? LOOPBACK`` > ``ON``                                                     |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:OPEN``                                                                      | ``rp_CanOpen``                             | Opens a socket connection for the specified interface.                                        | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:OPEN``                                                                        |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:CLOSE``                                                                     | ``rp_CanClose``                            | Closes an open connection.                                                                    | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:CLOSE``                                                                       |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id> <buffer>``                                                     | ``rp_CanSend``                             | Sends the frame to the specified address.                                                     | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:Send123 1,2,3``                                                               |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:RTR <buffer>``                                                 | ``rp_CanSend``                             | Sends the frame to the specified address marked as "Remote Transmission Request".             | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:Send123 1,2,3``                                                               |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Timeout<timeout> <buffer>``                                    | ``rp_CanSend``                             | | Sends the frame to the specified address.                                                   | in dev             |
| | Example:                                                                             |                                            | | There is a timeout for sending if the send buffer is full.                                  |                    |
| | ``CAN0:Send123:Timeout2000 1,2,3``                                                   |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Ext``                                                          | ``rp_CanSend``                             | | Sends the extended frame to the specified address.                                          | in dev             |
| | Example:                                                                             |                                            | | Sends an extended packet for can_id.                                                        |                    |
| | ``CAN0:Send123:Ext 1,2,3``                                                           |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Timeout<timeout>:Ext <buffer>``                                | ``rp_CanSend``                             | | Sends the extended frame to the specified address.                                          | in dev             |
| | Example:                                                                             |                                            | | There is a timeout for sending if the send buffer is full.                                  |                    |
| | ``CAN0:Send123:Timeout2000:Ext 1,2,3``                                               |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Timeout<timeout>:RTR <buffer>``                                | ``rp_CanSend``                             | | Sends the frame to the specified address marked as "Remote Transmission Request".           | in dev             |
| | Example:                                                                             |                                            | | There is a timeout for sending if the send buffer is full.                                  |                    |
| | ``CAN0:Send123:Timeout2000:RTR 1,2,3``                                               |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Ext:RTR``                                                      | ``rp_CanSend``                             | | Sends the extended frame to the specified address marked as "Remote Transmission Request".  | in dev             |
| | Example:                                                                             |                                            | | Sends an extended packet for can_id.                                                        |                    |
| | ``CAN0:Send123:Ext:RTR 1,2,3``                                                       |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Timeout<timeout>:Ext:RTR <buffer>``                            | ``rp_CanSend``                             | | Sends the extended frame to the specified address marked as "Remote Transmission Request".  | in dev             |
| | Example:                                                                             |                                            | | There is a timeout for sending if the send buffer is full.                                  |                    |
| | ``CAN0:Send123:Timeout2000:Ext:RTR 1,2,3``                                           |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Read?`` > ``<frame>``                                                       | ``rp_CanRead``                             | Reads from socket 1 frame.                                                                    | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:Read?`` > ``123,123,0,0,0,3,{1,2,3}``                                         |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Read:Timeout<timeout>?`` > ``<frame>``                                      | ``rp_CanRead``                             | Reads from socket 1 frame. Waits for the specified time, otherwise returns an empty string.   | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:Read:Timeout2000?`` > ``123,123,0,0,0,3,{1,2,3}``                             |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Filter:Add <filter>,<mask>``                                                | ``rp_CanAddFilter``                        | | Adds another filter to the list of filters.                                                 | in dev             |
| | Example:                                                                             |                                            | | Once all filters have been added, the command to                                            |                    |
| | ``CAN0:Filter:Add 0,0``                                                              |                                            | | apply filters on the socket must be invoked CAN<n>:Filter:Set.                              |                    |
| |                                                                                      |                                            | | A filter matches, when                                                                      |                    |
| |                                                                                      |                                            | | <received_can_id> & mask == filter & mask                                                   |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Filter:Remove <filter>,<mask>``                                             | ``rp_CanRemoveFilter``                     | Deletes the specified filter from the filter list.                                            | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:Filter:Remove 0,0``                                                           |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Filter:Clear``                                                              | ``rp_CanRemoveFilter``                     | Removes all filters from the list.                                                            | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:Filter:Clear``                                                                |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Filter:Set``                                                                | ``rp_CanSetFilter``                        | | Applies a list of filters to the socket connection.                                         | in dev             |
| | Example:                                                                             |                                            |                                                                                               |                    |
| | ``CAN0:Filter:Set``                                                                  |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:SHOW:ERROR``                                                                | ``rp_CanShowErrorFrames``                  | | When this mode is enabled, all errors will be                                               | in dev             |
| | Example:                                                                             |                                            | | converted through data frames with the error frame marking.                                 |                    |
| | ``CAN0:SHOW:ERROR``                                                                  |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
| |                                                                                      |                                            |                                                                                               |                    |
+----------------------------------------------------------------------------------------+--------------------------------------------+-----------------------------------------------------------------------------------------------+--------------------+



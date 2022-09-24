*******************************
List of supported SCPI commands
*******************************

.. (link - https://dl.dropboxusercontent.com/s/eiihbzicmucjtlz/SCPI_commands_beta_release.pdf)

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

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+---------------------------------------+-------------------------+-----------------------------------------------------------+
| SCPI                                  | API                     | DESCRIPTION                                               |
+=======================================+=========================+===========================================================+
| | ``DIG:PIN:DIR <dir>,<gpio>``        | ``rp_DpinSetDirection`` | Set the direction of digital pins to output or input.     |
| | Examples:                           |                         |                                                           |
| | ``DIG:PIN:DIR OUT,DIO0_N``          |                         |                                                           |
| | ``DIG:PIN:DIR IN,DIO1_P``           |                         |                                                           |
+---------------------------------------+-------------------------+-----------------------------------------------------------+
| | ``DIG:PIN <pin>,<state>``           | ``rp_DpinSetState``     | Set the state of digital outputs to 1 (HIGH) or 0 (LOW).  |
| | Examples:                           |                         |                                                           |
| | ``DIG:PIN DIO0_N,1``                |                         |                                                           |
| | ``DIG:PIN LED2,1``                  |                         |                                                           |
+---------------------------------------+-------------------------+-----------------------------------------------------------+
| | ``DIG:PIN? <pin>`` > ``<state>``    | ``rp_DpinGetState``     | Get state of digital inputs and outputs.                  |
| | Examples:                           |                         |                                                           |
| | ``DIG:PIN? DIO0_N``                 |                         |                                                           |
| | ``DIG:PIN? LED2``                   |                         |                                                           |
+---------------------------------------+-------------------------+-----------------------------------------------------------+

=========================
Analog Inputs and Outputs
=========================

Parameter options:

* ``<ain> = {AIN0, AIN1, AIN2, AIN3}``
* ``<aout> = {AOUT0, AOUT1, AOUT2, AOUT3}``
* ``<pin> = {ain, aout}``
* ``<value> = {value in Volts}``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+---------------------------------------+-------------------------+-----------------------------------------------------------+
| SCPI                                  | API                     | DESCRIPTION                                               |
+=======================================+=========================+===========================================================+
| | ``ANALOG:PIN <pin>,<value>``        | ``rp_ApinSetValue``     | | Set the analog voltage on the slow analog outputs.      |
| | Examples:                           |                         | | The voltage range of slow analog outputs is: 0 - 1.8 V  |
| | ``ANALOG:PIN AOUT2,1.34``           |                         |                                                           |
+---------------------------------------+-------------------------+-----------------------------------------------------------+
| | ``ANALOG:PIN? <pin>`` > ``<value>`` | ``rp_ApinGetValue``     | | Read the analog voltage from the slow analog inputs.    |
| | Examples:                           |                         | | The voltage range of slow analog inputs is: 0 - 3.3 V   |
| | ``ANALOG:PIN? AOUT2`` > ``1.34``    |                         |                                                           |
| | ``ANALOG:PIN? AIN1`` > ``1.12``     |                         |                                                           |
+---------------------------------------+-------------------------+-----------------------------------------------------------+


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
* ``<trigger> = {EXT_PE, EXT_NE, INT, GATED}``

   - ``EXT`` = External
   - ``INT`` = Internal
   - ``GATED`` = gated busts

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| SCPI                                 | API                        | DESCRIPTION                                                                |
+======================================+============================+============================================================================+
| | ``OUTPUT:STATE <state>``           | | ``rp_GenOutEnableSync``  | Runs or Stops both channels synchronously.                                 |
| | Examples:                          |                            |                                                                            |
| | ``OUTPUT:STATE ON``                |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``OUTPUT<n>:STATE <state>``        | | ``rp_GenOutEnable``      | Disable or enable fast analog outputs.                                     |
| | Examples:                          | | ``rp_GenOutDisable``     |                                                                            |
| | ``OUTPUT1:STATE ON``               |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:FREQ:FIX <frequency>``   | ``rp_GenFreq``             | Set the frequency of fast analog outputs.                                  |
| | Examples:                          |                            |                                                                            |
| | ``SOUR2:FREQ:FIX 100000``          |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:FUNC <func>``            | ``rp_GenWaveform``         | Set the waveform of fast analog outputs.                                   |
| | Examples:                          |                            |                                                                            |
| | ``SOUR2:FUNC TRIANGLE``            |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:VOLT <amplitude>``       | ``rp_GenAmp``              | | Set the amplitude voltage of fast analog outputs in Volts.               |
| | Examples:                          |                            | | Amplitude + offset value must be less than the maximum                   |
| | ``SOUR2:VOLT 0.5``                 |                            | | output range ± 1V.                                                       |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:VOLT:OFFS <offset>``     | ``rp_GenOffset``           | | Set the offset voltage of fast analog outputs in Volts                   |
| | Examples:                          |                            | | Amplitude + offset value must be less than the maximum                   |
| | ``SOUR1:VOLT:OFFS 0.2``            |                            | | output range ± 1V.                                                       |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:PHAS <phase>``           | ``rp_GenPhase``            | Set the phase of fast analog outputs.                                      |
| | Examples:                          |                            |                                                                            |
| | ``SOUR2:PHAS 30``                  |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:DCYC <par>``             | ``rp_GenDutyCycle``        | Set the duty cycle of the PWM waveform.                                    |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:DCYC 0.2``                 |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:TRAC:DATA:DATA <array>`` | ``rp_GenArbWaveform``      | Import data for arbitrary waveform generation.                             |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:TRAC:DATA:DATA``           |                            |                                                                            |
| | ``1,0.5,0.2``                      |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:BURS:STAT <burst>``      | ``rp_GenMode``             | | Enable or disable burst (pulse) mode.                                    |
| | Examples:                          |                            | | Red Pitaya will generate **R** bursts with **N** signal periods          |
| | ``SOUR1:BURS:STAT BURST``          |                            | | before stopping. **P** is the time between bursts.                       |
| | ``SOUR1:BURS:STAT CONTINUOUS``     |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:BURS:NCYC <count>``      | ``rp_GenBurstCount``       | Set the number of periods in a burst (**N**).                              |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:BURS:NCYC 3``              |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:BURS:NOR <count>``       | ``rp_GenBurstRepetitions`` | Set the number of repeated bursts (**R**).                                 |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:BURS:NOR 5``               |                            |                                                                            |
+--------------------------------------+----------------------------+---------------------------+------------------------------------------------+
| | ``SOUR<n>:BURS:INT:PER <time>``    | ``rp_GenBurstPeriod``      | | Set the duration of a single burst in microseconds (**P**).              |
| | Examples:                          |                            | | This includes the signal and delay.                                      |
| | ``SOUR1:BURS:INT:PER 1000000``     |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:TRIG:SOUR <trigger>``    | ``rp_GenTriggerSource``    | Set the trigger source for the selected signal.                            |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:TRIG:SOUR EXT_PE``         |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR:TRIG:INT``                  | ``rp_GenTrigger``          | | Triggers both sources/channels immediately.                              |
| |                                    |                            |                                                                            |
| | Examples:                          |                            |                                                                            |
| | ``SOUR:TRIG:INT``                  |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:TRIG:INT``               | ``rp_GenTrigger``          | | Triggers the selected source immediately for the selected channel.       |
| |                                    |                            |                                                                            |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:TRIG:INT``                 |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``GEN:RST``                        | ``rp_GenReset``            | Reset the generator to default settings.                                   |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``PHAS:ALIGN``                     | ``rp_GenSynchronise``      | Align the output phases of both channels.                                  |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+

.. note::

   For STEMlab 125-14 4-Input, these commands are not applicable.

=======
Acquire
=======

-------
Control
-------

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+----------------------------------+-----------------------------+------------------------------------------------------------------+
| SCPI                             | API                         | DESCRIPTION                                                      |
+==================================+=============================+==================================================================+
| ``ACQ:START``                    | ``rp_AcqStart``             | Start the acquisition.                                           |
+----------------------------------+-----------------------------+------------------------------------------------------------------+
| ``ACQ:STOP``                     | ``rp_AcqStop``              | Stop the acquisition.                                            |
+----------------------------------+-----------------------------+------------------------------------------------------------------+
| ``ACQ:RST``                      | ``rp_AcqReset``             | Stops the acquisition and sets all parameters to default values. |
+----------------------------------+-----------------------------+------------------------------------------------------------------+

--------------------------
Sampling rate & decimation
--------------------------

Parameter options:

* ``<decimation> = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536}`` Default: ``1``
* ``<average> = {OFF,ON}`` Default: ``ON``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+-----------------------------+----------------------------------------------------------------------+
| SCPI                                | API                         | DESCRIPTION                                                          |
+=====================================+=============================+======================================================================+
| | ``ACQ:DEC <decimation>``          | ``rp_AcqSetDecimation``     | Set the decimation factor.                                           |
| | Example:                          |                             |                                                                      |
| | ``ACQ:DEC 4``                     |                             |                                                                      |
+-------------------------------------+-----------------------------+----------------------------------------------------------------------+
| | ``ACQ:DEC?`` > ``<decimation>``   | ``rp_AcqGetDecimation``     | Get the decimation factor.                                           |
| | Example:                          |                             |                                                                      |
| | ``ACQ:DEC?`` > ``1``              |                             |                                                                      |
+-------------------------------------+-----------------------------+----------------------------------------------------------------------+
| | ``ACQ:AVG <average>``             | ``rp_AcqSetAveraging``      | | Enable/disable averaging.                                          |
|                                     |                             | | Each sample is the average of skipped samples if decimation > 1.   |     
+-------------------------------------+-----------------------------+----------------------------------------------------------------------+
| | ``ACQ:AVG?`` > ``<average>``      | ``rp_AcqGetAveraging``      | Get the averaging status.                                            |
| | Example:                          |                             |                                                                      |
| | ``ACQ:AVG?`` > ``ON``             |                             |                                                                      |
+-------------------------------------+-----------------------------+----------------------------------------------------------------------+


=======
Trigger
=======

Parameter options:

* ``<n> = {1,2}`` (set channel IN1 or IN2)
* ``<source> = {DISABLED, NOW, CH1_PE, CH1_NE, CH2_PE, CH2_NE, EXT_PE, EXT_NE, AWG_PE, AWG_NE}``  Default: ``DISABLED``
* ``<status> = {WAIT, TD}``
* ``<time> = {value in ns}``
* ``<count> = {value in samples}``
* ``<gain> = {LV, HV}``
* ``<level> = {value in V}``
* ``<mode> = {AC,DC}``

.. note::

   For STEMlab 125-14 4-Input ``<n> = {1,2,3,4}`` (set channel IN1, IN2, IN3 or IN4)
   
.. note::

   For STEMlab 125-14 4-Input ``<source> = {DISABLED, NOW, CH1_PE, CH1_NE, CH2_PE, CH2_NE, CH3_PE, CH3_NE, CH4_PE, CH4_NE, EXT_PE, EXT_NE, AWG_PE, AWG_NE}``  Default: ``DISABLED``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| SCPI                                | API                           | DESCRIPTION                                                                   |
+=====================================+===============================+===============================================================================+
| | ``ACQ:TRIG <source>``             | ``rp_AcqSetTriggerSrc``       | Disable triggering, trigger immediately or set trigger source & edge.         |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG CH1_PE``               |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:STAT?``                | ``rp_AcqGetTriggerState``     | Get trigger status. If DISABLED -> TD else WAIT.                              |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:STAT?`` > ``WAIT``     |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:FILL?``                | ``rp_AcqGetBufferFillState``  | | Returns 1 if the buffer is full of data. Otherwise returns 0.               |
| | Example:                          |                               | | (IN FUTURE BETA VERSION)                                                    |
| | ``ACQ:TRIG:FILL?`` > ``1``        |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:DLY <count>``          | ``rp_AcqSetTriggerDelay``     | Set the trigger delay in samples.                                             |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:DLY 2314``             |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:DLY?`` > ``<count>``   | ``rp_AcqGetTriggerDelay``     | Get the trigger delay in samples.                                             |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:DLY?`` > ``2314``      |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:DLY:NS <time>``        | ``rp_AcqSetTriggerDelayNs``   | Set the trigger delay in ns.                                                  |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:DLY:NS 128``           |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:DLY:NS?`` > ``<time>`` | ``rp_AcqGetTriggerDelayNs``   | Get the trigger delay in ns.                                                  |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:DLY:NS?`` > ``128ns``  |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:GAIN <gain>``       | ``rp_AcqSetGain``             | | Set the gain settings to HIGH or LOW.                                       |
| |                                   |                               | | (For SIGNALlab 250-12 this is 1:20 and 1:1 attenuator).                     |
| | Example:                          |                               | | This gain refers to jumper settings on Red Pitaya fast analog inputs.       |
| | ``ACQ:SOUR1:GAIN LV``             |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:GAIN?`` > ``<gain>``| ``rp_AcqGetGain``             | | Get the gain setting.                                                       |
| |                                   |                               | | (For SIGNALlab 250-12 this is 1:20 and 1:1 attenuator).                     |
| | Example:                          |                               |                                                                               |
| | ``ACQ:SOUR1:GAIN?`` > ``HV``      |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:COUP <mode>``       | ``rp_AcqSetAC_DC``            | Sets the AC / DC modes of input.                                              |
| | Example:                          |                               | (Only SIGNALlab 250-12)                                                       |
| | ``ACQ:SOUR1:COUP AC``             |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:COUP?`` > ``<mode>``| ``rp_AcqGetAC_DC``            | Get the AC / DC modes of input.                                               |
| | Example:                          |                               | (Only SIGNALlab 250-12)                                                       |
| | ``ACQ:SOUR1:COUP?`` > ``AC``      |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:LEV <level>``          | ``rp_AcqSetTriggerLevel``     | Set the trigger level in V.                                                   |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:LEV 0.125 V``          |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:LEV?`` > ``level``     | ``rp_AcqGetTriggerLevel``     | Get the trigger level in V.                                                   |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:LEV?`` > ``0.123 V``   |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:EXT:LEV <level>``      | ``rp_AcqSetTriggerLevel``     | Set the external trigger level in V.                                          |
| | Example:                          |                               | (Only SIGNALlab 250-12)                                                       |
| | ``ACQ:TRIG:EXT:LEV 1``            |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:EXT:LEV?`` > ``level`` | ``rp_AcqGetTriggerLevel``     | Get the external trigger level in V.                                          |
| | Example:                          |                               | (Only SIGNALlab 250-12)                                                       |
| | ``ACQ:TRIG:EXT:LEV?`` > ``1``     |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+


=============
Data pointers
=============

Parameter options:

* ``<pos> = {position inside circular buffer}``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+---------------------------------+------------------------------------+--------------------------------------------------------+
| SCPI                            | API                                | DESCRIPTION                                            |
+=================================+====================================+========================================================+
| | ``ACQ:WPOS?`` > ``pos``       | ``rp_AcqGetWritePointer``          | Returns the current position of the write pointer.     |
| | Example:                      |                                    |                                                        |
| | ``ACQ:WPOS?`` > ``1024``      |                                    |                                                        |
+---------------------------------+------------------------------------+--------------------------------------------------------+
| | ``ACQ:TPOS?`` > ``pos``       | ``rp_AcqGetWritePointerAtTrig``    | Returns the position where the trigger event appeared. |
| | Example:                      |                                    |                                                        |
| | ``ACQ:TPOS?`` > ``512``       |                                    |                                                        |
+---------------------------------+------------------------------------+--------------------------------------------------------+


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

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| SCPI                                   | API                          | DESCRIPTION                                                                            |
+========================================+==============================+========================================================================================+
| | ``ACQ:DATA:UNITS <units>``           | ``rp_AcqScpiDataUnits``      | Select units in which the acquired data will be returned.                              |
| | Example:                             |                              |                                                                                        |
| | ``ACQ:DATA:UNITS RAW``               |                              |                                                                                        |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``ACQ:DATA:UNITS?`` > ``<units>``    | ``rp_AcqGetScpiDataUnits``   | Get units in which the acquired data will be returned.                                 |
| | Example:                             |                              |                                                                                        |
| | ``ACQ:DATA:UNITS?`` > ``RAW``        |                              |                                                                                        |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``ACQ:DATA:FORMAT <format>``         | ``rp_AcqScpiDataFormat``     | Select the format in which the acquired data will be returned.                         |
| | Example:                             |                              |                                                                                        |
| | ``ACQ:DATA:FORMAT ASCII``            |                              |                                                                                        |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA:STA:END?``        | | ``rp_AcqGetDataPosRaw``    | | Read samples from start to stop position.                                            |
| | ``<start_pos>,<end_pos>``            | | ``rp_AcqGetDataPosV``      | | ``<start_pos> = {0,1,...,16384}``                                                    |
| | Example:                             |                              | | ``<stop_pos>  = {0,1,...,16384}``                                                    |
| | ``ACQ:SOUR1:DATA:STA:END? 10,13`` >  |                              |                                                                                        |
| | ``{123,231,-231}``                   |                              |                                                                                        |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA:STA:N?``          | | ``rp_AcqGetDataRaw``       | | Read ``m`` samples from the start position onwards.                                  |
| | ``<start_pos>,<m>``                  | | ``rp_AcqGetDataV``         |                                                                                        |
| | Example:                             |                              |                                                                                        |
| | ``ACQ:SOUR1:DATA:STA:N? 10,3`` >     |                              |                                                                                        |
| | ``{1.2,3.2,-1.2}``                   |                              |                                                                                        |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA?``                | | ``rp_AcqGetOldestDataRaw`` | | Read the full buffer.                                                                |
| | Example:                             | | ``rp_AcqGetOldestDataV``   | | Starting from the oldest sample in the buffer (first sample after trigger delay).    |
| | ``ACQ:SOUR2:DATA?`` >                |                              | | The trigger delay is set to zero by default (in samples or in seconds).              |
| | ``{1.2,3.2,...,-1.2}``               |                              | | If the trigger delay is set to zero, it will read the full buffer size starting      |
| |                                      |                              | | from the trigger.                                                                    |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA:OLD:N? <m>``      | | ``rp_AcqGetOldestDataRaw`` | | Read ``m`` samples after the trigger delay, starting from the oldest sample          |
| | Example:                             | | ``rp_AcqGetOldestDataV``   | | in the buffer (first sample after trigger delay).                                    |
| | ``ACQ:SOUR2:DATA:OLD:N? 3`` >        |                              | | The trigger delay is set to zero by default (in samples or in seconds).              |
| | ``{1.2,3.2,-1.2}``                   |                              | | If the trigger delay is set to zero, it will read m samples starting                 |
| |                                      |                              | | from the trigger.                                                                    |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA:LAT:N? <m>``      | | ``rp_AcqGetLatestDataRaw`` | | Read ``m`` samples before the trigger delay.                                         |
| | Example:                             | | ``rp_AcqGetLatestDataV``   | | The trigger delay is set to zero by default (in samples or in seconds).              |
| | ``ACQ:SOUR1:DATA:LAT:N? 3`` >        |                              | | If the trigger delay is set to zero, it will read m samples before the trigger.      |
| | ``{1.2,3.2,-1.2}``                   |                              |                                                                                        |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``ACQ:BUF:SIZE?`` > ``<size>``       | ``rp_AcqGetBufSize``         |  Returns the buffer size.                                                              |
| | Example:                             |                              |                                                                                        |
| | ``ACQ:BUF:SIZE?`` > ``16384``        |                              |                                                                                        |
+----------------------------------------+------------------------------+----------------------------------------------------------------------------------------+


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

+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| SCPI                                | API                          | DESCRIPTION                                                                            |
+=====================================+==============================+========================================================================================+
| | ``UART:INIT``                     | ``rp_UartInit``              | Initialises the API for working with UART.                                             |
| | Example:                          |                              |                                                                                        |
| | ``UART:INIT``                     |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:RELEASE``                  | ``rp_UartRelease``           | Releases all used resources.                                                           |
| | Example:                          |                              |                                                                                        |
| | ``UART:RELEASE``                  |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:SETUP``                    | ``rp_UartSetSettings``       | Applies specified settings to UART.                                                    |
| | Example:                          |                              |                                                                                        |
| | ``UART:SETUP``                    |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:BITS <bits>``              | ``rp_UartSetBits``           | Sets the character size in bits.                                                       |
| | Example:                          |                              |                                                                                        |
| | ``UART:BITS CS7``                 |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:BITS?`` > ``<bits>``       | ``rp_UartGetBits``           | Gets the character size in bits.                                                       |
| | Example:                          |                              |                                                                                        |
| | ``UART:BITS?`` > ``CS7``          |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:SPEED <speed>``            | ``rp_UartSetSpeed``          | Sets the speed of the UART connection.                                                 |
| | Example:                          |                              |                                                                                        |
| | ``UART:SPEED 115200``             |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:SPEED?`` > ``<speed>``     | ``rp_UartGetSpeed``          | Gets the speed of the UART connection.                                                 |
| | Example:                          |                              |                                                                                        |
| | ``UART:SPEED?`` > ``115200``      |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:STOPB <stop>``             | ``rp_UartSetStopBits``       | Sets the length of the stop bit.                                                       |
| | Example:                          |                              |                                                                                        |
| | ``UART:STOPB STOP2``              |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:STOPB?`` > ``<stop>``      | ``rp_UartGetStopBits``       | Gets the length of the stop bit.                                                       |
| | Example:                          |                              |                                                                                        |
| | ``UART:STOPB?`` > ``STOP2``       |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:PARITY <parity>``          | ``rp_UartSetParityMode``     | | Sets parity check mode.                                                              |
| | Example:                          |                              | | - NONE  = Disable parity check                                                       |
| | ``UART:PARITY ODD``               |                              | | - EVEN  = Set even mode for parity                                                   |
|                                     |                              | | - ODD   = Set odd mode for parity                                                    |
|                                     |                              | | - MARK  = Set Always 1                                                               |
|                                     |                              | | - SPACE = Set Always 0                                                               |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:PARITY?`` > ``<parity>``   | ``rp_UartGetParityMode``     | Gets parity check mode.                                                                |
| | Example:                          |                              |                                                                                        |
| | ``UART:PARITY?`` > ``ODD``        |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:TIMEOUT <timeout>``        | ``rp_UartSetTimeout``        | | Sets the timeout for reading from UART. 0 - Disable timeout. 1 = 1/10 sec.           |
| | Example:                          |                              | | Example: 10 - 1 sec. Max timout: 25.5 sec                                            |
| | ``UART:TIMEOUT 10``               |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:TIMEOUT?`` > ``<timeout>`` | ``rp_UartGetTimeout``        | Gets the timeout.                                                                      |
| | Example:                          |                              |                                                                                        |
| | ``UART:TIMEOUT?`` > ``10``        |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:WRITE<n> <data>``          | ``rp_UartWrite``             | Writes data to UART. <n> - the length of data sent to UART.                            |
| | Example:                          |                              |                                                                                        |
| | ``UART:WRITE5 1,2,3,4,5``         |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+
| | ``UART:READ<n>`` > ``<data>``     | ``rp_UartRead``              | Reads data from UART. <n> - the length of data retrieved from UART.                    |
| | Example:                          |                              |                                                                                        |
| | ``UART:READ5`` > ``{1,2,3,4,5}``  |                              |                                                                                        |
+-------------------------------------+------------------------------+----------------------------------------------------------------------------------------+


====
SPI
====

Parameter options:

* ``<mode> = {LISL, LIST, HISL, HIST}``  Default: ``LISL``
* ``<order> = {MSB, LSB}``  Default: ``MSB``
* ``<bits> = {7,..}``  Default: ``8``
* ``<speed> = {1,100000000}`` Default: ``50000000``
* ``<data> = {XXX,... | #HXX,... | #QXXX,... | #BXXXXXXXX,... }`` Array of data separated comma

   - ``XXX`` = Dec format
   - ``#HXX`` = Hex format
   - ``#QXXX`` = Oct format
   - ``#BXXXXXXXX`` = Bin format

+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| SCPI                                  | API                            | DESCRIPTION                                                                        |
+=======================================+================================+====================================================================================+
| | ``SPI:INIT``                        | ``rp_SPI_Init``                | Initializes the API for working with SPI.                                          |
| | Example:                            |                                |                                                                                    |
| | ``SPI:INIT``                        |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:INIT:DEV <path>``             | ``rp_SPI_InitDev``             | | Initializes the API for working with SPI. <path> - Path to the SPI device.       |
| | Example:                            |                                | | On some boards, it may be different from the standard: /dev/spidev1.0            |
| | ``SPI:INIT:DEV "/dev/spidev1.0"``   |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:RELEASE``                     | ``rp_SPI_Release``             | Releases all used resources.                                                       |
| | Example:                            |                                |                                                                                    |
| | ``SPI:RELEASE``                     |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETtings:DEF``                | ``rp_SPI_SetDefault``          | Sets the settings for SPI to default values.                                       |
| | Example:                            |                                |                                                                                    |
| | ``SPI:SET:DEF``                     |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETtings:SET``                | ``rp_SPI_SetSettings``         | Sets the specified settings for SPI.                                               |
| | Example:                            |                                |                                                                                    |
| | ``SPI:SET:SET``                     |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETtings:GET``                | ``rp_SPI_GetSettings``         | Gets the specified SPI settings.                                                   |
| | Example:                            |                                |                                                                                    |
| | ``SPI:SET:GET``                     |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETtings:MODE <mode>``        | ``rp_SPI_SetMode``             | | Sets the mode for SPI.                                                           |
| | Example:                            |                                | | - LISL = Low idle level, Sample on leading edge                                  |
| | ``SPI:SET:MODE LIST``               |                                | | - LIST = Low idle level, Sample on trailing edge                                 |
| |                                     |                                | | - HISL = High idle level, Sample on leading edge                                 |
| |                                     |                                | | - HIST = High idle level, Sample on trailing edge                                |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETtings:MODE?`` > ``<mode>`` | ``rp_SPI_GetMode``             | Gets the specified mode for SPI.                                                   |
| | Example:                            |                                |                                                                                    |
| | ``SPI:SET:MODE?`` > ``LIST``        |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETtings:SPEED <speed>``      | ``rp_SPI_SetSpeed``            | Sets the speed of the SPI connection.                                              |
| | Example:                            |                                |                                                                                    |
| | ``SPI:SET:SPEED 1000000``           |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETings:SPEED?`` > ``<speed>``| ``rp_SPI_GetSpeed``            | Gets the speed of the SPI connection.                                              |
| | Example:                            |                                |                                                                                    |
| | ``SPI:SET:SPEED?`` > ``1000000``    |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETtings:WORD <bits>``        | ``rp_SPI_SetWord``             | Specifies the length of the word in bits. Must be greater than or equal to 7.      |
| | Example:                            |                                |                                                                                    |
| | ``SPI:SET:WORD 8``                  |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:SETtings:WORD?`` > ``<bits>`` | ``rp_SPI_GetWord``             | Returns the length of a word.                                                      |
| | Example:                            |                                |                                                                                    |
| | ``SPI:SET:WORD?`` > ``8``           |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG:CREATE <n>``              | ``rp_SPI_CreateMessage``       | | Creates a message queue for SPI. Once created, they need to be initialized.      |
| | Example:                            |                                | | <n> - The number of messages in the queue.                                       |
| | ``SPI:MSG:CREATE 1``                |                                | | The message queue can operate within a single CS state switch.                   |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG:DEL``                     | ``rp_SPI_DestoryMessage``      | Deletes all messages and data buffers allocated for them.                          |
| | Example:                            |                                |                                                                                    |
| | ``SPI:MSG:DEL``                     |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG:SIZE?`` > ``<n>``         | ``rp_SPI_GetMessageLen``       | Returns the length of the message queue.                                           |
| | Example:                            |                                |                                                                                    |
| | ``SPI:MSG:SIZE?`` > ``1``           |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:TX<m> <data>``         | | ``rp_SPI_SetTX``             | | Sets data for the write buffer for the specified message.                        |
| | ``SPI:MSG<n>:TX<m>:CS <data>``      | | ``rp_SPI_SetTXCS``           | | CS - Toggles CS state after sending/receiving this message.                      |
| | Example:                            |                                | | <n> - index of message 0 <= n < msg queue size.                                  |
| | ``SPI:MSG0:TX4 1,2,3,4``            |                                | | <m> - TX buffer length.                                                          |
| | ``SPI:MSG1:TX3:CS 2,3,4``           |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:TX<m>:RX <data>``      | | ``rp_SPI_SetTXRX``           | | Sets data for the read and write buffers for the specified message.              |
| | ``SPI:MSG<n>:TX<m>:RX:CS <data>``   | | ``rp_SPI_SetTXRXCS``         | | CS - Toggles CS state after sending/receiving this message.                      |
| | Example:                            |                                | | <n> - index of message 0 <= n < msg queue size.                                  |
| | ``SPI:MSG0:TX4:RX 1,2,3,4``         |                                | | <m> - TX buffer length.                                                          |
| | ``SPI:MSG1:TX3:RX:CS 2,3,4``        |                                | | The read buffer is also created with the same length and initialized with zeros. |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:RX<m>``                | | ``rp_SPI_SetRX``             | | Initializes a buffer for reading the specified message.                          |
| | ``SPI:MSG<n>:RX<m>:CS``             | | ``rp_SPI_SetRXCS``           | | CS - Toggles CS state after receiving message.                                   |
| | Example:                            |                                | | <n> - index of message 0 <= n < msg queue size.                                  |
| | ``SPI:MSG0:RX4``                    |                                | | <m> - RX buffer length.                                                          |
| | ``SPI:MSG1:RX5:CS``                 |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:RX?`` > ``<data>``     | ``rp_SPI_GetRXBuffer``         | Returns a read buffer for the specified message.                                   |
| | Example:                            |                                |                                                                                    |
| | ``SPI:MSG1:RX?`` > ``{2,4,5}``      |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:TX?`` > ``<data>``     | ``rp_SPI_GetTXBuffer``         | Returns the write buffer for the specified message.                                |
| | Example:                            |                                |                                                                                    |
| | ``SPI:MSG1:TX?`` > ``{2,4,5}``      |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:CS?`` > ``ON|OFF``     | ``rp_SPI_GetCSChangeState``    | Returns the setting for CS mode for the specified message.                         |
| | Example:                            |                                |                                                                                    |
| | ``SPI:MSG1:CS?`` > ``ON``           |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``SPI:PASS``                        | ``rp_SPI_Pass``                | Sends the prepared messages to the SPI device.                                     |
| | Example:                            |                                |                                                                                    |
| | ``SPI:PASS``                        |                                |                                                                                    |
+---------------------------------------+--------------------------------+------------------------------------------------------------------------------------+


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

+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| SCPI                                             | API                            | DESCRIPTION                                                           |
+==================================================+================================+=======================================================================+
| | ``I2C:DEV<addr> <path>``                       | ``rp_I2C_InitDevice``          | | Initialises settings for I2C. <path> - Path to the I2C device       |
| | Example:                                       |                                | | <addr> - Device address on the I2C bus in dec format.               |
| | ``I2C:DEV80 "/dev/i2c-0"``                     |                                |                                                                       |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:DEV?`` > ``<addr>``                      | ``rp_I2C_getDevAddress``       | Returns the current address of the device.                            |
| | Example:                                       |                                |                                                                       |
| | ``I2C:DEV?`` > ``80``                          |                                |                                                                       |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:FMODE <mode>``                           | ``rp_I2C_setForceMode``        | Enables forced bus operation even if the device is in use.            |
| | Example:                                       |                                |                                                                       |
| | ``I2C:FMODE ON``                               |                                |                                                                       |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:FMODE?`` > ``<mode>``                    | ``rp_I2C_getForceMode``        | Gets the current forced mode setting.                                 |
| | Example:                                       |                                |                                                                       |
| | ``I2C:FMODE?`` > ``ON``                        |                                |                                                                       |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:Smbus:Read<reg>`` > ``<value>``          | ``rp_I2C_SMBUS_Read``          | | Reads 8 bit data from the specified register using                  |
| | Example:                                       |                                | | the SMBUS protocol.                                                 |
| | ``I2C:S:R2`` > ``0``                           |                                | | <reg> - Register address in dec format.                             |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:Smbus:Read<reg>:Word`` > ``<value>``     | ``rp_I2C_SMBUS_ReadWord``      | | Reads 16 bit data from the specified register using                 |
| | Example:                                       |                                | | the SMBUS protocol.                                                 |
| | ``I2C:S:R2:W`` > ``0``                         |                                | | <reg> - Register address in dec format.                             |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:Smbus:Read<reg>:Buffer<size>`` >         | ``rp_I2C_SMBUS_ReadBuffer``    | | Reads buffer data from the specified register using                 |
| |  ``<data>``                                    |                                | | the SMBUS protocol.                                                 |
| | Example:                                       |                                | | <reg> - Register address in dec format.                             |
| | ``I2C:S:R2:B2`` > ``{0,1}``                    |                                | | <size> - Read data size.                                            |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:Smbus:Write<reg> <value>``               | ``rp_I2C_SMBUS_Write``         | | Writes 8-bit data to the specified register using                   |
| |                                                |                                | | the SMBUS protocol.                                                 |
| | Example:                                       |                                | | <reg> - Register address in dec format.                             |
| | ``I2C:S:W2 10``                                |                                |                                                                       |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:Smbus:Write<reg>:Word <value>``          | ``rp_I2C_SMBUS_WriteWord``     | | Writes 16-bit data to the specified register using                  |
| |                                                |                                | | the SMBUS protocol.                                                 |
| | Example:                                       |                                | | <reg> - Register address in dec format.                             |
| | ``I2C:S:W2:W 10``                              |                                |                                                                       |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:Smbus:Write<reg>:Buffer<size> <data>``   | ``rp_I2C_SMBUS_WriteBuffer``   | | Writes buffer data to the specified register using                  |
| |                                                |                                | | the SMBUS protocol.                                                 |
| | Example:                                       |                                | | <reg> - Register address in dec format.                             |
| | ``I2C:S:W2:B2 0,1``                            |                                | | <size> - Read data size.                                            |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:IOctl:Read:Buffer<size>`` > ``<data>``   | ``rp_I2C_IOCTL_ReadBuffer``    | | Reads data from the I2C device through IOCTL.                       |
| | Example:                                       |                                | | <size> - Read data size.                                            |
| | ``I2C:IO:R:B2`` > ``{0,1}``                    |                                | |                                                                     |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+
| | ``I2C:IOctl:Write:Buffer<size> <data>``        | ``rp_I2C_IOCTL_WriteBuffer``   | | Writes data to the I2C device via IOCTL.                            |
| | Example:                                       |                                | | <size> - Read data size.                                            |
| | ``I2C:IO:W:B2  {0,1}``                         |                                | |                                                                     |
+--------------------------------------------------+--------------------------------+-----------------------------------------------------------------------+




.. note::

   SMBUS is a standardised protocol for communicating with I2C devices. Information about this protocol can be found in this link: |SMBUS specs|. IOCTL writes and reads data directly from I2C.

.. |SMBUS specs| raw:: html

    <a href="http://smbus.org/specs/" target="_blank">SMBUS specifcations</a>


=============
Specific LEDs
=============

Parameter options:

* ``<mode> = {OFF, ON}``  Default: ``ON``

+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| SCPI                                | API                            | DESCRIPTION                                                                        |
+=====================================+================================+====================================================================================+
| | ``LED:MMC <mode>``                | ``rp_SetLEDMMCState``          | Turns the yellow LED on or off (responsible for indicating the read memory card).  |
| | Example:                          |                                |                                                                                    |
| | ``LED:MMC OFF``                   |                                |                                                                                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``LED:MMC?`` > ``<mode>``         | ``rp_GetLEDMMCState``          | Gets the state of the MMC indicator.                                               |
| | Example:                          |                                |                                                                                    |
| | ``LED:MMC?`` > ``ON``             |                                |                                                                                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``LED:HB <mode>``                 | ``rp_SetLEDHeartBeatState``    | Turns the red LED on or off (responsible for indicating board activity).           |
| | Example:                          |                                |                                                                                    |
| | ``LED:HB OFF``                    |                                |                                                                                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``LED:HB?`` > ``<mode>``          | ``rp_GetLEDHeartBeatState``    | Gets the state of the HeartBeat indicator.                                         |
| | Example:                          |                                |                                                                                    |
| | ``LED:HB?`` > ``ON``              |                                |                                                                                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``LED:ETH <mode>``                | ``rp_SetLEDEthState``          | Turns the LED indicators on the network card on or off.                            |
| | Example:                          |                                |                                                                                    |
| | ``LED:ETH OFF``                   |                                |                                                                                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+
| | ``LED:ETH?`` > ``<mode>``         | ``rp_GetLEDEthState``          | Gets the state of the Ethernet indicators.                                         |
| | Example:                          |                                |                                                                                    |
| | ``LED:ETH?`` > ``ON``             |                                |                                                                                    |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------+

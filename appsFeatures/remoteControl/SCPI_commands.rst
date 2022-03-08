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

Table of correlated SCPI and API commands on Red Pitaya.

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+------------------------------------+-------------------------+------------------------------------------------------+
| SCPI                               | API                     | description                                          |
+====================================+=========================+======================================================+
| | ``DIG:PIN:DIR <dir>,<gpio>``     | ``rp_DpinSetDirection`` | Set direction of digital pins to output or input.    |
| | Examples:                        |                         |                                                      |                       
| | ``DIG:PIN:DIR OUT,DIO0_N``       |                         |                                                      |  
| | ``DIG:PIN:DIR IN,DIO1_P``        |                         |                                                      |                  
+------------------------------------+-------------------------+------------------------------------------------------+
| | ``DIG:PIN <pin>,<state>``        | ``rp_DpinSetState``     | Set state of digital outputs to 1 (HIGH) or 0 (LOW). |
| | Examples:                        |                         |                                                      |
| | ``DIG:PIN DIO0_N,1``             |                         |                                                      |
| | ``DIG:PIN LED2,1``               |                         |                                                      |
+------------------------------------+-------------------------+------------------------------------------------------+
| | ``DIG:PIN? <pin>`` > ``<state>`` | ``rp_DpinGetState``     | Get state of digital inputs and outputs.             |
| | Examples:                        |                         |                                                      |
| | ``DIG:PIN? DIO0_N``              |                         |                                                      |
| | ``DIG:PIN? LED2``                |                         |                                                      |
+------------------------------------+-------------------------+------------------------------------------------------+

=========================
Analog Inputs and Outputs
=========================

Parameter options:

* ``<ain> = {AIN0, AIN1, AIN2, AIN3}``
* ``<aout> = {AOUT0, AOUT1, AOUT2, AOUT3}``
* ``<pin> = {ain, aout}``
* ``<value> = {value in Volts}``
   
.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+---------------------------------------+---------------------+------------------------------------------------------+
| SCPI                                  | API                 | description                                          |
+=======================================+=====================+======================================================+
| | ``ANALOG:PIN <pin>,<value>``        | ``rp_ApinSetValue`` | | Set analog voltage on slow analog outputs.         |
| | Examples:                           |                     | | Voltage range of slow analog outputs is: 0 - 1.8 V |
| | ``ANALOG:PIN AOUT2,1.34``           |                     |                                                      |
+---------------------------------------+---------------------+------------------------------------------------------+
| | ``ANALOG:PIN? <pin>`` > ``<value>`` | ``rp_ApinGetValue`` | | Read analog voltage from slow analog inputs.       |
| | Examples:                           |                     | | Voltage range of slow analog inputs is: 0 3.3 V    |
| | ``ANALOG:PIN? AOUT2`` > ``1.34``    |                     |                                                      |
| | ``ANALOG:PIN? AIN1`` > ``1.12``     |                     |                                                      |
+---------------------------------------+---------------------+------------------------------------------------------+

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
* ``<array> = {value1, ...}`` max. 16k values, floats in the range -1 to 1
* ``<burst> = {BURST , CONTINUOUS}`` Default: ``CONTINUOUS``
* ``<count> = {1...50000}`` , Default: ``1``
* ``<time> = {1µs-500s}`` Value in *µs*.
* ``<trigger> = {EXT_PE, EXT_NE, INT, GATED}``

   - ``EXT`` = External
   - ``INT`` = Internal
   - ``GATED`` = gated busts

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| SCPI                                 | API                        | description                                                                |
+======================================+============================+============================================================================+
| | ``OUTPUT:STATE <state>``           | | ``rp_GenOutEnableSync``  | Runs or Stop two channels synchronously                                    |
| | Examples:                          |                            |                                                                            |
| | ``OUTPUT:STATE ON``                |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``OUTPUT<n>:STATE <state>``        | | ``rp_GenOutEnable``      | | Disable or enable fast analog outputs.                                   |
| | Examples:                          | | ``rp_GenOutDisable``     |                                                                            |
| | ``OUTPUT1:STATE ON``               |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:FREQ:FIX <frequency>``   | ``rp_GenFreq``             | Set frequency of fast analog outputs.                                      |
| | Examples:                          |                            |                                                                            |
| | ``SOUR2:FREQ:FIX 100000``          |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:FUNC <func>``            | ``rp_GenWaveform``         | Set waveform of fast analog outputs.                                       |
| | Examples:                          |                            |                                                                            |
| | ``SOUR2:FUNC TRIANGLE``            |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:VOLT <amplitude>``       | ``rp_GenAmp``              | | Set amplitude voltage of fast analog outputs.                            |
| | Examples:                          |                            | | Amplitude + offset value must be less than maximum output range ± 1V     |
| | ``SOUR2:VOLT 0.5``                 |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:VOLT:OFFS <offset>``     | ``rp_GenOffset``           | | Set offset voltage of fast analog outputs.                               |
| | Examples:                          |                            | | Amplitude + offset value must be less than maximum output range ± 1V     |
| | ``SOUR1:VOLT:OFFS 0.2``            |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:PHAS <phase>``           | ``rp_GenPhase``            | Set phase of fast analog outputs.                                          |
| | Examples:                          |                            |                                                                            |
| | ``SOUR2:PHAS 30``                  |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:DCYC <par>``             | ``rp_GenDutyCycle``        | Set duty cycle of PWM waveform.                                            |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:DCYC 0.2``                 |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:TRAC:DATA:DATA <array>`` | ``rp_GenArbWaveform``      | Import data for arbitrary waveform generation.                             |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:TRAC:DATA:DATA``           |                            |                                                                            |
| | ``1,0.5,0.2``                      |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:BURS:STAT <burst>``      | ``rp_GenMode``             | Enable or disable burst (pulse) mode.                                      |
| | Examples:                          |                            | Red Pitaya will generate **R** number of **N** periods of signal           |
| | ``SOUR1:BURS:STAT BURST``          |                            | and then stop. Time between bursts is **P**.                               |
| | ``SOUR1:BURS:STAT CONTINUOUS``     |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:BURS:NCYC <count>``      | ``rp_GenBurstCount``       | Set N number of periods in one burst.                                      |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:BURS:NCYC 3``              |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR1:BURS:NOR <count>``         | ``rp_GenBurstRepetitions`` | Set R number of repeated bursts.                                           |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:BURS:NOR 5``               |                            |                                                                            |
+--------------------------------------+----------------------------+---------------------------+------------------------------------------------+
| | ``SOUR1:BURS:INT:PER <time>``      | ``rp_GenBurstPeriod``      | Set P total time of one burst in in micro seconds.                         |
| | Examples:                          |                            | This includes the signal and delay.                                        |
| | ``SOUR1:BURS:INT:PER 1000000``     |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:TRIG:SOUR <trigger>``    | ``rp_GenTriggerSource``    | Set trigger source for selected signal.                                    |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:TRIG:SOUR EXT_PE``         |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR:TRIG:INT``                  | ``rp_GenTrigger``          | | Triggers selected source immediately for two channels                    |
| |                                    |                            |                                                                            |
| | Examples:                          |                            |                                                                            |
| | ``SOUR:TRIG:INT``                  |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``SOUR<n>:TRIG:INT``               | ``rp_GenTrigger``          | | Triggers selected source immediately for selected channel                |
| |                                    |                            |                                                                            |
| | Examples:                          |                            |                                                                            |
| | ``SOUR1:TRIG:INT``                 |                            |                                                                            |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``GEN:RST``                        | ``rp_GenReset``            | Reset generator to default settings.                                       |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+
| | ``PHAS:ALIGN``                     | ``rp_GenSynchronise``      | Aligning output phase of dual channels.                                    |
+--------------------------------------+----------------------------+----------------------------------------------------------------------------+

=======
Acquire
=======

Parameter options:

* ``<n> = {1,2}`` (set channel IN1 or IN2)

-------
Control
-------

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+---------------+-----------------+--------------------------------------------------------------+
| SCPI          | API             | description                                                  |
+===============+=================+==============================================================+
| ``ACQ:START`` | ``rp_AcqStart`` | Starts acquisition.                                          |
+---------------+-----------------+--------------------------------------------------------------+
| ``ACQ:STOP``  | ``rp_AcqStop``  | Stops acquisition.                                           |
+---------------+-----------------+--------------------------------------------------------------+
| ``ACQ:RST``   | ``rp_AcqReset`` | Stops acquisition and sets all parameters to default values. |
+---------------+-----------------+--------------------------------------------------------------+

--------------------------
Sampling rate & decimation
--------------------------

Parameter options:

* ``<decimation> = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536}`` Default: ``1``
* ``<average> = {OFF,ON}`` Default: ``ON``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+-----------------------------+-----------------------------------+
| SCPI                                | API                         | description                       |
+=====================================+=============================+===================================+
| ``ACQ:DEC <decimation>``            | ``rp_AcqSetDecimation``     | Set decimation factor.            |
+-------------------------------------+-----------------------------+-----------------------------------+
| | ``ACQ:DEC?`` > ``<decimation>``   | ``rp_AcqGetDecimation``     | Get decimation factor.            |
| | Example:                          |                             |                                   |
| | ``ACQ:DEC?`` > ``1``              |                             |                                   |
+-------------------------------------+-----------------------------+-----------------------------------+
| | ``ACQ:AVG <average>``             | ``rp_AcqSetAveraging``      | Enable/disable averaging.         |
+-------------------------------------+-----------------------------+-----------------------------------+
| | ``ACQ:AVG?`` > ``<average>``      | ``rp_AcqGetAveraging``      | Get averaging status.             |
| | Example:                          |                             |                                   |
| | ``ACQ:AVG?`` > ``ON``             |                             |                                   |
+-------------------------------------+-----------------------------+-----------------------------------+

=======
Trigger
=======

Parameter options:

* ``<source> = {DISABLED, NOW, CH1_PE, CH1_NE, CH2_PE, CH2_NE, EXT_PE, EXT_NE, AWG_PE, AWG_NE}``  Default: ``DISABLED``
* ``<status> = {WAIT, TD}``
* ``<time> = {value in ns}``
* ``<counetr> = {value in samples}``
* ``<gain> = {LV, HV}``
* ``<level> = {value in V}``
* ``<mode> = {AC,DC}``

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
| | ``ACQ:TRIG:DLY <time>``           | ``rp_AcqSetTriggerDelay``     | Set trigger delay in samples.                                                 |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:DLY 2314``             |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:DLY?`` > ``<time>``    | ``rp_AcqGetTriggerDelay``     | Get trigger delay in samples.                                                 |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:DLY?`` > ``2314``      |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:DLY:NS <time>``        | ``rp_AcqSetTriggerDelayNs``   | Set trigger delay in ns.                                                      |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:DLY:NS 128``           |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:DLY:NS?`` > ``<time>`` | ``rp_AcqGetTriggerDelayNs``   | Get trigger delay in ns.                                                      |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:DLY:NS?`` > ``128ns``  |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:GAIN <gain>``       | ``rp_AcqSetGain``             | | Set gain settings to HIGH or LOW                                            |
| |                                   |                               | | (For SIGNALlab 250-12 this is 1:20 and 1:1 attenuator).                     |
| | Example:                          |                               | | This gain is referring to jumper settings on Red Pitaya fast analog inputs. |
| | ``ACQ:SOUR1:GAIN LV``             |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:COUP <mode>``       | ``rp_AcqSetAC_DC``            | Sets the AC / DC modes for input.                                             |
| | Example:                          |                               | (Only SIGNALlab 250-12)                                                       |
| | ``ACQ:SOUR1:COUP AC``             |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:COUP?`` > ``<mode>``| ``rp_AcqGetAC_DC``            | Get the AC / DC modes for input.                                              |
| | Example:                          |                               | (Only SIGNALlab 250-12)                                                       |
| | ``ACQ:SOUR1:COUP?`` > ``AC``      |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:LEV <level>``          | ``rp_AcqSetTriggerLevel``     | Set trigger level in mV.                                                      |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:LEV 125 mV``           |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:LEV?`` > ``level``     | ``rp_AcqGetTriggerLevel``     | Get trigger level in mV.                                                      |
| | Example:                          |                               |                                                                               |
| | ``ACQ:TRIG:LEV?`` > ``123 mV``    |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:EXT:LEV <level>``      | ``rp_AcqSetTriggerLevel``     | Set trigger external level in V.                                              |
| | Example:                          |                               | (Only SIGNALlab 250-12)                                                       |
| | ``ACQ:TRIG:EXT:LEV 1``            |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+
| | ``ACQ:TRIG:EXT:LEV?`` > ``level`` | ``rp_AcqGetTriggerLevel``     | Get trigger external level in V.                                              |
| | Example:                          |                               | (Only SIGNALlab 250-12)                                                       |
| | ``ACQ:TRIG:EXT:LEV?`` > ``1``     |                               |                                                                               |
+-------------------------------------+-------------------------------+-------------------------------------------------------------------------------+

=============
Data pointers
=============

Parameter options:

* ``<pos> = {position inside circular buffer}``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+------------------------------+---------------------------------+------------------------------------------------+
| SCPI                         | API                             | DESCRIPTION                                    |
+------------------------------+---------------------------------+------------------------------------------------+
| | ``ACQ:WPOS?`` > ``pos``    | ``rp_AcqGetWritePointer``       | Returns current position of write pointer.     |
| | Example:                   |                                 |                                                |
| | ``ACQ:WPOS?`` > ``1024``   |                                 |                                                |
+------------------------------+---------------------------------+------------------------------------------------+
| | ``ACQ:TPOS?`` > ``pos``    | ``rp_AcqGetWritePointerAtTrig`` | Returns position where trigger event appeared. |
| | Example:                   |                                 |                                                |
| | ``ACQ:TPOS?`` > ``512``    |                                 |                                                |
+------------------------------+---------------------------------+------------------------------------------------+

=========
Data read
=========


* ``<units> = {RAW, VOLTS}``
* ``<format> = {BIN, ASCII}`` Default ``ASCII``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|

+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| SCPI                              | API                          | DESCRIPTION                                                                              |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``ACQ:DATA:UNITS <units>``      | ``rp_AcqScpiDataUnits``      | Selects units in which acquired data will be returned.                                   |
| | Example:                        |                              |                                                                                          |
| | ``ACQ:GET:DATA:UNITS RAW``      |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``ACQ:DATA:FORMAT <format>``    | ``rp_AcqScpiDataFormat``     | Selects format acquired data will be returned.                                           |
| | Example:                        |                              |                                                                                          |
| | ``ACQ:GET:DATA:FORMAT ASCII``   |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA:STA:END?`` > | | ``rp_AcqGetDataPosRaw``    | | Read samples from start to stop position.                                              |
| | ``<start_pos>,<end_pos>``       | | ``rp_AcqGetDataPosV``      | | ``<start_pos> = {0,1,...,16384}``                                                      |
| | Example:                        |                              | | ``<stop_pos> = {0,1,...116384}``                                                       |
| | ``ACQ:SOUR1:GET:DATA 10,13`` >  |                              |                                                                                          |
| | ``{123,231,-231}``              |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA:STA:N?``     | | ``rp_AcqGetDataRaw``       |  Read ``m`` samples from start position on.                                              |
| | ``<start_pos>,<m>`` > ``...``   | | ``rp_AcqGetDataV``         |                                                                                          |
| | Example:                        |                              |                                                                                          |
| | ``ACQ:SOUR1:DATA? 10,3`` >      |                              |                                                                                          |
| | ``{1.2,3.2,-1.2}``              |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA?``           | | ``rp_AcqGetOldestDataRaw`` | | Read full buf.                                                                         |
| | Example:                        | | ``rp_AcqGetOldestDataV``   | | Size starting from oldest sample in buffer (this is first sample after trigger delay). |
| | ``ACQ:SOUR2:DATA?`` >           |                              | | Trigger delay by default is set to zero (in samples or in seconds).                    |
| | ``{1.2,3.2,...,-1.2}``          |                              | | If trigger delay is set to zero it will read full buf. size starting from trigger.     |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA:OLD:N?<m>``  | | ``rp_AcqGetOldestDataRaw`` | | Read m samples after trigger delay, starting from oldest sample in buffer              |
| | Example:                        | | ``rp_AcqGetOldestDataV``   | | (this is first sample after trigger delay).                                            |
| | ``ACQ:SOUR2:DATA:OLD? 3`` >     |                              | | Trigger delay by default is set to zero (in samples or in seconds).                    |
| | ``{1.2,3.2,-1.2}``              |                              | | If trigger delay is set to zero it will read m samples starting from trigger.          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``ACQ:SOUR<n>:DATA:LAT:N?<m>``  | | ``rp_AcqGetLatestDataRaw`` | | Read ``m`` samples before trigger delay.                                               |
| | Example:                        | | ``rp_AcqGetLatestDataV``   | | Trigger delay by default is set to zero (in samples or in seconds).                    |
| | ``ACQ:SOUR1:DATA:LAT? 3`` >     |                              | | If trigger delay is set to zero it will read m samples before trigger.                 |
| | ``{1.2,3.2,-1.2}``              |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``ACQ:BUF:SIZE?`` > ``<size>``  | ``rp_AcqGetBufSize``         |  Returns buffer size.                                                                    |
| | Example:                        |                              |                                                                                          |
| | ``ACQ:BUF:SIZE?`` > ``16384``   |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+ 


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

+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| SCPI                              | API                          | DESCRIPTION                                                                              |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:INIT``                   | ``rp_UartInit``              | Initializes api for working with uart.                                                   |
| | Example:                        |                              |                                                                                          |
| | ``UART:INIT``                   |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:RELEASE``                | ``rp_UartRelease``           | Releases all used resources.                                                             |
| | Example:                        |                              |                                                                                          |
| | ``UART:RELEASE``                |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:SETUP``                  | ``rp_UartSetSettings``       | Applies specified settings to uart.                                                      |
| | Example:                        |                              |                                                                                          |
| | ``UART:SETUP``                  |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:BITS <bits>``            | ``rp_UartSetBits``           | Sets the character size in bits.                                                         |
| | Example:                        |                              |                                                                                          |
| | ``UART:BITS CS7``               |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:BITS? > <bits>``         | ``rp_UartGetBits``           | Gets the character size in bits.                                                         |
| | Example:                        |                              |                                                                                          |
| | ``UART:BITS? > CS7``            |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:SPEED <speed>``          | ``rp_UartSetSpeed``          | Sets the speed for the uart connection.                                                  |
| | Example:                        |                              |                                                                                          |
| | ``UART:SPEED 115200``           |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:SPEED? > <speed>``       | ``rp_UartGetSpeed``          | Gets the speed for the uart connection.                                                  |
| | Example:                        |                              |                                                                                          |
| | ``UART:SPEED? > 115200``        |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:STOPB <stop>``           | ``rp_UartSetStopBits``       | Sets the length of the stop bit.                                                         |
| | Example:                        |                              |                                                                                          |
| | ``UART:STOPB STOP2``            |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:STOPB? > <stop>``        | ``rp_UartGetStopBits``       | Gets the length of the stop bit.                                                         |
| | Example:                        |                              |                                                                                          |
| | ``UART:STOPB? > STOP2``         |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:PARITY <parity>``        | ``rp_UartSetParityMode``     | | Sets parity check mode.                                                                |
| | Example:                        |                              | | - NONE = Disable parity check                                                          |
| | ``UART:PARITY ODD``             |                              | | - EVEN = Set even mode for parity                                                      |
|                                   |                              | | - ODD = Set odd mode for parity                                                        |
|                                   |                              | | - MARK = Set Always 1                                                                  |
|                                   |                              | | - SPACE = Set Always 0                                                                 |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:PARITY? > <parity>``     | ``rp_UartGetParityMode``     | Gets parity check mode.                                                                  |
| | Example:                        |                              |                                                                                          |
| | ``UART:PARITY? > ODD``          |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:TIMEOUT <timeout>``      | ``rp_UartSetTimeout``        | | Sets timeout for read from uart. 0 - Disable timeout. 1 = 1/10 sec.                    |
| | Example:                        |                              | | Example: 10 - 1 sec. Max timout: 25.5 sec                                              |
| | ``UART:TIMEOUT 10``             |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:TIMEOUT? > <timeout>``   | ``rp_UartGetTimeout``        | Gets the timeout.                                                                        |
| | Example:                        |                              |                                                                                          |
| | ``UART:TIMEOUT? > 10``          |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:WRITE<n> <data>``        | ``rp_UartWrite``             | Writes data to uart. <n> - Length of passed data to uart.                                |
| | Example:                        |                              |                                                                                          |
| | ``UART:WRITE5 1,2,3,4,5``       |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:READ<n>? > <data>``      | ``rp_UartRead``              | Reads data from uart. <n> - Length of retrieved data from uart.                          |
| | Example:                        |                              |                                                                                          |
| | ``UART:READ5? > {1,2,3,4,5}``   |                              |                                                                                          |
+-----------------------------------+------------------------------+------------------------------------------------------------------------------------------+

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

+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| SCPI                                | API                            | DESCRIPTION                                                                              |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:INIT``                      | ``rp_SPI_Init``                | Initializes api for working with spi.                                                    |
| | Example:                          |                                |                                                                                          |
| | ``SPI:INIT``                      |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:INIT:DEV <path>``           | ``rp_SPI_InitDevice``          | | Initializes api for working with spi. <path> - Path to spi device                      |
| | Example:                          |                                | | On some boards, it may be different from the standard: /dev/spidev1.0                  |
| | ``SPI:INIT:DEV "/dev/spidev1.0"`` |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:RELEASE``                   | ``rp_SPI_Release``             | Releases all used resources.                                                             |
| | Example:                          |                                |                                                                                          |
| | ``SPI:RELEASE``                   |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:SETtings:DEF``              | ``rp_SPI_SetDefaultSettings``  | Sets the settings for SPI to default values.                                             |
| | Example:                          |                                |                                                                                          |
| | ``SPI:SET:DEF``                   |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:SETtings:SET``              | ``rp_SPI_GetSettings``         | Sets the specified settings for SPI.                                                     |
| | Example:                          |                                |                                                                                          |
| | ``SPI:SET:SET``                   |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:SETtings:GET``              | ``rp_SPI_SetSettings``         | Gets the specified SPI settings.                                                         |
| | Example:                          |                                |                                                                                          |
| | ``SPI:SET:GET``                   |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:SETtings:MODE <mode>``      | ``rp_SPI_SetMode``             | | Sets the mode for SPI.                                                                 |
| | Example:                          |                                | | - LISL = Low idle level, Sample on leading edge                                        |
| | ``SPI:SET:MODE LIST``             |                                | | - LIST = Low idle level, Sample on trailing edge                                       |
| |                                   |                                | | - HISL = High idle level, Sample on leading edge                                       |
| |                                   |                                | | - HIST = High idle level, Sample on trailing edge                                      |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:SETtings:MODE? > <mode>``   | ``rp_SPI_GetMode``             | Returns the specified mode for SPI.                                                      |
| | Example:                          |                                |                                                                                          |
| | ``SPI:SET:MODE? > LIST``          |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:SETtings:SPEED <speed>``    | ``rp_SPI_SetSpeed``            | Sets the speed for the spi connection.                                                   |
| | Example:                          |                                |                                                                                          |
| | ``SPI:SET:SPEED 1000000``         |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``UART:SPEED? > <speed>``         | ``rp_SPI_GetSpeed``            | Gets the speed the spi connection.                                                       |
| | Example:                          |                                |                                                                                          |
| | ``UART:SPEED? > 1000000``         |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:SETtings:WORD <bits>``      | ``rp_SPI_SetWordLen``          | Specifies the length of the word in bits. Must be greater than or equal to 7.            |
| | Example:                          |                                |                                                                                          |
| | ``SPI:SET:WORD 8``                |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:SETtings:WORD? > <bits>``   | ``rp_SPI_GetWordLen``          | Returns the length of a word.                                                            |
| | Example:                          |                                |                                                                                          |
| | ``SPI:SET:WORD? > 8``             |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG:CREATE <n>``            | ``rp_SPI_CreateMessage``       | | Creates a message queue for SPI. Once created, they need to be initialized.            |
| | Example:                          |                                | | <n> - Number of messages in the queue                                                  |
| | ``SPI:MSG:CREATE 1``              |                                | | The message queue can operate within a single CS state switch.                         |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG:DEL``                   | ``rp_SPI_DestoryMessage``      | Deletes all messages and data buffers allocated for them.                                |
| | Example:                          |                                |                                                                                          |
| | ``SPI:MSG:DEL``                   |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG:SIZE? > <n>``           | ``rp_SPI_GetMessageLen``       | Returns the length of the message queue.                                                 |
| | Example:                          |                                |                                                                                          |
| | ``SPI:MSG:SIZE? > 1``             |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:TX<m> <data>``       | ``rp_SPI_SetBufferForMessage`` | | Sets data for write buffer for the specified message.                                  |
| | ``SPI:MSG<n>:TX<m>:CS <data>``    |                                | | CS - Toggles CS state after sending/receiving this message.                            |
| | Example:                          |                                | | <n> - index of message 0 <= n < msg queue size.                                        |
| | ``SPI:MSG0:TX4 1,2,3,4``          |                                | | <m> - TX buffer length.                                                                |
| | ``SPI:MSG1:TX3:CS 2,3,4``         |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:TX<m>:RX <data>``    | ``rp_SPI_SetBufferForMessage`` | | Sets data for read and write buffers for the specified message.                        |
| | ``SPI:MSG<n>:TX<m>:RX:CS <data>`` |                                | | CS - Toggles CS state after sending/receiving this message.                            |
| | Example:                          |                                | | <n> - index of message 0 <= n < msg queue size.                                        |
| | ``SPI:MSG0:TX4:RX 1,2,3,4``       |                                | | <m> - TX buffer length.                                                                |
| | ``SPI:MSG1:TX3:RX:CS 2,3,4``      |                                | | The read buffer is also created with the same length and initialized with zeros.       |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:RX<m>``              | ``rp_SPI_SetBufferForMessage`` | | Initializes a buffer for reading the specified message.                                |
| | ``SPI:MSG<n>:RX<m>:CS``           |                                | | CS - Toggles CS state after receiving message.                                         |
| | Example:                          |                                | | <n> - index of message 0 <= n < msg queue size.                                        |
| | ``SPI:MSG0:RX4``                  |                                | | <m> - RX buffer length.                                                                |
| | ``SPI:MSG1:RX5:CS``               |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:RX? > <data>``       | ``rp_SPI_GetRxBuffer``         | Returns a read buffer for the specified message.                                         |
| | Example:                          |                                |                                                                                          |
| | ``SPI:MSG1:RX? > {2,4,5}``        |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:RX? > <data>``       | ``rp_SPI_GetTxBuffer``         | Returns the write buffer for the specified message.                                      |
| | Example:                          |                                |                                                                                          |
| | ``SPI:MSG1:RX? > {2,4,5}``        |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:MSG<n>:CS? > ON|OFF``       | ``rp_SPI_GetCSChangeState``    | Returns the setting for CS mode for the specified message.                               |
| | Example:                          |                                |                                                                                          |
| | ``SPI:MSG1:CS? > ON``             |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``SPI:PASS``                      | ``rp_SPI_ReadWrite``           | Sends prepared messages to the SPI device.                                               |
| | Example:                          |                                |                                                                                          |
| | ``SPI:PASS``                      |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+


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

+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| SCPI                                             | API                            | DESCRIPTION                                                                              |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:DEV<addr> <path>``                       | ``rp_I2C_InitDevice``          | | Initializes settings for i2c. <path> - Path to i2c device                              |
| | Example:                                       |                                | | <addr> - Device address on the i2c bus in dec format.                                  |
| | ``I2C:DEV80 "/dev/i2c-0"``                     |                                |                                                                                          |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:DEV? > <addr>``                          | ``rp_I2C_getDevAddress``       | Returns the current address of the device.                                               |
| | Example:                                       |                                |                                                                                          |
| | ``I2C:DEV? > 80``                              |                                |                                                                                          |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:FMODE <mode>``                           | ``rp_I2C_setForceMode``        | Enables forced bus operation even if the device is in use.                               |
| | Example:                                       |                                |                                                                                          |
| | ``I2C:FMODE ON``                               |                                |                                                                                          |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:FMODE? > <mode>``                        | ``rp_I2C_getForceMode``        | Gets the current forced mode setting.                                                    |
| | Example:                                       |                                |                                                                                          |
| | ``I2C:FMODE? > ON``                            |                                |                                                                                          |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:Smbus:Read<reg> > <value>``              | ``rp_I2C_SMBUS_Read``          | | Reads 8 bit data from the specified register using the SMBUS protocol.                 |
| | Example:                                       |                                | | <reg> - Register address in dec format.                                                |
| | ``I2C:S:R2 > 0``                               |                                |                                                                                          |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:Smbus:Read<reg>:Word > <value>``         | ``rp_I2C_SMBUS_ReadWord``      | | Reads 16 bit data from the specified register using the SMBUS protocol.                |
| | Example:                                       |                                | | <reg> - Register address in dec format.                                                |
| | ``I2C:S:R2:W > 0``                             |                                |                                                                                          |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:Smbus:Read<reg>:Buffer<size> > <data>``  | ``rp_I2C_SMBUS_ReadBuffer``    | | Reads buffer data from the specified register using the SMBUS protocol.                |
| | Example:                                       |                                | | <reg> - Register address in dec format.                                                |
| | ``I2C:S:R2:B2 > {0,1}``                        |                                | | <size> - Read data size.                                                               |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:Smbus:Write<reg> <value>``               | ``rp_I2C_SMBUS_Write``         | | Writes 8-bit data to the specified register using the SMBUS protocol.                  |
| | Example:                                       |                                | | <reg> - Register address in dec format.                                                |
| | ``I2C:S:W2 10``                                |                                |                                                                                          |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:Smbus:Write<reg>:Word <value>``          | ``rp_I2C_SMBUS_WriteWord``     | | Writes 16-bit data to the specified register using the SMBUS protocol.                 |
| | Example:                                       |                                | | <reg> - Register address in dec format.                                                |
| | ``I2C:S:W2:W 10``                              |                                |                                                                                          |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:Smbus:Write<reg>:Buffer<size> <data>``   | ``rp_I2C_SMBUS_WriteBuffer``   | | Writes buffer data to the specified register using the SMBUS protocol.                 |
| | Example:                                       |                                | | <reg> - Register address in dec format.                                                |
| | ``I2C:S:W2:B2 0,1``                            |                                | | <size> - Read data size.                                                               |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:IOctl:Read:Buffer<size> > <data>``       | ``rp_I2C_IOCTL_ReadBuffer``    | | Reads data from i2c device through IOCTL.                                              |
| | Example:                                       |                                | | <size> - Read data size.                                                               |
| | ``I2C:IO:R:B2 > {0,1}``                        |                                | |                                                                                        |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``I2C:IOctl:Write:Buffer<size> <data>``        | ``rp_I2C_IOCTL_WriteBuffer``   | | Writes data to i2c device via IOCTL.                                                   |
| | Example:                                       |                                | | <size> - Read data size.                                                               |
| | ``I2C:IO:W:B2  {0,1}``                         |                                | |                                                                                        |
+--------------------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+




.. note::

   SMBUS is a standardized protocol for communicating with i2c devices. Information about this protocol can be found in this link: `SMBUS specifcation <http://smbus.org/specs/>`_.
   IOCTL writes and reads data directly from i2c.


=============
Specific LEDs
=============

Parameter options:

* ``<mode> = {OFF, ON}``  Default: ``ON``

+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| SCPI                                | API                            | DESCRIPTION                                                                              |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``LED:MMC <mode>``                | ``rp_SetLEDMMCState``          | Turns on or off the yellow LED responsible for indicating the read memory card.          |
| | Example:                          |                                |                                                                                          |
| | ``LED:MMC OFF``                   |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``LED:MMC? > <mode>``             | ``rp_GetLEDMMCState``          | Gets the state of the MMC indicator.                                                     |
| | Example:                          |                                |                                                                                          |
| | ``LED:MMC? > ON``                 |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``LED:HB <mode>``                 | ``rp_SetLEDHeartBeatState``    | Turns on or off the red LED responsible for indicating board activity.                   |
| | Example:                          |                                |                                                                                          |
| | ``LED:HB OFF``                    |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``LED:HB? > <mode>``              | ``rp_GetLEDHeartBeatState``    | Gets the state of the HeartBeat indicator.                                               |
| | Example:                          |                                |                                                                                          |
| | ``LED:HB? > ON``                  |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``LED:ETH <mode>``                | ``rp_SetLEDEthState``          | Turns on or off the LED indicators on the network card.                                  |
| | Example:                          |                                |                                                                                          |
| | ``LED:ETH OFF``                   |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+
| | ``LED:ETH? > <mode>``             | ``rp_GetLEDEthState``          | Gets the state of the Ethernet indicators.                                               |
| | Example:                          |                                |                                                                                          |
| | ``LED:ETH? > ON``                 |                                |                                                                                          |
+-------------------------------------+--------------------------------+------------------------------------------------------------------------------------------+

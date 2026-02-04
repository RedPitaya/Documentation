
.. _commands_gen:

#################
Signal Generator
#################

.. contents:: Generation command index
   :local:
   :depth: 2
   :backlinks: top

|

Functionality overview
========================

Signal generator commands control Red Pitaya's fast analog outputs (DACs) for waveform generation. These commands support continuous signals, burst mode, frequency sweeps, and arbitrary waveform generation (AWG) with precise triggering and synchronization capabilities.

Key generation modes:

* **Continuous** - Generate signals indefinitely until stopped
* **Burst** - Generate a specific number of signal periods with controlled repetition
* **Sweep** - Linear frequency sweep between two frequencies over specified time
* **Arbitrary** - Generate custom waveforms defined by user data (16384 samples)


Important notes
========================

* For STEMlab 125-14 4-Input, the commands in this chapter are not applicable.
* Generation trigger is independent from acquisition trigger.
* Outputs must be enabled (``OUTPUT:STATE ON``) before triggering generation.
* AWG expects exactly 16384 samples per waveform period.
* Frequency range: 1 Hz to 50 MHz (board dependent).
* For detailed programming guidance, see :ref:`SCPI generation section <intro_gen_acq>` in the introduction.


Code examples
========================

Here are some examples of how to use the signal generation commands on Red Pitaya:

* :ref:`Signal generation examples <examples_genRF>`.
* :ref:`Acquisition and generation examples <examples_acq_genRF>`.


Parameters and command tables
==============================


Generator control
--------------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel OUT1 or OUT2)
- ``<state> = {ON,OFF}`` Default: ``OFF``
- ``<enable> = {true, false}`` Default: ``false``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                            | DESCRIPTION                                                                                  |  ECOSYSTEM         |
+=====================================================+=========================================================================================+==============================================================================================+====================+
| | ``GEN:RST``                                       | | C: ``rp_GenReset()``                                                                  | | Stops the generation and sets all generator parameters to default values.                  | 1.04-18 and up     |
| |                                                   | |                                                                                       | |                                                                                            |                    |
| |                                                   | | Python: ``rp_GenReset()``                                                             | |                                                                                            |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``PHAS:ALIGN``                                    | | C: ``rp_GenSynchronise()``                                                            | | Synchronously triggers the generation of both fast analog outputs immediately.             | 1.04-18 and up     |
| |                                                   | |                                                                                       | | The signal phase is aligned.                                                               |                    |
| |                                                   | | Python: ``rp_GenSynchronise()``                                                       | | (Same as SOUR:TRig:INT)                                                                    |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``OUTPUT<n>:STATE <state>``                       | | C: ``rp_GenOutEnable(rp_channel_t channel)``                                          | | Enable/disable supplying voltage to the specified fast analog output. When enabled,        | 1.04-18 and up     |
| | Examples:                                         | |    ``rp_GenOutDisable(rp_channel_t channel)``                                         | | the signal does not start generating, but the initial voltage value                        |                    |
| | ``OUTPUT1:STATE ON``                              | | Python: ``rp_GenOutEnable(<channel>)``                                                | | (``SOUR<n>:INITValue``, ``rp_GenSetInitGenValue``) appears on the fast analog output.      |                    |
| |                                                   | |         ``rp_GenOutDisable(<channel>)``                                               | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``OUTPUT<n>:STATE?`` > ``<state>``                | | C: ``rp_GenOutIsEnabled(rp_channel_t channel, bool *value)``                          | | Get the enable/disable supply voltage status of the specified fast analog output.          | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | |                                                                                            |                    |
| | ``OUTPUT1:STATE?`` > ``ON``                       | | Python: ``rp_GenOutIsEnabled(<channel>)``                                             | |                                                                                            |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``OUTPUT:STATE <state>``                          | | C: ``rp_GenOutEnableSync(bool enable)``                                               | | Enable/disable supplying voltage to both fast analog outputs. When enabled, the signal     | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | does not start generating, but the initial voltage value (``SOUR<n>:INITValue``,           |                    |
| | ``OUTPUT:STATE ON``                               | | Python: ``rp_GenOutEnableSync(<enable>)``                                             | |  ``rp_GenSetInitGenValue``) apperas on both fast analog outputs.                           |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+




Generator trigger
-------------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel OUT1 or OUT2)
- ``<state> = {ON,OFF}`` Default: ``OFF``
- ``<utime> = {value in us}`` Default: ``500``
- ``<trigger> = {EXT_PE, EXT_NE, INT, GATED}`` Default: ``INT``

    - ``EXT`` = External
    - ``INT`` = Internal
    - ``GATED`` = gated busts

- ``<enable> = {true, false}`` Default: ``false``

**Available Jupyter and API macros:**

- Generator trigger source - ``RP_GEN_TRIG_SRC_INTERNAL, RP_GEN_TRIG_SRC_EXT_PE, RP_GEN_TRIG_SRC_EXT_NE``



.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                            | DESCRIPTION                                                                                  |  ECOSYSTEM         |
+=====================================================+=========================================================================================+==============================================================================================+====================+
| | ``SOUR<n>:TRig:SOUR <trigger>``                   | | C: ``rp_GenTriggerSource(rp_channel_t channel, rp_trig_src_t src)``                   | | Set the trigger source for the selected signal (either internal or external).              | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | The external trigger must be a 3V3 CMOS signal.                                            |                    |
| | ``SOUR1:TRig:SOUR EXT_PE``                        | | Python: ``rp_GenTriggerSource(<channel>, <src>)``                                     | |                                                                                            |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRig:SOUR?`` > ``<trigger>``            | | C: ``rp_GenGetTriggerSource(rp_channel_t channel, rp_trig_src_t *src)``               | Get the trigger source setting.                                                              | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:TRig:SOUR?`` > ``EXT_PE``                 | | Python: ``rp_GenGetTriggerSource(<channel>)``                                         |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenResetTrigger(rp_channel_t channel)``                                       | Reset generator settings for the specified fast analog output.                               | 1.04-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenResetTrigger(<channel>)``                                             |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:TRig:INT``                                 | | C: ``rp_GenSynchronise()``                                                            | | Synchronously triggers the generation of both fast analog outputs immediately.             | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | The signal phase is aligned.                                                               |                    |
| | ``SOUR:TRig:INT``                                 | | Python: ``rp_GenSynchronise()``                                                       | | The command resets the FPGA and the signal starts to be generated from the beginning.      |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRig:INT``                              | | C: ``rp_GenResetTrigger(rp_channel_t channel)``                                       | | Triggers the generation of the specified fast analog output immediately.                   | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | The command resets the FPGA and the signal starts to be generated from the beginning.      |                    |
| | ``SOUR1:TRig:INT``                                | | Python: ``rp_GenResetTrigger(<channel>)``                                             |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:TRig:INT:ONLY``                            | | C: ``rp_GenTriggerOnlyBoth()``                                                        | | Synchronously triggers the generation of both fast analog outputs immediately.             | 2.07-43 and up     |
| | Examples:                                         | |                                                                                       | |                                                                                            |                    |
| | ``SOUR:TRig:INT:ONLY``                            | | Python: ``rp_GenTriggerOnlyBoth()``                                                   | |                                                                                            |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRig:INT:ONLY``                         | | C: ``rp_GenTriggerOnly(rp_channel_t channel)``                                        | Triggers the generation of the specified fast analog output immediately.                     | 2.07-43 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:TRig:INT:ONLY``                           | | Python: ``rp_GenTriggerOnly(<channel>)``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:TRig:EXT:DEBouncer[:US] <utime>``          | | C: ``rp_GenSetExtTriggerDebouncerUs(double utime)``                                   | Sets the external trigger generation debouncer in microseconds (value must be positive).     | 2.00-15 and up     |
| | Example:                                          | |                                                                                       |                                                                                              |                    |
| | ``SOUR:TRig:EXT:DEBouncer:US 1``                  | | Python: ``rp_GenSetExtTriggerDebouncerUs(<utime>)``                                   |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:TRig:EXT:DEBouncer[:US]?`` > ``<utime>``   | | C: ``rp_GenGetExtTriggerDebouncerUs(double *utime)``                                  | Get the external trigger generation debouncer setting in microseconds.                       | 2.00-15 and up     |
| | Example:                                          | |                                                                                       |                                                                                              |                    |
| | ``SOUR:TRig:EXT:DEBouncer:US?`` > ``1``           | | Python: ``rp_GenSetExtTriggerDebouncerUs(<utime>)``                                   |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``TRig:EXT:LEV <voltage>``                        | | C: ``rp_SetExternalTriggerLevel(float voltage)``                                      | Set the external trigger level in V.                                                         | 2.04-35 and up     |
| | Example:                                          | |                                                                                       | (Only SIGNALlab 250-12)                                                                      |                    |
| | ``TRig:EXT:LEV 1``                                | | Python: ``rp_SetExternalTriggerLevel(<voltage>)``                                     |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``TRig:EXT:LEV?`` > ``<voltage>``                 | | C: ``rp_GetExternalTriggerLevel(float* voltage)``                                     | Get the external trigger level in V.                                                         | 2.04-35 and up     |
| | Example:                                          | |                                                                                       | (Only SIGNALlab 250-12)                                                                      |                    |
| | ``TRig:EXT:LEV?`` > ``1``                         | | Python: ``rp_GetExternalTriggerLevel()``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+



Generator settings
--------------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel OUT1 or OUT2)
- ``<frequency> = {0 ... 62.5e6}`` (in Hertz). Default: ``1000``
- ``<type> = {SINE, SQUARE, TRIANGLE, SAWU, SAWD, PWM, ARBITRARY, DC, DC_NEG}`` Default: ``SINE``
- ``<amplitude> = {-1 ... 1}`` (in Volts). Default: ``1`` for SIGNALlab 250-12 ``{-5 ... 5}``
- ``<level> = {-1 ... 1}``(in Volts). Default: ``0`` for SIGNALlab 250-12 ``{-5 ... 5}``
- ``<offset> = {-1 ... 1}`` (in Volts). Default: ``0``
- ``<phase> = {-360 ... 360}`` (in Degrees). Default: ``0``
- ``<ratio> = {0 ... 1}`` Default: ``0.5`` Where 1 corresponds to 100%
- ``<time> = {0 ... 10000}`` Default: ``1`` The minimum and maximum value depends on the signal frequency.
- ``<array> = {value1, ...}`` Max 16384 values, floats in the range -1 to 1
- ``<waveform> = {value1, ...}`` Max 16384 values, floats in the range -1 to 1 (``arbBuffer`` for Python API and Jupyter)
- ``<lenght>`` waveform array length
- ``<load_mode> = {INF, L50}`` Default: ``INF``

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``
- Waveforms - ``RP_WAVEFORM_SINE, RP_WAVEFORM_SQUARE, RP_WAVEFORM_TRIANGLE, RP_WAVEFORM_RAMP_UP, RP_WAVEFORM_RAMP_DOWN, RP_WAVEFORM_DC, RP_WAVEFORM_PWM, RP_WAVEFORM_ARBITRARY, RP_WAVEFORM_DC_NEG, RP_WAVEFORM_SWEEP``
- Rise and fall times - ``RISE_FALL_MIN_RATIO, RISE_FALL_MAX_RATIO``
- Load modes - ``RP_GEN_HI_Z, RP_GEN_50Ohm``

*SIGNALlab 250-12 only:*

- Generator gain - ``RP_GAIN_1X, RP_GAIN_5X``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                            | DESCRIPTION                                                                                  |  ECOSYSTEM         |
+=====================================================+=========================================================================================+==============================================================================================+====================+
| | ``SOUR<n>:FUNC <type>``                           | | C: ``rp_GenWaveform(rp_channel_t channel, rp_waveform_t type)``                       | Set the waveform of a fast analog output.                                                    | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR2:FUNC TRIANGLE``                           | | Python: ``rp_GenWaveform(<channel>, <type>)``                                         |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FUNC?`` > ``<type>``                    | | C: ``rp_GenGetWaveform(rp_channel_t channel, rp_waveform_t *type)``                   | Get the waveform of a fast analog output.                                                    | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR2:FUNC?`` > ``TRIANGLE``                    | | Python: ``rp_GenGetWaveform(<channel>)``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FREQ:FIX <frequency>``                  | | C: ``rp_GenFreq(rp_channel_t channel, float frequency)``                              | | Set the signal frequency of a fast analog output.                                          | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | For the ARBITRARY waveform, this is the frequency of one signal period (a buffer of        |                    |
| | ``SOUR2:FREQ:FIX 100000``                         | | Python: ``rp_GenFreq(<channel>, <frequency>)``                                        | | 16384 samples).                                                                            |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FREQ:FIX:Direct <frequency>``           | | C: ``rp_GenFreqDirect(rp_channel_t channel, float frequency)``                        | | Set the channel signal frequency in FPGA without reseting the generator and rebuilding     | 2.04-35 and up     |
| | Examples                                          | |                                                                                       | | the signal.                                                                                |                    |
| | ``SOUR2:FREQ:FIX:Direct 100000``                  | | Python: ``rp_GenFreqDirect(<channel>, <frequency>)``                                  | |                                                                                            |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FREQ:FIX?`` > ``<frequency>``           | | C: ``rp_GenGetFreq(rp_channel_t channel, float *frequency)``                          | Get signal frequency of the specified channel.                                               | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR2:FREQ:FIX?`` > ``100000``                  | | Python: ``rp_GenGetFreq(<channel>)``                                                  |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:VOLT <amplitude>``                      | | C: ``rp_GenAmp(rp_channel_t channel, float amplitude)``                               | | Set the one-way amplitude of a fast analog output in Volts.                                | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | Amplitude + offset value must be less than the maximum output voltage range (±1 V)         |                    |
| | ``SOUR2:VOLT 0.5``                                | | Python: ``rp_GenAmp(<channel>, <amplitude>)``                                         | | (±2 V/ ±10 V (Hi-Z load) for SIGNALlab).                                                   |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:VOLT?`` > ``<amplitude>``               | | C: ``rp_GenGetAmp(rp_channel_t channel, float *amplitude)``                           | Get the one-way amplitude of a fast analog output in Volts.                                  | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR2:VOLT?`` > ``0.5``                         | | Python: ``rp_GenGetAmp(<channel>)``                                                   |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:VOLT:OFFS <offset>``                    | | C: ``rp_GenOffset(rp_channel_t channel, float offset)``                               | | Set the DC offset voltage of a fast analog output in Volts.                                | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | Amplitude + offset value must be less than the maximum output voltage range (±1 V)         |                    |
| | ``SOUR1:VOLT:OFFS 0.2``                           | | Python: ``rp_GenOffset(<channel>, <offset>)``                                         | | (±2 V/ ±10 V (Hi-Z load) for SIGNALlab).                                                   |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:VOLT:OFFS?`` > ``<offset>``             | | C: ``rp_GenGetOffset(rp_channel_t channel, float *offset)``                           | Get the DC offset of a fast analog output in Volts.                                          | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:VOLT:OFFS?`` > ``0.2``                    | | Python: ``rp_GenGetOffset(<channel>)``                                                |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:PHAS <phase>``                          | | C: ``rp_GenPhase(rp_channel_t channel, float phase)``                                 | | Set the phase of a fast analog output in degrees. The signal starts generating with the    | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | specified phase. For example, if the phase is set to 90 degrees, the signal starts         |                    |
| | ``SOUR2:PHAS 30``                                 | | Python: ``rp_GenPhase(<channel>, <phase>)``                                           | | generating as cosine instead of sine.                                                      |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:PHAS?`` > ``<phase>``                   | | C: ``rp_GenGetPhase(rp_channel_t channel, float *phase)``                             | Get the phase of a fast analog output in degrees.                                            | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR2:PHAS?`` > ``30``                          | | Python: ``rp_GenGetPhase(<channel>)``                                                 |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:DCYC <ratio>``                          | | C: ``rp_GenDutyCycle(rp_channel_t channel, float ratio)``                             | Set the duty cycle of the PWM waveform.                                                      | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:DCYC 0.2``                                | | Python: ``rp_GenDutyCycle(<channel>, <ratio>)``                                       |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:DCYC?`` > ``<ratio>``                   | | C: ``rp_GenGetDutyCycle(rp_channel_t channel, float *ratio)``                         | Get the duty cycle of the PWM waveform.                                                      | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:DCYC`` > ``0.2``                          | | Python: ``def rp_GenGetDutyCycle(<channel>)``                                         |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRAC:DATA:DATA <array>``                | | C: ``rp_GenArbWaveform(rp_channel_t channel, float *waveform, uint32_t length)``      | | Import data for one period of an arbitrary waveform (should be exactly 16384 samples).     | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | If fewer samples are provided, the output frequency will be higher.                        |                    |
| | ``SOUR1:TRAC:DATA:DATA 1,0.5,0.2``                | | Python: ``rp_GenArbWaveform(<channel>, <waveform>, <length>)``                        | |                                                                                            |                    |
| |                                                   | |         ``rp_GenArbWaveformNP(<channel>, <np_buffer>)``                               | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRAC:DATA:DATA?`` > ``<array>``         | | C: ``rp_GenGetArbWaveform(rp_channel_t channel, float *waveform, uint32_t *length)``  | Get the user-defined arbitrary waveform period.                                              | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:TRAC:DATA:DATA?`` >  ``1,0.5,0.2``        | | Python: ``rp_GenGetArbWaveform(<channel>, <waveform>)``                               |                                                                                              |                    |
| |                                                   | |         ``rp_GenGetArbWaveformNP(<channel>, <np_buffer>)``                            |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:LOAD <load_mode>``                      | | C: ``rp_GenSetLoadMode(rp_channel_t channel, rp_gen_load_mode_t mode)``               | | Set the load mode for the output. When switching from INF to L50 also halves the set       | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       | | amplitude (``SOUR<n>:VOLT``). When switching from L50 to INF the amplitude is doubled.     |                    |
| | ``SOUR2:LOAD L50``                                | | Python: ``rp_GenSetLoadMode(<channel>, <mode>)``                                      | | Frist set load, then set the amplitude. (SIGNALlab only)                                   |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:LOAD?`` > ``<load_mode>``               | | C: ``rp_GenGetLoadMode(rp_channel_t channel, rp_gen_load_mode_t *mode)``              | Get the load mode for the output. (SIGNALlab only)                                           | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR2:LOAD?`` > ``L50``                         | | Python: ``rp_GenGetLoadMode(<mode>)``                                                 |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenSetGainOut(rp_channel_t channel, rp_gen_gain_t gain_mode)``                | Set SIGNALlab output gain. (SIGNALlab only)                                                  | 1.04-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenSetGainOut(<channel>, <gain_mode>)``                                  |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenGetGainOut(rp_channel_t channel, rp_gen_gain_t *gain_mode)``               | Get SIGNALlab output gain. (SIGNALlab only)                                                  | 1.04-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenGetGainOut(<channel>)``                                               |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:RISE:TIME <time>``                      | | C: ``rp_GenRiseTime(rp_channel_t channel, float time)``                               | | Set signal rise time of a fast analog output in microseconds.                              | 2.00-18 and up     |
| | Examples:                                         | |                                                                                       | | The range of acceptable values depends on the frequency.                                   |                    |
| | ``SOUR1:RISE:TIME 0.1``                           | | Python: ``rp_GenRiseTime(<channel>, <time>)``                                         | | To configure, first specify the signal frequency.                                          |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:RISE:TIME?`` > ``<time>``               | | C: ``rp_GenGetRiseTime(rp_channel_t channel, float *time)``                           | Get signal rise time of a fast analog output in microseconds.                                | 2.00-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:RISE:TIME?`` > ``0.1``                    | | Python: ``rp_GenGetRiseTime(<channel>)``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FALL:TIME <time>``                      | | C: ``rp_GenFallTime(rp_channel_t channel, float time)``                               | | Set signal fall time of a fast analog output in microseconds.                              | 2.00-18 and up     |
| | Examples:                                         | |                                                                                       | | The range of acceptable values depends on the frequency.                                   |                    |
| | ``SOUR1:FALL:TIME 0.1``                           | | Python: ``rp_GenFallTime(<channel>, <time>)``                                         | | To configure, first specify the signal frequency.                                          |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:FALL:TIME?`` > ``<time>``               | | C: ``rp_GenGetFallTime(rp_channel_t channel, float *time)``                           | Get signal fall time of a fast analog output in microseconds.                                | 2.00-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:FALL:TIME?`` > ``0.1``                    | | Python: ``rp_GenGetFallTime(<channel>)``                                              |                                                                                              |                    |
|                                                     | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+



Burst mode
------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel OUT1 or OUT2)
- ``<mode> = {BURST, CONTINUOUS}`` Default: ``CONTINUOUS``
- ``<num>, <repetitions> = {1...65536}`` Default: ``1``
- ``<period> = {1 µs - 500 s}`` Value in *µs*.

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``
- Generator modes - ``RP_GEN_MODE_CONTINUOUS, RP_GEN_MODE_BURST``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                            | DESCRIPTION                                                                                  |  ECOSYSTEM         |
+=====================================================+=========================================================================================+==============================================================================================+====================+
| | ``SOUR<n>:BURS:STAT <mode>``                      | | C: ``rp_GenMode(rp_channel_t channel, rp_gen_mode_t mode)``                           | | Enable or disable burst (pulse) mode.                                                      | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | Red Pitaya will generate **R** bursts with **N** signal periods.                           |                    |
| | ``SOUR1:BURS:STAT BURST``                         | | Python: ``rp_GenMode(<channel>, <mode>)``                                             | | **P** is the time between the start of one and the start of the next burst.                |                    |
| | ``SOUR1:BURS:STAT CONTINUOUS``                    | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:STAT?`` > ``<mode>``               | | C: ``rp_GenGetMode(rp_channel_t channel, rp_gen_mode_t *mode)``                       | Get the generation mode.                                                                     | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:BURS:STAT?`` > ``BURST``                  | | Python: ``rp_GenGetMode(<channel>)``                                                  |                                                                                              |                    |
|                                                     | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:NCYC <num>``                       | | C: ``rp_GenBurstCount(rp_channel_t channel, int num)``                                | Set the number of cycles/periods in one burst (**N**).                                       | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:BURS:NCYC 3``                             | | Python: ``rp_GenBurstCount(<channel>, <num>)``                                        |                                                                                              |                    |
|                                                     | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:NCYC?`` > ``<num>``                | | C: ``rp_GenGetBurstCount(rp_channel_t channel, int *num)``                            | Get the number of generated waveforms in a burst.                                            | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:BURS:NCYC`` > ``3``                       | | Python: ``rp_GenGetBurstCount(<channel>)``                                            |                                                                                              |                    |
|                                                     | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:NOR <repetitions>``                | | C: ``rp_GenBurstRepetitions(rp_channel_t channel, int repetitions)``                  | Set the number of repeated bursts (**R**) (65536 == INF repetitions)                         | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:BURS:NOR 5``                              | | Python: ``rp_GenBurstRepetitions(<channel>, <repetitions>)``                          |                                                                                              |                    |
|                                                     | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:NOR?`` > ``<repetitions>``         | | C: ``rp_GenGetBurstRepetitions(rp_channel_t channel, int *repetitions)``              | Get the number of burst repetitions.                                                         | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:BURS:NOR`` > ``5``                        | | Python: ``rp_GenGetBurstRepetitions(<channel>)``                                      |                                                                                              |                    |
|                                                     | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:INT:PER <period>``                 | | C: ``rp_GenBurstPeriod(rp_channel_t channel, uint32_t period)``                       | | Set the duration of a single burst in microseconds (**P**). This specifies the time        | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       | | between the start of one and the start of the next burst. The bursts will always have at   |                    |
| | ``SOUR1:BURS:INT:PER 1000000``                    | | Python: ``rp_GenBurstPeriod(<channel>, <period>)``                                    | | least 1 us between them: If the period is shorter than the burst, the software will        |                    |
|                                                     | |                                                                                       | | default to 1 us between bursts.                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:INT:PER?`` > ``<period>``          | | C: ``rp_GenGetBurstPeriod(rp_channel_t channel, uint32_t *period)``                   | Get the period of a bursts in microseconds.                                                  | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:BURS:INT:PER?`` > ``1000000``             | | Python: ``rp_GenGetBurstPeriod(<channel>)``                                           |                                                                                              |                    |
|                                                     | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:INITValue <amplitude>``            | | C: ``rp_GenSetInitGenValue(rp_channel_t channel, float amplitude)``                   | | Set the initial voltage value that appears on the fast analog output once it is enabled    | 2.05-37 and up     |
| | Examples:                                         | |                                                                                       | | but before the signal is generated (See ``OUTPUT<n>:STATE``,                               |                    |
| | ``SOUR1:BURS:INITValue 0.5``                      | | Python: ``rp_GenSetInitGenValue(<channel>, <amplitude>)``                             | | ``rp_GenOutEnable(rp_channel_t channel)``).                                                |                    |
|                                                     | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:INITValue?`` > ``<amplitude>``     | | C: ``rp_GenGetInitGenValue(rp_channel_t channel, float *amplitude)``                  | | Get the initial voltage value that appears on the fast analog output once it is enabled    | 2.05-37 and up     |
| | Examples:                                         | |                                                                                       | | but before the signal is generated (See ``OUTPUT<n>:STATE``,                               |                    |
| | ``SOUR1:BURS:INITValue?`` > ``0.5``               | | Python: ``rp_GenGetInitGenValue(<channel>)``                                          | | ``rp_GenOutEnable(rp_channel_t channel)``).                                                |                    |
|                                                     | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:LASTValue <amplitude>``            | | C: ``rp_GenBurstLastValue(rp_channel_t channel, float amplitude)``                    | | Set the end value of the generated burst signal.                                           | 2.00-18 and up     |
| | Examples:                                         | |                                                                                       | | The output will stay on this value until a new signal is generated.                        |                    |
| | ``SOUR1:BURS:LASTValue 0.5``                      | | Python: ``rp_GenBurstLastValue(<channel>, <amplitude>)``                              | |                                                                                            |                    |
|                                                     | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:BURS:LASTValue?`` > ``<amplitude>``     | | C: ``rp_GenGetBurstLastValue(rp_channel_t channel, float *amplitude)``                | Get the end value of the generated burst signal.                                             | 2.00-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:BURS:LASTValue`` > ``0.5``                | | Python: ``rp_GenGetBurstLastValue(<channel>)``                                        |                                                                                              |                    |
|                                                     | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:INITValue <amplitude>``                 | | C: ``rp_GenSetInitGenValue(rp_channel_t channel, float amplitude)``                   | | Set the initial voltage value that appears on the fast analog output once it is enabled    | 2.00-18 and up     |
| | Examples:                                         | |                                                                                       | | but before the signal is generated (See ``OUTPUT<n>:STATE``,                               |                    |
| | ``SOUR1:INITValue 0.5``                           | | Python: ``rp_GenSetInitGenValue(<channel>, <amplitude>)``                             | | ``rp_GenOutEnable(rp_channel_t channel)``).                                                |                    |
|                                                     | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:INITValue?`` > ``<amplitude>``          | | C: ``rp_GenGetInitGenValue(rp_channel_t channel, float *amplitude)``                  | | Get the initial voltage value that appears on the fast analog output once it is enabled    | 2.00-18 and up     |
| | Examples:                                         | |                                                                                       | | but before the signal is generated (See ``OUTPUT<n>:STATE``,                               |                    |
| | ``SOUR1:INITValue?`` > ``0.5``                    | | Python: ``rp_GenGetInitGenValue(<channel>)``                                          | | ``rp_GenOutEnable(rp_channel_t channel)``).                                                |                    |
|                                                     | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+


.. _commands_sweep:


Sweep mode
------------

Set the waveform type to sweep to enable

**Parameter options:**

- ``<n> = {1,2}`` (set channel OUT1 or OUT2)
- ``<frequency> = {0 ... 62.5e6}`` (in Hertz). Default: ``1000`` (start), ``10000`` (end)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``
- Sweep direction - ``RP_GEN_SWEEP_DIR_NORMAL, RP_GEN_SWEEP_DIR_UP_DOWN``
- Sweep mode - ``RP_GEN_SWEEP_MODE_LINEAR, RP_GEN_SWEEP_MODE_LOG``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                            | DESCRIPTION                                                                                  |  ECOSYSTEM         |
+=====================================================+=========================================================================================+==============================================================================================+====================+
| | -                                                 | | C: ``rp_GenSweepStartFreq(rp_channel_t channel, float frequency)``                    | Set sweep start frequency.                                                                   | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenSweepStartFreq(<channel>, <frequency>)``                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenGetSweepStartFreq(rp_channel_t channel, float *frequency)``                | Get sweep start frequency.                                                                   | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenGetSweepStartFreq(<channel>)``                                        |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenSweepEndFreq(rp_channel_t channel, float frequency)``                      | Set sweep end frequency.                                                                     | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenSweepEndFreq(<channel>, <frequency>)``                                |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenGetSweepEndFreq(rp_channel_t channel, float *frequency)``                  | Get sweep end frequency.                                                                     | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenGetSweepEndFreq(<channel>)``                                          |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenSweepMode(rp_channel_t channel, rp_gen_sweep_mode_t mode)``                | Set sweep mode to either linear or logarithmic.                                              | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenSweepMode(<channel>, <mode>)``                                        |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenGetSweepMode(rp_channel_t channel, rp_gen_sweep_mode_t *mode)``            | Get sweep mode (either linear or logarithmic).                                               | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenGetSweepMode(<channel>)``                                             |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenSweepDir(rp_channel_t channel, rp_gen_sweep_dir_t mode)``                  | Set sweep direction (normal (up) or up-down).                                                | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenSweepDir(<channel>, <mode>)``                                         |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenGetSweepDir(rp_channel_t channel, rp_gen_sweep_dir_t *mode)``              | Get sweep direction (normal (up) or up-down).                                                | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenGetSweepDir(<channel>)``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+

.. _commands_sweep_ext:

Sweep mode extended
--------------------


**Parameter options:**

- ``<n> = {1,2}`` (set channel OUT1 or OUT2)
- ``<frequency> = {0 ... 62.5e6}`` (in Hertz). Default: ``1000`` (start), ``10000`` (end)
- ``<time> = {1 ... }`` (in μS). Default: ``1``
- ``<mode> = {LINEAR, LOG}`` (in μS). Default: ``LINEAR``
- ``<dir> = {NORMAL, UP_DOWN}`` (in μS). Default: ``NORMAL``
- ``<state> = {ON, OFF}``
- ``<count> = {0 ... }``. Default: ``1`` (start)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``
- Sweep direction - ``RP_GEN_SWEEP_DIR_NORMAL, RP_GEN_SWEEP_DIR_UP_DOWN``
- Sweep mode - ``RP_GEN_SWEEP_MODE_LINEAR, RP_GEN_SWEEP_MODE_LOG``
- State - ``True,False``


.. note::

    This API uses a class to control the sweep mode. This class is available in the rp-sweep library.

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                            | DESCRIPTION                                                                                  |  ECOSYSTEM         |
+=====================================================+=========================================================================================+==============================================================================================+====================+
| | -                                                 | | C++: ``run()``                                                                        | | Starts the frequency generator.                                                            | 2.04-35 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``run()``                                                                     |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C++: ``stop()``                                                                       | | Stops the thread that generates frequencies.                                               | 2.04-35 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``stop()``                                                                    |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:SWeep:DEFault``                            | | C++: ``setDefault()``                                                                 | | Stops sweep generation on all channels and sets default values.                            | 2.05-37 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR:SWeep:DEFault``                            | | Python: ``setDefault()``                                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:SWeep:RESET``                              | | C++: ``resetAll()``                                                                   | | Resets all channels at once.                                                               | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR:SWeep:RESET``                              | | Python: ``resetAll()``                                                                |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:SWeep:PAUSE <state>``                      | | C++: ``pause(bool state)``                                                            | | Stops the frequency change, but does not reset the state.                                  | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR:SWeep:PAUSE ON``                           | | Python: ``pause(<state>)``                                                            |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:STATE <state>``                   | | C++: ``genSweep(rp_channel_t channel, bool enable)``                                  | | Enables or disables generation of the specified channel.                                   | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:STATE ON``                          | | Python: ``genSweep(<channel>, <state>)``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:STATE?`` > ``<state>``            | | C++: ``isGen(rp_channel_t channel, bool *state)``                                     | | Returns the channel status.                                                                | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:STATE?`` > ``ON``                   | | Python: ``isGen(<channel>)``                                                          |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:FREQ:START <frequency>``          | | C++: ``setStartFreq(rp_channel_t channel, float frequency)``                          | | Set sweep start frequency.                                                                 | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:FREQ:START 1000``                   | | Python: ``setStartFreq(<channel>, <frequency>)``                                      |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:FREQ:START?`` > ``<frequency>``   | | C++: ``getStartFreq(rp_channel_t channel, float *frequency)``                         | | Get sweep start frequency.                                                                 | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:FREQ:START?`` > ``1000``            | | Python: ``getStartFreq(<channel>)``                                                   |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:FREQ:STOP <frequency>``           | | C++: ``setStopFreq(rp_channel_t channel, float frequency)``                           | | Set sweep stop frequency.                                                                  | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:FREQ:STOP 10000``                   | | Python: ``setStopFreq(<channel>, <frequency>)``                                       |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:FREQ:STOP?`` > ``<frequency>``    | | C++: ``getStopFreq(rp_channel_t channel, float *frequency)``                          | | Get sweep stop frequency.                                                                  | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:FREQ:STOP?`` > ``10000``            | | Python: ``getStopFreq(<channel>)``                                                    |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:TIME <time>``                     | | C++: ``setTime(rp_channel_t channel, int us)``                                        | | Sets the generation time, how long it takes to transition from the                         | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       | | starting frequency to the final frequency, measured in microseconds.                       |                    |
| | ``SOUR1:SWeep:TIME 10000``                        | | Python: ``setTime(<channel>, <frequency>)``                                           |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:TIME?`` > ``<time>``              | | C++: ``getTime(rp_channel_t channel, int *us)``                                       | | Returns generation time in microseconds.                                                   | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:TIME?`` > ``10000``                 | | Python: ``getTime(<channel>)``                                                        |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:MODE <mode>``                     | | C++: ``setMode(rp_channel_t channel, rp_gen_sweep_mode_t mode)``                      | | Set sweep mode to either linear or logarithmic.                                            | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:MODE LINEAR``                       | | Python: ``setMode(<channel>, <mode>)``                                                |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:MODE?`` > ``<mode>``              | | C++: ``getMode(rp_channel_t channel, rp_gen_sweep_mode_t *mode)``                     | | Get sweep mode (either linear or logarithmic).                                             | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:MODE?`` > ``LINEAR``                | | Python: ``getMode(<channel>)``                                                        |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:REP:INF <state>``                 | | C++: ``setNumberOfRepetitions(rp_channel_t _ch, bool _isInfinty, uint64_t _count)``   | | Sets the infinite signal generation mode.                                                  | 2.07-43 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:REP:INF ON``                        | | Python: ``setNumberOfRepetitions(<channel>, <state>, <count>)``                       |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:REP:INF?`` > ``<state>``          | | C++: ``getNumberOfRepetitions(rp_channel_t _ch, bool* _isInfinty, uint64_t* _count)`` | | Gets the infinite signal generation mode.                                                  | 2.07-43 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:REP:INF?`` > ``ON``                 | | Python: ``getNumberOfRepetitions(<channel>, <state>, <count>)``                       |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:REP:COUNT <count>``               | | C++: ``setNumberOfRepetitions(rp_channel_t _ch, bool _isInfinty, uint64_t _count)``   | | Sets the number of repetitions when generating a signal.                                   | 2.07-43 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:REP:COUNT 10``                      | | Python: ``setNumberOfRepetitions(<channel>, <state>, <count>)``                       |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:REP:COUNT?`` > ``<count>``        | | C++: ``getNumberOfRepetitions(rp_channel_t _ch, bool* _isInfinty, uint64_t* _count)`` | | Gets the number of repetitions when generating a signal.                                   | 2.07-43 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:REP:COUNT?`` > ``10``               | | Python: ``getNumberOfRepetitions(<channel>, <state>, <count>)``                       |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:DIR <dir>``                       | | C++: ``setDir(rp_channel_t channel, rp_gen_sweep_dir_t dir)``                         | | Set sweep direction (normal (up) or up-down).                                              | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:DIR UP_DOWN``                       | | Python: ``setDir(<channel>, <dir>)``                                                  |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:DIR?`` > ``<dir>``                | | C++: ``getDir(rp_channel_t channel, rp_gen_sweep_dir_t *dir)``                        | | Get sweep direction (normal (up) or up-down).                                              | 2.04-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:DIR?`` > ``UP_DOWN``                | | Python: ``getDir(<channel>)``                                                         |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_gen>`
* :ref:`Back to command list <command_list>`

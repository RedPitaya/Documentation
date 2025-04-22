
.. _commands_acq:

==============
Acquisition
==============

.. contents:: Index
   :local:
   :depth: 2
   :backlinks: none

|

--------------------
Acquisition Control
--------------------

**Parameter options:**

- ``<enable> = {true, false}``
- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<state> = {ON, OFF}`` Default: ``OFF``

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| SCPI                                | API, Jupyter                                    | DESCRIPTION                                                                |  ECOSYSTEM         |
+=====================================+=================================================+============================================================================+====================+
| | ``ACQ:START``                     | | C: ``rp_AcqStart()``                          | Start the acquisition.                                                     | 1.04-18 and up     |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqStart()``                     |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:START:CH<n>``               | | C: ``rp_AcqStartCh(rp_channel_t channel)``    | | Start the acquisition.                                                   | 2.05-37 and up     |
| |                                   | |                                               | | Used only in split trigger mode                                          |                    |
| |                                   | | Python: ``rp_AcqStartCh(<channel>)``          | | (currently only STEMlab 125-14 4-Input)                                  |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:STOP``                      | | C: ``rp_AcqStop()``                           | Stop the acquisition.                                                      | 1.04-18 and up     |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqStop()``                      |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:STOP:CH<n>``                | | C: ``rp_AcqStopCh(rp_channel_t channel)``     | | Stop the acquisition.                                                    | 2.05-37 and up     |
| |                                   | |                                               | | Used only in split trigger mode                                          |                    |
| |                                   | | Python: ``rp_AcqStopCh(<channel>)``           | | (currently only STEMlab 125-14 4-Input)                                  |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:RST``                       | | C: ``rp_AcqReset()``                          | | Stop the acquisition and reset all acquisition parameters to             | 1.04-18 and up     |
| |                                   | |                                               | | default values.                                                          |                    |
| |                                   | | Python: ``rp_AcqReset()``                     | |                                                                          |                    |
| |                                   | |                                               | |                                                                          |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:RST:CH<n>``                 | | C: ``rp_AcqResetCh(rp_channel_t channel)``    | | Stop the acquisition and reset all acquisition parameters to             | 2.05-37 and up     |
| |                                   | |                                               | | default values.                                                          |                    |
| |                                   | | Python: ``rp_AcqResetCh(<channel>)``          | | Used only in split trigger mode                                          |                    |
| |                                   | |                                               | | (currently only STEMlab 125-14 4-Input)                                  |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:SPLIT:TRig <state>``        | | C: ``rp_AcqSetSplitTrigger(bool enable)``     | | Enables split trigger mode.                                              | 2.05-37 and up     |
| |                                   | |                                               | | (currently only STEMlab 125-14 4-Input)                                  |                    |
| |                                   | | Python: ``rp_AcqSetSplitTrigger(<enable>)``   |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:SPLIT:TRig?`` > ``<state>`` | | C: ``rp_AcqGetSplitTrigger(bool* state)``     | | Returns the split trigger mode status                                    | 2.05-37 and up     |
| |                                   | |                                               | | (currently only STEMlab 125-14 4-Input)                                  |                    |
| |                                   | | Python: ``rp_AcqGetSplitTrigger()``           |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | -                                 | | C: ``rp_AcqResetFpga()``                      | Reset the acqusition writing state machine.                                | 1.04-18 and up     |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqResetFpga()``                 |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | -                                 | | C: ``rp_AcqSetArmKeep(bool enable)``          | Enable continous acquisition even after trigger has happened.              | 1.04-18 and up     |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqSetArmKeep(<enable>)``        |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | -                                 | | C: ``rp_AcqGetArmKeep(bool* state)``          | Get the status of continous acquisition after trigger setting.             | 1.04-18 and up     |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqGetArmKeep()``                |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+



--------------------------
Acquisition settings
--------------------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<decimation> = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536}`` Default: ``1``
- ``<decimation_ext> = {1, 2, 4, 8, 16, 17, 18, 19, ..., 65536}`` Default: ``1``
- ``<average> = {OFF, ON}`` Default: ``ON``
- ``<bypass> = {OFF, ON}`` Default: ``OFF``
- ``<state> = {LV, HV}`` Default: ``LV``
- ``<mode> = {AC, DC}`` Default ``DC``
- ``<units> = {RAW, VOLTS}`` Default ``VOLTS``
- ``<format> = {BIN, ASCII}`` Default ``ASCII``
- ``<enable> = {true, false}`` Default: ``true``


*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``
- Decimation - ``RP_DEC_1, RP_DEC_2, RP_DEC_4, RP_DEC_8, RP_DEC_16, RP_DEC_32, RP_DEC_64, RP_DEC_128, RP_DEC_256, RP_DEC_512, RP_DEC_1024, RP_DEC_2048, RP_DEC_4096, RP_DEC_8192, RP_DEC_16384, RP_DEC_32768, RP_DEC_65536``

*SIGNALlab 250-12 only (additional):*

- Input coupling - ``RP_DC, RP_AC``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                                   | DESCRIPTION                                                                   |  ECOSYSTEM         |
+=====================================================+================================================================================================+===============================================================================+====================+
| | ``ACQ:DEC <decimation>``                          | | C: ``rp_AcqSetDecimation(rp_acq_decimation_t decimation)``                                   | | Set the decimation factor (power of 2 from 1 to 65536).                     | 1.04-18 and up     |
| | Example:                                          | |                                                                                              | |                                                                             |                    |
| | ``ACQ:DEC 4``                                     | | Python: ``rp_AcqSetDecimation(<decimation>)``                                                | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:CH<n> <decimation>``                    | | C: ``rp_AcqSetDecimationCh(rp_channel_t channel, rp_acq_decimation_t decimation)``           | | Set the decimation factor (power of 2 from 1 to 65536).                     | 2.05-37 and up     |
| | Example:                                          | |                                                                                              | | Used only in split trigger mode                                             |                    |
| | ``ACQ:DEC:CH1 4``                                 | | Python: ``rp_AcqSetDecimationCh(<channel>, <decimation>)``                                   | | (currently only STEMlab 125-14 4-Input)                                     |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC?`` > ``<decimation>``                   | | C: ``rp_AcqGetDecimation(rp_acq_decimation_t* decimation)``                                  | Get the decimation factor.                                                    | 1.04-18 and up     |
| | Example:                                          | |                                                                                              |                                                                               |                    |
| | ``ACQ:DEC?`` > ``1``                              | | Python: ``rp_AcqGetDecimation()``                                                            |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:CH<n>?`` > ``<decimation>``             | | C: ``rp_AcqGetDecimationCh(rp_channel_t channel, rp_acq_decimation_t* decimation)``          | | Get the decimation factor.                                                  | 2.05-37 and up     |
| | Example:                                          | |                                                                                              | | Used only in split trigger mode                                             |                    |
| | ``ACQ:DEC:CH1?`` > ``1``                          | | Python: ``rp_AcqGetDecimationCh(<channel>)``                                                 | | (currently only STEMlab 125-14 4-Input)                                     |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:Factor <decimation_ext>``               | | C: ``rp_AcqSetDecimationFactor(uint32_t decimation)``                                        | | Set the extended decimation factor (power of 2 up to 16 then any            | 2.00-30 and up     |
| | Example:                                          | |                                                                                              | | whole number up to 65536).                                                  |                    |
| | ``ACQ:DEC:Factor 17``                             | | Python: ``rp_AcqSetDecimationFactor(<decimation>)``                                          | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:Factor:CH<n> <decimation_ext>``         | | C: ``rp_AcqSetDecimationFactorCh(rp_channel_t channel, uint32_t decimation)``                | | Set the extended decimation factor (power of 2 up to 16 then any            | 2.05-37 and up     |
| | Example:                                          | |                                                                                              | | whole number up to 65536).                                                  |                    |
| | ``ACQ:DEC:Factor:CH1 17``                         | | Python: ``rp_AcqSetDecimationFactorCh(<channel>, <decimation>)``                             | | Used only in split trigger mode                                             |                    |
| |                                                   | |                                                                                              | | (currently only STEMlab 125-14 4-Input)                                     |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:Factor?`` > ``<decimation_ext>``        | | C: ``rp_AcqGetDecimationFactor(uint32_t* decimation)``                                       | Get the extended decimation factor.                                           | 2.00-30 and up     |
| | Example:                                          | |                                                                                              |                                                                               |                    |
| | ``ACQ:DEC:Factor?`` > ``1``                       | | Python: ``rp_AcqGetDecimationFactor()``                                                      |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:Factor:CH<n>?`` > ``<decimation_ext>``  | | C: ``rp_AcqGetDecimationFactorCh(rp_channel_t channel, uint32_t* decimation)``               | | Get the extended decimation factor.                                         | 2.05-37 and up     |
| | Example:                                          | |                                                                                              | | Used only in split trigger mode                                             |                    |
| | ``ACQ:DEC:Factor:CH1?`` > ``1``                   | | Python: ``rp_AcqGetDecimationFactorCh(<channel>)``                                           | | (currently only STEMlab 125-14 4-Input)                                     |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_AcqConvertFactorToDecimation(uint32_t factor,rp_acq_decimation_t* decimation)``      | | Convert the decimation factor to the closest available decimation value     | 1.04-18 and up     |
| |                                                   | |                                                                                              | | (closest power of 2).                                                       |                    |
| |                                                   | | Python: ``rp_AcqConvertFactorToDecimation(<factor>)``                                        | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_AcqGetSamplingRateHz(float* sampling_rate)``                                         | | Get the current sampling rate in Hertz.                                     | 1.04-18 and up     |
| |                                                   | |                                                                                              | |                                                                             |                    |
| |                                                   | | Python: ``rp_AcqGetSamplingRateHz()``                                                        | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AVG <average>``                             | | C: ``rp_AcqSetAveraging(bool enabled)``                                                      | | Enable/disable averaging.                                                   | 1.04-18 and up     |
| |                                                   | |                                                                                              | | Each sample is the average of skipped samples if ``DEC`` > 1.               |                    |
| |                                                   | | Python: ``rp_AcqSetAveraging(<enable>)``                                                     | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AVG?`` > ``<average>``                      | | C: ``rp_AcqGetAveraging(bool *enabled)``                                                     | | Get the averaging status.                                                   | 1.04-18 and up     |
| | Example:                                          | |                                                                                              | | Averages the skipped samples when ``DEC`` > 1                               |                    |
| | ``ACQ:AVG?`` > ``ON``                             | | Python: ``rp_AcqGetAveraging()``                                                             | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AVG:CH<n> <average>``                       | | C: ``rp_AcqSetAveragingCh(rp_channel_t channel, bool enabled)``                              | | Enable/disable averaging.                                                   | 2.05-37 and up     |
| |                                                   | |                                                                                              | | Each sample is the average of skipped samples if ``DEC`` > 1.               |                    |
| |                                                   | | Python: ``rp_AcqSetAveragingCh(<channel>, <enable>)``                                        | | Used only in split trigger mode                                             |                    |
| |                                                   | |                                                                                              | | (currently only STEMlab 125-14 4-Input)                                     |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AVG:CH<n>?`` > ``<average>``                | | C: ``rp_AcqGetAveragingCh(rp_channel_t channel, bool *enabled)``                             | | Get the averaging status.                                                   | 2.05-37 and up     |
| | Example:                                          | |                                                                                              | | Averages the skipped samples when ``DEC`` > 1                               |                    |
| | ``ACQ:AVG:CH1?`` > ``ON``                         | | Python: ``rp_AcqGetAveragingCh(<channel>)``                                                  | | Used only in split trigger mode                                             |                    |
| |                                                   | |                                                                                              | | (currently only STEMlab 125-14 4-Input)                                     |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:FILTER:BYPASS:CH<n> <bypass>``              | | C: ``rp_AcqSetBypassFilter(rp_channel_t channel, bool enabled)``                             | | The function enables or disables the filter in the FPGA.                    | In dev             |
| |                                                   | |                                                                                              | |                                                                             |                    |
| |                                                   | | Python: ``rp_AcqSetBypassFilter(<channel>, <enable>)``                                       | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:FILTER:BYPASS:CH<n>?`` > ``<bypass>``       | | C: ``rp_AcqGetBypassFilter(rp_channel_t channel, bool *enabled)``                            | | Gets the current filter bypass from the FPGA                                | In dev             |
| | Example:                                          | |                                                                                              | |                                                                             |                    |
| | ``ACQ:FILTER:BYPASS:CH1?`` > ``ON``               | | Python: ``rp_AcqGetBypassFilter(<channel>)``                                                 | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:GAIN <state>``                      | | C: ``rp_AcqSetGain(rp_channel_t channel, rp_pinState_t state)``                              | | Set the gain for the specified channel to HIGH or LOW.                      | 1.04-18 and up     |
| |                                                   | |                                                                                              | | (For SIGNALlab 250-12 this is 1:20 and 1:1 attenuator).                     |                    |
| | Example:                                          | | Python: ``rp_AcqSetGain(<channel>, <state>)``                                                | | The gain refers to jumper settings on the Red Pitaya fast analog input.     |                    |
| | ``ACQ:SOUR1:GAIN LV``                             | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:GAIN?`` > ``<state>``               | | C: ``rp_AcqGetGain(rp_channel_t channel, rp_pinState_t* state)``                             | | Get the gain setting for the specified channel                              | 1.04-18 and up     |
| |                                                   | |                                                                                              | | (For SIGNALlab 250-12 this is 1:20 and 1:1 attenuator).                     |                    |
| | Example:                                          | | Python: ``rp_AcqGetGain(<channel>)``                                                         | |                                                                             |                    |
| | ``ACQ:SOUR1:GAIN?`` > ``HV``                      | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_AcqGetGainV(rp_channel_t channel, float* voltage)``                                  | | Get specified channel gain in Volts.                                        | 1.04-18 and up     |
| |                                                   | |                                                                                              | |                                                                             |                    |
| |                                                   | | Python: ``rp_AcqGetGainV(<channel>)``                                                        | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:COUP <mode>``                       | | C: ``rp_AcqSetAC_DC(rp_channel_t channel, rp_acq_ac_dc_mode_t mode)``                        | Set the AC / DC mode of the specified input (only SIGNALlab 250-12).          | 1.04-18 and up     |
| | Example:                                          | |                                                                                              |                                                                               |                    |
| | ``ACQ:SOUR1:COUP AC``                             | | Python: ``rp_AcqSetAC_DC(<channel>, <mode>)``                                                |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:COUP?`` > ``<mode>``                | | C: ``rp_AcqGetAC_DC(rp_channel_t channel, rp_acq_ac_dc_mode_t *status)``                     | Get the AC / DC mode of the specified input (only SIGNALlab 250-12).          | 1.04-18 and up     |
| | Example:                                          | |                                                                                              |                                                                               |                    |
| | ``ACQ:SOUR1:COUP?`` > ``AC``                      | | Python: ``rp_AcqGetAC_DC(<channel>)``                                                        |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DATA:Units <units>``                        | | C: - (See specific acquisition command)                                                      | | Select units in which the acquired data will be returned. For API commands  | 1.04-18 and up     |
| | Example:                                          | |                                                                                              | | this depends on which function is called (see specific functions for        |                    |
| | ``ACQ:DATA:Units RAW``                            | | Python: - (See specific acquisition command)                                                 | |  details).                                                                  |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DATA:Units?`` > ``<units>``                 | | C: - (See specific acquisition command)                                                      | Get units in which the acquired data will be returned.                        | 1.04-18 and up     |
| | Example:                                          | |                                                                                              |                                                                               |                    |
| | ``ACQ:DATA:Units?`` > ``RAW``                     | | Python: - (See specific acquisition command)                                                 |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DATA:FORMAT <format>``                      | | C: - (N/A)                                                                                   | | Select the format in which the acquired data will be returned.              | 1.04-18 and up     |
| | Example:                                          | |                                                                                              | | Only for remote SCPI control.                                               |                    |
| | ``ACQ:DATA:FORMAT ASCII``                         | | Python: - (N/A)                                                                              | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:BUF:SIZE?`` > ``<size>``                    | | C: ``rp_AcqGetBufSize(uint32_t *size)``                                                      | | Returns the buffer size.                                                    | 1.04-18 and up     |
| | Example:                                          | |                                                                                              | | For Python API specifically, the input parameter is the buffer itself.      |                    |
| | ``ACQ:BUF:SIZE?`` > ``16384``                     | | Python: ``rp_AcqGetBufSize(<buffer>)``                                                       | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | - (N/A)                                           | | C: - (look for *malloc* function online)                                                     | | Performs memory allocation and returns the requested buffer.                | 2.00-18 - 2.04-35  |
| |                                                   | |                                                                                              | | - ``<maxChannels>`` - how many channels will be acquired                    |                    |
| |                                                   | | Python: ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)`` | | - ``<enght>`` - length of the buffer in samples (max 16384)                 |                    |
| |                                                   | |                                                                                              | | - ``<initInt16>, <initDouble>, <initFloat>`` - buffer sample type, set one  |                    |
| |                                                   | |                                                                                              | |   to ``true``, others are ``false``.                                        |                    |
| |                                                   | |                                                                                              | | For Python API specifically. Replaced by functions returning NumPy buffers. |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | - (N/A)                                           | | C: - (look for *free* function online)                                                       | | Free the allocated resources.                                               | 2.00-18 - 2.04-35  |
| |                                                   | |                                                                                              | | - ``<buffer>`` - buffer to be released/freed                                |                    |
| |                                                   | | Python: ``rp_deleteBuffer(<buffer>)``                                                        | | For Python API specifically.                                                |                    |
| |                                                   | |                                                                                              | | Replaced by functions returning NumPy buffers.                              |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+


--------------------
Acquisition trigger
--------------------


**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<source> = {DISABLED, NOW, CH1_PE, CH1_NE, CH2_PE, CH2_NE, EXT_PE, EXT_NE, AWG_PE, AWG_NE}``  Default: ``DISABLED``
- ``<state> = {WAIT, TD}``
- ``<fill_state> = {0, 1}``
- ``<decimated_data_num> = {value in samples}`` (minimum value ``-8192``) Default: ``0``
- ``<time_ns> = {value in ns}`` Default: ``0``
- ``<value> = {value in us}`` Default: ``500``
- ``<voltage> = {value in V}`` Default: ``0``


*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)
- ``<source> = {CH3_PE, CH3_NE, CH4_PE, CH4_NE}``

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``
- Acquisition trigger - ``RP_TRIG_SRC_DISABLED, RP_TRIG_SRC_NOW, RP_TRIG_SRC_CHA_PE, RP_TRIG_SRC_CHA_NE, RP_TRIG_SRC_CHB_PE, RP_TRIG_SRC_CHB_NE, RP_TRIG_SRC_EXT_PE, RP_TRIG_SRC_EXT_NE, RP_TRIG_SRC_AWG_PE, RP_TRIG_SRC_AWG_NE``
- Acquisition trigger state - ``RP_TRIG_STATE_TRIGGERED, RP_TRIG_STATE_WAITING``
- Buffer size - ``ADC_BUFFER_SIZE, DAC_BUFFER_SIZE``


*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``
- Acquisition trigger - ``RP_TRIG_SRC_CHC_PE, RP_TRIG_SRC_CHC_NE, RP_TRIG_SRC_CHD_PE, RP_TRIG_SRC_CHD_NE``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| SCPI                                                   | API, Jupyter                                                                         | DESCRIPTION                                                                   |  ECOSYSTEM              |
+========================================================+======================================================================================+===============================================================================+=========================+
| | ``ACQ:TRig <source>``                                | | C: ``rp_AcqSetTriggerSrc(rp_acq_trig_src_t source)``                               | | Set acquisition trigger source. The options are disabled, trigger           | 1.04-18 and up          |
| | Example:                                             | |                                                                                    | | immediately, or set trigger source & edge.                                  |                         |
| | ``ACQ:TRig CH1_PE``                                  | | Python: ``rp_AcqSetTriggerSrc(<source>)``                                          | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:CH<n> <source>``                          | | C: ``rp_AcqSetTriggerSrcCh(rp_channel_t channel, rp_acq_trig_src_t source)``       | | Set acquisition trigger source. The options are disabled, trigger           | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | immediately, or set trigger source & edge.                                  |                         |
| | ``ACQ:TRig:CH1 CH1_PE``                              | | Python: ``rp_AcqSetTriggerSrcCh(<channel>, <source>)``                             | | Used only in split trigger mode                                             |                         |
| |                                                      | |                                                                                    | | (currently only STEMlab 125-14 4-Input)                                     |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | -                                                    | | C: ``rp_AcqGetTriggerSrc(rp_acq_trig_src_t* source)``                              | | Get acquisition trigger source.                                             | 1.04-18 and up          |
| |                                                      | |                                                                                    | |                                                                             |                         |
| |                                                      | | Python: ``rp_AcqGetTriggerSrc()``                                                  | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:STAT?`` > ``<state>``                     | | C: ``rp_AcqGetTriggerState(rp_acq_trig_state_t* state)``                           | | Get acquisition trigger status. If the trigger is ``DISABLED`` or the       | 1.04-18 and up          |
| | Example:                                             | |                                                                                    | | acquisition is triggered, the state is ``TD``. Otherwise, it is ``WAIT``.   |                         |
| | ``ACQ:TRig:STAT?`` > ``WAIT``                        | | Python: ``rp_AcqGetTriggerState()``                                                | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:STAT:CH<n>?`` > ``<state>``               | | C: ``rp_AcqGetTriggerStateCh(rp_channel_t channel, rp_acq_trig_state_t* state)``   | | Get acquisition trigger status. If the trigger is ``DISABLED`` or the       | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | acquisition is triggered, the state is ``TD``. Otherwise, it is ``WAIT``.   |                         |
| | ``ACQ:TRig:STAT:CH1?`` > ``WAIT``                    | | Python: ``rp_AcqGetTriggerStateCh(<channel>)``                                     | | Used only in split trigger mode                                             |                         |
| |                                                      | |                                                                                    | | (currently only STEMlab 125-14 4-Input)                                     |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:FILL?`` > ``<fill_state>``                | | C: ``rp_AcqGetBufferFillState(bool* state)``                                       | Returns 1 if the buffer is full of data. Otherwise returns 0.                 | 2.00-15 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:FILL?`` > ``1``                           | | Python: ``rp_AcqGetBufferFillState()``                                             |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:FILL:CH<n>?`` > ``<fill_state>``          | | C: ``rp_AcqGetBufferFillStateCh(rp_channel_t channel, bool* state)``               | | Returns 1 if the buffer is full of data. Otherwise returns 0.               | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:FILL:CH1?`` > ``1``                       | | Python: ``rp_AcqGetBufferFillStateCh(<channel>)``                                  | | (currently only STEMlab 125-14 4-Input)                                     |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY <decimated_data_num>``                | | C: ``rp_AcqSetTriggerDelay(int32_t decimated_data_num)``                           | | Set the trigger delay in samples. The triggering moment is by default in    | 1.04-18 and up          |
| | Example:                                             | |                                                                                    | | the middle of acquired buffer (at 8192th sample) (trigger delay set to 0).  |                         |
| | ``ACQ:TRig:DLY 2314``                                | | Python: ``rp_AcqSetTriggerDelay(<decimated_data_num>)``                            | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:CH<n> <decimated_data_num>``          | | C: ``rp_AcqSetTriggerDelayCh(rp_channel_t channel, int32_t decimated_data_num)``   | | Set the trigger delay in samples. The triggering moment is by default in    | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | the middle of acquired buffer (at 8192th sample) (trigger delay set to 0).  |                         |
| | ``ACQ:TRig:DLY:CH1 2314``                            | | Python: ``rp_AcqSetTriggerDelayCh(<channel>,<decimated_data_num>)``                | | Used only in split trigger mode                                             |                         |
| |                                                      | |                                                                                    | | (currently only STEMlab 125-14 4-Input)                                     |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY?`` > ``<decimated_data_num>``         | | C: ``rp_AcqGetTriggerDelay(int32_t* decimated_data_num)``                          | Get the trigger delay in samples.                                             | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:DLY?`` > ``2314``                         | | Python: ``rp_AcqGetTriggerDelay()``                                                |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:CH<n>?`` > ``<decimated_data_num>``   | | C: ``rp_AcqGetTriggerDelayCh(rp_channel_t channel, int32_t* decimated_data_num)``  | | Get the trigger delay in samples.                                           | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:DLY:CH1?`` > ``2314``                     | | Python: ``rp_AcqGetTriggerDelayCh(<channel>)``                                     | | (currently only STEMlab 125-14 4-Input)                                     |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:NS <time_ns>``                        | | C: ``rp_AcqSetTriggerDelayNs(int64_t time_ns)``                                    | | Set the trigger delay in ns. Must be multiple of the board's clock          | 1.04-18 and up          |
| | Example:                                             | |                                                                                    | | resolution (125 MHz clock == 8 ns resolution, 250 MHz == 4 ns resolution).  |                         |
| | ``ACQ:TRig:DLY:NS 128``                              | | Python: ``rp_AcqSetTriggerDelayNs(<time_ns>)``                                     | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:NS:CH<n> <time_ns>``                  | | C: ``rp_AcqSetTriggerDelayNsCh(rp_channel_t channel, int64_t time_ns)``            | | Set the trigger delay in ns. Must be multiple of the board's clock          | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | resolution (125 MHz clock == 8 ns resolution, 250 MHz == 4 ns resolution).  |                         |
| | ``ACQ:TRig:DLY:NS:CH1 128``                          | | Python: ``rp_AcqSetTriggerDelayNsCh(<channel>,<time_ns>)``                         | | Used only in split trigger mode                                             |                         |
| |                                                      | |                                                                                    | | (currently only STEMlab 125-14 4-Input)                                     |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:NS?`` > ``<time_ns>``                 | | C: ``rp_AcqGetTriggerDelayNs(int64_t* time_ns)``                                   | Get the trigger delay in ns.                                                  | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:DLY:NS?`` > ``128`` ns                    | | Python: ``rp_AcqGetTriggerDelayNs()``                                              |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:NS:CH<n>?`` > ``<time_ns>``           | | C: ``rp_AcqGetTriggerDelayNsCh(rp_channel_t channel, int64_t* time_ns)``           | | Get the trigger delay in ns.                                                | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:DLY:NS:CH1?`` > ``128`` ns                | | Python: ``rp_AcqGetTriggerDelayNsCh(<channel>)``                                   | | (currently only STEMlab 125-14 4-Input)                                     |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | -                                                    | | C: ``rp_AcqGetPreTriggerCounter(uint32_t* value)``                                 | | Get the pretrigger sample count (how many samples are in the buffer before  | 1.04-18 and up          |
| |                                                      | |                                                                                    | | the trigger position).                                                      |                         |
| |                                                      | | Python: ``rp_AcqGetPreTriggerCounter()``                                           | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:HYST <voltage>``                          | | C: ``rp_AcqSetTriggerHyst(float voltage)``                                         | Set the trigger hysteresis threshold value in Volts.                          | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:HYST 0.005``                              | | Python: ``rp_AcqSetTriggerHyst(<voltage>)``                                        |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:HYST?`` > ``<voltage>``                   | | C: ``rp_AcqGetTriggerHyst(float* voltage)``                                        | Get the trigger hysteresis threshold value in Volts.                          | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:HYST?`` > ``0.005`` V                     | | Python: ``rp_AcqGetTriggerHyst()``                                                 |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:LEV <voltage>``                           | | C: ``rp_AcqSetTriggerLevel(rp_channel_trigger_t channel, float voltage)``          | Set the trigger level in V.                                                   | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:LEV 0.125 V``                             | | Python: ``rp_AcqSetTriggerLevel(<channel>, <voltage>)``                            |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:LEV:CH<n> <voltage>``                     | | C: ``rp_AcqSetTriggerLevel(rp_channel_trigger_t channel, float voltage)``          | | Set the trigger level in V.                                                 | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:LEV:CH1 0.125 V``                         | | Python: ``rp_AcqSetTriggerLevel(<channel>, <voltage>)``                            | | (currently only STEMlab 125-14 4-Input)                                     |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:LEV?`` > ``<voltage>``                    | | C: ``rp_AcqGetTriggerLevel(rp_channel_trigger_t channel, float* voltage)``         | Get the trigger level in V.                                                   | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:LEV?`` > ``0.123`` V                      | | Python: ``rp_AcqGetTriggerLevel(<channel>)``                                       |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:LEV:CH<n>?`` > ``<voltage>``              | | C: ``rp_AcqGetTriggerLevel(rp_channel_trigger_t channel, float* voltage)``         | | Get the trigger level in V.                                                 | 2.05-37 and up          |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:LEV:CH1?`` > ``0.123`` V                  | | Python: ``rp_AcqGetTriggerLevel(<channel>)``                                       | | (currently only STEMlab 125-14 4-Input)                                     |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:EXT:LEV <voltage>``                       | | C: ``rp_AcqSetTriggerLevel(rp_channel_trigger_t channel, float voltage)``          | Set the external trigger level in V.                                          | 1.04-18 - 2.00-30       |
| | Example:                                             | |                                                                                    | (Only SIGNALlab 250-12)                                                       |                         |
| | ``ACQ:TRig:EXT:LEV 1``                               | | Python: ``rp_AcqSetTriggerLevel(<channel>, <voltage>)``                            |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:EXT:LEV?`` > ``<voltage>``                | | C: ``rp_AcqGetTriggerLevel(rp_channel_trigger_t channel, float* voltage)``         | Get the external trigger level in V.                                          | 1.04-18 - 2.00-30       |
| | Example:                                             | |                                                                                    | (Only SIGNALlab 250-12)                                                       |                         |
| | ``ACQ:TRig:EXT:LEV?`` > ``1``                        | | Python: ``rp_AcqGetTriggerLevel(<channel>)``                                       |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:EXT:DEBouncer:[US] <value>``              | | C: ``rp_AcqSetExtTriggerDebouncerUs(double value)``                                | | Set the external trigger acquisition debouncer in microseconds (value must  | 2.00-15 and up          |
| | Example:                                             | |                                                                                    | | be positive).                                                               |                         |
| | ``ACQ:TRig:EXT:DEBouncer:US 1``                      | | Python: ``rp_AcqSetExtTriggerDebouncerUs(<value>)``                                | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:EXT:DEBouncer:[US]?`` > ``<value>``       | | C: ``rp_AcqGetExtTriggerDebouncerUs(double *value)``                               | | Set the external trigger acquisition debouncer in microseconds.             | 2.00-15 and up          |
| | Example:                                             | |                                                                                    | |                                                                             |                         |
| | ``ACQ:TRig:EXT:DEBouncer:US?`` > ``1``               | | Python: ``rp_AcqGetExtTriggerDebouncerUs()``                                       | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``TRig:EXT:LEV <voltage>``                           | | C: ``rp_SetExternalTriggerLevel(float voltage)``                                   | Set the external trigger level in V.                                          | 2.04-35 and up          |
| | Example:                                             | |                                                                                    | (Only SIGNALlab 250-12)                                                       |                         |
| | ``TRig:EXT:LEV 1``                                   | | Python: ``rp_SetExternalTriggerLevel(<voltage>)``                                  |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``TRig:EXT:LEV?`` > ``<voltage>``                    | | C: ``rp_GetExternalTriggerLevel(float* voltage)``                                  | Get the external trigger level in V.                                          | 2.04-35 and up          |
| | Example:                                             | |                                                                                    | (Only SIGNALlab 250-12)                                                       |                         |
| | ``TRig:EXT:LEV?`` > ``1``                            | | Python: ``rp_GetExternalTriggerLevel()``                                           |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+




---------------
Data pointers
---------------

The data is written into a circular buffer, which is constantly overwritten, until the triggering moment. Consequently, the trigger position can be anywhere inside the circular buffer,
even though it is displayed to happen at approximately 8192nd sample in the acquired data (is affected by the ``ACQ:TRIG:DLY`` command).

**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<pos> = {position inside circular buffer}`` (0 ... 16383)

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+---------------------------------------+-----------------------------------------------------------------------------------+----------------------------------------------------------+--------------------+
| SCPI                                  | API, Jupyter                                                                      | DESCRIPTION                                              |  ECOSYSTEM         |
+=======================================+===================================================================================+==========================================================+====================+
| | ``ACQ:WPOS?`` > ``<pos>``           | | C: ``rp_AcqGetWritePointer(uint32_t* pos)``                                     | | Returns the current position of the write pointer,     | 1.04-18 and up     |
| | Example:                            | |                                                                                 | | i.e the index of the most recent sample in the buffer. |                    |
| | ``ACQ:WPOS?`` > ``1024``            | | Python: ``rp_AcqGetWritePointer()``                                             | |                                                        |                    |
| |                                     | |                                                                                 | |                                                        |                    |
+---------------------------------------+-----------------------------------------------------------------------------------+----------------------------------------------------------+--------------------+
| | ``ACQ:TPOS?`` > ``<pos>``           | | C: ``rp_AcqGetWritePointerAtTrig(uint32_t* pos)``                               | Returns the position where the trigger event appeared.   | 1.04-18 and up     |
| | Example:                            | |                                                                                 |                                                          |                    |
| | ``ACQ:TPOS?`` > ``512``             | | Python: ``rp_AcqGetWritePointerAtTrig()``                                       |                                                          |                    |
| |                                     | |                                                                                 |                                                          |                    |
+---------------------------------------+-----------------------------------------------------------------------------------+----------------------------------------------------------+--------------------+
| | ``ACQ:WPOS:CH<n>?`` > ``<pos>``     | | C: ``rp_AcqGetWritePointerCh(rp_channel_t channel, uint32_t* pos)``             | | Returns the current position of the write pointer,     | 2.05-37 and up     |
| | Example:                            | |                                                                                 | | i.e the index of the most recent sample in the buffer. |                    |
| | ``ACQ:WPOS:CH1?`` > ``1024``        | | Python: ``rp_AcqGetWritePointerCh(<channel>)``                                  | | Used only in split trigger mode                        |                    |
| |                                     | |                                                                                 | | (currently only STEMlab 125-14 4-Input)                |                    |
+---------------------------------------+-----------------------------------------------------------------------------------+----------------------------------------------------------+--------------------+
| | ``ACQ:TPOS:CH<n>?`` > ``<pos>``     | | C: ``rp_AcqGetWritePointerAtTrigCh(rp_channel_t channel, uint32_t* pos)``       | | Returns the position where the trigger event appeared. | 2.05-37 and up     |
| | Example:                            | |                                                                                 | | Used only in split trigger mode                        |                    |
| | ``ACQ:TPOS:CH1?`` > ``512``         | | Python: ``rp_AcqGetWritePointerAtTrigCh(<channel>)``                            | | (currently only STEMlab 125-14 4-Input)                |                    |
| |                                     | |                                                                                 |                                                          |                    |
+---------------------------------------+-----------------------------------------------------------------------------------+----------------------------------------------------------+--------------------+


-----------
Data read
-----------

**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<start_pos>, <end_pos>, <pos> = {0, 1, ..., 16383}``
- ``<buffer>`` Array to store the data into. For Python API use ``rp_createBuffer`` and for C API use *malloc*.
- ``<buffer_size>`` Size of the array for data storage.
- ``<t_pos> = {PRE_TRIG, POST_TRIG, PRE_POST_TRIG}`` Buffer reading direction mode relative to trigger

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| SCPI                                        | API, Jupyter                                                                                                                             | DESCRIPTION                                                                            |  ECOSYSTEM         |
+=============================================+==========================================================================================================================================+========================================================================================+====================+
| | ``ACQ:SOUR<n>:DATA:STArt:End?``           | | C: ``rp_AcqGetDataPosRaw(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, int16_t* buffer, uint32_t* buffer_size)``         | | Read samples from ``start_pos`` to ``end_pos``. For API commands, the buffer for     | 1.04-18 and up     |
| | ``<start_pos>,<end_pos>``                 | |    ``rp_AcqGetDataPosV(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, float* buffer, uint32_t* buffer_size)``             | | data storage and its size must also be provided. Use ``rp_createBuffer`` to allocate |                    |
| | Example:                                  | | Python: ``rp_AcqGetDataPosRaw(<channel>, <start_pos>, <end_pos>, <buffer>, <buffer_size>)``                                            | | data  for Python and *malloc* for C. API commands have two functions to return data  |                    |
| | ``ACQ:SOUR1:DATA:STArt:End? 10,13`` >     | |         ``rp_AcqGetDataPosV(<channel>, <start_pos>, <end_pos>, <buffer>, <buffer_size>)``                                              | | in Volts or RAW.                                                                     |                    |
| | ``{123,231,-231}``                        | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ''                                        | | Python: ``rp_AcqGetDataPosRawNP(channel, start_pos, end_pos, np_buffer)`` (Numpy buffer ``dtype=np.int16``)                            | | Copies the captured buffer data from ``start_pos`` to ``end_pos`` into the passed    | 2.05-37 and up     |
| |                                           | |         ``rp_AcqGetDataPosVNP(channel, start_pos, end_pos, np_buffer)`` (Numpy buffer ``dtype=np.float32``)                            | | NumPy buffer. The length of the copied data must match the ``np_buffer`` length.     |                    |
| |                                           | |                                                                                                                                        | | Faster than the Python functions above.                                              |                    |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | -                                         | | C: ``rp_AcqGetDataRawWithCalib(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)``                                 | | Read ``<size>`` samples from the ``<pos>`` onwards. The data is returned in RAW      | 1.04-18 and up     |
| |                                           | |                                                                                                                                        | | format with calibration applied.                                                     |                    |
| |                                           | | Python: ``rp_AcqGetDataRawWithCalib(<channel>, <pos>, <size>, <buffer>)``                                                              | | Numpy buffer must have the specified ``dtype`` format.                               |                    |
| |                                           | |         ``rp_AcqGetDataRawWithCalibNP(channel, pos, np_buffer)`` (Numpy buffer ``dtype=np.int16``)                                     | | Faster than the Python functions above.                                              |                    |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | -                                         | | C: ``rp_AcqGetNormalizedDataPos(uint32_t pos)``                                                                                        | | Normalizes the ADC buffer position. Returns the modulo operation of ADC buffer size. | 1.04-18 and up     |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
| |                                           | | Python: ``rp_AcqGetNormalizedDataPos(<pos>)``                                                                                          | |                                                                                      |                    |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:STArt:N?``             | | C: ``rp_AcqGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)``                                          | | Read ``size`` samples from the ``<start_pos>`` onwards.                              | 1.04-18 and up     |
| | ``<start_pos>,<size>``                    | |    ``rp_AcqGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)``                                               | |                                                                                      |                    |
| | Example:                                  | | Python: ``rp_AcqGetDataRaw(<channel>, <pos>, <size>, <buffer>)``                                                                       | |                                                                                      |                    |
| | ``ACQ:SOUR1:DATA:STArt:N? 10,3`` >        | |         ``rp_AcqGetDataV(<channel>, <pos>, <size>, <buffer>)``                                                                         | |                                                                                      |                    |
| | ``{1.2,3.2,-1.2}``                        | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ''                                        | | Python: ``rp_AcqGetDataRawNP(channel, pos, np_buffer)`` (Numpy buffer ``dtype=np.int16``)                                              | | Copies the captured buffer data into the passed NumPy buffer from ``pos``            | 2.05-37 and up     |
| |                                           | |         ``rp_AcqGetDataVNP(channel, pos, np_buffer)`` (Numpy buffer ``dtype=np.float32``)                                              | | onwards. The length of the copied data matches the ``np_buffer`` length.             |                    |
| |                                           | |                                                                                                                                        | | Numpy buffer must have the specified ``dtype`` format.                               |                    |
| |                                           | |                                                                                                                                        | | Faster than the Python functions above.                                              |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA?``                     | | C: ``rp_AcqGetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)``                                                   | | Read the full buffer.                                                                | 1.04-18 and up     |
| | Example:                                  | |    ``rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer)``                                                       | | Starting from the oldest sample in the buffer (first sample after trigger delay).    |                    |
| | ``ACQ:SOUR2:DATA?`` >                     | | Python: ``rp_AcqGetOldestDataRaw(<channel>, <size>, <buffer>)``                                                                        | | If the trigger delay is set to zero, it will read the full buffer size starting      |                    |
| | ``{1.2,3.2,...,-1.2}``                    | |         ``rp_AcqGetOldestDataV(<channel>, <size>, <buffer>)``                                                                          | | from the trigger.                                                                    |                    |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ''                                        | | Python: ``rp_AcqGetOldestDataRawNP(channel, np_buffer)`` (Numpy buffer ``dtype=np.int16``)                                             | | Copies the oldest captured buffer data into the passed NumPy buffer.                 | 2.05-37 and up     |
| |                                           | |         ``rp_AcqGetOldestDataVNP(channel, np_buffer)`` (Numpy buffer ``dtype=np.float32``)                                             | | The length of the copied data matches the ``np_buffer`` length.                      |                    |
| |                                           | |                                                                                                                                        | | Numpy buffer must have the specified ``dtype`` format.                               |                    |
| |                                           | |                                                                                                                                        | | Faster than the Python functions above.                                              |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:Old:N? <size>``        | | C: ``rp_AcqGetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)``                                                   | | Read the oldest ``<size>`` samples in the buffer.                                    | 1.04-18 and up     |
| | Example:                                  | |    ``rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer)``                                                       | |                                                                                      |                    |
| | ``ACQ:SOUR2:DATA:Old:N? 3`` >             | | Python: ``rp_AcqGetOldestDataRaw(<channel>, <size>, <buffer>)``                                                                        | |                                                                                      |                    |
| | ``{1.2,3.2,-1.2}``                        | |         ``rp_AcqGetOldestDataV(<channel>, <size>, <buffer>)``                                                                          | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ''                                        | | Python: ``rp_AcqGetOldestDataRawNP(channel, np_buffer)`` (Numpy buffer ``dtype=np.int16``)                                             | | Copies the oldest captured buffer data into the passed NumPy buffer.                 | 2.05-37 and up     |
| |                                           | |         ``rp_AcqGetOldestDataVNP(channel, np_buffer)`` (Numpy buffer ``dtype=np.float32``)                                             | | The length of the copied data matches the ``np_buffer`` length.                      |                    |
| |                                           | |                                                                                                                                        | | Numpy buffer must have the specified ``dtype`` format.                               |                    |
| |                                           | |                                                                                                                                        | | Faster than the Python functions above.                                              |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:LATest:N? <size>``     | | C: ``rp_AcqGetLatestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)``                                                   | | Read the latest ``<size>`` samples in the buffer.                                    | 1.04-18 and up     |
| | Example:                                  | |    ``rp_AcqGetLatestDataV(rp_channel_t channel, uint32_t* size, float* buffer)``                                                       | |                                                                                      |                    |
| | ``ACQ:SOUR1:DATA:LATest:N? 3`` >          | | Python: ``rp_AcqGetLatestDataRaw(<channel>, <size>, <buffer>)``                                                                        | |                                                                                      |                    |
| | ``{1.2,3.2,-1.2}``                        | |         ``rp_AcqGetLatestDataV(<channel>, <size>, <buffer>)``                                                                          | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ''                                        | | Python: ``rp_AcqGetLatestDataRawNP(channel, np_buffer)`` (Numpy buffer ``dtype=np.int16``)                                             | | Copies the latest captured buffer data into the passed NumPy buffer.                 | 2.05-37 and up     |
| |                                           | |         ``rp_AcqGetLatestDataVNP(channel, np_buffer)`` (Numpy buffer ``dtype=np.float32``)                                             | | The length of the copied data matches the ``np_buffer`` length.                      |                    |
| |                                           | |                                                                                                                                        | | Faster than the Python functions above.                                              |                    |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:TRig? <size>,<t_pos>`` | | C: ``rp_AcqGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)``                                          | | Read ``<size>`` samples relative to the trigger, depending on the setting.           | 2.05-37 and up     |
| | Example:                                  | |    ``rp_AcqGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)``                                               | | ``PRE_TRIG``, ``POST_TRIG`` trigger configuration returns ``size`` data samples.     |                    |
| | ``ACQ:SOUR1:DATA:TRig? 3,POST_TRIG`` >    | | Python: ``rp_AcqGetDataRaw(<channel>, <pos>, <size>, <buffer>)``                                                                       | | ``PRE_POST_TRIG`` returns ``size`` * 2 + 1 data samples, including the triggering    |                    |
| | ``{1.2,3.2,-1.2}``                        | |         ``rp_AcqGetDataV(<channel>, <pos>, <size>, <buffer>)``                                                                         | | moment                                                                               |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ''                                        | | Python: ``rp_AcqGetDataRawNP(channel, pos, np_buffer)`` (Numpy buffer ``dtype=np.int16``)                                              | | Copies the captured buffer data into the passed NumPy buffer from ``pos``            | 2.05-37 and up     |
| |                                           | |         ``rp_AcqGetDataVNP(channel, pos, np_buffer)`` (Numpy buffer ``dtype=np.float32``)                                              | | onwards. The length of the copied data matches the ``np_buffer`` length.             |                    |
| |                                           | |                                                                                                                                        | | Numpy buffer must have the specified ``dtype`` format.                               |                    |
| |                                           | |                                                                                                                                        | | Faster than the Python functions above.                                              |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+

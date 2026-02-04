
.. _commands_lcr:

========
LCR mode
========

Functionality overview
------------------------

LCR mode commands enable impedance measurements using Red Pitaya as an LCR meter. These commands support measurement of inductance (L), 
capacitance (C), and resistance (R) in both series and parallel configurations, with optional external LCR extension module support.


Important notes
----------------

* Requires appropriate signal amplitude and frequency for accurate measurements.
* External LCR extension module provides improved measurement range and accuracy.
* Shunt resistor selection affects measurement sensitivity.


Code examples
-----------------

[To be added - examples specific to LCR measurements]


Parameters and command table
-----------------------------

**Parameter options:**

- ``<enable> = {OFF, ON}``  Default: ``ON``
- ``<mode> = {SERIES, PARALLEL}``  Default: ``SERIES``
- ``<ext_mode> = {LCR_EXT, CUSTOM}``  Default: ``LCR_EXT``
- ``<ext_module_shunt> = {S10, S100, S1k, S10k, S100k, S1M}``  Default: ``S10``
- ``<frequency> = {0 ... 62.5e6}`` (in Hertz). Default: ``1000``
- ``<amplitude> = {-1 ... 1}`` (in Volts). Default: ``0.5``
- ``<offset> = {-1 ... 1}`` (in Volts). Default: ``0``
- ``<shunt> = {1 ... 100000000}`` (in Hertz). Default: ``100``
- ``<json>`` Result of measure in JSON format

**Available Jupyter and API macros:**

- *(Future OS release)*


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| SCPI                                      | API, Jupyter                                                     | DESCRIPTION                                                                         |  ECOSYSTEM         |
+===========================================+==================================================================+=====================================================================================+====================+
| | ``LCR:START``                           | | C: ``lcrApp_LcrRun()``                                         | | Starts the LCR processing thread and resets settings to default.                  | 2.05-37 and up     |
| | Example:                                | |                                                                | | Settings for the generator need to be made after starting the thread.             |                    |
| | ``LCR:START``                           | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:START:GEN``                       | | C: ``lcrApp_LcrReset()``                                       | | Starts the generator on out 1 with the specified settings.                        | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:START:GEN``                       | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:STOP``                            | | C: ``lcrApp_LcrStop()``                                        | | Stops the LCR thread.                                                             | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:STOP``                            | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:RESET``                           | | C: ``lcrApp_LcrReset()``                                       | | Resets default settings in LCR api.                                               | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:RESET``                           | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:MEASURE?`` > ``<json>``           | | C: ``lcrApp_LcrCopyParams(lcr_main_data_t *data)``             | | Returns calculations of the last processed data wrapped in json format.           | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:MEASURE?`` > ``{...}``            | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:FREQ <frequency>``                | | C: ``lcrApp_LcrSetFrequency(float frequency)``                 | | Sets the frequency for the generator.                                             | 2.05-37 and up     |
| | Example:                                | |                                                                | | To apply all the settings you need to call the command that starts the generator. |                    |
| | ``LCR:FREQ 1000``                       | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:FREQ?`` > ``<frequency>``         | | C: ``lcrApp_LcrGetFrequency(float *frequency)``                | | Returns the current frequency setting of the generator.                           | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:FREQ?`` > ``1000``                | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:VOLT <amplitude>``                | | C: ``lcrApp_LcrSetAmplitude(float volt)``                      | | Sets the amplitude for the generator. The default value is 0.5V.                  | 2.05-37 and up     |
| | Example:                                | |                                                                | | You can set any value up to 1V.  But you need to take into account that when      |                    |
| | ``LCR:VOLT 1000``                       | | Python:                                                        | | working with LCR, the position of the jumpers should be in the Hi-Z position.     |                    |
| |                                         | |                                                                | | Therefore, amplitude values greater than 0.5 will not be                          |                    |
| |                                         | |                                                                | | correct for most measurements.                                                    |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:VOLT?`` > ``<amplitude>``         | | C: ``lcrApp_LcrGetAmplitude(float *volt)``                     | | Returns the current amplitude setting.                                            | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:VOLT?`` > ``1000``                | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:VOLT:OFFS <offset>``              | | C: ``lcrApp_LcrSetOffset(float offset)``                       | | Sets the signal offset of the generator.                                          | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:VOLT:OFFS 0``                     | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:VOLT:OFFS?`` > ``<offset>``       | | C: ``lcrApp_LcrGetOffset(float *offset)``                      | | Returns the signal offset of the generator.                                       | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:VOLT:OFFS?`` > ``0``              | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:SHUNT <ext_module_shunt>``        | | C: ``lcrApp_LcrSetShunt(lcr_shunt_t shunt)``                   | | Sets the shunt on the expansion board for the LCR.                                | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:SHUNT S10``                       | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:SHUNT?`` > ``<ext_module_shunt>`` | | C: ``lcrApp_LcrGetShunt(lcr_shunt_t *shunt)``                  | | Returns the current shunt value. Even in AUTO shunt mode.                         | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:SHUNT?`` > ``S10``                | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:SHUNT:CUSTOM <shunt>``            | | C: ``lcrApp_LcrSetCustomShunt(int shunt)``                     | | Sets the shunt value when the expansion card is not in use.                       | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:SHUNT:CUSTOM 10``                 | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:SHUNT:CUSTOM?`` > ``<shunt>``     | | C: ``lcrApp_LcrGetCustomShunt(int *shunt)``                    | | Sets the shunt value when the expansion card is not in use.                       | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:SHUNT:CUSTOM?`` > ``10``          | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:SHUNT:MODE <ext_mode>``           | | C: ``lcrApp_LcrSetShuntMode(lcr_shunt_mode_t shunt_mode)``     | | Sets the usage mode. With and without expansion board.                            | 2.05-37 and up     |
| | Example:                                | |                                                                | | Must be set before starting the LCR.                                              |                    |
| | ``LCR:SHUNT:MODE LCR_EXT``              | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:SHUNT:MODE?`` > ``<ext_mode>``    | | C: ``lcrApp_LcrGetShuntMode(lcr_shunt_mode_t *shunt_mode)``    | | Returns the current shunt operation mode.                                         | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:SHUNT:MODE?`` > ``LCR_EXT``       | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:SHUNT:AUTO <enable>``             | | C: ``lcrApp_LcrSetShuntIsAuto(bool isShuntAuto)``              | | Enables or disables the automatic shunt selection mode for the expansion board.   | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:SHUNT:AUTO OFF``                  | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:CIRCUIT <mode>``                  | | C: ``lcrApp_LcrSetMeasSeries(bool series)``                    | | Sets the measuring mode to serial or parallel. Affects the parameters: L, C, R.   | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:CIRCUIT SERIES``                  | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:CIRCUIT?`` > ``<mode>``           | | C: ``lcrApp_LcrGetMeasSeries(bool *series)``                   | | Returns the measurement mode.                                                     | 2.05-37 and up     |
| | Example:                                | |                                                                |                                                                                     |                    |
| | ``LCR:CIRCUIT?`` > ``SERIES``           | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| | ``LCR:EXT:MODULE?`` > ``<enable>``      | | C: ``lcrApp_LcrIsModuleConnected(bool *state)``                | | Returns the status of the expansion board.                                        | 2.05-37 and up     |
| | Example:                                | |                                                                | | If the value is ON, the board is connected.                                       |                    |
| | ``LCR:EXT:MODULE?`` > ``ON``            | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_lcr>`
* :ref:`Back to command list <command_list>`

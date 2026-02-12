
.. _commands_temp_prot:

=================================
Temperature protection and power
=================================

Functionality overview
------------------------

Temperature protection and power commands monitor and control thermal management on SIGNALlab 250-12. These commands provide temperature 
readings, fan control, and automatic thermal protection to prevent hardware damage from overheating.


Important notes
----------------

* These commands are available only on SIGNALlab 250-12.
* Temperature protection automatically throttles or shuts down outputs when thermal limits are exceeded (85 degrees Celsius).
* Monitor temperature regularly during high-power operation.


Code examples
-----------------

[To be added - examples specific to temperature monitoring and protection]


Parameters and command table
-----------------------------

**Parameter options:**

- ``<enable> = {true, false}``

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| SCPI                                | API, Jupyter                                                                | DESCRIPTION                                                                        |  ECOSYSTEM         |
+=====================================+=============================================================================+====================================================================================+====================+
| | -                                 | | C++: ``rp_SetEnableTempProtection(rp_channel_t channel, bool enable)``    | | Enable/disable the DAC overheating protection mode for the specified fast analog | 1.04-18 and up     |
| |                                   | |                                                                           | | output (SIGNALlab 250-12 only).                                                  |                    |
| |                                   | | Python: ``rp_SetEnableTempProtection(<channel>, <enable>)``               | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetEnableTempProtection(rp_channel_t channel, bool* enable)``   | | Get the Enable/disable DAC overheating protection mode setting for the specified | 1.04-18 and up     |
| |                                   | |                                                                           | | fast analog output (SIGNALlab 250-12 only).                                      |                    |
| |                                   | | Python: ``rp_GetEnableTempProtection(channel)``                           | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_SetLatchTempAlarm(rp_channel_t channel, bool status)``          | | Reset the flag indicating that the DAC is overheated for the specified fast      | 1.04-18 and up     |
| |                                   | |                                                                           | | analog output (SIGNALlab 250-12 only).                                           |                    |
| |                                   | | Python: ``rp_SetLatchTempAlarm(<channel>, <status>)``                     | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetLatchTempAlarm(rp_channel_t channel, bool* status)``         | | Return the flag status indicating that the DAC is overheated for the specified   | 1.04-18 and up     |
| |                                   | |                                                                           | | fast analog output (SIGNALlab 250-12 only).                                      |                    |
| |                                   | | Python: ``rp_GetLatchTempAlarm(<channel>)``                               | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetRuntimeTempAlarm(rp_channel_t channel, bool* status)``       | | Returns the current DAC overheat status in real time (SIGNALlab 250-12 only).    | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetRuntimeTempAlarm(<channel>)``                             | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetCPUTemperature(uint32_t* raw)``                              | | Returns current CPU temperature.                                                 | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetCPUTemperature()``                                        | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetPowerI4(uint32_t* raw, float* value)``                       | | Returns the value from analog input AI4. For testing 5V line power.              | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetPowerI4()``                                               | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetPowerVCCPINT(uint32_t* raw, float* value)``                  | | Returns the value from VCCPINT(1.0V).                                            | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetPowerVCCPINT()``                                          | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetPowerVCCPAUX(uint32_t* raw, float* value)``                  | | Returns the value from VCCPAUX(1.8V).                                            | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetPowerVCCPAUX()``                                          | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetPowerVCCBRAM(uint32_t* raw, float* value)``                  | | Returns the value from VCCBRAM(1.0V).                                            | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetPowerVCCBRAM()``                                          | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetPowerVCCINT(uint32_t* raw, float* value)``                   | | Returns the value from VCCINT(1.0V).                                             | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetPowerVCCINT()``                                           | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetPowerVCCAUX(uint32_t* raw, float* value)``                   | | Returns the value from VCCAUX(1.8V).                                             | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetPowerVCCAUX()``                                           | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C++: ``rp_GetPowerVCCDDR(uint32_t* raw, float* value)``                   | | Returns the value from VCCDDR(1.5V).                                             | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetPowerVCCDDR()``                                           | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_temp_prot>`
* :ref:`Back to command list <command_list>`

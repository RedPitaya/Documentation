
.. _commands_analog:

=========================
Analog Inputs and Outputs
=========================

Functionality overview
------------------------

Analog I/O commands control Red Pitaya's slow analog channels on the extension connector. These provide DC voltage measurements (0-3.5V inputs) and generation (0-1.8V outputs) for interfacing with sensors, control circuits, and other analog peripherals.


Important notes
----------------

* Analog inputs: 0 to +3.5V range (12-bit resolution).
* Analog outputs: 0 to +1.8V range (12-bit resolution).
* Not to be confused with fast RF inputs/outputs used for signal acquisition and generation.


Code examples
-----------------

Here are some examples of how to use the analog I/O commands on Red Pitaya:

* :ref:`Analog examples <examples_analog>`.


Parameters and command table
-----------------------------

**Parameter options:**

- ``<ain> = {AIN0, AIN1, AIN2, AIN3}``
- ``<aout> = {AOUT0, AOUT1, AOUT2, AOUT3}``
- ``<pin> = {ain, aout}``
- ``<value> = {value in Volts}``

**Available Jupyter and API macros:**

- Analog outputs - ``RP_AOUT0, RP_AOUT1, ..., RP_AOUT3``
- Analog inputs - ``RP_AIN0, RP_AIN1, ..., RP_AIN3``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| SCPI                                  | API, Jupyter                                                                       | DESCRIPTION                                                                       |  ECOSYSTEM         |
+=======================================+====================================================================================+===================================================================================+====================+
| | ``ANALOG:RST``                      | | C: ``rp_ApinReset()``                                                            | Sets analog outputs to default values (0 V).                                      | 1.04-18 and up     |
| | Examples:                           | |                                                                                  |                                                                                   |                    |
| | ``ANALOG:RST``                      | | Python: ``rp_ApinReset()``                                                       |                                                                                   |                    |
| |                                     | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``ANALOG:PIN <pin>,<value>``        | | C: ``rp_ApinSetValue(rp_apin_t pin, float value)``                               | | Set the analog voltage on the slow analog outputs.                              | 1.04-18 and up     |
| | Examples:                           | |    ``rp_ApinSetValueRaw(rp_apin_t pin, uint32_t value)``                         | | The voltage range of slow analog outputs is: 0 - 1.8 V                          |                    |
| | ``ANALOG:PIN AOUT2,1.34``           | | Python: ``rp_ApinSetValue(<pin>, <value>)``                                      |                                                                                   |                    |
| |                                     | |         ``rp_ApinSetValueRaw(<pin>, <value>)``                                   |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``ANALOG:PIN? <pin>`` > ``<value>`` | | C: ``rp_ApinGetValue(rp_apin_t pin, float* value, uint32_t* raw)``               | | Read the analog voltage from the slow analog inputs.                            | 1.04-18 and up     |
| | Examples:                           | |    ``rp_ApinGetValueRaw(rp_apin_t pin, uint32_t* value)``                        | | The voltage range of slow analog inputs is: 0 - 3.3 V                           |                    |
| | ``ANALOG:PIN? AOUT2`` > ``1.34``    | | Python: ``rp_ApinGetValue(<pin>)``                                               |                                                                                   |                    |
| | ``ANALOG:PIN? AIN1`` > ``1.12``     | |         ``rp_ApinGetValueRaw(<pin>)``                                            |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_ApinGetRange(rp_apin_t pin, float* min_val, float* max_val)``            | Get voltage range of the specified analog pin.                                    | 1.04-18 and up     |
| |                                     | |                                                                                  |                                                                                   |                    |
| |                                     | | Python: ``rp_ApinGetRange(<pin>)``                                               |                                                                                   |                    |
| |                                     | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_AIpinGetValue(int unsigned pin, float* value, uint32_t* raw)``           | Get the analog voltage on the slow analog inputs (Volts or RAW).                  | 1.04-18 and up     |
| |                                     | |    ``rp_AIpinGetValueRaw(int unsigned pin, uint32_t* value)``                    |                                                                                   |                    |
| |                                     | | Python: ``rp_AIpinGetValue(<pin>)``                                              |                                                                                   |                    |
| |                                     | |         ``rp_AIpinGetValueRaw(<pin>)``                                           |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_AOpinSetValue(int unsigned pin, float value)``                           | Set the output voltage on slow analog outputs.                                    | 1.04-18 and up     |
| |                                     | |    ``rp_AOpinSetValueRaw(int unsigned pin, uint32_t value)``                     |                                                                                   |                    |
| |                                     | | Python: ``rp_AOpinSetValue(<pin>, <value>)``                                     |                                                                                   |                    |
| |                                     | |         ``rp_AOpinSetValueRaw(<pin>, <value>)``                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_AOpinGetValue(int unsigned pin, float* value, uint32_t* raw)``           | Get the output voltage on slow analog outputs.                                    | 1.04-18 and up     |
| |                                     | |    ``rp_AOpinGetValueRaw(int unsigned pin, uint32_t* value)``                    |                                                                                   |                    |
| |                                     | | Python: ``rp_AOpinGetValue(<pin>)``                                              |                                                                                   |                    |
| |                                     | |         ``rp_AOpinGetValueRaw(<pin>)``                                           |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_AOpinGetRange(int unsigned pin, float* min_val,  float* max_val)``       | Get voltage range of the specified analog output pin.                             | 1.04-18 and up     |
| |                                     | |                                                                                  |                                                                                   |                    |
| |                                     | | Python: ``rp_AOpinGetRange(<pin>)``                                              |                                                                                   |                    |
| |                                     | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_analog>`
* :ref:`Back to command list <command_list>`
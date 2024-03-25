.. _command_list:

********************************************
List of supported SCPI & API commands
********************************************

Here is a list of all available SCPI, API, and JupyterLab commands. The commands are organized into tables by functionality. Each table row represents the same command in SCPI, Python API, C API, and JupyterLAB.
The Jupyter commands are identical to Python API commands, so please refer to them. In the final two columns is a command description and ecosystem version in which the command first appeared.

At the beginning of each table are all command parameter options and available macros.

For API commands you can find a detailed description in these C header files:

- |API_header|


.. |API_header| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya/tree/master/rp-api/api/include" target="_blank">Red Pitaya GitHub API header files</a>


How to find all available SCPI commands per OS version?
========================================================

Use the ``SYSTem:Help?`` (IN DEV) SCPI command, which lists all available SCPI commands.

You can also find all SCPI commands that the board will accept depending on the Red Pitaya OS version here:

- Latest Beta OS: |all_os_scpi_commands|

For all other Red Pitaya OS versions, go to the link above and change the branch version to:

- 2.00-30 - Branch 2024.1 *(file ends in .cpp)*
- 2.00-23 - Branch 2023.3 *(file ends in .cpp)*
- 2.00-18 - Branch 2023.2 *(file ends in .c)*
- 2.00-15 - Branch 2023.1 - |all_os_scpi_commands_2.00-15| *(file ends in .c)*
- 1.04-28 - Branch 2022.2 *(file ends in .c)*
- 1.04-18 - Branch 2022.1 *(file ends in .c)*

.. image:: img/All_os_scpi_commands.png
   :width: 500


.. |all_os_scpi_commands| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/scpi-server/src/scpi-commands.cpp" target="_blank">Red Pitaya GitHub - scpi-server/src/scpi-commands.cpp</a>

.. |all_os_scpi_commands_2.00-15| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/Release-2023.1/scpi-server/src/scpi-commands.c" target="_blank">Red Pitaya GitHub 2023.1- scpi-server/src/scpi-commands.c</a>



.. _commands_init:

=========================
Initialization commands
=========================

Table of correlated SCPI and API commands for the Red Pitaya.

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+------------------------------------------------------+---------------------------------------------+-----------------------------------------------------------+--------------------+
| SCPI                                                 | API, Jupyter                                | DESCRIPTION                                               |  ECOSYSTEM         |
+======================================================+=============================================+===========================================================+====================+
| | -                                                  | | C: ``rp_Init()``                          | Initializes and enables the command interface.            | 1.04-18 and up     |
| |                                                    | |                                           |                                                           |                    |
| |                                                    | | Python: ``rp_Init()``                     |                                                           |                    |
| |                                                    | |                                           |                                                           |                    |
+------------------------------------------------------+---------------------------------------------+-----------------------------------------------------------+--------------------+
| | -                                                  | | C: ``rp_IsApiInit()``                     | Check whether the API interface is initialized.           | 1.04-18 and up     |
| |                                                    | |                                           |                                                           |                    |
| |                                                    | | Python: ``rp_IsApiInit()``                |                                                           |                    |
| |                                                    | |                                           |                                                           |                    |
+------------------------------------------------------+---------------------------------------------+-----------------------------------------------------------+--------------------+
| | -                                                  | | C: ``rp_Release()``                       | Release command interface resources.                      | 1.04-18 and up     |
| |                                                    | |                                           |                                                           |                    |
| |                                                    | | Python: ``rp_Release()``                  |                                                           |                    |
| |                                                    | |                                           |                                                           |                    |
+------------------------------------------------------+---------------------------------------------+-----------------------------------------------------------+--------------------+
| | -                                                  | | C: ``rp_Reset()``                         | | Resets digital and analog pin settings as well as       | 1.04-18 and up     |
| |                                                    | |                                           | | generation and acquisition settings to default values.  |                    |
| |                                                    | | Python: ``rp_Reset()``                    | |                                                         |                    |
| |                                                    | |                                           | |                                                         |                    |
+------------------------------------------------------+---------------------------------------------+-----------------------------------------------------------+--------------------+
| | -                                                  | | C: ``rp_Reset()``                         | | Resets digital and analog pin settings as well as       | 1.04-18 and up     |
| |                                                    | |                                           | | generation and acquisition settings to default values.  |                    |
| |                                                    | | Python: ``rp_Reset()``                    | |                                                         |                    |
| |                                                    | |                                           | |                                                         |                    |
+------------------------------------------------------+---------------------------------------------+-----------------------------------------------------------+--------------------+


.. _commands_board:

======================
Board control commands
======================

**Parameter options:**

- ``<year> = {1900, ...}`` Default: ``OS release date and time``
- ``<month> = {1, 12}``
- ``<day> = {1, 31}``
- ``<hours> = {0, 23}``
- ``<minutes> = {0, 59}``
- ``<seconds> = {0, 59}``
- ``<log_mode> = {OFF, CONSOLE, SYSLOG}``
- ``<board_id> = {0, 15}``
- ``<enable> = {true, false}``
- ``<errorCode> = {RP_OK, RP_EOED, RP_EOMD, RP_ECMD, RP_EMMD, RP_EUMD, RP_EOOR, RP_ELID, RP_EMRO, RP_EWIP, RP_EPN, RP_UIA, RP_FCA,``
- ``<errorCode> =  RP_RCA, RP_BTS, RP_EIPV, RP_EUF, RP_ENN, RP_EFOB, RP_EFCB, RP_EABA, RP_EFRB, RP_EFWB, RP_EMNC, RP_NOTS}``

**Available Jupyter and API macros:**

- Red Pitaya states and errors:
    - ``RP_OK`` - OK
    - ``RP_EOED`` - Failed to Open EEPROM Device.
    - ``RP_EOMD`` - Failed to open memory device.
    - ``RP_ECMD`` - Failed to close memory device.
    - ``RP_EMMD`` - Failed to map memory device.
    - ``RP_EUMD`` - Failed to unmap memory device.
    - ``RP_EOOR`` - Value out of range.
    - ``RP_ELID`` - LED input direction is not valid.
    - ``RP_EMRO`` - Modifying read only filed is not allowed.
    - ``RP_EWIP`` - Writing to input pin is not valid.
    - ``RP_EPN`` - Invalid Pin number.
    - ``RP_UIA`` - Uninitialized Input Argument.
    - ``RP_FCA`` - Failed to Find Calibration Parameters.
    - ``RP_RCA`` - Failed to Read Calibration Parameters.
    - ``RP_BTS`` - Buffer too small
    - ``RP_EIPV`` - Invalid parameter value
    - ``RP_EUF`` - Unsupported Feature
    - ``RP_ENN`` - Data not normalized
    - ``RP_EFOB`` - Failed to open bus
    - ``RP_EFCB`` - Failed to close bus
    - ``RP_EABA`` - Failed to acquire bus access
    - ``RP_EFRB`` - Failed to read from the bus
    - ``RP_EFWB`` - Failed to write to the bus

..    - ``RP_EMNC`` -
..    - ``RP_NOTS`` -

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| SCPI                                                 | API, Jupyter                                     | DESCRIPTION                                               |  ECOSYSTEM         |
+======================================================+==================================================+===========================================================+====================+
| | ``RP:LOGmode <log_mode>``                          | | -                                              | Enables scpi-server log output mode.                      | 1.04-18 and up     |
| | Examples:                                          | |                                                |                                                           |                    |
| | ``RP:LOGmode SYSLOG``                              | |                                                |                                                           |                    |
| |                                                    | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:TIME <hours>,<minutes>,<seconds>``        | | -                                              | Sets the time on the board.                               | 2.00-18 and up     |
| | Examples:                                          | |                                                |                                                           |                    |
| | ``SYSTem:TIME 16:12:45``                           | |                                                |                                                           |                    |
| | ``SYST:TIME 11:23:01``                             | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:TIME?`` > ``time``                        | | -                                              | Returns the current time on the board.                    | 2.00-18 and up     |
| | Examples:                                          | |                                                |                                                           |                    |
| | ``SYSTem:TIME?`` > ``16:12:45``                    | |                                                |                                                           |                    |
| | ``SYST:TIME?`` > ``11:23:01``                      | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:DATE <year>,<month>,<day>``               | | -                                              | Sets the date on the board.                               | 2.00-18 and up     |
| | Examples:                                          | |                                                |                                                           |                    |
| | ``SYSTem:DATE 2023-04-04``                         | |                                                |                                                           |                    |
| | ``SYST:DATE 2002-12-29``                           | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:DATE?`` > ``date``                        | | -                                              | Returns the current date on the board.                    | 2.00-18 and up     |
| | Examples:                                          | |                                                |                                                           |                    |
| | ``SYSTem:DATE?`` > ``2023-04-04``                  | |                                                |                                                           |                    |
| | ``SYST:DATE?`` > ``2002-12-29``                    | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:BRD:ID?`` > ``<board_id>``                | | C: ``rp_IdGetID(uint32_t *id)``                | Returns the Red Pitaya board ID.                          | 2.00-18 and up     |
| | Examples:                                          | |                                                |                                                           |                    |
| | ``SYSTem:BRD:ID?`` > ``1``                         | | Python: ``rp_IdGetID()``                       |                                                           |                    |
| |                                                    | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:BRD:Name?`` > ``board name``              | | C: ``const char* rp_GetVersion()``             | Returns the Red Pitaya board version.                     | 2.00-18 and up     |
| | Examples:                                          | |                                                |                                                           |                    |
| | ``SYSTem:BRD:Name?`` > ``STEMlab 125-14 v1.0``     | | Python: ``rp_GetVersion()``                    |                                                           |                    |
| |                                                    | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | ``SYSTem:Help?`` > ``<List of SCPI commands>``     | | -                                              | | Returns a list of all commands                          | 2.00-35 and up     |
| | Examples:                                          | |                                                | | that the SCPI server can process.                       |                    |
| | ``SYSTem:Help?`` > ``*CLS\n*ESE\n...``             | |                                                |                                                           |                    |
| |                                                    | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | -                                                  | | C: ``rp_IdGetDNA(uint64_t *dna)``              | Returns the unique DNA code of the FPGA chip.             | 2.00-18 and up     |
| |                                                    | |                                                |                                                           |                    |
| |                                                    | | Python: ``rp_IdGetDNA()``                      |                                                           |                    |
| |                                                    | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | -                                                  | | C: ``const char* rp_GetError(int errorCode)``  | Returns the description of the input error code.          | 2.00-18 and up     |
| |                                                    | |                                                |                                                           |                    |
| |                                                    | | Python: ``rp_GetError(<errorCode>)``           |                                                           |                    |
| |                                                    | |                                                |                                                           |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+
| | -                                                  | | C: ``rp_EnableDigitalLoop(bool enable)``       | | Enables/disables the Digital Loop (internal FPGA        | 2.00-18 and up     |
| |                                                    | |                                                | | connection between fast analog inputs and outputs).     |                    |
| |                                                    | | Python: ``rp_EnableDigitalLoop(<enable>)``     | |                                                         |                    |
| |                                                    | |                                                | |                                                         |                    |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+--------------------+




.. _commands_digital:

==============
LEDs and GPIOs
==============

**Parameter options:**

- ``<dir> = {OUT,IN}``
- ``<gpio> = {{DIO0_P...DIO7_P}, {DIO0_N...DIO7_N}}``
- ``<led> = {LED0...LED8}``
- ``<pin> = {gpio, led}``
- ``<state> = {0,1}``
- ``<reg_state> = {0b00000000}`` - One LED/DIO per bit.  *(10 bit DIO register on SDRlab and STEMlab 4-Input)*
- ``<reg_direction> = {0b00000000}`` - One DIO per bit.  *(10 bit DIO register on SDRlab and STEMlab 4-Input)*


**Available Jupyter and API macros:**

- States - ``RP_LOW, RP_HIGH``
- Directions - ``RP_IN, RP_OUT``
- LEDs - ``RP_LED0, RP_LED1, ..., RP_LED7``
- DIOx_P - ``RP_DIO0_P, RP_DIO1_P, ..., RP_DIO7_P`` *Goes up to 9 on SDRlab and STEMlab 4-Input*
- DIOx_N - ``RP_DIO0_N, RP_DIO1_N, ..., RP_DIO7_N`` *Goes up to 9 on SDRlab and STEMlab 4-Input*


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| SCPI                                  | API, Jupyter                                                                       | DESCRIPTION                                                                       |  ECOSYSTEM         |
+=======================================+====================================================================================+===================================================================================+====================+
| | ``DIG:RST``                         | | C: ``rp_DpinReset()``                                                            | | Sets digital pins to default values. Pins DIO1_P - DIO7_P,                      | 1.04-18 and up     |
| | Examples:                           | |                                                                                  | | RP_DIO0_N - RP_DIO7_N are set all INPUT and to LOW. LEDs are set to LOW/OFF.    |                    |
| | ``DIG:RST``                         | | Python: ``rp_DpinReset()``                                                       | |                                                                                 |                    |
| |                                     | |                                                                                  | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN:DIR <dir>,<gpio>``        | | C: ``rp_DpinSetDirection(rp_dpin_t pin, rp_pinDirection_t direction)``           | Set the direction of digital pins to output or input.                             | 1.04-18 and up     |
| | Examples:                           | |                                                                                  |                                                                                   |                    |
| | ``DIG:PIN:DIR OUT,DIO0_N``          | | Python: ``rp_DpinSetDirection(<pin>, <direction>)``                              |                                                                                   |                    |
| | ``DIG:PIN:DIR IN,DIO1_P``           | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN:DIR? <gpio>``             | | C: ``rp_DpinGetDirection(rp_dpin_t pin, rp_pinDirection_t* direction)``          | Get digital input output pin direction.                                           | 1.04-18 and up     |
| | Examples:                           | |                                                                                  |                                                                                   |                    |
| | ``DIG:PIN:DIR? DIO0_N``             | | Python: ``rp_DpinGetDirection(<pin>)``                                           |                                                                                   |                    |
| | ``DIG:PIN:DIR? DIO1_P``             | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN <pin>,<state>``           | | C: ``rp_DpinSetState(rp_dpin_t pin, rp_pinState_t state)``                       | | Set the state of digital outputs to 1 (HIGH) or 0 (LOW).                        | 1.04-18 and up     |
| | Examples:                           | |                                                                                  | | Returns a 1 (HIGH) if the pin is floating.                                      |                    |
| | ``DIG:PIN DIO0_N,1``                | | Python: ``rp_DpinSetState(<pin>, <state>)``                                      | |                                                                                 |                    |
| | ``DIG:PIN LED2,1``                  | |                                                                                  | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN? <pin>`` > ``<state>``    | | C: ``rp_DpinGetState(rp_dpin_t pin, rp_pinState_t* state)``                      | Get state of digital inputs and outputs.                                          | 1.04-18 and up     |
| | Examples:                           | |                                                                                  |                                                                                   |                    |
| | ``DIG:PIN? DIO0_N``                 | | Python: ``rp_DpinGetState(<pin>)``                                               |                                                                                   |                    |
| | ``DIG:PIN? LED2``                   | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_LEDSetState(uint32_t reg_state)``                                        | | Set the state of the 8-bit LED register. Each bit corresponds to the state      | 1.04-18 and up     |
| |                                     | |                                                                                  | | of one LED.                                                                     |                    |
| |                                     | | Python: ``rp_LEDSetState(<reg_state>)``                                          | |                                                                                 |                    |
| |                                     | |                                                                                  | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_LEDGetState(uint32_t *reg_state)``                                       | | Get the state of the 8-bit LED register. Each bit corresponds to the state      | 1.04-18 and up     |
| |                                     | |                                                                                  | | of one LED.                                                                     |                    |
| |                                     | | Python: ``rp_LEDGetState()``                                                     | |                                                                                 |                    |
| |                                     | |                                                                                  | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_GPIOnSetDirection(uint32_t reg_direction)``                              | | Set the state of the DIO_N or DIO_P direction register. Each bit corresponds    | 1.04-18 and up     |
| |                                     | |    ``rp_GPIOnSetDirection(uint32_t reg_direction)``                              | | to the direction of one DIO_N or DIO_P pin.                                     |                    |
| |                                     | | Python: ``rp_GPIOnSetDirection(<reg_direction>)``                                | |                                                                                 |                    |
| |                                     | |         ``rp_GPIOpSetDirection(<reg_direction>)``                                | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_GPIOnGetDirection(uint32_t *reg_direction)``                             | | Get the state of the DIO_N or DIO_P direction register. Each bit corresponds    | 1.04-18 and up     |
| |                                     | |    ``rp_GPIOpGetDirection(uint32_t *reg_direction)``                             | | to the direction of one DIO_N or DIO_P pin.                                     |                    |
| |                                     | | Python: ``rp_GPIOnGetDirection()``                                               | |                                                                                 |                    |
| |                                     | |         ``rp_GPIOpGetDirection()``                                               | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_GPIOnSetState(uint32_t reg_state)``                                      | | Set the state of the DIO_N or DIO_P state register. Each bit corresponds        | 1.04-18 and up     |
| |                                     | |    ``rp_GPIOpSetState(uint32_t reg_state)``                                      | | to the state of one DIO_N or DIO_P pin.                                         |                    |
| |                                     | | Python: ``rp_GPIOnSetState(<reg_state>)``                                        | |                                                                                 |                    |
| |                                     | |         ``rp_GPIOpSetState(<reg_state>)``                                        | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C: ``rp_GPIOnGetState(uint32_t *state)``                                         | | Get the state of the DIO_N or DIO_P state register. Each bit corresponds        | 1.04-18 and up     |
| |                                     | |    ``rp_GPIOpGetState(uint32_t *state)``                                         | | to the state of one DIO_N or DIO_P pin.                                         |                    |
| |                                     | | Python: ``rp_GPIOnGetState()``                                                   | |                                                                                 |                    |
| |                                     | |         ``rp_GPIOpGetState()``                                                   | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+



.. _commands_analog:

=========================
Analog Inputs and Outputs
=========================

**Parameter options:**

- ``<ain> = {AIN0, AIN1, AIN2, AIN3}``
- ``<aout> = {AOUT0, AOUT1, AOUT2, AOUT3}``
- ``<pin> = {ain, aout}``
- ``<value> = {value in Volts}``

**Available Jupyter and API macros:**

- Analog outputs - ``RP_AOUT0, RP_AOUT1, ..., RP_AOUT3``
- Analog inputs - ``RP_AIN0, RP_AIN1, ..., RP_AIN3``


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

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



.. _commands_daisy:

===============================
Daisy chain clocks and triggers
===============================

**Parameter options:**

- ``<state> = {OFF, ON}``
- ``<mode> = {ADC, DAC}``
- ``<enable> = {true, false}``

**Available Jupyter and API macros:**

- Shared trigger source - ``OUT_TR_ADC, OUT_TR_DAC``


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

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
| | ``DAISY:TRIG_O:ENable <state>``         | | C: ``rp_SetDpinEnableTrigOutput(bool enable)``                                   | | Turns GPION_0 into trigger output for selected source - acquisition or generation.                       | 2.00-15 - 2.00-30             |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRIG_O:ENable ON``              | | Python: ``rp_SetDpinEnableTrigOutput(<enable>)``                                 |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRig:Out:ENable <state>``       | | C: ``rp_SetDpinEnableTrigOutput(bool enable)``                                   | | Turns GPION_0 into trigger output for selected source - acquisition or generation.                       | 2.00-35 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRig:Out:ENable ON``            | | Python: ``rp_SetDpinEnableTrigOutput(<enable>)``                                 |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRIG_O:ENable?`` > ``<state>``  | | C: ``rp_GetDpinEnableTrigOutput(bool *state)``                                   | | Returns the current mode state for GPION_0. If true, then the pin mode works as a source.                | 2.00-15 - 2.00-30             |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRIG_O:ENable?`` > ``ON``       | | Python: ``rp_GetDpinEnableTrigOutput()``                                         |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRig:Out:ENable?`` > ``<state>``| | C: ``rp_GetDpinEnableTrigOutput(bool *state)``                                   | | Returns the current mode state for GPION_0. If true, then the pin mode works as a source.                | 2.00-35 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRig:Out:ENable?`` > ``ON``     | | Python: ``rp_GetDpinEnableTrigOutput()``                                         |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRIG_O:SOUR <mode>``            | | C: ``rp_SetSourceTrigOutput(rp_outTiggerMode_t mode)``                           | | Sets the trigger source mode ADC/DAC.                                                                    | 2.00-15 - 2.00-30             |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRIG_O:SOUR DAC``               | | Python: ``rp_SetSourceTrigOutput(<mode>)``                                       |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRig:Out:SOUR <mode>``          | | C: ``rp_SetSourceTrigOutput(rp_outTiggerMode_t mode)``                           | | Sets the trigger source mode ADC/DAC.                                                                    | 2.00-35 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRig:Out:SOUR DAC``             | | Python: ``rp_SetSourceTrigOutput(<mode>)``                                       |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRIG_O:SOUR?`` > ``<mode>``     | | C: ``rp_GetSourceTrigOutput(rp_outTiggerMode_t *mode)``                          | | Returns the trigger source mode.                                                                         | 2.00-15 - 2.00-30             |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRIG_O:SOUR?`` > ``DAC``        | | Python: ``rp_GetSourceTrigOutput()``                                             |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+
| | ``DAISY:TRig:Out:SOUR?`` > ``<mode>``   | | C: ``rp_GetSourceTrigOutput(rp_outTiggerMode_t *mode)``                          | | Returns the trigger source mode.                                                                         | 2.00-35 and up                |
| | Examples:                               | |                                                                                  |                                                                                                            |                               |
| | ``DAISY:TRig:Out:SOUR?`` > ``DAC``      | | Python: ``rp_GetSourceTrigOutput()``                                             |                                                                                                            |                               |
|                                           | |                                                                                  |                                                                                                            |                               |
+-------------------------------------------+------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------------------------+-------------------------------+


.. note::

   The daisy chain commands only work for the :ref:`X-channel system <x-ch_streaming>` and the :ref:`Red Pitaya Click Shields <click_shield>`.

.. note::

   The trigger signals from the SATA connector and the DIO0_P (External trigger pin) are OR-ed together in the software.
   The generation and acquisition trigger fronts apply after the signals have been combined and trigger either DAC or ADC depending on the ``DAISY:TRIG_O:SOUR <mode>`` command.



.. _commands_pll:

==================
Phase locked loop
==================

.. note::

   These commands only work on SIGNALlab 250-12


**Parameter options:**

- ``<state> = {OFF, ON}``
- ``<enable> = {true, false}``

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-----------------------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                       | DESCRIPTION                                                                       |  ECOSYSTEM         |
+=====================================================+====================================================================================+===================================================================================+====================+
| | ``RP:PLL:ENable <state>``                         | | C: ``rp_SetPllControlEnable(bool enable)``                                       | Enables/disables PLL control (SIGNALlab 250-12 only).                             | 2.00-35 and up     |
| | Examples:                                         | |                                                                                  |                                                                                   |                    |
| | ``RP:PLL:ENable ON``                              | | Python: ``rp_SetPllControlEnable(<enable>)``                                     |                                                                                   |                    |
| |                                                   | |                                                                                  |                                                                                   |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``RP:PLL:ENable?`` > ``<state>``                  | | C: ``rp_GetPllControlEnable(bool *enable)``                                      | Get the PLL enable setting (SIGNALlab 250-12 only).                               | 2.00-35 and up     |
| | Examples:                                         | |                                                                                  |                                                                                   |                    |
| | ``RP:PLL:ENable?`` > ``ON``                       | | Python: ``rp_GetPllControlEnable()``                                             |                                                                                   |                    |
| |                                                   | |                                                                                  |                                                                                   |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``RP:PLL:STATE?`` > ``<enable>``                  | | C: ``rp_GetPllControlLocked(bool *status)``                                      | Get the current state of the PLL (SIGNALlab 250-12 only).                         | 2.00-35 and up     |
| | Examples:                                         | |                                                                                  |                                                                                   |                    |
| | ``RP:PLL:STATE?`` > ``1``                         | | Python: ``rp_GetPllControlLocked()``                                             |                                                                                   |                    |
| |                                                   | |                                                                                  |                                                                                   |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+



.. _commands_gen:

================
Signal Generator
================

.. note::

   For STEMlab 125-14 4-Input, the commands in this chapter are not applicable.

--------------------
Generator control
--------------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel OUT1 or OUT2)
- ``<state> = {ON,OFF}`` Default: ``OFF``
- ``<enable> = {true, false}`` Default: ``false``


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

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



-------------------
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



.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

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
| | ``SOUR:TRig:INT``                                 | | Python: ``rp_GenSynchronise()``                                                       | |                                                                                            |                    |
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRig:INT``                              | | C: ``rp_GenTriggerOnly(rp_channel_t channel)``                                        | Triggers the generation of the specified fast analog output immediately.                     | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:TRig:INT``                                | | Python: ``rp_GenTriggerOnly(<channel>)``                                              |                                                                                              |                    |
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
| | ``TRig:EXT:LEV <voltage>``                        | | C: ``rp_SetExternalTriggerLevel(float voltage)``                                      | Set the external trigger level in V.                                                         | 2.00-35 and up     |
| | Example:                                          | |                                                                                       | (Only SIGNALlab 250-12)                                                                      |                    |
| | ``TRig:EXT:LEV 1``                                | | Python: ``rp_SetExternalTriggerLevel(<voltage>)``                                     |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``TRig:EXT:LEV?`` > ``<voltage>``                 | | C: ``rp_GetExternalTriggerLevel(float* voltage)``                                     | Get the external trigger level in V.                                                         | 2.00-35 and up     |
| | Example:                                          | |                                                                                       | (Only SIGNALlab 250-12)                                                                      |                    |
| | ``TRig:EXT:LEV?`` > ``1``                         | | Python: ``rp_GetExternalTriggerLevel()``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+


--------------------
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
- ``<array> = {value1, ...}`` Max 16384 values, floats in the range -1 to 1
- ``<waveform> = {value1, ...}`` Max 16384 values, floats in the range -1 to 1 (``arbBuffer`` for Python API and Jupyter)
- ``<lenght>`` waveform array length
- ``<load_mode> = {INF, L50}`` Default: ``INF``

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``
- Waveforms - ``RP_WAVEFORM_SINE, RP_WAVEFORM_SQUARE, RP_WAVEFORM_TRIANGLE, RP_WAVEFORM_RAMP_UP, RP_WAVEFORM_RAMP_DOWN, RP_WAVEFORM_DC, RP_WAVEFORM_PWM, RP_WAVEFORM_ARBITRARY, RP_WAVEFORM_DC_NEG, RP_WAVEFORM_SWEEP``
- Rise and fall times - ``RISE_FALL_MIN_RATIO, RISE_FALL_MAX_RATIO``

*SIGNALlab 250-12 only:*

- Generator gain - ``RP_GAIN_1X, RP_GAIN_5X``


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

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
| | ``SOUR<n>:FREQ:FIX:Direct <frequency>``           | | C: ``rp_GenFreqDirect(rp_channel_t channel, float frequency)``                        | | Set the channel signal frequency in FPGA without reseting the generator and rebuilding     | 2.00-35 and up     |
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
| | ``SOUR<n>:PHAS?`` > ``<phase>``                   | | C: ``rp_GenGetPhase(rp_channel_t channel, float *phase)``                             | Set the phase of a fast analog output in degrees.                                            | 1.04-18 and up     |
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
| |                                                   | |                                                                                       | |                                                                                            |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:TRAC:DATA:DATA?`` > ``<array>``         | | C: ``rp_GenGetArbWaveform(rp_channel_t channel, float *waveform, uint32_t *length)``  | Get the user-defined arbitrary waveform period.                                              | 1.04-18 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:TRAC:DATA:DATA?`` >  ``1,0.5,0.2``        | | Python: ``rp_GenGetArbWaveform(<channel>, <waveform>)``                               |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:LOAD <load_mode>``                      | | C: ``rp_GenSetLoadMode(rp_channel_t channel, float phase)``                           | Set the load mode for the output. (SIGNALlab only)                                           | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR2:LOAD L50``                                | | Python: ``rp_GenSetLoadMode(<channel>, <phase>)``                                     |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:LOAD?`` > ``<load_mode>``               | | C: ``rp_GenGetLoadMode(rp_channel_t channel, float *phase)``                          | Get the load mode for the output. (SIGNALlab only)                                           | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR2:LOAD?`` > ``L50``                         | | Python: ``rp_GenGetLoadMode(<channel>)``                                              |                                                                                              |                    |
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
| | -                                                 | | C: ``rp_GenRiseTime(rp_channel_t channel, float time)``                               | Set signal rise time of a fast analog output in microseconds.                                | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenRiseTime(<channel>, <time>)``                                         |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenGetRiseTime(rp_channel_t channel, float *time)``                           | Get signal rise time of a fast analog output in microseconds.                                | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenGetRiseTime(<channel>)``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenFallTime(rp_channel_t channel, float time)``                               | Set signal fall time of a fast analog output in microseconds.                                | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenFallTime(<channel>, <time>)``                                         |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C: ``rp_GenGetFallTime(rp_channel_t channel, float *time)``                           | Get signal fall time of a fast analog output in microseconds.                                | 2.00-18 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``rp_GenGetFallTime(<channel>)``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+


------------
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


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

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



------------
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


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

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



Sweep mode extended
~~~~~~~~~~~~~~~~~~~~~


**Parameter options:**

- ``<n> = {1,2}`` (set channel OUT1 or OUT2)
- ``<frequency> = {0 ... 62.5e6}`` (in Hertz). Default: ``1000`` (start), ``10000`` (end)
- ``<time> = {1 ... }`` (in μS). Default: ``1``
- ``<mode> = {LINEAR, LOG}`` (in μS). Default: ``LINEAR``
- ``<dir> = {NORMAL, UP_DOWN}`` (in μS). Default: ``NORMAL``
- ``<state> = {ON, OFF}``

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``
- Sweep direction - ``RP_GEN_SWEEP_DIR_NORMAL, RP_GEN_SWEEP_DIR_UP_DOWN``
- Sweep mode - ``RP_GEN_SWEEP_MODE_LINEAR, RP_GEN_SWEEP_MODE_LOG``
- State - ``True,False``


.. note::

    This API uses a class to control the sweep mode. This class is available in the rp-sweep library.

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                            | DESCRIPTION                                                                                  |  ECOSYSTEM         |
+=====================================================+=========================================================================================+==============================================================================================+====================+
| | -                                                 | | C++: ``run()``                                                                        | | Starts the frequency generator.                                                            | 2.00-35 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``run()``                                                                     |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | -                                                 | | C++: ``stop()``                                                                       | | Stops the thread that generates frequencies.                                               | 2.00-35 and up     |
| |                                                   | |                                                                                       |                                                                                              |                    |
| |                                                   | | Python: ``stop()``                                                                    |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:SWeep:RESET``                              | | C++: ``resetAll()``                                                                   | | Resets all channels at once.                                                               | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR:SWeep:RESET``                              | | Python: ``resetAll()``                                                                |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR:SWeep:PAUSE <state>``                      | | C++: ``pause(bool state)``                                                            | | Stops the frequency change, but does not reset the state.                                  | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR:SWeep:PAUSE ON``                           | | Python: ``pause(<State>)``                                                            |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:STATE <state>``                   | | C++: ``genSweep(rp_channel_t channel,bool enable)``                                   | | Enables or disables generation of the specified channel.                                   | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:STATE ON``                          | | Python: ``genSweep(<channel>, <State>)``                                              |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:STATE?`` > ``<state>``            | | C++: ``isGen(rp_channel_t channel,bool *state)``                                      | | Returns the channel status.                                                                | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:STATE?`` > ``ON``                   | | Python: ``isGen(<channel>)``                                                          |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:FREQ:START <frequency>``          | | C++: ``setStartFreq(rp_channel_t channel,float frequency)``                           | | Set sweep start frequency.                                                                 | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:FREQ:START 1000``                   | | Python: ``setStartFreq(<channel>, <frequency>)``                                      |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:FREQ:START?`` > ``<frequency>``   | | C++: ``getStartFreq(rp_channel_t channel,float *frequency)``                          | | Get sweep start frequency.                                                                 | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:FREQ:START?`` > ``1000``            | | Python: ``getStartFreq(<channel>)``                                                   |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:FREQ:STOP <frequency>``           | | C++: ``setStopFreq(rp_channel_t channel,float frequency)``                            | | Set sweep stop frequency.                                                                  | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:FREQ:STOP 10000``                   | | Python: ``setStopFreq(<channel>, <frequency>)``                                       |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:FREQ:STOP?`` > ``<frequency>``    | | C++: ``getStopFreq(rp_channel_t channel,float *frequency)``                           | | Get sweep stop frequency.                                                                  | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:FREQ:STOP?`` > ``10000``            | | Python: ``getStopFreq(<channel>)``                                                    |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:TIME <time>``                     | | C++: ``setTime(rp_channel_t channel,int us)``                                         | | Sets the generation time, how long it takes to transition from the                         | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       | | starting frequency to the final frequency, measured in microseconds.                       |                    |
| | ``SOUR1:SWeep:TIME 10000``                        | | Python: ``setTime(<channel>, <frequency>)``                                           |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:TIME?`` > ``<time>``              | | C++: ``getTime(rp_channel_t channel,int *us)``                                        | | Returns generation time in microseconds.                                                   | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:TIME?`` > ``10000``                 | | Python: ``getTime(<channel>)``                                                        |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:MODE <mode>``                     | | C++: ``setMode(rp_channel_t channel,rp_gen_sweep_mode_t mode)``                       | | Set sweep mode to either linear or logarithmic.                                            | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:MODE LINEAR``                       | | Python: ``setMode(<channel>, <mode>)``                                                |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:MODE?`` > ``<mode>``              | | C++: ``getMode(rp_channel_t channel,rp_gen_sweep_mode_t *mode)``                      | | Get sweep mode (either linear or logarithmic).                                             | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:MODE?`` > ``LINEAR``                | | Python: ``getMode(<channel>)``                                                        |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:DIR <dir>``                       | | C++: ``setDir(rp_channel_t channel,rp_gen_sweep_dir_t dir)``                          | | Set sweep direction (normal (up) or up-down).                                              | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:DIR UP_DOWN``                       | | Python: ``setDir(<channel>, <dir>)``                                                  |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+
| | ``SOUR<n>:SWeep:DIR?`` > ``<dir>``                | | C++: ``getDir(rp_channel_t channel,rp_gen_sweep_dir_t *dir)``                         | | Get sweep direction (normal (up) or up-down).                                              | 2.00-35 and up     |
| | Examples:                                         | |                                                                                       |                                                                                              |                    |
| | ``SOUR1:SWeep:DIR?`` > ``UP_DOWN``                | | Python: ``getDir(<channel>)``                                                         |                                                                                              |                    |
| |                                                   | |                                                                                       |                                                                                              |                    |
+-----------------------------------------------------+-----------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------------+--------------------+



.. _commands_acq:

==============
Acquisition
==============

--------------------
Acquisition Control
--------------------

**Parameter options:**

- ``<enable> = {true, false}``
- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<state> = {ON, OFF}`` Default: ``OFF``

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| SCPI                                | API, Jupyter                                    | DESCRIPTION                                                                |  ECOSYSTEM         |
+=====================================+=================================================+============================================================================+====================+
| | ``ACQ:START``                     | | C: ``rp_AcqStart()``                          | Start the acquisition.                                                     | 1.04-18 and up     |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqStart()``                     |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:START:CH<n>``               | | C: ``rp_AcqStartCh(rp_channel_t channel)``    | |Start the acquisition.                                                    | in dev             |
| |                                   | |                                               | | Used only in split trigger mode                                          |                    |
| |                                   | | Python: ``rp_AcqStartCh(<channel>)``          |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:STOP``                      | | C: ``rp_AcqStop()``                           | Stop the acquisition.                                                      | 1.04-18 and up     |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqStop()``                      |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:STOP:CH<n>``                | | C: ``rp_AcqStopCh(rp_channel_t channel)``     | | Stop the acquisition.                                                    | in dev             |
| |                                   | |                                               | | Used only in split trigger mode                                          |                    |
| |                                   | | Python: ``rp_AcqStopCh(<channel>)``           |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:RST``                       | | C: ``rp_AcqReset()``                          | | Stop the acquisition and reset all acquisition parameters to             | 1.04-18 and up     |
| |                                   | |                                               | | default values.                                                          |                    |
| |                                   | | Python: ``rp_AcqReset()``                     | |                                                                          |                    |
| |                                   | |                                               | |                                                                          |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:RST:CH<n>``                 | | C: ``rp_AcqResetCh(rp_channel_t channel)``    | | Stop the acquisition and reset all acquisition parameters to             | in dev             |
| |                                   | |                                               | | default values.                                                          |                    |
| |                                   | | Python: ``rp_AcqResetCh(<channel>)``          | | Used only in split trigger mode                                          |                    |
| |                                   | |                                               | |                                                                          |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:SPLIT:TRig <state>``        | | C: ``rp_AcqResetCh(rp_channel_t channel)``    | Enables split trigger mode.                                                | in dev             |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqResetCh(<channel>)``          |                                                                            |                    |
| |                                   | |                                               |                                                                            |                    |
+-------------------------------------+-------------------------------------------------+----------------------------------------------------------------------------+--------------------+
| | ``ACQ:SPLIT:TRig?`` > ``<state>`` | | C: ``rp_AcqResetCh(rp_channel_t channel)``    | Returns the split trigger mode status                                      | in dev             |
| |                                   | |                                               |                                                                            |                    |
| |                                   | | Python: ``rp_AcqResetCh(<channel>)``          |                                                                            |                    |
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


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                                   | DESCRIPTION                                                                   |  ECOSYSTEM         |
+=====================================================+================================================================================================+===============================================================================+====================+
| | ``ACQ:DEC <decimation>``                          | | C: ``rp_AcqSetDecimation(rp_acq_decimation_t decimation)``                                   | | Set the decimation factor (power of 2 from 1 to 65536).                     | 1.04-18 and up     |
| | Example:                                          | |                                                                                              | |                                                                             |                    |
| | ``ACQ:DEC 4``                                     | | Python: ``rp_AcqSetDecimation(<decimation>)``                                                | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:CH<n> <decimation>``                    | | C: ``rp_AcqSetDecimationCh(rp_channel_t channel, rp_acq_decimation_t decimation)``           | | Set the decimation factor (power of 2 from 1 to 65536).                     | in dev             |
| | Example:                                          | |                                                                                              | | Used only in split trigger mode                                             |                    |
| | ``ACQ:DEC:CH1 4``                                 | | Python: ``rp_AcqSetDecimationCh(<channel>, <decimation>)``                                   | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC?`` > ``<decimation>``                   | | C: ``rp_AcqGetDecimation(rp_acq_decimation_t* decimation)``                                  | Get the decimation factor.                                                    | 1.04-18 and up     |
| | Example:                                          | |                                                                                              |                                                                               |                    |
| | ``ACQ:DEC?`` > ``1``                              | | Python: ``rp_AcqGetDecimation()``                                                            |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:CH<n>?`` > ``<decimation>``             | | C: ``rp_AcqGetDecimationCh(rp_channel_t channel, rp_acq_decimation_t* decimation)``          | | Get the decimation factor.                                                  | in dev             |
| | Example:                                          | |                                                                                              | | Used only in split trigger mode                                             |                    |
| | ``ACQ:DEC:CH1?`` > ``1``                          | | Python: ``rp_AcqGetDecimationCh(<channel>)``                                                 |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:Factor <decimation_ext>``               | | C: ``rp_AcqSetDecimationFactor(uint32_t decimation)``                                        | | Set the extended decimation factor (power of 2 up to 16 then any            | 2.00-30 and up     |
| | Example:                                          | |                                                                                              | | whole number up to 65536).                                                  |                    |
| | ``ACQ:DEC:Factor 17``                             | | Python: ``rp_AcqSetDecimationFactor(<decimation>)``                                          | |                                                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:Factor:CH<n> <decimation_ext>``         | | C: ``rp_AcqSetDecimationFactorCh(rp_channel_t channel, uint32_t decimation)``                | | Set the extended decimation factor (power of 2 up to 16 then any            | in dev             |
| | Example:                                          | |                                                                                              | | whole number up to 65536).                                                  |                    |
| | ``ACQ:DEC:Factor:CH1 17``                         | | Python: ``rp_AcqSetDecimationFactorCh(<channel>, <decimation>)``                             | | Used only in split trigger mode                                             |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:Factor?`` > ``<decimation_ext>``        | | C: ``rp_AcqGetDecimationFactor(uint32_t* decimation)``                                       | Get the extended decimation factor.                                           | 2.00-30 and up     |
| | Example:                                          | |                                                                                              |                                                                               |                    |
| | ``ACQ:DEC:Factor?`` > ``1``                       | | Python: ``rp_AcqGetDecimationFactor()``                                                      |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:DEC:Factor:CH<n>?`` > ``<decimation_ext>``  | | C: ``rp_AcqGetDecimationFactorCh(rp_channel_t channel, uint32_t* decimation)``               | | Get the extended decimation factor.                                         | in dev             |
| | Example:                                          | |                                                                                              | | Used only in split trigger mode                                             |                    |
| | ``ACQ:DEC:Factor:CH1?`` > ``1``                   | | Python: ``rp_AcqGetDecimationFactorCh(<channel>)``                                           |                                                                               |                    |
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
| | ``ACQ:SOUR<n>:COUP <mode>``                       | | C: ``rp_AcqSetAC_DC(rp_channel_t channel,rp_acq_ac_dc_mode_t mode)``                         | Set the AC / DC mode of the specified input (only SIGNALlab 250-12).          | 1.04-18 and up     |
| | Example:                                          | |                                                                                              |                                                                               |                    |
| | ``ACQ:SOUR1:COUP AC``                             | | Python: ``rp_AcqSetAC_DC(<channel>, <mode>)``                                                |                                                                               |                    |
| |                                                   | |                                                                                              |                                                                               |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:COUP?`` > ``<mode>``                | | C: ``rp_AcqGetAC_DC(rp_channel_t channel,rp_acq_ac_dc_mode_t *status)``                      | Get the AC / DC mode of the specified input (only SIGNALlab 250-12).          | 1.04-18 and up     |
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
| | - (N/A)                                           | | C: - (look for *malloc* function online)                                                     | | Performs memory allocation and returns the requested buffer.                | 2.00-18 and up     |
| |                                                   | |                                                                                              | | - ``<maxChannels>`` - how many channels will be acquired                    |                    |
| |                                                   | | Python: ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)`` | | - ``<enght>`` - length of the buffer in samples (max 16384)                 |                    |
| |                                                   | |                                                                                              | | - ``<initInt16>, <initDouble>, <initFloat>`` - buffer sample type, set one  |                    |
| |                                                   | |                                                                                              | |   to ``true``, others are ``false``.                                        |                    |
| |                                                   | |                                                                                              | | For Python API specifically.                                                |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+--------------------+
| | - (N/A)                                           | | C: - (look for *free* function online)                                                       | | Free the allocated resources.                                               | 2.00-18 and up     |
| |                                                   | |                                                                                              | | - ``<buffer>`` - buffer to be released/freed                                |                    |
| |                                                   | | Python: ``rp_deleteBuffer(<buffer>)``                                                        | | For Python API specifically.                                                |                    |
| |                                                   | |                                                                                              | |                                                                             |                    |
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


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| SCPI                                                   | API, Jupyter                                                                         | DESCRIPTION                                                                   |  ECOSYSTEM              |
+========================================================+======================================================================================+===============================================================================+=========================+
| | ``ACQ:TRig <source>``                                | | C: ``rp_AcqSetTriggerSrc(rp_acq_trig_src_t source)``                               | | Set acquisition trigger source. The options are disabled, trigger           | 1.04-18 and up          |
| | Example:                                             | |                                                                                    | | immediately, or set trigger source & edge.                                  |                         |
| | ``ACQ:TRig CH1_PE``                                  | | Python: ``rp_AcqSetTriggerSrc(<source>)``                                          | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:CH<n> <source>``                          | | C: ``rp_AcqSetTriggerSrc(rp_channel_t channel, rp_acq_trig_src_t source)``         | | Set acquisition trigger source. The options are disabled, trigger           | in dev                  |
| | Example:                                             | |                                                                                    | | immediately, or set trigger source & edge.                                  |                         |
| | ``ACQ:TRig:CH1 CH1_PE``                              | | Python: ``rp_AcqSetTriggerSrc(<channel>, <source>)``                               | | Used only in split trigger mode                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
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
| | ``ACQ:TRig:STAT:CH<n>?`` > ``<state>``               | | C: ``rp_AcqGetTriggerStateCh(rp_channel_t channel, rp_acq_trig_state_t* state)``   | | Get acquisition trigger status. If the trigger is ``DISABLED`` or the       | in dev                  |
| | Example:                                             | |                                                                                    | | acquisition is triggered, the state is ``TD``. Otherwise, it is ``WAIT``.   |                         |
| | ``ACQ:TRig:STAT:CH1?`` > ``WAIT``                    | | Python: ``rp_AcqGetTriggerStateCh(<channel>)``                                     | | Used only in split trigger mode                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:FILL?`` > ``<fill_state>``                | | C: ``rp_AcqGetBufferFillState(bool* state)``                                       | Returns 1 if the buffer is full of data. Otherwise returns 0.                 | 2.00-15 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:FILL?`` > ``1``                           | | Python: ``rp_AcqGetBufferFillState()``                                             |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:FILL:CH<n>?`` > ``<fill_state>``          | | C: ``rp_AcqGetBufferFillStateCh(rp_channel_t channel, bool* state)``               | | Returns 1 if the buffer is full of data. Otherwise returns 0.               | in dev                  |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:FILL:CH1?`` > ``1``                       | | Python: ``rp_AcqGetBufferFillStateCh(<channel>)``                                  |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY <decimated_data_num>``                | | C: ``rp_AcqSetTriggerDelay(int32_t decimated_data_num)``                           | | Set the trigger delay in samples. The triggering moment is by default in    | 1.04-18 and up          |
| | Example:                                             | |                                                                                    | | the middle of acquired buffer (at 8192th sample) (trigger delay set to 0).  |                         |
| | ``ACQ:TRig:DLY 2314``                                | | Python: ``rp_AcqSetTriggerDelay(<decimated_data_num>)``                            | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:CH<n> <decimated_data_num>``          | | C: ``rp_AcqSetTriggerDelayCh(rp_channel_t channel, int32_t decimated_data_num)``   | | Set the trigger delay in samples. The triggering moment is by default in    | in dev                  |
| | Example:                                             | |                                                                                    | | the middle of acquired buffer (at 8192th sample) (trigger delay set to 0).  |                         |
| | ``ACQ:TRig:DLY:CH1 2314``                            | | Python: ``rp_AcqSetTriggerDelayCh(<channel>,<decimated_data_num>)``                | | Used only in split trigger mode                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY?`` > ``<decimated_data_num>``         | | C: ``rp_AcqGetTriggerDelay(int32_t* decimated_data_num)``                          | Get the trigger delay in samples.                                             | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:DLY?`` > ``2314``                         | | Python: ``rp_AcqGetTriggerDelay()``                                                |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:CH<n>?`` > ``<decimated_data_num>``   | | C: ``rp_AcqGetTriggerDelayCh(rp_channel_t channel, int32_t* decimated_data_num)``  | Get the trigger delay in samples.                                             | in dev                  |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:DLY:CH1?`` > ``2314``                     | | Python: ``rp_AcqGetTriggerDelayCh(<channel>)``                                     |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:NS <time_ns>``                        | | C: ``rp_AcqSetTriggerDelayNs(int64_t time_ns)``                                    | | Set the trigger delay in ns. Must be multiple of the board's clock          | 1.04-18 and up          |
| | Example:                                             | |                                                                                    | | resolution (125 MHz clock == 8 ns resolution, 250 MHz == 4 ns resolution).  |                         |
| | ``ACQ:TRig:DLY:NS 128``                              | | Python: ``rp_AcqSetTriggerDelayNs(<time_ns>)``                                     | |                                                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:NS:CH<n> <time_ns>``                  | | C: ``rp_AcqSetTriggerDelayNsCh(rp_channel_t channel, int64_t time_ns)``            | | Set the trigger delay in ns. Must be multiple of the board's clock          | in dev                  |
| | Example:                                             | |                                                                                    | | resolution (125 MHz clock == 8 ns resolution, 250 MHz == 4 ns resolution).  |                         |
| | ``ACQ:TRig:DLY:NS:CH1 128``                          | | Python: ``rp_AcqSetTriggerDelayNsCh(<channel>,<time_ns>)``                         | | Used only in split trigger mode                                             |                         |
| |                                                      | |                                                                                    | |                                                                             |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:NS?`` > ``<time_ns>``                 | | C: ``rp_AcqGetTriggerDelayNs(int64_t* time_ns)``                                   | Get the trigger delay in ns.                                                  | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:DLY:NS?`` > ``128`` ns                    | | Python: ``rp_AcqGetTriggerDelayNs()``                                              |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:DLY:NS:CH<n>?`` > ``<time_ns>``           | | C: ``rp_AcqGetTriggerDelayNsCh(rp_channel_t channel, int64_t* time_ns)``           | Get the trigger delay in ns.                                                  | in dev                  |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:DLY:NS:CH1?`` > ``128`` ns                | | Python: ``rp_AcqGetTriggerDelayNsCh(<channel>)``                                   |                                                                               |                         |
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
| | ``ACQ:TRig:LEV:CH<n> <voltage>``                     | | C: ``rp_AcqSetTriggerLevel(rp_channel_trigger_t channel, float voltage)``          | | Set the trigger level in V.                                                 | in dev                  |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:LEV:CH1 0.125 V``                         | | Python: ``rp_AcqSetTriggerLevel(<channel>, <voltage>)``                            |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:LEV?`` > ``<voltage>``                    | | C: ``rp_AcqGetTriggerLevel(rp_channel_trigger_t channel, float* voltage)``         | Get the trigger level in V.                                                   | 1.04-18 and up          |
| | Example:                                             | |                                                                                    |                                                                               |                         |
| | ``ACQ:TRig:LEV?`` > ``0.123`` V                      | | Python: ``rp_AcqGetTriggerLevel(<channel>)``                                       |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``ACQ:TRig:LEV:CH<n>?`` > ``<voltage>``              | | C: ``rp_AcqGetTriggerLevel(rp_channel_trigger_t channel, float* voltage)``         | | Get the trigger level in V.                                                 | in dev                  |
| | Example:                                             | |                                                                                    | | Used only in split trigger mode                                             |                         |
| | ``ACQ:TRig:LEV:CH1?`` > ``0.123`` V                  | | Python: ``rp_AcqGetTriggerLevel(<channel>)``                                       |                                                                               |                         |
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
| | ``TRig:EXT:LEV <voltage>``                           | | C: ``rp_SetExternalTriggerLevel(float voltage)``                                   | Set the external trigger level in V.                                          | 2.00-35 and up          |
| | Example:                                             | |                                                                                    | (Only SIGNALlab 250-12)                                                       |                         |
| | ``TRig:EXT:LEV 1``                                   | | Python: ``rp_SetExternalTriggerLevel(<voltage>)``                                  |                                                                               |                         |
| |                                                      | |                                                                                    |                                                                               |                         |
+--------------------------------------------------------+--------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------+
| | ``TRig:EXT:LEV?`` > ``<voltage>``                    | | C: ``rp_GetExternalTriggerLevel(float* voltage)``                                  | Get the external trigger level in V.                                          | 2.00-35 and up          |
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

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

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
| | ``ACQ:WPOS:CH<n>?`` > ``<pos>``     | | C: ``rp_AcqGetWritePointerCh(rp_channel_t channel, uint32_t* pos)``             | | Returns the current position of the write pointer,     | in dev             |
| | Example:                            | |                                                                                 | | i.e the index of the most recent sample in the buffer. |                    |
| | ``ACQ:WPOS:CH1?`` > ``1024``        | | Python: ``rp_AcqGetWritePointerCh(<channel>)``                                  | | Used only in split trigger mode                        |                    |
| |                                     | |                                                                                 | |                                                        |                    |
+---------------------------------------+-----------------------------------------------------------------------------------+----------------------------------------------------------+--------------------+
| | ``ACQ:TPOS:CH<n>?`` > ``<pos>``     | | C: ``rp_AcqGetWritePointerAtTrigCh(rp_channel_t channel, uint32_t* pos)``       | | Returns the position where the trigger event appeared. | in dev             |
| | Example:                            | |                                                                                 | | Used only in split trigger mode                        |                    |
| | ``ACQ:TPOS:CH1?`` > ``512``         | | Python: ``rp_AcqGetWritePointerAtTrigCh(<channel>)``                            |                                                          |                    |
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

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| SCPI                                        | API, Jupyter                                                                                                                             | DESCRIPTION                                                                            |  ECOSYSTEM         |
+=============================================+==========================================================================================================================================+========================================================================================+====================+
| | ``ACQ:SOUR<n>:DATA:STArt:End?``           | | C: ``rp_AcqGetDataPosRaw(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, int16_t* buffer, uint32_t* buffer_size)``         | | Read samples from start to end position. For API commands, the buffer for data       | 1.04-18 and up     |
| | ``<start_pos>,<end_pos>``                 | |    ``rp_AcqGetDataPosV(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, float* buffer, uint32_t* buffer_size)``             | | storage and its size must also be provided. Use ``rp_createBuffer`` to allocate data |                    |
| | Example:                                  | | Python: ``rp_AcqGetDataPosRaw(<channel>, <start_pos>, <end_pos>, <buffer>, <buffer_size>)``                                            | | for Python and *malloc* for C. API commands have two functions to return data in     |                    |
| | ``ACQ:SOUR1:DATA:STArt:End? 10,13`` >     | |         ``rp_AcqGetDataPosV(<channel>, <start_pos>, <end_pos>, <buffer>, <buffer_size>)``                                              | | Volts or RAW.                                                                        |                    |
| | ``{123,231,-231}``                        | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | -                                         | | C: ``rp_AcqGetDataRawWithCalib(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)``                                 | | Read ``<size>`` samples from the ``<pos>`` onwards. The data is returned in RAW      | 1.04-18 and up     |
| |                                           | |                                                                                                                                        | | format with calibration applied.                                                     |                    |
| |                                           | | Python: ``rp_AcqGetDataRawWithCalib(<channel>, <pos>, <size>, <buffer>)``                                                              | |                                                                                      |                    |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
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
| | ``ACQ:SOUR<n>:DATA?``                     | | C: ``rp_AcqGetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)``                                                   | | Read the full buffer.                                                                | 1.04-18 and up     |
| | Example:                                  | |    ``rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer)``                                                       | | Starting from the oldest sample in the buffer (first sample after trigger delay).    |                    |
| | ``ACQ:SOUR2:DATA?`` >                     | | Python: ``rp_AcqGetOldestDataRaw(<channel>, <size>, <buffer>)``                                                                        | | If the trigger delay is set to zero, it will read the full buffer size starting      |                    |
| | ``{1.2,3.2,...,-1.2}``                    | |         ``rp_AcqGetOldestDataV(<channel>, <size>, <buffer>)``                                                                          | | from the trigger.                                                                    |                    |
| |                                           | |                                                                                                                                        | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:Old:N? <size>``        | | C: ``rp_AcqGetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)``                                                   | | Read ``<size>`` samples after the trigger delay, starting from the oldest sample     | 1.04-18 and up     |
| | Example:                                  | |    ``rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer)``                                                       | | in the buffer (first sample after trigger delay).                                    |                    |
| | ``ACQ:SOUR2:DATA:Old:N? 3`` >             | | Python: ``rp_AcqGetOldestDataRaw(<channel>, <size>, <buffer>)``                                                                        | | The trigger delay is set to zero by default (in samples or in seconds).              |                    |
| | ``{1.2,3.2,-1.2}``                        | |         ``rp_AcqGetOldestDataV(<channel>, <size>, <buffer>)``                                                                          | | If the trigger delay is set to zero, it will read m samples starting                 |                    |
| |                                           | |                                                                                                                                        | | from the trigger.                                                                    |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``ACQ:SOUR<n>:DATA:LATest:N? <size>``     | | C: ``rp_AcqGetLatestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)``                                                   | | Read ``<size>`` samples before the trigger delay.                                    | 1.04-18 and up     |
| | Example:                                  | |    ``rp_AcqGetLatestDataV(rp_channel_t channel, uint32_t* size, float* buffer)``                                                       | | The trigger delay is set to zero by default (in samples or in seconds).              |                    |
| | ``ACQ:SOUR1:DATA:LAT:N? 3`` >             | | Python: ``rp_AcqGetLatestDataRaw(<channel>, <size>, <buffer>)``                                                                        | | If the trigger delay is set to zero, it will read m samples before the trigger.      |                    |
| | ``{1.2,3.2,-1.2}``                        | |         ``rp_AcqGetLatestDataV(<channel>, <size>, <buffer>)``                                                                          | |                                                                                      |                    |
+---------------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+


.. _commands_dma:

==============================
Deep Memory Acquisition (DMA)
==============================

-------------
DMA settings
-------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<byte> = {0...}`` in bytes
- ``<decimation> = {1, 2, 4, 8, 16, 17, 18, 19, ..., 65534, 65535, 65536}`` Default: ``1``
- ``<decimated_data_num> = {value in samples}`` Default: ``0``
- ``<pos> = {position inside circular buffer in samples}``
- ``<enable> = {ON, OFF}`` Default: ``OFF``
- ``<address> = {byte}`` Address of reserved memory
- ``<size> = {byte}`` Size of buffer in bytes. Default: 2 MB
- ``<samples> = {sample}`` Size of the acquisition buffer in samples. Default: 2 MB
- ``<units> = {RAW, VOLTS}`` Default: ``VOLTS``

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``


+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| SCPI                                                      | API, Jupyter                                                                                                               | DESCRIPTION                                                                     |  ECOSYSTEM         |
+===========================================================+============================================================================================================================+=================================================================================+====================+
| | ``ACQ:AXI:START?`` > ``<byte>``                         | | C: ``rp_AcqAxiGetMemoryRegion(uint32_t *_start,uint32_t *_size)``                                                        | | Returns the start address of the Deep Memory region.                          | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | API: Also returns the size of the memory region.                              |                    |
| | ``ACQ:AXI:START?`` > ``16777216``                       | | Python: ``rp_AcqAxiGetMemoryRegion()``                                                                                   | | This can also be achieved by displaying values of ``ADC_AXI_START``           |                    |
| |                                                         | |                                                                                                                          | | and ``ADC_AXI_END`` macros.                                                   |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SIZE?`` > ``<byte>``                          | | C: ``rp_AcqAxiGetMemoryRegion(uint32_t *_start,uint32_t *_size)``                                                        | | Get size of reserved memory for Deep Memory mode.                             | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | **API:** Also returns the start address of the memory region.                 |                    |
| | ``ACQ:AXI:SIZE?`` > ``2097152``                         | | Python: ``rp_AcqAxiGetMemoryRegion()``                                                                                   | | This can also be achieved by displaying values of ``ADC_AXI_START``           |                    |
| |                                                         | |                                                                                                                          | | and ``ADC_AXI_END`` macros.                                                   |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC <decimation>``                            | | C: ``rp_AcqAxiSetDecimationFactor(uint32_t decimation)``                                                                 | Sets the decimation used at acquiring signal for the Deep Memory Mode.          | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          |                                                                                 |                    |
| | ``ACQ:AXI:DEC 4``                                       | | Python: ``rp_AcqAxiSetDecimationFactor(<decimation>)``                                                                   |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC?`` > ``<decimation>``                     | | C: ``rp_AcqAxiGetDecimationFactor(uint32_t *decimation)``                                                                | Returns the decimation used for acquiring signal for the Deep Memory Mode.      | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          |                                                                                 |                    |
| | ``ACQ:AXI:DEC?`` > ``1``                                | | Python: ``rp_AcqAxiGetDecimationFactor()``                                                                               |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC:CH<n> <decimation>``                      | | C: ``rp_AcqAxiSetDecimationFactorCh(rp_channel_t channel, uint32_t decimation)``                                         | | Sets the decimation used at acquiring signal for the Deep Memory Mode.        | in dev             |
| | Example:                                                | |                                                                                                                          | | Used only in split trigger mode                                               |                    |
| | ``ACQ:AXI:DEC:CH1 4``                                   | | Python: ``rp_AcqAxiSetDecimationFactorCh(<channel>, <decimation>)``                                                      |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC:CH<n>?`` > ``<decimation>``               | | C: ``rp_AcqAxiGetDecimationFactorCh(rp_channel_t channel, uint32_t *decimation)``                                        | | Returns the decimation used for acquiring signal for the Deep Memory Mode.    | in dev             |
| | Example:                                                | |                                                                                                                          | | Used only in split trigger mode                                               |                    |
| | ``ACQ:AXI:DEC:CH1?`` > ``1``                            | | Python: ``rp_AcqAxiGetDecimationFactorCh(<channel>)``                                                                    |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:ENable <enable>``                     | | C: ``rp_AcqAxiEnable(rp_channel_t channel, bool enable)``                                                                | Sets the Deep Memory enable state.                                              | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          |                                                                                 |                    |
| | ``ACQ:AXI:SOUR1:ENable ON``                             | | Python: ``rp_AcqAxiEnable(<channel>, <enable>)``                                                                         |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Dly <decimated_data_num>``       | | C: ``rp_AcqAxiSetTriggerDelay(rp_channel_t channel, int32_t decimated_data_num)``                                        | | Sets the number of decimated data after the trigger is                        | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | written into memory.                                                          |                    |
| | ``ACQ:AXI:SOUR1:Trig:Dly 2314``                         | | Python: ``rp_AcqAxiSetTriggerDelay(<channel>, <decimated_data_num>)``                                                    | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Dly?`` > ``<decimated_data_num>``| | C: ``rp_AcqAxiGetTriggerDelay(rp_channel_t channel, int32_t *decimated_data_num)``                                       | | Returns the number of decimated data after the trigger is                     | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | written into memory.                                                          |                    |
| | ``ACQ:AXI:SOUR1:Trig:Dly?`` > ``2314``                  | | Python: ``rp_AcqAxiGetTriggerDelay(<channel>)``                                                                          | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:SET:Buffer <address>,<size>``         | | C: ``rp_AcqAxiSetBufferSamples(rp_channel_t channel, uint32_t address, uint32_t samples)``                               | | Sets the Deep Memory buffer address and size in samples.                      | 2.00-18 and up     |
| | Example:                                                | |    ``rp_AcqAxiSetBufferBytes(rp_channel_t channel, uint32_t address, uint32_t size)``                                    | | Buffer size must be a multiple of 2.                                          |                    |
| | ``ACQ:AXI:SOUR<n>:SET:Buffer 16777216,512``             | | Python: ``rp_AcqAxiSetBufferSamples(<channel>, <address>, <samples>)``                                                   | |                                                                               |                    |
| |                                                         | |         ``rp_AcqAxiSetBufferBytes(<channel>, <address>, <size>)``                                                        | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DATA:UNITS <units>``                          | | C: - (see ``rp_AcqAxiGetDataV`` and ``rp_AcqAxiGetDataRaw``)                                                             | | Select units in which the acquired data will be returned.                     | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | For API commands the units are selected with the get data function.           |                    |
| | ``ACQ:AXI:DATA:UNITS RAW``                              | | Python: - (see ``rp_AcqAxiGetDataV`` and ``rp_AcqAxiGetDataRaw``)                                                        | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DATA:UNITS?`` > ``<units>``                   | | C: - (see ``rp_AcqAxiGetDataV`` and ``rp_AcqAxiGetDataRaw``)                                                             | | Get units in which the acquired data will be returned.                        | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | For API commands the units are selected with the get data function.           |                    |
| | ``ACQ:AXI:DATA:UNITS?`` > ``RAW``                       | | Python: - (see ``rp_AcqAxiGetDataV`` and ``rp_AcqAxiGetDataRaw``)                                                        | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | - (NA)                                                  | | C: - (look for *malloc* function online)                                                                                 | | Performs memory allocation and returns the requested buffer.                  | 2.00-18 and up     |
| |                                                         | |                                                                                                                          | | - ``<maxChannels>`` - how many channels will be acquired                      |                    |
| |                                                         | | Python: ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)``                             | | - ``<enght>`` - length of the buffer in samples (max 16384)                   |                    |
| |                                                         | |                                                                                                                          | | - ``<initInt16>, <initDouble>, <initFloat>`` - buffer sample type, set one    |                    |
| |                                                         | |                                                                                                                          | |   to ``true``, others are ``false``.                                          |                    |
| |                                                         | |                                                                                                                          | | For Python API specifically.                                                  |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | - (NA)                                                  | | C: - (look for *free* function online)                                                                                   | | Free the allocated resources.                                                 | 2.00-18 and up     |
| |                                                         | |                                                                                                                          | | - ``<buffer>`` - buffer to be released/freed                                  |                    |
| |                                                         | | Python: ``rp_deleteBuffer(<buffer>)``                                                                                    | | For Python API specifically.                                                  |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+




----------------
DMA data read
----------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<count> = {value in samples}`` Default: ``0``
- ``<pos> = {samples}`` Position inside circular buffer in samples
- ``<size> = {samples}`` Size of acquired data in samples
- ``<buffer>`` Array to store the data into. For Python API use ``rp_createBuffer`` and for C API use *malloc*.

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``



.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| SCPI                                               | API, Jupyter                                                                                                               | DESCRIPTION                                                                     |  ECOSYSTEM         |
+====================================================+============================================================================================================================+=================================================================================+====================+
| | ``ACQ:AXI:SOUR<n>:TRIG:FILL?``                   | | C: ``rp_AcqAxiGetBufferFillState(rp_channel_t channel, bool* state)``                                                    | Indicates whether the Deep Memory buffer was full of data.                      | 2.00-18 and up     |
| | Example:                                         | |                                                                                                                          |                                                                                 |                    |
| | ``ACQ:AXI:SOUR1:TRIG:FILL?`` > ``1``             | | Python: ``rp_AcqAxiGetBufferFillState(<channel>)``                                                                       |                                                                                 |                    |
| |                                                  | |                                                                                                                          |                                                                                 |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Write:Pos?`` > ``<pos>``       | | C: ``rp_AcqAxiGetWritePointer(rp_channel_t channel, uint32_t* pos)``                                                     | | Returns current position of the Deep Memory write pointer.                    | 2.00-18 and up     |
| | Example:                                         | |                                                                                                                          | |                                                                               |                    |
| | ``ACQ:AXI:SOUR1:Write:Pos?`` > ``1024``          | | Python: ``rp_AcqAxiGetWritePointer(<channel>)``                                                                          | |                                                                               |                    |
| |                                                  | |                                                                                                                          | |                                                                               |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Pos?`` > ``<pos>``        | | C: ``rp_AcqAxiGetWritePointerAtTrig(rp_channel_t channel, uint32_t* pos)``                                               | | Returns position of Deep Memory write pointer at time when                    | 2.00-18 and up     |
| | Example:                                         | |                                                                                                                          | | the trigger arrived.                                                          |                    |
| | ``ACQ:AXI:SOUR1:Trig:Pos?`` > ``512``            | | Python: ``rp_AcqAxiGetWritePointerAtTrig(<channel>)``                                                                    | |                                                                               |                    |
| |                                                  | |                                                                                                                          | |                                                                               |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:DATA:Start:N? <pos>,<size>``   | | C: ``rp_AcqAxiGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)``                              | | Read ``count`` samples from the ``pos`` position onwards.                     | 2.00-18 and up     |
| | Example:                                         | |    ``rp_AcqAxiGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)``                         | | **SCPI:** Returns the value as a text array of values or a byte array.        |                    |
| | ``ACQ:AXI:SOUR1:DATA:Start:N? 20,3`` >           | | Python: ``rp_AcqAxiGetDataV(<channel>, <pos>, <size>, <buffer>)``                                                        | | Depending on the ``ACQ:AXI:DATA:UNITS`` setting.                              |                    |
| | ``{1.2,3.2,-1.2}``                               | |         ``rp_AcqAxiGetDataRaw(<channel>, <pos>, <size>, <buffer>)``                                                      | | **API:** Returns the Deep Memory buffer in specified units from specified     |                    |
| |                                                  | |                                                                                                                          | | position and desired size.                                                    |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+




.. _commads_uart:

====
UART
====

**Parameter options:**

- ``<bits> = {CS6, CS7, CS8}``  Default: ``CS8``
- ``<stop> = {STOP1, STOP2}``  Default: ``STOP1``
- ``<parity> = {NONE, EVEN, ODD, MARK, SPACE}``  Default: ``NONE``
- ``<timeout> = {0...255} in (1/10 seconds)`` Default: ``0``
- ``<speed> = {1200,2400,4800,9600,19200,38400,57600,115200,230400,576000,921000,1000000,1152000,1500000,2000000,2500000,3000000,3500000,4000000}`` Default: ``9600``
- ``<data> = {XXX, ... | #HXX, ... | #QXXX, ... | #BXXXXXXXX, ... }`` Array of data separated by commas

   - ``XXX`` = Dec format
   - ``#HXX`` = Hex format
   - ``#QXXX`` = Oct format
   - ``#BXXXXXXXX`` = Bin format

**Available Jupyter and API macros:**

- *(Future OS release)*


.. note::

    When establishing UART communication with Red Pitaya and another device, do not forget to connect the External Common Mode (GND) pin (in addition to the RX and TX pins). Otherwise, the communication might be unreliable.

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| SCPI                                | API, Jupyter                                                        | DESCRIPTION                                                                            |  ECOSYSTEM         |
+=====================================+=====================================================================+========================================================================================+====================+
| | ``UART:INIT``                     | | C: ``rp_UartInit()``                                              | Initialises the API for working with UART.                                             | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:INIT``                     | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:RELEASE``                  | | C: ``rp_UartRelease()``                                           | Releases all used resources.                                                           | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:RELEASE``                  | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SETUP``                    | | C: ``rp_UartSetSettings()``                                       | | Applies specified settings to UART.                                                  | 1.04-18 and up     |
| | Example:                          | |                                                                   | | Should be executed after communication parameters are set                            |                    |
| | ``UART:SETUP``                    | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:BITS <bits>``              | | C: ``rp_UartSetBits(rp_uart_bits_size_t _size)``                  | Sets the character size in bits.                                                       | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:BITS CS7``                 | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:BITS?`` > ``<bits>``       | | C: ``rp_UartGetBits(rp_uart_bits_size_t *value)``                 | Gets the character size in bits.                                                       | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:BITS?`` > ``CS7``          | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SPEED <speed>``            | | C: ``rp_UartSetSpeed(int value)``                                 | Sets the speed of the UART connection.                                                 | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:SPEED 115200``             | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SPEED?`` > ``<speed>``     | | C: ``rp_UartGetSpeed(int *value)``                                | Gets the speed of the UART connection.                                                 | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:SPEED?`` > ``115200``      | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:STOPB <stop>``             | | C: ``rp_UartSetStopBits(rp_uart_stop_bits_t _size)``              | Sets the length of the stop bit.                                                       | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:STOPB STOP2``              | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:STOPB?`` > ``<stop>``      | | C: ``rp_UartGetStopBits(rp_uart_stop_bits_t *value)``             | Gets the length of the stop bit.                                                       | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:STOPB?`` > ``STOP2``       | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:PARITY <parity>``          | | C: ``rp_UartSetParityMode(rp_uart_parity_t mode)``                | | Sets parity check mode.                                                              | 1.04-18 and up     |
| | Example:                          | |                                                                   | | - NONE  = Disable parity check                                                       |                    |
| | ``UART:PARITY ODD``               | | Python: ~                                                         | | - EVEN  = Set even mode for parity                                                   |                    |
| |                                   | |                                                                   | | - ODD   = Set odd mode for parity                                                    |                    |
| |                                   | |                                                                   | | - MARK  = Set Always 1                                                               |                    |
| |                                   | |                                                                   | | - SPACE = Set Always 0                                                               |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:PARITY?`` > ``<parity>``   | | C: ``rp_UartGetParityMode(rp_uart_parity_t *value)``              | Gets parity check mode.                                                                | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:PARITY?`` > ``ODD``        | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:TIMEOUT <timeout>``        | | C: ``rp_UartSetTimeout(uint8_t deca_sec)``                        | | Sets the timeout for reading from UART. 0 - Disable timeout. 1 = 1/10 sec.           | 1.04-18 and up     |
| | Example:                          | |                                                                   | | Example: 10 - 1 sec. Max timeout: 25.5 sec                                           |                    |
| | ``UART:TIMEOUT 10``               | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:TIMEOUT?`` > ``<timeout>`` | | C: ``rp_UartGetTimeout(uint8_t *value)``                          | Gets the timeout.                                                                      | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:TIMEOUT?`` > ``10``        | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:WRITE<n> <data>``          | | C: ``rp_UartWrite(unsigned char *buffer, int size)``              | Writes data to UART. ``<n>`` - the length of data sent to UART.                        | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:WRITE5 1,2,3,4,5``         | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:READ<n>?`` > ``<data>``    | | C: ``rp_UartRead(unsigned char *buffer, int *size)``              | Reads data from UART. ``<n>`` - the length of data retrieved from UART.                | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:READ5?`` > ``{1,2,3,4,5}`` | | Python: ~                                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+



.. _commands_spi:

====
SPI
====

**Parameter options:**

- ``<mode> = {LISL, LIST, HISL, HIST}``  Default: ``LISL``
- ``<cs_mode> = {NORMAL, HIGH}``  Default: ``NORMAL``
- ``<bits> = {7, 8}``  Default: ``8``
- ``<speed> = {1...100000000}`` Default: ``50000000``
- ``<data> = {XXX, ... | #HXX, ... | #QXXX, ... | #BXXXXXXXX, ... }`` Array of data separated by commas

   - ``XXX`` = Dec format
   - ``#HXX`` = Hex format
   - ``#QXXX`` = Oct format
   - ``#BXXXXXXXX`` = Bin format

**Available Jupyter and API macros:**

- *(Future OS release)*

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| SCPI                                       | API, Jupyter                                                                                                             | DESCRIPTION                                                                        |  ECOSYSTEM         |
+============================================+==========================================================================================================================+====================================================================================+====================+
| | ``SPI:INIT``                             | | C: ``rp_SPI_Init()``                                                                                                   | Initializes the API for working with SPI.                                          | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:INIT``                             | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:INIT:DEV <path>``                  | | C: ``rp_SPI_InitDevice(const char *_device)``                                                                          | | Initializes the API for working with SPI. ``<path>`` - Path to the SPI device.   | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        | | On some boards, it may be different from the standard: /dev/spidev1.0            |                    |
| | ``SPI:INIT:DEV "/dev/spidev1.0"``        | | Python:                                                                                                                | |                                                                                  |                    |
| |                                          | |                                                                                                                        | |                                                                                  |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:RELEASE``                          | | C: ``rp_SPI_Release()``                                                                                                | Releases all used resources.                                                       | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:RELEASE``                          | | Python:                                                                                                                |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:DEF``                     | | C: ``rp_SPI_SetDefaultSettings()``                                                                                     | Sets the settings for SPI to default values.                                       | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:SETtings:DEF``                     | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:SET``                     | | C: ``rp_SPI_SetSettings()``                                                                                            | | Sets the specified settings for SPI.                                             | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        | | Executed after specifying the parameters of communication.                       |                    |
| | ``SPI:SETtings:SET``                     | | Python:                                                                                                                | |                                                                                  |                    |
| |                                          | |                                                                                                                        | |                                                                                  |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:GET``                     | | C: ``rp_SPI_GetSettings()``                                                                                            | Gets the specified SPI settings.                                                   | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:SETtings:GET``                     | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:MODE <mode>``             | | C: ``rp_SPI_SetMode(rp_spi_mode_t mode)``                                                                              | | Sets the mode for SPI.                                                           | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        | | - LISL = Low idle level, Sample on leading edge                                  |                    |
| | ``SPI:SETtings:MODE LIST``               | | Python:                                                                                                                | | - LIST = Low idle level, Sample on trailing edge                                 |                    |
| |                                          | |                                                                                                                        | | - HISL = High idle level, Sample on leading edge                                 |                    |
| |                                          | |                                                                                                                        | | - HIST = High idle level, Sample on trailing edge                                |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:MODE?`` > ``<mode>``      | | C: ``rp_SPI_GetMode(rp_spi_mode_t *mode)``                                                                             | Gets the specified mode for SPI.                                                   | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:SETtings:MODE?`` > ``LIST``        | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:CSMODE <cs_mode>``        | | C: ``rp_SPI_SetCSMode(rp_spi_cs_mode_t mode)``                                                                         | | Sets the mode for CS.                                                            | 2.00-18 and up     |
| | Example:                                 | |                                                                                                                        | | - NORMAL = After the message is transmitted,                                     |                    |
| | ``SPI:SETtings:CSMODE NORMAL``           | | Python:                                                                                                                | | the CS line is set to the HIGH state.                                            |                    |
| |                                          | |                                                                                                                        | | - HIGH = After the message has been transmitted,                                 |                    |
| |                                          | |                                                                                                                        | | the CS line is set to the LOW state.                                             |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:CSMODE?`` > ``<cs_mode>`` | | C: ``rp_SPI_GetState(rp_spi_state_t *state)``                                                                          | Gets the specified CS mode for SPI.                                                | 2.00-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:SETtings:CSMODE?`` > ``NORMAL``    | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:SPEED <speed>``           | | C: ``rp_SPI_SetSpeed(int speed)``                                                                                      | Sets the speed of the SPI connection.                                              | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:SETtings:SPEED 1000000``           | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETings:SPEED?`` > ``<speed>``     | | C: ``rp_SPI_GetSpeed(int *speed)``                                                                                     | Gets the speed of the SPI connection.                                              | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:SETtings:SPEED?`` > ``1000000``    | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:WORD <bits>``             | | C: ``rp_SPI_SetWordLen(int len)``                                                                                      | Specifies the length of the word in bits. Must be greater than or equal to 7.      | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:SETtings:WORD 8``                  | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:SETtings:WORD?`` > ``<bits>``      | | C: ``rp_SPI_GetWordLen(int *len)``                                                                                     | Returns the length of a word.                                                      | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:SETtings:WORD?`` > ``8``           | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG:CREATE <n>``                   | | C: ``rp_SPI_CreateMessage(size_t len)``                                                                                | | Creates a message queue for SPI (reserves the space for data buffers)            | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        | | Once created, they need to be initialized.                                       |                    |
| | ``SPI:MSG:CREATE 1``                     | | Python:                                                                                                                | | ``<n>`` - The number of messages in the queue.                                   |                    |
|                                            | |                                                                                                                        | | The message queue can operate within a single CS state switch.                   |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG:DEL``                          | | C: ``rp_SPI_DestoryMessage()``                                                                                         | Deletes all messages and data buffers allocated for them.                          | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:MSG:DEL``                          | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG:SIZE?`` > ``<n>``              | | C: ``rp_SPI_GetMessageLen(size_t *len)``                                                                               | Returns the length of the message queue.                                           | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:MSG:SIZE?`` > ``1``                | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:TX<m> <data>``              | | C: ``rp_SPI_SetBufferForMessage(size_t msg,const uint8_t *tx_buffer,bool init_rx_buffer,size_t len, bool cs_change)``  | | Sets data for the write buffer for the specified message.                        | 1.04-18 and up     |
| | ``SPI:MSG<n>:TX<m>:CS <data>``           | |                                                                                                                        | | CS - Toggles CS state after sending/receiving this message.                      |                    |
| | Example:                                 | | Python:                                                                                                                | | ``<n>`` - index of message 0 <= n < msg queue size.                              |                    |
| | ``SPI:MSG0:TX4 1,2,3,4``                 | |                                                                                                                        | | ``<m>`` - TX buffer length.                                                      |                    |
| | ``SPI:MSG1:TX3:CS 2,3,4``                | |                                                                                                                        | | Sends ``<m>`` 'bytes' from message ``<n>``. No data is received.                 |                    |
| |                                          | |                                                                                                                        | |                                                                                  |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:TX<m>:RX <data>``           | | C: ``rp_SPI_SetBufferForMessage(size_t msg,const uint8_t *tx_buffer,bool init_rx_buffer,size_t len, bool cs_change)``  | | Sets data for the read and write buffers for the specified message.              | 1.04-18 and up     |
| | ``SPI:MSG<n>:TX<m>:RX:CS <data>``        | |                                                                                                                        | | CS - Toggles CS state after sending/receiving this message.                      |                    |
| | Example:                                 | | Python:                                                                                                                | | ``<n>`` - index of message 0 <= n < msg queue size.                              |                    |
| | ``SPI:MSG0:TX4:RX 1,2,3,4``              | |                                                                                                                        | | ``<m>`` - TX buffer length.                                                      |                    |
| | ``SPI:MSG1:TX3:RX:CS 2,3,4``             | |                                                                                                                        | | The read buffer is also created with the same length and initialized with zeros. |                    |
| |                                          | |                                                                                                                        | |                                                                                  |                    |
| |                                          | |                                                                                                                        | | Sends ``<m>`` 'bytes' from message ``<n>`` and receives the same amount of data  |                    |
| |                                          | |                                                                                                                        | |  from the dataline                                                               |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:RX<m>``                     | | C: ``rp_SPI_SetBufferForMessage(size_t msg,const uint8_t *tx_buffer,bool init_rx_buffer,size_t len, bool cs_change)``  | | Initializes a buffer for reading the specified message.                          | 1.04-18 and up     |
| | ``SPI:MSG<n>:RX<m>:CS``                  | |                                                                                                                        | | CS - Toggles CS state after receiving message.                                   |                    |
| | Example:                                 | | Python:                                                                                                                | | ``<n>`` - index of message 0 <= n < msg queue size.                              |                    |
| | ``SPI:MSG0:RX4``                         | |                                                                                                                        | | ``<m>`` - RX buffer length.                                                      |                    |
| | ``SPI:MSG1:RX5:CS``                      | |                                                                                                                        | |                                                                                  |                    |
| |                                          | |                                                                                                                        | | Receives ``<m>`` 'bytes' into message ``<n>``. No data is transmitted.           |                    |
| |                                          | |                                                                                                                        | |                                                                                  |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:RX?`` > ``<data>``          | | C: ``rp_SPI_GetRxBuffer(size_t msg,const uint8_t **buffer,size_t *len)``                                               | Returns a read buffer for the specified message.                                   | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:MSG1:RX?`` > ``{2,4,5}``           | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:TX?`` > ``<data>``          | | C: ``rp_SPI_GetTxBuffer(size_t msg,const uint8_t **buffer,size_t *len)``                                               | Returns the write buffer for the specified message.                                | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:MSG1:TX?`` > ``{2,4,5}``           | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:MSG<n>:CS?`` > ``ON|OFF``          | | C: ``rp_SPI_GetCSChangeState(size_t msg,bool *cs_change)``                                                             | Returns the setting for CS mode for the specified message.                         | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:MSG1:CS?`` > ``ON``                | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``SPI:PASS``                             | | C: ``rp_SPI_ReadWrite()``                                                                                              | Sends the prepared messages to the SPI device.                                     | 1.04-18 and up     |
| | Example:                                 | |                                                                                                                        |                                                                                    |                    |
| | ``SPI:PASS``                             | | Python:                                                                                                                |                                                                                    |                    |
| |                                          | |                                                                                                                        |                                                                                    |                    |
+--------------------------------------------+--------------------------------------------------------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+



.. _commands_i2c:

===
I2C
===

**Parameter options:**

- ``<mode> = {OFF, ON}``  Default: ``OFF``
- ``<value> = {XXX | #HXX | #QXXX | #BXXXXXXXX}``  Value in Decimal, Hexadecimal, Octal, or Binary format.
- ``<data> = {XXX, ... | #HXX, ... | #QXXX, ... | #BXXXXXXXX, ... }`` Array of data values separated by commas.

   - ``XXX`` = Dec format
   - ``#HXX`` = Hex format
   - ``#QXXX`` = Oct format
   - ``#BXXXXXXXX`` = Bin format

**Available Jupyter and API macros:**

- *(Future OS release)*

.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| SCPI                                             | API, Jupyter                                                                    | DESCRIPTION                                                           |  ECOSYSTEM         |
+==================================================+=================================================================================+=======================================================================+====================+
| | ``I2C:DEV<addr> <path>``                       | | C: ``rp_I2C_InitDevice(const char *_device,uint8_t addr)``                    | | Initializes settings for I2C.                                       | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | - ``<path>`` - Path to the I2C device.                              |                    |
| | ``I2C:DEV80 "/dev/i2c-0"``                     | | Python:                                                                       | | - ``<addr>`` - Device address on the I2C bus in dec format.         |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:DEV?`` > ``<addr>``                      | | C: ``rp_I2C_getDevAddress(int *address)``                                     | Returns the current address of the device.                            | 1.04-18 and up     |
| | Example:                                       | |                                                                               |                                                                       |                    |
| | ``I2C:DEV?`` > ``80``                          | | Python:                                                                       |                                                                       |                    |
| |                                                | |                                                                               |                                                                       |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:FMODE <mode>``                           | | C: ``rp_I2C_setForceMode(bool force)``                                        | Enables forced bus operation even if the device is in use.            | 1.04-18 and up     |
| | Example:                                       | |                                                                               |                                                                       |                    |
| | ``I2C:FMODE ON``                               | | Python:                                                                       |                                                                       |                    |
| |                                                | |                                                                               |                                                                       |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:FMODE?`` > ``<mode>``                    | | C: ``rp_I2C_getForceMode(bool *value)``                                       | Gets the current forced mode setting.                                 | 1.04-18 and up     |
| | Example:                                       | |                                                                               |                                                                       |                    |
| | ``I2C:FMODE?`` > ``ON``                        | | Python:                                                                       |                                                                       |                    |
| |                                                | |                                                                               |                                                                       |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>?`` > ``<value>``         | | C: ``rp_I2C_SMBUS_Read(uint8_t reg,uint8_t *value)``                          | | Reads 8 bit data from the specified register using                  | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | ``I2C:Smbus:Read2?`` > ``0``                   | | Python:                                                                       | | ``<reg>`` - Register address in dec format.                         |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>:Word?`` > ``<value>``    | | C: ``rp_I2C_SMBUS_ReadWord(uint8_t reg,uint16_t *value)``                     | | Reads 16 bit data from the specified register using                 | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | ``I2C:Smbus:Read2:Word?`` > ``0``              | | Python:                                                                       | | ``<reg>`` - Register address in dec format.                         |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>:Buffer<size>?`` >        | | C: ``rp_I2C_SMBUS_ReadBuffer(uint8_t reg, uint8_t *buffer, int *len)``        | | Reads buffer data from the specified register using                 | 1.04-18 and up     |
| |  ``<data>``                                    | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | Example:                                       | | Python:                                                                       | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:Smbus:Read2:Buffer2?`` > ``{0,1}``       | |                                                                               | | ``<size>`` - Read data size.                                        |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg> <value>``               | | C: ``rp_I2C_SMBUS_Write(uint8_t reg,uint8_t value)``                          | | Writes 8-bit data to the specified register using                   | 1.04-18 and up     |
| |                                                | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | Example:                                       | | Python:                                                                       | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:Smbus:Write2 10``                        | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg>:Word <value>``          | | C: ``rp_I2C_SMBUS_WriteWord(uint8_t reg,uint16_t value)``                     | | Writes 16-bit data to the specified register using                  | 1.04-18 and up     |
| |                                                | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | Example:                                       | | Python:                                                                       | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:Smbus:Write2:Word 10``                   | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg>:Buffer<size> <data>``   | | C: ``rp_I2C_SMBUS_WriteBuffer(uint8_t reg, uint8_t *buffer, int len)``        | | Writes buffer data to the specified register using                  | 1.04-18 and up     |
| |                                                | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | Example:                                       | | Python:                                                                       | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:Smbus:Write2:Buffer2 0,1``               | |                                                                               | | ``<size>`` - Read data size.                                        |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:IOctl:Read:Buffer<size>?`` > ``<data>``  | | C: ``rp_I2C_IOCTL_ReadBuffer(uint8_t *buffer, int len)``                      | | Reads data from the I2C device through IOCTL.                       | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | ``<size>`` - Read data size.                                        |                    |
| | ``I2C:IOctl:Read:Buffer2?`` > ``{0,1}``        | | Python:                                                                       | |                                                                     |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:IOctl:Write:Buffer<size> <data>``        | | C: ``rp_I2C_IOCTL_WriteBuffer(uint8_t *buffer, int len)``                     | | Writes data to the I2C device via IOCTL.                            | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | ``<size>`` - Read data size.                                        |                    |
| | ``I2C:IOctl:Write:Buffer2  {0,1}``             | | Python:                                                                       | |                                                                     |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+


.. note::

   SMBUS is a standardized protocol for communicating with I2C devices. Information about this protocol can be found in this link: |SMBUS specs|. IOCTL writes and reads data directly from I2C.

.. |SMBUS specs| raw:: html

    <a href="http://smbus.org/specs/" target="_blank">SMBUS specifcations</a>



.. _commands_can:

===
CAN
===

.. note::

   FPGA image *v0.94* is required to work with CAN.

**Parameter options:**

- ``<n> = {0,1}`` CAN interface
- ``<bool> = {OFF, ON}``
- ``<state> = {ERROR_ACTIVE, ERROR_WARNING, ERROR_PASSIVE, BUS_OFF, STOPPED, SLEEPING}``
- ``<mode> = {LOOPBACK, BERR_REPORTING}``
- ``<speed> = {1, 10000000}``
- ``<sp> = {0, 0.999}``
- ``<tq> = {unsigned integer}``
- ``<prop_seg> = {unsigned integer}``
- ``<phase_seg1> = {unsigned integer}``
- ``<phase_seg2> = {unsigned integer}``
- ``<sjw> = {unsigned integer}``
- ``<brp> = {unsigned integer}``
- ``<tseg1_min> = {unsigned integer}``
- ``<tseg2_min> = {unsigned integer}``
- ``<tseg2_min> = {unsigned integer}``
- ``<tseg2_max> = {unsigned integer}``
- ``<sjw_max> = {unsigned integer}``
- ``<brp_min> = {unsigned integer}``
- ``<brp_max> = {unsigned integer}``
- ``<brp_inc> = {unsigned integer}``
- ``<limits> = {<tseg1_min>, <tseg2_min>, <tseg2_min>, <tseg2_max>, <sjw_max>, <brp_min>, <brp_max>, <brp_inc>}``
- ``<clock> = {1...10000000}`` in Hz
- ``<tx_err> = {unsigned integer}``
- ``<rx_err> = {unsigned integer}``
- ``<rs_ms> = {unsigned integer}`` in milliseconds
- ``<can_id> = {unsigned integer}`` Destination address on CAN bus
- ``<buffer> = {XXX | XXX,XXX | XXX,XXX,XXX | XXX,...,XXX}`` Bytes for send from 0 to 8
- ``<timeout> = {unsigned integer}`` in milliseconds. ``0`` - timeout disabled
- ``<frame_header> = {unsigned integer}``
- ``<is_extended> = {0,1}``
- ``<is_error> = {0,1}``
- ``<is_rtr> = {0,1}``
- ``<frame> = {<can_id>, <frame_header>, <is_extended>, <is_error>, <is_rtr>, {<buffer>}}``
- ``<filter> = {unsigned integer}``
- ``<mask> = {unsigned integer}``


**Available Jupyter and API macros:**

- *(Future OS release)*


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| SCPI                                                                                | API, Jupyter                                                                  | DESCRIPTION                                                                 |  ECOSYSTEM         |
+=====================================================================================+===============================================================================+=============================================================================+====================+
| | ``CAN:FPGA <bool>``                                                               | | C: ``rp_CanSetFPGAEnable``                                                  | Enables FPGA forwarding from CAN controller to GPIO.                        | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN:FPGA ON``                                                                   | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN:FPGA?`` > ``<bool>``                                                        | | C: ``rp_CanGetFPGAEnable``                                                  | Gets the status from the FPGA of the CAN mode status.                       | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN:FPGA?`` > ``ON``                                                            | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:START``                                                                  | | C: ``rp_CanStart``                                                          | Sets the state of the specified interface to UP.                            | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:START``                                                                    | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:STOP``                                                                   | | C: ``rp_CanStop``                                                           | Sets the state of the specified interface to DOWN.                          | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:STOP``                                                                     | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:RESTART``                                                                | | C: ``rp_CanRestart``                                                        | Restarts the specified interface.                                           | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:RESTART``                                                                  | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:STATE?`` > ``<state>``                                                   | | C: ``rp_CanGetState``                                                       | | Returns the current state of the CAN interface.                           | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | ERROR_ACTIVE - RX/TX error count < 96                                     |                    |
| | ``CAN0:STATE?`` > ``ERROR_ACTIVE``                                                | | Python:                                                                     | | ERROR_WARNING - RX/TX error count < 128                                   |                    |
| |                                                                                   | |                                                                             | | ERROR_PASSIVE - RX/TX error count < 256                                   |                    |
| |                                                                                   | |                                                                             | | BUS_OFF - RX/TX error count >= 256                                        |                    |
| |                                                                                   | |                                                                             | | STOPPED - Device is stopped                                               |                    |
| |                                                                                   | |                                                                             | | SLEEPING - Device is sleeping                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITRate <speed>``                                                        | | C: ``rp_CanSetBitrate``                                                     | | Sets the bitrate for the specified interface. Sample point is             | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | set automatically.                                                        |                    |
| | ``CAN0:BITRate 200000``                                                           | | Python:                                                                     | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITRate:SP <speed>,<sp>``                                                | | C: ``rp_CanSetBitrateAndSamplePoint``                                       | Sets the bitrate and sample point for the specified interface.              | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:BITRate:SP 200000,0.8``                                                    | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITRate:SP?`` > ``<speed>,<sp>``                                         | | C: ``rp_CanGetBitrateAndSamplePoint``                                       | | Shows the real bit-rate in bits/sec and the sample-point in the           | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | range 0.000...0.999. If the calculation of bit-timing parameters          |                    |
| | ``CAN0:BITRate:SP?`` > ``200000,0.8``                                             | | Python:                                                                     | | is enabled in the kernel (CONFIG_CAN_CALC_BITTIMING=y), the               |                    |
| |                                                                                   | |                                                                             | | bit-timing can be defined by setting the "bitrate" argument.              |                    |
| |                                                                                   | |                                                                             | | Optionally, the "sample-point" can be specified. By default it's          |                    |
| |                                                                                   | |                                                                             | | 0.000 assuming CIA-recommended sample-points.                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITTiming <tq>,<prop_seg>,<phase_seg1>,<phase_seg2>,<sjw>,<brp>``        | | C: ``rp_CanSetBitTiming``                                                   | Set bit-timing settings.                                                    | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:BITTiming 1000,1,2,1,1,10``                                                | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITTiming?`` > ``<tq>,<prop_seg>,<phase_seg1>,<phase_seg2>,<sjw>,<brp>`` | | C: ``rp_CanGetBitTiming``                                                   | | Shows the time quanta in ns, propagation segment, phase buffer            | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | segment 1 and 2, and the synchronisation jump width in units of           |                    |
| | ``CAN0:BITTiming?`` > ``1000,1,2,1,1,10``                                         | | Python:                                                                     | | tq. They allow to define the CAN bit-timing in a hardware                 |                    |
| |                                                                                   | |                                                                             | | independent format as proposed by the Bosch CAN 2.0 spec (Chapter 8).     |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BITTiming:Limits?`` > ``<limits>``                                       | | C: ``rp_CanGetBitTimingLimits``                                             | | Shows the bit-timing constants of the CAN controller (here the            | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | "sja1000"), the minimum and maximum values of the time segment 1          |                    |
| | ``CAN0:BITTiming:Limits?`` > ``1,16,1,8,4,1,256,1``                               | | Python:                                                                     | | and 2, the synchronisation jump width in units of tq, the                 |                    |
| |                                                                                   | |                                                                             | | bitrate pre-scaler, and the CAN system clock frequency in Hz.             |                    |
| |                                                                                   | |                                                                             | | These constants can be used for user-defined (non-standard)               |                    |
| |                                                                                   | |                                                                             | | bit-timing calculation algorithms in user-space.                          |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:CLOCK?`` > ``<clock>``                                                   | | C: ``rp_CanGetClockFreq``                                                   | Returns the clock value in Hz.                                              | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:CLOCK?`` > ``10000000``                                                    | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:BUS:ERROR?`` > ``<tx_err>,<rx_err>``                                     | | C: ``rp_CanGetBusErrorCounters``                                            | Returns the number of errors on the bus.                                    | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:BUS:ERROR?`` > ``0,0``                                                     | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Restart:Time <rs_ms>``                                                   | | C: ``rp_CanSetRestartTime``                                                 | | Automatic restart delay time. If set to a non-zero value, a               | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | restart of the CAN controller will be triggered automatically,            |                    |
| | ``CAN0:Restart:Time 10``                                                          | | Python:                                                                     | | in case of a bus-off condition after the specified delay time             |                    |
| |                                                                                   | |                                                                             | | in milliseconds. By default it's OFF.                                     |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Restart:Time?`` > ``<rs_ms>``                                            | | C: ``rp_CanGetRestartTime``                                                 | Returns current settings for restart-ms.                                    | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:Restart:Time?`` > ``10``                                                   | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:MODE <mode>,<bool>``                                                     | | C: ``rp_CanSetControllerMode``                                              | Sets the controller mode.                                                   | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:MODE LOOPBACK,ON``                                                         | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:MODE? <mode>`` > ``<bool>``                                              | | C: ``rp_CanGetControllerMode``                                              | Checks the status of the selected mode.                                     | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:MODE? LOOPBACK`` > ``ON``                                                  | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:OPEN``                                                                   | | C: ``rp_CanOpen``                                                           | Opens a socket connection for the specified interface.                      | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:OPEN``                                                                     | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:CLOSE``                                                                  | | C: ``rp_CanClose``                                                          | Closes an open connection.                                                  | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:CLOSE``                                                                    | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id> <buffer>``                                                  | | C: ``rp_CanSend``                                                           | Sends the frame to the specified address.                                   | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:Send123 1,2,3``                                                            | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:RTR <buffer>``                                              | | C: ``rp_CanSend``                                                           | | Sends the frame to the specified address marked as                        | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | the "Remote Transmission Request".                                        |                    |
| | Example:                                                                          | | Python:                                                                     | |                                                                           |                    |
| | ``CAN0:Send123 1,2,3``                                                            | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Timeout<timeout> <buffer>``                                 | | C: ``rp_CanSend``                                                           | | Sends the frame to the specified address.                                 | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | There is a timeout for sending if the send buffer is full.                |                    |
| | ``CAN0:Send123:Timeout2000 1,2,3``                                                | | Python:                                                                     | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Ext``                                                       | | C: ``rp_CanSend``                                                           | | Sends the extended frame to the specified address.                        | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | Sends an extended packet for can_id.                                      |                    |
| | ``CAN0:Send123:Ext 1,2,3``                                                        | | Python:                                                                     | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Timeout<timeout>:Ext <buffer>``                             | | C: ``rp_CanSend``                                                           | | Sends the extended frame to the specified address.                        | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | There is a timeout for sending if the send buffer is full.                |                    |
| | ``CAN0:Send123:Timeout2000:Ext 1,2,3``                                            | | Python:                                                                     | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Timeout<timeout>:RTR <buffer>``                             | | C: ``rp_CanSend``                                                           | | Sends the frame to the specified address marked as                        | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | the "Remote Transmission Request".                                        |                    |
| | ``CAN0:Send123:Timeout2000:RTR 1,2,3``                                            | | Python:                                                                     | | There is a timeout for sending if the send buffer is full.                |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Ext:RTR``                                                   | | C: ``rp_CanSend``                                                           | | Sends the extended frame to the specified address marked as               | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | the "Remote Transmission Request".                                        |                    |
| | ``CAN0:Send123:Ext:RTR 1,2,3``                                                    | | Python:                                                                     | | Sends an extended packet for can_id.                                      |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Send<can_id>:Timeout<timeout>:Ext:RTR <buffer>``                         | | C: ``rp_CanSend``                                                           | | Sends the extended frame to the specified address marked as               | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | the "Remote Transmission Request".                                        |                    |
| | ``CAN0:Send123:Timeout2000:Ext:RTR 1,2,3``                                        | | Python:                                                                     | | There is a timeout for sending if the send buffer is full.                |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Read?`` > ``<frame>``                                                    | | C: ``rp_CanRead``                                                           | Reads from socket 1 frame.                                                  | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:Read?`` > ``123,123,0,0,0,3,{1,2,3}``                                      | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Read:Timeout<timeout>?`` > ``<frame>``                                   | | C: ``rp_CanRead``                                                           | | Reads from socket 1 frame. Waits for the specified time,                  | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | otherwise returns an empty.                                               |                    |
| | ``CAN0:Read:Timeout2000?`` > ``123,123,0,0,0,3,{1,2,3}``                          | | Python:                                                                     | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Filter:Add <filter>,<mask>``                                             | | C: ``rp_CanAddFilter``                                                      | | Adds another filter to the list of filters.                               | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | Once all filters have been added, the command to                          |                    |
| | ``CAN0:Filter:Add 0,0``                                                           | | Python:                                                                     | | apply filters on the socket must be invoked ``CAN<n>:Filter:Set.``        |                    |
| |                                                                                   | |                                                                             | | A filter matches, when                                                    |                    |
| |                                                                                   | |                                                                             | | <received_can_id> & mask == filter & mask                                 |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Filter:Remove <filter>,<mask>``                                          | | C: ``rp_CanRemoveFilter``                                                   | Deletes the specified filter from the filter list.                          | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:Filter:Remove 0,0``                                                        | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Filter:Clear``                                                           | | C: ``rp_CanRemoveFilter``                                                   | Removes all filters from the list.                                          | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:Filter:Clear``                                                             | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:Filter:Set``                                                             | | C: ``rp_CanSetFilter``                                                      | Applies a list of filters to the socket connection.                         | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             |                                                                             |                    |
| | ``CAN0:Filter:Set``                                                               | | Python:                                                                     |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
| |                                                                                   | |                                                                             |                                                                             |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+
| | ``CAN<n>:SHOW:ERROR``                                                             | | C: ``rp_CanShowErrorFrames``                                                | | When this mode is enabled, all errors will be                             | 2.00-30 and up     |
| | Example:                                                                          | |                                                                             | | converted through data frames with the error frame marking.               |                    |
| | ``CAN0:SHOW:ERROR``                                                               | | Python:                                                                     | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
| |                                                                                   | |                                                                             | |                                                                           |                    |
+-------------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------+--------------------+



.. _commands_status_leds:

=============
Status LEDs
=============

**Parameter options:**

- ``<enable> = {OFF, ON}``  Default: ``ON``

**Available Jupyter and API macros:**

- *(Future OS release)*


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| SCPI                                | API, Jupyter                                      | DESCRIPTION                                                                        |  ECOSYSTEM         |
+=====================================+===================================================+====================================================================================+====================+
| | ``LED:MMC <enable>``              | | C: ``rp_SetLEDMMCState(bool _enable)``          | Turn the Orange LED on or off (responsible for indicating the read memory card).   | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:MMC OFF``                   | | Python:                                         |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:MMC?`` > ``<enable>``       | | C: ``rp_GetLEDMMCState(bool *_enable)``         | Get the state of the MMC indicator.                                                | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:MMC?`` > ``ON``             | | Python:                                         |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:HB <enable>``               | | C: ``rp_SetLEDHeartBeatState(bool _enable)``    | Turn the Red LED on or off (responsible for indicating board activity).            | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:HB OFF``                    | | Python:                                         |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:HB?`` > ``<enable>``        | | C: ``rp_GetLEDMMCState(bool *_enable)``         | Get the state of the HeartBeat indicator (Red LED).                                | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:HB?`` > ``ON``              | | Python:                                         |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:ETH <enable>``              | | C: ``rp_SetLEDEthState(bool _enable)``          | Turn the LED indicators on the Ethernet connector on or off.                       | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:ETH OFF``                   | | Python:                                         |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:ETH?`` > ``<enable>``       | | C: ``rp_GetLEDMMCState(bool *_enable)``         | Ges the state of the Ethernet indicators.                                          | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:ETH?`` > ``ON``             | | Python:                                         |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+







.. _commands_temp_prot:

========================
Temperature protection
========================

.. note::

    These commands are available only on SIGNALlab 250-12

**Parameter options:**

- ``<enable> = {true, false}``

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``


.. tabularcolumns:: |p{28mm}|p{28mm}|p{28mm}|p{28mm}|

+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| SCPI                                | API, Jupyter                                                                | DESCRIPTION                                                                        |  ECOSYSTEM         |
+=====================================+=============================================================================+====================================================================================+====================+
| | -                                 | | C: ``rp_SetEnableTempProtection(rp_channel_t channel, bool enable)``      | | Enable/disable the DAC overheating protection mode for the specified fast analog | 1.04-18 and up     |
| |                                   | |                                                                           | | output (SIGNALlab 250-12 only).                                                  |                    |
| |                                   | | Python: ``rp_SetEnableTempProtection(<channel>, <enable>)``               | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C: ``rp_GetEnableTempProtection(rp_channel_t channel, bool *enable)``     | | Get the Enable/disable DAC overheating protection mode setting for the specified | 1.04-18 and up     |
| |                                   | |                                                                           | | fast analog output (SIGNALlab 250-12 only).                                      |                    |
| |                                   | | Python: ``rp_GetEnableTempProtection(<channel>)``                         | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C: ``rp_SetLatchTempAlarm(rp_channel_t channel, bool status)``            | | Reset the flag indicating that the DAC is overheated for the specified fast      | 1.04-18 and up     |
| |                                   | |                                                                           | | analog output (SIGNALlab 250-12 only).                                           |                    |
| |                                   | | Python: ``rp_SetLatchTempAlarm(<channel>, <status>)``                     | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C: ``rp_GetLatchTempAlarm(rp_channel_t channel, bool *status)``           | | Return the flag status indicating that the DAC is overheated for the specified   | 1.04-18 and up     |
| |                                   | |                                                                           | | fast analog output (SIGNALlab 250-12 only).                                      |                    |
| |                                   | | Python: ``rp_GetLatchTempAlarm(<channel>)``                               | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | -                                 | | C: ``rp_GetRuntimeTempAlarm(rp_channel_t channel, bool *status)``         | | Returns the current DAC overheat status in real time (SIGNALlab 250-12 only).    | 1.04-18 and up     |
| |                                   | |                                                                           | |                                                                                  |                    |
| |                                   | | Python: ``rp_GetRuntimeTempAlarm(<channel>)``                             | |                                                                                  |                    |
| |                                   | |                                                                           | |                                                                                  |                    |
+-------------------------------------+-----------------------------------------------------------------------------+------------------------------------------------------------------------------------+--------------------+

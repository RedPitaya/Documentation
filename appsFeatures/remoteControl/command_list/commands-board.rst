
.. _commands_board:

======================
Board control commands
======================

Functionality overview
------------------------

Board control commands provide general information about the Red Pitaya board, such as its ID, version, and date/time settings. They allow you to set general parameters for how the board operates, including logging modes and error handling.
These commands are essential for managing the board's configuration and ensuring it operates correctly.

They are meant to be executed once at the start of the application during the initialisation phase.


Important notes
----------------

*   ``RP:RET_ON_ERROR <bool>`` command is a non-standard SCPI command feature that enables a special mode for compatibility with older SCPI clients. When this mode is enabled, if errors occur when executing query commands, the server will return empty data with delimiters "\r\n", 
    which will prevent SCPI data or parameter requests to end in an infinite waiting-for-return loop when an error occurs on the Red Pitaya side. This is useful for maintaining compatibility with legacy systems that expect this behavior.


Code examples
-----------------

Since these commands are meant to be a one-time setup, no special code examples are provided.


Parameters and command table
-----------------------------

**Parameter options:**

- ``<year> = {1900, ...}`` Default: ``OS release date and time``
- ``<bool> = {OFF, ON}`` Default: ``OFF``
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

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| SCPI                                                 | API, Jupyter                                     | DESCRIPTION                                               |  ECOSYSTEM             |
+======================================================+==================================================+===========================================================+========================+
| | ``RP:LOGmode <log_mode>``                          | | -                                              | Enables scpi-server log output mode.                      | 1.04-18 and up         |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``RP:LOGmode SYSLOG``                              | |                                                |                                                           |                        |
| |                                                    | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``RP:RET_ON_ERROR <bool>``                         | | N/A                                            | | Enables a special mode for compatibility                | 2.07-43 and up         |
| | Examples:                                          | |                                                | | with older SCPI clients. When this mode is enabled,     |                        |
| | ``RP:RET_ON_ERROR ON``                             | |                                                | | if errors occur when executing query commands,          |                        |
| |                                                    | |                                                | | the server will return empty data with delimiters "\r\n"|                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:TIME <hours>,<minutes>,<seconds>``        | | -                                              | Sets the time on the board.                               | 2.00-18 and 2.00-36    |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:TIME 16,12,45``                           | |                                                |                                                           |                        |
| | ``SYST:TIME 11,23,01``                             | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:TIME "<hours>:<minutes>:<seconds>"``      | | -                                              | Sets the time on the board.                               | 2.05-37 and up         |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:TIME "16:12:45"``                         | |                                                |                                                           |                        |
| | ``SYST:TIME "11:23:01"``                           | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:TIME?`` > ``time``                        | | -                                              | Returns the current time on the board.                    | 2.00-18 and up         |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:TIME?`` > ``16:12:45``                    | |                                                |                                                           |                        |
| | ``SYST:TIME?`` > ``11:23:01``                      | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:DATE <year>,<month>,<day>``               | | -                                              | Sets the date on the board.                               | 2.00-18 and 2.00-36    |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:DATE 2023,04,04``                         | |                                                |                                                           |                        |
| | ``SYST:DATE 2002,12,29``                           | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:DATE "<year>-<month>-<day>"``             | | -                                              | Sets the date on the board.                               | 2.05-37 and up         |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:DATE "2023-04-04"``                       | |                                                |                                                           |                        |
| | ``SYST:DATE "2002-12-29"``                         | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:DATE?`` > ``date``                        | | -                                              | Returns the current date on the board.                    | 2.00-18 and up         |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:DATE?`` > ``2023-04-04``                  | |                                                |                                                           |                        |
| | ``SYST:DATE?`` > ``2002-12-29``                    | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:BRD:ID?`` > ``<board_id>``                | | C: ``rp_IdGetID(uint32_t *id)``                | Returns the Red Pitaya board ID.                          | 2.00-18 and up         |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:BRD:ID?`` > ``1``                         | | Python: ``rp_IdGetID()``                       |                                                           |                        |
| |                                                    | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:BRD:Name?`` > ``board name``              | | C: ``const char* rp_GetVersion()``             | Returns the Red Pitaya board version.                     | 2.00-18 and up         |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:BRD:Name?`` > ``STEMlab 125-14 v1.0``     | | Python: ``rp_GetVersion()``                    |                                                           |                        |
| |                                                    | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:VERSion?`` > ``OS version``               | | C: -                                           | Returns the Red Pitaya OS version.                        | IN DEV                 |
| | Examples:                                          | |                                                |                                                           |                        |
| | ``SYSTem:VERSion?`` > ``2.07-651``                 | | Python: -                                      |                                                           |                        |
| |                                                    | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | ``SYSTem:Help?`` > ``<List of SCPI commands>``     | | -                                              | | Returns a list of all commands                          | 2.04-35 and up         |
| | Examples:                                          | |                                                | | that the SCPI server can process.                       |                        |
| | ``SYSTem:Help?`` > ``*CLS\n*ESE\n...``             | |                                                |                                                           |                        |
| |                                                    | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | -                                                  | | C: ``rp_IdGetDNA(uint64_t *dna)``              | Returns the unique DNA code of the FPGA chip.             | 2.00-18 and up         |
| |                                                    | |                                                |                                                           |                        |
| |                                                    | | Python: ``rp_IdGetDNA()``                      |                                                           |                        |
| |                                                    | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | -                                                  | | C: ``const char* rp_GetError(int errorCode)``  | Returns the description of the input error code.          | 2.00-18 and up         |
| |                                                    | |                                                |                                                           |                        |
| |                                                    | | Python: ``rp_GetError(<errorCode>)``           |                                                           |                        |
| |                                                    | |                                                |                                                           |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+
| | -                                                  | | C: ``rp_EnableDigitalLoop(bool enable)``       | | Enables/disables the Digital Loop (internal FPGA        | 2.00-18 and up         |
| |                                                    | |                                                | | connection between fast analog inputs and outputs).     |                        |
| |                                                    | | Python: ``rp_EnableDigitalLoop(<enable>)``     | |                                                         |                        |
| |                                                    | |                                                | |                                                         |                        |
+------------------------------------------------------+--------------------------------------------------+-----------------------------------------------------------+------------------------+

|

* :ref:`Back to top <commands_board>`
* :ref:`Back to command list <command_list>`
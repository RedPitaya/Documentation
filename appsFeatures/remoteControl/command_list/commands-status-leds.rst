
.. _commands_status_leds:

=============
Status LEDs
=============

Functionality overview
------------------------

Status LED commands control the operational behavior of Red Pitaya's status LEDs. Enable or disable the automatic LED patterns that indicate system status, allowing manual LED control for custom applications.


Important notes
----------------

* Default state is ON (automatic status indication).
* Disabling the Ethernet LEDs will help reduce the fast analog input and output noise on the :ref:`Original generation <dev_guide_hardware>` of boards.


Code examples
-----------------

[To be added - examples specific to Status LEDs]


Parameters and command table
-----------------------------

**Parameter options:**

- ``<enable> = {OFF, ON}``  Default: ``ON``

**Available Jupyter and API macros:**

- NA


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| SCPI                                | API, Jupyter                                      | DESCRIPTION                                                                        |  ECOSYSTEM         |
+=====================================+===================================================+====================================================================================+====================+
| | ``LED:MMC <enable>``              | | C++: ``rp_SetLEDMMCState(bool enable)``         | Turn the Orange LED on or off (responsible for indicating the read memory card).   | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:MMC OFF``                   | | Python: ``rp_SetLEDMMCState(<enable>)``         |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:MMC?`` > ``<enable>``       | | C++: ``rp_GetLEDMMCState(bool *enable)``        | Get the state of the MMC indicator.                                                | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:MMC?`` > ``ON``             | | Python: ``rp_GetLEDMMCState()``                 |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:HB <enable>``               | | C++: ``rp_SetLEDHeartBeatState(bool enable)``   | Turn the Red LED on or off (responsible for indicating board activity).            | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:HB OFF``                    | | Python: ``rp_SetLEDHeartBeatState(<enable>)``   |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:HB?`` > ``<enable>``        | | C++: ``rp_GetLEDHeartBeatState(bool *enable)``  | Get the state of the HeartBeat indicator (Red LED).                                | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:HB?`` > ``ON``              | | Python: ``rp_GetLEDHeartBeatState()``           |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:ETH <enable>``              | | C++: ``rp_SetLEDEthState(bool enable)``         | Turn the Ethernet LED indicators on or off.                                        | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:ETH OFF``                   | | Python: ``rp_SetLEDEthState(<enable>)``         |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+
| | ``LED:ETH?`` > ``<enable>``       | | C++: ``rp_GetLEDEthState(bool *enable)``        | Get the state of the Ethernet indicators.                                          | 1.04-18 and up     |
| | Example:                          | |                                                 |                                                                                    |                    |
| | ``LED:ETH?`` > ``ON``             | | Python: ``rp_GetLEDEthState()``                 |                                                                                    |                    |
| |                                   | |                                                 |                                                                                    |                    |
+-------------------------------------+---------------------------------------------------+------------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_status_leds>`
* :ref:`Back to command list <command_list>`


.. _commands_init:

=========================
Initialization commands
=========================

Functionality overview
------------------------

Initialization commands prepare the Red Pitaya's hardware and software interfaces for operation. These commands must be called before using any other API functions to ensure proper hardware configuration and memory allocation.


Important notes
----------------

* Always call initialization commands before any other API operations.
* For API programs, ``rp_Init()`` must be the first command executed.
* SCPI server handles initialization automatically when connection is established.


Code examples
-----------------

Here are some examples of how to use the initialization commands on Red Pitaya:

* :ref:`Examples using API commands <examples>`.


Parameters and command table
-----------------------------

Table of correlated SCPI and API commands for the Red Pitaya.

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

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

|

* :ref:`Back to top <commands_init>`
* :ref:`Back to command list <command_list>`

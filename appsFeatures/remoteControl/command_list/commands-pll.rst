
.. _commands_pll:

==================
Phase locked loop
==================

.. note::

   These commands only work on SIGNALlab 250-12


**Parameter options:**

- ``<enable> = {OFF, ON}``
- ``<status> = {true, false}``

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-----------------------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| SCPI                                                | API, Jupyter                                                                       | DESCRIPTION                                                                       |  ECOSYSTEM         |
+=====================================================+====================================================================================+===================================================================================+====================+
| | ``RP:PLL:ENable <enable>``                        | | C: ``rp_SetPllControlEnable(bool enable)``                                       | | Enables/disables PLL control (SIGNALlab 250-12 only).                           | 2.04-35 and up     |
| | Examples:                                         | |                                                                                  | | Enables synchronisation with the 10 MHz reference clock connected to the        |                    |
| | ``RP:PLL:ENable ON``                              | | Python: ``rp_SetPllControlEnable(<enable>)``                                     | | SMA connector at the back.                                                      |                    |
| |                                                   | |                                                                                  | |                                                                                 |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``RP:PLL:ENable?`` > ``<enable>``                 | | C: ``rp_GetPllControlEnable(bool *enable)``                                      | Get the state of the PLL enable setting (SIGNALlab 250-12 only).                  | 2.04-35 and up     |
| | Examples:                                         | |                                                                                  |                                                                                   |                    |
| | ``RP:PLL:ENable?`` > ``ON``                       | | Python: ``rp_GetPllControlEnable()``                                             |                                                                                   |                    |
| |                                                   | |                                                                                  |                                                                                   |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``RP:PLL:STATE?`` > ``<status>``                  | | C: ``rp_GetPllControlLocked(bool *status)``                                      | | Get the status of the PLL synchronisation with the reference clock              | 2.04-35 and up     |
| | Examples:                                         | |                                                                                  | | ``1`` - Unit is synced with the reference clock                                 |                    |
| | ``RP:PLL:STATE?`` > ``1``                         | | Python: ``rp_GetPllControlLocked()``                                             | | ``0`` - Unit is not synced with the reference clock                             |                    |
| |                                                   | |                                                                                  | | (SIGNALlab 250-12 only).                                                        |                    |
+-----------------------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_pll>`
* :ref:`Back to command list <command_list>`

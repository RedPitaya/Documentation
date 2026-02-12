:orphan:

.. _commands_logic_analyzer:

=================
Logic Analyzer
=================



Functionality overview
------------------------




Important notes
----------------



Code examples
-----------------

Here are some examples of how to use the Logic analyzer commands on Red Pitaya:

* :ref:`Digital communication examples <examples_digcom>`.



Parameters and command table
-----------------------------

**Parameter options:**

- ``<shunt> = {1 ... 100000000}`` (in Hertz). Default: ``100``


**Available Jupyter and API macros:**

- *(Future OS release)*


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+
| SCPI                                      | API, Jupyter                                                     | DESCRIPTION                                                                         |  ECOSYSTEM         |
+===========================================+==================================================================+=====================================================================================+====================+
| | ``LCR:START``                           | | C++: ``lcrApp_LcrRun()``                                       | | Starts the LCR processing thread and resets settings to default.                  | 2.05-37 and up     |
| | Example:                                | |                                                                | | Settings for the generator need to be made after starting the thread.             |                    |
| | ``LCR:START``                           | | Python:                                                        |                                                                                     |                    |
| |                                         | |                                                                |                                                                                     |                    |
+-------------------------------------------+------------------------------------------------------------------+-------------------------------------------------------------------------------------+--------------------+















|

* :ref:`Back to top <commands_logic_analyzer>`
* :ref:`Back to command list <command_list>`


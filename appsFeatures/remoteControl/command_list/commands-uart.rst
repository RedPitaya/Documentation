
.. _commands_uart:

====
UART
====

Functionality overview
------------------------

UART commands provide serial communication capabilities through Red Pitaya's extension connector. Configure baud rate, data bits, parity, and stop bits to interface with serial devices, sensors, and other microcontrollers.


Important notes
----------------

* Always connect External Common Mode (GND) pin in addition to RX and TX for reliable communication.
* Default settings: 9600 baud, 8 data bits, no parity, 1 stop bit.
* Supported baud rates from 1200 to 4,000,000.


Code examples
-----------------

Here are some examples of how to use UART communication:

* :ref:`Digital communication examples <examples_digcom>`.
* :ref:`Logic analyzer examples <examples_la>`.


Parameters and command table
-----------------------------

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

- UART bit size - ``RP_UART_CS6, RP_UART_CS7, RP_UART_CS8``
- UART stop bits - ``RP_UART_STOP1, RP_UART_STOP2``
- UART parity mode - ``RP_UART_NONE, RP_UART_EVEN, RP_UART_ODD, RP_UART_MARK, RP_UART_SPACE``

.. note::

    When establishing UART communication with Red Pitaya and another device, do not forget to connect the External Common Mode (GND) pin (in addition to the RX and TX pins). Otherwise, the communication might be unreliable.


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| SCPI                                | API, Jupyter                                                        | DESCRIPTION                                                                            |  ECOSYSTEM         |
+=====================================+=====================================================================+========================================================================================+====================+
| | ``UART:INIT``                     | | C++: ``rp_UartInit()``                                            | Initialises the API for working with UART.                                             | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:INIT``                     | | Python: ``rp_UartInit()``                                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:RELEASE``                  | | C++: ``rp_UartRelease()``                                         | Releases all used resources.                                                           | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:RELEASE``                  | | Python: ``rp_UartRelease()``                                      |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SETUP``                    | | C++: ``rp_UartSetSettings()``                                     | | Applies specified settings to UART.                                                  | 1.04-18 and up     |
| | Example:                          | |                                                                   | | Should be executed after communication parameters are set                            |                    |
| | ``UART:SETUP``                    | | Python: ``rp_UartSetSettings()``                                  |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:BITS <bits>``              | | C++: ``rp_UartSetBits(rp_uart_bits_size_t _size)``                | Sets the character size in bits.                                                       | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:BITS CS7``                 | | Python: ``rp_UartSetBits(<size>)``                                |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:BITS?`` > ``<bits>``       | | C++: ``rp_UartGetBits(rp_uart_bits_size_t *value)``               | Gets the character size in bits.                                                       | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:BITS?`` > ``CS7``          | | Python: ``rp_UartGetBits()``                                      |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SPEED <speed>``            | | C++: ``rp_UartSetSpeed(int speed)``                               | Sets the speed of the UART connection.                                                 | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:SPEED 115200``             | | Python: ``rp_UartSetSpeed(<speed>)``                              |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:SPEED?`` > ``<speed>``     | | C++: ``rp_UartGetSpeed(int *speed)``                              | Gets the speed of the UART connection.                                                 | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:SPEED?`` > ``115200``      | | Python: ``rp_UartGetSpeed()``                                     |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:STOPB <stop>``             | | C++: ``rp_UartSetStopBits(rp_uart_stop_bits_t mode)``             | Sets the length of the stop bit.                                                       | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:STOPB STOP2``              | | Python: ``rp_UartSetStopBits(<mode>)``                            |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:STOPB?`` > ``<stop>``      | | C++: ``rp_UartGetStopBits(rp_uart_stop_bits_t *mode)``            | Gets the length of the stop bit.                                                       | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:STOPB?`` > ``STOP2``       | | Python: ``rp_UartGetStopBits()``                                  |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:PARITY <parity>``          | | C++: ``rp_UartSetParityMode(rp_uart_parity_t mode)``              | | Sets parity check mode.                                                              | 1.04-18 and up     |
| | Example:                          | |                                                                   | | - NONE  = Disable parity check                                                       |                    |
| | ``UART:PARITY ODD``               | | Python: ``rp_UartSetParityMode(<mode>)``                          | | - EVEN  = Set even mode for parity                                                   |                    |
| |                                   | |                                                                   | | - ODD   = Set odd mode for parity                                                    |                    |
| |                                   | |                                                                   | | - MARK  = Set Always 1                                                               |                    |
| |                                   | |                                                                   | | - SPACE = Set Always 0                                                               |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:PARITY?`` > ``<parity>``   | | C++: ``rp_UartGetParityMode(rp_uart_parity_t *mode)``             | Gets parity check mode.                                                                | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:PARITY?`` > ``ODD``        | | Python: ``rp_UartGetParityMode()``                                |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:TIMEOUT <timeout>``        | | C++: ``rp_UartSetTimeout(uint8_t deca_sec)``                      | | Sets the timeout for reading from UART. 0 - Disable timeout. 1 = 1/10 sec.           | 1.04-18 and up     |
| | Example:                          | |                                                                   | | Example: 10 - 1 sec. Max timeout: 25.5 sec                                           |                    |
| | ``UART:TIMEOUT 10``               | | Python: ``rp_UartSetTimeout(<deca_sec>)``                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:TIMEOUT?`` > ``<timeout>`` | | C++: ``rp_UartGetTimeout(uint8_t *value)``                        | Gets the timeout.                                                                      | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:TIMEOUT?`` > ``10``        | | Python: ``rp_UartGetTimeout()``                                   |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:WRITE<n> <data>``          | | C++: ``rp_UartWrite(unsigned char *buffer, int size)``            | Writes data to UART. ``<n>`` - the length of data sent to UART.                        | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:WRITE5 1,2,3,4,5``         | | Python: ``rp_UartWrite(<buffer>, <size>)``                        |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | ``UART:READ<n>?`` > ``<data>``    | | C++: ``rp_UartRead(unsigned char *buffer, int *size)``            | Reads data from UART. ``<n>`` - the length of data retrieved from UART.                | 1.04-18 and up     |
| | Example:                          | |                                                                   |                                                                                        |                    |
| | ``UART:READ5?`` > ``{1,2,3,4,5}`` | | Python: ``rp_UartRead(<buffer>, <size>)``                         |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+
| | - (NA)                            | | C++: NA                                                           | Creates a buffer for sending and receiving data.                                       | 2.04-35 and up     |
| |                                   | |                                                                   |                                                                                        |                    |
| |                                   | | Python: ``Buffer(<size>)``                                        |                                                                                        |                    |
| |                                   | |                                                                   |                                                                                        |                    |
+-------------------------------------+---------------------------------------------------------------------+----------------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_uart>`
* :ref:`Back to command list <command_list>`

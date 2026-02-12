
.. _commands_i2c:

===
I2C
===

Functionality overview
------------------------

I2C commands enable communication with I2C devices connected to Red Pitaya's extension connector. Control I2C bus initialization, device 
addressing, read/write operations, and clock stretching for interfacing with sensors, EEPROMs, and other I2C peripherals.


Important notes
----------------

* I2C device path may vary between board models.
* Device addresses are specified in 7-bit format (not including R/W bit).
* Clock stretching support depends on connected device capabilities.
* Use force mode carefully as it can interfere with devices in use.


Code examples
-----------------

Here are some examples of how to use I2C communication:

* :ref:`Digital communication examples <examples_digcom>`.
* :ref:`Logic analyzer examples <examples_la>`.


Parameters and command table
-----------------------------

**Parameter options:**

- ``<mode> = {OFF, ON}``  Default: ``OFF``
- ``<value> = {XXX | #HXX | #QXXX | #BXXXXXXXX}``  Value in Decimal, Hexadecimal, Octal, or Binary format.
- ``<data> = {XXX, ... | #HXX, ... | #QXXX, ... | #BXXXXXXXX, ... }`` Array of data values separated by commas.

   - ``XXX`` = Dec format
   - ``#HXX`` = Hex format
   - ``#QXXX`` = Oct format
   - ``#BXXXXXXXX`` = Bin format

.. **Available Jupyter and API macros:**


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| SCPI                                             | API, Jupyter                                                                    | DESCRIPTION                                                           |  ECOSYSTEM         |
+==================================================+=================================================================================+=======================================================================+====================+
| | ``I2C:DEV<addr> <path>``                       | | C++: ``rp_I2C_InitDevice(const char *device, uint8_t addr)``                  | | Initializes settings for I2C.                                       | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | - ``<path>`` - Path to the I2C device.                              |                    |
| | ``I2C:DEV80 "/dev/i2c-0"``                     | | Python: ``rp_I2C_InitDevice(<device>, <addr>)``                               | | - ``<addr>`` - Device address on the I2C bus in dec format.         |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:DEV?`` > ``<addr>``                      | | C++: ``rp_I2C_getDevAddress(int *address)``                                   | Returns the current address of the device.                            | 1.04-18 and up     |
| | Example:                                       | |                                                                               |                                                                       |                    |
| | ``I2C:DEV?`` > ``80``                          | | Python: ``rp_I2C_getDevAddress()``                                            |                                                                       |                    |
| |                                                | |                                                                               |                                                                       |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:FMODE <mode>``                           | | C++: ``rp_I2C_setForceMode(bool force)``                                      | Enables forced bus operation even if the device is in use.            | 1.04-18 and up     |
| | Example:                                       | |                                                                               |                                                                       |                    |
| | ``I2C:FMODE ON``                               | | Python: ``rp_I2C_setForceMode(<force>)``                                      |                                                                       |                    |
| |                                                | |                                                                               |                                                                       |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:FMODE?`` > ``<mode>``                    | | C++: ``rp_I2C_getForceMode(bool *value)``                                     | Gets the current forced mode setting.                                 | 1.04-18 and up     |
| | Example:                                       | |                                                                               |                                                                       |                    |
| | ``I2C:FMODE?`` > ``ON``                        | | Python: ``rp_I2C_getForceMode()``                                             |                                                                       |                    |
| |                                                | |                                                                               |                                                                       |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>?`` > ``<value>``         | | C++: ``rp_I2C_SMBUS_Read(uint8_t reg, uint8_t *value)``                       | | Reads 8 bit data from the specified register using                  | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | ``I2C:Smbus:Read2?`` > ``0``                   | | Python: ``rp_I2C_SMBUS_Read(<reg>)``                                          | | ``<reg>`` - Register address in dec format.                         |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>:Word?`` > ``<value>``    | | C++: ``rp_I2C_SMBUS_ReadWord(uint8_t reg, uint16_t *value)``                  | | Reads 16 bit data from the specified register using                 | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | ``I2C:Smbus:Read2:Word?`` > ``0``              | | Python: ``rp_I2C_SMBUS_ReadWord(<reg>)``                                      | | ``<reg>`` - Register address in dec format.                         |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | - (NA)                                         | | C++: ``rp_I2C_SMBUS_ReadCommand(uint8_t *value)``                             | | Read command from I2C using the SMBUS protocol.                     | 1.04-18 and up     |
| |                                                | |                                                                               | |                                                                     |                    |
| |                                                | | Python: ``rp_I2C_SMBUS_ReadCommand()``                                        | |                                                                     |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Read<reg>:Buffer<size>?`` >        | | C++: ``rp_I2C_SMBUS_ReadBuffer(uint8_t reg, uint8_t *buffer, int *len)``      | | Reads buffer data from the specified register using                 | 1.04-18 and up     |
| |  ``<data>``                                    | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | Example:                                       | | Python: ``rp_I2C_SMBUS_ReadBuffer(<reg>, <buffer>, <size>)``                  | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:Smbus:Read2:Buffer2?`` > ``{0,1}``       | |                                                                               | | ``<size>`` - Read data size.                                        |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg> <value>``               | | C++: ``rp_I2C_SMBUS_Write(uint8_t reg, uint8_t value)``                       | | Writes 8-bit data to the specified register using                   | 1.04-18 and up     |
| |                                                | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | Example:                                       | | Python: ``rp_I2C_SMBUS_Write(<reg>, <value>)``                                | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:Smbus:Write2 10``                        | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg>:Word <value>``          | | C++: ``rp_I2C_SMBUS_WriteWord(uint8_t reg, uint16_t value)``                  | | Writes 16-bit data to the specified register using                  | 1.04-18 and up     |
| |                                                | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | Example:                                       | | Python: ``rp_I2C_SMBUS_WriteWord(<reg>, <value>)``                            | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:Smbus:Write2:Word 10``                   | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | - (NA)                                         | | C++: ``rp_I2C_SMBUS_WriteCommand(uint8_t value)``                             | | Write command to I2C using the SMBUS protocol.                      | 1.04-18 and up     |
| |                                                | |                                                                               | |                                                                     |                    |
| |                                                | | Python: ``rp_I2C_SMBUS_WriteCommand(<value>)``                                | |                                                                     |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:Smbus:Write<reg>:Buffer<size> <data>``   | | C++: ``rp_I2C_SMBUS_WriteBuffer(uint8_t reg, uint8_t *buffer, int len)``      | | Writes buffer data to the specified register using                  | 1.04-18 and up     |
| |                                                | |                                                                               | | the SMBUS protocol.                                                 |                    |
| | Example:                                       | | Python: ``rp_I2C_SMBUS_WriteBuffer(<reg>, <buffer>, <len>)``                  | | ``<reg>`` - Register address in dec format.                         |                    |
| | ``I2C:Smbus:Write2:Buffer2 0,1``               | |                                                                               | | ``<size>`` - Read data size.                                        |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:IOctl:Read:Buffer<size>?`` > ``<data>``  | | C++: ``rp_I2C_IOCTL_ReadBuffer(uint8_t *buffer, int len)``                    | | Reads data from the I2C device through IOCTL.                       | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | ``<size>`` - Read data size.                                        |                    |
| | ``I2C:IOctl:Read:Buffer2?`` > ``{0,1}``        | | Python: ``rp_I2C_IOCTL_ReadBuffer(<buffer>, <len>)``                          | |                                                                     |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | ``I2C:IOctl:Write:Buffer<size> <data>``        | | C++: ``rp_I2C_IOCTL_WriteBuffer(uint8_t *buffer, int len)``                   | | Writes data to the I2C device via IOCTL.                            | 1.04-18 and up     |
| | Example:                                       | |                                                                               | | ``<size>`` - Read data size.                                        |                    |
| | ``I2C:IOctl:Write:Buffer2  {0,1}``             | | Python: ``rp_I2C_IOCTL_WriteBuffer(<buffer>, <len>)``                         | |                                                                     |                    |
| |                                                | |                                                                               | |                                                                     |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+
| | - (NA)                                         | | C++: N/A                                                                      | Creates a buffer for sending and receiving data.                      | 2.04-35 and up     |
| |                                                | |                                                                               |                                                                       |                    |
| |                                                | | Python: ``Buffer(<size>)``                                                    |                                                                       |                    |
| |                                                | |                                                                               |                                                                       |                    |
+--------------------------------------------------+---------------------------------------------------------------------------------+-----------------------------------------------------------------------+--------------------+


.. note::

   SMBUS is a standardized protocol for communicating with I2C devices. Information about this protocol can be found in this link: |SMBUS-specs|. IOCTL writes and reads data directly from I2C.

|

* :ref:`Back to top <commands_i2c>`
* :ref:`Back to command list <command_list>`

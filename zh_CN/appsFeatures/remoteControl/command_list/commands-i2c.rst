
.. _commands_i2c:

===
I2C
===

功能概述
------------------------

I2C 命令支持与连接到 Red Pitaya 扩展连接器的 I2C 设备通信。这些命令可用于控制 I2C 总线初始化、设备
寻址、读写操作和时钟拉伸，以连接传感器、EEPROM 及其他 I2C 外设。


重要说明
----------------

* I2C 设备路径可能因板卡型号而异。
* 设备地址以 7 位格式指定（不包括 R/W 位）。
* 时钟拉伸支持取决于所连接设备的能力。
* 请谨慎使用强制模式，因为它可能干扰正在使用的设备。


代码示例
-----------------

以下是如何使用 I2C 通信的示例：

* :ref:`数字通信示例 <examples_digcom>`。
* :ref:`逻辑分析仪示例 <examples_la>`。

|

参数与命令表
-----------------------------

**参数选项：**

- ``<mode> = {OFF, ON}``  默认值：``OFF``
- ``<value> = {XXX | #HXX | #QXXX | #BXXXXXXXX}``  值可以是十进制、十六进制、八进制或二进制格式。
- ``<data> = {XXX, ... | #HXX, ... | #QXXX, ... | #BXXXXXXXX, ... }`` 由逗号分隔的数据值数组。

   - ``XXX`` = 十进制格式
   - ``#HXX`` = 十六进制格式
   - ``#QXXX`` = 八进制格式
   - ``#BXXXXXXXX`` = 二进制格式

.. **Available Jupyter and API macros:**


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 50 81 71 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - 生态系统
    * - ``I2C:DEV<addr> <path>`` |br| Example: |br| ``I2C:DEV80 "/dev/i2c-0"``
      - C++: ``rp_I2C_InitDevice(const char *device, uint8_t addr)`` |br| Python: ``rp_I2C_InitDevice(<device>, <addr>)``
      - 初始化 I2C 设置。 |br| - ``<path>`` - I2C 设备路径。 |br| - ``<addr>`` - I2C 总线上的设备地址（十进制格式）。
      - 1.04-18 and up
    * - ``I2C:DEV?`` > ``<addr>`` |br| Example: |br| ``I2C:DEV?`` > ``80``
      - C++: ``rp_I2C_getDevAddress(int *address)`` |br| Python: ``rp_I2C_getDevAddress()``
      - 返回设备的当前地址。
      - 1.04-18 and up
    * - ``I2C:FMODE <mode>`` |br| Example: |br| ``I2C:FMODE ON``
      - C++: ``rp_I2C_setForceMode(bool force)`` |br| Python: ``rp_I2C_setForceMode(<force>)``
      - 即使设备正在使用，也启用强制总线操作。
      - 1.04-18 and up
    * - ``I2C:FMODE?`` > ``<mode>`` |br| Example: |br| ``I2C:FMODE?`` > ``ON``
      - C++: ``rp_I2C_getForceMode(bool *value)`` |br| Python: ``rp_I2C_getForceMode()``
      - 获取当前强制模式设置。
      - 1.04-18 and up
    * - ``I2C:Smbus:Read<reg>?`` > ``<value>`` |br| Example: |br| ``I2C:Smbus:Read2?`` > ``0``
      - C++: ``rp_I2C_SMBUS_Read(uint8_t reg, uint8_t *value)`` |br| Python: ``rp_I2C_SMBUS_Read(<reg>)``
      - 使用 SMBUS 协议从指定寄存器读取 8 位数据。 |br|  |br| ``<reg>`` - 寄存器地址（十进制格式）。
      - 1.04-18 and up
    * - ``I2C:Smbus:Read<reg>:Word?`` > ``<value>`` |br| Example: |br| ``I2C:Smbus:Read2:Word?`` > ``0``
      - C++: ``rp_I2C_SMBUS_ReadWord(uint8_t reg, uint16_t *value)`` |br| Python: ``rp_I2C_SMBUS_ReadWord(<reg>)``
      - 使用 SMBUS 协议从指定寄存器读取 16 位数据。 |br|  |br| ``<reg>`` - 寄存器地址（十进制格式）。
      - 1.04-18 and up
    * - - (NA)
      - C++: ``rp_I2C_SMBUS_ReadCommand(uint8_t *value)`` |br| Python: ``rp_I2C_SMBUS_ReadCommand()``
      - 使用 SMBUS 协议从 I2C 读取命令。
      - 1.04-18 and up
    * - ``I2C:Smbus:Read<reg>:Buffer<size>?`` > |br| ``<data>`` |br| Example: |br| ``I2C:Smbus:Read2:Buffer2?`` > ``{0,1}``
      - C++: ``rp_I2C_SMBUS_ReadBuffer(uint8_t reg, uint8_t *buffer, int *len)`` |br| Python: ``rp_I2C_SMBUS_ReadBuffer(<reg>, <buffer>, <size>)``
      - 使用 SMBUS 协议从指定寄存器读取缓冲区数据。 |br|  |br| ``<reg>`` - 寄存器地址（十进制格式）。 |br| ``<size>`` - 读取数据大小。
      - 1.04-18 and up
    * - ``I2C:Smbus:Write<reg> <value>`` |br| Example: |br| ``I2C:Smbus:Write2 10``
      - C++: ``rp_I2C_SMBUS_Write(uint8_t reg, uint8_t value)`` |br| Python: ``rp_I2C_SMBUS_Write(<reg>, <value>)``
      - 使用 SMBUS 协议向指定寄存器写入 8 位数据。 |br|  |br| ``<reg>`` - 寄存器地址（十进制格式）。
      - 1.04-18 and up
    * - ``I2C:Smbus:Write<reg>:Word <value>`` |br| Example: |br| ``I2C:Smbus:Write2:Word 10``
      - C++: ``rp_I2C_SMBUS_WriteWord(uint8_t reg, uint16_t value)`` |br| Python: ``rp_I2C_SMBUS_WriteWord(<reg>, <value>)``
      - 使用 SMBUS 协议向指定寄存器写入 16 位数据。 |br|  |br| ``<reg>`` - 寄存器地址（十进制格式）。
      - 1.04-18 and up
    * - - (NA)
      - C++: ``rp_I2C_SMBUS_WriteCommand(uint8_t value)`` |br| Python: ``rp_I2C_SMBUS_WriteCommand(<value>)``
      - 使用 SMBUS 协议向 I2C 写入命令。
      - 1.04-18 and up
    * - ``I2C:Smbus:Write<reg>:Buffer<size> <data>`` |br| Example: |br| ``I2C:Smbus:Write2:Buffer2 0,1``
      - C++: ``rp_I2C_SMBUS_WriteBuffer(uint8_t reg, uint8_t *buffer, int len)`` |br| Python: ``rp_I2C_SMBUS_WriteBuffer(<reg>, <buffer>, <len>)``
      - 使用 SMBUS 协议向指定寄存器写入缓冲区数据。 |br|  |br| ``<reg>`` - 寄存器地址（十进制格式）。 |br| ``<size>`` - 读取数据大小。
      - 1.04-18 and up
    * - ``I2C:IOctl:Read:Buffer<size>?`` > ``<data>`` |br| Example: |br| ``I2C:IOctl:Read:Buffer2?`` > ``{0,1}``
      - C++: ``rp_I2C_IOCTL_ReadBuffer(uint8_t *buffer, int len)`` |br| Python: ``rp_I2C_IOCTL_ReadBuffer(<buffer>, <len>)``
      - 通过 IOCTL 从 I2C 设备读取数据。 |br| ``<size>`` - 读取数据大小。
      - 1.04-18 and up
    * - ``I2C:IOctl:Write:Buffer<size> <data>`` |br| Example: |br| ``I2C:IOctl:Write:Buffer2  {0,1}``
      - C++: ``rp_I2C_IOCTL_WriteBuffer(uint8_t *buffer, int len)`` |br| Python: ``rp_I2C_IOCTL_WriteBuffer(<buffer>, <len>)``
      - 通过 IOCTL 向 I2C 设备写入数据。 |br| ``<size>`` - 读取数据大小。
      - 1.04-18 and up
    * - - (NA)
      - C++: N/A |br| Python: ``Buffer(<size>)``
      - 创建用于发送和接收数据的缓冲区。
      - 2.04-35 and up


.. note::

   SMBUS 是用于与 I2C 设备通信的标准化协议。有关该协议的信息请参见此链接： |SMBUS-specs|。IOCTL 直接从 I2C 读写数据。

|

* :ref:`返回顶部 <commands_i2c>`
* :ref:`返回命令列表 <command_list>`

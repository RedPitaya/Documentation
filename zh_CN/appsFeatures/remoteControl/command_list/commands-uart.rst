
.. _commands_uart:

====
UART
====

功能概览
------------------------

UART 命令通过 Red Pitaya 扩展连接器提供串行通信能力。可配置波特率、数据位、奇偶校验和停止位，以连接串行设备、传感器及其他微控制器。


重要说明
----------------

* 为确保通信可靠，除 RX 和 TX 外，务必连接外部共模（GND）引脚。
* 默认设置：9600 波特，8 个数据位，无奇偶校验，1 个停止位。
* 支持的波特率范围为 1200 to 4,000,000.


代码示例
-----------------

以下是 UART 通信的使用示例：

* :ref:`Digital communication examples <examples_digcom>`.
* :ref:`Logic analyzer examples <examples_la>`.

|

参数与命令表
-----------------------------

**参数选项：**

- ``<bits> = {CS6, CS7, CS8}``  默认值： ``CS8``
- ``<stop> = {STOP1, STOP2}``  默认值： ``STOP1``
- ``<parity> = {NONE, EVEN, ODD, MARK, SPACE}``  默认值： ``NONE``
- ``<timeout> = {0...255} in (1/10 seconds)``，默认值：``0``
- ``<speed> = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 576000, 921000, 1000000, 1152000, 1500000, 2000000, 2500000, 3000000, 3500000, 4000000}`` 默认值： ``9600``
- ``<data> = {XXX, ... | #HXX, ... | #QXXX, ... | #BXXXXXXXX, ... }`` 以逗号分隔的数据数组

   - ``XXX`` = 十进制格式
   - ``#HXX`` = 十六进制格式
   - ``#QXXX`` = 八进制格式
   - ``#BXXXXXXXX`` = 二进制格式

**可用的 Jupyter 和 API 宏：**

- UART bit size - ``RP_UART_CS6, RP_UART_CS7, RP_UART_CS8``
- UART stop bits - ``RP_UART_STOP1, RP_UART_STOP2``
- UART 奇偶校验模式 - ``RP_UART_NONE, RP_UART_EVEN, RP_UART_ODD, RP_UART_MARK, RP_UART_SPACE``

.. note::

    在 Red Pitaya 与其他设备建立 UART 通信时，务必连接外部共模（GND）引脚（以及 RX 和 TX 引脚）。否则， 
    通信可能不可靠。


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 37 69 88 20
    :header-rows: 1

    * - SCPI
      - API、Jupyter
      - 描述
      - 适用版本
    * - ``UART:INIT`` |br| 示例： |br| ``UART:INIT``
      - C++: ``rp_UartInit()`` |br| Python: ``rp_UartInit()``
      - 初始化用于 UART 操作的 API。
      - 1.04-18 及更高版本
    * - ``UART:RELEASE`` |br| 示例： |br| ``UART:RELEASE``
      - C++: ``rp_UartRelease()`` |br| Python: ``rp_UartRelease()``
      - 释放所有已使用的资源。
      - 1.04-18 及更高版本
    * - ``UART:SETUP`` |br| 示例： |br| ``UART:SETUP``
      - C++: ``rp_UartSetSettings()`` |br| Python: ``rp_UartSetSettings()``
      - 将指定设置应用于 UART。 |br| 应在设置通信参数后执行。
      - 1.04-18 及更高版本
    * - ``UART:BITS <bits>`` |br| 示例： |br| ``UART:BITS CS7``
      - C++: ``rp_UartSetBits(rp_uart_bits_size_t _size)`` |br| Python: ``rp_UartSetBits(<size>)``
      - 设置字符大小（位数）。
      - 1.04-18 及更高版本
    * - ``UART:BITS?`` > ``<bits>`` |br| 示例： |br| ``UART:BITS?`` > ``CS7``
      - C++: ``rp_UartGetBits(rp_uart_bits_size_t *value)`` |br| Python: ``rp_UartGetBits()``
      - 获取字符大小（位数）。
      - 1.04-18 及更高版本
    * - ``UART:SPEED <speed>`` |br| 示例： |br| ``UART:SPEED 115200``
      - C++: ``rp_UartSetSpeed(int speed)`` |br| Python: ``rp_UartSetSpeed(<speed>)``
      - 设置 UART 连接速度。
      - 1.04-18 及更高版本
    * - ``UART:SPEED?`` > ``<speed>`` |br| 示例： |br| ``UART:SPEED?`` > ``115200``
      - C++: ``rp_UartGetSpeed(int *speed)`` |br| Python: ``rp_UartGetSpeed()``
      - 获取 UART 连接速度。
      - 1.04-18 及更高版本
    * - ``UART:STOPB <stop>`` |br| 示例： |br| ``UART:STOPB STOP2``
      - C++: ``rp_UartSetStopBits(rp_uart_stop_bits_t mode)`` |br| Python: ``rp_UartSetStopBits(<mode>)``
      - 设置停止位长度。
      - 1.04-18 及更高版本
    * - ``UART:STOPB?`` > ``<stop>`` |br| 示例： |br| ``UART:STOPB?`` > ``STOP2``
      - C++: ``rp_UartGetStopBits(rp_uart_stop_bits_t *mode)`` |br| Python: ``rp_UartGetStopBits()``
      - 获取停止位长度。
      - 1.04-18 及更高版本
    * - ``UART:PARITY <parity>`` |br| 示例： |br| ``UART:PARITY ODD``
      - C++: ``rp_UartSetParityMode(rp_uart_parity_t mode)`` |br| Python: ``rp_UartSetParityMode(<mode>)``
      - 设置奇偶校验模式。 |br| - NONE  = 禁用奇偶校验 |br| - EVEN  = 设置偶校验模式 |br| - ODD   = 设置奇校验模式 |br| - MARK  = 始终设置为 1 |br| - SPACE = 始终设置为 0
      - 1.04-18 及更高版本
    * - ``UART:PARITY?`` > ``<parity>`` |br| 示例： |br| ``UART:PARITY?`` > ``ODD``
      - C++: ``rp_UartGetParityMode(rp_uart_parity_t *mode)`` |br| Python: ``rp_UartGetParityMode()``
      - 获取奇偶校验模式。
      - 1.04-18 及更高版本
    * - ``UART:TIMEOUT <timeout>`` |br| 示例： |br| ``UART:TIMEOUT 10``
      - C++: ``rp_UartSetTimeout(uint8_t deca_sec)`` |br| Python: ``rp_UartSetTimeout(<deca_sec>)``
      - 设置 UART 读取超时。0 表示禁用超时，1 表示 1/10 秒。 |br| 示例：10 表示 1 秒；最大超时为 25.5 秒。
      - 1.04-18 及更高版本
    * - ``UART:TIMEOUT?`` > ``<timeout>`` |br| 示例： |br| ``UART:TIMEOUT?`` > ``10``
      - C++: ``rp_UartGetTimeout(uint8_t *value)`` |br| Python: ``rp_UartGetTimeout()``
      - 获取超时设置。
      - 1.04-18 及更高版本
    * - ``UART:WRITE<n> <data>`` |br| 示例： |br| ``UART:WRITE5 1,2,3,4,5``
      - C++: ``rp_UartWrite(unsigned char *buffer, int size)`` |br| Python: ``rp_UartWrite(<buffer>, <size>)``
      - 向 UART 写入数据。 ``<n>`` - 发送到 UART 的数据长度。
      - 1.04-18 及更高版本
    * - ``UART:READ<n>?`` > ``<data>`` |br| 示例： |br| ``UART:READ5?`` > ``{1,2,3,4,5}``
      - C++: ``rp_UartRead(unsigned char *buffer, int *size)`` |br| Python: ``rp_UartRead(<buffer>, <size>)``
      - 从 UART 读取数据。 ``<n>`` - 从 UART 获取的数据长度。
      - 1.04-18 及更高版本
    * - - (NA)
      - C++: NA |br| Python: ``Buffer(<size>)``
      - 创建用于发送和接收数据的缓冲区。
      - 2.04-35 及更高版本

|

* :ref:`返回顶部 <commands_uart>`
* :ref:`返回命令列表 <command_list>`

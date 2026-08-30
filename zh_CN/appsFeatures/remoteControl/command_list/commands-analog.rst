
.. _commands_analog:

=========================
模拟输入与输出
=========================

功能概述
------------------------

模拟 I/O 命令控制扩展连接器上的 Red Pitaya 慢速模拟通道。这些通道可进行直流电压测量（输入范围 0-3.5V）和信号生成（输出范围 0-1.8V），用于连接传感器、控制电路及其他模拟外设。


重要说明
----------------

* 模拟输入：范围 0 至 +3.5V（12 位分辨率）。
* 模拟输出：范围 0 至 +1.8V（12 位分辨率）。
* 不要与用于信号采集和生成的快速 RF 输入/输出混淆。


代码示例
-----------------

以下是如何在 Red Pitaya 上使用模拟 I/O 命令的示例：

* :ref:`Analog examples <examples_analog>`.


参数与命令表
-----------------------------

**参数选项：**

- ``<ain> = {AIN0, AIN1, AIN2, AIN3}``
- ``<aout> = {AOUT0, AOUT1, AOUT2, AOUT3}``
- ``<pin> = {ain, aout}``
- ``<value> = {value in Volts}``

**可用的 Jupyter 和 API 宏：**

- Analog outputs - ``RP_AOUT0, RP_AOUT1, ..., RP_AOUT3``
- Analog inputs - ``RP_AIN0, RP_AIN1, ..., RP_AIN3``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 39 84 83 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - ECOSYSTEM
    * - ``ANALOG:RST`` |br| Examples: |br| ``ANALOG:RST``
      - C++: ``rp_ApinReset()`` |br| Python: ``rp_ApinReset()``
      - 将模拟输出设置为默认值（0 V）。
      - 1.04-18 and up
    * - ``ANALOG:PIN <pin>,<value>`` |br| Examples: |br| ``ANALOG:PIN AOUT2,1.34``
      - C++: ``rp_ApinSetValue(rp_apin_t pin, float value)`` |br| ``rp_ApinSetValueRaw(rp_apin_t pin, uint32_t value)`` |br| Python: ``rp_ApinSetValue(<pin>, <value>)`` |br| ``rp_ApinSetValueRaw(<pin>, <value>)``
      - 设置慢速模拟输出上的模拟电压。 |br| 慢速模拟输出的电压范围为：0 - 1.8 V
      - 1.04-18 and up
    * - ``ANALOG:PIN? <pin>`` > ``<value>`` |br| Examples: |br| ``ANALOG:PIN? AOUT2`` > ``1.34`` |br| ``ANALOG:PIN? AIN1`` > ``1.12``
      - C++: ``rp_ApinGetValue(rp_apin_t pin, float* value, uint32_t* raw)`` |br| ``rp_ApinGetValueRaw(rp_apin_t pin, uint32_t* value)`` |br| Python: ``rp_ApinGetValue(<pin>)`` |br| ``rp_ApinGetValueRaw(<pin>)``
      - 读取慢速模拟输入的模拟电压。 |br| 慢速模拟输入的电压范围为：0 - 3.3 V
      - 1.04-18 and up
    * - -
      - C++: ``rp_ApinGetRange(rp_apin_t pin, float* min_val, float* max_val)`` |br| Python: ``rp_ApinGetRange(<pin>)``
      - 获取指定模拟引脚的电压范围。
      - 1.04-18 and up
    * - -
      - C++: ``rp_AIpinGetValue(int unsigned pin, float* value, uint32_t* raw)`` |br| ``rp_AIpinGetValueRaw(int unsigned pin, uint32_t* value)`` |br| Python: ``rp_AIpinGetValue(<pin>)`` |br| ``rp_AIpinGetValueRaw(<pin>)``
      - 获取慢速模拟输入的模拟电压（Volts 或 RAW）。
      - 1.04-18 and up
    * - -
      - C++: ``rp_AOpinSetValue(int unsigned pin, float value)`` |br| ``rp_AOpinSetValueRaw(int unsigned pin, uint32_t value)`` |br| Python: ``rp_AOpinSetValue(<pin>, <value>)`` |br| ``rp_AOpinSetValueRaw(<pin>, <value>)``
      - 设置慢速模拟输出的输出电压。
      - 1.04-18 and up
    * - -
      - C++: ``rp_AOpinGetValue(int unsigned pin, float* value, uint32_t* raw)`` |br| ``rp_AOpinGetValueRaw(int unsigned pin, uint32_t* value)`` |br| Python: ``rp_AOpinGetValue(<pin>)`` |br| ``rp_AOpinGetValueRaw(<pin>)``
      - 获取慢速模拟输出的输出电压。
      - 1.04-18 and up
    * - -
      - C++: ``rp_AOpinGetRange(int unsigned pin, float* min_val,  float* max_val)`` |br| Python: ``rp_AOpinGetRange(<pin>)``
      - 获取指定模拟输出引脚的电压范围。
      - 1.04-18 and up

|

* :ref:`Back to top <commands_analog>`
* :ref:`Back to command list <command_list>`

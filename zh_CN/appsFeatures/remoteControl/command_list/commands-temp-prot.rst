
.. _commands_temp_prot:

=================================
温度保护与电源
=================================

功能概述
------------------------

温度保护与电源命令用于监测和控制 SIGNALlab 250-12 的热管理。这些命令提供温度
读数、风扇控制和自动热保护，防止过热导致硬件损坏。


重要说明
----------------

* 这些命令仅适用于 SIGNALlab 250-12。
* 超过温度限制 (85 °C) 时，温度保护会自动限制或关闭输出。
* 高功率运行期间应定期监测温度。


代码示例
-----------------

[待添加——温度监测和保护的专用示例]

|

参数与命令表
-----------------------------

**参数选项：**

- ``<enable> = {true, false}``

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道——``RP_CH_1, RP_CH_2``

*仅 STEMlab 125-14 4-Input（附加）：*

- 快速模拟通道——``RP_CH_3, RP_CH_4``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 37 77 84 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - 适用版本
    * - -
      - C++: ``rp_SetEnableTempProtection(rp_channel_t channel, bool enable)`` |br| Python: ``rp_SetEnableTempProtection(<channel>, <enable>)``
      - 为指定快速模拟输出启用/禁用 DAC 过热保护模式（仅 SIGNALlab 250-12）。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetEnableTempProtection(rp_channel_t channel, bool* enable)`` |br| Python: ``rp_GetEnableTempProtection(channel)``
      - 获取指定快速模拟输出的 DAC 过热保护模式启用/禁用设置（仅 SIGNALlab 250-12）。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_SetLatchTempAlarm(rp_channel_t channel, bool status)`` |br| Python: ``rp_SetLatchTempAlarm(<channel>, <status>)``
      - 重置表示指定快速模拟输出 DAC 过热的标志（仅 SIGNALlab 250-12）。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetLatchTempAlarm(rp_channel_t channel, bool* status)`` |br| Python: ``rp_GetLatchTempAlarm(<channel>)``
      - 返回表示指定快速模拟输出 DAC 过热的标志状态（仅 SIGNALlab 250-12）。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetRuntimeTempAlarm(rp_channel_t channel, bool* status)`` |br| Python: ``rp_GetRuntimeTempAlarm(<channel>)``
      - 实时返回当前 DAC 过热状态（仅 SIGNALlab 250-12）。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetCPUTemperature(uint32_t* raw)`` |br| Python: ``rp_GetCPUTemperature()``
      - 返回当前 CPU 温度。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetPowerI4(uint32_t* raw, float* value)`` |br| Python: ``rp_GetPowerI4()``
      - 返回模拟输入 AI4 的值，用于测试 5V 电源线。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetPowerVCCPINT(uint32_t* raw, float* value)`` |br| Python: ``rp_GetPowerVCCPINT()``
      - 返回 VCCPINT(1.0V) 的值。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetPowerVCCPAUX(uint32_t* raw, float* value)`` |br| Python: ``rp_GetPowerVCCPAUX()``
      - 返回 VCCPAUX(1.8V) 的值。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetPowerVCCBRAM(uint32_t* raw, float* value)`` |br| Python: ``rp_GetPowerVCCBRAM()``
      - 返回 VCCBRAM(1.0V) 的值。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetPowerVCCINT(uint32_t* raw, float* value)`` |br| Python: ``rp_GetPowerVCCINT()``
      - 返回 VCCINT(1.0V) 的值。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetPowerVCCAUX(uint32_t* raw, float* value)`` |br| Python: ``rp_GetPowerVCCAUX()``
      - 返回 VCCAUX(1.8V) 的值。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GetPowerVCCDDR(uint32_t* raw, float* value)`` |br| Python: ``rp_GetPowerVCCDDR()``
      - 返回 VCCDDR(1.5V) 的值。
      - 1.04-18 及更高版本

|

* :ref:`返回顶部 <commands_temp_prot>`
* :ref:`返回命令列表 <command_list>`

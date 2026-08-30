
.. _commands_status_leds:

=============
状态 LED
=============

功能概述
------------------------

状态 LED 命令控制 Red Pitaya 状态 LED 的运行行为。可以启用或禁用用于指示系统状态的自动 LED 模式，从而为自定义应用提供手动 LED 控制。


重要说明
----------------

* 默认状态为 ON（自动状态指示）。
* 禁用以太网 LED 有助于降低 :ref:`Original generation <dev_guide_hardware>` 板卡快速模拟输入和输出的噪声。


代码示例
-----------------

[待添加 - 状态 LED 专用示例]

|

参数与命令表
-----------------------------

**参数选项：**

- ``<enable> = {OFF, ON}``  默认值：``ON``

**可用的 Jupyter 和 API 宏：**

- NA


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 37 51 84 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - 生态系统
    * - ``LED:MMC <enable>`` |br| 示例： |br| ``LED:MMC OFF``
      - C++: ``rp_SetLEDMMCState(bool enable)`` |br| Python: ``rp_SetLEDMMCState(<enable>)``
      - 打开或关闭橙色 LED（用于指示正在读取的存储卡）。
      - 1.04-18 及更高版本
    * - ``LED:MMC?`` > ``<enable>`` |br| 示例： |br| ``LED:MMC?`` > ``ON``
      - C++: ``rp_GetLEDMMCState(bool *enable)`` |br| Python: ``rp_GetLEDMMCState()``
      - 获取 MMC 指示灯状态。
      - 1.04-18 及更高版本
    * - ``LED:HB <enable>`` |br| 示例： |br| ``LED:HB OFF``
      - C++: ``rp_SetLEDHeartBeatState(bool enable)`` |br| Python: ``rp_SetLEDHeartBeatState(<enable>)``
      - 打开或关闭红色 LED（用于指示板卡活动状态）。
      - 1.04-18 及更高版本
    * - ``LED:HB?`` > ``<enable>`` |br| 示例： |br| ``LED:HB?`` > ``ON``
      - C++: ``rp_GetLEDHeartBeatState(bool *enable)`` |br| Python: ``rp_GetLEDHeartBeatState()``
      - 获取 HeartBeat 指示灯（红色 LED）的状态。
      - 1.04-18 及更高版本
    * - ``LED:ETH <enable>`` |br| 示例： |br| ``LED:ETH OFF``
      - C++: ``rp_SetLEDEthState(bool enable)`` |br| Python: ``rp_SetLEDEthState(<enable>)``
      - 打开或关闭以太网 LED 指示灯。
      - 1.04-18 及更高版本
    * - ``LED:ETH?`` > ``<enable>`` |br| 示例： |br| ``LED:ETH?`` > ``ON``
      - C++: ``rp_GetLEDEthState(bool *enable)`` |br| Python: ``rp_GetLEDEthState()``
      - 获取以太网指示灯状态。
      - 1.04-18 及更高版本

|

* :ref:`返回顶部 <commands_status_leds>`
* :ref:`返回命令列表 <command_list>`

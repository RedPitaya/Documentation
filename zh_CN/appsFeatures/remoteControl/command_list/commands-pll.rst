
.. _commands_pll:

==================
锁相环
==================

功能概述
------------------------

锁相环（PLL）命令用于控制 SIGNALlab 250-12 专有的时钟同步电路。PLL 可将频率和相位精确锁定到外部参考时钟信号，适用于要求严格时序同步的应用。


重要说明
----------------

* 这些命令仅适用于 SIGNALlab 250-12。
* 应将 10 MHz 外部参考时钟（3V3 或 5V TTL）连接到板卡背面的 SMA 连接器。

代码示例
-----------------

[待添加——PLL 专用示例]

|

参数与命令表
-----------------------------

**参数选项：**

- ``<enable> = {OFF, ON}``
- ``<status> = {true, false}``

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 53 84 83 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - 生态系统版本
    * - ``RP:PLL:ENable <enable>`` |br| 示例： |br| ``RP:PLL:ENable ON``
      - C++: ``rp_SetPllControlEnable(bool enable)`` |br| Python: ``rp_SetPllControlEnable(<enable>)``
      - 启用/禁用 PLL 控制（仅适用于 SIGNALlab 250-12）。 |br| 启用与连接到板卡背面 SMA 连接器的 10 MHz 外部参考时钟同步。
      - 2.04-35 及更高版本
    * - ``RP:PLL:ENable?`` > ``<enable>`` |br| 示例： |br| ``RP:PLL:ENable?`` > ``ON``
      - C++: ``rp_GetPllControlEnable(bool *enable)`` |br| Python: ``rp_GetPllControlEnable()``
      - 获取 PLL 启用设置的状态（仅适用于 SIGNALlab 250-12）。
      - 2.04-35 及更高版本
    * - ``RP:PLL:STATE?`` > ``<status>`` |br| 示例： |br| ``RP:PLL:STATE?`` > ``1``
      - C++: ``rp_GetPllControlLocked(bool *status)`` |br| Python: ``rp_GetPllControlLocked()``
      - 获取 PLL 与参考时钟的同步状态 |br| ``1`` - 单元已与参考时钟同步 |br| ``0`` - 单元未与参考时钟同步 |br| （仅适用于 SIGNALlab 250-12）。
      - 2.04-35 及更高版本

|

* :ref:`返回顶部 <commands_pll>`
* :ref:`返回命令列表 <command_list>`

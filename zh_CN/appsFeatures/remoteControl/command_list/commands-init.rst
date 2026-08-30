
.. _commands_init:

=========================
初始化命令
=========================

功能概述
------------------------

初始化命令为 Red Pitaya 的硬件和软件接口准备运行环境。使用其他 API 函数前必须调用这些命令，以确保硬件配置和内存分配正确。


重要说明
----------------

* 始终在其他 API 操作之前调用初始化命令。
* 对于 API 程序，``rp_Init()`` 必须是执行的第一个命令。
* 建立连接时，SCPI 服务器会自动处理初始化。


代码示例
-----------------

以下是如何在 Red Pitaya 上使用初始化命令的示例：

* :ref:`使用 API 命令的示例 <examples>`。

|

参数与命令表
-----------------------------

Red Pitaya 的 SCPI 与 API 命令对照表。

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 54 45 59 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - 生态系统
    * - -
      - C++: ``rp_Init()`` |br| Python: ``rp_Init()``
      - 初始化并启用命令接口。
      - 1.04-18 and up
    * - -
      - C++: ``rp_IsApiInit()`` |br| Python: ``rp_IsApiInit()``
      - 检查 API 接口是否已初始化。
      - 1.04-18 and up
    * - -
      - C++: ``rp_Release()`` |br| Python: ``rp_Release()``
      - 释放命令接口资源。
      - 1.04-18 and up
    * - -
      - C++: ``rp_Reset()`` |br| Python: ``rp_Reset()``
      - 将数字和模拟引脚设置以及 |br| 生成和采集设置重置为默认值。
      - 1.04-18 and up
    * - -
      - C++: ``rp_Reset()`` |br| Python: ``rp_Reset()``
      - 将数字和模拟引脚设置以及 |br| 生成和采集设置重置为默认值。
      - 1.04-18 and up

|

* :ref:`返回顶部 <commands_init>`
* :ref:`返回命令列表 <command_list>`

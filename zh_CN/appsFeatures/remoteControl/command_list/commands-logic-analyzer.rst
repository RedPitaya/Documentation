:orphan:

.. _commands_logic_analyzer:

=================
逻辑分析仪
=================



功能概述
------------------------




重要说明
----------------



代码示例
-----------------

以下是如何在 Red Pitaya 上使用逻辑分析仪命令的示例：

* :ref:`数字通信示例 <examples_digcom>`。

|

参数与命令表
-----------------------------

**参数选项：**

- ``<shunt> = {1 ... 100000000}``（单位：Hertz）。默认值：``100``


**可用的 Jupyter 和 API 宏：**

- *（未来 OS 版本）*


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 43 66 85 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - 生态系统
    * - ``LCR:START`` |br| 示例： |br| ``LCR:START``
      - C++: ``lcrApp_LcrRun()`` |br| Python:
      - 启动 LCR 处理线程并将设置重置为默认值。 |br| 必须在线程启动后设置生成器参数。
      - 2.05-37 及更高版本















|

* :ref:`返回顶部 <commands_logic_analyzer>`
* :ref:`返回命令列表 <command_list>`

.. _fpga_project_logic:

#######################
FPGA logic 项目
#######################

``logic`` 项目是面向逻辑分析仪工作流的 FPGA 镜像。
其设计重点是数字数据采集和传输，包括基于 DMA 的 DDR 缓冲。

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

用途
----------

如果主要目标是观察和分析数字协议，而不是使用混合模拟仪器，请使用 ``logic``。

典型用例：

* 采集数字总线，供软件解码和分析
* 使用内存后备缓冲区执行逻辑分析仪式采集
* 构建数字触发/采集链原型

|

架构概述
----------------------

该项目包括：

* ``rtl/`` 下针对具体型号的顶层模块
* 通过 ``ip/system.tcl`` 完成的块设计集成
* ``dts/`` 下与 DMA 相关的设备树片段
* ``sim/`` 和 ``tbn/`` 下的仿真资源

设备树片段 ``dts/dma.dtsi`` 默认禁用 AXI DMA 节点；软件流程需要时，应通过运行时覆盖层启用这些节点。

|

项目结构
------------------

``prj/logic/`` 中包含：

* ``rtl/`` —— 项目顶层 RTL 和 PS 封装
* ``ip/`` —— Vivado 块设计 Tcl 定义
* ``dts/`` —— FPGA 和 DMA 覆盖层片段
* ``sdc/`` —— 支持型号的约束
* ``sim/`` 和 ``tbn/`` —— 仿真脚本和测试平台

|

构建与集成说明
----------------------------

典型命令：

* ``make project PRJ=logic MODEL=Z20``
* ``make PRJ=logic MODEL=Z20``
* ``make dts PRJ=logic MODEL=Z20``

与软件集成时：

* 检查是否为相应型号使用了正确的覆盖层/设备树路径
* 验证 DMA 通道启用状态和采集路径初始化
* 在分析工具链中验证预期的采样深度和触发行为

|

代码架构（模块）
----------------------------

主源文件是 ``prj/logic/rtl/red_pitaya_top.sv``。其结构沿用其他活跃项目的 Red Pitaya 集成模式，但侧重逻辑分析仪式数字采集。

核心集成模块：

* ``red_pitaya_ps`` —— PS/DDR/MIO 接口以及通往软件的 AXI 流桥接器。
* ``red_pitaya_pll`` —— 时钟生成和复位分配。
* ``sys_bus_interconnect`` —— 将系统总线地址空间划分给各功能模块。
* ``sys_bus_stub`` —— 未实现地址槽的终结器。
* ``old_id`` —— 镜像标识寄存器。
* ``cts`` —— 用于采集计时的时间戳计数器。
* ``muxctl`` —— 运行时路径/环回控制。

逻辑采集路径模块：

* ``old_la_top`` —— 从扩展输入执行逻辑分析仪采集，带触发和 DMA 流输出。
* ``old_asg_top``（实例 ``lg``）—— 用于数字激励的逻辑发生器输出。
* ``axi4_stream_pas`` —— 流直通/环回辅助路径。

支持模块：

* ``sys_reg_array_o`` + ``pdm`` —— 寄存器驱动的 PDM 输出支持。
* 可选的 ``sys_reg_array_o`` + ``pwm`` —— 仅在编译时启用后存在。

``prj/logic/dts/dma.dtsi`` 片段默认保持 DMA 节点禁用，直到预定的软件/覆盖层流程将其启用。

|

模块连接示意图
----------------------------

.. figure:: img/logic/logic_module_block_diagram.png
   :alt: Logic module block diagram
   :align: center

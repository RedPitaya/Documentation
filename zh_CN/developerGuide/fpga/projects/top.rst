.. _fpga_projects:

########################
FPGA 项目
########################

本节介绍 Red Pitaya 提供的各种 FPGA 项目。每个项目都用于演示 FPGA 硬件的不同功能和能力。

**相关文档：**

* :ref:`FPGA 寄存器映射 <fpga_registers>` - 各项目的详细寄存器文档
* :ref:`FPGA 开发 <fpga_top>` - FPGA 通用开发指南
* :ref:`从零开始创建自定义项目 <fpga_project_from_scratch>` - 手动创建项目时的约束文件和模型/配置文件选择

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

FPGA 仓库
==================

在开始介绍项目之前，先看看 |FPGA GitHub repository| 的结构。

该仓库包含多个 FPGA 项目，有些提供通用功能，有些则提供与特定应用相关的功能。

* 所有项目共用的代码（主要是可复用模块）直接位于顶层目录中。
* 项目专用代码位于 ``prj/<project_name>/`` 目录中。


.. |ug895| replace:: Vivado 系统级设计入口
.. _ug895: https://www.xilinx.com/support/documentation/sw_manuals/xilinx2017_2/ug895-vivado-system-level-design-entry.pdf


.. list-table::
   :header-rows: 1
   :widths: 25 75

   * - 路径
     - 内容
   * - ``archive/``
     - 使用 .xz 格式压缩的旧 FPGA bit 文件存档
   * - ``brd/``
     - 板卡文件（|ug895|_）
   * - ``doc/``
     - 文档（框图、地址空间等）
   * - ``dts/``
     - 设备树源 include 文件
   * - ``ip/``
     - 第三方 IP，目前为 Zynq 块设计
   * - ``prj/name``
     - 项目 `name` 的专用代码
   * - ``rtl/``
     - Verilog（SystemVerilog）*寄存器传输级* 代码
   * - ``sdc/``
     - *Synopsys Design Constraints*，包含 Xilinx 设计约束
   * - ``sim/``
     - 仿真脚本
   * - ``tbn/``
     - Verilog（SystemVerilog）*测试平台*
   * - ``Makefile``
     - 主 Makefile，用于运行 FPGA 相关工具
   * - ``*.tcl``
     - 在 FPGA 工具内部运行的 TCL 脚本
   * - ``*.rst``
     - 文档用 reStructuredText 文件


FPGA 项目
====================

所有现有项目都提供通用功能，或提供与特定应用相关的功能，具体见“应用”列。

建议使用 **0.94** 作为*默认项目*。


.. list-table::
   :header-rows: 1
   :widths: 15 45 25 15

   * - 项目名称
     - 说明
     - 应用
     - 状态
   * - 0.94
     - 默认且功能最完整的 Red Pitaya FPGA 镜像，是当前应用支持和大多数自定义分支的基线。在 2025.1 流程中仍是推荐的起始点。
     - 示波器；信号发生器；频谱分析仪；Bode 分析仪；阻抗分析仪；LCR 表；JupyterLab；**寄存器映射：** :ref:`v0.94 <fpga_094_dev>`
     - 活跃（默认）
   * - stream_app
     - 高吞吐量流式传输项目。支持 ADC/DAC/GPIO 在 PL 与 DDR 内存之间传输，以及主机到板卡的流式工作流。包含针对具体板卡的变体（例如 4-input 和 250-12）。
     - 数据流传输；流式服务器/API 流程；**寄存器映射：** :ref:`In Dev <regset_in_dev>`
     - 活跃
   * - logic
     - 面向逻辑分析仪的项目，使用基于 DMA 的采集将数据写入 DDR，侧重数字采集和协议分析工作流。
     - 逻辑分析仪
     - 活跃
   * - barebones
     - 使用各项目共享 PS 配置的 Linux 平台基础项目。它构建完整 Linux 设备树；其他项目通常只提供覆盖层。应用层有意保持精简或为空。
     - Linux 系统基础
     - 活跃
   * - pyrpl
     - 面向第三方 PyRPL 工作流的镜像，包含与锁相、IQ、滤波和反馈控制有关的 DSP 模块。
     - PyRPL/控制环路（高级 DSP/控制）
     - 社区维护
   * - fsbl
     - 用于 FSBL 和 U-Boot 产物的构建支持项目（XSA/FSBL 流程）。与 barebones 类似，但因 U-Boot 不需要完整 Linux 平台功能而启用较少的外设和设置。
     - 启动和平台产物
     - 构建支持
   * - Examples
     - 独立 Vivado 教学示例集合（例如 LED/GPIO/VGA 练习），适合培训和快速实验。
     - 学习和快速演示
     - 旧版

上表反映 FPGA 仓库 master 分支的 ``prj/`` 中当前存在的项目。以前版本中的旧项目可能仍可在历史 tag 中找到。

|

旧版项目
----------------

这些项目已从 FPGA 仓库移除，也不再积极维护。它们可能与最新硬件修订版或软件版本不兼容。仅在参考或维护旧系统时使用。

.. list-table::
   :header-rows: 1
   :widths: 15 50 20 15

   * - 项目名称
     - 说明
     - 应用
     - 状态
   * - 0.93
     - 原始 Red Pitaya FPGA 发布版本，包含所有原始缺陷。仅用于已弃用应用的向后兼容。
     -
     - 旧版
   * - classic
     - 大部分代码已用 SystemVerilog 重写。GPIO 和 LED 寄存器已从 housekeeping 部分移除，改用 PL 内部的 GPIO 控制器，使 Linux 内核功能可用于 GPIO（IRQ、SPI、I2C 和 1-Wire）以及 LED（触发器）。
     -
     - 旧版
   * - axi4lite
     - 此镜像用于测试各种 AXI4 总线实现，包含用于观察和检查总线实现性能的 Vivado 集成逻辑分析仪（ILA）。
     -
     - 旧版
   * - tft
     - TFT FPGA 镜像支持连接 TFT 显示器，说明请见 :ref:`此处 <tft_displays>`。与 0.97 和 0.98 OS 版本兼容。
     -
     - 旧版
   * - mercury
     - Jupyter Notebook 应用使用的旧镜像，在最新 OS 版本中已由 :ref:`Python API 命令 <C&Py_API>` 替代。
     - Jupyter Notebook
     - 旧版


项目详细说明
==============================

以下页面介绍当前仓库布局中的活跃项目。这里有意不介绍 PyRPL 和 Examples。

.. toctree::
    :maxdepth: 1

    v0_94.rst
    stream_app.rst
    logic.rst
    barebones.rst
    fsbl.rst

|

板卡兼容性
=====================

并非所有项目都兼容所有 Red Pitaya 板卡。下表展示各项目与不同板卡版本的兼容性。

下表展示哪些项目可用于哪些板卡。

.. include:: fpga_project_table.inc

.. include:: fpga_project_flags.inc


.. note::

    旧版项目不再积极维护，可能与最新硬件修订版或软件版本不兼容。建议新开发使用活跃项目。

.. substitutions

.. FPGA 兼容性表的板卡引用
.. |125-10| replace:: :ref:`STEMlab 125-10 <top_125_10>`
.. |125-14| replace:: :ref:`STEMlab 125-14 <top_125_14>`
.. |125-14_z7020| replace:: :ref:`STEMlab 125-14 Z7020 <top_125_14_Z7020_LN>`
.. |125-14_gen2| replace:: :ref:`STEMlab 125-14 Gen 2 <top_125_14_gen2>`
.. |125-14_pro_gen2| replace:: :ref:`STEMlab 125-14 PRO Gen 2 <top_125_14_pro_gen2>`
.. |125-14_pro_z7020| replace:: :ref:`STEMlab 125-14 PRO Z7020 Gen 2 <top_125_14_pro_z7020_gen2>`
.. |125-14_TI| replace:: :ref:`STEMlab 125-14 TI <top_125_14_TI>`
.. |65-16_TI| replace:: :ref:`STEMlab 65-16 TI <top_65_16_TI>`
.. |122-16| replace:: :ref:`SDRlab 122-16 <top_122_16>`
.. |125-14_4in| replace:: :ref:`STEMlab 125-14 4-Input <top_125_14_4-IN>`
.. |250-12| replace:: :ref:`SIGNALlab 250-12 <top_250_12>`

.. |FPGA GitHub repository| replace:: `FPGA GitHub repository <https://github.com/RedPitaya/RedPitaya-FPGA>`__








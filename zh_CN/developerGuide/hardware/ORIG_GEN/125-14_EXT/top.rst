.. _top_125_14_EXT:

#############################################
STEMlab 125-14 外部时钟版（已停产）
#############################################

.. figure:: ../125-14/img/STEMlab-125-14.jpg
    :width: 500
    :align: center

.. note::

    STEMlab 125-14 外部时钟版已停产（不再生产）。此处文档供现有用户参考。

|

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

概述
========

STEMlab 125-14 外部时钟版是标准 :ref:`STEMlab 125-14 <top_125_14>` 的硬件改装版本，可接受外部时钟源。
出厂时已移动 SMD 电阻，将 E2 连接器上的 Ext. ADC Clk± 引脚直接连接到 ADC 时钟输入，并旁路板载振荡器。

此变体适用于需要与外部设备进行时钟同步或以非标准采样率工作的应用。

|

特性
========

* 14-bit、125 MS/s ADC 和 DAC（使用 125 MHz 时钟）
* 支持外部时钟输入（硬件已预先改装）
* 双核 ARM Cortex-A9 处理器
* FPGA Xilinx Zynq 7010 SoC
* 512 MB RAM
* 16 路数字 I/O、4 路模拟输入、4 路模拟输出
* 多种通信接口：I2C、SPI、UART、CAN
* Micro USB 连接，用于供电和控制台

|

快速参考
===============

.. list-table::
   :widths: 40 60
   :header-rows: 1

   * - 类别
     - 关键规格
   * - ADC
     - 2 通道、14-bit、125 MS/s、DC-60 MHz
   * - DAC
     - 2 通道、14-bit、125 MS/s、DC-60 MHz
   * - 处理器
     - 双核 ARM Cortex-A9
   * - FPGA
     - Xilinx Zynq 7010 SoC
   * - RAM
     - 512 MB
   * - 数字 I/O
     - 16 路 GPIO @ 3.3V
   * - 模拟 I/O
     - 4 路输入（12-bit）、4 路输出（8-bit）
   * - 连接能力
     - Ethernet、USB、扩展连接器
   * - 特殊功能
     - 外部时钟输入（LVDS）

|

与标准 STEMlab 125-14 的差异
==========================================

本板卡在电气特性上与 :ref:`STEMlab 125-14 <top_125_14>` 相同，但出厂时已实施以下硬件改动：

.. list-table::
    :widths: 38 45 45
    :header-rows: 1

    * - **参数**
      - **STEMlab 125-14**
      - **STEMlab 125-14 外部时钟版**
    * - 板载 125 MHz 振荡器
      - 启用（驱动 ADC、FPGA、DAC）
      - 已旁路（与时钟路径断开）
    * - E2 引脚 23–24（Ext. ADC Clk±）
      - 未连接
      - 启用——必须接收有效的 LVDS 时钟
    * - 外部 ADC 时钟
      - 否（需要硬件改装）
      - 是（已预先改装，即插即用）
    * - 电阻 R25、R26
      - 位于默认位置
      - 已移至 R23、R24
    * - 无外部时钟时的运行情况
      - 正常（使用板载振荡器）
      - FPGA 无法工作；PS 使用 33 MHz 时钟启动

.. warning::

    板载振荡器已被旁路。如果 E2 引脚 23–24（Ext. ADC Clk±）上没有有效的外部 LVDS 时钟，板卡 **将无法执行信号采集或生成**。让这些引脚悬空或提供错误信号会导致 FPGA 无法工作。

    * **OS 2.07-48 或更高版本：** Linux OS 仍可使用内部 33 MHz 振荡器启动，但 FPGA 功能不可用。
    * **OS 2.07-48 之前的版本：** 没有有效外部时钟信号时，板卡将无法启动。

.. note::

    将本板卡用于同步功能时：

    * :ref:`X-channel 2.0（Click Shield）同步 <click_shield_sync>` 与本板卡兼容。
    * :ref:`X-channel 同步 <x-ch_streaming>` 需要 X-channel 系统（Primary 和 Secondary 板卡），该系统不同于外部时钟型号。

|

技术规格
=========================

STEMlab 125-14 外部时钟版与 :ref:`标准 STEMlab 125-14 <top_125_14>` 具有相同规格，另有以下特性：

* **外部 ADC 时钟：** 是（硬件已为外部时钟输入预先改装）
* **硬件改装：** 将电阻 R25、R26 移至 R23、R24，以启用外部时钟输入

完整技术规格请参阅 :ref:`STEMlab 125-14 规格 <top_125_14>`。

.. seealso::

    有关更多详细信息，请参阅 |Original Gen comparison table|。

|

性能与测量
============================

快速模拟前端的测量结果见：

* :ref:`Original Gen — STEMlab 125-14 <measurements_orig_gen>`。

|

原理图与 3D 模型
========================

原理图
----------

* :download:`Schematics_STEM_125-14_v1.1.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_125-14_v1.1.pdf>`.

.. note::

    外部时钟版使用与标准 STEMlab 125-14 相同的 PCB。唯一的物理差异是将电阻 R25、R26 移至 R23、R24。

机械规格与 3D 模型
--------------------------------------

* STEP :download:`3D_STEM_125-14_v1.0.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_125-14_v1.0.zip>`.

|

高级功能
==================

外部 ADC 时钟
-------------------

.. include:: ../_specs_common/ext_adc_clk.inc

|

其他资源
====================

有关其他规格和测量结果，请参阅：

* :ref:`STEMlab 125-14 <top_125_14>` — 标准 STEMlab 125-14 规格
* |Original Gen hardware specs| — Original Gen 通用规格
* |Original Gen comparison table| — 所有 Red Pitaya Original Gen 型号的比较

|

法律声明与免责声明
===================

.. include:: ../_specs_common/disclaimer.inc

|

.. substitutions

.. |E2| replace:: :ref:`E2 连接器 <E2_orig_gen>`
.. |Original Gen hardware specs| replace:: :ref:`Original Gen 硬件规格 <hw_specs_orig_gen>`
.. |Original Gen comparison table| replace:: :ref:`Original Gen 板卡比较表 <rp-board-comp-orig_gen>`
.. _NB6L72: https://www.onsemi.com/pdf/datasheet/nb6l72-d.pdf

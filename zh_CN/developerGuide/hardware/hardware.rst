.. _dev_guide_hardware:

硬件
########

本节提供所有 Red Pitaya 产品的完整硬件文档，包括详细规格、原理图、已知问题和对比表。


理解产品名称
============================

Red Pitaya 板卡名称采用统一格式：**[采样率]-[输入分辨率]**

例如：

* **STEMlab 125-14** = 125 MSps 采样率、14 位输入分辨率
* **SDRlab 122-16** = 122.88 MSps 采样率、16 位输入分辨率
* **SIGNALlab 250-12** = 250 MSps 采样率、12 位输入分辨率

附加后缀表示不同变体：

* **PRO** = 专业功能（内部/外部时钟切换、外部 QSPI 与 eMMC 启动、扩展连接能力）
* **Z7020** = Zynq 7020 FPGA（逻辑容量是标准 Zynq 7010 的两倍）
* **4-Input** = 四个输入通道，而非两个
* **LN** = 低噪声变体
* **EXT** = 支持外部时钟

|

理解产品代际
===========================

Red Pitaya 产品分为两个不同的硬件代际。**将两代产品分开，是为了区分功能和能力有所改进的新款板卡。**

第二代与初代对比
------------------------------

**它们为何不同？**

与初代相比，第二代板卡在硬件方面有显著改进：

* **改进的模拟前端** — 降低噪声和串扰，提升 SFDR 性能
* **USB-C 连接** — 取代用于供电和控制台的 Micro USB（第二代需要 5 V、3 A，初代需要 5 V、2 A）
* **增强的输出能力** — 高阻负载时为 ±2 V、50 Ω 负载时为 ±1 V，而初代板卡为 ±1 V
* **无上电毛刺** — 启动期间输出保持稳定
* **OS 要求** — 第二代需要 OS 2.07-43 或更高版本；初代可使用更旧版本（参见 :ref:`OS 版本兼容性 <os_compatibility>`）

**PRO 型号额外提供：**

* 内部/外部时钟切换
* 带 STM32 微控制器的 E3 扩展板（电源、看门狗和启动控制）
* eMMC 和 QSPI 启动选项

**选择板卡时：**

* 如果需要最新硬件改进、更低噪声和更好的模拟性能，请 **选择第二代**
* 如果需要 SDRlab 122-16（16 位 ADC）或 SIGNALlab 250-12（250 MS/s、BNC 连接器、AC/DC 耦合）等特定型号，请 **选择初代**

详细对比请参阅 :ref:`第二代对比表 <rp-board-comp-gen2>` 和 :ref:`初代对比表 <rp-board-comp-orig_gen>`。

|


识别板卡
===================

为了确保与软件和附件兼容，正确识别 Red Pitaya 板卡十分重要。本节提供相关指南，帮助你根据物理特征、序列号和其他标识确定板卡型号。

* :ref:`识别板卡型号 <ID_guide>` — 帮助你识别 Red Pitaya 板卡型号的完整指南。

|

产品
=========

本节提供所有现有 Red Pitaya 产品的信息，包括第二代板卡、初代板卡、扩展模块、已停产产品和已淘汰产品。


第二代板卡
-------------------------

第二代 Red Pitaya 板卡旨在提供比初代更强的性能和功能。

.. toctree::
    :maxdepth: 1

    GEN2/125-14_Gen2/top.rst
    GEN2/125-14_Gen2_Pro/top.rst
    GEN2/125-14_Gen2_Z7020_Pro/top.rst
    GEN2/65-16_TI/top.rst
    GEN2/125-14_TI/top.rst
    GEN2/faq/faq.rst

.. note::

    即使名称相似，第二代产品也与初代产品有所不同。


初代板卡
----------------

初代 Red Pitaya 板卡。

.. toctree::
    :maxdepth: 1

    ORIG_GEN/125-14/top.rst
    ORIG_GEN/125-14_4IN/top.rst
    ORIG_GEN/125-14_Z7020/top.rst
    ORIG_GEN/122-16/top.rst
    ORIG_GEN/122-16_EXT/top.rst
    ORIG_GEN/250-12/top.rst


扩展模块
------------------

.. toctree::
    :maxdepth: 1

    ext_modules/sensor_ext/sensor_ext.rst
    ext_modules/click_shield/click_shield.rst
    ext_modules/lcr_ext/lcr_ext.rst
    ext_modules/logic_ext/logic_ext.rst
    ext_modules/impedance_transformer/impedance_transformer.rst
    ext_modules/e3_ext/e3_hardware.rst
    ext_modules/extent_template/extent_template.rst


已停产
--------------

已停产的板卡和扩展模块不再生产，但 Red Pitaya 软件仍提供支持。

.. toctree::
    :maxdepth: 1

    ORIG_GEN/125-14_EXT/top.rst
    ORIG_GEN/125-14_LN/top.rst
    ORIG_GEN/125-14_MULTI/top.rst
    ORIG_GEN/125-10/top.rst


已淘汰
---------

已淘汰的板卡和扩展模块不再生产，当前 Red Pitaya 软件也不再提供支持。每种产品下均列出最后可用的软件版本。

.. toctree::
    :maxdepth: 1

    ext_modules/sdr_module/sdr_module.rst

|

规格与对比
==============================

通用硬件规格
--------------------------------

本节包含各代 Red Pitaya 产品的通用硬件规格。

.. toctree::
    :maxdepth: 1
    
    GEN2/hw_specs/hw_specs.rst
    ORIG_GEN/hw_specs/hw_specs.rst



产品对比表
--------------------------

产品对比表详细概述不同 Red Pitaya 产品在规格、特性和能力方面的差异。

.. toctree::
    :maxdepth: 1

    GEN2/compares/vs.rst
    ORIG_GEN/compares/vs.rst



已知硬件问题
=======================

本节列出各代 Red Pitaya 产品的已知硬件问题。

.. toctree::
    :maxdepth: 1

    GEN2/known_hw_issues/known_hw_issues.rst
    ORIG_GEN/known_hw_issues/known_hw_issues.rst



性能与测量
============================

Red Pitaya 板卡的实测性能数据。

.. toctree::
    :maxdepth: 1

    ORIG_GEN/measurements/STEMlab-125-14/index.rst



证书
=============

可以在此查找并下载 Red Pitaya 产品证书。

.. toctree::
    :maxdepth: 1
    
    cets.rst

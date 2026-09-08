.. _top_125_14_4-IN:

################################################
STEMlab 125-14 4-Input（四输入版）
################################################

.. figure:: img/STEMlab-125-14-4-Input.jpg
    :width: 600
    :align: center

|

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

概述
========

STEMlab 125-14 4-Input 是一款专用单板 RF 信号采集平台，提供 4 路模拟输入通道，而非标准的 2 路输入加 2 路输出配置。
与标准 STEMlab 125-14 相比，本板卡降低了串扰、噪声和失真，改善了 RF 性能，并采用功能更强的 Zynq 7020 FPGA。
|E2| 连接器上的集成 CLK_SEL 控制引脚可在板载振荡器与外部时钟源之间无缝切换，无需进行硬件改装。

|

与标准 STEMlab 125-14 的主要差异
=============================================

* **4 路模拟输入通道** @ 125 MS/s、14-bit（取代 2 路输入加 2 路输出）
* **无 RF 输出** — 所有 SMA 连接器均用于输入
* **改进的 RF 性能：** 降低串扰、噪声和失真
* **Zynq 7020 FPGA：** 处理能力更强，提供 22 个数字 I/O 引脚（7010 板卡为 16 个）
* **外部时钟支持：** 硬件集成 CLK_SEL 引脚（|E2| 的引脚 21），无需硬件改装

|

特性
========

* 具有 4 路输入通道的 14-bit、125 MS/s ADC
* 无模拟 RF 输出（所有通道均用于输入）
* 改进的 RF 输入性能（降低串扰、噪声和失真）
* 双核 ARM Cortex-A9 处理器
* FPGA Xilinx Zynq 7020 SoC
* 512 MB RAM
* 22 路数字 I/O（比标准 Zynq 7010 板卡多 6 路）
* 扩展连接器上提供 4 路模拟输入和 4 路模拟输出
* 外部时钟输入，可通过硬件选择时钟源（CLK_SEL 引脚）
* 多种通信接口：I2C、SPI、UART、CAN

|

快速参考
===============

.. list-table::
   :widths: 40 60
   :header-rows: 1

   * - **类别**
     - **关键规格**
   * - ADC
     - 4 通道、14-bit、125 MS/s、DC-60 MHz
   * - DAC
     - 无（无 RF 输出）
   * - 处理器
     - 双核 ARM Cortex-A9
   * - FPGA
     - Xilinx Zynq 7020 SoC
   * - RAM
     - 512 MB
   * - 数字 I/O
     - 22 路 GPIO @ 3.3V
   * - 模拟 I/O
     - 4 路输入（12-bit）、4 路输出（8-bit）
   * - 连接能力
     - Ethernet、USB、扩展连接器
   * - 特殊功能
     - 外部 ADC 时钟

|

板卡布局与引脚排列
======================

.. figure:: ../125-14/img/Red_Pitaya_pinout.jpg
    :alt: Red Pitaya 引脚排列
    :width: 700
    :align: center

|

技术规格
=========================

.. list-table::
   :widths: 30 30 15 15
   :header-rows: 1

   * - **参数**
     - **数值**
     - **单位**
     - **备注**
   * - **基本参数**
     - 
     - 
     - 
   * - 处理器
     - 双核 ARM Cortex-A9
     - \-
     - 
   * - FPGA
     - FPGA AMD (Xilinx) Zynq 7020 SoC
     - \-
     - 
   * - RAM
     - 512
     - MB
     - (4 Gb)
   * - 核心时钟频率
     - 125
     - MHz
     - 
   * - 系统存储
     - 最大 32 GB 的 Micro SD
     - \-
     - 
   * - 串行控制台连接器
     - Micro USB
     - \-
     - 
   * - 电源连接器
     - Micro USB
     - \-
     - 
   * - 功耗
     - 5 V, 2 A
     - \-
     - 最大
   * - **连接能力**
     - 
     - 
     - 
   * - Ethernet
     - 1
     - Gbit
     - 
   * - USB
     - USB-A 2.0
     - \-
     - 
   * - Wi-Fi
     - 需要 Wi-Fi 适配器
     - \-
     - 
   * - **RF 输入**
     - 
     - 
     - 
   * - RF 输入通道
     - 4
     - \-
     - 
   * - 采样率
     - 125
     - MS/s
     - 
   * - ADC 分辨率
     - 14
     - 位
     - 
   * - 输入阻抗
     - 1 MΩ / 10 pF
     - \-
     - 
   * - 满量程电压范围
     - ±1 (LV) / ±20 (HV)
     - V
     -
   * - 输入耦合
     - DC
     - \-
     - 
   * - 绝对最大输入电压
     - ±6 (LV) / ±30 (HV)
     - V
     - DC 数值 [#f1]_
   * - 输入 ESD 保护
     - 1500
     - V
     - DC
   * - 过载保护
     - 保护二极管
     - \-
     - 
   * - 带宽
     - DC - 60
     - MHz
     - 
   * - 连接器类型
     - SMA
     - \-
     - 
   * - **RF 输出**
     - 
     - 
     - 
   * - RF 输出通道
     - N/A
     - \-
     - 
   * - 采样率
     - N/A
     - \-
     - 
   * - DAC 分辨率
     - N/A
     - \-
     - 
   * - 负载阻抗
     - N/A
     - \-
     - 
   * - 电压范围
     - N/A
     - \-
     - 
   * - 输出耦合
     - N/A
     - \-
     - 
   * - 短路保护
     - N/A
     - \-
     - 
   * - 输出压摆率
     - N/A
     - \-
     - 
   * - 带宽
     - N/A
     - \-
     - 
   * - 连接器类型
     - N/A
     - \-
     - 
   * - **扩展连接器**
     - 
     - 
     - 
   * - 数字 GPIO
     - 22
     - \-
     - 
   * - 数字电压电平
     - 3.3
     - V
     - 
   * - GPIO 时间分辨率
     - 8
     - ns
     - 核心时钟频率
   * - 模拟输入
     - 4
     - \-
     - 
   * - 模拟输入电压范围
     - 0 - 7.0
     - V
     - 
   * - 模拟输入分辨率
     - 12
     - 位
     - 
   * - 模拟输入采样率 [#f8]_
     - 100
     - kS/s
     - 
   * - 模拟输出
     - 4
     - \-
     - 
   * - 模拟输出电压范围
     - 0 - 1.8
     - V
     - 
   * - 模拟输出分辨率
     - 8
     - 位
     - 
   * - 模拟输出采样率
     - ≲ 3.2
     - MS/s
     - 
   * - 模拟输出带宽 [#f9]_
     - ≈ 160
     - kHz
     - 
   * - 通信接口
     - I2C, SPI, UART, CAN
     - \-
     - 
   * - 可用电压 [#f10]_
     - +5, ±3.3
     - V
     - 
   * - 外部 ADC 时钟
     - 是
     - \-
     - |E2| 上的 CLK_SEL 引脚
   * - **同步**
     - 
     - 
     - 
   * - 外部触发输入
     - DIO0_P
     - \-
     - E1 连接器
   * - 外部触发输入阻抗
     - Hi-Z
     - \-
     - 数字输入
   * - 触发输出
     - DIO0_N
     - \-
     - E1 连接器 [#f3]_
   * - 菊花链连接器（S1 与 S2）
     - 是
     - \-
     - 
   * - 菊花链连接器速度
     - 最高 500
     - Mb/s
     - 
   * - 菊花链连接器类型
     - SATA
     - \-
     - 
   * - 参考时钟输入
     - 是 [#f4]_
     - \-
     - 需要硬件改装
   * - 参考时钟频率
     - 10
     - MHz
     - 需要硬件改装
   * - 参考时钟连接器类型
     - 2 引脚排针
     - \-
     - 需要硬件改装
   * - **启动选项**
     - 
     - 
     - 
   * - SD 卡
     - 是
     - \-
     - 
   * - QSPI
     - 未装配
     - \-
     - 
   * - eMMC
     - N/A
     - \-
     - 
   * - **环境规格**
     - 
     - 
     - 
   * - 工作温度范围
     - 0–55
     - ℃
     - 使用默认散热器
   * - 工作湿度范围
     - < 90%
     - RH
     - 
   * - 自动关机温度
     - 85
     - ℃
     - 
   * - **尺寸**
     - 
     - 
     - 
   * - 尺寸（长 x 宽 x 高）
     - 106.8 x 60.0 x 21.1
     - mm
     - 详情见 :ref:`原理图 <schematics_125_14_4_IN>`

.. seealso::

    有关更多详细信息，请参阅 |Original Gen comparison table|。

|

.. warning::

    **最大输入电压**

    * **LV 模式：** 绝对最大值 ±6 V
    * **HV 模式：** 绝对最大值 ±30 V

    超过这些数值可能对板卡造成永久损坏。

|

性能与测量
============================

.. note::

    虽然尚未发布 STEMlab 125-14 4-Input 板卡的专门测量结果，但预计其性能处于 STEMlab 125-14 与 STEMlab 125-14 Gen 2 板卡的测量范围内。
    4-Input 板卡在 STEMlab 125-14 Gen 2 之前不久生产，并采用了 Gen 2 的部分模拟前端改进。

快速模拟前端的测量结果见：

* :ref:`Original Gen — STEMlab 125-14 <measurements_orig_gen>`。
* :ref:`Gen 2 — STEMlab 125-14 Gen 2 <measurements_gen2>`。

|

.. _schematics_125_14_4_IN:

原理图与 3D 模型
========================

原理图
----------

* :download:`Schematics_STEM_125-14-4_IN_V1r3.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_STEM_125-14-4_IN_V1r3.pdf>`。

.. note::

    Red Pitaya 板卡不提供完整的硬件原理图。Red Pitaya 的代码是开源的，但硬件原理图并不开源；不过仍提供开发用原理图。
    该原理图包含硬件配置、FPGA 引脚连接等信息。

机械规格与 3D 模型
--------------------------------------

.. * PDF :download:`3D_STEM_125-14-4_IN_V1r3.pdf.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_125-14-4_IN_V1r3.pdf.zip>`.

* STEP :download:`3D_STEM_125-14-4_IN_V1r3.zip <https://downloads.redpitaya.com/doc/3D_models/3D_STEM_125-14-4_IN_V1r3.zip>`.

|

硬件详情
==================

组件
----------

**ADC：** Analog Devices `LTC2145-14 <https://www.analog.com/en/products/ltc2145-14.html>`_

    * 双通道 14-bit、125 MS/s ADC
    * 低噪声和低失真
    * 高动态范围

.. note::

    4-Input 板卡使用两颗 LTC2145-14 ADC 芯片实现 4 路输入通道。

**FPGA：** Xilinx `Zynq 7020 <https://docs.xilinx.com/v/u/en-US/ds190-Zynq-7000-Overview>`_

    * 双核 ARM Cortex-A9 @ 667 MHz
    * 可编程逻辑资源多于 Zynq 7010
    * E1 扩展连接器上有 22 路数字 I/O

**振荡器：** `IQ3309 <https://eu.mouser.com/datasheet/2/417/bf-8746.pdf>`_ 125 MHz

    * 提供默认 ADC 时钟
    * CLK_SEL = GND（外部时钟模式）时被旁路

|

扩展连接器与接口
===================================

概述
---------

STEMlab 125-14 4-Input 板卡具有以下连接器和接口：

* **E1 和 E2 连接器：** 主要扩展连接器，提供数字 I/O、模拟 I/O 和通信接口，可用于连接其他硬件、传感器或外设。
* **S1 和 S2 连接器：** 直接连接到 FPGA 的 SATA 连接器。与 STEMlab 125-14 不同，本板卡不支持通过这些连接器进行多板时钟同步，因为共享时钟信号不会传递到 ADC 和 DAC。
  这些连接器仍可用于在板卡或外部设备之间交换时钟、触发或数据信号。请注意，其电压电平为 1V8，并非 SATA 连接的标准电平。

|

连接器物理规格
----------------------------------

**E1 和 E2 扩展连接器：**

* 连接器类型：`2 x 13 引脚、IDC、2.54 mm 间距 <https://www.digikey.com/en/products/detail/adam-tech/BHR-26-VUA/9832284>`_
* 引脚数量：每个 26 个引脚（2x13 配置）
* 间距：2.54 mm (0.1")

**配对连接器：**

.. note::

    为自定义 Red Pitaya 扩展板选择配对连接器时，需要使用 `双层高度加高插座 <https://www.digikey.com/en/products/detail/samtec-inc/ESW-113-33-T-D/6693225>`_，以避开板卡上的散热器和以太网连接器。
    任何 *绝缘体高度* 不低于 0.635" (16.13 mm) 的连接器均可使用。此净空要求取决于板卡上最高的组件（散热器和以太网连接器）。

.. note::

    为防止损坏板卡或扩展板，将扩展板连接到 E1 和 E2 连接器时，请确保：

    * **连接器正确对齐** — 确保连接器正确对齐。Red Pitaya 板卡连接器的插座外壳留有额外空间，因此扩展板即使错位 ±1 个引脚，在外观上仍可能像是已连接。这可能损坏板卡和/或扩展板，请在上电前再次检查对齐情况。
    * **配对牢固** — 使用连接牢固的连接器，以防意外断开或损坏。

|

.. _E1_4IN:

E1 连接器——数字 I/O 与 CAN
----------------------------------

.. include:: ../_specs_common/E1_connector_7020.inc

|

.. _E2_4IN:

E2 连接器——模拟与通信
--------------------------------------

E2 扩展连接器提供模拟 I/O 和通信接口，并包含用于在板载振荡器与外部 ADC 时钟之间切换的 **CLK_SEL** 引脚。

**特性：**

* +5 V 电源（最大 0.5 A，与 USB 设备共享）
* -3.4 V 电源（最大 0.05 A）[#f7]_
* SPI、UART、I2C 通信接口
* 4 路慢速 ADC（12-bit、100 kS/s）
* 4 路慢速 DAC（8-bit PWM、≲ 3.2 MS/s）
* CLK_SEL 引脚（引脚 21）：GND = 外部时钟，3V3/悬空 = 内部时钟
* 引脚 23–24 上的外部 ADC 时钟输入（Ext. ADC Clk±）

**E2 引脚排列：**

.. list-table::
    :widths: 5 24 19 47 16
    :header-rows: 1

    * - 引脚
      - 说明
      - FPGA 引脚编号
      - FPGA 引脚说明
      - 电压电平
    * - 1
      - +5V
      - 
      - 
      - 
    * - 2
      - -3.4V [#f7]_
      - 
      - 
      - 
    * - 3
      - SPI (MOSI)
      - E9
      - PS_MIO10_500
      - 3V3
    * - 4
      - SPI (MISO)
      - C6
      - PS_MIO11_500
      - 3V3
    * - 5
      - SPI (SCK)
      - D9
      - PS_MIO12_500
      - 3V3
    * - 6
      - SPI (CS)
      - E8
      - PS_MIO13_500
      - 3V3
    * - 7
      - UART (TX)
      - D5
      - PS_MIO8_500
      - 3V3
    * - 8
      - UART (RX)
      - B5
      - PS_MIO9_500
      - 3V3
    * - 9
      - I2C (SCL)
      - B13
      - PS_MIO50_501
      - 3V3
    * - 10
      - I2C (SDA)
      - B9
      - PS_MIO51_501
      - 3V3
    * - 11
      - 外部通信模式（AIN）
      - 
      - 
      - GND（默认）
    * - 12
      - GND
      - 
      - 
      - 
    * - 13
      - 模拟输入 0
      - B19, A20
      - IO_L2P_T0_AD8P_35, IO_L2N_T0_AD8N_35
      - 0-7.0 V
    * - 14
      - 模拟输入 1
      - C20, B20
      - IO_L1P_T0_AD0P_35, IO_L1N_T0_AD0N_35
      - 0-7.0 V
    * - 15
      - 模拟输入 2
      - E17, D18
      - IO_L3P_T0_DQS_AD1P_35, IO_L3N_T0_DQS_AD1N_35
      - 0-7.0 V
    * - 16
      - 模拟输入 3
      - E18, E19
      - IO_L5P_T0_AD9P_35, IO_L5N_T0_AD9N_35
      - 0-7.0 V
    * - 17
      - 模拟输出 0
      - T10
      - IO_L1N_T0_34
      - 0-1.8 V
    * - 18
      - 模拟输出 1
      - T11
      - IO_L1P_T0_34
      - 0-1.8 V
    * - 19
      - 模拟输出 2
      - P15
      - IO_L24P_T3_34
      - 0-1.8 V
    * - 20
      - 模拟输出 3
      - U13
      - IO_L3P_T0_DQS_PUDC_B_34
      - 0-1.8 V
    * - 21
      - CLK_SEL
      - 
      - 
      - 3.3V / GND
    * - 22
      - GND
      - 
      - 
      - 
    * - 23
      - Ext. ADC Clk+
      - 
      - 
      - LVDS
    * - 24
      - Ext. ADC Clk-
      - 
      - 
      - LVDS
    * - 25
      - GND
      - 
      - 
      - 
    * - 26
      - GND
      - 
      - 
      - 

.. note::

    **UART TX (PS_MIO08)** 仅用作输出。上电时必须将其连接到 GND 或保持悬空（不得外接上拉电阻）！

.. note::

    **CLK_SEL 引脚（引脚 21）：** 拉至 **GND** 可选择外部时钟模式（引脚 23–24 上的 Ext. ADC Clk±）；拉至 **3V3** 或保持悬空可使用板载振荡器
    （内部时钟模式）。


|

辅助模拟输入与输出
------------------------------------

.. include:: ../_specs_common/slow_analog_io.inc

|

通用数字 I/O 通道
--------------------------------------

.. list-table::
   :widths: 30 30 15 15
   :header-rows: 1

   * - **参数**
     - **数值**
     - **单位**
     - **备注**
   * - GPIO 数量
     - 22
     - \-
     - 
   * - 数字电压电平
     - 3.3
     - V
     - 
   * - 绝对最小电压
     - -0.40
     - V
     - 
   * - 绝对最大电压
     - 3.3 + 0.55
     - V
     - 
   * - 电流限制
     - < 8
     - mA
     - 驱动能力
   * - 方向
     - 可配置
     - \-
     - 
   * - 时间分辨率
     - 8
     - ns
     - (1/125 MHz)
   * - 连接器位置
     - 扩展连接器 |E1|
     - \-
     - 

|

同步连接器（S1 与 S2）
--------------------------------------

.. include:: ../_specs_common/Sync_connectors_SATA_nosync.inc

|

高级功能
==================

电源
-------------

.. include:: ../_specs_common/power_supply.inc

|

外部 ADC 时钟
-------------------

.. include:: ../../GEN2/_specs_common/ext_adc_clk.inc

|

.. _ref_clk_4IN:

将振荡器锁定到外部 10 MHz 参考源
--------------------------------------------------------

可将内部振荡器锁定到通过 |E1| 连接器上的 DIO10 差分对（DIO10_P 和 DIO10_N）提供的外部 10 MHz 时钟。

.. figure:: img/4-Input_external_10MHz_ref.png
    :width: 600
    :align: center

这需要对板卡进行硬件改装：安装可选的 `Si570/Si571 VXCO <https://www.skyworksinc.com/-/media/skyworks/sl/documents/public/data-sheets/si570-71.pdf>`_
（压控振荡器），并使用 FPGA 将振荡器锁定到外部 10 MHz 时钟。

振荡器通过 FPGA 上的 PPL_LO（K14、IO_L20P_T3_AD6P_35）和 PLL_HI（J15、IO_25_35）引脚同步。

如果您对此功能感兴趣，请通过 support@redpitaya.com 联系我们。

|

校准
------------

.. include:: ../_specs_common/calibration.inc

|

其他资源
====================

有关其他规格和测量结果，请参阅：

* |Original Gen hardware specs| — Original Gen 通用规格
* |Original Gen comparison table| — 所有 Red Pitaya Original Gen 型号的比较

|

法律声明与免责声明
===================

.. include:: ../_specs_common/disclaimer.inc

|

.. rubric:: 脚注

.. [#f1] 绝对最大输入电压值适用于低于 1 kHz 的频率。对于更高频率，请将输入电压范围规格作为 **绝对最大值**。
.. [#f3] 请参阅 :ref:`X-channel 2.0（Click Shield）同步 <click_shield_sync>` 和 :ref:`X-channel 2.0（Click Shield）同步示例 <examples_multiboard_sync>`。
.. [#f4] 此功能需要安装可选 VXCO，对板卡进行硬件改装。更多详情见 :ref:`将振荡器锁定到外部 10 MHz 参考源章节 <ref_clk_4IN>`。
.. [#f7] 在较早的板卡修订版中，引脚 2 上的电源电压可能标为 -3.3 V，实际测量电压通常为 -3.4 V。
.. [#f8] 默认软件以取决于 CPU 的速度采样。若要以 100 kS/s 采集数据，必须实现额外的 FPGA 处理。
.. [#f9] 输出经过一阶低通滤波器。如需额外滤波，可根据具体应用要求在外部实现。
.. [#f10] 取决于具体应用。输出电流由扩展连接器和已连接的 USB 设备共享；未使用其他外设时，电流可以更高。

.. substitutions

.. |E1| replace:: :ref:`E1 连接器 <E1_4IN>`
.. |E2| replace:: :ref:`E2 连接器 <E2_4IN>`
.. |Original Gen hardware specs| replace:: :ref:`Original Gen 硬件规格 <hw_specs_orig_gen>`
.. |Original Gen comparison table| replace:: :ref:`Original Gen 板卡比较表 <rp-board-comp-orig_gen>`
.. _NB6L72: https://www.onsemi.com/pdf/datasheet/nb6l72-d.pdf

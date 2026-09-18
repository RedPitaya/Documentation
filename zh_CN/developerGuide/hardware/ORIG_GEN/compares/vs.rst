.. _rp-board-comp-orig_gen:

产品比较表（初代）
############################################

.. note::

    需要 Gen 2 产品比较表？请查看 :ref:`Gen 2 产品比较表 <rp-board-comp-gen2>`。

.. list-table::
    :widths: 20 30 30 30 30 30 30
    :align: center
    :header-rows: 1

    * - 
      - :ref:`STEMlab 125-14 <top_125_14>` |br| :ref:`STEMlab 125-14 LN <top_125_14_LN>` |br| :ref:`STEMlab 125-14 ext. clk <top_125_14_EXT>`
      - :ref:`STEMlab 125-14 Z7020 LN <top_125_14_Z7020_LN>`
      - :ref:`STEMlab 125-14 4-Input <top_125_14_4-IN>`
      - :ref:`SDRlab 122-16 <top_122_16>` |br| :ref:`SDRlab 122-16 ext. clk <top_122_16_EXT>`
      - :ref:`SIGNALlab 250-12 <top_250_12>`
      - :ref:`STEMlab 125-10 <top_125_10>` |br|
    * - |br| **基本信息**
      - 
      - 
      - 
      - 
      - 
      - 
    * - 处理器
      - 双核 ARM Cortex-A9
      - 双核 ARM Cortex-A9
      - 双核 ARM Cortex-A9
      - 双核 ARM Cortex-A9
      - 双核 ARM Cortex-A9
      - 双核 ARM Cortex-A9
    * - FPGA
      - FPGA AMD (Xilinx) Zynq 7010 SoC
      - FPGA AMD (Xilinx) Zynq 7020 SoC
      - FPGA AMD (Xilinx) Zynq 7020 SoC
      - FPGA AMD (Xilinx) Zynq 7020 SoC
      - FPGA AMD (Xilinx) Zynq 7020 SoC
      - FPGA AMD (Xilinx) Zynq 7010 SoC
    * - RAM
      - 512 MB (4 Gb)
      - 512 MB (4 Gb)
      - 512 MB (4 Gb)
      - 512 MB (4 Gb)
      - 1 GB (8 Gb)
      - 256 MB (2 Gb)
    * - 核心时钟频率
      - 125 MHz
      - 125 MHz
      - 125 MHz
      - 122.88 MHz
      - 250 MHz
      - 125 MHz
    * - 系统存储
      - Micro SD 最高 32 GB
      - Micro SD 最高 32 GB
      - Micro SD 最高 32 GB
      - Micro SD 最高 32 GB
      - Micro SD 最高 32 GB
      - Micro SD 最高 32 GB
    * - 串行控制台连接器
      - Micro USB
      - Micro USB
      - Micro USB
      - Micro USB
      - USB-C
      - 3 针连接器（未安装）
    * - 电源连接器
      - Micro USB
      - Micro USB
      - Micro USB
      - Micro USB
      - | 电源插座，| RJ45（仅 PoE 版本）
      - Micro USB
    * - 功耗
      - 5 V, 2 A max
      - 5 V, 2 A max
      - 5 V, 2 A max
      - 5 V, 2 A max
      - 24 V, 0.5 A max
      - 5 V, 1.5 A max
    * - |br| **连接**
      - 
      - 
      - 
      - 
      - 
      - 
    * - Ethernet
      - 1 Gbit
      - 1 Gbit
      - 1 Gbit
      - 1 Gbit
      - 1 Gbit
      - 1 Gbit
    * - USB
      - USB-A 2.0
      - USB-A 2.0
      - USB-A 2.0
      - USB-A 2.0
      - USB-A 2.0 (2x)
      - USB-A 2.0
    * - Wi-Fi
      - 需要 Wi-Fi 加密狗
      - 需要 Wi-Fi 加密狗
      - 需要 Wi-Fi 加密狗
      - 需要 Wi-Fi 加密狗
      - 需要 Wi-Fi 加密狗
      - 需要 Wi-Fi 加密狗
    * - |br| **RF 输入**
      - 
      - 
      - 
      - 
      - 
      - 
    * - RF 输入通道
      - 2
      - 2
      - 4
      - 2
      - 2
      - 2
    * - 采样率
      - 125 MS/s
      - 125 MS/s
      - 125 MS/s
      - 122.88 MS/s
      - 250 MS/s
      - 125 MS/s
    * - ADC 分辨率
      - 14 bit
      - 14 bit
      - 14 bit
      - 16 bit
      - 12 bit
      - 10 bit
    * - 输入阻抗
      - 1 MΩ / 10 pF
      - 1 MΩ / 10 pF
      - 1 MΩ / 10 pF
      - 50 Ω
      - 1 MΩ
      - 1 MΩ / 10 pF
    * - 满量程电压范围
      - | ±1 V (LV) | ±20 V (HV)
      - | ±1 V (LV) | ±20 V (HV)
      - | ±1 V (LV) | ±20 V (HV)
      - 0.5 Vpp/-2 dBm
      - | ±1 V | ±20 V（SW 可选）
      - | ±1 V (LV) | ±20 V (HV)
    * - 输入耦合
      - DC
      - DC
      - DC
      - AC
      - AC / DC（SW 可选）
      - DC
    * - **绝对最大值** **输入电压** [#f1]_
      - | **LV ±6 V** | **HV ±30 V**
      - | **LV ±6 V** | **HV ±30 V**
      - | **LV ±6 V** | **HV ±30 V**
      - | **DC 最大 50 V（AC 耦合）** | **用于 RF 的 1 Vpp**
      - | **LV ±6 V** | **HV ±30 V**
      - | **LV ±6 V** | **HV ±30 V**
    * - 输入 ESD 保护
      - 1500 VDC
      - 1500 VDC
      - 1500 VDC
      - 否
      - 1500 VDC
      - 1500 VDC
    * - 过载保护
      - 保护二极管
      - 保护二极管
      - 保护二极管
      - 直流电压保护
      - 保护二极管
      - 保护二极管
    * - 带宽
      - DC - 60 MHz
      - DC - 60 MHz
      - DC - 60 MHz
      - 300 kHz - 550 MHz（欠采样）
      - DC - 60 MHz
      - DC - 50 MHz
    * - 连接器类型
      - SMA
      - SMA
      - SMA
      - SMA
      - BNC
      - SMA
    * - |br| **RF 输出**
      - 
      - 
      - 
      - 
      - 
      - 
    * - RF 输出通道
      - 2
      - 2
      - N/A
      - 2
      - 2
      - 2
    * - 采样率
      - 125 MS/s
      - 125 MS/s
      - N/A
      - 122.88 MS/s
      - 250 MS/s
      - 125 MS/s
    * - DAC 分辨率
      - 14 bit
      - 14 bit
      - N/A
      - 14 bit
      - 14 bit
      - 10 bit
    * - 负载阻抗
      - 50 Ω
      - 50 Ω
      - N/A
      - 50 Ω
      - 50 Ω / Hi-Z
      - 50 Ω
    * - 电压范围
      - ±1 V
      - ±1 V
      - N/A
      - 0.5 Vpp/ -2 dBm（50 Ω 负载）
      - | ±1 V @ 50 Ω（x1 缩放）| ±2 V @ Hi-Z（x1 缩放）| ±5 V @ 50 Ω（x5 缩放）| ±10 V @ Hi-Z（x5 缩放）
      - ±1 V
    * - 输出耦合
      - DC
      - DC
      - N/A
      - AC
      - DC
      - DC
    * - 短路保护
      - 是
      - 是
      - N/A
      - 否
      - 是
      - 是
    * - 输出压摆率
      - 2 V / 10 ns
      - 2 V / 10 ns
      - N/A
      - N/A
      - 10 V / 17 ns
      - 2 V / 10 ns
    * - 带宽
      - DC - 60 MHz
      - DC - 60 MHz
      - N/A
      - 300 kHz - 60 MHz
      - DC - 60 MHz
      - DC - 50 MHz
    * - 连接器类型
      - SMA
      - SMA
      - N/A
      - SMA
      - BNC
      - SMA
    * - |br| **扩展连接器**
      - 
      - 
      - 
      - 
      - 
      - 
    * - 数字 IO
      - 16
      - 22
      - 22
      - 22
      - 19
      - 16
    * - 数字电压电平
      - 3.3 V
      - 3.3 V
      - 3.3 V
      - 3.3 V
      - 3.3 V
      - 3.3 V
    * - GPIO 时间分辨率
      - 8 ns
      - 8 ns
      - 8 ns
      - 8.138 ns
      - 4 ns
      - 8 ns
    * - 模拟输入
      - 4
      - 4
      - 4
      - 4
      - 4
      - 4
    * - 模拟输入电压范围
      - 0 - 7.0 V
      - 0 - 7.0 V
      - 0 - 7.0 V
      - 0 - 7.0 V
      - 0 - 7.0 V
      - 0 - 7.0 V
    * - 模拟输入分辨率
      - 12 bit
      - 12 bit
      - 12 bit
      - 12 bit
      - 12 bit
      - 12 bit
    * - 模拟输入采样率
      - 100 kS/s
      - 100 kS/s
      - 100 kS/s
      - 100 kS/s
      - 100 kS/s
      - 100 kS/s
    * - 模拟输出
      - 4
      - 4
      - 4
      - 4
      - 4
      - 4
    * - 模拟输出电压范围
      - 0 - 1.8 V
      - 0 - 1.8 V
      - 0 - 1.8 V
      - 0 - 1.8 V
      - 0 - 1.8 V
      - 0 - 1.8 V
    * - 模拟输出分辨率
      - 8 bit
      - 8 bit
      - 8 bit
      - 8 bit
      - 8 bit
      - 8 bit
    * - 模拟输出采样率
      - ≲ 3.2 MS/s
      - ≲ 3.2 MS/s
      - ≲ 3.2 MS/s
      - ≲ 3.2 MS/s
      - ≲ 3.2 MS/s
      - ≲ 3.2 MS/s
    * - 模拟输出带宽
      - ≈ 160 kHz
      - ≈ 160 kHz
      - ≈ 160 kHz
      - ≈ 160 kHz
      - ≈ 160 kHz
      - ≈ 160 kHz
    * - 通信接口
      - I2C, SPI, UART, CAN
      - I2C, SPI, UART, CAN
      - I2C, SPI, UART, CAN
      - I2C, SPI, UART, CAN
      - I2C, SPI, UART, CAN, USB
      - I2C, SPI, UART, CAN
    * - 可用电压
      - +5 V, +3V3, -3V4
      - +5 V, +3V3, -4 V
      - +5 V, ±3V3
      - +5 V, +3V3
      - +5 V, +3V3, -5V4
      - +5 V, +3V3, -3V4
    * - 外部 ADC 时钟
      - 仅外部时钟型号 [#f2]_
      - 仅外部时钟型号 [#f2]_
      - 是
      - 仅外部时钟型号 [#f2]_
      - 是
      - N/A
    * - |br| **同步**
      - 
      - 
      - 
      - 
      - 
      - 
    * - 外部触发输入
      - E1 连接器（DIO0_P）
      - E1 连接器（DIO0_P）
      - E1 连接器（DIO0_P）
      - E1 连接器（DIO0_P）
      - BNC 连接器
      - E1 连接器（DIO0_P）
    * - 外部触发输入阻抗
      - Hi-Z（数字输入）
      - Hi-Z（数字输入）
      - Hi-Z（数字输入）
      - Hi-Z（数字输入）
      - | 10 kΩ (HW_rev 1.0-1.2a) | 1 kΩ (HW_rev 1.2b)
      - Hi-Z（数字输入）
    * - 触发输出 [#f3]_
      - E1 连接器（DIO0_N）
      - E1 连接器（DIO0_N）
      - E1 连接器（DIO0_N）
      - E1 连接器（DIO0_N）
      - E1 连接器（DIO0_N）
      - E1 连接器（DIO0_N）
    * - 菊链连接器（S1 和 S2）
      - 是
      - 是
      - 是
      - 是
      - 是
      - N/A
    * - 菊链连接器速度
      - up to 500 Mb/s
      - up to 500 Mb/s
      - up to 500 Mb/s
      - up to 500 Mb/s
      - up to 500 Mb/s
      - N/A
    * - 菊链连接器类型
      - SATA
      - SATA
      - SATA
      - SATA
      - eSATA
      - N/A
    * - 参考时钟输入
      - N/A
      - N/A
      - 是 (HW mod.)
      - N/A
      - 是
      - N/A
    * - 参考时钟频率
      - N/A
      - N/A
      - 10 MHz (HW mod.)
      - N/A
      - 10 MHz
      - N/A
    * - 参考时钟连接器类型
      - N/A
      - N/A
      - 2 针排针
      - N/A
      - SMA（后面板）
      - N/A
    * - |br| **启动选项**
      - 
      - 
      - 
      - 
      - 
      - 
    * - SD 卡
      - 是
      - 是
      - 是
      - 是
      - 是
      - 是
    * - QSPI
      - 未安装
      - 未安装
      - 未安装
      - 未安装
      - N/A
      - N/A
    * - eMMC
      - N/A
      - N/A
      - N/A
      - N/A
      - N/A
      - N/A
    * - |br| **环境规格**
      - 
      - 
      - 
      - 
      - 
      - 
    * - 工作温度范围 [#f4]_
      - 0 to 55℃
      - 0 to 55℃
      - 0 to 55℃
      - 0 to 55℃
      - 0 to 55℃
      - 0 to 55℃
    * - 工作湿度范围
      - < 90% RH
      - < 90% RH
      - < 90% RH
      - < 90% RH
      - < 90% RH
      - < 90% RH
    * - 自动关机温度
      - 85℃
      - 85℃
      - 85℃
      - 85℃
      - 85℃
      - 85℃
.. warning::

    **最大输入电压（仅 SDRlab）**

    * **RF 信号：** 最大 1 Vpp（标称 0.5 Vpp）
    * **DC 电压：** 最高 50 V（输入为 AC 耦合，DC 不会传递到 ADC）

    超过 RF 输入电平可能永久损坏板卡。

.. warning::

    **最大输入电压**
    
    * **LV 模式：** 绝对最大值 ±6 V
    * **HV 模式：** 绝对最大值 ±30 V
    
    超过这些数值可能永久损坏板卡。

.. rubric:: 脚注

.. [#f1] 绝对最大输入电压值适用于低于 1 kHz 的频率。对于更高频率，请将输入电压范围规格作为 **绝对最大值**。
.. [#f2] 更多信息请参阅外部时钟板卡型号。
.. [#f3] 有关触发输出配置，请参阅 :ref:`X-channel 2.0 (Click Shield) 同步 <click_shield_sync>` 和 :ref:`X-channel 2.0 (Click Shield) 同步示例 <examples_multiboard_sync>`。
.. [#f4] 使用默认散热器时的数值。采用定制冷却方案可能支持更高温度，但为防止损坏，板卡会在 85℃ 时自动关机。

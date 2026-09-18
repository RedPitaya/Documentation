.. _measurements_gen2_outputs:

###########################
快速模拟输出
###########################

本页包含 Gen 2 快速模拟输出的详细规格和性能测量结果。

.. contents::
   :local:
   :depth: 2
   :backlinks: none

|

规格
========================

.. list-table::
    :header-rows: 1
    :widths: 30 30 15 15

    * - **参数**
      - **数值**
      - **单位**
      - **备注**
    * - **RF 输出**
      -
      -
      -
    * - RF 输出通道
      - 2
      - \-
      -
    * - 采样率
      - 125
      - MS/s
      -
    * - DAC 分辨率
      - 14
      - 位
      -
    * - 负载阻抗
      - 50 Ω (Hi-Z)
      - \-
      -
    * - 电压范围
      - | ±1 @ 50 Ω
        | ±2 @ Hi-Z
      - V
      -
    * - 输出耦合
      - DC
      - \-
      -
    * - 短路保护
      - 是
      - \-
      -
    * - 输出压摆率
      - 200
      - V/μs
      -
    * - RF 输出抖动 @40 MHz
      - 20
      - ps
      - RMS，典型值
    * - 带宽
      - DC - 50
      - MHz
      - 典型值
    * - 连接器类型
      - SMA
      - \-
      -

.. note::

    连接负载前，应在软件中设置输出负载阻抗。

|

硬件详情
========================

输出级原理图
-----------------------

输出级由缓冲放大器、低通滤波器和 DAC 驱动器组成。

.. figure:: img/schematics/Fast_analog_output_schematics.png
    :width: 800

更多信息请参阅各板卡的硬件文档。

|

性能测量
==========================

输出带宽
------------------

+------------------------------------+------------------------------------+
| 负载阻抗                           | 带宽                               |
+====================================+====================================+
| 50 Ω                               | 54.3 MHz (-3 dB)                   |
+------------------------------------+------------------------------------+
| High-Z                             | 55.0 MHz (-3 dB)                   |
+------------------------------------+------------------------------------+

.. figure:: img/RF_outputs/Bandwidth/OUT1LOW.png
    :width: 800

输出通道 1 在 50 Ω 负载下的带宽测量。

.. figure:: img/RF_outputs/Bandwidth/OUT1HIGH.png
    :width: 800

输出通道 1 在高阻负载下的带宽测量。

|

输出带宽平坦度
--------------------------

从 DC 到完整（-3 dB）带宽范围内，输出带宽平坦度保持在 -1 dB 以内。

|

输出阻抗
------------------

下图显示了输出通道（输出放大器和滤波器）的阻抗，同时给出原始 *STEMlab 125-14* 的输出阻抗以供比较。

.. figure:: img/RF_outputs/Output_impedance/Output_impedance.png
    :width: 800

原始板卡和 Gen 2 的输出阻抗测量。

.. figure:: img/RF_outputs/Output_impedance/SMITH_PITAYA_Gen1_VS_Gen2_markings.png
    :width: 800

原始板卡和 Gen 2 输出阻抗的 Smith 图。

|

输出相位噪声
------------------


.. figure:: img/RF_outputs/Phase_noise/noise_generation_Gen2.png
    :width: 800

1 Hz 至 1 MHz 之间的相位噪声测量。

|

输出 SFDR
------------------

+------------------+-----------------+-----------------+
|                  | **OUT 1**       | **OUT 2**       |
+==================+=================+=================+
| **f [MHz]**      | **SFDR [dB]**   | **SFDR [dB]**   |
+------------------+-----------------+-----------------+
| 0.1              | 56              | 54              |
+------------------+-----------------+-----------------+
| 1                | 52              | 58              |
+------------------+-----------------+-----------------+
| 10               | 58              | 55              |
+------------------+-----------------+-----------------+
| 20               | 44              | 44              |
+------------------+-----------------+-----------------+
| 30               | 45              | 45              |
+------------------+-----------------+-----------------+
| 40               | 44              | 45              |
+------------------+-----------------+-----------------+

.. figure:: img/RF_outputs/SFDR/SFDR_measurements.png
    :width: 800

两个输出通道的 SFDR 测量。

**特定频率下的测量**

.. figure:: img/RF_outputs/SFDR/SFDR_OUT1_100k.png
    :width: 800

100 kHz 时的 SFDR。

.. figure:: img/RF_outputs/SFDR/SFDR_OUT1_1M.png
    :width: 800

1 MHz 时的 SFDR。

.. figure:: img/RF_outputs/SFDR/SFDR_OUT1_10M.png
    :width: 800

10 MHz 时的 SFDR。

.. figure:: img/RF_outputs/SFDR/SFDR_OUT1_20M.png
    :width: 800

20 MHz 时的 SFDR。

.. figure:: img/RF_outputs/SFDR/SFDR_OUT1_30M.png
    :width: 800

30 MHz 时的 SFDR。

.. figure:: img/RF_outputs/SFDR/SFDR_OUT1_40M.png
    :width: 800

40 MHz 时的 SFDR。

|

输出 SNR
-------------------

.. figure:: img/RF_outputs/SNR/SNR_OUT1.png
    :width: 800

输出通道 1 的 SNR 测量（整个频谱）。

.. figure:: img/RF_outputs/SNR/SNR_OUT1_MEAS.png
    :width: 800

输出通道 1 的 SNR 测量（VBW 100 kHz）。

.. figure:: img/RF_outputs/SNR/SNR_OUT1_NO_SIGNAL.png
    :width: 800

输出通道 1 的 SNR 测量（无信号）。

|

.. Output THD
.. ------------------

.. Output ENOB
.. ------------------

.. Output noise floor
.. ------------------

.. Output IMD
.. ------------------

|

校准
==============

模拟输出校准
--------------------------

有关模拟输出校准，请参阅 :ref:`校准指南 <calibration_app>`。


.. _commands_gen:

#################
信号发生器
#################

.. contents:: Generation command index
   :local:
   :depth: 2
   :backlinks: top

|

功能概览
========================

信号发生器命令控制 Red Pitaya 的快速模拟输出（DAC）以生成波形。这些命令支持连续信号、突发模式、频率扫描和任意
波形发生（AWG），并具备精确的触发与同步能力。

主要发生模式：

* **连续** - 持续生成信号，直到停止
* **突发** - 按受控重复次数生成指定数量的信号周期
* **扫描** - 在指定时间内于两个频率之间进行线性频率扫描
* **任意** - 生成由用户数据定义的自定义波形（16384 个采样）


重要说明
========================

* 对于 STEMlab 125-14 4-Input，本章命令不适用。
* 发生触发独立于采集触发。
* 必须启用输出 (``OUTPUT:STATE ON``) 才能触发发生。
* AWG 每个波形周期必须恰好包含 16384 个采样。
* 频率范围：1 Hz 至 50 MHz（取决于板卡）。
* 有关详细编程指导，请参阅简介中的 :ref:`SCPI 发生部分 <intro_gen_acq>`。


代码示例
========================

以下是如何在 Red Pitaya 上使用信号发生命令的示例：

* :ref:`信号发生示例 <examples_genRF>`。
* :ref:`采集与发生示例 <examples_acq_genRF>`。

|

参数与命令表
==============================


发生器控制
--------------------

**参数选项：**

- ``<n> = {1,2}`` (设置 OUT1 或 OUT2 通道)
- ``<state> = {ON,OFF}`` 默认值： ``OFF``
- ``<enable> = {true, false}`` 默认值： ``false``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 53 89 94 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 生态系统
    * - ``GEN:RST``
      - C++: ``rp_GenReset()`` |br| Python: ``rp_GenReset()``
      - 停止发生并将所有发生器参数设置为默认值。
      - 1.04-18 及更高版本
    * - ``PHAS:ALIGN``
      - C++: ``rp_GenSynchronise()`` |br| Python: ``rp_GenSynchronise()``
      - 立即同步触发两个快速模拟输出的发生。 |br| 信号相位已对齐。 |br| （等同于 SOUR:TRig:INT）
      - 1.04-18 及更高版本
    * - ``OUTPUT<n>:STATE <state>`` |br| 示例： |br| ``OUTPUT1:STATE ON``
      - C++: ``rp_GenOutEnable(rp_channel_t channel)`` |br| ``rp_GenOutDisable(rp_channel_t channel)`` |br| Python: ``rp_GenOutEnable(<channel>)`` |br| ``rp_GenOutDisable(<channel>)``
      - 启用或禁用向指定快速模拟输出供电。启用后，信号不会开始发生，但初始电压值（``SOUR<n>:INITValue``、``rp_GenSetInitGenValue``）会出现在快速模拟输出端。
      - 1.04-18 及更高版本
    * - ``OUTPUT<n>:STATE?`` > ``<state>`` |br| 示例： |br| ``OUTPUT1:STATE?`` > ``ON``
      - C++: ``rp_GenOutIsEnabled(rp_channel_t channel, bool *value)`` |br| Python: ``rp_GenOutIsEnabled(<channel>)``
      - 获取指定快速模拟输出的启用/禁用供电电压状态。
      - 1.04-18 及更高版本
    * - ``OUTPUT:STATE <state>`` |br| 示例： |br| ``OUTPUT:STATE ON``
      - C++: ``rp_GenOutEnableSync(bool enable)`` |br| Python: ``rp_GenOutEnableSync(<enable>)``
      - 启用或禁用向两个快速模拟输出供电。启用后，信号不会开始发生，但初始电压值（``SOUR<n>:INITValue``、``rp_GenSetInitGenValue``）会出现在两个快速模拟输出端。
      - 1.04-18 及更高版本

|

发生器触发
-------------------

**参数选项：**

- ``<n> = {1,2}`` (设置 OUT1 或 OUT2 通道)
- ``<state> = {ON,OFF}`` 默认值： ``OFF``
- ``<utime> = {value in us}`` 默认值： ``500``
- ``<trigger> = {EXT_PE, EXT_NE, INT, GATED}`` 默认值： ``INT``

    - ``EXT`` = 外部
    - ``INT`` = 内部
    - ``GATED`` = 门控突发

- ``<enable> = {true, false}`` 默认值： ``false``

**可用的 Jupyter 和 API 宏：**

- 发生器触发源 - ``RP_GEN_TRIG_SRC_INTERNAL, RP_GEN_TRIG_SRC_EXT_PE, RP_GEN_TRIG_SRC_EXT_NE``



.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 53 89 94 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 适用版本
    * - ``SOUR<n>:TRig:SOUR <trigger>`` |br| 示例： |br| ``SOUR1:TRig:SOUR EXT_PE``
      - C++: ``rp_GenTriggerSource(rp_channel_t channel, rp_trig_src_t src)`` |br| Python: ``rp_GenTriggerSource(<channel>, <src>)``
      - 设置所选信号的触发源（内部或外部）。 |br| 外部触发必须是 3V3 CMOS 信号。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:TRig:SOUR?`` > ``<trigger>`` |br| 示例： |br| ``SOUR1:TRig:SOUR?`` > ``EXT_PE``
      - C++: ``rp_GenGetTriggerSource(rp_channel_t channel, rp_trig_src_t *src)`` |br| Python: ``rp_GenGetTriggerSource(<channel>)``
      - 获取触发源设置。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GenResetTrigger(rp_channel_t channel)`` |br| Python: ``rp_GenResetTrigger(<channel>)``
      - 重置指定快速模拟输出的发生器设置。
      - 1.04-18 及更高版本
    * - ``SOUR:TRig:INT`` |br| 示例： |br| ``SOUR:TRig:INT``
      - C++: ``rp_GenSynchronise()`` |br| Python: ``rp_GenSynchronise()``
      - 立即同步触发两个快速模拟输出的发生。 |br| 信号相位已对齐。 |br| 该命令会重置 FPGA，信号从头开始生成。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:TRig:INT`` |br| 示例： |br| ``SOUR1:TRig:INT``
      - C++: ``rp_GenResetTrigger(rp_channel_t channel)`` |br| Python: ``rp_GenResetTrigger(<channel>)``
      - 立即触发指定快速模拟输出的发生。 |br| 该命令会重置 FPGA，信号从头开始生成。
      - 1.04-18 及更高版本
    * - ``SOUR:TRig:INT:ONLY`` |br| 示例： |br| ``SOUR:TRig:INT:ONLY``
      - C++: ``rp_GenTriggerOnlyBoth()`` |br| Python: ``rp_GenTriggerOnlyBoth()``
      - 立即同步触发两个快速模拟输出的发生。
      - 2.07-43 及更高版本
    * - ``SOUR<n>:TRig:INT:ONLY`` |br| 示例： |br| ``SOUR1:TRig:INT:ONLY``
      - C++: ``rp_GenTriggerOnly(rp_channel_t channel)`` |br| Python: ``rp_GenTriggerOnly(<channel>)``
      - 立即触发指定快速模拟输出的发生。
      - 2.07-43 及更高版本
    * - ``SOUR:TRig:EXT:DEBouncer[:US] <utime>`` |br| Example: |br| ``SOUR:TRig:EXT:DEBouncer:US 1``
      - C++: ``rp_GenSetExtTriggerDebouncerUs(double utime)`` |br| Python: ``rp_GenSetExtTriggerDebouncerUs(<utime>)``
      - 设置外部发生触发去抖时间，单位为微秒 (值必须为正).
      - 2.00-15 及更高版本
    * - ``SOUR:TRig:EXT:DEBouncer[:US]?`` > ``<utime>`` |br| Example: |br| ``SOUR:TRig:EXT:DEBouncer:US?`` > ``1``
      - C++: ``rp_GenGetExtTriggerDebouncerUs(double *utime)`` |br| Python: ``rp_GenSetExtTriggerDebouncerUs(<utime>)``
      - 获取外部发生触发去抖时间设置，单位为微秒。
      - 2.00-15 及更高版本
    * - ``TRig:EXT:LEV <voltage>`` |br| Example: |br| ``TRig:EXT:LEV 1``
      - C++: ``rp_SetExternalTriggerLevel(float voltage)`` |br| Python: ``rp_SetExternalTriggerLevel(<voltage>)``
      - 设置外部触发电平，单位为 V。 |br| （仅限 SIGNALlab 250-12）
      - 2.04-35 及更高版本
    * - ``TRig:EXT:LEV?`` > ``<voltage>`` |br| Example: |br| ``TRig:EXT:LEV?`` > ``1``
      - C++: ``rp_GetExternalTriggerLevel(float* voltage)`` |br| Python: ``rp_GetExternalTriggerLevel()``
      - 获取外部触发电平，单位为 V。 |br| （仅限 SIGNALlab 250-12）
      - 2.04-35 及更高版本

|

发生器设置
--------------------

**参数选项：**

- ``<n> = {1,2}`` (设置 OUT1 或 OUT2 通道)
- ``<frequency> = {0 ... 62.5e6}`` （单位：Hz）。默认值： ``1000``
- ``<type> = {SINE, SQUARE, TRIANGLE, SAWU, SAWD, PWM, ARBITRARY, DC, DC_NEG}`` 默认值： ``SINE``
- ``<amplitude> = {-1 ... 1}``（单位为 Volts）。默认值：``1``；SIGNALlab 250-12 为 ``{-5 ... 5}``。
- ``<level> = {-1 ... 1}``（单位为 Volts）。默认值：``0``；SIGNALlab 250-12 为 ``{-5 ... 5}``。
- ``<offset> = {-1 ... 1}``（单位为 Volts）。默认值：``0``。
- ``<phase> = {-360 ... 360}``（单位为 Degrees）。默认值：``0``。
- ``<ratio> = {0 ... 1}`` 默认值：``0.5``；1 对应 100%。
- ``<time> = {0 ... 10000}`` 默认值：``1``；最小值和最大值取决于信号频率。
- ``<array> = {value1, ...}`` 最大 16384 个值，浮点数范围为 -1 至 1。
- ``<waveform> = {value1, ...}`` 最大 16384 个值，浮点数范围为 -1 至 1（Python API 和 Jupyter 使用 ``arbBuffer`` 或 ``NumPy array``）。
- ``<lenght>`` 波形数组长度
- ``<load_mode> = {INF, L50}`` 默认值： ``INF``

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``
- 波形 - ``RP_WAVEFORM_SINE, RP_WAVEFORM_SQUARE, RP_WAVEFORM_TRIANGLE, RP_WAVEFORM_RAMP_UP, RP_WAVEFORM_RAMP_DOWN, RP_WAVEFORM_DC, RP_WAVEFORM_PWM,``
  ``RP_WAVEFORM_ARBITRARY, RP_WAVEFORM_DC_NEG, RP_WAVEFORM_SWEEP``
- 上升和下降时间 - ``RISE_FALL_MIN_RATIO, RISE_FALL_MAX_RATIO``
- 负载模式 - ``RP_GEN_HI_Z, RP_GEN_50Ohm``

**波形模板与幅度**

所有波形（内置和任意）均定义为归一化值范围为 ``-1`` 至 ``1`` 的**模板**。这些模板值表示：

- 值 ``1`` → DAC 最大输出值
- 值 ``-1`` → DAC 最小输出值
- 值 ``0`` → 中心/零点

实际输出电压由通过 ``SOUR<n>:VOLT`` 命令设置的**幅度乘数**决定。FPGA 使用以下公式：

    **Output = (Waveform Template Value × Calibrated Amplitude Multiplier) + Calibration Offset**

要点：

- 波形模板只定义信号的**形状**，不包含幅度信息。
- 幅度通过 ``SOUR<n>:VOLT`` 独立控制（以 Volts 设置幅度）。
- FPGA 本身不知道 DAC 的满量程电压；它使用校准乘数将模板值转换为正确的输出电压。
- 对于自定义/任意波形（``SOUR<n>:TRAC:DATA:DATA``），发送到 Red Pitaya 前请确保所有值均归一化到 ``[-1, 1]`` 范围。

*仅限 SIGNALlab 250-12：*

- 发生器增益 - ``RP_GAIN_1X, RP_GAIN_5X``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 53 90 94 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 适用版本
    * - ``SOUR<n>:FUNC <type>`` |br| 示例： |br| ``SOUR2:FUNC TRIANGLE``
      - C++: ``rp_GenWaveform(rp_channel_t channel, rp_waveform_t type)`` |br| Python: ``rp_GenWaveform(<channel>, <type>)``
      - 设置快速模拟输出的波形。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:FUNC?`` > ``<type>`` |br| 示例： |br| ``SOUR2:FUNC?`` > ``TRIANGLE``
      - C++: ``rp_GenGetWaveform(rp_channel_t channel, rp_waveform_t *type)`` |br| Python: ``rp_GenGetWaveform(<channel>)``
      - 获取快速模拟输出的波形。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:FREQ:FIX <frequency>`` |br| 示例： |br| ``SOUR2:FREQ:FIX 100000``
      - C++: ``rp_GenFreq(rp_channel_t channel, float frequency)`` |br| Python: ``rp_GenFreq(<channel>, <frequency>)``
      - 设置快速模拟输出的信号频率。对于 ARBITRARY 波形，此频率对应一个信号周期（即包含 16384 个采样的缓冲区）。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:FREQ:FIX:Direct <frequency>`` |br| 示例： |br| ``SOUR2:FREQ:FIX:Direct 100000``
      - C++: ``rp_GenFreqDirect(rp_channel_t channel, float frequency)`` |br| Python: ``rp_GenFreqDirect(<channel>, <frequency>)``
      - 在 FPGA 中设置通道信号频率，无需重置发生器并重建信号。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:FREQ:FIX?`` > ``<frequency>`` |br| 示例： |br| ``SOUR2:FREQ:FIX?`` > ``100000``
      - C++: ``rp_GenGetFreq(rp_channel_t channel, float *frequency)`` |br| Python: ``rp_GenGetFreq(<channel>)``
      - 获取指定通道的信号频率。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:VOLT <amplitude>`` |br| 示例： |br| ``SOUR2:VOLT 0.5``
      - C++: ``rp_GenAmp(rp_channel_t channel, float amplitude)`` |br| Python: ``rp_GenAmp(<channel>, <amplitude>)``
      - 设置快速模拟输出的单向幅度，单位为伏特。幅度与偏置之和必须小于最大输出电压范围（±1 V；SIGNALlab 在高阻负载下为 ±2 V/±10 V）。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:VOLT?`` > ``<amplitude>`` |br| 示例： |br| ``SOUR2:VOLT?`` > ``0.5``
      - C++: ``rp_GenGetAmp(rp_channel_t channel, float *amplitude)`` |br| Python: ``rp_GenGetAmp(<channel>)``
      - 获取快速模拟输出的单向幅度，单位为伏特。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:VOLT:OFFS <offset>`` |br| 示例： |br| ``SOUR1:VOLT:OFFS 0.2``
      - C++: ``rp_GenOffset(rp_channel_t channel, float offset)`` |br| Python: ``rp_GenOffset(<channel>, <offset>)``
      - 设置快速模拟输出的 DC 偏置电压，单位为伏特。幅度与偏置之和必须小于最大输出电压范围（±1 V；SIGNALlab 在高阻负载下为 ±2 V/±10 V）。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:VOLT:OFFS?`` > ``<offset>`` |br| 示例： |br| ``SOUR1:VOLT:OFFS?`` > ``0.2``
      - C++: ``rp_GenGetOffset(rp_channel_t channel, float *offset)`` |br| Python: ``rp_GenGetOffset(<channel>)``
      - 获取快速模拟输出的 DC 偏置，单位为伏特。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:PHAS <phase>`` |br| 示例： |br| ``SOUR2:PHAS 30``
      - C++: ``rp_GenPhase(rp_channel_t channel, float phase)`` |br| Python: ``rp_GenPhase(<channel>, <phase>)``
      - 设置快速模拟输出的相位（单位：度）。信号从指定相位开始生成；例如相位设为 90 度时，信号将从余弦相位而非正弦相位开始。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:PHAS?`` > ``<phase>`` |br| 示例： |br| ``SOUR2:PHAS?`` > ``30``
      - C++: ``rp_GenGetPhase(rp_channel_t channel, float *phase)`` |br| Python: ``rp_GenGetPhase(<channel>)``
      - 获取快速模拟输出的相位（单位：度）。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:DCYC <ratio>`` |br| 示例： |br| ``SOUR1:DCYC 0.2``
      - C++: ``rp_GenDutyCycle(rp_channel_t channel, float ratio)`` |br| Python: ``rp_GenDutyCycle(<channel>, <ratio>)``
      - 设置 PWM 波形的占空比。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:DCYC?`` > ``<ratio>`` |br| 示例： |br| ``SOUR1:DCYC`` > ``0.2``
      - C++: ``rp_GenGetDutyCycle(rp_channel_t channel, float *ratio)`` |br| Python: ``def rp_GenGetDutyCycle(<channel>)``
      - 获取 PWM 波形的占空比。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:TRAC:DATA:DATA <array>`` |br| 示例： |br| ``SOUR1:TRAC:DATA:DATA 1,0.5,0.2``
      - C++: ``rp_GenArbWaveform(rp_channel_t channel, float *waveform, uint32_t length)`` |br| Python: ``rp_GenArbWaveform(<channel>, <waveform>, <length>)`` |br| ``rp_GenArbWaveformNP(<channel>, <np_buffer>)``
      - 导入一个任意波形周期的数据（应恰好包含 16384 个采样）。如果提供的采样较少，输出频率将更高。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:TRAC:DATA:DATA?`` > ``<array>`` |br| 示例： |br| ``SOUR1:TRAC:DATA:DATA?`` >  ``1,0.5,0.2``
      - C++: ``rp_GenGetArbWaveform(rp_channel_t channel, float *waveform, uint32_t *length)`` |br| Python: ``rp_GenGetArbWaveform(<channel>, <waveform>)`` |br| ``rp_GenGetArbWaveformNP(<channel>, <np_buffer>)``
      - 获取用户定义的任意波形周期。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:LOAD <load_mode>`` |br| 示例： |br| ``SOUR2:LOAD L50``
      - C++: ``rp_GenSetLoadMode(rp_channel_t channel, rp_gen_load_mode_t mode)`` |br| Python: ``rp_GenSetLoadMode(<channel>, <mode>)``
      - 设置输出负载模式。从 INF 切换至 L50 时，设定幅度（``SOUR<n>:VOLT``）也会减半；从 L50 切换至 INF 时幅度会加倍。请先设置负载，再设置幅度。（仅限 SIGNALlab）
      - 2.04-35 及更高版本
    * - ``SOUR<n>:LOAD?`` > ``<load_mode>`` |br| 示例： |br| ``SOUR2:LOAD?`` > ``L50``
      - C++: ``rp_GenGetLoadMode(rp_channel_t channel, rp_gen_load_mode_t *mode)`` |br| Python: ``rp_GenGetLoadMode(<mode>)``
      - 获取输出负载模式。（仅限 SIGNALlab）
      - 2.04-35 及更高版本
    * - -
      - C++: ``rp_GenSetGainOut(rp_channel_t channel, rp_gen_gain_t gain_mode)`` |br| Python: ``rp_GenSetGainOut(<channel>, <gain_mode>)``
      - 设置 SIGNALlab 输出增益。（仅限 SIGNALlab）
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_GenGetGainOut(rp_channel_t channel, rp_gen_gain_t *gain_mode)`` |br| Python: ``rp_GenGetGainOut(<channel>)``
      - 获取 SIGNALlab 输出增益。（仅限 SIGNALlab）
      - 1.04-18 及更高版本
    * - ``SOUR<n>:RISE:TIME <time>`` |br| 示例： |br| ``SOUR1:RISE:TIME 0.1``
      - C++: ``rp_GenRiseTime(rp_channel_t channel, float time)`` |br| Python: ``rp_GenRiseTime(<channel>, <time>)``
      - 设置快速模拟输出的信号上升时间（单位：微秒）。可接受的取值范围取决于频率；配置前请先指定信号频率。
      - 2.00-18 及更高版本
    * - ``SOUR<n>:RISE:TIME?`` > ``<time>`` |br| 示例： |br| ``SOUR1:RISE:TIME?`` > ``0.1``
      - C++: ``rp_GenGetRiseTime(rp_channel_t channel, float *time)`` |br| Python: ``rp_GenGetRiseTime(<channel>)``
      - 获取快速模拟输出的信号上升时间（单位：微秒）。
      - 2.00-18 及更高版本
    * - ``SOUR<n>:FALL:TIME <time>`` |br| 示例： |br| ``SOUR1:FALL:TIME 0.1``
      - C++: ``rp_GenFallTime(rp_channel_t channel, float time)`` |br| Python: ``rp_GenFallTime(<channel>, <time>)``
      - 设置快速模拟输出的信号下降时间（单位：微秒）。可接受的取值范围取决于频率；配置前请先指定信号频率。
      - 2.00-18 及更高版本
    * - ``SOUR<n>:FALL:TIME?`` > ``<time>`` |br| 示例： |br| ``SOUR1:FALL:TIME?`` > ``0.1``
      - C++: ``rp_GenGetFallTime(rp_channel_t channel, float *time)`` |br| Python: ``rp_GenGetFallTime(<channel>)``
      - 获取快速模拟输出的信号下降时间（单位：微秒）。
      - 2.00-18 及更高版本

|

突发模式
------------

**参数选项：**

- ``<n> = {1,2}`` (设置 OUT1 或 OUT2 通道)
- ``<mode> = {BURST, CONTINUOUS}`` 默认值： ``CONTINUOUS``
- ``<num>, <repetitions> = {1...65536}`` 默认值： ``1``
- ``<period> = {1 µs - 500 s}``，值以 *µs* 为单位。
- ``<period2> = {0.001 µs - 4 s}``，值以 *µs* 为单位。
- ``<state> = {ON,OFF}`` 默认值： ``OFF``

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``
- 发生器模式 - ``RP_GEN_MODE_CONTINUOUS, RP_GEN_MODE_BURST``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 53 89 94 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 适用版本
    * - ``SOUR<n>:BURS:STAT <mode>`` |br| 示例： |br| ``SOUR1:BURS:STAT BURST`` |br| ``SOUR1:BURS:STAT CONTINUOUS``
      - C++: ``rp_GenMode(rp_channel_t channel, rp_gen_mode_t mode)`` |br| Python: ``rp_GenMode(<channel>, <mode>)``
      - 启用或禁用突发（脉冲）模式。Red Pitaya 将生成 **R** 次突发，每次包含 **N** 个信号周期；**P** 表示相邻两次突发起点之间的时间。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:BURS:STAT?`` > ``<mode>`` |br| 示例： |br| ``SOUR1:BURS:STAT?`` > ``BURST``
      - C++: ``rp_GenGetMode(rp_channel_t channel, rp_gen_mode_t *mode)`` |br| Python: ``rp_GenGetMode(<channel>)``
      - 获取发生模式。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:BURS:NCYC <num>`` |br| 示例： |br| ``SOUR1:BURS:NCYC 3``
      - C++: ``rp_GenBurstCount(rp_channel_t channel, int num)`` |br| Python: ``rp_GenBurstCount(<channel>, <num>)``
      - 设置一次突发中的周期数（**N**）。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:BURS:NCYC?`` > ``<num>`` |br| 示例： |br| ``SOUR1:BURS:NCYC`` > ``3``
      - C++: ``rp_GenGetBurstCount(rp_channel_t channel, int *num)`` |br| Python: ``rp_GenGetBurstCount(<channel>)``
      - 获取一次突发中生成的波形数量。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:BURS:NOR <repetitions>`` |br| 示例： |br| ``SOUR1:BURS:NOR 5``
      - C++: ``rp_GenBurstRepetitions(rp_channel_t channel, int repetitions)`` |br| Python: ``rp_GenBurstRepetitions(<channel>, <repetitions>)``
      - 设置突发重复次数（**R**）；65536 表示无限重复。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:BURS:NOR?`` > ``<repetitions>`` |br| 示例： |br| ``SOUR1:BURS:NOR`` > ``5``
      - C++: ``rp_GenGetBurstRepetitions(rp_channel_t channel, int *repetitions)`` |br| Python: ``rp_GenGetBurstRepetitions(<channel>)``
      - 获取突发重复次数。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:BURS:INT:PER <period>`` |br| 示例： |br| ``SOUR1:BURS:INT:PER 1000000``
      - C++: ``rp_GenBurstPeriod(rp_channel_t channel, uint32_t period)`` |br| Python: ``rp_GenBurstPeriod(<channel>, <period>)``
      - 设置相邻两次突发起点之间的时间（单位：微秒，**P**）。两次突发之间至少间隔 1 µs；若设定周期短于突发持续时间，软件会采用 1 µs 的默认间隔。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:BURS:INT:PER?`` > ``<period>`` |br| 示例： |br| ``SOUR1:BURS:INT:PER?`` > ``1000000``
      - C++: ``rp_GenGetBurstPeriod(rp_channel_t channel, uint32_t *period)`` |br| Python: ``rp_GenGetBurstPeriod(<channel>)``
      - 获取突发周期，单位为微秒。
      - 1.04-18 及更高版本
    * - ``SOUR<n>:BURS:INT:PER <period2>`` |br| 示例： |br| ``SOUR1:BURS:INT:PER 1000000``
      - C++: ``rp_GenBurstPeriod(rp_channel_t channel, float period)`` |br| Python: ``rp_GenBurstPeriod(<channel>, <period>)``
      - 设置相邻两次突发起点之间的时间（单位：微秒，**P**）；小数部分以纳秒表示。
      - 3.00-57 及更高版本
    * - ``SOUR<n>:BURS:INT:PER?`` > ``<period2>`` |br| 示例： |br| ``SOUR1:BURS:INT:PER?`` > ``1000000``
      - C++: ``rp_GenGetBurstPeriod(rp_channel_t channel, float *period)`` |br| Python: ``rp_GenGetBurstPeriod(<channel>)``
      - 获取突发周期，单位为微秒。
      - 3.00-57 及更高版本
    * - ``SOUR<n>:BURS:INITValue <amplitude>`` |br| 示例： |br| ``SOUR1:BURS:INITValue 0.5``
      - C++: ``rp_GenSetInitGenValue(rp_channel_t channel, float amplitude)`` |br| Python: ``rp_GenSetInitGenValue(<channel>, <amplitude>)``
      - 设置输出启用后、信号开始生成前出现在快速模拟输出端的初始电压值（参见 ``OUTPUT<n>:STATE``、``rp_GenOutEnable(rp_channel_t channel)``）。
      - 2.05-37 及更高版本
    * - ``SOUR<n>:BURS:INITValue?`` > ``<amplitude>`` |br| 示例： |br| ``SOUR1:BURS:INITValue?`` > ``0.5``
      - C++: ``rp_GenGetInitGenValue(rp_channel_t channel, float *amplitude)`` |br| Python: ``rp_GenGetInitGenValue(<channel>)``
      - 获取输出启用后、信号开始生成前出现在快速模拟输出端的初始电压值（参见 ``OUTPUT<n>:STATE``、``rp_GenOutEnable(rp_channel_t channel)``）。
      - 2.05-37 及更高版本
    * - ``SOUR<n>:BURS:LASTValue <amplitude>`` |br| 示例： |br| ``SOUR1:BURS:LASTValue 0.5``
      - C++: ``rp_GenBurstLastValue(rp_channel_t channel, float amplitude)`` |br| Python: ``rp_GenBurstLastValue(<channel>, <amplitude>)``
      - 设置突发信号生成结束后的输出值；在生成新信号前，输出将保持该值。
      - 2.00-18 及更高版本
    * - ``SOUR<n>:BURS:LASTValue?`` > ``<amplitude>`` |br| 示例： |br| ``SOUR1:BURS:LASTValue`` > ``0.5``
      - C++: ``rp_GenGetBurstLastValue(rp_channel_t channel, float *amplitude)`` |br| Python: ``rp_GenGetBurstLastValue(<channel>)``
      - 获取生成的突发信号结束值。
      - 2.00-18 及更高版本
    * - ``SOUR<n>:BURS:USE:LASTSample <state>`` |br| 示例： |br| ``SOUR1:BURS:USE:LASTSample ON``
      - C++: ``rp_GenSetUseLastSample(rp_channel_t channel, bool enable)`` |br| Python: ``rp_GenSetUseLastSample(<channel>, <state>)``
      - 启用使用缓冲区最后一个采样而非“结束值”的模式；在生成新信号前，输出将保持该值。
      - 3.00-57 及更高版本
    * - ``SOUR<n>:BURS:USE:LASTSample?`` > ``<state>`` |br| 示例： |br| ``SOUR1:BURS:USE:LASTSample`` > ``ON``
      - C++: ``rp_GenGetUseLastSample(rp_channel_t channel, bool *enable)`` |br| Python: ``rp_GenGetUseLastSample(<channel>)``
      - 返回“Use Last Sample”模式的当前设置。
      - 3.00-57 及更高版本
    * - ``SOUR<n>:INITValue <amplitude>`` |br| 示例： |br| ``SOUR1:INITValue 0.5``
      - C++: ``rp_GenSetInitGenValue(rp_channel_t channel, float amplitude)`` |br| Python: ``rp_GenSetInitGenValue(<channel>, <amplitude>)``
      - 设置输出启用后、信号开始生成前出现在快速模拟输出端的初始电压值（参见 ``OUTPUT<n>:STATE``、``rp_GenOutEnable(rp_channel_t channel)``）。
      - 2.00-18 及更高版本
    * - ``SOUR<n>:INITValue?`` > ``<amplitude>`` |br| 示例： |br| ``SOUR1:INITValue?`` > ``0.5``
      - C++: ``rp_GenGetInitGenValue(rp_channel_t channel, float *amplitude)`` |br| Python: ``rp_GenGetInitGenValue(<channel>)``
      - 获取输出启用后、信号开始生成前出现在快速模拟输出端的初始电压值（参见 ``OUTPUT<n>:STATE``、``rp_GenOutEnable(rp_channel_t channel)``）。
      - 2.00-18 及更高版本

|

.. _commands_sweep:

扫描 模式
------------

将波形类型设置为 SWEEP 以启用扫描模式。

**参数选项：**

- ``<n> = {1,2}`` (设置 OUT1 或 OUT2 通道)
- ``<frequency> = {0 ... 62.5e6}`` （单位：Hz）。默认值： ``1000`` （起始）， ``10000`` （结束）

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``
- 扫描 方向 - ``RP_GEN_SWEEP_DIR_NORMAL, RP_GEN_SWEEP_DIR_UP_DOWN``
- 扫描 模式 - ``RP_GEN_SWEEP_MODE_LINEAR, RP_GEN_SWEEP_MODE_LOG``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 53 89 94 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 适用版本
    * - -
      - C++: ``rp_GenSweepStartFreq(rp_channel_t channel, float frequency)`` |br| Python: ``rp_GenSweepStartFreq(<channel>, <frequency>)``
      - 设置扫描起始频率。
      - 2.00-18 及更高版本
    * - -
      - C++: ``rp_GenGetSweepStartFreq(rp_channel_t channel, float *frequency)`` |br| Python: ``rp_GenGetSweepStartFreq(<channel>)``
      - 获取扫描起始频率。
      - 2.00-18 及更高版本
    * - -
      - C++: ``rp_GenSweepEndFreq(rp_channel_t channel, float frequency)`` |br| Python: ``rp_GenSweepEndFreq(<channel>, <frequency>)``
      - 设置扫描结束频率。
      - 2.00-18 及更高版本
    * - -
      - C++: ``rp_GenGetSweepEndFreq(rp_channel_t channel, float *frequency)`` |br| Python: ``rp_GenGetSweepEndFreq(<channel>)``
      - 获取扫描结束频率。
      - 2.00-18 及更高版本
    * - -
      - C++: ``rp_GenSweepMode(rp_channel_t channel, rp_gen_sweep_mode_t mode)`` |br| Python: ``rp_GenSweepMode(<channel>, <mode>)``
      - 将扫描模式设置为线性或对数。
      - 2.00-18 及更高版本
    * - -
      - C++: ``rp_GenGetSweepMode(rp_channel_t channel, rp_gen_sweep_mode_t *mode)`` |br| Python: ``rp_GenGetSweepMode(<channel>)``
      - 获取扫描模式（线性或对数）。
      - 2.00-18 及更高版本
    * - -
      - C++: ``rp_GenSweepDir(rp_channel_t channel, rp_gen_sweep_dir_t mode)`` |br| Python: ``rp_GenSweepDir(<channel>, <mode>)``
      - 设置扫描方向（正常（向上）或上下）。
      - 2.00-18 及更高版本
    * - -
      - C++: ``rp_GenGetSweepDir(rp_channel_t channel, rp_gen_sweep_dir_t *mode)`` |br| Python: ``rp_GenGetSweepDir(<channel>)``
      - 获取扫描方向（正常（向上）或上下）。
      - 2.00-18 及更高版本

|

.. _commands_sweep_ext:

扫描模式（扩展）
--------------------


**参数选项：**

- ``<n> = {1,2}`` (设置 OUT1 或 OUT2 通道)
- ``<frequency> = {0 ... 62.5e6}`` （单位：Hz）。默认值： ``1000`` （起始）、``10000`` （结束）
- ``<time> = {1 ... }`` （单位：μS）. 默认值： ``1``
- ``<mode> = {LINEAR, LOG}``。默认值： ``LINEAR``
- ``<dir> = {NORMAL, UP_DOWN}`` （单位：μS）. 默认值： ``NORMAL``
- ``<state> = {ON, OFF}``
- ``<count> = {0 ... }`` 。默认值： ``1`` （起始）

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``
- 扫描方向 - ``RP_GEN_SWEEP_DIR_NORMAL, RP_GEN_SWEEP_DIR_UP_DOWN``
- 扫描模式 - ``RP_GEN_SWEEP_MODE_LINEAR, RP_GEN_SWEEP_MODE_LOG``
- 状态 - ``True,False``


.. note::

    此 API 使用类来控制扫描模式。该类位于 rp-sweep 库中。

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 53 89 94 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - 生态系统
    * - -
      - C++: ``run()`` |br| Python: ``run()``
      - 启动频率生成器。
      - 2.04-35 及更高版本
    * - -
      - C++: ``stop()`` |br| Python: ``stop()``
      - 停止生成频率的线程。
      - 2.04-35 及更高版本
    * - ``SOUR:SWeep:DEFault`` |br| 示例： |br| ``SOUR:SWeep:DEFault``
      - C++: ``setDefault()`` |br| Python: ``setDefault()``
      - 停止所有通道的扫描生成并设置默认值。
      - 2.05-37 及更高版本
    * - ``SOUR:SWeep:RESET`` |br| 示例： |br| ``SOUR:SWeep:RESET``
      - C++: ``resetAll()`` |br| Python: ``resetAll()``
      - 一次性重置所有通道。
      - 2.04-35 及更高版本
    * - ``SOUR:SWeep:PAUSE <state>`` |br| 示例： |br| ``SOUR:SWeep:PAUSE ON``
      - C++: ``pause(bool state)`` |br| Python: ``pause(<state>)``
      - 停止频率变化，但不重置状态。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:STATE <state>`` |br| 示例： |br| ``SOUR1:SWeep:STATE ON``
      - C++: ``genSweep(rp_channel_t channel, bool enable)`` |br| Python: ``genSweep(<channel>, <state>)``
      - 启用或禁用指定通道的信号生成。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:STATE?`` > ``<state>`` |br| 示例： |br| ``SOUR1:SWeep:STATE?`` > ``ON``
      - C++: ``isGen(rp_channel_t channel, bool *state)`` |br| Python: ``isGen(<channel>)``
      - 返回通道状态。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:FREQ:START <frequency>`` |br| 示例： |br| ``SOUR1:SWeep:FREQ:START 1000``
      - C++: ``setStartFreq(rp_channel_t channel, float frequency)`` |br| Python: ``setStartFreq(<channel>, <frequency>)``
      - 设置扫描起始频率。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:FREQ:START?`` > ``<frequency>`` |br| 示例： |br| ``SOUR1:SWeep:FREQ:START?`` > ``1000``
      - C++: ``getStartFreq(rp_channel_t channel, float *frequency)`` |br| Python: ``getStartFreq(<channel>)``
      - 获取扫描起始频率。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:FREQ:STOP <frequency>`` |br| 示例： |br| ``SOUR1:SWeep:FREQ:STOP 10000``
      - C++: ``setStopFreq(rp_channel_t channel, float frequency)`` |br| Python: ``setStopFreq(<channel>, <frequency>)``
      - 设置扫描结束频率。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:FREQ:STOP?`` > ``<frequency>`` |br| 示例： |br| ``SOUR1:SWeep:FREQ:STOP?`` > ``10000``
      - C++: ``getStopFreq(rp_channel_t channel, float *frequency)`` |br| Python: ``getStopFreq(<channel>)``
      - 获取扫描结束频率。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:TIME <time>`` |br| 示例： |br| ``SOUR1:SWeep:TIME 10000``
      - C++: ``setTime(rp_channel_t channel, int us)`` |br| Python: ``setTime(<channel>, <frequency>)``
      - 设置生成时间，即从起始频率过渡到最终频率所需的时间，单位为微秒。 |br|
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:TIME?`` > ``<time>`` |br| 示例： |br| ``SOUR1:SWeep:TIME?`` > ``10000``
      - C++: ``getTime(rp_channel_t channel, int *us)`` |br| Python: ``getTime(<channel>)``
      - 返回生成时间（单位：微秒）。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:MODE <mode>`` |br| 示例： |br| ``SOUR1:SWeep:MODE LINEAR``
      - C++: ``setMode(rp_channel_t channel, rp_gen_sweep_mode_t mode)`` |br| Python: ``setMode(<channel>, <mode>)``
      - 将扫描模式设置为线性或对数模式。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:MODE?`` > ``<mode>`` |br| 示例： |br| ``SOUR1:SWeep:MODE?`` > ``LINEAR``
      - C++: ``getMode(rp_channel_t channel, rp_gen_sweep_mode_t *mode)`` |br| Python: ``getMode(<channel>)``
      - 获取扫描模式（线性或对数模式）。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:REP:INF <state>`` |br| 示例： |br| ``SOUR1:SWeep:REP:INF ON``
      - C++: ``setNumberOfRepetitions(rp_channel_t _ch, bool _isInfinty, uint64_t _count)`` |br| Python: ``setNumberOfRepetitions(<channel>, <state>, <count>)``
      - 设置无限信号生成模式。
      - 2.07-43 及更高版本
    * - ``SOUR<n>:SWeep:REP:INF?`` > ``<state>`` |br| 示例： |br| ``SOUR1:SWeep:REP:INF?`` > ``ON``
      - C++: ``getNumberOfRepetitions(rp_channel_t _ch, bool* _isInfinty, uint64_t* _count)`` |br| Python: ``getNumberOfRepetitions(<channel>, <state>, <count>)``
      - 获取无限信号生成模式。
      - 2.07-43 及更高版本
    * - ``SOUR<n>:SWeep:REP:COUNT <count>`` |br| 示例： |br| ``SOUR1:SWeep:REP:COUNT 10``
      - C++: ``setNumberOfRepetitions(rp_channel_t _ch, bool _isInfinty, uint64_t _count)`` |br| Python: ``setNumberOfRepetitions(<channel>, <state>, <count>)``
      - 设置生成信号时的重复次数。
      - 2.07-43 及更高版本
    * - ``SOUR<n>:SWeep:REP:COUNT?`` > ``<count>`` |br| 示例： |br| ``SOUR1:SWeep:REP:COUNT?`` > ``10``
      - C++: ``getNumberOfRepetitions(rp_channel_t _ch, bool* _isInfinty, uint64_t* _count)`` |br| Python: ``getNumberOfRepetitions(<channel>, <state>, <count>)``
      - 获取生成信号时的重复次数。
      - 2.07-43 及更高版本
    * - ``SOUR<n>:SWeep:DIR <dir>`` |br| 示例： |br| ``SOUR1:SWeep:DIR UP_DOWN``
      - C++: ``setDir(rp_channel_t channel, rp_gen_sweep_dir_t dir)`` |br| Python: ``setDir(<channel>, <dir>)``
      - 设置扫描方向（正常（向上）或上下）。
      - 2.04-35 及更高版本
    * - ``SOUR<n>:SWeep:DIR?`` > ``<dir>`` |br| 示例： |br| ``SOUR1:SWeep:DIR?`` > ``UP_DOWN``
      - C++: ``getDir(rp_channel_t channel, rp_gen_sweep_dir_t *dir)`` |br| Python: ``getDir(<channel>)``
      - 获取扫描方向（正常（向上）或上下）。
      - 2.04-35 及更高版本

|

* :ref:`返回顶部 <commands_gen>`
* :ref:`返回命令列表 <command_list>`

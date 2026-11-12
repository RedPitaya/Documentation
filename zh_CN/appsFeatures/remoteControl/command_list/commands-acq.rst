
.. _commands_acq:

##############
采集
##############

.. contents:: 采集命令索引
   :local:
   :depth: 2
   :backlinks: top

|

功能概述
=======================

采集命令控制 Red Pitaya 的快速模拟输入（ADC）以进行高速信号捕获。这些命令提供精确触发、抽取控制和缓冲区管理，用于捕获 DC 至 50 MHz 的信号。

采集关键概念：

* **循环内存缓冲区** - ADC 数据持续写入的硬件缓冲区（16384 个采样点）
* **数据缓冲区** - 用户可访问的缓冲区，触发点位于第 8192 个采样点（中间位置）
* **触发延迟** - 调整触发前数据与触发后数据的数量
* **抽取** - 降低有效采样率，以获取更长的时间窗口

正确采集数据的关键在于理解循环内存缓冲区与数据缓冲区之间的区别。


重要说明
=================

* 始终指定触发条件，以避免数据损坏。
* 标准缓冲区大小：16384 个采样点（如需更长的采集，请使用深度内存采集）。
* 数据缓冲区中的触发位置固定为第 8192 个采样点。
* 每次采集之间都必须重新启动采集（``ACQ:START``。
* 有关编程的详细指导，请参阅简介中的 :ref:`SCPI 采集章节 <intro_gen_acq>`。


代码示例
===============

以下是如何在 Red Pitaya 上使用采集命令的示例：

* :ref:`采集示例 <examples_acqRF>`.
* :ref:`采集与生成示例 <examples_acq_genRF>`.



采集控制
========================

**参数选项：**

- ``<enable> = {true, false}``
- ``<n> = {1,2}`` （设置通道 IN1 或 IN2）
- ``<state> = {ON, OFF}`` 默认值：``OFF``

*仅限 STEMlab 125-14 4-Input（附加）：*

- ``<n> = {3,4}`` （设置通道 IN3 或 IN4）

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 37 78 76 20
    :header-rows: 1

    * - SCPI
      - API、Jupyter
      - 描述
      - 生态系统
    * - ``ACQ:START``
      - C++: ``rp_AcqStart()`` |br| Python: ``rp_AcqStart()``
      - 启动采集。
      - 1.04-18 及更高版本
    * - ``ACQ:START:CH<n>``
      - C++: ``rp_AcqStartCh(rp_channel_t channel)`` |br| Python: ``rp_AcqStartCh(<channel>)``
      - 启动采集。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:STOP``
      - C++: ``rp_AcqStop()`` |br| Python: ``rp_AcqStop()``
      - 停止采集。
      - 1.04-18 及更高版本
    * - ``ACQ:STOP:CH<n>``
      - C++: ``rp_AcqStopCh(rp_channel_t channel)`` |br| Python: ``rp_AcqStopCh(<channel>)``
      - 停止采集。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:RST``
      - C++: ``rp_AcqReset()`` |br| Python: ``rp_AcqReset()``
      - 停止采集并将所有采集参数重置为 |br| 默认值。
      - 1.04-18 及更高版本
    * - ``ACQ:RST:CH<n>``
      - C++: ``rp_AcqResetCh(rp_channel_t channel)`` |br| Python: ``rp_AcqResetCh(<channel>)``
      - 停止采集并将所有采集参数重置为 |br| 默认值。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:UNLOCK``
      - C++: ``rp_AcqUnlockTrigger()`` |br| Python: ``rp_AcqUnlockTrigger()``
      - 检测到触发后解锁触发捕获。
      - 开发中
    * - ``ACQ:UNLOCK:CH<n>``
      - C++: ``rp_AcqUnlockTriggerCh(rp_channel_t)`` |br| Python: ``rp_AcqUnlockTriggerCh(<channel>)``
      - 解锁指定通道的触发捕获。 |br| 仅用于分离触发模式
      - 开发中
    * - -
      - C++: ``rp_AcqGetUnlockTrigger(bool* state)`` |br| Python: ``rp_AcqGetUnlockTrigger()``
      - 获取触发器当前阻塞状态。
      - 开发中
    * - -
      - C++: ``int rp_AcqGetUnlockTriggerCh(rp_channel_t channel, bool* state);`` |br| Python: ``rp_AcqGetUnlockTriggerCh(<channel>)``
      - 获取触发器当前阻塞状态。 在分离模式下
      - 开发中
    * - ``ACQ:SPLIT:TRig <state>``
      - C++: ``rp_AcqSetSplitTrigger(bool enable)`` |br| Python: ``rp_AcqSetSplitTrigger(<enable>)``
      - 启用分离触发模式。 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:SPLIT:TRig?`` > ``<state>``
      - C++: ``rp_AcqGetSplitTrigger(bool* state)`` |br| Python: ``rp_AcqGetSplitTrigger()``
      - 返回分离触发模式状态 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - -
      - C++: ``rp_AcqSetSplitTriggerPass(bool enable)`` |br| Python: ``rp_AcqSetSplitTriggerPass(<enable>)``
      - 即使硬件不支持分离触发，也可调用 Ch 函数 |br| ，方法是转发到通用函数。
      - 开发中
    * - -
      - C++: ``rp_AcqGetSplitTriggerPass(bool* state)`` |br| Python: ``rp_AcqGetSplitTriggerPass()``
      - 返回通道专用命令的函数转发状态。
      - 开发中
    * - ``ACQ:M16BIT <state>``
      - C++: ``rp_AcqSet16BitMode(bool enable)`` |br| Python: ``rp_AcqSet16BitMode(<enable>)``
      - 启用 FPGA 以 16-bit 格式返回数据的模式。
      - 开发中
    * - ``ACQ:M16BIT?`` > ``<state>``
      - C++: ``rp_AcqGet16BitMode(bool* state)`` |br| Python: ``rp_AcqGet16BitMode()``
      - 返回 16-bit 模式状态
      - 开发中
    * - -
      - C++: ``rp_AcqResetFpga()`` |br| Python: ``rp_AcqResetFpga()``
      - 重置采集写入状态机。
      - 1.04-18 及更高版本
    * - ``ACQ:KEEP:ARM <state>`` |br| 示例： |br| ``ACQ:KEEP:ARM ON``
      - C++: ``rp_AcqSetArmKeep(bool enable)`` |br| Python: ``rp_AcqSetArmKeep(<enable>)``
      - 即使触发发生后也持续采集。 |br| 启用后，触发后缓冲区仍会继续填充 |br| （ARM keep 模式）。
      - 开发中
    * - ``ACQ:KEEP:ARM?`` > ``<state>`` |br| 示例： |br| ``ACQ:KEEP:ARM?`` > ``ON``
      - C++: ``rp_AcqGetArmKeep(bool* state)`` |br| Python: ``rp_AcqGetArmKeep()``
      - 获取触发后持续采集设置的状态。 |br| 如果启用了 ARM keep 模式，则返回 ``ON``。
      - 开发中




采集设置
--------------------------

**参数选项：**

- ``<n> = {1,2}`` （设置通道 IN1 或 IN2）
- ``<decimation> = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536}`` 默认： ``1``
- ``<decimation_ext> = {1, 2, 4, 8, 16, 17, 18, 19, ..., 65536}`` 默认： ``1``
- ``<average> = {OFF, ON}`` 默认： ``ON``
- ``<bypass> = {OFF, ON}`` 默认： ``OFF``
- ``<state> = {LV, HV}`` 默认： ``LV``
- ``<mode> = {AC, DC}`` 默认 ``DC``
- ``<units> = {RAW, VOLTS}`` 默认 ``VOLTS``
- ``<format> = {BIN, ASCII}`` 默认 ``ASCII``
- ``<order> = {BEND, LEND}`` 默认 ``BEND``
- ``<enable> = {true, false}`` 默认： ``true``


*仅限 STEMlab 125-14 4-Input（附加）：*

- ``<n> = {3,4}`` （设置通道 IN3 或 IN4）

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``
- 抽取 - ``RP_DEC_1, RP_DEC_2, RP_DEC_4, RP_DEC_8, RP_DEC_16, RP_DEC_32, RP_DEC_64, RP_DEC_128, RP_DEC_256, RP_DEC_512, RP_DEC_1024, RP_DEC_2048,``
  ``RP_DEC_4096, RP_DEC_8192, RP_DEC_16384, RP_DEC_32768, RP_DEC_65536``

*仅 SIGNALlab 250-12（附加）：*

- 输入耦合 - ``RP_DC, RP_AC``

*仅限 STEMlab 125-14 4-Input（附加）：*

- 快速模拟通道 - ``RP_CH_3, RP_CH_4``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 53 96 79 20
    :header-rows: 1

    * - SCPI
      - API、Jupyter
      - 描述
      - 生态系统
    * - ``ACQ:DEC <decimation>`` |br| 示例： |br| ``ACQ:DEC 4``
      - C++: ``rp_AcqSetDecimation(rp_acq_decimation_t decimation)`` |br| Python: ``rp_AcqSetDecimation(<decimation>)``
      - 设置抽取因子 (从 1 到 65536 的 2 的幂).
      - 1.04-18 及更高版本
    * - ``ACQ:DEC:CH<n> <decimation>`` |br| 示例： |br| ``ACQ:DEC:CH1 4``
      - C++: ``rp_AcqSetDecimationCh(rp_channel_t channel, rp_acq_decimation_t decimation)`` |br| Python: ``rp_AcqSetDecimationCh(<channel>, <decimation>)``
      - 设置抽取因子 (从 1 到 65536 的 2 的幂). |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:DEC?`` > ``<decimation>`` |br| 示例： |br| ``ACQ:DEC?`` > ``1``
      - C++: ``rp_AcqGetDecimation(rp_acq_decimation_t* decimation)`` |br| Python: ``rp_AcqGetDecimation()``
      - 获取抽取因子.
      - 1.04-18 及更高版本
    * - ``ACQ:DEC:CH<n>?`` > ``<decimation>`` |br| 示例： |br| ``ACQ:DEC:CH1?`` > ``1``
      - C++: ``rp_AcqGetDecimationCh(rp_channel_t channel, rp_acq_decimation_t* decimation)`` |br| Python: ``rp_AcqGetDecimationCh(<channel>)``
      - 获取抽取因子. |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:DEC:Factor <decimation_ext>`` |br| 示例： |br| ``ACQ:DEC:Factor 17``
      - C++: ``rp_AcqSetDecimationFactor(uint32_t decimation)`` |br| Python: ``rp_AcqSetDecimationFactor(<decimation>)``
      - 设置扩展抽取因子 (最高至 16 的 2 的幂，之后可为任意 |br| 整数 最高至 65536).
      - 2.00-30 及更高版本
    * - ``ACQ:DEC:Factor:CH<n> <decimation_ext>`` |br| 示例： |br| ``ACQ:DEC:Factor:CH1 17``
      - C++: ``rp_AcqSetDecimationFactorCh(rp_channel_t channel, uint32_t decimation)`` |br| Python: ``rp_AcqSetDecimationFactorCh(<channel>, <decimation>)``
      - 设置扩展抽取因子 (最高至 16 的 2 的幂，之后可为任意 |br| 整数 最高至 65536). |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:DEC:Factor?`` > ``<decimation_ext>`` |br| 示例： |br| ``ACQ:DEC:Factor?`` > ``1``
      - C++: ``rp_AcqGetDecimationFactor(uint32_t* decimation)`` |br| Python: ``rp_AcqGetDecimationFactor()``
      - 获取扩展抽取因子.
      - 2.00-30 及更高版本
    * - ``ACQ:DEC:Factor:CH<n>?`` > ``<decimation_ext>`` |br| 示例： |br| ``ACQ:DEC:Factor:CH1?`` > ``1``
      - C++: ``rp_AcqGetDecimationFactorCh(rp_channel_t channel, uint32_t* decimation)`` |br| Python: ``rp_AcqGetDecimationFactorCh(<channel>)``
      - 获取扩展抽取因子. |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - -
      - C++: ``rp_AcqConvertFactorToDecimation(uint32_t factor,rp_acq_decimation_t* decimation)`` |br| Python: ``rp_AcqConvertFactorToDecimation(<factor>)``
      - 将抽取因子转换为最接近的可用抽取值 |br| (最接近的 2 的幂).
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_AcqGetSamplingRateHz(float* sampling_rate)`` |br| Python: ``rp_AcqGetSamplingRateHz()``
      - 获取当前采样率（单位：Hz）。
      - 1.04-18 及更高版本
    * - ``ACQ:AVG <average>``
      - C++: ``rp_AcqSetAveraging(bool enabled)`` |br| Python: ``rp_AcqSetAveraging(<enable>)``
      - 启用/禁用平均。 |br| 如果 ``DEC`` > 1，每个采样是跳过采样的平均值。 ``DEC`` > 1.
      - 1.04-18 及更高版本
    * - ``ACQ:AVG?`` > ``<average>`` |br| 示例： |br| ``ACQ:AVG?`` > ``ON``
      - C++: ``rp_AcqGetAveraging(bool *enabled)`` |br| Python: ``rp_AcqGetAveraging()``
      - 获取平均状态。 |br| 当 ``DEC`` > 1 时对跳过的采样求平均 ``DEC`` > 1
      - 1.04-18 及更高版本
    * - ``ACQ:AVG:CH<n> <average>``
      - C++: ``rp_AcqSetAveragingCh(rp_channel_t channel, bool enabled)`` |br| Python: ``rp_AcqSetAveragingCh(<channel>, <enable>)``
      - 启用/禁用平均。 |br| 如果 ``DEC`` > 1，每个采样是跳过采样的平均值。 ``DEC`` > 1. |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:AVG:CH<n>?`` > ``<average>`` |br| 示例： |br| ``ACQ:AVG:CH1?`` > ``ON``
      - C++: ``rp_AcqGetAveragingCh(rp_channel_t channel, bool *enabled)`` |br| Python: ``rp_AcqGetAveragingCh(<channel>)``
      - 获取平均状态。 |br| 当 ``DEC`` > 1 时对跳过的采样求平均 ``DEC`` > 1 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:FILTER:BYPASS:CH<n> <bypass>``
      - C++: ``rp_AcqSetBypassFilter(rp_channel_t channel, bool enabled)`` |br| Python: ``rp_AcqSetBypassFilter(<channel>, <enable>)``
      - 该函数启用或禁用 FPGA 中的滤波器。
      - 2.07-43 及更高版本
    * - ``ACQ:FILTER:BYPASS:CH<n>?`` > ``<bypass>`` |br| 示例： |br| ``ACQ:FILTER:BYPASS:CH1?`` > ``ON``
      - C++: ``rp_AcqGetBypassFilter(rp_channel_t channel, bool *enabled)`` |br| Python: ``rp_AcqGetBypassFilter(<channel>)``
      - 获取 FPGA 当前的滤波器旁路状态
      - 2.07-43 及更高版本
    * - ``ACQ:SOUR<n>:OFFS <offset>`` |br| 示例： |br| ``ACQ:SOUR1:OFFS 0.1``
      - C++: ``rp_AcqSetOffset(rp_channel_t channel, float value)`` |br| Python: ``rp_AcqSetOffset(<channel>, <value>)``
      - 请求数据时增加电压偏移。仅影响 float 和 double |br| 数据类型。原始数据保持不变。
      - 开发中
    * - ``ACQ:SOUR<n>:OFFS?`` > ``<offset>`` |br| 示例： |br| ``ACQ:SOUR1:OFFS?`` > ``0.1``
      - C++: ``rp_AcqGetOffset(rp_channel_t channel, float* value)`` |br| Python: ``rp_AcqGetOffset(<channel>)``
      - 返回以伏特为单位的偏移值。
      - 开发中
    * - ``ACQ:SOUR<n>:GAIN <state>`` |br| 示例： |br| ``ACQ:SOUR1:GAIN LV``
      - C++: ``rp_AcqSetGain(rp_channel_t channel, rp_pinState_t state)`` |br| Python: ``rp_AcqSetGain(<channel>, <state>)``
      - 将指定通道的增益设置为 HIGH 或 LOW。 |br| (对于 SIGNALlab 250-12，这对应 1:20 和 1:1 衰减器). |br| 增益对应 Red Pitaya 快速模拟输入上的跳线设置.
      - 1.04-18 及更高版本
    * - ``ACQ:SOUR<n>:GAIN?`` > ``<state>`` |br| 示例： |br| ``ACQ:SOUR1:GAIN?`` > ``HV``
      - C++: ``rp_AcqGetGain(rp_channel_t channel, rp_pinState_t* state)`` |br| Python: ``rp_AcqGetGain(<channel>)``
      - 获取指定通道的增益设置 |br| (对于 SIGNALlab 250-12，这对应 1:20 和 1:1 衰减器).
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_AcqGetGainV(rp_channel_t channel, float* voltage)`` |br| Python: ``rp_AcqGetGainV(<channel>)``
      - 获取指定通道的增益（单位：伏特）。
      - 1.04-18 及更高版本
    * - ``ACQ:SOUR<n>:COUP <mode>`` |br| 示例： |br| ``ACQ:SOUR1:COUP AC``
      - C++: ``rp_AcqSetAC_DC(rp_channel_t channel, rp_acq_ac_dc_mode_t mode)`` |br| Python: ``rp_AcqSetAC_DC(<channel>, <mode>)``
      - 设置指定输入的 AC / DC 模式（仅 SIGNALlab 250-12）。
      - 1.04-18 及更高版本
    * - ``ACQ:SOUR<n>:COUP?`` > ``<mode>`` |br| 示例： |br| ``ACQ:SOUR1:COUP?`` > ``AC``
      - C++: ``rp_AcqGetAC_DC(rp_channel_t channel, rp_acq_ac_dc_mode_t *status)`` |br| Python: ``rp_AcqGetAC_DC(<channel>)``
      - 获取指定输入的 AC / DC 模式（仅 SIGNALlab 250-12）。
      - 1.04-18 及更高版本
    * - ``ACQ:DATA:Units <units>`` |br| 示例： |br| ``ACQ:DATA:Units RAW``
      - C++: - (参见具体采集命令) |br| Python: - (参见具体采集命令)
      - 选择返回采集数据的单位。对于 API 命令 |br| 这取决于所调用的函数（详见具体函数）。
      - 1.04-18 及更高版本
    * - ``ACQ:DATA:Units?`` > ``<units>`` |br| 示例： |br| ``ACQ:DATA:Units?`` > ``RAW``
      - C++: - (参见具体采集命令) |br| Python: - (参见具体采集命令)
      - 获取返回采集数据的单位。
      - 1.04-18 及更高版本
    * - ``ACQ:DATA:FORMAT <format>`` |br| 示例： |br| ``ACQ:DATA:FORMAT ASCII``
      - C++: - (N/A) |br| Python: - (N/A)
      - 选择返回采集数据的格式。 |br| 仅用于远程 SCPI 控制。
      - 1.04-18 及更高版本
    * - ``ACQ:DATA:FORMAT?`` > ``<format>`` |br| 示例： |br| ``ACQ:DATA:FORMAT?`` > ``ASCII``
      - C++: - (N/A) |br| Python: - (N/A)
      - 返回当前格式设置。 |br| 仅用于远程 SCPI 控制。
      - 1.04-18 及更高版本
    * - ``ACQ:DATA:BYTE:ORDER <order>`` |br| 示例： |br| ``ACQ:DATA:BYTE:ORDER LEND``
      - C++: - (N/A) |br| Python: - (N/A)
      - 设置服务器在 BIN 模式查询时返回的字节序。 |br| 为获得最佳性能，将模式设置为 LEND |br| 仅用于远程 SCPI 控制。
      - 2.07-43 及更高版本
    * - ``ACQ:DATA:BYTE:ORDER?`` > ``<order>`` |br| 示例： |br| ``ACQ:DATA:BYTE:ORDER?`` > ``LEND``
      - C++: - (N/A) |br| Python: - (N/A)
      - 返回当前字节序设置。 |br| 仅用于远程 SCPI 控制。
      - 2.07-43 及更高版本
    * - ``ACQ:BUF:SIZE?`` > ``<size>`` |br| 示例： |br| ``ACQ:BUF:SIZE?`` > ``16384``
      - C++: ``rp_AcqGetBufSize(uint32_t *size)`` |br| Python: ``rp_AcqGetBufSize(<buffer>)``
      - 返回缓冲区大小。 |br| 对于 Python API，输入参数就是缓冲区本身.
      - 1.04-18 及更高版本
    * - - (N/A)
      - C++: - (查找 *malloc* 函数的在线文档) |br| Python: ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)``
      - 执行内存分配并返回请求的缓冲区。 |br| - ``<maxChannels>`` - 将采集的通道数 |br| - ``<enght>`` - 缓冲区长度（采样数） （最大 16384） |br| - ``<initInt16>, <initDouble>, <initFloat>`` - 缓冲区采样类型，将一个设置为 |br| 设置为 ``true``，其他设置为 ``false``。 |br| 对于 Python API。 由返回 NumPy 缓冲区的函数替代。
      - 2.00-18 - 2.04-35
    * - - (N/A)
      - C++: - (查找 *free* 函数的在线文档) |br| Python: ``rp_deleteBuffer(<buffer>)``
      - 释放已分配的资源。 |br| - ``<buffer>`` - 待释放的缓冲区 |br| 对于 Python API。 |br| 由返回 NumPy 缓冲区的函数替代。
      - 2.00-18 - 2.04-35



采集触发
--------------------


**参数选项：**

- ``<n> = {1,2}`` （设置通道 IN1 或 IN2）
- ``<source> = {DISABLED, NOW, CH1_PE, CH1_NE, CH2_PE, CH2_NE, EXT_PE, EXT_NE, AWG_PE, AWG_NE}``  默认： ``DISABLED``
- ``<source> = {<source>, CH1_AE, CH2_AE, EXT_AE, AWG_AE}  (any edge triggering)`` （任意边沿触发） **开发中**
- ``<state> = {WAIT, TD}``
- ``<tr_state> = {OK, TIMEOUT,ERROR}``
- ``<fill_state> = {0, 1}``
- ``<decimated_data_num> = {value in samples}`` (最小值 ``-8192``) 默认： ``0``
- ``<time_ns> = {value in nS}`` 默认： ``0``
- ``<value> = {value in us}`` 默认： ``500``
- ``<pre_counter> = {0...4294967295}``
- ``<voltage> = {value in V}`` 默认： ``0``
- ``<timeout_ms> = {timeout in milliseconds}`` （若要禁用超时，请使用：-1）
- ``<mode> = {TRIG, FILL}`` （中断事件类型）
- ``<enable> = {ON, OFF}`` 默认： ``OFF``

*仅限 STEMlab 125-14 4-Input（附加）：*

- ``<n> = {3,4}`` （设置通道 IN3 或 IN4）
- ``<source> = {CH3_PE, CH3_NE, CH4_PE, CH4_NE}``
- ``<source> = {<source>, CH3_AE, CH4_AE}  (any edge triggering)`` （任意边沿触发） **开发中**

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``
- 采集触发 - ``RP_TRIG_SRC_DISABLED, RP_TRIG_SRC_NOW, RP_TRIG_SRC_CHA_PE, RP_TRIG_SRC_CHA_NE, RP_TRIG_SRC_CHB_PE, RP_TRIG_SRC_CHB_NE,``
  ``RP_TRIG_SRC_EXT_PE, RP_TRIG_SRC_EXT_NE, RP_TRIG_SRC_AWG_PE, RP_TRIG_SRC_AWG_NE``
- 采集触发任意边沿 - ``RP_TRIG_SRC_CHA_AE, RP_TRIG_SRC_CHB_AE, RP_TRIG_SRC_EXT_AE, RP_TRIG_SRC_AWG_AE`` **开发中**
- 采集触发状态 - ``RP_TRIG_STATE_TRIGGERED, RP_TRIG_STATE_WAITING``
- 缓冲区大小 - ``ADC_BUFFER_SIZE, DAC_BUFFER_SIZE``
- 中断模式 - ``RP_INT_TRIGGER, RP_INT_FILL``

*仅限 STEMlab 125-14 4-Input（附加）：*

- 快速模拟通道 - ``RP_CH_3, RP_CH_4``
- 采集触发 - ``RP_TRIG_SRC_CHC_PE, RP_TRIG_SRC_CHC_NE, RP_TRIG_SRC_CHD_PE, RP_TRIG_SRC_CHD_NE``
- 采集触发任意边沿 - ``RP_TRIG_SRC_CHC_AE, RP_TRIG_SRC_CHD_AE`` **开发中**


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 61 86 79 25
    :header-rows: 1

    * - SCPI
      - API、Jupyter
      - 描述
      - 生态系统
    * - ``ACQ:TRig <source>`` |br| 示例： |br| ``ACQ:TRig CH1_PE``
      - C++: ``rp_AcqSetTriggerSrc(rp_acq_trig_src_t source)`` |br| Python: ``rp_AcqSetTriggerSrc(<source>)``
      - 设置采集触发源。选项包括禁用、立即触发 |br| ，或设置触发源和边沿。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:CH<n> <source>`` |br| 示例： |br| ``ACQ:TRig:CH1 CH1_PE``
      - C++: ``rp_AcqSetTriggerSrcCh(rp_channel_t channel, rp_acq_trig_src_t source)`` |br| Python: ``rp_AcqSetTriggerSrcCh(<channel>, <source>)``
      - 设置采集触发源。选项包括禁用、立即触发 |br| ，或设置触发源和边沿。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - -
      - C++: ``rp_AcqGetTriggerSrc(rp_acq_trig_src_t* source)`` |br| Python: ``rp_AcqGetTriggerSrc()``
      - 获取采集触发源。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:STAT?`` > ``<state>`` |br| 示例： |br| ``ACQ:TRig:STAT?`` > ``WAIT``
      - C++: ``rp_AcqGetTriggerState(rp_acq_trig_state_t* state)`` |br| Python: ``rp_AcqGetTriggerState()``
      - 获取采集触发状态。如果触发器为 ``DISABLED`` 或采集已触发，则状态为, the state is ``TD``. 否则为 ``WAIT``.
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:STAT:CH<n>?`` > ``<state>`` |br| 示例： |br| ``ACQ:TRig:STAT:CH1?`` > ``WAIT``
      - C++: ``rp_AcqGetTriggerStateCh(rp_channel_t channel, rp_acq_trig_state_t* state)`` |br| Python: ``rp_AcqGetTriggerStateCh(<channel>)``
      - 获取采集触发状态。如果触发器为 ``DISABLED`` 或采集已触发，则状态为, the state is ``TD``. 否则为 ``WAIT``. |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TRig:INT:ENABLE <mode>,<enable>`` |br| 示例： |br| ``ACQ:TRig:INT:ENABLE TRIG,ON``
      - C++: ``rp_AcqSetIntMask(rp_int_mode_t mode, bool enable)`` |br| Python: ``rp_AcqSetIntMask(<mode>, <enable>)``
      - 启用或禁用指定 |br| 中断事件的中断生成。 |br| - ``TRIG``: 满足触发条件（边沿、电平等） |br| - ``FILL``: 缓冲区已满，数据已准备好处理
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:INT:ENABLE? <mode>`` > ``<enable>`` |br| 示例： |br| ``ACQ:TRig:INT:ENABLE? TRIG`` > ``1``
      - C++: ``rp_AcqGetIntMask(rp_int_mode_t mode, bool* enable)`` |br| Python: ``rp_AcqGetIntMask(<mode>)``
      - 返回指定 |br| 中断事件当前的启用/禁用状态。 |br| 启用时返回 ``1`` （ON），禁用时返回 ``0`` （OFF）。
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:INT:ENABLE:CH<n> <mode>,<enable>`` |br| 示例： |br| ``ACQ:TRig:INT:ENABLE:CH1 TRIG,ON``
      - C++: ``rp_AcqSetIntMaskCh(rp_channel_t channel, rp_int_mode_t mode, bool enable)`` |br| Python: ``rp_AcqSetIntMaskCh(<channel>, <mode>, <enable>)``
      - 启用或禁用指定 |br| 通道和 中断事件的中断生成。 |br| 仅用于分离触发模式.
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:INT:ENABLE:CH<n>? <mode>`` > |br| ``<enable>`` |br| 示例： |br| ``ACQ:TRig:INT:ENABLE:CH1? TRIG`` > ``1``
      - C++: ``rp_AcqGetIntMaskCh(rp_channel_t channel, rp_int_mode_t mode,`` |br| ``bool* enable)`` |br| Python: ``rp_AcqGetIntMaskCh(<channel>, <mode>)``
      - 返回指定 |br| 指定通道和 中断事件的中断生成。 |br| 仅用于分离触发模式.
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:INT<timeout_ms>:STAT?`` > ``<tr_state>`` |br| 示例： |br| ``ACQ:TRig:INT1000:STAT?`` > ``OK``
      - C++: ``rp_AcqIntTriggerRead(int timeout_ms)`` |br| Python: ``rp_AcqIntTriggerRead(<timeout_ms>)``
      - 等待任意通道上的触发中断事件，超时单位为毫秒。 |br| 使用 -1 禁用超时。
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:INT<timeout_ms>:STAT:CH<n>?`` > ``<tr_state>`` |br| 示例： |br| ``ACQ:TRig:INT:STAT:CH1?`` > ``OK``
      - C++: ``rp_AcqIntTriggerReadCh(rp_channel_t channel, int timeout_ms)`` |br| Python: ``rp_AcqIntTriggerReadCh(<channel>, <timeout_ms>)``
      - 等待指定通道上的触发中断，超时单位为毫秒。 |br| 使用 -1 禁用超时。
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:FILL?`` > ``<fill_state>`` |br| 示例： |br| ``ACQ:TRig:FILL?`` > ``1``
      - C++: ``rp_AcqGetBufferFillState(bool* state)`` |br| Python: ``rp_AcqGetBufferFillState()``
      - 缓冲区数据已满时返回 1，否则返回 0。
      - 2.00-15 及更高版本
    * - ``ACQ:TRig:FILL:CH<n>?`` > ``<fill_state>`` |br| 示例： |br| ``ACQ:TRig:FILL:CH1?`` > ``1``
      - C++: ``rp_AcqGetBufferFillStateCh(rp_channel_t channel, bool* state)`` |br| Python: ``rp_AcqGetBufferFillStateCh(<channel>)``
      - 缓冲区数据已满时返回 1，否则返回 0。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TRig:INT<timeout_ms>:FILL?`` > ``<tr_state>`` |br| 示例： |br| ``ACQ:TRig:INT1000:FILL?`` > ``OK``
      - C++: ``rp_AcqIntFillRead(int timeout_ms)`` |br| Python: ``rp_AcqIntFillRead(<timeout_ms>)``
      - 等待任意通道上的缓冲区填充中断事件，超时单位为毫秒。 |br| 使用 -1 禁用超时。
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:INT<timeout_ms>:FILL:CH<n>?`` > ``<tr_state>`` |br| 示例： |br| ``ACQ:TRig:INT:FILL:CH1?`` > ``OK``
      - C++: ``rp_AcqIntFillReadCh(rp_channel_t channel, int timeout_ms)`` |br| Python: ``rp_AcqIntFillReadCh(<channel>, <timeout_ms>)``
      - 等待指定通道上的缓冲区填充中断，超时单位为毫秒。 |br| 使用 -1 禁用超时。
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:DLY <decimated_data_num>`` |br| 示例： |br| ``ACQ:TRig:DLY 2314``
      - C++: ``rp_AcqSetTriggerDelay(int32_t decimated_data_num)`` |br| Python: ``rp_AcqSetTriggerDelay(<decimated_data_num>)``
      - 设置以采样数表示的触发延迟。 默认触发时刻位于采集缓冲区 |br| 的中间 （第 8192 个采样；触发延迟设置为 0）。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:DLY:CH<n> <decimated_data_num>`` |br| 示例： |br| ``ACQ:TRig:DLY:CH1 2314``
      - C++: ``rp_AcqSetTriggerDelayCh(rp_channel_t channel, int32_t decimated_data_num)`` |br| Python: ``rp_AcqSetTriggerDelayCh(<channel>,<decimated_data_num>)``
      - 设置以采样数表示的触发延迟。 默认触发时刻位于采集缓冲区 |br| 的中间 （第 8192 个采样；触发延迟设置为 0）。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TRig:DLY?`` > ``<decimated_data_num>`` |br| 示例： |br| ``ACQ:TRig:DLY?`` > ``2314``
      - C++: ``rp_AcqGetTriggerDelay(int32_t* decimated_data_num)`` |br| Python: ``rp_AcqGetTriggerDelay()``
      - 获取以采样数表示的触发延迟。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:DLY:CH<n>?`` > ``<decimated_data_num>`` |br| 示例： |br| ``ACQ:TRig:DLY:CH1?`` > ``2314``
      - C++: ``rp_AcqGetTriggerDelayCh(rp_channel_t channel, int32_t* decimated_data_num)`` |br| Python: ``rp_AcqGetTriggerDelayCh(<channel>)``
      - 获取以采样数表示的触发延迟。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TRig:DLY:NS <time_ns>`` |br| 示例： |br| ``ACQ:TRig:DLY:NS 128``
      - C++: ``rp_AcqSetTriggerDelayNs(int64_t time_ns)`` |br| Python: ``rp_AcqSetTriggerDelayNs(<time_ns>)``
      - 设置以 ns 表示的触发延迟。 必须是板卡时钟 |br| 分辨率的整数倍 (125 MHz clock == 8 ns 分辨率的整数倍, 250 MHz == 4 ns 分辨率的整数倍).
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:DLY:NS:CH<n> <time_ns>`` |br| 示例： |br| ``ACQ:TRig:DLY:NS:CH1 128``
      - C++: ``rp_AcqSetTriggerDelayNsCh(rp_channel_t channel, int64_t time_ns)`` |br| Python: ``rp_AcqSetTriggerDelayNsCh(<channel>,<time_ns>)``
      - 设置以 ns 表示的触发延迟。 必须是板卡时钟 |br| 分辨率的整数倍 (125 MHz clock == 8 ns 分辨率的整数倍, 250 MHz == 4 ns 分辨率的整数倍). |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TRig:DLY:NS?`` > ``<time_ns>`` |br| 示例： |br| ``ACQ:TRig:DLY:NS?`` > ``128`` ns
      - C++: ``rp_AcqGetTriggerDelayNs(int64_t* time_ns)`` |br| Python: ``rp_AcqGetTriggerDelayNs()``
      - 获取以 ns 表示的触发延迟。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:DLY:NS:CH<n>?`` > ``<time_ns>`` |br| 示例： |br| ``ACQ:TRig:DLY:NS:CH1?`` > ``128`` ns
      - C++: ``rp_AcqGetTriggerDelayNsCh(rp_channel_t channel, int64_t* time_ns)`` |br| Python: ``rp_AcqGetTriggerDelayNsCh(<channel>)``
      - 获取以 ns 表示的触发延迟。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TRig:PRE:COUNTER?`` > ``<pre_counter>`` |br| 示例： |br| ``ACQ:TRig:PRE:COUNTER?`` > ``8192``
      - C++: ``rp_AcqGetPreTriggerCounter(uint32_t* value)`` |br| Python: ``rp_AcqGetPreTriggerCounter()``
      - 返回缓冲区中触发位置之前的有效数据点（采样）数量 |br| 。
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:PRE:COUNTER:CH<n>?`` > ``<pre_counter>`` |br| 示例： |br| ``ACQ:TRig:PRE:COUNTER:CH1?`` > ``8192``
      - C++: ``rp_AcqGetPreTriggerCounterCh(rp_channel_t channel, uint32_t* value)`` |br| Python: ``rp_AcqGetPreTriggerCounterCh(<channel>)``
      - 返回缓冲区中触发位置之前的有效数据点（采样）数量 |br| 触发位置。 |br| 仅用于分离触发模式.
      - 3.00-57 及更高版本
    * - ``ACQ:TRig:HYST <voltage>`` |br| 示例： |br| ``ACQ:TRig:HYST 0.005``
      - C++: ``rp_AcqSetTriggerHyst(float voltage)`` |br| Python: ``rp_AcqSetTriggerHyst(<voltage>)``
      - 设置以伏特为单位的触发迟滞阈值。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:HYST?`` > ``<voltage>`` |br| 示例： |br| ``ACQ:TRig:HYST?`` > ``0.005`` V
      - C++: ``rp_AcqGetTriggerHyst(float* voltage)`` |br| Python: ``rp_AcqGetTriggerHyst()``
      - 获取以伏特为单位的触发迟滞阈值。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:LEV <voltage>`` |br| 示例： |br| ``ACQ:TRig:LEV 0.125 V``
      - C++: ``rp_AcqSetTriggerLevel(rp_channel_trigger_t channel, float voltage)`` |br| Python: ``rp_AcqSetTriggerLevel(<channel>, <voltage>)``
      - 设置以 V 为单位的触发电平。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:LEV:CH<n> <voltage>`` |br| 示例： |br| ``ACQ:TRig:LEV:CH1 0.125 V``
      - C++: ``rp_AcqSetTriggerLevel(rp_channel_trigger_t channel, float voltage)`` |br| Python: ``rp_AcqSetTriggerLevel(<channel>, <voltage>)``
      - 设置以 V 为单位的触发电平。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TRig:LEV?`` > ``<voltage>`` |br| 示例： |br| ``ACQ:TRig:LEV?`` > ``0.123`` V
      - C++: ``rp_AcqGetTriggerLevel(rp_channel_trigger_t channel, float* voltage)`` |br| Python: ``rp_AcqGetTriggerLevel(<channel>)``
      - 获取以 V 为单位的触发电平。
      - 1.04-18 及更高版本
    * - ``ACQ:TRig:LEV:CH<n>?`` > ``<voltage>`` |br| 示例： |br| ``ACQ:TRig:LEV:CH1?`` > ``0.123`` V
      - C++: ``rp_AcqGetTriggerLevel(rp_channel_trigger_t channel, float* voltage)`` |br| Python: ``rp_AcqGetTriggerLevel(<channel>)``
      - 获取以 V 为单位的触发电平。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TRig:EXT:LEV <voltage>`` |br| 示例： |br| ``ACQ:TRig:EXT:LEV 1``
      - C++: ``rp_AcqSetTriggerLevel(rp_channel_trigger_t channel, float voltage)`` |br| Python: ``rp_AcqSetTriggerLevel(<channel>, <voltage>)``
      - 设置以 V 为单位的外部触发电平。 |br| （仅限 SIGNALlab 250-12）
      - 1.04-18 - 2.00-30
    * - ``ACQ:TRig:EXT:LEV?`` > ``<voltage>`` |br| 示例： |br| ``ACQ:TRig:EXT:LEV?`` > ``1``
      - C++: ``rp_AcqGetTriggerLevel(rp_channel_trigger_t channel, float* voltage)`` |br| Python: ``rp_AcqGetTriggerLevel(<channel>)``
      - 获取以 V 为单位的外部触发电平。 |br| （仅限 SIGNALlab 250-12）
      - 1.04-18 - 2.00-30
    * - ``ACQ:TRig:EXT:DEBouncer:[US] <value>`` |br| 示例： |br| ``ACQ:TRig:EXT:DEBouncer:US 1``
      - C++: ``rp_AcqSetExtTriggerDebouncerUs(double value)`` |br| Python: ``rp_AcqSetExtTriggerDebouncerUs(<value>)``
      - 以微秒为单位设置外部触发采集去抖时间 （值必须 |br| 为正）。
      - 2.00-15 及更高版本
    * - ``ACQ:TRig:EXT:DEBouncer:[US]?`` > ``<value>`` |br| 示例： |br| ``ACQ:TRig:EXT:DEBouncer:US?`` > ``1``
      - C++: ``rp_AcqGetExtTriggerDebouncerUs(double *value)`` |br| Python: ``rp_AcqGetExtTriggerDebouncerUs()``
      - 以微秒为单位设置外部触发采集去抖时间.
      - 2.00-15 及更高版本
    * - ``ACQ:TS <time_ns>`` |br| 示例： |br| ``ACQ:TS 0``
      - C++: ``rp_AcqSetInitTimestamp(uint64_t value)`` |br| Python: ``rp_AcqSetInitTimestamp(<value>)``
      - 设置采集的初始时间戳值（时钟周期）。
      - 3.00-57 及更高版本
    * - ``ACQ:TS:CH<n>?`` > ``<time_ns>`` |br| 示例： |br| ``ACQ:TS:CH1?`` > ``12345``
      - C++: ``rp_AcqGetTimestamp(rp_channel_t, uint64_t* time_ns)`` |br| Python: ``rp_AcqGetTimestamp(<channel>)``
      - 获取指定通道的采集时间戳（单位：ns）。
      - 3.00-57 及更高版本
    * - ``TRig:EXT:LEV <voltage>`` |br| 示例： |br| ``TRig:EXT:LEV 1``
      - C++: ``rp_SetExternalTriggerLevel(float voltage)`` |br| Python: ``rp_SetExternalTriggerLevel(<voltage>)``
      - 设置以 V 为单位的外部触发电平。 |br| （仅限 SIGNALlab 250-12）
      - 2.04-35 及更高版本
    * - ``TRig:EXT:LEV?`` > ``<voltage>`` |br| 示例： |br| ``TRig:EXT:LEV?`` > ``1``
      - C++: ``rp_GetExternalTriggerLevel(float* voltage)`` |br| Python: ``rp_GetExternalTriggerLevel()``
      - 获取以 V 为单位的外部触发电平。 |br| （仅限 SIGNALlab 250-12）
      - 2.04-35 及更高版本





数据指针
---------------

数据会写入循环缓冲区，并持续覆盖，直到触发时刻。因此，触发位置可以位于循环缓冲区内的任意位置，尽管在采集数据中它通常显示为约第 8192 个采样点（受 ``ACQ:TRIG:DLY`` 命令影响）。

**参数选项：**

- ``<n> = {1,2}`` （设置通道 IN1 或 IN2）
- ``<pos> = {position inside circular buffer}`` (0 ... 16383)

*仅限 STEMlab 125-14 4-Input（附加）：*

- ``<n> = {3,4}`` （设置通道 IN3 或 IN4）

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 39 83 58 20
    :header-rows: 1

    * - SCPI
      - API、Jupyter
      - 描述
      - 生态系统
    * - ``ACQ:WPOS?`` > ``<pos>`` |br| 示例： |br| ``ACQ:WPOS?`` > ``1024``
      - C++: ``rp_AcqGetWritePointer(uint32_t* pos)`` |br| Python: ``rp_AcqGetWritePointer()``
      - 返回写指针的当前位置， |br| 即缓冲区中最新采样的索引。
      - 1.04-18 及更高版本
    * - ``ACQ:TPOS?`` > ``<pos>`` |br| 示例： |br| ``ACQ:TPOS?`` > ``512``
      - C++: ``rp_AcqGetWritePointerAtTrig(uint32_t* pos)`` |br| Python: ``rp_AcqGetWritePointerAtTrig()``
      - 返回触发事件出现的位置。
      - 1.04-18 及更高版本
    * - ``ACQ:WPOS:CH<n>?`` > ``<pos>`` |br| 示例： |br| ``ACQ:WPOS:CH1?`` > ``1024``
      - C++: ``rp_AcqGetWritePointerCh(rp_channel_t channel, uint32_t* pos)`` |br| Python: ``rp_AcqGetWritePointerCh(<channel>)``
      - 返回写指针的当前位置， |br| 即缓冲区中最新采样的索引。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本
    * - ``ACQ:TPOS:CH<n>?`` > ``<pos>`` |br| 示例： |br| ``ACQ:TPOS:CH1?`` > ``512``
      - C++: ``rp_AcqGetWritePointerAtTrigCh(rp_channel_t channel, uint32_t* pos)`` |br| Python: ``rp_AcqGetWritePointerAtTrigCh(<channel>)``
      - 返回触发事件出现的位置。 |br| 仅用于分离触发模式 |br| （仅限 STEMlab 125-14 4-Input） |br| （所有板卡自 2.07-48 起）
      - 2.05-37 及更高版本



数据读取
-----------

**参数选项：**

- ``<n> = {1,2}`` （设置通道 IN1 或 IN2）
- ``<start_pos>, <end_pos>, <pos> = {0, 1, ..., 16383}``
- ``<buffer>`` 用于存储数据的数组。 对于 Python API，使用 ``rp_createBuffer`` 对于 C++ API，使用 *malloc*.
- ``<buffer_size>`` 用于存储数据的数组大小。
- ``<t_pos> = {PRE_TRIG, POST_TRIG, PRE_POST_TRIG}`` 相对于触发器的缓冲区读取方向模式

*仅限 STEMlab 125-14 4-Input（附加）：*

- ``<n> = {3,4}`` （设置通道 IN3 或 IN4）

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``

*仅限 STEMlab 125-14 4-Input（附加）：*

- 快速模拟通道 - ``RP_CH_3, RP_CH_4``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 45 138 88 20
    :header-rows: 1

    * - SCPI
      - API、Jupyter
      - 描述
      - 生态系统
    * - ``ACQ:SOUR<n>:DATA:STArt:End?`` |br| ``<start_pos>,<end_pos>`` |br| 示例： |br| ``ACQ:SOUR1:DATA:STArt:End? 10,13`` > |br| ``{123,231,-231}``
      - C++: ``rp_AcqGetDataPosRaw(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, int16_t* buffer, uint32_t* buffer_size)`` |br| ``rp_AcqGetDataPosV(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, float* buffer, uint32_t* buffer_size)`` |br| Python: ``rp_AcqGetDataPosRaw(<channel>, <start_pos>, <end_pos>, <buffer>, <buffer_size>)`` |br| ``rp_AcqGetDataPosV(<channel>, <start_pos>, <end_pos>, <buffer>, <buffer_size>)``
      - 读取从 ``start_pos`` 至 ``end_pos`` 的采样。 对于 API 命令， |br| 还必须提供用于存储数据的缓冲区及其大小。 使用 ``rp_createBuffer`` 为 |br| Python 分配数据，为 C++ 使用 *malloc*。 API 命令提供两个函数来返回 |br| 以 Volts 或 RAW 表示的数据。
      - 1.04-18 - 2.07-48
    * - ``ACQ:SOUR<n>:DATA:STArt:End?`` |br| ``<start_pos>,<end_pos>`` |br| 示例： |br| ``ACQ:SOUR1:DATA:STArt:End? 10,13`` > |br| ``{123,231,-231}``
      - C++: ``rp_AcqGetDataRawWithCalib(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, int16_t* buffer, uint32_t* buffer_size)`` |br| ``rp_AcqGetDataPosV(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, float* buffer, uint32_t* buffer_size)`` |br| Python: ``rp_AcqGetDataRawWithCalib(<channel>, <start_pos>, <end_pos>, <buffer>, <buffer_size>)`` |br| ``rp_AcqGetDataPosV(<channel>, <start_pos>, <end_pos>, <buffer>, <buffer_size>)``
      - 读取从 ``start_pos`` 至 ``end_pos`` 的采样。 对于 API 命令， |br| 还必须提供用于存储数据的缓冲区及其大小。 使用 ``rp_createBuffer`` 为 |br| Python 分配数据，为 C++ 使用 *malloc*。 API 命令提供两个函数来返回 |br| 以 Volts 或 RAW 表示的数据。
      - 3.00-57 及更高版本
    * - ''
      - Python: ``rp_AcqGetDataPosRawNP(channel, start_pos, end_pos, np_buffer)`` (Numpy 缓冲区 ``dtype=np.int16``) |br| ``rp_AcqGetDataPosVNP(channel, start_pos, end_pos, np_buffer)`` (Numpy 缓冲区 ``dtype=np.float32``)
      - 将捕获的缓冲区数据从 ``start_pos`` 到 ``end_pos`` 复制到传入的 |br| NumPy 缓冲区。 复制数据的长度必须与 ``np_buffer`` 长度匹配。 |br| 速度快于上述 Python 函数。
      - 2.05-37 及更高版本
    * - -
      - C++: ``rp_AcqGetDataRawWithCalib(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)`` |br| Python: ``rp_AcqGetDataRawWithCalib(<channel>, <pos>, <size>, <buffer>)`` |br| ``rp_AcqGetDataRawWithCalibNP(channel, pos, np_buffer)`` (Numpy 缓冲区 ``dtype=np.int16``)
      - 从 ``<pos>`` 开始读取 ``<size>`` 个采样。 数据以 RAW |br| 格式返回，并应用校准。 |br| Numpy 缓冲区必须使用指定的 ``dtype`` 格式。 |br| 速度快于上述 Python 函数。
      - 1.04-18 及更高版本
    * - -
      - C++: ``rp_AcqGetNormalizedDataPos(uint32_t pos)`` |br| Python: ``rp_AcqGetNormalizedDataPos(<pos>)``
      - 规范化 ADC 缓冲区位置，并返回 ADC 缓冲区大小的模运算结果。
      - 1.04-18 及更高版本
    * - ``ACQ:SOUR<n>:DATA:STArt:N?`` |br| ``<start_pos>,<size>`` |br| 示例： |br| ``ACQ:SOUR1:DATA:STArt:N? 10,3`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetDataRaw(<channel>, <pos>, <size>, <buffer>)`` |br| ``rp_AcqGetDataV(<channel>, <pos>, <size>, <buffer>)``
      - 从 ``<start_pos>`` 开始读取 ``size`` 个采样。
      - 1.04-18 - 2.07-48
    * - ``ACQ:SOUR<n>:DATA:STArt:N?`` |br| ``<start_pos>,<size>`` |br| 示例： |br| ``ACQ:SOUR1:DATA:STArt:N? 10,3`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqGetDataRawWithCalib(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetDataRawWithCalib(<channel>, <pos>, <size>, <buffer>)`` |br| ``rp_AcqGetDataV(<channel>, <pos>, <size>, <buffer>)``
      - 从 ``<start_pos>`` 开始读取 ``size`` 个采样。
      - 3.00-57 及更高版本
    * - ''
      - Python: ``rp_AcqGetDataRawNP(channel, pos, np_buffer)`` (Numpy 缓冲区 ``dtype=np.int16``) |br| ``rp_AcqGetDataVNP(channel, pos, np_buffer)`` (Numpy 缓冲区 ``dtype=np.float32``)
      - 将捕获的缓冲区数据从 ``pos`` 开始复制到传入的 NumPy 缓冲区 |br| onwards. 复制数据的长度与 ``np_buffer`` 长度匹配。 |br| Numpy 缓冲区必须使用指定的 ``dtype`` 格式。 |br| 速度快于上述 Python 函数。
      - 2.05-37 及更高版本
    * - ``ACQ:SOUR<n>:DATA?`` |br| 示例： |br| ``ACQ:SOUR2:DATA?`` > |br| ``{1.2,3.2,...,-1.2}``
      - C++: ``rp_AcqGetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetOldestDataRaw(<channel>, <size>, <buffer>)`` |br| ``rp_AcqGetOldestDataV(<channel>, <size>, <buffer>)``
      - 读取完整缓冲区。 |br| 从缓冲区中最旧的采样开始（触发延迟后的第一个采样）。 |br| 如果触发延迟设为零，则从触发位置开始读取完整缓冲区大小的数据 |br| 开始。
      - 1.04-18 - 2.07-48
    * - ``ACQ:SOUR<n>:DATA?`` |br| 示例： |br| ``ACQ:SOUR2:DATA?`` > |br| ``{1.2,3.2,...,-1.2}``
      - C++: ``rp_AcqGetOldestDataRawWithCalib(rp_channel_t channel, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetOldestDataRawWithCalib(<channel>, <size>, <buffer>)`` |br| ``rp_AcqGetOldestDataV(<channel>, <size>, <buffer>)``
      - 读取完整缓冲区。 |br| 从缓冲区中最旧的采样开始（触发延迟后的第一个采样）。 |br| 如果触发延迟设为零，则从触发位置开始读取完整缓冲区大小的数据 |br| 开始。
      - 3.00-57 及更高版本
    * - ''
      - Python: ``rp_AcqGetOldestDataRawNP(channel, np_buffer)`` (Numpy 缓冲区 ``dtype=np.int16``) |br| ``rp_AcqGetOldestDataVNP(channel, np_buffer)`` (Numpy 缓冲区 ``dtype=np.float32``)
      - 将捕获的最旧缓冲区数据复制到传入的 NumPy 缓冲区。 |br| 复制数据的长度与 ``np_buffer`` 长度匹配。 |br| Numpy 缓冲区必须使用指定的 ``dtype`` 格式。 |br| 速度快于上述 Python 函数。
      - 2.05-37 及更高版本
    * - ''
      - Python: ``rp_AcqGetOldestDataRawWithCalibNP(channel, np_buffer)`` (Numpy 缓冲区 ``dtype=np.int16``)
      - 将捕获的最旧缓冲区数据复制到传入的 NumPy 缓冲区。 |br| 复制数据的长度与 ``np_buffer`` 长度匹配。 |br| Numpy 缓冲区必须使用指定的 ``dtype`` 格式。 |br| 速度快于上述 Python 函数。
      - 3.00-57 及更高版本
    * - ``ACQ:SOUR<n>:DATA:Old:N? <size>`` |br| 示例： |br| ``ACQ:SOUR2:DATA:Old:N? 3`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqGetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetOldestDataRaw(<channel>, <size>, <buffer>)`` |br| ``rp_AcqGetOldestDataV(<channel>, <size>, <buffer>)``
      - 读取缓冲区中最旧的 ``<size>`` 个采样。
      - 1.04-18 - 2.07-48
    * - ``ACQ:SOUR<n>:DATA:Old:N? <size>`` |br| 示例： |br| ``ACQ:SOUR2:DATA:Old:N? 3`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqGetOldestDataRawWithCalib(rp_channel_t channel, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetOldestDataRawWithCalib(<channel>, <size>, <buffer>)`` |br| ``rp_AcqGetOldestDataV(<channel>, <size>, <buffer>)``
      - 读取缓冲区中最旧的 ``<size>`` 个采样。
      - 3.00-57 及更高版本
    * - ``ACQ:SOUR<n>:DATA:LATest:N? <size>`` |br| 示例： |br| ``ACQ:SOUR1:DATA:LATest:N? 3`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqGetLatestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetLatestDataV(rp_channel_t channel, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetLatestDataRaw(<channel>, <size>, <buffer>)`` |br| ``rp_AcqGetLatestDataV(<channel>, <size>, <buffer>)``
      - 读取缓冲区中最新的 ``<size>`` 个采样。
      - 1.04-18 - 2.07-48
    * - ``ACQ:SOUR<n>:DATA:LATest:N? <size>`` |br| 示例： |br| ``ACQ:SOUR1:DATA:LATest:N? 3`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqGetLatestDataRawWithCalib(rp_channel_t channel, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetLatestDataV(rp_channel_t channel, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetLatestDataRawWithCalib(<channel>, <size>, <buffer>)`` |br| ``rp_AcqGetLatestDataV(<channel>, <size>, <buffer>)``
      - 读取缓冲区中最新的 ``<size>`` 个采样。
      - 3.00-57 及更高版本
    * - ''
      - Python: ``rp_AcqGetLatestDataRawNP(channel, np_buffer)`` (Numpy 缓冲区 ``dtype=np.int16``) |br| ``rp_AcqGetLatestDataVNP(channel, np_buffer)`` (Numpy 缓冲区 ``dtype=np.float32``)
      - 将捕获的最新缓冲区数据复制到传入的 NumPy 缓冲区。 |br| 复制数据的长度与 ``np_buffer`` 长度匹配。 |br| 速度快于上述 Python 函数。
      - 2.05-37 及更高版本
    * - ''
      - Python: ``rp_AcqGetLatestDataRawWithCalibNP(channel, np_buffer)`` (Numpy 缓冲区 ``dtype=np.int16``)
      - 将捕获的最新缓冲区数据复制到传入的 NumPy 缓冲区。 |br| 复制数据的长度与 ``np_buffer`` 长度匹配。 |br| 速度快于上述 Python 函数。
      - 3.00-57 及更高版本
    * - ``ACQ:SOUR<n>:DATA:TRig? <size>,<t_pos>`` |br| 示例： |br| ``ACQ:SOUR1:DATA:TRig? 3,POST_TRIG`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetDataRaw(<channel>, <pos>, <size>, <buffer>)`` |br| ``rp_AcqGetDataV(<channel>, <pos>, <size>, <buffer>)``
      - 根据设置读取相对于触发器的 ``<size>`` 个采样。 |br| ``PRE_TRIG``, ``POST_TRIG`` 触发配置返回 ``size`` 个数据采样。 |br| ``PRE_POST_TRIG`` 返回 ``size`` * 2 + 1 个数据采样，包括触发 |br| 时刻
      - 2.05-37 - 2.07-48
    * - ``ACQ:SOUR<n>:DATA:TRig? <size>,<t_pos>`` |br| 示例： |br| ``ACQ:SOUR1:DATA:TRig? 3,POST_TRIG`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqGetDataRawWithCalib(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)`` |br| ``rp_AcqGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)`` |br| Python: ``rp_AcqGetDataRawWithCalib(<channel>, <pos>, <size>, <buffer>)`` |br| ``rp_AcqGetDataV(<channel>, <pos>, <size>, <buffer>)``
      - 根据设置读取相对于触发器的 ``<size>`` 个采样。 |br| ``PRE_TRIG``, ``POST_TRIG`` 触发配置返回 ``size`` 个数据采样。 |br| ``PRE_POST_TRIG`` 返回 ``size`` * 2 + 1 个数据采样，包括触发 |br| 时刻
      - 3.00-57 及更高版本
    * - ''
      - Python: ``rp_AcqGetDataRawNP(channel, pos, np_buffer)`` (Numpy 缓冲区 ``dtype=np.int16``) |br| ``rp_AcqGetDataVNP(channel, pos, np_buffer)`` (Numpy 缓冲区 ``dtype=np.float32``)
      - 将捕获的缓冲区数据从 ``pos`` 开始复制到传入的 NumPy 缓冲区 |br| onwards. 复制数据的长度与 ``np_buffer`` 长度匹配。 |br| Numpy 缓冲区必须使用指定的 ``dtype`` 格式。 |br| 速度快于上述 Python 函数。
      - 2.05-37 及更高版本

|

* :ref:`Back to top <commands_acq>`
* :ref:`Back to command list <command_list>`

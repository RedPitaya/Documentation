
.. _commands_dmm:

#################################
深度内存模式（DMM）
#################################

.. contents:: 深度内存模式命令索引
   :local:
   :depth: 2
   :backlinks: top

|

========================
功能概览
========================

深度内存模式命令以完整采样速率直接向 Red Pitaya 的 DDR3 RAM 流式读写数据，从而支持扩展数据采集和发生。这突破了标准采集 16384 个样本的限制，可捕获数百万个样本，唯一限制是可用 RAM 大小。

深度内存采集（DMA）使用 AXI DMA 协议在 FPGA 与 DDR 内存之间高速传输数据；深度内存发生则支持回放扩展的任意波形。


========================
重要说明
========================

* Red Pitaya OS 2.00-23 及更高版本可用。
* 需要分配足够的 DDR3 RAM（建议为 Linux OS 保留 100 MB）。
* 缓冲区越大，传输到计算机所需时间越长。
* 使用二进制格式（``ACQ:DATA:FORMAT BIN``）可加快 SCPI 数据传输。
* 详情请参阅 :ref:`深度内存采集概览 <intro_gen_acq>`。


========================
代码示例
========================

以下是深度内存模式的使用示例：

* :ref:`深度内存采集与发生示例 <examples_dmm>`。

|

.. _commands_dma:

===============================
深度内存采集（DMA）
===============================

-------------
DMA 设置
-------------

**参数选项：**

- ``<n> = {1,2}`` （设置通道 IN1 或 IN2）
- ``<byte> = {0...}``，单位为字节
- ``<decimation> = {1, 2, 4, 8, 16, 17, 18, 19, ..., 65534, 65535, 65536}`` 默认值：``1``
- ``<decimated_data_num> = {value in samples}`` 默认值：``0``
- ``<pos> = {position inside circular buffer in samples}`` （环形缓冲区中的采样位置）
- ``<enable> = {ON, OFF}`` 默认值：``OFF``
- ``<address> = {byte}`` 预留内存地址
- ``<size> = {byte}`` 缓冲区大小，单位为字节。默认值：2 MB
- ``<samples> = {sample}`` 采集缓冲区大小，单位为样本。默认值：2 MB
- ``<units> = {RAW, VOLTS}`` 默认值：``VOLTS``

*仅适用于 STEMlab 125-14 4-Input（附加）：*

- ``<n> = {3,4}`` （设置通道 IN3 或 IN4）

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``

*仅适用于 STEMlab 125-14 4-Input（附加）：*

- 快速模拟通道 - ``RP_CH_3, RP_CH_4``


.. list-table::
    :widths: 59 124 81 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 生态系统
    * - ``ACQ:AXI:START?`` > ``<byte>`` |br| Example: |br| ``ACQ:AXI:START?`` > ``16777216``
      - C++: ``rp_AcqAxiGetMemoryRegion(uint32_t *_start, uint32_t *_size)`` |br| Python: ``rp_AcqAxiGetMemoryRegion()``
      - 返回深度内存区域的起始地址。|br| API：同时返回内存区域大小。
      - 2.00-18 and up
    * - ``ACQ:AXI:SIZE?`` > ``<byte>`` |br| Example: |br| ``ACQ:AXI:SIZE?`` > ``2097152``
      - C++: ``rp_AcqAxiGetMemoryRegion(uint32_t *_start, uint32_t *_size)`` |br| Python: ``rp_AcqAxiGetMemoryRegion()``
      - 获取深度内存模式的预留内存大小。|br| **API：** 同时返回内存区域起始地址。
      - 2.00-18 and up
    * - ``ACQ:AXI:SOUR<n>:ENable <enable>`` |br| Example: |br| ``ACQ:AXI:SOUR1:ENable ON``
      - C++: ``rp_AcqAxiEnable(rp_channel_t channel, bool enable)`` |br| Python: ``rp_AcqAxiEnable(<channel>, <enable>)``
      - 启用深度内存采集中的指定采集通道。
      - 2.00-18 and up
    * - ``ACQ:AXI:DEC <decimation>`` |br| 示例： |br| ``ACQ:AXI:DEC 4``
      - C++: ``rp_AcqAxiSetDecimationFactor(uint32_t decimation)`` |br| Python: ``rp_AcqAxiSetDecimationFactor(<decimation>)``
      - 设置深度存储器模式中用于采集信号的抽取因子。
      - 2.00-18 and up
    * - ``ACQ:AXI:DEC?`` > ``<decimation>`` |br| 示例： |br| ``ACQ:AXI:DEC?`` > ``1``
      - C++: ``rp_AcqAxiGetDecimationFactor(uint32_t *decimation)`` |br| Python: ``rp_AcqAxiGetDecimationFactor()``
      - 返回深度存储器模式中用于采集信号的抽取因子。
      - 2.00-18 and up
    * - ``ACQ:AXI:DEC:CH<n> <decimation>`` |br| 示例： |br| ``ACQ:AXI:DEC:CH1 4``
      - C++: ``rp_AcqAxiSetDecimationFactorCh(rp_channel_t channel, uint32_t decimation)`` |br| Python: ``rp_AcqAxiSetDecimationFactorCh(<channel>, <decimation>)``
      - 设置深度存储器模式中用于采集信号的抽取因子。 |br| 仅用于分离触发模式
      - 2.05-37 and up
    * - ``ACQ:AXI:DEC:CH<n>?`` > ``<decimation>`` |br| 示例： |br| ``ACQ:AXI:DEC:CH1?`` > ``1``
      - C++: ``rp_AcqAxiGetDecimationFactorCh(rp_channel_t channel, uint32_t *decimation)`` |br| Python: ``rp_AcqAxiGetDecimationFactorCh(<channel>)``
      - 返回深度存储器模式中用于采集信号的抽取因子。 |br| 仅用于分离触发模式
      - 2.05-37 and up
    * - ``ACQ:AXI:SOUR<n>:Trig:Dly <decimated_data_num>`` |br| 示例： |br| ``ACQ:AXI:SOUR1:Trig:Dly 2314``
      - C++: ``rp_AcqAxiSetTriggerDelay(rp_channel_t channel, int32_t decimated_data_num)`` |br| Python: ``rp_AcqAxiSetTriggerDelay(<channel>, <decimated_data_num>)``
      - 设置触发后 |br| 写入内存的抽取数据数量。
      - 2.00-18 and up
    * - ``ACQ:AXI:SOUR<n>:Trig:Dly?`` > ``<decimated_data_num>`` |br| 示例： |br| ``ACQ:AXI:SOUR1:Trig:Dly?`` > ``2314``
      - C++: ``rp_AcqAxiGetTriggerDelay(rp_channel_t channel, int32_t *decimated_data_num)`` |br| Python: ``rp_AcqAxiGetTriggerDelay(<channel>)``
      - 返回触发后写入内存的抽取数据数量。
      - 2.00-18 and up
    * - ``ACQ:AXI:SOUR<n>:SET:Buffer <address>,<size>`` |br| 示例： |br| ``ACQ:AXI:SOUR<n>:SET:Buffer 16777216,512``
      - C++: ``rp_AcqAxiSetBufferSamples(rp_channel_t channel, uint32_t address, uint32_t samples)`` |br| ``rp_AcqAxiSetBufferBytes(rp_channel_t channel, uint32_t address, uint32_t size)`` |br| Python: ``rp_AcqAxiSetBufferSamples(<channel>, <address>, <samples>)`` |br| ``rp_AcqAxiSetBufferBytes(<channel>, <address>, <size>)``
      - 设置深度存储器缓冲区地址和采样数大小。 |br| 缓冲区大小必须是 2 的倍数。
      - 2.00-18 and up
    * - ``ACQ:AXI:DATA:UNITS <units>`` |br| 示例： |br| ``ACQ:AXI:DATA:UNITS RAW``
      - C++: -（参见 ``rp_AcqAxiGetDataV`` 和 ``rp_AcqAxiGetDataRaw``） |br| Python: -（参见 ``rp_AcqAxiGetDataV`` 和 ``rp_AcqAxiGetDataRaw``）
      - 选择返回采集数据的单位。 |br| 对于 API 命令，单位由获取数据函数选择。
      - 2.00-18 and up
    * - ``ACQ:AXI:DATA:UNITS?`` > ``<units>`` |br| 示例： |br| ``ACQ:AXI:DATA:UNITS?`` > ``RAW``
      - C++: -（参见 ``rp_AcqAxiGetDataV`` 和 ``rp_AcqAxiGetDataRaw``） |br| Python: -（参见 ``rp_AcqAxiGetDataV`` 和 ``rp_AcqAxiGetDataRaw``）
      - 获取返回采集数据的单位。 |br| 对于 API 命令，单位由获取数据函数选择。
      - 2.00-18 and up
    * - - (NA)
      - C++: -（在线查找 *malloc* 函数） |br| Python: ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)``
      - 执行内存分配并返回请求的缓冲区。 |br| - ``<maxChannels>`` - 将采集的通道数 |br| - ``<enght>`` - 缓冲区长度（采样数，最大 16384） |br| - ``<initInt16>, <initDouble>, <initFloat>`` - 缓冲区采样类型，将一个设置为 |br| ``true``，其他设置为 ``false``。 |br| 对于 Python API，已由返回 NumPy 缓冲区的函数替代。
      - 2.00-18 - 2.04-35
    * - - (NA)
      - C++: -（在线查找 *free* 函数） |br| Python: ``rp_deleteBuffer(<buffer>)``
      - 释放已分配的资源。 |br| - ``<buffer>`` - 待释放的缓冲区 |br| 对于 Python API，已由返回 NumPy 缓冲区的函数替代。
      - 2.00-18 - 2.04-35

|

----------------
DMA data read
----------------

**参数选项：**

- ``<n> = {1,2}`` (设置 IN1 或 IN2 通道)
- ``<count> = {value in samples}`` 默认值：``0``
- ``<pos> = {samples}`` 环形缓冲区中的采样位置
- ``<size> = {samples}`` 已采集数据的大小，单位为采样数
      - ``<buffer>`` 用于存储数据的数组。对于 Python API，使用 ``rp_createBuffer``；对于 C++ API，使用 *malloc*。

*STEMlab 125-14 4-Input 仅限（附加）：*

- ``<n> = {3,4}`` （设置 IN3 或 IN4 通道）

**可用的 Jupyter 和 API 宏：**

- 快速模拟通道 - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input 仅限（附加）：*

- 快速模拟通道 - ``RP_CH_3, RP_CH_4``


.. list-table::
    :widths: 52 124 81 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 适用版本
    * - ``ACQ:AXI:SOUR<n>:TRIG:FILL?`` |br| 示例： |br| ``ACQ:AXI:SOUR1:TRIG:FILL?`` > ``1``
      - C++: ``rp_AcqAxiGetBufferFillState(rp_channel_t channel, bool* state)`` |br| Python: ``rp_AcqAxiGetBufferFillState(<channel>)``
      - 指示深度存储器采集缓冲区是否已满。
      - 2.00-18 and up
    * - ``ACQ:AXI:SOUR<n>:Write:Pos?`` > ``<pos>`` |br| 示例： |br| ``ACQ:AXI:SOUR1:Write:Pos?`` > ``1024``
      - C++: ``rp_AcqAxiGetWritePointer(rp_channel_t channel, uint32_t* pos)`` |br| Python: ``rp_AcqAxiGetWritePointer(<channel>)``
      - 返回深度存储器采集写指针的当前位置。
      - 2.00-18 and up
    * - ``ACQ:AXI:SOUR<n>:Trig:Pos?`` > ``<pos>`` |br| 示例： |br| ``ACQ:AXI:SOUR1:Trig:Pos?`` > ``512``
      - C++: ``rp_AcqAxiGetWritePointerAtTrig(rp_channel_t channel, uint32_t* pos)`` |br| Python: ``rp_AcqAxiGetWritePointerAtTrig(<channel>)``
      - 返回触发到达时深度存储器采集写指针的 |br| 位置。
      - 2.00-18 and up
    * - ``ACQ:AXI:SOUR<n>:DATA:Start:N? <pos>,<size>`` |br| 示例： |br| ``ACQ:AXI:SOUR1:DATA:Start:N? 20,3`` > |br| ``{1.2,3.2,-1.2}``
      - C++: ``rp_AcqAxiGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)`` |br| ``rp_AcqAxiGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)`` |br| Python: ``rp_AcqAxiGetDataV(<channel>, <pos>, <size>, <buffer>)`` |br| ``rp_AcqAxiGetDataRaw(<channel>, <pos>, <size>, <buffer>)``
      - 从 ``pos`` 位置开始读取 ``count`` 个采样。 |br| **SCPI:** 返回值数组形式的文本数组或字节数组。 |br| 具体取决于 ``ACQ:AXI:DATA:UNITS`` 设置。 |br| **API:** 以指定单位从指定位置返回深度存储器缓冲区的 |br| 数据及所需大小。
      - 2.00-18 and up
    * - ''
      - Python: ``rp_AcqAxiGetDataVNP(<channel>, <pos>, <np_buffer>)`` (Numpy buffer ``dtype=np.float32``) |br| ``rp_AcqAxiGetDataRawNP(<channel>, <pos>, <np_buffer>)`` (Numpy buffer ``dtype=np.int16``)
      - 将捕获的 DMA 缓冲区数据从 ``pos`` 开始复制到传入的 NumPy 缓冲区 |br| 。复制数据的长度与 ``np_buffer`` 长度匹配。 |br| Numpy 缓冲区必须使用指定的 ``dtype`` 格式。 |br| 速度快于上述 Python 函数。
      - 2.05-37 and up
    * - ''
      - Python: ``rp_AcqAxiGetDataRawDirect(<channel>, <pos>, <size>)``
      - 返回不复制数据的内存区域（最快的方法）。 |br| 使用 ``frombuffer`` 函数提取数据。
      - 2.07-43 and up

|

.. _commands_dmg:

===============================
深度内存生成（DMG）
===============================

-------------
DMG 设置
-------------

**参数选项：**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<byte> = {0...}`` （单位：字节）
- ``<start> = {0...}`` （单位：字节）
- ``<end> = {0...}`` （单位：字节）
- ``<state> = {ON, OFF}`` 默认值：``OFF``
- ``<decimation> = {1, 2, 4, 8, 16, 17, 18, 19, ..., 65534, 65535, 65536}`` 默认值：``1``
- ``<array> = {value1, ...}`` 范围为 -1 至 1 的浮点数
- ``<enable> = {True, False}`` 默认值：``False``
- ``<start>, <end> = {byte}`` 保留内存的起始和结束地址

**可用的 Jupyter 和 API 宏：**

- Fast analog channels - ``RP_CH_1, RP_CH_2``


.. list-table::
    :widths: 59 124 81 20
    :header-rows: 1

    * - SCPI
      - API、Jupyter
      - 描述
      - 适用版本
    * - ``GEN:AXI:START?`` > ``<byte>`` |br| 示例： |br| ``GEN:AXI:START?`` > ``16777216``
      - C++: ``rp_GenAxiGetMemoryRegion(uint32_t *_start, uint32_t *_size)`` |br| Python: ``rp_GenAxiGetMemoryRegion()``
      - 返回深度内存区域的起始地址。 |br| API：同时返回内存区域大小。
      - 2.07-48 and up
    * - ``GEN:AXI:SIZE?`` > ``<byte>`` |br| 示例： |br| ``GEN:AXI:SIZE?`` > ``2097152``
      - C++: ``rp_GenAxiGetMemoryRegion(uint32_t *_start, uint32_t *_size)`` |br| Python: ``rp_GenAxiGetMemoryRegion()``
      - 获取深度内存模式的保留内存大小。 |br| **API：** 同时返回内存区域的起始地址。
      - 2.07-48 and up
    * - ``SOUR#:AXI:RESERVE`` > ``<start>,<end>`` |br| 示例： |br| ``SOUR1:AXI:RESERVE 2097152,2197152``
      - C++: ``rp_GenAxiReserveMemory(rp_channel_t channel, uint32_t start, uint32_t end)`` |br| Python: ``rp_GenAxiReserveMemory(<channel>, <start>, <end>)``
      - 在深度内存区域内为生成保留已分配区域 |br| （字节数）。
      - 2.07-48 and up
    * - ``SOUR#:AXI:RELEASE`` |br| 示例： |br| ``SOUR#:AXI:RELEASE``
      - C++: ``rp_GenAxiReleaseMemory(rp_channel_t channel)`` |br| Python: ``rp_GenAxiReleaseMemory(<channel>)``
      - 释放深度内存区域中为生成保留的内存。
      - 2.07-48 and up
    * - ``SOUR#:AXI:ENable <state>`` |br| 示例： |br| ``SOUR1:AXI:ENable ON``
      - C++: ``rp_GenAxiSetEnable(rp_channel_t channel, bool enable)`` |br| Python: ``rp_GenAxiSetEnable(<channel>, <enable>)``
      - 为指定通道启用深度内存生成。 |br| 必须预先保留内存区域。
      - 2.07-48 and up
    * - ``SOUR#:AXI:ENable?`` > ``<state>`` |br| 示例： |br| ``SOUR1:AXI:ENable?`` > ``ON``
      - C++: ``rp_GenAxiGetEnable(rp_channel_t channel, bool* enable)`` |br| Python: ``rp_GenAxiGetEnable(<channel>)``
      - 获取指定通道深度内存生成的启用状态。 |br| 通道。
      - 2.07-48 and up
    * - ``SOUR#:AXI:DEC <decimation>`` |br| 示例： |br| ``SOUR1:AXI:DEC 1``
      - C++: ``rp_GenAxiSetDecimationFactor(rp_channel_t channel, uint32_t decimation)`` |br| Python: ``rp_GenAxiSetDecimationFactor(<channel>, <decimation>)``
      - 设置深度内存生成的数据延迟模式值（生成抽取）。 |br|  每个采样点在 DAC 上保持 ``<decimation>`` 个时钟周期， |br| 从而有效降低输出采样率。
      - 2.07-48 and up
    * - ``SOUR#:AXI:DEC?`` > ``<decimation>`` |br| 示例： |br| ``SOUR1:AXI:DEC?`` > ``1``
      - C++: ``rp_GenAxiGetDecimationFactor(rp_channel_t channel, uint32_t* decimation)`` |br| Python: ``rp_GenAxiGetDecimationFactor(<channel>)``
      - 获取深度内存生成的数据延迟模式值（生成抽取）。 |br| 
      - 2.07-48 and up
    * - -
      - C++: ``rp_GenAxiWriteWaveform(rp_channel_t channel, float* buffer, uint32_t length)`` |br| Python: ``rp_GenAxiWriteWaveform(<channel>, <np_buffer>)``
      - 将数据从 NumPy 缓冲区复制到深度内存生成区域。数据必须采用 float 格式，缓冲区长度必须为预留 DMG 区域的一半（每个 float 会转换为两个 int16）；数值应位于满量程输出范围内（±1 V）。
      - 2.07-48 and up
    * - ``SOUR#:AXI:OFFSET#:DATA# <array>`` |br| 示例： |br| ``SOUR1:AXI:OFFSET0:DATA256 1,2,1,..``
      - C++: ``rp_GenAxiWriteWaveformOffset(rp_channel_t channel, uint32_t offset, float* buffer, uint32_t length)`` |br| Python: ``rp_GenAxiWriteWaveformOffset(<channel>, <offset>, <np_buffer>)``
      - 将数据从 NumPy 缓冲区复制到深度内存生成区域。数据必须采用 float 格式，缓冲区长度必须为预留 DMG 区域的一半（每个 float 会转换为两个 int16）；数值应位于满量程输出范围内（±1 V）。与前一个函数不同，此函数会在分隔位置添加偏移，以便分段写入数据。
      - 2.07-48 and up
    * - ``SOUR#:AXI:SET:CALIB`` |br| 示例： |br| ``SOUR1:AXI:SET:CALIB``
      - C++: ``rp_GenSetAmplitudeAndOffsetOrigin(rp_channel_t channel)`` |br| Python: ``rp_GenSetAmplitudeAndOffsetOrigin(<channel>)``
      - 将 DAC 校准值应用于 DMG 波形。
      - 2.07-48 and up

|

* :ref:`返回顶部 <commands_dmm>`
* :ref:`返回命令列表 <command_list>`

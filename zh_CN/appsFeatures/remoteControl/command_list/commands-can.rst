
.. _commands_can:

===
CAN
===

功能概览
------------------------

CAN（Controller Area Network）命令通过 Red Pitaya 扩展连接器提供 CAN 总线通信。可配置 CAN 接口、设置比特率和时序参数、管理过滤器，并为汽车和工业控制应用发送/接收 CAN 帧。


重要说明
----------------

* 使用 CAN 需要 FPGA 镜像 *v0.94*。
* 支持 CAN0 和 CAN1 接口。
* 正确配置比特率和采样点对可靠通信至关重要。
* 扩展连接器上需要硬件 CAN 收发器。


代码示例
-----------------

[待添加 - CAN 通信专用示例]


参数与命令表
-----------------------------

**参数选项：**

- ``<n> = {0,1}`` （设置 CAN0 或 CAN1 CAN 接口）
- ``<bool> = {OFF, ON}`` 默认值：``OFF``
- ``<state> = {ERROR_ACTIVE, ERROR_WARNING, ERROR_PASSIVE, BUS_OFF, STOPPED, SLEEPING}``
- ``<mode> = {LOOPBACK, LISTENONLY, 3_SAMPLES, ONE_SHOT, BERR_REPORTING}``
- ``<speed> = {1, 10000000}`` 比特率。
- ``<sp> = {0, 0.999}`` 采样点。
- ``<tq> = {unsigned integer}`` 时间量子，单位为 ns。
- ``<prop_seg> = {unsigned integer}`` 传播段。
- ``<phase_seg1> = {unsigned integer}`` 相位段 1。
- ``<phase_seg2> = {unsigned integer}`` 相位段 2。
- ``<sjw> = {unsigned integer}`` 同步跳转宽度。
- ``<brp> = {unsigned integer}`` 比特率预分频器。

- ``<limits> = {<tseg1_min>, <tseg1_max>, <tseg2_min>, <tseg2_max>, <sjw_max>, <brp_min>, <brp_max>, <brp_inc>}`` Constant:``1,16,1,8,4,1,256,1``
- ``<tseg1_min> = {unsigned integer}`` Time segment 1 minimum. Constant: ``1``
- ``<tseg1_max> = {unsigned integer}`` Time segment 1 maximum. Constant: ``16``
- ``<tseg2_min> = {unsigned integer}`` Time segment 2 minimum. Constant: ``1``
- ``<tseg2_max> = {unsigned integer}`` Time segment 2 maximum. Constant: ``8``
- ``<sjw_max> = {unsigned integer}`` Sinhronisation jump width maximum. Constant: ``4``
- ``<brp_min> = {unsigned integer}`` Bitrate per-scaler minimum. Constant: ``1``
- ``<brp_max> = {unsigned integer}`` Bitrate per-scaler maximum. Constant: ``256``
- ``<brp_inc> = {unsigned integer}`` Bitrate per-scaler increment. Constant: ``1``

- ``<clock> = {1...10000000}``，单位为 Hz。默认值：``10000000``
- ``<tx_err> = {unsigned integer}`` Tx 总线错误。
- ``<rx_err> = {unsigned integer}`` Rx 总线错误。
- ``<rs_ms> = {unsigned integer}`` 重启时间，单位为毫秒。``0`` = 关闭重启。默认值：``0``

- ``<timeout> = {unsigned integer}`` in milliseconds. Timeout when sending data. Needed if buffer is full ``0`` == timeout disabled

- ``<frame> = {<can_id>, <frame_header>, <is_extended>, <is_error>, <is_rtr>, {<buffer>}}`` CAN frame composition.
- ``<can_id> = {unsigned integer}`` Destination address on CAN bus
- ``<frame_header> = {unsigned integer}`` CAN frame header
- ``<is_extended> = {0,1}`` IDE bit. Normal (11-bit ID)/Extended (29-bit ID) CAN frame. ``0`` == Normal/CAN2.0A, ``1`` == Extended/CAN2.0B.
- ``<is_error> = {0,1}`` Error detected
- ``<is_rtr> = {0,1}`` RTR bit. Mark frame as remote transmission request. ``0`` == Send data, ``1`` == Request data.
- ``<buffer> = {XXX | XXX,XXX | XXX,XXX,XXX | XXX,...,XXX}`` Data buffer to transmit (from 0 to 8 Bytes). Data exceeding 8 bytes will be ignored.

- ``<filter> = {unsigned integer}`` CAN ID filter.
- ``<mask> = {unsigned integer}`` Filter mask.


**可用的 Jupyter 和 API 宏：**

- CAN 接口 - ``RP_CAN_0, RP_CAN_1``
- CAN 状态 - ``RP_CAN_STATE_ERROR_ACTIVE, RP_CAN_STATE_ERROR_WARNING, RP_CAN_STATE_ERROR_PASSIVE, RP_CAN_STATE_BUS_OFF, RP_CAN_STATE_STOPPED, RP_CAN_STATE_SLEEPING``
- CAN 模式 - ``RP_CAN_MODE_LOOPBACK, RP_CAN_MODE_LISTENONLY, RP_CAN_MODE_3_SAMPLES, RP_CAN_MODE_ONE_SHOT, RP_CAN_MODE_BERR_REPORTING``
- CAN 错误：

    - ``RP_HW_CAN_OK`` - 成功
    - ``RP_HW_CAN_ESI`` - 启动接口失败
    - ``RP_HW_CAN_EST`` - 停止接口失败
    - ``RP_HW_CAN_ERI`` - 重启接口失败
    - ``RP_HW_CAN_EUI`` - 未知接口
    - ``RP_HW_CAN_EBS`` - 设置或获取比特率和采样点失败
    - ``RP_HW_CAN_EBT`` - 设置或获取比特时序失败
    - ``RP_HW_CAN_EGF`` - 获取时钟参数失败
    - ``RP_HW_CAN_EGE`` - 获取错误计数器失败
    - ``RP_HW_CAN_ERT`` - 设置或获取重启时间失败
    - ``RP_HW_CAN_EGS`` - 获取当前接口状态失败
    - ``RP_HW_CAN_ECM`` - 获取或设置控制器模式失败
    - ``RP_HW_CAN_ECU`` - 不支持控制器模式
    - ``RP_HW_CAN_ESO`` - 打开套接字失败
    - ``RP_HW_CAN_ESC`` - 关闭套接字失败
    - ``RP_HW_CAN_ESA`` - 失败：套接字已打开
    - ``RP_HW_CAN_ESB`` - 绑定套接字失败
    - ``RP_HW_CAN_ESN`` - 失败：套接字未打开
    - ``RP_HW_CAN_ESD`` - 失败：缺少数据
    - ``RP_HW_CAN_ESBO`` - 失败：发送缓冲区溢出
    - ``RP_HW_CAN_ESTE`` - 失败：达到超时
    - ``RP_HW_CAN_ESPE`` - 失败：轮询错误
    - ``RP_HW_CAN_ESE`` - 失败：发送错误
    - ``RP_HW_CAN_ESFA`` - 添加过滤器失败：过滤器已存在于列表中
    - ``RP_HW_CAN_ESFS`` - 应用过滤器失败
    - ``RP_HW_CAN_ESEF`` - 设置错误处理失败
    - ``RP_HW_CAN_ESR`` - 从套接字读取帧失败


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 85 112 77 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 适用版本
    * - ``CAN:FPGA <bool>`` |br| 示例： |br| ``CAN:FPGA ON``
      - C++: ``rp_CanSetFPGAEnable(bool enable)`` |br| Python: ``rp_CanSetFPGAEnable(enable)``
      - 启用从 CAN 控制器到 GPIO 的 FPGA 转发。
      - 2.00-30 及更高版本
    * - ``CAN:FPGA?`` > ``<bool>`` |br| 示例： |br| ``CAN:FPGA?`` > ``ON``
      - C++: ``rp_CanGetFPGAEnable(bool *state)`` |br| Python: ``rp_CanGetFPGAEnable()``
      - 获取从 CAN 控制器到 GPIO 的 FPGA 转发状态。
      - 2.00-30 and up
    * - ``CAN<n>:START`` |br| 示例： |br| ``CAN0:START``
      - C++: ``rp_CanStart(rp_can_interface_t interface)`` |br| Python: ``rp_CanStart(<interface>)``
      - 将指定接口状态设置为 UP。 |br| 启动或重启接口前必须设置比特率。
      - 2.00-30 and up
    * - ``CAN<n>:STOP`` |br| 示例： |br| ``CAN0:STOP``
      - C++: ``rp_CanStop(rp_can_interface_t interface)`` |br| Python: ``rp_CanStop(<interface>)``
      - 将指定接口状态设置为 DOWN。
      - 2.00-30 and up
    * - ``CAN<n>:RESTART`` |br| 示例： |br| ``CAN0:RESTART``
      - C++: ``rp_CanRestart(rp_can_interface_t interface)`` |br| Python: ``rp_CanRestart(<interface>)``
      - 重启指定接口。 |br| 启动或重启接口前必须设置比特率。
      - 2.00-30 and up
    * - ``CAN<n>:STATE?`` > ``<state>`` |br| 示例： |br| ``CAN0:STATE?`` > ``ERROR_ACTIVE``
      - C++: ``rp_CanGetState(rp_can_interface_t interface, rp_can_state_t *state)`` |br| Python: ``rp_CanGetState(<interface>)``
      - 返回 CAN 接口当前状态。 |br| ``ERROR_ACTIVE`` - RX/TX error count < 96 |br| ``ERROR_WARNING`` - RX/TX error count < 128 |br| ``ERROR_PASSIVE`` - RX/TX error count < 256 |br| ``BUS_OFF`` - RX/TX error count >= 256 |br| ``STOPPED`` - 设备已停止 |br| ``SLEEPING`` - 设备处于休眠状态
      - 2.00-30 and up
    * - ``CAN<n>:BITRate <speed>`` |br| 示例： |br| ``CAN0:BITRate 200000``
      - C++: ``rp_CanSetBitrate(rp_can_interface_t interface, uint32_t bitRate)`` |br| Python: ``rp_CanGetStateName(<state>)``
      - 设置指定接口的比特率（Hz）。采样点会 |br| 自动设置。
      - 2.00-30 and up
    * - ``CAN<n>:BITRate:SP <speed>,<sp>`` |br| 示例： |br| ``CAN0:BITRate:SP 200000,0.8``
      - C++: ``rp_CanSetBitrateAndSamplePoint(rp_can_interface_t interface, uint32_t bitRate, float samplePoint)`` |br| Python: ``rp_CanSetBitrateAndSamplePoint(<interface>, <bitRate>, <samplePoint>)``
      - 设置指定接口的比特率（Hz）和采样点（0.1%）。
      - 2.00-30 and up
    * - ``CAN<n>:BITRate:SP?`` > ``<speed>,<sp>`` |br| 示例： |br| ``CAN0:BITRate:SP?`` > ``200000,0.8``
      - C++: ``rp_CanGetBitrateAndSamplePoint(rp_can_interface_t interface, uint32_t *bitRate, float *samplePoint)`` |br| Python: ``rp_CanGetBitrateAndSamplePoint(<interface>)``
      - 显示实际比特率 ``speed``in bits/sec and the sample-point ``sp`` |br| 范围为 0.000...0.999. |br| 如果内核启用了位定时参数计算 |br| (CONFIG_CAN_CALC_BITTIMING=y), 则可以通过设置 |br| the "bitrate" 参数定义位定时. 也可以指定 "sample-point" can be specified. |br| 默认值为 0.000 assuming CIA-recommended sample-points.
      - 2.00-30 and up
    * - ``CAN<n>:BITTiming <tq>,<prop_seg>,<phase_seg1>,<phase_seg2>,<sjw>,<brp>`` |br| 示例： |br| ``CAN0:BITTiming 1000,1,2,1,1,10``
      - C++: ``rp_CanSetBitTiming(rp_can_interface_t interface, rp_can_bittiming_t bitTiming)`` |br| Python: ``rp_CanSetBitTiming(<interface>, <bitTiming>)``
      - 设置位定时参数。 |br| `位定时信息 <https://en.wikipedia.org/wiki/CAN_bus#Bit_timing>`_
      - 2.00-30 and up
    * - ``CAN<n>:BITTiming?`` > ``<tq>,<prop_seg>,<phase_seg1>,<phase_seg2>,<sjw>,<brp>`` |br| 示例： |br| ``CAN0:BITTiming?`` > ``1000,1,2,1,1,10``
      - C++: ``rp_CanGetBitTiming(rp_can_interface_t interface, rp_can_bittiming_t *bitTiming)`` |br| Python: ``rp_CanGetBitTiming(<interface>, <bitTiming>)``
      - 显示时间量 ``tq`` in ns, propagation segment ``prop_seg``, |br| phase buffer segment 1 and 2 ``phase_seg1, phase_seg2``, and the |br| synchronisation jump width ``sjw`` in units of time quanta. |br| 这些设置以与硬件无关的格式定义 CAN 位定时 |br| proposed by Bosch CAN 2.0 specification (Chapter 8).
      - 2.00-30 and up
    * - ``CAN<n>:BITTiming:Limits?`` > ``<limits>`` |br| 示例： |br| ``CAN0:BITTiming:Limits?`` > ``1,16,1,8,4,1,256,1``
      - C++: ``rp_CanGetBitTimingLimits(rp_can_interface_t interface, rp_can_bittiming_limits_t *bitTiming)`` |br| Python: ``rp_CanGetBitTimingLimits(<interface>, <bitTiming>)``
      - 显示 CAN 控制器位定时常量 ("sja1000"), the |br| minimum and maximum values of time segment 1 and 2, the synchronisation |br| jump width ``swj`` in time quanta (``tq``) units, the bit rate |br| prescaler ``brp`` and the CAN system clock frequency in Hz. |br| These constants can be used for user defined (non-standard) bit timing |br| calculation algorithms in user space.
      - 2.00-30 and up
    * - ``CAN<n>:CLOCK?`` > ``<clock>`` |br| 示例： |br| ``CAN0:CLOCK?`` > ``10000000``
      - C++: ``rp_CanGetClockFreq(rp_can_interface_t interface, uint32_t *freq)`` |br| Python: ``rp_CanGetClockFreq(<interface>)``
      - 返回 CAN 时钟频率（单位：Hz）。
      - 2.00-30 and up
    * - ``CAN<n>:BUS:ERROR?`` > ``<tx_err>,<rx_err>`` |br| 示例： |br| ``CAN0:BUS:ERROR?`` > ``0,0``
      - C++: ``rp_CanGetBusErrorCounters(rp_can_interface_t interface, uint16_t *tx, uint16_t *rx)`` |br| Python: ``rp_CanGetBusErrorCounters(<interface>)``
      - 返回 RX 和 TX 总线上的错误数量。
      - 2.00-30 and up
    * - ``CAN<n>:Restart:Time <rs_ms>`` |br| 示例： |br| ``CAN0:Restart:Time 10``
      - C++: ``rp_CanSetRestartTime(rp_can_interface_t interface, uint32_t ms)`` |br| Python: ``rp_CanSetRestartTime(<interface>, <ms>)``
      - 自动重启延迟时间。如果设置为非零值，CAN 控制器将在总线关闭状态下于指定延迟时间后自动重启（单位：毫秒）。 |br| 默认设置为 ``0`` （OFF）。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Restart:Time?`` > ``<rs_ms>`` |br| 示例： |br| ``CAN0:Restart:Time?`` > ``10``
      - C++: ``rp_CanGetRestartTime(rp_can_interface_t interface, uint32_t *ms)`` |br| Python: ``rp_CanGetRestartTime(<interface>)``
      - 返回当前重启延迟时间（单位：ms）。
      - 2.00-30 及更高版本
    * - ``CAN<n>:MODE <mode>,<bool>`` |br| 示例： |br| ``CAN0:MODE LOOPBACK,ON``
      - C++: ``rp_CanSetControllerMode(rp_can_interface_t interface, rp_can_mode_t mode, bool state)`` |br| Python: ``rp_CanSetControllerMode(<interface>, <mode>, <state>)``
      - 设置控制器模式： |br| ``LOOPBACK`` - TX 与 RX 之间的内部连接 |br| ``LISTENONLY`` - 禁用 TX，仅 RX，用于 CAN 总线监控 |br| ``3_SAMPLES`` -  三重采样模式 |br| ``ONE_SHOT`` - 单次模式 |br| ``BERR_REPORTING`` - 总线错误报告 |br| 可以同时选择多个模式。
      - 2.00-30 及更高版本
    * - ``CAN<n>:MODE? <mode>`` > ``<bool>`` |br| 示例： |br| ``CAN0:MODE? LOOPBACK`` > ``ON``
      - C++: ``rp_CanGetControllerMode(rp_can_interface_t interface, rp_can_mode_t mode, bool *state)`` |br| Python: ``rp_CanGetControllerMode(<interface>, <mode>)``
      - 检查所选模式的状态。
      - 2.00-30 及更高版本
    * - ``CAN<n>:OPEN`` |br| 示例： |br| ``CAN0:OPEN``
      - C++: ``rp_CanOpen(rp_can_interface_t interface)`` |br| Python: ``rp_CanOpen(<interface>)``
      - 为指定接口打开套接字连接。
      - 2.00-30 及更高版本
    * - ``CAN<n>:CLOSE`` |br| 示例： |br| ``CAN0:CLOSE``
      - C++: ``rp_CanClose(rp_can_interface_t interface)`` |br| Python: ``rp_CanClose(<interface>)``
      - 关闭已打开的连接。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Send<can_id> <buffer>`` |br| 示例： |br| ``CAN0:Send123 1,2,3``
      - C++: ``rp_CanSend(rp_can_interface_t interface, uint32_t canId, unsigned char *data, uint8_t dataSize,`` |br| ``bool isExtended, bool rtr, uint32_t timeout)`` |br| Python: ``rp_CanSend(<interface>, <canId>, <data>, <dataSize>, <isExtended>, <rtr>, <timeout>)``
      - 将帧发送到指定地址 ``can_id``。 |br| 超过 8 字节的数据将被忽略。 |br| C++、Python：可选择启用 RTR、扩展帧并添加超时（见下文）。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Send<can_id>:RTR <buffer>`` |br| 示例： |br| 示例： |br| ``CAN0:Send123 1,2,3``
      - C++: '' (见上文) |br| Python: '' (见上文)
      - 将帧发送到指定地址 ``can_id``，并标记为“远程传输请求”（``rtr`` == true）。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Send<can_id>:Timeout<timeout> <buffer>`` |br| 示例： |br| ``CAN0:Send123:Timeout2000 1,2,3``
      - C++: '' (见上文) |br| Python: '' (见上文)
      - 将帧发送到指定地址 ``can_id``，当发送缓冲区已满时使用 ``timeout`` 进行发送。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Send<can_id>:Ext`` |br| 示例： |br| ``CAN0:Send123:Ext 1,2,3``
      - C++: '' (见上文) |br| Python: '' (见上文)
      - 将帧发送到指定地址 ``can_id``，使用扩展数据帧（``isExtended`` == True）。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Send<can_id>:Timeout<timeout>:Ext <buffer>`` |br| 示例： |br| ``CAN0:Send123:Timeout2000:Ext 1,2,3``
      - C++: '' (见上文) |br| Python: '' (见上文)
      - 将帧发送到指定地址 ``can_id``，使用扩展数据帧（``isExtended`` == True）；当发送缓冲区已满时使用 ``timeout`` 进行发送。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Send<can_id>:Timeout<timeout>:RTR <buffer>`` |br| 示例： |br| ``CAN0:Send123:Timeout2000:RTR 1,2,3``
      - C++: '' (见上文) |br| Python: '' (见上文)
      - 将帧发送到指定地址 ``can_id``，并标记为“远程传输请求”（``rtr`` == true）。 |br| 当发送缓冲区已满时使用 ``timeout`` 进行发送。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Send<can_id>:Ext:RTR`` |br| 示例： |br| ``CAN0:Send123:Ext:RTR 1,2,3``
      - C++: '' (见上文) |br| Python: '' (见上文)
      - 将帧发送到指定地址 ``can_id``，使用扩展数据帧（``isExtended`` == True），并标记为“远程传输请求”（``rtr`` == true）。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Send<can_id>:Timeout<timeout>:Ext:RTR <buffer>`` |br| 示例： |br| ``CAN0:Send123:Timeout2000:Ext:RTR 1,2,3``
      - C++: '' (见上文) |br| Python: '' (见上文)
      - 将帧发送到指定地址 ``can_id``，使用扩展数据帧（``isExtended`` == True），并标记为“远程传输请求”（``rtr`` == true）。 |br| 当发送缓冲区已满时使用 ``timeout`` 进行发送。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Read?`` > ``<frame>`` |br| 示例： |br| ``CAN0:Read?`` > ``123,123,0,0,0,3,{1,2,3}``
      - C++: ``rp_CanRead(rp_can_interface_t interface, uint32_t timeout, rp_can_frame_t *frame)`` |br| Python: ``rp_CanRead(<interface>, <timeout>, <frame>)``
      - 从指定 CAN 接口读取 1 个帧。 |br| C++, Python: 可选择添加超时 （见下文）。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Read:Timeout<timeout>?`` > ``<frame>`` |br| 示例： |br| ``CAN0:Read:Timeout2000?`` > ``123,123,0,0,0,3,{1,2,3}``
      - C++: '' (见上文) |br| Python: '' (见上文)
      - 从指定 CAN 接口读取 1 个帧。 如果未接收到帧 |br| 在 ``timeout`` 时间内，则返回空帧。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Filter:Add <filter>,<mask>`` |br| 示例： |br| ``CAN0:Filter:Add 0,0``
      - C++: ``rp_CanAddFilter(rp_can_interface_t interface, uint32_t filter, uint32_t mask)`` |br| Python: ``rp_CanAddFilter(<interface>, <filter>, <mask>)``
      - 将指定的“ID filter” ``filter``（掩码为 ``mask``）添加到过滤器列表。添加完所有过滤器后，必须调用 ``CAN<n>:Filter:Set`` 将过滤器应用到套接字。 |br| 过滤器匹配条件为 ``<received_can_id> & mask == filter & mask``
      - 2.00-30 及更高版本
    * - ``CAN<n>:Filter:Remove <filter>,<mask>`` |br| 示例： |br| ``CAN0:Filter:Remove 0,0``
      - C++: ``rp_CanRemoveFilter(rp_can_interface_t interface, uint32_t filter, uint32_t mask)`` |br| Python: ``rp_CanRemoveFilter(<interface>, <filter>, <mask>)``
      - 从指定 CAN 接口的过滤器列表中删除指定的“ID filter”。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Filter:Clear`` |br| 示例： |br| ``CAN0:Filter:Clear``
      - C++: ``rp_CanClearFilter(rp_can_interface_t interface)`` |br| Python: ``rp_CanClearFilter(<interface>)``
      - 从指定 CAN 接口的过滤器列表中移除所有过滤器。
      - 2.00-30 及更高版本
    * - ``CAN<n>:Filter:Set`` |br| 示例： |br| ``CAN0:Filter:Set``
      - C++: ``rp_CanSetFilter(rp_can_interface_t interface, bool isJoinFilter)`` |br| Python: ``rp_CanSetFilter(<interface>, <isJoinFilter>)``
      - 将 ID 过滤器列表应用到指定 CAN 接口的套接字连接。
      - 2.00-30 及更高版本
    * - ``CAN<n>:SHOW:ERROR`` |br| 示例： |br| ``CAN0:SHOW:ERROR``
      - C++: ``rp_CanShowErrorFrames(rp_can_interface_t interface, bool enable)`` |br| Python: ``rp_CanShowErrorFrames(<interface>, <enable>)``
      - 启用此模式后，所有错误都会转换为带有 |br| 错误帧标记的数据帧。
      - 2.00-30 及更高版本

|

* :ref:`返回顶部 <commands_can>`
* :ref:`返回命令列表 <command_list>`

.. _multiboard_stream:

#########################
多板 Streaming
#########################

同时从多个 Red Pitaya 板卡传输数据，以创建多通道采集和信号生成系统。

.. contents:: 目录
    :local:
    :backlinks: top

|

概述
*********

要同时从多个 Red Pitaya 板卡传输数据，请在每块板卡上启动 Streaming 应用。可以通过 Web 界面完成，也可以加载 ``stream_app`` FPGA 镜像并通过 SSH 运行 ``streaming-server`` 命令。然后将 :ref:`桌面客户端应用 <stream_desktop_app>` 或 :ref:`命令行客户端 <stream_command_client>` 下载到计算机。

桌面应用和命令行客户端都会检测同一本地网络中运行 Streaming 应用的所有 Red Pitaya 板卡，并允许同时启动或停止所有板卡的 Streaming 过程。

|

主要功能
=============

* **自动检测板卡：** 客户端自动发现本地网络中的所有板卡
* **同步控制：** 同时启动和停止所有板卡的 Streaming
* **多通道采集：** 合并多个板卡的通道（例如 2 块板卡 = 4 个通道，4 块板卡 = 8 个通道）
* **可扩展系统：** 增加板卡以扩展通道数量
* **独立配置：** 每块板卡可以使用不同设置

|

设置步骤
****************

步骤 1：准备 Red Pitaya 板卡
===================================

对系统中的每块 Red Pitaya 板卡：

1. **使用路由器或网络交换机连接到同一本地网络**
   
   * 所有板卡和运行客户端的计算机都必须连接到同一路由器或交换机
   * 板卡与计算机之间的直接以太网连接**无法**工作——应用需要路由器或交换机来自动检测板卡
   * 每块板卡会从路由器的 DHCP 服务器获取 IP 地址

2. **确保每块板卡都有唯一 IP 地址**
3. **加载 Streaming 应用：**
   
   * 通过 Web 界面：打开 Streaming 应用
   * 通过 SSH：运行 ``overlay.sh stream_app && streaming-server``

4. **确认应用正在运行** （LED 2 常亮，LED 0 闪烁）

|

步骤 2：配置每块板卡
==============================

分别配置每块板卡的 Streaming 参数：

* Set :ref:`ADC configuration <stream_adc_config>` (sampling rate, channels, resolution)
* Set :ref:`DAC configuration <stream_dac_config>` if needed
* Configure :ref:`Memory settings <stream_memory_config>` (block size, memory allocation)

.. note::

    为实现同步多通道采集，所有板卡应使用相同的采样率和分辨率。

|

步骤 3：安装 Streaming 客户端
==================================

下载并安装以下任一客户端：

* :ref:`桌面客户端应用 <stream_desktop_app>` - 用于基于 GUI 的控制
* :ref:`命令行客户端 <stream_command_client>` - 用于脚本和自动化

客户端会自动发现本地网络中运行 Streaming 应用的所有板卡。

.. note::

    确保所有板卡都连接到路由器，并且计算机防火墙或杀毒软件允许客户端应用进行网络通信（端口 :ref:`18900-18903 <stream_port_numbers>`）。

|

步骤 4：启动 Streaming
=========================

**使用桌面客户端：**

1. 打开桌面应用
2. 所有检测到的板卡都会显示在板卡列表中
3. 选择要进行 Streaming 的板卡
4. 单击“Start All”，同时从所有选定板卡开始 Streaming

**使用命令行客户端：**

命令行客户端可以自动检测多个板卡并从中传输数据。具体命令请参见 :ref:`命令行客户端文档 <stream_command_client>`。

|

硬件同步
*************************

对于需要板卡之间精确时间同步的应用，Red Pitaya 提供两种硬件同步方案，确保多板之间进行相位对齐的数据采集：

* **X-channel 系统** - 使用 SATA 或 USB-C 线缆的经济型菊链同步，适合中高采样率下的 2-3 块板卡。
* **X-channel 2.0（Click Shield）同步** - 使用专用 LVDS 缓冲器的专业时钟分配，推荐用于更大型系统（4 块及以上板卡）和最高采样率。

两种系统都可为波束成形、相位敏感测量和多通道信号处理等应用提供同步多板采集。

**完整的硬件同步设置、规格和比较** 请参见 :ref:`多板同步文档 <multiboard_sync>`。

.. note::

    基本多板 Streaming **不要求** 硬件同步。没有硬件同步时，Streaming 客户端仍可检测和控制多个板卡，但板卡之间的数据采集不会相位对齐。

|

网络注意事项
***********************

为了获得最佳多板 Streaming 性能：

路由器配置
=====================

1. **使用专用网络交换机或路由器（必需）：** 
   
   * **板卡检测所必需** - 直接以太网连接无法工作
   * 所有板卡必须连接到同一路由器或交换机才能自动发现
   * 减少网络拥塞
   * 提供稳定连接
   * 支持完整的 1 Gbit 速率

2. **分配静态 IP 地址：** 防止 IP 冲突并简化板卡识别

3. **服务质量（QoS）：** 如果可用，请提高 Streaming 流量优先级

|

网络带宽
==================

从多个板卡进行 Streaming 时，请考虑网络总带宽：

.. math::

    \text{Total bandwidth} = N_{boards} \times f_S \times N_{channels} \times Bps

其中：

* :math:`N_{boards}` - Red Pitaya 板卡数量
* :math:`f_S` - 采样频率
* :math:`N_{channels}` - 每块板卡的活动通道数
* :math:`Bps` - 每个采样的字节数（8 位为 1，16 位为 2）

**Example:** 2 boards, 62.5 MS/s, 2 channels each, 16-bit:

.. math::

    \text{Total} = 2 \times 62,500,000 \times 2 \times 2 = 500,000,000 \text{ Bytes/s} = 500 \text{ MB/s}

此配置超过以下两项限制：

* **1 Gbit Ethernet capacity** (~125 MB/s) - Network bottleneck
* **Per-board streaming limits** (~62.5 MB/s per board) - See :ref:`Data Streaming Limitations <streaming_limits>`

此时必须降低采样率或减少通道数。有关每块板卡限制和带宽计算的详细信息，请参见 :ref:`数据 Streaming 限制文档 <streaming_limits>`。

|

性能优化
*************************

要最大限度提升多板卡流传输性能：

降低每块板卡的数据速率
============================

1. **降低采样率：** 尽可能使用抽取
2. **减少通道：** 禁用未使用的通道
3. **8 位分辨率：** 不需要 16 位精度时使用
4. **RAW 格式：** 跳过 VOLTS 转换

|

优化网络
=================

1. **使用千兆以太网：** 确保所有网络组件支持 1 Gbit 或更高速度
2. **使用高质量线缆：** 使用 Cat 5e 或 Cat 6 线缆
3. **减少跳数：** 将板卡直接连接到同一交换机
4. **专用网络：** 将 Streaming 流量与其他网络活动隔离

|

错开 Streaming 启动时间
========================

如果同时启动所有板卡导致网络拥塞，可以考虑将启动时间错开几毫秒。
这有助于分散初始数据包突发流量。

.. note::

    这需要自定义 Streaming 客户端。

|

故障排除
****************

未检测到板卡
====================

**问题：** 客户端未显示所有板卡

**解决方案：** 

1.  **检查网络拓扑** —— 板卡必须通过路由器或交换机连接。计算机与板卡之间的直接以太网连接无法工作
2.  **确认所有板卡位于同一网络子网**
3.  **检查防火墙/杀毒软件设置** —— 确保允许 Python、C++ 和流传输客户端访问网络（端口 :ref:`18900-18903 <stream_port_numbers>`）
   
    如果看到如下错误：
    
    .. code-block:: shell-session

        Search: DONE
        Found boards:
        
    或：
    
    .. code-block:: shell-session

        Host not found
        The client did not connect
    
    防火墙或杀毒软件可能阻止了网络通信。请将 Python、C++ 和流传输客户端应用程序加入白名单。最简单的解决方法是多运行几次程序，然后
    检查防火墙/杀毒软件日志，确认它是否阻止了该应用程序，并为其创建例外规则（请在安全软件文档中查找“网络访问故障排除”“解决受阻通信”等内容）。

4.  **确保所有板卡都在运行流传输应用程序** （LED 2 常亮，LED 0 闪烁）
5.  **尝试从计算机 ping 每块板卡**
6.  **在受影响的板卡上重新启动流传输应用程序**

|

数据丢失
==========

**问题：** 部分板卡丢包或数据缺失

**解决方案：**

1. 降低总网络带宽占用（降低采样率、减少通道）
2. 检查网线质量和连接情况
3. 使用质量更高的网络交换机
4. 增大每块板卡的 :ref:`块大小 <stream_memory_config>`
5. 监控网络流量以识别瓶颈

|

使用场景
**********

4 通道采集（2 块板卡）
==================================

* **Setup:** 2× STEMlab 125-14 (2 channels each)
* **Result:** 4-channel synchronized acquisition
* **Example:** Quadrature signal analysis, 3-phase power monitoring

|

8 通道采集（4 块板卡）
==================================

* **Setup:** 4× STEMlab 125-14 (2 channels each)
* **Result:** 8-channel synchronized acquisition
* **Example:** Multi-sensor arrays, acoustic beamforming

|

16 通道采集（4× 4 输入板卡）
===========================================

* **Setup:** 4× STEMlab 125-14 4-Input (4 channels each)
* **Result:** 16-channel synchronized acquisition
* **Example:** Large sensor arrays, multi-channel FFT analysis

|

后续步骤
***********

* Set up hardware synchronization with :ref:`X-channel system <x-ch_streaming>`
* Review :ref:`Data Streaming Limitations <streaming_limits>` for bandwidth calculations
* Try the :ref:`Desktop client application <stream_desktop_app>` for easy multiboard control
* Learn about :ref:`Command line client <stream_command_client>` for automated multiboard streaming

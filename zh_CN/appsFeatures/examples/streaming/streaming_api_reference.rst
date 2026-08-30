.. _streaming_api_reference:

#########################
Streaming API 参考
#########################

Red Pitaya Streaming 客户端库的完整 API 文档。本库支持 Red Pitaya 与计算机之间的高性能数据传输。

.. note::

    Streaming 客户端库运行在您的**计算机**上（而不是 Red Pitaya 上），通过 TCP/IP 与运行在 Red Pitaya 上的 Streaming 服务器通信。

.. contents:: Table of contents
    :depth: 2
    :local:
    :backlinks: top

|

概述
*********

Streaming API 提供两个用于双向数据传输的主要客户端类：

* **ADCStreamClient** - 将 Red Pitaya ADC 输入数据传输到计算机
* **DACStreamClient** - 将波形从计算机传输到 Red Pitaya DAC 输出

两个类都采用基于回调的架构，实现高效、非阻塞的数据传输。

**架构：**

.. code-block:: text

    Computer                          Red Pitaya
    +------------------+             +-----------------+
    |  Your Program    |             | Streaming Server|
    |                  |   TCP/IP    |                 |
    |  ADCStreamClient |------------>|  FPGA -> ADC    |
    |  DACStreamClient |<------------|  DAC <- FPGA    |
    |                  |             |                 |
    |  Callback Class  |             |  Deep Memory    |
    +------------------+             +-----------------+

|

安装
*************

**Python:**

``rp_stream`` Python 库包含在 :ref:`Streaming 命令行客户端 <streaming_pc_clients>` 中。请从 Red Pitaya 上的 Data Stream control 应用下载命令行客户端。

**C++:**

C++ Streaming 库包含在 :ref:`Streaming 命令行客户端 <streaming_pc_clients>` 中。请从 Red Pitaya 上的 Data Stream control 应用下载命令行客户端。

|

类参考
****************

.. py:class:: ADCStreamClient
    
    ADC Streaming 操作的主要客户端类。

.. py:class:: ADCCallback
    
    ADC Streaming 事件的基础回调类。

.. py:class:: ADCPack
    
    包含 ADC 通道样本的数据包结构。

.. py:class:: DACStreamClient
    
    DAC Streaming 操作的主要客户端类。

.. py:class:: DACCallback
    
    DAC Streaming 事件的基础回调类。

|

ADC 流式传输 API
******************

ADCStreamClient 类
======================

用于将 Red Pitaya ADC 通道数据传输到计算机的主要类。

**基本用法：**

.. tabs::

    .. tab:: Python

        .. code-block:: python

            import rp_stream as streaming
            
            # Create client
            client = streaming.ADCStreamClient()
            
            # Set callback handler
            callback = MyADCCallback()
            client.setReceiveDataCallback(callback.__disown__())
            
            # Connect (auto-discovery)
            client.connect()
            
            # Configure streaming
            client.sendConfig('adc_decimation', '256')
            client.sendConfig('channel_state_1', 'ON')
            client.sendConfig('channel_state_2', 'ON')
            
            # Start streaming
            client.startStreaming()
            client.wait()

    .. tab:: C++

        .. code-block:: cpp

            #include "adc_streaming.h"
            #include "callbacks.h"
            
            // Create callback handler
            class MyCallback : public ADCCallback {
                void receivePack(ADCStreamClient* client, ADCPack& pack) override {
                    // Process incoming data
                }
            };
            
            // Create client
            ADCStreamClient client;
            MyCallback callback;
            client.setReceiveDataCallback(&callback);
            
            // Connect (auto-discovery)
            client.connect();
            
            // Configure streaming
            client.sendConfig("adc_decimation", "256");
            client.sendConfig("channel_state_1", "ON");
            client.sendConfig("channel_state_2", "ON");
            
            // Start streaming
            client.startStreaming();
            client.wait();

|

连接方法
-------------------

.. method:: connect() -> bool

    使用自动发现连接到单个 Red Pitaya。自动搜索网络中的可用 Red Pitaya 板卡并连接到找到的第一块板卡。
    
    :returns: 连接成功返回 ``True``，否则返回 ``False``
    :rtype: bool
    
    **示例：**
    
    .. code-block:: python
    
        if not client.connect():
            print("Connection failed")
    
    .. note::
    
        当前仅连接单个主机。进行多板采集时，请使用 ``connect(hosts)`` 方法。

.. method:: connect(hosts: list[str]) -> bool
    :no-index:

    连接多个 Red Pitaya 板卡进行同步多板采集（主从配置）。列表中的第一块板卡作为主板。
    
    :param hosts: 主机名或 IP 地址列表（第一项为主板，其余为从板）
    :type hosts: list[str]
    :returns: 所有连接成功时返回 ``True``
    :rtype: bool
    
    **示例：**
    
    .. code-block:: python
    
        # Master board first, then slaves
        boards = ["200.0.0.7", "200.0.0.8"]
        client.connect(boards)
        
        # Configure master board
        client.sendConfig(boards[0], 'adc_decimation', '64')
        client.sendConfig(boards[0], 'channel_state_1', 'ON')
        
        # Copy config to slave
        config = client.getFileConfig(boards[0])
        client.sendFileConfig(boards[1], config)

|

配置方法
----------------------

.. method:: sendConfig(key: str, value: str) -> bool

    向 Streaming 服务器发送配置参数。
   
    :param key: 配置参数名称
    :type key: str
    :param value: 字符串形式的参数值
    :type value: str
    :returns: 配置被接受时返回 ``True``
    :rtype: bool
   
    **常用参数：**
   
    .. list-table::
        :header-rows: 1
        :widths: 30 50 20
    
        * - 键
          - 说明
          - 取值
        * - ``adc_decimation``
          - 采样率除数（1–65536）
          - "1" - "65536"
        * - ``adc_pass_mode``
          - 目标模式
          - "NET", "FILE"
        * - ``channel_state_1``
          - 启用/禁用通道 1
          - "ON", "OFF"
        * - ``channel_state_2``
          - 启用/禁用通道 2
          - "ON", "OFF"
        * - ``channel_state_3``
          - 启用/禁用通道 3（250-12）
          - "ON", "OFF"
        * - ``channel_state_4``
          - 启用/禁用通道 4（250-12）
          - "ON", "OFF"
        * - ``block_size``
          - 网络数据包大小（字节）
          - "2048" - "2097152"
        * - ``adc_size``
          - FPGA 缓冲区大小（字节）
          - "1048576" - "104857600"
   
    **示例：**
   
    .. code-block:: python
   
        client.sendConfig('adc_decimation', '256')
        client.sendConfig('channel_state_1', 'ON')
        client.sendConfig('block_size', '131072')

.. method:: sendConfig(host: str, key: str, value: str) -> bool
    :no-index:

    在多板设置中向指定板卡发送配置。
   
    :param host: 目标 Red Pitaya 主机名
    :type host: str
    :param key: 配置参数名称
    :type key: str
    :param value: 参数值
    :type value: str
    :returns: 配置被接受时返回 ``True``
    :rtype: bool

.. method:: getConfig(key: str) -> str

    从服务器获取当前配置值。
   
    :param key: 配置参数名称
    :type key: str
    :returns: 字符串形式的当前值
    :rtype: str
   
    **示例：**
   
    .. code-block:: python
   
        decimation = client.getConfig('adc_decimation')
        print(f"Current decimation: {decimation}")

.. method:: getConfig(host: str, key: str) -> str
    :no-index:

    在多板设置中从指定板卡获取配置。
    
    :param host: 目标 Red Pitaya 主机名
    :type host: str
    :param key: 配置参数名称
    :type key: str
    :rtype: str

|

Streaming 控制方法
---------------------------

.. method:: startStreaming() -> bool

    启动数据传输过程。
   
    :returns: Streaming 成功启动时返回 ``True``
    :rtype: bool
   
    **示例：**
   
    .. code-block:: python
   
        if not client.startStreaming():
            print("Failed to start streaming")

.. method:: stopStreaming()

    停止所有已连接板卡上的 Streaming 过程。
    
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        client.stopStreaming()

.. method:: wait()

    阻塞直到 Streaming 完成或停止。请在 ``startStreaming()`` 后调用。
    
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        client.startStreaming()
        client.wait()  # Blocks here until streaming stops

.. method:: notifyStop()

    通知 Streaming 过程停止（用于回调或其他线程）。
    
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        # In callback after collecting enough data:
        if self.sample_count >= self.target_samples:
            client.notifyStop()

.. method:: notifyStop(host)
    :no-index:

    在多板设置中停止指定板卡的 Streaming。
    
    :param host: 目标 Red Pitaya 主机名
    :type host: str
    :rtype: None

|

配置文件方法
---------------------------

.. method:: sendFileConfig(config)

    以 JSON 字符串发送完整配置。
   
    :param config: JSON 配置字符串
    :type config: str
    :returns: 配置被接受时返回 ``True``
    :rtype: bool

.. method:: getFileConfig()

    以 JSON 字符串获取完整配置。
   
    :returns: JSON 配置字符串
    :rtype: str

|

实用方法
----------------

.. method:: setVerbose(enable)

    启用或禁用详细日志输出。
   
    :param enable: ``True`` 表示启用详细日志
    :type enable: bool
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        client.setVerbose(True)  # Show connection and transfer details

.. method:: setReceiveDataCallback(callback)

    注册回调对象以接收 Streaming 数据和事件。

    :param callback: ADCCallback 实例（在 Python 中使用 ``__disown__()``）
    :type callback: ADCCallback
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        callback = MyADCCallback()
        client.setReceiveDataCallback(callback.__disown__())

.. method:: removeReceiveDataCallback()

    注销回调处理程序。
    
    :rtype: None

|

ADCCallback 类
==================

用于处理 ADC 流传输事件的基类。重写方法以处理传入数据。

**最小实现：**

.. tabs::

    .. tab:: Python

        .. code-block:: python

            class MyCallback(streaming.ADCCallback):
                def __init__(self):
                    super().__init__()
                    self.data = []
                
                def receivePack(self, client, pack):
                    """Called when data arrives"""
                    if pack.channel1.samples > 0:
                        self.data.extend(pack.channel1.raw)

    .. tab:: C++

        .. code-block:: cpp

            #include "adc_streaming.h"
            #include "callbacks.h"
            
            class MyCallback : public ADCCallback {
            public:
                std::vector<int16_t> data;
                
                void receivePack(ADCStreamClient* client, ADCPack& pack) override {
                    // Process channel 1 data
                    if (pack.channel1.samples > 0) {
                        data.insert(data.end(), 
                                    pack.channel1.raw, 
                                    pack.channel1.raw + pack.channel1.samples);
                    }
                }
            };

|

数据回调方法
---------------------

.. method:: receivePack(client, pack)

    **主回调** - 流传输服务器收到新数据包时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param pack: 包含通道数据的 ADCPack 对象
    :type pack: ADCPack
    :rtype: None
   
    **ADCPack 结构：**
   
    .. code-block:: python
   
        pack.host              # str: Source Red Pitaya hostname
        pack.channel1.raw      # list[int16]: Raw ADC samples
        pack.channel1.samples  # int: Number of samples in packet
        pack.channel1.fpgaLost # int: Samples lost by FPGA buffer overflow
        pack.channel1.packId   # int: Packet sequence number
        # channel2, channel3, channel4 same structure
   
    **示例：**
   
    .. code-block:: python
   
        def receivePack(self, client, pack):
            # Store data
            self.ch1_data.extend(pack.channel1.raw)
            self.ch2_data.extend(pack.channel2.raw)
            
            # Monitor for data loss
            if pack.channel1.fpgaLost > 0:
                print(f"WARNING: Lost {pack.channel1.fpgaLost} samples")
            
            # Stop after collecting enough data
            if len(self.ch1_data) >= self.target_samples:
                client.notifyStop()

|

连接事件回调
---------------------------

.. note::

    所有回调方法都会接收 ``host`` 参数，用于标识触发事件的 Red Pitaya 板卡。这对于跟踪多板主从 
    配置中的事件至关重要。

.. method:: connected(client, host)

    成功连接到 Red Pitaya 时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 已连接 Red Pitaya 的主机名或 IP 地址
    :type host: str
    :rtype: None

.. method:: disconnected(client, host)

    与 Red Pitaya 的连接断开时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 已断开连接 Red Pitaya 的主机名或 IP 地址
    :type host: str
    :rtype: None

.. method:: error(client, host, code)

    发生连接或流传输错误时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 报告错误的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :param code: 错误代码（系统相关）
    :type code: int
    :rtype: None

|

服务器状态回调
-----------------------

.. method:: stopped(client, host)

    流传输正常停止时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 停止运行的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :rtype: None

.. method:: stoppedNoActiveChannels(client, host)

    因未启用通道而停止流传输时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 停止运行的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :rtype: None

.. method:: stoppedMemError(client, host)

    因内存分配错误而停止流传输时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 停止运行的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :rtype: None

.. method:: stoppedMemModify(client, host)

    因流传输期间内存配置改变而停止流传输时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 停止运行的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :rtype: None

.. method:: stoppedSDFull(client, host)

    因 SD 卡已满而停止向 SD 卡流传输时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 停止运行的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :rtype: None

.. method:: stoppedSDDone(client, host)

    向 SD 卡流传输成功完成时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 完成操作的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :rtype: None

|

配置连接回调
------------------------------------

.. method:: configConnected(client, host)

    建立配置连接时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 已连接 Red Pitaya 的主机名或 IP 地址
    :type host: str
    :rtype: None

.. method:: configError(client, host, code)

    配置连接发生错误时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 报告错误的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :param code: 错误代码
    :type code: int
    :rtype: None

.. method:: configErrorTimeout(client, host)

    配置连接超时时调用。
   
    :param client: ADCStreamClient 实例
    :type client: ADCStreamClient
    :param host: 超时的 Red Pitaya 主机名或 IP 地址
    :type host: str
    :rtype: None

|

DAC 流传输 API
******************

DACStreamClient 类
======================

用于将波形从计算机流传输到 Red Pitaya DAC 输出的主类。

**基本用法：**

.. tabs::

    .. tab:: Python

        .. code-block:: python

            import rp_stream as streaming
            
            # Create client
            client = streaming.DACStreamClient()
            
            # Set callback handler (optional)
            callback = MyDACCallback()
            client.setCallback(callback.__disown__())
            
            # Connect and configure
            client.connect()
            client.sendConfig('dac_rate', '125000000')
            client.sendConfig('dac_pass_mode', 'NET')
            
            # Stream from WAV file
            client.startStreaming('./waveform.wav')
            client.wait()

    .. tab:: C++

        .. code-block:: cpp

            #include "dac_streaming.h"
            #include "callbacks.h"
            
            // Create callback handler
            class MyCallback : public DACCallback {
                void sentPack(DACStreamClient* client, uint32_t ch1, uint32_t ch2) override {
                    // Handle sent packet notification
                }
            };
            
            // Create client
            DACStreamClient client;
            MyCallback callback;
            client.setCallback(&callback);
            
            // Connect and configure
            client.connect();
            client.sendConfig("dac_rate", "125000000");
            client.sendConfig("dac_pass_mode", "NET");
            
            // Stream from WAV file
            client.startStreaming("./waveform.wav");
            client.wait();

|

连接方法
-------------------

.. method:: connect() -> bool
    :no-index:

    使用自动发现连接到 Red Pitaya。
   
    :returns: ``True`` 如果连接成功
    :rtype: bool

.. method:: connect(host: str) -> bool
    :no-index:

    连接到指定的 Red Pitaya。
   
    :param host: 主机名或 IP 地址
    :type host: str
    :returns: ``True`` 如果连接成功
    :rtype: bool
   
    **示例：**
   
    .. code-block:: python
   
        if not client.connect("rp-f0a235.local"):
            print("Connection failed")

|

配置方法
----------------------

.. method:: sendConfig(key: str, value: str) -> bool
    :no-index:

    向流传输服务器发送配置参数。
    
    :param key: 配置参数名称
    :type key: str
    :param value: 参数值
    :type value: str
    :rtype: bool
   
    **常用 DAC 参数：**
   
    .. list-table::
        :header-rows: 1
        :widths: 30 50 20
   
        * - 键
          - 说明
          - 取值
        * - ``dac_rate``
          - DAC 输出速率（Hz）
          - "1" - "125000000"
        * - ``dac_pass_mode``
          - 源模式
          - "NET", "FILE"
        * - ``block_size``
          - 网络数据包大小（字节）
          - "2048" - "2097152"
        * - ``adc_size``
          - FPGA 缓冲区大小（字节）
          - "1048576" - "104857600"
   
    **示例：**
   
    .. code-block:: python
   
        client.sendConfig('dac_rate', '125000000')  # 125 MS/s
        client.sendConfig('block_size', '16384')

.. method:: getConfig(key: str) -> str
    :no-index:

    获取当前配置值。
    
    :param key: 配置参数名称
    :type key: str
    :rtype: str
   
    **示例：**
   
    .. code-block:: python
   
        rate = client.getConfig('dac_rate')

|

播放控制方法
--------------------------

.. method:: setRepeatCount(count)

    设置波形重复次数。
   
    :param count: 重复次数
    :type count: int
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        client.setRepeatCount(10)  # Play 10 times

.. method:: setRepeatInf(enable)

    启用或禁用无限重复模式。
   
    :param enable: ``True`` 表示连续播放
    :type enable: bool
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        client.setRepeatInf(True)  # Loop forever

|

流式传输方法
------------------

.. method:: startStreamingWAV(fileName)

    将 WAV 音频文件流式传输到 DAC 输出端。
   
    :param fileName: WAV 文件路径（相对或绝对路径）
    :type fileName: str
    :returns: 如果流式传输已启动则为 ``True``
    :rtype: bool
   
    **支持的格式：**
   
    * 单声道（1 个通道）- 输出到 DAC 1
    * 立体声（2 个通道）- 输出到 DAC 1 和 DAC 2
    * 8 位或 16 位 PCM
   
    **示例：**
   
    .. code-block:: python
   
        if not client.startStreamingWAV('./my_waveform.wav'):
            print("Failed to start")

.. method:: startStreamingTDMS(fileName)

    将 TDMS 文件流式传输到 DAC 输出端。
   
    :param fileName: TDMS 文件路径
    :type fileName: str
    :returns: 如果流式传输已启动则为 ``True``
    :rtype: bool

.. method:: startStreamingFromMemory()

    流式传输之前通过 ``setMemory16Bit()`` 加载到内存的波形。
   
    :returns: 如果流式传输已启动则为 ``True``
    :rtype: bool
   
    **示例：**
   
    .. code-block:: python
   
        # Load waveform data
        waveform = [100, 200, 300, ...]  # int16 values
        client.setMemory16Bit(1, waveform)
        client.setMemory16Bit(2, waveform)
        
        # Stream from memory
        client.startStreamingFromMemory()

.. method:: stopStreaming()
    :no-index:

    停止流式传输过程。
    
    :rtype: None

.. method:: wait()
    :no-index:

    阻塞，直到流式传输完成或停止。
    
    :rtype: None

.. method:: notifyStop()
    :no-index:

    发出停止流式传输的信号（用于回调或其他线程）。
    
    :rtype: None

|

内存加载方法
-----------------------

.. method:: setMemory8Bit(channel, buffer)

    将通道的 8 位波形数据加载到 FPGA 内存。
   
    :param channel: 通道号（1 或 2）
    :type channel: int
    :param buffer: 8 位有符号整数列表
    :type buffer: list[int]
    :returns: 如果数据成功加载则为 ``True``
    :rtype: bool
   
    **示例：**
   
    .. code-block:: python
   
        data = [127, 0, -128, 0, ...]  # 8-bit values
        client.setMemory8Bit(1, data)

.. method:: setMemory16Bit(channel, buffer)

    将通道的 16 位波形数据加载到 FPGA 内存。
   
    :param channel: 通道号（1 或 2）
    :type channel: int
    :param buffer: 16 位有符号整数列表
    :type buffer: list[int]
    :returns: 如果数据成功加载则为 ``True``
    :rtype: bool
   
    **示例：**
   
    .. code-block:: python
   
        import numpy as np
        
        # Generate waveform
        t = np.linspace(0, 1, 1024)
        waveform = (32767 * np.sin(2 * np.pi * t)).astype(np.int16)
        
        # Load to both channels
        client.setMemory16Bit(1, waveform.tolist())
        client.setMemory16Bit(2, waveform.tolist())

|

实用方法
----------------

.. method:: setVerbose(enable)
    :no-index:

    启用或禁用详细日志记录。
    
    :param enable: ``True`` 表示详细日志记录
    :type enable: bool
    :rtype: None

.. method:: setCallbackFunction(callback)

    注册回调以接收流式传输事件。
   
    :param callback: DACCallback 实例
    :type callback: DACCallback
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        callback = MyDACCallback()
        client.setCallbackFunction(callback.__disown__())

.. method:: removeCallbackFunction()

    注销回调处理器。
    
    :rtype: None

|

DACCallback 类
==================

用于处理 DAC 流式传输事件的基类。重写其中的方法即可监控流式传输进度。

**最小实现：**

.. tabs::

    .. tab:: Python

        .. code-block:: python

            class MyCallback(streaming.DACCallback):
                def __init__(self):
                    super().__init__()
                    self.packets_sent = 0
                
                def sentPack(self, client, ch1_size, ch2_size):
                    """Called after each packet is sent"""
                    self.packets_sent += 1
                    print(f"Sent CH1: {ch1_size} bytes, CH2: {ch2_size} bytes")

    .. tab:: C++

        .. code-block:: cpp

            #include "dac_streaming.h"
            #include "callbacks.h"
            
            class MyCallback : public DACCallback {
            public:
                int packets_sent = 0;
                
                void sentPack(DACStreamClient* client, uint32_t ch1_size, uint32_t ch2_size) override {
                    packets_sent++;
                    std::cout << "Sent CH1: " << ch1_size 
                                << " bytes, CH2: " << ch2_size << " bytes" << std::endl;
                }
            };

|

数据回调方法
---------------------

.. method:: sentPack(client, ch1_size, ch2_size)

    **主要回调** - 数据包成功发送到 DAC 后调用。
   
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param ch1_size: 发送到通道 1 的采样点数
    :type ch1_size: int
    :param ch2_size: 发送到通道 2 的采样点数
    :type ch2_size: int
    :rtype: None
   
    **示例：**
   
    .. code-block:: python
   
        def sentPack(self, client, ch1_size, ch2_size):
            self.total_samples += ch1_size + ch2_size
            print(f"Sent {self.total_samples:,} samples")

|

连接事件回调
---------------------------

.. method:: connected(client, host)
    :no-index:

    成功连接时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: disconnected(client, host)
    :no-index:

    连接丢失时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: error(client, host, code)
    :no-index:

    发生连接错误时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :param code: 错误代码
    :type code: int
    :rtype: None

|

服务器状态回调
-----------------------

.. method:: stopped(client, host)
    :no-index:

    流式传输正常停止时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: stoppedFileEnd(client, host)

    文件结束导致流式传输停止时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: stoppedFileBroken(client, host)

    文件损坏导致流式传输停止时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: stoppedEmpty(client, host)

    没有可用数据导致流式传输停止时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: stoppedMissingFile(client, host)

    找不到文件导致流式传输停止时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: stoppedMemError(client, host)
    :no-index:

    内存错误导致流式传输停止时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: stoppedMemModify(client, host)
    :no-index:

    流式传输期间内存被修改导致停止时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

|

配置连接回调
------------------------------------

.. method:: configConnected(client, host)
    :no-index:

    建立配置连接时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

.. method:: configError(client, host, code)
    :no-index:

    发生配置连接错误时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :param code: 错误代码
    :type code: int
    :rtype: None

.. method:: configErrorTimeout(client, host)
    :no-index:

    配置连接超时时调用。
    
    :param client: DACStreamClient 实例
    :type client: DACStreamClient
    :param host: 主机名或 IP
    :type host: str
    :rtype: None

|

数据结构
****************

ADCPack 结构
==================

包含单个流式传输数据包中所有通道的数据。

.. code-block:: python

    class ADCPack:
        host: str                # Source Red Pitaya hostname
        channel1: ADCChannel     # Channel 1 data
        channel2: ADCChannel     # Channel 2 data
        channel3: ADCChannel     # Channel 3 data (4-Input only)
        channel4: ADCChannel     # Channel 4 data (4-Input only)

|

ADCChannel 结构
=====================

包含单个 ADC 通道的数据和元数据。

.. code-block:: python

    class ADCChannel:
        samples: int             # Number of samples in this packet
        bitsBySample: int        # ADC resolution (12, 14, or 16 bits)
        fpgaLost: int            # Cumulative samples lost due to buffer overflow
        attenuator_1_20: bool    # True if 1:20 attenuator is active
        baseRate: int            # Base ADC sampling rate (Hz)
        adcBaseBits: int         # Native ADC bit depth
        packId: int              # Packet sequence number
        raw: list[int16]         # Raw ADC sample data

**使用示例：**

.. code-block:: python

    def receivePack(self, client, pack):
        ch1 = pack.channel1
        
        # Access samples
        samples = ch1.raw
        
        # Check for data loss
        if ch1.fpgaLost > 0:
            print(f"Lost {ch1.fpgaLost} samples")
        
        # Check attenuation
        if ch1.attenuator_1_20:
            print("1:20 attenuator is active")

|

完整示例
******************

有关包含错误处理和最佳实践的完整生产就绪示例，请参阅 :ref:`流式传输示例 <examples_streaming>`。

|

另请参阅
*********

* :ref:`流式传输应用 <streaming_top>`
* :ref:`快速入门指南 <streaming_quickstart>`
* :ref:`配置参考 <streaming_configuration_top>`
* :rp-github:`GitHub：流式传输客户端库 <streaming-client>`

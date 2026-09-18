.. _streaming_quickstart:

#########################
快速入门指南
#########################

在 5 分钟内开始使用 Red Pitaya Streaming。本指南展示将 ADC 数据从 Red Pitaya 传输到计算机所需的最少代码。

.. contents:: 目录
    :local:
    :backlinks: top

|

前置条件
**************

* 已连接到网络的 Red Pitaya 板卡
* 计算机已安装 Python 3.9 或更高版本
* Red Pitaya ``rp-stream`` Streaming 库（包含在 :ref:`Streaming 命令行客户端 <streaming_pc_clients>` 中）

|

步骤 1：启动 Streaming 服务器
************************************

首先确保 Streaming 应用正在 Red Pitaya 上运行。可以通过两种方式启动：

**选项 A：通过 Web 界面**

打开 Red Pitaya Web 界面并单击“Data stream control”应用。

**选项 B：加载 FPGA 并运行**

.. code-block:: bash

    ssh root@rp-xxxxxx.local
    overlay.sh stream_app
    streaming-server

运行后，LED 2 将亮起，LED 0 将闪烁。

|

步骤 2：最小 ADC Streaming 示例
***************************************

本示例以 488 kS/s 从两个 ADC 通道传输 1 秒数据。

创建名为 ``my_first_stream.py`` 的文件：

.. code-block:: python

    #!/usr/bin/python3
    import numpy as np
    import streaming

    # Simple callback to collect data
    class DataCollector(streaming.ADCCallback):
        def __init__(self):
            super().__init__()
            self.data_ch1 = []
            self.data_ch2 = []
        
        def receivePack(self, client, pack):
            """Called automatically when new data arrives"""
            self.data_ch1.extend(pack.channel1.raw)
            self.data_ch2.extend(pack.channel2.raw)
            print(f"Received {len(pack.channel1.raw)} samples")

    # Create streaming client
    client = streaming.ADCStreamClient()
    collector = DataCollector()
    client.setReceiveDataFunction(collector.__disown__())

    # Connect to Red Pitaya (auto-discovery)
    print("Connecting to Red Pitaya...")
    if not client.connect():
        print("ERROR: Cannot connect!")
        exit(1)

    # Configure streaming
    client.sendConfig('adc_decimation', '256')      # 125 MS/s ÷ 256 = 488 kS/s
    client.sendConfig('channel_state_1', 'ON')      # Enable channel 1
    client.sendConfig('channel_state_2', 'ON')      # Enable channel 2

    # Start streaming
    print("Starting acquisition...")
    client.startStreaming()
    
    # Wait for completion (or use Ctrl+C to stop)
    try:
        client.wait()
    except KeyboardInterrupt:
        print("\nStopping...")

    # Show results
    print(f"\nCollected {len(collector.data_ch1):,} samples per channel")
    print(f"Channel 1 range: {min(collector.data_ch1)} to {max(collector.data_ch1)}")
    print(f"Channel 2 range: {min(collector.data_ch2)} to {max(collector.data_ch2)}")

**运行：**

.. code-block:: bash

    python my_first_stream.py

应看到类似以下输出：

.. code-block:: text

    Connecting to Red Pitaya...
    Starting acquisition...
    Received 8192 samples
    Received 8192 samples
    ...
    
    Collected 488,281 samples per channel
    Channel 1 range: -145 to 132
    Channel 2 range: -98 to 87

|

理解代码
***********************

本示例演示 Streaming 的三个关键组件：

1.  **回调类** - 处理传入的数据包

    .. code-block:: python

        class DataCollector(streaming.ADCCallback):
            def receivePack(self, client, pack):
                # Process data as it arrives
                self.data_ch1.extend(pack.channel1.raw)

2.  **客户端设置** - 配置连接和参数

    .. code-block:: python

        client = streaming.ADCStreamClient()
        client.connect()  # Auto-discovery
        client.sendConfig('adc_decimation', '256')

3.  **Streaming 控制** - 启动并等待数据

    .. code-block:: python

        client.startStreaming()
        client.wait()

|

后续步骤
***********

基本 Streaming 已经运行后，可以探索更多高级功能：

* **提高采样率** - 将 ``adc_decimation`` 改为更小的值（125 MS/s 时最小为 1）
* **实时处理** - 在 ``receivePack()`` 回调中添加信号处理
* **保存到文件** - 将数据写入 CSV、HDF5 或二进制格式
* **实时可视化** - 使用 matplotlib 实时绘图

|

配置参数
*************************

可以调整的常用配置选项：

.. list-table::
    :header-rows: 1
    :widths: 30 50 20

    * - 参数
      - 描述
      - 默认值
    * - ``adc_decimation``
      - 采样率 = 125 MS/s ÷ 抽取因子（1、2、4、8、16、17、18、…、65536）
      - 1
    * - ``channel_state_1``
      - 启用通道 1（ON/OFF）
      - OFF
    * - ``channel_state_2``
      - 启用通道 2（ON/OFF）
      - OFF
    * - ``block_size``
      - 网络数据包大小（字节，2048-2097152）
      - 131072
    * - ``adc_pass_mode``
      - 目标（NET 或用于 SD 卡的 FILE）
      - NET

完整配置参考请参见 :ref:`Streaming 配置 <stream_configuration>`。

|

故障排除
****************

**无法连接 Red Pitaya 或未找到板卡**

    * 验证 IP 地址或主机名
    * 确保 Streaming 服务器正在运行（LED 2 应亮起且 LED 0 闪烁）
    * 检查网络连接：``ping rp-xxxxxx.local``
    * **检查防火墙/杀毒软件设置** - Python 或 C++ 可能被阻止访问网络

    表明防火墙/杀毒软件阻止连接的常见错误：

    .. code-block:: shell-session

        # Host not found error
        2026.01.30-14.25.08.342:  Host not found
        The client did not connect

    如果看到这些错误，请确保防火墙和杀毒软件允许 Python 与 C++ 访问网络。最简单的解决方法是运行程序几次，然后检查防火墙/杀毒软件日志，确认是否阻止了应用，并为其创建例外（请在安全软件文档中查找“网络访问故障排除”“解决通信阻塞”等内容）。

**未接收到数据**

   * 确认通道已启用（``channel_state_1`` 和 ``channel_state_2``）
   * 检查 Streaming 服务器是否仍在运行
   * 查看 Red Pitaya 日志：``journalctl -u streaming-server``

**报告数据丢失（``fpgaLost > 0``）**

   * 降低采样率（增大抽取因子）
   * 增大 ``block_size`` 以提高网络传输效率
   * 检查网络带宽和延迟

|

完整示例
******************

有关包含错误处理、内存管理和高级功能的可用于生产环境的示例，请参阅 :ref:`流传输示例 <examples_streaming>`。

**Python 示例：**

* :rp-github:`ADC 流传输 <RedPitaya-Examples/blob/main/python-api/Streaming/adc_1_stream.py>` - 使用 numpy 数组的完整 ADC 流传输
* :rp-github:`多板 ADC <RedPitaya-Examples/blob/main/python-api/Streaming/adc_2_stream.py>` - 从多个板卡同步采集
* :rp-github:`DAC 流传输 <RedPitaya-Examples/blob/main/python-api/Streaming/dac_1_stream.py>` - 从 WAV 文件生成波形
* :rp-github:`立体声 DAC <RedPitaya-Examples/blob/main/python-api/Streaming/dac_2_stream.py>` - 双通道 DAC 输出
* :rp-github:`内存流传输 <RedPitaya-Examples/blob/main/python-api/Streaming/dac_3_stream.py>` - 直接进行内存缓冲区流传输

**C++ 示例：**

* :rp-github:`ADC 流传输 <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_adc_1.cpp>` - 高性能 ADC 采集
* :rp-github:`多板 ADC <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_adc_2.cpp>` - 多板同步流传输
* :rp-github:`DAC 流传输 <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_1.cpp>` - WAV 文件生成和流传输
* :rp-github:`立体声 DAC <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_2.cpp>` - 立体声 WAV 输出
* :rp-github:`内存流传输 <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_3.cpp>` - 内存缓冲区流传输

|

API 文档
******************

有关类和方法的详细文档，请参阅 :ref:`流传输 API 参考 <streaming_api_reference>`。

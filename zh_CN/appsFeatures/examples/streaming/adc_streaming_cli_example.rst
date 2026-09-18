.. _stream_adc_cli_example:

#####################################
ADC 流传输示例（命令行）
#####################################

本示例演示如何使用 **rpsa_client** 命令行工具从 ADC 输入捕获数据并保存到计算机。
本教程涵盖从配置到数据采集和转换的完整工作流。

.. note::

    本教程使用 **rpsa_client** 命令行工具，而非 Python/C++ API。基于 API 的 ADC 流传输请参阅 :ref:`ADC API Streaming Tutorial <streaming_adc_api_example>`.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

前置条件
**************

开始本示例前，请确保具备：

* 使用 OS 2.07-43 或更高版本的 Red Pitaya 板卡
* 计算机已安装 :ref:`命令行客户端 <stream_command_client>`
* 为 ADC 流式传输预留足够的 :ref:`DMM 内存 <deepMemoryMode>` （建议至少 100 MB）
* 对 Red Pitaya 板卡的 :ref:`SSH 访问权限 <ssh>`
* 为获得最佳性能，在流式传输前 :ref:`禁用 Web 界面 <service_management>`
* 输入信号源（可选，也可捕获环境噪声进行测试）

|

概览
*********

本示例将引导你完成：

1. 建立到 Red Pitaya 的 SSH 连接
2. 加载 FPGA 并启动流传输应用
3. 配置 ADC 流传输参数
4. 将数据捕获为二进制格式
5. 将捕获数据转换为 WAV、CSV 或 TDMS 格式
6. 分析结果

本示例从两个输入通道以 1 MS/s（抽取 125）捕获数据。有关最大采样率和性能注意事项，请参见 :ref:`流式传输性能限制 <streaming_limits>`。

|

分步教程
**********************

步骤 1：建立 SSH 连接
==================================

使用 SSH 连接到 Red Pitaya 板卡。将 ``<IP_ADDRESS>`` 替换为 Red Pitaya 的 IP 地址，或使用 ``.local`` 地址。

.. code-block:: console

    ssh root@<IP_ADDRESS or .LOCAL_ADDRESS>

例如：

.. code-block:: console

    ssh root@192.168.1.100
    # or
    ssh root@rp-f0xxxx.local

默认密码为 ``root``。

|

步骤 2：加载 FPGA 并启动流传输应用
===================================================

通过 SSH 连接后，加载流传输 FPGA 镜像并启动流传输服务器：

.. code-block:: console

    redpitaya> overlay.sh stream_app
    redpitaya> streaming-server

你应看到 LED 2 亮起且 LED 0 闪烁，表示流传输应用正在运行。

.. note::

    保持此 SSH 终端打开。后续步骤需要 Streaming 服务器持续运行。

|

步骤 3：获取并编辑配置文件
=============================================

在计算机上打开新的终端或命令提示符窗口（不要关闭 SSH 会话）。进入命令行客户端的安装目录。

**下载配置文件：**

.. code-block:: console

    computer> .\rpsa_client.exe -c -g F

配置文件将下载到命令行客户端的 ``configs`` 目录。

|

**编辑配置文件：**

使用喜欢的文本编辑器打开下载的配置文件（通常类似于 ``config_<board_IP>.json``）。

本示例将通道 1 和 2 的 ADC 流式传输配置为 1 MS/s（抽取 125）：

.. code-block:: javascript

    {
        "adc_streaming" : {
            "adc_decimation" : 125,
            "channel_state_1" : "ON",
            "channel_state_2" : "ON",
            "channel_attenuator_1" : "A_1_1",
            "channel_attenuator_2" : "A_1_1",
            ...
        },
        "memory_manager" : {
            "adc_size" : 104857600,
            "block_size" : 8388608,
            ...
        }
    }

关键参数：

* ``adc_decimation: 125`` - 采样率 = 125 MS/s ÷ 125 = 1 MS/s
* ``channel_state_1/2: "ON"`` - 启用两个输入通道
* ``channel_attenuator_1/2: "A_1_1"`` - 1:1 衰减（±1V 范围）
* ``adc_size: 104857600`` - 为 ADC 缓冲区预留 100 MiB
* ``block_size: 8388608`` - 8 MiB 网络数据包大小（支持的最大值）

完整配置选项请参阅 :ref:`ADC 配置参考 <stream_adc_config>`。

.. note::

    **采样率计算：**
    
    .. math::

        \text{Sample Rate} = \frac{125 \text{ MS/s}}{\text{decimation}} = \frac{125,000,000}{125} = 1,000,000 \text{ samples/s}

.. note::

    1 MiB = 1024×1024 Bytes = 2^20 Bytes = 1,048,576 Bytes。这里使用 Mebibytes（MiB）而不是 Megabytes（MB），以避免与十进制系统混淆。

将编辑后的配置文件保存为 ``config_adc.json``.

|

**上传配置文件：**

将编辑后的配置文件上传到 Red Pitaya 板卡：

.. code-block:: console

    computer> .\rpsa_client.exe -c -s F -f .\configs\config_adc.json

|

步骤 4：启动 ADC 流传输并捕获数据
==============================================

开始将 ADC 数据捕获到二进制文件：

.. code-block:: console

    computer> .\rpsa_client.exe -i -f bin -t ./data/ -s 1000000

参数说明：

* ``-i`` - 输入（ADC 流式传输模式）
* ``-f bin`` - 二进制文件格式（效率最高）
* ``-t ./data/`` - 保存到 ``data`` 文件夹
* ``-s 1000000`` - 捕获 1,000,000 个采样点（1 MS/s 时为 1 秒）

该命令将开始捕获数据并显示进度：

.. code-block:: console

    Connecting to board...
    Connected: 192.168.1.100
    Starting streaming...
    Received: 500000 samples
    Received: 1000000 samples
    Streaming complete
    Data saved to: ./data/data_file_192.168.1.100.bin

.. tip::

    **采集时长：**
    
    若要捕获特定时长的数据，请计算采样数：
    
    .. math::

        \text{Samples} = \text{Sample Rate} \times \text{Duration (seconds)}
    
    示例：
    
    * 以 1 MS/s 采集 1 秒：``-s 1000000``
    * 以 1 MS/s 采集 5 秒：``-s 5000000``
    * 以 100 kS/s（抽取因子 1250）采集 10 秒：``-s 1000000``

要无限捕获，请省略 ``-s`` 参数，并使用 ``Ctrl+C`` 手动停止：

.. code-block:: console

    computer> .\rpsa_client.exe -i -f bin -t ./data/

|

步骤 5：转换二进制数据
=================================

捕获的二进制文件必须转换为可读格式才能分析。

**快速转换示例：**

.. code-block:: console

    computer> .\convert_tool.exe .\data\data_file_192.168.1.100.bin -f WAV

这将创建 WAV 文件，可在音频编辑器（如 |Audacity|）中打开进行分析。

**可用格式：**

* **WAV** - 用于音频编辑器（Audacity 等）和信号分析
* **CSV** - 用于电子表格、Python 和 MATLAB 分析
* **TDMS** - 用于 NI DIAdem 或 LabVIEW

有关文件信息显示、分段转换和格式详情等完整转换工具文档，请参阅 :ref:`转换工具参考 <streaming_convert_tool>`。

|

步骤 6：分析捕获数据
===================================

**使用 Python 快速分析：**

如果已安装 Python、NumPy 和 Matplotlib：

.. code-block:: python

    import numpy as np
    import matplotlib.pyplot as plt
    from scipy.io import wavfile

    # Read WAV file
    sample_rate, data = wavfile.read('data_file_192.168.1.100.wav')
    
    # Extract channels
    ch1 = data[:, 0]
    ch2 = data[:, 1]
    
    # Create time axis
    time = np.arange(len(ch1)) / sample_rate
    
    # Plot signals
    plt.figure(figsize=(12, 6))
    
    plt.subplot(2, 1, 1)
    plt.plot(time[:1000], ch1[:1000])  # First 1000 samples
    plt.title('Channel 1')
    plt.xlabel('Time (s)')
    plt.ylabel('Amplitude (V)')
    plt.grid(True)
    
    plt.subplot(2, 1, 2)
    plt.plot(time[:1000], ch2[:1000])
    plt.title('Channel 2')
    plt.xlabel('Time (s)')
    plt.ylabel('Amplitude (V)')
    plt.grid(True)
    
    plt.tight_layout()
    plt.show()
    
    # Calculate statistics
    print(f"Channel 1: min={ch1.min():.4f}V, max={ch1.max():.4f}V, mean={ch1.mean():.4f}V")
    print(f"Channel 2: min={ch2.min():.4f}V, max={ch2.max():.4f}V, mean={ch2.mean():.4f}V")

|

故障排除
****************

未捕获数据
=================

**问题：** 命令完成但文件为空或非常小

**解决方案：**

1. 确认 Red Pitaya 上的流传输服务器正在运行（LED 2 亮起、LED 0 闪烁）
2. 检查通道是否已启用：``"channel_state_1": "ON"``
3. 验证网络连接：``ping <Red_Pitaya_IP>``
4. 检查防火墙设置，确保 ``rpsa_client.exe`` 具有网络访问权限
5. 尝试在配置中将 ``block_size`` 增大到 8 MB

|

报告数据丢失
===================

**问题：** 控制台显示 “Lost samples” 或数据存在间断

**解决方案：**

1. **降低采样率** （增大抽取因子）：
   
   * 对于 500 kS/s，尝试将抽取因子设为 250
   * 对于 100 kS/s，可将抽取因子设为 1250

2. **确保使用最大块大小** （8 MB）：

   .. code-block:: json

       "block_size" : 8388608

3. **检查网络性能：**
   
   * 使用有线以太网连接（不要使用 WiFi）
   * 确保没有其他高负载网络流量
   * 关闭不必要的应用程序

4. **增大预留内存：**

   .. code-block:: json

       "adc_size" : 209715200    // 200 MiB

|

转换工具失败
======================

**问题：** ``convert_tool.exe`` 报错或崩溃

**解决方案：**

1. 确认二进制文件未损坏：
   
   .. code-block:: console

       computer> .\convert_tool.exe .\data\data_file.bin -i

2. 检查转换文件所需的可用磁盘空间
3. 确保文件格式使用大写：``WAV``、``CSV`` 或 ``TDMS``
4. 如果文件很大，尝试转换较小的片段

|

配置被拒绝
=======================

**问题：** 配置上传失败

**解决方案：**

1. 使用 JSON 验证器检查 JSON 语法
2. 确保所有参数值有效（参见 :ref:`配置参考 <stream_config>`）
3. 检查内存分配是否超过预留的 DMM 大小
4. 重启流传输服务器后重试

|

变体与扩展
***************************

高速捕获
===================

要获得最大网络流式传输速率，请使用仍在网络限制范围内的最低抽取因子。

使用两个通道和 16 位分辨率时，:ref:`最大网络传输速率为 62.5 MB/s <streaming_limits>`，这会限制可达到的最高采样率：

.. code-block:: javascript

    {
        "adc_streaming" : {
            "adc_decimation" : 8,
            "channel_state_1" : "ON",
            "channel_state_2" : "ON",
            "adc_size" : 209715200,
            "block_size" : 8388608,
            ...
        }
    }

这样每个通道约为 15.625 MS/s（125 MS/s ÷ 8），双通道产生 62.5 MB/s 的数据。

.. note::

    更高的采样率需要减少通道数或使用本地 SD 卡存储。详细吞吐量计算参见 :ref:`Streaming 性能限制 <streaming_limits>`。

|

单通道采集
=======================

要降低数据速率和存储需求，只采集一个通道：

.. code-block:: javascript

    {
        "adc_streaming" : {
            "channel_state_1" : "ON",
            "channel_state_2" : "OFF",
            ...
        }
    }

|

高分辨率模式
=====================

使用 1:20 衰减以获得 ±20V 输入范围：

.. code-block:: javascript

    {
        "adc_streaming" : {
            "channel_attenuator_1" : "A_1_20",
            "channel_attenuator_2" : "A_1_20",
            ...
        }
    }

|

AC 耦合
============

启用 AC 耦合以移除直流偏置：

.. code-block:: javascript

    {
        "adc_streaming" : {
            "channel_ac_dc_1" : "AC",
            "channel_ac_dc_2" : "AC",
            ...
        }
    }

|

触发采集
==================

如需仅在满足触发条件时采集，请使用基于 API 的方式。命令行客户端不支持高级触发，但可以：

1. 使用 :ref:`ADC API 流式传输教程 <streaming_adc_api_example>` 实现软件触发
2. 如需硬件触发，可通过 :ref:`GPIO <gpio>` 配置外部触发

|

后续步骤
***********

* 尝试不同的采样率和抽取值
* 阅读 :ref:`ADC 配置 <stream_adc_config>`，了解更多控制选项
* 通过 :ref:`禁用 Web 界面 <streaming_performance_optimization>` 优化性能
* 探索用于四通道及以上采集的 :ref:`多板卡同步流式传输 <multiboard_stream>`
* 尝试 :ref:`ADC API 流式传输教程 <streaming_adc_api_example>` 进行编程控制
* 使用信号处理工具（Python、MATLAB、LabVIEW）分析捕获数据

|

相关文档
**********************

* :ref:`命令行客户端参考 <stream_command_client>` —— 完整的 rpsa_client 文档
* :ref:`ADC 配置 <stream_adc_config>` —— 详细配置参数
* :ref:`流式传输内存管理 <stream_memory>` —— 了解 DMM 分配
* :ref:`ADC API 教程 <streaming_adc_api_example>` —— Python/C++ API 流式传输

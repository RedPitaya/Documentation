.. _examples_streaming:

#########################
Streaming 示例
#########################

.. note::

    **我们正在更新示例，以包含 OS 3.00-57 及更高版本的最新信息**

使用 Red Pitaya Streaming 客户端库演示 ADC 和 DAC Streaming 功能的完整可运行示例。

所有示例源代码都维护在 :rp-github:`GitHub <RedPitaya-Examples/tree/main/python-api/Streaming>` 上，便于访问和持续更新。

.. contents:: 目录
    :local:
    :backlinks: top

|

前置条件
**************

运行这些示例前：

* 使用 OS 2.07 或更高版本的 Red Pitaya 板卡
* Red Pitaya 上运行 Streaming 应用（参见 :ref:`Streaming 快速入门 <streaming_quickstart>`）。可以通过 Web 界面运行，也可以作为 :ref:`命令行服务器 <stream_command_client>` 运行。
* 已下载到计算机的 :ref:`Streaming 命令行客户端 <streaming_pc_clients>`
* 计算机和 Red Pitaya 连接到同一网络（推荐 LAN）
* 计算机已安装 Python 3.12（或更高版本）或 C++20 编译器
* 计算机防火墙/杀毒软件已允许 Streaming 客户端应用访问网络。

.. note::

    **防火墙/杀毒软件配置：** 如果遇到板卡检测或连接问题，请确保防火墙和杀毒软件允许 Python/C++ 访问网络。
    某些安全程序可能阻止 Python 的网络通信，导致客户端无法发现网络中的 Red Pitaya 板卡。

安装说明请参见 :ref:`Streaming 客户端设置 <stream_command_client>`。

|

快速入门
************

刚开始使用 Streaming？请从这里开始：

.. toctree::
    :maxdepth: 1

    streaming_quickstart
    streaming_adc_api_example
    streaming_dac_api_example
    adc_streaming_cli_example
    dac_streaming_cli_example
    streaming_api_reference

快速入门指南通过最小可运行示例帮助您在 5 分钟内开始传输数据。

|

ADC Streaming 示例
***********************

将 Red Pitaya 高速模拟输入的数据连续采集到计算机。

.. note::

    以下代码片段突出展示关键功能。完整的可运行示例（含完整错误处理和文档）请查看各节中的实现链接。

基本 ADC 数据采集
============================

从 ADC 通道传输数据，并自动管理内存和实时处理。

.. tabs::

    .. tab:: Python

        .. grid:: 1
            :gutter: 2

            .. grid-item-card:: **ADC Dual Channel Streaming**
                :link-type: url

                传输到 numpy 数组，并自动管理缓冲区。
                
                * 可配置采样率（通过抽取）
                * 高效使用内存的 numpy 数组存储
                * 实时数据丢失监测
                
                **复杂度：** ⭐⭐

        |

        **主要功能：**

        .. code-block:: python

            import streaming

            # Configure streaming parameters
            decimation = 256                    # Sample rate = 125 MS/s / decimation
            ch1_state = 'ON'                    # Enable channel 1
            ch2_state = 'ON'                    # Enable channel 2

            # Create client and callback
            client = streaming.ConfigStreamClient()
            obj = streaming.ADCStreamClient(client)

            callback = ConfigCallbackImpl()
            client.addCallback(callback)
            
            # Start streaming
            client.startStreaming()
            client.wait()

        **完整实现：** :rp-github:`stream_adc_capture.py <RedPitaya-Examples/blob/main/API_examples/Python_API/Streaming/stream_adc_capture.py>`

    .. tab:: C++

        .. grid:: 1
            :gutter: 2

            .. grid-item-card:: **C++ Dual Channel ADC Streaming**
                :link-type: url

                使用 ``std::vector buffers`` 进行高性能采集。
                
                * 预分配 std::vector 缓冲区
                * 实时计算最小值/最大值/平均值
                * 高效内存管理
                * 帧丢失检测
                
                **复杂度：** ⭐⭐⭐

        |  

        **主要功能：**

        .. code-block:: cpp

            #include "adc_streaming.h"
            #include "callbacks.h"
            
            class Callback : public ADCCallback {
                std::vector<int16_t> ch1_data;  // Pre-allocated buffer
                std::vector<int16_t> ch2_data;
                
                void receivePack(ADCStreamClient* client, ADCPack& pack) override {
                    // Process incoming ADC data packets
                }
            };
            
            // Create client and start streaming
            ADCStreamClient client;
            Callback callback;
            client.setReceiveDataCallback(&callback);
            client.startStreaming();

        **完整实现：** :rp-github:`stream_adc_capture.cpp <RedPitaya-Examples/blob/main/API_examples/C++/Streaming/stream_adc_capture.cpp>`

|

多板同步 ADC
==============================

从多个 Red Pitaya 板卡传输数据（4 个及以上通道），并进行硬件同步采集。

**功能：**

* 主从同步，实现相干相位采集
* 按板卡跟踪数据并统计
* 可配置板卡 IP
* 独立控制每块板卡的通道

**复杂度：** Python ⭐⭐⭐ | C++ ⭐⭐⭐⭐

|

.. tabs::

    .. tab:: Python

        **实现：** :rp-github:`adc_2_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/adc_2_stream.py>`

        .. code-block:: python

            import streaming
            
            # Define board IPs (master + slaves)
            hosts = ['192.168.0.114', '192.168.0.108']
            
            # Connect to all boards
            client = streaming.ADCStreamClient()
            client.connect(hosts)
            
            # Configure master board
            master = hosts[0]
            client.sendConfig(master, 'adc_decimation', '64')
            client.sendConfig(master, 'channel_state_1', 'ON')
            client.sendConfig(master, 'channel_state_2', 'ON')
            
            # Clone configuration to slaves
            for slave in hosts[1:]:
                client.cloneConfig(master, slave)
            
            # Start synchronized streaming
            client.startStreaming()

    .. tab:: C++

        **实现：** :rp-github:`stream_adc_2.cpp → <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_adc_2.cpp>`

        .. code-block:: cpp

            #include "adc_streaming.h"
            
            // Define board IPs (master + slaves)
            std::vector<std::string> hosts = {"192.168.0.114", "192.168.0.108"};
            
            // Connect to all boards
            ADCStreamClient client;
            client.connect(hosts);
            
            // Configure master board
            std::string master = hosts[0];
            client.sendConfig(master, "adc_decimation", "64");
            client.sendConfig(master, "channel_state_1", "ON");
            client.sendConfig(master, "channel_state_2", "ON");
            
            // Clone configuration to slaves
            for (size_t i = 1; i < hosts.size(); i++) {
                client.cloneConfig(master, hosts[i]);
            }
            
            // Start synchronized streaming
            client.startStreaming();

|

DAC Streaming 示例
***********************

从计算机向 Red Pitaya 高速模拟输出连续生成波形。

.. note::

    以下代码片段突出展示关键功能。完整的可运行示例（含完整错误处理和文档）请查看各节中的实现链接。

单通道 WAV 输出
==========================

从 WAV 音频文件生成信号并传输到 DAC 输出。

.. tabs::

    .. tab:: Python

        .. grid:: 1
            :gutter: 2

            .. grid-item-card:: **DAC Waveform Streaming**
                :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/python-api/Streaming/dac_1_stream.py
                :link-type: url

                从 WAV 文件向 DAC 输出传输自定义波形。
                
                * 可配置 DAC 速率（最高 125 MS/s）
                * 重复模式（有限或无限）
                * 支持 16 位样本格式
                
                **复杂度：** ⭐⭐

        |

        **主要功能：**

        .. code-block:: python

            import streaming
            import numpy as np
            from scipy.io.wavfile import write
            
            # Generate waveform and save as WAV
            t = np.linspace(0., 1., 1024)
            data = 32767 * np.sin(2. * np.pi * frequency * t)
            write('waveform.wav', sample_rate, data.astype(np.int16))

            # Configure and stream
            client = streaming.DACStreamClient()
            client.sendConfig('dac_rate', '125000000')  # 125 MS/s
            client.setRepeat(2)  # Repeat 2 times
            client.startStreaming('./waveform.wav')

        **完整实现：** :rp-github:`dac_1_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_1_stream.py>`

    .. tab:: C++

        .. grid:: 1
            :gutter: 2

            .. grid-item-card:: **C++ DAC Waveform Streaming**
                :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_1.cpp
                :link-type: url

                使用 WAV 文件进行高性能波形生成。
                
                * 支持预先生成的 WAV 文件
                * 高效样本缓冲
                * 可配置播放模式
                
                **复杂度：** ⭐⭐⭐

        |

        **主要功能：**

        .. code-block:: cpp

            #include "dac_streaming.h"
            
            // Generate sine wave and write WAV
            std::vector<int16_t> samples = generateSineWave(1000.0, 4096, 1.0);
            writeWAV("waveform.wav", 4096, samples);
            
            // Configure and stream
            DACStreamClient client;
            client.sendConfig("dac_rate", "125000000");  // 125 MS/s
            client.setRepeat(2);  // Repeat 2 times
            client.startStreaming("./waveform.wav");

        **完整实现：** :rp-github:`stream_dac_1.cpp → <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_1.cpp>`

|

立体声 DAC 输出
==================

将立体声信号同步传输到两个 DAC 通道。

**功能：**

* 立体声 WAV 文件生成
* 每个通道独立波形
* 无限循环播放
* 同步输出时序

**复杂度：** ⭐⭐⭐

|

.. tabs::

    .. tab:: Python

        **实现：** :rp-github:`dac_2_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_2_stream.py>`

        .. code-block:: python

            import streaming
            import numpy as np
            from scipy.io.wavfile import write
            
            # Create stereo waveform (2 channels)
            stereo = np.vstack((channel1_data, channel2_data)).transpose()
            write('stereo.wav', sample_rate, stereo)

            # Stream with infinite repeat
            client = streaming.DACStreamClient()
            client.sendConfig('dac_rate', '262144')
            client.setRepeatInf(True)
            client.startStreaming('./stereo.wav')

    .. tab:: C++

        **实现：** :rp-github:`stream_dac_2.cpp → <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_2.cpp>`

        .. code-block:: cpp

            #include "dac_streaming.h"
            
            // Generate stereo sine waves
            std::vector<int8_t> left = generate8bitSine(1000.0, 262144, 1.0);
            std::vector<int8_t> right = generate8bitSine(1000.0, 262144, 1.0);
            
            // Write stereo WAV and stream
            writeStereoWAV("stereo.wav", 262144, left, right);
            
            DACStreamClient client;
            client.sendConfig("dac_rate", "262144");
            client.setRepeatInf(true);
            client.startStreaming("./stereo.wav");

|

直接内存模式
===================

直接从内存缓冲区传输波形，实现零延迟播放。

**功能：**

* 零文件 I/O 开销
* 直接上传到 FPGA 内存
* 实时波形生成
* 独立通道控制

**复杂度：** ⭐⭐⭐

|

.. tabs::

    .. tab:: Python

        **实现：** :rp-github:`dac_3_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_3_stream.py>`

        .. code-block:: python

            import streaming
            import numpy as np
            
            # Generate waveform in memory
            waveform_data = (32767 * np.sin(2. * np.pi * t)).astype(np.int16).tolist()

            # Load directly to FPGA memory
            client = streaming.DACStreamClient()
            client.setMemory16Bit(1, waveform_data)  # Channel 1
            client.setMemory16Bit(2, waveform_data)  # Channel 2
            
            # Start streaming from memory (no file needed)
            client.startStreamingFromMemory()

    .. tab:: C++

        **实现：** :rp-github:`stream_dac_3.cpp → <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_3.cpp>`

        .. code-block:: cpp

            #include "dac_streaming.h"
            
            // Generate waveform in memory
            std::vector<int16_t> waveform = generateSineWave(1000.0, 32768, 1.0);
            
            // Load directly to FPGA memory
            DACStreamClient client;
            client.setMemory16Bit(1, waveform);  // Channel 1
            client.setMemory16Bit(2, waveform);  // Channel 2
            
            // Start streaming from memory (no file needed)
            client.startStreamingFromMemory();

|

API 参考
**************

有关 Streaming 客户端类、方法和回调系统的详细信息：

.. toctree::
    :maxdepth: 1

    streaming_api_reference

|

其他资源
*********************

* :ref:`Streaming 应用文档 <streaming_top>`
* :ref:`配置指南 <streaming_configuration_top>`
* :ref:`性能限制 <streaming_limits>`
* :ref:`性能优化 <streaming_performance_optimization>` - 禁用 Web 界面以获得最佳性能
* :ref:`多板同步 <x-ch_streaming>`
* :rp-github:`报告问题或请求示例 <RedPitaya-Examples/issues>`

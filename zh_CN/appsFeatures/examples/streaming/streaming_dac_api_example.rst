.. _streaming_dac_api_example:

DAC API 流式传输教程
############################

本教程演示如何使用流式传输客户端库将波形数据传输到 Red Pitaya 的 DAC 输出端。
你将学习如何生成自定义波形、配置播放参数，以及使用 API 高效地传输信号。

.. contents:: Table of contents
    :local:
    :backlinks: top

|

概述
=========

本示例展示了 DAC 流式传输的完整实现，包括：

* 自定义波形生成（正弦波示例）
* 可配置的 DAC 采样率（最高 125 MS/s）
* 支持 WAV 文件格式的波形数据
* 重复模式配置（有限次或无限次）
* 通过回调实时监控流式传输
* 自动播放控制与同步

**完整源代码：** :rp-github:`在 GitHub 上查看 stream_dac_1.py → <RedPitaya-Examples/blob/main/python-api/Streaming/stream_dac_1.py>`

|

准备工作
==============

.. TODO fix picture

**硬件：**

    - Red Pitaya 设备（任意型号）

.. figure:: ../../../img/STEMlab125-14V1-0.svg
    :width: 400
    :align: center

**软件：**

    - Python 3.8 或更高版本 / C++ 编译器
    - Red Pitaya 流式传输库（包含在 :ref:`Streaming command line client <streaming_pc_clients>` 中）
    - Python：NumPy 和 SciPy 库：``pip install numpy scipy``
    - Red Pitaya 上正在运行流式传输应用（参阅 :ref:`Quick Start <streaming_top>`）

|

关键概念
=============

架构
-------------

本示例使用**基于回调的架构**监控 DAC 流式传输：

.. code-block:: console

    Your Computer                           Red Pitaya
    +---------------------+                +------------------+
    | DACStreamClient     |    TCP/IP      | Streaming Server |
    |   |                 |--------------->|   |              |
    |   +--> connect()    |                |   +--> FPGA DAC  |
    |   +--> sendConfig() |                |                  |
    |   +--> startStream()|                |   Deep Memory    |
    |                     |                |   Buffer (4 MB)  |
    | Callback Class      |                +------------------+
    |   +--> sentPack()   |---> Monitors data sent
    |         +--> Count  |
    +---------------------+

|

.. note::

    以下代码示例为便于理解而进行了简化。完整的生产就绪代码（包含全面的错误处理）请参阅 :rp-github:`GitHub 上的完整示例 <RedPitaya-Examples/blob/main/python-api/Streaming/stream_dac_1.py>`。

DAC 速率配置
-----------------------

Red Pitaya DAC 的基准速率为 **125 MS/s**。你可以配置精确的采样率：

.. math::

    \text{DAC Rate} \leq 125\text{ MS/s}

**常用配置：**

.. list-table::
    :header-rows: 1
    :widths: 30 35 35

    * - DAC 速率
      - 每秒采样数
      - 使用场景
    * - 125 MS/s
      - 125,000,000
      - 最大带宽
    * - 62.5 MS/s
      - 62,500,000
      - 高速信号
    * - 15.625 MS/s
      - 15,625,000
      - 音频范围信号
    * - 1 MS/s
      - 1,000,000
      - 低频控制

|

实现演练
===========================

步骤 1：生成自定义波形
----------------------------------

首先创建要输出的波形数据。本示例生成正弦波并将其保存为 WAV 文件：

.. tabs::

    .. tab:: Python

        .. code-block:: python

            import numpy as np
            from scipy.io.wavfile import write

            # Waveform parameters
            waveform_frequency = 1          # 1 Hz sine wave
            waveform_samples = 1024 * 4     # 4096 samples
            wav_filename = "sin.wav"

            # Generate sine wave
            t = np.linspace(0., 1., waveform_samples)
            amplitude = np.iinfo(np.int16).max  # Maximum int16 value
            data = amplitude * np.sin(2. * np.pi * waveform_frequency * t)

            # Save as WAV file (16-bit PCM format)
            write(wav_filename, waveform_samples, data.astype(np.int16))
            print(f"Waveform saved to '{wav_filename}'")

    .. tab:: C++

        .. code-block:: cpp

            #include <fstream>
            #include <vector>
            #include <cmath>

            // WAV file header structure
            struct WavHeader {
                char riff[4] = {'R', 'I', 'F', 'F'};
                uint32_t fileSize;
                char wave[4] = {'W', 'A', 'V', 'E'};
                char fmt[4] = {'f', 'm', 't', ' '};
                uint32_t fmtSize = 16;
                uint16_t audioFormat = 1;  // PCM
                uint16_t numChannels = 1;
                uint32_t sampleRate;
                uint32_t byteRate;
                uint16_t blockAlign;
                uint16_t bitsPerSample = 16;
                char data[4] = {'d', 'a', 't', 'a'};
                uint32_t dataSize;
            };

            // Generate sine wave and save as WAV
            void generateWaveform(const char* filename, int samples) {
                std::vector<int16_t> waveform(samples);
                
                // Generate sine wave
                for (int i = 0; i < samples; i++) {
                    double t = (double)i / samples;
                    waveform[i] = 32767 * sin(2.0 * M_PI * t);
                }
                
                // Write WAV file
                WavHeader header;
                header.sampleRate = samples;
                header.byteRate = samples * 2;
                header.blockAlign = 2;
                header.dataSize = samples * 2;
                header.fileSize = 36 + header.dataSize;
                
                std::ofstream file(filename, std::ios::binary);
                file.write((char*)&header, sizeof(WavHeader));
                file.write((char*)waveform.data(), samples * 2);
            }

**要点：**

* WAV 格式使用 **16 位有符号整数** （-32768 至 32767），内部会转换为 14 位 DAC 电压（大多数板卡会忽略最低 2 位）
* WAV 文件头中的采样率不会影响 DAC 速率（在配置中单独设置）
* 如果波形大小能放入内存，则可以无缝重复

|

步骤 2：创建回调处理器
---------------------------------

实现一个回调类以监控流式传输事件：

.. tabs::

    .. tab:: Python

        .. code-block:: python

            import streaming

            class Callback(streaming.DACCallback):
                def __init__(self):
                    streaming.DACCallback.__init__(self)
                    self.counter = 0  # Count packets sent

                def sentPack(self, client, ch1_size, ch2_size):
                    """Called when data packet is sent to DAC"""
                    self.counter += 1
                    
                def connected(self, client, host):
                    print(f"DAC client connected: {host}")

                def error(self, client, host, code):
                    print(f"Error on {host}, code: {code}")
                    client.notifyStop()

                def stoppedFileEnd(self, client, host):
                    print(f"Playback finished: {host}")
                    client.notifyStop()

    .. tab:: C++

        .. code-block:: cpp

            #include "streaming.h"

            class Callback : public rp_dac_api::DACCallback {
            private:
                int counter = 0;

            public:
                void sentPack(
                    rp_dac_api::DACStreamClient *client,
                    uint64_t ch1_size,
                    uint64_t ch2_size) override 
                {
                    counter++;
                }

                void connected(
                    rp_dac_api::DACStreamClient *client,
                    std::string host) override 
                {
                    std::cout << "DAC client connected: " << host << std::endl;
                }

                void error(
                    rp_dac_api::DACStreamClient *client,
                    std::string host,
                    rp_dac_api::error_codes code) override 
                {
                    std::cout << "Error on " << host << ", code: " << (int)code << std::endl;
                    client->notifyStop();
                }

                void stoppedFileEnd(
                    rp_dac_api::DACStreamClient *client,
                    std::string host) override 
                {
                    std::cout << "Playback finished: " << host << std::endl;
                    client->notifyStop();
                }

                int getCounter() { return counter; }
            };

**回调方法：**

* ``sentPack()`` - 数据包发送到 DAC 时调用
* ``connected()`` - 客户端连接到服务器
* ``error()`` - 流式传输期间发生错误
* ``stopped*()`` - 各种停止条件（文件结束、内存错误等）

|

步骤 3：初始化流式传输客户端
-------------------------------------

创建客户端并注册回调：

.. tabs::

    .. tab:: Python

        .. code-block:: python

            # Create client and callback
            client = streaming.DACStreamClient()
            callback = Callback()
            
            # Register callback (transfers ownership to client)
            client.setCallbackFunction(callback.__disown__())
            
            # Optional: Enable verbose logging
            client.setVerbose(True)

    .. tab:: C++

        .. code-block:: cpp

            // Create client and callback
            auto client = rp_dac_api::DACStreamClient::Create();
            auto callback = new Callback();
            
            // Register callback
            client->setCallbackFunction(callback);
            
            // Optional: Enable verbose logging
            client->setVerbose(true);

|

步骤 4：连接到 Red Pitaya
-------------------------------

建立到流式传输服务器的 TCP/IP 连接：

.. tabs::

    .. tab:: Python

        .. code-block:: python

            if not client.connect():
                print("ERROR: Failed to connect to DAC streaming server")
                exit(1)
            
            print("Connected successfully")

    .. tab:: C++

        .. code-block:: cpp

            if (!client->connect()) {
                std::cerr << "ERROR: Failed to connect to DAC streaming server" << std::endl;
                return 1;
            }
            
            std::cout << "Connected successfully" << std::endl;

**连接前请确保：**

#. Red Pitaya 已通电且可通过网络访问
#. 已加载流式传输 FPGA 镜像：``overlay.sh stream_app``
#. 流式传输服务器正在运行：``streaming-server``

|

步骤 5：配置 DAC 参数
----------------------------------

设置 DAC 速率、内存分配和播放模式：

.. tabs::

    .. tab:: Python

        .. code-block:: python

            dac_rate = 125000000        # 125 MS/s
            block_size = 16384          # Network packet size
            dac_memory = 1638400        # Memory for DAC buffer

            # Configure DAC streaming
            client.sendConfig('dac_pass_mode', 'NET')
            client.sendConfig('dac_rate', f'{dac_rate}')
            client.sendConfig('block_size', f'{block_size}')
            client.sendConfig('dac_size', f'{dac_memory}')

            # Configure repeat mode
            client.setRepeatInf(False)      # False = finite repeat
            client.setRepeatCount(2)        # Repeat 2 times

    .. tab:: C++

        .. code-block:: cpp

            uint32_t dac_rate = 125000000;      // 125 MS/s
            uint32_t block_size = 16384;        // Network packet size
            uint32_t dac_memory = 1638400;      // Memory for DAC buffer

            // Configure DAC streaming
            client->sendConfig("dac_pass_mode", "NET");
            client->sendConfig("dac_rate", std::to_string(dac_rate));
            client->sendConfig("block_size", std::to_string(block_size));
            client->sendConfig("dac_size", std::to_string(dac_memory));

            // Configure repeat mode
            client->setRepeatInf(false);        // false = finite repeat
            client->setRepeatCount(2);          // Repeat 2 times

**配置参数：**

* ``dac_pass_mode`` - 设置为 ``'NET'`` 以进行网络流式传输（相对于 SD 卡文件）
* ``dac_rate`` - DAC 采样率，单位为 Hz（最大 125000000）
* ``block_size`` - 网络数据包大小，单位为字节。对于长波形，较大的大小可提高效率（短波形使用 8192-65536，长波形使用 1048576-2097152）。
* ``dac_size`` - 为 DAC 缓冲区预留的内存，单位为字节
* ``setRepeatInf()`` - ``True`` 表示连续播放，``False`` 表示有限次播放
* ``setRepeatCount()`` - 波形重复次数

|

步骤 6：启动流式传输
-------------------------

将 WAV 文件流式传输到 DAC：

.. tabs::

    .. tab:: Python

        .. code-block:: python

            # Start streaming from WAV file
            if not client.startStreamingWAV("./sin.wav"):
                print("ERROR: Failed to start DAC streaming")
                exit(1)

            print("Streaming started - outputting waveform to DAC")

            # Wait for streaming to complete
            client.wait()

            print(f"Total packets sent: {callback.counter}")

    .. tab:: C++

        .. code-block:: cpp

            // Start streaming from WAV file
            if (!client->startStreamingWAV("./sin.wav")) {
                std::cerr << "ERROR: Failed to start DAC streaming" << std::endl;
                return 1;
            }

            std::cout << "Streaming started - outputting waveform to DAC" << std::endl;

            // Wait for streaming to complete
            client->wait();

            std::cout << "Total packets sent: " << callback->getCounter() << std::endl;

**流式传输方法：**

* ``startStreamingWAV(filename)`` - 从 WAV 文件传输波形
* ``wait()`` - 阻塞，直到流式传输完成
* ``notifyStop()`` - 手动停止流式传输（从回调中调用）

|

完整示例代码
======================

组合所有步骤的完整可运行示例：

.. tabs::

    .. tab:: Python

        .. code-block:: python

            import streaming
            import numpy as np
            from scipy.io.wavfile import write

            # Callback class
            class Callback(streaming.DACCallback):
                def __init__(self):
                    streaming.DACCallback.__init__(self)
                    self.counter = 0

                def sentPack(self, client, ch1_size, ch2_size):
                    self.counter += 1
                    
                def connected(self, client, host):
                    print(f"Connected: {host}")

                def stoppedFileEnd(self, client, host):
                    print("Playback finished")
                    client.notifyStop()

            # Generate waveform
            samples = 1024 * 4
            t = np.linspace(0., 1., samples)
            data = 32767 * np.sin(2. * np.pi * t)
            write("sin.wav", samples, data.astype(np.int16))

            # Create client
            client = streaming.DACStreamClient()
            callback = Callback()
            client.setCallbackFunction(callback.__disown__())

            # Connect and configure
            if not client.connect():
                exit(1)

            client.sendConfig('dac_pass_mode', 'NET')
            client.sendConfig('dac_rate', '125000000')
            client.setRepeatCount(2)

            # Start streaming
            if not client.startStreamingWAV("./sin.wav"):
                exit(1)

            client.wait()
            print(f"Packets sent: {callback.counter}")

    .. tab:: C++

        .. code-block:: cpp

            #include "streaming.h"
            #include <iostream>
            #include <fstream>
            #include <vector>
            #include <cmath>

            // Callback class
            class Callback : public rp_dac_api::DACCallback {
            private:
                int counter = 0;

            public:
                void sentPack(rp_dac_api::DACStreamClient *client,
                             uint64_t ch1, uint64_t ch2) override {
                    counter++;
                }

                void connected(rp_dac_api::DACStreamClient *client,
                              std::string host) override {
                    std::cout << "Connected: " << host << std::endl;
                }

                void stoppedFileEnd(rp_dac_api::DACStreamClient *client,
                                   std::string host) override {
                    std::cout << "Playback finished" << std::endl;
                    client->notifyStop();
                }

                int getCounter() { return counter; }
            };

            // Generate WAV file (simplified - see Step 1 for full version)
            void generateWaveform(const char* filename, int samples) {
                // Implementation from Step 1...
            }

            int main() {
                // Generate waveform
                generateWaveform("sin.wav", 4096);

                // Create client
                auto client = rp_dac_api::DACStreamClient::Create();
                auto callback = new Callback();
                client->setCallbackFunction(callback);

                // Connect and configure
                if (!client->connect()) return 1;

                client->sendConfig("dac_pass_mode", "NET");
                client->sendConfig("dac_rate", "125000000");
                client->setRepeatCount(2);

                // Start streaming
                if (!client->startStreamingWAV("./sin.wav")) return 1;

                client->wait();
                std::cout << "Packets sent: " << callback->getCounter() << std::endl;

                return 0;
            }

|

常见问题与解决方案
============================

流式传输未启动
-------------------------

**现象：**

    - ``connect()`` 返回 False
    - 示波器上没有波形

**解决方案：**

#.  确认流式传输服务器正在 Red Pitaya 上运行：

    .. code-block:: console

        redpitaya> ps | grep streaming-server

#.  检查 FPGA 镜像是否已加载：

    .. code-block:: console

        redpitaya> overlay.sh stream_app

#. 验证网络连接和 IP 地址

|

波形削波或失真
-------------------------------

**现象：**

    - 输出信号峰值处发生削波
    - 波形形状异常

**解决方案：**

#. 检查波形幅度（int16 最大为 ±32767）
#. 验证 DAC 增益设置（仅 SIGNALlab）：``channel_gain_1`` 和 ``channel_gain_2``
#. 确保波形数据正确格式化为 16 位有符号整数
#. 使用 :ref:`校准应用 <calibration_app>` 校准 Red Pitaya 板卡

|

内存分配错误
--------------------------

**现象：**

    - 触发 ``stoppedMemError()`` 回调
    - 流式传输意外停止

**解决方案：**

#. 增大 ``dac_size`` 参数以容纳波形
#. 通过 :ref:`系统信息 <system_info>` 或 :ref:`DMM 检查预留内存部分 <DMM_change_reserved_memory>` 检查可用 DMM 内存
#. 如有必要，增加 Red Pitaya 为 DMM 分配的 DDR
#. 减小波形大小，或对大型信号使用重复模式

|

后续步骤
===========

现在你已经了解 DAC 流式传输的基础知识，可以继续：

* **自定义波形** - 生成复杂的任意信号
* **双通道** - 在 CH1 和 CH2 上输出不同信号
* **同步 ADC+DAC** - 激励响应测量
* **实时调制** - 在播放过程中更新波形

|

相关示例
=================

* :ref:`快速入门指南 <streaming_quickstart>` - 最小可运行示例
* :ref:`ADC 流式传输 <streaming_adc_api_example>` - 采集信号
* :ref:`API 参考 <streaming_api_reference>` - 完整方法文档
* :ref:`流式传输示例 <examples_streaming>` - 更多代码片段

|

完整源代码
=====================

**查看完整的生产就绪实现：** :rp-github:`在 GitHub 上查看 stream_dac_1.py → <RedPitaya-Examples/blob/main/python-api/Streaming/stream_dac_1.py>`

GitHub 版本包括：

* 完整的错误处理和验证
* 详细的内联注释
* 额外的回调处理器
* 配置示例

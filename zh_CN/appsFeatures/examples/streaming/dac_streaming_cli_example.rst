.. _stream_dac_cli_example:

#####################################
DAC 流式传输示例（命令行）
#####################################

本示例演示如何使用 **rpsa_client** 命令行工具在 DAC 输出端生成自定义正弦波信号。
本教程涵盖从创建波形到将其流式传输至 Red Pitaya 的完整流程。

.. note::

    本教程使用 **rpsa_client** 命令行工具，而不是 Python/C++ API。有关基于 API 的 DAC 流式传输，请参阅 :ref:`DAC API Streaming Tutorial <streaming_dac_api_example>`。

.. contents:: Table of contents
    :local:
    :backlinks: top

|

准备工作
**************

开始本示例前，请确保具备以下条件：

* OS 版本为 2.07-43 或更高版本的 Red Pitaya 板卡
* 计算机上已安装 :ref:`命令行客户端 <stream_command_client>`
* 已为 DAC 流式传输预留足够的 :ref:`DMM 内存 <deepMemoryMode>` （建议至少 100 MB）
* Python 3 以及 numpy 和 scipy.io.wavfile 库（用于创建波形）
* 可通过 :ref:`SSH 访问 <ssh>` 访问 Red Pitaya 板卡

|

概述
*********

本示例将引导你完成以下步骤：

1. 在 Python 中创建自定义正弦波波形
2. 建立到 Red Pitaya 的 SSH 连接
3. 加载 FPGA 并启动流式传输应用
4. 配置 DAC 流式传输参数
5. 启动 DAC 流式传输

本示例使用 **one-pack mode** 以获得最大性能：完整波形放入 DDR 内存，从而支持完整的 125 MS/s 输出速率。有关网络流式传输限制，请参阅 :ref:`流式传输性能限制 <streaming_limits>`。

|

分步教程
**********************

步骤 1：创建自定义波形
==================================

创建一个 Python 脚本，生成包含 1024 个采样点的正弦波信号。该波形将保存为 WAV 文件。

.. code-block:: python

    import numpy as np
    from scipy.io import wavfile
    import matplotlib.pyplot as plt

    # Waveform parameters
    N = 1024                                        # Number of samples in a period
    num_periods = 1                                 # Number of periods in the signal
    num_bits = 16
    max_val = 2**(num_bits-1) - 1                   #  32767
    min_val = -2**(num_bits-1)                      # -32768

    # Generate sine wave
    t = np.linspace(0, 1, N*num_periods)*2*np.pi
    y = np.sin(num_periods*t)*max_val               # FPGA divides the signal by 4

    # Convert to signed 16-bit integers
    y_signed16 = np.int16(y)

    # Optional: Plot to verify waveform
    plt.plot(y_signed16)
    plt.title('Custom waveform')
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.show()

    # Save as WAV file
    sample_rate = 44100                             # (Doesn't matter) Standard audio sample rate
    wavfile.write('arb_waveform_signed16.wav', sample_rate, y_signed16)
    
    print(f"Waveform created with {len(y_signed16)} samples")
    print(f"File size: {len(y_signed16) * 2} bytes")

将此脚本保存为 ``create_waveform.py`` 并运行：

.. code-block:: console

    python create_waveform.py

这将在当前目录中创建 ``arb_waveform_signed16.wav``。

|

步骤 2：建立 SSH 连接
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

步骤 3：加载 FPGA 并启动流式传输应用
===================================================

通过 SSH 连接后，加载流式传输 FPGA 镜像并启动流式传输服务器：

.. code-block:: console

    redpitaya> overlay.sh stream_app
    redpitaya> streaming-server

你应看到 LED 2 亮起且 LED 0 闪烁，这表示流式传输应用正在运行。

.. note::

    保持此 SSH 终端打开。后续步骤需要流式传输服务器持续运行。

|

步骤 4：获取并编辑配置文件
=============================================

在计算机上打开新的终端或命令提示符窗口（不要关闭 SSH 会话），然后进入命令行客户端的安装目录。

**下载配置文件：**

.. code-block:: console

    computer> .\rpsa_client.exe -c -g F

配置文件将下载到命令行客户端的 ``configs`` 文件夹。

|

**编辑配置文件：**

使用文本编辑器打开下载的配置文件（通常类似于 ``streaming_config.json``）。

在本示例中，使用生成的波形将 DAC 流式传输配置为最大速率：

.. code-block:: javascript

    {
        "dac_streaming" : {
            "channel_gain_1" : "X1",
            "dac_pass_mode" : "DAC_NET",
            "dac_rate" : 125000000,
            "file_sd" : "arb_waveform_signed16.wav",
            "file_type_sd" : "WAV",
            "repeat" : "DAC_REP_ON",
            "repeatCount" : 1,
            ...
        },
        "memory_manager" : {
            "block_size" : 8388608,
            "dac_size" : 104857600,
            ...
        }
    }

关键参数：

* ``dac_rate: 125000000`` - 125 MS/s 输出速率（波形放入内存时）
* ``block_size: 8388608`` - 8 MiB 网络数据包大小（支持的最大值）
* ``dac_size: 104857600`` - 为 DAC 缓冲区预留 100 MiB
* ``repeat: "DAC_REP_ON"`` - 启用波形重复
* ``repeatCount: 1`` - 重复次数（也可使用无限模式）

完整配置选项和 :ref:`DAC 速率限制 <streaming_limits>` 请参阅 :ref:`DAC 配置参考 <stream_dac_config>`。

.. note::

    1 MiB = 1024×1024 Bytes = 2^20 Bytes = 1,048,576 Bytes。这里使用 Mebibytes（MiB）而非 Megabytes（MB），以避免与十进制系统混淆。

将编辑后的配置文件保存为 ``config_dac.json``。

|

**上传配置文件：**

将编辑后的配置文件上传到 Red Pitaya 板卡：

.. code-block:: console

    computer> .\rpsa_client.exe -c -s F -f .\configs\config_dac.json

|

步骤 5：启动 DAC 流式传输
=================================

现在使用命令行客户端启动 DAC 流式传输。DAC 流式传输将在 OUT1 上生成正弦波信号。

.. code-block:: console

    computer> .\rpsa_client.exe -o -f wav -d <path_to_wav_file>\arb_waveform_signed16.wav -r inf

将 ``<path_to_wav_file>`` 替换为 WAV 文件的实际路径。

例如：

.. code-block:: console

    computer> .\rpsa_client.exe -o -f wav -d C:\Users\YourName\Documents\arb_waveform_signed16.wav -r inf

参数说明：

* ``-o`` - 输出（DAC 流式传输模式）
* ``-f wav`` - WAV 文件格式
* ``-d <path>`` - 数据文件路径
* ``-r inf`` - 无限重复

|

步骤 6：验证输出
===========================

现在可以使用以下方式验证 OUT1 上的正弦波输出：

* 连接到输出端的示波器
* Red Pitaya 示波器应用
* 频谱分析仪

输出应为纯净的正弦波，其频率由下式确定：

.. math::

    f_{out} = \frac{dac\_rate}{N} = \frac{125,000,000}{1024} \approx 122,070 \text{ Hz}

|

步骤 7：停止流式传输
============================

要停止 DAC 流式传输，请在命令行客户端终端中按 ``Ctrl+C``。

|

故障排除
****************

未生成波形
========================

**问题：** 没有输出信号

**解决方案：**

1. 确认流式传输服务器正在 Red Pitaya 上运行
2. 检查配置文件是否已成功上传
3. 确保 WAV 文件路径正确
4. 确认已分配足够内存（配置中的 ``dac_size``）
5. 检查波形文件是否损坏

|

数据丢失或信号不稳定
==============================

**问题：** 信号出现毛刺或不连续

**解决方案：**

1. **确保波形完全放入预留的 DDR 内存** （文件大小 < dac_size）
   
   * 波形完全放入预留区域时，Red Pitaya 可以全速生成数据（125 MSps）
   * 如果文件大于预留区域，将持续流式传输到板卡，从而显著降低性能和最大输出采样速率
   * 这是避免毛刺并实现最佳性能的最有效方法

2. 使用真正的流式模式时降低 ``dac_rate``
3. 将 ``block_size`` 增大到 8 MB
4. 确保波形至少包含 1024 个采样点
5. 检查网络稳定性

|

配置错误
=====================

**问题：** 配置文件被拒绝

**解决方案：**

1. 使用 JSON 验证器检查 JSON 语法
2. 检查所有参数值是否在有效范围内
3. 确保内存分配不超过预留的 DMM 大小
4. 确认文件路径和名称正确

|

变体与扩展
***************************

多个周期
=================

要生成多个正弦波周期，请修改 Python 脚本：

.. code-block:: python

    num_periods = 10                                # 10 periods
    t = np.linspace(0, num_periods, N*num_periods)*2*np.pi
    y = np.sin(t)*max_val

|

不同波形
====================

修改生成方程即可生成其他波形：

**方波：**

.. code-block:: python

    y = np.sign(np.sin(num_periods*t))*max_val

**锯齿波：**

.. code-block:: python

    from scipy import signal
    y = signal.sawtooth(num_periods*t)*max_val

**三角波：**

.. code-block:: python

    from scipy import signal
    y = signal.sawtooth(num_periods*t, width=0.5)*max_val

|

双通道输出
===================

创建包含两个通道的 WAV 文件，以同时使用 OUT1 和 OUT2：

.. code-block:: python

    # Generate two different waveforms
    y1 = np.sin(num_periods*t)*max_val              # OUT1: sine
    y2 = np.sin(2*num_periods*t)*max_val            # OUT2: sine at 2x frequency
    
    # Stack as stereo (2 channels)
    y_stereo = np.column_stack((y1, y2)).astype(np.int16)
    
    wavfile.write('stereo_waveform.wav', sample_rate, y_stereo)

|

后续步骤
***********

* 尝试不同的波形和参数
* 了解 :ref:`DAC 配置 <stream_dac_config>` 以获得更多控制选项
* 通过 :ref:`禁用 Web 界面 <streaming_performance_optimization>` 优化性能
* 查看 :ref:`数据生成限制 <stream_dac_limitations>` 以了解性能边界
* 尝试与 :ref:`ADC 流式传输 <stream_adc_config>` 组合，创建信号处理环路
* 探索 :ref:`高级配置 <stream_advanced_config>` 进行微调

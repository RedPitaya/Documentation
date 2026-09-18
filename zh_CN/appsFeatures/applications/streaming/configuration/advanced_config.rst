.. _stream_advanced_config:

#########################
高级配置
#########################

本节介绍 Streaming 应用的高级配置选项，包括端口号和配置文件管理。

.. contents:: 目录
    :local:
    :backlinks: top

|

.. _stream_port_numbers:

端口配置
*******************

数据流设置使用应用中设定的固定值：

.. tabs::

    .. group-tab:: OS 版本 2.07-43 或更高版本

        * 18900 - ADC 数据流服务器
        * 18901 - 配置服务器
        * 18902 - 广播服务器
        * 18903 - DAC 数据流服务器

    .. group-tab:: OS 版本 1.04-28 至 2.05-37

        * 8900 - ADC 数据流服务器
        * 8901 - 配置服务器
        * 8902 - 广播服务器
        * 8903 - DAC 数据流服务器

.. note::

    旧版 OS 的 Web 界面中包含 **Port** 设置，用户可在其中指定数据流的网络端口号。现在端口号固定为上述值。

|

配置文件
*******************

可以通过 Web 界面 UI 设置配置，随后配置会存储在 Red Pitaya 的以下位置之一：

* **/root/.streaming_config** （较旧 OS 版本）
* **/root/.config/redpitaya/apps/streaming/streaming_config.json** （OS 版本 2.00 及更高版本）

|

配置文件格式
==========================

.. tabs::

    .. group-tab:: OS 版本 3.00-57 或更高版本

        配置文件采用 JSON 格式，包含以下参数：

        .. code-block:: json
        
            {
                "adc_streaming" : 
                {
                    "adc_capture_time" : "ON",
                    "adc_decimation" : 32,
                    "adc_pass_mode" : "NET",
                    "channel_ac_dc_1" : "DC",
                    "channel_ac_dc_2" : "DC",
                    "channel_ac_dc_3" : "DC",
                    "channel_ac_dc_4" : "DC",
                    "channel_attenuator_1" : "A_1_1",
                    "channel_attenuator_2" : "A_1_1",
                    "channel_attenuator_3" : "A_1_1",
                    "channel_attenuator_4" : "A_1_1",
                    "channel_state_1" : "ON",
                    "channel_state_2" : "OFF",
                    "channel_state_3" : "OFF",
                    "channel_state_4" : "OFF",
                    "data_type_sd" : "RAW",
                    "format_sd" : "WAV",
                    "resolution" : "BIT_16",
                    "samples_limit_sd" : 0,
                    "use_calib" : "ON"
                },
                "dac_streaming" : 
                {
                    "channel_gain_1" : "X1",
                    "channel_gain_2" : "X1",
                    "dac_pass_mode" : "DAC_NET",
                    "dac_rate" : 31250000,
                    "file_sd" : "",
                    "file_type_sd" : "WAV",
                    "repeat" : "DAC_REP_ON",
                    "repeatCount" : 0
                },
                "memory_manager" : 
                {
                    "adc_size" : 0,
                    "block_size" : 1048576,
                    "dac_size" : 268435456,
                    "gpio_size" : 0
                }
            }

    .. group-tab:: OS 版本 2.07-43 至 2.07-51

        配置文件已更新，使所有设置更便于用户使用，但现在与旧版本不兼容。

        .. code-block:: json

            {
                "adc_streaming" : 
                {
                    "adc_decimation" : 2,
                    "adc_pass_mode" : "NET",
                    "channel_ac_dc_1" : "DC",
                    "channel_ac_dc_2" : "DC",
                    "channel_ac_dc_3" : "DC",
                    "channel_ac_dc_4" : "DC",
                    "channel_attenuator_1" : "A_1_1",
                    "channel_attenuator_2" : "A_1_1",
                    "channel_attenuator_3" : "A_1_1",
                    "channel_attenuator_4" : "A_1_1",
                    "channel_state_1" : "ON",
                    "channel_state_2" : "OFF",
                    "channel_state_3" : "OFF",
                    "channel_state_4" : "OFF",
                    "data_type_sd" : "RAW",
                    "format_sd" : "WAV",
                    "resolution" : "BIT_8",
                    "samples_limit_sd" : 1000000,
                    "use_calib" : "ON"
                },
                "dac_streaming" : 
                {
                    "channel_gain_1" : "X1",
                    "channel_gain_2" : "X1",
                    "dac_pass_mode" : "DAC_FILE",
                    "dac_rate" : 125000000,
                    "file_sd" : "sine.wav",
                    "file_type_sd" : "WAV",
                    "repeat" : "DAC_REP_OFF",
                    "repeatCount" : 1
                },
                "memory_manager" : 
                {
                    "adc_size" : 134217728,
                    "block_size" : 8388608,
                    "dac_size" : 134217728,
                    "gpio_size" : 134217728
                }
            }

.. note::

    **Memory Manager** 文件大小的单位为 Bytes。
    1 MiB = 1024*1024 Bytes = 2^20 Bytes = 1048576 Bytes。我们使用 Mebibytes（MiB）而不是 Megabytes（MB），以避免与十进制系统混淆。

|

配置参数
=========================

ADC 数据流参数
-------------------------

* **adc_capture_time** - 将时间戳信息保存到文件（"ON" 或 "OFF"）。
* **adc_decimation** - 抽取因子（1、2、4、8、16、17、18、...、65536）。
* **adc_pass_mode** - 数据流模式（网络使用 "NET"，本地 SD 卡使用 "FILE"）。
* **channel_ac_dc_X** - 通道 X 的 AC/DC 耦合（"AC" 或 "DC"）- *仅适用于 SIGNALlab 250-12*。
* **channel_attenuator_X** - 通道 X 的输入衰减（"A_1_1" 表示 1:1，"A_1_20" 表示 1:20）。
* **channel_state_X** - 启用/禁用通道 X（"ON" 或 "OFF"）。
* **data_type_sd** - SD 卡存储的数据格式（"RAW" 或 "VOLTS"）。
* **format_sd** - SD 卡存储的文件格式（"WAV"、"TDMS" 或 "BIN"）。
* **resolution** - ADC 分辨率（"BIT_8" 或 "BIT_16"）。
* **samples_limit_sd** - 要采集的采样数（0 表示无限制）。
* **use_calib** - 使用校准（"ON" 或 "OFF"）。

|

DAC 数据流参数
-------------------------

* **channel_gain_X** - 通道 X 的输出增益（"X1" 或 "X5"）。
* **dac_pass_mode** - 数据流模式（网络使用 "DAC_NET"，本地 SD 卡使用 "DAC_FILE"）。
* **dac_rate** - DAC 输出速率，单位为 Hz（例如 125 MS/s 对应 125000000）。
* **file_sd** - DAC 数据流源文件名。
* **file_type_sd** - 文件格式（"WAV" 或 "TDMS"）。
* **repeat** - 重复模式（"DAC_REP_OFF"、"DAC_REP_ON" 或 "DAC_REP_INF"）。
* **repeatCount** - 重复次数（repeat 为 "DAC_REP_ON" 时）。

|

内存管理器参数
--------------------------

* **adc_size** - ADC 数据流的保留内存，单位为 Bytes。
* **block_size** - 网络数据包大小，单位为 Bytes。
* **dac_size** - DAC 数据流的保留内存，单位为 Bytes。
* **gpio_size** - GPIO 数据流的保留内存，单位为 Bytes（尚未实现）。

|

管理配置文件
******************************

使用命令行客户端
===============================

可以使用 :ref:`命令行客户端 <stream_command_client>` 管理配置文件：

**从 Red Pitaya 下载配置文件：**

.. code-block:: console

    .\rpsa_client.exe -c -g F

下载的配置文件位于命令行客户端的 *configs* 文件夹中。

**将配置文件上传到 Red Pitaya：**

.. code-block:: console

    .\rpsa_client.exe -c -s F -f .\configs\config_dac.json

|

手动编辑
===============

也可以通过 :ref:`SSH <ssh>` 直接在 Red Pitaya 上手动编辑配置文件：

.. code-block:: bash

    ssh root@<IP_ADDRESS or .LOCAL_ADDRESS>
    nano /root/.config/redpitaya/apps/streaming/streaming_config.json

编辑后重启 Streaming 应用，使更改生效。

|

配置验证
=========================

手动编辑配置文件时，请确保：

1. **有效的 JSON 语法** - 使用 JSON 验证器检查文件。
2. **正确的参数值** - 参见上方参数说明。
3. **内存约束** - 总内存分配（adc_size + dac_size + gpio_size）不应超过保留的 DMM 区域。
4. **兼容的设置** - 确保抽取、速率和分辨率设置与 :ref:`数据流限制 <streaming_limits>` 兼容。

|

后续步骤
***********

* 尝试包含配置文件编辑的 :ref:`DAC 数据流示例 <stream_dac_cli_example>`。
* 了解 :ref:`命令行客户端用法 <stream_command_client>`。
* 查看 :ref:`数据流限制 <streaming_limits>`，验证配置。

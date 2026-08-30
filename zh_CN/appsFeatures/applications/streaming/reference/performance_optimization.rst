.. _streaming_performance_optimization:

#########################
性能优化
#########################

本指南介绍如何优化 Red Pitaya，以实现最大数据流性能。

.. contents:: Table of contents
    :local:
    :backlinks: top

|

1. 概述
************

要实现最大数据流性能，尤其是在高采样率或多通道情况下，系统级优化必不可少。影响最大的一项优化是禁用 Web 界面，这可以释放大量 CPU 资源和网络带宽。

.. note::

    在以下情况下，这些优化尤其重要：
    
    * 以高于 10 MS/s 的采样率进行数据流传输
    * 同时使用多个通道
    * 长时间进行数据流传输
    * 在较低规格的 Red Pitaya 型号上运行
    * 接近 :ref:`62.5 MB/s 网络传输限制 <streaming_limits>`

|

2. 快速开始：禁用 Web 界面
****************************************

优化数据流的最快方式：

.. code-block:: bash

    systemctl stop redpitaya_nginx
    systemctl disable redpitaya_nginx

这会立即停止 Web 界面，并阻止它在下次启动时运行。

稍后恢复 Web 界面：

.. code-block:: bash

    systemctl enable redpitaya_nginx
    systemctl start redpitaya_nginx

.. note::

    For complete service management instructions, including starting the SCPI server, automatic boot configuration, and troubleshooting, see the :ref:`Service Management Guide <service_management>`.

|

3. 其他优化
*****************************

内存分配
==================

Red Pitaya 板卡共有 512 MB DDR3 RAM。请为数据流缓冲区分配足够的 :ref:`深度存储模式（DMM） <deepMemoryMode>` 内存，同时为 Linux 运行保留足够内存：

* **最小值：** 基本数据流使用 100 MB。
* **推荐值：** 高速数据流使用 256 MB。
* **最大值：** 400 MB（至少为 Linux OS 运行保留 100 MB）。

.. note::

    始终为 Linux 操作系统保留至少 100 MB RAM。为数据流分配过多内存可能导致系统不稳定或崩溃。

请在禁用 Web 界面前通过 Web 界面配置 DMM 分配，或通过 SSH 手动配置：

.. code-block:: bash

    nano /root/.config/redpitaya/apps/streaming/streaming_config.json

有关内存分配和限制的更多信息，请参见 :ref:`深度存储模式 <deepMemoryMode>`。

|

网络配置
======================

要获得最大吞吐量：

1.  **使用有线以太网** （而不是 Wi-Fi）- 高速数据流需要千兆以太网。
2.  **使用路由器** - 当前数据流不支持直接连接 PC。
3.  **确认链路速度** 为 1 Gbps：

    .. code-block:: bash

        ethtool eth0

    在输出中查找 ``Speed: 1000Mb/s``。如果速度更低（100 Mbps 或 10 Mbps），请检查以太网电缆和交换机/路由器能力。

|

降低系统负载
======================

减少后台进程：

1. 关闭不必要的 SSH 连接（每个连接都会消耗资源）
2. 停止其他 Red Pitaya 应用
3. 不需要时禁用 Web 界面（参见上面的“快速开始”章节）

详情请参见 :ref:`服务管理 <service_management>`。

|

采样率限制
===================

请注意 :ref:`可实现的最大速率 <streaming_limits>`：

* **理论最大值：** 125 MB/s（1 Gbps 以太网）
* **实际网络限制：** ~62.5 MB/s（可实现的数据流速率）
* **单通道：** 最高 31.25 MS/s（62.5 MB/s ÷ 2 bytes/sample）
* **双通道：** 每通道最高 15.625 MS/s（合计 31.25 MS/s）

.. note::

    由于 Red Pitaya 的抽取限制，无法测试绝对最大数据流速率。持续网络数据流的实际限制约为 62.5 MB/s。
    修改 FPGA 固件并使用自定义软件可能实现更高速度，但这超出了典型使用范围（用户报告自定义配置最高可达 100 MB/s）。

超过这些限制需要：

* 减少活动通道数
* 使用本地 SD 卡存储，而不是网络数据流
* 增大抽取因子（降低采样率）

|

4. 工作流建议
*****************************

开发阶段
==================

在开发和测试期间：

1. 保持 Web 界面 **启用**，以便配置
2. 使用 Web 界面：

   * 配置数据流参数
   * 设置 DMM 内存分配
   * 测试基本功能

3. 监控性能并识别瓶颈

|

生产阶段
=================

对于生产数据流或关键测量：

1. 通过 Web 界面 **配置所有设置**
2. 使用 :ref:`rpsa_client <stream_command_client>` **下载配置**
3. **禁用 Web 界面** 以获得最大性能
4. 在目标采样率下 **验证数据流稳定性**
5. 对所有数据流操作 **使用命令行客户端**

命令行工作流请参见 :ref:`CLI 示例 <streaming_examples_top>`。

|

5. 验证
*****************

优化后验证性能：

检查服务状态
=====================

确认 Web 界面已停止：

.. code-block:: bash

    systemctl status redpitaya_nginx

预期输出：

.. code-block:: text

    ● redpitaya_nginx.service - Red Pitaya Nginx Web Server
         Active: inactive (dead)

|

测试数据流性能
============================

以目标采样率执行测试采集：

.. tabs::

    .. tab:: Command Line Client

        .. code-block:: bash

            rpsa_client -s -h <red_pitaya_ip> -f ./output/ -t wav

    .. tab:: Python API

        .. code-block:: python

            import streaming
            
            client = streaming.Streaming()
            # Configure and test streaming
            # Monitor for data loss warnings

在数据流期间监视系统资源：

.. code-block:: bash

    top

关注以下内容：

* CPU usage <80% during streaming
* No memory swapping
* Stable network throughput

|

6. Troubleshooting
********************

优化后仍然丢失数据
================================

如果优化后仍然出现数据丢失：

1.  **Reduce sample rate** - May be exceeding network bandwidth
2.  **Check decimation settings** - Ensure correct calculation:
   
    .. code-block:: text
   
        Sample rate = 125 MS/s ÷ decimation
        Network usage = sample_rate × channels × 2 bytes

3.  **Verify network quality** - Run ``ethtool eth0`` to check link
4.  **Increase DMM memory** - Provides more buffering
5.  **Check for packet loss:**

    .. code-block:: bash

        netstat -s | grep -i "packet.*loss"

|

无法重新启用 Web 界面
===============================

如果 Web 界面无法重新启动：

1.  Check service status:

    .. code-block:: bash

        systemctl status redpitaya_nginx

2.  Look for errors in logs:

    .. code-block:: bash

        journalctl -u redpitaya_nginx -n 50

3.  Restart the service:

    .. code-block:: bash

        systemctl restart redpitaya_nginx

4.  Reboot if necessary:

    .. code-block:: bash

        reboot

更多故障排除信息请参见 :ref:`服务管理 <service_management>`。

|

性能仍然较差
=======================

如果性能没有改善：

1. **检查硬件能力** - 较旧的板卡可能存在限制
2. **检查网络基础设施** - 使用不同的交换机/网线进行测试
3. **更新 Red Pitaya OS** - 较新版本包含性能改进
4. **检查配置** - 错误设置可能限制性能
5. **检查温度降频** - 确保散热充分

有关详细性能边界，请参见 :ref:`数据流限制 <streaming_limits>`。

|

7. Related Topics
*******************

* :ref:`Service Management <service_management>` - Complete guide to managing Red Pitaya services
* :ref:`Streaming Performance Limits <streaming_limits>` - Theoretical performance boundaries
* :ref:`Deep Memory Mode <deepMemoryMode>` - Memory allocation for streaming
* :ref:`Command Line Client <stream_command_client>` - Streaming without web interface
* :ref:`Network Configuration <sw_network>` - Optimize network settings

|

8. Additional Resources
*************************

* :ref:`Streaming Application Documentation <streaming_top>`
* :ref:`CLI Examples <examples_streaming>` - Command-line streaming workflows
* :ref:`Configuration Guide <streaming_configuration_top>` - Detailed parameter reference
* :ref:`Technical Details <streaming_technical_details>` - How streaming works internally

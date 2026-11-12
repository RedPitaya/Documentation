
.. _stream_util:

流式传输应用工具
===============================

也可以通过命令行启动流式传输服务器。

.. tabs::

    .. group-tab:: OS 版本 2.00 或更高

        .. code-block:: console

            root@rp-f0a235:~# streaming-server -h
            Usage:
                    streaming-server [-b] [-f PATH] [-p PORT] [-s PORT] [-v]
                    streaming-server [--background] [--file=PATH] [--port=PORT] [--search_port=PORT] [--verbose]

                    --background          -b        Run service in background.
                    --file=PATH           -f FILE   Path to configuration file.
                                                    By default uses the config file /root/.config/redpitaya/apps/streaming/streaming_config.json.
                    --verbose             -v        Displays information.

启动服务器请执行以下步骤：

#.  加载用于流式传输的 FPGA 镜像。

    .. tabs::

        .. group-tab:: OS 版本 2.00 或更高

            .. code-block:: console

                redpitaya> overlay.sh stream_app

        .. group-tab:: OS 版本 1.04 或更低

            .. code-block:: console

                redpitaya> cat /opt/redpitaya/fpga/fpga_streaming.bit > /dev/xdevcfg
                redpitaya> /opt/redpitaya/sbin/mkoverlay.sh stream_app

    .. note::

        **SIGNALlab 250-12** 使用 **stream_app_250** FPGA 镜像。

#.  准备配置文件。

    .. note::

        在 2.00 版本中，配置文件已移至新位置：**/root/.config/redpitaya/apps/streaming/streaming_config.json**

#.  启动控制台应用。

    .. code-block:: console

        root@rp-f07167:/# streaming-server -c /root/.streaming_config
        streaming-server started
        Lost rate: 0 / 763 (0 %)
        Lost rate: 0 / 766 (0 %)
        Lost rate: 0 / 766 (0 %)
        Lost rate: 0 / 766 (0 %)

在 Web 应用中编辑参数时，流式传输配置会自动创建并保存到文件 **/root/.streaming_config**。


.. note::

    对 Web 应用的任何更改都会自动修改配置文件。如果要保存配置，请复制该文件。

.. note::

    服务器可以在后台启动。为此请使用 -b 参数。在此模式下，应用可以作为系统启动时的服务使用。应用的服务信息会保存到 syslog 文件（默认情况下 Red Pitaya 未安装 Syslog）。

.. note::

    流式传输始终会创建三个文件：

        * 第一个文件存储流式传输的数据
        * 第二个文件存储流式传输过程的日志
        * 第三个文件存储流式传输期间丢失数据包的日志


数据流式传输
----------------

流式传输服务器运行后，即可开始从 ADC 采集数据并将数据传输到 Red Pitaya 板卡的 DAC。有关更多信息，请参阅 :ref:`数据流控制应用 <streaming_top>` 文档。

|

源代码
------------

|streaming app|.

流式传输提供两种客户端版本：适用于 Linux 和 Windows 操作系统的控制台客户端与桌面客户端。你可以从 Red Pitaya 自带的 Web 流式传输应用下载它们。
你也可以在 Mac OS 下使用 :ref:`QT Creator <comStreaming>` 根据源文件构建客户端。

.. |streaming app| replace:: :rp-github:`数据流控制应用源代码 <RedPitaya/tree/master/apps-tools/streaming_manager>`.

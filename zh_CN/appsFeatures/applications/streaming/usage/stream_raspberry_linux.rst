.. _stream_raspberry_linux:

将数据流式传输到 Raspberry Pi Linux
====================================

.. TODO add picture

将 Red Pitaya **rpsa streaming client** 下载并解压到 Raspberry Pi 板后，即可从直接运行于 Raspberry Pi 上的 Python 代码访问流式数据。

.. note::

    Raspberry Pi 上流式客户端的功能与 Red Pitaya 上相同。但需要注意，流式传输性能可能因 Raspberry Pi 板的硬件能力而异。在使用 Raspberry Pi 流式客户端进行数据采集前，建议检查系统要求和性能基准。

    由于 CPU 性能、内存和网络接口等硬件能力存在差异，Raspberry Pi 上的流式传输速度可能低于 Red Pitaya。建议在实际使用的 Raspberry Pi 型号上测试流式传输性能，并相应调整设置，以获得最佳性能。


#.  从 **Data stream control** Web 界面 **下载“Red Pitaya command line streaming client”**。客户端位于板卡本身，可以从此处下载。

    .. figure:: ../img/streaming_pc_clients_raspberry.png
        :width: 600
        :align: center

#.  **解压下载的文件**。
#.  在终端中使用 ``scp`` 命令 **将客户端上传到 Raspberry Pi**。客户端应上传到 ``/home/root/`` 目录。
#.  在终端中使用 ``ssh`` 命令 **建立到 Raspberry Pi 的 SSH 连接**。

    .. code-block:: console

        ssh root@<Raspberry_Pi_IP_address>

#.  在终端运行以下命令，**使客户端可执行**：

    .. code-block:: console

        chmod +x rpsa_client convert_tool

#.  **加载** ``stream_app`` **FPGA 镜像**：

    .. code-block:: console

        raspberrypi> overlay.sh stream_app

#.  在 Raspberry Pi 命令行中 **获取并编辑配置文件**。

    .. code-block:: console

        raspberrypi> ./rpsa_client -c -g F -v
        raspberrypi> nano ./configs/config_<Raspberry_Pi_IP_address>.json

#.  使用所需设置 **更新配置文件**。

    .. code-block:: console

        raspberrypi> ./rpsa_client -c -s F -f ./configs/config_<Raspberry_Pi_IP_address>.json -v

#.  **启动流式传输服务器**。

    .. code-block:: console

        raspberrypi> ./rpsa_client -s -f bin -m raw -l 1024 -v

有关配置参数的更多信息，请参阅 :ref:`rpsa_client 文档 <streaming_rpsa_client>`。

|

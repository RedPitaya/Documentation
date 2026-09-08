.. _stream_redpitaya_linux:

将数据流式传输到 Red Pitaya Linux
====================================

.. TODO add picture

将 Red Pitaya **rpsa streaming client** 下载并解压到 Red Pitaya 板后，即可从直接运行于 Red Pitaya 上的 Python 代码访问流式数据。

.. note::

    Red Pitaya 上流式客户端的功能与 :ref:`rpsa_client 文档 <streaming_rpsa_client>` 中描述的完全相同。但需要注意，由于数据保存到 SD 卡，而 SD 卡的读写速度相比计算机存储设备 :ref:`更低 <streaming_limits>`，流式传输过程的性能会低于计算机上的性能。


#.  从 **Data stream control** Web 界面 **下载“Red Pitaya command line streaming client”**。客户端位于板卡本身，可以从此处下载。

    .. figure:: ../img/streaming_pc_clients_redpitaya.png
        :width: 600
        :align: center

#.  **解压下载的文件**。
#.  在终端中使用 ``scp`` 命令 **将客户端上传到 Red Pitaya**。客户端应上传到 ``/home/root/`` 目录。
#.  在终端中使用 ``ssh`` 命令 **建立到 Red Pitaya 的 SSH 连接**。

    .. code-block:: console

        ssh root@<Red_Pitaya_IP_address>

#.  在终端运行以下命令，**使客户端可执行**：

    .. code-block:: console

        chmod +x rpsa_client convert_tool

#.  **加载** ``stream_app`` **FPGA 镜像**：

    .. code-block:: console

        redpitaya> overlay.sh stream_app

#.  在 Red Pitaya 命令行中 **获取并编辑配置文件**。

    .. code-block:: console

        redpitaya> ./rpsa_client -c -g F -v
        redpitaya> nano ./configs/config_<Red_Pitaya_IP_address>.json

#.  使用所需设置 **更新配置文件**。

    .. code-block:: console

        redpitaya> ./rpsa_client -c -s F -f ./configs/config_<Red_Pitaya_IP_address>.json -v

#.  **启动流式传输服务器**。

    .. code-block:: console

        redpitaya> ./rpsa_client -s -f bin -m raw -l 1024 -v

有关配置参数的更多信息，请参阅 :ref:`rpsa_client 文档 <streaming_rpsa_client>`。

|

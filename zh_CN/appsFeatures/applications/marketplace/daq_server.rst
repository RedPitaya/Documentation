.. _daq_server_app:

*********************
Red Pitaya DAQ 服务器
*********************

此应用支持以最高 15.625 MS/s 的速率连续生成和测量信号，这是 Red Pitaya 标准镜像无法实现的。
此外，该软件支持同步由多台 Red Pitaya 组成的集群（兼容 :ref:`X 通道系统 <x-ch_streaming>`）。该项目包含以下部分：

    -   适用于 RedPitaya 的 Alpine Linux 镜像
    -   FPGA 镜像
    -   可在 RedPitaya 上使用的客户端库（以 C 实现）
    -   通过 TCP/IP 访问功能的 SCPI 服务器
    -   用于访问服务器的 SCPI 客户端
    
有关 Red Pitaya DAQ 服务器的更多信息：

    -   |DAQ server docs|
    -   |DAQ server Github|
  
.. |X-channel| raw:: html

   <a href="https://redpitaya.com/product/stemlab-125-14-x-channel-system/" target="_blank">X 通道</a>
   
.. |DAQ server Github| raw:: html

   <a href="https://github.com/IBIResearch/RedPitayaDAQServer?tab=readme-ov-file" target="_blank">DAQ 服务器 Github</a>

.. |DAQ server docs| raw:: html

   <a href="https://ibiresearch.github.io/RedPitayaDAQServer/dev/" target="_blank">DAQ 服务器文档</a>

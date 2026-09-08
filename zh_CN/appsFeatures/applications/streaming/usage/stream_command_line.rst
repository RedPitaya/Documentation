.. _stream_command_client:

远程流式传输（命令行客户端）
=======================================

使用远程流式传输选项时，数据会通过网络传输到远程计算机。当所需数据处理超出 Red Pitaya 板卡的处理能力、必须借助远程计算机上更强大的工具完成时，此选项非常有用。
通过命令行客户端进行流式传输是最高效的数据传输方式，可实现尽可能高的数据传输速率。

命令行客户端支持 Windows 和 Linux 操作系统，并支持 :ref:`多板卡流式传输 <multiboard_stream>`。

.. tip::

    **要获得最高流式传输性能**，请在开始传输前禁用 Red Pitaya Web 界面，以释放系统资源和网络带宽。
    详情请参阅 :ref:`性能优化指南 <streaming_performance_optimization>`。

.. tabs::

    .. group-tab:: OS 2.07-48 or newer

        #.  **为计算机下载“命令行流式传输客户端”**。客户端位于板卡本身，可直接从板卡下载。

            .. figure:: ../img/streaming_cmd_clients_200_23.png
                :width: 1000
                :align: center

        #.  **启动 Streaming 应用**，可通过 Web 界面或 :ref:`命令行 <stream_util>` 启动。

        #.  **配置流属性**并点击 **Start**

            .. figure:: ../img/streaming_adc_network_200_23.png
                :width: 1000
                :align: center

                示例：在 CH1 和 CH2 上进行流式传输，16-bit 分辨率、100 ksps、TCP

        #.  在远程计算机上通过 ``Command Line`` 或 ``Terminal`` 运行流式传输客户端（从 Web 界面复制 IP 地址，并选择所需文件格式）。

            .. tabs::

                .. group-tab:: WAV

                    将配置文件发送到板卡，并开始将数据流式传输到远程计算机上的 WAV 文件：

                    .. code-block:: console

                        rpsa_client.exe -c -h 192.168.1.29 -s F -f ./configs/config_adc.json -v
                        rpsa_client.exe -s -h 192.168.1.29 -f wav -d ./output

                    .. figure:: ../img/client_com_line_wav_300_57.png
                        :width: 600
                        :align: center

                    按 ``Ctrl+C`` 可停止数据流式传输。

                    创建的 wav 文件可在 |Audacity| 或其他支持 WAV 文件类型的程序中读取或查看：

                    .. figure:: ../img/audacity.png
                        :width: 600
                        :align: center

                .. group-tab:: TDMS

                    .. code-block:: console

                        rpsa_client.exe -c -h 192.168.1.29 -s F -f ./configs/config_adc.json -v
                        rpsa_client.exe -s -h 192.168.1.29 -f tdms -d ./output

                    .. figure:: ../img/client_com_line_tdms_300_57.png
                        :width: 600
                        :align: center

                    按 ``Ctrl+C`` 可停止数据流式传输。

                    创建的 tdms 文件可在 |DIAdem| 或其他支持 TDMS 文件类型的程序中读取或查看。

                    .. figure:: ../img/diadem_tdms_file_viewer.png
                        :width: 600
                        :align: center

                .. group-tab:: BIN

                    .. code-block:: console

                        rpsa_client.exe -c -h 192.168.1.29 -s F -f ./configs/config_adc.json -v
                        rpsa_client.exe -s -h 192.168.1.29 -f bin -d ./output


                    .. figure:: ../img/client_com_line_bin_300_57.png
                        :width: 600
                        :align: center


                    应用会将板卡数据以二进制（BIN）格式保存。

                    可使用 :ref:`convert_tool <streaming_convert_tool>` 应用转换二进制文件。

                .. group-tab:: CSV

                    .. code-block:: console

                        rpsa_client.exe -c -h 192.168.1.29 -s F -f ./configs/config_adc.json -v
                        rpsa_client.exe -s -h 192.168.1.29 -f csv -d ./output


                    .. figure:: ../img/client_com_line_csv_300_57.png
                        :width: 600
                        :align: center


                    应用会将板卡数据以二进制（BIN）格式保存，然后使用
                    the :ref:`convert_tool <streaming_convert_tool>` application.

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    可使用 :ref:`convert_tool <streaming_convert_tool>` 应用转换二进制文件。

                    创建的 CSV 文件可使用任何文本编辑器、电子表格编辑器或其他支持 CSV 文件类型的应用打开：

                    .. figure:: ../img/csv_view.png
                        :width: 600
                        :align: center

                .. group-tab:: OS 版本 2.00-23 至 2.07-43

        #.  **为计算机下载“命令行流式传输客户端”**。客户端位于板卡本身，可直接从板卡下载。

            .. figure:: ../img/streaming_cmd_clients_200_23.png
                :width: 1000
                :align: center

        #.  **启动 Streaming 应用**，可通过 Web 界面或 :ref:`命令行 <stream_util>` 启动。

        #.  **配置流属性**并点击 **Start**。

            .. figure:: ../img/streaming_adc_network_200_23.png
                :width: 1000
                :align: center

                示例：在 CH1 和 CH2 上进行流式传输，16-bit 分辨率、100 ksps、TCP

        #.  在远程计算机上通过 ``Command Line`` 或 ``Terminal`` 运行流式传输客户端（从 Web 界面复制 IP 地址，并选择所需文件格式）。

            .. tabs::

                .. group-tab:: WAV

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t wav

                    .. figure:: ../img/tcp_client.png
                        :width: 600
                        :align: center

                    按 ``Ctrl+C`` 可停止数据流式传输。

                    创建的 wav 文件可在 |Audacity| 或其他支持 WAV 文件类型的程序中读取或查看：

                    .. figure:: ../img/audacity.png
                        :width: 600
                        :align: center

                .. group-tab:: TDMS

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t tdms

                    .. figure:: ../img/tcp_client2.png
                        :width: 600
                        :align: center

                    按 ``Ctrl+C`` 可停止数据流式传输。

                    创建的 tdms 文件可在 |DIAdem| 或其他支持 TDMS 文件类型的程序中读取或查看。

                    .. figure:: ../img/diadem_tdms_file_viewer.png
                        :width: 600
                        :align: center

                .. group-tab:: CSV

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t csv -s 100000 -v


                    .. figure:: ../img/tcp_client3.png
                        :width: 600
                        :align: center


                    应用会将板卡数据以二进制（BIN）格式保存。

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    可使用 :ref:`convert_tool <streaming_convert_tool>` 应用转换二进制文件。

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    创建的 CSV 文件可使用任何文本编辑器、电子表格编辑器或其他支持 CSV 文件类型的程序打开：

                    .. figure:: ../img/csv_view.png
                        :width: 600
                        :align: center

                .. group-tab:: OS 版本 2.00-15 或更早

        #.  **为计算机下载流式传输客户端**。客户端位于板卡本身，可直接从板卡下载。

            .. figure:: ../img/download_client_104.png
                :width: 800
                :align: center

        #.  **启动 Streaming 应用**，可通过 Web 界面或 :ref:`命令行 <stream_util>` 启动。

        #.  **配置流属性**并点击 **RUN**。

            .. figure:: ../img/streaming_network_104.png
                :width: 300
                :align: center

            示例：在 IN1 上进行流式传输，16-bit 分辨率、5 MS/s、TCP

        #.  在远程计算机上通过 ``Command Line`` 或 ``Terminal`` 运行流式传输客户端（从 Web 界面复制 IP 地址，并选择所需文件格式）。

            .. tabs::

                .. group-tab:: WAV

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t wav

                    .. figure:: ../img/tcp_client.png
                        :width: 600
                        :align: center

                    按 ``Ctrl+C`` 可停止数据流式传输。

                    创建的 wav 文件可在 |Audacity| 或其他支持 WAV 文件类型的程序中读取或查看：

                    .. figure:: ../img/audacity.png
                        :width: 600
                        :align: center

                .. group-tab:: TDMS

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t tdms

                    .. figure:: ../img/tcp_client2.png
                        :width: 600
                        :align: center

                    按 ``Ctrl+C`` 可停止数据流式传输。

                    创建的 tdms 文件可在 |DIAdem| 或其他支持 TDMS 文件类型的程序中读取或查看。

                    .. figure:: ../img/diadem_tdms_file_viewer.png
                        :width: 600
                        :align: center

                .. group-tab:: CSV

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t csv -s 100000 -v


                    .. figure:: ../img/tcp_client3.png
                        :width: 600
                        :align: center


                    应用会将板卡数据以二进制（BIN）格式保存。

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    可使用 :ref:`convert_tool <streaming_convert_tool>` 应用转换二进制文件。

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    创建的 CSV 文件可使用任何文本编辑器、电子表格编辑器或其他支持 CSV 文件类型的程序打开：

                    .. figure:: ../img/csv_view.png
                        :width: 600
                        :align: center

.. note::

    为获得最佳性能，应关闭 Web 界面，并通过终端使用 :ref:`Streaming utility <stream_util>` 启动流式传输应用。

.. warning::

    **需要配置防火墙/防病毒软件**

    ``rpsa_client`` 需要本地网络访问权限，才能检测 Red Pitaya 板卡并与其通信。如果遇到板卡检测或连接问题，请确保客户端应用已在防火墙和防病毒软件中获准访问本地网络。

    防火墙/防病毒软件阻止访问的常见症状：

    1.  **检测模式下未发现板卡：**

        .. code-block:: shell-session

            PS C:\RedPitaya\Streaming> .\rpsa_client.exe -d
            Search: DONE
            Found boards:

    2.  **连接板卡时出现找不到主机错误：**

        .. code-block:: shell-session

            2026.01.30-14.25.08.342:  Host not found
            The client did not connect

    **解决方案：** 将 ``rpsa_client`` 可执行文件加入白名单，并在防火墙/防病毒软件设置中允许其访问本地网络。最简单的解决方法是运行该程序几次，然后检查防火墙/防病毒日志，确认应用是否被阻止，并为其创建例外（可在安全软件文档中查找“网络访问故障排除”“解除被阻止的通信”等内容）。

    **需要连接路由器：** 为获得最佳性能，建议使用以太网线将 Red Pitaya 连接到路由器。通过以太网线直接连接计算机可能导致流式传输命令行客户端无法正常工作。

|

.. _streaming_rpsa_client:

``rpsa_client`` 使用说明
-----------------------------------

1.  **检测模式**

    此模式用于确定流式传输模式下本地网络中的 IP 地址。默认搜索时间约为 5 秒。

    .. literalinclude:: ../include/detectMode.txt

    如果未指定 IP，客户端会自动检测网络中的板卡，并随机连接到其中一块。

2.  **配置模式**

    此模式用于获取或设置板卡上的流式传输配置。

    .. literalinclude:: ../include/configMode.txt

    也可以单独设置变量：

    .. literalinclude:: ../include/configModeSingle.txt

3.  **远程控制模式**

    此模式用于以客户端方式控制流式传输。

    .. literalinclude:: ../include/remoteControlMode.txt

4.  **流式传输模式**

    此模式用于以客户端方式控制流式传输，同时在网络流式传输模式下捕获数据。

    .. literalinclude:: ../include/streamingMode.txt

5.  **DAC 流式传输模式**

    此模式使用文件中的信号生成输出数据。

    .. literalinclude:: ../include/dacStreamingMode.txt

6.  **配置变量**

    配置文件变量及其有效值。

    .. literalinclude:: ../include/configVariables.txt


.. note::

    如果不带参数运行控制台客户端，将打开帮助菜单，显示设置列表及其可接受的值。


配置文件位于客户端应用所在的同一文件夹中，文件名为 **config_<board_IP>.json**，包含流式传输应用的当前设置。首次请求配置文件后才会创建该文件。


.. _streaming_convert_tool:

转换工具
--------------

.. tabs::

    .. group-tab:: OS 2.07-43 or newer

        转换工具可以将 *.bin* 文件格式转换为 *.csv*、*.tdms* 或 *.wav* 文件。

        .. literalinclude:: ../include/convert_tool.txt

        转换二进制文件前，先使用以下命令检查文件信息：

        .. code-block:: bash

            .\convert_tool.exe .\<path_to_bin_file>\data_file.bin -i

        .. literalinclude:: ../include/convert_tool_info.txt

        文件信息包括数据被拆分成的段数。使用转换工具，可以只将流式文件中指定的部分转换为所需格式。

        .. code-block:: bash

            .\convert_tool.exe .\<path_to_bin_file>\data_file.bin -s 1 -e 18 -f CSV

        转换后的文件会出现在原始文件旁边。

        .. note::

            文件类型（CSV、TDMS 或 WAV）必须使用大写。

.. substitutions

.. |DIAdem| replace:: `DIAdem <https://www.ni.com/en-us/shop/data-acquisition-and-control/application-software-for-data-acquisition-and-control-category/what-is-diadem.html>`__

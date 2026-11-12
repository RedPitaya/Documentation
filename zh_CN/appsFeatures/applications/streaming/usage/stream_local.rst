.. _streaming_local:

本地流式传输（SD 卡）
==========================

使用本地流式传输选项时，数据会流式写入 Red Pitaya SD 卡上的文件。对于需要将数据本地存储、以便后续分析或处理的应用，此选项非常有用。

.. tabs::

    .. group-tab:: OS 版本 2.00-23 或更高版本

        #.  **配置流属性** 并点击 **Start**

            .. figure:: ../img/streaming_interface.png
                :width: 1000
            
            示例：在 CH1 和 CH2 上进行流式传输，采用 8 位分辨率，以 100 ksps 写入 WAV 文件格式

        #.  按 **Stop** 停止流式传输

        #.  在 **Files on SD card** 部分查看数据文件。每个数据文件有三个按钮：

            * **Log** - 特定流的数据日志；
            * **Lost** - 丢失数据包报告；
            * **Download** - 收集的数据流。

            点击所选文件，将其从 Red Pitaya 下载到计算机。

            .. figure:: ../img/streaming_interface.png
                :width: 1000
                :align: center

        #.  **在支持所选文件格式、可视化和处理的程序中打开文件**，例如使用 |DIAdem| 打开 TDMS 文件，或使用 |Audacity| 打开 WAV 文件。

            .. figure:: ../img/diadem_tdms_file_viewer.png
                :width: 800
                :align: center

    .. group-tab:: OS 版本 2.00-15 或更早版本

        #.  配置流属性并点击 **Run**

            .. figure:: ../img/streaming_interface_104.png
                :width: 800
            
            示例：在 CH1 上进行流式传输，采用 8 位分辨率，以 5.208 MS/s 写入 TDMS 文件格式

        #.  按 **STOP** 停止流式传输

        #.  点击 **Browse** 打开数据文件目录。每个数据流分为三个部分：

            * **DATA** - 收集的数据流；
            * **.log** - 特定流的数据日志；
            * **.log.lost** - 丢失数据包报告。

            点击所选文件，将其从 Red Pitaya 下载到计算机。

            .. figure:: ../img/capture.png
                :width: 600
                :align: center

        #.  在支持所选文件格式、可视化和处理的程序中打开文件，例如使用 |DIAdem| 打开 TDMS 文件，或使用 |Audacity| 打开 WAV 文件。

            .. figure:: ../img/diadem_tdms_file_viewer.png
                :width: 800
                :align: center

.. substitutions

.. |DIAdem| replace:: `DIAdem <https://www.ni.com/en-us/shop/data-acquisition-and-control/application-software-for-data-acquisition-and-control-category/what-is-diadem.html>`__

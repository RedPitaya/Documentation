.. _sdr_tx_rx_apps:

SDR 应用
################

.. note:: 

    已停用的 Red Pitaya SDR 模块已移至 :ref:`此处 <sdr_module>`。

Red Pitaya SDR 应用可将 Red Pitaya 板卡用作软件定义无线电。官方 Red Pitaya OS 提供以下应用：

    * 兼容 HPSDR 的 SDR 收发器。
    * 兼容 HPSDR 的 SDR 接收器。
    * SDR 收发器。

本节说明如何在官方 Red Pitaya OS 上运行上述应用。

.. note::
    
    上述应用是直接从 Pavel Demin 的 Alpine Linux 镜像移植而来的第三方应用。我们会在每个官方 Red Pitaya OS 版本中同步这些应用，因此它们可能不包含社区的最新更新。
    如需获取最新社区更新，请查看 |red_pitaya_notes|。


.. |red_pitaya_notes| raw:: html

   <a href="https://github.com/pavel-demin/red-pitaya-notes" target="_blank">Pavel Demin 的 Red Pitaya Notes GitHub</a>

|

兼容 HPSDR 的 SDR 收发器
=====================================

`高性能软件定义无线电 <https://openhpsdr.org/>`_\ （HPSDR）项目是一个开源软硬件项目，旨在为业余无线电爱好者和短波收听者开发模块化软件定义无线电（SDR）。

此版本的 SDR 收发器可配合 HPSDR 项目开发的软件以及支持 HPSDR/Metis 通信协议的其他 SDR 程序使用。

此 SDR 收发器模拟类似 Hermes 的 HPSDR 收发器，具有一个网络接口、两个接收器和一个发射器。

以下文档介绍了 HPSDR/Metis 通信协议：

    * :download:`Metis——工作原理 <https://raw.githubusercontent.com/TAPR/OpenHPSDR-SVN/master/Metis/Documentation/Metis-%20How%20it%20works_V1.33.pdf>`。
    * :download:`HPSDR——USB 数据协议 <https://github.com/TAPR/OpenHPSDR-SVN/raw/master/Documentation/USB_protocol_V1.58.doc>`。


软件
--------

兼容 HPSDR 的 SDR 收发器应可与大多数支持 HPSDR/Metis 通信协议的程序配合使用：

    * `PowerSDR mRX PS <https://openhpsdr.org/wiki/index.php?title=PowerSDR>`_，可从此 `链接 <https://github.com/TAPR/OpenHPSDR-PowerSDR/releases>`_ 下载。
    * 使用 ``hermes/quisk_conf.py`` 配置文件的 `QUISK <https://james.ahlstrom.name/quisk>`_。
    * `ghpsdr3-alex <https://napan.ca/ghpsdr3/index.php/Main_Page>`_ 分布式客户端—服务器系统。
    * `openHPSDR Android 应用 <https://play.google.com/store/apps/details?id=org.g0orx.openhpsdr>`_，详情见 `此链接 <https://g0orx.blogspot.com/2015/01/openhpsdr-android-application.html>`_。
    * 基于 openHPSDR Android 应用的 `Java 桌面应用 <https://g0orx.blogspot.com/2015/04/java-desktop-application-based-on.html>`_。

.. note::

    请注意，上述程序均为开源第三方软件，不由 Red Pitaya 团队维护。虽然这些程序以前可在 Red Pitaya 上运行，但项目开发者可能已停止维护。最新信息请参阅相应项目页面。


入门
---------------

要启动兼容 HPSDR 的 SDR 收发器，请在 Red Pitaya Web 界面中打开该应用，并使用兼容 HPSDR 的软件连接到 Red Pitaya 板卡。


配置输入和输出
-------------------------------

Red Pitaya 板卡上运行的 ``sdr-transceiver-hpsdr`` 程序需要六个命令行参数：

.. code-block:: bash

    sdr-transceiver-hpsdr 1 2 2 2 1 2

前四个参数对应接收器（RX1、RX2、RX3、RX4），其中 1 对应 IN1，2 对应 IN2。

最后两个参数对应输出（OUT1、OUT2），其中 1 对应 TX 信号，2 对应包络信号。

例如，要将 TX 信号发送到 OUT2，应编辑 ``start.sh`` 中的相应行，并将最后一个参数设为 1：

.. code-block:: bash

    sdr-transceiver-hpsdr 1 2 2 2 1 1

在官方 Red Pitaya OS 中，``start.sh`` 脚本位于：

    * **STEMlab 125-14** 上的 ``/opt/redpitaya/www/apps/sdr-transceiver-hpsdr`` 目录。
    * **SDRlab 122-16** 上的 ``/opt/redpitaya/www/apps/sdr-transceiver-122-88`` 目录。


更多信息
----------------

有关硬件连接、软件配置及其他详情，请参阅 Red Pitaya Notes，并选择相应的 Red Pitaya 板卡版本：

    * `STEMlab 125-14 SDR 收发器 HPSDR <https://pavel-demin.github.io/red-pitaya-notes/sdr-transceiver-hpsdr/>`_。
    * `SDRlab 122-16 SDR 收发器 HPSDR <https://pavel-demin.github.io/red-pitaya-notes/sdr-transceiver-hpsdr-122-88/>`_。

|

兼容 HPSDR 的 SDR 接收器
=====================================

此版本的 Red Pitaya SDR 接收器模拟：

    * **STEMlab 125-14**：一个带有八个接收器的 `Hermes <https://openhpsdr.org/hermes.php>`_ 模块，适用于需要八个接收器并兼容支持 HPSDR/Metis 通信协议程序的项目。
    * **SDRlab 122-16**：两个各带八个接收器的 `Hermes <https://openhpsdr.org/hermes.php>`_ 模块，适用于需要十六个接收器并兼容支持 HPSDR/Metis 通信协议程序的项目。

以下文档介绍了 HPSDR/Metis 通信协议：

    * :download:`Metis——工作原理 <https://raw.githubusercontent.com/TAPR/OpenHPSDR-SVN/master/Metis/Documentation/Metis-%20How%20it%20works_V1.33.pdf>`。
    * :download:`HPSDR——USB 数据协议 <https://github.com/TAPR/OpenHPSDR-SVN/raw/master/Documentation/USB_protocol_V1.58.doc>`。

软件
--------

兼容 HPSDR 的 SDR 接收器应可与大多数支持 HPSDR/Metis 通信协议的程序配合使用：

    * `PowerSDR mRX PS <https://openhpsdr.org/wiki/index.php?title=PowerSDR>`__，可从此 `链接 <https://github.com/TAPR/OpenHPSDR-PowerSDR/releases>`__ 下载。
    * 使用 ``hermes/quisk_conf.py`` 配置文件的 `QUISK <https://james.ahlstrom.name/quisk>`_。
    * `ghpsdr3-alex <https://napan.ca/ghpsdr3/index.php/Main_Page>`_ 分布式客户端—服务器系统。
    * `openHPSDR Android 应用 <https://play.google.com/store/apps/details?id=org.g0orx.openhpsdr>`_，详情见 `此链接 <https://g0orx.blogspot.com/2015/01/openhpsdr-android-application.html>`_。
    * 基于 openHPSDR Android 应用的 `Java 桌面应用 <https://g0orx.blogspot.com/2015/04/java-desktop-application-based-on.html>`_。

.. note::

    请注意，上述程序均为开源第三方软件，不由 Red Pitaya 团队维护。虽然这些程序以前可在 Red Pitaya 上运行，但项目开发者可能已停止维护。最新信息请参阅相应项目页面。


入门
---------------

要启动兼容 HPSDR 的 SDR 接收器，请在 Red Pitaya Web 界面中打开该应用，并使用兼容 HPSDR 的软件连接到 Red Pitaya 板卡。

要运行 CW Skimmer Server 和 Reverse Beacon Network Aggregator，请参阅下一节中的链接。


更多信息
----------------

有关硬件连接、软件配置及其他详情，请参阅 Red Pitaya Notes，并选择相应的 Red Pitaya 板卡版本：

    * `STEMlab 125-14 SDR 接收器 HPSDR <https://pavel-demin.github.io/red-pitaya-notes/sdr-receiver-hpsdr/>`_。
    * `SDRlab 122-16 SDR 接收器 HPSDR <https://pavel-demin.github.io/red-pitaya-notes/sdr-receiver-hpsdr-122-88/>`_。

|

SDR 收发器
===============

SDR 收发器由两个 SDR 接收器和两个 SDR 发射器组成。

.. tabs::

    .. tab:: STEMlab 125-14

        SDR 接收器的实现方式非常直观：

            * 将天线连接到其中一个高阻抗模拟输入。
            * 板载 ADC（125 MS/s 采样频率、14-bit 分辨率）将来自天线的 RF 信号数字化。
            * ADC 输出的数据由运行在 Red Pitaya FPGA 上的同相/正交（I/Q）数字下变频器（DDC）处理。

        有关 SDR 接收器的更多详情，请参阅此链接。

        SDR 发射器由类似模块组成，但排列顺序相反：

            * I/Q 数据由运行在 Red Pitaya FPGA 上的数字上变频器（DUC）处理。
            * 板载 DAC（125 MS/s 采样频率、14-bit 分辨率）输出 RF 信号。
            * 将天线连接到其中一个模拟输出。

        可调频率范围为 0 Hz 至 60 MHz。

        I/Q 数据速率可配置，可选设置为 20、50、100、250、500 和 1250 kSPS。

    .. tab:: SDRlab 122-16

        SDR 接收器的实现方式非常直观：

            * 将天线连接到其中一个高阻抗模拟输入。
            * 板载 ADC（122.88 MS/s 采样频率、16-bit 分辨率）将来自天线的 RF 信号数字化。
            * ADC 输出的数据由运行在 Red Pitaya FPGA 上的同相/正交（I/Q）数字下变频器（DDC）处理。

        SDR 发射器由类似模块组成，但排列顺序相反：

            * I/Q 数据由运行在 Red Pitaya FPGA 上的数字上变频器（DUC）处理。
            * 板载 DAC（122.88 MS/s 采样频率、14-bit 分辨率）输出 RF 信号。
            * 将天线连接到其中一个模拟输出。

        可调频率范围为 0 Hz 至 60 MHz。
        I/Q 数据速率可配置，可选设置为 24、48、96、192、384、768 和 1536 kSPS。


GNU Radio 入门
------------------------------

#. 将天线连接到 Red Pitaya 板卡的 IN1 连接器。
#. 在 Red Pitaya 板卡上打开 SDR Transceiver 应用。
#. 安装 `GNU Radio <https://www.gnuradio.org/>`_。
#. 克隆源代码仓库：

    .. code-block:: bash

        git clone https://github.com/pavel-demin/red-pitaya-notes

#. 运行 `GNU Radio Companion <https://wiki.gnuradio.org/index.php?title=Guided_Tutorial_GRC>`_ 并打开 AM 收发器流程图：

    .. code-block:: bash
        
        cd red-pitaya-notes/projects/sdr_transceiver_122_88/gnuradio
        export GRC_BLOCKS_PATH=.
        gnuradio-companion trx_am.grc

SDR# 与 HDSDR 入门
-----------------------------------

#. 将天线连接到 Red Pitaya 板卡的 IN1 连接器。
#. 在 Red Pitaya 板卡上打开 SDR Transceiver 应用。
#. 下载并安装 `SDR# <https://www.dropbox.com/sh/5fy49wae6xwxa8a/AAAdAcU238cppWziK4xPRIADa/sdr/sdrsharp_v1.0.0.1361_with_plugins.zip?dl=1>`_ 或 `HDSDR <https://www.hdsdr.de/>`_。
#. 下载适用于 SDR# 和 HDSDR 的 `预编译 ExtIO 插件 <https://www.dropbox.com/scl/fi/pl8gfjn2ay267or1zkohu/extio_red_pitaya.dll?rlkey=zhmv6qktymfeno8bdap94noq9&dl=1>`_。
#. 将 ``extio_red_pitaya.dll`` 复制到 SDR# 或 HDSDR 安装目录。
#. 启动 SDR# 或 HDSDR。
#. 在 SDR# 的 Source 列表中选择 Red Pitaya，或在 HDSDR 的 Options [F7] → Select Input 菜单中选择 Red Pitaya。
#. 在 SDR# 中按 Configure 图标，或在 HDSDR 中按 SDR-Device [F8] 按钮，然后输入 Red Pitaya 板卡的 IP 地址，并将 ADC 采样率设为 122.88 MSPS。
#. 在 SDR# 中按 Play 图标，或在 HDSDR 中按 Start [F2] 按钮。


更多信息
----------------

有关硬件连接、软件配置及其他详情，请参阅 Red Pitaya Notes，并选择相应的 Red Pitaya 板卡版本：

    * `STEMlab 125-14 SDR 收发器 <https://pavel-demin.github.io/red-pitaya-notes/sdr-transceiver/>`_。
    * `SDRlab 122-16 SDR 收发器 <https://pavel-demin.github.io/red-pitaya-notes/sdr-transceiver-122-88/>`_。

|

.. _sdr_macos:

macOS 兼容性
===================

Red Pitaya SDR 应用提供 **兼容 HPSDR/Metis（Hermes）** 的网络流。macOS 上的 SDR 客户端生态比 Windows 或 Linux 小，大多数常用客户端要么不原生支持 Hermes/Metis，要么需要额外配置。

macOS 上的已知问题
---------------------

* **SDR++** 在 macOS 上默认不包含 Hermes/Metis 源插件。
* 如果 Hermes 协议版本不匹配，**SparkSDR / Spark++** 可能无法发现 Red Pitaya。行为不一致（首次可用，随后崩溃）通常表明协议版本不匹配或配置文件损坏；可尝试在重新安装之间清除应用偏好设置。
* **Gqrx** 需要 SoapySDR 或 OsmoSDR 后端，无法直接连接 Red Pitaya。
* macOS 防火墙或内容与隐私设置可能会静默阻止 Hermes/Metis 协议使用的 UDP/TCP 端口。

建议方案
----------------------

1. **在 Linux 主机或 Linux 虚拟机上使用 ghpsdr3-alex（推荐）**

   在 Linux 计算机（或通过 Parallels、VMware、VirtualBox 在 Mac 上运行的 Linux 虚拟机）上安装 `ghpsdr3-alex <https://napan.ca/ghpsdr3/index.php/Main_Page>`_。将其配置为通过 Hermes/Metis 连接 Red Pitaya。ghpsdr3-alex 将作为服务器，供包括 macOS 客户端在内的众多 SDR 客户端连接，从而绕过协议不匹配问题。

2. **在 Windows 虚拟机中使用 PowerSDR mRX**

   已知使用 Red Pitaya/HAMlab 配置文件的 `PowerSDR mRX PS <https://github.com/TAPR/OpenHPSDR-PowerSDR/releases>`__ 可以可靠运行。请在 Mac 上的 Windows 虚拟机（Parallels、VMware 或 VirtualBox）中运行；如有需要，可通过远程桌面或音频/IQ 流传输到 macOS。

3. **Hermes → SoapySDR 网桥（高级）**

   SDR++ 支持 SoapySDR 后端。将 Red Pitaya 的 Hermes/Metis 流转换为兼容 SoapySDR 的源后，SDR++ 即可将 Red Pitaya 用作 Soapy 设备。撰写本文时尚无官方网桥，但可使用社区工具，或利用 ``libmetis`` / ``ghpsdr3`` 代码编写小型封装程序。此方案需要掌握 Linux 或 macOS 构建工具链。

实用参考资料
-----------------

* `HPSDR/Metis 协议文档 <https://raw.githubusercontent.com/TAPR/OpenHPSDR-SVN/master/Metis/Documentation/Metis-%20How%20it%20works_V1.33.pdf>`_
* `Pavel Demin 的 Red Pitaya Notes（社区 SDR 工具） <https://pavel-demin.github.io/red-pitaya-notes/>`_
* :ref:`Red Pitaya 软件已知问题 <known_sw_issues>`

|

作者与来源
===============

.. admonition:: 致谢

    | 本节 Red Pitaya SDR 应用的原始开发者是 Pavel Demin。
    | 我们的构建所使用的仓库：

        *   `Red Pitaya Notes <https://pavel-demin.github.io/red-pitaya-notes/>`_.

Pavel Demin 还开发了其他几款兼容 Red Pitaya 板卡的 SDR 应用，这些应用可在 Pavel Demin 的 Alpine Linux OS 镜像中获取。
有关这些应用的更多信息，请参阅 `Red Pitaya Notes <https://pavel-demin.github.io/red-pitaya-notes/>`_。

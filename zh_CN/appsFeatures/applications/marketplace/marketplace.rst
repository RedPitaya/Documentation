.. _marketplace:

################################
Marketplace 与社区贡献应用
################################

==========
概述
==========

Red Pitaya 支持全球研究人员、开发者和爱好者创建的大量社区应用。这些第三方应用扩展了 Red Pitaya 在科学研究、RF 通信、控制系统等专业场景中的能力。

**重要信息：**

.. note::

    对于 OS 2.07-43 及更高版本：应用市场已不再提供。所有独特应用将逐步迁移到官方 Red Pitaya OS，并可从主 Web 界面访问。

    对于较旧 OS 版本（2.07-43 之前）：应用市场仍可访问，但大多数应用需要更新才能兼容 OS 2.00+。请查看各应用页面获取兼容性信息。

**获取社区应用：**

社区应用不再通过应用市场分发。要安装社区应用：

1. 访问应用的社区页面（各部分中提供了链接）
2. 遵循应用作者提供的安装说明
3. 如需支持、报告错误或请求功能，请联系应用作者

.. note:: 

    Red Pitaya 团队不分发、维护或测试 Red Pitaya 社区开发的应用。我们的团队不对第三方应用承担责任。如需反馈、报告错误或获得支持，请直接联系项目作者。

|

=========================
可用应用
=========================

此处记录了以下社区应用。每个应用页面都包含开发者仓库或网站链接，可在其中找到安装说明和源代码。

**应用兼容性概览：**

下表提供社区应用的兼容性信息。有关详细要求和安装说明，请查看各应用页面。

.. list-table::
    :widths: 30 40 15 15
    :header-rows: 1

    * - 应用
      - 说明
      - OS 2.00+
      - 状态
    * - 数据采集与流式传输
      -
      -
      -
    * - DAQ Server
      - 高速连续数据采集（15.625 MS/s），支持多板同步
      - 定制 OS 镜像
      - 活跃
    * - RF 与通信
      -
      -
      -
    * - SDR (Pavel Demin)
      - 软件定义无线电收发器
      - 是 [#f1]_
      - 活跃
    * - VNA (Pavel Demin)
      - 用于 RF 测量的矢量网络分析仪
      - 是 [#f1]_
      - 活跃
    * - WSPR (Pavel Demin)
      - 面向业余无线电的弱信号传播报告器
      - 定制 OS 镜像
      - 活跃
    * - RadioBox
      - 多模式无线电收发器
      - 否
      - 已弃用
    * - Radar
      - 集成 Raspberry Pi 的开源雷达系统
      - 否
      - 停止维护
    * - 控制系统与信号处理
      -
      -
      -
    * - PyRPL (Leonhard Neuhaus)
      - 量子光学锁相放大器、数字滤波器和反馈控制
      - 是
      - 活跃
    * - Linien
      - 激光锁定
      - 是
      - 活跃
    * - Lock-in + PID (Marcelo Luda)
      - 带 PID 控制器的锁相放大器
      - 是
      - 活跃
    * - DSP Sandbox (Pau Gomez)
      - 数字信号处理开发环境
      - 定制镜像
      - 活跃
    * - LTI DSP Workbench (DashPi)
      - 线性时不变系统分析
      - 否
      - 停止维护
    * - 分析工具
      -
      -
      -
    * - Power Analysis
      - 功耗与效率测量
      - 否
      - 已弃用
    * - Frequency Response Analyzer
      - 频率响应测量与分析
      - 是
      - 已移植至官方 OS
    * - Impedance Analyzer
      - 复阻抗测量工具
      - 是
      - 已移植至官方 OS
    * - Multi-Pulse Height Analyzer (Pavel Demin)
      - 核能谱脉冲分析
      - 定制镜像
      - 活跃
    * - 科学研究
      -
      -
      -
    * - OCRA
      - 用于实时采集的开源 MRI 控制台
      - 请查看文档
      - 活跃
    * - EPICS
      - 实验物理与工业控制系统集成
      - 请查看文档
      - 活跃
    * - Qt-Based Tools
      - 面向 Red Pitaya 的 Qt 框架应用
      - 否
      - 停止维护
    * - Tesla Coil Driver
      - 音乐特斯拉线圈控制系统
      - 否
      - 停止维护
.. rubric:: 脚注

.. [#f1] Pavel Demin 的 SDR 和 VNA 应用既可在 :ref:`官方 Red Pitaya OS <sdr_tx_rx_apps>` 中访问（移植版本可能不是最新版本），也可作为其定制 alpine OS 镜像的一部分使用（最新版本）。

.. note::

    兼容性状态基于已知的最新信息。有关当前兼容性信息和安装说明，请查看各应用文档页面。

|

====================================
应用市场访问（旧版）
====================================

**对于运行早于 2.07-43 版本 OS 的用户：**

仍可通过 Red Pitaya Web 界面访问应用市场。使用应用市场：

1.  确保互联网连接：Red Pitaya 必须能够访问互联网，否则应用市场将无法打开。

    .. figure:: img/Marketplace_fail_connect.png
        :width: 600

2.  **连接到互联网：**
   
    - 通过 :ref:`Wi-Fi <wireless>` 或 :ref:`以太网电缆连接到路由器 <LAN>`
    - 如果 :ref:`直接连接到计算机 <dir_cab_connect>`，也可以配置网络直通（需要高级网络知识）


|

====================================
应用文档
====================================

.. toctree::
    :maxdepth: 2
    
    daq_server.rst
    sdr.rst
    vna.rst
    wspr.rst
    radiobox.rst
    radar.rst
    PyRPL.rst
    linien.rst
    Lock-in.rst
    dsp.rst
    lti.rst
    power_anal/power_anal.rst
    freq_res_anal/freq_res_anal.rst
    impedance_anal/impedance.rst
    multi_pulse_anal.rst
    ocra.rst
    epics.rst
    qt.rst
    tesla.rst

|

.. note::

    Red Pitaya 应用市场中部分第三方应用的代码位于 :rp-github:`Red Pitaya GitHub 仓库 - 已弃用应用 <RedPitaya/tree/master/deprecated>` 的 `deprecated` 目录中。不过，并非所有应用都托管在那里，有些应用可能拥有由原始开发者维护的独立仓库。

    上述应用由第三方开发者开发和维护。如需支持、报告错误或请求功能，请使用各应用文档页面提供的链接直接联系相应应用作者。

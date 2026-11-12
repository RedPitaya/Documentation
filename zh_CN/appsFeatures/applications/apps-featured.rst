.. _all_apps:

############
应用
############

所有 Red Pitaya 应用均基于 Web，无需安装任何本机软件。用户可通过智能手机、平板电脑或运行常见操作系统（macOS、Linux、Windows、Android 和 iOS）的 PC 上的浏览器访问这些应用。所有官方应用均可通过 :ref:`主 Web 界面 <quickstart_connect>` 访问。

本节提供所有可用 Red Pitaya 应用的完整指南：

**基础测量与分析：**

* **示波器与信号发生器** - 用于信号分析和生成的双通道示波器与波形发生器
* **频谱分析仪** - 频域分析和 FFT 测量
* **逻辑分析仪** - 数字信号捕获和协议分析
* **任意波形管理器** - 创建和管理自定义波形

**高级测量工具：**

* **Bode 分析仪** - 频率响应和增益/相位测量
* **阻抗分析仪** - 跨频率的复阻抗测量
* **LCR 测量仪** - 电感、电容和电阻测量
* **矢量网络分析仪（VNA）** - S 参数测量和 RF 特性分析

**数据采集与 RF：**

* **数据流控制** - 向 PC 高速连续传输数据
* **播放与录制** - 从文件保存和重放信号
* **SDR 收发器** - 软件定义无线电收发

**高级应用：**

* **PyRPL** - 基于 Python 的量子光学和反馈控制
* **应用市场** - 浏览和安装社区开发的应用

安装 Red Pitaya 的第三方应用时可能需要额外步骤。请参阅应用作者提供的安装指南。
有关离线安装应用的信息，请参阅 :ref:`开发者指南：手动安装应用 <manual_app_install>`。

.. toctree::
   :maxdepth: 1

   oscSigGen/osc.rst
   arb_manager/arb_manager.rst
   spectrum/spectrum.rst
   logic/logic.rst
   bode/bode.rst
   impedance/impedance.rst
   lcr_meter/lcr_meter.rst
   streaming/top.rst
   playback&record/playback&record.rst
   sdr_tx_rx/sdr_tx_rx.rst
   vna/appVNA.rst
   pyrpl/pyrpl.rst
   marketplace/marketplace.rst


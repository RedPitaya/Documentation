.. _radioBox_app:

****************************
RadioBox（Urlich Habel）
****************************

RadioBox 是在 FPGA 上实现的完整收发机。接收时，可以将天线直接连接到 SMA RF In 2 端口；在 SMA RF Out 2 端口可以监听解调信号。发射机则同时使用 SMA In/Out 1 连接器工作。如果需要外部 SDR 软件，可以在两个方向上选择 Linux AC97 声音驱动器的立体声通道，将数据馈入 FPGA 或获取数据流。要连接 SDR，可以将两个 AC97 通道设置为 QMIXers 调制的 I 和 Q 信号。

项目的更多详情请参阅以下 RadioBox Wiki 链接：

- |RadioBox|

.. warning::

   遗憾的是，作者已删除 RadioBox 相关文档及对应的 GitHub 页面，我们无法为此应用提供更多信息或支持。
   |Source Forge archive| 中仍可找到部分信息和代码。


.. note::

   RadioBox 应用可在 Red Pitaya 应用市场中获取。
   
.. |RadioBox| raw:: html

   <a href="https://github.com/DF4IAH/RedPitaya_RadioBox/wiki" target="_blank">RadioBox</a>

.. |Source Forge archive| raw:: html

   <a href="https://sourceforge.net/projects/redpitaya-radiobox/" target="_blank">RadioBox SourceForge 归档</a>

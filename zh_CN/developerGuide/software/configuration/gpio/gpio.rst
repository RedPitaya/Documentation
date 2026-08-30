################################
通用输入输出
################################

GPIOs
=====

本文介绍连接到 Zynq-7000 PS EMIO 模块的 GPIO 信号处理
这些信号通过 Linux GPIO 子系统用户空间接口作为扩展连接器 E1 上的通用输入/输出引脚访问。

有两种接口：旧版 sysfs 接口和基于字符设备的新接口。

|

引脚
====

连接到 PL 模块的引脚需要 FPGA 代码才能工作。如果在 FPGA 源码中将基于 PS 的 EMIO 信号直接连接到 FPGA 焊盘，
则可使用面向 PS 模块的 Linux 驱动进行管理。目前有两个 FPGA 项目采用此方式：classic 和 mercury。

可使用 bash 命令加载相应的 FPGA 比特流。

在当前 Red Pitaya OS 版本中，``overlay.sh`` 是生态系统使用的板卡感知加载器。它会检测板卡配置，并从
``/opt/redpitaya/fpga/<model>/<project>/`` 加载匹配的 ``fpga.bit.bin`` 和 ``fpga.dtbo`` 文件。

.. tabs::

    .. group-tab:: OS 2.00 版本

        .. code-block:: shell-session

            redpitaya> overlay.sh v0.94

    .. group-tab:: OS 1.04 或更早版本

        .. code-block:: shell-session

            redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg


虽然 Zynq SoC 提供 118 条 GPIO 线，但用户只能访问其中 16 条。这些引脚位于扩展连接器 E1 上，包括 DIO0_P 至 DIO7_P 和 DIO0_N 至 DIO7_N。
这些引脚可通过不同的编号/命名方案识别：

#. **线路编号**, 由 gpiod 工具、libgpiod 和底层字符设备接口使用
#. **sysfs 编号**, 由旧版 sysfs 接口使用，即线路编号加 906 的偏移值
#. **EMIO 信号名称**, 记录在设备树中
#. **GPIO 编号**，同样记录在设备树中
#. **引脚名称**，用于 SCPI 接口、API（带 ``RP_`` 前缀）以及 Red Pitaya 文档各处

.. note::

    使用 Zynq 7020 的 Red Pitaya 板卡型号可访问更多 GPIO 引脚：

        - *SDRlab 122-16, STEMlab 125-14 4-Input, STEMlab 125-14-Z7020-LN* - **22 pins**
        - *SIGNALlab 250-12* - **19 pins**

以下是这些编号/命名方案之间的对应关系：

.. list-table::
    :widths: 13 14 20 17 18 17
    :header-rows: 1

    * - 线路编号
      - sysfs 编号
      - FPGA 信号名称
      - EMIO 信号
      - GPIO 编号
      - 引脚名称
    * - 62 - 69
      - 968 - 975
      - exp_p_io[7:0]
      - EMIO8 - EMIO15
      - GPIO 0 - GPIO 7
      - DIO0_P - DIO7_P
    * - 70 - 77
      - 976 - 983
      - exp_n_io[7:0]
      - EMIO16 - EMIO23
      - GPIO 8 - GPIO 15
      - DIO0_N - DIO7_N

可使用 ``gpiod`` 软件包中的 ``gpioinfo`` 命令列出可用线路及其线路编号、EMIO 信号名称和 GPIO 编号：

.. code-block:: shell-session

    redpitaya> gpioinfo | grep GPIO
            line  62: "EMIO8  (GPIO 0)" unused input active-high
            line  63: "EMIO9  (GPIO 1)" unused input active-high
            ...

|

Linux 访问 GPIO
====================

SYSFS 访问
--------------

本文档用作参考：
`Linux+GPIO+Driver <https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842398/Linux+GPIO+Driver>`_


向 DIO0_P 引脚写入和读取数据的 Bash 示例（sysfs 编号 968）：

.. code-block:: shell-session

    #export pin 968
    $ echo "968" > /sys/class/gpio/export
    #set direction to output
    $ echo "out" > /sys/class/gpio/gpio968/direction
    #set pin to LOW
    $ echo "0" > /sys/class/gpio/gpio968/value
    #set pin to HIGH
    $ echo "1" > /sys/class/gpio/gpio968/value
    #set pin direction to input
    $ echo "in" > /sys/class/gpio/gpio968/direction
    #output pin value
    $ cat /sys/class/gpio/gpio968/value
    #when done with pin you should unexport it with
    $ echo 968 > /sys/class/gpio/unexport


更多信息请参阅 :rp-github:`SYSFS GPIO C example code <RedPitaya-Examples/tree/dev/gpio_sysfs>` 。

|

字符设备访问
------------------------

字符设备用户空间访问 GPIO 内核子系统已确认可在 4.8 及更高版本内核上工作。

参考： `GPIO for Engineers and Maker <https://elinux.org/images/9/9b/GPIO_for_Engineers_and_Makers.pdf>`_

.. raw:: html

    <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;">
        <iframe src="https://www.youtube.com/embed/lQRCDl0tFiQ" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
    </div>


Linux 内核在其 `tools <https://github.com/torvalds/linux/tree/master/tools/gpio>`_ 目录中包含 GPIO 工具。

我们提取了源代码，并从 ``gpio-utils.c`` 构建库，并从其他源文件构建可执行文件。

|

源代码
============

可在 GitHub 的 :rp-github:`gpio-utils 仓库中访问源代码和预编译二进制文件 <gpio-utils>`.

|


.. _bode_util:

Bode 分析仪
=============

可以在控制台中使用 Bode 分析仪。

.. note::

    环境准备方法请参阅本 :ref:`章节<bode_app>`。


.. tabs::

    .. group-tab:: OS 版本 2.00 或更高

        .. code-block:: console

            redpitaya> bode

            Bode analyzer version 2.07-494, compiled at Sat Mar 22 06:11:15 2025

            Usage:  bode [channel] [amplitude] [dc bias] [averaging] [count/steps] [start freq] [stop freq] [scale type] [probe]
            or
                    bode -calib

                    channel            Channel to generate signal on [1 / 2].
                    amplitude          Signal amplitude in V [0 - 1, which means max 2Vpp].
                    dc bias            DC bias/offset/component in V [0 - 1].
                                    Max sum of amplitude and DC bias is (0-1] V.
                    averaging          Number of samples per one measurement [>1].
                    count/steps        Number of measurements [>2].
                    start freq         Lower frequency limit in Hz [3 - 62.5e6].
                    stop freq          Upper frequency limit in Hz [3 - 62.5e6].
                    scale type         0 - linear, 1 - logarithmic.
                    probe              Probe value [1-1000].
                    -calib             Starts calibration mode. The calibration values will be saved in:/tmp/ba_calib.data
            Output: frequency [Hz], phase [deg], amplitude [dB]

要运行 Bode 实用程序，请执行以下步骤：

#.  加载 FPGA 镜像。

    .. tabs::

        .. group-tab:: OS 版本 2.00 或更高

            .. code-block:: console

                redpitaya> overlay.sh v0.94

        .. group-tab:: OS 版本 1.04 或更早

            .. code-block:: console

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg


#.  启动控制台应用。

    .. code-block:: console

        root@rp-f09508:~# bode 1 1 0 1 10 1000 100000 0
        1000.00     0.00025    0.34855
        12000.00    0.00090    0.34481
        23000.00    0.00209    0.32803
        34000.00    0.00859    0.33696
        45000.00    0.00335    0.26568
        56000.00    -0.00580   0.38830
        67000.00    -0.01751   0.36922
        78000.00    0.00635    0.32767
        89000.00    0.00521    0.38478
        100000.00   -0.00933   0.36610

|

源代码
-----------

Red Pitaya GitHub 仓库包含 Bode 实用程序的 :rp-github:`源代码 <RedPitaya/tree/master/tools/bode>`。

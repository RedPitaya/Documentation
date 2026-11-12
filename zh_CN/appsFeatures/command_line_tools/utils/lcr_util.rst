
.. _lcr_util:

LCR 测量仪
====================

可以从控制台使用 LCR 测量仪。

.. note::

    环境准备请参阅本 :ref:`章节<lrc_app>`。

.. tabs::

    .. group-tab:: OS 版本 3.00 及更高

        .. code-block:: console

            root@rp-f0b1cb:~# lcr
            LCR meter version 3.00-809, compiled at Thu Jul  2 08:50:41 2026

            Usage:  lcr freq r_shunt [-v]

                    freq               Signal frequency used for measurement in Hz.
                    r_shunt            Shunt resistor value in Ω [ 10, 100, 1000, 10000, 100000, 1000000 ]. If set to 0, Automatic ranging is used.
                    -v                 Verbose mode

            Output: Frequency [Hz], |Z|, Ohm [Ω], P [deg], Ls [H], Cs [F], Rs [Ω], Lp [H], Cp [F], Rp [Ω], Q, D, Xs [H], Gp [S], Bp [S], |Y| [S], -P [deg]

    .. group-tab:: OS 版本 2.00

        .. code-block:: console

            root@rp-f0a235:~# lcr
            LCR meter version 2.07-494, compiled at Sat Mar 22 06:11:15 2025

            Usage:  lcr freq r_shunt [-v]

                    freq               Signal frequency used for measurement Hz.
                    r_shunt            Shunt resistor value in Ohms [ 10, 100, 1000, 10000, 100000, 1000000 ]. If set to 0, Automatic ranging is used.
                    -v                 Verbose mode
                                    Automatic ranging demands Extenson module.

            Output: Frequency [Hz], |Z| [Ohm], P [deg], Ls [H], Cs [F], Rs [Ohm], Lp [H], Cp [F], Rp [Ohm], Q, D, Xs [H], Gp [S], Bp [S], |Y| [S], -P [deg]

运行 LCR 测量仪请执行以下三个步骤：

#.  如果不使用 :ref:`LCR 测量仪扩展板 <lrc_app>`，请按照下图连接分流电阻和 DUT（被测设备）。

    .. figure:: ../img/600px-Impedance_analyzer_manaul_R_Shunt.png
        :width: 600

#.  加载标准 FPGA 镜像。

    .. tabs::

        .. group-tab:: OS 版本 2.00 或更高

            .. code-block:: console

                redpitaya> overlay.sh v0.94

        .. group-tab:: OS 版本 1.04 或更低

            .. code-block:: console

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

#.  启动控制台应用。

    .. code-block:: console

        root@rp-f01c35:~# lcr 100 100000 -v
        Frequency       100 Hz
        Z       5.424000 kOmh
        Phase   1.364216 deg
        L(s)    205.533997 mH
        C(s)    -12.324000 uF
        R(s)    5.422000 kOmh
        L(p)    0.000000 H
        C(p)    0.000000 F
        R(p)    5.425000 kOmh
        Q       0.023815
        D       -41.991112
        X_s     129.141129
        G_p     0.000184
        B_p     0.000000
        |Y|     0.000184
        -P_Y    -1.364216 deg

|

源代码
-----------

Red Pitaya GitHub 仓库包含 :rp-github:`LCR 工具源代码 <RedPitaya/tree/master/tools/lcr>`。

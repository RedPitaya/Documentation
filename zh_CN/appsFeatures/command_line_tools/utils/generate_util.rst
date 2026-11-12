.. _generate_util:

信号发生器工具
========================

可以使用 generate 命令行工具控制 Red Pitaya 信号发生器。

.. tabs::

    .. group-tab:: OS version 3.00 and higher

        .. code-block:: console

            redpitaya> generate

            generate version 3.00-809-bce7a0397

            Usage: generate channel amplitude frequency[,end_frequency] [type] [-c] [-d]

                    channel         Channel to generate signal on [1, 2].
                    amplitude       Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
                    frequency       Signal frequency in Hz [0 - 62500000].
                    end_frequency   Sweep-to frequency in Hz [0 - 62500000].
                    type            Signal type [sine, sqr, tri, sweep, noise, ramp_up, ramp_down, dc, dc_neg] (default value sine).
                    -c              Disable calibration. By default calibration enabled.
                    -d              Debug FPGA registers.

            Setting the frequency to 0 will disable the generator completely.

    .. group-tab:: OS version 2.00

        .. code-block:: console

            root@rp-f0a235:~# generate
            generate version 2.07-494-d5436699b

            Usage: generate   channel amplitude frequency <type> <end frequency> <calib> <debug>

                    channel         Channel to generate signal on [1, 2].
                    amplitude       Peak-to-peak signal amplitude in Vpp [0.0 - 4.0].
                    frequency       Signal frequency in Hz [0 - 62500000].
                    type            Signal type [sine, sqr, tri, sweep, noise, dc].
                    end frequency   Sweep-to frequency in Hz [0 - 62500000].
                    calib           Disable calibration [-c]. By default calibration enabled.
                    debug           Debug FPGA registers [-d].

            Setting the frequency to 0 will disable the generator completely.

    .. group-tab:: OS version 1.00-1.04

        .. code-block:: console

            redpitaya> generate
            generate version 1.00-35-25a03ad-25a03ad

            Usage: generate channel amplitude frequency <gain> <type> <end frequency> <calib>

                channel         Channel to generate a signal on [1, 2].
                amplitude       Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
                frequency       Signal frequency in Hz [0.00 - 1.2e+08].
                gain            Gain output value [x1, x5] (default value x1).
                type            Signal type [sine, sqr, tri, sweep].
                end frequency   Sweep-to frequency in Hz [0.00 - 1.2e+08].
                calib           Disable calibration [-c]. By default calibration enabled

    .. group-tab:: OS version 0.99 or older

        .. code-block:: console

            redpitaya> generate
            generate version 0.90-299-1278

            Usage: generate   channel amplitude frequency <type>

                channel     Channel to generate a signal on [1, 2].
                amplitude   Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
                frequency   Signal frequency in Hz [0.0 - 6.2e+07].
                type        Signal type [sine, sqr, tri].


要运行信号生成工具，请执行以下步骤：

#.  加载 FPGA 镜像。

    .. tabs::

        .. group-tab:: OS version 2.00 or higher

            .. code-block:: console

                redpitaya> overlay.sh v0.94

        .. group-tab:: OS version 1.04 or older

            .. code-block:: console

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg


#.  启动控制台应用。

    .. code-block:: console

        redpitaya> generate 1 1 1000 sine
        redpitaya> generate 2 1 1000 sqr
        redpitaya> generate 1 1 1000 tri
        redpitaya> generate 2 1 1000 sweep 10000
        redpitaya> generate 1 1 1000 noise
        redpitaya> generate 2 1 1000 dc

信号发生器的性能因 Red Pitaya 型号而异。更多信息请参阅 Red Pitaya :ref:`原始一代 <rp-board-comp-orig_gen>` 或 :ref:`第二代 <rp-board-comp-gen2>` 对比表。

|

源代码
-----------

Red Pitaya GitHub 仓库包含 :rp-github:`generate 工具的源代码 <RedPitaya/tree/master/Test/generate>`。

.. _acquire_util:

.. TODO add acquire_p - split trigger mode functionality https://github.com/RedPitaya/RedPitaya/tree/master/Test/acquire_p

信号采集工具
==========================

可以使用 acquire 命令行工具采集 Red Pitaya 信号。该工具会将 ADC 缓冲区中的原始采样值输出到标准输出。用法说明如下：

acquire 工具有两种工作模式：

- **普通模式** - 工具等待触发事件，然后采集所有通道的数据。
- **分离触发模式** - 在各通道之间分离采集，每个通道拥有自己的触发器。此模式使用 acquire_p 工具。

|

acquire 工具用法
----------------------

标准 ``acquire`` 工具用法如下：

.. tabs::

    .. group-tab:: OS 版本 3.00

        .. code-block:: console

            redpitaya> acquire
            acquire Version: 3.00-809-bce7a0397

            Usage: acquire [OPTION]... SIZE <DEC>

            --equalization  -e    Use equalization filter in FPGA (default: disabled).
            --shaping       -s    Use shaping filter in FPGA (default: disabled).
            --bypass        -b    Bypass shaping filter in FPGA.
            --gain1=g       -1 g  Use Channel 1 gain setting g [lv, hv] (default: lv).
            --gain2=g       -2 g  Use Channel 2 gain setting g [lv, hv] (default: lv).
            --tr_ch=c       -t c  Enable trigger by channel. Setting c use for channels [1P, 1N, 1A, 2P, 2N, 2A, EP (external channel), EN (external channel)].
                                    P - positive edge, N -negative edge, A - any edge. By default trigger no set
            --tr_level=c    -l c  Set trigger level (default: 0).
            --hex           -x    Print value in hex.
            --volt          -o    Print value in volt.
            --int                 Interrupt-based operation mode.
            --avg                 Outputs the average value for the values in the buffer.
            --calib         -c    Disable calibration parameters
            --16bit               Enables 16Bit mode
            --hk            -k    Reset houskeeping (Reset state for GPIO). Default: disabled
            --axi           -a    Enable AXI interface. Also enable housekeeping reset. Default: disabled
            --debug         -g    Debug registers. Default: disabled
            --offset              Offset relative to the trigger pointer [-16384 .. 16384]
            --version       -v    Print version info.
            --help          -h    Print this message.
                SIZE                Number of samples to acquire [0 - 16384].
                DEC                 Decimation [1,2,4,8,16,...] (default: 1). Valid values are from 1 to 65536

    .. group-tab:: OS 版本 2.00

        .. code-block:: console

            redpitaya> acquire
            acquire Version: 2.07-651-631657660

            Usage: acquire [OPTION]... SIZE <DEC>

            --equalization  -e    Use equalization filter in FPGA (default: disabled).
            --shaping       -s    Use shaping filter in FPGA (default: disabled).
            --bypass        -b    Bypass shaping filter in FPGA.
            --gain1=g       -1 g  Use Channel 1 gain setting g [lv, hv] (default: lv).
            --gain2=g       -2 g  Use Channel 2 gain setting g [lv, hv] (default: lv).
            --tr_ch=c       -t c  Enable trigger by channel. Setting c use for channels [1P, 1N, 2P, 2N, EP (external channel), EN (external channel)].
                                    P - positive edge, N -negative edge. By default trigger no set
            --tr_level=c    -l c  Set trigger level (default: 0).
            --version       -v    Print version info.
            --help          -h    Print this message.
            --hex           -x    Print value in hex.
            --volt          -o    Print value in volt.
            --avg                 Outputs the average value for the values in the buffer.
            --calib         -c    Disable calibration parameters
            --hk            -k    Reset houskeeping (Reset state for GPIO). Default: disabled
            --axi           -a    Enable AXI interface. Also enable housekeeping reset. Default: disabled
            --debug         -g    Debug registers. Default: disabled
            --offset              Offset relative to the trigger pointer [-16384 .. 16384]
                SIZE                Number of samples to acquire [0 - 16384].
                DEC                 Decimation [1,2,4,8,16,...] (default: 1). Valid values are from 1 to 65536

        示例（使用抽取率 8 采集 1024 个样本，通道 1 使用 1:20 设置，并以电压显示结果）：

        .. code-block:: console

            redpitaya> acquire 1024 8 -1 lv -o
                -0.175803   0.000977
                0.021975    0.001099
                -0.075693   0.000977
                -0.190453   0.001099
                0.004883    0.001221
                -0.046392   0.001099
                -0.200220   0.000977
                -0.014650   0.001099
                -0.019534   0.001099
                -0.195336   0.000977
                -0.041509   0.001099
                ...

    .. group-tab:: OS 版本 1.00-1.04

        .. code-block:: console

            redpitaya> acquire

            Usage: acquire [OPTION]... SIZE <DEC>

                --equalization  -e    Use equalization filter in FPGA (default: disabled).
                --shaping       -s    Use shaping filter in FPGA (default: disabled).
                --atten1=a      -1 a  Use Channel 1 attenuator setting a [1, 20] (default: 1).
                --atten2=a      -2 a  Use Channel 2 attenuator setting a [1, 20] (default: 1).
                --dc=c          -d c  Enable DC mode. Setting c use for channels [1, 2, B(Both channels)].
                                        By default, AC mode is turned on.
                --tr_ch=c       -t c  Enable trigger by channel. Setting c use for channels [1P, 1N, 2P, 2N, EP (external channel), EN (external channel)].
                                        P - positive edge, N -negative edge. By default trigger no set
                --tr_level=c    -l c  Set trigger level (default: 0).
                --version       -v    Print version info.
                --help          -h    Print this message.
                --hex           -x    Print value in hex.
                --volt          -o    Print value in volt.
                --no_reg        -r    Disable load registers config for DAC and ADC.
                --calib         -c    Disable calibration parameters
                    SIZE                Number of samples to acquire [0 - 16384].
                    DEC                 Decimation [1,2,4,8,16,...] (default: 1). Valid values are from 1 to 65536

        示例（使用抽取率 8 采集 1024 个样本，通道 1 使用 1:20 设置，并以电压显示结果）：

        .. code-block:: console

            redpitaya> acquire 1024 8 -1 20 -o
                -0.175803   0.000977
                0.021975    0.001099
                -0.075693   0.000977
                -0.190453   0.001099
                0.004883    0.001221
                -0.046392   0.001099
                -0.200220   0.000977
                -0.014650   0.001099
                -0.019534   0.001099
                -0.195336   0.000977
                -0.041509   0.001099

    .. group-tab:: OS 版本 0.99 或更早

        .. code-block:: console

            redpitaya> acquire
            acquire version 0.90-299-1278

            Usage: acquire  size <dec>

                size     Number of samples to acquire [0 - 16384].
                dec      Decimation [1,8,64,1024,8192,65536] (default=1).


        示例（使用抽取率 8 采集 1024 个样本）：

        .. code-block:: console

            redpitaya> acquire 1024 8
                -148     -81
                -143     -84
                -139     -88
                -134     -82
                ...

运行信号采集工具的步骤如下：

#.  加载 FPGA 镜像。

    .. tabs::

        .. group-tab:: OS 版本 2.00 及更高

            .. code-block:: console

                redpitaya> overlay.sh v0.94

        .. group-tab:: OS 版本 1.04 或更早

            .. code-block:: console

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg


#.  启动控制台应用。

    .. code-block:: console

        redpitaya> acquire 1024 8 -1 20 -o
            -0.175803   0.000977
            0.021975    0.001099
            -0.075693   0.000977
            -0.190453   0.001099
            0.004883    0.001221
            -0.046392   0.001099
            -0.200220   0.000977
            -0.014650   0.001099
            -0.019534   0.001099
            -0.195336   0.000977
            -0.041509   0.001099
            ...

不同 Red Pitaya 型号的采集性能有所不同。更多信息请参阅 Red Pitaya :ref:`Original Gen 板卡比较 <rp-board-comp-orig_gen>` 或 :ref:`Gen 2 板卡比较 <rp-board-comp-gen2>`。

.. note::

    如果所有输入测量的是同一个信号，但产生了不同的测量结果，请使用 :ref:`calib utility <calib_util>` 或 :ref:`Calibration application <calibration_app>` 检查 Red Pitaya 的校准状态。

|

acquire_p 工具用法
------------------------

``acquire_p`` 工具用于在分离触发模式下捕获数据。它会将 ADC 缓冲区中的原始采样值输出到标准输出。用法说明如下：

.. tabs::

    .. group-tab:: OS 版本 3.00

        .. code-block:: console

            redpitaya> acquire_p
            Version: 3.00-809-bce7a0397

            Application for capturing data in split trigger mode.
            Usage: acquire_p [OPTION]... SIZE <DEC>
                SIZE                Number of samples to acquire [1 - 16384].
                DEC                 Decimation [1,2,4,8,16,17,18...65536] (default: 1). Valid values are from 1 to 65536

            --att1=a              Use Channel 1 attenuator setting a [1, 20] (default: 1).
            --att2=a              Use Channel 2 attenuator setting a [1, 20] (default: 1).

            --tr_ch1=c      -1 c  Enable trigger for ch 1. Setting c use for channels [N (now), 1P, 1N, 1A, 2P, 2N, 2A, EP (ext channel), EN (ext channel)].
            --tr_ch2=c      -2 c  Enable trigger for ch 2. Setting c use for channels [N (now), 1P, 1N, 1A, 2P, 2N, 2A, EP (ext channel), EN (ext channel)].
            --tr_lev1=c           Set trigger level for ch 1 (default: 0).
            --tr_lev2=c           Set trigger level for ch 2 (default: 0).

            --equalization  -e    Use equalization filter in FPGA (default: disabled).
            --shaping       -s    Use shaping filter in FPGA (default: disabled).
            --bypass        -b    Bypass shaping filter in FPGA.
            --version       -v    Print version info.
            --help          -h    Print this message.
            --hex           -x    Print value in hex.
            --volt          -o    Print value in volt.
            --calib         -c    Disable calibration parameters
            --16bit               Enables 16Bit mode
            --int                 Interrupt-based operation mode.
            --hk            -k    Reset houskeeping (Reset state for GPIO). Default: disabled
            --debug         -g    Debug registers. Default: disabled
            --offset              Offset relative to the trigger pointer [-16384 .. 16384]

|

源代码
-----------

Red Pitaya GitHub 仓库包含以下内容：

* :rp-github:`acquire 工具的源代码 <RedPitaya/tree/master/tools/acquire>`
* :rp-github:`acquire_p 工具的源代码 <RedPitaya/tree/master/tools/acquire_p>`

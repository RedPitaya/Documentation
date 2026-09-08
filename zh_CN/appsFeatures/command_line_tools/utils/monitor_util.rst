.. _monitor_util:

Monitor 实用程序
====================

访问系统寄存器
---------------------------

可以通过 Monitor 实用程序访问系统寄存器和 FPGA 寄存器。使用说明如下：

.. tabs::

    .. group-tab:: OS 版本 3.00 或更高

        .. code-block:: console

            redpitaya> monitor
            monitor version 3.00-809-bce7a0397

            Usage:
                    read addr: address
                    read addr: address-count
                    write addr: address value
                    write addr: address w value
                    read analog mixed signals: -ams
                    Showing graph of analog mixed signals: -ams_graph
                    set slow DAC: -sdac AO0 AO1 AO2 AO3 [V]
                    Clock frequency meter: -c
                    Print fpga version: -f
                    Print DTS version: -d
                    Print model name: -n
                    Print model id: -i
                    Print Housekeeping regset: -ph
                    Print Oscilloscope regset: -posc
                    Print Arbitrary Signal Generator regset: -pasg
                    Print Arbitrary Signal Generator signal from ch1: -pasg_ch1
                    Print Arbitrary Signal Generator signal from ch2: -pasg_ch2
                    Print Analog Mixed Signals regset: -pams
                    Print Daisy Chain regset: -pdaisy
                    Reserved memory for DMA: -r

    .. group-tab:: OS 版本 2.00

        .. code-block:: console

            redpitaya> monitor
            monitor version 2.07-501-e1eff7e0a

            Usage:
                    read addr: address
                    write addr: address value
                    read analog mixed signals: -ams
                    set slow DAC: -sdac AO0 AO1 AO2 AO3 [V]
                    Clock frequency meter: -c
                    Print fpga version: -f
                    Print model name: -n
                    Print model id: -i
                    Print Housekeeping regset: -ph
                    Print Oscilloscope regset: -posc
                    Print Arbitrary Signal Generator regset: -pasg
                    Print Analog Mixed Signals regset: -pams
                    Print Daisy Chain regset: -pdaisy
                    Reserved memory for DMA: -r

    .. group-tab:: OS 版本 1.04 或更早

        .. code-block:: console

            redpitaya>  monitor
            monitor version 1.03-0-ab43ad0-ab43ad0

            Usage:
                read addr: address
                write addr: address value
                read analog mixed signals: -ams
                set slow DAC: -sdac AO0 AO1 AO2 AO3 [V]


示例（读取系统寄存器）：

.. code-block:: console

    redpitaya> monitor -ams
    #ID	        Desc            Raw	            Val
    0           Temp(0C-85C)    0x00000b12	    75.670
    1	        AI0(0-3.5V)     0x00000008	    0.014
    2	        AI1(0-3.5V)     0x00000017	    0.039
    3	        AI2(0-3.5V)     0x00000008	    0.014
    4	        AI3(0-3.5V)     0x00000006	    0.010
    5	        AI4(5V0)        0x000004f9	    3.800
    6	        VCCPINT(1V0)    0x0000055e	    1.006
    7	        VCCPAUX(1V8)    0x00000995	    1.797
    8	        VCCBRAM(1V0)    0x00000561	    1.009
    9           VCCINT(1V0)     0x00000561	    1.009
    10          VCCAUX(1V8)     0x00000997	    1.798
    11          VCCDDR(1V5)     0x00000806	    1.504
    12          AO0(0-1.8V)     0x0000000f	    0.173
    13          AO1(0-1.8V)     0x0000004e	    0.900
    14          AO2(0-1.8V)     0x00000075	    1.350
    15          AO3(0-1.8V)     0x0000009c	    1.800

上述引脚的详细说明请参阅 :ref:`此处 <E1_orig_gen>`。
``-ams`` 开关可访问混合模拟信号，包括 Zynq SoC 温度、辅助模拟输入读数、电源电压和已配置的辅助模拟输出设置。可以使用 ``-SADC`` 开关通过 Monitor 实用程序设置辅助模拟输出：

.. code-block:: console

    redpitaya> monitor -sdac 0.9 0.8 0.7 0.6

.. note::

    对于配备 1 GB RAM 的板卡（SIGNALlab 250-12 和 STEMlab 125-14 Pro Z7020 Gen 2），VCCDDR 的预期电压为 1.35 V；对于其他所有板卡，则为 1.5 V。

|

访问 FPGA 寄存器
-------------------------

Red Pitaya 的信号处理基于 FPGA 和双核处理器这两个计算引擎，以有效分担任务。大多数高数据速率信号处理在 FPGA 构建模块中实现。这些模块可以使用寄存器进行参数配置。
FPGA 寄存器记录在 :ref:`Red Pitaya HDL 内存映射 <fpga_registers>` 文档中（请确保参考正确的 OS 版本）。可以使用上文所述的 Monitor 实用程序访问这些寄存器。
例如，以下 Monitor 命令序列会检查、修改并验证采集抽取参数（地址为 0x40100014）：

.. code-block:: console

    redpitaya> monitor 0x40100014
    0x00000001
    redpitaya>
    redpitaya> monitor 0x40100014 0x8
    redpitaya> monitor 0x40100014
    0x00000008
    redpitaya>

.. note::

    CPU 算法通过这些寄存器与 FPGA 通信。因此，用户应注意：读取或写入相同 FPGA 寄存器的 Red Pitaya 应用可能会产生相互干扰。不过，对于简单任务，如有需要，可以使用高级脚本（Bash、Python、MATLAB 等）调用 Monitor 实用程序直接与 FPGA 通信。

|

源代码
-----------

Red Pitaya GitHub 仓库包含 Monitor 实用程序的 :rp-github:`源代码 <RedPitaya/tree/master/tools/monitor>`。

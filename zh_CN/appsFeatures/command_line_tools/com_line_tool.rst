.. _com_line_tools:

##################
命令行工具
##################

Red Pitaya 提供命令行实用程序，可通过终端直接控制硬件。这些工具适用于脚本编写、自动化、测试以及无需 Web 界面的快速硬件交互。

.. note::

    命令行实用程序不得与 WEB 应用并行使用。

    要使 acquire、generate 和 monitor 工具正常运行，必须加载正确的 FPGA 镜像。请注意，运行应用会更改或重置已加载的 FPGA 镜像。
    要加载 FPGA 镜像，请在 Red Pitaya 上打开终端并执行以下命令：

    .. tabs::

        .. group-tab:: OS 版本 2.00 或更高

            .. code-block:: console

                redpitaya> overlay.sh v0.94
        
        .. group-tab:: OS 版本 1.04 或更早

            .. code-block:: console

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

.. toctree::
    :maxdepth: 1
   
    utils/generate_util.rst
    utils/acquire_util.rst
    utils/spectrum_util.rst
    utils/bode_util.rst
    utils/lcr_util.rst
    utils/daisy_util.rst
    utils/streaming_util.rst
    utils/monitor_util.rst
    utils/led_util.rst
    utils/calib_util.rst
    utils/filter_calib_util.rst
    utils/updater_util.rst
    utils/e3_i2c_util.rst
    utils/overlay_util.rst
    utils/profiles_util.rst
    utils/other_util.rst

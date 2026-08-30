.. _filter_calib_util:

滤波器校准工具
===========================

可以使用命令行工具访问和配置 Red Pitaya 频率均衡滤波器校准。滤波器均衡用于补偿 Red Pitaya 模拟前端的频率响应。

使用说明：

.. tabs::

    .. group-tab:: OS 版本 3.00 及更高版本

        .. code-block:: console

            root@rp-f0b1cb:~# filter_calib
            Version: 3.00-809-bce7a0397

            filter_calib -a | -e | -h [-i KK_VALUE] [-g GAIN] [-w]
            --auto                 -a      Automatic filter calibration using internal generator.
            --auto_ext             -e      Automatic filter calibration using external generator (PWM signal of 1kHz 1.8 Vpp).
            --initK=X              -i X    Sets the value for the KK parameter. The default value is 0xdFFFFF.
            --gain=X               -g X    Use gain setting X [LV, HV] (default: LV).
            --write                -w      Write new parameters to eeprom.
            --help                 -h      Print this message.

有关校准及其背后数学原理的更多信息，请参阅 :ref:`频率校准 <frequency_calibration>` 部分。

|

源代码
------------

Red Pitaya GitHub 仓库包含 :rp-github:`滤波器校准工具的源代码 <RedPitaya/tree/master/tools/filter_calib>`。


.. _daisy_util:

Daisy 实用程序
====================

Red Pitaya Daisy 实用程序是一款命令行工具，可通过 SATA 菊花链连接器同步多台 Red Pitaya 设备。该工具可启用触发和时钟同步、设置触发源模式，并配置采集和生成所用的外部触发去抖器。


.. tabs::

    .. group-tab:: OS 2.00 及更高版本

        .. code-block:: console

            redpitaya> daisy_tool

            Usage: daisy_tool -e[=State] | -o[=State] | -t[=Mode] | -c[=Mode] | -a[1.0] | -g[1.0] |-d

                    -e    Enables trigger sync over SATA daisy chain connectors.
                    -c    Enables clock sync over SATA daisy chain connectors.
                    -o    Turns GPION_0 into trigger output for selected source - acquisition or generation.
                    -t    Sets the trigger source mode. ADC/DAC.
                    -e    Enables clock and trigger sync over SATA daisy chain connectors.
                    -a    Sets ext. trigger debouncer for acquisition in μs (Value must be positive).
                    -g    Sets ext. trigger debouncer for generation in μs (Value must be positive).
                    -d    Register debug mode.

            Example:
                    ./daisy_tool -e=On -o=On -t=DAC -a2.2

            Optional parameter:
                    State = [Off | On]  Turns On or Off
                    Mode = [ADC | DAC]  Set ADC or DAC mode

            Notice: Application does not reset register settings when enabling modes.
                    If the flag does not have a parameter, it returns the value from the register.

|

源代码
------------

Red Pitaya GitHub 仓库包含 :rp-github:`daisy_tool 实用程序的源代码 <RedPitaya/tree/master/tools/daisy_tool>`。

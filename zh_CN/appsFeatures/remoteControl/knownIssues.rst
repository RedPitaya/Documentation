.. _commands_known_issues:

按 OS 版本列出的已知 SCPI 与 API 问题及变更
###################################################

这里列出了按 Red Pitaya OS 发布版本整理的已知 SCPI 与 API 命令问题及变更。

如果示例遇到问题、命令无法工作或代码无法运行，建议检查从最新 OS 发布版本到当前 OS 版本的已知问题列表，确认是否存在适用的变更。

|

如何查找每个 OS 版本的所有可用 SCPI 命令？
========================================================

使用 ``SYSTem:Help?`` （2.04-35）SCPI 命令，该命令会列出所有可用的 SCPI 命令。

也可以在此处查找板卡根据 Red Pitaya OS 版本所接受的全部 SCPI 命令：

* 最新 Beta OS：|all_os_scpi_commands|。

对于其他 Red Pitaya OS 版本，请打开上面的链接，并将分支版本改为：

* 3.00-57 - 分支 2026.1（*文件以 .cpp 结尾*）。
* 2.07-48 - 分支 2025.2（*文件以 .cpp 结尾*）。
* 2.07-43 - 分支 2025.1（*文件以 .cpp 结尾*）。
* 2.05-37 - 分支 2024.3（*文件以 .cpp 结尾*）。
* 2.04-35 - 分支 2024.2（*文件以 .cpp 结尾*）。
* 2.00-30 - 分支 2024.1（*文件以 .cpp 结尾*）。
* 2.00-23 - 分支 2023.3（*文件以 .cpp 结尾*）。
* 2.00-18 - 分支 2023.2（*文件以 .c 结尾*）。
* 2.00-15 - 分支 2023.1 - |all_os_scpi_commands_2.00-15| （*文件以 .c 结尾*）。
* 1.04-28 - 分支 2022.2（*文件以 .c 结尾*）。
* 1.04-18 - 分支 2022.1（*文件以 .c 结尾*）。

.. image:: img/All_os_scpi_commands.png
   :width: 800


.. |all_os_scpi_commands| replace:: :rp-github:`Red Pitaya GitHub - scpi-server/src/scpi-commands.cpp <RedPitaya/blob/master/scpi-server/src/scpi-commands.cpp>`

.. |all_os_scpi_commands_2.00-15| replace:: :rp-github:`Red Pitaya GitHub 2023.1- scpi-server/src/scpi-commands.c <RedPitaya/blob/Release-2023.1/scpi-server/src/scpi-commands.c>`

|

.. ! TODO - add new commands and issues to the list

.. IN-DEV
.. =======
..
.. New Commands
.. -------------
..
..
.. Command changes
.. -----------------
..
..
.. Issues
.. --------



2.05-37
=======

新增命令
-------------

* 标准采集和 DMA 的分离触发命令（当前仅限 4-Input）- 与现有命令相同，但以 "CH" 结尾。
* LCR 表命令（:ref:`LCR 模式<commands_lcr>`）。
* 返回 Numpy 数组的 DMA API 命令（``rp_AcqAxiGetDataRawNP(channel, pos, np_buffer)``、``rp_AcqAxiGetDataVNP``）。更多选项请查看 Red Pitaya 板上的 */opt/redpitaya/lib/python/rp.py*。
* 返回 Numpy 数组的采集 API 命令（``rp_AcqGetDataPosRawNP``、``rp_AcqGetDataPosVNP``、``rp_AcqGetLatestDataRawNP`` 等）。更多选项请查看 Red Pitaya 板上的 */opt/redpitaya/lib/python/rp.py*。
* 获取触发位置附近数据的采集命令 ``ACQ:SOUR<n>:DATA:TRig? <size>,<t_pos>``。
* Burst Init 和 Last 值命令：``SOUR<n>:BURS:INITValue <amplitude>`` 和 ``SOUR<n>:BURS:LASTValue <amplitude>``，功能与 ``SOUR<n>:INITValue <amplitude>`` 和 ``SOUR<n>:LASTValue <amplitude>`` 相同。
* 附加扫描命令 ``SOUR:SWeep:DEFault``。


命令变更
-----------------

* ``SYSTem:DATE "<year>-<month>-<day>"`` - 现在接受使用连字符而非逗号分隔的“标准”日期时间格式。


问题
--------

* 分离触发命令仅适用于 STEMlab 125-14 4-Input。



2.04-35
===========

新增命令
--------------

* ``SYSTem:Help?`` - displays all available SCPI commands.
* SWEEP SCPI commands (:ref:`Sweep mode extended <commands_sweep_ext>`).
* PLL SCPI commands for SIGNALlab 250-12 only (:ref:`Phase locked loop <commands_pll>`).
* ``SOUR<n>:FREQ:FIX:Direct <frequency>`` - change the frequency setting directly in the FPGA.
* ``SOUR<n>:LOAD <load_mode>`` - Select output load (50 Ohm or INF) for SIGNALlab 250-12.


命令变更
-----------------

* Changed ``ACQ:TRig:EXT:LEV`` to ``TRig:EXT:LEV`` (generation and acquisition share this command).
* Changed ``DAISY:TRIG_O:ENable`` to ``DAISY:TRig:Out:ENable``.
* Changed ``DAISY:TRIG_O:SOUR`` to ``DAISY:TRig:Out:SOUR``.

* For all SCPI commands ``TRIG`` was renamed to ``TRig`` (does not affect the backwards compatibility).
* Renamed ``SOUR:TRIG:EXT:DEBouncerUs`` to ``SOUR:TRig:EXT:DEBouncer[:US]`` (the previous command was misleading - will not be reverted).
* Renamed ``ACQ:TRIG:EXT:DEBouncerUs`` to ``ACQ:TRig:EXT:DEBouncer[:US]`` (the previous command was misleading - will not be reverted).
* ``ACQ:SOUR<n>:DATA:Start:End?`` to ``ACQ:SOUR<n>:DATA:STArt:End?`` (backwards compatible with 2.00-23 and older).
* ``ACQ:SOUR<n>:DATA:Start:N?`` to ``ACQ:SOUR<n>:DATA:STArt:N?`` (backwards compatible with 2.00-23 and older).
* ``ACQ:SOUR<n>:DATA:Last:N?`` to ``ACQ:SOUR<n>:DATA:LATest:N?`` (backwards compatible with 2.00-23 and older).


问题
----------

* Sweep 模式一旦启用就会自动开始改变频率，无论输出是否开启或是否发生生成器触发。
* ``SOUR<n>:TRIG:SOUR?`` - 陷入无限循环，不返回。
* ``SOUR<n>:FUNC?``、``SOUR<n>:VOLT?``、``SOUR<n>:Sweep:STAT?``、``SOUR<n>:Sweep:FREQ:START?`` - 均以 **"None\r\n<actual value>\r\n"** 格式返回（下一个以 ``?`` 结尾的命令会分多行返回，产生意外结果）。
* 如果尚未指定参数或接口已禁用，某些用于获取 CAN 数据的 SCPI 命令可能导致 Python 陷入无限循环（``CAN:FPGA?``、``CAN<n>:STATE?`` 等）。


2.00-30
===========

新增命令
--------------

* ``ACQ:DEC:F <decimation_ext>`` command - better version of ``ACQ:DEC`` command.
* CAN commands (:ref:`CAN <commands_can>`).


命令变更
----------------

* For all SCPI commands ``TRIG`` was renamed to ``TRig`` (does not affect the backwards compatibility).
* ``ACQ:SOUR<n>:DATA:STA:END?`` to ``ACQ:SOUR<n>:DATA:Start:End?``.
* ``ACQ:SOUR<n>:DATA:STA:N?`` to ``ACQ:SOUR<n>:DATA:Start:N?``.
* ``ACQ:SOUR<n>:DATA:OLD:N?`` to ``ACQ:SOUR<n>:DATA:Old:N?`` (does not affect the backwards compatibility).
* ``ACQ:SOUR<n>:DATA:LAT:N?`` to ``ACQ:SOUR<n>:DATA:Last:N?``.
* ``ACQ:DATA:UNITS`` to ``ACQ:DATA:Units`` (does not affect the backwards compatibility).
* ``SOUR:TRIG:EXT:DEBouncerUs`` to ``SOUR:TRig:EXT:DEBouncer[:US]`` (the previous command was misleading - will not be reverted).
* ``ACQ:TRIG:EXT:DEBouncerUs`` to ``ACQ:TRig:EXT:DEBouncer[:US]`` (the previous command was misleading - will not be reverted).
* ``UART:READ#`` to ``UART:READ#?``.
* ``I2C:Smbus:Read#`` to ``I2C:Smbus:Read#?``.
* ``I2C:Smbus:Read#:Word`` to ``I2C:Smbus:Read#:Word?``.
* ``I2C:Smbus:Read#:Buffer#`` to ``I2C:Smbus:Read#:Buffer#?``.
* ``I2C:IOctl:Read:Buffer#`` to ``I2C:IOctl:Read:Buffer#?``.


问题
---------

.. note::

    **命令的临时变更**
    我们发现此次命令重命名不向后兼容，因此将在下一次 OS 更新中恢复为旧版本。


2.00-23
===========

New commands
--------------

* Python API buffer commands:

    * ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)``.
    * ``rp_deleteBuffer(<buffer>)``.


Issues
---------

* 深度内存采集在 SDRlab 122-16 上无法工作（请升级到 2.00-30）。




2.00-18
===========

New commands
--------------

    * **板卡控制命令**：

    * ``SYSTem:TIME <hours>,<minutes>,<seconds>``.
    * ``SYSTem:TIME?``.
    * ``SYSTem:DATE <year>,<month>,<day>``.
    * ``SYSTem:DATE?``.
    * ``SYSTem:BRD:ID?``.
    * ``SYSTem:BRD:Name?``.

    * **菊链时钟和触发**：

    * ``DAISY:SYNC:TRIG <state>``.
    * ``DAISY:SYNC:TRIG?``.
    * ``DAISY:SYNC:CLK <state>``.
    * ``DAISY:SYNC:CLK?``.

    * **上升和下降时间 API 命令**：

    * ``rp_GenRiseTime(rp_channel_t channel, float time)``.
    * ``rp_GenGetRiseTime(rp_channel_t channel, float *time)``.
    * ``rp_GenFallTime(rp_channel_t channel, float time)``.
    * ``rp_GenGetFallTime(rp_channel_t channel, float *time)``.

    * **Last 和 Init 突发值**：

    * ``SOUR<n>:BURS:LASTValue <amplitude>``.
    * ``SOUR<n>:BURS:LASTValue?``.
    * ``SOUR<n>:INITValue <amplitude>``.
    * ``SOUR<n>:INITValue?``.

* **Sweep API 命令**。
* **深度内存采集（DMA）** 命令。
* ``SPI:SETtings:CSMODE <cs_mode>`` 命令 - 设置启动时 CS 引脚的默认值。


Issues
---------

* 深度内存采集仅适用于 STEMlab 125-14。
* 已移除 ``DAISY:ENable <state>``；其功能由 ``DAISY:SYNC:TRIG <state>`` 和 ``DAISY:SYNC:CLK <state>`` 命令替代。




2.00-15
===========

新增命令
--------------

    * **菊链时钟和触发**：

    * ``DAISY:ENable <state>``.
    * ``DAISY:ENable?``.
    * ``DAISY:TRIG_O:ENable <state>``.
    * ``DAISY:TRIG_O:ENable?``.
    * ``DAISY:TRIG_O:SOUR <mode>``.
    * ``DAISY:TRIG_O:SOUR?``.

    * **外部去抖滤波器命令**：

    * ``SOUR:TRig:EXT:DEBouncerUs <utime>``.
    * ``SOUR:TRig:EXT:DEBouncerUs?``.
    * ``ACQ:TRig:EXT:DEBouncerUs <value>``.
    * ``ACQ:TRig:EXT:DEBouncerUs?``.

* ``ACQ:TRig:FILL?`` 命令 - 检查采集缓冲区是否已满。


Issues
---------

* ``SPI:SET:CSMODE`` 和 ``SPI:SET:CSMODE?`` 无法工作。
* X-channel SCPI 控制存在错误。



1.04-28
===========

New commands
--------------

* NA.


Issues
---------

* ``SOUR:TRIG:INT`` 命令无法工作。它本应同步触发两个输出，但会被忽略。请使用 ``SOUR<n>:TRIG:INT`` 分别触发各个输出。
* ``ACQ:SOUR<n>:STA:END?`` 无法工作。



1.04-18 及更早版本
==================

我们的测试档案目前只覆盖到此处；对于更早版本，建议查阅 |Changelog| 了解特定板卡版本（该链接指向 STEMlab 125-14 更新日志）。

.. |Changelog| replace:: :rp-github:`Red Pitaya GitHub CHANGELOG <RedPitaya/blob/master/CHANGELOG.md>`

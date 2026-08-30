.. _playback&record:

#######################################
RF 信号录制与回放脚本
#######################################

RF 信号录制与回放脚本从 Red Pitaya 模拟输入（IN1/IN2）捕获 RF 信号脉冲，并立即在对应输出（OUT1/OUT2）上回放。它利用 **Deep Memory Acquisition** 实现高速录制，并利用 **Deep Memory Generation** 实现精确回放。

安装后，应用会设置为开机自动启动。应用通过 */opt/redpitaya/bin/* 目录中的配置文件进行控制。


工作原理
============

1. **采集**：每个通道独立监控其输入端的触发条件
2. **录制**：触发后使用 DMA 捕获信号，以实现最低延迟
3. **生成**：立即按照可配置的突发模式回放捕获的信号
4. **循环**：持续运行，直到手动停止

|

功能特性
========

- **双通道处理**：独立录制/回放 IN1→OUT1 和 IN2→OUT2 信号
- **深度内存模式**：利用 Red Pitaya 的 DMA 能力实现高速采集
- **分离触发模式**：每个通道独立处理触发
- **可配置参数**：灵活设置触发电平、缓冲区大小和突发模式
- **实时运行**：采用线程架构实现低延迟信号处理
- **自动启动**：Red Pitaya 启动时自动运行


.. note::

    此应用不应与 Red Pitaya WEB 界面并行使用。由于 *录制与回放* 应用占用大部分处理资源，Web 界面会明显变慢。

|

要求
============

**硬件**

- 任意 Red Pitaya 设备
- 正确端接的模拟输入/输出（50 Ω 阻抗匹配）

**软件**

- Red Pitaya Linux 2.07 或更高版本
- Nightly Build 637 或更高版本

.. warning::

    此应用消耗大量系统资源，**无法与 Red Pitaya Web 界面同时运行**。运行期间 Web 界面会严重变慢或无响应。

请确保 Red Pitaya 输入和输出正确端接（阻抗匹配）。否则，`传输线 <https://en.wikipedia.org/wiki/Transmission_line>`_ 上的 `振铃 <https://incompliancemag.com/circuit-theory-model-of-ringing-on-a-transmission-line/>`_ 可能导致 *Record and Playback* 应用出现未定义行为。Red Pitaya 快速模拟输入的输入阻抗为 1 MΩ，快速模拟输出的输出阻抗为 50 Ω。

|

安装
============

快速开始
-----------

1. 通过 SSH 连接到 Red Pitaya
2. 克隆仓库：``git clone https://github.com/RedPitaya/rec_and_play.git``
3. 启用脚本执行权限：``chmod +x ./rec_and_play/setup.sh``
4. 运行设置脚本：``cd rec_and_play && ./setup.sh``
5. 重启 Red Pitaya
6. 完成！应用会在启动时自动运行


选项 A：自动设置（推荐）
----------------------------------------

1.  与 Red Pitaya 建立 :ref:`SSH <ssh>` 连接。
#.  将 :rp-github:`rec_and_play GitHub 仓库 <rec_and_play/tree/master>` 下载到 Red Pitaya。

    .. code-block:: bash

        cd /root
        git clone https://github.com/RedPitaya/rec_and_play.git rap
        cd rap

#.  确保所有脚本均可执行，然后运行设置脚本。

    .. code-block:: bash

        chmod +x setup.sh
        ./setup.sh

#.  重启 Red Pitaya。

    .. code-block:: bash

        reboot


选项 B：手动设置
-----------------------

1.  与 Red Pitaya 建立 :ref:`SSH <ssh>` 连接。
#.  将 :rp-github:`rec_and_play GitHub 仓库 <rec_and_play/tree/master>` 下载到 Red Pitaya。

    .. code-block:: bash

        cd /root
        git clone https://github.com/RedPitaya/rec_and_play.git rap

    或者将仓库下载到计算机，再通过 SCP 命令将代码复制到 Red Pitaya：

    .. code-block:: bash

        scp -r /<path-to-downloaded-repository>/rec_and_play root@rp-xxxxxx.local:/root

#.  切换到 Red Pitaya 上的 *录制与回放* 目录。

    .. code-block:: bash

        cd /root/rap

#.  进入读写模式，并将脚本复制到 */opt/redpitaya/bin* 文件夹。

    .. code-block:: bash

        rw
        cp -f ./main.py /opt/redpitaya/bin/
        cp -f ./config.ini /opt/redpitaya/bin/

#.  （可选）编辑 ``/opt/redpitaya/sbin/startup.sh`` 并添加以下内容，使其随系统启动：

    .. code-block:: bash

        export PYTHONPATH=/opt/redpitaya/lib/python/:$PYTHONPATH
        /opt/redpitaya/bin/main.py

#.  重启 Red Pitaya。

    .. code-block:: bash

        reboot

|

配置
=============

*录制与回放* 应用使用 */opt/redpitaya/bin/* 目录中的配置文件（config.ini）。每个通道（ADC/DAC）独立配置。

**采集设置（ADC）**

.. list-table::
    :widths: 20 40 20 10
    :header-rows: 1

    * - 参数
      - 说明
      - 值
      - 单位
    * - trigger_level
      - 触发电压阈值
      - -1.0 to 1.0
      - 伏特
    * - trigger_mode
      - 触发条件
      - CH1_PE, CH1_NE, CH2_PE, CH2_NE
      - \-
    * - buffer_time
      - 录制时长
      - 1-30
      - µs


**生成设置（DAC）**

.. list-table::
    :widths: 20 40 30 10
    :header-rows: 1

    * - 参数
      - 说明
      - 值
      - 单位
    * - signal_source
      - 要录制的输入通道
      - IN1, IN2
      - \-
    * - count_burst
      - 每个突发的周期数（NCYC）
      - ≥1
      - 次
    * - repetition
      - 突发次数（NOR）
      - ≥1
      - count
    * - repetition_delay
      - 突发之间的延迟
      - ≥ (buffer_time × count_burst + 1)
      - µs


配置示例
--------------------

要更改设置，可以直接编辑 ``/opt/redpitaya/bin/`` 中的 config.ini 文件，或者编辑 record and play 目录中的 config.ini 文件并再次运行 setup.sh 脚本。要使更改生效，必须重启 main.py（重启 Red Pitaya，或终止进程后重新启动）。

``config.ini`` 示例：

.. code-block:: ini

    [ADC1]
    ; IN1 Trigger Level in volts
    trigger_level=0.1
    ; Trigger source (Values: CH1_PE, CH1_NE)
    trigger_mode=CH1_PE
    ; Record signal Buffer size in microseconds (min 1 µs)
    buffer_time=20

    [ADC2]
    ; IN2 Trigger Level in volts
    trigger_level=0.1
    ; Trigger source (Values: CH2_PE, CH2_NE)
    trigger_mode=CH2_PE
    ; Record signal Buffer size in microseconds (min 1 µs)
    buffer_time=20

    [DAC1]
    ; OUT1 Gen signal from source (IN1, IN2). Which input to use for recording data.
    signal_source=IN1
    ; Number of signal repetitions without delays (NCYC - number of cycles/periods in a single burst).
    count_burst=1
    ; Number of repetitions with delay (NOR - Number of Repetitions/Bursts). Each repetition includes `count_burst` (NCYC) recordings without delay.
    repetition=3
    ; Delay between repetitions.
    ; If there is a "repetition" number of repetitions, then the minimum allowed delay must be no less than:
    ; buffer_time * count_burst + 1 µS
    ; Otherwise the signal may break. If there are no repetitions, the value is ignored
    ; For example. buffer_time = 20, count_burst=2. repetition_delay = 20 * 2 + 1 = 41 µS
    repetition_delay=50

    [DAC2]
    ; OUT2 Gen signal from source (IN1, IN2). Which input to use for recording data.
    signal_source=IN2
    ; Number of signal repetitions without delays (NCYC - number of cycles/periods in a single burst).
    count_burst=1
    ; Number of repetitions with delay (NOR - Number of Repetitions/Bursts). Each repetition includes `count_burst` (NCYC) recordings without delay.
    repetition=3
    ; Delay between repetitions.
    ; If there is a "repetition" number of repetitions, then the minimum allowed delay must be no less than:
    ; buffer_time * count_burst + 1 µS
    ; Otherwise the signal may break. If there are no repetitions, the value is ignored
    ; For example. buffer_time = 20, count_burst=2. repetition_delay = 20 * 2 + 1 = 41 µS
    repetition_delay=50

.. note::

    - 支持**跨通道路由**，但未经测试（例如 IN1 到 OUT2）。
    - 两个通道的**缓冲区大小**应相同。
    - 必须遵守**时序约束**，以避免信号损坏。

|

使用
=====

启动应用
-------------------------

如果通过 ``setup.sh`` 安装，应用会在启动时自动运行。手动启动方法如下：

.. code-block:: bash

    cd /opt/redpitaya/bin
    python3 main.py


监控运行状态
--------------------

- 检查系统日志中的状态消息。
- 使用 ``top`` 或 ``htop`` 监控 CPU 使用率。
- 应用会持续运行，直到被中断。


停止应用
-------------------------

**临时停止** - 使应用停止运行，直到下一次启动：

- 在终端按 ``Ctrl+C``，或
- 在 ``top`` 中终止进程（输入 ``k`` 和进程 PID）。

    .. figure:: img/Rec_and_play_top_kill.png
        :alt: Top 命令和终止 PID
        :align: center
        :width: 800px

**永久禁用** - 先停止应用，然后：

1. 从 */opt/redpitaya/sbin* 目录中的 ``startup.sh`` 脚本移除它（可能需要进入 ``rw`` 模式）。
2. 删除或注释以下代码行：

    .. code-block:: bash

        # Here you can specify commands for autorun at system startup
        export PYTHONPATH=/opt/redpitaya/lib/python/:$PYTHONPATH
        /opt/redpitaya/bin/main.py

3. 也可以从 */opt/redpitaya/bin* 删除 *main.py* 和 *config.ini*。

|

故障排除
===============

常见问题
-------------

**设置 split trigger 出错**

- 确保使用兼容的 Red Pitaya OS 版本。
- 检查系统资源是否耗尽。

**缓冲区大小无效**

- 确认 ``buffer_time`` 在 1-30 µs 范围内。
- 确保配置中使用整数值。

**无信号输出**

- 检查输入信号电平和触发设置。
- 确认阻抗端接正确（50 Ω）。
- 确认 ``signal_source`` 配置正确。

**系统变慢**

- 这是正常现象 - 应用会使用大部分系统资源。
- 运行期间 Web 界面将无响应。

性能调优
------------------

- 减小 ``buffer_time`` 以获得更快响应。
- 调整 ``repetition_delay`` 以防止信号重叠。
- 使用 ``top`` 命令监控 CPU 使用率。
- 减小 ``LOOP_DELAY`` 的值，以更快检查触发。

|

常见问答
===

**问：可以与 Web 界面一起使用吗？**

答：不可以，此应用会占用全部处理资源，使 Web 界面无响应。

**问：最大缓冲区大小是多少？**

答：最大为 30 µs，受 Red Pitaya 的 DMA 能力限制。

**问：可以将 IN1 路由到 OUT2 吗？**

答：可以，但此配置未经测试。请在 DAC2 部分使用 ``signal_source=IN1``。

**问：如何更改触发灵敏度？**

答：在 ADC 部分调整 ``trigger_level`` （范围：-1.0 至 1.0 Volts）。

**问：为什么信号会中断？**

答：通常是因为 ``repetition_delay`` 不足。请确保其 ≥ (buffer_time × count_burst + 1) µs。

|

源代码
===========

我们的 GitHub 上提供 :rp-github:`Playback and Record 源代码 <rec_and_play/tree/master>`。

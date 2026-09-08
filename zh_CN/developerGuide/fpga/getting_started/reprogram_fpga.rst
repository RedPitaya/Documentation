.. _fpga_reprogramming:

########################
FPGA 重编程指南
########################

本指南介绍在 Red Pitaya 板卡上加载 FPGA 比特流的基础知识，包括加载预构建 FPGA 项目、上传自定义设计、验证配置以及恢复出厂设置。

.. seealso::

    **高级主题：**
    
    - :ref:`fpga_boot_loading` - 让 FPGA 在启动时自动加载
    - :ref:`fpga_advanced_loading` - 自定义比特流、设备树、实用工作流和常见问题
    - :ref:`device_tree` - 自定义硬件的设备树配置
    - :ref:`signal_mapping` - 硬件信号连接和引脚排列

.. contents:: 目录
    :local:
    :depth: 2
    :backlinks: top

|

**********************************
概述
**********************************

了解 FPGA 加载方法
====================================

Red Pitaya 根据 OS 版本使用不同的 FPGA 加载机制：

.. list-table::
    :header-rows: 1
    :widths: 20 40 40

    * - OS 版本
      - 方法
      - 主要特性
    * - 1.04 or older
      - Direct ``/dev/xdevcfg`` access
      - 简单，但不管理设备树
    * - 2.00 to 2.05-37
      - ``fpgautil`` command
      - Linux FPGA Manager 框架
    * - 2.07-43 or newer
      - ``overlay.sh`` script
      - 自动处理和验证设备树

.. note::

    从 OS 2.00 开始，Red Pitaya 采用 Linux FPGA Manager 框架，该框架与内核集成更好，并支持设备树覆盖。

|

何时使用本指南
======================

在以下情况下请使用本指南：

- 加载你创建的自定义 FPGA 设计
- 在不同的预构建 FPGA 项目之间切换
- 在开发过程中测试 FPGA 修改
- 验证 FPGA 配置
- 恢复出厂 FPGA 设置

有关启动加载、自定义设备树和部分重配置等高级主题，请参阅 :ref:`高级 FPGA 加载指南 <fpga_advanced_loading>`。

|

前置条件
=============

硬件和访问权限
-------------------

* Red Pitaya 板卡已 :ref:`通电并连接到本地网络 <quickstart_connect>`
* 可以通过 :ref:`SSH <ssh>` 访问 Red Pitaya 设备

文件要求
-----------------

根据使用场景，你需要准备：

**OS 2.00 或更高版本：**

* 二进制比特流文件（``.bit.bin``）
* 设备树覆盖文件（``.dtbo``）——自定义外设可选（参阅 :ref:`fpga_advanced_loading`）

**OS 1.04 或更低版本：**

* FPGA 比特流文件（``.bit``）

**命令行表示法**

在本指南中：

* **带有“redpitaya>”前缀的命令** - 建立 :ref:`SSH <ssh>` 连接后，在 Red Pitaya Linux OS 内执行
* **不带此前缀的命令** - 在计算机的本地终端或命令提示符中执行

|

**********************************
快速开始
**********************************

对于只需要命令的有经验用户：

.. tabs::

    .. tab:: OS 2.07-43 or newer

        .. code-block:: bash

            # Upload bitstream
            scp red_pitaya_top.bit.bin root@rp-xxxxxx.local:/root
            
            # Load FPGA
            ssh root@rp-xxxxxx.local
            redpitaya> fpgautil -b /root/red_pitaya_top.bit.bin
            
            # Or load pre-built project
            redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 v0.94

    .. tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            # Upload bitstream
            scp red_pitaya_top.bit.bin root@rp-xxxxxx.local:/root
            
            # Load FPGA
            ssh root@rp-xxxxxx.local
            redpitaya> fpgautil -b /root/red_pitaya_top.bit.bin

    .. tab:: OS 1.04 or older

        .. code-block:: bash

            # Upload bitstream
            scp red_pitaya_top.bit root@rp-xxxxxx.local:/root
            
            # Load FPGA
            ssh root@rp-xxxxxx.local
            redpitaya> cat /root/red_pitaya_top.bit > /dev/xdevcfg

|

**********************************
准备 FPGA 文件
**********************************

将 .bit 转换为 .bit.bin
============================

如果你有 Vivado 生成的 ``.bit`` 文件，请将其转换为 ``.bit.bin`` 格式，以用于 OS 2.00+。

.. note::

    仅 Red Pitaya OS 2.00 或更高版本需要此转换。OS 1.04 直接使用 ``.bit`` 文件。

|

进入 .bit 文件所在位置
-------------------------------

打开终端并进入包含比特流的目录：

.. code-block:: bash

    cd <Path/to/RedPitaya/repository>/prj/<project_name>/project/redpitaya.runs/impl_1

.. note::

    在 **Windows** 上，请将路径中的正斜杠改为反斜杠。

|

创建 .bif 文件并生成 .bit.bin
---------------------------------------

``bootgen`` 工具使用 ``.bif`` （Boot Image Format）配置文件转换比特流。

.. tabs::

    .. group-tab:: Linux

        .. code-block:: bash

            echo -n "all:{ red_pitaya_top.bit }" > red_pitaya_top.bif
            bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

    .. group-tab:: Windows (Vivado TCL Console)

        打开 Vivado 并使用 TCL 控制台，或使用 Vivado HSL Command Prompt：

        .. code-block:: bash

            echo all:{ red_pitaya_top.bit } > red_pitaya_top.bif
            bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

.. tip::

    Linux 和 Windows 的区别在于 ``echo`` 命令：
    
    - **Linux：** 使用 ``echo -n`` 以避免换行符
    - **Windows：** 使用不带 ``-n`` 标志的标准 ``echo``

|

上传文件到 Red Pitaya
==============================

通过 SCP 传输比特流
---------------------------

使用 ``scp`` 命令将文件从计算机复制到 Red Pitaya：

**OS 1.04 或更低版本（.bit 文件）：**

.. code-block:: bash

    scp red_pitaya_top.bit root@rp-xxxxxx.local:/root

**OS 2.00 或更高版本（.bit.bin 文件）：**

.. code-block:: bash

    scp red_pitaya_top.bit.bin root@rp-xxxxxx.local:/root

.. tip::

    在 Windows 上进行图形化文件传输时，请使用 WinSCP 或 FileZilla。

|

验证文件上传
------------------

通过 SSH 连接并检查文件：

.. code-block:: bash

    redpitaya> cd
    redpitaya> ls -lh

你应该能在 ``/root`` 目录中看到已上传的文件。

|

**********************************
加载 FPGA
**********************************

选择适合 Red Pitaya OS 版本的方法。


OS 2.07-43 或更高版本（推荐）
==================================

对于 OS 2.07+，你可以使用 ``fpgautil`` （仅加载比特流）或 ``overlay.sh`` （加载比特流 + 设备树）。

加载预构建 FPGA 项目
--------------------------------

Red Pitaya 包含预构建的 FPGA 镜像，可以直接按名称加载：

.. code-block:: bash

    # Load default v0.94 project
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94
    
    # Load streaming application
    redpitaya> /opt/redpitaya/sbin/overlay.sh stream_app
    
    # Load logic analyzer
    redpitaya> /opt/redpitaya/sbin/overlay.sh logic

.. note::

    ``overlay.sh`` 会读取 Red Pitaya 板卡配置文件，然后从 ``/opt/redpitaya/fpga/<model>/<project>/`` 加载匹配的文件。
    因此，同一个命令名称可以在不同板卡型号上工作。

加载自定义比特流
-------------------------

对于不修改设备树的简单 FPGA 加载：

.. code-block:: bash

    # Load bitstream only (keeps current device tree)
    redpitaya> fpgautil -b /root/red_pitaya_top.bit.bin

有关带设备树的高级自定义配置，请参阅 :ref:`fpga_advanced_loading`。

|

OS 2.00 至 2.05-37（fpgautil 方法）
=====================================

从 OS 2.00 开始，Red Pitaya 采用 Linux FPGA Manager 框架。使用 ``fpgautil`` 命令加载比特流。

加载 FPGA 比特流
----------------------

1. 确保 ``.bit.bin`` 文件已上传到 Red Pitaya

2. 使用 ``fpgautil`` 加载：

    .. code-block:: bash

        redpitaya> fpgautil -b red_pitaya_top.bit.bin

**特性：**

- 使用 Linux FPGA Manager 框架
- 验证比特流兼容性
- 报告加载状态

|

OS 1.04 或更低版本（旧版方法）
=================================

此方法直接访问 ``/dev/xdevcfg`` 设备来配置 FPGA。

加载 FPGA 比特流
----------------------

1. 确保 ``.bit`` 文件已上传到 Red Pitaya

2. 加载比特流：

    .. code-block:: bash

        redpitaya> cat red_pitaya_top.bit > /dev/xdevcfg

FPGA 会立即使用你的设计重新配置。

**限制：**

- 不管理设备树
- 不支持自动验证

|

**********************************
验证与故障排除
**********************************

确认 FPGA 配置
==============================

有多种方式可以确认 FPGA 已成功重新编程。

|

方法 1：检查状态文件（OS 2.07+）
----------------------------------------

覆盖脚本会创建验证文件：

**检查已加载的项目标识符：**

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf

**输出示例：**

.. code-block:: text

    v0.94                      # Standard project
    v0.94_my_project           # Custom bitstream
    v0.94_my_project_dtbo      # Custom bitstream + device tree

**检查详细加载信息：**

.. code-block:: bash

    redpitaya> cat /tmp/update_fpga.txt

**输出示例：**

.. code-block:: text

    Commit a1b2c3d4
    FPGA md5sum: d41d8cd98f00b204e9800998ecf8427e  /opt/redpitaya/fpga/Z10/v0.94/fpga.bit.bin
    Tue Oct 24 10:30:45 UTC 2025

|

方法 2：检查 FPGA Manager 状态
-----------------------------------

验证 FPGA Manager 是否成功加载配置：

.. code-block:: bash

    redpitaya> cat /sys/class/fpga_manager/fpga0/state

**预期输出：** ``operating``

**其他可能的状态：**

- ``unknown`` - FPGA Manager 未初始化
- ``write init`` - 开始配置
- ``write`` - 正在写入比特流
- ``write complete`` - 比特流写入成功
- ``write error`` - 配置失败

|

方法 3：检查自定义寄存器
--------------------------------

如果 FPGA 设计包含 ID 寄存器，可以直接验证：

.. code-block:: bash

    redpitaya> /opt/redpitaya/bin/monitor 0x40300050

该命令应返回预期的寄存器值（例如 :ref:`添加自定义组件教程 <fpga_tutorial_cust_comp>` 中的 ``0xfeedbacc``）。

|

方法 4：测试 LED 模式
----------------------------

对于控制 LED 的设计，可以观察板卡上的 8 个黄色 LED，以验证自定义模式。

|

常见问题与解决方案
============================

错误：“通过 FPGA manager 加载 BIN FILE 失败”
-----------------------------------------------------

.. code-block:: bash

    sh: 1: echo: echo: I/O error
    BIN FILE loading through FPGA manager failed

**可能的原因和解决方案：**

1. **比特流与板卡型号不兼容**
    
    检查 Red Pitaya 型号并验证构建标志：
    
    .. code-block:: bash
    
        redpitaya> /opt/redpitaya/bin/monitor -f
    
    使用 :ref:`正确的型号标志 <fpga_create_project>`（``MODEL=Z10``、``MODEL=Z20`` 等）重新构建 FPGA。

2. **比特流文件损坏**
    
    验证文件完整性：
    
    .. code-block:: bash
    
        redpitaya> ls -lh /root/red_pitaya_top.bit.bin
        redpitaya> md5sum /root/red_pitaya_top.bit.bin
    
    如果文件大小不匹配（通常约为 2-4 MB），请重新生成并上传文件。

3. **文件路径或文件名错误**
    
    确保文件名完全匹配：
    
    .. code-block:: bash
    
        redpitaya> ls /opt/my_project/
        # Must show: fpga.bit.bin (case-sensitive!)

4. **.bit 到 .bit.bin 的转换不正确**
    
    确认 bootgen 命令无错误完成，然后重试转换。

|

错误：“未找到设备树覆盖”
---------------------------------------

**对于标准设备树：**

检查基础项目是否存在：

.. code-block:: bash

    redpitaya> MODEL=$(/opt/redpitaya/bin/monitor -f)
    redpitaya> ls /opt/redpitaya/fpga/$MODEL/v0.94/fpga.dtbo

**对于自定义设备树：**

确保文件存在且名称正确：

.. code-block:: bash

    redpitaya> ls /opt/my_project/fpga.dtbo

|

FPGA 已加载但应用无法工作
---------------------------------------

**可能的原因：**

1. **设备树不匹配** - FPGA 硬件与设备树描述不一致
    
    - 从 Vivado 重新生成设备树（参阅 :ref:`device_tree`）
    - 验证寄存器地址与 FPGA 设计一致
    - 检查外设名称和属性是否正确

2. **无法访问自定义外设**
    
    测试寄存器访问：
    
    .. code-block:: bash
    
        # Try reading a register (use your address)
        redpitaya> /opt/redpitaya/bin/monitor 0x40000000
    
    如果读取结果为 0 或失败，请检查设备树内存区域。

3. **时钟配置不正确**
    
    - 验证 FPGA 设计中已启用 PL 时钟
    - 检查时钟频率是否符合设备树规范
    - 确保 AXI 时钟域配置正确

有关更多故障排除指导，请参阅 :ref:`fpga_advanced_loading` 中的完整常见问题解答。

|

**********************************
恢复出厂 FPGA
**********************************

如果想恢复到官方 Red Pitaya FPGA，请使用以下方法。

方法 1：重新加载出厂 FPGA（简单）
=======================================

对于 OS 2.00 或更高版本，只需加载默认项目：

.. tabs::

    .. tab:: OS 2.07+ (overlay.sh)

        .. code-block:: bash

            redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 v0.94

    .. tab:: OS 2.00-2.05 (fpgautil)

        .. code-block:: bash

            redpitaya> fpgautil -b /opt/redpitaya/fpga/$(monitor -f)/v0.94/fpga.bit.bin

或者重启 Red Pitaya：

.. code-block:: bash

    redpitaya> reboot

.. note::

    除非你配置了启动加载（参阅 :ref:`fpga_boot_loading`）或替换了默认 FPGA 镜像，否则此方法有效。

|

方法 2：禁用启动加载
===============================

如果设置了启动时自动加载 FPGA，请将其禁用：

**对于 startup.sh 方法：**

.. code-block:: bash

    redpitaya> rw
    redpitaya> nano /opt/redpitaya/sbin/startup.sh
    # Comment out or remove your FPGA loading line
    redpitaya> ro
    redpitaya> reboot

**对于 systemd 服务：**

.. code-block:: bash

    redpitaya> rw
    redpitaya> systemctl disable custom-fpga.service
    redpitaya> systemctl stop custom-fpga.service
    redpitaya> ro
    redpitaya> reboot

有关完整的启动加载管理，请参阅 :ref:`fpga_boot_loading`。

|

方法 3：恢复被替换的 FPGA 镜像
======================================

如果使用替换脚本覆盖了系统文件（高级方法）：

.. code-block:: bash

    # Run the replacement script without parameters
    redpitaya> /root/replace_fpga.sh
    
    # Reboot to activate
    redpitaya> reboot

这会恢复首次替换默认镜像时创建的备份。

|

方法 4：手动恢复（OS 1.04）
==================================

对于 OS 1.04，重启以重新加载出厂 FPGA：

.. code-block:: bash

    redpitaya> reboot

在 OS 1.04 上，出厂 FPGA 会在启动时自动加载。

|

**********************************
相关文档
**********************************

**FPGA 文档：**

- :ref:`fpga_boot_loading` - 让 FPGA 在启动时自动加载
- :ref:`fpga_advanced_loading` - 高级加载场景、工作流和常见问题
- :ref:`device_tree` - 自定义硬件的设备树配置
- :ref:`signal_mapping` - 硬件信号连接和引脚排列

**开发者指南：**

- :ref:`Red Pitaya FPGA 开发者指南 <fpga_top>` - FPGA 开发概述
- :ref:`添加自定义组件 <fpga_tutorial_cust_comp>` - FPGA 教程
- :ref:`C++ 和 Python API <C&Py_API>` - 软件接口

**应用示例：**

- :rp-github:`Red Pitaya GitHub 仓库 - 示例设计 <RedPitaya-Examples>`
- :rp-forum:`Red Pitaya 论坛 - 社区项目 <>`

.. _overlay_util:

######################################
Overlay 工具（FPGA 配置）
######################################

对于运行 OS 2.07-43 或更高版本的 Red Pitaya 设备，推荐使用 ``overlay.sh`` 脚本加载 FPGA 镜像。
这是 Red Pitaya 生态系统使用的专用开源 shell 脚本，用于根据检测到的板卡型号选择并加载正确的 FPGA 镜像和匹配的设备树 overlay。

.. contents:: Table of Contents
    :local:
    :backlinks: top
    :depth: 1

|


概述
=========

overlay 脚本（``overlay.sh``）是管理 Red Pitaya 板卡 FPGA 配置的命令行工具，可处理：

- 加载 FPGA 比特流文件
- 应用设备树 overlay
- 通过 ``fpgautil`` 工具管理 FPGA 重配置
- 跟踪已加载的 FPGA 镜像
- 支持部分重配置区域
- 根据检测到的板卡配置文件选择标准 FPGA 路径

它不会：

- 检查比特流字节序（假定格式正确）
- 直接与 FPGA Manager 交互（交由 ``fpgautil`` 处理）

从 Red Pitaya OS 2.00 开始，FPGA 加载机制从直接访问 ``/dev/xdevcfg`` 改为使用 Linux FPGA Manager 框架。
``overlay.sh`` 脚本提供：

- 与当前 Red Pitaya FPGA 加载系统兼容
- 设备树管理 - 自动加载匹配的 overlay
- 验证 - 跟踪并验证已加载配置
- 简化工作流 - 使用一条命令代替多个步骤
- 面向高级用户的部分重配置支持

对于内置 FPGA 项目，脚本使用 ``/opt/redpitaya/bin/profiles -f`` 读取板卡配置文件，并从以下位置加载文件：

.. code-block:: text

    /opt/redpitaya/fpga/<detected-model>/<fpga_name>/fpga.bit.bin
    /opt/redpitaya/fpga/<detected-model>/<fpga_name>/fpga.dtbo

如果提供自定义路径，脚本会使用这些路径而不是标准文件，同时仍将检测到的板卡型号作为 Red Pitaya 生态系统的选择依据。

上游脚本位于 Red Pitaya OS 仓库中：
`overlay.sh <https://github.com/RedPitaya/RedPitaya/blob/master/OS/filesystem/sbin/overlay.sh>`_.

.. note::

    For Red Pitaya OS 1.04 and older, use the legacy ``cat bitstream.bit > /dev/xdevcfg`` method instead. 
    See :ref:`FPGA Reprogramming Guide <fpga_reprogramming>` for details.

|


命令帮助
=============

不带参数运行 ``overlay.sh`` 会显示命令帮助：

.. tabs::

    .. group-tab:: OS version 3.00 and higher

        .. code-block:: console

            root@rp-f0b1cb:~# overlay.sh
            Usage: /opt/redpitaya/sbin/overlay.sh <fpga_name> [custom_fpga] [custom_devicetree] [overlay_name]

            Load FPGA bitstream and device tree overlay

            Parameters:
            <fpga_name>        - Name of FPGA configuration from /opt/redpitaya/fpga/$MODEL/
            [custom_fpga]      - Custom FPGA bitstream path (optional)
            [custom_devicetree]- Custom device tree overlay path (optional)
            [overlay_name]     - Custom overlay region name (optional, default: Full)

            Examples:
            /opt/redpitaya/sbin/overlay.sh v0.94                                                            - Load default v0.94 FPGA
            /opt/redpitaya/sbin/overlay.sh oscillator /path/to/custom.bin                                   - Load custom FPGA bitstream
            /opt/redpitaya/sbin/overlay.sh sdr /path/to/custom.bin /path/to/custom.dtbo                     - Load custom FPGA and device tree
            /opt/redpitaya/sbin/overlay.sh transmitter /path/to/fpga.bin /path/to/fpga.dtbo CustomRegion    - Load with custom overlay name

            Available FPGA configurations:
            - barebones
            - logic
            - pyrpl
            - stream_app
            - v0.94

        .. group-tab:: OS version 2.00

            .. code-block:: console

                root@rp-f0ef2d:~# overlay.sh
                Usage: /opt/redpitaya/sbin/overlay.sh <fpga_name> [custom_fpga] [custom_devicetree] [overlay_name]
                
                Load FPGA bitstream and device tree overlay
                
                Parameters:
                    <fpga_name>        - Name of FPGA configuration from /opt/redpitaya/fpga/$MODEL/
                    [custom_fpga]      - Custom FPGA bitstream path (optional)
                    [custom_devicetree]- Custom device tree overlay path (optional)
                    [overlay_name]     - Custom overlay region name (optional, default: Full)
                
                Examples:
                    /opt/redpitaya/sbin/overlay.sh v0.94                                                                - Load a built-in FPGA project
                    /opt/redpitaya/sbin/overlay.sh oscillator /path/to/custom.bit.bin                                   - Load custom FPGA bitstream
                    /opt/redpitaya/sbin/overlay.sh sdr /path/to/custom.bit.bin /path/to/custom.dtbo                     - Load custom FPGA and device tree
                    /opt/redpitaya/sbin/overlay.sh transmitter /path/to/fpga.bit.bin /path/to/fpga.dtbo CustomRegion    - Load with custom overlay name
                
                Available FPGA configurations:
                    - barebones
                    - logic
                    - pyrpl
                    - stream_app
                    - v0.94

|


基本用法
============

通过 SSH 访问
--------------

overlay 脚本需要通过 :ref:`SSH 访问 <ssh>` Red Pitaya 设备：

.. code-block:: bash

    ssh root@rp-xxxxxx.local

加载标准 FPGA 项目
--------------------------------

Red Pitaya 在 ``/opt/redpitaya/fpga/`` 中提供预构建的 FPGA 镜像。加载标准项目：

.. code-block:: bash

    redpitaya> overlay.sh v0.94

其他标准项目：

.. code-block:: bash

    # Load streaming application
    redpitaya> overlay.sh stream_app
    
    # Load logic analyzer
    redpitaya> overlay.sh logic

.. note::

    The script automatically detects your Red Pitaya model and loads the matching ``fpga.bit.bin`` and ``fpga.dtbo`` files from the corresponding
    ``/opt/redpitaya/fpga/<model>/<project>/`` directory.

|


命令语法
===============

基本语法：

.. code-block:: text

    overlay.sh <fpga_name> [custom_fpga] [custom_devicetree] [overlay_name]

参数：

- ``fpga_name`` - **必需。** 标准 Red Pitaya FPGA 镜像在 ``/opt/redpitaya/fpga/<model>/`` 下的项目名称
- ``custom_fpga`` - **可选。** 自定义 ``fpga.bit.bin`` 文件的完整路径
- ``custom_devicetree`` - **可选。** 自定义 ``fpga.dtbo`` 文件的完整路径
- ``overlay_name`` - **可选。** FPGA 可重配置区域名称（默认：``Full``）

.. important::

    The overlay region name ``Led`` is reserved by the system and cannot be used for custom loads.

|


使用示例
===============

示例 1：加载标准项目
----------------------------------

.. code-block:: bash

    redpitaya> overlay.sh v0.94

从 ``/opt/redpitaya/fpga/<model>/v0.94/`` 加载比特流和设备树。


示例 2：加载自定义比特流
----------------------------------

.. code-block:: bash

    # Copy bitstream to any accessible location
    redpitaya> cp /root/custom.bit.bin /root/custom.bit.bin
    
    # Load with standard device tree
    redpitaya> overlay.sh v0.94 /root/custom.bit.bin

从 ``/root/custom.bit.bin`` 加载自定义比特流，并保留 ``/opt/redpitaya/fpga/<model>/v0.94/`` 中的标准设备树。


示例 3：加载自定义比特流和设备树
--------------------------------------------------

.. code-block:: bash

    # Copy both files
    redpitaya> cp /root/custom.bit.bin /root/custom.bit.bin
    redpitaya> cp /root/custom.dtbo /root/custom.dtbo
    
    # Load both custom files
    redpitaya> overlay.sh v0.94 /root/custom.bit.bin /root/custom.dtbo

从提供的自定义路径加载两个文件。


示例 4：部分重配置
------------------------------------

.. code-block:: bash

    redpitaya> overlay.sh v0.94 /root/custom.bit.bin /root/custom.dtbo Region0

将自定义 FPGA 加载到指定的可重配置区域（Pblock）。

|


验证
=============

检查已加载的 FPGA
------------------

查看 FPGA 加载状态：

.. code-block:: bash

    redpitaya> cat /tmp/update_fpga.txt

示例输出：

.. code-block:: text

    Time taken to load BIN is 207.000000 Milli Seconds
    BIN FILE loaded through FPGA manager successfully
    FPGA md5sum: 7065fc8f7786967d7cc325727a6730ce  /opt/redpitaya/fpga/z20_125_v2/v0.94/fpga.bit.bin
    Wed Oct 22 11:47:27 AM EEST 2025

检查 FPGA 标识符：

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf
    # Example output: v0.94

验证 FPGA manager 状态：

.. code-block:: bash

    redpitaya> cat /sys/class/fpga_manager/fpga0/state
    # Expected output: operating

|


常见问题
==============

BIN FILE 加载失败
------------------------

**错误：** "BIN FILE loading through FPGA manager failed"

**可能原因：**

1. 比特流与板卡型号不兼容 - 确认构建时使用了正确的 MODEL 标志。
2. 比特流文件损坏 - 重新生成并重新上传。
3. 文件路径或文件名错误 - 确保文件名称准确为 ``fpga.bit.bin``。

**解决方案：**

.. code-block:: bash

    # Check your Red Pitaya model
    redpitaya> /opt/redpitaya/bin/monitor -f
    
    # Verify file exists and has reasonable size (2-4 MB)
    redpitaya> ls -lh /opt/my_project/fpga.bit.bin

找不到设备树
----------------------

**解决方案：** 确保设备树文件存在于正确位置：

.. code-block:: bash

    # For standard device tree
    redpitaya> ls /opt/redpitaya/fpga/<model>/v0.94/fpga.dtbo
    
    # For custom device tree
    redpitaya> ls /opt/my_project/fpga.dtbo

FPGA 已加载但无法工作
-----------------------------

**Possible causes:**

1. 设备树不匹配 - FPGA 硬件与设备树描述不一致。
2. 寄存器地址不正确。
3. 无法访问自定义外设。

**解决方案：** 使用 monitor 工具验证：

.. code-block:: bash

    # Test reading a register (example address)
    redpitaya> monitor 0x40000000

|


文件结构
===============

标准 FPGA 文件位置：

.. code-block:: text

    /opt/redpitaya/fpga/
    ├── Z10/              # STEMlab 125-10/14
    ├── Z20/              # SDRlab 122-16
    ├── Z20_125/          # STEMlab 125-14 (Z7020)
    ├── Z20_250/          # SIGNALlab 250-12
    └── Z20_4/            # STEMlab 125-14 4-Input
        ├── v0.94/
        │   ├── fpga.bit.bin
        │   ├── fpga.dtbo
        │   └── git_info.txt
        ├── stream_app/
        └── logic/

自定义 FPGA 文件位置：

.. code-block:: text

    /any/path/fpga.bit.bin    # Optional custom bitstream path
    /any/path/fpga.dtbo       # Optional custom device tree path

状态文件：

.. code-block:: text

    /tmp/loaded_fpga.inf       # FPGA identifier
    /tmp/update_fpga.txt       # Loading status with MD5 and timestamp

|


转换比特流文件
============================

overlay 脚本需要二进制比特流文件（``.bit.bin``）。如果有来自 Vivado 的 ``.bit`` 文件，请将其转换：

**Linux:**

.. code-block:: bash

    echo -n "all:{ red_pitaya_top.bit }" > red_pitaya_top.bif
    bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

**Windows (Vivado TCL Console):**

.. code-block:: bash

    echo all:{ red_pitaya_top.bit } > red_pitaya_top.bif
    bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

|


高级用法 - fpgautil
===========================

``fpgautil`` 工具是 ``overlay.sh`` 内部调用的底层工具，用于加载 FPGA 比特流。虽然大多数用户推荐使用 ``overlay.sh``，但高级用户可以直接使用 ``fpgautil``，以更精细地控制 FPGA 加载过程。

命令帮助
-------------

.. code-block:: console

    root@rp-f0ef2d:~# fpgautil
    
    fpgautil: FPGA Utility for Loading/reading PL Configuration
    
    Usage:  fpgautil -b <bin file path> -o <dtbo file path>
    
    Options: -b <binfile>           (Bin file path)
             -o <dtbofile>          (DTBO file path)
             -f <flags>             Optional: <Bitstream type flags>
                                       f := <Full | Partial >
             -n <Fpga region info>  FPGA Regions represent FPGA's
                                    and partial reconfiguration
                                    regions of FPGA's in the
                                    Device Tree
    
    Examples:
    (Load Full bitstream using Overlay)
    fpgautil -b top.bit.bin -o can.dtbo -f Full -n Full
    (Load Partial bitstream using Overlay)
    fpgautil -b rm0.bit.bin -o rm0.dtbo -f Partial -n PR0
    (Load Full bitstream using sysfs interface)
    fpgautil -b top.bit.bin -f Full
    (Load Partial bitstream using sysfs interface)
    fpgautil -b rm0.bit.bin -f Partial

使用说明
------------

**何时直接使用 fpgautil：**

- 需要直接控制的自定义自动化脚本
- 调试 FPGA 加载问题
- 高级部分重配置场景
- 集成到自定义部署工作流

**与 overlay.sh 的主要区别：**

- ``overlay.sh`` - 界面简化、自动检测型号，并代为处理文件路径
- ``fpgautil`` - 底层控制，需要明确指定路径和参数，直接提供 FPGA Manager 接口

.. note::

    大多数用户应使用 ``overlay.sh``，而不是直接使用 ``fpgautil``。overlay 脚本提供自动型号检测、简化的路径处理和更好的错误处理。

|


相关文档
======================

有关 overlay 脚本的完整信息（包括高级用法、自动化示例和详细故障排除），请参见：

- :ref:`FPGA 重编程指南 <fpga_reprogramming>` - 所有 OS 版本的 FPGA 加载流程及 overlay 详细用法
- :ref:`FPGA 项目创建 <fpga_create_project>` - 构建自定义 FPGA 项目

|

源代码
=====================

overlay 工具脚本的源代码位于 GitHub：

- :rp-github:`overlay.sh <RedPitaya/blob/master/OS/filesystem/sbin/overlay.sh>`

.. _emmc_flash_e3:

刷写 QSPI eMMC 模块上的 eMMC
##########################################

本指南介绍如何刷写 Red Pitaya QSPI eMMC 模块上的 eMMC 存储器。该流程使用 U-boot 的 USB Mass Storage（UMS）模拟功能，将 eMMC 作为标准 USB 存储设备呈现，从而可以从 PC 写入 Red Pitaya OS 镜像，操作方式与普通 SD 卡相同。

.. contents::
    :local:
    :backlinks: none
    :depth: 1

|

.. _emmc_flash_watchdog_note:

重要：停止 U-boot 自动启动时的看门狗行为
==========================================================

.. warning::

    在 U-boot 自动启动倒计时期间停止板卡，**会导致 QSPI eMMC 模块重启 Red Pitaya**。在此启动阶段，Zynq 处理器尚未启动 Red Pitaya OS，因此 E3 连接器上没有看门狗喂狗信号。E3 模块固件会将看门狗信号缺失视为系统故障，并触发电源复位。

    **尝试停止自动启动并进入 U-boot 控制台前，必须禁用看门狗。**

可以通过两种方式禁用看门狗：

**选项 1 — 修改 E3 模块固件（当前支持）**

    修改 E3 模块固件源代码以禁用看门狗定时器检查，然后重新刷写 QSPI eMMC 模块上的 STM32 微控制器，再继续执行 eMMC 刷写步骤。

    有关构建和编程 E3 固件的说明，请参阅 :ref:`E3 QSPI eMMC 模块软件指南 <E3_QSPI_eMMC_module_SW>`。

**选项 2 — 通过 I2C 发送看门狗禁用命令（未来 OS 版本提供）**

    未来的 Red Pitaya OS 版本将支持在重启进入 U-boot 前，通过 I2C 向 E3 模块发送看门狗禁用命令。此功能可用后，将不再需要选项 1 中的固件修改。

    有关 E3 模块支持的 I2C 命令，请参阅 :ref:`E3 I2C 控制器实用程序 <e3_i2c_controller_util>`。

|

前提条件
=============

继续之前，请确保具备以下条件：

* 一块已连接 QSPI eMMC 模块的 Red Pitaya 板卡（参见 :ref:`QSPI eMMC 板连接 <QSPI_eMMC_board>`）。
* 一根连接到 Red Pitaya **CON** 端口的 USB 转串口控制台线缆。
* 一个配置为 **115200 波特率、8N1** 的终端程序，例如 PuTTY、minicom 或 screen。
* 一台运行 `balenaEtcher <https://etcher.balena.io/>`_ 等磁盘镜像写入工具的 PC。
* 一根用于连接 Red Pitaya USB 端口和 PC 的 USB 线缆（eMMC 将显示为 USB 驱动器）。
* 已在 QSPI eMMC 模块上禁用看门狗（参见上文 :ref:`emmc_flash_watchdog_note`）。

.. note::

    官方 eMMC 支持要求 Red Pitaya OS 中包含支持 eMMC UMS 的 U-boot。请确保使用 OS 2.00 或更高版本。如果稳定版本尚未包含完整的 eMMC 支持，请按照 :ref:`每夜构建版安装指南 <nightly_build_installation>` 获取包含所需 U-boot 版本的构建。

|

刷写流程
==================

按照以下步骤将 Red Pitaya OS 刷写到 eMMC：

步骤 1：准备 SD 卡
----------------------------

将 Red Pitaya OS 2.00（或更高版本）镜像刷写到 microSD 卡。详细说明请参阅 :ref:`SD 卡准备指南 <prepareSD>`。

如果稳定版本尚未包含 eMMC 支持，请按照 :ref:`每夜构建版安装指南 <nightly_build_installation>`，在 SD 卡上安装最新的每夜构建版生态系统。

|

步骤 2：启动并停在 U-boot
---------------------------------

.. important::

    执行此步骤 **之前**，必须禁用 QSPI eMMC 模块上的看门狗。请参阅上文 :ref:`emmc_flash_watchdog_note`。

1.  将准备好的 SD 卡插入 Red Pitaya，并按下 QSPI eMMC 模块上的 **P-ON** 按钮开启板卡。
#.  打开连接到 Red Pitaya **CON** 串口控制台的串口终端（115200 波特率、8N1）。
#.  观察控制台输出。出现以下消息时，**立即按任意键** 停止自动启动：

    .. code-block:: text

        Hit any key to stop autoboot:

#.  此时应看到 U-boot 命令提示符：

    .. code-block:: text

        U-Boot>

|

步骤 3：启动 USB Mass Storage 模拟
-----------------------------------------

在 U-boot 提示符下输入以下命令，将 eMMC 作为 USB Mass Storage 设备呈现：

.. code-block:: text

    ums 0 mmc 0

此时 eMMC 将在 PC 上显示为可移动 USB 驱动器。UMS 会话处于活动状态时，U-boot 会定期向控制台输出状态消息。

.. note::

    ``mmc 0`` 指 eMMC 设备。某些板卡配置的设备索引可能不同。如果命令失败，请检查 U-boot 输出以确定正确的设备索引。

|

步骤 4：将 OS 镜像刷写到 eMMC
----------------------------------------

在 PC 上使用 balenaEtcher（或等效工具），将同一个 Red Pitaya OS 镜像写入上一步出现的 eMMC USB 驱动器。操作流程与 :ref:`SD 卡准备指南 <prepareSD>` 中介绍的标准 SD 卡写入流程相同。

.. note::

    如果需要每夜构建版生态系统，请先写入 Linux OS 镜像，然后按照 :ref:`每夜构建版安装指南 <nightly_build_installation>`，将生态系统归档文件直接解压到 eMMC 驱动器。

|

步骤 5：退出 UMS 模式并启动完整系统
------------------------------------------------

1.  镜像写入完成后，在 PC 上安全弹出 USB 驱动器。
#.  在串口终端中按 **Ctrl+C** 停止 UMS 会话并返回 U-boot 提示符。
#.  输入 ``reset`` （或使用 P-ON 按钮对板卡重新上电），从 SD 卡重新启动进入完整 OS：

    .. code-block:: text

        reset

|

步骤 6：将引导加载程序写入 QSPI 闪存
--------------------------------------------

Red Pitaya 从 SD 卡启动后，使用默认凭据（**root / root**）登录 Linux 控制台，并将启动镜像写入 QSPI 闪存：

.. code-block:: bash

    flashcp /opt/redpitaya/boot.bin /dev/mtd0

此操作会使用最新的引导加载程序对板载 QSPI 闪存进行编程；板卡要在未插入 SD 卡时从 eMMC 启动，必须完成此步骤。

.. warning::

    运行此命令前，请确保 Red Pitaya OS 已完全启动。对不完整或错误的 ``boot.bin`` 文件运行 ``flashcp``，可能导致板卡无法从 QSPI/eMMC 启动。

|

步骤 7：取出 SD 卡并从 eMMC 启动
-----------------------------------------------

1.  按住 **P-ON** 按钮 1 秒，关闭 Red Pitaya。
#.  从 SD 卡槽中取出 microSD 卡。
#.  打开 QSPI eMMC 模块上的 :ref:`eMMC 开关 <eMMC_switch>`，启用 eMMC 启动。
#.  按下 **P-ON** 按钮开启板卡。Red Pitaya 此时将从 eMMC 启动。

|

步骤摘要
=================

1.  禁用 E3 模块上的看门狗（修改固件或使用 I2C 命令）。
#.  准备一张安装了 Red Pitaya OS 2.00 或更高版本的 SD 卡（如有需要，包括每夜构建版）。
#.  启动板卡，在 U-boot 自动启动阶段停止，并运行 ``ums 0 mmc 0``。
#.  从 PC 将 OS 镜像刷写到 eMMC。
#.  从 SD 卡重新启动进入完整 OS。
#.  使用 ``flashcp /opt/redpitaya/boot.bin /dev/mtd0`` 将 ``boot.bin`` 写入 QSPI 闪存。
#.  关机、取出 SD 卡、启用 :ref:`eMMC 启动 <eMMC_switch>`，然后开机。

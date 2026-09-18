.. _SW_build_os:

###################
构建 Red Pitaya OS
###################

本指南介绍如何为 Red Pitaya 构建基于 Debian/Ubuntu 的 SD 卡镜像。

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

简介
==============

Red Pitaya OS 由两个主要组件组成：

1. **Debian/Ubuntu OS** （Ext4 分区）——包含基础操作系统、应用程序、库和服务
2. **生态系统** （FAT32 分区）——包含启动文件、FPGA 位流、内核和用户空间应用程序

两个组件都是系统正常运行所必需的。 OS 提供运行时环境，而生态系统
提供硬件接口和 Red Pitaya 专用应用。

|

构建脚本概览
======================

主要构建脚本
-------------------

以下脚本位于 ``debian`` 目录中，可直接执行：

.. list-table::
    :widths: 21 78
    :header-rows: 1

    * - Script
      - 描述
    * - ``image.sh``
      - 完整 SD 卡镜像构建流程（创建并格式化分区）
    * - ``image-update.sh``
      - 使用新的 ``ecosystem_*.zip``
    * - ``image-fsck.sh``
      - 对 SD 卡镜像分区运行 FSCK（用于从使用过的 SD 卡创建的镜像）
    * - ``image-clean.sh``
      - 已弃用


Chroot 环境脚本
----------------------------

以下脚本 are designed to run exclusively within a ``chroot`` environment:

.. warning::

    不要直接在主机 OS 上执行这些脚本。 它们会修改系统级配置，可能对主机系统造成严重损害。

.. list-table::
    :widths: 21 111
    :header-rows: 1

    * - Script
      - 描述
    * - ``ubuntu.sh``
      - Ubuntu 引导, locale, apt configuration, timezone, fake HW clock
    * - ``debian.sh``
      - Debian 引导（**实验性功能**，Web 应用程序尚不可用）
    * - ``tools.sh``
      - 软件编译工具
    * - ``zynq.sh``
      - ZYNQ 芯片硬件支持（U-Boot、I2C、EEPROM、dtc、IIO、NE10?、GPIO，以及具有硬件访问权限的用户组）
    * - ``network.sh``
      - ``systemd-networkd`` based wired/wireless network configuration and required tools (hostAP, supplicant)
    * - ``redpitaya.sh``
      - 生态系统应用所需的库（boost、jpeg、json），并安装和启用服务
    * - ``jupyter.sh``
      - Jupyter with NumPy and SciPy
    * - ``cmake3.21.sh``
      - 构建生态系统所需版本的 CMake
    * - ``watchdog.sh``
      - 配置看门狗服务
    * - ``tft.sh``
      - X-server and XFCE


配置文件
--------------------

The ``overlay`` directory contains configuration files that are installed individually onto the OS by the build scripts.

|

了解构建过程
=================================

OS 镜像内容
------------------

完整的 SD 卡镜像包含：

1.  **Debian/Ubuntu OS** (Ext4 partition):

    * 基础操作系统文件
    * 其他操作系统应用和库
    * Systemd 服务
    * 大部分网络配置文件
    * Jupyter 工作区


2.  **生态系统** (FAT32 分区):

    *   **裸机组件：**

        * ``boot.bin`` - 包含 FSBL、FPGA 比特流和 U-Boot
        * Linux 内核镜像和设备树文件
        * 备用 FPGA 比特流及对应的设备树覆盖层

    *   **用户空间组件：**

        * Bazaar 服务器（Nginx）和 WEB 应用
        * Red Pitaya API 库
        * SCPI 服务器

|

引导过程
--------------------

要构建可用的 OS 镜像，需要生态系统，因为没有 ``boot.bin`` and the Linux kernel,
系统将无法启动。同样，构建生态系统需要 OS 镜像，因为用户空间应用
是在模拟 ARM CPU 的 ``chroot`` 环境中构建的。

这会产生先有鸡还是先有蛋的问题。 首次构建流程如下：

1.  **构建不含生态系统的 OS 镜像**

    这将创建：

    * ``redpitaya_OS_*.img`` - 不可用的 SD 卡镜像（缺少启动文件和内核）
    * ``redpitaya_OS_*.tar.gz`` - 用于创建 ``chroot`` 环境的归档文件

2.  **在 chroot 环境中构建生态系统**

    * 使用 ``redpitaya_OS_*.tar.gz`` 文件创建 ``chroot`` 环境
    * 在 ``chroot`` 中执行必要脚本以构建生态系统
    * 生成 ``ecosystem_*.zip`` 文件

3.  **将 OS 镜像与生态系统合并**

    .. code-block:: shell-session

        OS/debian/image-update.sh redpitaya_OS_*.img ecosystem_*.zip


完成引导流程后，可以独立构建任一组件。 典型工作流是构建
在现有 ``chroot`` 环境中构建新的生态系统并更新 SD 卡。当项目根目录中存在 ``ecosystem_*.zip`` 文件后，
新的 OS 镜像会在构建过程中自动集成该文件。

|

.. _SW_os_req:

前置条件
==============

主机系统要求
--------------------------

要构建 Red Pitaya Debian/Ubuntu OS 镜像，需要运行 Ubuntu 的主机 PC。

.. list-table::
    :widths: 33 33
    :header-rows: 1

    * - Red Pitaya OS 版本
      - 主机平台 OS
    * - OS 3.0 及更高版本
      - Ubuntu 24.04 LTS 或更高版本
    * - OS 2.0 及更高版本
      - Ubuntu 22.04 LTS 或更高版本
    * - OS 1.04
      - Ubuntu 18.04 LTS 或更高版本

.. note::

    Vivado 2020 (FPGA 汇编所需) 无法安装在 Ubuntu 18.04. 因此，对于 OS 2.0 及更高版本，
    需要 Ubuntu 22.04 或更高版本。


所需软件包
------------------

以下示例使用 Ubuntu 22.04 LTS, 但其他 Ubuntu 版本的流程类似。

在主机 PC 上安装所需软件包：

.. code-block:: shell-session

    $ sudo apt-get install debootstrap qemu-user-static

|

构建 OS 镜像
=======================

按照以下步骤构建完整的 Red Pitaya OS 镜像。

步骤 1：克隆 GitHub 仓库
-------------------------------------

.. tabs::

    .. group-tab:: OS 2.0 或更高版本

        OS 构建脚本维护在独立的 :rp-github:`Ubuntu 仓库中 <ubuntu>`:

        .. code-block:: shell-session

            $ git clone https://github.com/RedPitaya/ubuntu.git
            cd ubuntu

    .. group-tab:: OS 1.04 或更低版本

        OS 构建脚本维护在主 :rp-github:`Red Pitaya 仓库 <RedPitaya>` 中：

        .. code-block:: shell-session

            $ git clone https://github.com/RedPitaya/RedPitaya.git
            cd RedPitaya

|

步骤 2：构建生态系统
-----------------------------

构建 OS 镜像前必须先构建生态系统。 请按照 :ref:`生态系统 <SW_build_ecosystem>`
章节中的说明完成此步骤。

.. note::

    首次引导时可跳过此步骤，先构建不可用的 OS 镜像，
    再使用它创建用于构建生态系统的 ``chroot`` 环境。

|

步骤 3：构建 OS 镜像
----------------------------

以 root 权限执行构建脚本：

.. tabs::

    .. group-tab:: OS 2.00 或更高版本

        .. code-block:: shell-session

            $ sudo build.sh

        ``build.sh`` 脚本调用 :rp-github:`image.sh <ubuntu/blob/main/debian/image.sh>`，执行完整的 OS 镜像构建流程。

    .. group-tab:: OS 1.04 或更低版本

        .. code-block:: shell-session

            $ sudo OS/debian/image.sh

.. warning::

    必须以 ``root`` 用户执行此脚本。 如果未切换到 root 就使用 ``sudo`` 运行，
    部分配置文件会被放置到错误用户的主目录中。

.. note::

    如果项目根目录中存在 ``ecosystem_*.zip`` 文件，它会自动集成
    到 OS 镜像中，从而创建完整可用的 SD 卡镜像。

|

构建过程中发生的操作
-------------------------------

构建过程中会执行以下步骤：

1.  **镜像创建**

    :rp-github:`image.sh <ubuntu/blob/main/debian/image.sh>` 创建文件名带时间戳的 SD 卡镜像。
    会创建两个分区：

    * 1024 MB FAT32 分区 用于生态系统
    * 剩余 SD 卡空间上的 OS Ext4 分区

2.  **基础系统安装**

    :rp-github:`image.sh <ubuntu/blob/main/debian/image.sh>` calls :rp-github:`ubuntu.sh <ubuntu/blob/main/debian/ubuntu.sh>`,
    用于安装基础系统和其他软件包，并配置：

    * APT（Debian 软件包系统）
    * 区域设置
    * 主机名
    * Time zone
    * 文件系统表
    * U-Boot
    * 用户和 UART 控制台访问

3.  **网络配置**

    :rp-github:`ubuntu.sh <ubuntu/blob/main/debian/ubuntu.sh>` 执行 :rp-github:`network.sh <ubuntu/blob/main/debian/network.sh>`，
    用于创建基于 ``systemd-networkd`` 的有线和无线网络配置。

4.  **Red Pitaya 专用配置**

    :rp-github:`redpitaya.sh <ubuntu/blob/main/debian/redpitaya.sh>` 安装其他 Debian 软件包
    （主要是库）Red Pitaya 应用所需的，并将 ``ecosystem*.zip`` 文件
    (（如果存在）) 到 FAT 分区中。

5.  **可选组件** (可注释掉)

    * :rp-github:`jupyter.sh <ubuntu/blob/main/debian/jupyter.sh>` - 安装 Jupyter notebook
    * :rp-github:`tft.sh <ubuntu/blob/main/debian/tft.sh>` - 安装 X-server 和 XFCE 桌面环境

|

更新现有镜像
============================

如果需要在不修改 Ext4 分区的情况下使用新生态系统更新现有 OS 镜像：


更新生态系统
---------------------

将镜像和生态系统文件作为参数执行更新脚本：

.. code-block:: shell-session

    $ sudo OS/debian/image-update.sh redpitaya_OS_*.img ecosystem_*.zip


Write to SD card
-----------------

更新镜像后，将其写入 micro SD 卡（最小 16 GB）：

.. code-block:: shell-session

    $ sudo dd bs=4M if=redpitaya_OS_*.img of=/dev/mmcblk0 status=progress

|

镜像维护
==================

文件系统检查
------------------

如果镜像经过用户执行的多个步骤创建（例如在运行中的 Red Pitaya 上进行安装或设置），
文件系统可能损坏。 The :rp-github:`image-fsck.sh <ubuntu/blob/main/debian/image-fsck.sh>` script 执行
文件系统检查且不做任何修改。

发布前在镜像上运行此脚本：

.. code-block:: shell-session

    $ sudo OS/debian/image-fsck.sh redpitaya_OS_*.img

|

缩减镜像大小
--------------------

.. warning::

    仅在运行中的 Red Pitaya 板卡上执行这些步骤。在主机 OS 上执行会导致问题。

可以通过清理操作缩减镜像大小：

* 删除未使用的软件（这些软件可能仅在编译时需要）
* 删除未使用的源文件和仓库
* Remove temporary files
* 将分区空闲空间填零

执行以下命令删除 APT 临时文件并清理空闲空间：

.. code-block:: shell-session

    $ apt-get clean
    $ cat /dev/zero > zero.file
    $ sync
    $ rm -f zero.file
    $ history -c

|

管理运行中的系统
=============================

Systemd 服务
-----------------

Red Pitaya 使用 ``systemd`` 作为 init 系统。服务控制 Red Pitaya 应用和服务器的启动与运行。

Service files are located in: ``OS/debian/overlay/etc/systemd/system/*.service``

可用服务
^^^^^^^^^^^^^^^^^^^

.. list-table::
    :widths: 25 100
    :header-rows: 1

    * - Service
      - 描述
    * - ``jupyter``
      - 用于 Python 开发的 Jupyter notebook
    * - ``redpitaya_scpi``
      - SCPI 服务器 (默认禁用，与 WEB 应用冲突)
    * - ``redpitaya_nginx``
      - 基于 Nginx 的 WEB 应用服务器


服务命令
^^^^^^^^^^^^^^^^^

启动或停止服务：

.. code-block:: shell-session

    $ systemctl start {service_name}
    $ systemctl stop {service_name}

在启动时启用或禁用服务：

.. code-block:: shell-session

    $ systemctl enable {service_name}
    $ systemctl disable {service_name}

检查服务状态：

.. code-block:: shell-session

    $ systemctl status {service_name}

|

系统调试
-----------------

分析启动过程和服务依赖关系
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

生成启动过程的可视化表示：

.. code-block:: shell-session

    $ systemd-analyze plot > /opt/redpitaya/www/apps/systemd-plot.svg
    $ systemd-analyze dot | dot -Tsvg > /opt/redpitaya/www/apps/systemd-dot.svg

这些命令会创建显示启动时间线和服务依赖图的 SVG 文件，可通过 Web 界面查看。

|

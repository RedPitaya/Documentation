.. _wsl_setup:

##################################
Windows Linux 子系统设置
##################################

Windows Linux 子系统（WSL）直接在 Windows 上提供 Linux 环境，可用于以下 Red Pitaya 开发任务：

- 使用 ``minicom`` 访问串行控制台
- 构建和编译软件
- 运行基于 Linux 的开发工具
- 访问 USB 设备（包括 Red Pitaya SD 卡）

本指南介绍 WSL 的安装、性能优化配置以及 USB 设备访问设置。

|

前置条件
=============

- Windows 10 版本 2004 及更高版本（Build 19041 及更高版本）或 Windows 11
- Windows 系统的管理员访问权限

|

WSL 基本安装
======================

Microsoft 提供了完整的安装说明。建议安装最新可用的 Ubuntu LTS 版本。

- |WSL| - Microsoft 官方 WSL 安装指南

快速安装（推荐）：

1.  以 **管理员** 身份打开 PowerShell 或 Windows 命令提示符
2.  运行安装命令：

    .. code-block:: powershell

        wsl --install

3.  按提示重启计算机
4.  重启后将打开 Linux 终端，以完成 Ubuntu 设置
5.  为 Linux 环境创建用户名和密码

.. note::

    默认 WSL 安装使用 WSL 2，它提供更好的性能和完整的系统调用兼容性。

|

USB 设备访问设置
========================

要将 USB 设备（例如 Red Pitaya 的串行控制台或 SD 卡读卡器）连接到 WSL，需要安装 ``usbipd-win``。

- |WSL-USB| - Microsoft 官方 USB 设备连接指南

安装 ``usbipd-win``
-------------------------

1.  以 **管理员** 身份打开 PowerShell 或 Windows 命令提示符
2.  使用 ``winget`` 安装：

    .. code-block:: powershell

        winget install usbipd

也可以从 |usbipd-releases| 页面下载并安装。

安装 Linux 工具
----------------------

在 WSL 终端中安装所需的 Linux 工具：

.. code-block:: bash

    sudo apt update
    sudo apt install linux-tools-generic hwdata minicom
    sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20

|

WSL 配置（.wslconfig）
==============================

要针对 Red Pitaya 开发优化 WSL，尤其是 USB 设备访问，应使用 ``.wslconfig`` 文件配置 WSL 设置。

创建 .wslconfig 文件
-----------------------------

应将 ``.wslconfig`` 文件放在 Windows 用户目录中：``C:\Users\<YourUsername>\.wslconfig``

.. note::

    此文件会影响计算机上运行的 **所有** WSL 2 发行版。

|

推荐配置
-------------------------

创建或编辑 ``C:\Users\<YourUsername>\.wslconfig``，内容如下：

.. code-block:: ini

    [wsl2]
    dnsTunneling=true
    networkingMode=mirrored

配置说明：

- **dnsTunneling=true** - 通过 Windows 隧道传输 DNS 查询，改善 DNS 解析，有助于解决网络连接问题。
- **networkingMode=mirrored** - 将 Windows 的网络接口镜像到 WSL，提供更好的网络兼容性，使 WSL 更容易访问本地网络上的设备。这对 USB 设备直通以及通过网络访问 Red Pitaya 尤其有用。

.. important::

    创建或修改 ``.wslconfig`` 文件后，必须重启 WSL 才能使更改生效：

    .. code-block:: powershell

        wsl --shutdown

    然后正常重启 WSL 发行版。

|

其他配置选项
--------------------------------

您可以添加其他设置，以根据需要优化 WSL。以下是一些常用选项：

.. code-block:: ini

    [wsl2]
    dnsTunneling=true
    networkingMode=mirrored
    
    # Memory allocation (default is 50% of total RAM)
    memory=8GB
    
    # Number of processors (default is all processors)
    processors=4
    
    # Swap space
    swap=4GB
    
    # Enable nested virtualization (for running VMs in WSL)
    nestedVirtualization=true

完整配置选项列表请参见 |WSL-config| 页面。

|

验证安装
===========================

验证 WSL 是否正确安装：

1.  打开 PowerShell 或 Windows 命令提示符窗口
2.  运行：

    .. code-block:: powershell

        wsl --list --verbose

    应看到已安装且版本为 2 的 Linux 发行版：

    .. code-block:: none

        NAME            STATE           VERSION
        * Ubuntu        Running         2

3.  启动 WSL：

    .. code-block:: powershell

        wsl

4. 现在应已进入 Linux 终端，可以运行 Linux 命令。

|

后续步骤
==========

完成 WSL 设置后，您可以：

- 使用它访问 :ref:`Red Pitaya 串行控制台 <console>`
- 安装用于构建 Red Pitaya 软件的开发工具
- 从 Windows 计算机访问 Red Pitaya SD 卡内容

|

故障排除
===============

WSL 无法启动
-------------------

1.  确保 BIOS/UEFI 中已启用虚拟化
2.  检查 Windows Hypervisor Platform 是否已启用：

    - 打开“启用或关闭 Windows 功能”
    - 启用“虚拟机平台”和“适用于 Linux 的 Windows 子系统”
    - 重启计算机

USB 设备未出现在 WSL 中
--------------------------------

1. 确保使用 ``usbipd`` 绑定并附加了设备
2. 检查 Linux 工具是否已在 WSL 中正确安装
3. 确认 .wslconfig 设置已生效（更改后重启 WSL）

网络连接问题
---------------------------

1. 检查 .wslconfig 文件是否包含 ``dnsTunneling=true`` 和 ``networkingMode=mirrored``
2. 使用 ``wsl --shutdown`` 重启 WSL，然后再次启动
3. 在 WSL 中尝试更新 ``/etc/resolv.conf`` 中的 DNS 设置

|

.. |WSL-config| raw:: html

    <a href="https://learn.microsoft.com/en-us/windows/wsl/wsl-config" target="_blank">WSL 配置文档</a>

.. |usbipd-releases| raw:: html

    <a href="https://github.com/dorssel/usbipd-win/releases" target="_blank">usbipd-win releases</a>

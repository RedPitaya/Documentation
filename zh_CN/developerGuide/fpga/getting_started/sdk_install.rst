.. _fpga_install_sdk:

#############################################
安装 Xilinx SDK 2019.1（旧版）
#############################################

本安装教程适用于希望开发 FPGA 项目、并且还需要修改 Red Pitaya 板卡上 ARM 处理器所运行软件的用户，例如创建自定义设备驱动程序或修改第一阶段启动加载器（FSBL）。

.. warning::

    本页面仅适用于旧版工具链。

    * **OS 1.04 - 2.00 请使用本页面** （Vivado 2020.1 + SDK 2019.1）。
    * **对于 OS 3.00 或更高版本，请使用 Vitis 2025.1**，安装流程见 :ref:`Vivado 安装指南 <FPGA_install_vivado>`。
   
    完整的旧版构建和项目生成命令流程请参见
    :ref:`旧版 Vivado 2020.1 兼容性 <fpga_legacy_2020_flow>`。

.. contents:: 目录
    :local:
    :depth: 2
    :backlinks: top

|

概述
=========

**什么是 Xilinx SDK？**

Xilinx Software Development Kit（SDK）是用于创建嵌入式软件应用程序的集成开发环境。在 Red Pitaya FPGA 开发中，SDK 用于：

- 生成第一阶段启动加载器（FSBL）
- 创建和修改设备树文件
- 开发自定义 Linux 驱动程序
- 为 ARM 处理器构建裸机应用程序
- 调试硬件-软件接口

**为什么使用 SDK 2019.1？**

Red Pitaya FPGA 项目专门配置为使用 SDK 2019.1。使用其他版本可能会导致以下组件出现兼容性问题：

- 设备树生成脚本
- FSBL 编译
- Vivado 生成的硬件交接文件
- 自动化构建脚本

.. note::

    AMD（Xilinx）从 2019.2 版本开始以 Vitis 替代 SDK。

    Red Pitaya OS 3.00 或更高版本已经使用 Vitis 2025.1。本 SDK 页面仅为与旧版 OS 分支保持向后兼容而保留。

|

前置条件
==============

安装 SDK 前，请确保具备以下条件：

**系统要求**

- **Operating System:** 
  
  - Ubuntu 18.04/20.04/22.04/24.04
  - Windows 10 或更高版本（存在限制，不推荐）
  
- **磁盘空间：** 至少 60 GB 可用空间（推荐 100 GB）
- **内存：** 至少 8 GB（推荐 16 GB）
- **网络连接：** 用于下载安装程序（约 24 GB）

**软件前置条件**

- 必须先安装 **Vivado 2020.1** （参见 :ref:`Vivado 安装指南 <FPGA_install_vivado>`）
- **Git** 命令行工具
- 所需的系统库（Linux）

**用户账户**

- AMD 账户（免费注册地址：https://login.amd.com/）
- 下载存档 SDK 版本的权限

.. note::

    构建 :ref:`Red Pitaya OS <SW_os_req>` 和 :ref:`生态系统 <SW_ecosys_req>` 都需要 SDK 2019.1，且二者仅支持 Ubuntu Linux。
    为获得最佳的基于 SDK 的项目构建效果，请使用 Ubuntu 作为原生平台。

|

安装步骤
===================

下载 SDK 2019.1 安装程序
-------------------------------

1. **创建/登录 AMD 账户**

    访问 |AMD-login|；如果还没有账户，请创建一个免费账户。

2. **进入 Vivado SDK 下载页面**

    进入 |Vivado-downloads-archive| （Vitis/SDK 存档页面）。

3. **选择 Vivado 2019.1**

    - 滚动查找 **2019.1** 版本
    - 页面会显示多个安装程序选项，请找到以下版本：
   
        - **Vivado Design Suite - HLx Editions - 2019.1  Full Product Installation**

4. **下载安装程序**

    - 下载：``Vivado HLx 2019.1: All OS installer Single-File Download``
    - 文件大小：约 21.39 GB

    .. figure:: img/SDK-install/SDK-tar-file.png
        :align: center
        :width: 1000

.. note::

    **重要：** 由于 SDK 网络安装程序已经无法使用，请从存档下载完整的 Vivado 2019.1 安装程序，其中也包含 SDK 2019.1。

|

安装所需库（仅 Linux）
----------------------------------------

在 Linux 上运行 SDK 安装程序前，请安装所需的系统库：

.. code-block:: bash

   # Update package list
   sudo apt update
   
   # Install required libraries for SDK
   sudo apt install -y \
       libxft2 \
       libxft2:i386 \
       lib32stdc++6 \
       libgtk2.0-0:i386 \
       dpkg-dev:i386 \
       libncurses5 \
       libtinfo5
   
   # Install additional dependencies for FSBL and device tree generation
   sudo apt install -y \
       libncurses-dev \
       libedit-dev \
       libxrender-dev \
       libxrender-dev:i386 \
       libxt6 \
       libxt6:i386

.. note::

   如果使用 Ubuntu 22.04 或更新版本，默认软件仓库中可能没有某些 32 位库。如果遇到软件包缺失错误，可能需要启用 i386 架构：

   .. code-block:: bash

      sudo dpkg --add-architecture i386
      sudo apt update
      sudo apt install <package-name>:i386

|

运行 SDK 安装程序
-----------------------

Linux 安装
~~~~~~~~~~~~~~~~~~~

1. **解压安装程序：**

    - 进入下载目录
    - 解压下载的 ``.tar.gz`` 文件：
    
    .. code-block:: bash
    
        tar -xvf Xilinx_Vivado_SDK_2019.1_0524_1430.tar.gz

2. **使安装程序可执行：**

    .. code-block:: bash

        # Navigate to download directory
        cd ~/Downloads
        
        # Make installer executable
        chmod +x Xilinx_Vivado_SDK_2019.1_0524_1430.bin

3. **处理 OS 版本警告（Ubuntu 20.04/22.04）：**

    Vivado SDK 2019.1 官方支持 Ubuntu 18.04。如果运行的是更新版本，且安装程序给出 OS 版本警告，可以临时修改 ``/etc/os-release``：

    .. code-block:: bash

        # Backup the original file
        sudo cp /etc/os-release /etc/os-release.backup
        
        # Edit the file
        sudo nano /etc/os-release

    Change the VERSION line to:

    .. code-block:: text

        VERSION="18.04.4 LTS (Bionic Beaver)"

    Save and exit (Ctrl+X, then Y, then Enter).

    .. figure:: img/Vivado-installer-linux-warning3.png
        :align: center
        :width: 800

3. **运行安装程序：**

    .. code-block:: bash

        # Run installer
        sudo ./Xilinx_Vivado_SDK_2019.1_0524_1430.bin

    The graphical installer will launch.

4. **恢复 os-release（重要！）：**

    安装完成后，恢复原始文件：

    .. code-block:: bash

        sudo mv /etc/os-release.backup /etc/os-release

    **Failure to restore this file may cause issues with other software!**

|

Windows 安装
~~~~~~~~~~~~~~~~~~~~~

1. **解压安装程序：**

    - 进入下载目录
    - 使用 7-Zip 或类似工具解压下载的 ``.tar.gz`` 文件。

1. **运行安装程序可执行文件：**

   - 打开解压后的文件夹并运行 ``xsetup.exe`` 可执行文件。
   - Windows 可能会请求管理员权限，请点击 “Yes”

2. **按照安装向导操作：**

   图形化安装程序将启动。

|

SDK 安装向导步骤
-------------------------------

1. **欢迎界面**

    - 如果出现 “newer version available” 消息，请将其关闭。
    - 点击 **Next**

    .. figure:: img/SDK-install/SDK-installer-1.png
        :align: center
        :width: 1000

2. **接受许可协议**

    - 勾选所有 “I Agree” 复选框
    - 点击 **Next**

    .. figure:: img/SDK-install/SDK-installer-2.png
        :align: center
        :width: 1000

3. **选择版本**

    - 选择 **Vivado HL Design Edition**
    - 点击 **Next**

    .. figure:: img/SDK-install/SDK-installer-3.png
        :align: center
        :width: 1000

    .. note::

        Vivado HL Design Edition 也包含 SDK 2019.1。

4. **选择安装选项**

   勾选以下组件：

   - ✅ **Software Development Kit (SDK)**
   - ✅ **DocNav** （文档浏览器，可选但推荐）

   取消勾选不需要的组件以节省空间。参考下图。

    .. figure:: img/SDK-install/SDK-installer-4.png
        :align: center
        :width: 1000

5. **选择安装位置**

    **默认路径：**
    
    - **Linux:** ``/opt/Xilinx/SDK/2019.1`` or ``/tools/Xilinx/SDK/2019.1``
    - **Windows:** ``C:\Xilinx\SDK\2019.1``

    .. note::

        **Linux 重要提示：** 如果将 Vivado 安装在 ``/opt/Xilinx/``，请将 SDK 安装到相同的父目录（``/opt/Xilinx/SDK/2019.1``），以便统一管理工具。

    点击 **Next**

    .. figure:: img/SDK-install/SDK-installer-5.png
       :align: center
       :width: 1000

6. **安装摘要**

    - 检查所选内容
    - 注意安装大小（约 25 GB）
    - 点击 **Install**

    .. figure:: img/SDK-install/SDK-installer-6.png
        :align: center
        :width: 1000

7. **安装进度**

    - 根据系统性能，安装可能需要 30-60 分钟

8. **安装完成**

    - 点击 **Finish**
    - **不要** 立即启动 SDK；需要先配置环境变量

9. **删除 Vivado 2019.1 文件（可选）**

    由于已经安装 Vivado 2020.1，可以删除 Vivado 2019.1 文件以释放磁盘空间：

    .. code-block:: bash

        sudo rm -rf /opt/Xilinx/Vivado/2019.1

10. **恢复 os-release（仅 Linux）**

    如果之前修改过 ``/etc/os-release``，请按照 Linux 安装部分第 4 步所述，确保已将其恢复为原始版本。

|

安装后配置
=================================

环境变量（Linux）
-------------------------------

安装完成后，必须配置环境变量，以便系统能够找到 SDK 可执行文件。

**临时配置（仅当前终端会话）**

在终端中运行以下命令：

.. code-block:: bash

    # Source SDK settings script
    source /opt/Xilinx/SDK/2019.1/settings64.sh
    
    # Add SDK to PATH (may be necessary for some tools)
    export PATH=/opt/Xilinx/SDK/2019.1/bin:$PATH

.. note::

    如果安装目录不同，请将 ``/opt/Xilinx/`` 替换为实际安装目录。

**永久配置（推荐）**

将 SDK 设置添加到 ``.bashrc`` 文件，以便自动加载：

.. code-block:: bash

    # Open .bashrc in text editor
    nano ~/.bashrc

将以下行添加到文件末尾：

.. code-block:: bash

    # Xilinx Vivado 2020.1 settings
    source /opt/Xilinx/Vivado/2020.1/settings64.sh
    
    # Xilinx SDK 2019.1 settings
    source /opt/Xilinx/SDK/2019.1/settings64.sh
    
    # Add SDK to PATH
    export PATH=/opt/Xilinx/SDK/2019.1/bin:$PATH

保存并退出（Ctrl+X、Y、Enter）。

**应用更改：**

.. code-block:: bash

    # Reload .bashrc
    source ~/.bashrc

|

环境变量（Windows）
---------------------------------

**方法 1：自动设置**

Windows 安装程序通常会自动添加环境变量。打开新的命令提示符并输入以下命令进行验证：

.. code-block:: batch

    echo %XILINX_SDK%

如果显示 SDK 路径，则配置完成；否则请继续使用方法 2。

**方法 2：手动配置**

1. 右键点击 “This PC” 或 “My Computer” → **Properties**
2. 点击 **Advanced system settings**
3. 点击 **Environment Variables**
4. 在 “System variables” 下点击 **New**

添加以下变量：

- **Variable name:** ``XILINX_SDK``
  **Variable value:** ``C:\Xilinx\SDK\2019.1``

- **Variable name:** ``XILINX_VIVADO``
  **Variable value:** ``C:\Xilinx\Vivado\2020.1``

5. 编辑 **Path** 变量：
   
    - 选择 **Path** → 点击 **Edit**
    - 点击 **New**
    - 添加：``C:\Xilinx\SDK\2019.1\bin``
    - 添加：``C:\Xilinx\Vivado\2020.1\bin``

6. 在所有窗口中点击 **OK**

7. **重启终端** 或计算机，使更改生效

详细的 Windows PATH 说明请参见 `Windows PATH 指南 <https://www.computerhope.com/issues/ch000549.htm>`__。

|

验证安装
====================

测试 SDK 命令行工具
-----------------------------

**Linux：**

.. code-block:: bash

    # Check SDK version
    which xsdk
    
    # Expected output: /opt/Xilinx/SDK/2019.1/bin/xsdk
    
    # Check HSI (Hardware Software Interface) tool
    which hsi
    
    # Expected output: /opt/Xilinx/SDK/2019.1/bin/hsi
    
    # Verify SDK is in PATH
    echo $PATH | grep SDK

**Windows：**

.. code-block:: batch

    # Check SDK installation
    where xsdk
    
    # Expected output: C:\Xilinx\SDK\2019.1\bin\xsdk.bat
    
    # Check environment variable
    echo %XILINX_SDK%

|

启动 SDK GUI（可选测试）
--------------------------------

要验证图形界面是否正常工作：

**Linux:**

.. code-block:: bash

    # Launch SDK
    xsdk &

**Windows:**

.. code-block:: batch

    # Launch SDK
    xsdk

SDK 应打开工作区选择对话框。确认其成功启动后即可关闭该对话框。

|

在 Red Pitaya 项目中使用 SDK
====================================

SDK 与构建系统的集成
-----------------------------------

Red Pitaya FPGA 项目使用 SDK 完成以下工作：

1. **FSBL 生成：** 创建第一阶段启动加载器
2. **设备树生成：** 为 Linux 内核生成设备树文件
3. **硬件-软件接口：** 连接 FPGA 硬件与 ARM 软件

**使用 SDK 的构建命令：**

构建 Red Pitaya FPGA 项目时，Make 会自动调用 SDK：

.. code-block:: bash

    # Build FPGA project (includes FSBL and device tree generation)
    make PRJ=v0.94 MODEL=Z10
    
    # Build only FSGA (skips SDK parts)
    make build PRJ=v0.94 MODEL=Z10

.. !! Check the make build above - does it exist?

|

使用的 SDK 组件
--------------------

**HSI（硬件软件接口）**

TCL 脚本使用 ``hsi`` 命令行工具来：

- 读取 Vivado 生成的硬件交接文件（``.hdf``）
- 生成 FSBL 源代码
- 生成设备树源文件
- 配置处理器设置

**XSCT（Xilinx 软件命令行工具）**

用于：

- 构建 FSBL 可执行文件
- 交叉编译 ARM 应用程序
- 通过 JTAG 调试

**Red Pitaya 构建中的文件位置：**

.. code-block:: console

    fpga/
    ├── prj/v0.94/
    │   └── sdk/
    │       └── fsbl/           # FSBL source generated by HSI
    ├── hsi/
    │   ├── fsbl.elf            # Compiled FSBL binary
    │   └── dts/                # Device tree sources
    └── dts/
        └── system.dts          # Final device tree file

|

SDK 常见使用场景
============================

场景 1：使用 FSBL 构建 FPGA
-------------------------------------

要构建包含 FSBL 的完整 FPGA 项目：

.. code-block:: bash

    # Navigate to FPGA repository
    cd RedPitaya-FPGA
    
    # Source environment variables (if not in .bashrc)
    source /opt/Xilinx/Vivado/2020.1/settings64.sh
    source /opt/Xilinx/SDK/2019.1/settings64.sh
    
    # Build everything (bitstream, FSBL, device tree)
    make PRJ=v0.94 MODEL=Z10

构建过程中会调用 SDK 来生成 FSBL 和设备树。

|

场景 2：仅生成 FSBL
----------------------------------

如果不重新构建整个 FPGA，只重新生成 FSBL：

.. code-block:: bash

    # Navigate to project directory
    cd RedPitaya-FPGA/prj/v0.94
    
    # Run FSBL TCL script
    hsi -source ../../red_pitaya_hsi_fsbl.tcl -tclargs v0.94 Z10

FSBL 二进制文件将生成于 ``fpga/hsi/fsbl.elf``。

|

场景 3：修改设备树
-----------------------------------

要为 FPGA 设计定制设备树：

1. **生成初始设备树：**

    .. code-block:: bash

        make PRJ=v0.94 MODEL=Z10

2. **编辑设备树源文件：**

    .. code-block:: bash

        nano fpga/dts/system.dts

3. **编译设备树：**

    .. code-block:: bash

        # Compile DTS to DTB (device tree blob)
        dtc -I dts -O dtb -o system.dtb fpga/dts/system.dts

4. **部署到 Red Pitaya：**

    .. code-block:: bash

        scp system.dtb root@rp-xxxxxx.local:/boot/devicetree.dtb

|

场景 4：创建自定义裸机应用程序
----------------------------------------------------

要创建运行在 ARM 处理器上的裸机应用程序：

1. **启动 SDK：**

    .. code-block:: bash

        xsdk &

2. **导入硬件平台：**

    - File → New → Application Project
    - 从 Vivado 导出内容中选择硬件平台（``.hdf`` 文件）

3. **编写应用程序：**

    - 选择 “Empty Application” 模板
    - 添加 C++ 源文件

4. **构建并运行：**

    - 右键点击项目 → Build Project
    - 使用 JTAG 下载并在 Red Pitaya 上运行

|

故障排除
================

SDK 无法启动
----------------

**问题：** 找不到 ``xsdk`` 命令

**解决方案：**

.. code-block:: bash

    # Check if SDK is in PATH
    echo $PATH | grep SDK
    
    # If not, source settings script
    source /opt/Xilinx/SDK/2019.1/settings64.sh
    
    # Add to .bashrc for permanent fix
    echo "source /opt/Xilinx/SDK/2019.1/settings64.sh" >> ~/.bashrc

|

HSI 命令失败
------------------

**问题：** FPGA 构建期间出现 ``hsi: command not found``

**解决方案：**

.. code-block:: bash

    # Verify HSI is installed
    ls /opt/Xilinx/SDK/2019.1/bin/hsi
    
    # If file exists but command not found, add to PATH
    export PATH=/opt/Xilinx/SDK/2019.1/bin:$PATH
    
    # Add to .bashrc
    echo 'export PATH=/opt/Xilinx/SDK/2019.1/bin:$PATH' >> ~/.bashrc

|

FSBL 生成失败
----------------------

**问题：** ``make`` 期间出现错误：“FSBL generation failed”

**可能原因和解决方案：**

1. **缺少 .hdf 文件：**

    .. code-block:: bash

        # Verify hardware handoff exists
        ls prj/v0.94/project/redpitaya.sdk/
        
        # If missing, export from Vivado:
        # File → Export → Export Hardware (include bitstream)

2. **SDK 版本不匹配：**

    .. code-block:: bash

        # Check SDK version
        xsdk -version
        
        # Should show: Xilinx SDK 2019.1

3. **SDK 安装损坏：**

    .. code-block:: bash

        # Reinstall SDK or run repair from installer

|

缺少库（Linux）
---------------------------

**问题：** SDK 无法启动，并显示库错误

**解决方案：**

.. code-block:: bash

    # Install 32-bit library support
    sudo dpkg --add-architecture i386
    sudo apt update
    
    # Install missing libraries
    sudo apt install -y \
        libxft2:i386 \
        libncurses5 \
        libtinfo5 \
        libstdc++6:i386

|

权限被拒绝错误
--------------------------

**问题：** 无法写入 FSBL 或设备树文件

**解决方案：**

.. code-block:: bash

    # Fix directory permissions
    sudo chown -R $USER:$USER RedPitaya-FPGA
    chmod -R u+w RedPitaya-FPGA
    
    # Or run make with sudo (not recommended)
    sudo make PRJ=v0.94 MODEL=Z10

|

设备树编译失败
-------------------------------

**问题：** ``dtc: command not found``

**解决方案：**

.. code-block:: bash

    # Install device tree compiler
    sudo apt install device-tree-compiler
    
    # Verify installation
    dtc --version

|

其他资源
=====================

**官方文档：**

- `Xilinx SDK User Guide (UG1027) <https://docs.xilinx.com/v/u/en-US/ug1027-sdk-user-guide>`_
- `Xilinx HSI User Guide (UG1138) <https://docs.xilinx.com/v/u/en-US/ug1138-vivado-sw-hw-interface>`_
- `Device Tree Xilinx Repository <https://github.com/Xilinx/device-tree-xlnx>`_

**Red Pitaya 资源：**

- :ref:`Vivado 安装指南 <FPGA_install_vivado>`
- :ref:`FPGA 项目创建 <fpga_create_project>`
- :ref:`设备树配置 <device_tree>` （即将推出）
- :rp-forum:`Red Pitaya Forum <>`

**社区支持：**

- `AMD Xilinx Forums <https://adaptivesupport.amd.com/>`_
- :rp-forum:`Red Pitaya Forum <>`
- :rp-github:`GitHub Issues <RedPitaya-FPGA/issues>`

|

后续步骤
===========

SDK 安装完成后，可以继续：

1. :ref:`创建第一个 FPGA 项目 <fpga_create_project>`
2. :ref:`构建 FPGA 项目 <fpga_create_project>`
3. :ref:`生成设备树 <device_tree>`
4. :ref:`通过 JTAG 对 FPGA 编程 <fpga_jtag_programming>`

完整的 FPGA 开发工作流请参见 :ref:`FPGA 开发指南 <build-fpga>`。

.. _SW_build_ecosystem:

##########################
构建 Red Pitaya 生态系统
##########################

本指南介绍如何构建 Red Pitaya 生态系统，其中包括 FPGA 比特流、Linux 内核、启动文件、
API 库、SCPI 服务器和 Web 应用。

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

简介
=============

什么是生态系统
----------------------

Red Pitaya 生态系统包含 Red Pitaya 正常运行所需的全部软件和硬件组件：

* **FPGA 比特流** - 不同应用的硬件逻辑设计
* **启动组件** - FSBL、U-Boot 和启动脚本
* **Linux 内核** - 操作系统内核和设备树文件
* **用户空间组件** - API 库、SCPI 服务器和 Web 应用
* **开发工具** - 工具和示例

生态系统打包为 ``ecosystem_*.zip`` 文件，可部署到 SD 卡的 FAT32 分区。

|

生态系统目录结构
-------------------------------

Red Pitaya 源代码按多个目录组织：

.. list-table::
    :widths: 19 145
    :header-rows: 1

    * - 目录
      - 内容
    * - ``rp-api``
      - ``librp.so``、``librp2.so``、``librp-gpio.so``、``librp-i2c.so``、``librp-spi.so`` 等 API 源代码
    * - ``apps-free``
      - 旧版（2.00 之前）环境的 Web 应用（还包括控制器模块和 GUI 客户端）
    * - ``apps-tools``
      - Web 界面主页和系统管理应用
    * - ``Bazaar``
      - 带依赖项的 Nginx 服务器、Bazaar 模块和应用控制器模块加载器
    * - ``fpga``
      - FPGA 设计（RTL、测试平台、仿真和综合脚本），基于 SystemVerilog [#f1]_
    * - ``OS``
      - GNU/Linux 操作系统组件
    * - ``patches``
      - 应用于官方 Linux OS 的补丁
    * - ``scpi-server``
      - SCPI 服务器
    * - ``Test``
      - 命令行工具（``acquire``、``generate`` 等）和测试
    * - ``Examples``
      - 使用不同编程语言操作外设的示例
    * - ``build_scripts``
      - 用于构建生态系统和准备存储卡镜像的脚本

.. [#f1] FPGA 设计位于 :rp-github:`RedPitaya-FPGA` 仓库中，构建过程中会将其克隆到 ``fpga/`` 子目录。

|

.. _SW_ecosys_req:

前置条件
==============

主机系统要求
-------------------------

Red Pitaya 生态系统必须在 Linux 主机系统上构建。

.. list-table::
    :widths: 33 33
    :header-rows: 1

    * - Red Pitaya 生态系统版本
      - 主机平台 OS
    * - Ecosystem 3.0 及更高版本
      - Ubuntu 24.04 LTS 或更高版本
    * - Ecosystem 2.0 及更高版本
      - Ubuntu 22.04 LTS 或更高版本
    * - Ecosystem 1.04
      - Ubuntu 18.04 LTS 或更高版本


其他 OS 构建要求请参阅 :ref:`OS 构建要求 <SW_os_req>` 章节。

|

所需软件包
----------------------------

在 Ubuntu 主机系统上安装以下软件包。


基础开发工具
^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: shell-session

    # Generic dependencies
    sudo apt-get install make curl xz-utils git cmake

    # U-Boot build dependencies
    sudo apt-get install libssl-dev device-tree-compiler u-boot-tools

    # Secure chroot
    sudo apt-get install schroot

    # QEMU for ARM emulation
    sudo apt-get install qemu qemu-user qemu-user-static

    # 32-bit libraries
    sudo apt-get install lib32z1 lib32ncurses5 libbz2-1.0:i386 lib32stdc++6


Python 3 与构建工具
^^^^^^^^^^^^^^^^^^^^^^^^^^

构建部分生态系统组件需要 Python 3.10 或更高版本。

.. code-block:: shell-session

    sudo apt-get install python3 python3-pip
    sudo pip3 install --upgrade pip
    sudo pip3 install meson
    sudo apt-get install ninja-build

.. note::

    Meson 构建系统是可选的，主要用于 x86 PC 上的开发。

|

Xilinx Vivado 与 SDK
----------------------

构建过程需要 AMD Xilinx Vivado 和 SDK（裸机工具链）。

所需版本
^^^^^^^^^^^^^^^^^^

.. list-table::
    :widths: 33 33
    :header-rows: 1

    * - Red Pitaya 生态系统版本
      - FPGA 开发工具
    * - Ecosystem 3.0 及更高版本
      - Vivado 2025.1 和 Vitis 2025.1
    * - Ecosystem 2.0 及更高版本
      - Vivado 2020.1 和 SDK 2019.1
    * - Ecosystem 1.04
      - Vivado 2020.1 和 SDK 2019.1

.. warning::

    Vivado 和 SDK 的版本至关重要。不同版本之间不兼容。
    请确保安装上面列出的确切版本。

.. note::

    未来的 Red Pitaya OS 版本将迁移到 Vitis。目前仍需要 Vivado 和 SDK。


安装要求
^^^^^^^^^^^^^^^^^^^^^^^^^^

1. 按照以下安装说明操作： :ref:`Creating a Vivado SDK/Vitis project <fpga_create_sdk_project>`
   以及 :ref:`Vivado 安装 <FPGA_install_vivado>` 章节

2. **同时安装 Vivado 和 SDK** - 安装 Vivado 时，确保同时选择 SDK（裸机工具链）

3. **使用默认安装路径** - 两个工具最好安装在默认位置 (``/opt/Xilinx/``)

4. **创建 gmake 符号链接** - Vivado 需要 ``gmake``，而 Ubuntu 中不存在该命令：

   .. code-block:: shell-session

       sudo ln -s /usr/bin/make /usr/bin/gmake


虚拟机安装（可选）
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

如果 Vivado 在虚拟机中运行且安装在主机共享文件夹中：

1. **使用 VirtualBox** - VMware 的 Ubuntu 客户机 VMware-tools 存在缺陷，无法正确挂载共享文件系统

2. **安装未加密的 Ubuntu** - 加密安装会阻止部分 Red Pitaya 构建流程

3. **配置共享文件夹**:

   * 打开 Ubuntu 虚拟机的 VirtualBox 设置
   * 转到“共享文件夹”
   * 添加主机上的 Xilinx 安装目录（通常为 ``/opt/``）
   * 启用“自动挂载”选项

4. **安装 VirtualBox 增强功能**:

   .. code-block:: shell-session

       sudo apt-get install virtualbox-guest-dkms

5. **访问共享文件夹** - 重启后，可在 ``/media/sf_Xilinx`` （需要 root 权限）

|

Red Pitaya 源代码
------------------------

克隆仓库
^^^^^^^^^^^^^^^^^^^^^

进入首选开发目录并克隆仓库：

.. code-block:: shell-session

    git clone https://github.com/RedPitaya/RedPitaya.git
    cd RedPitaya

具体分支或标签的选择取决于你的需求。


配置环境
^^^^^^^^^^^^^^^^^^^^^^

将 ``LC_ALL`` 环境变量设置为 ``C`` （区域设置相关构建工具需要）：

.. code-block:: shell-session

    echo $LC_ALL

如果命令返回空行，请设置该变量：

.. code-block:: shell-session

    export LC_ALL=C

要使设置永久生效，请将该行添加到 ``~/.bashrc`` 文件。

.. warning::

    不支持在加密的主目录上构建生态系统，因为 ``schroot`` 无法访问加密目录。
    请创建单独的非加密目录（例如 ``/home/ecosystem_build``）用于构建。

|

了解构建流程
=================================

构建环境架构
--------------------------------

Red Pitaya 构建过程使用多个环境：

* **本地计算机（x86）** - 使用交叉编译器在此编译 FPGA 比特流和 Linux 内核
* **Chroot 环境（ARM）** - 在模拟 ARM 环境中编译用户空间应用（API、SCPI 服务器、Web 应用）

构建脚本会根据需要在这些环境之间自动切换。

|

重要说明
----------------

继续之前，请了解以下要点：

1. **不是标准 Linux 构建** - 构建通过 ``schroot`` 使用 Red Pitaya 虚拟 ARM 环境，而不是常规交叉编译设置

2. **需要 Ubuntu 主机** - 构建必须在 Ubuntu（原生环境或虚拟机）上运行。不支持 Windows、macOS 和 WSL

3. **自动切换环境** - 构建脚本会自动处理 x86 和 ARM 环境之间的切换。
   :rp-github:`自动切换示例 <RedPitaya/blob/master/build_scripts/build_OS.sh#L184>`：

   .. code-block:: shell-session

       make -f Makefile.x86

       schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
       make -f Makefile CROSS_COMPILE="" REVISION=$GIT_COMMIT_SHORT
       EOL_CHROOT

       make -f Makefile.x86 zip

4. **磁盘空间要求** - 确保至少有 10 GB 可用磁盘空间用于源代码和编译

|

.. _SW_ecosys_build_proc:

构建生态系统
========================

完整构建过程会创建可部署到 Red Pitaya 硬件的完整生态系统包。


准备构建环境
-------------------------------

步骤 1：加载构建设置
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``settings.sh`` 脚本会配置 Vivado 和 SDK 的环境变量。如果使用了非默认安装路径，请编辑此文件：

.. code-block:: shell-session

    source settings.sh


步骤 2：创建下载缓存（可选）
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

创建缓存目录以存储下载的源代码 tar 包（可加快后续构建）：

.. code-block:: shell-session

    mkdir -p dl
    export DL=$PWD/dl


步骤 3：下载 ARM Ubuntu 环境
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

从以下位置下载预构建的 ARM Ubuntu 根环境： :rp-download:`Red Pitaya download server <>`.

.. tabs::

    .. group-tab:: Ecosystem 2.00 及更高版本

        .. code-block:: shell-session

            wget https://downloads.redpitaya.com/downloads/LinuxOS/redpitaya_OS_17-31-47_20-Mar-2025.tar.gz
            sudo chown root:root redpitaya_OS_17-31-47_20-Mar-2025.tar.gz
            sudo chmod 664 redpitaya_OS_17-31-47_20-Mar-2025.tar.gz

    .. group-tab:: Ecosystem 1.04

        .. code-block:: shell-session

            wget https://downloads.redpitaya.com/downloads/LinuxOS/redpitaya_ubuntu_04-oct-2021.tar.gz
            sudo chown root:root redpitaya_ubuntu_04-oct-2021.tar.gz
            sudo chmod 664 redpitaya_ubuntu_04-oct-2021.tar.gz

.. note::

    或者，也可以按照 :ref:`OS 镜像构建说明 <SW_build_os>` 创建自己的根环境。


步骤 4：配置 schroot
^^^^^^^^^^^^^^^^^^^^^^^^^^^

创建 schroot 配置文件： ``/etc/schroot/chroot.d/red-pitaya-ubuntu.conf``

将占位符替换为：

* 下载 tar 包的绝对路径
* 需要构建访问权限的用户列表（逗号分隔）

.. tabs::

    .. group-tab:: Ecosystem 2.00 及更高版本

        .. code-block:: none

            [red-pitaya-ubuntu]
            description=Red Pitaya Debian/Ubuntu OS image
            type=file
            file=/absolute/path/to/redpitaya_OS_17-31-47_20-Mar-2025.tar.gz
            users=your-username
            root-users=your-username
            root-groups=root
            profile=desktop
            personality=linux
            preserve-environment=true

    .. group-tab:: Ecosystem 1.04

        .. code-block:: none

            [red-pitaya-ubuntu]
            description=Red Pitaya Debian/Ubuntu OS image
            type=file
            file=/absolute/path/to/redpitaya_ubuntu_04-oct-2021.tar.gz
            users=your-username
            root-users=your-username
            root-groups=root
            profile=desktop
            personality=linux
            preserve-environment=true

|

完整构建流程
---------------------

.. tabs::

    .. group-tab:: Ecosystem 2.00 及更高版本

        **选项 1：自动构建脚本**

        为所有板卡型号构建：

        .. code-block:: shell-session

            cd build_scripts
            sudo ./build_OS.sh

        **选项 2：手动构建**

        逐步构建：

        .. code-block:: shell-session

            make -f Makefile.x86
            schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
            make
            EOL_CHROOT
            make -f Makefile.x86 zip

        **交互式 ARM shell**

        要获取交互式 ARM shell 进行调试：

        .. code-block:: shell-session

            schroot -c red-pitaya-ubuntu

        .. note::

            与 Ecosystem 1.04 不同，2.0 及更高版本会同时为所有板卡型号构建。
            板卡特定差异只会影响 FPGA 比特流编译。

    .. group-tab:: Ecosystem 1.04

        **选项 1：自动构建脚本**

        使用针对特定板卡型号预先制作的构建脚本：

        .. tabs::

            .. group-tab:: STEMlab 125-14 (Default)

                .. code-block:: shell-session

                    cd build_scripts
                    sudo ./build_Z10.sh

            .. group-tab:: STEMlab 125-14 Z7020 LN

                .. code-block:: shell-session

                    cd build_scripts
                    sudo ./build_Z20_125.sh

            .. group-tab:: STEMlab 125-14 4-Input

                .. code-block:: shell-session

                    cd build_scripts
                    sudo ./build_Z20_4CH.sh

            .. group-tab:: SDRlab 122-16

                .. code-block:: shell-session

                    cd build_scripts
                    sudo ./build_Z20.sh

            .. group-tab:: SIGNALlab 250-12

                .. code-block:: shell-session

                    cd build_scripts
                    sudo ./build_Z250_12.sh

        **选项 2：手动构建**

        通过选择 MODEL 参数逐步构建：

        .. tabs::

            .. group-tab:: STEMlab 125-14 (Default)

                STEMlab 125-14 使用 Z7010，无需 MODEL 参数：

                .. code-block:: shell-session

                    make -f Makefile.x86
                    schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
                    make
                    EOL_CHROOT
                    make -f Makefile.x86 zip

            .. group-tab:: STEMlab 125-14 4-Input

                STEMlab 125-14 4-Input 使用 Z7020：

                .. code-block:: shell-session

                    make -f Makefile.x86 MODEL=Z20_125_4CH
                    schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
                    make MODEL=Z20_125_4CH
                    EOL_CHROOT
                    make -f Makefile.x86 zip MODEL=Z20_125_4CH

            .. group-tab:: SDRlab 122-16

                SDRlab 122-16 使用 Z7020：

                .. code-block:: shell-session

                    make -f Makefile.x86 MODEL=Z20
                    schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
                    make MODEL=Z20
                    EOL_CHROOT
                    make -f Makefile.x86 zip MODEL=Z20

            .. group-tab:: SIGNALlab 250-12

                SIGNALlab 250-12 使用 Z7020：

                .. code-block:: shell-session

                    make -f Makefile.x86 MODEL=Z20_250_12
                    schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
                    make MODEL=Z20_250_12
                    EOL_CHROOT
                    make -f Makefile.x86 zip MODEL=Z20_250_12

        **交互式 ARM shell**

        要获取用于调试的交互式 ARM shell：

        .. code-block:: shell-session

            schroot -c red-pitaya-ubuntu

|

部分重建
================

无需重建整个生态系统即可单独重建组件。


可用组件
--------------------

.. tabs::

    .. group-tab:: Ecosystem 1.04

        以下组件可以单独构建：

        * FPGA and device tree
        * U-Boot
        * Linux kernel
        * API
        * SCPI 服务器
        * Free applications

    .. group-tab:: Ecosystem 2.00 and higher

        以下组件可以单独构建：

        * FPGA 和 Overlay
        * U-Boot
        * Linux 内核
        * API
        * SCPI 服务器
        * 控制台工具和 Web 应用程序

|

设置构建环境
------------------------

.. tabs::

    .. group-tab:: Ecosystem 1.04

        配置 Vivado 和 SDK 以进行交叉编译：

        .. code-block:: shell-session

            source settings.sh

        在某些系统（包括 Ubuntu 18.04）上，Vivado 的库设置可能与系统库冲突。
        如有需要，请禁用 Vivado 库覆盖：

        .. code-block:: shell-session

            export LD_LIBRARY_PATH=""

    .. group-tab:: Ecosystem 2.00 and higher

        配置 Vivado、SDK 和交叉编译工具：

        .. code-block:: shell-session

            source settings.sh
            export CROSS_COMPILE=arm-linux-gnueabihf-
            export ARCH=arm
            export PATH=$PATH:/opt/Xilinx/Xilinx/Vivado/2020.1/bin
            export PATH=$PATH:/opt/Xilinx/SDK/2019.1/bin
            export PATH=$PATH:/opt/Xilinx/SDK/2019.1/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin/

|

打包生态系统
----------------------

.. tabs::

    .. group-tab:: Ecosystem 2.00 and higher

        构建组件后，将其打包为 zip 压缩包：

        .. code-block:: shell-session

            make -f Makefile.x86 zip

    .. group-tab:: Ecosystem 1.04

        After building components, package them into a zip archive:

        .. code-block:: shell-session

            make -f Makefile.x86 zip

|

构建 FPGA 比特流和设备树
----------------------------------------

.. tabs::

    .. group-tab:: Ecosystem 2.00 and higher

        每个 FPGA 版本使用设备树覆盖层。针对特定板卡型号进行构建：

        .. code-block:: shell-session

            make -f Makefile.x86 fpga MODEL=Z10
            make -f Makefile.x86 fpga MODEL=Z20
            make -f Makefile.x86 fpga MODEL=Z20_125
            make -f Makefile.x86 fpga MODEL=Z20_125_4CH
            make -f Makefile.x86 fpga MODEL=Z20_250_12

        详细说明请参阅 :ref:`构建 FPGA <FPGA_project_flags>`。

        .. note::

            仅构建所需型号，以加快构建过程。

    .. group-tab:: Ecosystem 1.04

        构建 FPGA 比特流和设备树源文件：

        .. code-block:: shell-session

            make -f Makefile.x86 fpga

        详细说明请参阅 :ref:`构建 FPGA <FPGA_project_flags>` 和 :ref:`设备树详情 <devicetree>`。


        **构建设备树编译器（可选）**

        如果需要带覆盖层补丁的设备树编译器：

        .. code-block:: shell-session

            sudo apt-get install flex bison
            git clone git@github.com:pantoniou/dtc.git
            cd dtc
            git checkout overlays
            make
            sudo make install PREFIX=/usr

        .. note::

            ``tools/dtc`` 目录中提供了预编译二进制文件。

|

构建 U-Boot
--------------

.. tabs::

    .. group-tab:: Ecosystem 2.00 and higher

        构建 U-Boot 二进制文件和启动脚本：

        .. code-block:: shell-session

            make -f Makefile.x86 boot

        此操作会从 GitHub 下载 Xilinx U-Boot 源代码，应用 Red Pitaya 补丁（来自 ``patches/`` 目录），然后进行构建。

        .. note::

            会创建两个版本的 ``boot.bin``：

            * 一个用于具有 512 MB RAM 的板卡
            * 一个用于具有 1 GB RAM 的板卡

            还会创建两个版本的 Linux 内核启动脚本。

        .. note::

            U-Boot 的设备树使用 ``dts_uboot/`` 文件夹中的文件构建，这些文件定义了板卡启动所需的最小外设要求。

    .. group-tab:: Ecosystem 1.04

        构建 U-Boot binary and boot scripts:

        .. code-block:: shell-session

            make -f Makefile.x86 u-boot

        此操作会从 GitHub 下载 Xilinx U-Boot 源代码，应用 Red Pitaya 补丁（来自 ``patches/`` 目录），然后进行构建。

|

构建 Linux 内核和设备树二进制文件
--------------------------------------------

.. tabs::

    .. group-tab:: Ecosystem 2.00 and higher

        构建 Linux 内核和设备树：

        .. code-block:: shell-session

            make -f Makefile.x86 linux
            make -f Makefile.x86 devicetree

        此操作会从 GitHub 下载 Xilinx Linux 内核源代码，应用 Red Pitaya 补丁（来自 ``patches/`` 目录），然后进行构建。

        .. note::

            构建设备树前必须先构建 FPGA 项目，因为 ``dtb`` 和 ``dts`` 文件基于 FPGA 裸机项目。

    .. group-tab:: Ecosystem 1.04

        构建 Linux 内核和设备树二进制文件：

        .. code-block:: shell-session

            make -f Makefile.x86 linux
            make -f Makefile.x86 linux-install
            make -f Makefile.x86 devicetree
            make -f Makefile.x86 devicetree-install

        此操作会从 GitHub 下载 Xilinx Linux 内核源代码，应用 Red Pitaya 补丁（来自 ``patches/`` 目录），然后进行构建。

|

构建启动文件
----------------

.. tabs::

    .. group-tab:: Ecosystem 2.00 and higher

        .. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    .. group-tab:: Ecosystem 1.04

        创建包含 FSBL、FPGA 比特流和 U-Boot 的启动文件：

        .. code-block:: shell-session

            make -f Makefile.x86 boot


构建用户空间应用
-------------------------------

.. tabs::

    .. group-tab:: Ecosystem 2.00 and higher

        在 ARM chroot 环境中构建各个组件：

        .. code-block:: shell-session

            schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
            make api
            make nginx
            make scpi
            make sdr
            make bode
            make monitor
            make generator
            make acquire
            make calib
            make daisy_tool
            make spectrum
            make led_control
            make ecosystem
            make updater
            make main_menu
            make scpi_manager
            make streaming_manager
            make calib_app
            make network_manager
            make jupyter_manager
            EOL_CHROOT

        .. note::

            某些组件相互依赖。使用 ``make all`` 可一次性构建全部组件。

    .. group-tab:: Ecosystem 1.04

        .. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


|


组件专属信息
================================

以下章节提供各组件的详细信息。


API 库
------------

构建 Red Pitaya API 库：

.. code-block:: shell-session

    schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
    make api
    EOL_CHROOT

**输出文件：**

* 库：``api/lib/librp.so``
* 头文件：``api/includes/redpitaya/rp.h``

**安装到 Red Pitaya：**

.. code-block:: shell-session

    scp build/api/lib/*.so root@192.168.0.100:/opt/redpitaya/lib/

将 ``192.168.0.100`` 替换为 Red Pitaya 的 IP 地址（或使用 ``.local`` 地址）。

|

U-Boot EEPROM 配置
----------------------------

U-Boot 变量存储在 EEPROM 中，但启动时不会自动读取。如果未读取 EEPROM，则使用默认常量值。

要从 EEPROM 更新并重新计算变量值：

.. code-block:: shell-session

    i2c dev 0
    # Offset 0x1800 + 0x4 (crc32)
    eeprom read  0 0x50 0 0x1804 0x400
    env import -b 0 0x400 hw_rev serial ethaddr

|

SCPI 服务器
------------

构建 SCPI 服务器：

.. code-block:: shell-session

    schroot -c red-pitaya-ubuntu <<- EOL_CHROOT
    make scpi
    EOL_CHROOT

**输出文件：** ``scpi-server/scpi-server``

**安装到 Red Pitaya：**

.. code-block:: shell-session

    scp scpi-server/scpi-server root@192.168.0.100:/opt/redpitaya/bin/

将 ``192.168.0.100`` 替换为 Red Pitaya 的 IP 地址（或使用 ``.local`` 地址）。

.. note::

    Red Pitaya 使用 :rp-github:`定制的 SCPI 解析器 <scpi-parser/tree/redpitaya>`，其中包含针对 Red Pitaya 硬件优化的函数。

更多信息请参见 :rp-github:`SCPI 服务器 README <RedPitaya/blob/master/scpi-server/README.md>`。

|

旧版 Web 应用
------------------------

要从 ``apps-free`` 目录构建应用，请遵循 :rp-github:`仓库中的说明 <RedPitaya/blob/master/apps-free/README.md>`。

.. warning::

    ``apps-free`` 中的应用针对 Ecosystem 1.04 及更早版本开发。要在 Ecosystem 2.00 及更高版本中运行，需要进行修改。

|

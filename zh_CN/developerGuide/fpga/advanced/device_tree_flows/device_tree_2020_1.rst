.. _device_tree_2020_1:

############################################################
设备树生成（Vivado 2020.1 + SDK 2019.1）
############################################################

.. warning::

    此流程用于与较旧的 Red Pitaya 构建版本保持向后兼容。
    对于新开发，请使用 :ref:`device_tree_2025_1`。

本页面介绍基于 HSI 的旧版设备树生成流程，该流程围绕以下组件构建：

- Vivado 2020.1
- Xilinx SDK 2019.1
- Device Tree Xilinx 源码的本地克隆

旧版默认设备树源版本：

- ``DTS_VER=2017.2``

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

前置条件
================

旧版流程要求：

- Vivado 2020.1
- Xilinx SDK 2019.1 (``xsct``)
- Device Tree Xilinx repository checkout

.. important::

    此流程要求使用旧版 HSI 脚本和目录约定。

|

自动下载（完整生态系统构建）
==========================================

使用主仓库的 ``Makefile.x86`` 构建完整 Red Pitaya 生态系统时，Device Tree Xilinx 仓库
会自动下载：

.. code-block:: bash

    # In the main RedPitaya repository
    make -f Makefile.x86

Makefile 使用以下地址下载归档：

.. code-block:: makefile

    DTREE_URL ?= https://github.com/Xilinx/device-tree-xlnx/archive/$(DTREE_TAG).tar.gz

|

手动设置（独立 FPGA 构建）
=====================================

使用独立的旧版 FPGA 脚本时，请手动提供 Device Tree Xilinx：

.. code-block:: bash

    # Navigate to RedPitaya-FPGA directory
    cd RedPitaya-FPGA

    # Create tmp directory if it doesn't exist
    mkdir -p tmp
    cd tmp

    # Clone Device Tree Xilinx repository
    git clone https://github.com/Xilinx/device-tree-xlnx device-tree-xlnx-xilinx-v2017.2
    cd device-tree-xlnx-xilinx-v2017.2
    git checkout xilinx-v2017.2

.. note::

    常见的旧版为 ``2017.2``，但可以通过 ``DTS_VER`` 更改。
    检出目录名称必须遵循 ``device-tree-xlnx-xilinx-v{version}``。

|

来自 FPGA 构建流程
=========================

在旧版流程中，使用 HSI 根据 Vivado 硬件定义生成设备树文件。

.. code-block:: bash

    cd RedPitaya-FPGA
    make PRJ=stream_app MODEL=Z10

此流程将：

1. 使用 Vivado 2020.1 生成 Vivado 硬件设计
2. 导出硬件定义 ``prj/{project}/sdk/red_pitaya.sysdef``
3. 运行 ``xsct red_pitaya_hsi_dts.tcl``
4. 将生成的 DTS 文件放入 ``prj/{project}/sdk/dts/``

用于生成 DTS 的旧版 Makefile 命令：

.. code-block:: bash

    xsct red_pitaya_hsi_dts.tcl $(PRJ) DTS_VER=$(DTS_VER) MODEL=$(MODEL)

旧版版本覆盖示例：

.. code-block:: bash

    make PRJ=stream_app MODEL=Z10 DTS_VER=2018.1

完整构建详情请参阅某个旧版 RedPitaya-FPGA 仓库版本中的 :rp-github:`Makefile <RedPitaya-FPGA/blob/2.07-48/Makefile>`。
该链接指向 OS 2.07-48 的 makefile。对于其他版本，请在 GitHub 仓库中选择其他发行版或标签。

|

理解 DTS 脚本
=============================

旧版 ``red_pitaya_hsi_dts.tcl`` 脚本流程基于 HSI，并执行以下操作：

1. 从 ``sdk/red_pitaya.sysdef`` 打开硬件设计
2. 将仓库路径设置为 ``tmp/device-tree-xlnx-xilinx-v{DTS_VER}``
3. 为 ``ps7_cortexa9_0`` 创建设备树软件设计
4. 设置内核版本和 overlay 配置
5. 在 ``sdk/dts/`` 中生成 DTS 输出

Typical command sequence:

.. code-block:: tcl

    hsi open_hw_design $path_sdk/red_pitaya.sysdef
    hsi set_repo_path ../../../tmp/device-tree-xlnx-xilinx-v$ver/
    hsi create_sw_design device-tree -os device_tree -proc ps7_cortexa9_0
    hsi set_property CONFIG.kernel_version $ver [hsi get_os]
    hsi set_property CONFIG.dt_overlay true [hsi get_os]
    hsi generate_target -dir $path_sdk/dts

这是为旧版流水线保留的兼容方法。

|

相关链接
===============

- :ref:`device_tree` - 父级设备树页面（编译、加载、故障排除）
- :ref:`device_tree_2025_1` - 用于新开发的当前流程
- :ref:`fpga_install_sdk` - SDK 安装参考

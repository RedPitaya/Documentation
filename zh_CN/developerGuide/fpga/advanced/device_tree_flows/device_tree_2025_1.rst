.. _device_tree_2025_1:

############################################################
设备树生成（Vivado 2025.1 + Vitis 2025.1）
############################################################

本页介绍当前基于以下版本的 Red Pitaya 设备树生成流程：

- Vivado 2025.1
- Vitis 2025.1 (``xsct``)

如需了解旧版兼容流程（Vivado 2020.1 + SDK 2019.1），请参阅 :ref:`device_tree_legacy_2020_1`。

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

前置条件
================

安装匹配的 Xilinx 工具，并确保 ``xsct`` 已位于 PATH 中。

所需版本：

- Vivado 2025.1
- Vitis 2025.1

.. important::

    为获得稳定结果，请使用匹配的 Vivado 和 Vitis 版本。

|

自动下载（完整生态系统构建）
==========================================

通过主仓库 ``Makefile.x86`` 构建完整 Red Pitaya 生态系统时，设备树源代码仓库由生态系统构建流程处理。

|

手动设置（独立 FPGA 构建）
=====================================

对于当前的独立 FPGA 构建，无需手动在本地检出 ``device-tree-xlnx``。
``red_pitaya_hsi_dts.tcl`` 脚本会使用带有 ``-git-branch xlnx_rel_v{DTS_VER}`` 参数的 ``createdts``。

|

从 FPGA 构建流程生成
=========================

标准构建流程会根据导出的 XSA 硬件平台自动生成设备树。

.. code-block:: bash

    cd RedPitaya-FPGA
    make PRJ=stream_app MODEL=Z10

此流程将：

1. 在 Vivado 2025.1 中构建硬件设计
2. 导出 ``prj/{project}/sdk/red_pitaya.xsa``
3. 运行 ``xsct red_pitaya_hsi_dts.tcl``
4. 将生成的 DTS 文件放入 ``prj/{project}/sdk/dts/``

用于生成 DTS 的 Makefile 命令：

.. code-block:: bash

    xsct red_pitaya_hsi_dts.tcl $(PRJ) DTS_VER=$(DTS_VER) MODEL=$(MODEL)

默认设备树源代码版本：

- ``DTS_VER=2025.1``

覆盖版本的示例：

.. code-block:: bash

    make PRJ=stream_app MODEL=Z10 DTS_VER=2025.1

完整构建详情请参阅 RedPitaya-FPGA 仓库中的 `Makefile <https://github.com/RedPitaya/RedPitaya-FPGA/blob/master/Makefile>`_。

|

理解 DTS 脚本
=============================

RedPitaya-FPGA 中的 ``red_pitaya_hsi_dts.tcl`` 脚本使用 ``createdts`` 流程，并执行以下操作：

1. 从 ``sdk/red_pitaya.xsa`` 读取硬件平台
2. 使用 ``DTS_VER`` 选择分支后缀 ``xlnx_rel_v{DTS_VER}``
3. 生成启用了 overlay 支持的 DTS 输出
4. 将生成的文件复制到 ``sdk/dts/``

脚本使用的核心命令：

.. code-block:: tcl

    createdts -hw $xsa_file -platform-name redpitaya_platform -git-branch xlnx_rel_v$ver -overlay -out $output_dir

完整实现细节请参阅 `red_pitaya_hsi_dts.tcl <https://github.com/RedPitaya/RedPitaya-FPGA/blob/master/red_pitaya_hsi_dts.tcl>`_。

|

相关链接
===============

- :ref:`device_tree` - 设备树上级页面（编译、加载、故障排除）
- :ref:`overlay_util` - overlay 脚本快速参考
- :ref:`fpga_advanced_loading` - FPGA 和设备树重新编程综合指南

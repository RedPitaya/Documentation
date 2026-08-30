.. _FPGA_install_vivado:

#################################
安装 Vivado 和 Vitis
#################################

本安装教程面向所有希望使用 Red Pitaya 板卡 FPGA 的用户。

.. contents:: 目录
    :local:
    :depth: 2
    :backlinks: top

|


要求
=============

你的计算机或虚拟机需要具备以下环境之一：

* Ubuntu 18.04 或更高版本
* Linux Mint OS
* Windows，并具备：
    
    * 压缩包解压工具（例如 *Winrar* 或 *7zip*）
    * Windows Subsystem for Linux（推荐）
    * *make* 工具（推荐）

Vivado 同时支持 Linux 和 Windows 操作系统。本教程将介绍这两种操作系统上的安装过程及其差异。Mac 用户应使用运行受支持操作系统之一的虚拟机。

Windows 用户可以受益于使用适用于 Linux 的 Windows 子系统（WSL），因为它便于与 Red Pitaya 交互并获取串行控制台信息，但编程 FPGA 并不要求使用 WSL。此外，具备 **make** 工具可以简化 FPGA 项目的构建过程。安装说明请参阅：

* :ref:`WSL 设置指南 <wsl_setup>`
* :ref:`C++ 编译器和 Make 工具设置 <cpp_make_install>`

|

Vivado 和 Vitis 版本
==========================

Vivado 和 Vitis 的版本取决于你使用的 Red Pitaya OS 版本。

.. note::

    必须针对你的 Red Pitaya OS 版本使用正确版本的 Vivado 和 Vitis。在 FPGA 开发过程中使用错误版本可能导致意外问题和错误。

    **为什么不能使用任意或最新版本的 Vivado？**

    原因其实很简单：自动项目构建脚本是针对特定 Vivado/Vitis 版本编写的，无法在不同版本上工作。
    虽然可以使用不同版本的 Vivado/Vitis，但你必须手动创建新项目并添加所有文件，这不建议初学者采用。


.. tabs::

    .. group-tab:: OS 3.00 或更高版本

        **Vivado 2025.1 + Vitis 2025.1**

    .. group-tab:: OS 1.04 - 2.00

        **Vivado 2020.1 + SDK 2019.1**

|

按版本划分的 Vivado 和 Vitis 安装说明
======================================================

.. toctree::
    :maxdepth: 1

    vivado_install/vivado_2025_1.rst
    vivado_install/vivado_2020_1.rst

|

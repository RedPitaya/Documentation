
.. _fpga_programming_environment:

###########################################
FPGA 开发入门
###########################################

本节引导你设置 FPGA 开发环境并创建第一个 Red Pitaya FPGA 项目。当前 Red Pitaya OS 版本使用 Vivado 2025.1 和 Vitis 2025.1；旧版 SDK 2019.1 文档保留用于较旧的 OS 分支。

.. note::

    **各 OS 版本对应的工具链**

    * **OS 3.00 或更高版本：** Vivado 2025.1 + Vitis 2025.1（当前流程）
    * **OS 1.04 - 2.00：** Vivado 2020.1 + SDK 2019.1（旧版流程）

**本节内容：**

* **简介** — 了解 Red Pitaya FPGA 架构、所需工具和开发工作流程
* **安装 Vivado 和 Vitis** — 当前 FPGA 与 ARM 软件开发安装流程
* **安装 SDK（旧版）** — 面向较旧 OS 分支的 SDK 2019.1 设置
* **项目工作流程** — 创建、定制和集成项目（基于模板或从零开始）
* **仿真** — 部署到硬件前使用行为仿真验证设计
* **重新编程 FPGA** — 将比特流加载到 Red Pitaya 并测试设计
* **创建 SDK 项目** — 创建与 FPGA 设计交互的 ARM 软件项目

.. toctree::
    :maxdepth: 1

    intro.rst
    vivado_install.rst
    sdk_install.rst
    projects/top.rst
    simulation.rst
    reprogram_fpga.rst


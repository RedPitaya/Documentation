.. _fpga_top:

###############
FPGA 章节
###############

本节介绍如何构建和修改 Red Pitaya 板卡的 FPGA 设计，适用于希望使用 Vivado 及配套软件工具链创建自己的 FPGA 项目或修改现有项目的用户。

**前提知识：** 具备数字逻辑设计和 Verilog/VHDL 基础，并熟悉 Vivado 开发环境。具备 Linux 命令行使用经验会有所帮助。

|

===========================================
FPGA 文档导航
===========================================

**初学者推荐阅读顺序：**

1. :ref:`入门 <fpga_programming_environment>` — 安装 Vivado 和配套软件工具链，创建第一个项目并学习仿真。
2. :ref:`FPGA 教程 <fpga_tutorials_top>` — 常见 FPGA 任务的分步教程（**即将推出**）
3. :ref:`FPGA 项目 <fpga_projects>` — 了解可用项目和仓库结构
4. :ref:`高级主题 <fpga_advanced>` — 启动加载、JTAG 编程和设备树（按需阅读）
5. :ref:`寄存器 <fpga_registers>` — 对应 OS 版本的寄存器映射（参考资料）

**有经验用户快速入口：**

* 修改现有项目？→ 从 :ref:`入门 <fpga_programming_environment>` 开始
* 手动构建自定义项目？→ 参阅 :ref:`从零创建自定义项目 <fpga_project_from_scratch>`
* 查找项目示例？→ 前往 :ref:`FPGA 项目 <fpga_projects>`
* 配置仿真？→ 查看入门章节中的 :ref:`仿真 <fpga_simulation>`
* 查找分步指南？→ 查看 :ref:`FPGA 教程 <fpga_tutorials_top>` （即将推出）
* 需要寄存器地址？→ 查看对应 OS 版本的 :ref:`寄存器 <fpga_registers>`
* 高级配置？→ 参阅 :ref:`高级主题 <fpga_advanced>`

|

===========================================
典型 FPGA 开发工作流程
===========================================

开始工作流程前，请选择与 Red Pitaya OS 代际相匹配的工具链。

.. list-table::
    :header-rows: 1
    :widths: 20 25 25 30

    * - Red Pitaya OS 代际
      - FPGA 设计工具
      - ARM 软件工具
      - 备注
    * - 3.00 及更高版本
      - AMD Vivado 2025.1
      - AMD Vitis 2025.1
      - 新开发项目的推荐默认路径。
    * - 2.00-1.04（旧版）
      - Xilinx Vivado 2020.1
      - Xilinx SDK 2019.1
      - 仅在维护旧 OS 分支时使用。

.. note::

    请确保 Vivado 和软件工具与目标 OS 版本保持一致。在同一构建流程中混用现代和旧版工具链通常会造成交接与集成问题。

**1. 环境设置**


    * **当前 OS 路径：** 安装 AMD Vivado 2025.1 和 AMD Vitis 2025.1
    * **旧版 OS 路径：** 安装 Xilinx Vivado 2020.1 和 Xilinx SDK 2019.1
    * 克隆 Red Pitaya FPGA 仓库
    * 熟悉仓库结构

**2. 选择起点**

    * **修改现有项目：** 从标准项目（v0.94、streaming、axi4lite）开始定制
    * **创建新项目：** 以现有项目为模板修改功能
    * **添加自定义 IP：** 将自己的 Verilog/VHDL 模块集成到现有设计中

**3. 开发周期**

    1. **设计：** 在 Vivado 中修改 RTL 代码或框图
    #. **仿真：** 运行行为仿真以验证逻辑并及早发现错误（可节省数小时调试时间）
    #. **综合：** 运行综合，检查错误和资源使用情况
    #. **实现：** 对设计进行布局布线
    #. **生成比特流：** 创建 FPGA 二进制文件（.bit）
    #. **测试：** 将比特流加载到 Red Pitaya 并验证功能

.. note::

    **为何仿真至关重要：** 对设计进行仿真可在几分钟内发现逻辑错误、时序问题和功能问题，而部署到硬件后再调试可能需要数小时。务必在综合前进行仿真，学习 FPGA 开发时尤其如此。

**4. 集成**

    * 添加新外设时创建或修改设备树
    * 更新软件驱动程序/API，以连接新的 FPGA 功能
    * 记录寄存器映射和用法

**5. 部署**

    * 将比特流复制到 Red Pitaya
    * 使用 ``overlay`` 系统在运行时加载
    * 配置启动时自动加载（可选）

|

======================
各章节内容
======================

* **入门** — 工具链安装（当前版和旧版）、项目创建、从零自定义设置、仿真和 FPGA 重新编程基础
* **FPGA 教程** — 常见 FPGA 开发任务的分步指南（即将推出）
* **FPGA 项目** — 可用项目（v0.94、streaming、mercury 等）、仓库结构和项目说明
* **寄存器** — 按 OS 版本整理的内存映射寄存器地址和说明
* **高级主题** — 启动配置、JTAG 编程、设备树和信号映射

.. toctree::
    :maxdepth: 1

    getting_started/top.rst
    fpga_tutorials/tutorial_top
    projects/top.rst
    advanced/top.rst
    regset/top.rst

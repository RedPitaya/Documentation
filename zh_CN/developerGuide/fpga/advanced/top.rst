.. _fpga_advanced:

###########################################
FPGA 高级主题
###########################################

本节介绍 Red Pitaya FPGA 开发中超出基本项目创建和修改范围的高级主题。这些主题对于生产部署、硬件集成和高级调试工作流程至关重要。

**本节内容：**

* **FPGA 启动加载** — 配置系统启动时自动加载 FPGA 比特流
* **高级 FPGA 加载** — 用于运行时 FPGA 切换和管理的 Overlay 系统
* **JTAG 编程** — 通过 JTAG 直接编程 FPGA，用于快速制作原型和调试
* **设备树配置** — 为自定义外设和硬件配置创建并修改设备树
* **信号映射** — 硬件引脚分配、XADC 输入、GPIO 连接和物理信号路由

.. toctree::
    :maxdepth: 1

    fpga_boot_loading.rst
    fpga_advanced_loading.rst
    jtag_programming.rst
    device_tree.rst
    signal_mapping.rst

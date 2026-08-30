.. _device_tree:

###################
设备树
###################

Linux 使用设备树描述内存映射硬件的特性和地址空间。设备树由 ``dtc`` 工具从源文件编译而成，并在 Linux 内核启动前由 U-Boot 加载。

Red Pitaya 支持两种设备树生成流程：

- **当前流程（推荐）**：Vivado 2025.1 + Vitis 2025.1（XSCT ``createdts``）
- **旧版兼容流程**：Vivado 2020.1 + SDK 2019.1（HSI + 本地 device-tree-xlnx checkout）

请根据目标流程查看下面的页面，以执行准确的命令。

在 Red Pitaya 上，设备树对于以下事项尤其重要：

- 配置 PS（Processing System，处理系统）外设
- 描述 PL（Programmable Logic，可编程逻辑）中的自定义 AXI 外设
- 管理 GPIO 和模拟输入映射
- 通过 pinctrl 覆盖配置信号路由
- 为 XADC 模拟输入启用 Linux IIO 驱动


.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

流程选择
================

.. toctree::
    :maxdepth: 1

    device_tree_flows/device_tree_2025_1.rst
    device_tree_flows/device_tree_2020_1.rst

|

设备树文件类型
=========================

处理 Red Pitaya FPGA 项目时，生成流程会产生几种设备树文件：

.. list-table:: Make 生成的设备树文件
    :widths: 20 80
    :header-rows: 1

    * - 文件
      - 描述
    * - zynq-7000.dtsi
      - PS 外设和接口
    * - pl.dtsi
      - PL 中的 AXI 外设
    * - system.dts
      - 完整的系统设备树（包含上述文件）

.. note::

    生成脚本会根据导出的硬件设计创建这些文件。
    当前 Red Pitaya FPGA 项目配置为 Vivado 2025.1。旧版项目可能仍以 Vivado 2020.1 为目标。

|

编译设备树
========================

设备树必须先从源文件（.dts/.dtsi）编译为二进制 blob（.dtb）格式，之后才能由 U-Boot 加载。

基本编译
-------------------

使用设备树编译器（dtc）编译设备树源文件：

.. code-block:: bash

    dtc -I dts -O dtb -o devicetree.dtb system.dts

其中：

- ``-I dts``：输入格式为设备树源文件
- ``-O dtb``：输出格式为设备树 blob
- ``-o devicetree.dtb``：输出文件名
- ``system.dts``：输入源文件


在 Red Pitaya 板卡上
---------------------

Red Pitaya 将设备树存储在 ``/opt/redpitaya/dts/`` 中，并为每种板卡型号设置子目录。你可以直接在板卡上重新编译设备树：

.. code-block:: console

    root@rp-f01c3d:~# rw
    root@rp-f01c3d:~# cd /opt/redpitaya/dts/$(monitor -f)/
    root@rp-f01c3d:~# dtc -I dts -O dtb ./dtraw.dts -o devicetree.dtb
    root@rp-f01c3d:~# reboot

.. note::

    更新设备树后务必重启。U-Boot 在启动期间加载新的 DTB 后，修改才会生效。

|

修改设备树
==========================

你可以修改设备树源文件来定制硬件配置。常见的修改包括：

- 添加自定义 AXI 外设
- 更改 GPIO 引脚分配
- 配置外设属性
- 添加设备树覆盖


编辑设备树源文件
-------------------------------

设备树源文件采用层级结构，其中节点表示硬件组件：

.. code-block:: dts

    / {
        amba {
            gpio@e000a000 {
                compatible = "xlnx,zynq-gpio-1.0";
                reg = <0xe000a000 0x1000>;
                interrupts = <0 20 4>;
            };
        };
    };

编辑设备树源文件时，始终保持正确的缩进并确保闭合大括号完整。

|

加载自定义设备树
=================================

编译自定义设备树后，可以使用覆盖脚本将其加载到 Red Pitaya 板卡上。


使用覆盖脚本
-----------------------

:ref:`overlay.sh <overlay_util>` 脚本（OS 2.00+）提供了一种便捷方式，可将自定义 FPGA 比特流及其设备树一起加载：

.. code-block:: bash

    overlay.sh v0.94 /root/custom.bit.bin /root/custom.dtbo

该方式保留标准 Red Pitaya 项目名称作为板卡型号锚点，同时将内置的 FPGA 和设备树文件替换为你指定的路径。

有关覆盖脚本用法的详细信息，请参阅：

- :ref:`overlay_util` - 命令行用法速查
- :ref:`fpga_advanced_loading` - 包含高级示例的完整指南


手动加载
-----------------

对于较旧的 OS 版本或需要手动控制的场景，可以直接使用 fpgautil 工具加载设备树：

.. code-block:: bash

    fpgautil -b path/to/bitstream.bit.bin -o path/to/devicetree.dtbo

.. note::

    设备树必须采用 DTBO（Device Tree Blob Overlay，设备树 blob 覆盖）格式才能在运行时加载。请在 dtc 中使用 ``-O dtb`` 选项生成正确的格式。

|

故障排除
=================

设备树编译错误
--------------------------------

**错误：设备树源文件中存在语法错误**

- **原因**：DTS 语法格式错误、缺少大括号或节点结构不正确
- **解决方案**：仔细检查语法，确保所有节点都有起始和结束大括号，并检查缩进

**错误：包含文件的引用未定义**

- **原因**：包含的 .dtsi 文件路径缺失或不正确
- **解决方案**：验证 include 路径，确保所有必需的 .dtsi 文件位于同一目录中，或已被正确引用


设备树未加载
-------------------------

**症状：设备树修改未生效**

- **原因**：设备树未正确编译，或板卡未重启
- **解决方案**：

    - 确认 devicetree.dtb 文件已更新（检查时间戳）
    - 确认更新设备树后已重启板卡
    - 检查启动期间 U-Boot 控制台输出中是否有加载设备树的消息

**症状：Linux 中看不到 FPGA 外设**

- **原因**：设备树未正确描述 PL 外设
- **解决方案**：

    - 确认 pl.dtsi 是根据正确的 Vivado 设计生成的
    - 检查 system.dts 是否包含 pl.dtsi
    - 确保 AXI 外设地址与硬件设计一致

|

其他资源
=====================

- :ref:`fpga_install_sdk` - SDK 安装和 HSI 工具用法
- :ref:`signal_mapping` - 物理信号连接和 GPIO 映射
- :ref:`overlay_util` - 覆盖脚本速查
- :ref:`fpga_advanced_loading` - FPGA 和设备树重新编程完整指南
- `Device Tree Xilinx Repository <https://github.com/Xilinx/device-tree-xlnx>`_ - Xilinx 官方设备树源文件
- `Linux Device Tree Documentation <https://www.kernel.org/doc/Documentation/devicetree/>`_ - 关于设备树用法的内核文档
- `Device Tree Compiler (DTC) <https://git.kernel.org/pub/scm/utils/dtc/dtc.git>`_ - DTC 官方工具仓库

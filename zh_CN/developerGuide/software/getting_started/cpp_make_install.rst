.. _cpp_make_install:

##########################
C++ 编译器和 Make 工具设置
##########################

本指南介绍如何在 Windows 上使用 Chocolatey 包管理器安装 C++ 编译器（MinGW-w64）和 make 工具。这些工具对于以下任务至关重要：

- 编译 Red Pitaya streaming 库中的 C++ 示例
- 为 Red Pitaya 构建 C/C++ 应用程序
- 运行 Makefile 以自动执行构建过程
- 生成和构建 FPGA 项目

.. note::

    **Linux/macOS 用户：** 这些工具通常已预安装，或可通过系统的软件包管理器（``apt``、``yum``、``brew``）获取。本指南重点介绍 Windows 安装方式。

前置条件
========

- 具有管理员权限的 Windows 10/11
- PowerShell 或 Windows 命令提示符

安装 Chocolatey 包管理器
========================

Chocolatey 是 Windows 的包管理器，可通过命令行简化软件安装。

官方安装指南：|Chocolatey-Install|

快速安装：

1.  以**管理员**身份打开 PowerShell（右键单击 PowerShell →“以管理员身份运行”）

2.  运行安装命令：

    .. code-block:: powershell

        Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

3.  等待安装完成。此时应看到成功消息。

4.  验证安装：

    .. code-block:: powershell

        choco --version

    此时应看到 Chocolatey 版本号（例如 ``2.3.0``）。

.. note::

    安装 Chocolatey 后，可能需要关闭并重新打开 PowerShell，才能识别 ``choco`` 命令。

安装 MinGW-w64（C++ 编译器）
============================

MinGW-w64 为 Windows 提供 GCC 编译器套件，其中包括用于编译 C++ 的 ``g++``。

通过 Chocolatey 安装：

.. code-block:: powershell

    choco install mingw -y

此命令会安装：

- ``gcc`` - C 编译器
- ``g++`` - C++ 编译器  
- ``gdb`` - GNU 调试器
- 标准 C/C++ 库和头文件

**验证安装：**

.. code-block:: powershell

    g++ --version

此时应看到类似以下的输出：

.. code-block:: none

    g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders) 14.2.0
    Copyright (C) 2024 Free Software Foundation, Inc.

**测试编译：**

创建一个简单的测试文件 ``test.cpp``：

.. code-block:: cpp

    #include <iostream>
    int main() {
        std::cout << "C++ compiler works!" << std::endl;
        return 0;
    }

编译并运行：

.. code-block:: powershell

    g++ test.cpp -o test.exe
    .\test.exe

此时应看到控制台输出 ``C++ compiler works!``。

安装 Make 工具
==============

``make`` 工具通过读取定义编译规则和依赖关系的 Makefile 来自动执行构建过程。

通过 Chocolatey 安装：

.. code-block:: powershell

    choco install make -y

**验证安装：**

.. code-block:: powershell

    make --version

此时应看到类似以下的输出：

.. code-block:: none

    GNU Make 4.4.1
    Built for Windows32
    Copyright (C) 1988-2023 Free Software Foundation, Inc.

**测试 make：**

创建一个简单的 ``Makefile``：

.. code-block:: makefile

    hello:
    	@echo "Make utility works!"

运行：

.. code-block:: powershell

    make hello

此时应看到控制台输出 ``Make utility works!``。

.. note::

    Makefile 要求使用 **TAB 字符** 缩进，而不是空格。编辑 Makefile 时，请确保文本编辑器配置为使用制表符。

环境变量
========

Chocolatey 会在安装过程中自动将已安装工具添加到系统 PATH。如果无法识别这些命令：

1.  关闭并重新打开终端/PowerShell
2.  检查安装目录是否位于 PATH 中：

    .. code-block:: powershell

        $env:PATH -split ';' | Select-String -Pattern 'mingw|make'

3.  如果仍然无法使用，请注销 Windows 后重新登录

使用工具
========

编译 Red Pitaya Streaming 示例
------------------------------

现在可以编译 Red Pitaya C++ streaming 示例：

.. code-block:: powershell

    # Navigate to examples directory
    cd C:\path\to\RedPitaya-Examples\C\API_Examples\Streaming

    # Compile an example
    g++ -std=c++20 -o stream_adc_1.exe stream_adc_1.cpp -I..\..\..\include -L..\..\..\lib -lrp-streaming


使用 Makefile 构建
------------------

对于包含 Makefile 的项目：

.. code-block:: powershell

    # Build project
    make

    # Clean build artifacts
    make clean

    # Build specific target
    make target_name


FPGA 项目生成
-------------

对于 FPGA 开发（参见 :ref:`FPGA Getting Started <fpga_top>`），使用 make 工具生成 Vivado 项目：

.. code-block:: powershell

    # Generate FPGA project
    cd C:\path\to\RedPitaya\fpga\prj\v0.94
    make project

其他安装方法
============

手动安装 MinGW-w64
-------------------

如果不想使用 Chocolatey：

#. 从以下位置下载 MinGW-w64：|MinGW-Download|
#. 运行安装程序并按照设置向导操作
#. 手动将 ``bin`` 目录添加到系统 PATH：
   
   - 右键单击“This PC”→“Properties”→“Advanced system settings”
   - 单击“Environment Variables”
   - 在“System variables”下编辑“Path”变量
   - 添加 MinGW-w64 ``bin`` 目录（例如 ``C:\mingw64\bin``）


手动安装 Make
-------------

如果不想使用 Chocolatey：

#. 从以下位置下载 Make：|Make-Download|
#. 将其解压到类似 ``C:\Program Files\Make`` 的位置
#. 将该目录添加到系统 PATH（参见上述步骤）

故障排除
========

安装后找不到命令
----------------

#. 关闭并重新打开终端/PowerShell
#. 验证 PATH 是否包含工具目录：

    .. code-block:: powershell

        $env:PATH

#. 注销 Windows 后重新登录
#. 如果问题仍然存在，请重启计算机


streaming 库编译错误
--------------------

请确认：

#. 已下载完整的 Red Pitaya streaming 客户端软件包
#. streaming 库文件（``rp-streaming.dll``、头文件）可访问
#. 编译命令中使用了正确的 include 路径（``-I``）和库路径（``-L``）


Make 报告缺少分隔符
-------------------

这通常表示 Makefile 使用了空格而非制表符。请将编辑器配置为在 Makefile 中使用制表符缩进。


Chocolatey 安装失败
-------------------

#. 确认正在以管理员身份运行 PowerShell
#. 检查互联网连接
#. 尝试再次运行安装命令
#. 检查防病毒软件是否阻止了安装

相关文档
========

- :ref:`WSL Setup <wsl_setup>` - Windows 上的替代 Linux 环境
- :ref:`FPGA Getting Started <fpga_top>` - 使用 make 生成 FPGA 项目
- :ref:`Streaming Examples <examples_streaming>` - C++ streaming API 示例

.. |Chocolatey-Install| raw:: html

    <a href="https://chocolatey.org/install" target="_blank">Chocolatey 安装指南</a>

.. |MinGW-Download| raw:: html

    <a href="https://www.mingw-w64.org/downloads/" target="_blank">MinGW-w64 下载</a>

.. |Make-Download| raw:: html

    <a href="https://gnuwin32.sourceforge.net/packages/make.htm" target="_blank">Windows GNU Make</a>

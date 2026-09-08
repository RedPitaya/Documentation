.. _fpga_create_project:

##############################################
在 Vivado（2025.1）中创建 FPGA 项目
##############################################

为了简化新 FPGA 项目的创建或现有项目功能的添加，Red Pitaya FPGA 仓库提供了可自动生成 :ref:`现有项目 <fpga_projects>` 的脚本和模板。

.. note::

    本节介绍基于 RedPitaya-FPGA 仓库脚本的 **Vivado 2025.1** （OS 3.00+）当前构建流程。
    旧版 Vivado 2020.1 方法仍可用于向后兼容，并在 :ref:`旧版 Vivado 2020.1 兼容性 <legacy_vivado_2020_1_compatibility>` 节中概述。

.. contents:: 目录
    :local:
    :depth: 2
    :backlinks: top

|


下载 FPGA GitHub 仓库
================================

首先，将 |FPGA GitHub repository| 下载到本地计算机。进入 |FPGA GitHub repository| 并下载此项目的 ZIP 文件夹。

.. figure:: img/FPGA-repository.png
    :width: 1000
    :align: center

如果使用 Windows，请将项目仓库下载并解压到任意文件夹。记住解压后仓库的位置。

或者，如果使用 Linux，请先安装 Git，然后进入目标位置并克隆 Red Pitaya Git 仓库。

.. code-block:: bash

    sudo apt-get install git
    git clone https://github.com/RedPitaya/RedPitaya-FPGA.git

无论采用哪种方式，**解压或克隆仓库的路径中都不要使用空格**。

最后，将解压后的仓库文件夹重命名为 **RedPitaya-FPGA**。

|

访问旧版本仓库
-------------------------------------------

上述说明适用于位于 *master* 分支的最新版本 Red Pitaya FPGA。如果需要旧版本，请在 GitHub 仓库中检查对应的分支或标签。

在 OS 1.04-18 之前，FPGA 仓库属于主 |Red Pitaya GitHub repository| 的一部分，FPGA 项目位于 *fpga* 目录中。

|

.. _FPGA_project_flags:

构建项目选项
=======================

创建新的 FPGA 项目时，每位用户都必须考虑目标硬件平台的具体要求和限制。每种 Red Pitaya 板卡都有自己的规格，可能需要对 FPGA 设计采用不同的配置和优化。
为简化操作，Red Pitaya FPGA 仓库提供了一组脚本和模板，可作为新项目的起点。这些模板包含预配置设置和示例设计，可以根据单个项目的需求进行定制。

脚本会根据所选标志自动构建项目。下表显示哪些板卡支持哪些项目。

.. include:: ../../projects/fpga_project_table.inc

.. include:: ../../projects/fpga_project_flags.inc


.. note::

    每种构建项目标志与构建型号标志的组合都应视为唯一组合，只与对应的 Red Pitaya 板卡型号兼容。这意味着，即使两块板卡使用相同的 FPGA 芯片，为一块板卡生成的比特流也可能无法在另一块板卡上工作。
    例如，为 *STEMlab 125-14* 生成的比特流无法在 *SDRlab 122-16* 上工作，上传时会产生以下错误。
    
    .. code-block:: bash

        sh: 1: echo: echo: I/O error
        BIN FILE loading through FPGA manager failed

|

构建过程
=================

.. note::

    继续之前，请确认已正确遵循 :ref:`Vivado 和 Vitis 安装说明 <FPGA_install_vivado>`。

    当前 RedPitaya-FPGA 流程的主要入口为：

    * ``open_vivado.sh`` (Linux/Unix-like shells)
    * ``open_vivado.bat`` (native Windows CMD/PowerShell)
    * Root ``Makefile`` targets (``make project``, ``make``, ``make dts``)


自动项目生成脚本有两种运行模式：

* **非项目模式**：此模式生成一组文件，无需打开 Vivado GUI 即可用于构建项目。适合偏好命令行工具或希望自动化构建过程的用户。
* **项目模式**：此模式生成可在 Vivado GUI 中打开、进一步编辑和定制的 Vivado 项目。适合希望使用 Vivado 图形界面并交互式修改设计的用户。

|

.. _fpga_non_project_mode:

非项目模式
-----------------

在非项目模式下，生成的文件按扁平目录结构组织，更易于管理和对单个文件进行版本控制。但用户会失去 Vivado 项目结构带来的便利，例如在 Vivado GUI 中轻松打开和编辑项目的能力。
非项目模式使用 RTL、约束和板卡配置文件生成输出，而不会创建完整的 GUI 项目。

.. note::

    Red Pitaya FPGA 仓库必须通过 ``git`` 命令下载，否则项目创建会失败。

当前仓库包含以下相关脚本类型：

.. list-table:: 相关脚本类型
    :header-rows: 1
    :widths: 35 65

    * - TCL 脚本
      - 功能
    * - ``red_pitaya_vivado_<MODEL>.tcl``
      - 为所选型号生成比特流和报告。
    * - ``red_pitaya_hsi_fsbl.tcl``
      - 生成 FSBL 可执行二进制文件（参见 |SDK/Vitis project creation|）。
    * - ``red_pitaya_hsi_dts.tcl``
      - 生成设备树源文件（参见 |SDK/Vitis project creation|）。
    * - ``red_pitaya_vivado_sim.tcl``
      - 生成仿真文件。


1. **打开终端或 shell**。

    * **Linux**：使用普通终端。
    * **Windows 原生 GUI 流程**：使用带有 ``open_vivado.bat`` 的 CMD/PowerShell。
    * **Windows 基于 make 的流程**：使用类 Unix shell（*Git Bash*、*MSYS2* 或 *WSL*），因为 Makefile 使用 Unix shell 工具。

    .. note::

        对于 Windows 上基于 ``make`` 的构建，请在 shell 环境中安装并提供以下工具：``make``、``gcc``、``dtc`` 和 ``xsct``。

#. **进入解压后的 FPGA 仓库**。本例中我们已将解压后的文件夹重命名为 RedPitaya-FPGA。如果尚未重命名，请使用原始名称。

    .. code-block:: bash

        cd "<path to Red Pitaya repository>/RedPitaya-FPGA"

    .. note::

        与 Linux 和 Vivado 不同，Windows 文件路径使用反斜杠（``\``），而不是正斜杠（``/``）。

#. **生成项目**。在终端或命令提示符中运行以下命令。注意这里**没有 ``project`` 关键字**，该关键字用于 :ref:`项目模式 <fpga_project_mode>`。

    .. code-block:: bash

        make PRJ=name MODEL=model

    这是 RedPitaya-FPGA 的标准非项目构建命令。
    也可以只生成设备树：

    .. code-block:: bash

        make dts PRJ=name MODEL=model

#. **比特流位置**。生成的 *.bit* 文件位于 **/prj/<project_name>/out/red_pitaya.bit**。


.. note::

    如果项目生成过程中发生错误，可能是 Vivado 版本不正确或缺少依赖项。请确保安装了正确版本的 Vivado，并满足所有必要依赖。
    有关此问题的更多信息，请参阅 :ref:`在不同 Vivado 版本中运行脚本 <different_vivado_version>` 节。

|

.. _fpga_project_mode:

项目模式
-------------

项目模式会生成完整的 Vivado 项目结构，包括所有必需的文件和目录。用户可以在 Vivado GUI 中打开项目并按需修改。
以此模式创建项目只需要 Red Pitaya FPGA 仓库。可按以下步骤创建项目：

1.  **打开终端或 shell**。

    * **Linux/类 Unix shell**：

      .. code-block:: bash

          ./open_vivado.sh <project_name> <model>

      示例：

      .. code-block:: bash

          ./open_vivado.sh v0.94 Z20_250

    * **Windows CMD/PowerShell（原生）**：

      .. code-block:: bat

          open_vivado.bat <project_name> <model>

      示例：

      .. code-block:: bat

          open_vivado.bat v0.94 Z20_250

    * **替代方式（Windows 上的 Linux 或类 Unix shell）：**

      .. code-block:: bash

          make project PRJ=<project_name> MODEL=<model>

#.  **进入解压后的 FPGA 仓库**。本例中我们已将解压后的文件夹重命名为 RedPitaya-FPGA。如果尚未重命名，请使用原始名称。

    .. code-block:: bash

        cd "<path to Red Pitaya repository>/RedPitaya-FPGA"

    .. note::

        与 Linux 和 Vivado 不同，Windows 文件路径使用反斜杠（``\``），而不是正斜杠（``/``）。

#.  **创建或打开项目**。根据您的操作系统或 shell，使用上述命令之一。

    以下是命令行选项的参考图片：

    * **终端/CMD**

        .. figure:: img/Vivado-CMD.png
            :width: 800
            :align: center

    * **Vivado HLS 命令提示符**

        .. figure:: img/Vivado-hls-command-prompt.png
            :width: 800
            :align: center

    * **Vivado TCL 控制台**

        .. figure:: img/Vivado-tcl-console.png
            :width: 800
            :align: center

#.  **修改项目**。打开项目后，其中包含所有必需的 Red Pitaya 文件。
    然后可以在 *red_pitaya_top.sv* 文件末尾添加或编写 Verilog 模块，或者右键点击 *Design Sources* 文件夹并选择 *Add Source* 来添加新源文件。
    有关如何添加源文件并在设计中连接它们的更多信息，请参阅 :ref:`修改项目一节 <fpga_modify_project>`。

#.  **比特流生成**。现在可以点击 Vivado GUI 中相应的按钮，运行综合、实现和比特流生成。
    生成的 *.bit* 文件位于 **prj/<project_name>/project/redpitaya.runs/impl_1/**，文件名为 **red_pitaya_top.bit** （比特流文件名与设计顶层模块名称相同）。

    .. figure:: img/Vivado-GUI.png
       :width: 600
       :align: center

|

关于项目创建过程，有几点重要事项需要注意：

6.  **重新打开现有项目** - 打开 Vivado，从 **Recent Projects** 列表中选择项目。

    .. figure:: img/Vivado-recent-projects.png
        :width: 800
        :align: center

#.  **重新创建现有项目** - 对同一个 ``PRJ`` 再次运行 *make project* 命令可能会覆盖生成的项目资源。请备份重要的 RTL 资源和 IP 核。

|

.. _fpga_copy_project:

创建安全的项目副本
=============================

.. note::

    本节信息适用于 **自动项目生成**。手动创建项目的过程要简单得多，只需复制基准项目，并按需修改 RTL 和约束。更多信息请参阅 :ref:`从零创建自定义项目 <fpga_project_from_scratch>`。

安全的项目副本是现有项目的复制品，可以在不影响原始项目的情况下进行修改。当您之后可能需要访问原始项目，或希望备份自定义设计时，这很有用，因为再次运行自动项目生成脚本可能会覆盖自定义设计。

这很重要的原因：

- 重新构建同一个 ``PRJ`` 可能覆盖生成的数据
- 保留独立的 ``prj/<new_project>`` 文件夹可以简化备份和版本管理

以下内容**不**需要重命名：

- 根目录启动器/型号脚本，例如 ``red_pitaya_vivado_Z10.tcl`` 或 ``red_pitaya_vivado_Z20.tcl``
- ``open_vivado.sh`` / ``open_vivado.bat``
- 项目本地文件名 ``ip/system.tcl``

这些脚本由 ``MODEL`` 选择，然后使用作为 ``PRJ`` 传入的文件夹名称进入 ``prj/<new_project>``。

建议步骤：

1. 在 ``prj/`` 下创建新的项目文件夹。
2. 将基准项目（例如 ``prj/v0.94``）复制到新文件夹中。
3. 将自定义 RTL 放入 ``prj/<new_project>/rtl``。
4. 将测试平台放在 ``prj/<new_project>/tbn`` 中。
5. 使用显式型号标志进行构建。

示例：

.. code-block:: bash

    cd RedPitaya-FPGA
    cp -r prj/v0.94 prj/new_project
    make project PRJ=new_project MODEL=Z10
    make PRJ=new_project MODEL=Z10

Windows 原生打开项目示例：

.. code-block:: bat

    open_vivado.bat new_project Z10

复制后的附加检查
--------------------------------

复制项目目录通常足以处理 ``v0.94`` 等基准项目。
但是，对于每个项目而言，这种做法**并不总是充分**。

对当前 ``RedPitaya-FPGA`` master 的仓库检查表明，一些根目录型号脚本包含特定于项目名称的逻辑，例如：

- ``if {$prj_name == "stream_app"}``
- ``if {$prj_name == "logic"}``

这些分支在载入本地块设计 Tcl 之前设置项目专用的全局变量。

这意味着：

- 将 ``v0.94`` 复制为新名称通常很直接
- 将 ``stream_app`` 或 ``logic`` 复制为新名称可能需要额外更新脚本

重命名项目副本后通常需要执行的后续任务：

1. 检查复制的项目是否依赖 ``red_pitaya_vivado_<MODEL>.tcl`` 中与 ``$prj_name`` 的匹配。
2. 如果依赖，请针对新项目名称更新这些条件，或将项目专用设置重构到项目本地 Tcl 中。
3. 检查 ``tbn/`` 及类似文件夹下的本地辅助脚本，查找硬编码的项目路径或旧名称。

.. note::

    在当前仓库中，主要构建入口会正确使用复制后的文件夹名称。只有当项目依赖精确的项目名称检查，或包含带硬编码路径的辅助脚本时，才需要额外工作。

有关超出模板复制范围、创建项目时手动选择文件（约束和配置文件）的详细信息，请参阅 :ref:`fpga_project_from_scratch`。

|

.. _fpga_legacy_2020_flow:

.. _legacy_vivado_2020_1_compatibility:

旧版 Vivado 2020.1 兼容性
====================================

当前 RedPitaya-FPGA ``master`` 分支面向 **Vivado 2025.1**。对于较旧的 OS 分支或为 Vivado 2020.1 创建的归档项目，请继续使用旧版流程。

* **当前分支（OS 3.00+）：** Vivado 2025.1
* **旧版流程（OS 1.04 - 2.00）：** Vivado 2020.1 + SDK 2019.1

有关旧版工具的安装和使用，请参阅 :ref:`Vivado 2020.1 安装 <FPGA_install_vivado_2020_1>` 和 :ref:`SDK 2019.1 旧版安装 <fpga_install_sdk>`。

旧版流程步骤（已根据仓库标签验证）
-----------------------------------------------------

使用为 Vivado 2020.1 构建的旧版 RedPitaya-FPGA 快照（例如标签 ``2.07-48``）。

1. **克隆仓库并检出旧版标签**

    .. code-block:: bash

        git clone https://github.com/RedPitaya/RedPitaya-FPGA.git
        cd RedPitaya-FPGA
        git checkout 2.07-48

2. **使用旧版脚本的项目模式（打开 GUI 项目）**

    .. code-block:: bash

        make project PRJ=v0.94 MODEL=Z10

    此旧版流程使用 ``red_pitaya_vivado_project_<MODEL>.tcl`` 脚本。

3. **非项目模式（直接构建比特流）**

    .. code-block:: bash

        make PRJ=v0.94 MODEL=Z10

4. **可选：仅生成设备树**

    .. code-block:: bash

        make dts PRJ=v0.94 MODEL=Z10

5. **预期的旧版输出**

    * 比特流：``prj/v0.94/out/red_pitaya.bit``
    * 比特流二进制文件：``prj/v0.94/out/red_pitaya.bit.bin``

旧版流程的 Windows 和 Linux 说明
----------------------------------------

* **Linux**：在已加载 Vivado 2020.1 环境的普通 shell 中运行命令。
* **使用类 Unix shell（Git Bash/MSYS2/WSL）的 Windows**：``make`` 流程与上述相同。
* **没有 make 的 Windows CMD/PowerShell**：使用旧版 Tcl 入口直接运行 Vivado：

  .. code-block:: bat

      C:\Xilinx\Vivado\2020.1\bin\vivado.bat -source red_pitaya_vivado_project_Z10.tcl -tclargs v0.94

  .. code-block:: bat

      C:\Xilinx\Vivado\2020.1\bin\vivado.bat -source red_pitaya_vivado_Z10.tcl -tclargs v0.94

| 

.. _different_vivado_version:

在不同 Vivado 版本中运行脚本
==================================================

在不同于脚本生成所用版本的 Vivado 版本中运行自动项目生成脚本可能会产生错误。这是因为脚本针对特定 Vivado 版本定制，可能与其他版本不兼容。
如果可能，请安装生成脚本时使用的 Vivado 版本。如果无法做到，可以尝试修改脚本，使其兼容您的 Vivado 版本。
请注意，**这不保证能够正常工作，且可能需要对脚本进行额外修改**。

* **Vivado 版本（当前脚本）：** 2025.1

:ref:`项目模式 <fpga_project_mode>` 和 :ref:`非项目模式 <fpga_non_project_mode>` 脚本都针对特定 Vivado 版本设计，在不同版本中运行可能失败。

.. code-block:: shell-session

    ... This script was generated using Vivado <2025.1> and is being run in <other_version> ...

1.  首先，在脚本中**找到 Vivado 版本行**，其形式应如下：

    .. code-block:: shell-session

        set scripts_vivado_version 2025.1

#.  **仅在必要时更改脚本版本**。这是让构建在另一 Vivado 版本中继续进行的快速变通方法。
    但是，如果您使用的版本中某些 IP 不同，此方案可能导致问题。

    要正确更新脚本，请在 :ref:`项目模式 <fpga_project_mode>` 中打开项目，并从菜单中选择 **Reports > Report IP Status**。代码窗口下方会打开一个新选项卡。
    如果并非所有 IP 都是最新版本，则需要更新它们。但在此之前，必须手动修改 TCL 脚本，使其匹配您的 Vivado 版本；否则 Vivado 启动时不会创建块设计。

    .. figure:: img/Vivado-IPupdate.png
        :width: 800
        :align: center

#.  **更新脚本**。IP 更新到最新版本后，进入 Tcl 控制台选项卡并运行以下命令。

    .. code-block:: shell-session

        write_bd_tcl systemZ10.tcl

    这会生成新的 tcl 脚本，用于替换 ``prj/<project name>/ip`` 目录中的旧脚本。

    .. note::

        脚本名称可能因所使用的板卡型号而异。请检查 :ref:`构建项目选项 <FPGA_project_flags>`，根据项目标志确定正确的脚本名称。





.. 替换定义


.. |FPGA GitHub repository| replace:: `FPGA GitHub 仓库 <https://github.com/RedPitaya/RedPitaya-FPGA>`__
.. |Red Pitaya GitHub repository| replace:: `Red Pitaya GitHub 仓库 <https://github.com/RedPitaya/RedPitaya>`__
.. |SDK/Vitis project creation| replace:: :ref:`SDK/Vitis 项目创建 <fpga_create_sdk_project>`

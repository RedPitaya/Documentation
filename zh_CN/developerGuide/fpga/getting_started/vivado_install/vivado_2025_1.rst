.. _FPGA_install_vivado_2025_1:

###############################################
安装 Vitis 2025.1 和 Vivado 2025.1
###############################################

本安装教程将指导您在计算机或虚拟机上安装 Vitis 2025.1 和 Vivado 2025.1。本教程适用于希望在 Red Pitaya OS 3.00 或更高版本上使用 Red Pitaya 板卡 FPGA 的用户。

在较旧版本的 Red Pitaya OS 中，需要分别安装 Vivado 2020.1 和 Xilinx SDK 2019.1。Vivado 用于构建 FPGA 比特流，而 Xilinx SDK 用于构建 ARM 软件。在 Red Pitaya OS 3.00 或更高版本中，Vitis 2025.1 同时用于这两项任务。

安装 Vitis 时也会安装对应版本的 Vivado，因此我们可以同时使用这两个工具。

.. contents:: 目录
    :local:
    :depth: 2
    :backlinks: top

|

软件兼容性
=======================

要为以下 Red Pitaya OS 版本构建 FPGA 比特流，必须使用 Vivado 2025.1：

* Red Pitaya OS 3.00 或更高版本

|


创建 AMD 账户
============================

无论使用哪种操作系统，我们都需要创建免费的 **AMD 账户**。

    .. figure:: ../img/Vivado-install/Licence-AMD-sign-in.png
        :width: 400

之前版本的 Vivado 需要 Vivado WebPACK 许可证，但 Vivado 2025.1 对 Zynq 7000 系列不需要许可证。

|

下载 Vitis 2025.1
=======================

.. note::

    编写本教程时，Vitis 的最新版本为 2026.1。预计 AMD Vitis 下载页面会更新，因此下载链接的位置可能会变化。
    但是，下载和安装过程的总体模式应保持不变。

1.  前往 :ref:`AMD Vitis 下载 <vitis_downloads>`，然后点击 **Download Vitis** 按钮。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_download_1.png
        :width: 1000
        :align: center

#.  从页面右侧的下拉菜单中选择 **Vitis 2025.1**。这会将您重定向到 Vitis 2025.1 的下载页面。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_download_2.png
        :width: 1000
        :align: center

#.  稍微向下滚动，直到看到 **Unified installer for FPGA & Adaptive SoC Tools - 2025.1 - Jun 4, 2025**。如果下拉菜单尚未展开，请点击向下箭头将其展开。

    .. note::

        Vitis 2025.1 有一个日期为 2025 年 9 月 17 日的 Update 1 版本，它支持一些额外设备，但 Zynq 7000 系列并不需要该版本，而且只会占用计算机上的额外空间。因此，我们将使用原始的 Vitis 2025.1 版本。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_download_3.png
        :width: 1000
        :align: center

#.  根据所使用的计算机操作系统，从三个可用选项中为您的操作系统选择适当的 **AMD Unified installer for FPGA & Adaptive SoC Tools - 2025.1**：

    * Windows 使用 **Windows Self Extracting Web Installer**。
    * Linux 使用 **Linux Self Extracting Web Installer**。

    .. note::

        如果 Self Extracting Web Installer 因任何原因无法工作，请使用 **Unified Installer**。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_download_4.png
        :width: 1000
        :align: center

#.  点击链接后，您会被重定向到 AMD 登录页面。使用 AMD 用户名和密码登录。如果您没有 AMD 账户，则需要立即创建一个（免费）。

    .. figure:: ../img/Vivado-install/Licence-AMD-sign-in.png
        :width: 500
        :align: center

#.  登录页面会将您重定向到下载中心的 **Name and Address verification** 页面。填写所需信息，然后点击页面底部的 **Download** 按钮。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_5.png
        :width: 1000
        :align: center

#.  下载会自动开始。由于文件大小约为 200 MB，下载不应耗时太久。

    .. note::

        如果使用 **Unified Installer**，文件下载时间会明显更长。请确保网络连接稳定且下载不中断。如果下载中断，您必须从头开始下载。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_6.png
        :width: 400
        :align: center

#.  如果下载的是 **Unified Installer**，请使用您偏好的方法解压 ``.tar.gz`` 文件。

此时，您应该已经拥有解压后的 Vitis 2025.1 安装程序。接下来我们将分别介绍各操作系统的安装过程。

|

安装 Vitis 2025.1
=========================

Windows 和 Linux 的安装过程完全相同，因此将在同一节中介绍这两种操作系统。

.. note::

    由于 Vitis 2025.1 可能只支持数量固定的 Linux Ubuntu 版本，且未考虑未来发布的版本，因此将来安装时可能需要“伪造” Ubuntu 版本。可以理解，这并不理想，但对于尚未更新以支持较新操作系统的软件，这是常见做法。如果在安装过程中遇到问题，请参阅 AMD Vitis 官方文档或向 Red Pitaya 社区寻求帮助。

安装过程相当直接。您只需运行安装程序并按说明操作。

#.  双击下载的 **FPGAs_AdaptiveSoCs_Unified_SDI_2025.1_0530_0145_Win64.exe** 或 **FPGAs_AdaptiveSoCs_Unified_SDI_2025.1_0530_0145_Lin64.bin** 安装程序。对于统一安装程序，请进入解压后的文件夹并运行 **xsetup.exe** 或 **xsetup.bin** 文件以开始安装。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_1.png
        :width: 300

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_2.png
        :width: 500

#.  安装程序启动后，会弹出窗口通知您有新版本的安装程序可用。点击 **Continue** 继续安装。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_3.png
        :width: 600

#.  第一个界面显示安装要求，包括支持的操作系统。点击 **Next** 继续。由于统一安装程序不使用互联网连接，可能会弹出警告，提示无法访问下载服务器。关闭警告并继续安装。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_4.png
        :width: 1000
        :align: center

#.  使用 **Web installers** 时，系统会要求您登录 AMD 账户。在较旧的 Vivado 版本中，这是一个主要问题，因为安装程序无法连接 AMD 服务器来验证用户身份。如果此方式无法工作，请使用会跳过登录过程的 **Unified installer**。

    选择 **Download and Install Now**，然后点击 **Next**。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_5.png
        :width: 1000
        :align: center

#.  选择 **Vitis**，因为我们将安装完整环境，同时启用 ARM 处理器的软件开发。如果您只计划使用 Vivado 进行 FPGA 开发，也可以仅选择 **Vivado**。点击 **Next** 继续。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_6.png
        :width: 1000
        :align: center

#.  接下来会显示安装选项。请务必选中 **SoCs** 下的 **Zynq-7000 All Programmable SoC** 选项。这是 Red Pitaya 板卡所需的唯一选项。其他复选框保持原样。如果其他开发需要额外选项，请按需选择。请注意，选择不必要的选项会增加安装时间和磁盘空间占用。

    点击 **Next** 继续。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_7.png
        :width: 1000
        :align: center


#.  在很长的许可证协议列表中勾选所有协议框，然后点击 **Next**。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_8.png
        :width: 1000
        :align: center

#.  现在需要选择安装目录。默认安装目录为 **C:/Xilinx**，但必要时可以改为其他目录。这里使用 **C:/Programs/Xilinx** 目录，您也可以自行更改。

    确保在 **Apply shortcut & file associations** 下选择 **All users**，否则快捷方式只对管理员用户账户可用。

    点击 **Next**。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_9.png
        :width: 1000
        :align: center

#.  检查安装摘要，然后点击 **Install** 开始安装。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_10.png
        :width: 1000
        :align: center

#.  等待安装完成。根据所选选项、计算机速度和网络连接情况，这可能需要一段时间。安装过程会从 AMD 服务器下载必要文件，因此需要稳定的互联网连接。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_11.png
        :width: 1000
        :align: center

#.  安装完成后，您会看到以下界面。点击 **OK** 结束安装过程。

    .. figure:: ../img/Vivado-install/2025.1/Vitis_2025_install_12.png
        :width: 1000
        :align: center
    
#.  随后会弹出 License Manager 窗口。由于 Zynq 7000 系列不需要许可证，我们只需关闭该窗口。如果使用其他 FPGA，请按照 License Manager 中的说明获取许可证。

#.  **Windows** - 将 Vivado 和 Vitis 的 ``bin`` 文件夹添加到 ``PATH`` 环境变量，这样您打开的任何新 shell 都可以使用 ``vivado`` 和 ``vitis`` 命令。

    如果 Vivado 安装在默认位置，请添加以下文件夹：

    .. code-block:: text

        C:\Xilinx\2025.1\Vivado\bin
        C:\Xilinx\2025.1\Vitis\bin

    如果使用了诸如 ``C:\Programs\Xilinx`` 的自定义安装目录，请改为添加以下文件夹：

    .. code-block:: text

        C:\Programs\Xilinx\2025.1\Vivado\bin
        C:\Programs\Xilinx\2025.1\Vitis\bin

    将文件夹添加到 **User variables > Path** 可仅更新当前用户，添加到 **System variables > Path** 则可供所有用户使用。更新系统 PATH 需要管理员权限。修改 PATH 后，请关闭并重新打开 shell，使其读取新设置。

#.  **Linux** - 对于 Linux 用户，建议将 **.settings64-Vivado.sh** 和 **.settings64-Vitis.sh** 脚本添加到 shell 配置文件（例如 **.bashrc** 或 **.zshrc**）中，这样就可以在终端输入 **vitis** 或 **vivado** 来启动 Vitis 和 Vivado。

    .. code-block:: shell

        echo 'source /opt/Programs/Xilinx/2025.1/Vivado/.settings64-Vivado.sh' >> ~/.bashrc
        echo 'source /opt/Programs/Xilinx/2025.1/Vitis/.settings64-Vitis.sh' >> ~/.bashrc
        source ~/.bashrc

    .. note::

        上述命令中的路径可能因安装过程中选择的安装目录而异。请相应调整路径。

#.  最后一步是检查 Ubuntu/Linux 计算机上的 *Language and Region settings*，确保 **Format** 使用 **点号（“.”）作为小数分隔符** （英国或美国格式均可）。**Vivado 要求使用点号作为小数分隔符**，否则可能导致比特流生成问题，因为 Vivado 将无法识别模型的某些部分。

#.  现在，我们已经可以在 Windows 和 Linux 操作系统上使用 Vivado 2025.1。

|

.. _FPGA_install_vivado_2020_1:

###############################
Vivado 2020.1 安装
###############################

本安装教程将指导你在计算机或虚拟机上安装 Vivado 2020.1。本教程适用于希望在 Red Pitaya OS 1.04-2.07
中使用 Red Pitaya 板卡 FPGA 的所有用户。

.. contents:: Table of Contents
    :local:
    :depth: 2
    :backlinks: top

|

软件兼容性
=======================

构建以下 Red Pitaya OS 版本的 FPGA 比特流需要使用 Vivado 2020.1：

* Red Pitaya OS 1.04
* Red Pitaya OS 2.00 (2.00 - 2.07)

|

获取 WebPACK 许可证
============================

无论使用哪种操作系统，都需要先获取免费的 **ISE WebPACK 许可证**。我们先完成这一步。

1. Go to the `AMD Xilinx License Form <https://account.amd.com/en/forms/license/license-form.html>`_.
#. 使用 AMD 账户登录。如果没有 AMD 账户，需要创建一个；注册免费。

    .. figure:: ../img/Vivado-install/Licence-AMD-sign-in.png
        :width: 400
    
#. 填写个人信息。请确保将许可证类型选择为 **Vivado WebPACK**，然后点击 **Submit**。
#. 许可证文件会发送到注册邮箱。请将 **.lic** 文件保存到安全位置，稍后还会用到。

|


下载 Vivado 2020.1
=======================

1.  打开 |Vivado-downloads|。
#.  进入 **Vivado Archive**，选择 **2020.1** 选项。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-archive.png
        :width: 1000
        :align: center

    .. figure:: ../img/Vivado-install/2020.1/Vivado-2020_1.png
        :width: 1000
        :align: center

#.  在 2020.1 下拉菜单中向下滚动，直到看到“Vivado Design Suite - HLx Editions - 2020.1  Full Product Installation”（就在第一个
    下载链接之后）。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-update1.png
        :width: 1000
        :align: center
    
    .. figure:: ../img/Vivado-install/2020.1/Vivado-full-download.png
        :width: 1000
        :align: center

#. 这里有三个下载链接。请使用 **Vivado HLx 2020.1: All OS installer Single-File Download (TAR/GZIP - 35.51 GB)**，因为自 Xilinx 被 AMD 收购后，
    Windows 和 Linux 自解压 Web Installer 已无法工作。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-tar-file.png
        :width: 1000
        :align: center

#. 点击链接后，系统会要求登录。请使用 AMD 用户名和密码。如果没有 AMD 账户，需要创建一个；注册免费。

    .. figure:: ../img/Vivado-install/Licence-AMD-sign-in.png
        :width: 500
        :align: center

#. 你会被重定向到下载中心，在那里填写信息并点击页面底部的“DOWNLOAD”按钮开始下载。请注意，这是一个 35 GB 的文件，
    下载时间取决于网络连接速度，可能需要较长时间。

    .. figure:: ../img/Vivado-install/Licence-AMD-download-centre.png
        :width: 1000
        :align: center

#.  使用你偏好的方法解压 .tar.gz 文件。

此时应已得到解压后的 Vivado 2020.1 安装目录。下面分别介绍各操作系统的安装过程。

|

安装 Vivado 2020.1
=========================

Windows 和 Linux 的安装过程略有不同。


Windows
---------

Windows 安装非常直接，只需运行安装程序并按照说明操作即可。

1.  使用 *7zip* 或 *WinRAR* 解压 *.tar.gz* 文件。
#.  双击 **xsetup.exe** 文件开始安装。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer.png
        :width: 400

#.  安装程序启动后，会弹出两个窗口，提示安装程序无法访问服务器。请关闭这两个窗口。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-1.png
        :width: 600

#.  第一个界面显示安装要求。仔细查看可发现，它说明仅支持 Windows 10，但在 Windows 11 上也可以安装运行。点击 **Next** 继续。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-2.png
        :width: 1000
        :align: center

#.  勾选所有许可证协议复选框，然后点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-3.png
        :width: 1000
        :align: center

#.  选择 **Vivado**，因为我们只安装 Vivado 编程环境，而不是完整的 Vitis。然后点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-4.png
        :width: 1000
        :align: center

#.  选择 **Vivado HL WebPACK**，因为我们将使用免费的 Vivado 版本。点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-5.png
        :width: 1000
        :align: center

#.  下一个界面显示安装选项。勾选下图所示的所有复选框，然后点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-6.png
        :width: 1000
        :align: center

#.  现在需要选择安装目录。默认安装目录为 **C:/Xilinx**，如有需要也可以更改为其他目录。
    下图使用的是 **C:/Programs/Xilinx** 目录。点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-7.png
        :width: 1000
        :align: center

#.  检查安装摘要，然后点击 **Install** 开始安装。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-8.png
        :width: 1000
        :align: center

#.  等待安装完成。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-9.png
        :width: 1000
        :align: center

#.  安装完成后会看到以下界面。点击 **OK** 结束安装过程。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-10.png
        :width: 1000
        :align: center

#.  现在安装 **ISE WebPACK 许可证**。这是一个允许使用 Vivado 编程环境的免费许可证。下面介绍如何从 Vivado 打开 **License Manager**。

    .. figure:: ../img/Vivado-install/2020.1/Licence-open-manager.png
        :width: 1000
        :align: center
    
#.  在 License Manager 窗口中点击 **Load license** 按钮。

    .. figure:: ../img/Vivado-install/2020.1/Licence-load-licence.png
        :width: 1000
        :align: center

#.  点击 **Copy License** 按钮，导航到之前保存下载的 **.lic** 文件的位置。选择该文件并点击 **Open**。
#.  随后可以在 **View License Status** 窗口查看已安装许可证的信息，其中应列出 **ISE WebPACK 许可证**。

    .. figure:: ../img/Vivado-install/2020.1/Licence-view-licence-status.png
        :width: 1000
        :align: center

#.  现在可以在 Windows 上使用 Vivado 2020.1。你可以在开始菜单中搜索 **Vivado** 启动它，
    也可以运行安装目录中的 **vivado.bat** 文件（例如 **C:/Programs/Xilinx/Vivado/2020.1/bin/vivado.bat**）。

|


Linux
------

Linux 安装过程比 Windows 稍复杂，但仍然比较直接。下面是在 Linux 上安装 Vivado 2020.1 的步骤：

1.  首先，进入下载 *.tar.gz* 文件的目录并将其解压。

    .. code-block:: shell

        tar -xvzf <file-name>.tar.gz

#.  然后，使生成的文件可执行并运行它。

    .. code-block:: shell
        
        chmod +x ./Xilinx_Unified_2020.1_0602_1208_Lin64.bin
        sudo ./Xilinx_Unified_2020.1_0602_1208_Lin64.bin

#.  由于 Vivado 2020.1 不支持 Ubuntu 20.04 及更高版本，安装过程中会弹出警告并阻止安装继续进行。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-linux-warning1.png
        :width: 1000
        :align: center


#.  点击 **OK** 后，安装程序窗口还会出现异常并消失，此时必须在终端按 **Ctrl+C** 强制退出安装过程。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-linux-warning2.png
        :width: 1000
        :align: center

#.  为避免这种情况，我们会在安装期间“伪造”操作系统版本。在 **/etc** 目录中找到 **os-release** 文件。
    使用文本编辑器（例如 **nano**）以超级用户身份打开该文件：

    .. code-block:: shell

       sudo nano /etc/os-release

#.  记下 **VERSION** 行（对于 Ubuntu 20.04，应为 **VERSION="20.04.6 LTS (Focal Fossa)"**）。然后将 **VERSION** 行改为：

    .. code-block:: bash

        VERSION="18.04.4 LTS (Bionic Beaver)"
        
#.  保存文件（安装完成后**务必**记得改回原值）。

    以下是不同 Ubuntu 版本的 VERSION 行速查（请参考 `Ubuntu release guide <https://documentation.ubuntu.com/project/release-team/list-of-releases/>`_）：

    * Ubuntu 18.04 - VERSION="18.04.6 LTS (Bionic Beaver)"
    * Ubuntu 20.04 - VERSION="20.04.6 LTS (Focal Fossa)"
    * Ubuntu 22.04 - VERSION="22.04.5 LTS (Jammy Jellyfish)"
    * Ubuntu 24.04 - VERSION="24.04.3 LTS (Noble Numbat)"

#.  编辑后的文件应如下所示：

    .. figure:: ../img/Vivado-installer-linux-warning3.png
        :width: 1000
        :align: center

    |

    .. note::

        如果 Ubuntu 在操作系统版本被“伪造”期间安装软件包，可能会导致系统问题。要修复此问题，请尝试执行以下命令：

        .. code-block:: shell

            sudo apt-get install --reinstall base-files

#.  重新启动安装过程。

    .. code-block:: shell
        
        sudo ./Xilinx_Unified_2020.1_0602_1208_Lin64.bin

#.  安装程序启动后，会弹出两个窗口，提示安装程序无法访问服务器。请关闭这两个窗口。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-1.png
        :width: 600

#.  第一个界面显示安装要求。仔细查看可发现，它说明仅支持 Windows 10，但在 Windows 11 上也可以安装运行。点击 **Next** 继续。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-2.png
        :width: 1000
        :align: center

#.  勾选所有许可证协议复选框，然后点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-3.png
        :width: 1000
        :align: center

#.  选择 **Vivado**，因为我们只安装 Vivado 编程环境，而不是完整的 Vitis。然后点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-4.png
        :width: 1000
        :align: center

#.  选择 **Vivado HL WebPACK**，因为我们将使用免费的 Vivado 版本。点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-5.png
        :width: 1000
        :align: center

#.  下一个界面显示安装选项。勾选下图所示的所有复选框，然后点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-6.png
        :width: 1000
        :align: center

#.  现在需要选择安装目录。默认安装目录为 **/opt/Xilinx**，如有需要也可以更改为其他目录。
    本教程使用默认目录。点击 **Next**。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-7.png
        :width: 1000
        :align: center

#.  检查安装摘要，然后点击 **Install** 开始安装。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-8.png
        :width: 1000
        :align: center

#.  等待安装完成。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-9.png
        :width: 1000
        :align: center

#.  安装完成后会看到以下界面。点击 **OK** 结束安装过程。

    .. figure:: ../img/Vivado-install/2020.1/Vivado-installer-10.png
        :width: 1000
        :align: center

#.  将 **os-release** 文件中的 **VERSION** 恢复为原始值。

    .. code-block:: shell

       sudo nano /etc/os-release

    以下是不同 Ubuntu 版本的 VERSION 行速查（请参考 `Ubuntu release guide <https://documentation.ubuntu.com/project/release-team/list-of-releases/>`_）：

    * Ubuntu 18.04 - VERSION="18.04.6 LTS (Bionic Beaver)"
    * Ubuntu 20.04 - VERSION="20.04.6 LTS (Focal Fossa)"
    * Ubuntu 22.04 - VERSION="22.04.5 LTS (Jammy Jellyfish)"
    * Ubuntu 24.04 - VERSION="24.04.3 LTS (Noble Numbat)"

#.  启动 Vivado IDE 前，需要安装一些额外库。打开终端并运行以下命令：

    .. code-block:: shell

        sudo apt-get install libxft2 libxft2:i386

    .. note::

        如果运行的是 32 位系统，*libxft2:i386* 库将无法安装（*Unable to locate package libxft2:i386*）。解决方法是安装 *libxft2*，
        我们已经完成了这一步。

#.  现在安装 **ISE WebPACK licence**。这是一个免费许可证，可用于 Vivado 编程环境。按下图所示从 Vivado 打开 **License Manager**。

    .. figure:: ../img/Vivado-install/2020.1/Licence-open-manager.png
        :width: 1000
        :align: center
    
#.  在 License Manager 窗口中点击 **Load license** 按钮。

    .. figure:: ../img/Vivado-install/2020.1/Licence-load-licence.png
        :width: 1000
        :align: center

#.  点击 **Copy License** 按钮，前往此前下载的 **.lic** 文件保存位置。选择该文件并点击 **Open**。

#.  随后可在 **View License Status** 窗口中查看已安装许可证的信息，其中应列出 **ISE WebPACK licence**。

    .. figure:: ../img/Vivado-install/2020.1/Licence-view-licence-status.png
        :width: 1000
        :align: center

#.  接下来将 Vivado 设置文件加入系统路径。打开终端并运行以下命令：

    .. code-block:: shell

       echo 'source /opt/Xilinx/Vivado/2020.1/settings64.sh' >> ~/.bashrc
       source ~/.bashrc

#.  最后检查 Ubuntu/Linux 计算机的 *Language and Region settings*，确保 **Format** 使用 **点号（“.”）作为小数分隔符**（英国或美国格式均可）。
    **Vivado 要求使用点号作为小数分隔符**，否则 Vivado 可能无法识别模型的某些部分，从而导致 bitstream 生成问题。

#.  现在可以在 Linux 上使用 Vivado 2020.1 了。

|

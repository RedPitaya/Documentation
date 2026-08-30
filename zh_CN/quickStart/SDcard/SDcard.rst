.. _prepareSD:

###############
准备 SD 卡
###############

本节介绍如何在 SD 卡上安装或更新 Red Pitaya OS。

.. contents::
    :local:
    :backlinks: none
    :depth: 1


*******************
安装步骤
*******************

按照以下步骤在 SD 卡上安装 Red Pitaya OS：

1.  **下载最新的 Red Pitaya OS 3.00 镜像**：

    * :download:`最新稳定版（3.00-57） <https://downloads.redpitaya.com/downloads/Unify/RedPitaya_OS_3.00-57_stable.img.zip>` — |CHANGELOG| （解压后 MD5：930574230e45249e1cd23d735e93ca3a）。

    .. note::

        最新 Red Pitaya OS 版本（2.00 及更高版本）适用于所有 Red Pitaya 板卡型号。

    .. figure:: img/microSDcard-RP.png
        :width: 200

#.  **将镜像写入 SD 卡**：使用磁盘镜像写入工具将镜像写入 SD 卡。推荐使用 |balenaEtcher|。安装说明：

    * :ref:`Windows <windows_gui>`
    * :ref:`Linux <linux_gui>`
    * :ref:`macOS <macos_gui>`

#.  **将 SD 卡插入 Red Pitaya**。

    .. figure:: img/pitaya-quick-start-insert-sd-card.png
        :align: center
        :width: 400

#.  **连接电源和以太网线**，并检查启动期间的状态 LED 顺序。如果发现任何异常行为，请查看 :ref:`常见问题故障排除章节 <faq>`。

    .. raw:: html

        <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;">
            <iframe src="https://www.youtube.com/embed/9xZCAkXAkw8" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
        </div>

    .. note::

        **（OS 2.07-43 及更高版本）** 将 OS 写入 SD 卡后的首次启动过程中，存储卡分区会自动调整大小，以使用卡的全部容量。为完成此过程，板卡会再次重启，因此首次启动时间会略有增加。

#.  **通过 Web 界面连接板卡**。详细信息请查看 :ref:`快速入门说明 <quickstart_connect>`。
#.  **在主要软件版本之间更新时** （例如从 1.04 更新到 2.00），请将校准参数重置为 **Factory Default** （或 :ref:`重新校准 Red Pitaya <calibration_app>`）。


.. note::

    有关旧版 OS、每夜构建版、命令行安装及其他高级主题，请参阅 :ref:`SD 卡高级指南 <sdcard_advanced>`。

.. note::

    如需查看更新 OS 的所有方式，请参阅 :ref:`更新 Red Pitaya OS <os_update>` 章节。

|

*******************************************************
Windows、Linux 和 macOS 安装说明
*******************************************************

请选择你的操作系统，以查看将 Red Pitaya OS 镜像写入 SD 卡的具体说明。

.. note::

    所有 OS 版本的安装过程相同。推荐使用 |balenaEtcher|，因为它支持所有平台且操作简单。



.. _windows_gui:

=======
Windows
=======

#.  **将 SD 卡插入 PC 或 SD 读卡器**。

    .. figure:: img/SDcard_insert.jpg
        :align: center
        :width: 600

#.  **下载** 并安装 |balenaEtcher|。

#.  **打开 Balena Etcher 应用程序**。

    .. figure:: img/SDcard_Win_BalenaEtcher.png
        :align: center
        :width: 160

#.  **Flash from file**：选择已下载的 Red Pitaya 镜像文件（Balena Etcher 同时支持压缩文件和解压后的文件）。

    .. figure:: img/SDcard_Win_BalEtc_FlashFromFile.png
        :align: center
        :width: 800

#.  **Select target**：选择 SD 卡的驱动器号。Balena Etcher 只会显示外部驱动器。

    .. figure:: img/SDcard_Win_BalEtc_SelectTarget.png
        :align: center
        :width: 800

    .. note::

        Balena Etcher 只会显示外部驱动器，但如果计算机中插入了多张存储卡或多个 USB 设备，请务必仔细选择正确的驱动器。
        如果选错，所选驱动器上的数据可能会被擦除。可以在 Windows 资源管理器的左栏中轻松查看驱动器号（例如 E:）。

    .. figure:: img/SDcard_Win_BalEtc_SelectTarget2.png
        :align: center
        :width: 800

#.  **Flash**：点击 **Flash** 后，计算机会提示是否允许此操作。点击 **yes**，等待写入和验证完成。

    .. figure:: img/SDcard_Win_BalEtc_Flash.png
        :align: center
        :width: 800

#.  **关闭 Balena Etcher**。

    .. figure:: img/SDcard_Win_BalEtc_FlashComplete.png
        :align: center
        :width: 800

|

.. _linux_gui:

=====
Linux
=====

.. note::

    建议在 Linux 上使用 |balenaEtcher|。请按照与 :ref:`Windows <windows_gui>` 相同的说明操作。

也可以使用内置的 Image Writer 工具：

#.  **打开解压后的 SD 卡镜像**：右键点击解压后的 SD 卡镜像，选择 **Open With > Disk Image Writer**。

    .. figure:: img/DIW_1.png
        :align: center
        :width: 800

#.  **选择 SD 卡**：在 **Restore Disk Image** 窗口的 **Destination** 下拉菜单中选择 SD 卡。

    .. note::

        请仔细选择正确的设备；可通过容量判断，例如 16 GB SD 卡。

    .. figure:: img/DIW_3.png
        :align: center
        :width: 800

#.  **确认选择**：系统会要求确认选择并输入密码。

.. note::

    有关使用 ``dd`` 进行命令行安装及其他高级选项，请参阅 :ref:`SD 卡高级指南 <sdcard_advanced>`。

|

.. _macos_gui:

=====
macOS
=====

.. note::

    建议在 macOS 上使用 |balenaEtcher|。请按照与 :ref:`Windows <windows_gui>` 相同的说明操作。

也可以使用 ApplePi-Baker：

#.  将 **SD 卡插入** PC 或 SD 读卡器。

    .. figure:: img/SDcard_insert.jpg
        :align: center
        :width: 600

#.  **下载** |ApplePi-Baker|。

#.  **打开 ApplePi-Baker**，并在提示时输入管理员密码。

#.  根据容量识别并 **选择 SD 卡驱动器**。

    .. figure:: img/SDcard_macOS_ApplePi-Baker_drive.png
        :align: center
        :width: 1000

#.  **选择 Red Pitaya OS 镜像文件**：选择已下载的 Red Pitaya 镜像文件，等待写入过程完成。

    .. figure:: img/SDcard_macOS_ApplePi-Baker_image.png
        :align: center
        :width: 1000

.. note::

    有关使用 ``dd`` 进行命令行安装及其他高级选项，请参阅 :ref:`SD 卡高级指南 <sdcard_advanced>`。





.. substitutions

.. |CHANGELOG| replace:: :rp-github:`CHANGELOG <RedPitaya/blob/master/CHANGELOG.md>`

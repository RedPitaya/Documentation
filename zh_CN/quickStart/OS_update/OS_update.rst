
.. _os_update:

########################
更新 Red Pitaya OS
########################

可以通过以下方式升级 Red Pitaya OS：

1. 使用 **软件更新管理器** 应用程序。在 Web 主界面中点击右下角的 **生态系统版本标签**，或打开 **System** 菜单，即可访问该应用程序。
   使用软件更新管理器更新操作系统的方法见 :ref:`software_update_manager` 章节。

    * 此方法要求 Red Pitaya 板卡能够连接互联网。有关如何将 Red Pitaya 板卡连接到互联网的详细信息，请参阅 :ref:`网络管理器 <network_manager>` 章节。
    * 此方法只能升级生态系统版本，不能升级 Linux 版本。

    .. figure:: img/OS_update_app_menu.png
        :width: 600

#. **手动更新 OS**：从 Red Pitaya 网站下载最新的 SD 卡镜像，并将其写入 SD 卡。手动更新 OS 的方法见 :ref:`准备 SD 卡 <prepareSD>` 章节。

#. 可以使用 **Updater 命令行工具** 自动更新 **每夜构建版** 生态系统。有关 Updater 命令行工具的详细用法，请参阅 :ref:`生态系统更新实用程序 <update_util>` 章节。

我们建议 :ref:`手动更新操作系统 <prepareSD>`，因为不同的正式 OS 版本之间经常会更换 Linux 操作系统版本。

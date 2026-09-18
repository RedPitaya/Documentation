.. _sdcard_advanced:

#############################
SD 卡高级指南
#############################

本节介绍 SD 卡的高级信息，包括旧版 OS、每夜构建版、命令行安装方法、分区结构以及手动升级流程。

.. contents::
    :local:
    :backlinks: top
    :depth: 2


.. note::

    基本安装说明请参阅 :ref:`准备 SD 卡 <prepareSD>`。


***********
OS 版本
***********

OS 版本按从新到旧的顺序列出。每个版本都包含镜像下载链接（用于下载 OS 镜像）和变更日志链接（列出该 OS 的主要变更）。

===============
最新 OS
===============

.. note::

    *一个 OS，适用于所有板卡*。
    最新 OS 版本（2.00 及更高版本）适用于所有 Red Pitaya 板卡型号。

**Red Pitaya OS 3.0** ：

* :download:`最新稳定版（3.00-57） <https://downloads.redpitaya.com/downloads/Unify/RedPitaya_OS_3.00-57_stable.img.zip>` — |CHANGELOG| （解压后 MD5：930574230e45249e1cd23d735e93ca3a）。


**Red Pitaya OS 2.0** ：

* :download:`2.07-48 <https://downloads.redpitaya.com/downloads/Unify/RedPitaya_OS_2.07-48_stable.img.zip>` — |CHANGELOG| （解压后 MD5：5d02710fd87a71b4c049ffa5105b69e5）。

旧版本可在 |download_os_old| 中找到。

.. |download_os_old| replace:: :rp-download:`此处 <downloads/Unify/old>`

.. note::

    如果从 1.04 或更旧的 OS 镜像升级后运行 2.00 或更高版本 OS 时遇到问题，请查看 |this GitHub solution|。其他问题请联系 |SUPPORT TEAM|。

.. note::

    从 1.04 或更旧版本升级到 2.00 或更高版本（或从 2.00 或更新版本降级到 1.04 或更旧版本）时，必须将校准参数恢复出厂设置。请打开 Red Pitaya Web 界面，进入 **System => Calibration => Manual DC calibration**。点击 **Reset**，选择 **Factory** 并确认重置。有关校准的更多详情，请参阅 :ref:`校准应用 <calibration_app>`。


=========
1.04 OS
=========

**1.04 OS 版本与板卡型号相关** 。请仅下载与板卡类型兼容的版本。

下面的视频介绍如何识别 Red Pitaya 板卡型号，并将 1.04 或更旧版本 OS 安装到 SD 卡。

.. raw:: html

    <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;">
        <iframe src="https://www.youtube.com/embed/Qq_YRv2nk3c" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
    </div>


**STEMlab 125-14 和 STEMlab 125-10** ：

* :download:`1.04-28 <https://downloads.redpitaya.com/downloads/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-28_beta.img.zip>` — |CHANGELOG| （压缩包 MD5：92e14e68d27e63568fb87954239e9fb0）。
* :download:`1.04-18 <https://downloads.redpitaya.com/downloads/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-18_stable.img.zip>` — |CHANGELOG| （压缩包 MD5：f6cde9b3264a12372873d039535e58d5）。


**STEMlab 125-14（辅助/从板）** （不推荐，请改用 2.00 版本）：

* :download:`1.04-06 <https://downloads.redpitaya.com/downloads/Streaming_slave_boards/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-6_slave_beta.img.zip>` — |CHANGELOG| （压缩包 MD5：ef928d3014d806539e4360e59b7f6a99）。


**STEMlab 125-14 Z7020** ：

* :download:`1.04-14 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020/STEMlab_125-14-Z7020_OS_1.04-14_beta.img.zip>` — |CHANGELOG| （压缩包 MD5：c740aab5d7b374924f19171e1edd3161）。
* :download:`1.04-10 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020/STEMlab_125-14-Z7020_OS_1.04-10_stable.img.zip>` — |CHANGELOG| （压缩包 MD5：3770f34e954674b0423db33ed8a3471d）。


**STEMlab 125-14 四输入版** （不推荐，请改用 2.00 版本）：

* :download:`1.04-03 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020-4CH/STEMlab_125-14-4CH_OS_1.04-3_beta.img.zip>` — |CHANGELOG_Z20_4CH| （压缩包 MD5：414c1e7572ec116657a356f3ee2000ac）。


**SDRlab 122-16** ：

* :download:`1.04-15 <https://downloads.redpitaya.com/downloads/SDRlab-122-16/SDRlab_122-16_OS_1.04-15_beta.img.zip>` — |CHANGELOG_Z20| （压缩包 MD5：ba9f8be2f19630b42ee7b56bdd1d4392）。
* :download:`1.04-11 <https://downloads.redpitaya.com/downloads/SDRlab-122-16/SDRlab_122-16_OS_1.04-11_stable.img.zip>` — |CHANGELOG_Z20| （压缩包 MD5：634cf27555d4ae8900c92833afc1ddb9）。


**SIGNALlab 250-12** ：

* :download:`1.04-30 <https://downloads.redpitaya.com/downloads/SIGNALlab-250-12/SIGNALlab_250-12_OS_1.04-30_beta.img.zip>` — |CHANGELOG_Z20_250_12| （压缩包 MD5：2acb0579dbf67a40828a9b60a59be9e8）。
* :download:`1.04-27 <https://downloads.redpitaya.com/downloads/SIGNALlab-250-12/SIGNALlab_250-12_OS_1.04-27_stable.img.zip>` — |CHANGELOG_Z20_250_12| （压缩包 MD5：40601a42fb06cf23f43aefe15d042a01）。


=================
旧版 OS
=================

数据库中的所有旧版 OS 都可在归档中找到：

* |Red Pitaya archive| — 某些镜像可能需要分别安装 ecosystem 和 Linux OS。请查看 :ref:`每夜构建版安装说明 <nightly_build_installation>`。

.. note::

    *不可能。也许归档并不完整。*

    归档中没有的 OS 镜像已经湮没在时间长河中。如果你正在寻找归档中缺失的特定 OS 或 ecosystem，建议在 |redpitaya-forum| 上向社区提问。
    也许有人仍将它保存在磁盘上。

手动升级 ecosystem 请参阅 `手动升级 ecosystem`_。


.. _nightly_builds:

==============
每夜构建版
==============

每夜构建版是即将发布的 Red Pitaya OS 开发活动快照，包含计划在正式版本中提供的最新功能和错误修复。这些构建版便于用户在新版本发布为 Beta 或稳定版之前测试自己的配置是否存在潜在问题、试用新功能，并反馈改进建议。
我们发布每夜构建版，是为了保持代码库健康，缩短修复已报告问题或实现改进建议中所提新功能的时间。
由于这些构建版是最新代码的快照，相比稳定版本，你更可能遇到问题。请将问题报告至 support@redpitaya.com，以便开发人员检查并进行必要修复。

**每夜构建版 ecosystem**：

* |nightly builds|  -  `NIGHTLY CHANGELOG <https://downloads.redpitaya.com/downloads/Unify/nightly_builds/CHANGELOG.txt>`_.


每夜构建版的安装说明见下方的 :ref:`每夜构建版安装指南 <nightly_build_installation>`。

.. note::

    这些 OS 版本属于 Alpha 发布版，可能不稳定，并可能导致配置错误或测量数据丢失。
    建议仅将其用于测试；或者仅在你报告了错误、请求了功能且技术人员明确指导你继续操作时使用。


************************************
命令行安装
************************************

对于偏好命令行工具的用户，下面提供 Linux 和 macOS 的详细说明。

.. _linux_cli:

=====
Linux
=====

.. note::

    请注意，使用 ``dd`` 工具可能会覆盖计算机上的任意分区。
    如果在下面的说明中指定了错误的设备，可能会删除 Linux 主分区。
    请务必谨慎操作。

#.  **将 SD 卡插入 PC 或 SD 读卡器。**

#.  **打开终端**，使用 ``df -h`` 检查可用磁盘。
    本例 SD 卡容量为 16 GB，设备名为 ``/dev/sdx``，分为 ``/dev/sdx1`` 和 ``/dev/sdx2`` 两个分区。
    挂载到 ``/`` 的驱动器是主驱动器，请务必不要使用它。

    .. code-block:: console

        $ df -h
        Filesystem       Size  Used   Avail  Use%  Mounted on
        /dev/sdx1        118M   27M     92M   23%  /media/somebody/CAD5-1E3D
        /dev/sdx2       15.9G 1013M   15.8G   33%  /media/somebody/7b2d3ba8-95ed-4bf4-bd67-eb52fe65df55

#.  **使用** ``umount /dev/sdxN`` **卸载 SD 卡的所有分区** （请将 N 替换为正确的数字）。

    .. code-block:: console

        $ sudo umount /dev/sdx1 /dev/sdx2

#.  **使用以下命令将镜像写入 SD 卡。** 。
    将 ``red_pitaya_image_file.img`` 替换为解压后的 Red Pitaya SD 卡镜像文件名，并将 ``/dev/device_name`` 替换为 SD 卡路径。

    .. code-block:: console

        $ sudo dd bs=1M if=red_pitaya_image_file.img of=/dev/device_name

#.  **等待进程完成。**


.. _macos_cli:

=====
macOS
=====

#.  **将 SD 卡插入 PC 或 SD 读卡器。**
#.  **打开磁盘工具**：点击 ``cmd + space``，在搜索框中输入 **Disk Utility** 并按回车。在菜单中选择 SD 卡，点击 **Erase** 按钮（注意不要误删磁盘！）。

    .. figure:: img/SDcard_macOS_DiskUtility.png
        :align: center
        :width: 1000

#.  **打开终端**：点击 ``cmd + space``，在搜索框中输入 **Terminal** 并按回车。输入 ``cd Desktop``，然后按回车。
#.  **卸载分区**，以便覆盖磁盘。在终端中输入 ``diskutil list`` 并按回车，系统将显示所有存储设备。

    .. figure:: img/Screen-Shot-2015-08-07-at-16.59.50.png
        :align: center
        :width: 800

#.  **使用以下命令卸载**：``diskutil UnmountDisk /dev/diskn``（请正确填入磁盘编号 ``n``！）

    .. figure:: img/Screen-Shot-2015-08-07-at-17.14.34.png
        :align: center
        :width: 800

#.  **将镜像写入 SD 卡**：输入 ``sudo dd bs=1m if=path_of_your_image.img of=/dev/rdiskn``。请将 ``n`` 替换为之前记录的编号。注意磁盘名之前有字母 ``r``，命令中也要使用它！

    .. figure:: img/Screen-Shot-2015-08-07-at-17.14.45.png
        :align: center
        :width: 800

#.  **等待进程完成**：输入密码，等待几分钟，直到镜像写入完成。
#.  **弹出 SD 卡**：镜像写入完成后，输入 ``diskutil eject /dev/diskn`` 并按回车。


.. _SDcard_partitions:

*************************
Red Pitaya OS 分区
*************************

SD 卡上的 Red Pitaya OS 镜像包含两个分区。从 OS 2.05-37 起，分区如下：

1.  **1 GB FAT** 包含 **ecosystem**：

    * 启动文件：FSBL、FPGA 镜像、U-Boot、Linux 内核；
    * Red Pitaya API 库和头文件；
    * Red Pitaya Web 应用、脚本和工具；
    * 定制的 Nginx Web 服务器。


2.  **约 8 GB Ext4** 包含 **Linux OS**：

    * Ubuntu/Debian OS；
    * 各种库；
    * 网络设置定制；
    * systemd 服务定制。

Red Pitaya 的大部分源代码都会编译到 ecosystem 中。因此，ecosystem 更新更频繁，以适应新功能和错误修复。ecosystem 越新，FAT 分区通常越大（最早的 Red Pitaya OS 镜像的 FAT 分区约为 128 MB）。
Linux OS 的更新频率较低。

.. note::

    通常，ecosystem 越新，FAT 分区越大。
    你可以在 |Red Pitaya archive| 中找到所有可用的 Red Pitaya OS 镜像和 Ecosystem zip 文件。

.. note::

    每个 Red Pitaya 版本的新功能、错误修复和已知错误列表见 |CHANGELOG|。


==================================
删除 SD 卡上的分区
==================================

为全新安装 Red Pitaya OS 准备 SD 卡时，有时需要删除 SD 卡上的旧分区。

.. note::

    如果 BalenaEtcher 无法将镜像写入 SD 卡（出现 *writer process ended unexpectedly* 错误），可能是 SD 卡上存在需要先删除的分区。

.. note::

    删除分区会擦除 SD 卡上的所有数据。继续操作前请务必备份重要数据。

    **选择磁盘时请务必谨慎，避免删除错误磁盘上的分区。**

Windows
--------

#.  **将 SD 卡** 插入 PC 或 SD 读卡器。
#.  **打开磁盘管理工具**：打开 **Computer Management > Disk Management** 工具。此操作需要管理员权限。

    .. figure:: img/Disk_management_delete_partitions.png
        :align: center
        :width: 800

#.  **删除分区**：右键点击 SD 卡上的每个分区，选择 **Delete Volume**。

    .. figure:: img/Disk_management_delete_volume.png
        :align: center
        :width: 800

#.  **检查 SD 卡**：删除所有分区后，SD 卡应显示为 **Unallocated**。

    .. figure:: img/Disk_management_unallocated.png
        :align: center
        :width: 800

#.  关闭 **Disk Management** 工具，并按照 :ref:`准备 SD 卡 <prepareSD>` 中的说明使用 BalenaEtcher 安装 Red Pitaya OS。

Linux
--------

#.  **插入 SD 卡**：将 SD 卡重新插入 PC 或 SD 读卡器。
#.  **列出可用磁盘**：使用 ``lsblk`` 或 ``fdisk -l`` 列出可用磁盘。
#.  **选择 SD 卡设备**：选择 SD 卡设备（例如 ``/dev/sdx``），然后使用 ``sudo fdisk /dev/sdx`` 删除所有现有分区：

    * 输入 ``d`` 并按回车删除一个分区。
    * 如果有多个分区，重复上一步，直到删除所有分区。
    * 输入 ``w`` 并按回车将更改写入磁盘，然后退出 ``fdisk``。

MACOS
--------

#.  **插入 SD 卡**：将 SD 卡重新插入 PC 或 SD 读卡器。
#.  **删除分区**：按照 `Apple 官方支持页面 <https://support.apple.com/en-gb/guide/disk-utility/dskutl14079/mac>`_ 的说明，使用 **Disk Utility** 应用删除 SD 卡上的所有现有分区。


.. _manual_ecosystem_upgrade:

****************************
手动升级 ecosystem
****************************

除了写入完整 SD 卡镜像，也可以只升级 ecosystem。
手动升级可以修复损坏的 SD 卡镜像（仅 FAT 分区损坏时），或安装与当前 Linux 版本兼容的旧版、新版或自定义 ecosystem zip 文件。

#.  从 |Red Pitaya archive| **下载 zip 文件**。
#.  **将 SD 卡插入** 读卡器。

    .. note::

        **不要** 格式化 SD 卡，因为这也会删除 Linux OS 分区。

#.  **删除 FAT 分区中的所有文件** 。使用 ``Shift + Delete``，避免将文件放入同一分区的回收站。
#.  **将 ecosystem zip 文件内容解压** 到现在为空的分区中。

如果希望保留无线设置，请不要删除以下文件：

* ``wpa_supplicant.conf``
* ``hostapd.conf``


.. _nightly_build_installation:

**********************************
每夜构建版安装指南
**********************************

.. note::

    每夜构建版每周发布数次，包含最新功能和错误修复。
    每夜构建版是 OS 的 Alpha 版本，测试不如正式发布版充分，因此可能包含错误。

如 :ref:`Red Pitaya OS 分区 <SDcard_partitions>` 章节所述，每个 Red Pitaya OS 由两个独立文件组成：

* **Linux OS** — *red_pitaya_OS-beta_<Linux OS version>.img.zip*，包含 Ubuntu OS、Red Pitaya 库等。
* **Ecosystem** — *ecosystem-<Linux OS version>-<Nightly Build ecosystem number>-<ID>.zip*，包含 Red Pitaya Web API。

正式发布的 Red Pitaya OS 将 Linux OS 和 ecosystem 合并在一个镜像文件中。对于每夜构建版（Alpha OS）的新功能开发，将二者分开更便于处理，因此每夜构建版以两个独立文件发布。

.. list-table::
    :header-rows: 1
    :widths: 20 20 40 20

    * - Red Pitaya OS
      - OS 发布日期
      - 每夜构建版（Alpha）版本
      - Linux 版本
    * - IN DEV
      -
      - NB 811 及更高版本
      - 3.00
    * - 3.00-57
      - 7.7.2026
      - NB 810 及更早版本
      - 3.00
    * - 2.07-48
      - 1.12.2025
      - NB 655 及更早版本
      - 2.07
    * - 2.07-43
      - 4.9.2025
      - NB 622 及更早版本
      - 2.07
    * - 2.05-37
      - 7.8.2024
      - NB 345 及更早版本
      - 2.05
    * - 2.04-35
      - 15.3.2024
      - NB 258 及更早版本
      - 2.04
    * - 2.00-30
      - 11.1.2024
      - NB 215 及更早版本
      - 2.03
    * - 2.00-23
      - 5.10.2023
      - NB 162 及更早版本
      - 2.01
    * - 2.00-22
      - 4.10.2023
      - NB 160 及更早版本
      - 2.01
    * - 2.00-18
      - 26.7.2023
      - NB 141 及更早版本
      - 2.00



1.  **下载每夜构建版 Ecosystem**：下载包含 `每夜构建版 Ecosystem <https://downloads.redpitaya.com/downloads/Unify/nightly_builds/>`_ 的 .zip 文件（通常选择可用编号中最大的一个）。

    * 每夜构建版（Alpha）ecosystem 的命名格式为 **ecosystem-<Linux OS version>-<Nightly build ecosystem number>-<ID>.zip**。

#.  **进入 RedPitaya 下载页面**：下载 `最新 Linux OS <https://downloads.redpitaya.com/downloads/LinuxOS/>`_。

    * Linux OS 版本的命名格式为 **red_pitaya_OS-beta_<Linux OS version>.img.zip**。

    .. note::

        确保 Linux OS 版本与所选每夜构建版（Alpha）ecosystem 文件名中列出的版本相同。

    .. note::

        请注意，**Official Red Pitaya OS != Red Pitaya Linux OS**。Linux 文件只包含 Linux，而正式发布版同时包含 ecosystem 和 Linux。
        此处我们只需要 Linux 文件。

#.  **使用 BalenaEtcher 将 Linux OS 写入 SD 卡**。由于 BalenaEtcher 会在安装过程结束时自动断开 SD 卡与计算机的连接，请将 SD 卡重新插入计算机。
#.  **将 Alpha ecosystem** 从 .zip 文件直接解压到 SD 卡（如果可能，请不要先解压到计算机上的文件夹）。
#.  **将 SD 卡插入** Red Pitaya 并通电。


**请仔细阅读本节**

解压 Alpha ecosystem 时，由于 FAT 文件系统不区分大小写，某些文件可能会被覆盖。
对于 ``CONNMARK.h`` 和 ``connmark.h`` 这样的文件，文件系统会将它们视为同一个文件，因此系统会提示你选择保留哪个文件。

.. note::

    对于正常系统运行，可以任选一个文件，因为它们 **不会影响系统运行** 。

    出于开发目的，你应当已经在使用 Linux Ubuntu 原生 OS，因此不会出现此警告。这些文件对开发至关重要，开发系统中必须同时存在每个文件的两个版本。

* 如果先将文件解压到文件夹，也会发生这种情况，但系统可能不会通知你发生了变化（该过程会自动进行）。
* 这是 FAT 文件系统不区分大小写导致的问题，因此 ``connmark.h`` 和 ``CONNMARK.h`` 等文件会被视为同一个文件。


================================
更新每夜构建版 ecosystem
================================

若只更新每夜构建版 ecosystem，可以使用 :ref:`Ecosystem 更新工具 <update_util>`，也可以按照上面 :ref:`手动升级 ecosystem <manual_ecosystem_upgrade>` 一节的说明手动更新。


**********************************
在新板卡上安装旧版 OS
**********************************

随着 2.00 OS 的推出，EEPROM 中校准参数的存储格式发生了变化，因而与旧版 OS（1.04 及更早版本）不兼容。
从 2.00 OS 降级到 1.04 或更早版本时会出现问题，因为旧版 OS 无法读取新生产板卡 EEPROM 中存储的新校准参数格式。
遗憾的是，由于 EEPROM 校准格式发生了上述变化，这一过程并不只是将旧 OS 安装到 SD 卡并运行那么简单。

.. note::

    下面介绍的流程仅适用于降级到 0.98 至 1.04 版本的 OS。

.. note::

    可以在以下 Gen 2 板卡上安装 1.04 或更早版本的 OS：

    * :ref:`STEMlab 125-14 Gen 2 <top_125_14_gen2>`
    * :ref:`STEMlab 125-14 PRO Gen 2 <top_125_14_pro_gen2>`

    其他 :ref:`Gen 2 和 TI 板卡 <dev_guide_hardware>` 需要 OS 2.07-43 或更高版本才能正常运行。

虽然我们不建议这样做，但部分用户可能出于各种原因希望降级到旧版 OS。下面是具体的分步操作指南。

    1.  **手动将最新 OS 版本安装** 到新获得的板卡上。请参阅 :ref:`快速安装说明 <prepareSD>`。
    #.  **与板卡建立 SSH 连接**，访问 Red Pitaya 的 Linux 终端。请参阅 :ref:`SSH 连接说明 <ssh>`。

        .. code-block:: shell-session

            ssh root@<red_pitaya_ip_address>

    #.  使用 :ref:`calib 命令行工具 <calib_util>` **将校准数据转换为旧格式** ：

        .. code-block:: shell-session

            calib -o

        这会将 EEPROM 用户区中的校准数据转换为旧格式。

        .. note::

            转换 **不会** 覆盖 EEPROM 中的出厂校准区。因此，通过 :ref:`calib 工具 <calib_util>` 或 :ref:`校准应用 <calibration_app>` 将校准重置为“出厂默认值”将不起作用。

    #.  **将旧版 OS 安装** 到 SD 卡并启动板卡。
    #.  **调整频率校准** （仅限 Gen 2 板卡）。



******************
调整文件系统大小
******************

.. note::

    **（OS 2.07-43 及更高版本）** 将 OS 写入 SD 卡后的首次启动过程中，存储卡分区会 **自动调整大小** ，以使用卡的全部容量。为完成此过程，板卡会再次重启，因此首次启动时间会略有增加。无需手动操作。

对于 **旧版 OS** ，文件系统分区大小受镜像中定义的大小限制（通常为 8 GB），必须手动调整大小。
要增加可用空间，请运行以下脚本：

.. code-block:: shell-session

    root@rp-f03dee:~# /opt/redpitaya/sbin/resize.sh

脚本完成后，系统会要求重启 Red Pitaya。如果一切正常，系统启动后磁盘容量会增加。可以使用以下命令检查：

.. code-block:: shell-session

    root@rp-f03dee:~# df -h


.. note::

    如果文件系统大小没有变化，请尝试手动运行以下命令：

    .. code-block:: shell-session

        root@rp-f03dee:~# sudo resize2fs /dev/mmcblk0p2




.. substitutions


.. |this GitHub solution| replace:: :rp-github:`此 GitHub 解决方案 <RedPitaya/issues/250>`

.. |SUPPORT TEAM| replace:: :rp-web:`支持团队 <contact-us>`

.. |GitHub| replace:: :rp-github:`Red Pitaya GitHub <RedPitaya>`

.. |CHANGELOG| replace:: :rp-github:`CHANGELOG <RedPitaya/blob/master/CHANGELOG.md>`

.. |CHANGELOG_Z20| replace:: :rp-github:`CHANGELOG <RedPitaya/blob/master/CHANGELOG_Z20.md>`

.. |CHANGELOG_Z20_250_12| replace:: :rp-github:`CHANGELOG <RedPitaya/blob/master/CHANGELOG_Z20_250_12.md>`

.. |CHANGELOG_Z20_4CH| replace:: :rp-github:`CHANGELOG <RedPitaya/blob/master/CHANGELOG_Z20_4CH.md>`

.. |Red Pitaya archive| replace:: :rp-download:`Red Pitaya 归档 <downloads/>`

.. |nightly builds| replace:: :rp-download:`Red Pitaya 下载 <downloads/Unify/nightly_builds/>`

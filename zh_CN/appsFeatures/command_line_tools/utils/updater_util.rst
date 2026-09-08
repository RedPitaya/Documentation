.. _update_util:

生态系统更新工具
========================

生态系统更新工具用于将 Red Pitaya 生态系统自动更新到最新 Nightly Build 版本之一。它可以在 Red Pitaya 板卡终端中运行。该工具可以访问 `Red Pitaya 下载网站 <https://downloads.redpitaya.com/downloads/>`_ 上的 Nightly Build 数据库，下载指定的 Nightly Build 生态系统版本并将其安装到板卡上。

软件要求
----------------------

* **2.07-48** Red Pitaya OS 版本或更高版本。

|

使用方法
========================

.. tabs::

    .. group-tab:: OS 版本 3.00 或更高版本

        .. code-block:: console

            root@rp-f0b1cb:~# updater
            updater Version: 3.00-809-bce7a0397

            Usage: updater -m file,file,...
                updater -d URL [-v]
                updater -n FILE [-v]
                updater -n NUMBER [-v]
                updater -i FILE [-v]
                updater -i NUMBER [-v]
                updater -l
                updater -p
                updater -a USER:PASSWORD
                updater -r
                updater -w
                updater -e

            --md5=FILES              -m FILES           Calculates md5 for the specified files.
            --download=URL           -d URL             Downloads a file to a directory: /home/redpitaya/ecosystems.
            --download_nb=FILE       -n FILE            Download ecosystem by file name from NB server.
            --download_nb=NUMBER     -n NUMBER          Download ecosystem by build number from NB server.
            --download_prod=FILE     -t FILE            Download ecosystem by file name from Prod server.
            --download_prod=NUMBER   -t NUMBER          Download ecosystem by build number from Prod server.
            --install=FILE           -i FILE            Installs the ecosystem by file name on the SD card.
            --install=NUMBER         -i NUMBER          Installs the ecosystem by build number on the SD card.
            --list                   -l                 List of loaded ecosystems.
            --list_nb                -r                 List of ecosystems on the server in the NB folder.
            --list_prod              -p                 List of ecosystems on the server in the Production folder.
            --auth                   -a USER:PASSWORD   Login and password.
            --verbose                -v                 Produce verbose output.
            --webcontrol             -w                 Starts websocket control mode.
            --last                   -e                 Downloads and installs the latest version from NB.

    .. group-tab:: OS 版本 2.00

        .. code-block:: console

            root@rp-f0a235:~# updater
            updater Version: 2.07-501-e1eff7e0a

            Usage: updater -m file,file,...
                updater -d URL [-v]
                updater -n FILE [-v]
                updater -n NUMBER [-v]
                updater -i FILE [-v]
                updater -i NUMBER [-v]
                updater -l
                updater -r

            --md5=FILES           -m FILES     Calculates md5 for the specified files.
            --download=URL        -d URL       Downloads a file to a directory: /home/redpitaya/ecosystems.
            --download_nb=FILE    -n FILE      Download ecosystem by file name from NB server.
            --download_nb=NUMBER  -n NUMBER    Download ecosystem by build number from NB server.
            --install=FILE        -i FILE      Installs the ecosystem by file name on the SD card.
            --install=NUMBER      -i NUMBER    Installs the ecosystem by build number on the SD card.
            --list                -l           List of loaded ecosystems.
            --list_nb             -r           List of ecosystems on the server in the NB folder.
            --verbose             -v           Produce verbose output.

使用更新工具的步骤如下：

#.  使用 **-r** 选项列出服务器上的生态系统。程序会自动检查文件与归档内容，并比较 MD5 校验和。
    列表会根据 MD5 校验和显示文件名及其状态（``OK`` 或 ``BROKEN``）。

#.  使用 **-n** 选项从 Nightly Build 服务器下载生态系统。可以指定文件名，也可以使用构建编号（例如 495）。下载的文件将保存到 **/home/redpitaya/ecosystems** 目录。
    另外，如果 Red Pitaya 无法访问互联网，可以从 Nightly Build 服务器下载文件，将其传输到 Red Pitaya，再复制到 **/home/redpitaya/ecosystems** 目录。

#.  使用 **-l** 选项列出本地可用的生态系统。列表会显示文件名及其状态（``OK`` 或 ``BROKEN``）。

#.  使用 **-i** 选项安装下载的生态系统。可以指定文件名，也可以使用构建编号（例如 495）。

#.  重启 Red Pitaya 板卡以应用更改。

.. note::

    某些 Nightly Build 生态系统还需要更新 Red Pitaya Linux OS。
    生态系统更新工具无法更新 Red Pitaya Linux 版本。要更新 Linux 版本，请遵循 :ref:`准备 SD 卡 <prepareSD>` 部分的说明。

|

使用示例
----------------

从 Nightly Build 服务器下载生态系统：

.. code-block:: console

    root@rp-f0f0f1:~# updater -n 400 -v
    [==================================================] 100.0% (4.7 MB/s)

    File downloaded: ecosystem-2.05-400-2e2b7a22c.zip

列出服务器上的生态系统：

.. code-block:: console

    root@rp-f0f0f1:~# updater -l
    ecosystem-2.05-400-2e2b7a22c.zip    [BROKEN]
    ecosystem-2.07-495-58e93bf58.zip    [OK]
    ecosystem-2.07-493-d5436699b.zip    [OK]

安装下载的生态系统：

.. code-block:: console

    root@rp-f0f0f1:~# updater -i 495 -v
    Unzip   [==================================================] 100.0% (5009/5009)
    Install [==================================================] 100.0% (5009/5009)
    The board needs to be rebooted.

|

更新生态系统和 Red Pitaya Linux OS 的其他方式
------------------------------------------------------------

.. include:: ../../../quickStart/OS_update/OS_update_options.inc

|

源代码
------------

Red Pitaya GitHub 仓库包含 :rp-github:`生态系统更新工具的源代码 <RedPitaya/tree/master/tools/updater>`。

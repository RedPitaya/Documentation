.. _remote_software_delpoy:

###########################
远程软件部署
###########################

:ref:`软件更新管理器 <software_update_manager>` 可以配置为从用户定义的服务器上传自定义软件。

要实现此功能，需要修改 Red Pitaya GitHub 中的以下两个文件，将其中的 Red Pitaya 下载服务器

.. code-block::
  
    http://downloads.redpitaya.com/downloads/$1
  
替换为用户定义的服务器地址。

* |list.sh|
* |download.sh|

.. |list.sh| replace:: :rp-github:`list.sh <RedPitaya/blob/master/apps-tools/updater/scripts/list.sh>`

.. |download.sh| replace:: :rp-github:`download.sh <RedPitaya/blob/master/apps-tools/updater/scripts/download.sh>`

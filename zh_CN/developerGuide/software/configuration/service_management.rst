.. _service_management:

####################
服务管理
####################

Red Pitaya 使用 systemd 管理后台服务。本指南介绍如何控制系统服务，可用于优化性能、排查问题和定制系统行为。

.. contents:: 目录
    :local:
    :backlinks: top

|

概述
*********

Red Pitaya 运行多个提供不同功能的后台服务。了解如何管理这些服务后，您可以：

* 针对特定任务优化系统性能
* 排查与服务相关的问题
* 定制启动时运行的服务
* 在需要时释放系统资源

|

Red Pitaya 服务
********************

Red Pitaya 的主要系统服务包括：

.. list-table::
    :widths: 30 70
    :header-rows: 1

    * - 服务名称
      - 描述
    * - ``redpitaya_nginx``
      - 为 Red Pitaya Web 界面和应用定制的 Nginx Web 服务器
    * - ``redpitaya_e3_controller``
      - 检测 E3 插槽是否连接外部板卡的服务（仅在 PRO Gen 2 板卡上启用）
    * - ``redpitaya_startup``
      - 运行 Red Pitaya 启动脚本的服务
    * - ``redpitaya_scpi``
      - Red Pitaya SCPI 服务器

.. note::

    要查看所有已安装的 Red Pitaya 服务（包括非活动服务），请使用：
    
    .. code-block:: bash
    
        systemctl list-units "redpitaya*" --no-pager --all

有关其他系统服务及详细信息，请参阅 :ref:`构建 Red Pitaya OS <SW_build_os>` 文档。

.. important::

    **Web 界面（Nginx）与 SCPI 服务器互斥**
    
    ``redpitaya_nginx`` Web 界面和 SCPI 服务器（``/opt/redpitaya/bin/monitor``）不能同时运行。两者访问相同的硬件资源，会造成冲突。
    
    * **启动 SCPI 之前：** 使用 ``systemctl stop redpitaya_nginx`` 停止 Nginx 服务
    * **启动 Web 界面之前：** 使用 ``systemctl stop redpitaya_scpi`` 停止所有正在运行的 SCPI 服务器实例
    
    更多详情请参阅 :ref:`SCPI 服务器文档 <scpi_commands>`。

|

基本服务命令
***********************

所有服务管理命令都需要通过 SSH 访问 Red Pitaya。连接说明请参阅 :ref:`SSH 访问 <ssh>`。

启动服务
================

立即启动服务：

.. code-block:: bash

    systemctl start <service_name>

示例：

.. code-block:: bash

    systemctl start redpitaya_nginx

服务会立即启动，但除非已启用，否则下次启动时不会自动启动。

|

停止服务
===============

立即停止正在运行的服务：

.. code-block:: bash

    systemctl stop <service_name>

示例：

.. code-block:: bash

    systemctl stop redpitaya_nginx

服务会立即停止，但如果已启用，下次启动时可能会重新启动。

|

启用开机启动服务
=======================

配置服务，使其在启动时自动运行：

.. code-block:: bash

    systemctl enable <service_name>

示例：

.. code-block:: bash

    systemctl enable redpitaya_scpi

.. note::

    此命令只配置启动行为。若还要立即启动服务：
    
    .. code-block:: bash
    
        systemctl enable redpitaya_nginx
        systemctl start redpitaya_nginx

|

禁用开机启动服务
=========================

阻止服务在启动时自动运行：

.. code-block:: bash

    systemctl disable <service_name>

示例：

.. code-block:: bash

    systemctl disable redpitaya_nginx

.. note::

    此命令只影响启动行为。若还要停止当前正在运行的服务：
    
    .. code-block:: bash
    
        systemctl disable redpitaya_nginx
        systemctl stop redpitaya_nginx

|

检查服务状态
=====================

查看服务当前状态：

.. code-block:: bash

    systemctl status <service_name>

正在运行的服务示例输出：

.. code-block:: text

    ● redpitaya_nginx.service - Red Pitaya Nginx Web Server
         Loaded: loaded (/etc/systemd/system/redpitaya_nginx.service; enabled)
         Active: active (running) since Wed 2026-02-05 10:23:15 UTC; 2h ago
       Main PID: 1234 (nginx)
          Tasks: 5
         Memory: 12.3M
         CGroup: /system.slice/redpitaya_nginx.service

已停止服务的示例输出：

.. code-block:: text

    ● redpitaya_nginx.service - Red Pitaya Nginx Web Server
         Loaded: loaded (/etc/systemd/system/redpitaya_nginx.service; disabled)
         Active: inactive (dead)

按 ``q`` 退出状态视图。

|

重启服务
==================

重启服务（先停止再启动）：

.. code-block:: bash

    systemctl restart <service_name>

修改配置后或需要清除服务状态问题时，这一命令很有用。

|

列出所有服务
==================

查看所有 Red Pitaya 服务及其状态：

.. code-block:: bash

    systemctl list-units "redpitaya*" --no-pager

示例输出：

.. code-block:: text

    UNIT                            LOAD   ACTIVE   SUB     DESCRIPTION
    redpitaya_e3_controller.service loaded inactive dead    Service for an application that detects...
    redpitaya_nginx.service         loaded active   running Customized Nginx web server for Red Pitaya...
    redpitaya_startup.service       loaded inactive dead    Service for startup script Red Pitaya
    redpitaya_scpi.service          loaded inactive dead    SCPI server for Red Pitaya

|

常见使用场景
*****************

为提升性能禁用 Web 界面
=======================================

运行性能关键型应用（例如高速流式传输）时，可以禁用 Web 界面以释放资源：

.. code-block:: bash

    systemctl stop redpitaya_nginx
    systemctl disable redpitaya_nginx

恢复 Web 界面：

.. code-block:: bash

    systemctl enable redpitaya_nginx
    systemctl start redpitaya_nginx

**使用场景：** 
* 高速数据流式传输（:ref:`参见流式传输优化 <streaming_performance_optimization>`）
* CPU 密集型信号处理
* 尽量减少网络带宽占用

|

手动运行 SCPI 服务器
==============================

如果需要 :ref:`SCPI 命令 <scpi_commands>` 访问，可以在终端中手动启动 SCPI 服务器。

.. warning::

    **SCPI 服务器和 Nginx Web 界面不能同时运行。** 两者访问相同的硬件资源，会造成冲突。

临时使用 SCPI 时，请停止 Web 界面（下次启动时会重新启动）：

.. code-block:: bash

    systemctl stop redpitaya_nginx
    /opt/redpitaya/bin/monitor &

``&`` 会在后台运行命令，因此可以继续使用终端。

.. note::

    如果希望 SCPI 在启动时自动运行而不是启动 Web 界面，请参阅 SCPI 文档中的 :ref:`启动时运行 SCPI 服务器 <scpi_boot_time>`。

**使用场景：**
* 通过 :ref:`SCPI 命令 <scpi_commands>` 远程控制仪器
* 自动化测试与测量
* 与测试设备集成

完整的 SCPI 设置、命令参考和示例请参阅 :ref:`SCPI 服务器文档 <scpi_commands>`。

|

启动时运行自定义命令
=================================

启动脚本（``/opt/redpitaya/sbin/startup.sh``）可用于在每次启动时运行自定义命令。这适用于需要在系统启动后执行、但不应作为 systemd 服务管理的任务。

.. note::

    **使用 `enable`/`disable` 进行永久服务配置**
    
    要永久阻止服务在启动时运行，只需运行一次 ``systemctl disable <service_name>``。此配置会在重启后保持，无需使用启动脚本。
    
    启动脚本用于运行需要在启动时执行的命令，而不是管理服务的启用/禁用状态。

**示例场景：** 在启动时自动运行 SCPI 服务器

1. 编辑启动脚本：

   .. code-block:: bash

       nano /opt/redpitaya/sbin/startup.sh

2. 在文件末尾添加命令：

   .. code-block:: bash

       # Start SCPI server automatically
       /opt/redpitaya/bin/monitor &

3. 保存并退出（``Ctrl+X``、``Y``、``Enter``）

这些命令会在每次启动时自动运行。

|

故障排查
****************

服务无法启动
====================

如果服务启动失败：

1. 检查服务状态中的错误消息：

   .. code-block:: bash

       systemctl status <service_name>

2. 查看详细日志：

   .. code-block:: bash

       journalctl -u <service_name> -n 50

3. 检查是否已有其他实例在运行：

   .. code-block:: bash

       ps aux | grep <service_name>

|

服务持续重启
=========================

如果服务停止后自动重启，可能配置了自动重启：

1. 检查服务配置：

   .. code-block:: bash

       systemctl cat <service_name>

2. 在服务文件中查找 ``Restart=`` 设置

3. 禁用服务以阻止自动重启：

   .. code-block:: bash

       systemctl disable <service_name>
       systemctl stop <service_name>

|

重启后更改未保留
====================================

如果服务状态未保留：

1. 确认使用的是 ``enable``/``disable`` 命令，而不只是 ``start``/``stop``

2. 验证更改是否生效：

   .. code-block:: bash

       systemctl is-enabled <service_name>

|

相关主题
***************

* :ref:`SSH 访问 <ssh>` - 服务管理所需
* :ref:`构建 Red Pitaya OS <SW_build_os>` - 完整服务列表和 systemd 详情
* :ref:`流式传输性能优化 <streaming_performance_optimization>` - 针对流式传输的服务优化
* :ref:`网络配置 <sw_network>` - 网络服务配置

|

其他资源
*********************

* `systemd 文档 <https://www.freedesktop.org/software/systemd/man/systemctl.html>`_ - 官方 systemd/systemctl 参考
* :ref:`已知软件问题 <known_sw_issues>` - 常见服务相关问题
* `Red Pitaya 论坛 <https://forum.redpitaya.com>`_ - 服务问题的社区支持

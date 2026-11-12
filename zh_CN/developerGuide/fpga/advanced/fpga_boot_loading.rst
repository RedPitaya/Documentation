.. _fpga_boot_loading:

##################################
FPGA 启动加载配置
##################################

本指南介绍如何让自定义 FPGA 在 Red Pitaya 启动时自动加载。默认情况下，FPGA 配置只会持续到设备关机、复位或加载新的 FPGA 镜像为止。

.. seealso::

    **前置条件：**
    
    设置启动加载前，需要准备可正常工作的 FPGA 比特流。请参阅：
    
    - :ref:`fpga_reprogramming` - FPGA 加载基础指南
    - :ref:`fpga_advanced_loading` - 自定义 FPGA 配置

.. contents:: 目录
    :local:
    :depth: 2
    :backlinks: top

|

**********************************
了解持久性
**********************************

FPGA 配置生命周期
=============================

默认情况下，FPGA 配置会持续到以下事件之一发生：

1. 设备关机或复位
2. 加载新的 FPGA 镜像（Web 应用、界面重新加载）
3. 通过软件更改 FPGA 配置

本节介绍如何让自定义 FPGA 在启动时自动加载。

何时使用启动加载
==========================

在以下情况下可以设置自动启动加载：

- 部署带有自定义 FPGA 的生产系统
- 希望每次断电重启后都加载同一个 FPGA
- 需要在启动时保持一致的硬件配置
- 运行无需人工干预的无头系统
- 开发具有固定 FPGA 功能的专用设备

|


方法 1：使用 startup.sh 脚本（推荐）
=================================================

**startup.sh 脚本** 是 Red Pitaya 推荐的启动时运行命令的方法。该脚本在系统启动后恰好运行一次，因此非常适合加载 FPGA 和执行其他初始化任务。

.. seealso::

    有关 startup.sh 脚本以及启动时运行应用的更多详情，请参阅 :ref:`C++ 和 Python API 文档 <runApp_api>`。

为什么选择 startup.sh？
------------------------------

**优点：**

- Red Pitaya 官方推荐的方法
- 配置和维护简单
- 在系统启动时恰好运行一次
- 与其他 Red Pitaya 文档保持一致
- 易于启用/禁用
- 无需复杂的服务配置

**适用于：**

- 大多数 FPGA 启动加载场景
- 生产部署
- 快速原型设计和测试
- 希望遵循 Red Pitaya 标准实践的场景

|

基本步骤
----------------

**步骤 1：启用读写模式**

.. code-block:: bash

    redpitaya> rw

**步骤 2：复制 FPGA 文件（如有需要）**

如果 FPGA 比特流和设备树文件尚未位于 ``/opt/redpitaya`` 中，请复制它们：

.. code-block:: bash

    # Example: Copy from /root to /opt/redpitaya/fpga/<model>/my_project/
    redpitaya> mkdir -p /opt/redpitaya/fpga/$(monitor -f)/my_project
    redpitaya> cp /root/red_pitaya_top.bit.bin /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.bit.bin
    redpitaya> cp /root/devicetree.dtbo /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.dtbo

**步骤 3：编辑 startup.sh 脚本**

.. code-block:: bash

    redpitaya> nano /opt/redpitaya/sbin/startup.sh

**步骤 4：在文件末尾添加 FPGA 加载命令**

确切命令取决于 OS 版本。请将命令添加到最后一行注释**之前**：

.. tabs::

    .. group-tab:: OS 2.07-43 or newer

        .. code-block:: bash

            #!/bin/bash
            
            # ... existing startup.sh content ...
            
            # Load custom FPGA with device tree overlay
            /opt/redpitaya/sbin/overlay.sh v0.94 my_project
            
            # Here you can specify commands for autorun at system startup

    .. group-tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            #!/bin/bash
            
            # ... existing startup.sh content ...
            
            # Load custom FPGA at boot
            fpgautil -b /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.bit.bin
            
            # Here you can specify commands for autorun at system startup

    .. group-tab:: OS 1.04 or older

        .. code-block:: bash

            #!/bin/bash
            
            # ... existing startup.sh content ...
            
            # Load custom FPGA at boot
            cat /opt/redpitaya/fpga/$(monitor -f)/my_project/fpga.bit > /dev/xdevcfg
            
            # Here you can specify commands for autorun at system startup


.. note::

    对于 OS 2.07+，``overlay.sh`` 命令会自动从指定项目目录加载 FPGA 比特流（``fpga.bit.bin``）和设备树覆盖（``fpga.dtbo``）。

**步骤 5：保存文件并返回只读模式**

.. code-block:: bash

    # Press Ctrl+X, then Y, then Enter to save in nano
    redpitaya> ro

**步骤 6：重启进行测试**

.. code-block:: bash

    redpitaya> reboot

**步骤 7：验证 FPGA 已正确加载**

重启后，检查已加载的 FPGA：

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf

|

禁用或修改
----------------------

要停止在启动时加载自定义 FPGA：

**步骤 1：启用读写模式**

.. code-block:: bash

    redpitaya> rw

**步骤 2：编辑 startup.sh 脚本**

.. code-block:: bash

    redpitaya> nano /opt/redpitaya/sbin/startup.sh

**步骤 3：注释掉或删除 FPGA 加载行**

.. code-block:: bash

    #!/bin/bash
    
    # ... existing startup.sh content ...
    
    # Load custom FPGA at boot (disabled)
    # /opt/redpitaya/sbin/overlay.sh v0.94 my_project
    
    # Here you can specify commands for autorun at system startup

**步骤 4：保存并重启**

.. code-block:: bash

    redpitaya> ro
    redpitaya> reboot

|


方法 2：使用 systemd 服务（备选）
===============================================

对于偏好 systemd 服务的高级用户，可以创建一个在启动时运行的自定义服务。该方法可以更好地控制服务依赖关系和启动顺序。

.. note::

    **startup.sh 方法** （方法 1）更简单，推荐大多数用户使用。只有在需要服务依赖、重启策略或日志记录等高级功能时，才使用 systemd 服务。

何时使用 systemd
--------------------

在需要以下功能时使用 systemd 服务：

- 对启动顺序进行细粒度控制
- 服务依赖关系（在网络启动后启动等）
- 失败时自动重启
- 高级日志记录和监控
- 与其他 systemd 服务集成
- 服务级资源限制

|

创建 systemd 服务
-----------------------

**步骤 1：创建服务文件**

.. code-block:: bash

    redpitaya> rw
    redpitaya> nano /etc/systemd/system/custom-fpga.service

**步骤 2：添加服务配置**

.. tabs::

    .. group-tab:: OS 2.07-43 or newer

        .. code-block:: ini

            [Unit]
            Description=Load Custom FPGA at Boot
            After=network.target
            
            [Service]
            Type=oneshot
            ExecStart=/opt/redpitaya/sbin/overlay.sh v0.94 my_project
            RemainAfterExit=yes
            
            [Install]
            WantedBy=multi-user.target

    .. group-tab:: OS 2.00 to 2.05-37

        .. code-block:: ini

            [Unit]
            Description=Load Custom FPGA at Boot
            After=network.target
            
            [Service]
            Type=oneshot
            ExecStart=/usr/bin/fpgautil -b /root/red_pitaya_top.bit.bin
            RemainAfterExit=yes
            
            [Install]
            WantedBy=multi-user.target

    .. group-tab:: OS 1.04 or older

        .. code-block:: ini

            [Unit]
            Description=Load Custom FPGA at Boot
            After=network.target
            
            [Service]
            Type=oneshot
            ExecStart=/bin/bash -c 'cat /root/red_pitaya_top.bit > /dev/xdevcfg'
            RemainAfterExit=yes
            
            [Install]
            WantedBy=multi-user.target

**步骤 3：启用并启动服务**

.. code-block:: bash

    redpitaya> systemctl daemon-reload
    redpitaya> systemctl enable custom-fpga.service
    redpitaya> systemctl start custom-fpga.service
    redpitaya> ro

**步骤 4：验证服务状态**

.. code-block:: bash

    redpitaya> systemctl status custom-fpga.service

禁用服务
-----------

.. code-block:: bash

    redpitaya> rw
    redpitaya> systemctl disable custom-fpga.service
    redpitaya> systemctl stop custom-fpga.service
    redpitaya> ro

|


方法 3：使用 /etc/profile.d（登录方法）
==============================================

此方法会在用户通过 SSH 登录时加载 FPGA。对于启动加载，**不推荐** 使用此方法，原因如下：

- 只有有人登录时才运行（不是在系统启动时运行）
- 每次 SSH 登录都会运行（可能造成延迟）
- 可能干扰自动化脚本

**仅当** 你明确希望由用户登录触发 FPGA 加载，而不是由系统启动触发时，才使用此方法。

.. note::

    由于 Red Pitaya 会在启动时自动登录 ``root`` 用户，因此对于默认设置，此方法实际上会在启动时运行。不过，它仍会在每次登录时执行。

|

设置步骤
-----------------

**步骤 1：创建启动脚本**

.. code-block:: bash

    redpitaya> rw
    redpitaya> nano /etc/profile.d/custom_fpga.sh

**步骤 2：添加加载命令**

.. tabs::

    .. group-tab:: OS 2.07-43 or newer

        .. code-block:: bash

            #!/bin/bash
            /opt/redpitaya/sbin/overlay.sh v0.94 my_project

    .. group-tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            #!/bin/bash
            fpgautil -b /root/red_pitaya_top.bit.bin

    .. group-tab:: OS 1.04 or older

        .. code-block:: bash

            #!/bin/bash
            cat /root/red_pitaya_top.bit > /dev/xdevcfg

**步骤 3：赋予可执行权限**

.. code-block:: bash

    redpitaya> chmod +x /etc/profile.d/custom_fpga.sh
    redpitaya> ro

.. warning::

    此方法会在**每次登录**时运行，而不只是在启动时运行。这可能导致：
    
    - 活跃会话期间重新加载 FPGA
    - 登录延迟
    - 重复初始化
    
    启动加载请改用**方法 1（startup.sh）**。

|


方法 4：替换默认 FPGA 镜像（高级）
================================================

此方法会用自定义镜像覆盖默认 Red Pitaya FPGA 镜像，使其成为系统默认镜像。

.. warning::

    - 此操作会修改系统文件。请保留备份！
    - 仅适用于 OS 2.00 或更高版本
    - 需要 v0.94 行为的应用将使用你的自定义 FPGA
    - 除非确实需要系统范围替换，否则请使用方法 1

何时使用此方法
-------------------------

在以下情况下替换默认 FPGA：

- 希望所有 Red Pitaya 应用都使用自定义 FPGA
- 永远不需要标准 v0.94 项目
- 需要系统范围的 FPGA 替换
- 自定义 FPGA 保持 v0.94 寄存器兼容性

.. important::

    使用此方法后，``overlay.sh v0.94`` 等命令将加载自定义 FPGA，而不是出厂默认 FPGA。

|

替换脚本
-------------------

此脚本会自动创建备份，并安全替换默认 FPGA：

**步骤 1：创建脚本**

.. code-block:: bash

    redpitaya> nano /root/replace_fpga.sh

**步骤 2：添加脚本内容**

.. code-block:: bash

    #!/bin/bash

    BITSTREAM=$1
    MODEL=$(/opt/redpitaya/bin/monitor -f)
    PROJ=v0.94

    # Enable read-write privileges
    mount -o rw,remount /opt/redpitaya

    # Check if backup already exists
    if [ ! -f "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin" ]; then
        # Create backup of original fpga.bit.bin
        cp "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin" \
           "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin"
    fi

    if [ $# -eq 0 ]; then
        # Restore original file
        cp -f "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin" \
              "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin"
        conf="Restored original fpga.bit.bin"
    else
        # Replace with custom image
        cp -f "$(realpath $1)" \
              "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin"
        conf="fpga.bit.bin overwritten with $BITSTREAM"
    fi

    mount -o ro,remount /opt/redpitaya
    echo "$conf"

**步骤 3：赋予可执行权限**

.. code-block:: bash

    redpitaya> chmod +x /root/replace_fpga.sh

**步骤 4：替换默认 FPGA**

.. code-block:: bash

    redpitaya> ./replace_fpga.sh /root/red_pitaya_top.bit.bin

**步骤 5：重启以激活**

.. code-block:: bash

    redpitaya> reboot

|

恢复原始 FPGA
-------------------------

.. code-block:: bash

    # Run the replacement script without parameters
    redpitaya> /root/replace_fpga.sh
    
    # Reboot to activate
    redpitaya> reboot

这会恢复首次替换默认镜像时创建的备份。

|


已弃用的方法
======================

使用 /etc/rc.local（已弃用）
---------------------------------

.. warning::

    在较新的 Linux 发行版（Ubuntu 18.04+）中，**此方法已弃用**，在近期 Red Pitaya OS 版本上可能无法工作。基于 systemd 的系统默认不再启用 ``rc.local`` 服务。
    
    **请改用方法 1（startup.sh）或方法 2（systemd 服务）。**

对于仍提供 ``rc.local`` 的旧系统，可以将命令添加到 ``/etc/rc.local``：

**步骤 1：检查 rc.local 是否存在且已启用**

.. code-block:: bash

    redpitaya> systemctl status rc-local.service

如果找不到该服务或服务已禁用，请改用方法 1 或方法 2。

**步骤 2：编辑 rc.local（如可用）**

.. code-block:: bash

    redpitaya> rw
    redpitaya> nano /etc/rc.local

**步骤 3：在** ``exit 0`` **之前添加加载命令**

.. tabs::

    .. group-tab:: OS 2.07-43 or newer

        .. code-block:: bash

            #!/bin/bash
            /opt/redpitaya/sbin/overlay.sh v0.94 my_project
            exit 0

    .. group-tab:: OS 2.00 to 2.05-37

        .. code-block:: bash

            #!/bin/bash
            fpgautil -b /root/red_pitaya_top.bit.bin
            exit 0

    .. group-tab:: OS 1.04 or older

        .. code-block:: bash

            #!/bin/bash
            cat /root/red_pitaya_top.bit > /dev/xdevcfg
            exit 0

**步骤 4：赋予可执行权限**

.. code-block:: bash

    redpitaya> chmod +x /etc/rc.local
    redpitaya> ro

**步骤 5：重启进行测试**

.. code-block:: bash

    redpitaya> reboot

|


方法比较
-----------------------

.. list-table::
    :header-rows: 1
    :widths: 25 35 40

    * - 方法
      - 优点
      - 缺点
    * - startup.sh script
      - **推荐**，Red Pitaya 标准方法，简单，启动时运行一次，易于管理
      - 需要编辑文件
    * - systemd service
      - 清晰、易管理、控制能力强，支持服务依赖
      - 更复杂，需要了解 systemd
    * - /etc/profile.d
      - 易于添加/删除
      - 仅在登录时加载（不是启动时），每次登录都会运行
    * - Replace default
      - 系统范围生效，影响所有应用
      - 修改系统文件，较难恢复
    * - /etc/rc.local (deprecated)
      - 简单，单个文件
      - **已弃用**，新系统不提供

**建议：**大多数场景使用 **startup.sh 脚本（方法 1）**。只有在需要高级服务控制功能时，才使用 systemd 服务（方法 2）。

|


启动加载故障排除
===============================

FPGA 未在启动时加载
-------------------------

**检查 startup.sh 语法：**

.. code-block:: bash

    redpitaya> cat /opt/redpitaya/sbin/startup.sh
    # Look for your FPGA loading command

**手动测试命令：**

.. code-block:: bash

    # Try running the command directly
    redpitaya> /opt/redpitaya/sbin/overlay.sh v0.94 my_project
    
    # Check for errors
    echo $?

**检查文件权限：**

.. code-block:: bash

    redpitaya> ls -l /opt/redpitaya/sbin/startup.sh
    # Should be executable

**查看启动日志：**

.. code-block:: bash

    redpitaya> journalctl -b | grep -i fpga
    redpitaya> dmesg | grep -i fpga

|

服务无法启动（systemd）
-------------------------------

**检查服务状态：**

.. code-block:: bash

    redpitaya> systemctl status custom-fpga.service

**查看服务日志：**

.. code-block:: bash

    redpitaya> journalctl -u custom-fpga.service

**验证服务文件语法：**

.. code-block:: bash

    redpitaya> systemctl cat custom-fpga.service

**重新加载 systemd 配置：**

.. code-block:: bash

    redpitaya> systemctl daemon-reload

|

启动时加载了错误的 FPGA
-------------------------

**检查已加载的 FPGA：**

.. code-block:: bash

    redpitaya> cat /tmp/loaded_fpga.inf

**检查 startup.sh 是否存在冲突：**

.. code-block:: bash

    redpitaya> grep overlay.sh /opt/redpitaya/sbin/startup.sh
    # Look for multiple FPGA loading commands

**检查是否存在多个服务：**

.. code-block:: bash

    redpitaya> systemctl list-units | grep fpga

|


相关文档
======================

- :ref:`fpga_reprogramming` - FPGA 加载基础指南
- :ref:`fpga_advanced_loading` - 高级 FPGA 配置
- :ref:`C++ 和 Python API <C&Py_API>` - startup.sh 脚本详情
- :ref:`device_tree` - 设备树配置

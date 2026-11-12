.. _fpga_tutorial_configure_fpga:

####################################
教程辅助工具：configure_fpga.sh
####################################

.. warning::

    ``configure_fpga.sh`` 是一个**仅供教程使用的实用脚本**。它不属于官方 Red Pitaya 软件栈，也不支持用于生产环境。

    对于 OS 2.07-43 或更高版本上的官方 FPGA 加载，请改用 ``overlay.sh`` 脚本。完整参考请参阅 :ref:`fpga_reprogramming`。

|

概述
========

本系列教程会生成编译后的 FPGA 比特流，必须将其加载到 Red Pitaya 板卡上，才能测试和验证您的设计。官方的标准工具是 ``overlay.sh``，它负责管理设备树覆盖层，也是生产工作流的正确方式。

但是，``overlay.sh`` 要求比特流旁边存在匹配的设备树覆盖层（``.dtbo``）文件。自定义教程项目不会附带预构建的设备树覆盖层，因此直接使用 ``overlay.sh`` 需要额外步骤，这些步骤不在本教程范围内。

``configure_fpga.sh`` 通过在下一次启动或重新加载前，以 **直接替换 SD 卡上的活动 FPGA 比特流文件** 的方式解决这一问题，无需设备树覆盖层。该脚本 **不会** 修改设备树——启动时已加载的设备树（针对 v0.94 镜像）会保持活动状态。教程项目设计为与此设备树兼容，因此无需进行任何更改。这种方式以部分安全性和灵活性换取简洁性，适合开发和学习。

.. list-table:: configure_fpga.sh 与 overlay.sh 对比
    :header-rows: 1
    :widths: 30 35 35

    * - 属性
      - ``configure_fpga.sh``
      - ``overlay.sh``
    * - 用途
      - 教程开发
      - 生产环境 / 官方使用
    * - 需要设备树覆盖层
      - 否
      - 是
    * - 重启时自动恢复
      - 否（磁盘写入具有持久性）
      - 否（磁盘写入具有持久性，必须手动运行 ``overlay.sh``）
    * - 原始镜像备份
      - 是（自动创建 ``fpga_orig.*``）
      - 不适用（由 OS 管理）
    * - 自动检测板卡型号
      - 是
      - 是
    * - 自动检测 OS 版本
      - 是（读取 ``/root/.version``）
      - 是

|

工作原理
============

该脚本执行以下步骤：

1. 从 ``/root/.version`` 读取 OS 版本，以确定正确的比特流文件扩展名（OS 3.x 使用 ``.bin``，OS 2.x 使用 ``.bit.bin``）。
2. 使用 ``/opt/redpitaya/bin/monitor -f`` 自动检测板卡型号。
3. 将 FPGA 文件系统分区重新挂载为读写模式。
4. 首次运行时，将原始比特流备份为 ``fpga_orig.*``——**该备份是永久的，后续运行不会覆盖它**。
5. 用您的自定义比特流替换活动比特流文件（如果未提供比特流，则恢复原始比特流）。
6. 将分区重新挂载为只读模式。

重新对 FPGA 编程后（例如重启，或手动触发 FPGA 重新加载），新的比特流才会生效。最简单的方式是重启：

.. code-block:: bash

    reboot

|

前置条件
=============

* 运行 OS 2.00 或更高版本（2.x 或 3.x）的 Red Pitaya 板卡
* 访问 Red Pitaya 板卡的 :ref:`SSH 访问 <ssh>`
* 板卡上的 root 权限（SSH 会话默认为 root）
* 已传输到板卡上的编译后比特流（``.bin`` 或 ``.bit.bin``）

.. note::

    运行脚本前，比特流必须已经位于板卡上。使用 ``scp`` 或 Red Pitaya Web 界面传输比特流。
    请参阅 :ref:`将比特流复制到板卡 <fpga_copy_project>`。

|

用法
=====

**语法**

.. code-block:: bash

    configure_fpga.sh [-h] [BITSTREAM] [PROJ]

**参数**

.. list-table::
    :header-rows: 1
    :widths: 20 80

    * - 参数
      - 描述
    * - ``BITSTREAM``
      - 板卡上自定义比特流文件的路径。如果省略，脚本会恢复原始比特流。
    * - ``PROJ``
      - 要操作的 FPGA 项目槽位。默认为 ``v0.94``，本系列所有教程都使用该槽位。

**选项**

.. list-table::
    :header-rows: 1
    :widths: 20 80

    * - 选项
      - 描述
    * - ``-h``, ``--help``
      - 打印用法信息并退出。

|

示例
========

**加载自定义比特流（教程开发期间最常见）**

.. code-block:: bash

    configure_fpga.sh /root/my_project.bin

这会将 ``my_project.bin`` 加载到 ``v0.94`` 项目槽位。首次运行时会自动备份原始比特流。

**加载自定义比特流并显式指定项目槽位**

.. code-block:: bash

    configure_fpga.sh /root/my_project.bin v0.94

**恢复原始比特流**

.. code-block:: bash

    configure_fpga.sh

不带参数调用脚本会将 ``fpga_orig.*`` 恢复为 ``fpga.*``。这要求此前运行过脚本并已创建备份。

**打印帮助**

.. code-block:: bash

    configure_fpga.sh -h

|

恢复原始 FPGA
============================

.. warning::

    由于 ``configure_fpga.sh`` 会物理替换 SD 卡上的 ``fpga.*`` 比特流文件，运行 ``overlay.sh v0.94`` **不会** 恢复原始镜像——它只会重新加载当前磁盘上的同一个自定义比特流。``overlay.sh`` 不知道该脚本创建的备份。

有两种方式可以恢复出厂 FPGA 镜像：

1. **使用脚本** （要求已存在之前创建的备份）：

   .. code-block:: bash

       configure_fpga.sh

   这会将 ``fpga_orig.*`` 恢复为 ``fpga.*``。备份会在脚本首次运行时自动创建，且永远不会被覆盖。

2. **重新刷写 SD 卡** （始终有效，并移除所有修改）：

   如果备份文件不再存在，或者您希望获得完全干净的状态，请使用官方 OS 镜像重新刷写 SD 卡。
   相关说明请参阅 :ref:`OS update <os_update>`。

|

脚本源代码
=============

该脚本位于 Red Pitaya FPGA 教程仓库中。通过 ``scp`` 将其复制到 Red Pitaya 板卡：

.. code-block:: bash

    scp configure_fpga.sh root@<board_ip>:/root/

然后为其添加可执行权限：

.. code-block:: bash

    chmod +x /root/configure_fpga.sh

.. seealso::

    - :ref:`fpga_reprogramming` — 官方 FPGA 加载参考（``overlay.sh``、``fpgautil``）
    - :ref:`fpga_copy_project` — 如何向 Red Pitaya 板卡传输文件

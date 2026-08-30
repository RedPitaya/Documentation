
.. _troubleshooting_guide:

#########################
故障排除指南
#########################

本节介绍如何排查使用 Red Pitaya 时可能遇到的常见问题。如果你遇到的问题未在本指南中涉及，请参阅 :ref:`常见问题 <faq>` 章节，或联系我们的支持团队寻求帮助。

.. contents:: 目录
    :local:
    :depth: 2
    :backlinks: top

|


正常运行状态
================

在介绍各项故障排除步骤之前，先明确正常运行的基准状态。最简单的方法是将 Red Pitaya 的运行分为两部分：

* **板卡本身** — 板卡是由硬件和软件共同组成的物理设备。
* **网络连接** — 网络连接是 Red Pitaya 与计算机之间的连接，包括网线、路由器、交换机、其他网络设备以及计算机上的网络配置。

Red Pitaya 板卡
-----------------

可以通过板卡上的状态 LED 检查 Red Pitaya 板卡的状态。下表说明状态 LED 正常工作时的表现：

.. csv-table::
    :header: "颜色", "功能", "闪烁模式", "说明"
    :widths: 18, 22, 25, 35

    ":blue:`蓝色`", "FPGA 比特流状态", "常亮", "FPGA 比特流已成功加载。"
    ":green:`绿色`", "电源状态", "常亮", "Red Pitaya 上的所有电源均正常工作。"
    ":red:`红色`", "CPU 负载状态", "心跳模式", "CPU 正常运行。"
    ":orange:`橙色`", "SD 卡访问", "以较慢间隔偶尔闪烁", "每次闪烁对应一次 SD 卡访问。"

.. note::

    **E3 模块** — :ref:`QSPI eMMC 模块 <E3_QSPI_eMMC_module_HW>` 将橙色 LED 改接至内部看门狗定时器（该 LED 会持续闪烁）。

|

网络连接
------------------

可以使用 `.local` 地址，通过 Web 界面或 SSH 连接 Red Pitaya 板卡来检查网络连接。如果能通过任一方式连接 Red Pitaya 板卡，并且 Web 界面能够加载，则说明网络连接正常。

|

故障排除流程
==========================

至此，我们已经明确了 Red Pitaya 板卡和网络连接的正常运行状态。如果其中任一部分出现问题，请按照以下步骤进行排查。

该流程是一份逐步排查 Red Pitaya 常见问题的指南。建议按顺序执行各步骤，因为这些步骤经过安排，可帮助你高效定位并解决问题。

每个步骤分别侧重故障排除流程的不同部分：

* **步骤 1：更新 OS/固件** — 将 Red Pitaya OS 和固件更新到最新版本。
* **步骤 2：状态 LED** — 确认板卡本身是否正常运行。
* **步骤 3：网络连接** — 检查本地网络访问和连接问题。
* **步骤 4：串口控制台启动日志** — 检查启动消息并识别启动错误。
* **步骤 5：硬件连接** — 检查线缆、外部设备和板卡连接。
* **步骤 6：Web 应用程序** — 检查 Web 界面和应用程序行为。
* **步骤 7：高级故障排除** — 检查更具体的硬件和软件问题。

.. note::

    对 Red Pitaya 板卡进行故障排除时，请 **断开连接到板卡的所有设备和扩展板**。这样有助于隔离问题，并确认故障并非由外部设备或扩展板引起。

    **保持外部时钟连接** — 如果使用的是 Red Pitaya 外部时钟版本，请在故障排除过程中保持外部时钟连接。

.. toctree::
    :maxdepth: 1

    troubleshooting_guide/step1_OS
    troubleshooting_guide/step2_LEDs
    troubleshooting_guide/step3_network
    troubleshooting_guide/step4_serial_console
    troubleshooting_guide/step5_hardware
    troubleshooting_guide/step6_web_apps
    troubleshooting_guide/step7_advanced

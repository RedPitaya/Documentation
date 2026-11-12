.. _troubleshooting_network:

###############################
步骤 3：网络连接
###############################

本节介绍如何排查使用 Red Pitaya 时可能出现的网络连接问题。

.. contents:: 目录
    :local:
    :depth: 2
    :backlinks: top

|

适用条件
================

在此阶段，Red Pitaya 板卡应已上电，状态 LED 应正常工作。如果状态 LED 工作异常，请参阅 :ref:`步骤 2：检查状态 LED <troubleshooting_status_leds>` 章节。

|

逐步排查网络问题
=====================================

继续执行以下步骤前，请检查能否 :ref:`通过 Web 界面连接板卡 <quickstart_connect>`。如果无法连接 Web 界面，请按照以下步骤排查网络连接。

检查软件
---------------

1.  **使用最新版 Google Chrome**。使用最新版 Google Chrome 作为 Web 浏览器。Web 界面的某些功能在其他浏览器或较旧的 Chrome 版本中可能无法正常工作。
#.  对 ``rp-xxxxxx.local`` 网站 **禁用广告拦截器**。
#.  **禁用 VPN**，因为 VPN 可能阻止连接。
#.  **检查防火墙或防病毒软件**。某些安全工具可能会阻止 Web 界面、SSH 或本地网络发现。进入 **Network firewall** 设置，检查 Red Pitaya 是否被阻止（查找 **Resolve blocked communication** 或类似选项）。如果板卡被阻止，请允许其通过防火墙通信。
#.  如果页面只能部分打开或显示旧信息，请 **清除浏览器缓存**。

|

检查硬件
-----------------

6.  **确认线缆连接**。请参考 :ref:`连接指南 <quickstart_connect>` 中的建议。
#.  **检查以太网线和接口是否损坏**。将 Red Pitaya 使用的以太网线插入计算机并验证互联网连接。更换以太网线，或尝试路由器上的其他以太网接口。

|

检查网络基础配置
---------------------

8.  **位于同一本地网络**。确保 Red Pitaya 和计算机均连接到同一 :ref:`本地网络 <faq_connected>`。
#.  **复杂网络**。在包含多个路由器、交换机或接入点的复杂网络中，确认两个设备位于同一子网。
#.  **检查网络列表**。在 ``Command Prompt`` 或 ``Terminal`` 中使用 ``arp -a`` 命令查找 Red Pitaya 的 MAC 和 IP 地址。
#.  **Ping Red Pitaya**。分别对 Red Pitaya IP 地址和 ``rp-xxxxxx.local`` 地址使用 ``ping`` 命令。
#.  **使用 IP 地址代替 .local**。在浏览器 URL 中输入 IP 地址，而不是 ``rp-xxxxxx.local``。
#.  **访客网络与隔离**。确保计算机未连接访客网络，并检查路由器是否启用了客户端隔离或 AP 隔离。
#.  **检查网络安全限制**。某些网络可能具有阻止连接的安全限制，例如大学网络要求所有设备通过专用网页确认身份。Red Pitaya 板卡可能无法连接此类网络。请尝试连接其他网络（例如家庭网络），检查问题是否仍然存在。
#.  **将板卡连接到路由器**，不要直接连接计算机，然后重试上述步骤。计算机应通过以太网或 Wi-Fi 连接到同一路由器。

|

检查路由器设置
-----------------------

16.  确认路由器已 **启用 DHCP**。
#.  **重启路由器或清除路由器内部缓存/ARP 表**。路由器拥有用于保存客户端信息的内部缓存/ARP 表，每条记录都有特定的有效期（通常为一小时或更久），因此过期的客户端信息可能造成连接问题。这对 Red Pitaya 板卡尤其重要，因为 OS 可以即时更新，从而产生与板卡本身无关的连接问题。更新 Red Pitaya OS 后，路由器缓存中可能仍保留旧 MAC 地址。重启路由器或清除内部缓存/ARP 表可解决此问题。
#.  **检查重复 IP 地址**。如果其他设备已使用同一 IP 地址，连接可能失败或变得不稳定。
#.  **检查静态 IP 设置**。如果 Red Pitaya 或计算机使用手动 IP 地址，请确保其与网络中其他设备处于同一地址范围。
#.  **使用其他计算机和路由器**。某些网络可能具有阻止连接的安全限制，例如大学网络要求所有设备通过专用网页确认身份。

|

计算机 OS 设置
-----------------------

计算机 OS 设置阻止连接 Red Pitaya 的情况相当常见。请检查以下项目：

21. **检查网络隐私设置**。确保网络设置为 **Private** （Windows）或 **Trusted** （Linux 和 macOS）。如果网络设置为 **Public** 或 **Untrusted**，计算机可能阻止连接 Red Pitaya。这在 **直接连接** （Red Pitaya 通过以太网线直接连接计算机）时尤其常见。

    可能需要通过命令行调整这些设置（可能需要管理员权限）。以下为 Windows 11 示例：

    .. code-block:: powershell

        # Check the network profile
        Get-NetConnectionProfile

        # Change the network profile to Private
        Set-NetConnectionProfile -Name "NetworkName" -NetworkCategory Private

    .. code-block:: powershell

        PS C:\Users\localadmin> Get-NetConnectionProfile

        Name                     : Unidentified network
        InterfaceAlias           : Ethernet
        InterfaceIndex           : 3
        NetworkCategory          : Public
        DomainAuthenticationKind : None
        IPv4Connectivity         : LocalNetwork
        IPv6Connectivity         : NoTraffic

        Name                     : WifiName
        InterfaceAlias           : WiFi
        InterfaceIndex           : 22
        NetworkCategory          : Public
        DomainAuthenticationKind : None
        IPv4Connectivity         : Internet
        IPv6Connectivity         : NoTraffic

        PS C:\Users\localadmin> Set-NetConnectionProfile -InterfaceIndex 3 -NetworkCategory Private
        PS C:\Users\localadmin> Get-NetConnectionProfile


        Name                     : Unidentified network
        InterfaceAlias           : Ethernet
        InterfaceIndex           : 3
        NetworkCategory          : Private
        DomainAuthenticationKind : None
        IPv4Connectivity         : LocalNetwork
        IPv6Connectivity         : NoTraffic

        Name                     : WifiName
        InterfaceAlias           : WiFi
        InterfaceIndex           : 22
        NetworkCategory          : Public
        DomainAuthenticationKind : None
        IPv4Connectivity         : Internet
        IPv6Connectivity         : NoTraffic

#.  **确认以太网端口设置（仅 Linux 和 macOS）**。如果使用 Linux 或 macOS，且 Red Pitaya 通过以太网线直接连接计算机，请检查以太网端口的 IPv4 和 IPv6 设置是否分别设为 **DHCP** 和 **Local Only**。也可以改为通过路由器连接 Red Pitaya。
#.  **内容与隐私设置（macOS）**。如果 Mac 无法连接 Red Pitaya，可能是 **Content and privacy settings** 阻止了 WebSocket。更新设置后需要注销再重新登录。可能需要完全禁用内容与隐私设置。

    .. figure:: ../img/MAC_content_privacy.png
        :width: 800

    .. figure:: ../img/MAC_content_privacy2.png
        :width: 600

    .. figure:: ../img/MAC_content_privacy3.png
        :width: 600

#.  **确认 mDNS 和 DNS-SD 可用（仅旧版 Windows）**。

        * **Windows 10 或更高版本** 已支持 mDNS 和 DNS-SD，无需安装其他软件。
        * **Windows 7/8** 用户应安装 :rp-download:`Bonjour Print Services <tools/BonjourPSSetup.exe>`，否则无法访问 ``*.local`` 地址。

#.  **禁用网络适配器节能功能**。某些计算机会使以太网或 Wi-Fi 适配器进入睡眠状态，从而中断连接。
        
|

尝试隔离测试
-----------------------

26. **尝试其他计算机**。如有可能，尝试从同一网络中的其他计算机连接 Red Pitaya 板卡。
#. **尝试其他网络**。如有可能，尝试从其他网络连接 Red Pitaya 板卡，例如使用家庭网络代替大学网络。

|

后续步骤
============

如果已完成网络检查但问题仍然存在，请继续执行下一项故障排除步骤：

* :ref:`步骤 4：串口控制台启动日志 <troubleshooting_serial_console>`。
* 或点击本页面右下角的 **下一页** （两者会进入同一页面）。

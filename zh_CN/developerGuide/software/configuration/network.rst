.. _network:

#######
网络
#######

本节详细介绍 Red Pitaya 的网络配置，面向希望了解网络配置细节的高级用户和开发者。对于大多数用户，推荐使用 :ref:`网络管理器应用 <network_manager>` 配置网络。

.. contents:: 目录
   :local:
   :depth: 2

|

快速设置
==============

Red Pitaya 支持两种无线模式：

* **客户端模式** - 创建 ``/opt/redpitaya/wpa_supplicant.conf``。
* **接入点模式** - 创建 ``/opt/redpitaya/hostapd.conf``，并删除 ``/opt/redpitaya/wpa_supplicant.conf``。

.. note::

	切换接入点模式和客户端模式无需重启。网络管理器脚本会在更新配置文件后重启相关服务。

|

网络配置
----------------------

当前网络配置以 `systemd-networkd <https://www.freedesktop.org/software/systemd/man/latest/systemd.network.html>`_ 为基础。创建 Debian/Ubuntu SD 卡镜像时，几乎所有网络配置细节都由 bash 脚本 :rp-github:`network.sh <ubuntu/blob/main/debian/network.sh>` 完成。该脚本安装网络相关软件包，并从 Git 仓库复制网络配置文件。

选择以 ``systemd-networkd`` 为重点是任意的，但采用围绕 `systemd <https://systemd.io/>`__ 的单一方案，应能减少维护所需的工作量。

WiFi 配置的大部分复杂性来自对 WiFi 接入点模式和客户端模式之间切换的支持。

|

UDEV
====

``systemd`` 通过 `UDEV <https://www.freedesktop.org/software/systemd/man/latest/udev.html>`__ 规则提供 `可预测的网络接口名称 <https://www.freedesktop.org/wiki/Software/systemd/PredictableNetworkInterfaceNames/>`_。在本例中，内核将 USB WiFi 适配器命名为 ``wlan0``，随后 ``UDEV`` 规则 ``/lib/udev/rules.d/73-usb-net-by-mac.rules`` 使用以下规则将其重命名为 ``enx{MAC}``：

.. code-block:: shell-session

	# Use MAC based names for network interfaces which are directly or indirectly
	# on USB and have an universally administered (stable) MAC address (second bit
	# is 0).
	
	IMPORT{cmdline}="net.ifnames", ENV{net.ifnames}=="0", GOTO="usb_net_by_mac_end"
	PROGRAM="/bin/readlink /etc/udev/rules.d/80-net-setup-link.rules", RESULT=="/dev/null", GOTO="usb_net_by_mac_end"
	
	ACTION=="add", SUBSYSTEM=="net", SUBSYSTEMS=="usb", NAME=="", \
		ATTR{address}=="?[014589cd]:*", \
		IMPORT{builtin}="net_id", NAME="$env{ID_NET_NAME_MAC}"
	
	LABEL="usb_net_by_mac_end"


为了简化通用 WiFi 配置，最好无论使用哪种适配器都采用相同的接口名称。可以通过修改规则文件覆盖 ``UDEV`` 规则来实现：将修改后的规则文件放入目录 ``/etc/udev/rules.d/73-usb-net-by-mac.rules``。由于文件中的其余规则与 Red Pitaya 无关，也可以创建一个链接到 ``/dev/null`` 的覆盖文件来停用该规则。

.. code-block:: shell-session

   	# ln -s /dev/null /etc/udev/rules.d/73-usb-net-by-mac.rules

|

有线网络设置
================

有线接口 ``eth0`` 的配置文件 :rp-github:`/etc/systemd/network/wired.network <ubuntu/blob/main/debian/overlay/etc/systemd/network/wired.network>` 将其配置为使用 DHCP。

在 1.04 之前的 OS 版本中，使用 `不同的 DHCP 客户端 <https://linux.die.net/man/8/dhclient>`__，因此可以定义固定租约，在 DHCP 失败时提供备用地址。使用 ``systemd`` 集成的 DHCP 客户端无法实现这一点；可以改为设置固定地址，或使用链路本地地址（zeroconf，后文介绍）。

可以修改配置文件来选择静态 IP 地址。也可以同时使用 DHCP 提供的地址和静态地址，但这不适合作为发行版默认设置，因为可能导致 IP 地址冲突。将以下行添加到 `systemd-networkd <https://www.freedesktop.org/software/systemd/man/latest/systemd.network.html>`_ 文件即可配置固定 IP 地址。

.. code-block:: none

	[Network]
	Address=192.168.0.15/24
	Gateway=192.168.0.1

|

WiFi 客户端
===========

页面底部列出了 :ref:`支持的 USB Wi-Fi 适配器 <support_wifi_adapter>`。

列出无线接入点：

.. code-block:: shell-session

   	# iw wlan0 scan | grep SSID


将 ``wpa_supplicant.conf`` 配置文件写入 FAT 分区。可以在尖括号中提供 ``ssid`` 和 ``passphrase``。

.. code-block:: shell-session

	# rw
	$ wpa_passphrase <ssid> [passphrase] > /opt/redpitaya/wpa_supplicant.conf


重启 WPA supplicant：

.. code-block:: shell-session

    # systemctl restart wpa_supplicant@wlan0.service

|

WiFi 接入点
=================

将 `hostapd.conf <https://git.w1.fi/cgit/hostap/plain/hostapd/hostapd.conf>`_ 配置文件写入 FAT 分区；如果客户端配置文件 ``wpa_supplicant.conf`` 存在，则将其删除：

.. code-block:: shell-session

	# rw
	$ nano /opt/redpitaya/hostapd.conf
	$ rm /opt/redpitaya/wpa_supplicant.conf


重启接入点服务：

.. code-block:: shell-session

   	# systemctl restart hostapd@wlan0.service

|

.. _wireless_setup:

无线网络设置
==============

无线接口 ``wlan0`` 的配置文件为 :rp-github:`/etc/systemd/network/wireless.network <ubuntu/tree/main/debian/overlay/etc/systemd/network>`。

为支持两种模式，此文件必须链接到客户端模式配置
:rp-github:`/etc/systemd/network/wireless.network.client <ubuntu/blob/main/debian/overlay/etc/systemd/network/wireless.network.client>`
或接入点配置
:rp-github:`/etc/systemd/network/wireless.network.ap <ubuntu/blob/main/debian/overlay/etc/systemd/network/wireless.network.ap>`.
两种选项之间的切换由
:rp-github:`/etc/systemd/system/wireless-mode-ap.service <ubuntu/blob/main/debian/overlay/etc/systemd/system/wireless-mode-ap.service>`
以及
:rp-github:`/etc/systemd/system/wireless-mode-client.service <ubuntu/blob/main/debian/overlay/etc/systemd/system/wireless-mode-client.service>`
实现；这些服务必须在启动早期、其他大多数网络相关服务运行之前执行。如果没有无线配置文件，第三个服务
:rp-github:`/etc/systemd/system/wireless_adapter_up@.service <ubuntu/blob/main/debian/overlay/etc/systemd/system/wireless_adapter_up@.service>`
会将 ``wireless.network`` 链接到客户端模式，并为适配器上电，以便 ``iwlist`` 正常工作。

接口模式的选择取决于接入点配置文件 ``/opt/redpitaya/hostapd.conf`` 和客户端配置文件 ``/opt/redpitaya/wpa_supplicant.conf`` 是否存在。如果存在 ``wpa_supplicant.conf``，无论 ``hostapd.conf`` 是否存在，都会尝试使用客户端模式配置。如果仅存在 ``hostapd.conf``，则会尝试使用接入点配置。如果两个配置文件都不存在，则不会配置 WiFi。

+----------------------------+------------------------------+
| 文件                       | 说明                         |
+============================+==============================+
| ``wpa_supplicant.conf``    | 客户端配置                   |
+----------------------------+------------------------------+
| ``hostapd.conf``           | 接入点配置                   |
+----------------------------+------------------------------+

|

无线客户端设置
---------------------

无线网络几乎都使用某种加密/身份验证方案来保证安全，这由工具 `wpa_supplicant <https://w1.fi/wpa_supplicant/>`_ 处理。
`Debian Network Manager <https://wiki.debian.org/NetworkManager>`_ / `Ubuntu Network Manager <https://help.ubuntu.com/community/NetworkManager>`_ 的默认网络配置选项是 `Network Manager <https://wiki.gnome.org/Projects/NetworkManager>`_。它有时会与默认安装的 ``systemd-networkd`` 冲突，本例正是如此。在 `Debian <https://packages.debian.org/trixie/wpasupplicant>`_ / Ubuntu 中，缺少设备 `特定 @.service <https://git.w1.fi/cgit/hostap/tree/wpa_supplicant/systemd/wpa_supplicant.service.arg.in>`_ 服务，因此我们在 Git 仓库中 :rp-github:`复制了 wpa_supplicant@.service <ubuntu/blob/main/debian/overlay/etc/systemd/system/wpa_supplicant%40.service>`。

默认情况下，该服务作为 ``multi-user.target`` 的依赖安装；如果无法正常启动（例如 USB WiFi 适配器未插入），就会延迟 ``multi-user.target``。同时，适配器插入 Red Pitaya 后服务也不会自动启动。下面的修改同时解决这两个问题。

.. code-block:: shell-session

	[Install]
	-Alias=multi-user.target.wants/wpa_supplicant@%i.service
	+WantedBy=sys-subsystem-net-devices-%i.device


加密/身份验证配置文件链接到 FAT 分区，以便用户访问。因此，只需在 FAT 分区提供正确的 ``wpa_supplicant.conf`` 文件，即可启用无线客户端模式。

.. code-block:: shell-session

   	# ln -s /opt/redpitaya/wpa_supplicant.conf /etc/wpa_supplicant/wpa_supplicant.conf


可以使用 ``wpa_passphrase`` 工具创建此配置文件：

.. code-block:: shell-session

   	$ wpa_passphrase <ssid> [passphrase] > /opt/redpitaya/wpa_supplicant.conf

|

无线接入点设置
---------------------------

WiFi 接入点功能由 `hostapd <https://w1.fi/hostapd/>`__ 应用提供。由于上游版本不支持 ``wireless extensions`` API，该应用不会作为 Debian 软件包安装，而是下载、打补丁、重新编译后安装。

守护进程由 :rp-github:`hostapd@.service <ubuntu/blob/main/debian/overlay/etc/systemd/system/hostapd%40.service>` 负责启动。热插拔的实现方式与 ``wpa_supplicant@.service`` 相同。

要启用接入点模式，必须将 `hostapd.conf <https://git.w1.fi/cgit/hostap/plain/hostapd/hostapd.conf>`_ 配置文件放在 SD 卡的 FAT 分区，并删除客户端模式配置文件 ``wpa_supplicant.conf``。在 Red Pitaya shell 中，该文件显示为 ``/opt/redpitaya/hostapd.conf``。

.. code-block:: none

	interface=wlan0
	ssid=<ssid>
	driver=nl80211
	hw_mode=g
	channel=6
	macaddr_acl=0
	auth_algs=1
	ignore_broadcast_ssid=0
	wpa=2
	wpa_passphrase=<passphrase>
	wpa_key_mgmt=WPA-PSK
	wpa_pairwise=TKIP
	rsn_pairwise=CCMP


必须编辑此文件以设置所选的 ``<ssid>`` 和 ``<passphrase>``。其他设置用于当前最安全的个人加密方式。

|

无线路由器
~~~~~~~~~~~~~~~

在接入点模式下，如果有线接口已连接到本地网络，Red Pitaya 就会充当无线路由器。

在有线网络配置文件 :rp-github:`/etc/systemd/network/wired.network <ubuntu/blob/main/debian/overlay/etc/systemd/network/wired.network>` 中，有两行用于启用 IP 转发和伪装。

.. code-block:: none

	IPForward=yes
	IPMasquerade=yes


iptables 配置 :rp-github:`/etc/iptables/iptables.rules <ubuntu/blob/main/debian/overlay/etc/iptables/iptables.rules>` 由 iptables 服务 :rp-github:`/etc/systemd/system/iptables.service <ubuntu/blob/main/debian/overlay/etc/systemd/system/iptables.service>` 启用。

.. warning::
	
	**安全警告：** 此功能与默认密码结合使用可能造成严重的安全问题。由于正常使用 Red Pitaya 并不需要此功能，目前已将其禁用。

	用户可以自行启用，但应了解其中的安全影响。

|

``systemd`` 服务
====================

使用以下命令启用处理上述配置的服务。

.. code-block:: shell-session

	# enable systemd network related services
	systemctl enable systemd-networkd
	systemctl enable systemd-resolved
	systemctl enable systemd-timesyncd
	systemctl enable wpa_supplicant@wlan0.service
	systemctl enable hostapd@wlan0.service
	systemctl enable wireless-mode-client.service
	systemctl enable wireless-mode-ap.service
	systemctl enable iptables.service
	#systemctl enable wpa_supplicant@wlan0.path
	#systemctl enable hostapd@wlan0.path
	systemctl enable hostname-mac.service
	systemctl enable avahi-daemon.service
	
	# enable service for creating SSH keys on first boot
	systemctl enable ssh-reconfigure

|

DNS 解析器
============

要启用 ``systemd`` 集成的解析器，必须为 ``/etc/resolv.conf`` 创建符号链接。

.. code-block:: shell-session

   	# ln -sf /run/systemd/resolve/resolv.conf /etc/resolv.conf


也可以将默认 DNS 服务器添加到 ``*.network`` 文件中。

.. code-block:: none

	nameserver=8.8.8.8
	nameserver=8.8.4.4

|

NTP（网络时间协议）
===========================

不使用常见的 ``ntpd``，而使用轻量级的 ``systemd-timesyncd`` `SNTP <https://www.ntp.org/ntpfaq/NTP-s-def/#AEN1271>`_ 客户端。由于默认情况下 NTP 服务器由 DHCP 提供，因此无需对 `timesyncd.conf <https://www.freedesktop.org/software/systemd/man/latest/timesyncd.conf.html>`_ 做额外配置。

要查看时间同步状态，请运行：

.. code-block:: shell-session

   	$ timedatectl status


要启用该服务，请运行：

.. code-block:: shell-session

   	# timedatectl set-ntp true

|

SSH 服务器
==========

系统已安装 OpenSSH 服务器，并启用了 root 用户访问。

在 SD 卡 Debian/Ubuntu 镜像创建结束时会删除加密证书。首次启动时，由 :rp-github:`/etc/systemd/system/ssh-reconfigure.service <ubuntu/blob/main/debian/overlay/etc/systemd/system/ssh-reconfigure.service>` 重新创建证书。因此首次启动会稍慢一些，但这样可以确保每块板卡的 SSH 加密证书都是唯一的。

|

零配置网络
=============================

链路本地地址
------------------

如果在 ``systemd.network`` 文件中使用 ``LinkLocalAddressing=yes`` 行启用此功能，``systemd-networkd`` 就能为接口提供 `链路本地地址 <https://en.wikipedia.org/wiki/Link-local_address>`_。所有接口都启用了此设置，因此每个活动接口都会在保留的 ``169.254.0.0/16`` 地址块中获得一个地址。

|

Zeroconf
--------

如果用于访问设备的计算机支持 zeroconf（Avahi/Bonjour），还可以进行名称解析。由于同一网络中可能有多台设备，必须对它们加以区分。使用以太网 MAC 地址的最后三段（去掉冒号；地址印在每台设备的以太网连接器上）生成主机名，再由主机名生成链接名称。例如，若 MAC 地址为 ``00:26:32:f0:f1:f2``，则缩短字符串 ``shortMAC`` 为 ``f0f1f2``。

主机名由 :rp-github:`/etc/systemd/system/hostname-mac.service <ubuntu/blob/main/debian/overlay/etc/systemd/system/hostname-mac.service>` 生成，该服务必须在启动过程早期运行。要设置自己的主机名，请替换 ``hostname-mac.service`` 中的以下行：

.. code-block:: shell-session

	hostnamectl set-hostname / * MY HOST NAME * /


现在可以通过 ``http://rp-<shortMAC>.local`` 访问每台设备。

同样，可以使用以下命令通过 SSH 访问：

.. code-block:: shell-session

   	$ ssh root@rp-<shortMAC>.local


对于 redpitaya.com 服务器提供的 *Discovery* 服务，此服务是一个很好的替代方案。

使用 `Avahi daemon <https://avahi.org/>`_ 发布特定服务。系统提供了三个配置文件。

* HTTP :rp-github:`/etc/avahi/services/bazaar.service <ubuntu/blob/main/debian/overlay/etc/avahi/services/bazaar.service>`
* SSH  :rp-github:`/etc/avahi/services/ssh.service    <ubuntu/blob/main/debian/overlay/etc/avahi/services/ssh.service>`
* SCPI :rp-github:`/etc/avahi/services/scpi.service   <ubuntu/blob/main/debian/overlay/etc/avahi/services/scpi.service>`

|

.. _support_wifi_adapter:

WiFi 适配器兼容性
==========================

特定 USB Wi-Fi 适配器是否受支持，主要取决于其芯片组的 Linux 驱动支持情况。

按 OS 版本划分的兼容性
---------------------------

* **OS 3.00 及更高版本** - 支持基于 RTL8812BU 和 RTL8188CUS 的适配器。默认禁用接入点模式。
* **OS 2.00 及更高版本** - RTL8192CU 和 RTL8188CUS 类适配器支持客户端模式。
* **OS 1.04 及更早版本** - BCM43143 支持客户端和接入点模式；RTL8192CU 类适配器仅支持客户端模式。

推荐的适配器
--------------------

* **OS 3.00 及更高版本** - TP-Link Archer T3U AC1300（RTL8812BU）。
* **OS 2.00 及更早版本** - :rp-web:`Red Pitaya WiFi Dongle <product/red-pitaya-wi-fi-dongle>` 或 Edimax EW-7811Un V2。

.. note::

	支持的适配器列表并不完整。其他适配器可能也能工作，但不属于官方支持范围。主要要求是适配器芯片组必须受 Red Pitaya OS 使用的 Linux 内核支持。也可以手动将其他芯片组添加到内核中。

芯片组摘要
---------------

.. list-table::
   :widths: 25 20 25 40
   :header-rows: 1

   * - 芯片组
     - 客户端模式
     - 接入点模式
     - 备注
   * - RTL8812BU
     - 是
     - 默认禁用
     - OS 3.00 及更高版本的主要目标。
   * - RTL8192CU / RTL8188CUS
     - 是
     - 已禁用
     - 实际使用 ``rtl8xxxu`` 类驱动。
   * - BCM43143
     - 是
     - 已禁用
     - 主要与较旧 OS 版本相关。

.. note::

	该表显示最新 OS 版本的支持状态。较旧 OS 版本对同一芯片组的支持可能不同（请参阅上面的 `按 OS 版本划分的兼容性`_ 部分）。


如何验证适配器支持情况
-----------------------------

插入 USB Wi-Fi 适配器后，使用以下命令：

.. code-block:: shell-session

	$ lsusb
	$ dmesg | tail -n 50
	$ iw list

检查是否检测到适配器，以及 ``Supported interface modes`` 是否包含所需模式（``managed`` 或 ``AP``）。

|

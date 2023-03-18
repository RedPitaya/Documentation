.. _faq:

###
FAQ
###

***********************************
How to get started with Red Pitaya?
***********************************

* :ref:`Quick start <quick_start>`


***************************************
How to connect to Red Pitaya in 5 steps
***************************************

* :ref:`Connected to router <LAN>`
* :ref:`Direct connection to computer <dir_cab_connect>`


**************************************************
How can I start using RP measurement applications?
**************************************************

* :ref:`Connect to Red Pitaya <ConnectSTEMlab>`


*********************************************************
How to control RP remotely using LabVIEW, MATLAB, Python?
*********************************************************

|remoteControl|

.. |remoteControl| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/appsFeatures/remoteControl/remoteControl.html#remotecontrol" target="_blank">Remote control (MATLAB, LabVIEW, Scilab or Python)</a>

***********************************
How to start with FPGA development?
***********************************

|software|

.. |software| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/software/software.html#software" target="_blank">Software</a>

******************
How to upgrade OS?
******************

|prepareSD|

.. |prepareSD| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/quickStart/SDcard/SDcard.html#preparesd" target="_blank">Prepare SD card</a>

****************************************
How to connect the external clock to RP?
****************************************

* |external_125_14|
* |external_122_16|

.. |external_125_14| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/125-14/top.html#external-125-14" target="_blank">STEMlab 125-14 & STEMlab 125-14-Z7020</a>
   
.. |external_122_16| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/122-16/top.html#external-122-16" target="_blank">SDRlab 122-16</a>

.. _internetAccess:

******************************************************************
How can I make sure that my Red Pitaya has access to the internet?
******************************************************************

How can I make sure that my Red Pitaya has access to the internet?

1. Connect to your Red Pitaya over |SSH|.
2. Make sure that you can ``ping google.com`` website:

   .. code-block:: shell-session

      root@rp-f03dee:~# ping -c 4 google.com
      PING google.com (216.58.212.142) 56(84) bytes of data.
      64 bytes from ams15s21-in-f142.1e100.net (216.58.212.142): icmp_seq=1 ttl=57 time=27.3 ms
      64 bytes from ams15s21-in-f142.1e100.net (216.58.212.142): icmp_seq=2 ttl=57 time=27.1 ms
      64 bytes from ams15s21-in-f142.1e100.net (216.58.212.142): icmp_seq=3 ttl=57 time=27.1 ms
      64 bytes from ams15s21-in-f142.1e100.net (216.58.212.142): icmp_seq=4 ttl=57 time=27.1 ms

      --- google.com ping statistics ---
      4 packets transmitted, 4 received, 0% packet loss, time 3004ms
      rtt min/avg/max/mdev = 27.140/27.212/27.329/0.136 ms

.. |SSH| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/software/console/ssh/ssh.html#ssh" target="_blank">SSH</a>   
 
 
.. _faqConnected:
      
******************************************************************************************************
How can I make sure that Red Pitaya is connected to the same network as my computer/tablet/smartphone?
******************************************************************************************************

The most common answer would be: just make sure that your Red Pitaya and your PC/tablet/smartphone are both connected to the same router or your smartphone hotspot.

In order to test it, you can use a PC that is connected to the same local network as your Red Pitaya and try the following:

1. Open the terminal window.

   * **Windows**: Go to RUN, type in ``cmd`` and press enter.
   * **Linux**: Click on the application button, type in ``Terminal`` and press enter.
   * **macOS**: Hit **cmd + space**, type in ``Terminal`` and press enter.

2. Enter ``arp -a`` command to get a list of all devices in your local area network
   and try to find your Red Pitaya MAC address on the list.

   .. code-block:: shell-session

      $ arp -a
      ? (192.168.178.117) at 00:08:aa:bb:cc:dd [ether] on eth0
      ? (192.168.178.118) at 00:26:32:f0:3d:ee [ether] on eth0
      ? (192.168.178.105) at e8:01:23:45:67:8a [ether] on eth0

   .. note::

      If you have a cable connection, then your MAC address
      is written on your Red Pitaya LAN connector.

   .. figure:: MAC.png
      :align: center

.. note:: 

   If you have established a wireless connection, then you should check the MAC address of your wireless USB dongle. The MAC addresses are typically written on the USB dongles. 

3. Type your Red Pitaya IP into your WEB browser and connect to it.

   .. figure:: Screen-Shot-2015-09-26-at-09.34.00.png
      :align: center

If your Red Pitaya is not listed on the list of your local network devices on the local network, then it is necessary to check that your Red Pitaya is connected to your local network.

*******************************************************************
How to find the Red Pitaya URL if it is not written on the sticker?
*******************************************************************

The Red Pitaya URL is ``rp-xxxxxx.local`` where ``xxxxxx`` must be replaced with the last 6 digits of the MAC address that is written on the sticker.

If the RP MAC address is ``00:26:33:F1:13:D5``, the last 6 digits are ``F113D5`` and the URL is ``rp-f113d5.local``.

.. figure:: Screen-Shot-2016-08-17-at-09.50.31-503x600.png
   :align: center

.. _isConnected:

********************************************
Is Red Pitaya connected to my local network?
********************************************

1. Connect your Red Pitaya to a PC over a serial console. |Serial Console|?

2. Type “ip a” and hit enter to check the status of your ethernet connection on Red Pitaya.

   a) If you have connected to your Red Pitaya over a wireless connection, you should check the status of ``wlan0`` interface.

   b) If you have connected to your Red Pitaya over a cable connection, you should check ``eth0`` interface.

3. Type Red Pitaya IP into your web browser to see if you can connect to it.

   .. figure:: Screen-Shot-2015-09-26-at-09.34.00.png
      :align: center

.. |Serial Console| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/software/console/console/console.html#setting-up-serial-console" target="_blank">How</a>


.. _troubleshooting:

**************************
Problems connecting to RP?
**************************

.. figure:: blinking-pitaya-eth.gif
   :align: center

#. First check the LEDs:

   a. If the **green LED** is not **ON** or is **blinking**. It seems like something is wrong with the power supply, or maybe it's the USB cable. Make sure that:

       1. you have plugged the USB cable into the right USB connector on the Red Pitaya
       2. your power supply is 5V/2A
       3. try to replace the USB cable and also the USB power supply

   #. If the **green LED** is turned **ON** but the **blue LED** is turned **OFF**. In this case, there is an error while loading the Red Pitaya system from the SD card. Make sure that:

       * you have correctly inserted the Red Pitaya SD card and the Red Pitaya OS has been installed
         (Notice that Red Pitayas already comes with a pre-installed OS on SD cards. Anyhow, SD cards might get corrupted- in such case follow this instructions on how to |prepareSD| to properly re-install Red Pitaya OS to SD card)
       
       * try to use another SD card

   #. If both the **green** and **blue** LEDs are **ON**, but the **red** and **orange** LEDs are **not blinking**.
      The red LED indicates CPU heartbeat, while the orange LED indicates access to the SD card. Notice that these two LEDs always start blinking 10 seconds after the green and blue LEDs are turned on.

#. Make sure your Red Pitaya and computer are both connected to the same |faqConnected|.

#. If you are a Windows user, please look at the note below.

.. note::

   **Windows 7/8** users should install `Bonjour Print Services <https://downloads.redpitaya.com/tools/BonjourPSSetup.exe>`_,
   otherwise access to ``*.local`` addresses will not work.

   **Windows 10** already supports mDNS and DNS-SD,
   so there is no need to install additional software.


.. |faqConnected| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/quickStart/troubleshooting/troubleshooting.html#faqconnected" target="_blank">local network</a>


***************************************************
Problems with upgrading OS, accessing market place?
***************************************************

1. Make sure your Red Pitaya has access to the internet. |internet access|?
#. Force a refresh of the Red Pitaya application page. |Wiki refresh|?

.. |internet access| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/quickStart/troubleshooting/troubleshooting.html#internetaccess" target="_blank">How</a>
   
.. |Wiki refresh| raw:: html

   <a href="http://www.wikihow.com/Force-Refresh-in-Your-Internet-Browser" target="_blank">How</a>

*********************
Slow WIFI connection?
*********************

If your wireless connection with Red Pitaya works very slowly and all the applications seem very unresponsive and not running smoothly, please check the following:

* Check the WiFi signal strength on your PC/tablet/smartphone.
* Check the WiFi signal strength of your Red Pitaya.

   1. Connect to your Red Pitaya via an |SSH| connection.

   #. Enter the ``cat /proc/net/wireless`` command in order to get information about link quality and signal strength.

      .. figure:: Screen-Shot-2015-09-26-at-20.28.27.png
         :align: center

      Link quality measures the number of packet errors that occur. The lower the number of packet errors, the higher this will be. Link quality goes from 0-100%.

      Level, or signal strength, is a simple measure of the amplitude of the signal that is received. The closer you are to the access point, the higher this will be.

* If you are in an area with many routers around you, it might happen that more of them operate on the same wifi channel, which drastically decreases data throughput and slows down connection.
Here are the instructions on how to |Wifi channel|.
  For MAC users, we recommend using the Scan feature of the |Wireless Diagnostic Tool| in order to find the best wifi channel.

.. note::
    
    For full performance, a wired connection is preferred.

.. |Wifi channel| raw:: html

   <a href="http://www.howtogeek.com/howto/21132/change-your-wi-fi-router-channel-to-optimize-your-wireless-signal/" target="_blank">change your wifi router channel in order to optimise your wireless signal</a>

.. |Wireless Diagnostic Tool| raw:: html

   <a href="http://www.howtogeek.com/211034/troubleshoot-and-analyze-your-mac%E2%80%99s-wi-fi-with-the-wireless-diagnostics-tool/" target="_blank">Wireless Diagnostic Tool</a>
   
*************************
WIFI dongle not detected?
*************************

Please note that not all are compatible. A list is in the documentation: |Supported Wifi Dongles| 

.. |Supported Wifi Dongles| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/software/other_info/os/network.html#support-wifi-adapter" target="_blank">Supported USB Wi-Fi adapters</a>

***************************************
Where can I find Red Pitaya schematics?
***************************************

* |STEMlab 125-10 sch|
* |STEMlab 125-14 sch|
* |SDRlab 122-16 sch|
* |SIGNALlab 250-12 sch|

.. |STEMlab 125-10 sch| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/shem.html#schematics" target="_blank">STEMlab 125-10</a>

.. |STEMlab 125-14 sch| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/shem.html#schematics" target="_blank">STEMlab 125-14</a>
   
.. |SDRlab 122-16 sch| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/shem.html#schematics" target="_blank">SDRlab 122-16</a>

.. |SIGNALlab 250-12 sch| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/shem.html#schematics" target="_blank">SIGNALlab 250-12</a>

***********************************************************
My device shows wrong measurements. How can I calibrate it?
***********************************************************

The Red Pitaya can be calibrated using the |Calibration Tool|.

.. |Calibration Tool| raw:: html

   <a href="https://redpitaya.readthedocs.io/en/latest/appsFeatures/systemtool/calibration.html" target="_blank">Calibration Tool</a>

*****************************************************************************
Web interface not functioning properly or experimenting with freezing?
*****************************************************************************

Please ensure that your browser's ad blocker is turned off and that your proxy settings are correct. For local connections to the Red Pitaya unit, proxy settings should not be required.

*******************************
Red Pitaya not booting anymore?
*******************************

A possible cause could be a corrupted card, and the recommendation is a manual OS re-write: |prepareSD|

***********************************************************************************
Is there a hardware difference between the STEMlab125-14 and the ISO17025 versions?
***********************************************************************************

No, the hardware is identical. The only difference is that the latter would have been sent to a certification lab and the appropriate measurements would have been made.

*************************
Undesired disconnections?
*************************

We recommend testing on a different computer, checking the state of the Ethernet cables and power supply, proxy settings, and re-writing the OS.


********************************************
Red Pitaya not booting even after OS update?
********************************************

Please use the Balena Etcher application to re-write the OS manually. The latest Windows update has been reported to have broken the Win32 disc imager. |prepareSD|

*****************************
Is Red Pitaya failing to update?
*****************************

Please use the Balena Etcher application to re-write the OS manually. The latest Windows update has been reported to have broken the Win32 disc imager. |prepareSD|


********************
How to report a bug?
********************

Please send us an e-mail at support@redpitaya.com with the following information:

* The model of Red Pitaya used
* Version of Red Pitaya OS
* Information about the bug
* Clear instructions about how to reproduce it.

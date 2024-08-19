.. _prepareSD:

###############
Prepare SD card
###############


***********
OS Versions
***********

The OS versions are listed from newest to oldest. For development OS (Nightly Builds), please check the `Nightly Builds`_ chapter located at the end of the OS section.

==========
2.00 OS
==========

With the 2.00 OS versions we moved to a unified OS image for all boards (One OS to rule them all).

**RedPitaya OS 2.0**:

  - `Latest Beta (2.05-37) <https://downloads.redpitaya.com/downloads/Unify/RedPitaya_OS_2.05-37_beta.img.zip>`_  - |CHANGELOG| (MD5 (unzipped): ad55cb45cf92bf8e40e3901f24a677ba)
  - `Latest Stable (2.04-35) <https://downloads.redpitaya.com/downloads/Unify/RedPitaya_OS_2.04-35_stable.img.zip>`_  - |CHANGELOG| (MD5 (unzipped): d3d59bca29421987550289fce29b87b5)

|

New C libraries were added with the Unified (2.00) OS ecosystem, which causes the C program compilation to fail on older OS.

Please make sure that your Red Pitaya OS and the downloaded |GitHub| ecosystem repository are compatible.
We recommend using a |GitHub| ecosystem that is meant to run on your current Red Pitaya OS version:

  - 2.05-37 - Branch 2024.3
  - 2.04-35 - Branch 2024.2
  - 2.00-30 - Branch 2024.1
  - 2.00-23 - Branch 2023.3
  - 2.00-18 - Branch 2023.2
  - 2.00-15 - Branch 2023.1
  - 1.04-28 - Branch 2022.2
  - 1.04-18 - Branch 2022.1

Using an old OS with a newer GitHub ecosystem can result in compatibility isses.

.. note::

   When updating the OS to 2.00 version from 1.04 or older (or downgrading from 2.00 to 1.04 or older), a factory reset of calibration parameters must be performed. Please open the Red Pitaya's web interface and head to **System => Calibration => Manual DC calibration**. Click on **Reset**, select **Factory**, and confirm the reset. For more details on calibration, please see the :ref:`Calibration application <calibration_app>`.


.. note::

   If you have problems running the 2.00 version of the OS and you updated from the 1.04 or older OS image, please check |this GitHub solution|. For all other problems please contact the |SUPPORT TEAM|.

.. |this GitHub solution| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya/issues/250" target="_blank">this GitHub solution</a>

.. |SUPPORT TEAM| raw:: html

   <a href="https://redpitaya.com/contact-us/" target="_blank">support team</a>

.. |GitHub| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya" target="_blank">Red Pitaya GitHub</a>




=========
1.04 OS
=========

The 1.04 OS versions are board specific. Please download only versions compatible with your board type.

**STEMlab 125-14 & STEMlab 125-10**:

   *   `1.04-28 <https://downloads.redpitaya.com/downloads/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-28_beta.img.zip>`_  - |CHANGELOG| (MD5 (zipped): 92e14e68d27e63568fb87954239e9fb0)
   *   `1.04-18 <https://downloads.redpitaya.com/downloads/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-18_stable.img.zip>`_  - |CHANGELOG| (MD5 (zipped): f6cde9b3264a12372873d039535e58d5)


**STEMlab 125-14 (SECONDARY/SLAVE board)**:

   *   `1.04-06 <https://downloads.redpitaya.com/downloads/Streaming_slave_boards/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-6_slave_beta.img.zip>`_  - |CHANGELOG| (MD5 (zipped): ef928d3014d806539e4360e59b7f6a99)


**STEMlab 125-14-Z7020**:

   *   `1.04-14 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020/STEMlab_125-14-Z7020_OS_1.04-14_beta.img.zip>`_  - |CHANGELOG| (MD5 (zipped): c740aab5d7b374924f19171e1edd3161)
   *   `1.04-10 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020/STEMlab_125-14-Z7020_OS_1.04-10_stable.img.zip>`_  - |CHANGELOG| (MD5 (zipped): 3770f34e954674b0423db33ed8a3471d)


**STEMlab 125-14 4-Input**:

   *   `1.04-03 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020-4CH/STEMlab_125-14-4CH_OS_1.04-3_beta.img.zip>`_  - |CHANGELOG_Z20_4CH| (MD5 (zipped): 414c1e7572ec116657a356f3ee2000ac)


**SDRlab 122-16**:

   *   `1.04-15 <https://downloads.redpitaya.com/downloads/SDRlab-122-16/SDRlab_122-16_OS_1.04-15_beta.img.zip>`_  - |CHANGELOG_Z20| (MD5 (zipped): ba9f8be2f19630b42ee7b56bdd1d4392)
   *   `1.04-11 <https://downloads.redpitaya.com/downloads/SDRlab-122-16/SDRlab_122-16_OS_1.04-11_stable.img.zip>`_  - |CHANGELOG_Z20| (MD5 (zipped): 634cf27555d4ae8900c92833afc1ddb9)


**SIGNALlab 250-12**:

   *   `1.04-30 <https://downloads.redpitaya.com/downloads/SIGNALlab-250-12/SIGNALlab_250-12_OS_1.04-30_beta.img.zip>`_  - |CHANGELOG_Z20_250_12| (MD5 (zipped): 2acb0579dbf67a40828a9b60a59be9e8)
   *   `1.04-27 <https://downloads.redpitaya.com/downloads/SIGNALlab-250-12/SIGNALlab_250-12_OS_1.04-27_stable.img.zip>`_  - |CHANGELOG_Z20_250_12| (MD5 (zipped): 40601a42fb06cf23f43aefe15d042a01)


.. note::

   To run the C applications with 1.04 or older OS, please use the 2022.2 or older release/branch of the GitHub ecosystem


.. |CHANGELOG| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG.md" target="_blank">CHANGELOG</a>

.. |CHANGELOG_Z20| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG_Z20.md" target="_blank">CHANGELOG</a>

.. |CHANGELOG_Z20_250_12| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG_Z20_250_12.md" target="_blank">CHANGELOG</a>

.. |CHANGELOG_Z20_4CH| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG_Z20_4CH.md" target="_blank">CHANGELOG</a>


=================
Older OS versions
=================

All older OS versions that are in our database are available in our archive:

   *   |Red Pitaya archive|

For manual ecosystem upgrades please refer to `Manual upgrade`_.

.. |Red Pitaya archive| raw:: html

   <a href="https://downloads.redpitaya.com/downloads/" target="_blank">Red Pitaya archive link</a>

.. _nightly_builds:

==============
Nightly Builds
==============

The nightly builds are snapshots of the development activity for upcoming Red Pitaya OS releases and include the newest features and bug fixes scheduled for the official releases. These builds are made available to make it easier for users to test their setup for potential issues with an upcoming release or to test new features and provide feedback on improving them before they are released as a Beta OS or Stable version.

We have decided to release the nightly builds to ensure that our codebase stays healthy and to shorten the time to fix some of the reported issues or implement some new features reported as suggestions for improvement.

As these builds are snapshots of the latest code, odds are you will encounter more issues compared to stable releases. Please report any issues to support@redpitaya.com so that our developers can review them and make any needed fixes.

**Nightly Builds ecosystem**:

   *    |nightly builds|  -  `NIGHTLY CHANGELOG <https://downloads.redpitaya.com/downloads/Unify/nightly_builds/CHANGELOG.txt>`_

Ecosystem builds run every Saturday night.

.. note::

   These OS versions may be unstable and may cause misconfigurations or measurement data loss.
   We recommend that you use them solely for testing purposes, or you have reported a bug or requested a feature and our technical staff has instructed you to proceed.

.. note::

   When updating from an OS version older than 2.00 to a Nightly Build version, a factory reset of calibration parameters must be performed. Please open the Red Pitaya's web interface and head to **System => Calibration => Manual DC calibration**. Click on **Reset**, select **Factory**, and confirm the reset. For more details on calibration, please see the :ref:`Calibration application <calibration_app>`.


.. |nightly builds| raw:: html

   <a href="https://downloads.redpitaya.com/downloads/Unify/nightly_builds/" target="_blank">Red Pitaya downloads</a>


**************************************
Download and install the SD card image
**************************************

The next procedure will create a clean SD card image.

1. Select an appropriate OS version from above and download it.

   .. figure:: img/microSDcard-RP.png
       :width: 10%

#. Unzip the SD card image.

#. Write the image onto an SD card. Instructions are available for various operating systems:

.. contents::
   :local:
   :backlinks: none
   :depth: 1

4. Insert the SD card into the Red Pitaya.

   .. figure:: img/pitaya-quick-start-insert-sd-card.png
      :align: center

#. Reset the calibration parameters to **Factory Default** (or :ref:`recalibrate your Red Pitaya <calibration_app>`).

   .. note::

       When updating the OS to 2.00 version from 1.04 or older (or downgrading from 2.00 to 1.04 or older), a factory reset of calibration parameters must be performed. Please open the Red Pitaya's web interface and head to **System => Calibration => Manual DC calibration**. Click on **Reset**, select **Factory**, and confirm the reset. For more details on calibration, please see the :ref:`Calibration application <calibration_app>`.

.. note::

   This video shows how to identify your Red Pitaya model and write a memory card.

   .. raw:: html

    <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;">
        <iframe src="https://www.youtube.com/embed/Qq_YRv2nk3c" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
    </div>

=======
Windows
=======

.. _windows_gui:

#. Insert the SD card into your PC or SD card reader.

   .. figure:: img/SDcard_insert.jpg
      :align: center

#. Download |balenaEtcher| and install it.

   .. |balenaEtcher| raw:: html

      <a href="https://www.balena.io/etcher/" target="_blank">Balena Ethcer</a>

#. Open the newly installed Balena Etcher application.

   .. figure:: img/SDcard_Win_BalenaEtcher.png
      :align: center

#. Under **Flash from file** select an unzipped Red Pitaya image file.

   .. figure:: img/SDcard_Win_BalEtc_FlashFromFile.png
      :align: center

#. Under **Select target** choose the drive letter of the SD card. Balena Etcher will only show you external drives.

   .. figure:: img/SDcard_Win_BalEtc_SelectTarget.png
      :align: center

   .. note::

      Balena Etcher will only show you external drives, but please be careful to select the correct drive if you have multiple cards or USBs plugged into your computer. If you choose the wrong one, you risk erasing data from the selected drive. You can easily see the drive letter (for example, E:) by looking in the left column of Windows Explorer.

   .. figure:: img/SDcard_Win_BalEtc_SelectTarget2.png
      :align: center

#. When you click **Flash** the computer will prompt you to allow the operation. Click **yes** and wait for the flashing and validation to be completed.

   .. figure:: img/SDcard_Win_BalEtc_Flash.png
      :align: center

#. Close Balena Etcher.

   .. figure:: img/SDcard_Win_BalEtc_FlashComplete.png
      :align: center

=====
Linux
=====

.. _linux_gui:

.. note::

   You can also use |balenaEtcher| on Linux and macOS. Instructions are under :ref:`Windows section <windows_gui>`.

-------------------------
Ubuntu using Image Writer
-------------------------

#. Right-click on the extracted SD card image and select **Open With > Disk Image Writer**.

   .. figure:: img/DIW_1.png
      :align: center
      :width: 50%

      Context menu

   .. figure:: img/DIW_2.png
      :align: center
      :width: 50%

      Select tool dialog

2. In the **Restore Disk Image** window, select your SD card in the **Destination** pull-down menu.
   Be careful to select the correct device; use the size for orientation (for example, a 16 GB SD card).

   .. figure:: img/DIW_3.png
      :align: center
      :width: 50%

      Select drive dialog

3. You will be asked to confirm your choice and enter a password.
   Additional dialog windows will again show the selected destination drive.
   Take the opportunity to reconsider whether you chose the right device.


.. _linux_cli:

------------
Command line
------------

.. note::

   Please note that the use of the ``dd`` tool can overwrite any partition of your machine.
   If you specify the wrong device in the instructions below, you could delete your primary Linux partition.
   Please be careful.

#. Insert the SD card into your PC or SD card reader.

   .. figure:: img/SDcard_insert.jpg
      :align: center

#. Open the terminal and check the available disks with ``df -h``.
   Our SD card is 16 GB. It is named ``/dev/sdx`` and divided into two partitions, ``/dev/sdx1`` and ``/dev/sdx2``.
   The drive mounted at ``/`` is your main drive.
   Be careful not to use it.

   .. code-block:: shell-session

      $ df -h
      Filesystem       Size  Used   Avail  Use%  Mounted on
      /dev/sdx1        118M   27M     92M   23%  /media/somebody/CAD5-1E3D
      /dev/sdx2       15.9G 1013M   15.8G   33%  /media/somebody/7b2d3ba8-95ed-4bf4-bd67-eb52fe65df55

#. Unmount all SD card partitions with ``umount /dev/sdxN``
   (make sure you replace N with the right numbers).

   .. code-block:: shell-session

      $ sudo umount /dev/sdx1 /dev/sdx2

#. Write the image onto the SD card with the following command.
   Replace the ``red_pitaya_image_file.img`` with
   the name of the unzipped Red Pitaya SD Card Image
   and replace ``/dev/device_name`` with the path to the SD card.

   .. code-block:: shell-session

      $ sudo dd bs=1M if=red_pitaya_image_file.img of=/dev/device_name

#. Wait until the process has finished.


=====
macOS
=====

.. _macos_gui:

.. note::

   You can also use |balenaEtcher| on Linux and macOS. Instructions are under :ref:`Windows section <windows_gui>`.

-------------------
Using ApplePi-Baker
-------------------

#. Insert the SD card into your PC or SD card reader.

   .. figure:: img/SDcard_insert.jpg
      :align: center

#. Download |ApplePi|. Direct link:

   *   `ApplePi-Baker-v2.2.3.dmg <https://www.tweaking4all.com/downloads/raspberrypi/ApplePi-Baker-v2.2.3.dmg>`_
   *   `ApplePi-Baker-1.9.9.dmg <https://www.tweaking4all.com/downloads/raspberrypi/ApplePi-Baker-1.9.9.dmg>`_

   .. |ApplePi| raw:: html

      <a href="https://www.tweaking4all.com/hardware/raspberry-pi/applepi-baker-v2" target="_blank">ApplePi-Baker</a>

#. Click on *ApplePi-Baker* icon, then click *Open* in order to run it.

   .. figure:: img/SDcard_macOS_open.png
      :align: center

#. Drag and drop *ApplePi-Baker* for installation.

   .. figure:: img/SDcard_macOS_install.png
      :align: center

#. Enter your admin password and click OK.

   .. figure:: img/SDcard_macOS_password.png
      :align: center

#. Select the SD card drive. This can be recognised by the size of the card, which is 16 GB.

   .. figure:: img/SDcard_macOS_ApplePi-Baker_drive.png
      :align: center

#. Select the Red Pitaya OS image file.

   .. figure:: img/SDcard_macOS_ApplePi-Baker_image.png
      :align: center

#. It's coffee time. The application will show you the estimated time for accomplishment.

   .. figure:: img/SDcard_macOS_ApplePi-Baker_wait.png
      :align: center

#. When the operation is finished, the status will change to idle.

   .. figure:: img/SDcard_macOS_ApplePi-Baker_quit.png
      :align: center


.. _macos_cli:

------------
Command line
------------

#. Insert the SD card into your PC or SD card reader.

   .. figure:: img/SDcard_insert.jpg
      :align: center

#. Click **cmd + space**, type **Disk Utility** into the search box and press enter.
   From the menu, select your SD card and click on the **Erase** button (be careful not to delete your disk!).

   .. figure:: img/SDcard_macOS_DiskUtility.png
      :align: center

#. Click **cmd + space**, then enter ``cd`` into the **Terminal**.
   Then type ``cd Desktop`` and press enter once more.

#. Unmount the partition so that you will be able to overwrite the disk.
   Type ``diskutil list`` into the Terminal and press enter.
   This will show you the list of all memory devices.

   .. figure:: img/Screen-Shot-2015-08-07-at-16.59.50.png
      :align: center

   Unmount with: ``diskutil UnmountDisk /dev/diskn``
   (insert the number ``n`` of your disk correctly!)

   .. figure:: img/Screen-Shot-2015-08-07-at-17.14.34.png
      :align: center

#. Type: ``sudo dd bs=1m if=path_of_your_image.img of=/dev/rdiskn``
   (Remember to replace ``n`` with the number that you noted before!)
   (notice that there is a letter ``r`` in front of the disk name, use that as well!)

   .. figure:: img/Screen-Shot-2015-08-07-at-17.14.45.png
      :align: center

#. Type in your password and wait a few minutes for the image to be written.

#. When the image is written, type: ``diskutil eject /dev/diskn`` and press enter.

#. Safely eject the SD card.


**********
Background
**********

A Red Pitaya SD card contains two partitions:

1. 128 MB FAT contains the **ecosystem**:

   *   boot files: FSBL, FPGA images, U-Boot, Linux kernel
   *   Red Pitaya API libraries and header files
   *   Red Pitaya web applications, scripts, tools
   *   customized Nginx web server


2. ~8 GB Ext4 contains the **OS**:

   *   Ubuntu/Debian OS
   *   various libraries
   *   network setup customization
   *   systemd services customization

Most of Red Pitaya's source code translates into the ecosystem.
Therefore, it is updated more often.
The OS is changed less frequently.

.. note::

   You can find older and developed Red Pitaya OS images and Ecosystem zip files
   on our |download server|.

.. |download server| raw:: html

   <a href="https://downloads.redpitaya.com/downloads/" target="_blank">download server</a>


.. note::

   A list of new features, bug fixes, and known bugs for each Red Pitaya release
   can be found in our |CHANGELOG|.


**************
Manual upgrade
**************

Instead of writing the whole SD card image,
it is possible to upgrade only the ecosystem.

A manual upgrade allows you to fix a corrupted SD card image
(if only the FAT partition is corrupted) or to install
older, newer, or custom ecosystem zip files.

#. Download a zip file from our |download server|.

#. Insert the SD card into the card reader.

#. Delete all files from the FAT partition.
   Use ``Shift + Delete`` to avoid placing files
   into the trash bin on the same partition.

#. Extract the ecosystem zip file contents onto the now empty partition.

If you wish to keep wireless settings, skip deleting the next files:

*   ``wpa_supplicant.conf``
*   ``hostapd.conf``


******************
Resize file system
******************

When recording an image to a flash card of any size, we get sections of the file system of 4 GB in size.
In order to increase the available free space, you need to execute the following script:

      .. code-block:: shell-session

          root@rp-f03dee:~# /opt/redpitaya/sbin/resize.sh

After the script is completed, the system will ask you to restart your Red Pitaya.
If everything is done correctly, the system will start with an increased space size. This can be checked with the following command:

      .. code-block:: shell-session

          root@rp-f03dee:~# df -h


.. note::

   If the file system size has not changed, try to manually run the command:

      .. code-block:: shell-session

         root@rp-f03dee:~# sudo resize2fs /dev/mmcblk0p2

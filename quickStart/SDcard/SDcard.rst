.. _prepareSD:

###############
Prepare SD card
###############

In this section you will find instrucitons on how to install the Red Pitaya OS on an SD card.

.. contents::
    :local:
    :backlinks: top
    :depth: 2


********************************
Quick installation instructions
********************************

The following steps will guide you through the process of installing the Red Pitaya OS on an SD card.

1. Select the latest :ref:`Red Pitaya OS version image <os_versions>` and download it.

    .. figure:: img/microSDcard-RP.png
        :width: 200

#. Use a disk image writing tool (for example, Balena Etcher) to write the image onto the SD card. Instructions are available for various operating systems:

    * :ref:`Windows <windows_gui>`.
    * :ref:`Linux <linux_gui>`.
    * :ref:`macOS <macos_gui>`.

#. Insert the SD card into the Red Pitaya.

    .. figure:: img/pitaya-quick-start-insert-sd-card.png
        :align: center
        :width: 400

#. Connect the power supply and ethernet cable and check the status LED sequence during boot.

    .. raw:: html

        <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;">
            <iframe src="https://www.youtube.com/embed/9xZCAkXAkw8" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
        </div>

    If you spot any unexpected behaviour, please check the :ref:`FAQ troubleshooting section <faq>`.

#. Connect to the board via the web interface. For more information check the :ref:`quick start instructions <quickstart_connect>`.

#. When updating between major software releases (for example, from 1.04 to 2.00), reset the calibration parameters to **Factory Default** (or :ref:`recalibrate your Red Pitaya <calibration_app>`).


.. note::

    To see all options for updating the OS, please refer to the :ref:`Update Red Pitaya OS <os_update>` section.

|

.. _os_versions:

***********
OS Versions
***********

The OS versions are listed from newest to oldest. Each listed OS version consists of an image download link (to download the OS image) and a changelog link (listing the major changes in the OS).

===============
Latest 2.00 OS
===============

.. note::

    *One OS to rule them all*.
    The 2.00 OS versions work on all Red Pitaya board models.

**Red Pitaya OS 2.0**:

* :download:`Latest Stable (2.07-48) <https://downloads.redpitaya.com/downloads/Unify/RedPitaya_OS_2.07-48_stable.img.zip>`  - |CHANGELOG| (MD5 (extracted): 5d02710fd87a71b4c049ffa5105b69e5).

|
Other previous versions of OS can be found `here <https://downloads.redpitaya.com/downloads/Unify/old/>`
|

.. note::

    If you have problems running the 2.00 version of the OS and you updated from the 1.04 or older OS image, please check |this GitHub solution|. For all other problems please contact the |SUPPORT TEAM|.

.. note::

    When updating the OS to 2.00 version from 1.04 or older (or downgrading from 2.00 to 1.04 or older), a factory reset of calibration parameters must be performed. Please open the Red Pitaya's web interface and head to **System => Calibration => Manual DC calibration**. Click on **Reset**, select **Factory**, and confirm the reset. For more details on calibration, please see the :ref:`Calibration application <calibration_app>`.


.. note::

    If you have problems running the 2.00 version of the OS and you updated from the 1.04 or older OS image, please check |this GitHub solution|. For all other problems please contact the |SUPPORT TEAM|.


=========
1.04 OS
=========

The **1.04 OS versions are board model specific**. Please download only versions compatible with your board type.

Here is a video on how to identify the Red Pitaya board model and install 1.04 or older OS to the SD card.

.. raw:: html

    <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;">
        <iframe src="https://www.youtube.com/embed/Qq_YRv2nk3c" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
    </div>


**STEMlab 125-14 & STEMlab 125-10**:

* :download:`1.04-28 <https://downloads.redpitaya.com/downloads/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-28_beta.img.zip>`  - |CHANGELOG| (MD5 (zipped): 92e14e68d27e63568fb87954239e9fb0).
* :download:`1.04-18 <https://downloads.redpitaya.com/downloads/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-18_stable.img.zip>`  - |CHANGELOG| (MD5 (zipped): f6cde9b3264a12372873d039535e58d5).


**STEMlab 125-14 (secondary/slave board)** (not recommended - use 2.00 version instead):

* :download:`1.04-06 <https://downloads.redpitaya.com/downloads/Streaming_slave_boards/STEMlab-125-1x/STEMlab_125-xx_OS_1.04-6_slave_beta.img.zip>`  - |CHANGELOG| (MD5 (zipped): ef928d3014d806539e4360e59b7f6a99).


**STEMlab 125-14 Z7020**:

* :download:`1.04-14 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020/STEMlab_125-14-Z7020_OS_1.04-14_beta.img.zip>`  - |CHANGELOG| (MD5 (zipped): c740aab5d7b374924f19171e1edd3161).
* :download:`1.04-10 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020/STEMlab_125-14-Z7020_OS_1.04-10_stable.img.zip>`  - |CHANGELOG| (MD5 (zipped): 3770f34e954674b0423db33ed8a3471d).


**STEMlab 125-14 4-Input** (not recommended - use 2.00 version instead):

* :download:`1.04-03 <https://downloads.redpitaya.com/downloads/STEMlab-125-14-Z7020-4CH/STEMlab_125-14-4CH_OS_1.04-3_beta.img.zip>`  - |CHANGELOG_Z20_4CH| (MD5 (zipped): 414c1e7572ec116657a356f3ee2000ac).


**SDRlab 122-16**:

* :download:`1.04-15 <https://downloads.redpitaya.com/downloads/SDRlab-122-16/SDRlab_122-16_OS_1.04-15_beta.img.zip>`  - |CHANGELOG_Z20| (MD5 (zipped): ba9f8be2f19630b42ee7b56bdd1d4392).
* :download:`1.04-11 <https://downloads.redpitaya.com/downloads/SDRlab-122-16/SDRlab_122-16_OS_1.04-11_stable.img.zip>`  - |CHANGELOG_Z20| (MD5 (zipped): 634cf27555d4ae8900c92833afc1ddb9).


**SIGNALlab 250-12**:

* :download:`1.04-30 <https://downloads.redpitaya.com/downloads/SIGNALlab-250-12/SIGNALlab_250-12_OS_1.04-30_beta.img.zip>`  - |CHANGELOG_Z20_250_12| (MD5 (zipped): 2acb0579dbf67a40828a9b60a59be9e8).
* :download:`1.04-27 <https://downloads.redpitaya.com/downloads/SIGNALlab-250-12/SIGNALlab_250-12_OS_1.04-27_stable.img.zip>`  - |CHANGELOG_Z20_250_12| (MD5 (zipped): 40601a42fb06cf23f43aefe15d042a01).



=================
Older OS versions
=================

All older OS versions that are in our database are available in our archive:

* |Red Pitaya archive| - some images may require separate ecosystem and Linux OS installation. Check the :ref:`nightly build installation instructions <nighly_build_installation>`.

.. note::

    *Impossible. Perhaps the archives are incomplete.*

    OS images not in our archive have been lost to the sands of time. If you are looking for a specific OS or ecosystem that is missing from the archives, we suggest you ask the community on the |RP_forum|. There is a chance someone has it lying around on the disk.

For manual ecosystem upgrade please refer to `Manual ecosystem upgrade`_.



.. _nightly_builds:

==============
Nightly Builds
==============

The nightly builds are snapshots of the development activity for upcoming Red Pitaya OS releases and include the newest features and bug fixes scheduled for the official releases. These builds are made available to make it easier
for users to test their setup for potential issues with an upcoming release or to test new features and provide feedback on improving them before they are released as a Beta OS or Stable version.
We have decided to release the nightly builds to ensure that our codebase stays healthy and to shorten the time to fix some of the reported issues or implement some new features reported as suggestions for improvement.
As these builds are snapshots of the latest code, odds are you will encounter more issues compared to stable releases. Please report any issues to support@redpitaya.com so that our developers can review them and make any needed fixes.

**Nightly Builds ecosystem**:

* |nightly builds|  -  `NIGHTLY CHANGELOG <https://downloads.redpitaya.com/downloads/Unify/nightly_builds/CHANGELOG.txt>`_.


The instructions for installing the Nightly Builds are available in the :ref:`Nightly build installation guide <nighly_build_installation>` below.

.. note::

    These OS versions are Alpha releases and may be unstable and may cause misconfigurations or measurement data loss.
    We recommend that you use them solely for testing purposes, or you have reported a bug or requested a feature and our technical staff has instructed you to proceed.




*******************************************************
Installation instructions for Windows, Linux and MacOS
*******************************************************

Here you can find the installation instructions for vairous computer OS systems.

.. contents::
    :local:
    :depth: 1


For all OS versions, the installation process is the same. The only difference is the tool used to write the image onto the SD card.
Deleting the existing partitions on the SD card beforehand can help with the installation process and avoid potential limited space issues.

=======
Windows
=======

.. _windows_gui:

#. Insert the SD card into your PC or SD card reader.

    .. figure:: img/SDcard_insert.jpg
        :align: center
        :width: 600

#. If necessary delete the existing partitions on the SD card using the *Computer manager* or *Disk management* tool.

    .. figure:: img/Computer_manager.png
        :align: center
        :width: 800

#. Download |balenaEtcher| and install it.

#. Open the newly installed Balena Etcher application.

    .. figure:: img/SDcard_Win_BalenaEtcher.png
        :align: center
        :width: 160

#. Under **Flash from file** select the downloaded Red Pitaya image file (Balena Etcher accepts both zipped and unzipped files).

    .. figure:: img/SDcard_Win_BalEtc_FlashFromFile.png
        :align: center
        :width: 800

#. Under **Select target** choose the drive letter of the SD card. Balena Etcher will only show you external drives.

    .. figure:: img/SDcard_Win_BalEtc_SelectTarget.png
        :align: center
        :width: 800

    .. note::

        Balena Etcher will only show you external drives, but please be careful to select the correct drive if you have multiple cards or USBs plugged into your computer.
        If you choose the wrong one, you risk erasing data from the selected drive. You can easily see the drive letter (for example, E:) by looking in the left column of Windows Explorer.

    .. figure:: img/SDcard_Win_BalEtc_SelectTarget2.png
        :align: center
        :width: 800

#. When you click **Flash** the computer will prompt you to allow the operation. Click **yes** and wait for the flashing and validation to be completed.

    .. figure:: img/SDcard_Win_BalEtc_Flash.png
        :align: center
        :width: 800

#. Close Balena Etcher.

    .. figure:: img/SDcard_Win_BalEtc_FlashComplete.png
        :align: center
        :width: 800

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
        :width: 800

        Context menu

    .. figure:: img/DIW_2.png
        :align: center
        :width: 800

        Select tool dialog

2. In the **Restore Disk Image** window, select your SD card in the **Destination** pull-down menu.
   Be careful to select the correct device; use the size for orientation (for example, a 16 GB SD card).

    .. figure:: img/DIW_3.png
        :align: center
        :width: 800

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
        :width: 600

#. Open the terminal and check the available disks with ``df -h``.
   Our SD card is 16 GB. It is named ``/dev/sdx`` and divided into two partitions, ``/dev/sdx1`` and ``/dev/sdx2``.
   The drive mounted at ``/`` is your main drive. Be careful not to use it.

    .. code-block:: console

        $ df -h
        Filesystem       Size  Used   Avail  Use%  Mounted on
        /dev/sdx1        118M   27M     92M   23%  /media/somebody/CAD5-1E3D
        /dev/sdx2       15.9G 1013M   15.8G   33%  /media/somebody/7b2d3ba8-95ed-4bf4-bd67-eb52fe65df55

#. Unmount all SD card partitions with ``umount /dev/sdxN`` (make sure you replace N with the right numbers).

    .. code-block:: console

        $ sudo umount /dev/sdx1 /dev/sdx2

#. Write the image onto the SD card with the following command.
   Replace the ``red_pitaya_image_file.img`` with the name of the unzipped Red Pitaya SD Card Image and replace ``/dev/device_name`` with the path to the SD card.

    .. code-block:: console

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
        :width: 600

#. Download |ApplePi|. Direct link:

    * `ApplePi-Baker-v2.2.3.dmg <https://www.tweaking4all.com/downloads/raspberrypi/ApplePi-Baker-v2.2.3.dmg>`_.
    * `ApplePi-Baker-1.9.9.dmg <https://www.tweaking4all.com/downloads/raspberrypi/ApplePi-Baker-1.9.9.dmg>`_.

#. Click on *ApplePi-Baker* icon, then click *Open* in order to run it.

    .. figure:: img/SDcard_macOS_open.png
        :align: center
        :width: 600

#. Drag and drop *ApplePi-Baker* for installation.

    .. figure:: img/SDcard_macOS_install.png
        :align: center
        :width: 600

#. Enter your admin password and click OK.

    .. figure:: img/SDcard_macOS_password.png
        :align: center
        :width: 600

#. Select the SD card drive. This can be recognised by the size of the card, which is 16 GB.

    .. figure:: img/SDcard_macOS_ApplePi-Baker_drive.png
        :align: center
        :width: 1000

#. Select the Red Pitaya OS image file.

    .. figure:: img/SDcard_macOS_ApplePi-Baker_image.png
        :align: center
        :width: 1000

#. It's coffee time. The application will show you the estimated time for accomplishment.

    .. figure:: img/SDcard_macOS_ApplePi-Baker_wait.png
        :align: center
        :width: 1000

#. When the operation is finished, the status will change to idle.

    .. figure:: img/SDcard_macOS_ApplePi-Baker_quit.png
        :align: center
        :width: 1000


.. _macos_cli:

------------
Command line
------------

#. Insert the SD card into your PC or SD card reader.

    .. figure:: img/SDcard_insert.jpg
        :align: center
        :width: 600

#. Click **cmd + space**, type **Disk Utility** into the search box and press enter. From the menu, select your SD card and click on the **Erase** button (be careful not to delete your disk!).

    .. figure:: img/SDcard_macOS_DiskUtility.png
        :align: center
        :width: 1000

#. Click **cmd + space**, then enter ``cd`` into the **Terminal**. Then type ``cd Desktop`` and press enter once more.

#. Unmount the partition so that you will be able to overwrite the disk. Type ``diskutil list`` into the Terminal and press enter. This will show you the list of all memory devices.

    .. figure:: img/Screen-Shot-2015-08-07-at-16.59.50.png
        :align: center
        :width: 800

#. Unmount with: ``diskutil UnmountDisk /dev/diskn`` (insert the number ``n`` of your disk correctly!)

    .. figure:: img/Screen-Shot-2015-08-07-at-17.14.34.png
        :align: center
        :width: 800

#. Type: ``sudo dd bs=1m if=path_of_your_image.img of=/dev/rdiskn``. Remember to replace ``n`` with the number that you noted before. Notice that there is a letter ``r`` in front of the disk name, use that as well!.

    .. figure:: img/Screen-Shot-2015-08-07-at-17.14.45.png
        :align: center
        :width: 800

#. Type in your password and wait a few minutes for the image to be written.

#. When the image is written, type: ``diskutil eject /dev/diskn`` and press enter.

#. Safely eject the SD card.



.. _SDcard_partitions:

*************************
Red Pitaya OS partitions
*************************

The Red Pitaya OS image on the SD card contains two partitions. As of OS 2.05-37, the partitions are as follows:

1. The 1 GB FAT contains the **ecosystem**:

    * Boot files: FSBL, FPGA images, U-Boot, Linux kernel;
    * Red Pitaya API libraries and header files;
    * Red Pitaya web applications, scripts, tools;
    * Customized Nginx web server.


2. The ~8 GB Ext4 contains the **OS**:

    * Ubuntu/Debian OS,
    * various libraries,
    * network setup customization,
    * systemd services customization.

Most of Red Pitaya's source code translates into the ecosystem. Therefore, it is updated more often to accomodate new features and bug fixes. The newer the ecosystem, the larger the FAT partitions (the earlies Red Pitaya OS images have around 128 MB FAT partitions).
The Linux OS is updated less frequently.

.. note::

    Genereally, the newer the ecosystem, the larger the FAT partition size.
    You can find all available Red Pitaya OS images and Ecosystem zip files on our |Red Pitaya archive|.

.. note::

    A list of new features, bug fixes, and known bugs for each Red Pitaya release can be found in our |CHANGELOG|.



.. _manual_ecosystem_upgrade:

****************************
Manual ecosystem upgrade
****************************

Instead of writing the whole SD card image, it is possible to upgrade only the ecosystem.
A manual upgrade allows you to fix a corrupted SD card image (if only the FAT partition is corrupted) or to install older, newer, or custom ecosystem zip files compatible with the current Linux version.

#. Download a zip file from our |Red Pitaya archive|.

#. Insert the SD card into the card reader.

    .. note::

        Do **not** format the SD card as this will also delete the Linux OS partition.

#. Delete all files from the FAT partition. Use ``Shift + Delete`` to avoid placing files into the trash bin on the same partition.

#. Extract the ecosystem zip file contents onto the now empty partition.

If you wish to keep wireless settings, skip deleting the next files:

* ``wpa_supplicant.conf``.
* ``hostapd.conf``.



.. _nighly_build_installation:

**********************************
Nightly build installation guide
**********************************

.. note::

    Nightly builds are released several times a week and contain the latest features and bug fixes.
    The nightly builds are alpha versions of the OS and are not as thoroughly tested as the official releases, so they may contain bugs.

As mentioned in the :ref:`Red Pitaya OS partitions <SDcard_partitions>` chapter, each Red Pitaya OS consists of two separate files:

* **Linux OS** - *red_pitaya_OS-beta_<Linux OS version>.img.zip* - which contains Ubuntu OS, Red Pitaya libraries, etc.
* **Ecosystem** - *ecosystem-<Linux OS version>-<Nightly Build ecosystem number>-<ID>.zip* - Red Pitaya Web APIs.

The official Red Pitaya OS releases have both the Linux OS and the ecosystem combined into one image file. For new feature development used for Nightly build (alpha OS) versions it is easier to have the two separated, so the nightly builds are released as two separate files.

+-----------------+-----------------+---------------------------------------+-------------------+
| Red Pitaya OS   | OS release date | Nightly Build (alpha) versions        | Linux version     |
+=================+=================+=======================================+===================+
| 2.00-18         | 26.7.2023       | up to NB 141                          | 2.00              |
+-----------------+-----------------+---------------------------------------+-------------------+
| 2.00-22         | 4.10.2023       | up to NB 160                          | 2.01              |
+-----------------+-----------------+---------------------------------------+-------------------+
| 2.00-23         | 5.10.2023       | up to NB 162                          | 2.01              |
+-----------------+-----------------+---------------------------------------+-------------------+
| 2.00-30         | 11.1.2024       | up to NB 215                          | 2.03              |
+-----------------+-----------------+---------------------------------------+-------------------+
| 2.04-35         | 15.3.2024       | up to NB 258                          | 2.04              |
+-----------------+-----------------+---------------------------------------+-------------------+
| 2.05-37         | 7.8.2024        | up to NB 345                          | 2.05              |
+-----------------+-----------------+---------------------------------------+-------------------+
| 2.07-43         | 4.9.2025        | up to NB 622                          | 2.07              |
+-----------------+-----------------+---------------------------------------+-------------------+
| IN DEV          | -               | 623 and later                         | 2.07 and newer    |
+-----------------+-----------------+---------------------------------------+-------------------+


1.  Download the .zip containing the `Nightly Build Ecosystem <https://downloads.redpitaya.com/downloads/Unify/nightly_builds/>`_ (usually the highest number available).

    * Nightly build (alpha) ecosystems are named **ecosystem-<Linux OS version>-<Nightly build ecosystem number>-<ID>.zip**.

#.  Go to the *RedPitaya/downloads* page and download the `latest Linux OS <https://downloads.redpitaya.com/downloads/LinuxOS/>`_.

    * Linux OS versions are named **red_pitaya_OS-beta_<Linux OS version>.img.zip**.

    .. note::

        Make sure the Linux OS version is the same as the one listed in the name of selected Nightly build (alpha ecosystem).

    .. note::

        Please note that **Official Red Pitaya OS != Red Pitaya Linux OS**. The Linux contains just the Linux, while the official relase contains both the ecosystem and the Linux. We are looking for just the Linux here.

#.  Write the Linux OS to the SD card using the BalenaEtcher. As the BalenaEtcher will automatically close the connection between the SD and the computer at the end of the installation process, reinsert the SD card into the computer.

#.  Extract the alpha ecosystem from the .zip directly to the SD card (if possible without first extracting it to a folder on the computer).

#.  Insert the SD card into the Red Pitaya and power it on.


**Please read this section carefully**

When unpacking the alpha ecosystem, some files may be overwritten because the FAT file system is not case-sensitive.
Files such as CONNMARK.h and connmark.h will appear to the search system to be the same file, so you will be prompted to choose which file to keep.
Choose from the following options (depending on the byte size of the files):

+---------------+------------------+-------------------+
| File name     | File byte size   | Prompt overwrite? |
+===============+==================+===================+
| ipt_ttl.h     | 375              | No                |
+---------------+------------------+-------------------+
| ipt_ECN.h     | 901              | Yes               |
+---------------+------------------+-------------------+
| ip6t_HL.h     | 408              | Yes               |
+---------------+------------------+-------------------+
| xt_MARK.h     | 184              | Yes               |
+---------------+------------------+-------------------+
| xt_DSCP.h     | 697              | Yes               |
+---------------+------------------+-------------------+
| xt_tcpmss.h   | 235              | No                |
+---------------+------------------+-------------------+
| xt_RATEEST.h  | 859              | No                |
+---------------+------------------+-------------------+
| xt_CONNMARK.h | 901              | No                |
+---------------+------------------+-------------------+

.. note::

    Please note that the file names are approximate.

    **As a general rule, always choose the smaller file unless the difference in size is more than 200 bytes.**
    (For example, if you are asked to choose between file sizes of 199 bytes and 901 bytes, choose 901.
    If the choice is between 235 bytes and 253 bytes, choose 235 (the smaller size)).

* This will also happen if you first extract to a folder, but you may not be informed of the change (it happens automatically).
* There may be other file combinations that work, this is one that works for us.
* This is a problem with the FAT file system, which is not case-sensitive, so files like "connmark.h" and "CONNMARK.h" are interpreted as the same file.
* If you use a different combination of files, you may not be able to connect to Red Pitaya.

================================
Updating nighlty build ecosystem
================================

To update just the nightly build ecosystem, you can use the :ref:`Ecosystem update utility <update_util>`.



**********************************
Installing older OS on new boards
**********************************

With the introduction of the 2.00 OS, a change was made to the calibration parameters storage format in the EEPROM, which makes it incompatible with older OS versions (1.04 and older).
This causes issues when downgrading from 2.00 OS to 1.04 or older OS versions, as the older OS versions cannot read the new calibration parameters format stored in the EEPROM of newly produced boards.
Unfortunately, the process is not as simple as installing the old OS to the SD card and running it, due to the mentioned change of EEPROM calibration format.

.. note::

    The procedure described below is only suitable for downgrading to OS version 0.98 to 1.04.

.. note::

    It is possible to install 1.04 or older OS to the following Gen 2 boards:

    * :ref:`STEMlab 125-14 Gen 2 <top_125_14_gen2>`.
    * :ref:`STEMlab 125-14 PRO Gen 2 <top_125_14_pro_gen2>`.

    The other :ref:`Gen 2 and TI boards <dev_guide_hardware>` require OS 2.07-43 or newer for proper operation.

Though we do not recommend it, some users may want to downgrade to an older OS version for various reasons. Here is a step-by-step guide on how to do it.

    1. **Manually install the latest 2.00 OS version** onto the newly acquired board. See the :ref:`quick installation instructions <prepareSD>`.
    #. **Establish an SSH connection** with the board to get access to the Red Pitaya's Linux terminal. See the :ref:`SSH connection instructions <ssh>`.

        .. code-block:: shell-session

            ssh root@<red_pitaya_ip_address>

    #. **Convert the calibration to old format** using the :ref:`calib command line utility <calib_util>` command line utility:

        .. code-block:: shell-session

            calib -o

        This will convert the calibration data in the user space of the EEPROM to the old format.

        .. note::

            The conversion will **NOT** overwrite the factory calibration section in the EEPROM. Therefore, resetting to the calibration to "factory defaults" via
            the :ref:`calib utility <calib_util>` or :ref:`Calibration application <calibration_app>` will not work.

    #. **Install the older OS** to the SD card and boot the board.
    #. **Adjust the frequency calibration** (Gen 2 boards only). We suggest

|


******************
Resize file system
******************

When we record an image to a flash card of any size, we get sections of the file system that are 4 GB in size.
In order to increase the available free space, you need to run the following script:

.. code-block:: shell-session

    root@rp-f03dee:~# /opt/redpitaya/sbin/resize.sh

When the script is finished, the system will ask you to reboot your Red Pitaya.
If everything is done correctly, the system will start with an increased disk size. This can be checked with the following command:

.. code-block:: shell-session

    root@rp-f03dee:~# df -h


.. note::

    If the file system size has not changed, try running the command manually:

    .. code-block:: shell-session

        root@rp-f03dee:~# sudo resize2fs /dev/mmcblk0p2



.. substitutions


.. |this GitHub solution| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/issues/250" target="_blank">this GitHub solution</a>

.. |SUPPORT TEAM| raw:: html

    <a href="https://redpitaya.com/contact-us/" target="_blank">support team</a>

.. |GitHub| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya" target="_blank">Red Pitaya GitHub</a>


.. |CHANGELOG| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG.md" target="_blank">CHANGELOG</a>

.. |CHANGELOG_Z20| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG_Z20.md" target="_blank">CHANGELOG</a>

.. |CHANGELOG_Z20_250_12| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG_Z20_250_12.md" target="_blank">CHANGELOG</a>

.. |CHANGELOG_Z20_4CH| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG_Z20_4CH.md" target="_blank">CHANGELOG</a>

.. |Red Pitaya archive| raw:: html

    <a href="https://downloads.redpitaya.com/downloads/" target="_blank">Red Pitaya archive</a>

.. |RP_forum| raw:: html

    <a href="https://forum.redpitaya.com/" target="_blank">Red Pitaya forum</a>

.. |nightly builds| raw:: html

    <a href="https://downloads.redpitaya.com/downloads/Unify/nightly_builds/" target="_blank">Red Pitaya downloads</a>

.. |balenaEtcher| raw:: html

    <a href="https://www.balena.io/etcher/" target="_blank">balenaEtcher</a>

.. |ApplePi| raw:: html

    <a href="https://www.tweaking4all.com/hardware/raspberry-pi/applepi-baker-v2" target="_blank">ApplePi-Baker</a>
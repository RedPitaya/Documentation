.. _prepareSD:

###############
Prepare SD card
###############

This section contains instructions for installing or updating the Red Pitaya OS on an SD card.

.. contents::
    :local:
    :backlinks: none
    :depth: 1


*******************
Installation steps
*******************

Follow these steps to install the Red Pitaya OS on an SD card:

1. Download the latest Red Pitaya OS 2.00 image:

    * :download:`Latest Stable (2.07-48) <https://downloads.redpitaya.com/downloads/Unify/RedPitaya_OS_2.07-48_stable.img.zip>`  - |CHANGELOG| (MD5 (extracted): 5d02710fd87a71b4c049ffa5105b69e5).

    .. note::

        The 2.00 OS versions work on all Red Pitaya board models.

    .. figure:: img/microSDcard-RP.png
        :width: 200

#. Use a disk image writing tool to write the image onto the SD card. We recommend |balenaEtcher|. Installation instructions:

    * :ref:`Windows <windows_gui>`
    * :ref:`Linux <linux_gui>`
    * :ref:`macOS <macos_gui>`

#. Insert the SD card into the Red Pitaya.

    .. figure:: img/pitaya-quick-start-insert-sd-card.png
        :align: center
        :width: 400

#. Connect the power supply and Ethernet cable and check the status LED sequence during boot. If you spot any unexpected behaviour, please check the :ref:`FAQ troubleshooting section <faq>`.

    .. raw:: html

        <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;">
            <iframe src="https://www.youtube.com/embed/9xZCAkXAkw8" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
        </div>

#. Connect to the board via the web interface. For more information check the :ref:`quick start instructions <quickstart_connect>`.

#. When updating between major software releases (for example, from 1.04 to 2.00), reset the calibration parameters to **Factory Default** (or :ref:`recalibrate your Red Pitaya <calibration_app>`).


.. note::

    For older OS versions, nightly builds, command-line installation, and other advanced topics, see the :ref:`Advanced SD card guide <sdcard_advanced>`.

.. note::

    To see all options for updating the OS, please refer to the :ref:`Update Red Pitaya OS <os_update>` section.



*******************************************************
Installation instructions for Windows, Linux and macOS
*******************************************************

Select your operating system for specific instructions on writing the Red Pitaya OS image to an SD card.

.. note::

    The installation process is the same for all OS versions. We recommend using |balenaEtcher| as it works on all platforms and is easy to use.



.. _windows_gui:

=======
Windows
=======

#. Insert the SD card into your PC or SD card reader.

    .. figure:: img/SDcard_insert.jpg
        :align: center
        :width: 600

#. Download |balenaEtcher| and install it.

#. Open the Balena Etcher application.

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



.. _linux_gui:

=====
Linux
=====

.. note::

    We recommend using |balenaEtcher| on Linux. Follow the same instructions as for :ref:`Windows <windows_gui>`.

Alternatively, use the built-in Image Writer tool:

#. Right-click on the extracted SD card image and select **Open With > Disk Image Writer**.

    .. figure:: img/DIW_1.png
        :align: center
        :width: 800

#. In the **Restore Disk Image** window, select your SD card in the **Destination** pull-down menu.
   Be careful to select the correct device; use the size for orientation (for example, a 16 GB SD card).

    .. figure:: img/DIW_3.png
        :align: center
        :width: 800

#. You will be asked to confirm your choice and enter a password.

.. note::

    For command-line installation using ``dd`` and other advanced options, see the :ref:`Advanced SD card guide <sdcard_advanced>`.



.. _macos_gui:

=====
macOS
=====

.. note::

    We recommend using |balenaEtcher| on macOS. Follow the same instructions as for :ref:`Windows <windows_gui>`.

Alternatively, use ApplePi-Baker:

#. Insert the SD card into your PC or SD card reader.

    .. figure:: img/SDcard_insert.jpg
        :align: center
        :width: 600

#. Download |ApplePi-Baker|.

#. Open ApplePi-Baker and enter your admin password when prompted.

#. Select the SD card drive by recognizing its size.

    .. figure:: img/SDcard_macOS_ApplePi-Baker_drive.png
        :align: center
        :width: 1000

#. Select the Red Pitaya OS image file and wait for the writing process to complete.

    .. figure:: img/SDcard_macOS_ApplePi-Baker_image.png
        :align: center
        :width: 1000

.. note::

    For command-line installation using ``dd`` and other advanced options, see the :ref:`Advanced SD card guide <sdcard_advanced>`.





.. substitutions

.. |CHANGELOG| replace:: :rp-github:`CHANGELOG <RedPitaya/blob/master/CHANGELOG.md>`


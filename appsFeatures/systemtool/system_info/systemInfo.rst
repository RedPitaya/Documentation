.. _system_info:

###############
System Info
###############

In the four corners of the Red Pitaya web interface there are the following widgets:

.. image:: img/System_info.jpg
    :align: center
    :width: 1000


1. **General System information button:** Includes optional features that can be turned ON/OFF. For more information see the section below.
2. **Power button:** Manual *Power Off* or *Reboot* of the board.
3. **Download system report:** Downloads a .zip file with information for the developers. Please attach it to the support mail with the issue description. The report should download after approx. 15 seconds.
4. **Current OS and ecosystem version:** Reroutes to the :ref:`Software update tool <software_update_manager>` if clicked. At boot, Red Pitaya checks for software updates and displays a yellow exclamation mark here if a new release is available.


General OS and Ecosystem info
=================================

Once the Info button is clicked, the following settings will be displayed:

.. image:: img/Info_button.png
    :align: center
    :width: 800

In the **System Info** section, general information regarding *Board model*, *MAC address*, *DNA number*, etc. is displayed.

.. note::

    The ecosystem version for nightly builds is labelled 2.00-0, as shown in the image above.

The **System Settings** section contains the following options:

    1. **Boot-up File consistency check:** If checked, during the boot, a file system check of the SD card is performed, which increases the overall boot-up time.
    2. **Turn ON LED:** If checked, the Red (Heartbeat) and Orange (SD card read) LEDs are enabled.
    3. **BOOT mode:** Some board models (SIGNALlab 250-12 and STEMlab 125-14 Gen2 Z7020 Pro) have a button **Up to 1 GB RAM** located here (see the picture below). If highlighted, the board boots with 1 GB RAM instead of 512 MB.
    4. **Restore default app settings:** Restores all saved application settings to default values.

.. figure:: img/Info_button_250-12.png
    :align: center
    :width: 800

    System information on SIGNALlab 250-12.


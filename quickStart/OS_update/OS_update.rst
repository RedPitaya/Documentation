
.. _os_update:

########################
Update Red Pitaya OS
########################

Red Pitaya OS can be upgraded by:

1. The **Software update manager** application, which can be accessed from the main web interface by clicking on the **ecosystem version label** in the bottom right corner, or by opening the **System** menu.
   Instructions for updating the operating system using the Software Update Manager are described in the :ref:`software_update_manager` section.

    * This method requires an Internet connection on the Red Pitaya board. See the :ref:`Network manager <network_manager>` section for more information on how to connect your Red Pitaya board to the Internet.
    * Can only upgrade the ecosystem version, not the Linux version.

    .. figure:: img/OS_update_app_menu.png
        :width: 600

#. **Manually update the OS** by downloading the latest SD card image from the Red Pitaya website and flashing it to the SD card. Instructions for manually updating the OS are described in the :ref:`prepare SD card <prepareSD>` section.

#. The **Updater command line tool** can be used to automatically update the **nightly build** ecosystem version. For more information on using the updater command line tool, refer to the :ref:`ecosystem update utility <update_util>` section.

We recommend :ref:`manually updating the operating system <prepareSD>`, as it is common for the Linux operating system to change between official OS releases.
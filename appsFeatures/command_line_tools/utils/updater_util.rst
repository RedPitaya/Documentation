.. _update_util:

Ecosystem update utility
========================

**Software requirements:**

* **IN-DEV** Red Pitaya OS version or newer.

The ecosystem update utility is used to automatically update the Red Pitaya ecosystem to one of the latest Nightly Build versions. It can be run from the terminal on the Red Pitaya board. The utility can access the Nightly build database on the `Red Pitaya downloads website <https://downloads.redpitaya.com/downloads/>`_, download the specified Nightly build ecosystem version and install it on the board.

.. code-block:: console

    root@rp-f0a235:~# updater
    updater Version: 2.07-501-e1eff7e0a

    Usage: updater -m file,file,...
        updater -d URL [-v]
        updater -n FILE [-v]
        updater -n NUMBER [-v]
        updater -i FILE [-v]
        updater -i NUMBER [-v]
        updater -l
        updater -r

    --md5=FILES           -m FILES     Calculates md5 for the specified files.
    --download=URL        -d URL       Downloads a file to a directory: /home/redpitaya/ecosystems.
    --download_nb=FILE    -n FILE      Download ecosystem by file name from NB server.
    --download_nb=NUMBER  -n NUMBER    Download ecosystem by build number from NB server.
    --install=FILE        -i FILE      Installs the ecosystem by file name on the SD card.
    --install=NUMBER      -i NUMBER    Installs the ecosystem by build number on the SD card.
    --list                -l           List of loaded ecosystems.
    --list_nb             -r           List of ecosystems on the server in the NB folder.
    --verbose             -v           Produce verbose output.

Here are the setps to use the updater utility:

#. List the ecosystems on the server using the **-r** option. THe program automatically checks the contents of the file and the contents of the archives and compares the MD5 sums.
    The list will show the file names and their status (``OK`` or ``BROKEN``), depending on the MD5 sum.

#. Download the ecosystem from the Nightly build server using the **-n** option. The file name can be specified or the build number (for example, 495) can be used. The downloaded file will be saved in the **/home/redpitaya/ecosystems** directory.
    Alternatively, if Red Pitaya does not have access to the internet, the file can be downloaded from the Nightly build server, transfered to the Red Pitaya and copied to the **/home/redpitaya/ecosystems** directory.

#. List the locally available ecosystems using the **-l** option. The list will show the file names and their status (``OK`` or ``BROKEN``).

#. Install the downloaded ecosystem using the **-i** option. The file name can be specified or the build number (for example, 495) can be used.

#. Reboot the Red Pitaya board to apply the changes.

.. note::

    Some Nightly build ecosystems will also require an update to the Red Pitaya Linux OS.
    The Ecosystem update utility cannot update the Red Pitaya Linux version. To update the Linux version, please follow the instructions in the :ref:`Prepare SD card <prepareSD>` section.


**Examples of use:**

Downloading an ecosystem from the Nightly build server:

.. code-block:: console

    root@rp-f0f0f1:~# updater -n 400 -v
    [==================================================] 100.0% (4.7 MB/s)

    File downloaded: ecosystem-2.05-400-2e2b7a22c.zip

Listing the ecosystems on the server:

.. code-block:: console

    root@rp-f0f0f1:~# updater -l
    ecosystem-2.05-400-2e2b7a22c.zip    [BROKEN]
    ecosystem-2.07-495-58e93bf58.zip    [OK]
    ecosystem-2.07-493-d5436699b.zip    [OK]

Installing a downloaded ecosystem:

.. code-block:: console

    root@rp-f0f0f1:~# updater -i 495 -v
    Unzip   [==================================================] 100.0% (5009/5009)
    Install [==================================================] 100.0% (5009/5009)
    The board needs to be rebooted.


Other ways to update the ecosystem and Red Pitaya Linux OS
------------------------------------------------------------

.. include:: ../../../quickStart/OS_update/OS_update_options.inc


Source code
------------

The Red Pitaya GitHub repository contains the `source code for the Ecosystem update utility <https://github.com/RedPitaya/RedPitaya/tree/master/Test>`_.

.. TODO:: Update link to the source code.

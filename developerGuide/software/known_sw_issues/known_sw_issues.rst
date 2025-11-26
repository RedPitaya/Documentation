.. _known_sw_issues:

########################
Known software issues
########################

.. TODO Add new issues

In this section is a list of known software issues with the Red Pitaya platforms on 2.00 OS. These issues will be fixed with the next major software updates.


Streaming application EOL error
================================

The :ref:`Streaming desktop application <stream_desktop_app>` and :ref:`command line client <stream_command_client>` are not working on beta OS version 2.05-37. Red Pitaya unit reports an EOL error within two minuts of starting the desktop application. This also affects the command line client, where specifying the stream time (-t) parameter will cause the same error.

This issue is fixed in the latest :ref:`Nightly Build OS versions <nightly_builds>`. We will fix this issue in the next official OS release.

Please use the :ref:`2.04-35 OS version <prepareSD>` for the streaming application until the issue is resolved.


Direct connection on MAC
===========================

If a MAC computer will not connect to the Red Pitaya, it is possible that **Content and Privacy Settings** are blocking websockets.  After updating the settings you will need to log out and log in again. It may be necessary to completely disable **Content and privacy settings**.

.. figure:: img/MAC_content_privacy.png
    :width: 800

.. figure:: img/MAC_content_privacy2.png
    :width: 600

|


Wi-Fi Low Signal Bug
======================

The Wi-Fi dongles, when connected to the Red Pitaya board (all board models), show incorrect signal levels for some Wi-Fi networks (0 out of 5 bars).
When connected to a laptop, the same Wi-Fi dongles work and show correct levels.

This issue will be resolved in a future OS version by updating the Linux kernel driver to 6.3.

We also plan on adding support for new Wi-Fi dongles.



I2C SCPI fails after 508 R/W attempts
=======================================

When using the SCPI server to continuously read an I2C device, the SCPI server hangs when retrieving data from the 508th transmission.

.. code-block:: console

    9560,"*I2C:IOctl:Write:Buffer2 Failed write buffer to i2c: Failed to init I2C."

There was a problem with the I2C devices not closing and after a while crashing with an error that there weren't enough descriptors.

The problem is fixed in Nightly Build versions 613 or higher.





Fixed
======


Web interface constantly reloading when using direct ethernet connection
--------------------------------------------------------------------------

**Fixed on OS version 2.05-37 and higher**

When connecting the Red Pitaya directly to a computer via an ethernet cable, the web interface constantly reloads. This issue is not present when using a network switch or router.


Local network visibility
--------------------------

**Fixed on OS versions 2.05-37 and higher**

Red Pitaya does not appear in the ARP table at boot time (when using the "arp -a" command). It is still pingable and appears in the ARP table when a connection is made to the rp-xxxxxx.local address.


STEMlab 125-10 Out-of-Memory
-----------------------------

**Fixed on Nightly Build versions 447 or higher together with Linux 2.06**

STEMlab 125-10 has 256 MB (2 Gb) of RAM, which is half the resources of STEMlab 125-14 (512 MB (4 Gb)). With the revision of the applications in the 2.00 OS, the applications require more RAM resources than before, which overloads the resources of STEMlab 125-10 (causes the Logic Analyzer application to crash on startup with an out-of-memory error from NGINX).

.. note::

    Please note that STEMlab 125-10 will soon reach end-of-life for software support (exact date to be determined). All users will be notified in advance. Before this happens, we will provide a final OS version where all applications will work.

**For previous OS versions, please follow the instructions below:**

Currently, the fastest solution is to add a SWAP space to the Red Pitaya's SD card (about 1 GB should be sufficient).
Here are instructions on how to `add a SWAP file to Ubuntu OS <https://www.digitalocean.com/community/tutorials/how-to-add-swap-space-on-ubuntu-22-04>`_

It may be necessary to increase the size of the Red Pitaya OS partition on the SD card:

* Create a copy of the Red Pitaya OS on the SD card (e.g. using the `dd` command).
* Resize the OS partition on the SD card using a tool like `parted`.
* Add SWAP space.

For more information on SWAP, see the link above.


SIGNALlab 250-12 output voltage range
---------------------------------------

On 1.04 OS versions, the oscilloscope application on SIGNALlab 250-12 has issues with setting output voltage range (gain x1 and gain x5) and cannot reach ±10 V.

The issue is not present when using the SCPI or API commands.

The issue is fixed in the 2.00 OS versions.

|
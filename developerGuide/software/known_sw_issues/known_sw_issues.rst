.. _known_sw_issues:

########################
Known software issues
########################

In this section is a list of known software issues with the Red Pitaya platforms on 2.00 OS. These issues will be fixed with the next major software updates.



Direct connection on MAC
===========================

If a MAC computer will not connect to the Red Pitaya, it is possible that **Content and Privacy Settings** are blocking websockets.  After updating the settings you will need to log out and log in again. It may be necessary to completely disable **Content and privacy settings**.

.. figure:: img/MAC_content_privacy.png
    :width: 800

.. figure:: img/MAC_content_privacy2.png
    :width: 600

|

STEMlab 125-10 Out-of-Memory
=============================

STEMlab 125-10 has 256 MB (2 Gb) of RAM, which is half the resources of STEMlab 125-14 (512 MB (4 Gb)). With the revision of the applications in the 2.00 OS, the applications require more RAM resources than before, which overloads the resources of STEMlab 125-10 (causes the Logic Analyzer application to crash on startup with an out-of-memory error from NGINX).

.. note::

    Please note that STEMlab 125-10 will soon reach end-of-life for software support (exact date to be determined). All users will be notified in advance. Before this happens, we will provide a final OS version where all applications will work.

Currently, the fastest solution is to add a SWAP space to the Red Pitaya's SD card (about 1GB should be sufficient).
Here are instructions on how to add a SWAP file to the Red Pitaya: `https://www.digitalocean.com/community/tutorials/how-to-add-swap-space-on-ubuntu-22-04`_

It may be necessary to increase the size of the Red Pitaya OS partition on the SD card:

- Create a copy of the Red Pitaya OS on the SD card (e.g. using the `dd` command).
- Resize the OS partition on the SD card using a tool like `parted`.
- Add SWAP space

For more information on SWAP, see the link above.

|

Wi-Fi Low Signal Bug
======================

The Wi-Fi dongles, when connected to the Red Pitaya board (all board models), show incorrect signal levels for some Wi-Fi networks (0 out of 5 bars).
When connected to a laptop, the same Wi-Fi dongles work and show correct levels.

This issue will be resolved in a future OS version by updating the Linux kernel driver to 6.3.



Fixed
======

Local network visibility
--------------------------

**Fixed on OS versions 2.05-37 and higher**

Red Pitaya does not appear in the ARP table at boot time (when using the "arp -a" command). It is still pingable and appears in the ARP table when a connection is made to the rp-xxxxxx.local address.


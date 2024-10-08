.. _known_sw_issues:

########################
Known software issues
########################

In this section is a list of known software issues with the Red Pitaya platforms ordered by the Red Pitaya OS release version. These issues will be fixed with the next major software updates.

==========
2.05-37
==========

Fixed
-------

- Local network visibility fixed


STEMlab 125-10 out-of-memory
-----------------------------

..TODO


Direct connection on MAC
-------------------------

If a MAC computer does not want to connect to the Red Pitaya, it is possible that **Content and privacy settings** are blocking websockets.  After updating settings you must log out and log in again. It may be necessary to completely disable the **Content and privacy settings**.

.. figure:: img/MAC_content_privacy.png
    :width: 800

.. figure:: img/MAC_content_privacy2.png
    :width: 600


Wi-Fi Low Signal Bug
-----------------------

The Wi-Fi dongles, when plugged into the Red Pitaya board (all board models), show incorrect signal levels for some Wi-Fi networks (0 out of 5 bars).
When connected to a laptop the same Wi-Fi dongles work and show correct levels.

This issue will be fixed by updating the Linux kernel driver to 6.3.



==========
2.04-35
==========

Local network visibility
---------------------------

Red Pitaya does not appear in the ARP table upon boot (when using the "arp -a" command). It is still pingable and appears in the ARP table upon establishing connection through the rp-xxxxxx.local address.


Direct connection on MAC
-------------------------

If a MAC computer does not want to connect to the Red Pitaya, it is possible that **Content and privacy settings** are blocking websockets.  After updating settings you must log out and log in again. It may be necessary to completely disable the **Content and privacy settings**.

.. figure:: img/MAC_content_privacy.png
    :width: 800

.. figure:: img/MAC_content_privacy2.png
    :width: 600


Wi-Fi Low Signal Bug
-----------------------

The Wi-Fi dongles, when plugged into the Red Pitaya board (all board models), show incorrect signal levels for some Wi-Fi networks (0 out of 5 bars).
When connected to a laptop the same Wi-Fi dongles work and show correct levels.

This issue will be fixed by updating the Linux kernel driver to 6.3.


STEMlab 125-10 logic analyzer
----------------------------------

The logic analyzer application fails to load on the STEMlab 125-10. Please use an older version of the OS.



==========
2.00-30
==========

Local network visibility
---------------------------

Red Pitaya does not appear in the ARP table upon boot (when using the "arp -a" command). It is still pingable and appears in the ARP table upon establishing connection through the rp-xxxxxx.local address.


Wi-Fi Low Signal Bug
-----------------------

The Wi-Fi dongles, when plugged into the Red Pitaya board (all board models), show incorrect signal levels for some Wi-Fi networks (0 out of 5 bars).
When connected to a laptop the same Wi-Fi dongles work and show correct levels.

This issue will be fixed by updating the Linux kernel driver to 6.3.



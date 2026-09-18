
Red Pitaya Gen 2 boards support two physical power inputs: 

1. **USB-C connector**
2. **+5V pin (pin 1) and GND pin (pin 25,26) on the |E2| connector**

The sections below describe the supported powering scenarios and their implications.

|

**External Power Specifications:**

+--------------------------+-----------------------------+
| **Parameter**            | **Specification**           |
+==========================+=============================+
| Power supply voltage     | 5 V                         |
+--------------------------+-----------------------------+
| Maximum current draw     | 3.0 A                       |
+--------------------------+-----------------------------+
| Power supply type        | DC                          |
+--------------------------+-----------------------------+
| Abs. max. voltage        | 5.5 V                       |
+--------------------------+-----------------------------+
| Abs. min. voltage        | 4.5 V                       |
+--------------------------+-----------------------------+

.. note::

    The board's maximum current draw is 3.0 A. The power supply may have a higher current rating — this will not cause any issues.

.. note::

    **Why is power protection implemented?**
    The USB-C protection circuit was introduced because boards were being powered from computer USB ports, which typically provide 0.5–0.9 A — insufficient for reliable operation 
    and likely to cause reboots and network disconnections.

|

**Powering scenario 1 — Recommended: USB-C with a standard USB-C power supply**

Connect a USB-C power supply (5 V, 3 A) with functional CC lines to the USB-C connector. Leave jumper **JP5 unbridged** (default).

* The USB-C protection circuit detects the CC lines and confirms the supply is USB-C compliant.
* The **Power Error LED remains off**, indicating normal operation.
* Full overcurrent protection (3.0 A PTC resettable fuse) is active.

.. note::

    A USB-C power supply without CC lines (e.g. a simple 2-wire USB-C cable with a generic 5 V adapter) will **not** satisfy the protection circuit and will cause the Power Error LED 
    to light up, as described in scenario 2b below.

|

**Powering scenario 2 — Alternative: 2-pin (non-USB-C) power supply**

If a 2-wire 5 V power supply is used (no CC lines), there are two connection options:

**2a — Via the E2 connector (+5V pin)**

Connect the supply directly to pin 1 (+5V) and pin 25/26 (GND) on the |E2| connector. The JP5 jumper state does not matter in this case.

* The USB-C protection logic is entirely bypassed — the protection circuit is not in the power path.
* The 3.0 A PTC resettable fuse on the |E2| +5V pin remains active for overcurrent protection.
* The **Power Error LED will be on**, because the USB-C protection circuit receives board power but no CC line signal.

**2b — Via the USB-C connector**

Connect the 2-wire supply through the USB-C connector. **JP5 must be bridged** to allow power flow in this configuration.

* The USB-C protection circuit is in the power path and receives power, but receives no CC line signal.
* The **Power Error LED will be on** — this is expected behaviour, not a fault.
* It is the user's responsibility to verify that the supply provides a stable 5 V at up to 3 A.

.. warning::

    When using scenario 2 (either sub-option), the **Power Error LED being on is expected and does not indicate a hardware fault**. It indicates that the USB-C protection circuit cannot 
    verify the connected supply's compliance. The user must ensure the supply meets the 5 V / 3 A specification independently.

|

**Available Power Rails on Extension Connectors:**

The |E1| and |E2| connector expose several power rails that can be used to supply power to **external devices or circuits connected to the board**. The current limits below are the maximum currents that Red Pitaya can source from each rail to external loads — they are not related to the board's own power consumption.

+--------------------------+-----------------------------+
| **Voltage Rail**         | **Max. Sourceable Current** |
+==========================+=============================+
| +5 V                     | 0.5 A [#f13]_               |
+--------------------------+-----------------------------+
| -5 V                     | 0.1 A                       |
+--------------------------+-----------------------------+
| +3V3                     | 0.5 A [#f13]_               |
+--------------------------+-----------------------------+

.. note::

    Exceeding these limits may cause voltage rail instability or trigger the board's protection circuitry, which can result in a board reset or shutdown.

The +5V pin on |E2| (pin 1) also serves as a power input when using powering scenario 2a. In that role it is protected by a 3.0 A PTC resettable fuse located on the PCB near the |E2| connector.


Red Pitaya boards can be powered through two methods:

1. **Micro USB connector**
2. **+5V pin (pin 1) and GND pin (pin 25, 26) on the |E2| connector**

**Power Supply Specifications:**

+--------------------------+-----------------------------+
| **Parameter**            | **Specification**           |
+==========================+=============================+
| Power supply voltage     | 5 V                         |
+--------------------------+-----------------------------+
| Maximum current draw     | 2.0 A                       |
+--------------------------+-----------------------------+
| Power supply type        | DC                          |
+--------------------------+-----------------------------+

.. note::

    The board's maximum current draw is 2.0 A. The power supply may have a higher current rating — this will not cause any issues.

The micro-USB power input includes a simple integrated protection circuit that prevents damage to the board.

.. figure:: ../hw_specs/img/schematics/Protection.png
    :width: 600
    :align: center

    Protection circuit for powering through the micro-USB connector

.. warning::

    When powering the Red Pitaya through the extension connector (+5V pin on |E2|), external protection must be provided by the user to protect the board 
    from overvoltage and overcurrent conditions.

|

**Available Power Rails on Extension Connectors:**

The |E1| and |E2| connectors expose several power rails that can be used to supply power to **external devices or circuits connected to the board**. The current 
limits below are the maximum currents that Red Pitaya can source from each rail to external loads — they are not related to the board's own power consumption.

+--------------------------+-----------------------------+
| **Voltage Rail**         | **Max. Sourceable Current** |
+==========================+=============================+
| +5 V                     | 0.5 A [#f10]_               |
+--------------------------+-----------------------------+
| +3V3                     | 0.5 A [#f10]_               |
+--------------------------+-----------------------------+
| -3.3V / -3.4V / -4 V     | 0.05 A                      |
+--------------------------+-----------------------------+

.. note::

    Exceeding these limits may cause voltage rail instability, which can result in a board reset or shutdown.

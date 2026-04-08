
The Original generation Red Pitaya boards feature SATA connectors for multi-board synchronisation (daisy-chaining).

**Synchronisation Connectors:**

+--------------------------+-----------------------------+
| **Parameter**            | **Specification**           |
+==========================+=============================+
| Connector type           | SATA                        |
+--------------------------+-----------------------------+
| Number of connectors     | 2 (for daisy-chaining)      |
+--------------------------+-----------------------------+
| Maximum data rate        | up to 500 Mb/s              |
+--------------------------+-----------------------------+
| Purpose                  | Clock and trigger sync      |
+--------------------------+-----------------------------+

.. note::

    The SATA connectors are meant to be used for synchronising multiple Red Pitaya boards. They are not compatible with standard SATA storage devices (voltage 
    levels are 1V8), so extra care must be taken when connecting external devices to these connectors to avoid damaging the board.

.. note::

    For multi-board synchronisation, the secondary boards require hardware modification (resistor relocation: R25, R26 → R27, R28) to receive the clock signal through the 
    SATA connectors. Please refer to the :ref:`External ADC Clock section <external_125_14>` for more information.

.. seealso::

    * :ref:`X-channel system specifications <top_125_14_MULTI>` - Multi-channel system details
    * :ref:`X-channel 2.0 (Click Shield) synchronisation <click_shield_sync>` - Alternative synchronisation method for Original and Gen 2 boards
    * :ref:`Multi-board synchronisation examples <examples_multiboard_sync>` - Software examples

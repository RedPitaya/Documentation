
The Original generation Red Pitaya boards feature SATA connectors that are connected directly to the FPGA. Unlike the STEMlab 125-14, this board does not support multi-board clock 
synchronisation through the SATA connectors — the shared clock signal does not propagate to the ADC and DAC, so true synchronisation is not achievable this way. The connectors can 
still be used to exchange clock, trigger, or data signals between boards or external devices.

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

    The SATA connectors use 1V8 logic levels, which is non-standard for SATA connections. They are **not** compatible with standard SATA storage devices. Exercise caution when 
    connecting external devices to these connectors to avoid damaging the board.


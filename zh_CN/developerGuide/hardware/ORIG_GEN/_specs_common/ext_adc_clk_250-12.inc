
The main ADC, DAC, and FPGA CLK signal can be supplied from an external source through the **Ext. ADC Clk±** ports on the |E2| connector.

**Signal Path**

The clock signal travels directly through the ADC, then to the FPGA, and DAC, ensuring consistent timing across the signal acquisition path.

|

**External Clock Specifications**

The external clock should be a differential LVDS signal:

+-------------------------------------------------------+----------------------------------------------+---------+---------+---------+---------+
| Parameter                                             | Description                                  | Min     | Typ     | Max     | Unit    |
+=============================+=========================+==============================================+=========+=========+=========+=========+
|                             | Clock input pins        | 23 (Clk+) and 24 (Clk-) on |E2|              |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
|                             | Input standards         | LVDS                                         |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
|                             | Input clock coupling    | AC (on-board capacitors)                     |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| :math:`f_{CLK}`             | Input frequency range   | ADC and DAC dependant                        | 1       |         | 250     | MHz     |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| :math:`V_{ID,DIFF,PP}`      | Input voltage swing     | Differential peak-to-peak                    |         | 0.35    | 0.8     | V       |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| IDC                         | Input clock duty cycle  |                                              | 45%     |         | 55%     |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+

.. note::

    The typical operating frequency for the SIGNALlab 250-12 is **250 MHz**.

    Operating outside the board's specified frequency is possible but voids all performance guarantees. See the warning below.

For exact voltage levels and timing requirements, please refer to the oscillator datasheet.

.. warning::

    **Not a reference clock input:** The Ext. ADC Clk± ports are not a reference clock input for a PLL or any other timing circuit. 
    They directly drive the main sampling clock for the ADC, DAC, and FPGA. Connecting a reference clock signal intended for a PLL will 
    not function as expected.

    For locking to an external frequency reference, use the dedicated :ref:`10 MHz SMA reference clock input <top_250_12>` on the back panel.

.. warning::

    **Changing the external clock frequency during operation is not supported.**

    The Zynq 7020 PL uses Mixed-Mode Clock Managers (MMCMs) and PLLs to derive internal fabric clocks from the input clock.
    Changing the external clock frequency during operation will cause the MMCM/PLL to lose lock, resulting in undefined output clocks
    and acquisition/generation errors. A full FPGA reset or reconfiguration is required after any clock frequency change.


.. note::

    **Operating at non-standard clock frequencies:**

    The Red Pitaya FPGA is designed, tested, and guaranteed to operate correctly at the board's specified core clock frequency (250 MHz for SIGNALlab 250-12).
    
    While it is possible to run the board at different clock frequencies, please be aware that:
    
    1. **FPGA functionality:** The official FPGA configuration may not function as intended at non-standard frequencies and requires thorough testing
    2. **Sampling rates:** The ADC and DAC sampling rates will change proportionally with the clock frequency
    3. **Analog bandwidth:** The analog bandwidth of the board will change with the clock frequency
    4. **Absence of external clock:**
    
       * **OS 2.07-48 or higher:** If no valid external clock is present, the PS side will boot using an internal 33 MHz oscillator, but the FPGA will not operate (no signal acquisition/generation functionality)
       * **OS versions prior to 2.07-48:** The board will fail to boot (stuck in reboot cycle) if no valid external clock is detected

.. note::

    **Advanced: Dynamic clock reconfiguration**

    The standard Red Pitaya FPGA bitstream does not implement the Dynamic Reconfiguration Port (DRP) interface that AMD (Xilinx) provides for
    runtime MMCM/PLL reconfiguration. A custom FPGA design using DRP-based MMCM reconfiguration with active lock monitoring could theoretically
    support runtime clock frequency changes, but this requires extensive FPGA development and verification. The PS side (ARM/Linux) is not affected
    by clock changes, as it runs from its own independent 33 MHz crystal-derived PLL.

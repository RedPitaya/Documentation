
The main ADC, DAC, and FPGA CLK signal can be supplied from an external source through the **Ext. ADC Clk±** ports on the |E2| connector.

**Clock Selection**

Both the internal oscillator clock and the external clock signal are connected to the `NB6L72`_ Differential Crosspoint Switch.
The **CLK_SEL** pin (pin 21 on |E2|) is used to select the clock source:

* **3V3 (logic high) or unconnected:** Internal clock (default), supplied from the onboard oscillator.
* **GND (logic low):** External clock, supplied through the Ext. ADC Clk± ports.


**Signal Path**

The clock signal travels from the output of the `NB6L72`_ through the ADC to the FPGA and DAC, ensuring consistent timing across the signal acquisition path.


**External Clock Specifications**

The external ADC clock should comply with `NB6L72`_ input specifications:

+-------------------------------------------------------+----------------------------------------------+---------+---------+---------+---------+
| Parameter                                             | Description                                  | Min     | Typ     | Max     | Unit    |
+=============================+=========================+==============================================+=========+=========+=========+=========+
|                             | Clock input pins        | 23 (Clk+) and 24 (Clk-) on |E2|              |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
|                             | Input standards         | LVPECL, CML, LVDS, LVCMOS, LVTTL             |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
|                             | Input clock coupling    | AC (on-board capacitors)                     |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| :math:`f_{CLK}`             | Input frequency range   |                                              | 1       |         | 125     | MHz     |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| :math:`V_{ID,DIFF,PP}`      | Input voltage swing     | Differential peak-to-peak                    | 150     |         | 3300    | mV      |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| IDC                         | Input clock duty cycle  |                                              | 45%     |         | 55%     |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+

.. note::

    The typical operating frequency depends on the board variant:

    * **STEMlab 125-14 Gen 2 boards:** 125 MHz

    Operating outside the board's specified frequency is possible but voids all performance guarantees. See the warning below.

.. note::

    The board includes AC coupling capacitors on the external clock inputs, so the input signal must have sufficient amplitude and slew rate to meet 
    the `NB6L72`_ input specifications after AC coupling.

    For further information on voltage levels and timing requirements, please refer to the `NB6L72`_ datasheet.

.. warning::

    **Not a reference clock input:** The Ext. ADC Clk± ports are not a reference clock input for a PLL or any other timing circuit. 
    They directly drive the main sampling clock for the ADC, DAC, and FPGA. Connecting a reference clock signal intended for a PLL will 
    not function as expected.

.. warning::

    **Changing the external clock frequency during operation is not supported.**

    The Zynq 7010/7020 PL uses Mixed-Mode Clock Managers (MMCMs) and PLLs to derive internal fabric clocks from the input clock.
    Changing the external clock frequency during operation will cause the MMCM/PLL to lose lock, resulting in undefined output clocks
    and acquisition/generation errors. A full FPGA reset or reconfiguration is required after any clock frequency change.

.. note::

    **Operating at non-standard clock frequencies:**

    The Red Pitaya FPGA is designed, tested, and guaranteed to operate correctly at the board's specified core clock frequency 
    (125 MHz for STEMlab 125-14, 122.88 MHz for SDRlab 122-16, etc).
    
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

.. note::

    When synchronising multiple Red Pitaya boards, please keep in mind that:

    * :ref:`X-channel 2.0 synchronisation (Click Shields) <click_shield>` works out-of-the-box
    * :ref:`X-channel synchronisation <x-ch_streaming>` requires a hardware modification as secondary boards differ from the primary board

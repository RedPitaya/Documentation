
Similar to Gen 2 boards, the TI boards also support an external clock input. The main difference, however, is that the TI boards use the `LMK03318`_ Clock Generator, which includes a PLL, 
frequency synthesizer with integrated VCO, and multiple output drivers instead of just a simple clock switch. The main ADC, DAC, and FPGA CLK signals are all synthesized from the `LMK03318`_ 
and can differ from each other and the external clock. This means that the external clock supplied through the **Ext. ADC Clk±** ports on the |E2| connector can act as a reference for 
the `LMK03318`_, which in turn generates the main sampling clocks for the ADC, DAC, and FPGA.

By default, the `LMK03318`_ is configured to accept a 125 MHz reference clock, which is then used to generate the 125 MHz sampling clock for the DAC and FPGA, and the 125 MHz or 65 MHz 
sampling clock for the ADC (depending on the board). If a different external clock frequency is supplied, the `LMK03318`_ must be configured to use that reference frequency instead.
|

**Clock Selection**

Both the internal oscillator clock and the external reference clock signal are connected to the `LMK03318`_ Clock Generator.
The **CLK_SEL** pin (pin 21 on |E2|) is used to select the reference clock source:

* **3V3 (logic high) or unconnected:** Internal clock (default), supplied from the onboard oscillator.
* **GND (logic low):** External clock, supplied through the Ext. ADC Clk± ports.

|

**Signal Path**

The reference clock signal travels to the `LMK03318`_, where it is processed to generate the sampling clocks for the ADC, DAC, and FPGA, and then distributed to these components, 
ensuring consistent timing across the signal acquisition path.

|

**External Clock Specifications**

+-------------------------------------------------------+----------------------------------------------+---------+---------+---------+---------+
| Parameter                                             | Description                                  | Min     | Typ     | Max     | Unit    |
+=============================+=========================+==============================================+=========+=========+=========+=========+
|                             | Clock input pins        | 23 (Clk+) and 24 (Clk-) on |E2|              |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
|                             | Input standards         | LVPECL, LVDS, LVCMOS, CML, HCSL              |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
|                             | Input clock coupling    | AC (on-board capacitors)                     |         |         |         |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| :math:`f_{CLK}`             | Input frequency range   |                                              | 1       | 125     | 300     | MHz     |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| :math:`V_{ID,DIFF,PP}`      | Input voltage swing     | Differential peak-to-peak                    | 0.2     |         | 2.0     | V       |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| :math:`\frac{dV}{dt}`       | Input edge slew rate    | Differential, peak-to-peak                   | 0.5     |         |         | V/ns    |
|                             |                         +----------------------------------------------+---------+---------+---------+---------+
|                             | (20% to 80%)            | Single-ended, non-driven input tied to GND   | 0.5     |         |         | V/ns    |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+
| IDC                         | Input clock duty cycle  |                                              | 40%     |         | 60%     |         |
+-----------------------------+-------------------------+----------------------------------------------+---------+---------+---------+---------+

.. note::

    The board includes AC coupling capacitors on the external clock inputs, so the input signal must have sufficient amplitude and slew rate to meet 
    the `LMK03318`_ input specifications after AC coupling.

    For further information on voltage levels and timing requirements, please refer to the `LMK03318`_ datasheet.

|

**Configuring the external clock frequency**

The default `LMK03318`_ configuration is set for a **125 MHz reference clock**. If you want to use a different external clock frequency, you need to reconfigure the `LMK03318`_ registers 
accordingly. This can be done through the I2C interface using the Red Pitaya's PS side (ARM/Linux). The LMK03318 is available at I2C bus address 0b1010000 (0x50).

To change the reference frequency, you need to calculate the appropriate register settings for the desired frequency and write them to the `LMK03318`_ over I2C.

.. note::

    It is possible to switch the control of the I2C bus to the FPGA (PL side) and implement the I2C interface in the FPGA itself, but this is not supported in the standard Red Pitaya firmware 
    and requires custom FPGA development.

.. warning::

    **Changing the external clock frequency during operation is not supported.**

    The Zynq 7010/7020 PL uses Mixed-Mode Clock Managers (MMCMs) and PLLs to derive internal fabric clocks from the input clock.
    Changing the external clock frequency during operation will cause the MMCM/PLL to lose lock, resulting in undefined output clocks
    and acquisition/generation errors. A full FPGA reset or reconfiguration is required after any clock frequency change.

.. note::

    **Operating at non-standard clock frequencies:**

    The Red Pitaya FPGA is designed, tested, and guaranteed to operate correctly at the board's specified core clock frequency.
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

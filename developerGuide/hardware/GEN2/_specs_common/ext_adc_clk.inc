
The main ADC and FPGA CLK signal can be supplied from an external source through the **Ext. ADC Clk±** ports on the |E2| connector.

**Clock Selection**

Both the internal oscillator clock and the external clock signal are connected to the `NB6L72`_ Differential Crosspoint Switch.
The **CLK_SEL** pin (pin 21 on |E2|) is used to select the clock source:

* **3V3 (logic high) or unconnected:** Internal clock (default)
* **GND (logic low):** External clock


**Signal Path**

The clock signal travels from the output of the `NB6L72`_ through the ADC to the FPGA, ensuring consistent timing across the signal acquisition path.


**External Clock Specifications**

The external ADC clock should comply with `NB6L72`_ input specifications:

* **Differential LVDS signaling**
* **Power supply:** 3V3
* **Connector:** Pins 23 (Clk+) and 24 (Clk-) on |E2|

For exact voltage levels and timing requirements, please refer to the `NB6L72`_ datasheet.

.. note::

    When synchronising multiple Red Pitaya boards, please keep in mind that:

    * :ref:`Click Shield synchronisation <click_shield>` works out-of-the-box
    * :ref:`X-channel synchronisation <x-ch_streaming>` requires a hardware modification as secondary boards differ from the primary board

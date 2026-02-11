
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

    The Red Pitaya FPGA is designed, tested, and guaranteed to operate correctly at the board's specified core clock frequency 
    (125 MHz for STEMlab 125-14, 122.88 MHz for SDRlab 122-16, etc).
    
    While it is possible to run the board at different clock frequencies, please be aware that:
    
    - The FPGA may not function as intended at non-standard frequencies and requires thorough testing
    - The ADC and DAC sampling rates will change proportionally with the clock frequency
    - Lower clock frequencies will reduce the analog bandwidth of the board
    - Red Pitaya does not guarantee proper operation at frequencies other than the specified core clock
    
    The board will boot with any valid external clock signal. 2.07-48 and higher OS versions do not block boot-up if the external clock is absent.

.. note::

    When synchronising multiple Red Pitaya boards, please keep in mind that:

    * :ref:`Click Shield synchronisation <click_shield>` works out-of-the-box
    * :ref:`X-channel synchronisation <x-ch_streaming>` requires a hardware modification as secondary boards differ from the primary board

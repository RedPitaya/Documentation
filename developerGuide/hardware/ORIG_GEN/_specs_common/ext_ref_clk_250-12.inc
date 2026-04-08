
The SIGNALlab 250-12 features a dedicated **10 MHz SMA reference clock input** located on the back panel. This allows the board's internal oscillator output to be phase-locked to an external 10 MHz reference, enabling tight frequency synchronization with external instruments and other SIGNALlab 250-12 boards.

.. note::

    This is distinct from the :ref:`External ADC Clock <top_250_12>` input on the |E2| connector. The 10 MHz reference clock disciplines the onboard PLL/oscillator, while the External ADC Clock replaces the oscillator entirely as the direct sampling clock source.

|

**Reference Clock Specifications**

+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Parameter                                    | Description                              | Min     | Typ     | Max     | Unit    |
+==============================================+==========================================+=========+=========+=========+=========+
| Reference clock input frequency              |                                          |         | 10      |         | MHz     |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Input signal type                            | TTL/CMOS digital signal                  |         |         |         |         |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Input amplitude range                        |                                          | 0       |         | 5       | V       |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Threshold voltage V_T+ (positive)            |                                          |         | 1.5     |         | V       |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Threshold voltage V_T- (negative)            |                                          |         | 1.0     |         | V       |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Input impedance                              |                                          |         | 10      |         | kΩ      |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Input buffer IC                              | 74LVC1G14GW (Schmitt-trigger inverter)   |         |         |         |         |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Connector type                               | SMA                                      |         |         |         |         |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+
| Connector location                           | Back panel                               |         |         |         |         |
+----------------------------------------------+------------------------------------------+---------+---------+---------+---------+

.. warning::

    Only connect a 10 MHz reference clock to this input. Connecting signals at other frequencies or voltage levels may damage the board.

.. note::

    The higher the quality of the reference clock, the better the performance of the board's PLL and overall system stability.

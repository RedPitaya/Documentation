.. _imp_anal_app:

******************
Impedance Analyzer
******************

The Impedance analyzer application enables measurements of impedance, phase, and other parameters of the selected DUT (Device Under Test). Measurements can be taken in the **Frequency sweep** mode with a frequency resolution of 1 Hz or in the **Measurements sweep** mode with the desired number of measurements at a constant frequency. The selectable frequency range is from 1 Hz to 60 MHz, although the recommended frequency range is up to 1 MHz. The impedance range is from 0.1 Ω to 10 MΩ. When using the Impedance analyzer application with the LCR Extension module, insert 0 in the shunt resistor field.

.. figure:: LCR_2.png

.. note::

    The impedance range is dependent on the selected frequency and maximum accuracy, and a suitable measurement can not be performed at all frequencies and impedance ranges. The impedance range is given in the picture below. The range of capacitors or inductors can be extrapolated from the given picture. The basic accuracy of the Impedance Analyzer is 5%. The Impedance Analyzer application is calibrated for 1 m Kelvin probes. More accurate measurements can be performed in the **measurement sweep** mode at a constant frequency.

.. figure:: LCR_range.png

When using the Impedance Analyzer application, optimal results are achieved when the Red Pitaya GND is connected to your mains EARTH lead as is shown below. We also recommend shielding of Red Pitaya and the LCR extension module.

.. figure:: 600px-E_module_connection.png

In the pictures below are shown comparison measurements of the selected DUT. Measurements are taken with a Red Pitaya and a Keysight precision LCR meter. From these plots you can extract basic Red Pitaya accuracy.

.. note::

    The Red Pitaya LCR metre and Impedance Analyzer are not certified for certain accuracy or range.

.. figure:: 300px-LCR_100R.png
.. figure:: 300px-LCR_100K.png
.. figure:: 300px-LCR_1M.png

The Impedance Analyzer application can be used without the LCR Extension module using manual setting of the shunt resistor. This option is described below.

.. note::

    You will need to change the ``C_cable`` parameter in the code when using your setup.

.. figure:: 600px-Impedance_analyzer_manaul_R_Shunt.png

.. note::

    The Impedance Analyzer application is available on the Red Pitaya marketplace.

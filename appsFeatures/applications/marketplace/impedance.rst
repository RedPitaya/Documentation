******************
Impedance analyzer
******************

The Impedance analyzer application enables measurements of
Impedance, Phase and other parameters of the selected DUT (Device Under Test).
Measurements can be performed in the **Frequency sweep** mode
with 1Hz frequency resolution or in the **Measurements sweep** mode
with the desired number of measurements at constant frequency.
The selectable frequency range is from 1Hz to 60MHz,
although the recommended frequency range is up to 1MHz.
The impedance range is from 0.1 Ohm to 10 Mohm.
When using the Impedance analyzer application with the LCR Extension module,
insert 0 in the shunt resistor field.

.. figure:: LCR_2.png

Impedance analyzer application enables measurements of Impedance,
Phase and other parameters of selected DUT (Device Under Test).
Measurements can be performed in *Frequency sweep* mode
with 1Hz of frequency resolution or in *Measurements sweep* mode
with desired numbers of measurement at constant frequency.
Selectable frequency range is from 1Hz to 60MHz,
although the recommended frequency range is up to 1MHz*.
Impedance range is from 0.1 Ohm – 10 MOhm*.
When using Impedance analyzer application with LCR Extension module
insert 0 in the shunt resistor field.

.. note::

   Impedance range is dependent on the selected frequency and maximum accuracy
   and suitable measurement can not be performed at all frequencies and impedance ranges.
   Impedance range is given in picture bellow. Range for Capacitors or Inductors
   can be extrapolated from given picture. Basic accuracy of the Impedance analyzer is 5%.
   Impedance analyzer application is calibrated for 1 m Kelvin probes.
   More accurate measurements can be performed in Measurement sweep at constant frequency.

.. figure:: LCR_range.png

When using Impedance analyzer application optimal results are achieved wheni
the Red Pitaya GND is connected to your mains EARTH lead as is shown below.
We also recommend shielding of Red Pitaya and LCR extension module.

.. figure:: 600px-E_module_connection.png

On pictures below are shown comparison measurements of the selected DUT.
Measurements are taken with Red Pitaya and Keysight precision LCR meter.
From this plots you can extract basic Red Pitaya accuracy.

.. note::

    Red Pitaya LCR meter/Impedance analyzer are not certificated for certain accuracy or range.

.. figure:: 300px-LCR_100R.png
.. figure:: 300px-LCR_100K.png
.. figure:: 300px-LCR_1M.png

Impedance analyzer application can be used without LCR Extension module
using manual setting of shunt resistor. This option is described below.

.. note::

   You will need to change ``C_cable`` parameter in the code when using your setup.

.. figure:: 600px-Impedance_analyzer_manaul_R_Shunt.png

.. note::

   Impedance analyzer application is available on Red Pitaya marketplace.
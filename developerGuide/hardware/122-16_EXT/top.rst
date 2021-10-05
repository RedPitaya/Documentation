.. _top_122_16_EXT:

SDRlab 122-16 external clock
#############################

This SDRlab version is standard STEMlab 122-16 modified in such a way that the ADC and
DAC clock can be provided from an external source clock.
External clock should be connected to Ext ADC CLK- and + pins.
External clock signal levels should be LVDS in the range from 1MHz to 122.8MHz according to
ADC spec.

.. figure:: ../125-14/Extension_connector.png
   :align: center

For more information please refer to:

* `ADC specifications <https://www.analog.com/en/products/LTC2185.html>`_
* :ref:`RP clock wiring <external_122_16>`

For all other specifications please refer to standard :ref:`SDRlab 122-16 specs <top_122_16>`.
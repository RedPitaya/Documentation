.. _top_125_14_EXT:

STEMlab 125-14 external clock
#############################

   :ref:`Tachnical specification overview <rp-board-comp>`

This STEMlab version is standard STEMlab 125-14 modified in such a way that the ADC and
DAC clock can be provided from an external source clock.
External clock should be connected to Ext ADC CLK- and + pins.
External clock signal levels should be LVDS in the range from 1MHz to 125MHz according to
ADC spec.

.. figure:: ../125-14/Extension_connector.png
   :align: center

For more information please refer to:

* `ADC specifications <https://www.analog.com/media/en/technical-documentation/data-sheets/21454314fa.pdf>`_
* :ref:`RP clock wiring <external_125_14>`

For all other specifications please refer to standard :ref:`STEMlab 125-14 specs <top_125_14>`.
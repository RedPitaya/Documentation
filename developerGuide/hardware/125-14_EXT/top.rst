.. _top_125_14_EXT:

STEMlab 125-14 external clock
#############################

This STEMlab version is standard STEMlab 125-14 modified in such a way that the ADC and
DAC clock can be provided from an external source clock.
External clock should be connected to Ext ADC CLK- and + pins.
External clock signal levels should be LVDS in the range from 1MHz to 125MHz according to
ADC spec.

.. figure:: ../125-14/Extension_connector.png
   :align: center


*********
Technical
*********

* :ref:`Comparison of boards <rp-board-comp>`

**********
Schematics
**********

* `Red_Pitaya_Schematics_v1.0.1.pdf <https://downloads.redpitaya.com/doc//Red_Pitaya_Schematics_v1.0.1.pdf>`_

.. note::

    Red Pitaya board HW FULL schematics are not available. Red Pitaya has an open source code but not an open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connection and similar.

*************************
Mechanical specifications
*************************

* `Red_Pitaya_3Dmodel_v1.0.zip <https://downloads.redpitaya.com/doc/Red_Pitaya_3Dmodel_v1.0.zip>`_

******************
ADC specifications
******************

* `Data sheet <https://www.analog.com/media/en/technical-documentation/data-sheets/21454314fa.pdf>`_


***************
RP clock wiring
***************

* :ref:`External ADC clock <external_125_14>`


For all other specifications please refer to standard :ref:`STEMlab 125-14 specs <top_125_14>`.

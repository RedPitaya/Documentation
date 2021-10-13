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

*********
Technical specifications
*********

* :ref:`Product comparison table <rp-board-comp>`

**********
Schematics
**********

* `STEM122-16SDR_V1r1_Series1.PDF <https://downloads.redpitaya.com/doc/Customer_Schematics_STEM122-16SDR_V1r1%28Series1%29.PDF>`_

.. note::

    Red Pitaya board HW FULL schematics are not available. Red Pitaya has an open source code but not an open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connection and similar.

*************************
Mechanical specifications
*************************

* `STEM122-16SDR_V1r1_3Dpdf.zip <https://downloads.redpitaya.com/doc/STEM122-16SDR_V1r1_3Dpdf.zip>`_
* `STEM122-16SDR_V1r1_3Dstep.zip <https://downloads.redpitaya.com/doc/STEM122-16SDR_V1r1_3Dstep.zip>`_

******************
ADC specifications
******************

* `Data sheets <https://www.analog.com/en/products/LTC2185.html>`_


***************
RP clock wiring
***************

* :ref:`External ADC clock <external_122_16>`

For all other specifications please refer to standard :ref:`SDRlab 122-16 specs <top_122_16>`.
.. _top_125_14:

##############
STEMlab 125-14
##############


************************
Technical specifications
************************

* :ref:`Product comparison table <rp-board-comp>`

**********
Schematics
**********

* `Red_Pitaya_Schematics_v1.0.1.pdf <https://downloads.redpitaya.com/doc//Red_Pitaya_Schematics_v1.0.1.pdf>`_

.. note::

    FULL HW schematics for the Red Pitaya board are not available. Red Pitaya has open source code but not open hardware schematics. Nonetheless, DEVELOPMENT schematics are available. This schematic will give you information about HW configuration, FPGA pin connections, and similar.

*************************
Mechanical specifications
*************************

* `Red_Pitaya_3Dmodel_v1.0.zip <https://downloads.redpitaya.com/doc/Red_Pitaya_3Dmodel_v1.0.zip>`_


***********
Components
***********

* `ADC <https://www.analog.com/en/products/ltc2145-14.html>`_
* `DAC <https://www.analog.com/en/products/AD9767.html>`_
* `FPGA <https://docs.xilinx.com/v/u/en-US/ds190-Zynq-7000-Overview>`_
* `DC-DC converter <https://www.analog.com/en/products/LTC3615.html>`_
* `Oscillator <https://eu.mouser.com/datasheet/2/417/bf-8746.pdf>`_
* `SRAM-DDR3 <https://www.digikey.com/en/products/detail/micron-technology-inc/MT41J256M16HA-125-E/4315785>`_
* `QSPI <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_



**************
Fast analog IO
**************

.. toctree::
   :maxdepth: 6

   fastIO

*********
Extension
*********

.. toctree::
   :maxdepth: 6

   extent


.. _external_125_14:

******************
External ADC clock
******************

The ADC clock can be provided by:

    * On board 125MHz XO (default)
    * From an external source/through extension connector :ref:`E2 <E2>` (R25, R26 should be moved to location R23, R24)
    * Directly from the FPGA (R25, R26 should be relocated to R27, R28) 

.. figure:: External_clk.png
    :alt: Logo
    :align: center

    Schematic


.. figure:: External_clock_top.png
    :alt: Logo
    :align: center

    Top side


.. figure:: External_clock_bottom.png
    :alt: Logo
    :align: center

    Bottom side

.. figure:: External_clock_bottom_photo.png
    :alt: Logo
    :align: center
    :width:  400px


************
Certificates
************

Besides the functional testing, Red Pitaya passed the safety and electromagnetic compatibility (EMC) tests at an
external |testing and certification institute|.

.. |testing and certification institute| raw:: html

    <a href="http://www.siq.si/?L=3" target="_blank">testing and certification institute</a>

.. toctree::
   :maxdepth: 6

   cets


***************
Cooling options
***************

For additional cooling, we recommend a 30 mm or 25 mm fan. You can utilise the power connector on the board to power the fan, but please note that it supplies only 5 V. The power connector is located between the micro-SD socket and the host USB connector.

.. figure:: cooling-powerPin.jpg
    :width: 50%
    :align: center

    | Red Pitaya power connector.
    | Image via `blog <https://rroeng.blogspot.com/2014/03/keep-your-red-pitaya-cool.html>`_ (with permission from Jacek Radzikowski).


.. note::

    The power connector is a standard 2-pin 0.1" connector.
    Supplies only 5 V.


.. toctree::
   :maxdepth: 6

   cooling

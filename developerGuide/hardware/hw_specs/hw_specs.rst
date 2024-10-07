.. _hw_specs:

#########################
Hardware specifications
#########################

In this section you can find hardware specifications for all Red Pitaya board models. The specifications are measured on the STEMlab 125-14 Gen1 board, but are similar on the other board models (except where specifically stated). Any future measurements will be added to this section.

Please refer to the board model documentation for schematics, relevant components, mechanical specifications, and 3D models. Please note that the full hardware schematics for the Red Pitaya boards are not available. While Red Pitaya has open-source code, the hardware schematics are not open source. However, development schematics with information regarding hardware configuration, FPGA pin connections, and similar, are available.

========
Gen 1
========

----------------
Fast analog IO
----------------

.. toctree::
   :maxdepth: 6

   fastIO

-----------------------
Extension connectors
-----------------------

.. toctree::
   :maxdepth: 6

   extent


.. _qspi_chip:

----------
QSPI 
----------

Please note that the `QSPI chip <https://www.infineon.com/cms/en/product/memories/nor-flash/standard-spi-nor-flash/quad-spi-flash/s25fl128sagnfi001/>`_, located on the top layer of the board just to the right of TP1A under the heatsink (:ref:`STEMlab 125-14 schematics <schematics_125_14>`), is not populated by default on Red Pitaya boards. For further information on board modifications, please contact support@redpitaya.com or info@redpitaya.com.

.. warning::

    Any non-Red Pitaya hardware modification will void the warranty, and we cannot guarantee support for modified boards.


------------------
Cooling options
------------------

For enhanced cooling, we suggest utilising a 30 mm or 25 mm fan. The board's power connector can be employed to power the fan, however, it is important to note that it provides a maximum of 5 V. The power connector is situated between the micro-SD socket and the host USB connector.

.. figure:: img/cooling/cooling-powerPin.jpg
    :width: 50%
    :align: center

    Red Pitaya power connector. Image via `blog <https://rroeng.blogspot.com/2014/03/keep-your-red-pitaya-cool.html>`_ (with permission from Jacek Radzikowski).


.. note::

    The power connector is a standard 2-pin 0.1" connector.
    Supplies only 5 V.


.. toctree::
   :maxdepth: 2

   cooling


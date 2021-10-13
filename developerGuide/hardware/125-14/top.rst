.. _top_125_14:

##############
STEMlab 125-14
##############


*********
Technical specifications
*********

* :ref:`Product comparison table <rp-board-comp>`

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

ADC clock can be provided by:

    * On board 125MHz XO (default)
    * From external source / through extension connector :ref:`E2 <E2>` (R25,R26 should be moved to location R23,R24)
    * Directly from FPGA (R25,R26 should be moved to location R27,R28)

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

Besides the functional testing Red Pitaya passed the safety and electromagnetic compatibility (EMC) tests at an 
external `testing and certification institute <http://www.siq.si/?L=3>`_.


.. toctree::
   :maxdepth: 6
   
   cets


***************
Cooling options
***************

For additional cooling we recommend a 30mm or 25mm fan. You can utilize the power connector on the board to power
the fan, however please note that it supplies only 5 V. The power connector is located between micro-SD socket and 
the host USB connector.

.. figure:: cooling-powerPin.jpg
    :width: 50%
    :align: center

    | Red Pitaya power connector.
    | Image via `blog <https://rroeng.blogspot.com/2014/03/keep-your-red-pitaya-cool.html>`_ (with permission from Jacek Radzikowski).

    
.. note::
 
    Power connector is a standard 2-pin 0.1" connector.
    Supplies only 5V.
    

.. toctree::
   :maxdepth: 6
   
   cooling

***************
LED description
***************


    ======  ==========================================================================================================
    color
    ======  ==========================================================================================================
    blue    FPGA bitstream status (in normal operation this LED is turned ON indicating fpga bitstream was 
            successfully loaded)
    green   power supply status (in normal operation this LED is turned ON indicating that all power supplies on Red 
            Pitaya are working properly)
    red     heartbeat blinking pattern should show CPU load (in normal operation this LED is blinking)
    orange  SD card access indicator (in normal operation this LED is blinking in slow intervals)   
    ======  ==========================================================================================================
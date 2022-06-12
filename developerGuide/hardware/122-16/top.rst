.. _top_122_16:

SDRlab 122-16
#############

************************
Technical specifications
************************

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

.. _external_122_16:

******************
External ADC clock
******************

ADC clock can be provided by:

  * On board 122.88MHz XO (default)
  * From external source / through extension connector (instructions provided bellow)


* Remove: R37, R46
* Add: R34 = 0R, R35 = 0R


 .. figure:: External_img1.png
    :align: center


* Remove: FB11

 .. figure:: External_img2.png
    :align: center


* Remove: 0R on C64, R24
* Add: C64 = 100nF, C63 = 100nF, R36 = 100R

 .. figure:: External_img3.png
    :align: center


 .. figure:: External_shem.png
    :width: 50%
    :align: center

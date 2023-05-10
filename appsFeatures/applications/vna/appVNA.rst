.. _vna_extension:

#######################
Vector Network Analyzer
#######################

******************************
What do I need before I start?
******************************

1. VNA application requirements:

    * Windows or Linux-based personal computer (PC).

2. The following accessories and materials are available in the Red Pitaya store:

    * any kit that includes a STEMlab 125-14 or 125-10 (discontinued) board
    * Vector Network Analyzer bridge module


***************************************************
Start using Red Pitaya as a Vector Network Analyzer
***************************************************

========================================================
Connect Vector Network Analyzer bridge to the Red Pitaya
========================================================

    * Connect the VNA module's OUT to the Red Pitaya IN1
    * Connect the VNA module's IN to the Red Pitaya OUT1.
    * Set the IN1 jumpers on the Red Pitaya to the LV position.

.. figure::  img/vna_bridge_module_connections.png
    :align: center

=========================================================
Install & run network Vector Network Analyzer control app
=========================================================

------------------
Windows users only
------------------

    * Download and unpack the `control program <https://downloads.redpitaya.com/downloads/Clients/vna/vna-windows-tool.zip>`__.
    * Run the ``vna.exe`` program.

----------------
Linux users only
----------------

    * Install Python 3 and all the required libraries:

        .. code-block:: shell-session

            sudo apt-get install python3-dev python3-pip python3-numpy python3-pyqt5 libfreetype6-dev
            sudo pip3 install matplotlib mpldatacursor

    * Download and unpack the `control program <https://downloads.redpitaya.com/downloads/Clients/vna/vna-windows-tool.zip>`__.
    * Run the control program:

        .. code-block:: shell-session

            python3 vna.py

=====================================================
Type in the IP or URL address of the Red Pitaya board
=====================================================

----------------------------------------
Connect by entering the Red Pitaya's IP:
----------------------------------------

.. figure::  img/1_ip.PNG
    :align: center

To find the IP address of the Red Pitaya board, first connect to RedPitaya by following these :ref:`instructions <quick_start>`.


Then go to System->Network Manager. The IP is written next to the label.
Address: xxx.xxx.xxx.xxx .

.. figure::  img/network_manager_icon.png
    :width:  150px
    :align: center

----------------------------------
Connect by entering RedPitaya URL:
----------------------------------

.. figure::  img/1_url.PNG
    :align: center

============================================================
Run the Vector Network Analyzer application on the RedPitaya
============================================================

.. figure::  img/vna_icon.png
    :width:  150px
    :align: center

==============================================================
Click "Connect" inside the Vector Network Analyzer control app
==============================================================

.. figure::  img/2_connect.PNG
    :align: center

***************************************
Perform calibration and start measuring
***************************************

.. note::

   The VNA module works for frequencies above 500 kHz. Please start the calibration process at 500 kHz (ignore calibration values in the pictrures).


    .. figure::  img/3_calibrate.PNG
        :align: center

#. Connect the SMA OPEN calibration connector marked with the letter O to the DUT SMA connector of the network vector analyzer bridge module. Click the button "Open" and wait for the calibration procedure to complete.

    .. figure:: img/04_Calibration_O.jpg
        :align: center

#. Connect the SMA SHORT calibration connector marked with the letter S to the DUT SMA connector of the network vector analyzer bridge module. Click the button "Short" and wait for the calibration procedure to complete.

    .. figure:: img/03_Calibration_S.jpg
        :align: center

#. Connect the SMA LOAD calibration connector marked with the letter L to the DUT SMA connector of the network vector analyzer bridge module. Click the button "Load" and wait for the calibration procedure to complete.

    .. figure:: img/05_Calibration_L.jpg
        :align: center

#. Select the Smith chart tab at the bottom and then click the Single button to perform a single measurement of the DUT. A dot in the middle of the Smith chart circle (@ 50 Ohm) will indicate that VNA is properly measuring the reference 50 Ohm LOAD.

    .. figure::  img/4-load_DUT_smith_chart.PNG
        :align: center

#. Disconnect the LOAD SMA connector and connect whatever DUT you’d like to measure.

    .. figure::  img/07_Product_Combo.jpg
        :align: center

=========
Examples:
=========

#. Measurement of a 21-meter vertical antenna
    The antenna is not properly tuned (at frequency 14, 21 MHz, SWR should be = 1.5).

    .. figure::  img/antenna.png
        :align: center

#. 20-meter bandpass filter for HAM RADIO
    SWR is better than 1.5 between the start and stop band frequencies, and the filter load is around 50 Ohm.

.. figure::  img/bandpass_filter.png
    :align: center

.. figure::  img/bandpass_filter_smith_chart.png
    :align: center

.. admonition:: Credits

    | The original developer of the Vector Network Analyzer RedPitaya application is Pavel Demin.
    | Repositories used by our builds:

        * |red-pitaya-notes|
     
.. |red-pitaya-notes| raw:: html

    <a href="https://github.com/RedPitaya/red-pitaya-notes" target="_blank">Red Pitaya notes repository</a>

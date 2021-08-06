Bode Analyzer
#############

.. figure:: 01_iPad_Combo_Bode.jpg

This application will turn your Red Pitaya into an affordable Bode analyzer. It is the perfect tool for educators, 
students, makers, hobbyists and professionals seeking affordable, highly functional test and measurement equipment. 
The Bode analyzer is an ideal application for measuring frequency responses of the passive/active filters, complex 
impedances and any other electronic circuit. The Gain/Phase frequency response can be used to characterize any device
under test completely, you can perform linear and logarithmic sweeps. Gain and Phase can be measured from 1Hz to 
60MHz. The basic user interface enables quick interaction and parameter settings. The Bode analyzer can be used for 
the measurement of Stability of control circuits such as the DC/DC converters in power supplies, Influence of 
termination on amplifiers or filters, Ultrasonic and piezo electric systems and similar. All Red Pitaya applications 
are web-based and don’t require the installation of any native software. Users can access them via a browser using 
their smartphone, tablet or a PC running any popular operating system (MAC, Linux, Windows, Android and iOS). 
The graphical user interface of the Bode analyzer application is shown below.

The graphical interface is divided into 5 areas:

.. figure:: BA_Slika_01.png

1. **Stop/Run button:** It is used to start and stop measurement. **Calibrate button:** When the selected calibration 
   of the setup is started.
2. **Measurement settings panel:** It is used for setting the measurement parameters such as the frequency range, 
   scale, number of steps, excitation signal amplitude, excitation signal DC bias and averaging number.

.. figure:: BA_Slika_02.png

3. **Plot settings panel:** It is used to set the Gain and Phase graph ranges as also manual or auto scale mode.

.. figure:: BA_Slika_03.png

4. **Gain graph:** The Gain frequency response of the DUT (device under test) is plotted for the selected frequency 
   range.
#. **Phase graph:** The Phase frequency response of the DUT (device under test) is plotted for the selected frequency 
   range.

FEATURES
********

Main feature of the Bode analyzer application are described below:

    - Measured parameters: Gain, Phase
    - The Bode analyzer application will enable you to measure the gain and phase frequency response for the desired 
      DUT (device under test)
    - The frequency sweep range of the Bode analyzer application is from 1Hz to 60MHz with a 1Hz resolution
    - Linear and Logarithmic Frequency sweep modes are available. The Logarithmic sweep mode (scale) enables 
      measurements in large frequencies range, while the linear sweep mode is used for measurement in the small 
      frequencies range.
    - excitation signal parameters (amplitude and DC bias) can be adjusted to make measurements in different 
      sensitivities and conditions (amplifiers etc.).
    - The calibration function enables calibrating long leads and to remove leads and cables effect on final 
      measurements. The calibration will also calibrate your Red Pitaya if any parasitics effects are present.   
   
.. figure:: BA_Slika_05.png
   
   
Specifications
**************  

+--------------------------------------------+-------------------------------+--------------------------------+
|                                            | STEMlab 125 - 10              |  STEMlab 125 - 14              |
+--------------------------------------------+-------------------------------+--------------------------------+
| Frequency span                             | 1Hz-50MHz                     |  1Hz-60MHz                     |
+--------------------------------------------+-------------------------------+--------------------------------+
| Frequency resolution                       | 1Hz                           |  1Hz                           |
+--------------------------------------------+-------------------------------+--------------------------------+
| Excitation signal amplitude                | 0 - 1 V                       |  0 - 1 V                       |
+--------------------------------------------+-------------------------------+--------------------------------+
| Excitation signal DC bias                  | 0 - 0.5 V                     |  0 - 0.5 V                     |
+--------------------------------------------+-------------------------------+--------------------------------+
| Resolution                                 | 10bit                         |  14bit                         |
+--------------------------------------------+-------------------------------+--------------------------------+
| Maximum number of steps per measurement    | 1000                          |  1000                          |
+--------------------------------------------+-------------------------------+--------------------------------+
| Max input amplitude                        | | ± 1 V (LV jumper settings), | |  ± 1 V (LV jumper settings), |
|                                            | | ± 20 V (HV jumper settings) | |  ± 20 V (HV jumper settings) |
+--------------------------------------------+-------------------------------+--------------------------------+
| Measured parameters                        | Gain, Phase                   |  Gain, Phase                   |
+--------------------------------------------+-------------------------------+--------------------------------+
| Frequency sweep modes                      | Linear/Logarithmic            |  Linear/Logarithmic            |
+--------------------------------------------+-------------------------------+--------------------------------+

.. note::

    Plese take care that :ref:`position <anain>` are set to the correct input rage!
    

HW connections
**************

When using the Bode analyzer application, please follow the connection diagram described below. Also use the 50 Ohm 
termination on the OUT1.

.. figure:: BA_Slika_04.png


Console application
*******************

Bode Analyzer can be used from console.

.. code-block:: console

   root@rp-f01c35:~# bode
   Too few arguments!

   Bode analyzer version 1.04-133-feaf63b43, compiled at Fri Jan 22 04:25:24 2021

   Usage:	bode [channel] [amplitude] [dc bias] [averaging] [count/steps] [start freq] [stop freq] [scale type]
   or
      bode -calib

      channel            Channel to generate signal on [1 / 2].
      amplitude          Signal amplitude in V [0 - 1, which means max 2Vpp].
      dc bias            DC bias/offset/component in V [0 - 1].
                        Max sum of amplitude and DC bias is (0-1]V.
      averaging          Number of samples per one measurement [>1].
      count/steps        Number of measurements [>2].
      start freq         Lower frequency limit in Hz [3 - 62.5e6].
      stop freq          Upper frequency limit in Hz [3 - 62.5e6].
      scale type         0 - linear, 1 - logarithmic.
      -calib             Starts calibration mode. The calibration values will be saved in:/tmp/ba_calib.data
   Output:	frequency [Hz], phase [deg], amplitude [dB]



For run the bode, you need to do 2 steps:

    #. ) Load the FPGA image of streaming

        .. code-block:: console

            root@rp-f01c35:/# cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    #. ) Launch a console application.

        .. code-block:: console

            root@rp-f09508:~# bode 1 1 0 1 10 1000 100000 0
            1000.00    0.00025    0.34855
            12000.00    0.00090    0.34481
            23000.00    0.00209    0.32803
            34000.00    0.00859    0.33696
            45000.00    0.00335    0.26568
            56000.00    -0.00580    0.38830
            67000.00    -0.01751    0.36922
            78000.00    0.00635    0.32767
            89000.00    0.00521    0.38478
            100000.00    -0.00933    0.36610

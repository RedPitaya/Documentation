.. _bode_app:

Bode Analyzer
#############

.. figure:: img/01_iPad_Combo_Bode.jpg

This application will turn your Red Pitaya into an affordable Bode analyzer. It is the perfect tool for educators, students, makers, hobbyists, and professionals seeking affordable, highly functional test and measurement equipment. 

The Bode analyzer is an ideal application for measuring the frequency responses of passive and active filters, complex impedances, and any other electronic circuit. The Gain/Phase frequency response can be used to completely characterise any device under test. You can perform linear and logarithmic sweeps. Gain and phase can be measured from 1 Hz to 60 MHz. The basic user interface enables quick interaction and parameter settings. The Bode analyzer can be used for the measurement of the stability of control circuits such as the DC/DC converters in power supplies, the influence of termination on amplifiers or filters, ultrasonic and piezoelectric systems, and similar. All Red Pitaya applications are web-based and don’t require the installation of any native software. Users can access them via a browser using their smartphone, tablet or a PC running any popular operating system (MAC, Linux, Windows, Android, and iOS). 

The graphical user interface of the Bode analyzer application, that is shown bellow, is divided into 5 areas:

.. figure:: img/BA_Slika_01.png

1. **Stop/Run button:** Start and stop the measurement. **Calibrate button:** Start the calibration for the current setup.

2. **Measurement settings panel:** Set the measurement parameters such as the frequency range, scale, number of steps, excitation signal amplitude, excitation signal DC bias, and averaging number.

.. figure:: img/BA_Slika_02.png

3. **Plot settings panel:** Set the Gain and Phase graph ranges as well as manual or auto scale mode.

.. figure:: img/BA_Slika_03.png

4. **Gain graph:** The gain frequency response of the DUT (device under test) is plotted for the selected frequency range.

#. **Phase graph:** The phase frequency response of the DUT (device under test) is plotted for the selected frequency range.


Features
********

The main features of the Bode analyzer application are described below:

   -   Measured parameters: Gain, Phase
   -   The Bode analyzer application will enable you to measure the gain and phase frequency response for the desired DUT (device under test).
   -   The frequency sweep range of the Bode analyzer application is from 1 Hz to 60 MHz with a 1 Hz resolution.
   -   Linear and logarithmic frequency sweep modes are available. The logarithmic sweep mode (scale) enables measurements in a large frequency range, while the linear sweep mode is used for measurements in a small frequency range.
   -   Excitation signal parameters (amplitude and DC bias) can be adjusted to make measurements in different sensitivities and conditions (amplifiers, etc.).
   -   The calibration function enables calibrating long leads and removing leads' and cables' effects on final measurements. The calibration will also calibrate your Red Pitaya if any parasitic effects are present. Bode calibration data is stored in **/tmp/ba_calib.data**.
   
.. figure:: img/BA_Slika_05.png
   
   
Specifications
**************  

  +--------------------------------------------+-------------------------------+--------------------------------+
  |                                            | STEMlab 125-10                | STEMlab 125-14                 |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Frequency span                             | 1 Hz - 50 MHz                 | 1 Hz - 60 MHz                  |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Frequency resolution                       | 1 Hz                          | 1 Hz                           |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Excitation signal amplitude                | 0 - 1 V                       | 0 - 1 V                        |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Excitation signal DC bias                  | 0 - 0.5 V                     | 0 - 0.5 V                      |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Resolution                                 | 10 bit                        | 14 bit                         |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Maximum number of steps per measurement    | 1000                          | 1000                           |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Max input amplitude                        | | ± 1 V (LV jumper settings), | |  ± 1 V (LV jumper settings), |
  |                                            | | ± 20 V (HV jumper settings) | |  ± 20 V (HV jumper settings) |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Measured parameters                        | Gain, Phase                   | Gain, Phase                    |
  +--------------------------------------------+-------------------------------+--------------------------------+
  | Frequency sweep modes                      | Linear/Logarithmic            | Linear/Logarithmic             |
  +--------------------------------------------+-------------------------------+--------------------------------+

.. note::

    Please take care that the jumpers behind the :ref:`analog inputs <anain>` are set to the correct input range!


HW connections
**************

When using the Bode analyzer application, please follow the connection diagram described below. Also use the 50 Ohm 
termination on the OUT1.

.. figure:: img/BA_Slika_04.png

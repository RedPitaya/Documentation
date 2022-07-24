.. _lrc_app:

*********
LCR meter
*********

.. figure:: 01_iPad_Combo_LCR.jpg

This application will turn your Red Pitaya into an affordable LCR meter. It is the perfect tool for educators, students, makers, hobbyists, and professionals seeking affordable, highly functional test and measurement equipment. Resistors, capacitors, and inductors are basic components of all electrical circuits, and while working on your projects, you will definitely need to measure some components laying around on your working bench. The Red Pitaya's LCR meter will enable you to speed up the procedure and accurately measure the components just by switching from one application to another.

.. note:: 

    An additional extension module is needed to use the LCR metre application. The module can be purchased from the |RP store|. 
    
.. |RP store| raw::html
    <a href="https://redpitaya.com/shop/" target="_blank">Red Pitaya store</a>    

All Red Pitaya applications are web-based and don’t require the installation of any native software. Users can access them via a browser using their smartphone, tablet or a PC running any popular operating system (MAC, Linux, Windows, Android, and iOS). The elements of the LCR meter application are arranged logically and offer a familiar user interface similar to bench LCR meters.

.. figure:: Slika_01_LCR_meter_WEB_page.png

The graphical interface is divided into 6 main areas:
    
    #. **Hold/Run button:** Used to start and stop the measurement. **Log data button:** When selected, the measurements of parameters selected in the "Data options" field are logged in the table shown in area 6.
    
    #. **Data options panel:** It is used for selecting the desired parameter for which the measurement will be displayed on the main window panel shown in area 4.
    
    #. **Measurement option panel:** It is used to select a measuring frequency, range mode, and range value. The user can select between the Parallel and Series measuring modes as well as between the Tolerance, Relative or Normal modes (modes described in the features section).
    
    #. **Main display:** On this panel, the measurements of the parameters selected in the "Data option" field are shown. The primary parameter is shown with a larger font and the secondary parameter with a smaller one. This is a very common practise since, by reading values from the display, the user can automatically see the most important results.
    
    #. **Secondary display:** On the secondary display, the main settings are shown: current selected parameters, measuring frequency, and range mode. Also, the Min, Max, and average values or primary parameters are shown.
    
    #. **Logging table:** Used to log and export measured data. Logging is started by selecting the "Log data" button. The maximum number of rows/measurements in the table is 1000.
    
    #. **Optional button field:** Used to manipulate the table. The "Clear Min/Max" button will reset the Min and Max values on the secondary display. The "Export table" button will export the measured data in .csv format. The "Clear all" button will delete all measurements from the table and the "Clear" button will delete the currently selected measurement.


Connecting the LCR module
*************************

.. figure:: E_module_connection.png


Features
********

The main features of the LCR meter applications are described below:

+-------------------------------+----------------------------+----------------------------+
|                               | STEMlab 125-10             | STEMlab 125-14             |
+-------------------------------+----------------------------+----------------------------+
| Measured primary parameters   | Z, L, C, R                 | Z, L, C, R                 |
+-------------------------------+----------------------------+----------------------------+
| Measured secondary parameters | P, D, Q, E                 | P, D, Q, E                 |
+-------------------------------+----------------------------+----------------------------+
| Selectable frequencies        | 100 Hz, 1 kHz,             | 100 Hz, 1 kHz,             |
|                               | 10 kHz, 100 kHz            | 10 kHz, 100 kHz            |
+-------------------------------+----------------------------+----------------------------+
| Impedance range               | 1 Ω - 10 MΩ                | 1 Ω - 10 MΩ                |
+-------------------------------+----------------------------+----------------------------+
| DC bias                       | 0.5 V                      | 0.5 V                      |
+-------------------------------+----------------------------+----------------------------+
| Basic accuracy                | 5,00%                      | 1,00%                      |
+-------------------------------+----------------------------+----------------------------+
| Max input voltage             | 0.5 Vpp                    | 0.5 Vpp                    |
+-------------------------------+----------------------------+----------------------------+
| Input protection              | Yes                        | Yes                        |
+-------------------------------+----------------------------+----------------------------+
| Parameter range Z             | 1 Ω - 10 MΩ                | 1 Ω - 10 MΩ                |
+-------------------------------+----------------------------+----------------------------+
| Parameter range Rs, Rp        | 1 Ω - 10 MΩ                | 1 Ω - 10 MΩ                |
+-------------------------------+----------------------------+----------------------------+
| Parameter range Ls, Lp        | 100 nH - 1000 H            | 100 nH - 1000 H            |
+-------------------------------+----------------------------+----------------------------+
| Parameter range Cs, Cp        | 10 pF - 100 mF             | 1 pF - 100 mF              |
+-------------------------------+----------------------------+----------------------------+
| Parameter range P             |  ± 180 deg                 | ± 180 deg                  |
+-------------------------------+----------------------------+----------------------------+


MEASURED PRIMARY PARAMETERS: Z, L, C, R
=======================================

The LCR meter application will enable you to measure basic parameters of the passive electrical components:

    - **R** – resistance
    - **C** – capacitance
    - **L** – inductance
    - **Z** – impedance


MEASURED SECONDARY PARAMETERS: P, D, Q, E
=========================================

Alongside the main parameters, the secondary parameters are also measured and calculated. These parameters are common in describing the properties and the quality of the passive components:

    - **P** - impedance phase (phase between measured current and voltage)
    - **D** - dissipation factor (often used to quantify capacitor quality)
    - **Q** - quality factor (often used to quantify inductor quality)
    - **ESR** - equivalent series resistance


SELECTABLE FREQUENCIES: 100 Hz, 1 kHz, 10 kHz, 100 kHz
======================================================

The LCR meter enables measurements at 4 different frequencies (100 Hz, 1 kHz, 10 kHz, 100 kHz). The user can select a desired frequency, and the LCR application will use sine signals with the selected frequency to measure the impedance.


RANGE MODE: AUTO, MANUAL
=========================

Since the measured values are unknown, the LCR meter will adjust the measuring range to provide the best accuracy. If the user expects some value in creating ranges, then the Manual mode can be used.


MEASUREMENT MODE: TOLERANCE, RELATIVE, NORMAL
==============================================

The "Tolerance" and "Relative" buttons are used for measuring in the tolerance and relative modes. When neither is selected, the LCR meter measures in the "Normal" mode.

    - **Tolerance mode:** The last value measured before clicking the "Tolerance" button is saved and used to calculate the percentage difference between the new value and the saved one.

    - **Relative mode:** The last value measured before clicking the "Relative" button is saved and used to calculate the relative difference between the new value and the saved one.


EQUIVALENT CIRCUIT CALCULATION MODE: PARALLEL, SERIES
=====================================================

The Parallel and Series measuring modes denote the use of a series or parallel equivalent circuit to calculate the parameters (R, C, L...) from the measured impedance Z. The LCR metre will only measure the complex value *Z=|Z|e(jP)*, where P is the measured phase and |Z| is the impedance amplitude. All other parameters are calculated from the series or parallel equivalent circuit.


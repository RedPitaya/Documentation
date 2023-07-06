.. _power_anal_app:

**************
Power Analyzer
**************

The application is based on the oscilloscope app with a change to the controller and server module.

.. figure:: power_analyzer.png
    :align: left
    :scale: 70 %

     The user interface of the Power Analyzer application.

    ..

The user interface is divided into 8 parts:

    - **Graphs:** The user interface plots the received data using the *flot* library. The power is calculated from the data on current and voltage. All three are then transformed into data series. The length of the series is adjusted to the screen resolution, and the library takes care of the interpolation between the data points.
    - **Acquisition settings:** The user can select the current probe, voltage probe attenuation, and sampling frequency. When the current probe is selected, an LED will turn on the Red Pitaya, which indicates that the corresponding output channel has been turned on. The user can also input the probe attenuation and probe factor should a different one be needed. In the frequency drop-down menu, the different possible bandwidths are available (corresponding to the decimation) as half the sampling frequency. The last option is a DC mode, where the application measures only the average of both signals and the working power.
    - **Stop:** Clicking the button will temporarily stop the application.
    - **Trigger settings:** Set the mode, channel, edge, and trigger level.
    - **Plot settings:** Turn specific plots on or off; change the scale, offset, and time base of the signals.
    - **Measurement settings:** Consists of multiple tabs, which are the same as in the **Measurement results**. In each tab, several different settings can be selected for display. In the harmonics tab, you can input the number of harmonics, which will then be used in calculations.
    - **Measurement results:** Consist of multiple tabs for ease of use, as in **Measurement settings**. The plot locations also roughly correspond to where the select box is.
    - **Save measurements:** When clicked, the data starts logging. Each measurement is logged with a timestamp. The results can be found on the Red Pitaya in the directory **measurements**. The name is composed of the date and the timestamp of the start of the logging.

You can read more about the inner workings of the controller, the server, and the server module in chapters 5.2.2 onwards (page 42 of the thesis).

More about the Power Analyzer can be found here (click on the PDF icon to download the thesis) (please note that the thesis is in Slovene):

   |Power Analyzer|

.. note::

   The Power Analyzer application is available on the Red Pitaya marketplace.
   
.. |Power Analyzer| raw:: html

   <a href="https://repozitorij.uni-lj.si/IzpisGradiva.php?id=85012&lang=eng" target="_blank">Power Analyzer documentation</a>

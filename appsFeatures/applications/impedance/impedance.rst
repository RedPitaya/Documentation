.. _impedance_app:

###################
Impedance Analyzer
###################

This application will turn your Red Pitaya into an Impedance analyzer. It is the perfect tool for educators, students, makers, hobbyists, and professionals seeking affordable, highly functional test and measurement equipment.

Impedance is an important parameter used to characterize electronic components, electronic circuits, and the materials used to make components. Impedance analysis can also be used to characterize materials exhibiting dielectric behavior such as biological tissue, foodstuffs or geological samples (`Wikipedia - impedance analyzer <https://en.wikipedia.org/wiki/Impedance_analyzer>`_)

The impedance analyzer uses the direct current-voltage method and has a frequency range from 1 Hz to 50 MHz. The frequency range and number of measurements can be arbitrarily selected.

All Red Pitaya applications are web-based and do not require the installation of any native software. Users can access them via a web browser using their smartphone, tablet, or a PC running any popular operating system (MAC, Linux, Windows, Android, and iOS).

Features
***********

The impedance analyzer enables the measurement of the following parameters:

- Impedance |Z| (Ohm)
- Phase P (degrees)
- Admittance Y (S)
- Inverse phase -P (degrees)
- Serial resistance Rs (Ohm)
- Parallel resistance Rp (Ohm)
- Serial reactance Xs (Ohm)
- Parallel conductance Gp (S)
- Parallel susceptance Bp (S)
- Serial capacitance Cs (F)
- Parallel capacitance Cp (F)
- Serial inductance Ls (H)
- Parallel inducatnce Lp (H)
- Quality factor Q
- Dissipation factor D

.. figure:: img/Impedance_analyzer_main.png
    :width: 1000

The graphical user interface of the Impedance analyzer application is divided into 4 areas:

#. **Top settings menu:** Export data, reset settings and start or stop the measurements.
#. **Measurement control pannel:** Set the shunt resistior, measurement parameters, plot settings, and put cursors on the main graph area.
#. **Current measurement data:** The current step number and frequency of generated pulses required for the measurement.
#. **Main graph area:** Main graph area displays the impedance response of the DUT (device under test).


Top settings menu
==================

.. figure:: img/IA_top_settings.png
  :width: 300

Top settings menu contains the following functionality:

#. **Question mark button:** Leads to the impedance analyzer documenatation webpage (here)
#. **Menu dropdown:**

    - *Export data:* Export the currently displayed data as either a “Graph” or a “CSV file”. If graph is chosen, a screenshot of the application is taken and automatically downloads via the browser. Otherwise, a CSV file with data is donwloaded from the board.
    - *Reset:* Resets all impedance analyzer application settings back to default.

#. **Stop/Run button:** Start and stop the measurement.

Measurement control panel
==========================

Here we can set measurement parameters such as the frequency range, scale, number of steps, excitation signal amplitude, excitation signal DC bias, and averaging number.


Settings
---------

.. figure:: img/IA_plot_settings.png
    :width: 260

- **Start frequency [Hz]:** The impedance analyzer starts measuring the DUT frequency response at this frequency.
- **End frequency [Hz]:** The impedance analyzer ends measuring the DUT frequency response at this frequency.
- **Steps:** Number of measurements performed. The frequency range between **Start frequency** and **End frequency** is divided according to the **measure scale** setting and measurements are performed at each point.
- **Measure scale:** Either liner or logarithmic sweep mode (scale). The logarithmic sweep mode enables measurements in a large frequency range, while the linear sweep mode is used for measurements in a small frequency range.



##TODO



At each frequency point Red Pitaya sends out a burst signal with **Period number** periods, one=way amplitude of **Amplitdue [V]**, offset **DC bias[V]**, and the frequency recalculated from the settings above.
The **Averaging** deterimines wheter the final measurement is an average of all sent pulses or not.

- **Period number:** Number of signal periods in a single measurement.
- **Amplitude [V]:** Excitation signal amplitude.
- **DC bias [V]:** Excitation signal DC bias (offset).
- **Averaging:** When set to ``1``, the result of each measurement is an average of all sent signal periods.
- **Invalid input data:** Button to show invalid measurements on the graph.
- **Analysis input threshold ppV:** Measured responses smaller than this setting will be treated as the minimal threshold value (for caluclation purposes).

.. note::

    The sum of **Amplitdue** and **DC bias** is capped at 1 Volt. For example, if Amplitude is set to 0.4 V, the DC bias can be set to a maximum of 0.6 V.


Plot settings
--------------

.. figure:: img/Bode_analyzer_plot_settings.png
    :width: 260

Settings for the plot.

- **Gain min, Gain max [dB]:** Minimum and maximum value on the amplitude axis (Y-axis, left side).
- **Phase min, Phase max [deg]:** Minimum and manxumum value on the phase axis (Y-axis, right side).
- **Autoscale:** When selected, the two settings above are ignored and calculated automatically from the measurements.


Cursor settings
---------------

.. figure:: img/Bode_analyzer_cursor_settings.png
    :width: 260

Up to two cursors can be put on each of the axis. **F** stands for frequency, **G** for gain, and **P** for phase. The cursors each show the current value and the absolute difference between the two cursors on the same axis.
Cursors can be moved with *Click+Drag*.





Source code
==============

The `Impedance Analyzer source code <https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools/impedance_analyzer>`_ is available on our GitHub.


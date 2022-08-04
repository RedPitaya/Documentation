Oscilloscope & Signal Generator
###############################

.. figure:: 01_iPad_Combo_Oscilloscope.jpg

This application will turn your Red Pitaya board into a 2-channel oscilloscope and a 2-channel signal generator. It is the perfect tool for educators, students, makers, hobbyists, and professionals seeking affordable, highly functional test and measurement equipment. The simple and intuitive user interface provides all the necessary tools for signal analysis and measurements. 

High-end specifications will satisfy more demanding users looking for powerful tools for their work benches. The application is web-based and doesn’t require the installation of any native software. Users can access them via any web browser (Google Chrome is recommended) using their smartphone, tablet or a PC running any popular operating system (MAC, Linux, Windows, Android, and iOS). The elements in the Oscilloscope & Sig. Generator application are arranged logically and offer a familiar user interface.


.. tabs::

   .. tab:: STEMlab 125-10, 125-14, SDRlab 122-16, SIGNALlab 250-12

        .. figure:: Slika_02_OSC.png
            :width: 50%
            :align: center

   .. tab:: STEMlab 125-14 4-Input

        .. figure:: Slika_02_OSC_4-in.png
            :width: 50%
            :align: center


Apart from the graph, there are five areas in which the surface is divided:

    1. Autoscale: Automatically sets up the Oscilloscope settings for the optimal display of the input signals. By pressing the button, the voltage axis and time axis are set so that at least one full period of the signal will fill the screen.
    #. Channels / Trigger / Measuring Tools: This menu provides controls for inputs and outputs, trigger, guides, and measurements.
    #. Axis control panel: By pressing the horizontal ± buttons, the scaling of the X axis is changed and thus the selected time range is displayed in the graph. The vertical ± buttons change the Y axis and thus the displayed voltage range of the signal. In addition, the settings for the time frame, trigger, zero point of the X axis, and sampling rate are displayed.
    #. Channel Setting display: Indicates the scale of the Y axis for all channels that are switched.

    
Features
********

The Oscilloscope & Signal generator's main features are listed below:

    - Run/stop and auto-set functionality
    - Signals position and scale controls
    - Trigger controls (source, level, slope)
    - Trigger modes: auto, normal, and single triggering
    - Input calibration wizard
    - Cursors
    - Measurements
    - Mathematical operations
    - Signal generator controls (waveform, amplitude, frequency, phase)
    

Autoscale
=========

Automatically sets up the Oscilloscope to best display the input signal. By pressing this button, the voltage axis and the time axis are set so that at least one full period of the signal will fill the screen.

    .. figure:: Slika_03_OSC_left.png
        :width: 49%
        :align: center

    .. figure:: Slika_03_OSC_right.png
        :width: 49%
        :align: center


Inputs
======
  
On the right side of the Oscilloscope & Sig. Generator application interface, the IN1 and IN2 channels are listed. By a  simple click on the name of a channel (not the gear) the channel gets highlighted and you can simply control all the  settings of the respective channel.
The available settings by device model:

.. tabs::

    .. tab:: STEMlab 125-10, 125-14, 125-14 4-Input

        .. figure:: Slika_05_OSC_125.png
            :height: 280px


        - **SHOW:** Shows or hides the curve associated with the channel.
        - **INVERT:** Reflects the graph on the X axis.
        - **Probe attenuation:** (must be selected manually) The division that was set on the probe.
        - **Vertical offset:** Moves the curve up or down.
        - **LV and HV:** Must be selected according to the jumper :ref:`position <anain>` on each channel.


    .. tab:: SDRlab 122-16
     
        .. figure:: Slika_05_OSC_122.png
            :height: 280px

        - **SHOW:** Shows or hides the curve associated with the channel.
        - **INVERT:** Reflects the graph on the X axis.
        - **Probe attenuation:** (must be selected manually) The division that was set on the probe.
        - **Vertical offset:** Moves the curve up or down.

    .. tab:: SIGNALlab 250-12

        .. figure:: Slika_05_OSC_250.png
            :height: 280px


        - **SHOW:** Shows or hides the curve associated with the channel.
        - **INVERT:** Reflects the graph on the X axis.
        - **Probe attenuation:** (must be selected manually) The division that was set on the probe.
        - **Vertical offset:** Moves the curve up or down.
        - **Input attenuation:** 1:1 (± 1V) / 1:20 (± 20V) is selected automatically when adjusting V/div setting, user can also select range manually through WEB interface settings.
        - **AC/DC coupling**


.. |analog inputs| raw:: html

    <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/125-14/fastIO.html#analog-inputs" target="_blank">position</a>

    
Outputs
=======
.. _output-ref:

On the right side of the Oscilloscope & Sig. Generator application interface, the OUT1 and OUT2 channels are listed. With a simple click on the name of a channel (not the gear), the channel gets highlighted and you can simply control all the settings of the respective channel. 

The available settings are the following: 

.. tabs::

  .. tab:: STEMlab 125-10, 125-14

      .. figure:: Slika_06_OSC_125.png
          :height: 360px


      - **ON:** Turns the output of the generator ON/OFF.
      - **SHOW:** Shows a signal preview (notice that the signal is not phase aligned with the input/output signal).
      - **Type:** Various waveforms are available for output: SINE (sinus), SQUARE (rectangle), TRIANGLE (triangle), SAWU (rising sawtooth), SAWD (falling sawtooth), DC and PWM (Pulse Width Modulation).
      - **Trigger:** Enables the user to select an internal or external trigger for the generator.
      - **Frequency:** Frequency of output signal.
      - **Amplitude:** Amplitude of output signal.
      - **Offset:** DC offset.
      - **Phase:** Phase between both output signals.
      - **Duty cycle:** PWM signal duty cycle.

  .. tab:: SDRlab 122-16
     
      .. figure:: Slika_06_OSC_122.png
          :height: 360px
          

      - **ON:** Turns the output of the generator ON/OFF.
      - **SHOW:** Shows a signal preview (notice that signal is not phase aligned with the input/output signal).
      - **Type:** Various waveforms are available for output: SINE (sinus).
      - **Trigger:** Enables the user to select an internal or external trigger for the generator.
      - **Frequency:** Frequency of output signal.
      - **Amplitude:** Amplitude of output signal.
      - **Phase:** Phase between both output signals.

  .. tab:: SIGNALlab 250-12

      .. figure:: Slika_06_OSC_250.png
          :height: 360px


      - **ON:** Turns the output of the generator ON/OFF.
      - **SHOW:** Shows a signal preview (notice that signal is not phase aligned with the input/output signal).
      - **Type:** Various waveforms are available for output: SINE (sinus), SQUARE (rectangle), TRIANGLE (triangle), SAWU (rising sawtooth), SAWD (falling sawtooth), DC and PWM (Pulse Width Modulation).
      - **Trigger:** Enables the user to select internal or external trigger for the generator.
      - **Frequency:** Frequency of output signal.
      - **Amplitude:** Amplitude of output signal.
      - **Offset:** DC offset.
      - **Gain:**  Displays the status of the output gain stage.
      - **Phase:** Phase between both output signals.
      - **Duty cycle:** PWM signal duty cycle.
      - **Load:** Output load.


.. note::

   On the board STEMlab 125-14 4-Input this outputs are missing

=======
Trigger
=======

.. figure:: Slika_07_OSC.png
    :width: 40%
    :align: right


The trigger is used to enable the scope to display changing waveforms on the screen of the scope in a steady fashion. The parameter Source defines the trigger source used for this. The trigger source can be input channel 1 (IN1), input channel 2 (IN2), or an external source. The available settings are the following:

    - **LEVEL** The trigger level value is used to determine at which value of signal amplitude the trigger condition will be satisfied (true). When signal amplitude achieves or crosses this value, the trigger state is set to "true". Following the "true" trigger condition, the acquisition and signal plotting will be executed.
    - **EGDE** Since during the time sweep (acquisition), signal amplitude can cross the trigger level from the higher value to the lowest one or vice versa. The edge setting will determine in which case the trigger condition will be set to "true".
    - **NORMAL** The acquisition (trace (re)plotting) is executed only if the trigger state is "true". In other words, the signal needs to satisfy the trigger condition in order to be acquired and (re)plotted by the Oscilloscope.
    - **SINGLE** After trigger conditions are satisfied by the observed signal, the acquisition is executed only once, and trace re-plotting is stopped regardless of the repetitive "true" trigger states.
    - **AUTO** Trigger state and conditions are disregarded. Signal acquisition and signal trace re-plotting are executed in a repetitive (continuous) manner. This setting is the default one.
    - **STOP** Pause triggers.
    - **RUN** Starts/continues triggering.

The Source parameter defines the source used for this purpose. With the IN1 or the IN2, the signal at the respective input is selected; with the EXT, you can invoke the trigger from outside through:

.. tabs::

   .. tab:: STEMlab 125-10, 125-14, 125-14 4-Input, SDRlab 122-16

      Pin 3 on the header row :ref:`E1 <E1>`.
      

   .. tab:: SIGNALlab 250-12

      BNC connector available on the front panel

.. |E1| raw:: html

    <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/hardware/125-14/extent.html#extension-connector-e1" target="_blank">E1</a>




External ref. clock (only SIGNALlab 250-12)
===========================================

External reference clock input can be enabled through the settings menu. Once enabled, its status is displayed in the main interface. The "green" status indicates that the sampling clock is locked to the external reference clock.

.. figure:: Silka_EXT_CLOCK.png
    :width: 30%


Math
=====

Among the more interesting features of a digital oscilloscope is the "math" channel. The available settings are the following:

    - **\+** Adds the selected channels.
    - **\-** Subtract the selected channels.
    - **\*** Multiply selected channels.
    - **ABS** Gives an absolute value of the selected signal.
    - **dy/dt** Gives an time derivation of the selected signal.
    - **ydt** Gives an time integration of the selected signal.
    - **INVERT** Inverts the signal.

.. figure:: Slika_08_OSC.png

Cursor
======

This feature enables the user to easily get the data of relevant basic measurements, such as signal period, amplitude, time delay, amplitude difference between two points, time difference between two points, etc.

.. figure:: Slika_09_OSC.png


Navigate
========

When you have a lot of data to analyze, it is very important to get through it easily. Navigate left and right by 
dragging the data where you want and effortlessly zoom in and out by using your mouse scroll wheel.

.. figure:: Slika_04_OSC.png

Measurements
============

The menu can be found under the MEAS button. Here you can select up to 4 measured values in total and then provide the corresponding values. In the Operator field, select the desired measurement and then set the signal from which channel the value should be taken. One click on DONE shows the value at the bottom of the channel settings. You may choose among the following:

    - **P2P:** The difference between the lowest and the highest measured voltage value.
    - **MEAN:** The signal's calculated average.
    - **MAX:** The maximum voltage value measured.
    - **MIN:** The lowest voltage value measured.
    - **RMS:** The calculated RMS (root mean square) of the signal.
    - **DUTY CYCLE:** The signal’s duty cycle (ratio of the pulse duration and period length).
    - **PERIOD:** Displays the period length, the time length of a vibration.
    - **FREQ:** The frequency of the signal.

.. figure:: Slika_10_OSC.png

Specifications
**************

Oscilloscope
============

.. tabularcolumns:: |p{70mm}|p{50mm}|p{50mm}|p{50mm}|p{50mm}|p{50mm}|

+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
|                             | STEMlab 125-10                  | STEMlab 125-14                  | STEMlab 125-14 4Ch Z7020 LN     | SDRlab 122-16                | SIGNALlab 250-12             |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| Input channels              | 2                               | 2                               | 4                               | 2                            | 2                            |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| Bandwidth                   | 40 MHz                          | 50 MHz                          | 50 MHz                          | 300 kHz - 50 MHz             | 60 MHz                       |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| Resolution                  | 10 bit                          | 14 bit                          | 14 bit                          | 16 bit                       | 12 bit                       |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| Memory depth                | 16k samples                     | 16k samples                     | 16k samples                     | 16k samples                  | 16k samples                  |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| Input range                 | ± 1V (LV) and ± 20V (HV) [#f1]_ | ± 1V (LV) and ± 20V (HV) [#f1]_ | ± 1V (LV) and ± 20V (HV) [#f1]_ | ± 0.25V / -2 dBm             | ± 1V / ± 20V [#f2]_          |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| Input coupling              | DC                              | DC                              | DC                              | AC                           | AC/DC [#f2]_                 |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| Minimal Voltage Sensitivity | ± 1.95mV / ± 39mV               | ± 0.122mV / ± 2.44mV            | ± 0.122mV / ± 2.44mV            | ± 7.6uV                      | ± 0.488mV / ± 9.76mV         |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| External Trigger            | through extension connector     | through extension connector     | through extension connector     | through extension connector  | through BNC connector        |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+
| Input impedance             | 1 MΩ                            | 1 MΩ                            | 1 MΩ                            | 50 Ω                         | 1 MΩ                         |
+-----------------------------+---------------------------------+---------------------------------+---------------------------------+------------------------------+------------------------------+


Signal generator
================

.. tabularcolumns:: |p{70mm}|p{50mm}|p{50mm}|p{50mm}|p{50mm}|p{50mm}|

+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+
|                  | STEMlab 125-10       | STEMlab 125-14       | STEMlab 125-14 4Ch Z7020 LN   | SDRlab 122-16        | SIGNALlab 250-12                        |
+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+
| Output channels  | 2                    | 2                    | N/A                           | 2                    | 2                                       |
+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+
| Frequency Range  | 0 - 50 MHz           | 0 - 50 MHz           | N/A                           | 300 kHz - 60 MHz     | 0 - 60 MHz                              |
+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+
| Resolution       | 10 bit               | 14 bit               | N/A                           | 14 bit               | 12 bit                                  |
+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+
| Signal buffer    | 16k samples          | 16k samples          | N/A                           | 16k samples          | 16k samples                             |
+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+
| Output range     | ± 1V                 | ± 1V                 | N/A                           | ± 0.5V/ +4dBm        | ± 1V / ± 5V (into 50 ohm load) [#f2]_   |
|                  |                      |                      |                               |                      | ± 2V / ± 10V (Hi-Z load) [#f2]_         | 
+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+
| Coupling         | DC                   | DC                   | N/A                           | AC                   | DC                                      |
+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+
| Output load      | 50 Ω                 | 50 Ω                 | N/A                           | 50 Ω                 | 50 Ω                                    |
+------------------+----------------------+----------------------+-------------------------------+----------------------+-----------------------------------------+

.. [#f1]
    jumper selectable

.. [#f2]
    software selectable

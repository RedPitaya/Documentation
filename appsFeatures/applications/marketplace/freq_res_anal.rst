***************************
Frequency Response analyzer
***************************

The Frequency Response analyzer enables the measurements of
the frequency amplitude response of the desired DUT (Device Under Test).
The measurements of the frequency response are in the range from 0Hz to 60MHz.
The measurements are done in real time and the frequency range is NOT adjustable.
Measuring can be done for each channel independently,
i.e. it enables simultaneous measurements of two DUTs.
The application works in such way that it is generating band noise signals on OUT1 and OUT2,
this signal is fed to the DUT where the DUT’s response is acquired on IN1 and IN2.
The acquired signals are analyzed using the DFT algorithm and
the frequency response of the DUT is plotted on the GUI.
This application is very useful for filter measurements and similar.

.. figure:: 600px-F_analyzer.png

Frequency response analyzer enables measurements of frequency amplitude response of desired DUT (Device Under Test).
The measurements of frequency response are in range from 0Hz to 60MHz.
Measurements are in real time and the frequency range is NOT adjustable.
Measurement can be done for each channel independently, i.e it enables simultaneously measurements of two DUTs.
How to connect DUT to the Red Pitaya when using Frequency Response analyser is shown in picture below.

.. figure:: 600px-Frequency_response_analyzer_connections.png

.. note::

   Frequency response analyzer application is available on Red Pitaya marketplace.
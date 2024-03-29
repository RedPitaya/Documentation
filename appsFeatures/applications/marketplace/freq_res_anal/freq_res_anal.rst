.. _freqRes_app:

***************************
Frequency Response Analyzer
***************************

The Frequency Response analyzer enables measurements of the frequency amplitude response of the desired DUT (Device Under Test). The measurements of the frequency response are in the range from 0 Hz to 60 MHz. The measurements are done in real time and the frequency range is NOT adjustable. Measuring can be done for each channel independently, i.e., it enables simultaneous measurements of two DUTs.

The application works in such a way that it generates band noise signals on OUT1 and OUT2. This signal is fed to the DUT where the DUT’s response is acquired on IN1 and IN2. The acquired signals are analysed using the DFT algorithm, and the frequency response of the DUT is plotted on the GUI. This application is very useful for filter measurements and similar.

.. figure:: 600px-F_analyzer.png
    :width: 600

The Frequency Response Analyzer enables measurements of the frequency amplitude response of a desired DUT (Device Under Test). The measurements of frequency response are in the range from 0 Hz to 60 MHz. Measurements are in real time and the frequency range is NOT adjustable. Measurement can be done for each channel independently, i.e., it enables simultaneous measurements of two DUTs. How to connect DUT to the Red Pitaya when using the Frequency Response Analyzer is shown in the picture below.

.. figure:: 600px-Frequency_response_analyzer_connections.png
    :width: 600

.. note::

   The Frequency Response Analyzer application is available on the Red Pitaya marketplace.

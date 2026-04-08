.. _fpga_tutorials_rf_inputs:

#################
RF Inputs
#################

Red Pitaya boards feature high-speed analog RF inputs capable of acquiring signals at up to 125 Msps. This section provides hands-on FPGA tutorials that teach you how to process 
and manipulate these input signals directly in the FPGA fabric.

Through these tutorials, you'll learn how to:

* Interface with the ADC data stream and process raw samples
* Implement signal triggering and conditional data capture
* Create digital signal processing blocks like decimation filters and moving averages
* Connect RF input data to other FPGA peripherals (GPIOs, LEDs, custom logic)
* Build voltage threshold detectors and event-driven logic

Whether you're building custom measurement instruments, implementing real-time signal analysis, or creating specialized data acquisition systems, these tutorials will give you 
the foundational skills to work effectively with RF inputs in your FPGA designs.

.. toctree::
    :maxdepth: 1

    moving_average


.. note::

    We will expand the tutorials in this section over time, so check back regularly for new content and examples related to RF input processing on Red Pitaya boards.

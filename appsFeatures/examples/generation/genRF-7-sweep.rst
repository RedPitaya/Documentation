Generate sweep signal
##########################

Description
=============

This example shows how to program Red Pitaya to generate a sweep signal from 100 Hz to 100 kHz. Voltage and frequency ranges depend on the Red Pitaya model.


Required hardware
==================

    - Red Pitaya device

.. figure:: ../general_img/RedPitaya_general.png


SCPI Code Examples
====================

Code - MATLAB®
---------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab



Code - Python
-----------------

.. code-block:: python

    #!/usr/bin/env python3
    import redpitaya_scpi as scpi
    
    channel = 1
    
    waveform = 'sine'
    ampl = 1
    
    # Sweep settings
    sweep_start_freq = 100
    sweep_stop_freq = 100000
    sweep_time_us = 5000000     # in microseconds
    sweep_mode = "log"          # linear / log
    sweep_dir = "up_down"       # normal / up_down
    
    
    IP = 'rp-f0a235.local'          # Connecting to Red Pitaya
    rp = scpi.scpi(IP)
    
    rp.tx_txt("GEN:RST")
    
    rp.tx_txt(f"SOUR{channel}:FUNC {waveform.upper()}")     # Specifying waveform
    rp.tx_txt(f"SOUR{channel}:VOLT {ampl}")         # Setting one-way amplitude
    
    # Configuring Sweep settings
    rp.tx_txt(f"SOUR{channel}:SWeep:FREQ:START {sweep_start_freq}")     # Start frequency
    rp.tx_txt(f"SOUR{channel}:SWeep:FREQ:STOP {sweep_stop_freq}")       # Stop/End frequency
    rp.tx_txt(f"SOUR{channel}:SWeep:TIME {sweep_time_us}")              # Sweep time in us
    
    rp.tx_txt(f"SOUR{channel}:SWeep:MODE {sweep_mode.upper()}")         # Sweep mode
    rp.tx_txt(f"SOUR{channel}:SWeep:DIR {sweep_dir.upper()}")           # Direction
    
    rp.tx_txt(f"SOUR{channel}:SWeep:STATE ON")                          # Turning ON sweep mode
    rp.tx_txt(f"OUTPUT{channel}:STATE ON")                              # Enabling output channel
    rp.tx_txt(f"SOUR{channel}:TRIG:INT")                                # Triggering the generator
    
    rp.close()




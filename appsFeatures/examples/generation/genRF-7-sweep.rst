Generate sweep signal
##########################

Description
=============

This example shows how to program Red Pitaya to generate a sweep signal from 100 Hz to 100 kHz. Voltage and frequency ranges depend on the Red Pitaya model.


Required hardware
==================

    - Red Pitaya device

.. figure:: ../general_img/RedPitaya_general.png


Required software
==================

- :ref:`Red Pitaya Nightly Build OS or higher <prepareSD>`


SCPI Code Examples
====================

Code - MATLAB®
---------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Variables
    waveform = 'sine';
    ampl = 1;
    
    % Sweep settings
    sweep_start_freq = 100;
    sweep_stop_freq = 100000;
    sweep_time_us = 5000000;    % in microseconds
    sweep_mode = 'log';         % linear / log
    sweep_dir = 'up_down';       % normal / up_down
    
    
    %% Define Red Pitaya as TCP client object
    
    IP = 'rp-f0a235.local';           % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);
    
    %% Open connection with your Red Pitaya
    RP.ByteOrder = "big-endian";
    configureTerminator(RP, "CR/LF");
    
    % Reset Generation
    writeline(RP,'GEN:RST');
    
    writeline(RP, append('SOUR1:FUNC ', upper(waveform)));
    
    % Configure sweep settings
    writeline(RP, append('SOUR1:SWeep:FREQ:START ', num2str(sweep_start_freq)));
    writeline(RP, append('SOUR1:SWeep:FREQ:STOP ', num2str(sweep_stop_freq)));
    writeline(RP, append('SOUR1:SWeep:TIME ', num2str(sweep_time_us)));
    
    writeline(RP, append('SOUR1:SWeep:MODE ', upper(sweep_mode)));
    writeline(RP, append('SOUR1:SWeep:DIR ', upper(sweep_dir)));
    
    writeline(RP, 'SOUR1:SWeep:STATE ON');
    writeline(RP, 'OUTPUT1:STATE ON');
    writeline(RP, 'SOUR1:TRIG:INT');
    
    %% Close connection with Red Pitaya
    clear RP;



Code - Python
-----------------

**Using just SCPI commands:**

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

**Using functions: (IN DEV)**

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
    
    # Set generator settings (waveform and amplitude, frequency does not matter)
    rp.gen_set(channel, waveform, ampl, sweep_start_freq)
    
    # Set sweep mode settings
    rp.gen_sweep_set(channel, sweep_start_freq, sweep_stop_freq, sweep_time_us, sweep_mode, sweep_dir)
    
    rp.tx_txt(f"SOUR{channel}:SWeep:STATE ON")                          # Turning ON sweep mode
    rp.tx_txt(f"OUTPUT{channel}:STATE ON")                              # Enabling output channel
    rp.tx_txt(f"SOUR{channel}:TRIG:INT")                                # Triggering the generator
    
    rp.close()


.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>



API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead, the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information are :ref:`here <comC>`.

Code - C API
---------------

.. code-block:: c



Code - Python API
------------------

.. code-block:: python





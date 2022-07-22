Synchronised one-pulse signal generation and acquisition
########################################################


.. http://blog.redpitaya.com/examples-new/synchronized-one-pulse-generating-and-acquiring/


Description
***********

This example shows how to acquire 16k samples of signal on fast analog inputs. The signal will be acquired simultaneously with the generated signal. The time length of the acquired signal depends on the time scale of a buffer that can be set with a decimation factor. The decimations and time scales of a buffer are given in the |sample rate and decimation|. Voltage and frequency ranges depend on the Red Pitaya model. 

.. |sample rate and decimation| raw::html
    <a href="https://redpitaya.readthedocs.io/en/latest/appsFeatures/examples/acqRF-samp-and-dec.html#sampling-rate-and-decimations" target="_blank">table</a>


Required hardware
*****************

    - Red Pitaya device

Wiring example for STEMlab 125-14 & STEMlab 125-10:   
 
.. figure:: generate_continous_signal_on_fast_analog_output.png

Circuit
*******

.. figure:: generate_continous_signal_on_fast_analog_output_circuit1.png

Code - MATLAB®
**************

.. code-block:: matlab

    The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

    clc
    clear all
    close all

    IP = '192.168.178.111';           % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya
    RP.ByteOrder = "big-endian";
    configureTerminator(RP,"CR/LF");
    
    flush(RP);


    %% The example generate sine bursts every 0.5 seconds
    writeline(RP,'GEN:RST');                        % Reset Generator & Acquisition
    writeline(RP,'ACQ:RST');

    writeline(RP,'SOUR1:FUNC SINE');
    writeline(RP,'SOUR1:FREQ:FIX 1000000');         % Set frequency of output signal
    writeline(RP,'SOUR1:VOLT 1');                   % Set amplitude of output signal

    writeline(RP,'SOUR1:BURS:STAT BURST');      % Set burst mode to BURST
    writeline(RP,'SOUR1:BURS:NCYC 3');          % Set 3 pulses of sine wave

    %% Set Acquisition

    writeline(RP,'ACQ:DEC 1');
    writeline(RP,'ACQ:TRIG:LEV 0');
    writeline(RP,'ACQ:TRIG:DLY 0');


    %% Start gen % acq

    writeline(RP,'ACQ:START');
    pause(1);
    writeline(RP,'ACQ:TRIG AWG_PE');
    writeline(RP,'OUTPUT1:STATE ON');           % Set output to ON
    pause(1);
    
    writeline(RP,'SOUR1:TRIG:INT');
    
    %% Wait for trigger
    while 1
        trig_rsp = writeread(RP,'ACQ:TRIG:STAT?')
        if strcmp('TD',trig_rsp(1:2))
            break;
        end
    end

    %% Read & plot

    signal_str = writeread(RP,'ACQ:SOUR1:DATA?');
    signal_num = str2num(signal_str(1, 2:length(signal_str) - 3));
    plot(signal_num)
    grid on

    %% Close connection with Red Pitaya
    clear RP;


Code - Python
*************

.. code-block:: python

    import sys
    import time
    import matplotlib.pyplot as plt
    import redpitaya_scpi as scpi

    IP = '192.168.178.111'
    rp_s = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 1000000
    ampl = 1

    # Generation
    rp_s.tx_txt('GEN:RST')
    rp_s.tx_txt('ACQ:RST')

    rp_s.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR1:VOLT ' + str(ampl))

    rp_s.tx_txt('SOUR1:BURS:STAT BURST')        # Mode set to BURST
    rp_s.tx_txt('SOUR1:BURS:NCYC 3')            # 3 periods in each burst

    # Acqusition
    rp_s.tx_txt('ACQ:DEC 1')
    rp_s.tx_txt('ACQ:TRIG:LEV 0')
    rp_s.tx_txt('ACQ:TRIG:DLY 0')

    rp_s.tx_txt('ACQ:START')
    time.sleep(1)
    rp_s.tx_txt('ACQ:TRIG AWG_PE')
    rp_s.tx_txt('OUTPUT1:STATE ON')
    time.sleep(1)

    rp_s.tx_txt('SOUR1:TRIG:INT')

    # Wait for trigger
    while 1:
        rp_s.tx_txt('ACQ:TRIG:STAT?')           # Get Trigger Status
        if rp_s.rx_txt() == 'TD':               # Triggerd?
            break


    # Read data and plot

    rp_s.tx_txt('ACQ:SOUR1:DATA?')              # Read full buffer (source 1)
    data_string = rp_s.rx_txt()                 # data into a string

    # Remove brackets and empty spaces + string => float
    data_string = data_string.strip('{}\n\r').replace("  ", "").split(',')    
    data = list(map(float, data_string))        # transform data into float

    plt.plot(data)
    plt.show()



Code - LabVIEW
**************

.. figure:: Synchronised-one-pulse-signal-generation-and-acquisition_LV.png

`Download <https://downloads.redpitaya.com/downloads/Clients/labview/Synchronised%20one%20pulse%20signal%20generation%20and%20acquisition.vi>`_

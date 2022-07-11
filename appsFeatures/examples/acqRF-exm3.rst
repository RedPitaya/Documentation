Synchronised one pulse signal generation and acquisition
########################################################


.. http://blog.redpitaya.com/examples-new/synchronized-one-pulse-generating-and-acquiring/


Description
***********

This example shows how to acquire 16k samples of signal on fast analog inputs. Signal will be acquired simultaneously with the generated signal. Time length of the acquired signal depends on the time scale of a buffer that can be set with a decimation factor. Decimations and time scales of a buffer are given in the :ref:`table <s_rate_and_dec>`. Voltage and frequency ranges depend on Red Pitaya model. 


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

    The code is written in MATLAB. In the code we use SCPI commands and TCP client communication. Copy code to MATLAB editor and press run.

    clc
    clear all
    close all

    IP= '192.168.178.111';           % Input IP of your Red Pitaya...
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


Code - LabVIEW
**************

.. figure:: Synchronised-one-pulse-signal-generation-and-acquisition_LV.png

`Download <https://downloads.redpitaya.com/downloads/Clients/labview/Synchronised%20one%20pulse%20signal%20generation%20and%20acquisition.vi>`_

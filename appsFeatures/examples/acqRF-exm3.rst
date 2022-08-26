Triggering on external trigger
######################################

.. http://blog.redpitaya.com/examples-new/on-given-external-trigger-acquire-signal-on-fast-analog-input/

Description
***********

This example shows how to acquire 16k samples of a signal on fast analog inputs. The signal will be acquired when the external trigger condition is met. The time length of the acquired signal depends on the time scale of a buffer that can be set with a decimation factor. The decimations and time scales of a buffer are given in the |sample rate and decimation|. Voltage and frequency ranges depend on the Red Pitaya model. 

.. |sample rate and decimation| raw:: html

    <a href="https://redpitaya.readthedocs.io/en/latest/appsFeatures/examples/acqRF-samp-and-dec.html#sampling-rate-and-decimations" target="_blank">table</a>


Required hardware
*****************

    - Red Pitaya device
    - Signal (function) generator
    
Wiring example for STEMlab 125-14 & STEMlab 125-10:

.. figure:: on_given_external_trigger_acquire_signal_on_fast_analog_input.png

Circuit
*******

.. figure:: on_given_external_trigger_acquire_signal_on_fast_analog_input_circuit.png


Code - MATLAB®
**************

.. code-block:: matlab

    The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

    %% Define Red Pitaya as TCP/IP object
    clear all
    close all
    clc
    IP = '192.168.178.111';                % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya

    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');

    flush(RP);

    % Set decimation value (sampling rate) in respect to your 
    % acquired signal frequency

    writeline(RP,'ACQ:RST');
    writeline(RP,'ACQ:DEC 4');


    % Set trigger delay to 0 samples
    % 0 samples delay sets trigger to center of the buffer
    % Signal on your graph will have trigger in the center (symmetrical)
    % Samples from left to the center are samples before the trigger 
    % Samples from center to the right are samples after the trigger

    writeline(RP,'ACQ:TRIG:DLY 0');

    % for SIGNALlab device there is a possiblity to set the trigger threshold 
    % writeline(RP,'ACQ:TRIG:EXT:LEV 1')


    %% Start & Trigg
    % Trigger source setting must be after ACQ:START
    % Set trigger to source 1 positive edge

    writeline(RP,'ACQ:START');
    % After acquisition is started some time delay is needed in order to acquire fresh samples in to buffer
    pause(1);
    % Here we have used time delay of one second but you can calculate the exact value taking in to account buffer
    % length and sampling rate

    writeline(RP,'ACQ:TRIG EXT_PE');
    % Wait for trigger
    % Until trigger is true wait with acquiring
    % Be aware of while loop if trigger is not achieved
    % Ctrl+C will stop code execution in MATLAB

    while 1
        trig_rsp = writeread(RP,'ACQ:TRIG:STAT?')
    
        if strcmp('TD',trig_rsp(1:2))  % Read only TD
    
            break;
    
        end
    end
    
    % % FUTURE BETA
    % % wait for fill adc buffer
    % while 1
    %     fill_state = writeread(RP,'ACQ:TRIG:FILL?')
    %     
    %     if strcmp('1', fill_state(1:1))
    % 
    %         break;
    % 
    %     end
    % end
    
    % Read data from buffer 
    signal_str   = writeread(RP,'ACQ:SOUR1:DATA?');
    signal_str_2 = writeread(RP,'ACQ:SOUR2:DATA?');

    % Convert values to numbers.
    % The first character in string is “{“   
    % and the last 3 are 2 spaces and “}”.  

    signal_num   = str2num(signal_str  (1, 2:length(signal_str)  - 3));
    signal_num_2 = str2num(signal_str_2(1,2:length(signal_str_2) - 3));

    plot(signal_num)
    hold on
    plot(signal_num_2,'r')
    grid on
    ylabel('Voltage / V')
    xlabel('samples')

    clear RP;


Code - Python
*************

.. code-block:: python
    
    #!/usr/bin/python3
    
    import sys
    import redpitaya_scpi as scpi
    import matplotlib.pyplot as plot

    rp_s = scpi.scpi(sys.argv[1])

    rp_s.tx_txt('ACQ:DEC 4')
    rp_s.tx_txt('ACQ:START')
    rp_s.tx_txt('ACQ:TRIG EXT_PE')

    while 1:
        rp_s.tx_txt('ACQ:TRIG:STAT?')
        if rp_s.rx_txt() == 'TD':
            break
    
    ## FUTURE BETA
    # while 1:
    #     rp_s.tx_txt('ACQ:TRIG:FILL?')
    #     if rp_s.rx_txt() == '1':
    #         break

    rp_s.tx_txt('ACQ:SOUR1:DATA?')
    buff_string = rp_s.rx_txt()
    buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
    buff = list(map(float, buff_string))

    plot.plot(buff)
    plot.ylabel('Voltage')
    plot.show()


Code - LabVIEW
**************

.. figure:: Signal-acquisition-on-external-trigger_LV.png

`Download <https://downloads.redpitaya.com/downloads/Clients/labview/Signal%20acquisition%20on%20external%20trigger.vi>`_

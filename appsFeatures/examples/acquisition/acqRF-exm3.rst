Triggering on external trigger
######################################

.. http://blog.redpitaya.com/examples-new/on-given-external-trigger-acquire-signal-on-fast-analog-input/

Description
=============

This example shows how to acquire 16k samples of a signal on fast analog inputs. The signal will be acquired when the external trigger condition is met. The time length of the acquired signal depends on the time scale of a buffer that can be set with a decimation factor. The decimations and time scales of a buffer are given in the :ref:`sample rate and decimation <s_rate_and_dec>`. Voltage and frequency ranges depend on the Red Pitaya model. 


Required hardware
===================

    -   Red Pitaya device
    -   Signal (function) generator
    
Wiring example for STEMlab 125-14 & STEMlab 125-10:

.. figure:: img/on_given_external_trigger_acquire_signal_on_fast_analog_input.png

Circuit
========

.. figure:: img/on_given_external_trigger_acquire_signal_on_fast_analog_input_circuit.png


SCPI Code Examples
====================


Code - MATLAB®
---------------

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

    % Reset Acquisition
    writeline(RP,'ACQ:RST');

    %% ACQUISITION
    % Set decimation value (sampling rate) in respect to your 
    % acquired signal frequency

    writeline(RP,'ACQ:DEC 4');

    % For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    writeline(RP,'ACQ:TRIG:EXT:DEBouncerUs 500');


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
    
    % wait for fill adc buffer
    while 1
        fill_state = writeread(RP,'ACQ:TRIG:FILL?')
        if strcmp('1', fill_state(1:1))
            break;
        end
    end
    
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
--------------

Using just SCPI commands:

.. code-block:: python
    
    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi
    import matplotlib.pyplot as plot

    IP = 'rp-f066c8.local'

    rp_s = scpi.scpi(IP)
    
    rp_s.tx_txt('ACQ:RST')

    rp_s.tx_txt('ACQ:DEC 4')

    # For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    rp_s.tx_txt('ACQ:TRIG:EXT:DEBouncerUs 500')

    rp_s.tx_txt('ACQ:START')
    rp_s.tx_txt('ACQ:TRIG EXT_PE')

    while 1:
        rp_s.tx_txt('ACQ:TRIG:STAT?')
        if rp_s.rx_txt() == 'TD':
            break
    
    while 1:
        rp_s.tx_txt('ACQ:TRIG:FILL?')
        if rp_s.rx_txt() == '1':
            break

    rp_s.tx_txt('ACQ:SOUR1:DATA?')
    buff_string = rp_s.rx_txt()
    buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
    buff = list(map(float, buff_string))

    plot.plot(buff)
    plot.ylabel('Voltage')
    plot.show()


Using functions:

.. code-block:: python
    
    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi
    import matplotlib.pyplot as plot

    IP = 'rp-f066c8.local'

    dec = 4

    rp_s = scpi.scpi(IP)

    rp_s.tx_txt('ACQ:RST')
    
    # Function for configuring Acquisitio
    rp_s.acq_set(dec)

    # For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    rp_s.tx_txt('ACQ:TRIG:EXT:DEBouncerUs 500')
    
    rp_s.tx_txt('ACQ:START')
    rp_s.tx_txt('ACQ:TRIG EXT_PE')

    while 1:
        rp_s.tx_txt('ACQ:TRIG:STAT?')
        if rp_s.rx_txt() == 'TD':
            break
    
    while 1:
        rp_s.tx_txt('ACQ:TRIG:FILL?')
        if rp_s.rx_txt() == '1':
            break

    # function for Data Acquisition
    buff = rp_s.acq_data(1, convert= True)

    plot.plot(buff)
    plot.ylabel('Voltage')
    plot.show()


.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>


Code - LabVIEW
----------------

.. figure:: img/Signal-acquisition-on-external-trigger_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Signal%20acquisition%20on%20external%20trigger.vi>`_



API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information is :ref:`here <comC>`.


Code - C API
---------------

.. code-block:: c

    /* Red Pitaya C API example of Acquiring a signal on external trigger on a specific channel */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include "rp.h"


    int main(int argc, char **argv){

        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
            fprintf(stderr, "Rp api init failed!\n");
        }

        /* Reset Generation and Acquisition */
        rp_GenReset();
        rp_AcqReset();

        /* Generation */
        /*LOOB BACK FROM OUTPUT 2 - ONLY FOR TESTING*/
        rp_GenFreq(RP_CH_1, 20000.0);
        rp_GenAmp(RP_CH_1, 1.0);
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
        rp_GenOutEnable(RP_CH_1);


        /* Acquisition */
        uint32_t buff_size = 16384;
        float *buff = (float *)malloc(buff_size * sizeof(float));

        rp_AcqSetDecimation(RP_DEC_8);
        rp_AcqSetTriggerLevel(RP_CH_1, 0.5); //Trig level is set in Volts while in SCPI
        rp_AcqSetTriggerDelay(0);

        // There is an option to select coupling when using SIGNALlab 250-12
        // rp_AcqSetAC_DC(RP_CH_1, RP_AC);           // enables AC coupling on Channel 1

        // By default LV level gain is selected
        rp_AcqSetGain(RP_CH_1, RP_LOW);              // user can switch gain using this command

        rp_AcqStart();

        /* After the acquisition is started some time delay is needed to acquire fresh samples into buffer
        Here we have used a time delay of one second but you can calculate the exact value taking into account buffer
        length and sampling rate*/

        sleep(1);
        rp_AcqSetTriggerSrc(RP_TRIG_SRC_EXT_PE);
        rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;

        while(1){
            rp_AcqGetTriggerState(&state);
            if(state == RP_TRIG_STATE_TRIGGERED){
                break;
            }
        }

        
        bool fillState = false;
        while(!fillState){
            rp_AcqGetBufferFillState(&fillState);
        }

        rp_AcqGetOldestDataV(RP_CH_1, &buff_size, buff);
        int i;
        for(i = 0; i < buff_size; i++){
            printf("%f\n", buff[i]);
        }

        /* Releasing resources */
        free(buff);
        rp_Release();
        return 0;
    }


Code - Python API
------------------

.. code-block:: python

    #!/usr/bin/python3

    import time
    import numpy as np
    import rp


    #? Possible decimations:
    #?  RP_DEC_1, RP_DEC_2, RP_DEC_4, RP_DEC_8, RP_DEC_16 , RP_DEC_32 , RP_DEC_64 ,
    #?  RP_DEC_128, RP_DEC_256, RP_DEC_512, RP_DEC_1024, RP_DEC_2048, RP_DEC_4096, RP_DEC_8192, 
    #?  RP_DEC_16384, RP_DEC_32768, RP_DEC_65536

    dec = rp.RP_DEC_1

    trig_lvl = 0.5
    trig_dly = 0

    #? Possible acquisition trigger sources:
    #?  RP_TRIG_SRC_DISABLED, RP_TRIG_SRC_NOW, RP_TRIG_SRC_CHA_PE, RP_TRIG_SRC_CHA_NE, RP_TRIG_SRC_CHB_PE,
    #?  RP_TRIG_SRC_CHB_NE, RP_TRIG_SRC_EXT_PE, RP_TRIG_SRC_EXT_NE, RP_TRIG_SRC_AWG_PE, RP_TRIG_SRC_AWG_NE, 
    #?  RP_TRIG_SRC_CHC_PE, RP_TRIG_SRC_CHC_NE, RP_TRIG_SRC_CHD_PE, RP_TRIG_SRC_CHD_NE

    acq_trig_sour = rp.RP_TRIG_SRC_EXT_PE
    N = 16384

    # Initialize the interface
    rp.rp_Init()

    # Reset Aquisition
    rp.rp_AcqReset()

    ##### Acquisition #####
    # Set Decimation
    rp.rp_AcqSetDecimation(dec)

    #? Possible triggers:
    #?  RP_T_CH_1, RP_T_CH_2, RP_T_CH_3, RP_T_CH_4, RP_T_CH_EXT

    # Set trigger level
    rp.rp_AcqSetTriggerLevel(rp.RP_T_CH_1, trig_lvl)

    # Set trigger delay
    rp.rp_AcqSetTriggerDelay(trig_dly)


    print("Acq_start")
    # Start Acquisition
    rp.rp_AcqStart()

    # Specify trigger - input 1 positive edge
    rp.rp_AcqSetTriggerSrc(acq_trig_sour)

    # Trigger state
    while 1:
        trig_state = rp.rp_AcqGetTriggerState()[1]
        if trig_state == rp.RP_TRIG_STATE_TRIGGERED:
            break

    # Fill state
    while 1:
        if rp.rp_AcqGetBufferFillState()[1]:
            break


    ### Get data ###
    # RAW
    ibuff = rp.i16Buffer(N)
    res = rp.rp_AcqGetOldestDataRaw(rp.RP_CH_1, N, ibuff.cast())

    # Volts
    fbuff = rp.fBuffer(N)
    res = rp.rp_AcqGetDataV(rp.RP_CH_1, 0, N, fbuff)

    data_V = np.zeros(N, dtype = float)
    data_raw = np.zeros(N, dtype = int)

    for i in range(0, N, 1):
        data_V[i] = fbuff[i]
        data_raw[i] = ibuff[i]
 
    print(f"Data in Volts: {data_V}")
    print(f"Raw data: {data_raw}")


    # Release resources
    rp.rp_Release()


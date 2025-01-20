
Instant signal acquisition
##########################

Description
=============

This example shows how to instantly acquire 16k samples of a signal on fast analog inputs.
The time length of the acquired signal depends on the time scale of a buffer that can be set with a decimation factor.
The decimations and time scales of a buffer are given in the :ref:`sample rate and decimation <s_rate_and_dec>`.
Voltage and frequency ranges depend on the Red Pitaya model.


Required hardware
====================

    -   Red Pitaya device
    -   Signal (function) generator
    
Wiring example:

.. figure:: img/on_given_trigger_acquire_signal_on_fast_analog_input.png


Required software
==================

.. include:: ../sw_requirement.inc


Circuit
=========

.. figure:: img/on_given_trigger_acquire_signal_on_fast_analog_input_circuit.png


SCPI Code Examples
====================

.. include:: ../dec_factor_note.inc
    
Code - MATLAB®
----------------

.. include:: ../matlab.inc

.. code-block:: matlab

    %% Define Red Pitaya as TCP/IP object
    close all
    clc
    IP = 'rp-f0a235.local';                % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    dec = 1;
    trig_lvl = 0.1;
    gain = 'LV';
    % coupling = 'AC';      % SIGNALlab 250-12 only
    trig_dly = 0;
    acq_trig = 'CH1_PE';

    %% Open connection with your Red Pitaya
    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');
    flush(RP);

    % Reset Acquisition
    writeline(RP,'ACQ:RST');

    %% ACQUISITION
    % Set decimation vale (sampling rate) in respect to the
    % acquired signal frequency

    writeline(RP, append('ACQ:DEC:Factor ', num2str(dec)));

    % Set trigger delay to 0 samples
    % 0 samples delay set trigger to center of the acquired data buffer
    % The triggering moment is in the center (8192nd sample)
    % Samples from left to the center were acquired before the trigger
    % Samples from center to the right were acquired after the trigger

    writeline(RP, append('ACQ:TRig:DLY ', num2str(trig_dly)));

    % SIGNALlab 250-12 has an option to set the external trigger level threshold 
    % writeline(RP, append('ACQ:TRig:EXT:LEV ', trig_lvl));

    %% Start & Trigg
    % Trigger source command must be set after ACQ:START
    % Set trigger to source 1 positive edge

    writeline(RP,'ACQ:START');

    % After acquisition is started, some time delay is needed in order to acquire fresh samples in to buffer
    % Here we use a time delay of one second but you can calculate exact value taking in to account buffer
    % length and sampling rate

    pause(1);

    % Immediately trigger the acquisition
    writeline(RP,'ACQ:TRig NOW');

    % % This loop is not needed as we triggered the acquisition manually
    % while 1
    %     trig_rsp = writeread(RP,'ACQ:TRig:STAT?')
    %     if strcmp('TD', trig_rsp(1:2))  % Read only TD
    %         break;
    %     end
    % end

    % wait for fill adc buffer
    while 1
        fill_state = writeread(RP,'ACQ:TRig:FILL?')
        if strcmp('1', fill_state(1:1))
            break;
        end
    end 
        
    % Read data from buffer 
    data_str   = writeread(RP,'ACQ:SOUR1:DATA?');
    data_str_2 = writeread(RP,'ACQ:SOUR2:DATA?');

    % Convert values to numbers.
    data   = str2num(data_str  (2:length(data_str)  -1));
    data_2 = str2num(data_str_2(2:length(data_str_2)-1));

    hold on
    plot(data)
    plot(data_2,'r')
    grid on
    ylabel('Voltage / V')
    xlabel('Samples')

    clear RP;


Code - Python
--------------

Using SCPI commands:

.. code-block:: python
    
    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi
    import matplotlib.pyplot as plot

    IP = 'rp-f066c8.local'

    rp_s = scpi.scpi(IP)

    rp_s.tx_txt('ACQ:RST')

    rp_s.tx_txt('ACQ:DEC 4')
    rp_s.tx_txt('ACQ:START')
    rp_s.tx_txt('ACQ:TRig NOW')

    while 1:
        rp_s.tx_txt('ACQ:TRig:STAT?')
        if rp_s.rx_txt() == 'TD':
            break

    ## ! OS 2.00 or higher only ! ##
    while 1:
        rp_s.tx_txt('ACQ:TRig:FILL?')
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

    rp_s = scpi.scpi(IP)
    
    rp_s.tx_txt('ACQ:RST')
    
    dec = 4
    
    # Function for configuring Acquisition
    rp_s.acq_set(dec)

    rp_s.tx_txt('ACQ:START')
    rp_s.tx_txt('ACQ:TRig NOW')

    while 1:
        rp_s.tx_txt('ACQ:TRig:STAT?')
        if rp_s.rx_txt() == 'TD':
            break

    ## ! OS 2.00 or higher only ! ##
    while 1:
        rp_s.tx_txt('ACQ:TRig:FILL?')
        if rp_s.rx_txt() == '1':
            break

    # function for Data Acquisition
    buff = rp_s.acq_data(1, convert= True)

    plot.plot(buff)
    plot.ylabel('Voltage')
    plot.show()


.. include:: ../python_scpi_note.inc

API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C API
--------------

.. code-block:: c

    /* Red Pitaya C API example of Instantly acquiring a signal on a specific channel */

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
        rp_AcqSetTriggerLevel(RP_CH_1, 0.5);         // Trig level is set in Volts while in SCPI
        rp_AcqSetTriggerDelay(0);

        // There is an option to select coupling when using SIGNALlab 250-12
        // rp_AcqSetAC_DC(RP_CH_1, RP_AC);           // enables AC coupling on Channel 1

        // By default LV level gain is selected
        rp_AcqSetGain(RP_CH_1, RP_LOW);              // user can switch gain using this command

        rp_AcqStart();

        /* After the acquisition is started some time delay is needed to acquire fresh samples into buffer
        Here we have used a time delay of one second but you can calculate the exact value taking into account buffer
        length and sampling rate */

        sleep(1);
        rp_AcqSetTriggerSrc(RP_TRIG_SRC_NOW);
        rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;

        while(1){
            rp_AcqGetTriggerState(&state);
            if(state == RP_TRIG_STATE_TRIGGERED){
                break;
            }
        }

        %%! OS 2.00 or higher only !%%
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
-------------------

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

    acq_trig_sour = rp.RP_TRIG_SRC_NOW
    N = 16384

    # Initialize the interface
    rp.rp_Init()

    # Reset Acquisition
    rp.rp_AcqReset()

    ##### Acquisition #####
    # Set Decimation
    rp.rp_AcqSetDecimation(dec)


    # Set trigger level and delay
    rp.rp_AcqSetTriggerLevel(rp.RP_T_CH_1, trig_lvl)
    rp.rp_AcqSetTriggerDelay(trig_dly)

    # Start Acquisition
    print("Acq_start")
    rp.rp_AcqStart()

    # Specify trigger - immediately
    rp.rp_AcqSetTriggerSrc(acq_trig_sour)

    # Trigger state
    while 1:
        trig_state = rp.rp_AcqGetTriggerState()[1]
        if trig_state == rp.RP_TRIG_STATE_TRIGGERED:
            break

    ## ! OS 2.00 or higher only ! ##
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


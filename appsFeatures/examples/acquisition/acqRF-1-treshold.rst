.. _trig_threshold_example:

Triggering with a threshold on channel
######################################

Description
============

This example shows how to acquire 16k samples of a signal on fast analog inputs. The signal will be acquired when the internal trigger condition is met. The time length of the acquired signal depends on the time scale of a buffer that can be set with a decimation factor. The decimations and time scales of a buffer are given in the :ref:`sample rate and decimation <s_rate_and_dec>`. Voltage and frequency ranges depend on the Red Pitaya model. 


Required hardware
==================

    -   Red Pitaya device
    -   Signal (function) generator
    
Wiring example:

.. figure:: img/on_given_trigger_acquire_signal_on_fast_analog_input.png


Required software
==================

.. include:: ../sw_requirement.inc


Circuit
=======

.. figure:: img/on_given_trigger_acquire_signal_on_fast_analog_input_circuit.png


SCPI Code Examples
====================

.. include:: ../dec_factor_note.inc
    
Code - MATLAB®
---------------

.. include:: ../matlab.inc

In this section choose the desired format and units of the acquired data.
The format can be ASCII or BIN. The units can be VOLTS or RAW.

.. code-block:: matlab

    % Define Red Pitaya as TCP/IP object
    close all
    clc
    IP = 'rp-f0a235.local';         % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    dec = 1;
    trig_lvl = 0;
    gain = 'LV';
    data_format = 'VOLTS';
    data_units = 'ASCII';
    % coupling = 'AC';              % SIGNALlab 250-12 only
    trig_dly = 0;
    acq_trig = 'CH1_PE';

    %% Open connection with your Red Pitaya
    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');
    flush(RP);

    % Acquire Data ASCII/VOLTS MODE
    % Set decimation vale (sampling rate) in respect to the
    % acquired signal frequency

    writeline(RP,'ACQ:RST');
    writeline(RP, append('ACQ:DEC:Factor ', num2str(dec)));
    writeline(RP,append('ACQ:TRig:LEV ', num2str(trig_lvl)));

    % Select acquisition units and format
    writeline(RP, append('ACQ:SOUR1:GAIN ', gain));             % LV gain is selected by default
    writeline(RP, append('ACQ:DATA:FORMAT ', data_format));    
    writeline(RP, append('ACQ:DATA:Units ', data_units));       % RAW/VOLTS => VOLTS, ASCII/RAW => ASCII

    % SIGNALlab 250-12 has an option to select input coupling
    % writeline(RP, append('ACQ:SOUR1:COUP ', coupling));       % enables AC coupling on channel 1

    % Set trigger delay to 0 samples
    % 0 samples delay set trigger to center of the acquired data buffer
    % The triggering moment is in the center (8192nd sample)
    % Samples from left to the center were acquired before the trigger
    % Samples from center to the right were acquired after the trigger

    writeline(RP, append('ACQ:TRig:DLY ', num2str(trig_dly)));

    %% Start & Trigger
    % Trigger source command must be set after ACQ:START
    % Set trigger to source 1 positive edge

    writeline(RP,'ACQ:START');
    % After acquisition is started, some time delay is needed in order to acquire fresh samples in to buffer
    % Here we use a time delay of one second but you can calculate exact value taking in to account buffer
    % length and sampling rate
    pause(1)
    writeline(RP, append('ACQ:TRig ', acq_trig));
    % Wait for trigger
    % Until trigger is true wait with acquiring
    % Be aware of while loop if trigger is not achieved
    % Ctrl+C will stop code executing in MATLAB

    % % This loop can be skipped if waiting for buffer full condition
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

The decoding of the acquired data depends on the selected format and units. The following code that corresponds to the selected units and format should be added at the end of the code block above.

.. tabs::

    .. tab:: ASCII/VOLTS and ASCII/RAW mode

        .. code-block:: matlab
                
            % Read data from buffer
            data_str = writeread(RP,'ACQ:SOUR1:DATA?');

            % Convert values to numbers.
            % The first character in string is a "{"
            % and the last character is a "}".

            data = str2num(data_str(2:length(data_str)-1));

            plot(data)
            grid on
            ylabel('Voltage / V')
            xlabel('Samples')

            clear RP;

    .. tab:: BIN/VOLTS mode

        .. code-block:: matlab
            
            % Read data from buffer
            writeline(RP, 'ACQ:SOUR1:DATA?');
            % Read header for binary format
            header = read(RP, 1);

            % Reading size of block, what informed about data size
            header_size = str2double(strcat(read(RP, 1, 'int8')));

            % Reading size of data (4*16384)
            data_size = str2double(strcat(read(RP, header_size, 'char')));

            % Read data
            data = read(RP, data_size/4, 'single');       % BIN/VOLTS

            plot(data)
            grid on;
            ylabel('Voltage / V')
            xlabel('Samples')

            clear RP;


    .. tab:: BIN/RAW mode

        .. code-block:: matlab

            % Read data from buffer
            writeline(RP, 'ACQ:SOUR1:DATA?');

            % Read header for binary format
            header = read(RP, 1);

            % Reading size of block, what informed about data size
            header_size = str2double(strcat(read(RP, 1, 'int8')));
            
            % Reading size of data
            data_size =   str2double(strcat(read(RP, header_size, 'char'))')
            
            % Read data
            data = read(RP, data_size/2, 'int16');      % BIN/RAW mode
            
            plot(data)
            grid on;
            ylabel('Voltage / V')
            xlabel('Samples')

            clear RP;


    .. tab:: ASCII/VOLTS mode for 4-Input

        .. code-block:: matlab

            % Read data from the buffer 
            data_str   = writeread(RP,'ACQ:SOUR1:DATA?');
            data_str_2 = writeread(RP,'ACQ:SOUR2:DATA?');
            data_str_3 = writeread(RP,'ACQ:SOUR3:DATA?');
            data_str_4 = writeread(RP,'ACQ:SOUR4:DATA?');

            % Convert values to numbers.
            % The first character in string is a "{"
            % and the last 3 are two empty spaces followed by a "}".

            data   = str2num(data_str(2:length(data_str)-1));
            data_2 = str2num(data_str_2(2:length(data_str_2)-1));
            data_3 = str2num(data_str_3(2:length(data_str_3)-1));
            data_4 = str2num(data_str_4(2:length(data_str_4)-1));

            hold on;
            plot(data,'r')
            plot(data_2,'g')
            plot(data_3,'b')
            plot(data_4,'m')
            grid on
            ylabel('Voltage / V')
            xlabel('Samples')

            clear RP;


Code - Python
--------------

**SCPI commands:**

In this section choose the desired format and units of the acquired data.
The format can be ASCII or BIN. The units can be VOLTS or RAW.

.. code-block:: python

    #!/usr/bin/env python3

    import numpy as np
    import matplotlib.pyplot as plt
    import redpitaya_scpi as scpi

    IP = 'rp-f0a235.local'

    dec = 1
    trig_lvl = 0.1
    data_units = 'volts'
    data_format = 'ascii'
    acq_trig = 'CH1_PE'

    rp = scpi.scpi(IP)
                
    rp.tx_txt('ACQ:RST')

    rp.tx_txt(f"ACQ:DEC:Factor {dec}")
    rp.tx_txt(f"ACQ:DATA:Units {data_units.upper()}")
    rp.tx_txt(f"ACQ:DATA:FORMAT {data_format.upper()}")

    rp.tx_txt(f"ACQ:TRig:LEV {trig_lvl}")

    rp.tx_txt('ACQ:START')
    rp.tx_txt(f"ACQ:TRig {acq_trig}")

    while 1:
        rp.tx_txt('ACQ:TRig:STAT?')
        if rp.rx_txt() == 'TD':
            break

    ## ! OS 2.00 or higher only ! ##
    while 1:
        rp.tx_txt('ACQ:TRig:FILL?')
        if rp.rx_txt() == '1':
            break

The decoding of the acquired data depends on the selected format and units. The following code that corresponds to the selected units and format should be added at the end of the code block above.

.. note::

    Do not forget to change the units and format in the code above.

.. tabs::

    .. tab:: ASCII/VOLTS mode

        .. code-block:: python

            rp.tx_txt('ACQ:SOUR1:DATA?')
            buff_string = rp.rx_txt()
            buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
            buff = np.array(buff_string).astype(np.float64)

            plt.plot(buff)
            plt.ylabel('Voltage')
            plt.show()

    .. tab:: BIN/VOLTS mode

        .. code-block:: python

            rp.tx_txt('ACQ:SOUR1:DATA?')
            buff_byte = rp.rx_arb()
            buff = np.frombuffer(buff_byte, dtype='>f4')
            #buff = [struct.unpack('!f', bytearray(buff_byte[i:i+4]))[0] for i in range(0, len(buff_byte), 4)]

            plt.plot(buff)
            plt.ylabel('Voltage')
            plt.show()

    .. tab:: BIN/RAW mode

        .. code-block:: python

            rp.tx_txt('ACQ:SOUR1:DATA?')
            buff_byte = rp.rx_arb()
            buff = np.frombuffer(buff_byte, dtype='>i2')
            #buff = [struct.unpack('!h', bytearray(buff_byte[i:i+2]))[0] for i in range(0, len(buff_byte), 2)]

            plt.plot(buff)
            plt.ylabel('Voltage')
            plt.show()

    .. tab:: ASCII/VOLTS mode 4-Input

        .. code-block:: python

            rp.tx_txt('ACQ:SOUR1:DATA?')
            buff_string = rp.rx_txt()
            buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
            buff = np.array(buff_string).astype(np.float64)

            rp.tx_txt('ACQ:SOUR2:DATA?')
            buff_string = rp.rx_txt()
            buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
            buff2 = np.array(buff_string).astype(np.float64)

            rp.tx_txt('ACQ:SOUR3:DATA?')
            buff_string = rp.rx_txt()
            buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
            buff3 = np.array(buff_string).astype(np.float64)

            rp.tx_txt('ACQ:SOUR4:DATA?')
            buff_string = rp.rx_txt()
            buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
            buff4 = np.array(buff_string).astype(np.float64)

            plt.plot(buff, 'r')
            plt.plot(buff2, 'g')
            plt.plot(buff3, 'b')
            plt.plot(buff4, 'm')
            plt.ylabel('Voltage')
            plt.show()


**SCPI functions:**

.. tabs::

    .. tab:: ASCII/VOLTS mode

        .. code-block:: python

            #!/usr/bin/env python3

            import numpy as np
            import matplotlib.pyplot as plot
            import redpitaya_scpi as scpi

            IP = 'rp-f066c8.local'

            dec = 1
            trig_lvl = 0.5

            rp = scpi.scpi(IP)
            rp.tx_txt('ACQ:RST')
        
            # Function for configuring Acquisition
            rp.acq_set(dec, trig_lvl, units='volts', form='ascii')

            rp.tx_txt('ACQ:START')
            rp.tx_txt('ACQ:TRig CH1_PE')

            while 1:
                rp.tx_txt('ACQ:TRig:STAT?')
                if rp.rx_txt() == 'TD':
                    break

            ## ! OS 2.00 or higher only ! ##
            while 1:
                rp.tx_txt('ACQ:TRig:FILL?')
                if rp.rx_txt() == '1':
                    break

            # function for Data Acquisition
            buff = rp.acq_data(1, bin= False, convert= True)

            plt.plot(buff)
            plt.ylabel('Voltage')
            plt.show()

    .. tab:: BIN/VOLTS mode

        .. code-block:: python

            #!/usr/bin/env python3

            import numpy as np
            import matplotlib.pyplot as plot
            import redpitaya_scpi as scpi

            IP = 'rp-f066c8.local'

            dec = 1
            trig_lvl = 0.5

            rp = scpi.scpi(IP)
            rp.tx_txt('ACQ:RST')
            
            # Function for configuring Acquisition
            rp.acq_set(dec, trig_lvl, units='volts', form='bin')

            rp.tx_txt('ACQ:START')
            rp.tx_txt('ACQ:TRig CH1_PE')

            while 1:
                rp.tx_txt('ACQ:TRig:STAT?')
                if rp.rx_txt() == 'TD':
                    break

            ## ! OS 2.00 or higher only ! ##
            while 1:
                rp.tx_txt('ACQ:TRig:FILL?')
                if rp.rx_txt() == '1':
                    break

            # function for Data Acquisition
            buff = rp.acq_data(1, bin= True, convert= True)

            plt.plot(buff)
            plt.ylabel('Voltage')
            plt.show()

    .. tab:: BIN/RAW mode

        .. code-block:: python
        
            #!/usr/bin/env python3

            import numpy as np
            import matplotlib.pyplot as plot
            import redpitaya_scpi as scpi

            IP = 'rp-f066c8.local'

            dec = 1
            trig_lvl = 0.5

            rp = scpi.scpi(IP)
            rp.tx_txt('ACQ:RST')
            
            # Function for configuring Acquisition
            rp.acq_set(dec, trig_lvl, units='raw', form='bin') 

            rp.tx_txt('ACQ:START')
            rp.tx_txt('ACQ:TRig CH1_PE')

            while 1:
                rp.tx_txt('ACQ:TRig:STAT?')
                if rp.rx_txt() == 'TD':
                    break

            ## ! OS 2.00 or higher only ! ##
            while 1:
                rp.tx_txt('ACQ:TRig:FILL?')
                if rp.rx_txt() == '1':
                    break


            # function for Data Acquisition
            buff = rp.acq_data(1, bin= True, convert= True)

            plt.plot(buff)
            plt.ylabel('Voltage')
            plt.show()

    .. tab:: ASCII/VOLTS mode 4-Input

        .. code-block:: python

            #!/usr/bin/env python3

            import numpy as np
            import matplotlib.pyplot as plot
            import redpitaya_scpi as scpi

            IP = 'rp-f066c8.local'

            dec = 1
            trig_lvl = 0.5
            trig_dly = 0

            rp = scpi.scpi(IP)
            rp.tx_txt('ACQ:RST')
            
            # Function for configuring Acquisition
            rp.acq_set(dec, trig_lvl, trig_delay, units='volts', form='ascii', input4=True) 

            rp.tx_txt('ACQ:START')
            rp.tx_txt('ACQ:TRig CH1_PE')

            while 1:
                rp.tx_txt('ACQ:TRig:STAT?')
                if rp.rx_txt() == 'TD':
                    break

            ## ! OS 2.00 or higher only ! ##
            while 1:
                rp.tx_txt('ACQ:TRig:FILL?')
                if rp.rx_txt() == '1':
                    break

            # function for Data Acquisition
            buff  = rp.acq_data(1, bin= False, convert= True, input4 =True)
            buff2 = rp.acq_data(2, bin= False, convert= True, input4 =True)
            buff3 = rp.acq_data(3, bin= False, convert= True, input4 =True)
            buff4 = rp.acq_data(4, bin= False, convert= True, input4 =True)

            plt.plot(buff, 'r')
            plt.plot(buff2, 'g')
            plt.plot(buff3, 'b')
            plt.plot(buff4, 'm')
            plt.ylabel('Voltage')
            plt.show()


.. include:: ../python_scpi_note.inc

Code - Scilab
-------------

Scilab socket input buffer can read approximately 800 samples from Red Pitaya. This is the problem in contributed code
for Scilab sockets. How to set the socket is described in the Blink example.

.. code-block:: scilab

    clear all
    clc
    
    // Load SOCKET Toolbox. 
    exec(SCI+'contribsocket_toolbox_2.0.1loader.sce'); 
    SOCKET_init();
    
    // Define Red Pitaya as TCP/IP object
    IP= '192.168.178.56';            // Input IP of your Red Pitaya...
    port = 5000;                     // If you are using WiFi then IP is:               
    tcpipObj='RedPitaya';            // 192.168.128.1
    
    // Open connection with your Red Pitaya
    
    SOCKET_open(tcpipObj,IP,port);
    
    // Set decimation value (sampling rate) concerning you 
    // acquired signal frequency
    
    
    SOCKET_write(tcpipObj,'ACQ:RST');
    
    SOCKET_write(tcpipObj,'ACQ:DEC 8');
    
    // Set trigger level to 500 mV
    
    SOCKET_write(tcpipObj,'ACQ:TRig:LEV 0.5');
    
    //There is an option to select coupling when using SIGNALlab 250-12 
    // SOCKET_write(tcpipObj,'ACQ:SOUR1:COUP AC'); // enables AC coupling on Channel 1

    //By default LOW-level gain is selected
    SOCKET_write(tcpipObj,'ACQ:SOUR1:GAIN LV'); // user can switch gain using this command

    // Set trigger delay to 0 samples
    // 0 samples delay set trigger to centre of the buffer
    // Signal on your graph will have a trigger in the centre (symmetrical)
    // Samples from left to centre are samples before the trigger 
    // Samples from the centre to the right are samples after the trigger
    
    SOCKET_write(tcpipObj,'ACQ:TRig:DLY 0');
    
    //// Start & Trigg
    // Trigger source setting must be after ACQ:START
    // Set trigger to source 1 positive edge
    
    SOCKET_write(tcpipObj,'ACQ:START');
    SOCKET_write(tcpipObj,'ACQ:TRig CH1_PE');  
    
    // Wait for the trigger
    // Until the trigger is true wait to acquire
    // Be aware of the while loop if the trigger is not achieved
    // Ctrl+C will stop code executing 
    
    xpause(1E+6)
    
    // Read data from the buffer 
    
    data_str=SOCKET_query(tcpipObj,'ACQ:SOUR1:DATA:OLD:N? 800');
    
    // Convert values to numbers.// First character in the string is “{“  
    // and 2 latest are empty spaces and the last is “}”.  
    data_str=part(data_str, 2:length(data_str)-1)
    data=strtod(strsplit(data_str,",",length(data_str)))';
    
    plot(data)
    
    SOCKET_close(tcpipObj);


Code - LabVIEW
---------------

.. figure:: img/On-trigger-signal-acquisition_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/On%20trigger%20signal%20acquisition.vi>`_



API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C API
---------------

.. tabs::

    .. tab:: 125-10, 125-14, 122-16, 250-12

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
                rp_AcqSetTriggerLevel(RP_CH_1, 0.5);    // Trig level is set in Volts while in SCPI 
                rp_AcqSetTriggerDelay(0);

                // There is an option to select coupling when using SIGNALlab 250-12 
                // rp_AcqSetAC_DC(RP_CH_1, RP_AC);      // enables AC coupling on Channel 1

                // By default LV level gain is selected
                rp_AcqSetGain(RP_CH_1, RP_LOW);         // user can switch gain using this command


                rp_AcqStart();
            
                /* After the acquisition is started some time delay is needed to acquire fresh samples into buffer
                Here we have used a time delay of one second but you can calculate the exact value taking into account buffer
                length and sampling rate */
            
                sleep(1);
                rp_AcqSetTriggerSrc(RP_TRIG_SRC_CHA_PE);
                rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;
            
                while(1){
                    rp_AcqGetTriggerState(&state);
                    if(state == RP_TRIG_STATE_TRIGGERED){
                        break;
                    }
                }

                // !! OS 2.00 or higher only !! //
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

    .. tab:: 125-14 4-Input

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

                uint32_t buff_size = 16384;
                float *buff_ch1 = (float *)malloc(buff_size * sizeof(float));
                float *buff_ch2 = (float *)malloc(buff_size * sizeof(float));
                float *buff_ch3 = (float *)malloc(buff_size * sizeof(float));
                float *buff_ch4 = (float *)malloc(buff_size * sizeof(float));

                /* Reset Acquisition */
                rp_AcqReset();

                /* Acquisition */
                rp_AcqSetDecimation(RP_DEC_8);
                rp_AcqSetTriggerLevel(RP_CH_1, 0.5);
                rp_AcqSetTriggerDelay(0);

                rp_AcqStart();

                /* After the acquisition is started some time delay is needed to acquire fresh samples into buffer
                Here we have used a time delay of one second but you can calculate the exact value taking into account buffer
                length and sampling rate*/

                sleep(1);
                rp_AcqSetTriggerSrc(RP_TRIG_SRC_CHA_PE);
                rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;

                while(1){
                    rp_AcqGetTriggerState(&state);
                    if(state == RP_TRIG_STATE_TRIGGERED){
                        sleep(1);
                        break;
                    }
                }

                // !! OS 2.00 or higher only !! //
                bool fillState = false;
                while(!fillState){
                    rp_AcqGetBufferFillState(&fillState);
                }

                uint32_t pos = 0;        
                rp_AcqGetWritePointerAtTrig(&pos);
                rp_AcqGetDataV2(pos, &buff_size, buff_ch1,buff_ch2, buff_ch3, buff_ch4);

                int i;
                for(i = 0; i < buff_size; i++){
                    printf("%f %f %f %f\n", buff_ch1[i],buff_ch2[i],buff_ch3[i],buff_ch4[i]);
                }

                /* Releasing resources */
                free(buff_ch1);
                free(buff_ch2);
                free(buff_ch3);
                free(buff_ch4);
                rp_Release();

                return 0;
            }  


Code - Python API
-------------------

.. tabs::

    .. tab:: 125-10, 125-14, 122-16, 250-12

        .. code-block:: python

            #!/usr/bin/python3

            import time
            import numpy as np
            import rp


            #? Possible waveforms:
            #?   RP_WAVEFORM_SINE, RP_WAVEFORM_SQUARE, RP_WAVEFORM_TRIANGLE, RP_WAVEFORM_RAMP_UP,
            #?   RP_WAVEFORM_RAMP_DOWN, RP_WAVEFORM_DC, RP_WAVEFORM_PWM, RP_WAVEFORM_ARBITRARY,
            #?   RP_WAVEFORM_DC_NEG, RP_WAVEFORM_SWEEP

            channel = rp.RP_CH_1
            channel2 = rp.RP_CH_2
            waveform = rp.RP_WAVEFORM_SINE
            freq = 100000
            ampl = 1.0

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

            acq_trig_sour = rp.RP_TRIG_SRC_CHA_PE
            N = 16384

            # Initialize the interface
            rp.rp_Init()

            # Reset Generation and Acquisition
            rp.rp_GenReset()
            rp.rp_AcqReset()

            ###### Generation #####
            # OUT1
            print("Gen_start")
            rp.rp_GenWaveform(channel, waveform)
            rp.rp_GenFreqDirect(channel, freq)
            rp.rp_GenAmp(channel, ampl)

            # OUT2
            rp.rp_GenWaveform(channel2, waveform)
            rp.rp_GenFreqDirect(channel2, freq)
            rp.rp_GenAmp(channel2, ampl)

            #? Possible trigger sources:
            #?  RP_GEN_TRIG_SRC_INTERNAL, RP_GEN_TRIG_SRC_EXT_PE, RP_GEN_TRIG_SRC_EXT_NE

            # Specify generator trigger source
            rp.rp_GenTriggerSource(channel, rp.RP_GEN_TRIG_SRC_INTERNAL)

            # Enable output synchronisation
            rp.rp_GenOutEnableSync(True)



            ##### Acquisition #####
            # Set Decimation
            rp.rp_AcqSetDecimation(rp.RP_DEC_1)

            #? Possible triggers:
            #?  RP_T_CH_1, RP_T_CH_2, RP_T_CH_EXT

            # Set trigger level and delay
            rp.rp_AcqSetTriggerLevel(rp.RP_T_CH_1, trig_lvl)
            rp.rp_AcqSetTriggerDelay(trig_dly)


            # Start Acquisition
            print("Acq_start")
            rp.rp_AcqStart()

            # Specify trigger - input 1 positive edge
            rp.rp_AcqSetTriggerSrc(acq_trig_sour)

            rp.rp_GenTriggerOnly(channel)       # Trigger generator

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
                
                
            # Get data
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
    
    .. tab:: 125-14 4-Input

        .. code-block:: python
        
            #!/usr/bin/python3

            import time
            import numpy as np
            import rp
            
            #? Possible channels
            #?  RP_CH_1, RP_CH_2, RP_CH_3, RP_CH_4
            
            acq_channel = rp.RP_CH_1

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

            acq_trig_sour = rp.RP_TRIG_SRC_CHA_PE
            N = 16384

            # Initialize the interface
            rp.rp_Init()

            # Reset Acquisition
            rp.rp_AcqReset()

            ##### Acquisition #####
            # Set Decimation
            rp.rp_AcqSetDecimation(rp.RP_DEC_1)

            #? Possible triggers:
            #?  RP_T_CH_1, RP_T_CH_2, RP_T_CH_3, RP_T_CH_4, RP_T_CH_EXT

            # Set trigger level and delay
            rp.rp_AcqSetTriggerLevel(rp.RP_T_CH_1, trig_lvl)
            rp.rp_AcqSetTriggerDelay(trig_dly)


            # Start Acquisition
            print("Acq_start")
            rp.rp_AcqStart()

            # Specify trigger - input 1 positive edge
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
                
                
            # Get data
            # RAW
            ibuff = rp.i16Buffer(N)
            res = rp.rp_AcqGetOldestDataRaw(acq_channel, N, ibuff.cast())

            # Volts
            fbuff = rp.fBuffer(N)
            res = rp.rp_AcqGetDataV(acq_channel, 0, N, fbuff)

            data_V = np.zeros(N, dtype = float)
            data_raw = np.zeros(N, dtype = int)

            for i in range(0, N, 1):
                data_V[i] = fbuff[i]
                data_raw[i] = ibuff[i]

            print(f"Data in Volts: {data_V}")
            print(f"Raw data: {data_raw}")

            # Release resources
            rp.rp_Release()



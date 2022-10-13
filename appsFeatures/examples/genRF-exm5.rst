Generate two synchronous signals
################################

.. http://blog.redpitaya.com/examples-new/generate-signal-on-fast-analog-outputs-with-external-triggering/

Description
***********

This example shows how to program Red Pitaya to generate two synchronous analog signals. Voltage and frequency ranges depend on the Red Pitaya model.


Required hardware
*****************

    - Red Pitaya device

.. figure:: output_y49qDi.gif

Code - MATLAB®
**************

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Define Red Pitaya as TCP client object
    clc
    clear all
    close all

    IP = '192.168.178.56';            % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);


    %% Open connection with your Red Pitaya
 
   RP.ByteOrder = "big-endian";
    configureTerminator(RP, "CR/LF");

    writeline(RP,'GEN:RST');
    writeline(RP,'SOUR1:FUNC SINE');            % Set function of output signal
                                                    % {sine, square, triangle, sawu, sawd, pwm}
    writeline(RP,'SOUR1:FREQ:FIX 2000');        % Set frequency of output signal
    writeline(RP,'SOUR1:VOLT 1');               % Set amplitude of output signal

    writeline(RP,'SOUR2:FUNC SINE');            % Set function of output signal
                                                    % {sine, square, triangle, sawu, sawd, pwm}
    writeline(RP,'SOUR2:FREQ:FIX 2000');        % Set frequency of output signal
    writeline(RP,'SOUR2:VOLT 1');               % Set amplitude of output signal

    writeline(RP,'OUTPUT:STATE ON');            % Start both channels simultaneously
    writeline(RP,'SOUR:TRIG:INT');              % Generate triggers

    %% Close connection with Red Pitaya

    clear RP;


Code - C
********

.. note::

    Although the C code examples don't require the use of the SCPI server, we have included them here to demonstrate how the same functionality can be achieved with different programming languages. 
    Instructions on how to compile the code are |compiling and running C|.

.. |compiling and running C| raw:: html

    <a href="https://redpitaya.readthedocs.io/en/latest/developerGuide/software/build/comC.html#compiling-and-running-c-applications" target="_blank">here</a>

.. code-block:: c

    /* Red Pitaya external trigger pulse generation Example */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "rp.h"


    int main(int argc, char **argv){

        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
            fprintf(stderr, "Rp api init failed!\n");
        }

        rp_GenSynchronise();

        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
        rp_GenFreq(RP_CH_1, 2000);
        rp_GenAmp(RP_CH_1, 1);

        rp_GenWaveform(RP_CH_2, RP_WAVEFORM_SINE);
        rp_GenFreq(RP_CH_2, 2000);
        rp_GenAmp(RP_CH_2, 1);

        rp_GenOutEnableSync(true);
        rp_GenTriggerOnly(RP_CH_1);
        rp_GenTriggerOnly(RP_CH_2);

        /* Release rp resources */
        rp_Release();

        return 0;
    }


Code - Python
*************

Using just SCPI commands:

.. code-block:: python

    #!/usr/bin/python3
    
    import sys
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi("192.168.1.17")

    wave_form = 'sine'
    freq = 2000
    ampl = 1

    rp_s.tx_txt('GEN:RST')

    rp_s.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR1:VOLT ' + str(ampl))
    rp_s.tx_txt('SOUR2:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR2:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR2:VOLT ' + str(ampl))

    rp_s.tx_txt('OUTPUT:STATE ON')
    rp_s.tx_txt('SOUR:TRIG:INT')

Using functions (will be implemented soon):

.. code-block:: python

    #!/usr/bin/python3
    
    import sys
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi("192.168.1.17")

    wave_form = 'sine'
    freq = 2000
    ampl = 1

    rp_s.tx_txt('GEN:RST')
    
    # Function for configuring a Source 
    rp_s.sour_set(1, wave_form, ampl, freq)
    rp_s.sour_set(2, wave_form, ampl, freq)

    rp_s.tx_txt('OUTPUT:STATE ON')
    rp_s.tx_txt('SOUR:TRIG:INT')


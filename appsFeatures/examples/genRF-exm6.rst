Generate two burst asynced signals
##################################

Description
***********

This example shows how to program Red Pitaya to generate two asynced analog signals. Voltage and frequency ranges depend on the Red Pitaya model.

.. figure:: exmp6.png
    :align: center

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
    IP = '192.168.1.106';           % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    RP.ByteOrder = "big-endian";
    configureTerminator(RP,"CR/LF");

    %% The example generate sine bursts every 0.5 seconds indefinety
    writeline(RP,'GEN:RST');

    writeline(RP,'SOUR1:FUNC SINE');
    writeline(RP,'SOUR1:FREQ:FIX 4');           % Set frequency of output signal
    writeline(RP,'SOUR1:VOLT 1');               % Set amplitude of output signal

    writeline(RP,'SOUR1:BURS:STAT BURST');      % Set burst mode to BURST - Red Pitaya will
                                                % generate R number of N periods of signal and then stop.
                                                % Time between bursts is P.
                                                
    writeline(RP,'SOUR1:BURS:NCYC 2');          % Set 2 (N) periods of sine wave in one pulse
    writeline(RP,'SOUR1:BURS:NOR 1');           % 1 (R) sine wave pulse
    writeline(RP,'SOUR1:BURS:INT:PER 5000');    % Set time (P) of burst period in microseconds = 5 * 1/Frequency * 1000000

    writeline(RP,'SOUR2:FUNC SINE');
    writeline(RP,'SOUR2:FREQ:FIX 4');           % Set frequency of output signal
    writeline(RP,'SOUR2:VOLT 1');               % Set amplitude of output signal

    writeline(RP,'SOUR2:BURS:STAT BURST');      % Set burst mode to ON
    writeline(RP,'SOUR2:BURS:NCYC 2');          % Set 2 (N) periods of sine wave in a pulse
    writeline(RP,'SOUR2:BURS:NOR 1');           % 1 (R) sine wave pulse
    writeline(RP,'SOUR2:BURS:INT:PER 5000');    % Set time (P) of burst period in microseconds = 5 * 1/Frequency * 1000000

    writeline(RP,'OUTPUT:STATE ON');            % Set both outputs to ON

    pause(2)
    writeline(RP,'SOUR1:TRIG:INT');

    pause(2)
    writeline(RP,'SOUR2:TRIG:INT');

    pause(1)
    writeline(RP,'SOUR:TRIG:INT');

    %% Close connection with Red Pitaya

    clear RP;


Code - C
********

.. note::

    Although the C code examples don't require the use of the SCPI server, we have included them here to demonstrate how the same functionality can be achieved with different programming languages. 
    Instructions on how to compile the code are :ref:`here <comC>`.


.. code-block:: c

    /* Red Pitaya C API example Generating signal pulse on an external trigger 
    * This application generates a specific signal */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "rp.h"

    int main(int argc, char **argv){
        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
                fprintf(stderr, "Rp api init failed!\n");
        }

        rp_GenSynchronise(); // The generator is reset on both channels.

        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
        rp_GenFreq(RP_CH_1, 4);
        rp_GenAmp(RP_CH_1, 1.0);

        rp_GenWaveform(RP_CH_2, RP_WAVEFORM_SINE);
        rp_GenFreq(RP_CH_2, 4);
        rp_GenAmp(RP_CH_2, 1.0);

        rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
        rp_GenBurstCount(RP_CH_1, 2);
        rp_GenBurstRepetitions(RP_CH_1, 1);
        rp_GenBurstPeriod(RP_CH_1, 5000);

        rp_GenMode(RP_CH_2, RP_GEN_MODE_BURST);
        rp_GenBurstCount(RP_CH_2, 2);
        rp_GenBurstRepetitions(RP_CH_2, 1);
        rp_GenBurstPeriod(RP_CH_2, 5000);

        rp_GenOutEnableSync(true);
        sleep(2);
        rp_GenTrigger(RP_CH_1);
        sleep(2);
        rp_GenTrigger(RP_CH_2);
        sleep(1);
        rp_GenSynchronise();

        rp_Release();
    }


Code - Python
*************

Using just SCPI commands:

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import time
    import redpitaya_scpi as scpi

    IP = '192.168.1.97'
    rp_s = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 4
    ampl = 1

    rp_s.tx_txt('GEN:RST')

    rp_s.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR1:VOLT ' + str(ampl))

    rp_s.tx_txt('SOUR2:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR2:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR2:VOLT ' + str(ampl))

    rp_s.tx_txt('SOUR1:BURS:STAT BURST')
    rp_s.tx_txt('SOUR1:BURS:NCYC 2')
    rp_s.tx_txt('SOUR1:BURS:NOR 1')
    rp_s.tx_txt('SOUR1:BURS:INT:PER 5000')

    rp_s.tx_txt('SOUR2:BURS:STAT BURST')
    rp_s.tx_txt('SOUR2:BURS:NCYC 2')
    rp_s.tx_txt('SOUR2:BURS:NOR 1')
    rp_s.tx_txt('SOUR2:BURS:INT:PER 5000')

    rp_s.tx_txt('OUTPUT:STATE ON')
    time.sleep(2)
    rp_s.tx_txt('SOUR1:TRIG:INT')
    time.sleep(2)
    rp_s.tx_txt('SOUR2:TRIG:INT')
    time.sleep(1)
    rp_s.tx_txt('SOUR:TRIG:INT')
    
    rp_s.close()

Using functions:

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import time
    import redpitaya_scpi as scpi

    IP = '192.168.1.97'
    rp_s = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 4
    ampl = 1

    rp_s.tx_txt('GEN:RST')
    
    # Function for configuring a Source 
    rp_s.sour_set(1, wave_form, ampl, freq, burst=True, ncyc=2, nor=1, period= 5000)
    rp_s.sour_set(2, wave_form, ampl, freq, burst=True, ncyc=2, nor=1, period= 5000)

    rp_s.tx_txt('OUTPUT:STATE ON')
    time.sleep(2)
    rp_s.tx_txt('SOUR1:TRIG:INT')
    time.sleep(2)
    rp_s.tx_txt('SOUR2:TRIG:INT')
    time.sleep(1)
    rp_s.tx_txt('SOUR:TRIG:INT')
    
    rp_s.close()

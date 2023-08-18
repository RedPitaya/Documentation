Generate signal pulses
######################

.. http://blog.redpitaya.com/examples-new/generate-signal-pulses/


Description
***********

This example shows how to generate signal pulses of predefined signal waveforms like sine, triangle, square, ramp up, ramp down, or pwm. A generated signal can be observed by an oscilloscope.

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
    IP = '192.168.178.111';         % Input IP of your Red Pitaya...
    port = 5000;                    % If you are using WiFi then IP is:
    RP = tcpclient(IP, port);       % 192.168.128.1

    RP.ByteOrder = "big-endian";
    configureTerminator(RP, "CR/LF");

    %% The example generate sine bursts every 0.5 seconds indefinety
    % writeline(RP,'GEN:RST');

    writeline(RP,'SOUR1:FUNC SINE');
    writeline(RP,'SOUR1:FREQ:FIX 1000');        % Set frequency of output signal
    writeline(RP,'SOUR1:VOLT 1');               % Set amplitude of output signal

    writeline(RP,'SOUR1:BURS:STAT BURST');      % Set burst mode to ON (Red Pitaya will 
                                                % generate R number of N periods of signal and then stop.
                                                % Time between bursts is P.)
                                                
    writeline(RP,'SOUR1:BURS:NCYC 1');          % Set 1 (N) pulses of sine wave
    writeline(RP,'SOUR1:BURS:NOR 10000');       % (R) number of sine wave pulses (set to 65536 for INF pulses)
    writeline(RP,'SOUR1:BURS:INT:PER 5000');    % Set time (P) of burst period in microseconds = 5 * 1/Frequency * 1000000
    
    writeline(RP,'OUTPUT1:STATE ON');           % Set output to ON
    writeline(RP,'SOUR1:TRIG:INT');             % Set generator trigger to immediately


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

        /* Burst count */


        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
            fprintf(stderr, "Rp api init failed!\n");
        }

        rp_GenReset();

        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
        rp_GenFreq(RP_CH_1, 1000);
        rp_GenAmp(RP_CH_1, 1.0);

        rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
        rp_GenBurstCount(RP_CH_1, 1);
        rp_GenBurstRepetitions(RP_CH_1, 10000);     // set to 65536 for INF pulses
        rp_GenBurstPeriod(RP_CH_1, 5000);

        rp_GenOutEnable(RP_CH_1);
        rp_GenTriggerOnly(RP_CH_1);

        rp_Release();
    }


Code - Python
*************

Using just SCPI commands:

.. code-block:: python

    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi(sys.argv[1])

    wave_form = 'sine'
    freq = 1000
    ampl = 1

    rp_s.tx_txt('GEN:RST')

    rp_s.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR1:VOLT ' + str(ampl))
    rp_s.tx_txt('SOUR1:BURS:STAT BURST')                # activate Burst mode
    rp_s.tx_txt('SOUR1:BURS:NCYC 1')                    # Signal periods in a Burst pulse
    rp_s.tx_txt('SOUR1:BURS:NOR 10000');                # Total number of bursts (set to 65536 for INF pulses)
    rp_s.tx_txt('SOUR1:BURS:INT:PER 5000');             # Burst period (time between two bursts (signal + delay in microseconds))

    rp_s.tx_txt('OUTPUT1:STATE ON')
    rp_s.tx_txt('SOUR1:TRIG:INT')

Using functions:

.. code-block:: python

    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi(sys.argv[1])

    wave_form = 'sine'
    freq = 10000
    ampl = 1

    rp_s.tx_txt('GEN:RST')
    
    # Function for configuring a Source
    rp_s.sour_set(1, wave_form, ampl, freq, burst=True, nor=10000, ncyc=2, period=5000)
    # nor=65536 for INF pulses
    
    rp_s.tx_txt('OUTPUT1:STATE ON')
    rp_s.tx_txt('SOUR1:TRIG:INT')

.. note::

    The Python functions are accessible with the latest version of the redpitaya_scpi.py document available on our |redpitaya_scpi|.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order. The code should function at approximately the same speed without them.

    For further information on functions please consult the redpitaya_scpi.py code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">GitHub</a>


Code - LabVIEW
**************

.. figure:: Generate-signal-pulses_LV.png

`Downloads <https://downloads.redpitaya.com/downloads/Clients/labview/Generate%20signal%20pulses.vi>`_

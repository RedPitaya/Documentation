Generate signal pulses
######################

Description
=============

This example shows how to generate signal pulses of predefined signal waveforms like sine, triangle, square, ramp up, ramp down, or PWM. A generated signal can be observed by an oscilloscope.

Required hardware
=====================

    - Red Pitaya device

.. figure:: ../general_img/RedPitaya_general.png


Required software
===================

.. include:: ../sw_requirement.inc


SCPI Code Examples
====================

Code - MATLAB®
--------------

.. include:: ../sw_requirement.inc

.. code-block:: matlab


    %% Define Red Pitaya as TCP/IP object
    clc
    close all
    IP = 'rp-f0a235.local';             % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    RP.ByteOrder = 'big-endian';
    configureTerminator(RP, 'CR/LF');

    %% Setup a burst signal
    waveform = 'sine';                  % {sine, square, triangle, sawu, sawd, pwm}
    freq = 1000;
    ampl = 1;

    ncyc = 3;
    nor = 4;
    period = 5000;

    writeline(RP,'GEN:RST');

    writeline(RP, append('SOUR1:FUNC ', waveform));
    writeline(RP, append('SOUR1:FREQ:FIX ', num2str(freq)));
    writeline(RP, append('SOUR1:VOLT ', num2str(ampl)));

    writeline(RP,'SOUR1:BURS:STAT BURST');                          % Set burst mode to ON (Red Pitaya will 
                                                                    % generate R number of N periods of signal and then stop.
                                                                    % Time between bursts is P.)
    writeline(RP, append('SOUR1:BURS:NCYC ', num2str(ncyc)));       % N (waveform) periods in one burst
    writeline(RP, append('SOUR1:BURS:NOR ', num2str(nor)));         % Number bursts R (set to 65536 for INF pulses)
    writeline(RP, append('SOUR1:BURS:INT:PER ', num2str(period)));  % Time (P) between start of one and start of second burst in µs

    writeline(RP,'SOUR1:TRig:SOUR INT');
    writeline(RP,'OUTPUT1:STATE ON');                               % Set output to ON
    writeline(RP,'SOUR1:TRig:INT');                                 % Generate trigger

    %% Close connection with Red Pitaya
    clear RP;
    

Code - Python
---------------

**Using SCPI commands:**

.. code-block:: python

    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi

    IP = 'rp-f066c8.local'
    rp_s = scpi.scpi(IP)

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
    rp_s.tx_txt('SOUR1:TRig:INT')

    rp_s.close()

**Using functions:**

.. code-block:: python

    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi

    IP = 'rp-f066c8.local'
    rp_s = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 10000
    ampl = 1

    rp_s.tx_txt('GEN:RST')
    
    # Function for configuring a Source
    rp_s.sour_set(1, wave_form, ampl, freq, burst=True, nor=10000, ncyc=2, period=5000)
    # nor=65536 for INF pulses
    
    rp_s.tx_txt('OUTPUT1:STATE ON')
    rp_s.tx_txt('SOUR1:TRig:INT')

    rp_s.close()

.. include:: ../python_scpi_note.inc
    
Code - LabVIEW
-----------------

.. figure:: img/Generate-signal-pulses_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Generate%20signal%20pulses.vi>`_


API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C API
------------

.. code-block:: c

    /* Red Pitaya C API example pf Generating signal pulse on an external trigger */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "rp.h"

    int main(int argc, char **argv){

        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
            fprintf(stderr, "Rp api init failed!\n");
        }

        /* Reset Generation */
        rp_GenReset();

        /* Generation */
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
        rp_GenFreq(RP_CH_1, 1000);
        rp_GenAmp(RP_CH_1, 1.0);

        rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
        rp_GenBurstCount(RP_CH_1, 1);
        rp_GenBurstRepetitions(RP_CH_1, 10000);     // set to 65536 for INF pulses
        rp_GenBurstPeriod(RP_CH_1, 5000);

        rp_GenOutEnable(RP_CH_1);
        rp_GenTriggerOnly(RP_CH_1);

        /* Releasing resources */
        rp_Release();
        return 0;
    }


Code - Python API
------------------

.. code-block:: python

    #!/usr/bin/python3

    import time
    import rp

    #? Possible waveforms:
    #?   RP_WAVEFORM_SINE, RP_WAVEFORM_SQUARE, RP_WAVEFORM_TRIANGLE, RP_WAVEFORM_RAMP_UP,
    #?   RP_WAVEFORM_RAMP_DOWN, RP_WAVEFORM_DC, RP_WAVEFORM_PWM, RP_WAVEFORM_ARBITRARY,
    #?   RP_WAVEFORM_DC_NEG, RP_WAVEFORM_SWEEP

    channel = rp.RP_CH_1        # rp.RP_CH_2
    waveform = rp.RP_WAVEFORM_SINE
    freq = 1000
    ampl = 1

    ncyc = 1            # Number of waveform periods in one burst
    nor = 1000          # Number of repeated bursts 
    period = 5000       # Delay between start of first burst and start of second burst
                    # in mircoseconds
                    
    #? Possible modes:
    #?   RP_GEN_MODE_CONTINUOUS, RP_GEN_MODE_BURST
    mode = rp.RP_GEN_MODE_BURST

    # Initialize the interface
    rp.rp_Init()

    # Reset generator
    rp.rp_GenReset()


    ###### Generation #####
    rp.rp_GenWaveform(channel, waveform)
    rp.rp_GenFreqDirect(channel, freq)
    rp.rp_GenAmp(channel, ampl)

    # Change to burst mode
    rp.rp_GenMode(channel, mode)
    rp.rp_GenBurstCount(channel, ncyc)                  # Ncyc
    rp.rp_GenBurstRepetitions(channel, nor)             # Nor
    rp.rp_GenBurstPeriod(channel, period)               # Period


    # Enable output and trigger the generator
    rp.rp_GenOutEnable(channel)
    rp.rp_GenTriggerOnly(channel)
    
    # Release resources
    rp.rp_Release()


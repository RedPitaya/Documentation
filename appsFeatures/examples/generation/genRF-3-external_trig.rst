Generate a signal on external trigger
#####################################

Description
=============

This example shows how to program Red Pitaya to generate an analog signal on an external trigger. Red Pitaya will first wait for a trigger from an external source and start generating the desired signal right after the trigger condition is met. The same concept also works for continuous signal generation on external trigger Voltage and frequency ranges depending on the Red Pitaya model.


Required hardware
====================

    - Red Pitaya device

.. figure:: ../general_img/RedPitaya_general.png


Required software
==================

.. include:: ../sw_requirement.inc


SCPI Code Examples
====================

Code - MATLAB®
-----------------

.. include:: ../matlab.inc
    
.. code-block:: matlab

    %% Define Red Pitaya as TCP/IP object
    clc
    close all
    IP = 'rp-f0a235.local';            % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya
    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');

    flush(RP);                      % clear input & output buffers
    % flush(RP, 'input')
    % flush(RP, 'output')

    %% Variables
    waveform = 'sine';                  % {sine, square, triangle, sawu, sawd, pwm}
    freq = 1000;
    ampl = 1;

    ncyc = 3;
    nor = 4;
    period = 5000;

    debounce_dly = 500;                 % External trigger debounce delay

    % Reset Generation
    writeline(RP, 'GEN:RST')

    %% Generate a signal
    writeline(RP, append('SOUR1:FUNC ', waveform));
    writeline(RP, append('SOUR1:FREQ:FIX ', num2str(freq)));
    writeline(RP, append('SOUR1:VOLT ', num2str(ampl)));

    writeline(RP,'SOUR1:BURS:STAT BURST');                          % Set burst mode to ON (Red Pitaya will 
                                                                    % generate R number of N periods of signal and then stop.
                                                                    % Time between bursts is P.)
    writeline(RP, append('SOUR1:BURS:NCYC ', num2str(ncyc)));       % N (waveform) periods in one burst
    writeline(RP, append('SOUR1:BURS:NOR ', num2str(nor)));         % Number bursts R (set to 65536 for INF pulses)
    writeline(RP, append('SOUR1:BURS:INT:PER ', num2str(period)));  % Time (P) between start of one and start of second burst in µs

    % For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    writeline(RP,append('SOUR:TRig:EXT:DEBouncerUs ', num2str(debounce_dly)));
    writeline(RP,'SOUR1:TRig:SOUR EXT_PE');                         % Set generator trigger to external

    writeline(RP,'OUTPUT1:STATE ON');                               % Set output to ON

    % For generating signal pulses, your trigger signal frequency must be less than
    % frequency of generating signal pulses. If your trigger signal frequency
    % is higher than the frequency of generating signal pulses
    % you will get a continuous signal on output, instead of pulses.

    clear RP;


Code - Python
-----------------

**Using SCPI commands:**

.. code-block:: python
    
    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi
    
    IP = '192.168.178.56'
    rp = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 200
    ampl = 1

    rp.tx_txt('GEN:RST')

    rp.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp.tx_txt('SOUR1:VOLT ' + str(ampl))
    
    rp.tx_txt('SOUR1:BURS:STAT BURST')        # Set burst mode to CONTINUOUS/skip this section for sine wave generation on External trigger
    rp.tx_txt('SOUR1:BURS:NCYC 1')

    # For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    rp.tx_txt('SOUR:TRig:EXT:DEBouncerUs 500')
    rp.tx_txt('SOUR1:TRig:SOUR EXT_PE')

    rp.tx_txt('OUTPUT1:STATE ON')
    
    rp.close()

**Using functions:**

.. code-block:: python
    
    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi

    IP = '192.168.178.56'
    rp = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 200
    ampl = 1

    rp.tx_txt('GEN:RST')

    # Function for configuring a Source
    rp.sour_set(1, wave_form, ampl, freq, burst=True, ncyc=1, trig="EXT_PE")

    # For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    rp.tx_txt('SOUR:TRig:EXT:DEBouncerUs 500')
    
    rp.tx_txt('OUTPUT1:STATE ON')
    
    rp.close()


.. include:: ../python_scpi_note.inc

Code - LabVIEW
---------------

.. figure:: img/Generate-signal-on-external-trigger_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Generate%20signal%20on%20external%20trigger.vi>`_



API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C API
---------------

.. code-block:: c

    /* Red Pitaya C API example of Generation a signal on a external trigger */

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
        rp_GenFreq(RP_CH_1, 200);
        rp_GenAmp(RP_CH_1, 1);

        rp_GenBurstCount(RP_CH_1, 1);
        rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
        rp_GenSetExtTriggerDebouncerUs(500);
        rp_GenTriggerSource(RP_CH_1, RP_GEN_TRIG_SRC_EXT_PE);

        rp_GenOutEnable(RP_CH_1);

        /* Release rp resources */
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
    freq = 200
    ampl = 1
    
    ncyc = 2            # Number of waveform periods in one burst
    nor = 2             # Number of repeated bursts 
    period = 30000      # Delay between start of first burst and start of second burst
                        # in mircoseconds
    
    debounce_len = 50000  # microseconds
    
    #? Possible modes:
    #?   RP_GEN_MODE_CONTINUOUS, RP_GEN_MODE_BURST
    mode = rp.RP_GEN_MODE_BURST
    
    #? Possible trigger sources:
    #?   RP_GEN_TRIG_SRC_INTERNAL, RP_GEN_TRIG_SRC_EXT_PE, RP_GEN_TRIG_SRC_EXT_NE
    gen_trig_sour = rp.RP_GEN_TRIG_SRC_EXT_PE
    
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
    
    # Set length of internal debounce filter in us (minimum of 1 us)
    rp.rp_GenSetExtTriggerDebouncerUs(debounce_len)
    
    # Specify generator trigger source
    rp.rp_GenTriggerSource(channel, gen_trig_sour)
    
    # Enable output
    rp.rp_GenOutEnable(channel)
    
    # Release resources
    rp.rp_Release()


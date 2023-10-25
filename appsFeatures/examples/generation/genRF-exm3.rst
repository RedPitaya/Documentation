Generate a signal on external trigger
#####################################

.. http://blog.redpitaya.com/examples-new/generate-signal-on-fast-analog-outputs-with-external-triggering/

Description
=============

This example shows how to program Red Pitaya to generate an analog signal on an external trigger. Red Pitaya will first wait for a trigger from an external source and start generating the desired signal right after the trigger condition is met. The same concept also works for continuous signal generation on external trigger Voltage and frequency ranges depending on the Red Pitaya model.


Required hardware
====================

    - Red Pitaya device

.. figure:: ../general_img/RedPitaya_general.png


SCPI Code Examples
====================

Code - MATLAB®
-----------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Define Red Pitaya as a TCP client object
    clc
    clear all
    close all

    IP = '192.168.178.56';          % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya
    RP.ByteOrder = "big-endian";
    configureTerminator(RP,"CR/LF");

    flush(RP);                      % clear input & output buffers
    % flush(RP, 'input')
    % flush(RP, 'output')


    % Reset Generation
    writeline(RP, 'GEN:RST')

    %% GENERATION
    writeline(RP,'SOUR1:FUNC SINE');            % Set function of output signal {sine, square, triangle, sawu, sawd, pwm}
    writeline(RP,'SOUR1:FREQ:FIX 200');         % Set frequency of output signal
    writeline(RP,'SOUR1:VOLT 1');               % Set amplitude of output signal

    writeline(RP,'SOUR1:BURS:STAT BURST');      % Set burst mode to CONTINUOUS for sine wave generation on External trigger
    writeline(RP,'SOUR1:BURS:NCYC 1');          % Set 1 pulses of sine wave

    % For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    writeline(RP,'SOUR:TRIG:EXT:DEBouncerUs 500');
    writeline(RP,'SOUR1:TRIG:SOUR EXT_PE');     % Set generator trigger to external

    writeline(RP,'OUTPUT1:STATE ON');           % Set output to ON

    % For generating signal pulses, your trigger signal frequency must be less than
    % frequency of generating signal pulses. If your trigger signal frequency
    % is higher than the frequency of generating signal pulses
    % you will get a continuous signal on output, instead of pulses.

    clear RP;


Code - Python
-----------------

**Using just SCPI commands:**

.. code-block:: python
    
    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi
    
    IP = '192.168.178.56'
    rp_s = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 200
    ampl = 1

    rp_s.tx_txt('GEN:RST')

    rp_s.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR1:VOLT ' + str(ampl))
    
    rp_s.tx_txt('SOUR1:BURS:STAT BURST')        # Set burst mode to CONTINUOUS/skip this section for sine wave generation on External trigger
    rp_s.tx_txt('SOUR1:BURS:NCYC 1')

    # For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    rp_s.tx_txt('SOUR:TRIG:EXT:DEBouncerUs 500')
    rp_s.tx_txt('SOUR1:TRIG:SOUR EXT_PE')

    rp_s.tx_txt('OUTPUT1:STATE ON')
    
    rp_s.close()

**Using functions:**

.. code-block:: python
    
    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi

    IP = '192.168.178.56'
    rp_s = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 200
    ampl = 1

    rp_s.tx_txt('GEN:RST')

    # Function for configuring a Source
    rp_s.sour_set(1, wave_form, ampl, freq, burst=True, ncyc=1, trig="EXT_PE")

    # For short triggering signals set the length of internal debounce filter in us (minimum of 1 us)
    rp_s.tx_txt('SOUR:TRIG:EXT:DEBouncerUs 500')
    
    rp_s.tx_txt('OUTPUT1:STATE ON')
    
    rp_s.close()


.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>


Code - LabVIEW
---------------

.. figure:: img/Generate-signal-on-external-trigger_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Generate%20signal%20on%20external%20trigger.vi>`_



API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead, the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information are :ref:`here <comC>`.


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
    #?   RP_GEN_MODE_CONTINUOUS, RP_GEN_MODE_BURST, RP_GEN_MODE_STREAM
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


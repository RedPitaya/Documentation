Generate signal pulses
######################

.. http://blog.redpitaya.com/examples-new/generate-signal-pulses/


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

    % Reset Generation
    writeline(RP,'GEN:RST');

    %% GENERATION
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
    writeline(RP,'SOUR1:TRig:INT');             % Set generator trigger to immediately

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

.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>


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


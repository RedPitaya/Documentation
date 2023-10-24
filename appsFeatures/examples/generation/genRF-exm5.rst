Generate two synchronous signals
################################

.. http://blog.redpitaya.com/examples-new/generate-signal-on-fast-analog-outputs-with-external-triggering/

Description
============

This example shows how to program Red Pitaya to generate two synchronous analog signals. Voltage and frequency ranges depend on the Red Pitaya model.


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

    IP = '192.168.178.56';            % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);


    %% Open connection with your Red Pitaya
 
    RP.ByteOrder = "big-endian";
    configureTerminator(RP, "CR/LF");

    % Reset Generation
    writeline(RP,'GEN:RST');

    %% GENERATION
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


Code - Python
---------------

**Using just SCPI commands:**

.. code-block:: python

    #!/usr/bin/env python3
    
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
    
    rp_s.close()

**Using functions:**

.. code-block:: python

    #!/usr/bin/env python3
    
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
    
    rp_s.close()


.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>



API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information is :ref:`here <comC>`.

Code - C API
---------------

.. code-block:: c

    /* Red Pitaya C API example of Generating Synced signals */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "rp.h"

    int main(int argc, char **argv){

        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
            fprintf(stderr, "Rp api init failed!\n");
        }

        /* Reset Generation and */
        rp_GenReset();

        /* Generation */
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


Code - Python API
------------------

.. code-block:: python

    #!/usr/bin/python3

    import time
    import numpy as np
    import rp

    #? Possible waveforms:
    #?   RP_WAVEFORM_SINE, RP_WAVEFORM_SQUARE, RP_WAVEFORM_TRIANGLE, RP_WAVEFORM_RAMP_UP,
    #?   RP_WAVEFORM_RAMP_DOWN, RP_WAVEFORM_DC, RP_WAVEFORM_PWM, RP_WAVEFORM_ARBITRARY,
    #?   RP_WAVEFORM_DC_NEG, RP_WAVEFORM_SWEEP

    channel = rp.RP_CH_1        # rp.RP_CH_2
    channel2 = rp.RP_CH_2
    waveform = rp.RP_WAVEFORM_SINE
    freq = 10000
    ampl = 1

    #? Possible trigger sources:
    #?   RP_GEN_TRIG_SRC_INTERNAL, RP_GEN_TRIG_SRC_EXT_PE, RP_GEN_TRIG_SRC_EXT_NE
    gen_trig_sour = rp.RP_GEN_TRIG_SRC_INTERNAL
    
    # Initialize the interface
    rp.rp_Init()

    # Reset generator
    rp.rp_GenReset()

    ###### Generation #####
    # OUT1
    rp.rp_GenWaveform(channel, waveform)
    rp.rp_GenFreqDirect(channel, freq)
    rp.rp_GenAmp(channel, ampl)

    # OUT2
    rp.rp_GenWaveform(channel2, waveform)
    rp.rp_GenFreqDirect(channel2, freq)
    rp.rp_GenAmp(channel2, ampl)

    # Specify generator trigger source
    rp.rp_GenTriggerSource(channel, gen_trig_sour)

    # Enable output synchronisation
    rp.rp_GenOutEnableSync(True)
    rp.rp_GenOutEnable(channel)

    # Syncronise output channels
    rp.rp_GenSynchronise()
    rp.rp_GenTriggerOnly(channel)

    # Release resources
    rp.rp_Release()


Generate two synchronous signals
################################

Description
============

This example shows how to program Red Pitaya to generate two synchronous analog signals. Voltage and frequency ranges depend on the Red Pitaya model.


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
    configureTerminator(RP, 'CR/LF');

    waveform = 'sine';                  % {sine, square, triangle, sawu, sawd, pwm}
    freq = 1000;
    ampl = 1;
    waveform2 = 'triangle';                  % {sine, square, triangle, sawu, sawd, pwm}
    freq2 = 2000;
    ampl2 = 0.5;

    writeline(RP,'GEN:RST');
    writeline(RP, append('SOUR1:FUNC ', waveform));
    writeline(RP, append('SOUR1:FREQ:FIX ', num2str(freq)));
    writeline(RP, append('SOUR1:VOLT ', num2str(ampl)));

    writeline(RP, append('SOUR2:FUNC ', waveform2));
    writeline(RP, append('SOUR2:FREQ:FIX ', num2str(freq2)));
    writeline(RP, append('SOUR2:VOLT ', num2str(ampl2)));

    writeline(RP,'OUTPUT:STATE ON');       % Start two channels simultaneously
    writeline(RP,'SOUR:TRig:INT');

    %% Close connection with Red Pitaya
    clear RP;


Code - Python
---------------

**Using SCPI commands:**

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
    rp_s.tx_txt('SOUR:TRig:INT')
    
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
    rp_s.tx_txt('SOUR:TRig:INT')
    
    rp_s.close()


.. include:: ../python_scpi_note.inc


API Code Examples
====================

.. include:: ../c_code_note.inc


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
        rp.rp_GenSynchronise()

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

    # Syncronise output channels
    rp.rp_GenSynchronise()

    # Release resources
    rp.rp_Release()


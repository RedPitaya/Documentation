Generate two burst asynced signals
##################################

Description
==============

This example shows how to program Red Pitaya to generate two asynced analog signals. Voltage and frequency ranges depend on the Red Pitaya model.

.. figure:: img/generate_two_burst_asynced_signals.png
    :align: center


Required hardware
==================

    - Red Pitaya device

.. figure:: ../general_img/RedPitaya_general.png


Required software
==================

.. include:: ../sw_requirement.inc


SCPI Code Examples
====================

Code - MATLAB®
------------------

.. include:: ../matlab.inc

.. code-block:: matlab

    %% Define Red Pitaya as TCP/IP object
    clc
    close all
    IP = 'rp-f0a235.local';        % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');

    waveform = ['sine' 'sine'];
    freq = [4 4];
    ampl = [1 1];
    ncyc = [2 2];
    nor  = [1 1];
    period = [5000 5000];

    writeline(RP,'GEN:RST');

    writeline(RP, append('SOUR1:FUNC ', waveform(1)));
    writeline(RP, append('SOUR1:FREQ:FIX ', num2str(freq(1))));
    writeline(RP, append('SOUR1:VOLT ', num2str(ampl(1))));

    writeline(RP,'SOUR1:BURS:STAT BURST');                              % Set burst mode to ON
    writeline(RP, append('SOUR1:BURS:NCYC ', num2str(ncyc(1))));        % N (waveform) periods in one burst
    writeline(RP, append('SOUR1:BURS:NOR ', num2str(nor(1))));          % Number bursts R (set to 65536 for INF pulses)
    writeline(RP, append('SOUR1:BURS:INT:PER ', num2str(period(1))));   % Time (P) between start of one and start of second burst in µs

    writeline(RP, append('SOUR2:FUNC ', waveform(2)));
    writeline(RP, append('SOUR2:FREQ:FIX ', num2str(freq(2))));
    writeline(RP, append('SOUR2:VOLT ', num2str(ampl(2))));

    writeline(RP,'SOUR2:BURS:STAT BURST');                              % Set burst mode to ON
    writeline(RP, append('SOUR2:BURS:NCYC ', num2str(ncyc(2))));        % N (waveform) periods in one burst
    writeline(RP, append('SOUR2:BURS:NOR ', num2str(nor(2))));          % Number bursts R (set to 65536 for INF pulses)
    writeline(RP, append('SOUR2:BURS:INT:PER ', num2str(period(2))));   % Time (P) between start of one and start of second burst in µs

    writeline(RP,'OUTPUT:STATE ON');                                    % Enable both outputs
    pause(2)
    writeline(RP,'SOUR1:TRig:INT');
    pause(2)
    writeline(RP,'SOUR2:TRig:INT');
    pause(1)
    writeline(RP,'SOUR:TRig:INT');

    %% Close connection with Red Pitaya
    clear RP;


Code - Python
---------------

**Using SCPI commands:**

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import time
    import redpitaya_scpi as scpi

    IP = '192.168.1.97'
    rp = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 4
    ampl = 1

    rp.tx_txt('GEN:RST')

    rp.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp.tx_txt('SOUR1:VOLT ' + str(ampl))

    rp.tx_txt('SOUR2:FUNC ' + str(wave_form).upper())
    rp.tx_txt('SOUR2:FREQ:FIX ' + str(freq))
    rp.tx_txt('SOUR2:VOLT ' + str(ampl))

    rp.tx_txt('SOUR1:BURS:STAT BURST')
    rp.tx_txt('SOUR1:BURS:NCYC 2')
    rp.tx_txt('SOUR1:BURS:NOR 1')
    rp.tx_txt('SOUR1:BURS:INT:PER 5000')

    rp.tx_txt('SOUR2:BURS:STAT BURST')
    rp.tx_txt('SOUR2:BURS:NCYC 2')
    rp.tx_txt('SOUR2:BURS:NOR 1')
    rp.tx_txt('SOUR2:BURS:INT:PER 5000')

    rp.tx_txt('OUTPUT:STATE ON')
    time.sleep(2)
    rp.tx_txt('SOUR1:TRig:INT')
    time.sleep(2)
    rp.tx_txt('SOUR2:TRig:INT')
    time.sleep(1)
    rp.tx_txt('SOUR:TRig:INT')
    
    rp.close()

**Using functions:**

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import time
    import redpitaya_scpi as scpi

    IP = '192.168.1.97'
    rp = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 4
    ampl = 1

    rp.tx_txt('GEN:RST')
    
    # Function for configuring a Source 
    rp.sour_set(1, wave_form, ampl, freq, burst=True, ncyc=2, nor=1, period= 5000)
    rp.sour_set(2, wave_form, ampl, freq, burst=True, ncyc=2, nor=1, period= 5000)

    rp.tx_txt('OUTPUT:STATE ON')
    time.sleep(2)
    rp.tx_txt('SOUR1:TRig:INT')
    time.sleep(2)
    rp.tx_txt('SOUR2:TRig:INT')
    time.sleep(1)
    rp.tx_txt('SOUR:TRig:INT')
    
    rp.close()


.. include:: ../python_scpi_note.inc


API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C API
---------------

.. code-block:: c

    /* Red Pitaya C API example of Generating two asynced burst signals */

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
    freq = 10
    ampl = 1

    ncyc = 2
    nor = 1
    period = 5000

    # Initialize the interface
    rp.rp_Init()

    # Reset generator
    rp.rp_GenReset()

    ###### Generation #####
    # OUT1
    rp.rp_GenWaveform(channel, waveform)
    rp.rp_GenFreqDirect(channel, freq)
    rp.rp_GenAmp(channel, ampl)

    # Change to burst mode
    rp.rp_GenMode(channel, rp.RP_GEN_MODE_BURST)
    rp.rp_GenBurstCount(channel, ncyc)                  # Ncyc
    rp.rp_GenBurstRepetitions(channel, nor)             # Nor
    rp.rp_GenBurstPeriod(channel, period)               # Period

    # OUT2
    rp.rp_GenWaveform(channel2, waveform)
    rp.rp_GenFreqDirect(channel2, freq)
    rp.rp_GenAmp(channel2, ampl)

    # Change to burst mode
    rp.rp_GenMode(channel2, rp.RP_GEN_MODE_BURST)
    rp.rp_GenBurstCount(channel2, ncyc)                  # Ncyc
    rp.rp_GenBurstRepetitions(channel2, nor)             # Nor
    rp.rp_GenBurstPeriod(channel2, period)               # Period


    #? Possible trigger sources:
    #?   RP_GEN_TRIG_SRC_INTERNAL, RP_GEN_TRIG_SRC_EXT_PE, RP_GEN_TRIG_SRC_EXT_NE

    # Specify generator trigger source
    rp.rp_GenTriggerSource(channel, rp.RP_GEN_TRIG_SRC_INTERNAL)

    # Enable output synchronisation
    rp.rp_GenOutEnableSync(True)
    time.sleep(0.1)

    # Syncronise output channels
    rp.rp_GenTriggerOnly(channel)
    time.sleep(0.5)
    rp.rp_GenTriggerOnly(channel2)
    time.sleep(0.5)
    rp.rp_GenSynchronise()

    # Release resources
    rp.rp_Release()


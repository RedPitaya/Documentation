Generate continuous signal
##########################

.. http://blog.redpitaya.com/examples-new/generate-continuous-signal-on-fast-analog-outputs/

Description
=============

This example shows how to program Red Pitaya to generate an analog 2 kHz sine wave signal with a 1 V amplitude. Voltage and frequency ranges depend on the Red Pitaya model.


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
---------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Define Red Pitaya as TCP client object

    IP = '192.168.178.111';           % Input IP of your Red Pitaya...
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
    writeline(RP,'OUTPUT1:STATE ON');           % Set output to ON

    writeline(RP,'SOUR1:TRig:INT');             % Generate trigger

    %% Close connection with Red Pitaya
    clear RP;
    
    
Code - Python
----------------

**Using SCPI commands:**

.. code-block:: python

    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi
    
    IP = "192.168.178.111"
    rp_s = scpi.scpi(IP)

    wave_form = 'sine'
    freq = 2000
    ampl = 1

    rp_s.tx_txt('GEN:RST')

    rp_s.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR1:VOLT ' + str(ampl))

    # Enable output
    rp_s.tx_txt('OUTPUT1:STATE ON')
    rp_s.tx_txt('SOUR1:TRig:INT')

    rp_s.close()

**Using functions:**

.. code-block:: python

    #!/usr/bin/env python3
    
    import sys
    import redpitaya_scpi as scpi
    
    wave_form = 'sine'
    freq = 2000
    ampl = 1

    IP = "192.168.178.111"
    rp_s = scpi.scpi(IP)
    
    rp_s.tx_txt('GEN:RST')
    
    # Function for configuring a Source 
    rp_s.sour_set(1, wave_form, ampl, freq)
    
    # Enable output
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
---------------

.. figure:: img/Generate-continuous-signal_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Generate%20continuous%20signal.vi>`_



API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C API
---------------

.. code-block:: c

    /* Red Pitaya C API example of Continuous generation on a specific channel */ 

    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "rp.h"

    int main(int argc, char **argv){

        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
            fprintf(stderr, "Rp api init failed!\n");
        }

        /* Reset generator */
        rp_GenReset();

        /* Generation */
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);    // Waveform
        rp_GenFreq(RP_CH_1, 2000.0);                  // Frequency
        rp_GenAmp(RP_CH_1, 1.0);                      // Amplitude

        // Emable channel output
        rp_GenOutEnable(RP_CH_1);

        // Trigger generation
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
    freq = 2000
    ampl = 1

    # Initialize the interface
    rp.rp_Init()

    # Reset generator
    rp.rp_GenReset()

    ###### Generation #####
    rp.rp_GenWaveform(channel, waveform)
    rp.rp_GenFreqDirect(channel, freq)
    rp.rp_GenAmp(channel, ampl)

    # Enable output and trigger the generator
    rp.rp_GenOutEnable(channel)
    rp.rp_GenTriggerOnly(channel)

    # Release resources
    rp.rp_Release()


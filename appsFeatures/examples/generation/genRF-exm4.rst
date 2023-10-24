Custom waveform signal generation
#################################

.. http://blog.redpitaya.com/examples-new/custom-signal-generating

Description
=============

This example shows how to program Red Pitaya to generate a custom waveform signal. Voltage and frequency ranges depend on the Red Pitaya model.

.. note::

    You can send fewer samples than a full buffer (16384 samples) to the Red Pitaya, but the frequency will be adjusted accordingly. This means that if you send 8192 samples instead and specify the frequency as 10 kHz, Red Pitaya will generate a 20 kHz signal.

Required hardware
==================

    - Red Pitaya device

.. figure:: ../general_img/RedPitaya_general.png



SCPI Code Examples
====================

Code - MATLAB®
----------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Define Red Pitaya as a TCP client object
    clc
    clear all
    close all
    IP = '192.168.178.102';           % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    flush(RP);                              % Flush input and output
    % flush(RP, 'input')
    % flush(RP, 'output')
    
    %% Open connection with your Red Pitaya and the close previous one
    x = instrfind;
    clear RP;


    RP = tcpclient(IP, port);
    RP.ByteOrder = "big-endian";
    configureTerminator(RP,"CR/LF");
    
    %% Calculate arbitrary waveform with 16384 samples
    % Values of arbitrary waveform must be in the range from -1 to 1.
    N = 16383;
    t = 0:(2*pi)/N:2*pi;
    x = sin(t) + 1/3*sin(3*t);
    y = 1/2*sin(t) + 1/4*sin(4*t);
    plot(t,x,t,y)
    grid on;

    %% Convert waveforms to string with 5 decimal places accuracy
    waveform_ch_1_0 = num2str(x,'%1.5f,');
    waveform_ch_2_0 = num2str(y,'%1.5f,');

    % the last two elements are empty spaces “,”.
    waveform_ch_1 =waveform_ch_1_0(1,1:length(waveform_ch_1_0)-3);
    waveform_ch_2 =waveform_ch_2_0(1,1:length(waveform_ch_2_0)-3);

     % Reset Generation
    writeline(RP,'GEN:RST')                     % Reset to default settings

    %% GENERATION
    writeline(RP,'SOUR1:FUNC ARBITRARY');       % Set function of output signal
    writeline(RP,'SOUR2:FUNC ARBITRARY');       % {sine, square, triangle, sawu, sawd}

    writeline(RP,['SOUR1:TRAC:DATA:DATA ' waveform_ch_1])  % Send waveforms to Red Pitya
    writeline(RP,['SOUR2:TRAC:DATA:DATA ' waveform_ch_2])

    writeline(RP,'SOUR1:VOLT 0.7');             % Set amplitude of output signal
    writeline(RP,'SOUR2:VOLT 1');

    writeline(RP,'SOUR1:FREQ:FIX 4000');        % Set frequency of output signal
    writeline(RP,'SOUR2:FREQ:FIX 4000');


    writeline(RP,'OUTPUT:STATE ON');            % Start both channels simultaneously
    writeline(RP,'SOUR:TRIG:INT');              % Generate triggers

    clear RP;



Code - Python
-----------------

**Using just SCPI commands:**

.. code-block:: python

    #!/usr/bin/env python3
    
    import numpy as np
    import math
    from matplotlib import pyplot as plt
    import redpitaya_scpi as scpi

    IP = '192.168.178.102'
    rp_s = scpi.scpi(IP)

    wave_form = 'arbitrary'
    freq = 10000
    ampl = 1

    N = 16384               # Number of samples
    t = np.linspace(0, 1, N)*2*math.pi

    x = np.sin(t) + 1/3*np.sin(3*t)
    y = 1/2*np.sin(t) + 1/4*np.sin(4*t)

    plt.plot(t, x, t, y)
    plt.title('Custom waveform')
    plt.show()


    waveform_ch_10 = []
    waveform_ch_20 = []

    for n in x:
        waveform_ch_10.append(f"{n:.5f}")
    waveform_ch_1 = ", ".join(map(str, waveform_ch_10))

    for n in y:
        waveform_ch_20.append(f"{n:.5f}")
    waveform_ch_2 = ", ".join(map(str, waveform_ch_20))


    rp_s.tx_txt('GEN:RST')

    rp_s.tx_txt('SOUR1:FUNC ' + str(wave_form).upper())
    rp_s.tx_txt('SOUR2:FUNC ' + str(wave_form).upper())

    rp_s.tx_txt('SOUR1:TRAC:DATA:DATA ' + waveform_ch_1)
    rp_s.tx_txt('SOUR2:TRAC:DATA:DATA ' + waveform_ch_2)

    rp_s.tx_txt('SOUR1:FREQ:FIX ' + str(freq))
    rp_s.tx_txt('SOUR2:FREQ:FIX ' + str(freq))

    rp_s.tx_txt('SOUR1:VOLT ' + str(ampl))
    rp_s.tx_txt('SOUR2:VOLT ' + str(ampl))

    rp_s.tx_txt('OUTPUT:STATE ON')
    rp_s.tx_txt('SOUR:TRIG:INT')
    
    rp_s.close()

**Using functions:**

.. code-block:: python

    #!/usr/bin/env python3
    
    import numpy as np
    import math
    from matplotlib import pyplot as plt
    import redpitaya_scpi as scpi

    IP = '192.168.178.102'
    rp_s = scpi.scpi(IP)

    wave_form = 'arbitrary'
    freq = 10000
    ampl = 1

    N = 16384                   # Number of samples
    t = np.linspace(0, 1, N)*2*math.pi

    x = np.sin(t) + 1/3*np.sin(3*t)
    y = 1/2*np.sin(t) + 1/4*np.sin(4*t)

    plt.plot(t, x, t, y)
    plt.title('Custom waveform')
    plt.show()

    rp_s.tx_txt('GEN:RST')

    # Function for configuring a Source 
    rp_s.sour_set(1, wave_form, ampl, freq, data= x)
    rp_s.sour_set(2, wave_form, ampl, freq, data= y)

    rp_s.tx_txt('OUTPUT:STATE ON')
    rp_s.tx_txt('SOUR:TRIG:INT')
    
    rp_s.close()


.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>



Code - LabVIEW
----------------

.. figure:: img/Custom-waveform-signal-generator_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Custom%20waveform%20signal%20generation.vi>`_



API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information is :ref:`here <comC>`.

Code - C API
---------------

.. code-block:: c

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    #include "rp.h"

    #define M_PI 3.14159265358979323846

    int main(int argc, char **argv){

        int i;
        int buff_size = 16384;

        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
            fprintf(stderr, "Rp api init failed!\n");
        }

        float *t = (float *)malloc(buff_size * sizeof(float));
        float *x = (float *)malloc(buff_size * sizeof(float));
        float *y = (float *)malloc(buff_size * sizeof(float));

        for(i = 1; i < buff_size; i++){
            t[i] = (2 * M_PI) / buff_size * i;
        }

        for (int i = 0; i < buff_size; ++i){
            x[i] = sin(t[i]) + ((1.0/3.0) * sin(t[i] * 3));
            y[i] = (1.0/2.0) * sin(t[i]) + (1.0/4.0) * sin(t[i] * 4);
        }

        /* Reset Generation */
        rp_GenReset();

        /* Generation */
        rp_GenSynchronise();

        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
        rp_GenWaveform(RP_CH_2, RP_WAVEFORM_ARBITRARY);

        rp_GenArbWaveform(RP_CH_1, x, buff_size);
        rp_GenArbWaveform(RP_CH_2, y, buff_size);

        rp_GenAmp(RP_CH_1, 0.7);
        rp_GenAmp(RP_CH_2, 1.0);

        rp_GenFreq(RP_CH_1, 4000.0);
        rp_GenFreq(RP_CH_2, 4000.0);

        rp_GenOutEnable(RP_CH_1);
        rp_GenOutEnable(RP_CH_2);
        rp_GenTriggerOnly(RP_CH_1);
        rp_GenTriggerOnly(RP_CH_2);

        /* Releasing resources */
        free(y);
        free(x);
        free(t);
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
    waveform = rp.RP_WAVEFORM_ARBITRARY
    freq = 10000
    ampl = 1
    
    N = 16384       # Number of samples in the buffer
     
    ##### Custom waveform setup #####
    x = rp.arbBuffer(N)
    y = rp.arbBuffer(N)
    
    t = np.linspace(0, 1, N)*2*np.pi
    
    x_temp = np.sin(t) + 1/3*np.sin(3*t)
    y_temp = 1/2*np.sin(t) + 1/4*np.sin(4*t)
    
    for i in range(0, N, 1):
        x[i] = float(x_temp[i])
        y[i] = float(y_temp[i])
    
    
    # Initialize the interface
    rp.rp_Init()
    
    # Reset generator
    rp.rp_GenReset()
    
    ###### Generation #####
    rp.rp_GenWaveform(channel, waveform)
    rp.rp_GenArbWaveform(channel, x.cast(), N)
    rp.rp_GenFreqDirect(channel, freq)
    rp.rp_GenAmp(channel, ampl)
    
    rp.rp_GenWaveform(channel2, waveform)
    rp.rp_GenArbWaveform(channel2, y.cast(), N)
    rp.rp_GenFreqDirect(channel2, freq)
    rp.rp_GenAmp(channel2, ampl)
    
    #? Possible trigger sources:
    #?   RP_GEN_TRIG_SRC_INTERNAL, RP_GEN_TRIG_SRC_EXT_PE, RP_GEN_TRIG_SRC_EXT_NE
    
    # Specify generator trigger source
    rp.rp_GenTriggerSource(channel, rp.RP_GEN_TRIG_SRC_INTERNAL)
    
    # Enable output synchronisation
    rp.rp_GenOutEnableSync(True)
    rp.rp_GenOutEnable(channel)
    
    # Syncronise output channels
    rp.rp_GenSynchronise()
    rp.rp_GenTriggerOnly(channel)
    
    
    # Release resources
    rp.rp_Release()
 

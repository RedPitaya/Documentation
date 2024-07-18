Generate sweep signal
##########################

Description
=============

This example shows how to program Red Pitaya to generate a sweep signal from 1 kHz to 100 kHz. Voltage and frequency ranges depend on the Red Pitaya model.


Required hardware
==================

    - Red Pitaya device

.. figure:: ../general_img/RedPitaya_general.png


Required software
==================

- :ref:`Red Pitaya Nightly Build OS or higher <prepareSD>`


SCPI Code Examples
====================

Code - MATLAB®
---------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Variables
    waveform = 'sine';
    ampl = 1;
    
    % Sweep settings
    sweep_start_freq = 1000;
    sweep_stop_freq = 100000;
    sweep_time_us = 5000000;    % in microseconds
    sweep_mode = 'log';         % linear / log
    sweep_dir = 'up_down';       % normal / up_down
    
    
    %% Define Red Pitaya as TCP client object
    
    IP = 'rp-f0a235.local';           % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);
    
    %% Open connection with your Red Pitaya
    RP.ByteOrder = "big-endian";
    configureTerminator(RP, "CR/LF");
    
    % Reset Generation
    writeline(RP,'GEN:RST');
    
    writeline(RP, append('SOUR1:FUNC ', upper(waveform)));
    
    % Configure sweep settings
    writeline(RP, append('SOUR1:SWeep:FREQ:START ', num2str(sweep_start_freq)));
    writeline(RP, append('SOUR1:SWeep:FREQ:STOP ', num2str(sweep_stop_freq)));
    writeline(RP, append('SOUR1:SWeep:TIME ', num2str(sweep_time_us)));
    
    writeline(RP, append('SOUR1:SWeep:MODE ', upper(sweep_mode)));
    writeline(RP, append('SOUR1:SWeep:DIR ', upper(sweep_dir)));
    
    writeline(RP, 'SOUR1:SWeep:STATE ON');
    writeline(RP, 'OUTPUT1:STATE ON');
    writeline(RP, 'SOUR1:TRIG:INT');
    
    %% Close connection with Red Pitaya
    clear RP;



Code - Python
-----------------

**Using just SCPI commands:**

.. code-block:: python

    #!/usr/bin/env python3
    import redpitaya_scpi as scpi
    
    channel = 1
    
    waveform = 'sine'
    ampl = 1
    
    # Sweep settings
    sweep_start_freq = 1000
    sweep_stop_freq = 100000
    sweep_time_us = 5000000     # in microseconds
    sweep_mode = "log"          # linear / log
    sweep_dir = "up_down"       # normal / up_down
    
    
    IP = 'rp-f0a235.local'          # Connecting to Red Pitaya
    rp = scpi.scpi(IP)
    
    rp.tx_txt("GEN:RST")
    
    rp.tx_txt(f"SOUR{channel}:FUNC {waveform.upper()}")     # Specifying waveform
    rp.tx_txt(f"SOUR{channel}:VOLT {ampl}")         # Setting one-way amplitude
    
    # Configuring Sweep settings
    rp.tx_txt(f"SOUR{channel}:SWeep:FREQ:START {sweep_start_freq}")     # Start frequency
    rp.tx_txt(f"SOUR{channel}:SWeep:FREQ:STOP {sweep_stop_freq}")       # Stop/End frequency
    rp.tx_txt(f"SOUR{channel}:SWeep:TIME {sweep_time_us}")              # Sweep time in us
    
    rp.tx_txt(f"SOUR{channel}:SWeep:MODE {sweep_mode.upper()}")         # Sweep mode
    rp.tx_txt(f"SOUR{channel}:SWeep:DIR {sweep_dir.upper()}")           # Direction
    
    rp.tx_txt(f"SOUR{channel}:SWeep:STATE ON")                          # Turning ON sweep mode
    rp.tx_txt(f"OUTPUT{channel}:STATE ON")                              # Enabling output channel
    rp.tx_txt(f"SOUR{channel}:TRIG:INT")                                # Triggering the generator
    
    rp.close()

**Using functions: (IN DEV)**

.. code-block:: python

    #!/usr/bin/env python3
    import redpitaya_scpi as scpi
    
    channel = 1
    
    waveform = 'sine'
    ampl = 1
    
    # Sweep settings
    sweep_start_freq = 1000
    sweep_stop_freq = 100000
    sweep_time_us = 5000000     # in microseconds
    sweep_mode = "log"          # linear / log
    sweep_dir = "up_down"       # normal / up_down
    
    
    IP = 'rp-f0a235.local'          # Connecting to Red Pitaya
    rp = scpi.scpi(IP)
    
    rp.tx_txt("GEN:RST")
    
    # Set generator settings (waveform and amplitude, frequency does not matter)
    rp.gen_set(channel, waveform, ampl, sweep_start_freq)
    
    # Set sweep mode settings
    rp.gen_sweep_set(channel, sweep_start_freq, sweep_stop_freq, sweep_time_us, sweep_mode, sweep_dir)
    
    rp.tx_txt(f"SOUR{channel}:SWeep:STATE ON")                          # Turning ON sweep mode
    rp.tx_txt(f"OUTPUT{channel}:STATE ON")                              # Enabling output channel
    rp.tx_txt(f"SOUR{channel}:TRIG:INT")                                # Triggering the generator
    
    rp.close()


.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>



API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead, the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information are :ref:`here <comC>`.

Code - C++ API
---------------

.. code-block:: cpp

    /* Red Pitaya C++ API example of generating a sweep signal */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    
    #include "rp.h"
    #include "common/rp_sweep.h"
    
    
    using namespace rp_sweep_api;
    
    int main(int argc, char *argv[]) {

        /* Variables */
        int start_freq = 1000;
        int stop_freq = 100000;
        int sweep_time_us = 5000000;
        rp_gen_sweep_mode_t sweep_mode = RP_GEN_SWEEP_MODE_LINEAR;  // RP_GEN_SWEEP_MODE_LOG
        rp_gen_sweep_dir_t sweep_dir = RP_GEN_SWEEP_DIR_NORMAL;     // RP_GEN_SWEEP_DIR_UP_DOWN
    
        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
            fprintf(stderr, "Rp api init failed!\n");
        }
    
        if(rp_SWInit() != RP_OK){
            fprintf(stderr, "Rp sweep init failed!\n");
        }
    
    
        /* Reset Generation and clear all sweep parameters */
        rp_GenReset();
        rp_SWResetAll();
    
        /* Configure Generator parameters */
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
        rp_GenFreq(RP_CH_1, start_freq);
        rp_GenAmp(RP_CH_1, 1.0);
    
        /* Configure sweep parameters */
        rp_SWSetStartFreq(RP_CH_1, start_freq);
        rp_SWSetStopFreq(RP_CH_1, stop_freq);
        rp_SWSetTime(RP_CH_1, sweep_time_us);
        rp_SWSetMode(RP_CH_1, sweep_mode);
        rp_SWSetDir(RP_CH_1, sweep_dir);
    
        /* Turn on the output */
        rp_GenOutEnable(RP_CH_1);
        rp_GenTriggerOnly(RP_CH_1);
    
        /* Turn ON Sweep generator */
        rp_SWGenSweep(RP_CH_1, true);
    
        /* Start sweep generation */
        rp_SWRun();
        printf("Press enter to continue...\n");
        getchar();
        /* Stop sweep generation */
        rp_SWStop();
        printf("Press enter to continue...\n");
        getchar();
    
        /* Release resources */
        rp_SWRelease();
        rp_Release();
        return 0;
    }



Code - Python API
------------------

.. code-block:: python

    #!/usr/bin/python3
    
    import time
    import rp
    import rp_sweep
    
    
    channel = rp.RP_CH_1        # rp.RP_CH_2
    waveform = rp.RP_WAVEFORM_SINE
    ampl = 1
    
    # Sweep settings
    sweep_start_freq = 1000
    sweep_stop_freq = 100000
    sweep_time_us = 5000000                         # in microseconds
    sweep_mode = rp_sweep.RP_GEN_SWEEP_MODE_LINEAR  # linear / log
    sweep_dir = rp_sweep.RP_GEN_SWEEP_DIR_NORMAL    # normal / up_down
    
    # Initialize the interface
    rp.rp_Init()
    rp_sweep.rp_SWInit()
    
    # Reset generator and sweep mode
    rp.rp_GenReset()
    rp_sweep.rp_SWResetAll()
    
    print("Reset")
    ###### Generation #####
    rp.rp_GenWaveform(channel, waveform)
    rp.rp_GenFreqDirect(channel, sweep_start_freq)
    rp.rp_GenAmp(channel, ampl)
    
    ## Sweep settings
    rp_sweep.rp_SWSetStartFreq(channel, sweep_start_freq)
    rp_sweep.rp_SWSetStopFreq(channel, sweep_stop_freq)
    rp_sweep.rp_SWSetTime(channel, sweep_time_us)
    rp_sweep.rp_SWSetMode(channel, sweep_mode)
    rp_sweep.rp_SWSetDir(channel, sweep_dir)
    
    print(f"Start freq: {rp_sweep.rp_SWGetStartFreq(channel)[1]}")
    print(f"Stop freq: {rp_sweep.rp_SWGetStopFreq(channel)[1]}")
    print(f"Time [us]: {rp_sweep.rp_SWGetTime(channel)[1]}")
    print(f"Mode: {rp_sweep.rp_SWGetMode(channel)[1]}")
    print(f"Dir: {rp_sweep.rp_SWGetDir(channel)[1]}")
    print("Sweep set")
    
    rp_sweep.rp_SWGenSweep(channel, True)
    
    # Enable output and trigger the generator
    rp.rp_GenOutEnable(channel)
    rp.rp_GenTriggerOnly(channel)
    
    rp_sweep.rp_SWRun()
    input()
    rp_sweep.rp_SWStop()
    
    rp_sweep.rp_SWGenSweep(channel, False)
    
    # Release resources
    rp_sweep.rp_SWRelease()
    rp.rp_Release()




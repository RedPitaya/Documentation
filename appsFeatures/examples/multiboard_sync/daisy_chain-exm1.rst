.. _daisy_chain_sync_exam1:

Daisy chain generation and acquisition
######################################


.. http://blog.redpitaya.com/examples-new/daisy-chain-generation-and-acquisition/


Description
============

This example shows how to synchronise the Red Pitaya X-channel system (daisy chain) to simultaneously acquire 16k samples of a generated signal on multiple units (fast RF inputs and outputs).

Required hardware
===================

    - Primary Red Pitaya device (STEMlab 125-14 LN)
    - One or more Secondary devices (STEMlab 125-14 LN Secondary)
    - SATA cables
    - SMA cables and SMA T-connectors

Wiring example:

-   Connect OUT1 of the primary device with IN1 of the primary device and IN1 of the secondary device.
-   Connect the Primary and Secondary devices with SATA cables


Required software
===================

.. include:: ../sw_requirement.inc


SCPI Code Examples
====================


Code - MATLAB
--------------

.. code-block:: matlab

    %% ### DAISY CHAIN EXAMPLE ###
    % This example is for setting up two units (one primary and one secondary)
    % For multiple secondary units duplicate the code for the secondary unit
    % and change the IP address and RP_SEC to for example, RP_SECx (where x is
    % a consecutive secondary unit)
    % This example is written for the X-channel System connected with SATA cables
    
    %% Parameters
    clear all;
    close all;
    clc
    
    % Generation
    wave_form = 'SINE';
    freq = 100e3;
    ampl = 1;
    
    % Acquisition
    dec = 2;
    trig_lvl = 0.5;
    trig_dly = 7000;
    
    %% Set up the IP and SCPI server
    
    IP_PRI = 'rp-f066c8.local';           % Primary unit
    IP_SEC = 'rp-f0ac90.local';           % Secondary unit
    
    port = 5000;
    RP_PRI = tcpclient(IP_PRI, port);           % create a TCP client object
    RP_SEC = tcpclient(IP_SEC, port);
    
    RP_PRI.ByteOrder = 'big-endian';            % Define byte order and terminator for both units
    configureTerminator(RP_PRI, 'CR/LF'); 
    RP_SEC.ByteOrder = 'big-endian';
    configureTerminator(RP_SEC, 'CR/LF');       % defines the line terminator (end sequence of input characters)
    
    flush(RP_PRI);
    fprintf('Program start');


    %% Reseting Generation and Acquisition
    writeline(RP_PRI,'GEN:RST');
    writeline(RP_PRI,'ACQ:RST');
    
    writeline(RP_SEC,'GEN:RST');
    writeline(RP_SEC,'ACQ:RST');


    %%% ENABLING THE DAISY CHAIN PRIMARY UNIT %%%
    writeline(RP_PRI,'DAISY:SYNC:TRig ON');
    writeline(RP_PRI,'DAISY:SYNC:CLK ON');
    writeline(RP_PRI,'DAISY:TRIG_O:SOUR ADC');      % Select which trigger will be passed on over SATA
    
    writeline(RP_PRI,'DIG:PIN LED5,1');     % indicator
    
    fprintf('Trig: %s\n', writeread(RP_PRI,'DAISY:SYNC:TRig?'));
    fprintf('CLK: %s\n', writeread(RP_PRI,'DAISY:SYNC:CLK?'));
    fprintf('Source: %s\n', writeread(RP_PRI,'DAISY:TRIG_O:SOUR?'));
    
    %%% ENABLING THE DAISY CHAIN SECONDARY UNIT %%%
    % this section must be copied if using multiple secondary devices (once for each device)
    writeline(RP_SEC,'DAISY:SYNC:TRig ON');
    writeline(RP_SEC,'DAISY:SYNC:CLK ON');
    
    writeline(RP_SEC,'DIG:PIN LED5,1');     % indicator


    %% Generation - Primary unit
    writeline(RP_PRI, append('SOUR1:FUNC ', wave_form));
    writeline(RP_PRI, append('SOUR1:FREQ:FIX ', num2str(freq)));
    writeline(RP_PRI, append('SOUR1:VOLT ', num2str(ampl)));
    
    writeline(RP_PRI, 'OUTPUT1:STATE ON');
    fprintf('Generation start\n');
    
    
    %% Acquisition Setup
    % Primary unit
    writeline(RP_PRI, append('ACQ:DEC ', int2str(dec)));
    writeline(RP_PRI, append('ACQ:TRig:LEV ', num2str(trig_lvl)));
    writeline(RP_PRI, append('ACQ:TRig:DLY ', num2str(trig_dly)));
    
    % Secondary unit
    writeline(RP_SEC, append('ACQ:DEC ', num2str(dec)));
    writeline(RP_SEC, append('ACQ:TRig:LEV ', num2str(trig_lvl)));
    writeline(RP_SEC, append('ACQ:TRig:DLY ', num2str(trig_dly)));
    
    
    %% Acquisition Start
    fprintf('ACQ Start\n');
    % First on secondary unit
    writeline(RP_SEC, 'ACQ:START');
    pause(0.05);
    writeline(RP_SEC, 'ACQ:TRig EXT_NE');
    
    % Then on primary unit
    writeline(RP_PRI, 'ACQ:START');
    pause(0.05);
    writeline(RP_PRI, 'ACQ:TRig CH1_PE');
    
    pause(0.1);
    writeline(RP_PRI, 'SOUR1:TRig:INT');    % Simulate a trigger
    
    % Acquisition check if data is ready
    
    % ## Primary unit ##
    while 1
        % Get Trigger Status
        trigger = writeread(RP_PRI, 'ACQ:TRig:STAT?');
        if strcmp(trigger,'TD')      % Triggerd?
            break
        end
    end
    fprintf('Trigger primary condition met.\n');

    %%! OS 2.00 or higher only !%%
    while 1
        if strcmp(writeread(RP_PRI,'ACQ:TRig:FILL?'),'1')
            break
        end
    end
    fprintf('Buffer primary filled.\n');
    
    % ## Secondary unit ##
    while 1
        % Get Trigger Status
        if strcmp(writeread(RP_SEC,'ACQ:TRig:STAT?'),'TD')      % Triggerd?
            break
        end
    end
    fprintf('Trigger secondary condition met.\n');

    %%! OS 2.00 or higher only !%%
    while 1
        if strcmp(writeread(RP_SEC,'ACQ:TRig:FILL?'),'1')
            break
        end
    end
    fprintf('Buffer secondary filled.\n');
    
    
    %% Read and plot data
    data_string_pri = writeread(RP_PRI,'ACQ:SOUR1:DATA?');
    data_string_sec = writeread(RP_SEC,'ACQ:SOUR1:DATA?');
    
    % Convert values to numbers.
    % The first character in string is “{“
    % and the last 3 are 2 spaces and “}”.
    
    data_pri = str2num(data_string_pri(1, 2:length(data_string_pri) - 3));
    data_sec = str2num(data_string_sec(1, 2:length(data_string_sec) - 3));
    
    % Plotting
    x = 0:16383;
    
    % MATLAB 2019b or higher
    t = tiledlayout(2,1);     % for MATLAB r2023a use 'vertical'
    
    nexttile
    plot(x, data_pri)
    title('Primary unit data')
    ylabel('V')
    xlabel('Samples')
    
    nexttile
    plot(x,data_sec)
    title('Secondary unit data')
    ylabel('V')
    xlabel('Samples')
    
    title(t, 'Acquired data')
    
    writeline(RP_PRI,'DIG:PIN LED5,0');
    writeline(RP_SEC,'DIG:PIN LED5,0');
    writeline(RP_PRI, 'OUTPUT1:STATE OFF');
    
    clear RP_PRI RP_SEC;



Code - Python
--------------

**Using SCPI commands:**

.. code-block:: python
    
    #!/usr/bin/env python3
    """Daisy chain example for Red Pitaya"""

    import time
    import matplotlib.pyplot as plt
    import numpy as np

    import redpitaya_scpi as scpi

    # Connect OUT1 primary with IN1 primary and IN1 secondary

    wave_form = "sine"
    freq = 100000
    ampl = 1

    dec = 2
    trig_lvl = 0.5
    trig_dly = 7000


    IP_PRIM = 'rp-f0a235.local'   # IP Test OS Red Pitaya
    IP_SEC = 'rp-f0ac90.local'

    rp_prim = scpi.scpi(IP_PRIM)
    rp_sec = scpi.scpi(IP_SEC)

    print("Program Start")

    rp_prim.tx_txt('GEN:RST')
    rp_prim.tx_txt('ACQ:RST')

    rp_sec.tx_txt('GEN:RST')
    rp_sec.tx_txt('ACQ:RST')

    ###### ENABLING THE DAISY CHAIN PRIMARY UNIT ######

    rp_prim.tx_txt('DAISY:SYNC:TRig ON')    #! OFF (without sync)
    rp_prim.tx_txt('DAISY:SYNC:CLK ON')
    rp_prim.tx_txt('DAISY:TRIG_O:SOUR ADC')
  
    rp_prim.tx_txt('DIG:PIN LED5,1')            # LED Indicator

    time.sleep(0.2)

    print(f"Trig: {rp_prim.txrx_txt('DAISY:SYNC:TRig?')}")
    print(f"CLK: {rp_prim.txrx_txt('DAISY:SYNC:CLK?')}")
    print(f"Sour: {rp_prim.txrx_txt('DAISY:TRIG_O:SOUR?')}\n")

    ###### ENABLING THE DAISY CHAIN SECONDARY UNIT ######
  
    rp_sec.tx_txt('DAISY:SYNC:TRig ON')  #! OFF (without sync)  
    rp_sec.tx_txt('DAISY:SYNC:CLK ON')
    rp_sec.tx_txt('DAISY:TRIG_O:SOUR ADC')     # Ext trigger will trigger the ADC
  
    rp_sec.tx_txt('DIG:PIN LED5,1')             # LED Indicator

    print("Start generator\n")


    ### Generation ### - Primary unit
    rp_prim.tx_txt(f'SOUR1:FUNC {wave_form}')
    rp_prim.tx_txt(f'SOUR1:FREQ:FIX {freq}')
    rp_prim.tx_txt(f'SOUR1:VOLT {ampl}')
  
    rp_prim.tx_txt('OUTPUT1:STATE ON')

    ### Aquisition ###

    # Primary unit
    rp_prim.tx_txt(f'ACQ:DEC {dec}')
    rp_prim.tx_txt(f'ACQ:TRig:LEV {trig_lvl}')
    rp_prim.tx_txt(f'ACQ:TRig:DLY {trig_dly}')

    # Secondary unit
    rp_sec.tx_txt(f'ACQ:DEC {dec}')
    rp_sec.tx_txt(f'ACQ:TRig:LEV {trig_lvl}')
    rp_sec.tx_txt(f'ACQ:TRig:DLY {trig_dly}')

  
    rp_sec.tx_txt('ACQ:START')
    time.sleep(0.2)                           # Not necessary
    rp_sec.tx_txt('ACQ:TRig EXT_NE')          #! CH1_PE (without sync trig) EXT_NE (with sync trig)
                                              # If not synchronised make sure no signal arrives before both units are set up

    rp_prim.tx_txt('ACQ:START')
    time.sleep(0.2)
    rp_prim.tx_txt('ACQ:TRig CH1_PE')

    time.sleep(1)                             # Symulating a trigger after one second
    rp_prim.tx_txt('SOUR1:TRig:INT')

    print("ACQ start")

    while 1:
        # Get Trigger Status
        if rp_prim.txrx_txt('ACQ:TRig:STAT?') == 'TD':               # Triggerd?
            break
    print("Trigger primary condition met.")

    ## ! OS 2.00 or higher only ! ##
    while 1:
        if rp_prim.txrx_txt('ACQ:TRig:FILL?') == '1':
            break
    print("Buffer primary filled.")

    while 1:
        # Get Trigger Status
        if rp_sec.txrx_txt('ACQ:TRig:STAT?') == 'TD':               # Triggerd?
            break
    print("Trigger secondary condition met.")

    ## ! OS 2.00 or higher only ! ##
    while 1:
        if rp_sec.txrx_txt('ACQ:TRig:FILL?') == '1':
            break
    print("Buffer secondary filled.")


    # Read data and plot
    rp_prim.tx_txt('ACQ:SOUR1:DATA?')               # Read full buffer primary (source 1)
    data_string1 = rp_prim.rx_txt()                 # data into a string

    rp_sec.tx_txt('ACQ:SOUR1:DATA?')                # Read full buffer secondary (source 1)
    data_string2 = rp_sec.rx_txt()

    # Display both buffers at once
    n = 2
    buff = np.zeros((n,16384))

    # Remove brackets and empty spaces + string => float
    data_string1 = data_string1.strip('{}\n\r').replace("  ", "").split(',')
    data_string2 = data_string2.strip('{}\n\r').replace("  ", "").split(',')
    # Transform data into data series
    buff[0, :] = list(map(float, data_string1))
    buff[1, :] = list(map(float, data_string2))


    ######## PLOTTING THE DATA #########
    fig, axs = plt.subplots(n, sharex = True)               # plot the data (n subplots)
    fig.suptitle("Measurements P1 S2")

    for i in range(0,n,1):                                  # plotting the acquired buffers            
        axs[i].plot(buff[i])

    plt.show()

    rp_prim.close()
    rp_sec.close()


**Using functions:**

.. code-block:: python
    
    #!/usr/bin/env python3
    """Daisy chain example for Red Pitaya"""

    import time
    import matplotlib.pyplot as plt
    import numpy as np

    import redpitaya_scpi as scpi

    # Connect OUT1 primary with IN1 primary and IN1 secondary


    IP_PRIM = 'rp-f0a235.local'   # IP Test OS Red Pitaya
    IP_SEC = 'rp-f0ac90.local'

    rp_prim = scpi.scpi(IP_PRIM)
    rp_sec = scpi.scpi(IP_SEC)

    print("Program Start")

    rp_prim.tx_txt('GEN:RST')
    rp_prim.tx_txt('ACQ:RST')

    rp_sec.tx_txt('GEN:RST')
    rp_sec.tx_txt('ACQ:RST')

    ###### ENABLING THE DAISY CHAIN PRIMARY UNIT ######

    rp_prim.tx_txt('DAISY:SYNC:TRig ON')    #! OFF (without sync)
    rp_prim.tx_txt('DAISY:SYNC:CLK ON')
    rp_prim.tx_txt('DAISY:TRIG_O:SOUR ADC')
  
    rp_prim.tx_txt('DIG:PIN LED5,1')            # LED Indicator

    time.sleep(0.2)

    print(f"Trig: {rp_prim.txrx_txt('DAISY:SYNC:TRig?')}")
    print(f"CLK: {rp_prim.txrx_txt('DAISY:SYNC:CLK?')}")
    print(f"Sour: {rp_prim.txrx_txt('DAISY:TRIG_O:SOUR?')}\n")

    ###### ENABLING THE DAISY CHAIN SECONDARY UNIT ######
  
    rp_sec.tx_txt('DAISY:SYNC:TRig ON')  #! OFF (without sync)  
    rp_sec.tx_txt('DAISY:SYNC:CLK ON')
    rp_sec.tx_txt('DAISY:TRIG_O:SOUR ADC')     # Ext trigger will trigger the ADC
  
    rp_sec.tx_txt('DIG:PIN LED5,1')             # LED Indicator

    print("Start generator\n")


    ### Generation ### - Primary unit
    rp_prim.sour_set(1, "sine", 1, 100000)
    rp_prim.tx_txt('OUTPUT1:STATE ON')

    ### Aquisition ###

    # Primary unit
    rp_prim.acq_set(dec = 2,
                    trig_lvl = 0.5,
                    trig_delay = 7000)


    # Secondary unit
    rp_sec.acq_set(dec = 2,
                   trig_lvl = 0.5,
                   trig_delay = 7000)


    rp_sec.tx_txt('ACQ:START')
    time.sleep(0.2)                           # Not necessary
    rp_sec.tx_txt('ACQ:TRig EXT_NE')          #! CH1_PE (without sync trig) EXT_NE (with sync trig)
                                              # If not synchronised make sure no signal arrives before both units are set up

    rp_prim.tx_txt('ACQ:START')
    time.sleep(0.2)
    rp_prim.tx_txt('ACQ:TRig CH1_PE')

    time.sleep(1)                             # Symulating a trigger after one second
    rp_prim.tx_txt('SOUR1:TRig:INT')

    print("ACQ start")

    while 1:
        # Get Trigger Status
        if rp_prim.txrx_txt('ACQ:TRig:STAT?') == 'TD':               # Triggerd?
            break
    print("Trigger primary condition met.")

    ## ! OS 2.00 or higher only ! ##
    while 1:
        if rp_prim.txrx_txt('ACQ:TRig:FILL?') == '1':
            break
    print("Buffer primary filled.")

    while 1:
        # Get Trigger Status
        if rp_sec.txrx_txt('ACQ:TRig:STAT?') == 'TD':               # Triggerd?
            break
    print("Trigger secondary condition met.")

    ## ! OS 2.00 or higher only ! ##
    while 1:
        if rp_sec.txrx_txt('ACQ:TRig:FILL?') == '1':
            break
    print("Buffer secondary filled.")


    # Read data and plot
    rp_prim.tx_txt('ACQ:SOUR1:DATA?')               # Read full buffer primary (source 1)
    data_string1 = rp_prim.rx_txt()                 # data into a string

    rp_sec.tx_txt('ACQ:SOUR1:DATA?')                # Read full buffer secondary (source 1)
    data_string2 = rp_sec.rx_txt()

    # Display both buffers at once
    n = 2
    buff = np.zeros((n,16384))

    # Remove brackets and empty spaces + string => float
    data_string1 = data_string1.strip('{}\n\r').replace("  ", "").split(',')
    data_string2 = data_string2.strip('{}\n\r').replace("  ", "").split(',')
    # Transform data into data series
    buff[0, :] = list(map(float, data_string1))
    buff[1, :] = list(map(float, data_string2))


    ######## PLOTTING THE DATA #########
    fig, axs = plt.subplots(n, sharex = True)               # plot the data (n subplots)
    fig.suptitle("Measurements P1 S2")

    for i in range(0,n,1):                                  # plotting the acquired buffers            
        axs[i].plot(buff[i])

    plt.show()

    rp_prim.close()
    rp_sec.close()


.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>



API Code Examples
====================

.. include:: ../c_code_note.inc

.. Code - C API
.. ---------------


Code - Python API
------------------

.. code-block:: python

    #!/usr/bin/python3
    
    import time
    import numpy as np
    import rp
    
    ########! Primary unit code !#########
    channel = rp.RP_CH_1        # rp.RP_CH_2
    waveform = rp.RP_WAVEFORM_SINE
    freq = 100000
    ampl = 1.0

    trig_lvl = 0.5
    trig_dly = 0

    dec = rp.RP_DEC_1

    gen_trig_sour = rp.RP_GEN_TRIG_SRC_INTERNAL

    acq_trig_sour = rp.RP_TRIG_SRC_CHA_PE

    N = 16384

    # Initialize the interface
    rp.rp_Init()

    # Reset Generation and Acquisition
    rp.rp_GenReset()
    rp.rp_AcqReset()

    ###### Enable Daisy Chain #####
    rp.rp_SetEnableDiasyChainClockSync(True)        # Sync Clock
    rp.rp_SetEnableDaisyChainTrigSync(True)         # Sync Trigger

    # Choose which trigger to synchronise (rp.OUT_TR_ADC, rp.OUT_TR_DAC)
    rp.rp_SetSourceTrigOutput(rp.OUT_TR_ADC)

    # LED indicator
    rp.rp_DpinSetState(rp.RP_LED5, rp.RP_HIGH)

    
    ###### Generation #####
    print("Gen_start")
    rp.rp_GenWaveform(channel, waveform)
    rp.rp_GenFreqDirect(channel, freq)
    rp.rp_GenAmp(channel, ampl)

    rp.rp_GenTriggerSource(channel, gen_trig_sour)
    rp.rp_GenOutEnable(channel)

    ##### Acquisition #####
    rp.rp_AcqSetDecimation(dec)
    
    # Set trigger level and delay
    rp.rp_AcqSetTriggerLevel(rp.RP_T_CH_1, trig_lvl)
    rp.rp_AcqSetTriggerDelay(trig_dly)

    # Start Acquisition
    print("Acq_start")
    rp.rp_AcqStart()

    # Specify trigger - input 1 positive edge
    rp.rp_AcqSetTriggerSrc(acq_trig_sour)

    rp.rp_GenTriggerOnly(channel)       # Trigger generator

    # Trigger state
    while 1:
        trig_state = rp.rp_AcqGetTriggerState()[1]
        if trig_state == rp.RP_TRIG_STATE_TRIGGERED:
            break

    ## ! OS 2.00 or higher only ! ##
    # Fill state
    while 1:
        if rp.rp_AcqGetBufferFillState()[1]:
            break

    ### Get data ###
    # Volts
    fbuff = rp.fBuffer(N)
    res = rp.rp_AcqGetDataV(rp.RP_CH_1, 0, N, fbuff)
    
    data_V = np.zeros(N, dtype = float)
    
    for i in range(0, N, 1):
        data_V[i] = fbuff[i]
    
    print(f"Data in Volts: {data_V}")
    
    # Release resources
    rp.rp_Release()



    ########! Secondary unit code !#########
    channel = rp.RP_CH_1        # rp.RP_CH_2
    waveform = rp.RP_WAVEFORM_SINE
    freq = 100000
    ampl = 1.0

    trig_lvl = 0.5
    trig_dly = 0

    dec = rp.RP_DEC_1

    # Initialize the interface
    rp.rp_Init()

    # Reset Generation and Acquisition
    rp.rp_GenReset()
    rp.rp_AcqReset()

    ###### Enable Daisy Chain #####
    rp.rp_SetEnableDiasyChainClockSync(True)        # Sync Clock
    rp.rp_SetEnableDaisyChainTrigSync(True)         # Sync Trigger

    # Choose which trigger to synchronise (rp.OUT_TR_ADC, rp.OUT_TR_DAC)
    rp.rp_SetSourceTrigOutput(rp.OUT_TR_ADC)

    # LED indicator
    rp.rp_DpinSetState(rp.RP_LED5, rp.RP_HIGH)


    ##### Acquisition #####
    rp.rp_AcqSetDecimation(dec)
    rp.rp_AcqSetTriggerDelay(trig_dly)

    # Start Acquisition
    print("Acq_start")
    rp.rp_AcqStart()

    # Specify trigger - must be EXT_NE
    rp.rp_AcqSetTriggerSrc(rp.RP_TRIG_SRC_EXT_NE)

    # Trigger state
    while 1:
        trig_state = rp.rp_AcqGetTriggerState()[1]
        if trig_state == rp.RP_TRIG_STATE_TRIGGERED:
            break

    ## ! OS 2.00 or higher only ! ##
    # Fill state
    while 1:
        if rp.rp_AcqGetBufferFillState()[1]:
            break
    
    ### Get data ###
    # Volts
    fbuff = rp.fBuffer(N)
    res = rp.rp_AcqGetDataV(rp.RP_CH_1, 0, N, fbuff)
    data_V = np.zeros(N, dtype = float)

    for i in range(0, N, 1):
        data_V[i] = fbuff[i]

    print(f"Data in Volts: {data_V}")
    
    # Release resources
    rp.rp_Release()


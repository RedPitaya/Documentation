Daisy chain click-shield generation and acquisition
###################################################


.. http://blog.redpitaya.com/examples-new/daisy-chain-generation-and-acquisition/


Description
***********

This example shows how to synchronise the Red Pitaya X-channel system (daisy chain) to simultaneously acquire 16k samples of a generated signal on multiple units (fast RF inputs and outputs).
Red Pitaya click shields are required for all units.

Required hardware
*****************

    - Primary Red Pitaya device (STEMlab 125-14 LN)
    - One or more Secondary devices (STEMlab 125-14 LN Secondary)
    - A click shield for each unit
    - Cables

**Wiring example:**

  - Connect OUT1 of the primary device with IN1 of the primary device and IN1 of the secondary device.
  - Connect the click shields with "" cables

**Click shield switch and jumper positions:**

  Primary unit:
  
    - REF CLOCK    ==> ON
    - CLOCK SELECT ==> EXT
    - J4, J5, J6, J7 present

  Secondary units:

    - REF CLOCK    ==> OFF
    - CLOCK SELECT ==> EXT
    - J6, J7 present

**Pictures coming soon...**

.. note::

  The trigger signals from the SATA connector and the DIO0_P (External trigger pin) are OR-ed together in the software. The generation and acquisition trigger fronts apply after the "OR gate" and trigger either DAC or ADC, depending on the ``DAISY:TRIG_O:SOUR <mode>`` command.

Code - Python
*************

Using just SCPI commands:

.. code-block:: python
    
    #!/usr/bin/env python3
    """ Click shield daisy chain example for Red Pitaya """

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

    rp_prim.tx_txt('DAISY:SYNC:TRIG ON')    #! OFF (without sync)
    rp_prim.tx_txt('DAISY:SYNC:CLK ON')
    rp_prim.tx_txt('DAISY:TRIG_O:ENable ON')     # Enables GPIO0_N as trigger output
    rp_prim.tx_txt('DAISY:TRIG_O:SOUR ADC')      # Ext trigger will trigger the ADC
  
    rp_prim.tx_txt('DIG:PIN LED5,1')             # LED Indicator

    time.sleep(0.2)

    print(f"Trig sync: {rp_prim.txrx_txt('DAISY:SYNC:TRIG?')}")
    print(f"CLK sync: {rp_prim.txrx_txt('DAISY:SYNC:CLK?')}")
    print(f"GPIO0_N trig: {rp_prim.txrx_txt('DAISY:TRIG_O:SOUR?')}\n")
    print(f"Source: {rp_prim.txrx_txt('DAISY:TRIG_O:SOUR?')}\n")

    ###### ENABLING THE DAISY CHAIN SECONDARY UNIT ######
  
    rp_sec.tx_txt('DAISY:SYNC:TRIG ON')    #! OFF (without sync)
    rp_sec.tx_txt('DAISY:SYNC:CLK ON')
    rp_sec.tx_txt('DAISY:TRIG_O:ENable ON')     # Enables GPIO0_N as trigger output
    rp_sec.tx_txt('DAISY:TRIG_O:SOUR ADC')      # Ext trigger will trigger the ADC
  
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
    rp_prim.tx_txt(f'ACQ:TRIG:LEV {trig_lvl}')
    rp_prim.tx_txt(f'ACQ:TRIG:DLY {trig_dly}')

    # Secondary unit
    rp_sec.tx_txt(f'ACQ:DEC {dec}')
    rp_sec.tx_txt(f'ACQ:TRIG:LEV {trig_lvl}')
    rp_sec.tx_txt(f'ACQ:TRIG:DLY {trig_dly}')

  
    rp_sec.tx_txt('ACQ:START')
    time.sleep(0.2)                           # Not necessary
    rp_sec.tx_txt('ACQ:TRIG EXT_NE')          #! CH1_PE (without sync trig) EXT_NE (with sync trig)
                                              # If not synchronised make sure no signal arrives before both units are set up

    rp_prim.tx_txt('ACQ:START')
    time.sleep(0.2)
    rp_prim.tx_txt('ACQ:TRIG CH1_PE')

    time.sleep(1)                             # Symulating a trigger after one second
    rp_prim.tx_txt('SOUR1:TRIG:INT')

    print("ACQ start")

    while 1:
        # Get Trigger Status
        if rp_prim.txrx_txt('ACQ:TRIG:STAT?') == 'TD':               # Triggerd?
            break
    print("Trigger primary condition met.")

    while 1:
        if rp_prim.txrx_txt('ACQ:TRIG:FILL?') == '1':
            break
    print("Buffer primary filled.")

    while 1:
        # Get Trigger Status
        if rp_sec.txrx_txt('ACQ:TRIG:STAT?') == 'TD':               # Triggerd?
            break
    print("Trigger secondary condition met.")

    while 1:
        if rp_sec.txrx_txt('ACQ:TRIG:FILL?') == '1':
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


Using functions:

.. code-block:: python
    
    #!/usr/bin/env python3
    """ Click shield daisy chain example for Red Pitaya """

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

    rp_prim.tx_txt('DAISY:SYNC:TRIG ON')    #! OFF (without sync)
    rp_prim.tx_txt('DAISY:SYNC:CLK ON')
    rp_prim.tx_txt('DAISY:TRIG_O:ENable ON')     # Enables GPIO0_N as trigger output
    rp_prim.tx_txt('DAISY:TRIG_O:SOUR ADC')
  
    rp_prim.tx_txt('DIG:PIN LED5,1')            # LED Indicator

    time.sleep(0.2)

    print(f"Trig sync: {rp_prim.txrx_txt('DAISY:SYNC:TRIG?')}")
    print(f"CLK sync: {rp_prim.txrx_txt('DAISY:SYNC:CLK?')}")
    print(f"GPIO0_N trig: {rp_prim.txrx_txt('DAISY:TRIG_O:SOUR?')}\n")
    print(f"Source: {rp_prim.txrx_txt('DAISY:TRIG_O:SOUR?')}\n")

    ###### ENABLING THE DAISY CHAIN SECONDARY UNIT ######
  
    rp_sec.tx_txt('DAISY:SYNC:TRIG ON')  #! OFF (without sync)  
    rp_sec.tx_txt('DAISY:SYNC:CLK ON')
    rp_sec.tx_txt('DAISY:TRIG_O:ENable ON')    # Enables GPIO0_N as trigger output
    rp_sec.tx_txt('DAISY:TRIG_O:SOUR ADC')     # Ext trigger will trigger the ADC
  
    rp_sec.tx_txt('DIG:PIN LED5,1')            # LED Indicator

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
    rp_sec.tx_txt('ACQ:TRIG EXT_NE')          #! CH1_PE (without sync trig) EXT_NE (with sync trig)
                                              # If not synchronised make sure no signal arrives before both units are set up

    rp_prim.tx_txt('ACQ:START')
    time.sleep(0.2)
    rp_prim.tx_txt('ACQ:TRIG CH1_PE')

    time.sleep(1)                             # Symulating a trigger after one second
    rp_prim.tx_txt('SOUR1:TRIG:INT')

    print("ACQ start")

    while 1:
        # Get Trigger Status
        if rp_prim.txrx_txt('ACQ:TRIG:STAT?') == 'TD':               # Triggerd?
            break
    print("Trigger primary condition met.")

    while 1:
        if rp_prim.txrx_txt('ACQ:TRIG:FILL?') == '1':
            break
    print("Buffer primary filled.")

    while 1:
        # Get Trigger Status
        if rp_sec.txrx_txt('ACQ:TRIG:STAT?') == 'TD':               # Triggerd?
            break
    print("Trigger secondary condition met.")

    while 1:
        if rp_sec.txrx_txt('ACQ:TRIG:FILL?') == '1':
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

    The Python functions are accessible with the latest version of the redpitaya_scpi.py document available on our |redpitaya_scpi|.
    The functions represent a quality-of-life improvement. They combine the SCPI commands in optimal order. The code should function at approximately the same speed without them.

    For further information on functions, please consult the redpitaya_scpi.py code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">GitHub</a>

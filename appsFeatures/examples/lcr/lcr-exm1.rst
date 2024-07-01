.. _lcr_example:

LCR meter example
######################################

Description
============

In this example we will learn how to perform LCR meter measurements through SCPI commands.

Required hardware
==================

    -   Red Pitaya device
    -   Protoboard
    -   LCR circuit or some components
    -   Either LCR meter extension or an external shunt resistor

Instructions on how to connect the circuit to the Red Pitaya board are available :ref:`here <How to use the impedance analyzer>`.

Circuit
=======

This tutorial requires either the *LCR meter extension module* or an *external shunt resitior*.
Each method has its own upsides and downsides. Here is a quick guide on how to setup the hardware.

LCR extension module
---------------------

.. figure::  img/E_module_connection.png
    :width: 1000

The LCR meter extension module is easier to connect and automatically switches between the following shunt reisistor values:

- 10 Ω
- 100 Ω
- 1 kΩ
- 10 kΩ
- 100 kΩ
- 1 MΩ

Read more about the LCR meter extension module in our :ref:`documentation <lcr_extension_module>`.


External shunt resistor
-------------------------

.. figure::  img/IA_shunt_connection.png
    :width: 600

.. note::

    To minimise the effect of Red Pitaya's input impedance on measurements, reconfigure the jumpers as shown in the figure above (connect the middle two pins on both inputs) to bypass the input resistor divider.
    This **reduces the input voltage range to +-0.5 V**, so ensure that the output voltage setting does not exceed +-0.5 V (**ABSOLUTE MAX 0.75 V (amplitude + offset)**).


SCPI Code Examples
====================

.. note::

  This code is written for **in-dev or higher OS**. For older OS versions, please check when specific commands were released (a note is added to each command introduced in 2.00 or higher verisons).

Code - MATLAB®
---------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Define Red Pitaya as TCP/IP object
    clc
    clear all
    close all
    IP = '169.254.162.154';           % IP of your Red Pitaya
    port = 5000;
    RP = tcpclient(IP, port);
    
    % Variables
    lcr_shunt_mode = "custom";   % Custom when using shunt resistor, lcr_ext when using the extension module ("custom" or "lcr_ext")
    lcr_shunt_auto = "off";      % Automatic shunt only for LCR meter extension ("on" or "off")
        
    lcr_shunt = 10;              % Shunt resistor value
    lcr_frequency = 100000;      % Frequency at which the measurement is performed
    lcr_ampl = 0.5;              % Generator amplitude    (MAX 0.5 V (amplitude + offset)) - (ABSOLUTE MAX 0.75 V (amplitude + offset))
    lcr_offs = 0;                % Generator offset
    lcr_circuit = "series";      % "series" or "parallel" - measurement mode (affects L, C, and R parameters)
    
    
    %% Open connection with your Red Pitaya
    RP.ByteOrder = "big-endian";
    configureTerminator(RP,"CR/LF");
    
    flush(RP);
    
    % BEFORE START - CHECK EXT BOARD!
    ext_mode = writeread(RP, 'LCR:EXT:MODULE?')
    
    % BEFORE START - SET SHUNT MODE!
    writeline(RP,append('LCR:SHUNT:MODE ', upper(lcr_shunt_mode)));
    shunt_mode = writeread(RP, 'LCR:SHUNT:MODE?')
    
    % Start LCR meter
    writeline(RP, 'LCR:START')
    
    % Disable automatic shunt setting
    writeline(RP,append('LCR:SHUNT:AUTO ', upper(lcr_shunt_auto)));
    
    % Set custom shunt resistor
    writeline(RP,append('LCR:SHUNT:CUSTOM ', num2str(lcr_shunt)));
    shunt = writeread(RP, 'LCR:SHUNT:CUSTOM?')
    
    % Set LCR settings
    writeline(RP,append('LCR:FREQ ', num2str(lcr_frequency)));
    frequency = writeread(RP, 'LCR:FREQ?')
    
    writeline(RP,append('LCR:VOLT ', num2str(lcr_ampl)));
    ampl = writeread(RP, 'LCR:VOLT?')
    
    writeline(RP,append('LCR:VOLT:OFFS ', num2str(lcr_offs)));
    offset = writeread(RP, 'LCR:VOLT:OFFS?')
    
    writeline(RP,append('LCR:CIRCUIT ', upper(lcr_circuit)));
    circuit = writeread(RP, 'LCR:CIRCUIT?')
    
    % Start the generator after changing the settings
    writeline(RP, 'LCR:START:GEN')
    
    data = writeread(RP, 'LCR:MEASURE?');
    txt = jsondecode(data);
    display(txt)
    
    % Stop the LCR
    writeline(RP, 'LCR:STOP')
    
    clear RP;


Code - Python
--------------

.. code-block:: python

    #!/usr/bin/env python3
    
    """SCPI example of using LCR commands"""
    
    import time
    import json
    import numpy as np
    import redpitaya_scpi as scpi
    
    
    lcr_shunt_mode = "custom"   # Custom when using shunt resistor, lcr_ext when using the extension module ("custom" or "lcr_ext")
    lcr_shunt_auto = "off"      # Automatic shunt only for LCR meter extension ("on" or "off")
    
    lcr_shunt = 10              # Shunt resistor value
    lcr_frequency = 100000      # Frequency at which the measurement is performed
    lcr_ampl = 0.5              # Generator amplitude    (MAX 0.5 V (amplitude + offset)) - (ABSOLUTE MAX 0.75 V (amplitude + offset))
    lcr_offs = 0                # Generator offset
    lcr_circuit = "series"      # "series" or "parallel" - measurement mode (affects L, C, and R parameters)
    
    
    # IP setup
    IP = "rp-f0a235.local"                         # Red Pitaya IP
    rp = scpi.scpi(IP)                       # open connection to Red Pitaya
    
    # BEFORE START - CHECK EXT BOARD!
    print(f"LCR:EXT:MODULE: {rp.txrx_txt("LCR:EXT:MODULE?")}")
    rp.check_error()
    
    # BEFORE START - SET SHUNT MODE!
    rp.tx_txt(f"LCR:SHUNT:MODE {lcr_shunt_mode.upper()}")
    print(f"LCR:SHUNT:MODE: {rp.txrx_txt("LCR:SHUNT:MODE?")}")


    # Start LCR meter
    rp.tx_txt("LCR:START") 
    
    # Disable automatic shunt setting
    rp.tx_txt(f"LCR:SHUNT:AUTO {lcr_shunt_auto.upper()}")
    
    # Set custom shunt resistor
    rp.tx_txt(f"LCR:SHUNT:CUSTOM {lcr_shunt}")
    print(f"LCR:SHUNT:CUSTOM: {rp.txrx_txt("LCR:SHUNT:CUSTOM?")}")
    
    # Set LCR settings
    rp.tx_txt(f"LCR:FREQ {lcr_frequency}")
    print(f"LCR:FREQ: {rp.txrx_txt("LCR:FREQ?")}")
    
    rp.tx_txt(f"LCR:VOLT {lcr_ampl}")
    print(f"LCR:VOLT: {rp.txrx_txt("LCR:VOLT?")}")
    
    rp.tx_txt(f"LCR:VOLT:OFFS {lcr_offs}")
    print(f"LCR:VOLT:OFFS: {rp.txrx_txt("LCR:VOLT:OFFS?")}")
    
    rp.tx_txt(f"LCR:CIRCUIT {lcr_circuit}")
    print(f"LCR:CIRCUIT: {rp.txrx_txt("LCR:CIRCUIT?")}")
    
    # Start the generator after changing the settings.
    rp.tx_txt("LCR:START:GEN")
    rp.check_error()
    
    time.sleep(1)
    
    rp.tx_txt("LCR:MEASURE?")
    data = json.loads(rp.rx_txt())
    
    print("LCR:MEASURE?", data)
    print("Freq", data["freq"])
    print("R_s", data["R_s"])
    print("C_s", data["C_s"])
    print("L_s", data["L_s"])
    rp.check_error()
    
    rp.tx_txt("LCR:STOP")
    
    rp.close()


API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead, the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information are :ref:`here <comC>`.


Code - C API
--------------

**Coming soon**


Code - Python API
-------------------

**Coming soon**



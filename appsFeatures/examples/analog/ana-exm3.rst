Interactive voltage setting on a slow analog output
###################################################

..  http://blog.redpitaya.com/examples-new/interactive-voltage-setting-on-slow-analog-output-2/

Description
=============

This example shows how to set analog voltage on slow analog Red Pitaya outputs using a MATLAB slider. Slow analog outputs on the Red Pitaya are in the range of 0 to 1.8 Volts.

Required hardware
====================

    - Red Pitaya device
    - Voltmeter

Wiring example for STEMlab 125-14 & STEMlab 125-10:

.. figure:: img/Set_analog_voltage_on_slow_analog_input1.png

Circuit
=========

.. figure:: img/Set_analog_voltage_on_slow_analog_input_circuit1.png


SCPI Code Examples
====================

Code - MATLAB®
----------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab 

    function sliderDemo

        f = figure(1);
        global p;
        
        
        %// initialize the slider
        h = uicontrol(...
            'parent'  , f,...        
            'units'   , 'normalized',...     %// pixels settings
            'style'   , 'slider',...
            'position', [0.05 0.05 0.9 0.05],...
            'min'     , 1,...                %// Make the "value" between min ...
            'max'     , 100,...              %// max 10, with initial value
            'value'   , 10,...               %// as set.
            'callback', @sliderCallback);    %// This is called when using the
                                            %// arrows
                                            %// and/or when clicking the slider bar

        hLstn = addlistener(h,'ContinuousValueChange',@sliderCallback);
        %// (variable appears unused, but not assigning it to anything means that
        %// the listener is stored in the 'ans' variable. If "ans" is overwritten,
        %// the listener goes out of scope and is thus destroyed, and thus, it no
        %// longer works.

        function  sliderCallback(~,~)
    
            p =(get(h,'value'))

            %% Define Red Pitaya as TCP/IP object

            IP = '192.168.178.108';           % Input IP of your Red Pitaya...
            port = 5000;
            RP = tcpclient(IP, port);

            %% Open connection with your Red Pitaya

            RP.ByteOrder = "big-endian";
            configureTerminator(RP,"CR/LF");

            %% Set your output voltage value and pin

            out_voltage = num2str((1.8/100)*p)      % From 0 - 1.8 volts
            out_num = '2';                          % Analog outputs 0,1,2,3
            %% Set your SCPI command with strcat function

            scpi_command = strcat('ANALOG:PIN AOUT',out_num,',',out_voltage);

            %% Send SCPI command to Red Pitaya

            writeline(RP, scpi_command);

            %% Close connection with Red Pitaya

            clear RP;
        end
    end


Code - LabVIEW
----------------

.. figure:: img/Interactive-voltage-setting-on-slow-analog-output_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Interactive%20voltage%20setting%20on%20slow%20analog%20output.vi>`_


API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information is :ref:`here <comC>`.

.. Code - C API
.. ---------------

.. code-block:: c


Code - Python API
------------------

.. code-block:: python

    #!/usr/bin/python3
    import time
    import rp

    analog_out = [rp.RP_AOUT0, rp.RP_AOUT1, rp.RP_AOUT2, rp.RP_AOUT3]
    out_voltage = [1.0, 1.0, 1.0, 1.0]
    is_float = True

    # Initialize the interface
    rp.rp_Init()

    # Reset analog pins
    rp.rp_ApinReset()

    #####! Choose one of two methods, comment the other !#####
    while 1:
        out_voltage = input("Enter Values of 4 analog inputs: ").split()     # Split input

        for i in range(4):
            try:
                # Try to convert input to float
                float(out_voltage[i])
            except ValueError:
                is_float = False      # set flag to false if the conversion fails
            else:
                is_float = True
                out_voltage[i] = float(out_voltage[i])  # convert input string to float

                if not 0 <= out_voltage[i] <= 1.8:   # Check for value out of bounds
                    out_voltage[i] = 1.0

        if is_float:              # If input is float
            for i in range(4):
                #! METHOD 1: Configuring specific Analog pin
                rp.rp_ApinSetValue(analog_out[i], out_voltage[i])
                print (f"Set voltage on AO[{i}] to {out_voltage[i]} V")

                #! METHOD 2: Configure just slow Analog outputs
                rp.rp_AOpinSetValue(i, out_voltage[i])
                print (f"Set voltage on AO[{i}] to {out_voltage[i]} V")
        else:
            print("Invalid input")
        time.sleep(0.2)

    # Release resources
    rp.rp_Release()


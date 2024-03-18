Push button and turn on LED diode
##########################################

.. `Push button and turn on LED diode <http://blog.redpitaya.com/examples-new/push-button-and-turn-on-led-diode/>`_


Description
=============

This example shows how to control Red Pitaya onboard LEDs and read the states of extension connector GPIOs.
When the button is pressed, the LED will turn on.

Required hardware
===================

    - Red Pitaya device
    - Push button
    - Resistor 1k
    - RedPitaya_Push_button

Wiring example for STEMlab 125-14 & STEMlab 125-10:

.. figure:: img/RedPitaya_Push_button.png

Circuit

.. figure:: img/RedPitaya_Push_button_circuit.png


SCPI Code Examples
====================

Code - MATLAB®
---------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Define Red Pitaya as TCP/IP object
            
    IP= '192.168.178.56';           % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya

    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');

    writeline(RP,'DIG:PIN:DIR IN,DIO5_N');      % Set DIO5_N  to be input

    i = 1;

    while i < 1000                    		    % You can set while 1 for a continuous loop
        state = str2num(writeread(RP,'DIG:PIN? DIO5_N'));

        if state==1
            writeline(RP,'DIG:PIN LED5,0');
        end

        if state==0
            writeline(RP,'DIG:PIN LED5,1');
        end
        pause(0.1)                     				% Set time delay for Red Pitaya response
        i = i+1;
    end

    %% Close connection with Red Pitaya
    clear RP;


Code - Python
--------------

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import redpitaya_scpi as scpi

    IP = 'rp-f066c8.local'
    rp_s = scpi.scpi(IP)

    # set all DIO*_N pins to inputs
    for i in range(8):
        rp_s.tx_txt('DIG:PIN:DIR IN,DIO'+str(i)+'_N')

    # copy DIOi_N pin state to LEDi state fir each i [0:7]
    while 1:
        for i in range(8):
            rp_s.tx_txt('DIG:PIN? DIO'+str(i)+'_N')
            state = rp_s.rx_txt()
            rp_s.tx_txt('DIG:PIN LED'+str(i)+','+str(state))

    rp_s.close()


Code - LabVIEW
---------------

.. figure:: img/Push-button-and-turn-on-LED_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Push%20button%20and%20turn%20on%20LED.vi>`_


API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead, the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information are :ref:`here <comC>`.

Code - C API
------------

.. code-block:: c

    #include <stdio.h>
    #include <stdlib.h>
    #include "rp.h"

    int main (int argc, char **argv) {
        rp_pinState_t state;

        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }

        // configure DIO[0:7]_N to inputs
        for (int i=0; i<8; i++) {
            rp_DpinSetDirection (i+RP_DIO0_N, RP_IN);
        }

        // transfer each input state to the corresponding LED state
        while (1) {
            for (int i=0; i<8; i++) {
                rp_DpinGetState (i+RP_DIO0_N, &state);
                rp_DpinSetState (i+RP_LED0, state);
            }
        }

        // Releasing resources
        rp_Release();

        return EXIT_SUCCESS;
    }


Code - Python API
------------------

.. code-block:: python

    #!/usr/bin/python3

    import time
    import rp
    
    # Initialize the interface
    rp.rp_Init()
    
    #####! Choose one of two methods, comment the other !#####
    
    #! METHOD 1: Interacting with Registers direclty
    
    diox_n = [0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000]
    led = 0
    
    # Set all DIO*_N pins to inputs
    rp.rp_GPIOnSetDirection(0b00000000)     # 0 == input, 1 == output
    
    # Transfer each digital input state to the corresponding LED
    # Please note that Red Pitaya GPIOs default to HIGH state when left floating.
    while 1:
        led = 0
    
        state = rp.rp_GPIOnGetState()[1]        # Get DIO_N input register
    
        for i in range(8):
            led += (state & diox_n[i])          # isolate each DIOx_N input and add the value to LEDs (bitwise AND)
        rp.rp_LEDSetState(led)
        time.sleep(0.2)
    
    
    #! METHOD 2: Using Macros
    
    diox_n = [rp.RP_DIO0_N, rp.RP_DIO1_N, rp.RP_DIO2_N, rp.RP_DIO3_N, rp.RP_DIO4_N, rp.RP_DIO5_N, rp.RP_DIO6_N, rp.RP_DIO7_N]
    led_array = [rp.RP_LED0, rp.RP_LED1, rp.RP_LED2, rp.RP_LED3, rp.RP_LED4, rp.RP_LED5, rp.RP_LED6, rp.RP_LED7]
    
    for i in range(8):
        rp.rp_DpinSetDirection(diox_n[i], rp.RP_IN)
    
    while 1:
        for i in range(8):
            state = rp.rp_DpinGetState(diox_n[i])[1]        # Get state of DIOx_N
            rp.rp_DpinSetState(led_array[i], state)         # Transfer state to the corresponding LED
        time.sleep(0.2)
    
    
    # Release resources
    rp.rp_Release()



Push button and turn on LED diode
#################################

.. `Push button and turn on LED diode <http://blog.redpitaya.com/examples-new/push-button-and-turn-on-led-diode/>`_


Description
***********

This example shows how to control Red Pitaya onboard LEDs and read the states of extension connector GPIOs.
When the button is pressed, the LED will turn on.

Required hardware
*****************

    - Red Pitaya device
    - Push button
    - Resistor 1K
    - RedPitaya_Push_button

Wiring example for STEMlab 125-14 & STEMlab 125-10:

.. figure:: RedPitaya_Push_button.png

Circuit

.. figure:: RedPitaya_Push_button_circuit.png

Code - MATLAB®
**************

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

    while i<1000                    			% You can set while 1 for continuous loop

    state = str2num(writeread(RP,'DIG:PIN? DIO5_N'));

        if state==1
        
            writeline(RP,'DIG:PIN LED5,0');
            
        end

        if state==0

            writeline(RP,'DIG:PIN LED5,1');

        end

    pause(0.1)                     				% Set time delay for Red Pitaya response

    i = i+1

    end

    %% Close connection with Red Pitaya
    clear RP;

Code - C
********

.. note::

    Although the C code examples don't require the use of the SCPI server, we have included them here to demonstrate how the same functionality can be achieved with different programming languages. 
    Instructions on how to compile the code are :ref:`here <comC>`.

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


Code - Python
*************

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi(sys.argv[1])

    # set all DIO*_N pins to inputs
    for i in range(8):
        rp_s.tx_txt('DIG:PIN:DIR IN,DIO'+str(i)+'_N')

    # copy DIOi_N pin state to LEDi state fir each i [0:7]
    while 1:
        for i in range(8):
            rp_s.tx_txt('DIG:PIN? DIO'+str(i)+'_N')
            state = rp_s.rx_txt()
            rp_s.tx_txt('DIG:PIN LED'+str(i)+','+str(state))


Code - LabVIEW
**************

.. figure:: Push-button-and-turn-on-LED_LV.png

`Dowload <https://downloads.redpitaya.com/downloads/Clients/labview/Push%20button%20and%20turn%20on%20LED.vi>`_

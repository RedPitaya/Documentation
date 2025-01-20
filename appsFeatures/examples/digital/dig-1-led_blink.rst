.. _blink:

Blink
#####

Description
===========

This example shows how to control one of the Red Pitaya on-board LEDs and make it blink.


Required hardware
==================

    - Red Pitaya device

.. figure:: img/redpitaya_led0_blink.gif


Required software
==================

.. include:: ../sw_requirement.inc


SCPI Code Examples
====================

Code - MATLAB ®
----------------

.. include:: ../matlab.inc

.. code-block:: matlab

    %% Define Red Pitaya as TCP/IP object

    IP = ('rp-f0a235.local');               % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);               % creates a TCP client object
    
    %% Open connection with your Red Pitaya
    RP.ByteOrder = "big-endian";
    configureTerminator(RP, 'CR/LF');       % defines the line terminator (end sequence of input characters)
    
    %% Send SCPI command to Red Pitaya to turn ON LED1
    for i=1:5
        writeline(RP,'DIG:PIN LED1,1');     % Peripheral_Unit: Unit_Part/function:subfunction/settings 
        % readline()                        % reading data
        % writeread()                       % send a command and read the reply
    
        pause(1);                           % Set time of LED ON
    
        % Send SCPI command to Red Pitaya to turn OFF LED1
        writeline(RP,'DIG:PIN LED1,0');
    
        % other possible commands:
        % DIG:PIN:DIR <dir>,<gpio>
        % DIG:PIN <pin>,<state>
        % DIG:PIN? <pin> => <state>         % Acquire status or read data
    
        pause(1);
    end
    %% Close connection with Red Pitaya
    
    clear RP;


Code - Python
--------------

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import time
    import redpitaya_scpi as scpi

    IP = 'rp-f066c8.local'
    rp_s = scpi.scpi(IP)

    if (len(sys.argv) > 2):
        led = int(sys.argv[2])
    else:
        led = 0

    print ("Blinking LED["+str(led)+"]")

    period = 1 # seconds

    while 1:
        time.sleep(period/2.0)
        rp_s.tx_txt('DIG:PIN LED' + str(led) + ',' + str(1))
        time.sleep(period/2.0)
        rp_s.tx_txt('DIG:PIN LED' + str(led) + ',' + str(0))

    rp_s.close()

.. include:: ../python_scpi_note.inc


Code - Scilab
--------------

.. code-block:: scilab

    clc

    // Load SOCKET Toolbox. Steps 7&8
    exec(SCI+'contribsocket_toolbox_2.0.1loader.sce'); 
    SOCKET_init();

    IP = '192.168.128.1';
    port = 5000;
    tcpipObj ='RedPitaya';

    SOCKET_open(tcpipObj, IP, port);

    SOCKET_write(tcpipObj, 'DIG:PIN LED1,1');
    xpause(5*1E+6)
    SOCKET_write(tcpipObj, 'DIG:PIN LED1,0');

    SOCKET_close(tcpipObj);


Code - LabVIEW
----------------

.. figure:: img/Blink_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Blink.vi>`_


API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C API
-------------

.. code-block:: c

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "rp.h"

    int main (int argc, char **argv) {
        int unsigned period = 1000000; // uS
        int unsigned led;

        // index of blinking LED can be provided as an argument
        if (argc > 1) {
            led = atoi(argv[1]);
        // otherwise LED 0 will blink
        } else {
            led = 0;
        }
        printf("Blinking LED[%u]\n", led);
        led += RP_LED0;

        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }

        int unsigned retries = 1000;
        while (retries--){
            rp_DpinSetState(led, RP_HIGH);
            usleep(period/2);
            rp_DpinSetState(led, RP_LOW);
            usleep(period/2);
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

    period = 1      # period in secodns

    # Initialize the interface
    rp.rp_Init()

    #####! Choose one of two methods, comment the other !#####
    #! METHOD 1: Interacting with Registers direclty
    while 1:
        time.sleep(period/2.0)
        rp.rp_LEDSetState(0b00000001)     # or 0b00000001
        time.sleep(period/2.0)
        rp.rp_LEDSetState(0b00000000)     # or 0


    #! METHOD 2: Using Macros
    while 1:
        time.sleep(period/2.0)
        rp.rp_DpinSetState(rp.RP_LED0, rp.RP_HIGH)
        time.sleep(period/2.0)
        rp.rp_DpinSetState(rp.RP_LED0, rp.RP_LOW)

    # Release resources
    rp.rp_Release()



Set analog voltage on a slow analog output
##########################################

.. http://blog.redpitaya.com/examples-new/set-analog-voltage-on-slow-analog-output-4/


Description
=============

This example shows how to set the analog voltage of slow analog outputs on the Red Pitaya extension connector. Slow analog outputs on the Red Pitaya are in the range of 0 to 1.8 Volts.

Required hardware
===================

    - Red Pitaya device
    - Voltmeter
    
Wiring example for STEMlab 125-14 & STEMlab 125-10:

.. figure:: img/Set_analog_voltage_on_slow_analog_input1.png


Required software
===================

.. include:: ../sw_requirement.inc


Circuit
========

.. figure:: img/Set_analog_voltage_on_slow_analog_input_circuit1.png


SCPI Code Examples
====================

Code - MATLAB®
---------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

.. code-block:: matlab

    %% Define Red Pitaya as TCP client object
    IP= '192.168.178.108';          % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya

    RP.ByteOrder = "big-endian";
    configureTerminator(RP,"CR/LF");

    writeline(RP,'ANALOG:PIN AOUT0,0.3');  % 0.3 Volts is set on output 0
    writeline(RP,'ANALOG:PIN AOUT1,0.9');
    writeline(RP,'ANALOG:PIN AOUT2,1');
    writeline(RP,'ANALOG:PIN AOUT3,1.5');

    clear RP;


Code - Python
--------------

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import redpitaya_scpi as scpi

    IP = 'rp-f066c8.local'

    rp_s = scpi.scpi(IP)

    value = [1,1,1,1]
    for i in range(4):
        if len(sys.argv) > (i+2):
            value[i] = sys.argv[i+2]
        print ("Voltage setting for AO["+str(i)+"] = "+str(value[i])+"V")

    for i in range(4):
        rp_s.tx_txt('ANALOG:PIN AOUT' + str(i) + ',' + str(value[i]))

    rp_s.close()


Code - LabVIEW
---------------

.. figure:: img/Set-analog-voltage-on-slow-analog-output_LV.png

- `Download Example <https://downloads.redpitaya.com/downloads/Clients/labview/Set%20analog%20voltage%20on%20slow%20analog%20output.vi>`_



API Code Examples
====================

.. include:: ../c_code_note.inc
    

Code - C API
---------------

.. code-block:: c

    /* Set analog voltage on slow analog output */

    #include <stdio.h>
    #include <stdlib.h>

    #include "rp.h"

    int main (int argc, char **argv) {
        float value [4];

        // Voltages can be provided as an argument (default is 1 V)
        for (int i=0; i<4; i++) {
            if (argc > (1+i)) {
                value [i] = atof(argv[1+i]);
            } else {
                value [i] = 1.0;
            }
            printf("Voltage setting for AO[%i] = %1.1fV\n", i, value [i]);
        }

        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }

        // Setting a voltage for each ananlog output
        for (int i=0; i<4; i++) {
            int status = rp_AOpinSetValue(i, value[i]);
            if (status != RP_OK) {
                printf("Could not set AO[%i] voltage.\n", i);
            }
        }

        // wait for user input
        getchar();

        // Releasing resources
        rp_Release();

        return EXIT_SUCCESS;
    }


Code - Python API
------------------

.. code-block:: python

    #!/usr/bin/python3
    import rp

    analog_out = [rp.RP_AOUT0, rp.RP_AOUT1, rp.RP_AOUT2, rp.RP_AOUT3]
    out_voltage = [1.0, 1.0, 1.0, 1.0]

    # Initialize the interface
    rp.rp_Init()

    # Reset analog pins
    rp.rp_ApinReset()

    #####! Choose one of two methods, comment the other !#####

    #! METHOD 1: Configuring specific Analog pin
    for i in range(4):
        rp.rp_ApinSetValue(analog_out[i], out_voltage[i])
        print (f"Set voltage on AO[{i}] to {out_voltage[i]} V")


    #! METHOD 2: Configure just slow Analog outputs
    for i in range(4):
        rp.rp_AOpinSetValue(i, out_voltage[i])
        print (f"Set voltage on AO[{i}] to {out_voltage[i]} V")

    # Release resources
    rp.rp_Release()


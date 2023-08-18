.. _click_shield_motion:

#####################
Motion Click Board
#####################

Description
============

This is an example of using Red Pitaya with the Red Pitaya Click Shield and Motion Click Board.
If the sensor detects motion, a message is displayed in the command line and LED 0 on the Red Pitaya is turned OFF.


Required hardware
==================

    -   Red Pitaya device
    -   Red Pitaya Click Shield
    -   Motion click board


Code C
=======

The code should be copied to the Red Pitaya using the *"scp"* or similar command and compiled on the board.

.. note::

    Instructions on how to compile the code are :ref:`here <comC>`.


.. code-block:: C

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "rp.h"
    
    // Choose a microbus depending on where the click board is   
    #define mikrobus1IntPin RP_DIO2_P    // Microbus 1
    #define mikrobus2IntPin RP_DIO4_P    // Microbus 2

    
    int main (int argc, char **argv) {
        rp_pinState_t state;
    
        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
        
        rp_DpinSetDirection (mikrobus1IntPin, RP_IN);
        
        while(1){
            // Get button value
            rp_DpinGetState(mikrobus1IntPin, &state);
          
            if (state == RP_HIGH){
                // Turn LED 0 ON if no motion is detected
                rp_DpinSetState(RP_LED0, RP_HIGH);  
                printf("There is no motion.\n");
            }
            else{
                // Turn LED 0 OFF if motion is detected
                rp_DpinSetState(RP_LED0, RP_LOW);
                printf("There is motion.\n");
            }
            usleep(1000000);
    
        }
    
        // Releasing resources
        rp_Release();
    
        return EXIT_SUCCESS;
    }

Code written by Žiga Fon

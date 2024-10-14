.. _click_shield_relay:

#####################
Relay Click Board
#####################

Description
============

This is an example of using Red Pitaya with the Red Pitaya Click Shield and Relay Click Board.
The two relays on the click board can be closed on command. Consequently, the LEDs are turned ON on the Red Pitaya.


Required hardware
==================

    -   Red Pitaya device
    -   Red Pitaya Click Shield
    -   Relay click board

Required software
==================

.. include:: ../../../sw_requirement.inc


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
    #define MIKROBUS 1    // 1 == Microbus 1, 2 == Microbus 2
    
    #if MIKROBUS == 1
        #define RL1_PIN RP_DIO1_P    // Microbus 1
        #define RL2_PIN RP_DIO3_P
    #else
        #define RL1_PIN RP_DIO1_N    // Microbus 2
        #define RL2_PIN RP_DIO3_N
    #endif
    
    int main (int argc, char **argv) {
       
    
        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
    
        // configure DIO[0:1]_N to outputs
        rp_DpinSetDirection (RL1_PIN, RP_OUT);    
        rp_DpinSetDirection (RL2_PIN, RP_OUT);
    
           
    
        // transfer each input state to the corresponding LED state
        while (1) {
            rp_DpinSetState (RP_LED0, 1); 
            rp_DpinSetState (RL1_PIN, 1);
            rp_DpinSetState (RL2_PIN, 1);
            usleep(1000000);     // 10e6 uS = 1s
            rp_DpinSetState (RP_LED0, 0); 
            rp_DpinSetState (RL1_PIN, 0);
            rp_DpinSetState (RL2_PIN, 0);
            usleep(1000000);
        }
    
        // Releasing resources
        rp_Release();
        return EXIT_SUCCESS;
    }

Code made by Žiga Fon.

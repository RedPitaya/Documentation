.. _click_shield_current:

#####################
Current Click Board
#####################

Description
============

This is an example of using Red Pitaya with the Red Pitaya Click Shield and Current Click Board.
The example demonstrates how to measure the current through a shunt resistor.


Required hardware
==================

    -   Red Pitaya device
    -   Red Pitaya Click Shield
    -   Current click board


Required software
==================

.. include:: ../sw_requirement.inc


Code C
=======

The code should be copied to the Red Pitaya using the *"scp"* or similar command and compiled on the board.

.. note::

    Instructions on how to compile the code are :ref:`here <comC>`.


.. code-block:: C

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <time.h>
  
    #include "rp.h"

    // Choose a microbus depending on where the click board is
    #define MIKROBUS 1    // 1 == Microbus 1, 2 == Microbus 2
    
    #if MIKROBUS == 1
        #define AIN_PIN 0    // Microbus 1
    #else
        #define AIN_PIN 1    // Microbus 2
    #endif


    void convertToEngineeringUnit(double number) {
        const char* units[] = {"A", "mA", "μA", "nA"};
        double magnitude = number;
        int unitIndex = 0;
    
        while (magnitude <= 1.0 && unitIndex < 3) {
            magnitude *= 1000.0;
            unitIndex++;
        }
    
        printf("Current:%lf %s\n", magnitude, units[unitIndex]);
    }


    double get_current(int pin_name, float resistor_value) {
       
        // Get ADC value from the specified pin
        float value;
    
        rp_AIpinGetValue(pin_name, &value);
        double max_current = 3.3/(20.0 * resistor_value);
        printf("Min current is 2 mA, maximum is "  );
        convertToEngineeringUnit(max_current);
        
        // Calculate current
        float voltage = value / 20.0;    // gain of circuit is 20
        double current = voltage / (resistor_value);
        
        return current;
    }
    
    float recommendResistor(float current) {
    
        if (current != 0) {
            float resistor = 0.075 / current;
            printf("The recommended resistor value for best measurement (R) is %.2f ohms.\n", resistor);
            return resistor;
        }
        else {
            printf("Error: Current (I) cannot be zero.\n");
            return -1;     // Return -1 to indicate an error
        }
    }
    
    int main (int argc, char **argv) {
        
        float resistor_value ; 
    
        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
    
    
        while(1){
          printf("Enter the value of your resistor in ohms: ");    // circuit 5 Ohms
      
          scanf("%f", &resistor_value);    // 5
          float current = get_current(AIN_PIN, resistor_value); 
          
          convertToEngineeringUnit(current);
          recommendResistor(current);
          usleep(1000000);
        }
        // Releasing resources
        rp_Release();
    
    
        return EXIT_SUCCESS;
    }

Code written by Žiga Fon.

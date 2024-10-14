.. _click_shield_dcmotor:

########################
DC Motor 2 Click Board
########################

Description
============

This is an example of using Red Pitaya with the Red Pitaya Click Shield and DC Motor 2 Click Board.
The program is used to control the DC motor.


Required hardware
==================

    -   Red Pitaya device
    -   Red Pitaya Click Shield
    -   DC Motor 2 click board


Required software
=================

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
    #include <string.h>
    
    #include "rp.h"
        
    // Choose a microbus depending on where the click board is
    #define MIKROBUS 1    // 1 == Microbus 1, 2 == Microbus 2
    
    #if MIKROBUS == 1
        #define PWM_PIN RP_DIO1_P    // Microbus 1
        #define IN1_PIN RP_DIO1_N
        #define IN2_PIN RP_DIO2_N
        #define SLP_PIN RP_DIO2_P
    #else
        #define PWM_PIN RP_DIO3_P    // Microbus 2
        #define IN1_PIN RP_DIO3_N
        #define IN2_PIN RP_DIO4_N
        #define SLP_PIN RP_DIO4_P
    #endif
      
        
    void pwm(int pin, int duty_cycle,int num_seconds) 
    {   
        int period_us = 875;
        int num_periods = 0;
        int pulse_us = (duty_cycle * period_us) / 100;
        
        rp_DpinSetDirection(pin, RP_OUT);    // Set pin as output
    
        while (num_periods !=  num_seconds *1000 ) {
            rp_DpinSetState(pin, RP_HIGH);  // Set pin state high
            usleep(pulse_us);               // Delay for pulse duration
    
            rp_DpinSetState(pin, RP_LOW);    // set pin state low
            usleep(period_us - pulse_us);    // delay for the remaining period
    
            num_periods++;                   // increment the number of periods
            }
    }
        
    void pwm_sweep(int pin, int sweep_time, const char* up_or_down) 
    {   
        int period_us = 875;
        int num_steps = sweep_time * 1000;   // Convert sweep time to milliseconds
        
        rp_DpinSetDirection(pin, RP_OUT);    // Set pin as output
    
        // Increase or decrease speed
        if (strcmp(up_or_down, "up") == 0){
            // The motor starts spinning at 15% (0.15)
            for (int i = 0.15 * num_steps; i <= num_steps; i++) {
                int duty_cycle = (i * 100) / num_steps;           // percentage of power,  0 to 100
                int pulse_us = (duty_cycle * period_us) / 100;
            
                rp_DpinSetState(pin, RP_HIGH);  // Set pin state high
                usleep(pulse_us);               // Delay for pulse duration
        
                rp_DpinSetState(pin, RP_LOW);    // set pin state low
                usleep(period_us - pulse_us);    // delay for the remaining period
            }
        }
        else{
            // The motor starts spinning at 15% (0.15)
            for (int i = num_steps; i >= 0.15 * num_steps ; i--) {
                int duty_cycle = (i * 100) / num_steps;         // percentage of power,  0 to 100
                int pulse_us = (duty_cycle * period_us) / 100;
            
                rp_DpinSetState(pin, RP_HIGH);  // Set pin state high
                usleep(pulse_us);               // Delay for pulse duration
        
                rp_DpinSetState(pin, RP_LOW);    // set pin state low
                usleep(period_us - pulse_us);    // delay for the remaining period
            }
        }
    }
        
    void setMotorMode(const char* motorMode) {
    
        if (strcmp(motorMode, "MODE_CCW") == 0) {
            rp_DpinSetState(IN1_PIN, RP_LOW);
            rp_DpinSetState(IN2_PIN, RP_HIGH);
            rp_DpinSetState(SLP_PIN, RP_HIGH);
        } else if (strcmp(motorMode, "MODE_CW") == 0) {
            rp_DpinSetState(IN1_PIN, RP_HIGH);
            rp_DpinSetState(IN2_PIN, RP_LOW);
            rp_DpinSetState(SLP_PIN, RP_HIGH);
        } else if (strcmp(motorMode, "MODE_STOP") == 0) {
            rp_DpinSetState(IN1_PIN, RP_LOW);
            rp_DpinSetState(IN2_PIN, RP_LOW);
            rp_DpinSetState(SLP_PIN, RP_HIGH);
        } else if (strcmp(motorMode, "MODE_STANDBY") == 0) {
            rp_DpinSetState(IN1_PIN, RP_LOW);
            rp_DpinSetState(IN2_PIN, RP_LOW);
            rp_DpinSetState(SLP_PIN, RP_LOW);
        } else {
            // Handle the default case
        }
    }
    
        
    int main (int argc, char **argv) {
    
        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
    
        // Set digital pins as outputs
        rp_DpinSetDirection(IN1_PIN, RP_OUT);
        rp_DpinSetDirection(IN2_PIN, RP_OUT);
        rp_DpinSetDirection(SLP_PIN, RP_OUT);
    
        // Set motor direction
        setMotorMode("MODE_CCW");
        
        pwm_sweep(PWM_PIN, 10, "up");      // set sweep ramp up to 10 seconds
        pwm_sweep(PWM_PIN, 10, "down");    // set motor to increase speed (up) or decrease it
    
        while(1){
            
            setMotorMode("MODE_CCW");       // Set motor mode to counter-clockwise
            pwm(PWM_PIN, 50, 3);            // Run motor at 50% duty cycle for 3 seconds
          
            setMotorMode("MODE_STOP");      // Set motor mode to stop
          
            pwm(PWM_PIN, 50, 3);            // Run motor at 50% duty cycle for 3 seconds
    
            setMotorMode("MODE_CW");        // Set motor mode to clockwise
            pwm(PWM_PIN, 50, 3);            // Run motor at 50% duty cycle for 3 seconds
    
            setMotorMode("MODE_STANDBY");   // Set motor mode to standby
            pwm(PWM_PIN, 50, 3);            // Run motor at 50% duty cycle for 3 seconds
        }
    
        // Releasing resources
        rp_Release();
    
        return EXIT_SUCCESS;
    }

Code written by Žiga Fon.

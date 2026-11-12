.. _click_shield_button:

#####################
Button G Click Board
#####################

说明
============

本示例演示如何将 Red Pitaya 与 Red Pitaya Click Shield 和 Button G Click Board 配合使用。
按下 Click Board 上的 G 按钮后，Red Pitaya 上的 LED 会亮起。


所需硬件
==================

    -   Red Pitaya 设备
    -   Red Pitaya Click Shield
    -   Button G Click Board


所需软件
=================

.. include:: ../../../sw_requirement.inc


代码 C
=======

应使用 *"scp"* 或类似命令将代码复制到 Red Pitaya，并在板卡上编译。

.. note::

    有关如何编译代码的说明请参阅 :ref:`此处 <comC>`。


.. code-block:: C

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    #include "rp.h"
    
    
    // Choose a microbus depending on where the click board is
    #define MIKROBUS 1
    
    #if MIKROBUS == 1
        #define INT_PIN RP_DIO2_P    // Microbus 1
        #define PWM_PIN RP_DIO1_P
    #else
        #define INT_PIN RP_DIO4_P    // Microbus 2
        #define PWM_PIN RP_DIO3_P
    #endif
    
    
    void pwm(int pin, int duty_cycle, float num_seconds){   
        int period_us = 875;
        int num_periods = 0;
        int pulse_us = (duty_cycle * period_us) / 100;
        
        // configure pin as output
        rp_DpinSetDirection(pin, RP_OUT);
    
        while (1) {
    
            // check for end condition (here, 100 periods)  100
            if (num_periods == num_seconds * 1000) {
                break;
            }
        
            rp_DpinSetState(pin, RP_HIGH);  // Set pin state high
            usleep(pulse_us);               // Delay for pulse duration
    
            rp_DpinSetState(pin, RP_LOW);    // set pin state low
            usleep(period_us - pulse_us);    // delay for the remaining period
    
            num_periods++;                   // increment the number of periods
        }
    }
    
    
    int main (int argc, char **argv) {
        rp_pinState_t state;
    
        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
    
        // configure pin as input
        rp_DpinSetDirection (INT_PIN, RP_IN);
        
        //getting the value of the INT pin
        while(1){
            // Get button value
            rp_DpinGetState(INT_PIN, &state);
            if (state == RP_HIGH){
                // Turn the light ON/OFF based on the button value
                rp_DpinSetState(RP_LED0, state);
                //pin name, strength in power %, length of turn on
                pwm(PWM_PIN, 100, 0.1);
            }
            else{
                // Turn the light ON/OFF based on the button value
                rp_DpinSetState(RP_LED0, state); 
                pwm(PWM_PIN, 0, 0.1);
            }
        }
    
        // Releasing resources
        rp_Release();
    
        return EXIT_SUCCESS;
    }

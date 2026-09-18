.. _click_shield_vibromotor:

#########################
Vibro Motor Click Board
#########################

描述
============

本示例演示如何将 Red Pitaya 与 Red Pitaya Click Shield 和 Vibro Motor Click Board 配合使用。
程序会使 Click Shield 和 Red Pitaya 振动。振动强度由 *pwm* 函数设置。


所需硬件
==================

    -   Red Pitaya 设备
    -   Red Pitaya Click Shield
    -   Vibro Motor Click Board


所需软件
===================

.. include:: ../../../sw_requirement.inc
    

代码 C
=======

应使用 *"scp"* 或类似命令将代码复制到 Red Pitaya，然后在板卡上编译。

.. note::

    有关如何编译代码的说明请参阅 :ref:`此处 <comC>`。


.. code-block:: C

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    #include "rp.h"
    
    
    #define MIKROBUS 1
    
    // Choose a microbus depending on where the click board is
    #if MIKROBUS == 1           // 1 == Microbus 1, 2 == Microbus 2
        #define PWM_PIN RP_DIO1_P
    #else
        #define PWM_PIN RP_DIO3_P
    #endif
    
    
    void pwm(int pin, int duty_cycle,int num_seconds) 
    {   
        int period_us = 875;
        int num_periods = 0;
        int pulse_us = (duty_cycle * period_us) / 100;
        
        // set pin as output
        rp_DpinSetDirection(pin, RP_OUT);
    
        while (1) {
    
            // check for end condition (here, 100 periods)  100
            if (num_periods ==  num_seconds *1000 ) {
                break;
            }
        
            rp_DpinSetState(pin, RP_HIGH);      // set pin state high
            usleep(pulse_us);       // delay for pulse duration
            rp_DpinSetState(pin, RP_LOW);       // set pin state low
            usleep(period_us - pulse_us);       // delay for remaining period
            num_periods++;          // increment number of periods
        }
    }
    
    int main (int argc, char **argv) {
    
        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
     
        // run motor at 50% duty cycle for 3 seconds
        pwm(PWM_PIN, 50, 3);
        // the motor doesn't run at less than 30% power
    
        // Releasing resources
        rp_Release();
    
        return EXIT_SUCCESS;
    }

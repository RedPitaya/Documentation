.. _click_shield_light:

#####################
Light Click Board
#####################

描述
============

本示例演示如何将 Red Pitaya 与 Red Pitaya Click Shield 和 Light Click Board 配合使用。
测量光强，并通过命令提示符输出消息。


所需硬件
==================

    -   Red Pitaya 设备
    -   Red Pitaya Click Shield
    -   Light Click Board


所需软件
==================

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

    // Choose a microbus depending on where the click board is
    #define MIKROBUS 1    // 1 == Microbus 1, 2 == Microbus 2
    
    #if MIKROBUS == 1
        #define AIN_PIN 0    // Microbus 1
    #else
        #define AIN_PIN 1    // Microbus 2
    #endif


    int main (int argc, char **argv) {
      
        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
    
        while(1){
        
            float value;
      
            // Get light value
            rp_AIpinGetValue(AIN_PIN, &value);
            printf("Measured voltage on AI[%i] = %1.2fV\n", 0, value);
            
            if (value >= 2.0){
                // Turn ON an LED based on the measured light intensity
                rp_DpinSetState(RP_LED0, RP_HIGH);  
                printf("There is LIGHT\n");
            }
            else if (value <= 0.5){
                // Turn OFF an LED based on the measured light intensity
                rp_DpinSetState(RP_LED0, RP_LOW);
                printf("There is no light\n");
            }
            else{
                printf("There is some light\n");
            }
            usleep(1000000);
        }
    
        // Releasing resources
        rp_Release();
    
        return EXIT_SUCCESS;
    }

.. _click_shield_relay:

#####################
继电器 Click 板
#####################

描述
============

本示例演示如何将 Red Pitaya 与 Red Pitaya Click Shield 和继电器 Click 板配合使用。
Click 板上的两个继电器可按命令闭合，从而点亮 Red Pitaya 上的 LED。


所需硬件
==================

    -   Red Pitaya 设备
    -   Red Pitaya Click Shield
    -   继电器 Click 板

所需软件
==================

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

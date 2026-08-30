.. _click_shield_motion:

#####################
Motion Click Board
#####################

描述
============

本示例演示如何将 Red Pitaya 与 Red Pitaya Click Shield 和 Motion Click Board 配合使用。
如果传感器检测到运动，命令行会显示消息，并且 Red Pitaya 上的 LED 0 会关闭。


所需硬件
==================

    -   Red Pitaya 设备
    -   Red Pitaya Click Shield
    -   Motion Click Board

所需软件
=================

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
        #define INT_PIN RP_DIO2_P    // Microbus 1
    #else
        #define INT_PIN RP_DIO4_P    // Microbus 2
    #endif

    int main (int argc, char **argv) {
        rp_pinState_t state;

        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }

        rp_DpinSetDirection (INT_PIN, RP_IN);

        while(1){
            // Get button value
            rp_DpinGetState(INT_PIN, &state);

            if (state == RP_HIGH){
                // Turn LED 0 ON if no motion is detected
                rp_DpinSetState(RP_LED0, RP_HIGH);
                printf("There is no motion.\r");
            }
            else{
                // Turn LED 0 OFF if motion is detected
                rp_DpinSetState(RP_LED0, RP_LOW);
                printf("There is motion.   \r");
            }
            fflush(stdout);
            usleep(100000);

        }

        // Releasing resources
        rp_Release();

        return EXIT_SUCCESS;
    }

.. _click_shield_captouch:

#######################
Cap Touch Click Board
#######################

描述
============

本示例演示如何将 Red Pitaya 与 Red Pitaya Click Shield 和 Cap Touch Click Board 配合使用。
按下 Click Board 上的电容式按钮时，Red Pitaya 上的 LED 会亮起。


所需硬件
==================

    -   Red Pitaya 设备
    -   Red Pitaya Click Shield
    -   Cap Touch Click Board


所需软件
=====================

.. include:: ../../../sw_requirement.inc


代码 C
=======

应使用 *"scp"* 或类似命令将代码复制到 Red Pitaya，然后在板卡上编译。

.. note::

    有关如何编译代码的说明请参阅 :ref:`此处 <comC>`。


.. code-block:: C

    #include <stdio.h>
    #include <stdlib.h>

    #include "rp.h"

    // Choose a microbus depending on where the click board is
    #define MIKROBUS 1    // 1 == Microbus 1, 2 == Microbus 2
    
    #if MIKROBUS == 1
        #define INT_PIN RP_DIO2_P
    #else
        #define INT_PIN RP_DIO4_P
    #endif

  
    int main (int argc, char **argv) {
      rp_pinState_t state;

      // Initialization of API
      if (rp_Init() != RP_OK) {
          fprintf(stderr, "Red Pitaya API init failed!\n");
          return EXIT_FAILURE;
      }
  
      // Configure DIO0_N as input
      rp_DpinSetDirection (INT_PIN, RP_IN);
      
      while(1){
        // Get the button value
        rp_DpinGetState(INT_PIN, &state);
        if (state == RP_HIGH){
          // Turn the light ON/OFF based on the button value
          rp_DpinSetState(RP_LED0, state);
        }
        else{
          // Turn the light ON/OFF based on the button value
          rp_DpinSetState(RP_LED0, state);
        }
    
    
      }
    
      // Releasing resources
      rp_Release();
  
      return EXIT_SUCCESS;
    }

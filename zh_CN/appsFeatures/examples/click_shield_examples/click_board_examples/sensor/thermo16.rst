.. _click_shield_thermo16:

#######################
Thermo 16 Click Board
#######################

描述
============

本示例演示如何将 Red Pitaya 与 Red Pitaya Click Shield 和 Thermo 16 Click Board 配合使用。
程序从传感器读取温度测量值，并在命令行中显示。


所需硬件
==================

    -   Red Pitaya 设备
    -   Red Pitaya Click Shield
    -   Thermo 16 Click Board


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
    #define MIKROBUS 1    // 1 == Microbus 1, 2 == Microbus 2

    #if MIKROBUS == 1
        #define AIN_PIN 0    // Microbus 1
    #else
        #define AIN_PIN 1    // Microbus 2
    #endif
    
    
    float get_average_temperature() {
    
        float values[30];
        float sum = 0.0;
        float average;
        int i;
        
        for (i = 0; i < 30; i++) {
            // read analog input value from Red Pitaya
            rp_AIpinGetValue(AIN_PIN, &values[i]);
            sum += values[i];
            usleep(50000);    /  /0.05 seconds
        }
    
        average = sum / 30.0;
        return (average -0.5-0.03) * 100.0;    //TEMP_IN_CELSIUS;
        
        // standard deviation = ABSOLUTE MISTAKE / Sqrt(3) = 1,25 °C / Sqrt(3) = 0.72 °C
        // with 68% certainty
        // uncertainty due to repeated measurements can be disregarded
    }

    
    int main (int argc, char **argv) {
        float  temperature, correction;
    
        // Initialization of API
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
    
        temperature =  get_average_temperature();
        correction= -9.0;      // add a correction if necessary;
        temperature = temperature + correction;
    
        printf("Measured TEMP_IN_KELVIN = %1.2f°C +- 0.72°C \n",  (temperature + 273.15)   );
        printf("Measured TEMP_IN_FARENHEIT  = %1.2f°F +- 1.3°F \n",  (( temperature * 9.0/5.0 ) + 32.0 )     );
        printf("Measured TEMP_IN_CELSIUS  = %1.2f°C +- 0.72°C\n",  temperature);
    
        // Releasing resources
        rp_Release();
        
        return EXIT_SUCCESS;
    }

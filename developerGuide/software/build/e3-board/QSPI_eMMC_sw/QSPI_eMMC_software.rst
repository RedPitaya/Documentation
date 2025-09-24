.. _E3_QSPI_eMMC_module_SW:

QSPI eMMC module - software
##############################

The QSPI eMMC module provides secure and robust Red Pitaya boot and shutdown options.

|e3_top| |e3_bottom|

.. |e3_top| image:: img/QSPI_eMMC_module_Gen2_top.png
   :width: 600

.. |e3_bottom| image:: img/QSPI_eMMC_module_Gen2_bottom.png
   :width: 600

.. contents::
    :local:
    :depth: 2
    :backlinks: none

|

Features
========

* Single button power on/off of Red Pitaya board.
* QSPI and eMMC boot options.
* An on-board STM microcontroller that provides.

    * Red Pitaya power up.
    * Safe Red Pitaya shutdown.
    * Watchdog timer functionality.
    * Boot media selection (SD card/eMMC).

* Arduino firmware with open source code.
* Connector for 8 high-speed differential lines directly connected to the Zynq FPGA (or 16 GPIOs).

More information about the QSPI eMMC module can be found in the :ref:`hardware section <E3_QSPI_eMMC_module_HW>`.


Software and hardware requirements
====================================

The QSPI eMMC module is designed to be used with the Red Pitaya *STEMlab 125-14 Pro Gen 2* and *STEMlab 125-14 Pro Z7020 Gen 2* boards. It is connected to the Red Pitaya board via the E3 connector. The E3 connector controls the power and booting of the Red Pitaya.
The QSPI eMMC module is powered by the Red Pitaya board, so no additional power supply is needed. To program the QSPI eMMC module you will need the following hardware:

* Red Pitaya STEMlab 125-14 PRO Gen 2 board.
* QSPI eMMC module.

And one of the following:

* ST-Link/V2 programmer and 5 wire 2.54mm pitch to 2.0mm pitch cable (programming via SWD).
* USB to micro USB cable (programming via USB).
* TTL to USB Serial Converter cable (3.3 V) - for example TTL-232R-3V3 (programming through UART - currently not supported).

The ST-Link/V2 programmer is the recommended way to program the QSPI eMMC module. It is a versatile programmer that can be used to program a wide range of STM32 microcontrollers. The USB to micro USB cable can be used to program the QSPI eMMC module via the USB port.
The TTL to USB Serial Converter cable can be used to program the QSPI eMMC module via the UART port, which is not directly accessible on the module.

.. note::

    To test the connection between the QSPI eMMC module and the computer, please attempt to connect to the QSPI eMMC module with the ST-Link/V2 programmer. If the connection is unsuccessful, please check the cables between the module and the computer and try switching the USB port on the computer.


ST-Link/V2 programmer
---------------------

1. Connect the ST-Link/V2 to the computer via the supplied USB cable. A red LED should light up on the programmer.
#. If the drivers are not installed automatically, download and install the drivers from the `ST official website <https://www.st.com/en/development-tools/stsw-link009.html>`_.
#. Connect the 5-wire 2.54mm pitch to 2.0mm pitch cable between the CN7 connector on the QSPI eMMC module and the ST-Link/V2 programmer.

    .. figure:: img/ST-LinkV2_connections.png
        :alt: ST-Link/V2 programmer connections
        :align: center
        :width: 800px


USB connection
--------------

Connect the USB to micro USB cable between the micro USB port (CN4 connector) on the QSPI eMMC module and the computer.


UART connection (currently not supported)
------------------------------------------

1. Connect the TTL to USB Serial Converter cable between the UART port on the QSPI eMMC module and the computer. Make sure that the TX and RX pins are connected correctly.

    .. figure:: img/FTDI_serial_cable_pinout.png
        :alt: USB to Serial cable
        :align: center
        :width: 800px

Please note that not all USB ports on the computer may work. If you have problems connecting to the QSPI eMMC module, try using a different USB port.


Software requirements
=====================

The QSPI eMMC module features an STM32 microcontroller (STM32L412K8T6) which can be programmed in multiple different ways, which include:

* Arduino IDE + STM32 cube programer.
* STM32CubeIDE.
* Visual Studio Code + PlatformIO.
* Visual Studio Code + various STM32 libraries & plugins.

The options listed above are just some of the most common ways to program any STM32 microcontroller. Here we will use the Arduino IDE and STM32 cube programer, but you are free to pick your favourite method.


Installation steps
==================

Here is a detailed guide on how to install the necessary software to program the QSPI eMMC module.

1. **Arduino IDE**

    * Download the latest version of the Arduino IDE from the `Arduino official website <https://www.arduino.cc/en/software>`_.
    * Open the Arduino IDE and go to *File -> Preferences*.
    * In the Additional Boards Manager URLs field, add the following link:
      ``https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json``
    * Click OK to close the Preferences window.
    * Go to *Tools -> Board -> Boards Manager*.
    * In the Boards Manager window, type "STM32" in the search bar.
    * Install the latest version of the "STM32 MCU based boards" package by STMicroelectronics.
    * Restart Arduino IDE.

2. **STM32 cube programer**

    * Download the STM32 cube programer from the `official website <https://www.st.com/en/development-tools/stm32cubeprog.html>`_. You will need to create an STM account to download the software.
    * Install the program and open it. During installation make sure you install all the necessary drivers.


Arduino IDE setup
=================

1. Open the Arduino IDE and go to *Tools -> Board*.
#. Select *STM32 MCU based boards -> Generic STM32L4 series*.

    .. figure:: img/Arduino_IDE_board.png
        :alt: Arduino IDE board selection
        :align: center
        :width: 1000px

#. Under *Tools -> Board Part Number*, select *Generic L412K8Tx*.

    .. figure:: img/Arduino_IDE_board_part_num.png
        :alt: Arduino IDE board part number selection
        :align: center
        :width: 800px

#. Under *Tools -> USB Support*, select *CDC (generic 'Serial' supersede U(S)ART)*.
#. Under *Tools -> Upload Method*, select the preferred upload method:
        
    * *STM32CubeProgrammer (SWD)* for ST-Link V2 programmer.
    * *STM32CubeProgrammer (Serial)* for USB to Serial cable.
    * *STM32CubeProgrammer (DFU)* for USB to micro USB cable.

    Here are the recommended *Tools* settings:

    .. figure:: img/Arduino_IDE_tool_settings.png
        :alt: Arduino IDE tools settings
        :align: center
        :width: 800px

6. Open the Arduino sketch for the QSPI eMMC module. You can find the sketch and the latest version of the QSPI eMMC module firmware in the :github:`RedPitaya/` - Links to any GitHub repository.. !PLACEHOLDER!#.

.. `Red Pitaya GitHub repository <>`_.

.. ..TODO add the link to the script


Arduino script setup
------------------------

When programming the QSPI eMMC module we need to be careful to perform the following steps:

1. **Create a new file named "build.opt" in the same directory as the Arduino sketch.** This file should contain the following lines:

    .. code-block:: bash

        -HAL_I2C_MODULE_ENABLED
        -HAL_UART_MODULE_ENABLED
        -HAL_PCD_MODULE_ENABLED
        -HAL_HCD_MODULE_ENABLED

    The definitions in the "build.opt" file are used to enable certain features in the STM32L412K8T6 microcontroller. The definitions above are used to enable the I2C, UART, USB pin configurations. 
    The presence of *build.opt* file is automatically checked during the project build, so we don't need to worry about including it in the project.

#. **Include libraries:** 

    * **PeripheralPins.h** - this library provides the pin definitions for the STM32L412K8T6 microcontroller. It includes the pin definitions for all the peripherals on the microcontroller.
    * **Wire.h** - this library provides the I2C communication functions.

#. **Redefine the default weak pinmap declarations.** The pin declarations are defined as "weak" in the *PeripheralPins.h* library. We must redefine them in the arduino sketch as not all the interface pins are used or available on the microcontroller. Add the following lines at the beginning of the arduino sketch:

   .. code-block:: c

        /* REDEFINE DEFAULT PINMAP */
        const PinMap PinMap_I2C_SDA[] = {
        { PB_4, I2C3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3) },
        { PB_7, I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1) },
        { NC, NP, 0 }
        };

        const PinMap PinMap_I2C_SCL[] = {
        { PA_7, I2C3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3) },
        { PB_6, I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1) },
        { NC, NP, 0 }
        };

        const PinMap PinMap_UART_TX[] = {
        { PA_2, USART2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2) },
        { NC, NP, 0 }
        };

        const PinMap PinMap_UART_RX[] = {
        { PA_3, USART2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2) },
        { NC, NP, 0 }
        };

        const PinMap PinMap_USB[] = {
        { PA_11, USB, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF10_USB_FS) },  // USB_DM
        { PA_12, USB, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF10_USB_FS) },  // USB_DP
        { NC, NP, 0 }
        };

    .. note::

        Pin redefinitions are cruicial for proper operation of the QSPI eMMC module. If the pins are not redefined, the microcontroller will not work as expected.

#. **Redefine the pin names:**

    .. code-block:: c

        /* PIN DEFINITIONS */
        #define PWR_ON_CN_PIN (PA0)     // Power On signal from CN7
        #define PWR_ON_PB_PIN (PA1)     // Controlled with P-ON button
        #define UART_TX_PIN (PA2)       // UART (NC) - Shares the bus with I2C1
        #define UART_RX_PIN (PA3)       // Populate R17, R18, R3 and R4 to connect to DIO12_N, DIO12_P
        #define E3_WDT_KICK_PIN (PA4)   // Watchdog timer
        #define E3_SHDN_PIN (PA5)       // Shutdown signal
        #define PS_POR_PIN (PA6)        // PS signal (Power-On reset) - Read only
        #define PWR_ON_PIN (PB1)        // Power supply control
        #define LED_RED_PIN (PA8)       // Red LED
        #define LED_GREEN_PIN (PA9)     // Green LED
        #define USB_N_PIN (PA11)
        #define USB_P_PIN (PA12)
        #define UC_SWDIO_PIN (PA13)     // ST-LINK SWD communication
        #define UC_SWCLK_PIN (PA14)
        #define I2C0_SCL_PIN (PB6)      // I2C0 bus connected to Red Pitaya I2C
        #define I2C0_SDA_PIN (PB7)
        #define I2C1_SCL_PIN (PA7)      // I2C1 (NC) - Shares the bus with UART
        #define I2C1_SDA_PIN (PB4)      // Populate R3 and R4 to connect to DIO12_N, DIO12_P

#. **Decleare UART and I2C buses:**

    .. code-block:: c

        // UART and I2C startup
        HardwareSerial Serial1(UART_RX_PIN, UART_TX_PIN);
        TwoWire Wire0(I2C0_SDA_PIN, I2C0_SCL_PIN);  // I2C 0
        // TwoWire Wire1(I2C1_SDA_PIN, I2C1_SCL_PIN);     // I2C 1

    I2C1 and UART are currently not supported (there is currently no connector on the QSPI eMMC module).

#. **Configure the pins inside the *setup()* function:**

    .. code-block:: c

        // Initialize pin IO
        pinMode(PWR_ON_CN_PIN, INPUT);    // Connector Power ON signal
        pinMode(PWR_ON_PB_PIN, INPUT);    // Button Power ON signal
        pinMode(E3_WDT_KICK_PIN, INPUT);  // Watchdog timer kick from Red Pitaya
        pinMode(E3_SHDN_PIN, OUTPUT);     // Shutdown signal for Red Pitaya
        pinMode(PS_POR_PIN, INPUT);       // Monitor Power Supply Ready activity from Red Pitaya (Power ON Reset)
        pinMode(PWR_ON_PIN, OUTPUT);      // Power ON signal for Red Pitaya
        pinMode(LED_GREEN_PIN, OUTPUT);   // Green LED
        pinMode(LED_RED_PIN, OUTPUT);     // Red LED

        // Disable LEDs
        LED_off(LED_RED_PIN);
        LED_off(LED_GREEN_PIN);

        // I2C and UART init
        Serial1.begin(115200);                  // Start UART interface
        Wire0.begin(I2C_ADDR);                  // Start I2C0 - available at address I2C_ADDR
        Wire0.setClock(400000);                 // Set I2C speed
        Wire0.onReceive(I2C0_receive_handler);  // On I2C recieve and request from master execute a handler function
        Wire0.onRequest(I2C0_request_handler);
        /*
        // I2C1 not implemented currently
        Wire1.begin(I2C_ADDR);                  // Start I2C1
        Wire1.setClock(400000);
        Wire1.onReceive(I2C1_recieve_handler);
        Wire1.onRequest(I2C1_request_handler);
        */
    
.. note::

    The steps above are necessary for proper operation of the microcontroller. If anything is missing, the microcontroller will not work as expected.


Programming the board
=====================

The QSPI eMMC module must be connected to a powered Red Pitaya unit during the programming process. The Red Pitaya unit provides power to the QSPI eMMC module.


Arduin IDE
----------

The program can be uploaded to the QSPI eMMC module with Arduino IDE in three different ways:

* **ST-Link/V2 programmer (SWD)**.
* **USB to micro USB cable (DFU)**.
* **USB to Serial cable (UART)**.

Before uploading the program, please verify the code in the Arduino IDE (green arrow button) in the top left corner of the window. If there are no errors, you can proceed with the upload.

1. **ST-Link/V2 programmer (SWD)**

    * Connect the ST-Link/V2 programmer to the computer and the QSPI eMMC module.
    * Select *STM32CubeProgrammer (SWD)* as the upload method in the Arduino IDE.
    * Click the upload button in the Arduino IDE.

2. **USB to micro USB cable (DFU)**
    
    * Connect the USB to micro USB cable between the computer and the QSPI eMMC module.
    * Select *STM32CubeProgrammer (DFU)* as the upload method in the Arduino IDE.
    * Click the upload button in the Arduino IDE.
    * If the upload fails, disconnect and reconnect the USB cable and try again. The USB cable must be reconnected after each upload. Please note that this will reset the board.

3. **USB to Serial cable (UART) (currently not supported)**
    
    * Connect the USB to Serial cable between the computer and the QSPI eMMC module.
    * Select *STM32CubeProgrammer (Serial)* as the upload method in the Arduino IDE.
    * Click the upload button in the Arduino IDE.
    * When Arduino IDE reaches the uploading stage, press the reset button on the QSPI eMMC module. This will put the board in the bootloader mode and the program will be uploaded.


STM32 Cube Programmer
---------------------

Alternatively, you can use the STM32CubeProgrammer software to program the QSPI eMMC module with a compiled binary version of your program. You can use any of the three methods listed above to connect the QSPI eMMC module to the computer.

1. Open the STM32CubeProgrammer software.
#. Connect the QSPI eMMC module to the computer.
#. Select the desired COM port from the dropdown in the STM32CubeProgrammer. Configure any additional settings if needed.

    .. figure:: img/STM32_cube_select.png
        :alt: STM32CubeProgrammer select communication port
        :align: center
        :width: 400

#. Click the "Connect" button. The QSPI eMMC module should be automatically detected by the STM32CubeProgrammer.

    .. figure:: img/STM32_cube_connected.png
        :alt: STM32CubeProgrammer connected to the QSPI eMMC module
        :align: center
        :width: 1000

#. Open the *Erasing & Programming* tab in the left hand menu.

    .. figure:: img/STM32_cube_menu.png
        :alt: STM32CubeProgrammer erase and program tab
        :align: center
        :width: 400

#. Click the "Browse" button and select the compiled binary file of your program. You can get the compiled binary file from the Arduino IDE by clicking the "Sketch -> Export compiled binary" option.

    .. figure:: img/Arduino_IDE_compiled_binary.png
        :alt: Arduino IDE compiled binary
        :align: center
        :width: 600px

#. Check the "Verify programming" and "Run after programming" boxes.
#. Click the "Start Programming" button to upload the program to the QSPI eMMC module.

    .. figure:: img/STM32_cube_program.png
        :alt: STM32CubeProgrammer programming the QSPI eMMC module
        :align: center
        :width: 1000px
    
#. After the programming is complete, STM32CubeProgrammer will display a few pop-up windows informing you of device disconnecting and that the programming was successful. Click "OK" on all of them.


QSPI eMMC module schematics and pinout
========================================

You can find the QSPI eMMC module schematics and pinout in the :ref:`hardware section <E3_QSPI_eMMC_module_HW>`.


QSPI eMMC module firmware
==========================

.. TODO decide on the final link to the firmware

The QSPI eMMC module firmware is written in Arduino IDE C++ and is available in the `Red Pitaya GitHub repository <https://github.com/RedPitaya/RedPitaya-Examples>`_. (**Link not yet available**)

The firmware program is a state machine that controls the power of Red Pitaya in acordance with the user input. The program is has the following states:

* **Power up** - Red Pitaya is booting up. After a set amout of time, the power and watchdog signals are monitored. If the signals are not detected, the program will go to the power reset state, otherwise it will go to the power on state.
* **Power on** - Red Pitaya is powered on. If the power button is held for two seconds, the state switches to power down. Watchdog and power signals are monitored. If the signals are not detected, the program will go to the power reset state, otherwise it will stay in the power on state.
* **Power down** - Red Pitaya is shutting down. A singal is sent to Red Pitaya to start the power off process. After a set amount of time, the program enters the power off state.
* **Power off** - Red Pitaya is powered off. The program will stay in this state until the power button is pressed.
* **Power down reset** - Red Pitaya will reset after a power down. A singal is sent to Red Pitaya to start the power off process. After a set amount of time, the program enters the power reset state.
* **Power reset** - Red Pitaya is powered off. After a set amount of time, the program enters the power up state. If reset state is reached multiple times in a row, the board will enter power fail state.
* **Power fail** - Red Pitaya is powered off. The program will stay in this state until the power button is pressed. Then it goes to the power off state.

At any point in time, the user can press and hold the power button to force the Red Pitaya to power off.

The state machine diagram is shown below:

.. figure:: img/E3_state_diagram.png
    :alt: QSPI eMMC module state machine
    :align: center
    :width: 1200px

The firmware program is written in a way that it can be easily modified to suit the user's needs. The program is well commented and structured so that the user can easily understand and modify it.

The state changes can be controlled from the Red Pitaya with the E3 I2C controller.


.. _e3_i2c_controller_sw:

E3 I2C controller
=================

.. the text is located in another directory, so we need just include it here - make changes in that file and they will be reflected here

.. include:: ../../../../../appsFeatures/command_line_tools/utils/e3_i2c_controller.inc


E3 Hardware specifications
==========================

For information on hardware specifications such as pinout of the QSPI eMMC module, please refer to the :ref:`hardware section <E3_QSPI_eMMC_module_HW>`.


FAQ
===


.. Linked to E3_QSPI_eMMC_module_HW section, add instructions and explanation of the basic program 


`Back to top <E3_QSPI_eMMC_module_SW>`_

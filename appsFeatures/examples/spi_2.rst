SPI (HW api)
############

.. http://blog.redpitaya.com/examples-new/spi/

Description
***********

This example shows communication with the red pitaya SPI. This code is for testing writing and reading via SPI protocol. In order for the code to work, you need to connect the MISO and MOSI connectors.


Required hardware
*****************

    - Red Pitaya device

.. figure:: output_y49qDi.gif

Code - C
********

.. note::

    C code examples don't require the use of the SCPI server, we have included them here to demonstrate how the same functionality can be achieved with different programming languages. 
    Instructions on how to compile the code are here -> `link <https://redpitaya.readthedocs.io/en/latest/developerGuide/comC.html>`_

.. code-block:: c

    /* @brief This is a simple application for testing SPI communication on a RedPitaya
    *
    * (c) Red Pitaya  http://www.redpitaya.com
    *
    * This part of code is written in C programming language.
    * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
    * for more details on the language used herein.
    */


    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "rp_hw.h"


    int main(int argc, char *argv[]){

        char *buffer = "TEST string";
        char rx_buf[255];
        memset(rx_buf,0,255);

        int res = rp_SPI_InitDevice("/dev/spidev1.0"); // Init spi api.
        printf("Init result: %d\n",res);
        
        res = rp_SPI_SetDefaultSettings(); // Set default settings.
        printf("Set default settings: %d\n",res);
        
        res = rp_SPI_GetSettings(); // Get uart speed.
        printf("Get current settings of spi: %d\n",res);

        res = rp_SPI_SetMode(RP_SPI_MODE_LIST); // Set SPI mode: Low idle level, sample on trailing edge.
        printf("Set mode: %d\n",res);

        res = rp_SPI_SetSpeed(50000000); // Set SPI speed.
        printf("Set speed: %d\n",res);

        res = rp_SPI_SetWordLen(8); // Set word bit size.
        printf("Set word length: %d\n",res);

        res = rp_SPI_SetSettings(); // Apply settings to SPI.
        printf("Set settings: %d\n",res);

        res = rp_SPI_CreateMessage(2); // Create 2 message.
        printf("Set settings: %d\n",res);

        res = rp_SPI_SetBufferForMessage(0,(uint8_t*)buffer,true,strlen(buffer),false); // Set buffer for first message and create RX buffer.
        printf("Set buffers for first msg: %d\n",res);

        res = rp_SPI_SetBufferForMessage(1,0,true,100,false); // Create RX buffer.
        printf("Set buffers for second msg: %d\n",res);
        
        res = rp_SPI_ReadWrite(); // Pass message to SPI.
        printf("Read/Write to spi: %d\n",res);

        uint8_t *rx_buffer = 0;
        size_t rx_size = 0;
        res = rp_SPI_GetRxBuffer(0,&rx_buffer,&rx_size); // Get pointer to rx buffer. No need free buffer. Api itself destroy buffer. 

        if (rx_buffer)
            printf("Read message: %s (res %d)\n",rx_buffer,res);
        
        res = rp_SPI_DestoryMessage();

        res = rp_SPI_Release(); // Close spi api.
        printf("UnInit result: %d\n",res);

        return 0;
    }

Code - MATLAB®
**************

.. code-block:: matlab

    %% Define Red Pitaya as TCP/IP object

    IP= '';           % Input IP of your Red Pitaya...
    port = 5000;
    tcpipObj=tcpip(IP, port);

    %% Open connection with your Red Pitaya

    fopen(tcpipObj);
    tcpipObj.Terminator = 'CR/LF';
    fprintf(tcpipObj,'SPI:INIT:DEV "/dev/spidev1.0"');

    fprintf(tcpipObj,'SPI:SET:DEF');           % set default settings

    fprintf(tcpipObj,'SPI:SET:GET');           % get default settings

    fprintf(tcpipObj,'SPI:SET:MODE LIST');     % set mode: Low idle level, sample on trailing edge

    fprintf('Mode %s\n', query(tcpipObj,'SPI:SET:MODE?')); % check current mode setting

    fprintf(tcpipObj,'SPI:SET:SPEED 5000000'); % set spi speed

    fprintf('Speed %s\n', query(tcpipObj,'SPI:SET:SPEED?')); % check current speed setting

    fprintf(tcpipObj,'SPI:SET:WORD 8');        % set word length

    fprintf('Word length %s\n', query(tcpipObj,'SPI:SET:WORD?')); % check current speed setting

    fprintf(tcpipObj,'SPI:SET:SET');           % apply setting to spi

    %% Work with spi messages

    fprintf(tcpipObj,'SPI:MSG:CREATE 2');      % create 2 messages with diffrent buffers

    fprintf('Check message count %s\n', query(tcpipObj,'SPI:MSG:SIZE?')); 

    fprintf(tcpipObj,'SPI:MSG0:TX4:RX 13,14,15,16');  % sets the first message to write and read buffers of 4 bytes

    fprintf(tcpipObj,'SPI:MSG1:RX7:CS'); % Sets the buffer for the second message to read 7 bytes long and switch the CS signal level

    fprintf(tcpipObj,'SPI:PASS'); % sends data to SPI

    fprintf('TX buffer of 1 msg %s\n', query(tcpipObj,'SPI:MSG0:TX?'));

    fprintf('RX buffer of 1 msg %s\n', query(tcpipObj,'SPI:MSG0:TX?'));

    fprintf('RX buffer of 2 msg %s\n', query(tcpipObj,'SPI:MSG1:RX?'));

    fprintf(tcpipObj,'SPI:MSG:DEL'); % Deletes messages


    %% Close connection with Red Pitaya

    fprintf(tcpipObj,'SPI:RELEASE');           % close spi

    fclose(tcpipObj);


Code - Python
*************

.. code-block:: python


#!/usr/bin/python

    import sys
    import time
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi(sys.argv[1])

    rp_s.tx_txt('SPI:INIT:DEV "/dev/spidev1.0"')
    print("Init SPI")

    rp_s.tx_txt('SPI:SET:DEF')
    print("Set default settings")

    rp_s.tx_txt('SPI:SET:GET')
    print("Get settings")

    rp_s.tx_txt('SPI:SET:MODE LIST')
    print("Set mode")

    rp_s.tx_txt('SPI:SET:MODE?')
    print("Get mode:",rp_s.rx_txt())


    rp_s.tx_txt('SPI:SET:SPEED 5000000')
    print("Set speed")

    rp_s.tx_txt('SPI:SET:SPEED?')
    print("Get speed:",rp_s.rx_txt())

    rp_s.tx_txt('SPI:SET:WORD 8')
    print("Set word length")

    rp_s.tx_txt('SPI:SET:WORD?')
    print("Get word length:",rp_s.rx_txt())

    rp_s.tx_txt('SPI:SET:SET')
    print("Set settings")

    rp_s.tx_txt('SPI:MSG:CREATE 2')
    print("Create message")

    rp_s.tx_txt('SPI:MSG:SIZE?')
    print("Message size:",rp_s.rx_txt())

    rp_s.tx_txt('SPI:MSG0:TX4:RX 13,14,15,16')
    print("Set message")

    rp_s.tx_txt('SPI:MSG1:RX7:CS')
    print("Set message 2")

    rp_s.tx_txt('SPI:PASS')
    print("Pass message")

    rp_s.tx_txt('SPI:MSG0:TX?')
    print("Tx buffer:",rp_s.rx_txt())

    rp_s.tx_txt('SPI:MSG0:RX?')
    print("Received data:",rp_s.rx_txt())

    rp_s.tx_txt('SPI:MSG1:RX?')
    print("Received data 2:",rp_s.rx_txt())

    rp_s.tx_txt('SPI:MSG1:CS?')
    print("CS state for message 2:",rp_s.rx_txt())

    rp_s.tx_txt('SPI:MSG:DEL')
    print("Delete message")

    rp_s.tx_txt('SPI:RELEASE')
    print("Release SPI")
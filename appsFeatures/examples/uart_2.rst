UART (HW api)
#############

.. http://blog.redpitaya.com/examples-new/uart/

Description
***********

This example demonstrates communication using the red pitaya uart protocol. The code below simulates a loop back
sending a message from the uart TX connector to the uart RX connector on red pitaya.


Required hardware
*****************

    - Red Pitaya

.. figure:: output_y49qDi.gif

Code - C
********

.. note::

    C code examples don't require the use of the SCPI server, we have included them here to demonstrate how the same functionality can be achieved with different programming languages. 
    Instructions on how to compile the code are here -> `link <https://redpitaya.readthedocs.io/en/latest/developerGuide/comC.html>`_

.. code-block:: c

    /* @brief This is a simple application for testing UART communication on a RedPitaya
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
        int size = 255;

        int res = rp_UartInit(); // init uart api
        printf("Init result: %d\n",res);
        
        res = rp_UartSetTimeout(10); // set timeout in 1/10 sec. 10 = 1 sec 
        printf("Set timeout: %d\n",res);
        
        res = rp_UartSetSpeed(115200); // set uart speed
        printf("Set speed: %d\n",res);

        res = rp_UartSetBits(RP_UART_CS8); // set word size
        printf("Set CS8: %d\n",res);

        res = rp_UartSetStopBits(RP_UART_STOP2); // set stop bits
        printf("Set Stop Bits 2: %d\n",res);

        res = rp_UartSetParityMode(RP_UART_MARK); // set parity
        printf("Set Parity Mode: %d\n",res);
        
        res = rp_UartSetSettings(); // apply settings to uart
        printf("Set settings: %d\n",res);
        
        res = rp_UartWrite((unsigned char*)buffer,strlen(buffer)); // write buffer to uart
        printf("Write result: %d\n",res);

        res = rp_UartRead((unsigned char*)rx_buf,&size); // read from uart
        printf("Read result: %d\n",res);   
        printf("Size: %d (%s)\n",size,rx_buf);

        res = rp_UartRelease(); // close uart api
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
    fprintf(tcpipObj,'UART:INIT');

    fprintf(tcpipObj,'UART:BITS CS7');         % set size 7 bit
    res = query(tcpipObj,'UART:BITS?');        % check current settings for bit size 
    fprintf('Bit size %s\n', res);

    fprintf(tcpipObj,'UART:SPEED 57600');      % set uart speed
    res = query(tcpipObj,'UART:SPEED?');       % check current settings for speed
    fprintf('Speed %s\n', res);

    fprintf(tcpipObj,'UART:STOPB STOP2');      % set stop bits
    res = query(tcpipObj,'UART:STOPB?');       % check current settings for stop bits
    fprintf('Stop bits %s\n', res);

    fprintf(tcpipObj,'UART:PARITY ODD');       % set parity
    res = query(tcpipObj,'UART:PARITY?');      % check current settings for parity
    fprintf('Parity %s\n', res);

    fprintf(tcpipObj,'UART:TIMEOUT 10');       % set timeout in 1/10 sec. 10 = 1 sec 
    res = query(tcpipObj,'UART:TIMEOUT?');     % check current settings for parity
    fprintf('Timeout %s\n', res);

    fprintf(tcpipObj,'UART:SETUP');           % apply setting to uart 

    fprintf(tcpipObj,'UART:WRITE7 #H11,#H22,#H33,33,33,#Q11,#B11001100');  % write to uart 7 bytes
    fprintf('Write 7 bytes to uart: #H11,#H22,#H33,33,33,#Q11,#B11001100\n');

    res = query(tcpipObj,'UART:READ3');        % read from uart 3 bytes
    fprintf('Read: %s\n', res);

    res = query(tcpipObj,'UART:READ4');        % read from uart 4 bytes
    fprintf('Read: %s\n', res);

    fprintf(tcpipObj,'UART:RELEASE');          % close uart

    %% Close connection with Red Pitaya

    fclose(tcpipObj);

Code - Python
*************

.. code-block:: python

    #!/usr/bin/python

    import sys
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi(sys.argv[1])

    rp_s.tx_txt('UART:INIT')
    print("Init UART")


    rp_s.tx_txt('UART:BITS CS7')
    print("Set bit size CS7")

    rp_s.tx_txt('UART:BITS?')
    print("Check bit size",rp_s.rx_txt())

    rp_s.tx_txt('UART:SPEED 57600')
    print("Set speed 57600")

    rp_s.tx_txt('UART:SPEED?')
    print("Check speed",rp_s.rx_txt())

    rp_s.tx_txt('UART:STOPB STOP2')
    print("Set stop bit STOP2")

    rp_s.tx_txt('UART:STOPB?')
    print("Check stop bit",rp_s.rx_txt())

    rp_s.tx_txt('UART:PARITY ODD')
    print("Set parity mode: ODD")

    rp_s.tx_txt('UART:PARITY?')
    print("Check parity mode",rp_s.rx_txt())

    rp_s.tx_txt('UART:TIMEOUT 10')
    print("Set timeout: 10 decams")

    rp_s.tx_txt('UART:TIMEOUT?')
    print("Check timeout",rp_s.rx_txt())


    rp_s.tx_txt('UART:SETUP')
    print("Setup settings")

    rp_s.tx_txt('UART:WRITE7 #H11,#H22,#H33,33,33,#Q11,#B11001100')
    print("Write 7 bytes to uart: #H11,#H22,#H33,33,33,#Q11,#B11001100'")

    rp_s.tx_txt('UART:READ3')
    print("Read: ",rp_s.rx_txt())

    rp_s.tx_txt('UART:READ4')
    print("Read: ",rp_s.rx_txt())

    rp_s.tx_txt('UART:RELEASE')
    print("Release UART")
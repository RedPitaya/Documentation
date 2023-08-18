UART (HW api)
#############

.. http://blog.redpitaya.com/examples-new/uart/

Description
***********

This example demonstrates communication using the Red Pitaya UART protocol. The code below simulates a loopback by sending a message from the UART TX connector to the UART RX connector on the Red Pitaya.

.. note::

    When establishing UART communication with Red Pitaya and another device do not forget to connect the External Common Mode (GND) pin. Otherwise, the results might be unreliable.


Required hardware
*****************

    - Red Pitaya

.. figure:: ../general_img/RedPitaya_general.png

Code - C
********

.. note::

    Although the C code examples don't require the use of the SCPI server, we have included them here to demonstrate how the same functionality can be achieved with different programming languages. 
    Instructions on how to compile the code are :ref:`here <comC>`.


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

    %% Define Red Pitaya as TCP client object

    IP = '192.168.178.56';              % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya

    RP.ByteOrder = "big-endian";
    configureTerminator(RP,"CR/LF");

    writeline(RP,'UART:INIT');

    writeline(RP,'UART:BITS CS7');              % set size 7 bit
    res = writeread(RP,'UART:BITS?');           % check current settings for bit size
    fprintf('Bit size %s\n', res);

    writeline(RP,'UART:SPEED 57600');           % set uart speed
    res = writeread(RP,'UART:SPEED?');          % check current settings for speed
    fprintf('Speed %s\n', res);

    writeline(RP,'UART:STOPB STOP2');           % set stop bits
    res = writeread(RP,'UART:STOPB?');          % check current settings for stop bits
    fprintf('Stop bits %s\n', res);

    writeline(RP,'UART:PARITY ODD');            % set parity
    res = writeread(RP,'UART:PARITY?');         % check current settings for parity
    fprintf('Parity %s\n', res);

    writeline(RP,'UART:TIMEOUT 10');            % set timeout in 1/10 sec. 10 = 1 sec
    res = writeread(RP,'UART:TIMEOUT?');        % check current settings for parity
    fprintf('Timeout %s\n', res);

    writeline(RP,'UART:SETUP');                 % apply settings to uart

    writeline(RP,'UART:WRITE7 #H11,#H22,#H33,33,33,#Q11,#B11001100');       % write to uart 7 bytes
    fprintf('Write 7 bytes to uart: #H11,#H22,#H33,33,33,#Q11,#B11001100\n');

    res = writeread(RP,'UART:READ3');           % read from uart 3 bytes
    fprintf('Read: %s\n', res);

    res = writeread(RP,'UART:READ4');           % read from uart 4 bytes
    fprintf('Read: %s\n', res);

    writeline(RP,'UART:RELEASE');               % close uart

    %% Close connection with Red Pitaya

    clear RP;


Code - Python
*************

Using just SCPI commands:

.. code-block:: python

    #!/usr/bin/env python3

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
    
    
Using functions:

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi(sys.argv[1])
    
    speed = 57600
    bits = "CS7"
    parity = "ODD"
    stop = 2
    timeout = 10
    
    # function for configuring UART settings
    rp_s.uart_set(speed, bits, parity, stop, timeout)

    # function to get UART settings
    uart_set = rp_s.uart_get_setings()
    print("\n")

    rp_s.tx_txt('UART:WRITE7 #H11,#H22,#H33,33,33,#Q11,#B11001100')
    print("Write 7 bytes to uart: #H11,#H22,#H33,33,33,#Q11,#B11001100'")

    rp_s.tx_txt('UART:READ3')
    print("Read: ",rp_s.rx_txt())

    rp_s.tx_txt('UART:READ4')
    print("Read: ",rp_s.rx_txt())
    print("\n")
    
    # function to send a string through UART
    rp_s.uart_write_string("Hello World")   # set the ascii parameter to True if bits == CS7 or to False if bits == CS8
    
    # function to read a string through UART
    message = rp_s.uart_read_string(length = 11)
    print(f"{message}\n")

    rp_s.tx_txt('UART:RELEASE')
    print("Release UART")
    
    rp_s.close()


.. note::

    The Python functions are accessible with the latest version of the redpitaya_scpi.py document available on our |redpitaya_scpi|.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order. The code should function at approximately the same speed without them.

    For further information on functions please consult the redpitaya_scpi.py code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">GitHub</a>


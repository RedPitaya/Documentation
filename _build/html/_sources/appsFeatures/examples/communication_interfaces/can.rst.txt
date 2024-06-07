CAN (HW api)
#############

.. http://blog.redpitaya.com/examples-new/uart/

Description
***********

This example demonstrates communication using the Red Pitaya CAN interface. The code below simulates a loopback by sending a message from the CAN socket.


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

    /* @brief This is a simple application for testing CAN communication on a RedPitaya
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
    #include "rp_hw_can.h"


    int main(int argc, char *argv[]){

        int res = rp_CanSetFPGAEnable(true); // init can in fpga for pass can controller to GPIO (N7,P7) 
        printf("Init result: %d\n",res);
        
        res = rp_CanStop(RP_CAN_0); // set can0 interface to DOWN  for configure
        printf("Stop can0: %d\n",res);
        
        res = rp_CanSetBitrate(RP_CAN_0,200000); // set can0 bitrate
        printf("Set bitrate: %d\n",res);

        res = rp_CanSetControllerMode(RP_CAN_0,RP_CAN_MODE_LOOPBACK,true); // set loopback mode
        printf("Set loopback mode ON: %d\n",res);

        res = rp_CanStart(RP_CAN_0); // set can0 interface to UP
        printf("Start can0: %d\n",res);

        res = rp_CanOpen(RP_CAN_0); // open socket for can0
        printf("Open socket: %d\n",res);

        unsigned char tx_buffer[8];
        tx_buffer[0] = 1;
        tx_buffer[1] = 2;
        tx_buffer[2] = 3;
        res = rp_CanSend(RP_CAN_0,123, tx_buffer,3,false,false,0); // write buffer to can0
        printf("Write result: %d\n",res);

        rp_can_frame_t frame;
        res = rp_CanRead(RP_CAN_0,2000, &frame); // read frame from can0
        printf("Read result: %d\n",res);   
        printf("Can ID: %d data: %d,%d,%d\n",frame.can_id,frame.data[0],frame.data[1],frame.data[2]);

        res = rp_CanClose(RP_CAN_0); // close socket for can0
        printf("Close can0 result: %d\n",res);
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
    fprintf(tcpipObj,'CAN:FPGA ON');

    fprintf(tcpipObj,'CAN0:STOP');             % stop can interface for configure

    fprintf(tcpipObj,'CAN0:BITRate 200000');   % set bitrate for can0
    res = query(tcpipObj,'CAN0:BITRate:SP?');
    fprintf('Bitrate %s\n', res);

    fprintf(tcpipObj,'CAN0:MODE LOOPBACK,ON'); % set loopback mode

    fprintf(tcpipObj,'CAN0:START');            % start can0 interface 

    fprintf(tcpipObj,'CAN0:OPEN');             % open can0 socket 

    fprintf(tcpipObj,'CAN0:Send123 1,2,3');    % write to can0 3 bytes
    fprintf('CAN0:Send123 1,2,3\n');

    res = query(tcpipObj,'CAN0:Read:Timeout2000?'); % read frame from can0
    fprintf('Read: %s', res);

    fprintf(tcpipObj,'CAN0:CLOSE');            % close can0

    %% Close connection with Red Pitaya

    fclose(tcpipObj);



Code - Python
*************

Using just SCPI commands:

.. code-block:: python

    #!/usr/bin/python3

    import sys
    import time
    import redpitaya_scpi as scpi

    rp_s = scpi.scpi(sys.argv[1])

    rp_s.tx_txt('CAN:FPGA ON')
    print("CAN:FPGA ON")
    rp_s.check_error()

    rp_s.tx_txt('CAN0:STOP')
    print("CAN0:START")
    rp_s.check_error()

    rp_s.tx_txt('CAN0:BITRate 200000')
    print("CAN0:BitRate 200000")
    rp_s.check_error()

    rp_s.tx_txt('CAN0:MODE LOOPBACK,ON')
    print("CAN0:MODE LOOPBACK,ON")
    rp_s.check_error()

    rp_s.tx_txt('CAN0:START')
    print("CAN0:START")
    rp_s.check_error()

    rp_s.tx_txt('CAN0:OPEN')
    print("CAN0:OPEN")
    rp_s.check_error()

    rp_s.tx_txt('CAN0:Send123 1,2,3')
    print("CAN0:SEND123 1,2,3")
    rp_s.check_error()

    rp_s.tx_txt('CAN0:Read:Timeout2000?')
    print("CAN0:Read:Timeout2000?",rp_s.rx_txt_check_error())

    rp_s.tx_txt('CAN0:CLOSE')
    print("CAN0:CLOSE")
    rp_s.check_error()
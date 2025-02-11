

I2C switch AC/DC mode (SIGNALlab 250-12)
#########################################


Description
===========

This 250-12 board example shows how to switch AC/DC modes over I2C using the SMBUS protocol.

Required hardware
==================

    - Red Pitaya SIGNALlab 250-12

Required software
==================

.. include:: ../sw_requirement.inc

  
SCPI Code Examples
====================

.. include:: ../matlab.inc

Code - MATLAB®
---------------

.. code-block:: matlab

    %% Define Red Pitaya as TCP/IP object
    IP = 'rp-f0a235.local';              % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya
    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');

    % working with RP 250-12 v1.2. For HW revision 1.1 and newer, replace dev address with 32 (0x20)
    writeline(RP,'I2C:DEV33 "/dev/i2c-0"');
    writeline(RP,'I2C:FMODE ON');                           % set force mode
    fprintf('Turn on AC/DC ch1 & ch2\n');

    value = 0x55;
    writeline(RP, append('I2C:Smbus:Write2 %d', num2str(value)));   % write 2 bytes in i2c throw SMBUS
    java.lang.Thread.sleep(1000);

    value = value & ~ 0x0F;
    writeline(RP, append('I2C:Smbus:Write2 %d', num2str(value)));   % write 2 bytes in i2c throw SMBUS

    java.lang.Thread.sleep(3000);
    fprintf('Turn off AC/DC ch1 & ch2\n');

    value = 0xAA;
    writeline(RP, append('I2C:Smbus:Write2 %d', num2str(value)));   % write 2 bytes in i2c throw SMBUS

    java.lang.Thread.sleep(1000);

    value = value & ~ 0x0F;
    writeline(RP, append('I2C:Smbus:Write2 %d', num2str(value)));   % write 2 bytes in i2c throw SMBUS

    java.lang.Thread.sleep(1000);
                    
    value = writeread(RP,'I2C:Smbus:Read2?');       % read 2 bytes from reg 0x02 throw SMBUS
    value = str2num(value(2:length(value) -1));
    fprintf('Reg 0x02: %x\n', value);

    %% Close connection with Red Pitaya
    clear RP;


Code - Python
--------------

.. code-block:: python

    #!/usr/bin/env python3

    import time
    from struct import *
    import redpitaya_scpi as scpi

    IP = 'rp-f066c8.local'
    rp = scpi.scpi(IP)

    # working on SIGNALlab 250-12 HW revision v1.2. For HW revision 1.1 and older, replace dev address with 32 (0x20)
    rp.tx_txt('I2C:DEV33 "/dev/i2c-0"')
    print("Init I2C")

    rp.tx_txt('I2C:FMODE ON')
    print("Set force mode")

    #  Swich AC_DC for In 1
    print("Turn on AC/DC ch1 & ch2")

    value = 0x55
    rp.tx_txt(f'I2C:Smbus:Write2 {value}') # write to i2c
    print(f"Write value for reg 0x2: {value}")

    time.sleep(1)

    value = (value & ~0x0F)
    rp.tx_txt(f'I2C:Smbus:Write2 {value}') # write to i2c
    print(f"Write value for reg 0x2: {value}")

    time.sleep(3)

    print("Turn off AC/DC ch1 & ch2")

    value = 0xAA
    rp.tx_txt(f'I2C:Smbus:Write2 {value}') # write to i2c
    print(f"Write value for reg 0x2: {value}")

    time.sleep(1)

    value = (value & ~0x0F)
    rp.tx_txt(f'I2C:Smbus:Write2 {value}') # write to i2c
    print(f"Write value for reg 0x2: {value}")

    rp.tx_txt('I2C:Smbus:Read2?')
    value = int(rp.rx_txt().strip('{}\n\r'))
    print(f"Read value for reg 0x2: {value}")


.. include:: ../python_scpi_note.inc


API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C
----------

.. code-block:: c

    /* @brief This is a simple application for testing I2C communication on a RedPitaya
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
    #include <unistd.h>
    #include "rp_hw.h"


    int main(int argc, char *argv[]){

        int res = rp_I2C_InitDevice("/dev/i2c-0",0x21); // Init i2c api.
        printf("Init result: %d\n",res);

        res = rp_I2C_setForceMode(true); // Set force mode.
        printf("Set force mode: %d\n",res);

        printf("Turn on AC/DC ch1 & ch2\n");

        uint16_t value = 0x0055;

        res = rp_I2C_SMBUS_WriteWord(0x02,value);
        printf("Write 2 bytes: %d\n",res);

        usleep(1000000);

        value = value & ~ 0x000F;

        res = rp_I2C_SMBUS_WriteWord(0x02,value);
        printf("Write 2 bytes: %d\n",res);

        usleep(3000000);

        printf("Turn off AC/DC ch1 & ch2\n");

        value = 0x00AA;

        res = rp_I2C_SMBUS_WriteWord(0x02,value);
        printf("Write 2 bytes: %d\n",res);

        usleep(1000000);

        value = value & ~ 0x000F;

        res = rp_I2C_SMBUS_WriteWord(0x02,value);
        printf("Write 2 bytes: %d\n",res);

        uint16_t read_value = 0;

        res = rp_I2C_SMBUS_ReadWord(0x02,&read_value);
        printf("Read 2 bytes: 0x%x (res: %d)\n",read_value, res);

        return 0;
    }

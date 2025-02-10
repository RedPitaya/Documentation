I2C internal
#############

Description
============

This example demonstrates communication with the 24LC64 EEPROM memory on the Red Pitaya using the I2C protocol through SPCI and API commands. The code below reads the calibration values from the EEPROM and displays them. The data is displayed correctly only on 125-xx boards.


Required hardware
==================

    - Red Pitaya

.. figure:: ../general_img/RedPitaya_general.png


Required software
=================

.. include:: ../sw_requirement.inc


  
SCPI Code Examples
====================

.. ! TODO 

.. note::

    The calibration parameter order has changed with 2.00 OS. We will update the example soon.


Code - MATLAB®
---------------

.. code-block:: matlab

    %% Define Red Pitaya as TCP client object
    IP = 'rp-f066c8.local';              % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya
    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');

    writeline(RP,'I2C:DEV80 "/dev/i2c-0"');
    writeline(RP,'I2C:FMODE ON');       % force slave mode operation

    % EEPROM 24LC64 only works through IOCTL
    writeline(RP,'I2C:IOctl:Write:Buffer2 0,0');    % set read address = 0

    b1 = writeread(RP,'I2C:IOctl:Read:Buffer32?');  % read 32 bytes from i2c 
    b2 = writeread(RP,'I2C:IOctl:Read:Buffer16?');  % read 16 bytes from i2c

    b_num = str2num(b1(2:length(b1)-1));
    b_num(33:48) = str2num(b2(2:length(b2)-1));

    calib = typecast(uint8(b_num),'int32');

    fprintf('ADC Ch1 High %d\n', calib(3));
    fprintf('ADC Ch2 High %d\n', calib(4));
    fprintf('ADC Ch1 Low %d\n', calib(5));
    fprintf('ADC Ch2 Low %d\n', calib(6));
    fprintf('ADC Ch1 Low offset %d\n', calib(7));
    fprintf('ADC Ch2 Low offset %d\n', calib(8));
    fprintf('DAC Ch1 %d\n', calib(9));
    fprintf('DAC Ch2 %d\n', calib(10));
    fprintf('DAC Ch1 offset %d\n', calib(11));
    fprintf('DAC Ch2 offset %d\n', calib(12));

    %% Close connection with Red Pitaya
    clear RP;


Code - Python
--------------

.. code-block:: python

    #!/usr/bin/env python3

    import sys
    import time
    from struct import *
    import redpitaya_scpi as scpi

    rp = scpi.scpi(sys.argv[1])

    rp.tx_txt('I2C:DEV80 "/dev/i2c-0"')
    print("Init I2C")

    rp.tx_txt('I2C:FMODE ON')
    print("Set force mode")

    # EEPROM 24LC64 only works through IOCTL
    # set read address = 0
    rp.tx_txt('I2C:IOctl:Write:Buffer2 0,0')
    print("Write address for read")

    rp.tx_txt('I2C:IOctl:Read:Buffer32?')
    b1 = rp.rx_txt().strip('{').strip('}')

    rp.tx_txt('I2C:IOctl:Read:Buffer16?')
    b2 = rp.rx_txt().strip('{').strip('}')

    buff = (b1 + "," + b2).split(",")
    byte_array = bytearray(b'')
    for s in buff:
        byte_array.append(int(s))

    calib = [unpack('i', byte_array[i:i+4])[0] for i in range(0, len(byte_array), 4)]
    print("ADC Ch1 High", calib[2])
    print("ADC Ch2 High", calib[3])
    print("ADC Ch1 Low", calib[4])
    print("ADC Ch2 Low", calib[5])
    print("ADC Ch1 Low offset", calib[6])
    print("ADC Ch2 Low offset", calib[7])
    print("DAC Ch1", calib[8])
    print("DAC Ch2", calib[9])
    print("DAC Ch1 offset", calib[10])
    print("DAC Ch2 offset", calib[11])


.. include:: ../python_scpi_note.inc


API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C
---------

.. tabs::

    .. tab:: OS 1.04 or older

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

                int res = rp_I2C_InitDevice("/dev/i2c-0",0x50); // Init i2c api.
                printf("Init result: %d\n",res);
    
                res = rp_I2C_setForceMode(true); // Set force mode.
                printf("Set force mode: %d\n",res);
    
                uint8_t wb[2] = {0,0};
                res = rp_I2C_IOCTL_WriteBuffer(wb,2); // Write position for reading.
                printf("Write 2 bytes: %d\n",res);

                usleep(100000);

                int32_t rb[12];
                res = rp_I2C_IOCTL_ReadBuffer((uint8_t*)rb,32); // Read 32 bytes from I2C
                printf("Read 32 bytes: %d\n",res);

                res = rp_I2C_IOCTL_ReadBuffer((uint8_t*)(rb + 8),16);  // Read 16 bytes from I2C
                printf("Read 16 bytes: %d\n",res); 

                printf("ADC Ch1 High %d\n",rb[2]);
                printf("ADC Ch2 High %d\n",rb[3]);
                printf("ADC Ch1 Low %d\n",rb[4]);
                printf("ADC Ch2 Low %d\n",rb[5]);
                printf("ADC Ch1 Low offset %d\n",rb[6]);
                printf("ADC Ch2 Low offset %d\n",rb[7]);
                printf("DAC Ch1 %d\n",rb[8]);
                printf("DAC Ch2 %d\n",rb[9]);
                printf("DAC Ch1 offset %d\n",rb[10]);
                printf("DAC Ch2 offset %d\n",rb[11]);

                return 0;
            }

    .. tab:: OS 2.00 or newer

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
            #include "rp_hw-calib.h"

            int main(int argc, char *argv[]){

                // This example shows how to work with EEPROM via I2C

                int res = rp_I2C_InitDevice("/dev/i2c-0",0x50); // Init i2c api.
                printf("Init result: %d\n",res);

                res = rp_I2C_setForceMode(true); // Set force mode.
                printf("Set force mode: %d\n",res);

                uint8_t wb[2] = {0,0};
                res = rp_I2C_IOCTL_WriteBuffer(wb,2); // Write position for reading.
                printf("Write 2 bytes: %d\n",res);

                usleep(100000);

                uint8_t rb[1];

                res = rp_I2C_IOCTL_ReadBuffer(rb,1); // Read 1 byte from I2C
                printf("Read 1 byte: %d\n",res);
                uint8_t df = rb[0];
                printf("Data format %d\n",df);
                res = rp_I2C_IOCTL_WriteBuffer(wb,2); // Write position for reading.
                printf("Write 2 bytes: %d\n",res);
                usleep(100000);

                rp_calib_params_t calib;

                if (df == 5){
                    rp_calib_params_universal_t data;
                    uint16_t size = sizeof(data);
                    res = rp_I2C_IOCTL_ReadBuffer((uint8_t*)&data,size);
                    printf("Read %d byte: %d\n",size,res);
                    res = rp_CalibConvertEEPROM((uint8_t*)&data,size,&calib);
                    printf("Convert calib: %d\n",res);
                }else{
                    rp_eepromWpData_t data;
                    uint16_t size = sizeof(data);
                    res = rp_I2C_IOCTL_ReadBuffer((uint8_t*)&data,size);
                    printf("Read %d byte: %d\n",size,res);
                    res = rp_CalibConvertEEPROM((uint8_t*)&data,size,&calib);
                    printf("Convert calib: %d\n",res);
                }
                rp_CalibPrint(&calib);
                return 0;
            }


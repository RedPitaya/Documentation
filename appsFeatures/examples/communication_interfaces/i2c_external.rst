
I2C external
#############

Description
============

This example demonstrates communication with an external 24LC64 EEPROM memory connected to the I2C port of the Red Pitaya using SPCI and API commands. The code below first writes a custom message to the EEPROM and then reads it back.

.. note::

    The following code works for the 24LC64 EEPROM chip and should be modified for use with other external I2C devices. The lower three bits of the 24LC64 EEPROM HW address are hardware defined by the pins on the PCB. In addition, the first two bytes transmitted correspond to the target address in the EEPROM.
    Please refer to the datasheet of your I2C device for the correct addressing and communication protocol.


Required hardware
==================

    - Red Pitaya

.. figure:: ../general_img/RedPitaya_general.png


Required software
=================

.. include:: ../sw_requirement.inc


  
SCPI Code Examples
====================

Code - MATLAB®
---------------

.. code-block:: matlab

    %% Define Red Pitaya as TCP client object

    IP = '192.168.178.56';              % Input IP of your Red Pitaya...
    port = 5000;
    RP = tcpclient(IP, port);

    %% Open connection with your Red Pitaya
    RP.ByteOrder = 'big-endian';
    configureTerminator(RP,'CR/LF');

    writeline(RP,'I2C:DEV80 "/dev/i2c-0"');
    writeline(RP,'I2C:FMODE ON');       % set force mode

    % EEPROM 24LC64 only works through IOCTL

   
    %% Close connection with Red Pitaya
    clear RP;


Code - Python
--------------

.. code-block:: python


  
.. note::

    The Python functions are accessible with the latest version of the redpitaya_scpi.py document available on our |redpitaya_scpi|.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order. The code should function at approximately the same speed without them.

    For further information on functions please consult the redpitaya_scpi.py code.


.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">GitHub</a>



API Code Examples
====================

.. include:: ../c_code_note.inc


Code - C
---------

.. tabs::

    



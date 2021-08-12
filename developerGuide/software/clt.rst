.. _clu:

######################
Command line utilities
######################

*********************************
Red Pitaya command line utilities
*********************************

.. Note::
   
    Command line utilities must not be used in parallel with a WEB application.
   
    For correct operation of the acquire tool, it is mandatory that the correct FPGA image is loaded. Please note,
    the some application can change the FPGA image loaded.
    To load the FPGA image open a terminal on the Red Pitaya and execute the following command:
    
    .. code-block:: shell-session

       cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg





==========================
LED enable/disable utility
==========================

The Red Pitaya LEDs indications can be enabled or disabled through the led_control command-line utility.
Disabling LEDs is important for applications where noise level needs to be reduced to its minimum.

Usage instructions:

.. code-block:: shell-session

    root@rp-f09508:~# led_control

    Usage: led_control -y[=State] | -r[=State] | -e [=State]

        -y    9 Yellow LED. Responsible for the status of reading the memory card.
        -r    Red LED, which is responsible for the heartbeat.
        -e    LEDs on ethernet connector.

    Optional parameter:
        State = [Off | On]  Turns LEDs on or off


For disable:

.. code-block:: shell-session

    root@rp-f09508:~# led_control -y=Off -e=Off -r=Off

For enable:

.. code-block:: shell-session

    root@rp-f09508:~# led_control -y=On -e=On -r=On

======================================================
Other useful information related to command line tools
======================================================

.. toctree::
   :maxdepth: 6
   
   clt_other
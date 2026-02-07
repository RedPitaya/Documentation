
.. _led_util:

LED control utility
==========================

The Red Pitaya's LED indicators can be enabled or disabled using the led_control command line utility. Disabling the LEDs is important for applications where noise levels need to be kept to a minimum.

Use instructions:

.. code-block:: console

    redpitaya> led_control

    Usage: led_control -y[=State] | -r[=State] | -e[=State]

        -y    9 Yellow LED. Responsible for the status of reading the memory card.
        -r    Red LED, which is responsible for the heartbeat.
        -e    LEDs on ethernet connector.

    Optional parameter:
        State = [Off | On]  Turns LEDs on or off


To disable the LEDs:

.. code-block:: console

    root@rp-f09508:~# led_control -y=Off -e=Off -r=Off

To enable the LEDs:

.. code-block:: console

    root@rp-f09508:~# led_control -y=On -e=On -r=On

|

Source code
-----------

The Red Pitaya GitHub repository contains the :rp-github:`source code for the led control utility <RedPitaya/tree/master/Test/led_control>`.

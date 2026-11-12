
.. _led_util:

LED 控制实用程序
==========================

可使用 ``led_control`` 命令行实用程序启用或禁用 Red Pitaya 的 LED 指示灯。对于需要将噪声水平降至最低的应用，禁用 LED 十分重要。

使用说明：

.. tabs::

    .. group-tab:: OS 2.00 及更高版本

        .. code-block:: console

            redpitaya> led_control

            Usage: led_control -y[=State] | -r[=State] | -e[=State]

                -y    9 Yellow LED. Responsible for the status of reading the memory card.
                -r    Red LED, which is responsible for the heartbeat.
                -e    LEDs on ethernet connector.

            Optional parameter:
                State = [Off | On]  Turns LEDs on or off


禁用 LED：

.. code-block:: console

    root@rp-f09508:~# led_control -y=Off -e=Off -r=Off

启用 LED：

.. code-block:: console

    root@rp-f09508:~# led_control -y=On -e=On -r=On

|

源代码
-----------

Red Pitaya GitHub 仓库包含 :rp-github:`LED 控制实用程序的源代码 <RedPitaya/tree/master/tools/led_control>`。

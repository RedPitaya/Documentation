
.. _e3_i2c_controller_util:

E3 I2C 控制器实用程序
==========================

E3 I2C 控制器是一款用于控制 QSPI eMMC 板卡的命令行工具。该工具可通过 I2C 通信读取和写入 QSPI eMMC 板卡的数值，还可控制及读取板卡的电源状态，并检查错误。

软件要求
----------------------

* Red Pitaya OS **2.07-48 或更高版本**。


用法
-----

.. code-block:: shell-session

    Usage: e3_i2c_controller -w hw_id Value [-v]
    Usage: e3_i2c_controller -we hw_id Value [-v]
    Usage: e3_i2c_controller -wd Value [-v]
    Usage: e3_i2c_controller -wde Value [-v]
    Usage: e3_i2c_controller -r [-v]
                    -w    Writes a value to the device at the address: 0x10.
                    -wd   Writes a value to the device at the address: 0x10. HW version is determined automatically.
                    -we   Writes a value to the device at the address: 0x10 and check error. Tool return 0 - no error. 1 - error present.
                    -wde  Writes a value to the device at the address: 0x10 and check error. Tool return 0 - no error. 1 - error present. HW version is determined automatically.
                    -r    Reads a value from a device.
                    -v    Decodes the received values.
    Parameters:
        hw_id = Expansion board version. The value must be in HEX format. (For example 0x01)
        Value = Value in HEX format or in string format. (For example 0x01 or PWR_OFF)

    Value:
                    PWR_OFF = 0x00.
                    PWR_UP = 0x01.
                    PWR_ON = 0x02.
                    PWR_DWN = 0x03.
                    PWR_DWN_RST = 0x04.
                    VERB = 0xFF.

    Examples:
                    e3_i2c_controller -w 0x02 PWR_UP
                    e3_i2c_controller -w 0x1 0x2
                    e3_i2c_controller -we 0x1 0x2
                    e3_i2c_controller -wd 0x2
                    e3_i2c_controller -wd PWR_UP
                    e3_i2c_controller -wde 0x2
                    e3_i2c_controller -r -v
                    e3_i2c_controller -r

该实用程序可在以下 **状态** 之间切换：

* ``PWR_UP`` - 0x01
* ``PWR_ON`` - 0x02
* ``PWR_DWN`` - 0x03
* ``PWR_DWN_RST`` - 0x04
* ``VERB`` - 0xFF - 切换详细输出模式。

切换到其他状态会立即切断 Red Pitaya 单元的电源，因此软件会阻止此操作。
切换详细输出模式不会改变状态。启用详细输出模式时，QSPI eMMC 板卡会将状态信息发送到该板卡上的 UART 总线。

请求更改状态时，QSPI eMMC 板卡会返回以下 **错误代码** 之一：

* ``E3_OK`` - 0x00 - 状态更改成功
* ``E3_NOK`` - 0x01 - 状态更改被阻止；更改到所请求的状态会切断 Red Pitaya 单元的电源。
* ``E3_ERR`` - 0x02 - 状态更改失败；请求了未知状态。

|

源代码
------------

Red Pitaya GitHub 仓库包含 :rp-github:`E3 I2C 控制器实用程序的源代码 <RedPitaya/tree/master/tools/e3_led_controller>`。

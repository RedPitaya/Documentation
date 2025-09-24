

The E3 I2C controller is a command line tool that can be used to control the QSPI eMMC board. The tool can be used to read and write values to the QSPI eMMC board using the I2C communication. The tool can be used to control the power state of the QSPI eMMC board, read the power state of the QSPI eMMC board, and check for errors.

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

The utility can switch between the following **states**:

* ``PWR_UP`` - 0x01
* ``PWR_ON`` - 0x02
* ``PWR_DWN`` - 0x03
* ``PWR_DWN_RST`` - 0x04
* ``VERB`` - 0xFF - Toggle verbose mode.

Switching to other states would immediately cut power to the Red Pitaya unit and is therefore prevented by the software.
Toggling verbose mode does not change the state. When verbose mode is enabled, the QSPI eMMC board will send status information to the UART bus on the QSPI eMMC board.

When requesting a state change, the QSPI eMMC board will return one of the following **error codes**:

* ``E3_OK`` - 0x00 - State change successful
* ``E3_NOK`` - 0x01 - State change prevented. Changing to the requested state would cut the power to the Red Pitaya unit.
* ``E3_ERR`` - 0x02 - State change failed. Unknown state requested.

Source code
------------

The Red Pitaya GitHub repository contains the `source code for the E3 I2C controller utility <https://github.com/RedPitaya/RedPitaya-Examples>`_.

.. TODO Update link to the source code.

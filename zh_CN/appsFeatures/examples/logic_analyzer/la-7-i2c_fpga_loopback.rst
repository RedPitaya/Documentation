.. _LA_i2c_loopback_fpga:

解码 I2C 协议（FPGA 回环）
######################################

描述
============

本示例演示如何使用逻辑分析仪命令解码 I2C 协议。Red Pitaya 在 I2C 端口上生成 I2C 消息，并在指定的数字输入上进行解码。捕获的数据存储在 ``i2c_data.bin`` 文件中，可用于进一步分析。
配置本示例时，请确保 I2C API 设置与 I2C 解码器设置匹配。

将 I2C 引脚连接到数字引脚：

- **I2C SDA (E2) <-> DIO6_P (E1)**
- **I2C SCK (E2) <-> DIO7_P (E1)**


.. include:: la_i2c_settings.inc

.. note::

    Red Pitaya API 的 I2C 速度固定为 400 kHz。


所需硬件
==================

    - Red Pitaya
    - 引脚跳线

.. figure:: ../general_img/RedPitaya_general.png

|

所需软件
===================

.. include:: ../sw_requirements_indev.inc

API 代码示例
==================

代码 - Python
--------------

.. code-block:: python

    #!/usr/bin/python3
    """ Example of using the Logic Analyzer Python API to decode an internal I2C signal on Red Pitaya.
    """
    import sys
    import time
    import rp_la
    import rp_hw
    import rp_hw_profiles
    import numpy as np
    from rp_overlay import overlay

    # Define callback
    class Callback(rp_la.CLACallback):
        def captureStatus(self, controller, isTimeout, bytes, samples, preTrig, postTrig):
            print("CaptureStatus timeout =", isTimeout, "bytes =", bytes, "samples =", samples, "preTrig =", preTrig, "postTrig =", postTrig)

        def decodeDone(self, controller, name):
            print("Decode done ", name)

    print("""Before the test, connect:
        - I2C SDA (E2) <-> any DIO _P (E1)
        - I2C SCL (E2) <-> any DIO _P (E1)""")
    ####! Read data from the internal EEPROM and decode it with the I2C decoder !####

    ## I2C API settins ##
    dev_addr = 0b1010000
    eeprom_size = 8192
    page_size = 32
    offset = 0x0000

    ## I2C decoder settings ##
    i2c_acq_speed = 400000                  # Fixed to 400 kHz
    i2c_addr_format = 0                     # Shifted = 0, Unshifted = 1
    i2c_invert_bit = 0
    i2c_sda = 7                             # I2C SDA (1 - first line.  Valid values are from 1 to 8)
    i2c_scl = 8                             # I2C SCL

    # LA acquisition
    trigger_ch = rp_la.LA_T_CHANNEL_8               # Trigger chanels are 1 to 8
    trig_edge = rp_la.LA_RISING_OR_FALLING          # LOW, HIGH, RISING, FALLING, RISING_OR_FALLING

    enable_RLE = True
    decimation = 32
    acq_rate = int(rp_hw_profiles.rp_HPGetBaseSpeedHzOrDefault() / decimation)
    pre_trig_samples = int(125e6/decimation * 1e-3)
    post_trig_samples = int(125e6/decimation * 10e-3)
    print(f"Pre post trigger: {pre_trig_samples} {post_trig_samples}")


    # Change FPGA image to logic analyzer "logic"
    fpga = overlay("logic")

    # Create controller and initialize FPGA
    rp_cla = rp_la.CLAController()
    rp_cla.initFpga()

    callback = Callback()
    rp_cla.setDelegate(callback.__disown__())

    # Initialize I2C API and configure settings
    res = rp_hw.rp_I2C_InitDevice("/dev/i2c-0", dev_addr)
    print(f"InitDevice: {'success' if not res else 'fail'}")
    rp_hw.rp_I2C_setForceMode(True)

    # Copy EEPROM address data to buffer
    buff_addr = rp_hw.Buffer(2)
    buff_addr[0] = offset >> 8
    buff_addr[1] = offset & 0xFF

    buff_i2c = rp_hw.Buffer(page_size)      # Create buffer for I2C data

    # Set LA parameters
    rp_cla.setEnableRLE(True)
    rp_cla.setDecimation(decimation)
    rp_cla.setTrigger(trigger_ch, trig_edge)
    rp_cla.setPreTriggerSamples(pre_trig_samples)
    rp_cla.setPostTriggerSamples(post_trig_samples)

    # Add I2C decoder and configure settings
    rp_cla.addDecoder("I2C", rp_la.LA_DECODER_I2C)
    rp_cla.setDecoderSettingsUInt("I2C", "acq_speed", acq_rate)
    rp_cla.setDecoderSettingsUInt("I2C", "invert_bit", i2c_invert_bit)
    rp_cla.setDecoderSettingsUInt("I2C", "address_format", i2c_addr_format)
    rp_cla.setDecoderSettingsUInt("I2C", "scl", i2c_scl)
    rp_cla.setDecoderSettingsUInt("I2C", "sda", i2c_sda)
    print(f"I2C decoder settings: {rp_cla.getDecoderSettings('I2C')}")

    # Start acquisition
    rp_cla.runAsync(0)
    print("Started acquire data")

    time.sleep(0.1)     # Wait for LA to acquire some data

    # Reset read/write counter to the wanted address
    rp_hw.rp_I2C_IOCTL_WriteBuffer(buff_addr, 2)
    time.sleep(6e3/1e6) # 6 ms

    rp_hw.rp_I2C_IOCTL_ReadBuffer(buff_i2c, page_size)

    # Wait for trigger
    res = rp_cla.wait(1000)
    if res:
        print("Exit by timeout")
        sys.exit(1)

    # Save data to file
    rp_cla.saveCaptureDataToFile("i2c_data.bin")

    # Get captured data
    rawBytesCount = rp_cla.getCapturedDataSize()
    raw_data = np.zeros(rawBytesCount, dtype=np.uint8)
    print(f"Packed samples count: {rp_cla.getDataNP(raw_data)}")

    # Get unpacked RLE data
    rle_data = np.zeros(rp_cla.getCapturedSamples(), dtype=np.uint8)
    print(f"Unpacked samples count: {rp_cla.getUnpackedRLEDataNP(rle_data)}")     
    print(f"RLE DATA {raw_data}")
    print(f"UNPACKED DATA {rle_data}\n")

    rp_cla.printRLE(False)

    print("\nDecoded data")
    decode = rp_cla.getDecodedData("I2C")
    for index in range(len(decode)):
        print(f"{rp_cla.getAnnotation(rp_la.LA_DECODER_I2C, decode[index]['control'])} = {decode[index]}")

    del rp_cla

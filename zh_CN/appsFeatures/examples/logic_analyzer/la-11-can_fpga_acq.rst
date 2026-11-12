.. _LA_can_fpga_acq:

解码 CAN 协议（FPGA 采集）
##########################################

描述
============

本示例演示如何使用逻辑分析仪命令解码 CAN 协议。Red Pitaya 在指定的数字输入上捕获数据并进行解码。捕获的数据存储在 ``can_data.bin`` 文件中，可用于进一步分析。
配置本示例时，请确保捕获的 CAN 设置与 CAN 解码器设置相匹配。

.. include:: la_can_settings.inc


所需硬件
==================

    - Red Pitaya
    - CAN 收发器（例如 |MCP2542-Click|）
    - 引脚跳线

没有 CAN 收发器时，无法解码 CAN 协议。

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
    """ Example of using the Logic Analyzer Python API to decode an external CAN signal on Red Pitaya.
    """

    import sys
    import time
    import rp_la
    import rp_hw_profiles
    import numpy as np
    from rp_overlay import overlay

    # Define callback
    class Callback(rp_la.CLACallback):
        def captureStatus(self, controller, isTimeout, bytes, samples, preTrig, postTrig):
            print("CaptureStatus timeout =", isTimeout, "bytes =", bytes, "samples =", samples, "preTrig =", preTrig, "postTrig =", postTrig)

        def decodeDone(self, controller, name):
            print("Decode done ", name)

    # CAN decoder settings
    can_decoder = "CAN"
    dec_fast_bitrate = 2000000
    dec_invert_bit = 0
    dec_nominal_bitrate = 200000
    dec_rx = 1
    dec_sample_point = 87

    # LA acquisition
    trigger_ch = rp_la.LA_T_CHANNEL_1               # Trigger chanels are 1 to 8
    trig_edge = rp_la.LA_RISING_OR_FALLING          # LOW, HIGH, RISING, FALLING, RISING_OR_FALLING

    enable_RLE = True
    decimation = 16
    acq_rate = int(rp_hw_profiles.rp_HPGetBaseSpeedHzOrDefault() / decimation)
    pre_trig_samples = int(125e6/decimation * 1e-3)
    post_trig_samples = int(125e6/decimation * 3e-3)
    print(f"Pre post trigger: {pre_trig_samples} {post_trig_samples}")


    # Change FPGA image to logic analyzer "logic"
    fpga = overlay("logic")

    # Create controller and initialize FPGA
    rp_cla = rp_la.CLAController()
    rp_cla.initFpga()

    callback = Callback()
    rp_cla.setDelegate(callback.__disown__())

    # Set LA parameters
    rp_cla.setEnableRLE(True)
    rp_cla.setDecimation(decimation)
    rp_cla.setTrigger(trigger_ch, trig_edge)
    rp_cla.setPreTriggerSamples(pre_trig_samples)
    rp_cla.setPostTriggerSamples(post_trig_samples)

    # Add I2C decoder and configure settings
    rp_cla.addDecoder(can_decoder, rp_la.LA_DECODER_CAN)
    rp_cla.setDecoderSettingsUInt(can_decoder, "acq_speed", acq_rate)
    rp_cla.setDecoderSettingsUInt(can_decoder, "invert_bit", dec_invert_bit)
    rp_cla.setDecoderSettingsUInt(can_decoder, "fast_bitrate", dec_fast_bitrate)
    rp_cla.setDecoderSettingsUInt(can_decoder, "nominal_bitrate", dec_nominal_bitrate)
    rp_cla.setDecoderSettingsUInt(can_decoder, "rx", dec_rx)
    rp_cla.setDecoderSettingsUInt(can_decoder, "sample_point", dec_sample_point)

    print(f"CAN decoder settings: {rp_cla.getDecoderSettings(f'{can_decoder}')}")

    # Start acquisition
    rp_cla.runAsync(0)
    print("Started data acquisition")

    time.sleep(0.1)             # Wait for LA to acquire some data

    # Wait for trigger
    res = rp_cla.wait(0)        # No timeout set
    if res:
        print("Exit by timeout")
        sys.exit(1)

    # Save data to file
    rp_cla.saveCaptureDataToFile("can_data.bin")

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
    decode = rp_cla.getDecodedData(can_decoder)
    for index in range(len(decode)):
        print(f"{rp_cla.getAnnotation(rp_la.LA_DECODER_CAN, decode[index]['control'])} = {decode[index]}")

    # Close the interface and release resources
    print("End Program")
    del rp_cla

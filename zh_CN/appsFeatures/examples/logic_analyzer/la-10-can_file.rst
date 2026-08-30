.. _LA_can_file:

解码 CAN 协议（从文件读取）
######################################

.. note::

    CAN 协议无法提供 FPGA 回环示例，因为逻辑分析仪和 CAN 协议共用相同的数字引脚。

说明
============

本示例演示如何使用逻辑分析仪命令解码 CAN 协议。Red Pitaya 从 ``can_data.bin`` 文件加载 CAN 数据并进行解码。
配置本示例时，请确保 CAN 解码器设置与采集设置相匹配。

.. include:: la_can_settings.inc


所需硬件
==================

    - Red Pitaya

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
    """ Example for decoding LA CAN data from file. Settings are also loaded from a file.
    """
    import rp_la

    rp_cla = rp_la.CLAController()

    rp_cla.loadFromFile("can_data.bin", True, 0)

    rp_cla.addDecoder("CAN", rp_la.LA_DECODER_CAN)
    f = open("can_settings.json", "r", encoding="utf-8")
    rp_cla.setDecoderSettings("CAN", f.read())

    print("Settings:")
    print(rp_cla.getDecoderSettings("CAN"))

    print("\nDecoded data\n")
    decode = rp_cla.decode("CAN")
    for index in range(len(decode)):
        print(rp_cla.getAnnotation(rp_la.LA_DECODER_CAN, decode[index]['control']), " = ", decode[index])
    del rp_cla



修改解码器设置
===========================

.. code-block:: python

    #!/usr/bin/python3
    """This script demonstrates how to modify the settings of the CAN decoder in the json files."""

    import json
    import rp_hw_profiles
    import rp_la

    # Define callback
    class Callback(rp_la.CLACallback):
        def captureStatus(self, controller, isTimeout, bytes, samples, preTrig, postTrig):
            print("captureStatus timeout =",isTimeout,"bytes =",bytes,"samples =",samples,"preTrig =",preTrig,"postTrig =",postTrig)

        def decodeDone(self, controller, name):
            print("Decode done ",name)

    can_decoder = "CAN"

    decimation = 16
    acq_rate = int(rp_hw_profiles.rp_HPGetBaseSpeedHzOrDefault() / decimation)

    # Create controller
    rp_cla = rp_la.CLAController()
    callback = Callback()
    rp_cla.setDelegate(callback.__disown__())

    # LA FPGA must be loaded/LA Application must be open
    rp_cla.initFpga()

    # Add decoders
    rp_cla.addDecoder(can_decoder, rp_la.LA_DECODER_CAN)

    # Get settings from Red Pitaya
    can_settings = rp_cla.getDecoderSettings(can_decoder)
    print(f"CAN decoder settings: {can_settings}")

    # Modify settings
    can_settings = json.loads(can_settings)

    can_settings["acq_speed"] = acq_rate        # Acquisition speed =! decimation settings
    can_settings["fast_bitrate"] = 2000000
    can_settings["nominal_bitrate"] = 200000
    can_settings["invert_bit"] = 0
    can_settings["rx"] = 1                      # CAN RX   (1 - first line.  Valid values are from 1 to 8), 0 == disabled
    can_settings["sample_point"] = 87.5

    # Save json data to a file
    with open("can_settings.json", "w", encoding='utf8') as json_file:
        json.dump(can_settings, json_file, indent=4)

    del rp_cla


将解码器设置保存到 json 文件
=====================================

.. code-block:: python

    #!/usr/bin/python3
    """This script demonstrates how to save the settings of the CAN decoder to a json file."""

    import json
    import rp_la

    # Define callback
    class Callback(rp_la.CLACallback):
        def captureStatus(self, controller, isTimeout, bytes, samples, preTrig, postTrig):
            print("captureStatus timeout =",isTimeout,"bytes =",bytes,"samples =",samples,"preTrig =",preTrig,"postTrig =",postTrig)

        def decodeDone(self, controller, name):
            print("Decode done ",name)

    # Create controller
    rp_cla = rp_la.CLAController()
    callback = Callback()
    rp_cla.setDelegate(callback.__disown__())

    # LA FPGA must be loaded/LA Application must be open
    rp_cla.initFpga()

    # Add decoders
    rp_cla.addDecoder("CAN", rp_la.LA_DECODER_CAN)

    # Get settings from Red Pitaya
    can_settings = rp_cla.getDecoderSettings("CAN")

    print(f"CAN decoder settings: {can_settings}")

    # Save json data to a file
    can_settings = json.loads(can_settings)
    with open("can_settings.json", "w", encoding='utf8') as json_file:
        json.dump(can_settings, json_file, indent=4)

    del rp_cla

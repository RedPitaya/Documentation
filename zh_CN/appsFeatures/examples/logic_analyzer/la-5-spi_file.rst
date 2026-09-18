.. _LA_spi_file:

解码 SPI 协议（来自文件）
######################################

描述
============

本示例演示如何使用逻辑分析仪命令解码 SPI 协议。Red Pitaya 从 ``spi_data.bin`` 文件加载 SPI 数据并进行解码。
配置本示例时，请确保 SPI 解码器设置与捕获设置相匹配。

.. include:: la_spi_settings.inc

.. note::

    Red Pitaya API 的 SPI 速度会四舍五入到最接近的可编程值。对于 1 MHz，实际速度为 SPI 时钟速度 781250 Hz。


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
    """ Example for decoding LA SPI data from file. Settings are also loaded from a file.
    """
    import rp_la

    rp_cla = rp_la.CLAController()

    rp_cla.loadFromFile("spi_data.bin", True, 0)

    rp_cla.addDecoder("SPI", rp_la.LA_DECODER_SPI)
    f = open("spi_settings.json", "r", encoding='utf-8')
    rp_cla.setDecoderSettings("SPI", f.read())

    print("Settings:")
    print(rp_cla.getDecoderSettings("SPI"))

    print("\nDecoded data\n")
    decode = rp_cla.decode("SPI")
    for index in range(len(decode)):
        print(rp_cla.getAnnotation(rp_la.LA_DECODER_SPI,decode[index]['control'])," = ",decode[index])
    del rp_cla


修改解码器设置
===========================

.. code-block:: python

    #!/usr/bin/python3
    """This script demonstrates how to modify the settings of the SPI decoder in the json files."""

    import json
    import rp_hw_profiles
    import rp_la

    # Define callback
    class Callback(rp_la.CLACallback):
        def captureStatus(self, controller, isTimeout, bytes, samples, preTrig, postTrig):
            print("captureStatus timeout =",isTimeout,"bytes =",bytes,"samples =",samples,"preTrig =",preTrig,"postTrig =",postTrig)

        def decodeDone(self, controller, name):
            print("Decode done ",name)

    spi_decoder = "SPI"

    decimation = 16
    acq_rate = int(rp_hw_profiles.rp_HPGetBaseSpeedHzOrDefault() / decimation)

    # Create controller
    rp_cla = rp_la.CLAController()

    callback = Callback()
    rp_cla.setDelegate(callback.__disown__())

    # LA FPGA must be loaded/LA Application must be open
    rp_cla.initFpga()

    # Add decoders
    rp_cla.addDecoder(spi_decoder, rp_la.LA_DECODER_SPI)

    # Get settings from Red Pitaya
    spi_settings = rp_cla.getDecoderSettings(spi_decoder)
    print(f"SPI decoder settings: {spi_settings}")

    # Modify settings
    spi_settings = json.loads(spi_settings)

    ## SPI decoder settings ##
    # - LISL - Low  idle level, sample on leading edge  - cpol=0, cpha=0
    # - LIST - Low  idle level, sample on trailing edge - cpol=0, cpha=1
    # - HISL - High idle level, sample on leading edge  - cpol=1, cpha=0
    # - HIST - High idle level, sample on trailing edge - cpol=1, cpha=1

    spi_settings["acq_speed"  ] = acq_rate      # Acquisition speed =! decimation setting
    spi_settings["bit_order"  ] = 0             # MsbFirst = 0, LsbFirst = 1
    spi_settings["cpha"       ] = 0             # 0, 1
    spi_settings["cpol"       ] = 0             # 0, 1
    spi_settings["cs_polarity"] = 0             # ActiveLow = 0, ActiveHigh = 1
    spi_settings["invert_bit" ] = 0
    spi_settings["word_size"  ] = 8             # 7, 8
    spi_settings["clk"        ] = 3             # SPI CLK   (1 - first line.  Valid values are from 1 to 8), 0 == disabled
    spi_settings["cs"         ] = 4             # SPI CS
    spi_settings["miso"       ] = 1             # SPI MISO
    spi_settings["mosi"       ] = 2             # SPI MOSI

    # Save json data to a file
    with open("spi_settings.json", "w", encoding='utf8') as json_file:
        json.dump(spi_settings, json_file, indent=4)

    del rp_cla


将解码器设置保存到 json 文件
=====================================

.. code-block:: python

    #!/usr/bin/python3
    """This script demonstrates how to save the settings of the SPI decoder to a json file."""

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
    rp_cla.addDecoder("SPI", rp_la.LA_DECODER_SPI)

    # Get settings from Red Pitaya
    spi_settings = rp_cla.getDecoderSettings("SPI")

    print(f"SPI decoder settings: {spi_settings}")

    # Save json data to a file
    spi_settings = json.loads(spi_settings)
    with open("spi_settings.json", "w", encoding='utf8') as json_file:
        json.dump(spi_settings, json_file, indent=4)

    del rp_cla

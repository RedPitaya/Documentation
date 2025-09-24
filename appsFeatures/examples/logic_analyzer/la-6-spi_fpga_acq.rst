.. _LA_spi_fpga_acq:

Decoding SPI protocol (FPGA acquisition)
##########################################

Description
============

This example demonstrates how to decode the SPI protocol using logic analyser commands. Red Pitaya captures data on the specified digital inputs and decodes it. The captured data is stored in the "spi_data.bin" file, which can be used for further analysis.
When configuring the example, make sure that the captured SPI settings match the SPI decoder settings.

.. include:: la_spi_settings.inc


Required hardware
==================

    - Red Pitaya
    - pin jumper wires

.. figure:: ../general_img/RedPitaya_general.png

|

Required software
===================

.. include:: ../sw_requirements_indev.inc

API Code Examples
==================

Code - Python
--------------

.. code-block:: python

    #!/usr/bin/python3
    """ Example of using the Logic Analyzer Python API to decode an external SPI signal on Red Pitaya.
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


    ## SPI decoder settings ##
    # - LISL - Low  idle level, sample on leading edge  - cpol=0, cpha=0
    # - LIST - Low  idle level, sample on trailing edge - cpol=0, cpha=1
    # - HISL - High idle level, sample on leading edge  - cpol=1, cpha=0
    # - HIST - High idle level, sample on trailing edge - cpol=1, cpha=1

    dec_bit_order = 0                   # MsbFirst = 0, LsbFirst = 1
    dec_cpha = 0                        # 0, 1
    dec_cpol = 0                        # 0, 1
    dec_invert_bit = 0
    dec_word_size = 8                   # 7, 8
    dec_cs_polarity = 0                 # ActiveLow = 0, ActiveHigh = 1
    dec_cs = 4                          # SPI CS   (1 - first line.  Valid values are from 1 to 8)
    dec_clk = 3                         # SPI CLK
    dec_miso = 1                        # SPI MISO
    dec_mosi = 2                        # SPI MOSI

    # LA acquisition
    trigger_ch = rp_la.LA_T_CHANNEL_3       # Trigger chanels are 1 to 8
    trig_edge = rp_la.LA_RISING_OR_FALLING  # LOW, HIGH, RISING, FALLING, RISING_OR_FALLING

    enable_RLE = True
    decimation = 8
    acq_rate = int(rp_hw_profiles.rp_HPGetBaseSpeedHzOrDefault() / decimation)
    pre_trig_samples = int(125e6/decimation * 1e-3)
    post_trig_samples = int(125e6/decimation * 2e-3)
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

    # Add SPI decoder and configure decoder settings
    rp_cla.addDecoder("SPI", rp_la.LA_DECODER_SPI)
    rp_cla.setDecoderSettingsUInt("SPI", "acq_speed", acq_rate)
    rp_cla.setDecoderSettingsUInt("SPI", "bitOrder", dec_bit_order)
    rp_cla.setDecoderSettingsUInt("SPI", "cpha", dec_cpha)
    rp_cla.setDecoderSettingsUInt("SPI", "cpol", dec_cpol)
    rp_cla.setDecoderSettingsUInt("SPI", "invert_bit", dec_invert_bit)
    rp_cla.setDecoderSettingsUInt("SPI", "word_size", dec_word_size)
    rp_cla.setDecoderSettingsUInt("SPI", "cs_polarity", dec_cs_polarity)
    rp_cla.setDecoderSettingsUInt("SPI", "cs", dec_cs)
    rp_cla.setDecoderSettingsUInt("SPI", "clk", dec_clk)
    rp_cla.setDecoderSettingsUInt("SPI", "miso", dec_miso)
    rp_cla.setDecoderSettingsUInt("SPI", "mosi", dec_mosi)

    # Start acquisition
    rp_cla.runAsync(0)
    print("Started acquire data")

    time.sleep(0.1)             # Wait for LA to acquire some data

    # Wait for trigger
    res = rp_cla.wait(0)        # No timeout set
    if res:
        print("Exit by timeout")
        sys.exit(1)

    # Save data to file
    rp_cla.saveCaptureDataToFile("spi_data.bin")

    # Get data
    rawBytesCount = rp_cla.getCapturedDataSize()
    raw_data = np.zeros(rawBytesCount, dtype=np.uint8)
    print(f"Packed samples count: {rp_cla.getDataNP(raw_data)}")

    # Create RLE data
    rle_data = np.zeros(rp_cla.getCapturedSamples(), dtype=np.uint8)
    print(f"Unpacked samples count: {rp_cla.getUnpackedRLEDataNP(rle_data)}")
    print(f"RLE DATA {raw_data}")
    print(f"UNPACKED DATA {rle_data}\n")

    rp_cla.printRLE(False)

    print("\nDecoded data")
    decode = rp_cla.getDecodedData("SPI")
    for index in range(len(decode)):
        print(f"{rp_cla.getAnnotation(rp_la.LA_DECODER_SPI, decode[index]['control'])} = {decode[index]}")

    print("End program")
    del rp_cla

.. _LA_uart_loopback_fpga:

Decoding UART protocol (FPGA loopback)
######################################

Description
============

This example demonstrates how to decode the UART protocol using logic analyser commands. Red Pitaya generates a UART message on the UART ports and decodes it on the specified digital inputs. The captured data is stored in the "uart_data.bin" file, which can be used for further analysis.
When configuring the example, make sure that the UART API settings match the UART decoder settings.

Connect the **UART TX (E2) pin to DIO4_P (E1)** before running the example. The UART RX pin can be left unconnected as it does not transmit any data.

.. include:: la_uart_settings.inc


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
    """ Example of using the Logic Analyzer Python API to decode an internal UART signal on Red Pitaya.
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

    print("Before the test, connect the output UART TX (E2) <-> DIO4_P (E1) !!!")

    data = list("TEST string")
    data_int = [ord(char) for char in data] # Convert data to ASCII values
    data_size = len(data_int)

    ## UART API settins ##
    uart_speed = 921600                     # 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600
    uart_timeout = 10                       # 0 - 255
    uart_word_size = rp_hw.RP_UART_CS8      # CS6, CS7, CS8
    uart_parity = rp_hw.RP_UART_ODD         # NONE, EVEN, ODD, MARK, SPACE
    uart_stop_bits = rp_hw.RP_UART_STOP1    # STOP1, STOP2

    ## UART decoder settings ##
    dec_baudrate = 921600                   # 1200,2400,4800,9600,19200,38400,57600,115200,230400,576000,921600
    dec_bit_order = 0                       # LSB_FIRST = 0, MSB_FIRST = 1
    dec_invert = 0
    dec_num_data_bits = 8                   # 5, 6, 7, 8, 9
    dec_num_stop_bits = 1                   # STOP_BITS_NO = 0, STOP_BITS_05 = 1, STOP_BITS_10 = 2, STOP_BITS_15 = 3, STOP_BITS_20 = 4
    dec_parity = 2                          # NONE = 0, EVEN = 1, ODD = 2, ALWAYS_0 = 3, ALWAYS_1 = 4
    dec_rx = 5                              # UART RX (1 - first line.  Valid values are from 1 to 8)
    dec_tx = 6                              # UART TX
    dec_timeout_ms = 1000

    # LA acquisition
    trigger_ch = rp_la.LA_T_CHANNEL_5               # Trigger chanels are 1 to 8
    trig_edge = rp_la.LA_RISING_OR_FALLING          # LA_LOW, LA_HIGH, LA_RISING, LA_FALLING, LA_RISING_OR_FALLING

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

    # Initialize UART API and configure settings
    rp_hw.rp_UartInit()
    rp_hw.rp_UartSetSpeed(uart_speed)
    rp_hw.rp_UartSetBits(uart_word_size)
    rp_hw.rp_UartSetStopBits(uart_stop_bits)
    rp_hw.rp_UartSetParityMode(uart_parity)
    rp_hw.rp_UartSetSettings()

    # Copy data to buffer
    buff_uart = rp_hw.Buffer(data_size)
    for i in range(data_size):
        buff_uart[i] = data_int[i]

    # Set LA parameters
    rp_cla.setEnableRLE(True)
    rp_cla.setDecimation(decimation)
    rp_cla.setTrigger(trigger_ch, trig_edge)
    rp_cla.setPreTriggerSamples(pre_trig_samples)
    rp_cla.setPostTriggerSamples(post_trig_samples)

    # Add UART decoder and configure settings
    rp_cla.addDecoder("UART", rp_la.LA_DECODER_UART)
    rp_cla.setDecoderSettingsUInt("UART", "acq_speed", acq_rate)
    rp_cla.setDecoderSettingsUInt("UART", "baudrate", dec_baudrate)
    rp_cla.setDecoderSettingsUInt("UART", "bitOrder", dec_bit_order)
    rp_cla.setDecoderSettingsUInt("UART", "invert", dec_invert)
    rp_cla.setDecoderSettingsUInt("UART", "num_data_bits", dec_num_data_bits)
    rp_cla.setDecoderSettingsUInt("UART", "num_stop_bits", dec_num_stop_bits)
    rp_cla.setDecoderSettingsUInt("UART", "parity", dec_parity)
    rp_cla.setDecoderSettingsUInt("UART", "rx", dec_rx)
    rp_cla.setDecoderSettingsUInt("UART", "tx", dec_tx)

    # Start acquisition
    rp_cla.runAsync(0)
    print("Started acquire data")

    time.sleep(0.1)     # Wait for LA to acquire some data

    # Write data to UART
    rp_hw.rp_UartWrite(buff_uart, data_size)

    # Wait for trigger
    res = rp_cla.wait(1000)
    if res:
        print("Exit by timeout")
        sys.exit(1)

    # Save data to file
    rp_cla.saveCaptureDataToFile("uart_data.bin")

    # Get data
    rawBytesCount = rp_cla.getCapturedDataSize()
    raw_data = np.zeros(rawBytesCount, dtype=np.uint8)
    print(f"Packed samples count: {rp_cla.getDataNP(raw_data)}")

    # Get RLE data
    rle_data = np.zeros(rp_cla.getCapturedSamples(), dtype=np.uint8)
    print(f"Unpacked samples count: {rp_cla.getUnpackedRLEDataNP(rle_data)}")     
    print(f"RLE DATA {raw_data}")
    print(f"UNPACKED DATA {rle_data}\n")

    rp_cla.printRLE(False)

    print("\nDecoded data")
    decode = rp_cla.getDecodedData("UART")
    for index in range(len(decode)):
        print(f"{rp_cla.getAnnotation(rp_la.LA_DECODER_UART, decode[index]['control'])} = {decode[index]}")

    # Release resources
    del rp_cla


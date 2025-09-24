.. _LA_uart_file:

Decoding UART protocol (from file)
######################################

Description
============

This example demonstrates how to decode the UART protocol using logic analyser commands. Red Pitaya loads the UART data from the "uart_data.bin" file and decodes it.
When configuring the example, make sure that the UART decoder settings match the capture settings.

.. include:: la_uart_settings.inc


Required hardware
==================

    - Red Pitaya

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
    """ Example for decoding LA UART data from file. Settings are also loaded from a file.
    """
    import rp_la

    rp_cla = rp_la.CLAController()

    rp_cla.loadFromFile("uart_data.bin", True, 0)

    rp_cla.addDecoder("UART", rp_la.LA_DECODER_UART)
    f = open("uart_settings.json", "r", encoding='utf8')
    rp_cla.setDecoderSettings("UART", f.read())

    print("Settings:")
    print(rp_cla.getDecoderSettings("UART"))

    print("\nDecoded data\n")
    decode = rp_cla.decode("UART")
    for index in range(len(decode)):
        print(rp_cla.getAnnotation(rp_la.LA_DECODER_UART,decode[index]['control'])," = ",decode[index])
    del rp_cla


Modifying decoder settings
===========================

.. code-block:: python

    #!/usr/bin/python3
    """This script demonstrates how to modify the settings of the UART decoder in the json files."""

    import json
    import rp_hw_profiles
    import rp_la

    # Define callback
    class Callback(rp_la.CLACallback):
        def captureStatus(self, controller, isTimeout, bytes, samples, preTrig, postTrig):
            print("captureStatus timeout =",isTimeout,"bytes =",bytes,"samples =",samples,"preTrig =",preTrig,"postTrig =",postTrig)

        def decodeDone(self, controller, name):
            print("Decode done ",name)

    uart_decoder = "UART"

    decimation = 16
    acq_rate = int(rp_hw_profiles.rp_HPGetBaseSpeedHzOrDefault() / decimation)

    # Create controller
    rp_cla = rp_la.CLAController()

    callback = Callback()
    rp_cla.setDelegate(callback.__disown__())

    # LA FPGA must be loaded/LA Application must be open
    rp_cla.initFpga()

    # Add decoders
    rp_cla.addDecoder(uart_decoder, rp_la.LA_DECODER_UART)

    # Get settings from Red Pitaya
    uart_settings = rp_cla.getDecoderSettings(uart_decoder)
    print(f"UART decoder settings: {uart_settings}")

    # Modify settings
    uart_settings = json.loads(uart_settings)

    uart_settings["acq_speed"    ] = acq_rate   # Acquisition speed =! decimation setting
    uart_settings["baudrate"     ] = 921600     # 1200,2400,4800,9600,19200,38400,57600,115200,230400,576000,921600
    uart_settings["bitOrder"     ] = 0          # LSB_FIRST = 0, MSB_FIRST = 1
    uart_settings["invert"       ] = 0
    uart_settings["num_data_bits"] = 8          # 5, 6, 7, 8, 9
    uart_settings["num_stop_bits"] = 1          # 0 = 0, 0.5 = 1, 1.0 = 2, 1.5 = 3, 2.0 = 4
    uart_settings["parity"       ] = 2          # NONE = 0, EVEN = 1, ODD = 2, ALWAYS_0 = 3, ALWAYS_1 = 4
    uart_settings["rx"           ] = 1          # UART RX   (1 - first line.  Valid values are from 1 to 8), 0 == disabled
    uart_settings["tx"           ] = 0          # UART TX

    # Save json data to a file
    with open("uart_settings.json", "w", encoding='utf8') as json_file:
        json.dump(uart_settings, json_file, indent=4)

    del rp_cla


Save decoder settings to a json file
=====================================

.. code-block:: python

    #!/usr/bin/python3
    """This script demonstrates how to save the settings of the UART decoder to a json file."""

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
    rp_cla.addDecoder("UART", rp_la.LA_DECODER_UART)

    # Get settings from Red Pitaya
    uart_settings = rp_cla.getDecoderSettings("UART")

    print(f"UART decoder settings: {uart_settings}")

    # Save json data to a file
    uart_settings = json.loads(uart_settings)
    with open("uart_settings.json", "w", encoding='utf8') as json_file:
        json.dump(uart_settings, json_file, indent=4)

    del rp_cla

.. _LA_i2c_file:

Decoding I2C protocol (from file)
######################################

Description
============

This example demonstrates how to decode the I2C protocol using logic analyser commands. Red Pitaya loads the I2C data from the "i2c_data.bin" file and decodes it.
When configuring the example, make sure that the I2C decoder settings match the capture settings.

.. include:: la_i2c_settings.inc


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
    """ Example for decoding LA I2C data from file. Settings are also loaded from a file.
    """
    import rp_la

    rp_cla = rp_la.CLAController()

    rp_cla.loadFromFile("i2c_data.bin", True, 0)

    rp_cla.addDecoder("I2C", rp_la.LA_DECODER_I2C)
    f = open("i2c_settings.json", "r", encoding="utf-8")
    rp_cla.setDecoderSettings("I2C", f.read())

    print("Settings:")
    print(rp_cla.getDecoderSettings("I2C"))

    print("\nDecoded data\n")
    decode = rp_cla.decode("I2C")
    for index in range(len(decode)):
        print(rp_cla.getAnnotation(rp_la.LA_DECODER_I2C, decode[index]['control']), " = ", decode[index])
    del rp_cla


Modifying decoder settings
===========================

.. code-block:: python

    #!/usr/bin/python3
    """This script demonstrates how to modify the settings of the I2C decoder in the json files."""

    import json
    import rp_hw_profiles
    import rp_la

    # Define callback
    class Callback(rp_la.CLACallback):
        def captureStatus(self, controller, isTimeout, bytes, samples, preTrig, postTrig):
            print("captureStatus timeout =",isTimeout,"bytes =",bytes,"samples =",samples,"preTrig =",preTrig,"postTrig =",postTrig)

        def decodeDone(self, controller, name):
            print("Decode done ",name)

    i2c_decoder = "I2C"

    decimation = 16
    acq_rate = int(rp_hw_profiles.rp_HPGetBaseSpeedHzOrDefault() / decimation)

    # Create controller
    rp_cla = rp_la.CLAController()

    callback = Callback()
    rp_cla.setDelegate(callback.__disown__())

    # LA FPGA must be loaded/LA Application must be open
    rp_cla.initFpga()

    # Add decoders
    rp_cla.addDecoder(i2c_decoder, rp_la.LA_DECODER_I2C)

    # Get settings from Red Pitaya
    i2c_settings = rp_cla.getDecoderSettings(i2c_decoder)
    print(f"I2C decoder settings: {i2c_settings}")

    # Modify settings
    i2c_settings = json.loads(i2c_settings)

    i2c_settings["acq_speed"     ] = 400000     # Fixed to 400 kHz
    i2c_settings["address_format"] = 0          # Shifted = 0, Unshifted = 1
    i2c_settings["invert_bit"    ] = 0
    i2c_settings["scl"           ] = 1          # I2C SCL   (1 - first line.  Valid values are from 1 to 8), 0 == disabled
    i2c_settings["sda"           ] = 2          # I2C SDA


    # Save json data to a file
    with open("i2c_settings.json", "w", encoding='utf8') as json_file:
        json.dump(i2c_settings, json_file, indent=4)

    del rp_cla


Save decoder settings to a json file
=====================================

.. code-block:: python

    #!/usr/bin/python3
    """This script demonstrates how to save the settings of the I2C decoder to a json file."""

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
    rp_cla.addDecoder("I2C", rp_la.LA_DECODER_I2C)

    # Get settings from Red Pitaya
    i2c_settings = rp_cla.getDecoderSettings("I2C")

    print(f"I2C decoder settings: {i2c_settings}")

    # Save json data to a file
    i2c_settings = json.loads(i2c_settings)
    with open("i2c_settings.json", "w", encoding='utf8') as json_file:
        json.dump(i2c_settings, json_file, indent=4)

    del rp_cla

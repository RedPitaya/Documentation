.. _LA_can_file:

Decoding CAN protocol (from file)
######################################

.. note::

    An FPGA loopback example for the CAN protocol is not possible as the Logic Analyzer and the CAN protocol share the same digital pins.

Description
============

This example demonstrates how to decode the CAN protocol using logic analyser commands. Red Pitaya loads the CAN data from the "can_data.bin" file and decodes it.
When configuring the example, make sure that the CAN decoder settings match the capture settings.

.. include:: la_can_settings.inc


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



Modifying decoder settings
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


Save decoder settings to a json file
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

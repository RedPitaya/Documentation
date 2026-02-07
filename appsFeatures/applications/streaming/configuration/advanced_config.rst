.. _stream_advanced_config:

#########################
Advanced configuration
#########################

This section covers advanced configuration options for the Streaming application, including port numbers and configuration file management.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

.. _stream_port_numbers:

Port configuration
*******************

The settings for streaming have fixed values that are set in the application:

.. tabs::

    .. group-tab:: OS version 2.07-43 or newer

        * 18900 - ADC streaming server
        * 18901 - Configuration Server
        * 18902 - Broadcast server
        * 18903 - DAC streaming server

    .. group-tab:: OS version 1.04-28 to 2.05-37

        * 8900 - ADC streaming server
        * 8901 - Configuration Server
        * 8902 - Broadcast server
        * 8903 - DAC streaming server

.. note::

    Older OS versions included a **Port** setting in the web interface where users could specify the network port number for data 
    streaming. The port numbers are now fixed to the values above.

|

Configuration file
*******************

Configuration can be set over the WEB interface UI, which is afterwards stored in one of the following locations on the Red Pitaya:

* **/root/.streaming_config** (older OS versions)
* **/root/.config/redpitaya/apps/streaming/streaming_config.json** (OS version 2.00 and newer)

|

Configuration file format
==========================

.. tabs::

    .. group-tab:: OS version 2.07-43 or newer

        The configuration file has been updated to make all settings more user-friendly, but it is now incompatible with older versions.

        .. code-block:: json

            {
                "adc_streaming" : 
                {
                    "adc_decimation" : 2,
                    "adc_pass_mode" : "FILE",
                    "channel_ac_dc_1" : "DC",
                    "channel_ac_dc_2" : "DC",
                    "channel_ac_dc_3" : "DC",
                    "channel_ac_dc_4" : "DC",
                    "channel_attenuator_1" : "A_1_1",
                    "channel_attenuator_2" : "A_1_1",
                    "channel_attenuator_3" : "A_1_1",
                    "channel_attenuator_4" : "A_1_1",
                    "channel_state_1" : "ON",
                    "channel_state_2" : "OFF",
                    "channel_state_3" : "OFF",
                    "channel_state_4" : "OFF",
                    "data_type_sd" : "RAW",
                    "format_sd" : "WAV",
                    "resolution" : "BIT_8",
                    "samples_limit_sd" : 1000000,
                    "use_calib" : "ON"
                },
                "dac_streaming" : 
                {
                    "channel_gain_1" : "X1",
                    "channel_gain_2" : "X1",
                    "dac_pass_mode" : "DAC_FILE",
                    "dac_rate" : 125000000,
                    "file_sd" : "sine.wav",
                    "file_type_sd" : "WAV",
                    "repeat" : "DAC_REP_OFF",
                    "repeatCount" : 1
                },
                "memory_manager" : 
                {
                    "adc_size" : 134217728,
                    "block_size" : 8388608,
                    "dac_size" : 134217728,
                    "gpio_size" : 134217728
                }
            }

.. note::

    The "Memory Manager" file sizes are in Bytes.
    1 MiB = 1024*1024 Bytes = 2^20 Bytes = 1048576 Bytes. We are using Mebibytes (MiB) instead of Megabytes (MB) to avoid confusion with 
    the decimal system.

|

Configuration parameters
=========================

ADC streaming parameters
-------------------------

* **adc_decimation:** Decimation factor (1, 2, 4, 8, 16, 17, 18, ..., 65536)
* **adc_pass_mode:** Streaming mode ("NET" for network, "FILE" for local SD card)
* **channel_ac_dc_X:** AC/DC coupling for channel X ("AC" or "DC") - *only for SIGNALlab 250-12*
* **channel_attenuator_X:** Input attenuation for channel X ("A_1_1" for 1:1, "A_1_20" for 1:20)
* **channel_state_X:** Enable/disable channel X ("ON" or "OFF")
* **data_type_sd:** Data format for SD card storage ("RAW" or "VOLTS")
* **format_sd:** File format for SD card storage ("WAV", "TDMS", or "BIN")
* **resolution:** ADC resolution ("BIT_8" or "BIT_16")
* **samples_limit_sd:** Number of samples to acquire (0 for unlimited)
* **use_calib:** Use calibration ("ON" or "OFF")

|

DAC streaming parameters
-------------------------

* **channel_gain_X:** Output gain for channel X ("X1" or "X5")
* **dac_pass_mode:** Streaming mode ("DAC_NET" for network, "DAC_FILE" for local SD card)
* **dac_rate:** DAC output rate in Hz (e.g., 125000000 for 125 MS/s)
* **file_sd:** Filename for DAC streaming source
* **file_type_sd:** File format ("WAV" or "TDMS")
* **repeat:** Repeat mode ("DAC_REP_OFF", "DAC_REP_ON", or "DAC_REP_INF")
* **repeatCount:** Number of repetitions (when repeat is "DAC_REP_ON")

|

Memory manager parameters
--------------------------

* **adc_size:** Reserved memory for ADC streaming in Bytes
* **block_size:** Network packet size in Bytes
* **dac_size:** Reserved memory for DAC streaming in Bytes
* **gpio_size:** Reserved memory for GPIO streaming in Bytes (not yet implemented)

|

Managing configuration files
******************************

Using the Command Line Client
===============================

The configuration file can be managed using the :ref:`Command Line Client <stream_command_client>`:

**Download configuration file from Red Pitaya:**

.. code-block:: console

    .\rpsa_client.exe -c -g F

The downloaded configuration file is located in the *configs* folder of the command line client.

**Upload configuration file to Red Pitaya:**

.. code-block:: console

    .\rpsa_client.exe -c -s F -f .\configs\config_dac.json

|

Manual editing
===============

You can also manually edit the configuration file directly on the Red Pitaya via :ref:`SSH <ssh>`:

.. code-block:: bash

    ssh root@<IP_ADDRESS or .LOCAL_ADDRESS>
    nano /root/.config/redpitaya/apps/streaming/streaming_config.json

After editing, restart the streaming application for changes to take effect.

|

Configuration validation
=========================

When editing configuration files manually, ensure:

1. **Valid JSON syntax:** Use a JSON validator to check your file
2. **Correct parameter values:** Refer to the parameter descriptions above
3. **Memory constraints:** Total memory allocation (adc_size + dac_size + gpio_size) should not exceed the reserved DMM region
4. **Compatible settings:** Ensure decimation, rate, and resolution settings are compatible with :ref:`streaming limitations <streaming_limits>`

|

Next steps
***********

* Try the :ref:`DAC Streaming Example <stream_dac_cli_example>` which includes configuration file editing
* Learn about :ref:`Command Line Client usage <stream_command_client>`
* Review :ref:`Data Streaming Limitations <streaming_limits>` to validate your configuration

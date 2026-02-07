.. _stream_adc_config:

#############################
ADC streaming configuration
#############################

.. figure:: ../img/streaming_adc.png
    :width: 800

The ADC configuration section allows the user to set the parameters for the data acquisition process. The settings depend on the 
selected **Mode** (*Network* or *Local*).

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Configuration modes
********************

.. tabs::

    .. group-tab:: Network

        The user can set:

        * **IP address:** The IP address of the Red Pitaya board.  
        * **Rate:** The sampling frequency (rate). Should be calculated from the selected settings and the :ref:`data streaming limitation <streaming_limits>`.
        * **Resolution:** Input channel resolution (8 or 16 bits). Determines the number of Bytes per sample (1 or 2).
        * **Use calibration:** Select whether the input calibration should be used or not.
        * **Type of file saved:** Select the file format for the saved data. The following formats are supported:
            
            * WAV (standard audio file format) (maximum WAV file size is 4 GB),
            * TDMS (Technical Data Management Streaming file format),
            * BIN (Fast and compact binary format). It can be converted to CSV format using the :ref:`convert_tool <streaming_convert_tool>` application.
        
        * **Input channels:** Select the input channels to be used for data acquisition by turning on the corresponding switches. The following options are available:
            
            * Channel 1 (CH1),
            * Channel 2 (CH2),
            * Channel 3 (CH3) - *STEMlab 125-14 4-Input only*,
            * Channel 4 (CH4) - *STEMlab 125-14 4-Input only*.

        * **Input attenuation:** For each channel select the input attenuation mode. The following options are available:
            
            * 1:20 - HV (high voltage mode),
            * 1:1 - LV (low voltage mode).

        The *Save mode* setting is specified on the remote client side.

        .. note::

            Older OS versions also include the **Port** setting, where the user can specify the network port number for the data 
            streaming. The port numbers are now fixed. See the :ref:`Configuration information <stream_port_numbers>` section 
            for more details.

    .. group-tab:: Local

        The user can set:

        * **Samples:** Number of samples to be acquired (*ALL* for unlimited sampling)
        * **Rate:** The sampling frequency (rate). Should be calculated from the selected settings and the :ref:`data streaming limitation <streaming_limits>`.
        * **Resolution:** Input channel resolution (8 or 16 bits). Determines the number of Bytes per sample (1 or 2).
        * **Use calibration:** Select whether the input calibration should be used or not.
        * **Type of file saved:** Select the file format for the saved data. The following formats are supported:
            
            * WAV (standard audio file format) (maximum WAV file size is 4 GB),
            * TDMS (Technical Data Management Streaming file format),
            * BIN (Fast and compact binary format). It can be converted to CSV format using the :ref:`convert_tool <streaming_convert_tool>` application.

        * **Save mode:** Select the save mode for the data. The following modes are supported:
            
            * RAW (raw data in ADC counts),
            * VOLTS (data converted to Volts).
        
        * **Input channels:** Select the input channels to be used for data acquisition by turning on the corresponding switches. The following options are available:
            
            * Channel 1 (CH1),
            * Channel 2 (CH2),
            * Channel 3 (CH3) - *STEMlab 125-14 4-Input only*,
            * Channel 4 (CH4) - *STEMlab 125-14 4-Input only*.

        * **Input attenuation:** For each channel select the input attenuation mode. The following options are available:
            
            * 1:20 - HV (high voltage mode),
            * 1:1 - LV (low voltage mode).

|

File formats
*************

The following file formats are supported for ADC streaming:

* **WAV (Wave Audio File Format):** Standard audio file format with a maximum file size of 4 GB. Compatible with most audio processing software.
* **TDMS (Technical Data Management Streaming):** National Instruments file format designed for high-speed data acquisition and logging.
* **BIN (Binary):** Fast and compact binary format. Can be converted to CSV format using the :ref:`convert_tool <streaming_convert_tool>` application.

|

Save modes
***********

When streaming data locally, you can select the save mode:

* **RAW:** Saves raw data in ADC counts (native format from the ADC).
* **VOLTS:** Converts and saves data in Volts based on the attenuation settings.

.. note::

    RAW mode is more compact and faster to save, while VOLTS mode is more user-friendly for analysis. The choice depends on your specific use case and post-processing requirements.
    Both mode automatically include the calibration if the "Use calibration" option is selected.

|

Channel configuration
**********************

Input channels
===============

Select which input channels to use for data acquisition:

* **CH1** - Always available
* **CH2** - Always available
* **CH3** - STEMlab 125-14 4-Input only
* **CH4** - STEMlab 125-14 4-Input only

.. note::

    More active channels will reduce the maximum sampling rate due to increased data throughput. See 
    :ref:`Data Streaming Limitations <streaming_limits>` for details.

|

Input attenuation
==================

For each active channel, select the input attenuation mode:

* **1:1 - LV (Low Voltage mode):** ±1V input range
* **1:20 - HV (High Voltage mode):** ±20V input range

The attenuation setting affects the input range and sensitivity of each channel.

|

Next steps
***********

* Configure :ref:`DAC streaming <stream_dac_config>` if you need signal generation
* Set up :ref:`Memory configuration <stream_memory_config>` to optimize performance
* Learn about :ref:`Data Streaming Limitations <streaming_limits>` to calculate maximum sampling rates

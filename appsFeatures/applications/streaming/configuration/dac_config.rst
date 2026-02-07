.. _stream_dac_config:

#############################
DAC streaming configuration
#############################

.. figure:: ../img/streaming_dac.png
    :width: 800

The DAC configuration section allows the user to set the parameters for the data generation process. The settings depend on 
the selected **Mode** (*Network* or *Local*).

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Configuration modes
********************

.. tabs::

    .. group-tab:: Network

        The user can set:

        * **Rate:** The DAC sample output frequency (rate). Should be selected according to the :ref:`data streaming limitations <streaming_limits>`.

        The other settings are specified in the configuration file located in */root/.config/redpitaya/apps/streaming/streaming_config.json*. 
        The file can be updated manually or through the :ref:`Command Line Client <stream_command_client>`.

    .. group-tab:: Local

        The user can set:

        *   **Rate:** The DAC sample output frequency (rate). Should be selected according to the :ref:`data streaming limitations <streaming_limits>`.
        *   **File name:** Select the file to be used for data generation from the dropdown menu. The file must be in WAV or TDMS format. 
            The two buttons are used for file upload and deleting the selected file.
        *   **File format:** Select the file format of the file used for the data generation. The following formats are supported:
            
            * WAV (standard audio file format),
            * TDMS (Technical Data Management Streaming file format).

        *   **Repeat mode:** Select the repeat mode for the data generation. The following modes are supported:
            
            * **Off:** The file is generated once then the streaming stops. 
            * **On:** The file is generated *Repeat count* times then the streaming stops.
            * **Infinity:** The file is continuously generated until the streaming is stopped.

        *   **Repeat count:** How many times the should the file be repeated.

WAV and TDMS file formats can have up to two channel signals at the same time. While **Channel select** is not available, 
the first channel will be generated on OUT1 and the second channel on OUT2.

.. note::

    Currently, the only supported format is 16-bit RAW. In the future we will also support other formats and 8-bit mode.

|

DAC streaming modes
********************

To prevent data loss when generating small data files at a high DAC frequency, only one memory block will be sent and generated 
if the data file size is smaller than the memory block size. Otherwise, the data will be sent and generated *repetition* number 
of times.

This means that the DAC streaming has two modes of operation:

One-pack mode
==============

If the data file size is smaller than the reserved memory block size, there is only a single data transfer between the board 
and computer and the data can be generated at the full 125 MS/s. The generation data is stored in the :ref:`DMM memory <deepMemoryMode>` 
together with the specified number of repetitions.

* **Maximum dac_rate:** 125 MHz (125 MS/s)
* **Use case:** Short waveforms, arbitrary waveform generation

|

True streaming mode
====================

If the data file size is larger than the reserved memory block size, then the data is streamed from the computer to the board. 
To achieve the best performance, we recommend setting the block size to 8 MB and have the signal fit into the 
:ref:`DMM region <deepMemoryMode>` completely.

* **Maximum stable dac_rate:** ~5 MHz (5 MS/s) for 16-bit resolution
* **Use case:** Long waveforms, continuous signal generation

.. warning::

    Setting the DAC rate higher than 5 MHz in true streaming mode may result in data loss and unstable signal generation.

.. note::

    Remote data generation is currently possible only through the :ref:`Command Line Client <stream_command_client>`. The 
    desktop application currently does not support this feature.

|

File formats
*************

The following file formats are supported for DAC streaming:

* **WAV (Wave Audio File Format):** Standard audio file format. Maximum file size is 4 GB.
* **TDMS (Technical Data Management Streaming):** National Instruments file format.

Both formats can contain up to two channels (OUT1 and OUT2).

.. note::

    The DAC streaming is currently limited to 16-bit resolution and the WAV or TDMS file format.
    The WAV file format has a maximum size of 4 GB, which limits the maximum number of samples that can be generated to 
    approximately 268 million samples (for 16-bit resolution).

|

Best practices
***************

For optimal DAC streaming performance:

1. **Use one-pack mode when possible:** Keep your waveform small enough to fit in the reserved :ref:`DMM memory <stream_memory_config>`.
2. **Set block size to 8 MB:** When using true streaming mode, use the maximum block size for best performance.
3. **Minimum 1024 samples per channel:** To avoid inconsistencies in the generated signal due to C++ program overhead.
4. **Consider the signal length:** Ideally, the signal should fit completely into the specified block size.

|

Simultaneous ADC and DAC streaming
************************************

ADC and DAC streaming can work simultaneously, allowing the user to acquire data from the fast analog inputs and generate 
signals on the fast analog outputs at the same time.

.. note::
    
    Please note that the load on the processor will increase and the maximum performance of each mode will decrease when 
    running both modes simultaneously.

|

Next steps
***********

* Try the :ref:`DAC Streaming Example <stream_dac_cli_example>` to learn how to generate custom waveforms
* Review :ref:`Data Generation Limitations <stream_dac_limitations>` for performance constraints
* Configure :ref:`Memory settings <stream_memory_config>` to optimize DAC streaming performance

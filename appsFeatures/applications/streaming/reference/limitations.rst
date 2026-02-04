.. _streaming_limits:

############################
Data streaming limitations
############################

The streaming application has some limitations that should be considered when configuring the data acquisition and generation process. 
These limitations are related to the maximum data rates and the minimum streamed data size.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Data rate limitations
**********************

The maximum data rates (per board) are determined by the hardware capabilities of the Red Pitaya board and the network transfer rates. 
The following limitations apply:

Maximum data rates
===================

.. tabs::

    .. group-tab:: OS 2.07-43 or newer

        * **SD card streaming:** 10 MB/s (SD card class 10 is recommended for optimal streaming performance)
        * **Network streaming:** 62.5 MB/s for streaming over 1 Gbit network (:ref:`connecting the board to a router <LAN>` is recommended to achieve the best streaming performance)

    .. group-tab:: OS 1.04-28 to 2.05-37

        * **SD card streaming:** 10 MB/s (SD card class 10 is recommended for optimal streaming performance)
        * **Network streaming:** 20 MB/s for streaming over 1 Gbit network (:ref:`connecting the board to a router <LAN>` is recommended to achieve the best streaming performance)

The main limiting factor for the maximum data rate is the processor which reads the data from the DDR memory buffer and converts it 
into Ethernet packets for network transmission. The data path is: **Inputs → FPGA → DDR → Processor → Ethernet → Network → PC**.

If the data rate exceeds the maximum sustainable rate, the processor will not be able to keep up with the incoming data stream 
(reading the buffer before the FPGA overwrites it), leading to packet loss and consequently missing data. The :ref:`block size <stream_memory_config>` 
setting determines how much data is transferred in each packet, but the overall limitation is the processor's ability to handle the 
continuous data flow.

.. note::

    Using multiple streaming modes simultaneously (e.g. ADC and DAC streaming) will affect the maximum data rate as the processor load 
    increases.

|

Factors affecting data rate
=============================

The maximum achievable data rate depends on several factors:

1.  **Processor overhead:** Any extra processing done by the processor (e.g. data conversion, web interface updates, etc.) will reduce 
    the maximum data rate
2.  **Network configuration:** Direct connection vs router, network congestion, cable quality
3.  **SD card speed:** Class 10 or higher recommended for local streaming
4.  **Data format:** RAW format is faster than VOLTS conversion
5.  **File format:** BIN format has less overhead than WAV or TDMS
6.  **Client capabilities:** The streaming client application performance

|

Highest possible data rate
============================

The highest possible data rate is achieved using:

1. :ref:`Command line client <stream_command_client>`
2. **RAW** data format (no conversion)
3. **Binary (BIN)** file type (minimal overhead)
4. **Web interface closed** (no UI updates)
5. **Single streaming mode** (ADC or DAC, not both)

This is the most efficient way to transfer data as no data conversion is performed before it is sent over the network.

|

Calculating maximum sampling frequency
****************************************

The following calculation can be used to determine the maximum **continuous** sampling frequency for streaming:

.. math::

    f_{S, max} = \frac{v_{max}}{N \times Bps}

Where:

* :math:`f_{S, max}` - is the maximum continuous sampling frequency
* :math:`v_{max}` - is the maximum data rate for the selected streaming mode (10 MB/s for local streaming, 62.5 MB/s for network streaming on OS 2.07-43+)
* :math:`N` - is the number of input channels selected for data acquisition (1, 2, 3 or 4)
* :math:`Bps` - (Bytes per sample) is the number of bytes used to represent each sample (1 for 8-bit resolution, 2 for 16-bit resolution)

.. note::

    These calculations apply to **continuous streaming**. For short bursts, higher sampling rates up to 125 MS/s are possible 
    by utilizing the DDR memory buffer (see "Short duration high-speed acquisition" below).

|

Example calculations
=====================

.. note::

    The following examples use the network streaming limit of **62.5 MB/s** (OS 2.07-43 or newer). For OS 1.04-28 to 2.05-37, 
    use **20 MB/s** instead.

Example 1: Network streaming, single channel, 16-bit
------------------------------------------------------

* :math:`v_{max}` = 62.5 MB/s = 62,500,000 Bytes/s
* :math:`N` = 1 channel
* :math:`Bps` = 2 Bytes (16-bit)

.. math::

    f_{S, max} = \frac{62,500,000}{1 \times 2} = 31,250,000 \text{ samples/s} = 31.25 \text{ MS/s}

|

Example 2: Network streaming, two channels, 8-bit
---------------------------------------------------

* :math:`v_{max}` = 62.5 MB/s = 62,500,000 Bytes/s
* :math:`N` = 2 channels
* :math:`Bps` = 1 Byte (8-bit)

.. math::

    f_{S, max} = \frac{62,500,000}{2 \times 1} = 31,250,000 \text{ samples/s} = 31.25 \text{ MS/s}

|

Example 3: Local (SD card) streaming, single channel, 16-bit
--------------------------------------------------------------

* :math:`v_{max}` = 10 MB/s = 10,000,000 Bytes/s
* :math:`N` = 1 channel
* :math:`Bps` = 2 Bytes (16-bit)

.. math::

    f_{S, max} = \frac{10,000,000}{1 \times 2} = 5,000,000 \text{ samples/s} = 5 \text{ MS/s}

|

Example 4: Network streaming (older OS), single channel, 16-bit
-----------------------------------------------------------------

For OS versions 1.04-28 to 2.05-37 with 20 MB/s network limit:

* :math:`v_{max}` = 20 MB/s = 20,000,000 Bytes/s
* :math:`N` = 1 channel
* :math:`Bps` = 2 Bytes (16-bit)

.. math::

    f_{S, max} = \frac{20,000,000}{1 \times 2} = 10,000,000 \text{ samples/s} = 10 \text{ MS/s}

|

Short duration high-speed acquisition
=======================================

.. note::

    **Burst mode capability:** If acquiring a limited amount of samples in a short duration, it is possible to reach higher sampling 
    frequencies (up to the full sampling speed of fast analog inputs - 125 MS/s). This works because the :ref:`Deep Memory Mode <deepMemoryMode>` 
    buffer in DDR memory can temporarily store data much faster than it can be continuously streamed out to the network or SD card.
    
    The amount of data that can be acquired at full speed depends on the available DDR buffer size. Once the buffer fills, the 
    acquisition rate is limited by the maximum continuous streaming rate listed above.

|

Packet size limitations
************************

To increase the efficiency of the application, there is a minimum data packet (chunk) size that can be sent through the network. 
This can have a big impact at high decimation values, as it may take a long time to fill a chunk before sending it over the network.

.. warning::

    If the stream is stopped before a chunk is full, the acquired data is discarded. Consequently, the save file can have a size of 
    **0 bits**.

|

Minimum chunk sizes
====================

Here are the minimum chunk limitations sorted by file type and units:

+--------------------+-----------------+----------------+----------------+
| File type \\ Units | WAV             | TDMS           | BIN            |
+====================+=================+================+================+
| VOLTS              | 128.043 kb      | 128.133 kb     | 64.090 kb      |
+--------------------+-----------------+----------------+----------------+
| RAW                | 64.043 kb       | 64.133 kb      | 64.090 kb      |
+--------------------+-----------------+----------------+----------------+

|

.. _stream_dac_limitations:

Data generation limitations
****************************

The data generation process has different limitations than ADC streaming because the data path is reversed. Since data must be 
received over the network and processed before being sent to the FPGA, the expected performance is lower than for ADC streaming.

For details about the DAC streaming architecture and why these limitations exist, see :ref:`Technical Details <streaming_technical_details>`.

DAC rate limitations
=====================

Here are limitations for the **dac_rate** variable for each of the two modes:

.. tabs::

    .. group-tab:: OS 2.07-43 or newer

        * **One-pack mode:** Maximum **dac_rate** is 125 MHz (125 MS/s)
        * **True streaming mode:** Maximum stable **dac_rate** is about 5 MHz (5 MS/s) for 16-bit resolution

        .. warning::

            Setting the DAC rate higher than 5 MHz in true streaming mode may result in data loss and unstable signal generation.

|

DAC performance recommendations
=================================

When generating data from a file, we recommend:

1. **Set block size to 2 MB** for high-quality signal generation
2. **Fit the signal into DMM memory** - The entire file should fit into the :ref:`DMM region <stream_memory_config>` for best performance
3. **Minimum 1024 samples per channel** - To avoid inconsistencies in the generated signal due to C++ program overhead
4. **Ideal signal length** - The signal should fit completely into the specified block size

|

Additional factors
===================

* **Network USB card:** If used, can limit the maximum data rate
* **File size constraints:** WAV file format has a maximum size of 4 GB, limiting the maximum number of samples to approximately 268 million (for 16-bit resolution)
* **Resolution:** Currently limited to 16-bit resolution for DAC streaming (board output resolution will override this setting if lower)

.. note::

    The DAC streaming is currently limited to 16-bit resolution and the WAV or TDMS file format.

|

Performance optimization tips
*******************************

To maximize streaming performance:

ADC streaming optimization
===========================

1. Use **RAW** data format instead of VOLTS
2. Use **BIN** file format for minimal overhead
3. Close the web interface during streaming
4. Use appropriate :ref:`block size <stream_memory_config>` for your sampling rate
5. Connect board to a router for stable network streaming
6. Use a high-quality Class 10 SD card for local streaming
7. Disable unused channels
8. Use 8-bit resolution when 16-bit precision is not required

|

DAC streaming optimization
===========================

1. Keep waveforms small enough for :ref:`one-pack mode <stream_dac_config>`
2. Use 2 MB block size for true streaming mode
3. Pre-load data into :ref:`DMM memory <stream_memory_config>`
4. Ensure waveform has at least 1024 samples per channel
5. Avoid streaming DAC and ADC simultaneously at maximum rates

|

Next steps
***********

* Review :ref:`ADC Configuration <stream_adc_config>` to set appropriate sampling rates
* Check :ref:`DAC Configuration <stream_dac_config>` for generation rate settings
* Configure :ref:`Memory settings <stream_memory_config>` to optimize for your use case
* See :ref:`Examples <streaming_examples_top>` for practical implementations

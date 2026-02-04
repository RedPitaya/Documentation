.. _examples_streaming:

#########################
Streaming Examples
#########################

Complete, ready-to-run examples demonstrating ADC and DAC streaming capabilities using the Red Pitaya streaming client library.

All example source code is maintained on :rp-github:`GitHub <RedPitaya-Examples/tree/main/python-api/Streaming>` for easy access and continuous updates.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Prerequisites
**************

Before running these examples:

* Red Pitaya board with OS version 2.00 or newer
* Streaming application running on Red Pitaya (see :ref:`Streaming Quick Start <streaming_quickstart>`). Either in the web interface or as :ref:`command-line server <stream_command_client>`.
* :ref:`Streaming command line client <streaming_pc_clients>` downloaded to your computer
* Computer and Red Pitaya connected to the same network (LAN recommended)
* Python 3.12 (or higher) or C++20 compiler installed on your computer
* Unblocked network access for the streaming client application in your computer's firewall/antivirus software.

.. note::

    **Firewall/Antivirus Configuration:** If you experience issues with board detection or connection, ensure that Python/C++ is allowed network access in your firewall and antivirus software. 
    Some security programs may block Python's network communication, preventing the client from discovering Red Pitaya boards on the network.

For installation instructions, see :ref:`Streaming Client Setup <stream_command_client>`.

|

Quick Start
************

New to streaming? Start here:

.. toctree::
    :maxdepth: 1

    streaming_quickstart

The quick start guide shows a minimal working example to get you streaming data in under 5 minutes.

|

ADC Streaming Examples
***********************

Continuous data acquisition from Red Pitaya fast analog inputs to your computer.

Basic ADC Data Acquisition
============================

Stream data from ADC channels to numpy arrays with automatic memory management.

.. grid:: 1
   :gutter: 2

    .. grid-item-card:: 📥 ADC Dual Channel Streaming
        :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/python-api/Streaming/adc_1_stream.py
        :link-type: url

        Continuously stream data from two ADC channels simultaneously.
        
        * Configurable sample rate (via decimation)
        * Automatic buffer management
        * Real-time data loss monitoring
        * Memory-efficient numpy array storage
        
        **Language:** Python | **Complexity:** ⭐⭐ | :ref:`Tutorial <streaming_adc_example>`

|

**Key Features Demonstrated:**

.. code-block:: python

    import streaming

    # Configure streaming parameters
    decimation = 256                    # Sample rate = 125 MS/s / decimation
    capture_duration = 1                # seconds
    ch1_state = 'ON'                    # Enable channel 1
    ch2_state = 'ON'                    # Enable channel 2

    # Create client and callback
    client = streaming.ADCStreamClient()
    callback = streaming.ADCCallback()            # Handles incoming data
    
    # Start streaming
    client.startStreaming()
    client.wait()

**View the complete implementation:** :rp-github:`adc_1_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/adc_1_stream.py>`

|

Coming Soon
===========

* **C++ ADC Streaming** - High-performance ADC acquisition in C++
.. * **Multi-channel ADC** - Stream from 4+ channels using synchronized boards
.. * **Triggered Acquisition** - Combine with external triggering for event capture

|

DAC Streaming Examples
***********************

Continuous waveform generation on Red Pitaya fast analog outputs from your computer.

Single Channel WAV Output
==========================

Generate signals on DAC output from WAV audio files.

.. grid:: 1
    :gutter: 2

    .. grid-item-card:: 📤 DAC Mono Streaming
        :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/python-api/Streaming/dac_1_stream.py
        :link-type: url

        Stream a single-channel waveform from a WAV file to DAC output.
        
        * Load waveform from WAV file
        * Configurable DAC rate (up to 125 MS/s)
        * Repeat mode (finite or infinite)
        * Network packet size optimization
        
        **Language:** Python | **Complexity:** ⭐⭐

|

**Key Features Demonstrated:**

.. code-block:: python

    # Generate waveform and save as WAV
    t = np.linspace(0., 1., 1024)
    data = 32767 * np.sin(2. * np.pi * frequency * t)
    write('waveform.wav', sample_rate, data.astype(np.int16))

    # Configure and stream
    client = streaming.DACStreamClient()
    client.sendConfig('dac_rate', '125000000')      # 125 MS/s
    client.startStreamingWAV('./waveform.wav')
    client.wait()

**View the complete implementation:** :rp-github:`dac_1_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_1_stream.py>`

|

Stereo DAC Output
==================

Stream stereo signals to both DAC channels simultaneously.

.. grid:: 1
    :gutter: 2

    .. grid-item-card:: 📤📤 DAC Stereo Streaming
        :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/python-api/Streaming/dac_2_stream.py
        :link-type: url

        Stream a dual-channel waveform to both DAC outputs in continuous loop mode.
        
        * Stereo WAV file support
        * Independent waveforms per channel
        * Infinite loop playback
        * Synchronized output timing
        
        **Language:** Python | **Complexity:** ⭐⭐

|

**Key Features Demonstrated:**

.. code-block:: python

    # Create stereo waveform (2 channels)
    stereo = np.vstack((channel1_data, channel2_data)).transpose()
    write('stereo.wav', sample_rate, stereo)

    # Stream with infinite repeat
    client.setRepeatInf(True)
    client.startStreamingWAV('./stereo.wav')

**View the complete implementation:** :rp-github:`dac_2_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_2_stream.py>`

|

Direct Memory Mode
===================

Stream waveforms directly from memory without intermediate files for maximum performance.

.. grid:: 1
    :gutter: 2

    .. grid-item-card:: ⚡ DAC Memory Streaming
        :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/python-api/Streaming/dac_3_stream.py
        :link-type: url

        High-performance streaming by loading waveforms directly into FPGA memory.
        
        * No file I/O overhead
        * Faster data transfer
        * Real-time waveform generation
        * Independent channel control
        
        **Language:** Python | **Complexity:** ⭐⭐⭐

|

**Key Features Demonstrated:**

.. code-block:: python

    # Generate waveform in memory
    waveform_data = (32767 * np.sin(2. * np.pi * t)).astype(np.int16).tolist()

    # Load directly to FPGA memory
    client.setMemory16Bit(1, waveform_data)  # Channel 1
    client.setMemory16Bit(2, waveform_data)  # Channel 2
    
    # Start streaming from memory (no file needed)
    client.startStreamingFromMemory()

**View the complete implementation:** :rp-github:`dac_3_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_3_stream.py>`

|

.. Coming Soon
.. ===========

* **C++ DAC Streaming** - High-performance DAC generation in C++
.. * **Multi-board DAC** - Synchronized waveform generation across multiple boards
.. * **Custom Waveforms** - Advanced signal processing and modulation examples

.. |

API Reference
**************

For detailed information about the streaming client classes, methods, and callback system:

.. toctree::
    :maxdepth: 1

    streaming_api_reference

|

Additional Resources
*********************

* :ref:`Streaming Application Documentation <streaming_top>`
* :ref:`Configuration Guide <stream_configuration>`
* :ref:`Performance Limits <streaming_limits>`
* :ref:`Multi-board Synchronization <x-ch_streaming>`
* :rp-github:`Report Issues or Request Examples <RedPitaya-Examples/issues>`

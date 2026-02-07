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

* Red Pitaya board with OS version 2.07 or newer
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
    streaming_adc_api_example
    streaming_dac_api_example
    adc_streaming_cli_example
    dac_streaming_cli_example
    streaming_api_reference

The quick start guide shows a minimal working example to get you streaming data in under 5 minutes.

|

ADC Streaming Examples
***********************

Continuous data acquisition from Red Pitaya fast analog inputs to your computer.

.. note::

    The code snippets below highlight key features. For complete, runnable examples with full error handling and documentation, follow the implementation 
    links in each section.

Basic ADC Data Acquisition
============================

Stream data from ADC channels with automatic memory management and real-time processing.

.. tabs::

    .. tab:: Python

        .. grid:: 1
            :gutter: 2

            .. grid-item-card:: **ADC Dual Channel Streaming**
                :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/python-api/Streaming/adc_1_stream.py
                :link-type: url

                Stream to numpy arrays with automatic buffer management.
                
                * Configurable sample rate (via decimation)
                * Memory-efficient numpy array storage
                * Real-time data loss monitoring
                
                **Complexity:** ⭐⭐

        |

        **Key Features:**

        .. code-block:: python

            import streaming

            # Configure streaming parameters
            decimation = 256                    # Sample rate = 125 MS/s / decimation
            capture_duration = 1                # seconds
            ch1_state = 'ON'                    # Enable channel 1
            ch2_state = 'ON'                    # Enable channel 2

            # Create client and callback
            client = streaming.ADCStreamClient()
            callback = streaming.ADCCallback()  # Handles incoming data
            
            # Start streaming
            client.startStreaming()
            client.wait()

        **Complete implementation:** :rp-github:`adc_1_stream.py <RedPitaya-Examples/blob/main/python-api/Streaming/adc_1_stream.py>`

    .. tab:: C++

        .. grid:: 1
            :gutter: 2

            .. grid-item-card:: **C++ Dual Channel ADC Streaming**
                :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_adc_1.cpp
                :link-type: url

                High-performance acquisition with ``std::vector buffers``.
                
                * Pre-allocated std::vector buffers
                * Real-time min/max/mean calculations
                * Efficient memory management
                * Frame loss detection
                
                **Complexity:** ⭐⭐⭐

        |  

        **Key Features:**

        .. code-block:: cpp

            #include "adc_streaming.h"
            #include "callbacks.h"
            
            class Callback : public ADCCallback {
                std::vector<int16_t> ch1_data;  // Pre-allocated buffer
                std::vector<int16_t> ch2_data;
                
                void receivePack(ADCStreamClient* client, ADCPack& pack) override {
                    // Process incoming ADC data packets
                }
            };
            
            // Create client and start streaming
            ADCStreamClient client;
            Callback callback;
            client.setReceiveDataCallback(&callback);
            client.startStreaming();

        **Complete implementation:** :rp-github:`stream_adc_1.cpp <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_adc_1.cpp>`

|

Multi-Board Synchronized ADC
==============================

Stream data from multiple Red Pitaya boards (4+ channels) with hardware-synchronized acquisition.

**Features:**

* Master/slave synchronization for phase-coherent capture
* Per-board data tracking and statistics
* Configurable board IPs
* Independent channel control per board

**Complexity:** Python ⭐⭐⭐ | C++ ⭐⭐⭐⭐

|

.. tabs::

    .. tab:: Python

        **Implementation:** :rp-github:`adc_2_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/adc_2_stream.py>`

        .. code-block:: python

            import streaming
            
            # Define board IPs (master + slaves)
            hosts = ['192.168.0.114', '192.168.0.108']
            
            # Connect to all boards
            client = streaming.ADCStreamClient()
            client.connect(hosts)
            
            # Configure master board
            master = hosts[0]
            client.sendConfig(master, 'adc_decimation', '64')
            client.sendConfig(master, 'channel_state_1', 'ON')
            client.sendConfig(master, 'channel_state_2', 'ON')
            
            # Clone configuration to slaves
            for slave in hosts[1:]:
                client.cloneConfig(master, slave)
            
            # Start synchronized streaming
            client.startStreaming()

    .. tab:: C++

        **Implementation:** :rp-github:`stream_adc_2.cpp → <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_adc_2.cpp>`

        .. code-block:: cpp

            #include "adc_streaming.h"
            
            // Define board IPs (master + slaves)
            std::vector<std::string> hosts = {"192.168.0.114", "192.168.0.108"};
            
            // Connect to all boards
            ADCStreamClient client;
            client.connect(hosts);
            
            // Configure master board
            std::string master = hosts[0];
            client.sendConfig(master, "adc_decimation", "64");
            client.sendConfig(master, "channel_state_1", "ON");
            client.sendConfig(master, "channel_state_2", "ON");
            
            // Clone configuration to slaves
            for (size_t i = 1; i < hosts.size(); i++) {
                client.cloneConfig(master, hosts[i]);
            }
            
            // Start synchronized streaming
            client.startStreaming();

|

DAC Streaming Examples
***********************

Continuous waveform generation on Red Pitaya fast analog outputs from your computer.

.. note::

    The code snippets below highlight key features. For complete, runnable examples with full error handling and documentation, follow the implementation 
    links in each section.

Single Channel WAV Output
==========================

Generate and stream signals from WAV audio files to DAC output.

.. tabs::

    .. tab:: Python

        .. grid:: 1
            :gutter: 2

            .. grid-item-card:: **DAC Waveform Streaming**
                :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/python-api/Streaming/dac_1_stream.py
                :link-type: url

                Stream custom waveforms from WAV files to DAC outputs.
                
                * Configurable DAC rate (up to 125 MS/s)
                * Repeat mode (finite or infinite)
                * 16-bit sample format support
                
                **Complexity:** ⭐⭐

        |

        **Key Features:**

        .. code-block:: python

            import streaming
            import numpy as np
            from scipy.io.wavfile import write
            
            # Generate waveform and save as WAV
            t = np.linspace(0., 1., 1024)
            data = 32767 * np.sin(2. * np.pi * frequency * t)
            write('waveform.wav', sample_rate, data.astype(np.int16))

            # Configure and stream
            client = streaming.DACStreamClient()
            client.sendConfig('dac_rate', '125000000')  # 125 MS/s
            client.setRepeat(2)  # Repeat 2 times
            client.startStreaming('./waveform.wav')

        **Complete implementation:** :rp-github:`dac_1_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_1_stream.py>`

    .. tab:: C++

        .. grid:: 1
            :gutter: 2

            .. grid-item-card:: **C++ DAC Waveform Streaming**
                :link: https://github.com/RedPitaya/RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_1.cpp
                :link-type: url

                High-performance waveform generation with WAV files.
                
                * Pre-generated WAV file support
                * Efficient sample buffering
                * Configurable playback modes
                
                **Complexity:** ⭐⭐⭐

        |

        **Key Features:**

        .. code-block:: cpp

            #include "dac_streaming.h"
            
            // Generate sine wave and write WAV
            std::vector<int16_t> samples = generateSineWave(1000.0, 4096, 1.0);
            writeWAV("waveform.wav", 4096, samples);
            
            // Configure and stream
            DACStreamClient client;
            client.sendConfig("dac_rate", "125000000");  // 125 MS/s
            client.setRepeat(2);  // Repeat 2 times
            client.startStreaming("./waveform.wav");

        **Complete implementation:** :rp-github:`stream_dac_1.cpp → <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_1.cpp>`

|

Stereo DAC Output
==================

Stream stereo signals to both DAC channels with perfect synchronization.

**Features:**

* Stereo WAV file generation
* Independent waveforms per channel
* Infinite loop playback
* Synchronized output timing

**Complexity:** ⭐⭐⭐

|

.. tabs::

    .. tab:: Python

        **Implementation:** :rp-github:`dac_2_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_2_stream.py>`

        .. code-block:: python

            import streaming
            import numpy as np
            from scipy.io.wavfile import write
            
            # Create stereo waveform (2 channels)
            stereo = np.vstack((channel1_data, channel2_data)).transpose()
            write('stereo.wav', sample_rate, stereo)

            # Stream with infinite repeat
            client = streaming.DACStreamClient()
            client.sendConfig('dac_rate', '262144')
            client.setRepeatInf(True)
            client.startStreaming('./stereo.wav')

    .. tab:: C++

        **Implementation:** :rp-github:`stream_dac_2.cpp → <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_2.cpp>`

        .. code-block:: cpp

            #include "dac_streaming.h"
            
            // Generate stereo sine waves
            std::vector<int8_t> left = generate8bitSine(1000.0, 262144, 1.0);
            std::vector<int8_t> right = generate8bitSine(1000.0, 262144, 1.0);
            
            // Write stereo WAV and stream
            writeStereoWAV("stereo.wav", 262144, left, right);
            
            DACStreamClient client;
            client.sendConfig("dac_rate", "262144");
            client.setRepeatInf(true);
            client.startStreaming("./stereo.wav");

|

Direct Memory Mode
===================

Stream waveforms directly from memory buffers for zero-latency playback.

**Features:**

* Zero file I/O overhead
* Direct FPGA memory upload
* Real-time waveform generation
* Independent channel control

**Complexity:** ⭐⭐⭐

|

.. tabs::

    .. tab:: Python

        **Implementation:** :rp-github:`dac_3_stream.py → <RedPitaya-Examples/blob/main/python-api/Streaming/dac_3_stream.py>`

        .. code-block:: python

            import streaming
            import numpy as np
            
            # Generate waveform in memory
            waveform_data = (32767 * np.sin(2. * np.pi * t)).astype(np.int16).tolist()

            # Load directly to FPGA memory
            client = streaming.DACStreamClient()
            client.setMemory16Bit(1, waveform_data)  # Channel 1
            client.setMemory16Bit(2, waveform_data)  # Channel 2
            
            # Start streaming from memory (no file needed)
            client.startStreamingFromMemory()

    .. tab:: C++

        **Implementation:** :rp-github:`stream_dac_3.cpp → <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_3.cpp>`

        .. code-block:: cpp

            #include "dac_streaming.h"
            
            // Generate waveform in memory
            std::vector<int16_t> waveform = generateSineWave(1000.0, 32768, 1.0);
            
            // Load directly to FPGA memory
            DACStreamClient client;
            client.setMemory16Bit(1, waveform);  // Channel 1
            client.setMemory16Bit(2, waveform);  // Channel 2
            
            // Start streaming from memory (no file needed)
            client.startStreamingFromMemory();

|

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
* :ref:`Configuration Guide <streaming_configuration_top>`
* :ref:`Performance Limits <streaming_limits>`
* :ref:`Performance Optimization <streaming_performance_optimization>` - Disable web interface for maximum performance
* :ref:`Multi-board Synchronization <x-ch_streaming>`
* :rp-github:`Report Issues or Request Examples <RedPitaya-Examples/issues>`

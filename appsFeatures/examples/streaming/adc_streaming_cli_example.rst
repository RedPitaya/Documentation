.. _stream_adc_cli_example:

#####################################
ADC Streaming Example (Command Line)
#####################################

This example demonstrates how to capture data from the ADC inputs and save it to your computer using the **rpsa_client** command-line tool. 
This tutorial covers the complete workflow from configuration to data acquisition and conversion.

.. note::

    This tutorial uses the **rpsa_client** command-line tool, not the Python/C++ API. For API-based ADC streaming, see :ref:`ADC API Streaming Tutorial <streaming_adc_api_example>`.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Prerequisites
**************

Before starting this example, ensure you have:

* Red Pitaya board with OS version 2.07-43 or newer
* :ref:`Command line client <stream_command_client>` installed on your computer
* Enough :ref:`DMM memory <deepMemoryMode>` reserved for ADC streaming (at least 100 MB recommended)
* :ref:`SSH access <ssh>` to your Red Pitaya board
* For maximum performance, :ref:`disable the web interface <service_management>` before streaming
* Input signal source (optional - can capture ambient noise for testing)

|

Overview
*********

This example will guide you through:

1. Establishing SSH connection to Red Pitaya
2. Loading the FPGA and starting the streaming application
3. Configuring the ADC streaming parameters
4. Capturing data to binary format
5. Converting the captured data to WAV, CSV, or TDMS format
6. Analyzing the results

The example captures data at 1 MS/s (decimation 125) from both input channels. For maximum achievable sample rates and performance considerations, see :ref:`Streaming Performance Limits <streaming_limits>`.

|

Step-by-step tutorial
**********************

Step 1: Establish SSH connection
==================================

Connect to your Red Pitaya board using SSH. Replace ``<IP_ADDRESS>`` with your Red Pitaya's IP address or use the ``.local`` address.

.. code-block:: console

    ssh root@<IP_ADDRESS or .LOCAL_ADDRESS>

For example:

.. code-block:: console

    ssh root@192.168.1.100
    # or
    ssh root@rp-f0xxxx.local

The default password is ``root``.

|

Step 2: Load FPGA and start streaming application
===================================================

Once connected via SSH, load the streaming FPGA image and start the streaming server:

.. code-block:: console

    redpitaya> overlay.sh stream_app
    redpitaya> streaming-server

You should see LED 2 turn on and LED 0 blinking, indicating the streaming application is running.

.. note::

    Keep this SSH terminal open. The streaming server must be running for the next steps.

|

Step 3: Get and edit the configuration file
=============================================

Open a new terminal or command prompt window on your computer (don't close the SSH session). Navigate to the directory where the command line client is installed.

**Download the configuration file:**

.. code-block:: console

    computer> .\rpsa_client.exe -c -g F

The configuration file will be downloaded to the ``configs`` folder of the command line client.

|

**Edit the configuration file:**

Open the downloaded configuration file (usually named something like ``config_<board_IP>.json``) with your favorite text editor. 

For this example, configure ADC streaming at 1 MS/s (decimation 125) on channels 1 and 2:

.. code-block:: javascript

    {
        "adc_streaming" : {
            "adc_decimation" : 125,
            "channel_state_1" : "ON",
            "channel_state_2" : "ON",
            "channel_attenuator_1" : "A_1_1",
            "channel_attenuator_2" : "A_1_1",
            ...
        },
        "memory_manager" : {
            "adc_size" : 104857600,
            "block_size" : 8388608,
            ...
        }
    }

Key parameters:

* ``adc_decimation: 125`` - Sample rate = 125 MS/s ÷ 125 = 1 MS/s
* ``channel_state_1/2: "ON"`` - Enable both input channels
* ``channel_attenuator_1/2: "A_1_1"`` - 1:1 attenuation (±1V range)
* ``adc_size: 104857600`` - 100 MiB reserved for ADC buffer
* ``block_size: 8388608`` - 8 MiB network packet size (max supported)

For complete configuration options, see :ref:`ADC Configuration Reference <stream_adc_config>`

.. note::

    **Sample Rate Calculation:**
    
    .. math::

        \text{Sample Rate} = \frac{125 \text{ MS/s}}{\text{decimation}} = \frac{125,000,000}{125} = 1,000,000 \text{ samples/s}

.. note::

    1 MiB = 1024×1024 Bytes = 2^20 Bytes = 1,048,576 Bytes. We are using Mebibytes (MiB) instead of Megabytes (MB) to avoid confusion with the decimal system.

Save the edited configuration file as ``config_adc.json``.

|

**Upload the configuration file:**

Upload the edited configuration file to the Red Pitaya board:

.. code-block:: console

    computer> .\rpsa_client.exe -c -s F -f .\configs\config_adc.json

|

Step 4: Start ADC streaming and capture data
==============================================

Start capturing ADC data to a binary file:

.. code-block:: console

    computer> .\rpsa_client.exe -i -f bin -t ./data/ -s 1000000

Parameters explained:

* ``-i`` - Input (ADC streaming mode)
* ``-f bin`` - Binary file format (most efficient)
* ``-t ./data/`` - Save to the ``data`` folder
* ``-s 1000000`` - Capture 1,000,000 samples (1 second at 1 MS/s)

The command will start capturing data and display progress:

.. code-block:: console

    Connecting to board...
    Connected: 192.168.1.100
    Starting streaming...
    Received: 500000 samples
    Received: 1000000 samples
    Streaming complete
    Data saved to: ./data/data_file_192.168.1.100.bin

.. tip::

    **Capture duration:**
    
    To capture for a specific time period, calculate the number of samples:
    
    .. math::

        \text{Samples} = \text{Sample Rate} \times \text{Duration (seconds)}
    
    Examples:
    
    * 1 second at 1 MS/s: ``-s 1000000``
    * 5 seconds at 1 MS/s: ``-s 5000000``
    * 10 seconds at 100 kS/s (decimation 1250): ``-s 1000000``

To capture indefinitely, omit the ``-s`` parameter and stop manually with ``Ctrl+C``:

.. code-block:: console

    computer> .\rpsa_client.exe -i -f bin -t ./data/

|

Step 5: Convert the binary data
=================================

The captured binary file must be converted to a readable format for analysis.

**Quick conversion example:**

.. code-block:: console

    computer> .\convert_tool.exe .\data\data_file_192.168.1.100.bin -f WAV

This creates a WAV file that can be opened in audio editors like |Audacity| for analysis.

**Available formats:**

* **WAV** - For audio editors (Audacity, etc.) and signal analysis
* **CSV** - For spreadsheets, Python, MATLAB analysis  
* **TDMS** - For NI DIAdem or LabVIEW

For complete convert tool documentation including file info display, segment conversion, and format details, see :ref:`Convert Tool Reference <streaming_convert_tool>`.

|

Step 6: Analyze the captured data
===================================

**Quick analysis with Python:**

If you have Python with NumPy and Matplotlib installed:

.. code-block:: python

    import numpy as np
    import matplotlib.pyplot as plt
    from scipy.io import wavfile

    # Read WAV file
    sample_rate, data = wavfile.read('data_file_192.168.1.100.wav')
    
    # Extract channels
    ch1 = data[:, 0]
    ch2 = data[:, 1]
    
    # Create time axis
    time = np.arange(len(ch1)) / sample_rate
    
    # Plot signals
    plt.figure(figsize=(12, 6))
    
    plt.subplot(2, 1, 1)
    plt.plot(time[:1000], ch1[:1000])  # First 1000 samples
    plt.title('Channel 1')
    plt.xlabel('Time (s)')
    plt.ylabel('Amplitude (V)')
    plt.grid(True)
    
    plt.subplot(2, 1, 2)
    plt.plot(time[:1000], ch2[:1000])
    plt.title('Channel 2')
    plt.xlabel('Time (s)')
    plt.ylabel('Amplitude (V)')
    plt.grid(True)
    
    plt.tight_layout()
    plt.show()
    
    # Calculate statistics
    print(f"Channel 1: min={ch1.min():.4f}V, max={ch1.max():.4f}V, mean={ch1.mean():.4f}V")
    print(f"Channel 2: min={ch2.min():.4f}V, max={ch2.max():.4f}V, mean={ch2.mean():.4f}V")

|

Troubleshooting
****************

No data captured
=================

**Problem:** Command completes but file is empty or very small

**Solutions:**

1. Verify streaming server is running on Red Pitaya (LED 2 on, LED 0 blinking)
2. Check that channels are enabled: ``"channel_state_1": "ON"``
3. Verify network connectivity: ``ping <Red_Pitaya_IP>``
4. Check firewall settings - ensure ``rpsa_client.exe`` has network access
5. Try increasing ``block_size`` to 8 MB in configuration

|

Data loss reported
===================

**Problem:** Console shows "Lost samples" or data has gaps

**Solutions:**

1. **Reduce sample rate** (increase decimation):
   
   * Try decimation 250 for 500 kS/s
   * Or decimation 1250 for 100 kS/s

2. **Ensure maximum block size** (8 MB):

   .. code-block:: json

       "block_size" : 8388608

3. **Check network performance:**
   
   * Use wired Ethernet connection (not WiFi)
   * Ensure no other heavy network traffic
   * Close unnecessary applications

4. **Increase reserved memory:**

   .. code-block:: json

       "adc_size" : 209715200    // 200 MiB

|

Conversion tool fails
======================

**Problem:** ``convert_tool.exe`` reports errors or crashes

**Solutions:**

1. Verify the binary file is not corrupted:
   
   .. code-block:: console

       computer> .\convert_tool.exe .\data\data_file.bin -i

2. Check available disk space for the converted file
3. Ensure the file format is uppercase: ``WAV``, ``CSV``, or ``TDMS``
4. Try converting smaller segments if the file is very large

|

Configuration rejected
=======================

**Problem:** Configuration upload fails

**Solutions:**

1. Validate JSON syntax using a JSON validator
2. Ensure all parameter values are valid (see :ref:`Configuration Reference <stream_config>`)
3. Check memory allocations don't exceed reserved DMM size
4. Restart the streaming server and try again

|

Variations and extensions
***************************

High-speed capture
===================

For maximum network streaming rate, use the lowest decimation that stays within network limits.

With 2 channels at 16-bit resolution, the :ref:`maximum network transfer rate is 62.5 MB/s <streaming_limits>`, which limits maximum achievable sample rate:

.. code-block:: javascript

    {
        "adc_streaming" : {
            "adc_decimation" : 8,
            "channel_state_1" : "ON",
            "channel_state_2" : "ON",
            "adc_size" : 209715200,
            "block_size" : 8388608,
            ...
        }
    }

This achieves approximately 15.625 MS/s per channel (125 MS/s ÷ 8), which generates 62.5 MB/s for dual channels.

.. note::

    Higher sample rates require fewer channels or local SD card storage. See :ref:`Streaming Performance Limits <streaming_limits>` for detailed throughput calculations.

|

Single channel capture
=======================

To reduce data rate and storage, capture only one channel:

.. code-block:: javascript

    {
        "adc_streaming" : {
            "channel_state_1" : "ON",
            "channel_state_2" : "OFF",
            ...
        }
    }

|

High-resolution mode
=====================

Use 1:20 attenuation for ±20V input range:

.. code-block:: javascript

    {
        "adc_streaming" : {
            "channel_attenuator_1" : "A_1_20",
            "channel_attenuator_2" : "A_1_20",
            ...
        }
    }

|

AC coupling
============

Remove DC offset by enabling AC coupling:

.. code-block:: javascript

    {
        "adc_streaming" : {
            "channel_ac_dc_1" : "AC",
            "channel_ac_dc_2" : "AC",
            ...
        }
    }

|

Triggered capture
==================

To capture only when a trigger condition is met, use the API-based approach. The command-line client does not support advanced triggering, but you can:

1. Use the :ref:`ADC API Streaming Tutorial <streaming_adc_api_example>` for software triggering
2. Configure external trigger via :ref:`GPIO <gpio>` if hardware triggering is needed

|

Next steps
***********

* Experiment with different sample rates and decimation values
* Learn about :ref:`ADC Configuration <stream_adc_config>` for more control options
* Optimize performance by :ref:`disabling the web interface <streaming_performance_optimization>`
* Explore :ref:`Multi-board synchronized streaming <multiboard_stream>` for 4+ channels
* Try the :ref:`ADC API Streaming Tutorial <streaming_adc_api_example>` for programmatic control
* Analyze captured data with signal processing tools (Python, MATLAB, LabVIEW)

|

Related documentation
**********************

* :ref:`Command Line Client Reference <stream_command_client>` - Complete rpsa_client documentation
* :ref:`ADC Configuration <stream_adc_config>` - Detailed configuration parameters
* :ref:`Streaming Memory Management <stream_memory>` - Understanding DMM allocation
* :ref:`ADC API Tutorial <streaming_adc_api_example>` - Python/C++ API streaming


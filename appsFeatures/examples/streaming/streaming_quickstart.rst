.. _streaming_quickstart:

#########################
Quick Start Guide
#########################

Get started with Red Pitaya streaming in under 5 minutes. This guide shows the minimal code needed to stream ADC data from your Red Pitaya to your computer.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Prerequisites
**************

* Red Pitaya board connected to your network
* Python 3.9 or newer installed on your computer
* Red Pitaya ``rp-stream`` streaming library (included in the :ref:`Streaming command line client <streaming_pc_clients>`)

|

Step 1: Start the Streaming Server
************************************

First, ensure the streaming application is running on your Red Pitaya. You can start it in two ways:

**Option A: From the Web Interface**

Open your Red Pitaya's web interface and click on the "Data stream control" application.

**Option B: Load FPGA and Run**

.. code-block:: bash

    ssh root@rp-xxxxxx.local
    overlay.sh stream_app
    streaming-server

Once running, LED 2 will turn on and LED 0 will blink.

|

Step 2: Minimal ADC Streaming Example
***************************************

This example streams 1 second of data from both ADC channels at 488 kS/s.

Create a file called ``my_first_stream.py``:

.. code-block:: python

    #!/usr/bin/python3
    import numpy as np
    import streaming

    # Simple callback to collect data
    class DataCollector(streaming.ADCCallback):
        def __init__(self):
            super().__init__()
            self.data_ch1 = []
            self.data_ch2 = []
        
        def receivePack(self, client, pack):
            """Called automatically when new data arrives"""
            self.data_ch1.extend(pack.channel1.raw)
            self.data_ch2.extend(pack.channel2.raw)
            print(f"Received {len(pack.channel1.raw)} samples")

    # Create streaming client
    client = streaming.ADCStreamClient()
    collector = DataCollector()
    client.setReceiveDataFunction(collector.__disown__())

    # Connect to Red Pitaya (auto-discovery)
    print("Connecting to Red Pitaya...")
    if not client.connect():
        print("ERROR: Cannot connect!")
        exit(1)

    # Configure streaming
    client.sendConfig('adc_decimation', '256')      # 125 MS/s ÷ 256 = 488 kS/s
    client.sendConfig('channel_state_1', 'ON')      # Enable channel 1
    client.sendConfig('channel_state_2', 'ON')      # Enable channel 2

    # Start streaming
    print("Starting acquisition...")
    client.startStreaming()
    
    # Wait for completion (or use Ctrl+C to stop)
    try:
        client.wait()
    except KeyboardInterrupt:
        print("\nStopping...")

    # Show results
    print(f"\nCollected {len(collector.data_ch1):,} samples per channel")
    print(f"Channel 1 range: {min(collector.data_ch1)} to {max(collector.data_ch1)}")
    print(f"Channel 2 range: {min(collector.data_ch2)} to {max(collector.data_ch2)}")

**Run it:**

.. code-block:: bash

    python my_first_stream.py

You should see output like:

.. code-block:: text

    Connecting to Red Pitaya...
    Starting acquisition...
    Received 8192 samples
    Received 8192 samples
    ...
    
    Collected 488,281 samples per channel
    Channel 1 range: -145 to 132
    Channel 2 range: -98 to 87

|

Understanding the Code
***********************

The example demonstrates the three key components of streaming:

1.  **Callback Class** - Handles incoming data packets

    .. code-block:: python

        class DataCollector(streaming.ADCCallback):
            def receivePack(self, client, pack):
                # Process data as it arrives
                self.data_ch1.extend(pack.channel1.raw)

2.  **Client Setup** - Configure connection and parameters

    .. code-block:: python

        client = streaming.ADCStreamClient()
        client.connect()  # Auto-discovery
        client.sendConfig('adc_decimation', '256')

3.  **Streaming Control** - Start and wait for data

    .. code-block:: python

        client.startStreaming()
        client.wait()

|

Next Steps
***********

Now that you have basic streaming working, explore more advanced features:

* **Increase sample rate** - Change ``adc_decimation`` to lower values (min: 1 for 125 MS/s)
* **Process in real-time** - Add signal processing in the ``receivePack()`` callback
* **Save to file** - Write data to CSV, HDF5, or binary formats
* **Visualize live** - Use matplotlib for real-time plotting

|

Configuration Parameters
*************************

Common configuration options you can adjust:

.. list-table::
    :header-rows: 1
    :widths: 30 50 20

    * - Parameter
      - Description
      - Default
    * - ``adc_decimation``
      - Sample rate = 125 MS/s ÷ decimation (1, 2, 4, 8, 16, 17, 18, ..., 65536)
      - 1
    * - ``channel_state_1``
      - Enable channel 1 (ON/OFF)
      - OFF
    * - ``channel_state_2``
      - Enable channel 2 (ON/OFF)
      - OFF
    * - ``block_size``
      - Network packet size in bytes (2048-2097152)
      - 131072
    * - ``adc_pass_mode``
      - Destination (NET or FILE for SD card)
      - NET

For complete configuration reference, see :ref:`Streaming Configuration <stream_configuration>`.

|

Troubleshooting
****************

**Cannot connect to Red Pitaya or board not found**

    * Verify the IP address or hostname
    * Ensure streaming server is running (LED 2 should be on and LED 0 blinking)
    * Check network connectivity: ``ping rp-xxxxxx.local``
    * **Check firewall/antivirus settings** - Python or C++ may be blocked from network access

    Common error symptoms indicating firewall/antivirus blocking:

    .. code-block:: shell-session

        # Host not found error
        2026.01.30-14.25.08.342:  Host not found
        The client did not connect

    If you see these errors, ensure Python and C++ are allowed network access in your firewall and antivirus software. The easiest way to resolve this is to run the program a few times, then 
    check the firewall/antivirus logs to see if it blocked the application, and create an exception for it (look for "Network access troubleshooting", "Resolve blocked communication", 
    etc. in your security software documentation).

**No data received**

   * Verify channels are enabled (``channel_state_1`` and ``channel_state_2``)
   * Check if streaming server is still running
   * Review Red Pitaya logs: ``journalctl -u streaming-server``

**Data loss reported (``fpgaLost > 0``)**

   * Reduce sample rate (increase decimation)
   * Increase ``block_size`` for more efficient network transfer
   * Check network bandwidth and latency

|

Complete Examples
******************

For production-ready examples with error handling, memory management, and advanced features, see :ref:`Streaming Examples <examples_streaming>`.

**Python Examples:**

* :rp-github:`ADC Streaming <RedPitaya-Examples/blob/main/python-api/Streaming/adc_1_stream.py>` - Full-featured ADC streaming with numpy arrays
* :rp-github:`Multi-Board ADC <RedPitaya-Examples/blob/main/python-api/Streaming/adc_2_stream.py>` - Synchronized acquisition from multiple boards
* :rp-github:`DAC Streaming <RedPitaya-Examples/blob/main/python-api/Streaming/dac_1_stream.py>` - Generate waveforms from WAV files
* :rp-github:`Stereo DAC <RedPitaya-Examples/blob/main/python-api/Streaming/dac_2_stream.py>` - Dual channel DAC output
* :rp-github:`Memory Streaming <RedPitaya-Examples/blob/main/python-api/Streaming/dac_3_stream.py>` - Direct memory buffer streaming

**C++ Examples:**

* :rp-github:`ADC Streaming <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_adc_1.cpp>` - High-performance ADC acquisition
* :rp-github:`Multi-Board ADC <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_adc_2.cpp>` - Synchronized multi-board streaming
* :rp-github:`DAC Streaming <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_1.cpp>` - WAV file generation and streaming
* :rp-github:`Stereo DAC <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_2.cpp>` - Stereo WAV output
* :rp-github:`Memory Streaming <RedPitaya-Examples/blob/main/C/API_Examples/Streaming/stream_dac_3.cpp>` - Memory buffer streaming

|

API Documentation
******************

For detailed class and method documentation, see :ref:`Streaming API Reference <streaming_api_reference>`.

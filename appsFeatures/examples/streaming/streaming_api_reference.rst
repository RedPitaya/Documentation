.. _streaming_api_reference:

#########################
Streaming API Reference
#########################

Complete API documentation for the Red Pitaya streaming client library. This library enables high-performance data streaming between Red Pitaya and your computer.

.. note::

    The streaming client library runs on your **computer** (not on Red Pitaya). It communicates with the streaming server running on Red Pitaya over TCP/IP.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Overview
*********

The streaming API provides two main client classes for bidirectional data streaming:

* **ADCStreamClient** - Stream data from Red Pitaya ADC inputs to your computer
* **DACStreamClient** - Stream waveforms from your computer to Red Pitaya DAC outputs

Both classes use a callback-based architecture for efficient, non-blocking data transfer.

**Architecture:**

.. code-block:: text

    Computer                          Red Pitaya
    ┌──────────────────┐             ┌─────────────────┐
    │  Your Program    │             │ Streaming Server│
    │                  │   TCP/IP    │                 │
    │  ADCStreamClient ├────────────►│  FPGA → ADC     │
    │  DACStreamClient │◄────────────┤  DAC ← FPGA     │
    │                  │             │                 │
    │  Callback Class  │             │  Deep Memory    │
    └──────────────────┘             └─────────────────┘

|

Installation
*************

**Python:**

The ``rp_stream`` Python library is included with the :ref:`Streaming command line client <streaming_pc_clients>`. Download the command line client from the Data Stream control application 
on your Red Pitaya.

**C++:**

The C++ streaming library is included with the :ref:`Streaming command line client <streaming_pc_clients>`. Download the command line client from the Data Stream control application 
on your Red Pitaya.

|

ADC Streaming API
******************

ADCStreamClient Class
======================

Main class for streaming data from Red Pitaya ADC channels to your computer.

**Basic Usage:**

.. code-block:: python

    import rp_stream as streaming
    
    # Create client
    client = streaming.ADCStreamClient()
    
    # Set callback handler
    callback = MyADCCallback()
    client.setReciveDataFunction(callback.__disown__())
    
    # Connect (auto-discovery)
    client.connect()
    
    # Configure streaming
    client.sendConfig('adc_decimation', '256')
    
    # Start streaming
    client.startStreaming()
    client.wait()

|

Connection Methods
-------------------

.. py:method:: connect() -> bool

    Connect to a single Red Pitaya using auto-discovery. Automatically searches the network for available Red Pitaya boards and connects to the first one found.
    
    :returns: ``True`` if connection successful, ``False`` otherwise
    
    **Example:**
    
    .. code-block:: python
    
        if not client.connect():
            print("Connection failed")
    
    .. note::
    
        Currently connects to a single host only. For multi-board acquisition, use ``connect(hosts)`` method.

.. py:method:: connect(hosts: list[str]) -> bool

    Connect to multiple Red Pitaya boards for synchronized multi-board acquisition (master/slave configuration). The first board in the list acts as the master.
    
    :param hosts: List of hostnames or IP addresses (first is master, rest are slaves)
    :returns: ``True`` if all connections successful
    
    **Example:**
    
    .. code-block:: python
    
        # Master board first, then slaves
        boards = ["200.0.0.7", "200.0.0.8"]
        client.connect(boards)
        
        # Configure master board
        client.sendConfig(boards[0], 'adc_decimation', '64')
        client.sendConfig(boards[0], 'channel_state_1', 'ON')
        
        # Copy config to slave
        config = client.getFileConfig(boards[0])
        client.sendFileConfig(boards[1], config)

|

Configuration Methods
----------------------

.. py:method:: sendConfig(key: str, value: str) -> bool

   Send a configuration parameter to the streaming server.
   
   :param key: Configuration parameter name
   :param value: Parameter value as string
   :returns: ``True`` if configuration accepted
   
   **Common parameters:**
   
   .. list-table::
      :header-rows: 1
      :widths: 30 50 20
   
      * - Key
        - Description
        - Values
      * - ``adc_decimation``
        - Sample rate divisor (1-65536)
        - "1" - "65536"
      * - ``adc_pass_mode``
        - Destination mode
        - "NET", "FILE"
      * - ``channel_state_1``
        - Enable/disable channel 1
        - "ON", "OFF"
      * - ``channel_state_2``
        - Enable/disable channel 2
        - "ON", "OFF"
      * - ``channel_state_3``
        - Enable/disable channel 3 (250-12)
        - "ON", "OFF"
      * - ``channel_state_4``
        - Enable/disable channel 4 (250-12)
        - "ON", "OFF"
      * - ``block_size``
        - Network packet size (bytes)
        - "2048" - "2097152"
      * - ``adc_size``
        - FPGA buffer size (bytes)
        - "1048576" - "104857600"
   
   **Example:**
   
   .. code-block:: python
   
       client.sendConfig('adc_decimation', '256')
       client.sendConfig('channel_state_1', 'ON')
       client.sendConfig('block_size', '131072')

.. py:method:: sendConfig(host: str, key: str, value: str) -> bool

   Send configuration to a specific board in multi-board setup.
   
   :param host: Target Red Pitaya hostname
   :param key: Configuration parameter name
   :param value: Parameter value
   :returns: ``True`` if configuration accepted

.. py:method:: getConfig(key: str) -> str

   Retrieve current configuration value from the server.
   
   :param key: Configuration parameter name
   :returns: Current value as string
   
   **Example:**
   
   .. code-block:: python
   
       decimation = client.getConfig('adc_decimation')
       print(f"Current decimation: {decimation}")

.. py:method:: getConfig(host: str, key: str) -> str

   Retrieve configuration from specific board in multi-board setup.

|

Streaming Control Methods
---------------------------

.. py:method:: startStreaming() -> bool

   Start the data streaming process.
   
   :returns: ``True`` if streaming started successfully
   
   **Example:**
   
   .. code-block:: python
   
       if not client.startStreaming():
           print("Failed to start streaming")

.. py:method:: stopStreaming() -> void

   Stop the streaming process on all connected boards.
   
   **Example:**
   
   .. code-block:: python
   
       client.stopStreaming()

.. py:method:: wait() -> void

   Block until streaming completes or is stopped. Call this after ``startStreaming()``.
   
   **Example:**
   
   .. code-block:: python
   
       client.startStreaming()
       client.wait()  # Blocks here until streaming stops

.. py:method:: notifyStop() -> void

   Signal the streaming process to stop (for use in callbacks or other threads).
   
   **Example:**
   
   .. code-block:: python
   
       # In callback after collecting enough data:
       if self.sample_count >= self.target_samples:
           client.notifyStop()

.. py:method:: notifyStop(host: str) -> void

   Stop streaming on a specific board in multi-board setup.

|

Configuration File Methods
---------------------------

.. py:method:: sendFileConfig(config: str) -> bool

   Send a complete configuration as JSON string.
   
   :param config: JSON configuration string
   :returns: ``True`` if configuration accepted

.. py:method:: getFileConfig() -> str

   Retrieve complete configuration as JSON string.
   
   :returns: JSON configuration string

|

Utility Methods
----------------

.. py:method:: setVerbose(enable: bool) -> void

   Enable or disable detailed logging output.
   
   :param enable: ``True`` for verbose logging
   
   **Example:**
   
   .. code-block:: python
   
       client.setVerbose(True)  # Show connection and transfer details

.. py:method:: setReciveDataFunction(callback: ADCCallback) -> void

   Register a callback object to receive streaming data and events.
   
   :param callback: ADCCallback instance (use ``__disown__()`` in Python)
   
   **Example:**
   
   .. code-block:: python
   
       callback = MyADCCallback()
       client.setReciveDataFunction(callback.__disown__())

.. py:method:: removeReciveDataFunction() -> void

   Unregister the callback handler.

|

ADCCallback Class
==================

Base class for handling ADC streaming events. Override methods to process incoming data.

**Minimal Implementation:**

.. code-block:: python

    class MyCallback(streaming.ADCCallback):
        def __init__(self):
            super().__init__()
            self.data = []
        
        def recievePack(self, client, pack):
            """Called when data arrives"""
            self.data.extend(pack.channel1.raw)

|

Data Callback Method
---------------------

.. py:method:: recievePack(client: ADCStreamClient, pack: ADCPack) -> void

   **Primary callback** - Called when a new data packet arrives from the streaming server.
   
   :param client: The ADCStreamClient instance
   :param pack: ADCPack object containing channel data
   
   **ADCPack Structure:**
   
   .. code-block:: python
   
       pack.host              # str: Source Red Pitaya hostname
       pack.channel1.raw      # list[int16]: Raw ADC samples
       pack.channel1.samples  # int: Number of samples in packet
       pack.channel1.fpgaLost # int: Samples lost by FPGA buffer overflow
       pack.channel1.packId   # int: Packet sequence number
       # channel2, channel3, channel4 same structure
   
   **Example:**
   
   .. code-block:: python
   
       def recievePack(self, client, pack):
           # Store data
           self.ch1_data.extend(pack.channel1.raw)
           self.ch2_data.extend(pack.channel2.raw)
           
           # Monitor for data loss
           if pack.channel1.fpgaLost > 0:
               print(f"WARNING: Lost {pack.channel1.fpgaLost} samples")
           
           # Stop after collecting enough data
           if len(self.ch1_data) >= self.target_samples:
               client.notifyStop()

|

Connection Event Callbacks
---------------------------

.. note::

    All callback methods receive a ``host`` parameter that identifies which Red Pitaya board triggered the event. This is essential for tracking events in multi-board master/slave 
    configurations.

.. py:method:: connected(client: ADCStreamClient, host: str) -> void

   Called when successfully connected to a Red Pitaya.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that connected

.. py:method:: disconnected(client: ADCStreamClient, host: str) -> void

   Called when connection to a Red Pitaya is lost.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that disconnected

.. py:method:: error(client: ADCStreamClient, host: str, code: int) -> void

   Called when a connection or streaming error occurs.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya reporting the error
   :param code: Error code (system-specific)

|

Server State Callbacks
-----------------------

.. py:method:: stopped(client: ADCStreamClient, host: str) -> void

   Called when streaming stops normally.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that stopped

.. py:method:: stoppedNoActiveChannels(client: ADCStreamClient, host: str) -> void

   Called when streaming stops because no channels are enabled.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that stopped

.. py:method:: stoppedMemError(client: ADCStreamClient, host: str) -> void

   Called when streaming stops due to memory allocation error.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that stopped

.. py:method:: stoppedMemModify(client: ADCStreamClient, host: str) -> void

   Called when streaming stops due to memory configuration change during streaming.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that stopped

.. py:method:: stoppedSDFull(client: ADCStreamClient, host: str) -> void

   Called when streaming to SD card stops because the card is full.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that stopped

.. py:method:: stoppedSDDone(client: ADCStreamClient, host: str) -> void

   Called when streaming to SD card completes successfully.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that completed

|

Configuration Connection Callbacks
------------------------------------

.. py:method:: configConnected(client: ADCStreamClient, host: str) -> void

   Called when configuration connection is established.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that connected

.. py:method:: configError(client: ADCStreamClient, host: str, code: int) -> void

   Called when configuration connection encounters an error.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya reporting the error
   :param code: Error code

.. py:method:: configErrorTimeout(client: ADCStreamClient, host: str) -> void

   Called when configuration connection times out.
   
   :param client: The ADCStreamClient instance
   :param host: Hostname or IP of the Red Pitaya that timed out

|

DAC Streaming API
******************

DACStreamClient Class
======================

Main class for streaming waveforms from your computer to Red Pitaya DAC outputs.

**Basic Usage:**

.. code-block:: python

    import rp_stream as streaming
    
    # Create client
    client = streaming.DACStreamClient()
    
    # Set callback handler (optional)
    callback = MyDACCallback()
    client.setCallbackFunction(callback.__disown__())
    
    # Connect and configure
    client.connect("rp-xxxxxx.local")
    client.sendConfig('dac_rate', '125000000')
    
    # Stream from WAV file
    client.startStreamingWAV('./waveform.wav')
    client.wait()

|

Connection Methods
-------------------

.. py:method:: connect() -> bool

   Connect to Red Pitaya using auto-discovery.
   
   :returns: ``True`` if connection successful

.. py:method:: connect(host: str) -> bool

   Connect to specific Red Pitaya.
   
   :param host: Hostname or IP address
   :returns: ``True`` if connection successful
   
   **Example:**
   
   .. code-block:: python
   
       if not client.connect("rp-f0a235.local"):
           print("Connection failed")

|

Configuration Methods
----------------------

.. py:method:: sendConfig(key: str, value: str) -> bool

   Send configuration parameter to streaming server.
   
   **Common DAC parameters:**
   
   .. list-table::
      :header-rows: 1
      :widths: 30 50 20
   
      * - Key
        - Description
        - Values
      * - ``dac_rate``
        - DAC output rate (Hz)
        - "1" - "125000000"
      * - ``dac_pass_mode``
        - Source mode
        - "NET", "FILE"
      * - ``block_size``
        - Network packet size (bytes)
        - "2048" - "2097152"
      * - ``adc_size``
        - FPGA buffer size (bytes)
        - "1048576" - "104857600"
   
   **Example:**
   
   .. code-block:: python
   
       client.sendConfig('dac_rate', '125000000')  # 125 MS/s
       client.sendConfig('block_size', '16384')

.. py:method:: getConfig(key: str) -> str

   Retrieve current configuration value.
   
   **Example:**
   
   .. code-block:: python
   
       rate = client.getConfig('dac_rate')

|

Playback Control Methods
--------------------------

.. py:method:: setRepeatCount(count: int) -> void

   Set number of times to repeat the waveform.
   
   :param count: Number of repetitions
   
   **Example:**
   
   .. code-block:: python
   
       client.setRepeatCount(10)  # Play 10 times

.. py:method:: setRepeatInf(enable: bool) -> void

   Enable or disable infinite repeat mode.
   
   :param enable: ``True`` for continuous playback
   
   **Example:**
   
   .. code-block:: python
   
       client.setRepeatInf(True)  # Loop forever

|

Streaming Methods
------------------

.. py:method:: startStreamingWAV(fileName: str) -> bool

   Stream a WAV audio file to DAC outputs.
   
   :param fileName: Path to WAV file (relative or absolute)
   :returns: ``True`` if streaming started
   
   **Supported formats:**
   
   * Mono (1 channel) - outputs on DAC 1
   * Stereo (2 channels) - outputs on DAC 1 and DAC 2
   * 8-bit or 16-bit PCM
   
   **Example:**
   
   .. code-block:: python
   
       if not client.startStreamingWAV('./my_waveform.wav'):
           print("Failed to start")

.. py:method:: startStreamingTDMS(fileName: str) -> bool

   Stream a TDMS file to DAC outputs.
   
   :param fileName: Path to TDMS file
   :returns: ``True`` if streaming started

.. py:method:: startStreamingFromMemory() -> bool

   Stream waveforms previously loaded to memory with ``setMemory16Bit()``.
   
   :returns: ``True`` if streaming started
   
   **Example:**
   
   .. code-block:: python
   
       # Load waveform data
       waveform = [100, 200, 300, ...]  # int16 values
       client.setMemory16Bit(1, waveform)
       client.setMemory16Bit(2, waveform)
       
       # Stream from memory
       client.startStreamingFromMemory()

.. py:method:: stopStreaming() -> void

   Stop the streaming process.

.. py:method:: wait() -> void

   Block until streaming completes or is stopped.

.. py:method:: notifyStop() -> void

   Signal streaming to stop (for use in callbacks or other threads).

|

Memory Loading Methods
-----------------------

.. py:method:: setMemory8Bit(channel: int, buffer: list[int8]) -> bool

   Load 8-bit waveform data into FPGA memory for a channel.
   
   :param channel: Channel number (1 or 2)
   :param buffer: List of 8-bit signed integers
   :returns: ``True`` if data loaded successfully
   
   **Example:**
   
   .. code-block:: python
   
       data = [127, 0, -128, 0, ...]  # 8-bit values
       client.setMemory8Bit(1, data)

.. py:method:: setMemory16Bit(channel: int, buffer: list[int16]) -> bool

   Load 16-bit waveform data into FPGA memory for a channel.
   
   :param channel: Channel number (1 or 2)
   :param buffer: List of 16-bit signed integers
   :returns: ``True`` if data loaded successfully
   
   **Example:**
   
   .. code-block:: python
   
       import numpy as np
       
       # Generate waveform
       t = np.linspace(0, 1, 1024)
       waveform = (32767 * np.sin(2 * np.pi * t)).astype(np.int16)
       
       # Load to both channels
       client.setMemory16Bit(1, waveform.tolist())
       client.setMemory16Bit(2, waveform.tolist())

|

Utility Methods
----------------

.. py:method:: setVerbose(enable: bool) -> void

   Enable or disable detailed logging.

.. py:method:: setCallbackFunction(callback: DACCallback) -> void

   Register callback to receive streaming events.
   
   **Example:**
   
   .. code-block:: python
   
       callback = MyDACCallback()
       client.setCallbackFunction(callback.__disown__())

.. py:method:: removeCallbackFunction() -> void

   Unregister the callback handler.

|

DACCallback Class
==================

Base class for handling DAC streaming events. Override methods to monitor streaming progress.

**Minimal Implementation:**

.. code-block:: python

    class MyCallback(streaming.DACCallback):
        def __init__(self):
            super().__init__()
            self.packets_sent = 0
        
        def sendedPack(self, client, ch1_size, ch2_size):
            """Called after each packet is sent"""
            self.packets_sent += 1

|

Data Callback Method
---------------------

.. py:method:: sendedPack(client: DACStreamClient, ch1_size: int, ch2_size: int) -> void

   **Primary callback** - Called after a data packet is successfully sent to the DAC.
   
   :param client: The DACStreamClient instance
   :param ch1_size: Number of samples sent to channel 1
   :param ch2_size: Number of samples sent to channel 2
   
   **Example:**
   
   .. code-block:: python
   
       def sendedPack(self, client, ch1_size, ch2_size):
           self.total_samples += ch1_size + ch2_size
           print(f"Sent {self.total_samples:,} samples")

|

Connection Event Callbacks
---------------------------

.. py:method:: connected(client: DACStreamClient, host: str) -> void

   Called when successfully connected.

.. py:method:: disconnected(client: DACStreamClient, host: str) -> void

   Called when connection is lost.

.. py:method:: error(client: DACStreamClient, host: str, code: int) -> void

   Called when a connection error occurs.

|

Server State Callbacks
-----------------------

.. py:method:: stopped(client: DACStreamClient, host: str) -> void

   Called when streaming stops normally.

.. py:method:: stoppedFileEnd(client: DACStreamClient, host: str) -> void

   Called when streaming stops because the file ended.

.. py:method:: stoppedFileBroken(client: DACStreamClient, host: str) -> void

   Called when streaming stops due to corrupted file.

.. py:method:: stoppedEmpty(client: DACStreamClient, host: str) -> void

   Called when streaming stops because no data is available.

.. py:method:: stoppedMissingFile(client: DACStreamClient, host: str) -> void

   Called when streaming stops because the file is not found.

.. py:method:: stoppedMemError(client: DACStreamClient, host: str) -> void

   Called when streaming stops due to memory error.

.. py:method:: stoppedMemModify(client: DACStreamClient, host: str) -> void

   Called when streaming stops due to memory modification during streaming.

|

Configuration Connection Callbacks
------------------------------------

.. py:method:: configConnected(client: DACStreamClient, host: str) -> void

   Called when configuration connection is established.

.. py:method:: configError(client: DACStreamClient, host: str, code: int) -> void

   Called when configuration connection error occurs.

.. py:method:: configErrorTimeout(client: DACStreamClient, host: str) -> void

   Called when configuration connection times out.

|

Data Structures
****************

ADCPack Structure
==================

Contains data from a single streaming packet with information for all channels.

.. code-block:: python

    class ADCPack:
        host: str                # Source Red Pitaya hostname
        channel1: ADCChannel     # Channel 1 data
        channel2: ADCChannel     # Channel 2 data
        channel3: ADCChannel     # Channel 3 data (250-12 only)
        channel4: ADCChannel     # Channel 4 data (250-12 only)

|

ADCChannel Structure
=====================

Contains data and metadata for a single ADC channel.

.. code-block:: python

    class ADCChannel:
        samples: int             # Number of samples in this packet
        bitsBySample: int        # ADC resolution (12, 14, or 16 bits)
        fpgaLost: int            # Cumulative samples lost due to buffer overflow
        attenuator_1_20: bool    # True if 1:20 attenuator is active
        baseRate: int            # Base ADC sampling rate (Hz)
        adcBaseBits: int         # Native ADC bit depth
        packId: int              # Packet sequence number
        raw: list[int16]         # Raw ADC sample data

**Example Usage:**

.. code-block:: python

    def recievePack(self, client, pack):
        ch1 = pack.channel1
        
        # Access samples
        samples = ch1.raw
        
        # Check for data loss
        if ch1.fpgaLost > 0:
            print(f"Lost {ch1.fpgaLost} samples")
        
        # Check attenuation
        if ch1.attenuator_1_20:
            print("1:20 attenuator is active")

|

Complete Examples
******************

For complete, production-ready examples with error handling and best practices:

.. toctree::
   :maxdepth: 1

   examples_streaming_top

|

See Also
*********

* :ref:`Streaming Application <streaming_top>`
* :ref:`Quick Start Guide <streaming_quickstart>`
* :ref:`Configuration Reference <stream_configuration>`
* :rp-github:`GitHub: Streaming Client Library <streaming-client>`

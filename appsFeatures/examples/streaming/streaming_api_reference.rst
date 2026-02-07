.. _streaming_api_reference:

#########################
Streaming API Reference
#########################

Complete API documentation for the Red Pitaya streaming client library. This library enables high-performance data streaming between Red Pitaya and your computer.

.. note::

    The streaming client library runs on your **computer** (not on Red Pitaya). It communicates with the streaming server running on Red Pitaya over TCP/IP.

.. contents:: Table of contents
    :depth: 2
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
    +------------------+             +-----------------+
    |  Your Program    |             | Streaming Server|
    |                  |   TCP/IP    |                 |
    |  ADCStreamClient |------------>|  FPGA -> ADC    |
    |  DACStreamClient |<------------|  DAC <- FPGA    |
    |                  |             |                 |
    |  Callback Class  |             |  Deep Memory    |
    +------------------+             +-----------------+

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

Class Reference
****************

.. py:class:: ADCStreamClient
    
    Main client class for ADC streaming operations.

.. py:class:: ADCCallback
    
    Base callback class for ADC streaming events.

.. py:class:: ADCPack
    
    Data packet structure containing ADC channel samples.

.. py:class:: DACStreamClient
    
    Main client class for DAC streaming operations.

.. py:class:: DACCallback
    
    Base callback class for DAC streaming events.

|

ADC Streaming API
******************

ADCStreamClient Class
======================

Main class for streaming data from Red Pitaya ADC channels to your computer.

**Basic Usage:**

.. tabs::

    .. tab:: Python

        .. code-block:: python

            import rp_stream as streaming
            
            # Create client
            client = streaming.ADCStreamClient()
            
            # Set callback handler
            callback = MyADCCallback()
            client.setReceiveDataCallback(callback.__disown__())
            
            # Connect (auto-discovery)
            client.connect()
            
            # Configure streaming
            client.sendConfig('adc_decimation', '256')
            client.sendConfig('channel_state_1', 'ON')
            client.sendConfig('channel_state_2', 'ON')
            
            # Start streaming
            client.startStreaming()
            client.wait()

    .. tab:: C++

        .. code-block:: cpp

            #include "adc_streaming.h"
            #include "callbacks.h"
            
            // Create callback handler
            class MyCallback : public ADCCallback {
                void receivePack(ADCStreamClient* client, ADCPack& pack) override {
                    // Process incoming data
                }
            };
            
            // Create client
            ADCStreamClient client;
            MyCallback callback;
            client.setReceiveDataCallback(&callback);
            
            // Connect (auto-discovery)
            client.connect();
            
            // Configure streaming
            client.sendConfig("adc_decimation", "256");
            client.sendConfig("channel_state_1", "ON");
            client.sendConfig("channel_state_2", "ON");
            
            // Start streaming
            client.startStreaming();
            client.wait();

|

Connection Methods
-------------------

.. method:: connect() -> bool

    Connect to a single Red Pitaya using auto-discovery. Automatically searches the network for available Red Pitaya boards and connects to the first one found.
    
    :returns: ``True`` if connection successful, ``False`` otherwise
    :rtype: bool
    
    **Example:**
    
    .. code-block:: python
    
        if not client.connect():
            print("Connection failed")
    
    .. note::
    
        Currently connects to a single host only. For multi-board acquisition, use ``connect(hosts)`` method.

.. method:: connect(hosts: list[str]) -> bool
    :no-index:

    Connect to multiple Red Pitaya boards for synchronized multi-board acquisition (master/slave configuration). The first board in the list acts as the master.
    
    :param hosts: List of hostnames or IP addresses (first is master, rest are slaves)
    :type hosts: list[str]
    :returns: ``True`` if all connections successful
    :rtype: bool
    
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

.. method:: sendConfig(key: str, value: str) -> bool

    Send a configuration parameter to the streaming server.
   
    :param key: Configuration parameter name
    :type key: str
    :param value: Parameter value as string
    :type value: str
    :returns: ``True`` if configuration accepted
    :rtype: bool
   
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

.. method:: sendConfig(host: str, key: str, value: str) -> bool
    :no-index:

    Send configuration to a specific board in multi-board setup.
   
    :param host: Target Red Pitaya hostname
    :type host: str
    :param key: Configuration parameter name
    :type key: str
    :param value: Parameter value
    :type value: str
    :returns: ``True`` if configuration accepted
    :rtype: bool

.. method:: getConfig(key: str) -> str

    Retrieve current configuration value from the server.
   
    :param key: Configuration parameter name
    :type key: str
    :returns: Current value as string
    :rtype: str
   
    **Example:**
   
    .. code-block:: python
   
        decimation = client.getConfig('adc_decimation')
        print(f"Current decimation: {decimation}")

.. method:: getConfig(host: str, key: str) -> str
    :no-index:

    Retrieve configuration from specific board in multi-board setup.
    
    :param host: Target Red Pitaya hostname
    :type host: str
    :param key: Configuration parameter name
    :type key: str
    :rtype: str

|

Streaming Control Methods
---------------------------

.. method:: startStreaming() -> bool

    Start the data streaming process.
   
    :returns: ``True`` if streaming started successfully
    :rtype: bool
   
    **Example:**
   
    .. code-block:: python
   
        if not client.startStreaming():
            print("Failed to start streaming")

.. method:: stopStreaming()

    Stop the streaming process on all connected boards.
    
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        client.stopStreaming()

.. method:: wait()

    Block until streaming completes or is stopped. Call this after ``startStreaming()``.
    
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        client.startStreaming()
        client.wait()  # Blocks here until streaming stops

.. method:: notifyStop()

    Signal the streaming process to stop (for use in callbacks or other threads).
    
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        # In callback after collecting enough data:
        if self.sample_count >= self.target_samples:
            client.notifyStop()

.. method:: notifyStop(host)
    :no-index:

    Stop streaming on a specific board in multi-board setup.
    
    :param host: Target Red Pitaya hostname
    :type host: str
    :rtype: None

|

Configuration File Methods
---------------------------

.. method:: sendFileConfig(config)

    Send a complete configuration as JSON string.
   
    :param config: JSON configuration string
    :type config: str
    :returns: ``True`` if configuration accepted
    :rtype: bool

.. method:: getFileConfig()

    Retrieve complete configuration as JSON string.
   
    :returns: JSON configuration string
    :rtype: str

|

Utility Methods
----------------

.. method:: setVerbose(enable)

    Enable or disable detailed logging output.
   
    :param enable: ``True`` for verbose logging
    :type enable: bool
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        client.setVerbose(True)  # Show connection and transfer details

.. method:: setReceiveDataCallback(callback)

    Register a callback object to receive streaming data and events.

    :param callback: ADCCallback instance (use ``__disown__()`` in Python)
    :type callback: ADCCallback
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        callback = MyADCCallback()
        client.setReceiveDataCallback(callback.__disown__())

.. method:: removeReceiveDataCallback()

    Unregister the callback handler.
    
    :rtype: None

|

ADCCallback Class
==================

Base class for handling ADC streaming events. Override methods to process incoming data.

**Minimal Implementation:**

.. tabs::

    .. tab:: Python

        .. code-block:: python

            class MyCallback(streaming.ADCCallback):
                def __init__(self):
                    super().__init__()
                    self.data = []
                
                def receivePack(self, client, pack):
                    """Called when data arrives"""
                    if pack.channel1.samples > 0:
                        self.data.extend(pack.channel1.raw)

    .. tab:: C++

        .. code-block:: cpp

            #include "adc_streaming.h"
            #include "callbacks.h"
            
            class MyCallback : public ADCCallback {
            public:
                std::vector<int16_t> data;
                
                void receivePack(ADCStreamClient* client, ADCPack& pack) override {
                    // Process channel 1 data
                    if (pack.channel1.samples > 0) {
                        data.insert(data.end(), 
                                    pack.channel1.raw, 
                                    pack.channel1.raw + pack.channel1.samples);
                    }
                }
            };

|

Data Callback Method
---------------------

.. method:: receivePack(client, pack)

    **Primary callback** - Called when a new data packet arrives from the streaming server.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param pack: ADCPack object containing channel data
    :type pack: ADCPack
    :rtype: None
   
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
   
        def receivePack(self, client, pack):
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

.. method:: connected(client, host)

    Called when successfully connected to a Red Pitaya.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that connected
    :type host: str
    :rtype: None

.. method:: disconnected(client, host)

    Called when connection to a Red Pitaya is lost.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that disconnected
    :type host: str
    :rtype: None

.. method:: error(client, host, code)

    Called when a connection or streaming error occurs.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya reporting the error
    :type host: str
    :param code: Error code (system-specific)
    :type code: int
    :rtype: None

|

Server State Callbacks
-----------------------

.. method:: stopped(client, host)

    Called when streaming stops normally.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that stopped
    :type host: str
    :rtype: None

.. method:: stoppedNoActiveChannels(client, host)

    Called when streaming stops because no channels are enabled.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that stopped
    :type host: str
    :rtype: None

.. method:: stoppedMemError(client, host)

    Called when streaming stops due to memory allocation error.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that stopped
    :type host: str
    :rtype: None

.. method:: stoppedMemModify(client, host)

    Called when streaming stops due to memory configuration change during streaming.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that stopped
    :type host: str
    :rtype: None

.. method:: stoppedSDFull(client, host)

    Called when streaming to SD card stops because the card is full.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that stopped
    :type host: str
    :rtype: None

.. method:: stoppedSDDone(client, host)

    Called when streaming to SD card completes successfully.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that completed
    :type host: str
    :rtype: None

|

Configuration Connection Callbacks
------------------------------------

.. method:: configConnected(client, host)

    Called when configuration connection is established.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that connected
    :type host: str
    :rtype: None

.. method:: configError(client, host, code)

    Called when configuration connection encounters an error.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya reporting the error
    :type host: str
    :param code: Error code
    :type code: int
    :rtype: None

.. method:: configErrorTimeout(client, host)

    Called when configuration connection times out.
   
    :param client: The ADCStreamClient instance
    :type client: ADCStreamClient
    :param host: Hostname or IP of the Red Pitaya that timed out
    :type host: str
    :rtype: None

|

DAC Streaming API
******************

DACStreamClient Class
======================

Main class for streaming waveforms from your computer to Red Pitaya DAC outputs.

**Basic Usage:**

.. tabs::

    .. tab:: Python

        .. code-block:: python

            import rp_stream as streaming
            
            # Create client
            client = streaming.DACStreamClient()
            
            # Set callback handler (optional)
            callback = MyDACCallback()
            client.setCallback(callback.__disown__())
            
            # Connect and configure
            client.connect()
            client.sendConfig('dac_rate', '125000000')
            client.sendConfig('dac_pass_mode', 'NET')
            
            # Stream from WAV file
            client.startStreaming('./waveform.wav')
            client.wait()

    .. tab:: C++

        .. code-block:: cpp

            #include "dac_streaming.h"
            #include "callbacks.h"
            
            // Create callback handler
            class MyCallback : public DACCallback {
                void sentPack(DACStreamClient* client, uint32_t ch1, uint32_t ch2) override {
                    // Handle sent packet notification
                }
            };
            
            // Create client
            DACStreamClient client;
            MyCallback callback;
            client.setCallback(&callback);
            
            // Connect and configure
            client.connect();
            client.sendConfig("dac_rate", "125000000");
            client.sendConfig("dac_pass_mode", "NET");
            
            // Stream from WAV file
            client.startStreaming("./waveform.wav");
            client.wait();

|

Connection Methods
-------------------

.. method:: connect() -> bool
    :no-index:

    Connect to Red Pitaya using auto-discovery.
   
    :returns: ``True`` if connection successful
    :rtype: bool

.. method:: connect(host: str) -> bool
    :no-index:

    Connect to specific Red Pitaya.
   
    :param host: Hostname or IP address
    :type host: str
    :returns: ``True`` if connection successful
    :rtype: bool
   
    **Example:**
   
    .. code-block:: python
   
        if not client.connect("rp-f0a235.local"):
            print("Connection failed")

|

Configuration Methods
----------------------

.. method:: sendConfig(key: str, value: str) -> bool
    :no-index:

    Send configuration parameter to streaming server.
    
    :param key: Configuration parameter name
    :type key: str
    :param value: Parameter value
    :type value: str
    :rtype: bool
   
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

.. method:: getConfig(key: str) -> str
    :no-index:

    Retrieve current configuration value.
    
    :param key: Configuration parameter name
    :type key: str
    :rtype: str
   
    **Example:**
   
    .. code-block:: python
   
        rate = client.getConfig('dac_rate')

|

Playback Control Methods
--------------------------

.. method:: setRepeatCount(count)

    Set number of times to repeat the waveform.
   
    :param count: Number of repetitions
    :type count: int
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        client.setRepeatCount(10)  # Play 10 times

.. method:: setRepeatInf(enable)

    Enable or disable infinite repeat mode.
   
    :param enable: ``True`` for continuous playback
    :type enable: bool
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        client.setRepeatInf(True)  # Loop forever

|

Streaming Methods
------------------

.. method:: startStreamingWAV(fileName)

    Stream a WAV audio file to DAC outputs.
   
    :param fileName: Path to WAV file (relative or absolute)
    :type fileName: str
    :returns: ``True`` if streaming started
    :rtype: bool
   
    **Supported formats:**
   
    * Mono (1 channel) - outputs on DAC 1
    * Stereo (2 channels) - outputs on DAC 1 and DAC 2
    * 8-bit or 16-bit PCM
   
    **Example:**
   
    .. code-block:: python
   
        if not client.startStreamingWAV('./my_waveform.wav'):
            print("Failed to start")

.. method:: startStreamingTDMS(fileName)

    Stream a TDMS file to DAC outputs.
   
    :param fileName: Path to TDMS file
    :type fileName: str
    :returns: ``True`` if streaming started
    :rtype: bool

.. method:: startStreamingFromMemory()

    Stream waveforms previously loaded to memory with ``setMemory16Bit()``.
   
    :returns: ``True`` if streaming started
    :rtype: bool
   
    **Example:**
   
    .. code-block:: python
   
        # Load waveform data
        waveform = [100, 200, 300, ...]  # int16 values
        client.setMemory16Bit(1, waveform)
        client.setMemory16Bit(2, waveform)
        
        # Stream from memory
        client.startStreamingFromMemory()

.. method:: stopStreaming()
    :no-index:

    Stop the streaming process.
    
    :rtype: None

.. method:: wait()
    :no-index:

    Block until streaming completes or is stopped.
    
    :rtype: None

.. method:: notifyStop()
    :no-index:

    Signal streaming to stop (for use in callbacks or other threads).
    
    :rtype: None

|

Memory Loading Methods
-----------------------

.. method:: setMemory8Bit(channel, buffer)

    Load 8-bit waveform data into FPGA memory for a channel.
   
    :param channel: Channel number (1 or 2)
    :type channel: int
    :param buffer: List of 8-bit signed integers
    :type buffer: list[int]
    :returns: ``True`` if data loaded successfully
    :rtype: bool
   
    **Example:**
   
    .. code-block:: python
   
        data = [127, 0, -128, 0, ...]  # 8-bit values
        client.setMemory8Bit(1, data)

.. method:: setMemory16Bit(channel, buffer)

    Load 16-bit waveform data into FPGA memory for a channel.
   
    :param channel: Channel number (1 or 2)
    :type channel: int
    :param buffer: List of 16-bit signed integers
    :type buffer: list[int]
    :returns: ``True`` if data loaded successfully
    :rtype: bool
   
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

.. method:: setVerbose(enable)
    :no-index:

    Enable or disable detailed logging.
    
    :param enable: ``True`` for verbose logging
    :type enable: bool
    :rtype: None

.. method:: setCallbackFunction(callback)

    Register callback to receive streaming events.
   
    :param callback: DACCallback instance
    :type callback: DACCallback
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        callback = MyDACCallback()
        client.setCallbackFunction(callback.__disown__())

.. method:: removeCallbackFunction()

    Unregister the callback handler.
    
    :rtype: None

|

DACCallback Class
==================

Base class for handling DAC streaming events. Override methods to monitor streaming progress.

**Minimal Implementation:**

.. tabs::

    .. tab:: Python

        .. code-block:: python

            class MyCallback(streaming.DACCallback):
                def __init__(self):
                    super().__init__()
                    self.packets_sent = 0
                
                def sentPack(self, client, ch1_size, ch2_size):
                    """Called after each packet is sent"""
                    self.packets_sent += 1
                    print(f"Sent CH1: {ch1_size} bytes, CH2: {ch2_size} bytes")

    .. tab:: C++

        .. code-block:: cpp

            #include "dac_streaming.h"
            #include "callbacks.h"
            
            class MyCallback : public DACCallback {
            public:
                int packets_sent = 0;
                
                void sentPack(DACStreamClient* client, uint32_t ch1_size, uint32_t ch2_size) override {
                    packets_sent++;
                    std::cout << "Sent CH1: " << ch1_size 
                                << " bytes, CH2: " << ch2_size << " bytes" << std::endl;
                }
            };

|

Data Callback Method
---------------------

.. method:: sentPack(client, ch1_size, ch2_size)

    **Primary callback** - Called after a data packet is successfully sent to the DAC.
   
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param ch1_size: Number of samples sent to channel 1
    :type ch1_size: int
    :param ch2_size: Number of samples sent to channel 2
    :type ch2_size: int
    :rtype: None
   
    **Example:**
   
    .. code-block:: python
   
        def sentPack(self, client, ch1_size, ch2_size):
            self.total_samples += ch1_size + ch2_size
            print(f"Sent {self.total_samples:,} samples")

|

Connection Event Callbacks
---------------------------

.. method:: connected(client, host)
    :no-index:

    Called when successfully connected.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: disconnected(client, host)
    :no-index:

    Called when connection is lost.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: error(client, host, code)
    :no-index:

    Called when a connection error occurs.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :param code: Error code
    :type code: int
    :rtype: None

|

Server State Callbacks
-----------------------

.. method:: stopped(client, host)
    :no-index:

    Called when streaming stops normally.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: stoppedFileEnd(client, host)

    Called when streaming stops because the file ended.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: stoppedFileBroken(client, host)

    Called when streaming stops due to corrupted file.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: stoppedEmpty(client, host)

    Called when streaming stops because no data is available.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: stoppedMissingFile(client, host)

    Called when streaming stops because the file is not found.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: stoppedMemError(client, host)
    :no-index:

    Called when streaming stops due to memory error.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: stoppedMemModify(client, host)
    :no-index:

    Called when streaming stops due to memory modification during streaming.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

|

Configuration Connection Callbacks
------------------------------------

.. method:: configConnected(client, host)
    :no-index:

    Called when configuration connection is established.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

.. method:: configError(client, host, code)
    :no-index:

    Called when configuration connection error occurs.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :param code: Error code
    :type code: int
    :rtype: None

.. method:: configErrorTimeout(client, host)
    :no-index:

    Called when configuration connection times out.
    
    :param client: The DACStreamClient instance
    :type client: DACStreamClient
    :param host: Hostname or IP
    :type host: str
    :rtype: None

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
        channel3: ADCChannel     # Channel 3 data (4-Input only)
        channel4: ADCChannel     # Channel 4 data (4-Input only)

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

    def receivePack(self, client, pack):
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

For complete, production-ready examples with error handling and best practices, see :ref:`Streaming Examples <examples_streaming>`.

|

See Also
*********

* :ref:`Streaming Application <streaming_top>`
* :ref:`Quick Start Guide <streaming_quickstart>`
* :ref:`Configuration Reference <streaming_configuration_top>`
* :rp-github:`GitHub: Streaming Client Library <streaming-client>`



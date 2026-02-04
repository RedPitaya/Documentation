.. _streaming_technical_details:

#########################
Technical details
#########################

This section provides technical information about how the Streaming application works internally, including the data path, architecture, and implementation details.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

How does it work?
******************

The streaming application uses a carefully designed data transfer path to achieve high-speed, continuous data streaming with minimal data loss.

Data path
==========

.. TODO add picture of the data path

The streaming application uses the following data transfer path:

**Inputs → FPGA → DDR → Processor → Ethernet → Network → PC**

Each component in this path plays a specific role in the data streaming process:

* **Inputs:** Analog signals from BNC connectors
* **FPGA:** High-speed ADC data capture and DMA controller
* **DDR:** Ping-pong buffers for temporary data storage
* **Processor:** ARM CPU running the streaming server application
* **Ethernet:** Network interface (Gigabit Ethernet controller)
* **Network:** TCP/IP connection to client
* **PC:** Client application receiving streamed data

|

ADC streaming architecture
***************************

FPGA to DDR transfer
=====================

The FPGA streams data directly from the fast analog inputs to the DDR memory. This direct memory access ensures minimal latency and maximum throughput.

Key features:

* **Direct streaming:** No intermediate buffering in FPGA
* **Hardware-accelerated:** FPGA handles all ADC data capture
* **Continuous operation:** Data flows continuously from ADC to DDR

|

Ping-pong buffer mechanism
============================

Two ping-pong buffers are used to store the data in the DDR memory. This double-buffering technique ensures continuous data streaming without interruptions.

**Buffer operation:**

1. FPGA fills **Buffer A** while the processor reads from **Buffer B**
2. When **Buffer A** is full, FPGA raises a "buffer full" flag
3. FPGA checks if the processor has finished reading **Buffer B**
4. If reading is complete:
   
   * FPGA switches to filling **Buffer B**
   * Processor switches to reading **Buffer A**

5. If reading is NOT complete:
   
   * FPGA reports buffer overwrite error
   * Current data in **Buffer B** is discarded (data loss)
   * FPGA starts overwriting **Buffer B**

This mechanism allows for continuous data streaming, but requires the processor to keep up with the data rate to avoid data loss.

|

Processor to network transfer
===============================

The processor reads the data from the DDR memory and converts it into Ethernet packets, which are then sent over the network to the remote computer.

**Processing steps:**

1. **Read from DDR:** Processor retrieves data from the filled buffer
2. **Data conversion:** (Optional) Convert from RAW to VOLTS if requested
3. **Packet creation:** Package data into network packets of specified block size
4. **Network transmission:** Send packets via Ethernet to remote client

The data is streamed in chunks (packets) of a specified size, which can be configured in the :ref:`memory configuration settings <stream_memory_config>`.

|

DAC streaming architecture
***************************

The logic for DAC streaming is symmetrical to the ADC streaming, but the pipeline is reversed:

**PC → Network → PHY → Processor → DDR → FPGA → Outputs**

|

Network to processor transfer
===============================

1. **Packet reception:** Processor receives data packets from the network
2. **Data validation:** Verify packet integrity and sequence
3. **Buffer management:** Store data in DDR memory ping-pong buffers

|

Processor to FPGA transfer
============================

1. **DDR to FPGA:** Data is read from DDR memory by the FPGA
2. **DAC generation:** FPGA sends data to DAC at specified rate
3. **Buffer switching:** Ping-pong buffers ensure continuous generation

|

Performance considerations
===========================

Since the pipeline is reversed, the client that receives the data on the Red Pitaya isn't the large, high-speed buffer on the computer (as in ADC streaming), 
so the expected performance is lower than for ADC streaming.

Key differences:

* **Limited buffering:** Red Pitaya has less memory space than a computer
* **Upload limitations:** Network upload speeds may be lower than download speeds
* **Processing overhead:** Additional validation and buffering required

This is why the :ref:`DAC streaming limitations <stream_dac_limitations>` are more restrictive than ADC streaming limitations.

|

Memory management
******************

Deep Memory Mode (DMM) integration
====================================

The Streaming application shares the reserved memory region with the :ref:`Deep Memory Mode <deepMemoryMode>`. This shared memory architecture 
provides several benefits:

* **Flexible allocation:** Memory can be allocated dynamically between ADC, DAC, and GPIO streaming
* **Large buffers:** Up to 32 MB (default) or more of reserved memory
* **Efficient utilization:** Unused memory in one mode can be allocated to another

See :ref:`Memory Configuration <stream_memory_config>` for details on managing the reserved memory.

|

Block size and memory allocation
==================================

The block size determines the size of each data packet sent over the network, while memory allocation divides the reserved DDR 
memory between ADC, DAC, and GPIO streaming modes.

The `CMemoryManager` class handles memory allocation and reallocates the DDR memory buffers when settings are changed through 
the web interface or configuration file. These settings are communicated to client applications over the network when they connect.

For detailed guidance on choosing block sizes and allocating memory for your specific use case, see :ref:`Memory Configuration <stream_memory_config>`.

|

Data formats and conversion
*****************************

Data resolution and byte allocation
=====================================

The streaming application supports two resolution modes:

* **8-bit resolution:** 1 Byte per sample
* **16-bit resolution:** 2 Bytes per sample

.. note::

    Even for boards with 14-bit native ADC resolution (e.g., STEMlab 125-14), the 16-bit resolution mode uses 2 Bytes per 
    sample. The extra 2 bits are used for padding to align with standard data types.

|

ADC data formats
=================

**RAW format:**

* Native ADC counts (14-bit for STEMlab 125-14)
* Applies calibration automatically (OS 2.07-43 and newer)
* No conversion overhead
* Maximum performance
* Requires post-processing on the computer (converting to Volts)

**VOLTS format:**

* Converted to voltage values
* Applies calibration automatically
* Slightly reduced performance due to conversion overhead
* Ready-to-use data

|

File formats
=============

**BIN (Binary):**

* Fastest and most compact
* Minimal overhead
* Requires conversion for analysis (use :ref:`convert_tool <streaming_convert_tool>`)

**WAV (Wave Audio):**

* Standard audio format
* Compatible with audio software
* 4 GB maximum file size
* Some overhead for format compliance

**TDMS (Technical Data Management Streaming):**

* National Instruments format
* Self-documenting (includes metadata)
* Compatible with |DIAdem| and LabVIEW
* Some overhead for metadata

|

Source code and development
*****************************

The :rp-github:`Streaming application source code <RedPitaya/tree/master/apps-tools/streaming_manager>` is available 
on GitHub.

Architecture components:

* **FPGA logic:** Handles ADC/DAC data transfer and DDR memory management
* **Server application:** Runs on Red Pitaya, manages streaming process
* **Client applications:** Desktop and command-line tools for remote control
* **Web interface:** Browser-based control and monitoring

|

Next steps
***********

* Understand :ref:`Data Streaming Limitations <streaming_limits>` to see how these technical details affect performance
* Configure :ref:`Memory settings <stream_memory_config>` based on your understanding of the buffer architecture
* Try the :ref:`Examples <streaming_examples_top>` to see the system in action
* Review :ref:`Advanced Configuration <stream_advanced_config>` for fine-tuning

|

.. substitutions

.. |DIAdem| replace:: `DIAdem <https://www.ni.com/en-us/shop/data-acquisition-and-control/application-software-for-data-acquisition-and-control-category/what-is-diadem.html>`__

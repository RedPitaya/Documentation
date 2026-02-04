.. _multiboard_stream:

#########################
Multiboard streaming
#########################

Stream data from multiple Red Pitaya boards simultaneously to create multi-channel acquisition and generation systems.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Overview
*********

To stream data from multiple Red Pitaya boards simultaneously, start the streaming application on each board. This can be done either 
through the web interface or by loading the ``stream_app`` FPGA image and running the ``streaming-server`` command via SSH. Then either 
download the :ref:`desktop client application <stream_desktop_app>` or the :ref:`command line client <stream_command_client>` to your 
computer.

Both the desktop application and the command line client will detect all Red Pitaya boards on the same local network that are running 
the streaming application and allow for simultaneously starting and stopping the streaming process on all boards.

|

Key features
=============

* **Automatic board detection:** Clients automatically discover all boards on the local network
* **Synchronized control:** Start and stop streaming on all boards simultaneously
* **Multi-channel acquisition:** Combine channels from multiple boards (e.g., 2 boards = 4 channels, 4 boards = 8 channels)
* **Scalable system:** Add more boards to increase channel count
* **Independent configuration:** Each board can have different settings

|

Setup procedure
****************

Step 1: Prepare Red Pitaya boards
===================================

For each Red Pitaya board in your system:

1. **Connect to the same local network using a router or network switch**
   
   * All boards and the computer running the client must be connected to the same router or switch
   * Direct Ethernet connection between boards and computer will **not** work - the application requires a router or switch for automatic board detection
   * Each board will receive an IP address from the router's DHCP server

2. Ensure each board has a unique IP address
3. Load the streaming application:
   
   * Via web interface: Open the Streaming application
   * Via SSH: Run ``overlay.sh stream_app && streaming-server``

4. Verify the application is running (LED 2 on, LED 0 blinking)

|

Step 2: Configure each board
==============================

Configure the streaming parameters for each board individually:

* Set :ref:`ADC configuration <stream_adc_config>` (sampling rate, channels, resolution)
* Set :ref:`DAC configuration <stream_dac_config>` if needed
* Configure :ref:`Memory settings <stream_memory_config>` (block size, memory allocation)

.. note::

    All boards should use the same sampling rate and resolution for synchronized multi-channel acquisition.

|

Step 3: Install streaming client
==================================

Download and install either:

* :ref:`Desktop client application <stream_desktop_app>` - For GUI-based control
* :ref:`Command line client <stream_command_client>` - For scripting and automation

The client will automatically discover all boards running the streaming application on the local network.

|

Step 4: Start streaming
=========================

**Using desktop client:**

1. Open the desktop application
2. All detected boards will appear in the board list
3. Select the boards you want to stream from
4. Click "Start All" to begin streaming from all selected boards simultaneously

**Using command line client:**

The command line client can detect and stream from multiple boards automatically. See the :ref:`command line client documentation <stream_command_client>` 
for specific commands.

|

Hardware synchronization
*************************

For applications requiring precise timing synchronization between boards, Red Pitaya offers two hardware synchronization solutions that 
ensure phase-aligned data acquisition across multiple boards:

* **X-channel system** - Cost-effective daisy-chain synchronization using SATA or USB-C cables. Ideal for 2-3 boards at moderate to high sampling rates.
* **Click Shield synchronization** - Professional clock distribution using dedicated LVDS buffers. Recommended for larger systems (4+ boards) and maximum sampling rates.

Both systems enable synchronized multi-board acquisition for applications such as beamforming, phase-sensitive measurements, and multi-channel signal processing.

**For complete hardware synchronization setup, specifications, and comparison**, see the :ref:`Multiboard Synchronisation documentation <multiboard_sync>`.

.. note::

    Hardware synchronization is **not required** for basic multiboard streaming. The streaming clients can detect and control multiple 
    boards without hardware sync, but the data acquisition will not be phase-aligned between boards.

|

Network considerations
***********************

For optimal multiboard streaming performance:

Router configuration
=====================

1. **Use a dedicated network switch or router (required):**
   
   * **Essential for board detection** - Direct Ethernet connection will not work
   * All boards must be connected to the same router or switch for automatic discovery
   * Reduces network congestion
   * Provides stable connections
   * Enables full 1 Gbit speeds

2. **Assign static IP addresses:** Prevents IP conflicts and simplifies board identification

3. **Quality of Service (QoS):** If available, prioritize streaming traffic

|

Network bandwidth
==================

Consider the total network bandwidth when streaming from multiple boards:

.. math::

    \text{Total bandwidth} = N_{boards} \times f_S \times N_{channels} \times Bps

Where:

* :math:`N_{boards}` - Number of Red Pitaya boards
* :math:`f_S` - Sampling frequency
* :math:`N_{channels}` - Number of active channels per board
* :math:`Bps` - Bytes per sample (1 for 8-bit, 2 for 16-bit)

**Example:** 2 boards, 62.5 MS/s, 2 channels each, 16-bit:

.. math::

    \text{Total} = 2 \times 62,500,000 \times 2 \times 2 = 500,000,000 \text{ Bytes/s} = 500 \text{ MB/s}

This configuration exceeds both:

* **1 Gbit Ethernet capacity** (~125 MB/s) - Network bottleneck
* **Per-board streaming limits** (~62.5 MB/s per board) - See :ref:`Data Streaming Limitations <streaming_limits>`

In this case, you must reduce sampling rate or use fewer channels. For detailed per-board limitations and bandwidth calculations, 
see the :ref:`Data Streaming Limitations documentation <streaming_limits>`.

|

Performance optimization
*************************

To maximize multiboard streaming performance:

Reduce per-board data rate
============================

1. **Lower sampling rate:** Use decimation when possible
2. **Fewer channels:** Disable unused channels
3. **8-bit resolution:** Use when 16-bit precision isn't required
4. **RAW format:** Skip VOLTS conversion

|

Optimize network
=================

1. **Use Gigabit Ethernet:** Ensure all network components support 1 Gbit or higher
2. **Quality cables:** Use Cat 5e or Cat 6 cables
3. **Minimize hops:** Connect boards directly to the same switch
4. **Dedicated network:** Isolate streaming traffic from other network activity

|

Stagger streaming start
========================

If starting all boards simultaneously causes network congestion, consider staggering the start times by a few milliseconds. 
This can help distribute the initial burst of data packets.

|

Troubleshooting
****************

Boards not detected
====================

**Problem:** Client doesn't see all boards

**Solutions:**

1.  **Check network topology** - Boards must be connected through a router or switch. Direct Ethernet connection between computer and 
    boards will not work
2.  Verify all boards are on the same network subnet
3.  **Check firewall/antivirus settings** - Ensure Python, C++ and the streaming client are allowed network access (ports :ref:`18900-18903 <stream_port_numbers>`)
   
    If you see errors like:
    
    .. code-block:: shell-session

        Search: DONE
        Found boards:
        
    or:
    
    .. code-block:: shell-session

        Host not found
        The client did not connect
    
    Your firewall or antivirus may be blocking network communication. Whitelist Python, C++ and the streaming client application. The easiest way to resolve this is to run the program a few times, then 
    check the firewall/antivirus logs to see if it blocked the application, and create an exception for it (look for "Network access troubleshooting", "Resolve blocked communication", 
    etc. in your security software documentation).

4.  Ensure streaming application is running on all boards (LED 2 on, LED 0 blinking)
5.  Try pinging each board from your computer
6.  Restart the streaming application on affected boards

|

Synchronization issues
=======================

**Problem:** Data from boards is not synchronized

**Solutions:**

1. Check that all boards have the same sampling rate
2. Verify hardware synchronization is properly configured
3. Use :ref:`X-channel system <x-ch_streaming>` for precise synchronization
4. Check for clock drift in long acquisitions

|

Data loss
==========

**Problem:** Packet loss or missing data from some boards

**Solutions:**

1. Reduce total network bandwidth (lower sampling rate, fewer channels)
2. Check network cable quality and connections
3. Use a higher-quality network switch
4. Increase :ref:`block size <stream_memory_config>` for each board
5. Monitor network traffic to identify bottlenecks

|

Use cases
**********

4-channel acquisition (2 boards)
==================================

* **Setup:** 2× STEMlab 125-14 (2 channels each)
* **Result:** 4-channel synchronized acquisition
* **Example:** Quadrature signal analysis, 3-phase power monitoring

|

8-channel acquisition (4 boards)
==================================

* **Setup:** 4× STEMlab 125-14 (2 channels each)
* **Result:** 8-channel synchronized acquisition
* **Example:** Multi-sensor arrays, acoustic beamforming

|

16-channel acquisition (4× 4-input boards)
===========================================

* **Setup:** 4× STEMlab 125-14 4-Input (4 channels each)
* **Result:** 16-channel synchronized acquisition
* **Example:** Large sensor arrays, multi-channel FFT analysis

|

Next steps
***********

* Set up hardware synchronization with :ref:`X-channel system <x-ch_streaming>`
* Review :ref:`Data Streaming Limitations <streaming_limits>` for bandwidth calculations
* Try the :ref:`Desktop client application <stream_desktop_app>` for easy multiboard control
* Learn about :ref:`Command line client <stream_command_client>` for automated multiboard streaming

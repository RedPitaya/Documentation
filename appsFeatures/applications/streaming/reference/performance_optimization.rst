.. _streaming_performance_optimization:

#########################
Performance Optimization
#########################

This guide describes optimizations to achieve maximum streaming performance on Red Pitaya.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Overview
*********

For maximum streaming performance, especially at high sample rates or with multiple channels, system-level optimizations are essential. The most impactful optimization is disabling the web interface, which frees up significant CPU resources and network bandwidth.

.. note::

    These optimizations are particularly important when:
    
    * Streaming at sample rates above 10 MS/s
    * Using multiple channels simultaneously
    * Streaming over long durations
    * Running on lower-spec Red Pitaya models
    * Approaching the :ref:`62.5 MB/s network transfer limit <streaming_limits>`

|

Quick Start: Disable Web Interface
************************************

The fastest way to optimize for streaming:

.. code-block:: bash

    systemctl stop redpitaya_nginx
    systemctl disable redpitaya_nginx

This immediately stops the web interface and prevents it from starting on next boot.

To restore the web interface later:

.. code-block:: bash

    systemctl enable redpitaya_nginx
    systemctl start redpitaya_nginx

.. note::

    For complete service management instructions, including starting the SCPI server, automatic boot configuration, and troubleshooting, see the :ref:`Service Management Guide <service_management>`.

|

Additional Optimizations
*************************

Memory Allocation
==================

Red Pitaya boards have 512 MB of DDR3 RAM total. Ensure adequate :ref:`Deep Memory Mode (DMM) <deepMemoryMode>` allocation for streaming buffers while leaving sufficient memory for Linux operation:

* **Minimum:** 100 MB for basic streaming
* **Recommended:** 256 MB for high-rate streaming  
* **Maximum:** 400 MB (leaving at least 100 MB for Linux OS operation)

.. note::

    Always reserve at least 100 MB of RAM for the Linux operating system. Allocating too much memory to streaming can cause system instability or crashes.

Configure DMM allocation in the web interface before disabling it, or manually via SSH:

.. code-block:: bash

    nano /root/.config/redpitaya/apps/streaming/streaming_config.json

For more information on memory allocation and limits, see :ref:`Deep Memory Mode <deepMemoryMode>`.

|

Network Configuration
======================

For maximum throughput:

1.  **Use wired Ethernet** (not Wi-Fi) - Gigabit Ethernet required for high-speed streaming
2.  **Use router** - Direct connection to PC is currently not supported for streaming
3.  **Verify link speed** is 1 Gbps:

    .. code-block:: bash

        ethtool eth0

    Look for ``Speed: 1000Mb/s`` in the output. If the speed is lower (100 Mbps or 10 Mbps), check your Ethernet cable and switch/router capabilities.

|

System Load Reduction
======================

Minimize background processes:

1. Close unnecessary SSH connections (each consumes resources)
2. Stop other Red Pitaya applications
3. Disable the web interface when not needed (see Quick Start section above)

For more details, see :ref:`Service Management <service_management>`.

|

Sample Rate Limits
===================

Be aware of the :ref:`maximum achievable rates <streaming_limits>`:

* **Theoretical maximum:** 125 MB/s (1 Gbps Ethernet)
* **Practical network limit:** ~62.5 MB/s (achievable streaming rate)
* **Single channel:** Up to 31.25 MS/s (62.5 MB/s ÷ 2 bytes/sample)
* **Dual channel:** Up to 15.625 MS/s per channel (31.25 MS/s combined)

.. note::

    The absolute maximum streaming rate cannot be tested due to Red Pitaya's decimation limits. The practical limit is approximately 62.5 MB/s for sustained network streaming.
    Higher speeds may be possible with modifications to the FPGA firmware and custom software, but this is beyond the scope of typical usage (users have reporeted up to 100 MB/s with custom setups).

Going beyond these limits requires:

* Reducing active channels
* Using local SD card storage instead of network streaming
* Increasing decimation (reducing sample rate)

|

Workflow Recommendations
*************************

Development Phase
==================

During development and testing:

1. Keep web interface **enabled** for easy configuration
2. Use web interface to:

   * Configure streaming parameters
   * Set DMM memory allocation
   * Test basic functionality

3. Monitor performance and identify bottlenecks

|

Production Phase
=================

For production streaming or critical measurements:

1. **Configure all settings** via web interface
2. **Download configuration** using :ref:`rpsa_client <stream_command_client>`
3. **Disable web interface** for maximum performance
4. **Verify streaming stability** at target sample rates
5. **Use command-line client** for all streaming operations

See :ref:`CLI Examples <streaming_examples_top>` for command-line workflows.

|

Verification
*************

After optimization, verify performance:

Check Service Status
=====================

Confirm web interface is stopped:

.. code-block:: bash

    systemctl status redpitaya_nginx

Expected output:

.. code-block:: text

    ● redpitaya_nginx.service - Red Pitaya Nginx Web Server
         Active: inactive (dead)

|

Test Streaming Performance
============================

Run a test capture at your target sample rate:

.. tabs::

    .. tab:: Command Line Client

        .. code-block:: bash

            rpsa_client -h <red_pitaya_ip> -p TCP -f ./ -t wav

    .. tab:: Python API

        .. code-block:: python

            import streaming
            
            client = streaming.Streaming()
            # Configure and test streaming
            # Monitor for data loss warnings

Monitor system resources during streaming:

.. code-block:: bash

    top

Look for:

* CPU usage <80% during streaming
* No memory swapping
* Stable network throughput

|

Troubleshooting
****************

Data Loss Despite Optimization
================================

If experiencing data loss after optimization:

1.  **Reduce sample rate** - May be exceeding network bandwidth
2.  **Check decimation settings** - Ensure correct calculation:
   
    .. code-block:: text
   
        Sample rate = 125 MS/s ÷ decimation
        Network usage = sample_rate × channels × 2 bytes

3.  **Verify network quality** - Run ``ethtool eth0`` to check link
4.  **Increase DMM memory** - Provides more buffering
5.  **Check for packet loss:**

    .. code-block:: bash

        netstat -s | grep -i "packet.*loss"

|

Can't Re-enable Web Interface
===============================

If web interface won't restart:

1.  Check service status:

    .. code-block:: bash

        systemctl status redpitaya_nginx

2.  Look for errors in logs:

    .. code-block:: bash

        journalctl -u redpitaya_nginx -n 50

3.  Restart the service:

    .. code-block:: bash

        systemctl restart redpitaya_nginx

4.  Reboot if necessary:

    .. code-block:: bash

        reboot

For more troubleshooting, see :ref:`Service Management <service_management>`.

|

Performance Still Poor
=======================

If performance doesn't improve:

1. **Check hardware capabilities** - Older boards may have limitations
2. **Verify network infrastructure** - Test with different switch/cable
3. **Update Red Pitaya OS** - Newer versions have performance improvements
4. **Review configuration** - Incorrect settings can limit performance
5. **Check for thermal throttling** - Ensure adequate cooling

See :ref:`Streaming Limitations <streaming_limits>` for detailed performance boundaries.

|

Related Topics
***************

* :ref:`Service Management <service_management>` - Complete guide to managing Red Pitaya services
* :ref:`Streaming Performance Limits <streaming_limits>` - Theoretical performance boundaries
* :ref:`Deep Memory Mode <deepMemoryMode>` - Memory allocation for streaming
* :ref:`Command Line Client <stream_command_client>` - Streaming without web interface
* :ref:`Network Configuration <sw_network>` - Optimize network settings

|

Additional Resources
*********************

* :ref:`Streaming Application Documentation <streaming_top>`
* :ref:`CLI Examples <examples_streaming>` - Command-line streaming workflows
* :ref:`Configuration Guide <streaming_configuration_top>` - Detailed parameter reference
* :ref:`Technical Details <streaming_technical_details>` - How streaming works internally

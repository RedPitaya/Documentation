
.. _stream_util:

Streaming application utility
===============================

The streaming server can also be started through the command line.

.. code-block:: console

    root@rp-f0a235:~# streaming-server -h
    Usage:
            streaming-server [-b] [-f PATH] [-p PORT] [-s PORT] [-v]
            streaming-server [--background] [--file=PATH] [--port=PORT] [--search_port=PORT] [--verbose]

            --background          -b        Run service in background.
            --file=PATH           -f FILE   Path to configuration file.
                                            By default uses the config file /root/.config/redpitaya/apps/streaming/streaming_config.json.
            --verbose             -v        Displays information.

To start the server, follow these steps:

    #. Load the FPGA image for streaming.

        .. tabs::

            .. group-tab:: OS version 1.04 or older

                .. code-block:: console

                    redpitaya> cat /opt/redpitaya/fpga/fpga_streaming.bit > /dev/xdevcfg
                    redpitaya> /opt/redpitaya/sbin/mkoverlay.sh stream_app

            .. group-tab:: OS version 2.00

                .. code-block:: console

                    redpitaya> overlay.sh stream_app

        .. note::

            **SIGNALlab 250-12** uses **stream_app_250** FPGA image.

    #. Prepare a configuration file.

        .. note::

            In version 2.00, the configuration file has been moved to a new location: **/root/.config/redpitaya/apps/streaming/streaming_config.json**

    #. Launch the console application.

        .. code-block:: console

            root@rp-f07167:/# streaming-server -c /root/.streaming_config
            streaming-server started
            Lost rate: 0 / 763 (0 %)
            Lost rate: 0 / 766 (0 %)
            Lost rate: 0 / 766 (0 %)
            Lost rate: 0 / 766 (0 %)

The configuration for streaming is automatically created and saved in the file: **/root/.streaming_config** during the editing of the parameters in the web application.


.. note::

    Any changes to the web application will automatically modify the configuration file. If you want to save the configuration, then make a copy of the file.

.. note::

    The server can be started in the background. To do this, use the -b parameter. In this mode, the application can be used as a service at system startup. Service information from the application is saved in the syslog file (by default, the Syslog is not installed on Red Pitaya).

.. note::

    Streaming always creates two files:

        *   The first stores of streamed data
        *   The second stores the data transfer report


Data streaming
----------------

Once the streaming server is running, you can start streaming data from ADC and to DACs of the Red Pitaya board. For more information, please refer to the :ref:`Data stream control application <streaming_top>` documentation.


Source Code
------------

|streaming app|.

For streaming, two versions of clients are available - console and desktop for Linux and Windows operating systems. You can download them from the WEB streaming application on Red Pitaya itself. 
You can also build a version from source files under Mac OS using :ref:`QT Creator <comStreaming>`.

.. |streaming app| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools/streaming_manager" target="_blank">Data stream control application source code</a>.



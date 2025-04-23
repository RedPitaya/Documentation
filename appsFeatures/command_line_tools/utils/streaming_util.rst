
.. _stream_util:

.. TODO check if this is even available!!!

Streaming application
=====================

The server for streaming can be started not only using the web interface but also through the command line.

.. code-block:: console

    root@rp-f07167:/# streaming-server
    Missing parameters: Configuration file
    Usage: streaming-server
	    -b run service in the background
	    -c path to the config file

To start the server, you need to do 3 steps:

    #. Load the FPGA image for streaming

        .. tabs::

            .. group-tab:: OS version 1.04 or older

                .. code-block:: console

                    redpitaya> cat /opt/redpitaya/fpga/fpga_streaming.bit > /dev/xdevcfg
                    redpitaya> /opt/redpitaya/sbin/mkoverlay.sh stream_app

            .. group-tab:: OS version 2.00

                .. code-block:: console

                    redpitaya> overlay.sh stream_app


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

    The server can be started in the background. To do this, use the -b parameter. In this mode, the application can be used as a service at system startup. Service information from the application is saved in the syslog file (by default, the Syslog is not installed on RP).

.. note::

    Streaming always creates two files:

        *   The first stores of streamed data
        *   The second stores the data transfer report

.. note::

    Streaming app sources are available here: |streaming app|.
    For streaming, two versions of clients are available - console and desktop for Linux and Windows operating systems. You can download them from the WEB streaming application on Red Pitaya itself. You can also build a version from source files under Mac OS using :ref:`QT Creator <comStreaming>`.

.. |streaming app| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools/streaming_manager" target="_blank">streaming app</a>



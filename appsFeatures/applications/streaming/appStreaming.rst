.. _streaming_top:

#########
Streaming
#########

The Streaming application enables users to stream data from Red Pitaya to:

    * A file saved on the Red Pitaya SD card
    * A file saved on a remote computer via the ethernet protocol (UDP or TCP).

The user can set:

    * The sampling frequency (rate)
    * Input channel count (Channel 1, Channel 2, or Both (4 Channels for STEMlab 125-14 4-Input))
    * Input channel resolution (8 or 16 bits)
    * Input attenuation (HV/LV mode) (for 125-xx, a switch of the jumper is required)
    * Whether to use the calibration or not (for 125-xx, the filter is also calibrated)
    * RAW / Volts mode
    * The number of samples or unlimited sampling

Streamed data can be stored into:

    * Standard audio WAV file format
    * Technical Data Management Streaming (TDMS) file format
    * Fast and compact binary format (BIN). It can be converted to CSV format.

Max. streaming speeds are limited to:

    * 10 MB/s for streaming to an SD card (SD card class 10 is recommended for optimal streaming performance)
    * 20 MB/s for streaming over 1 Gbit network (A :ref:`direct connection <dir_cab_connect>` is recommended to achieve the best streaming performance)

.. note::

   The maximum continuous streaming speeds are limited to the total input data rate, not the network transfer rates. If the maximum data rate is exceeded, the data pipeline inside Red Pitaya starts to clog, which leads to unpredictable behaviour.
   Here are a few examples of maximum data rates:

      - One channel, 8-bits per sample: Max sampling frequency 20 MHz.
      - One channel, 16-bits per sample: Max sampling frequency 10 MHz.
      - Two channels, 8-bits per sample: Max sampling frequency per channel 10 MHz (assuming same frequencies for both channels)
      - Two channels, 16-bits per sample: Max sampling frequency per channel 5 MHz (assuming same frequencies for both channels)

   If acquiring a limited amount of samples in a short duration, it is possible to reach higher sampling frequencies (up to the sampling speed of fast analog inputs).

**Minumum streamed data size**

To increase the efficiency of the application, there is a minimum data size that can be sent through the network. This can have a big impact at high decimation values, as it takes a long time to fill a chunck. If the stream is stopped before a chunck is completed, the data is discarded and the saved file has a size of **0 b**.

Here are the minimum chunck limitations sorted by file type and units:


.. list-table:: Title
   :widths: 20 20 20
   :header-rows: 1

   * - File type \ Units
     - VOLTS
     - RAW
   * - WAV 
     - 128.043 kb
     - 64.043 kb
   * - TDMS
     - 128.133 kb
     - 64.133 kb
   * - BIN
     - 64.090 kb
     - 64.090 kb


.. note::

   We plan to expand the functionality by adding the generation to the Streaming application in the future. For now, it is possible for a user to implement it by themselves.



******************************************************
Getting started with the Red Pitaya streaming feature
******************************************************

#. Run the Streaming app from the Red Pitaya Web interface

    .. figure:: img/redpitaya_main_page.png
        :width: 60%
        :align: center

#. Stream locally to a file

    #. Set the app's properties & click RUN

        .. figure:: img/to_file_settings.png
            :width: 20%
            :align: center

            Example: streaming on ch1, 8-bit resolution, 5.208 MS/s into TDMS file format

    #. Press STOP to stop streaming

    #. Click Browse to open the file browser and download the streaming data file

        .. figure:: img/capture.png
           :width: 50%
           :align: center

    #. Open the file in a program that supports TDMS file reading, visualisation, and processing, such as |DIAdem|.

        .. figure:: img/diadem_tdms_file_viewer.png
           :width: 80%
           :align: center

#. Streaming to a remote computer

    #. Get the streaming client for your computer. Clients are located on the board itself and can be downloaded from there.

        .. figure:: img/download_client.png
            :width: 50%
            :align: center

    #. Set the app's properties & click RUN

        .. figure:: img/tcp_settings.png
            :width: 20%
            :align: center

            Example: streaming on ch1, 16-bit resolution 5 MS/s, TCP

    #. Run the streaming app on a remote computer (copy the IP address from the web interface and choose the required file format).

    .. tabs::

        .. group-tab:: WAV

            .. code-block:: console

                rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t wav

            .. figure:: img/tcp_client.png
                :width: 50%
                :align: center

            Data streaming can be stopped by pressing *Ctrl + C*.

            The created wav file can be read or viewed in |Audacity|:

            .. figure:: img/audacity.png
                :width: 80%
                :align: center

        .. group-tab:: TDMS

            .. code-block:: console

                rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t tdms

            .. figure:: img/tcp_client2.png
                :width: 50%
                :align: center

            Data streaming can be stopped by pressing *Ctrl + C*.

            The created tdms file can be read or viewed in |DIAdem|.

            .. figure:: img/diadem_tdms_file_viewer.png
                :width: 80%
                :align: center

        .. group-tab:: CSV

            .. code-block:: console

                rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t csv -s 100000 -v


            .. figure:: img/tcp_client3.png
                :width: 50%
                :align: center


            The application saves data from the board in BIN format. This is a binary format. If the application has finished writing data correctly and there is enough free space on the disk, the conversion to CSV format will be automatic.

            .. figure:: img/csv_list.png
                :width: 50%
                :align: center


            The created CSV file can be opened with any text editor or spreadsheet editor:

            .. figure:: img/csv_view.png
                :width: 80%
                :align: center


            .. note::

                The binary file can be converted using the *convert_tool* application.

                .. figure:: img/csv_list.png
                    :width: 50%
                    :align: center


                In this application, you can also see the structure of the received file and the state of the file.

                .. figure:: img/csv_state.png
                    :width: 50%
                    :align: center


.. |DIAdem| raw:: html

    <a href="https://www.ni.com/en-us/shop/data-acquisition-and-control/application-software-for-data-acquisition-and-control-category/what-is-diadem.html" target="_blank">DIAdem</a>


.. |Audacity| raw:: html

    <a href="https://www.audacityteam.org" target="_blank">Audacity</a>


******************************************************
Streaming application for the Desktop (Linux, Windows)
******************************************************

.. note::

   The streaming client application currently does not work on Windows 11. This issue will be fixed in the future.


You can also use the desktop version of the client for streaming.

    #. Download the client

        .. tabs::

            .. group-tab:: OS version 1.04 or older

                |Streaming Client|

            .. group-tab:: OS version 2.00

                Files with clients are in the streaming web application. You can download it from Red Pitaya itself.


    #. Unzip and run the client

        .. note::

            For Linux clients, after unpacking, the files (rpsa_client_qt.sh, bin/rpsa_client_qt) must be made executable.

            .. figure:: img/qt1.png
                    :width: 50%
                    :align: center

            For Windows clients, you need to grant access to the network.

            .. note::

               It is possible that an Antivirus program might block the desktop client. If you experience this issue, we recommend whitelisting the Streaming Client folder.

    #. The running application automatically detects boards on the network if streaming is running on them. The boards and the client must be on the same network.

        .. figure:: img/qt2.png
                :width: 50%
                :align: center

.. |Streaming Client| raw:: html

    <a href="https://downloads.redpitaya.com/downloads/Clients/streaming/desktop/" target="_blank">Desktop clients</a>

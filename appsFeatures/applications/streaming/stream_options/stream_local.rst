.. _streaming_local:

Local streaming (SD card)
==========================

When using the local streaming option, the data is streamed to a file on the Red Pitaya SD card. This option is useful for applications where the data needs to be stored locally for later analysis or processing.

.. tabs::

    .. group-tab:: OS version 2.00-15 or older

        #. Configure the stream propertie & click **Run**

            .. figure:: ../img/streaming_interface_104.png
                :width: 800
            
            Example: streaming on CH1, 8-bit resolution, 5.208 MS/s into TDMS file format

        #. Press **STOP** to stop streaming

        #. Click *Browse* to open the data file directory. Each data stream is split into three sections:

            * *DATA* - collected data stream,
            * *.log* - data log of the specific stream,
            * *.log.lost* - report on lost packets.

            Click on the selected file to download it from Red Pitaya to the computer.

            .. figure:: ../img/capture.png
                :width: 600
                :align: center

        #. Open the file in a program that supports the selected file format, visualisation, and processing, such as |DIAdem| for TDMS files, or |Audacity| for WAV.

            .. figure:: ../img/diadem_tdms_file_viewer.png
                :width: 800
                :align: center

    .. group-tab:: OS version 2.00-23 or newer

        #. **Configure the stream properties** & click **Start**

            .. figure:: ../img/streaming_interface.png
                :width: 1000
            
            Example: streaming on CH1 and CH2, 8-bit resolution, 100 ksps into WAV file format

        #. Press **Stop** to stop streaming

        #. Check the *Files on SD card* section for the data files. Each data file has three buttons:

            * *Log* - data log of the specific stream,
            * *Lost* - report on lost packets,
            * *Download* - collected data stream.

            Click on the selected file to download it from Red Pitaya to the computer.

            .. figure:: ../img/streaming_interface.png
                :width: 1000
                :align: center

        #. **Open the file in a program** that supports the selected file format, visualisation, and processing, such as |DIAdem| for TDMS files, or |Audacity| for WAV.

            .. figure:: ../img/diadem_tdms_file_viewer.png
                :width: 800
                :align: center


.. substitutions

.. |DIAdem| raw:: html

    <a href="https://www.ni.com/en-us/shop/data-acquisition-and-control/application-software-for-data-acquisition-and-control-category/what-is-diadem.html" target="_blank">DIAdem</a>


.. |Audacity| raw:: html

    <a href="https://www.audacityteam.org" target="_blank">Audacity</a>

.. |Streaming Client| raw:: html

    <a href="https://downloads.redpitaya.com/downloads/Clients/streaming/desktop/" target="_blank">here</a>

.. |br| raw:: html

    <br>


.. _stream_command_client:

Remote streaming (command line client)
=======================================

When using the remote streaming option, the data is streamed to a remote computer over the network. This option is useful for applications where the necessary data processing exceeds the capabilities of the Red Pitaya board and must therefore be done with more powerful tools on a remote computer.
Streaming through the command line client is the most effective way to transfer the data, allowing for the highest possible data transfer rate.

The command line client is available for Windows and Linux operating systems and supports :ref:`Multiboard streaming <multiboard_stream>`.

.. tabs::

    .. group-tab:: OS version 2.00-15 or older

        #.  **Download the streaming client** for your computer. Clients are located on the board itself and can be downloaded from there.

            .. figure:: ../img/download_client_104.png
                :width: 800
                :align: center
        
        #.  **Start the Streaming application** from the web interface or from the :ref:`Command line <stream_util>`.

        #.  **Configure the stream properties** & click **RUN**

            .. figure:: ../img/streaming_network_104.png
                :width: 300
                :align: center

            Example: streaming on IN1, 16-bit resolution 5 MS/s, TCP

        #.  **Run the streaming client** via *Command Line or Terminal* on a remote computer (copy the IP address from the web interface and choose the required file format).

            .. tabs::

                .. group-tab:: WAV

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t wav

                    .. figure:: ../img/tcp_client.png
                        :width: 600
                        :align: center

                    Data streaming can be stopped by pressing *Ctrl+C*.

                    The created wav file can be read or viewed in |Audacity| or another program that supports WAV file type:

                    .. figure:: ../img/audacity.png
                        :width: 600
                        :align: center

                .. group-tab:: TDMS

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t tdms

                    .. figure:: ../img/tcp_client2.png
                        :width: 600
                        :align: center

                    Data streaming can be stopped by pressing *Ctrl+C*.

                    The created tdms file can be read or viewed in |DIAdem| or another program that supports TDMS file type.

                    .. figure:: ../img/diadem_tdms_file_viewer.png
                        :width: 600
                        :align: center

                .. group-tab:: CSV

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t csv -s 100000 -v


                    .. figure:: ../img/tcp_client3.png
                        :width: 600
                        :align: center


                    The application saves data from the board in binary (BIN) format.

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    The binary file can be converted using the :ref:`convert_tool <streaming_convert_tool>` application.

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    The created CSV file can be opened with any text editor, spreadsheet editor, or any other application that supports the CSV file type:

                    .. figure:: ../img/csv_view.png
                        :width: 600
                        :align: center

                    .. note::

                        Using the :ref:`convert_tool <streaming_convert_tool>` you can also see the structure of the received file and the state of the file.

                        .. figure:: ../img/csv_state.png
                            :width: 600
                            :align: center

    .. group-tab:: OS version 2.00-23 or newer

        #.  **Download the "command line streaming client"** for your computer. Clients are located on the board itself and can be downloaded from there.

            .. figure:: ../img/streaming_cmd_clients_200_23.png
                :width: 1000
                :align: center

        #.  **Start the Streaming application** from the web interface or from the :ref:`Command line <stream_util>`.

        #.  **Configure the stream properties** & click **Start**

            .. figure:: ../img/streaming_adc_network_200_23.png
                :width: 1000
                :align: center

                Example: streaming on CH1 and CH2, 16-bit resolution, 100 ksps, TCP 

        #.  **Run the streaming client** via *Command Line or Terminal* on a remote computer (copy the IP address from the web interface and choose the required file format).

            .. tabs::

                .. group-tab:: WAV

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t wav

                    .. figure:: ../img/tcp_client.png
                        :width: 600
                        :align: center

                    Data streaming can be stopped by pressing *Ctrl+C*.

                    The created wav file can be read or viewed in |Audacity| or another program that supports WAV file type:

                    .. figure:: ../img/audacity.png
                        :width: 600
                        :align: center

                .. group-tab:: TDMS

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t tdms

                    .. figure:: ../img/tcp_client2.png
                        :width: 600
                        :align: center

                    Data streaming can be stopped by pressing *Ctrl+C*.

                    The created tdms file can be read or viewed in |DIAdem| or another program that supports TDMS file type.

                    .. figure:: ../img/diadem_tdms_file_viewer.png
                        :width: 600
                        :align: center

                .. group-tab:: CSV

                    .. code-block:: console

                        rpsa_client.exe -h 192.168.1.29 -p TCP -f ./ -t csv -s 100000 -v


                    .. figure:: ../img/tcp_client3.png
                        :width: 600
                        :align: center


                    The application saves data from the board in binary (BIN) format.

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    The binary file can be converted using the :ref:`convert_tool <streaming_convert_tool>` application.

                    .. figure:: ../img/csv_list.png
                        :width: 600
                        :align: center

                    The created CSV file can be opened with any text editor, spreadsheet editor, or any other application that supports the CSV file type:

                    .. figure:: ../img/csv_view.png
                        :width: 600
                        :align: center

                    .. note::

                        Using the :ref:`convert_tool <streaming_convert_tool>` application you can also see the structure of the received file and the state of the file.

                        .. figure:: ../img/csv_state.png
                            :width: 600
                            :align: center

.. note::

    For best performance, the web interface should be closed and the streaming application should be started from the terminal via the :ref:`Streaming utility <stream_util>`.

.. warning::

    **Firewall/Antivirus Configuration Required**
    
    The ``rpsa_client`` requires network access to detect and communicate with Red Pitaya boards. If you experience board detection or connection issues, ensure the client application is allowed network access in your firewall and antivirus software.
    
    Common symptoms of firewall/antivirus blocking:
    
    .. code-block:: shell-session

       # No boards detected in detect mode
       PS C:\RedPitaya\Streaming> .\rpsa_client.exe -d
       Search: DONE
       Found boards:

    .. code-block:: shell-session

       # Host not found error
       2026.01.30-14.25.08.342:  Host not found
       The client did not connect

    **Solution:** Whitelist the ``rpsa_client`` executable and allow it to access your local network in your firewall/antivirus settings. The easiest way to resolve this is to run the 
    program a few times, then check the firewall/antivirus logs to see if it blocked the application, and create an exception for it (look for "Network access troubleshooting", "Resolve 
    blocked communication", etc. in your security software documentation).

Instructions for the rpsa_client
-----------------------------------

1. **Detect mode**

    This mode allows you to determine the IP addresses that are in the local network in streaming mode. By default, the search takes about 5 seconds.

   	.. literalinclude:: ../include/detectMode.txt

    If no IP is specified, the client will automatically detect boards on the network and connect to a random board.

2. **Configuration mode**

    This mode allows you to get or set the streaming configuration on the boards.

   	.. literalinclude:: ../include/configMode.txt

    Variables can also be set individually:

    .. literalinclude:: ../include/configModeSingle.txt

3. **Remote control mode**
      
    This mode allows you to control streaming as a client.

   	.. literalinclude:: ../include/remoteControlMode.txt

4. **Streaming mode**

    This mode allows you to control streaming as a client, and also captures data in network streaming mode.

    .. literalinclude:: ../include/streamingMode.txt

5. **DAC streaming mode**

    This mode allows you to generate output data using a signal from a file.

    .. literalinclude:: ../include/dacStreamingMode.txt

6. **Configuration variables**

    Configuration file variables and their valid values.

    .. literalinclude:: ../include/configVariables.txt


.. note::

    If you run the console client with no parameters, the help menu will open, displaying a list of settings and their respective acceptable values.


The configuration file is located in the same folder as the client application. The file is named **config_<board_IP>.json** and contains the current settings of the streaming application. The file is created after the first configuration file request.


.. _streaming_convert_tool:

Convert tool
--------------

.. tabs::

    .. group-tab:: OS 2.07-43 or newer

        The convert tool allows you to convert the *.bin* file format into a *.csv*, *.tdms*, or *.wav* file.

        .. literalinclude:: ../include/convert_tool.txt

        To convert the binary file, first check the file information using:

        .. code-block:: bash

            .\convert_tool.exe .\<path_to_bin_file>\data_file.bin -i

        .. literalinclude:: ../include/convert_tool_info.txt

        The file information includes the number of segments into which the data is split. Using the convert tool, you can choose to convert only the specfied portion of the streamed file to the desired forma

        .. code-block:: bash

            .\convert_tool.exe .\<path_to_bin_file>\data_file.bin -s 1 -e 18 -f CSV

        The converted file will appear next to the original file.

        .. note::

            The file type (CSV, TDMS or WAV) must be capitalised.

.. substitutions

.. |DIAdem| replace:: `DIAdem <https://www.ni.com/en-us/shop/data-acquisition-and-control/application-software-for-data-acquisition-and-control-category/what-is-diadem.html>`__



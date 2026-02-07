.. _stream_redpitaya_linux:

Streaming data to Red Pitaya Linux
====================================

.. TODO add picture

Downloading and extracting the Red Pitaya **rpsa streaming client** onto the Red Pitaya board allows you to access the streamed data from Python code running directly on the Red Pitaya.

.. note::

    The functionality of the steaming client on the Red Pitaya is exactly the same as documented in the :ref:`rpsa_client documentation <streaming_rpsa_client>`. However, it is important to note that the performance 
    of the streaming process will be lower than on the computer as the data is saved to the SD card, which has :ref:`lower read/write speeds <streaming_limits>` compared to a computer's storage.


#.  **Download the "Red Pitaya command line streaming client"** from the **Data stream control** web interface. The client is located on the board itself and can be downloaded from there.

    .. figure:: ../img/streaming_pc_clients_redpitaya.png
        :width: 600
        :align: center

#.  **Unzip the downloaded file**.
#.  **Upload the client to the Red Pitaya** using the ``scp`` command in the terminal. The client should be uploaded to the ``/home/root/`` directory.
#.  **Establish an SSH connection** to the Red Pitaya using the ``ssh`` command in the terminal.

    .. code-block:: console

        ssh root@<Red_Pitaya_IP_address>

#.  **Make the client executable** by running the following command in the terminal:

    .. code-block:: console

        chmod +x rpsa_client convert_tool

#.  **Load the** ``stream_app`` **FPGA image**:

    .. code-block:: console

        redpitaya> overlay.sh stream_app

#.  **Get the configuration file and edit it** from the command line on the Red Pitaya.

    .. code-block:: console

        redpitaya> ./rpsa_client -c -g F -v
        redpitaya> nano ./configs/config_<Red_Pitaya_IP_address>.json

#.  **Update the configuration file** with the desired settings.

    .. code-block:: console

        redpitaya> ./rpsa_client -c -s F -f ./configs/config_<Red_Pitaya_IP_address>.json -v

#.  **Start the streaming server**.

    .. code-block:: console

        redpitaya> ./rpsa_client -s -f bin -m raw -l 1024 -v

For more information on the configuration parameters, please refer to the :ref:`rpsa_client documentation <streaming_rpsa_client>`.

|

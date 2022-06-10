.. _mch_streaming_top:

#######################
X-channel streaming
#######################

.. |br| raw:: html

    <br>

***********************
Overview:
***********************

X-Channel streaming is suitable for applications that require multiple acquisition or generation channels.

Red Pitaya X-Channel streaming software provides ability of streaming analog and digital signals to client PCs from 
several Red Pitaya devices simultaneously, with synchronized clock and trigger among all Red Pitayas in the system.

Streaming can be done in both directions. Users can stream acquired analog and digital signals from Red Pitaya devices 
to client computer or streame analog and digital signals from the client to Red Pitaya devices outputs. X-Channel 
streaming software also provides the ability to control streaming completely remotely from client PCs.

.. figure:: img/RPs_to_PC_conn.png
    :width: 80%

***********************
Setup preparation:
***********************

What do I need before I start?
Red Pitaya STEMlab 125-14 X-channel system that consists of multiple STEMlab 125-14 LN devices that are modified for 
clock and trigger synchronization, and also comes with SATA synchronization cables and software thatsupports X-Channel 
RF signal acquisition and generation.

.. figure:: img/Master_and_slaves.jpg
    :width: 80%

Notice that in Red Pitaya STEMlab 125-14 X-channel system inludes two types of devices:

    * one STEMlab 125-14 MASTER device (which is standard STEMlab 125-14 device)
    * one or more STEMlab 125-14 SLAVE devices that are marked with “S” sticker

In order to achieve synchronization, the MASTER device provides a clock and trigger over the SATA S1 connector that 
is then connected to the S2 of SLAVE 1 board. SLAVE1 then passes the clock forward to SLAVE 2, SLAVE2 to SLAVE 3, and 
so on (SLAVE N to SLAVE N+1). This way we can achieve synchronization of all boards in the system.

Important notice: MASTER and SLAVE boards do use different OS-es!

MASTER runs standard Red Pitaya device OS while SLAVE boards require a special OS that only supoorts X-channel streaming.

| `MASTER board OS <>`__
| `SLAVE board OS <>`__

Due to frequent OS updates, it is recommended to always use latest OS software.

***********************
Connecting together:
***********************

    #.  Connect all Red Pitayas to same network via ethernet cables (switch or router that is connected to Client PC).

        Improtant notice: Make sure that you network can provide enough throughput for all the data you are about to 
        stream. It is also recommnnede to use dedicated network only used only for X-channel system.


    #.  Connect SATA cables betwen master and slave devices.

        MASTER SATA S1 -> SLAVE 1 SATA S2

        SLAVE 1 SATA S1 -> SLAVE 2 SATA S2

        SLAVE 2 SATA S1 -> SLAVE 3 SATA S2

        ...


    #.  Connect power supply to the Red Pitaya board

.. figure:: img/Master_and_slaves_2.jpg
    :width: 80%

***********************
Download a X-channel streaming client to your computer
***********************

1.) Connect to MASTER board by typing URL on sticker to WEB browser and open streamin app

.. figure:: img/run_app.png
    :width: 80%

2.) Click CLIENTs button to get client app for Linux or Windows and download it to you client computer

.. figure:: img/download_client.png
    :width: 80%

***********************
Examples of use
***********************

Symultanious acquisiton of 6 input signals

In this example we will acquire data from all 3 RP units which gives as 6 RF input channels.

.. code-block:: shell-session

    MASTER IP=192.168.2.141, SLAVE1_IP=192.168.2.60 SLAVE2_IP=192.168.2.25


1.  Open streaming app on MASTER ana all SLAVE boards view WEB interface

Notice: streamin app can be also started via ssh by running /opt/redpitaya/bin/streaming-server.run.sh on RP

2.  Open streaming app on MASTER ana all SLAVE boards view WEB interface

3.  Set streaming paramters / confirguration

Configuration can be set over WEB interface UI which is then stored into /root/.streaming_config on RP.

In this example we will show how to set configuration remotely using alredy prepared `test.conf <https://downloads.redpitaya.com/doc/streaming/test.conf>`__ 
that will set all MASTERS and SLAVES to these settings.

.. figure:: img/settings.png
    :width: 80%

.. code-block:: shell-session

    rpsa_client.exe -c -h 192.168.2.141,192.168.2.60,192.168.2.25 -s F -f test.conf -v

    2022.06.02-15.20.21.173:  Connected: 192.168.2.141
    2022.06.02-15.20.21.176:  Connected: 192.168.2.25
    2022.06.02-15.20.21.178:  Connected: 192.168.2.60
    2022.06.02-15.20.21.278:  Send configuration to: 192.168.2.141
    2022.06.02-15.20.21.291:  Send configuration to: 192.168.2.25
    2022.06.02-15.20.21.291:  SET: 192.168.2.141 [OK]
    2022.06.02-15.20.21.303:  Send configuration to: 192.168.2.60
    2022.06.02-15.20.21.309:  Send configuration save command to: 192.168.2.141
    2022.06.02-15.20.21.324:  SET: 192.168.2.25 [OK]
    2022.06.02-15.20.21.332:  Send configuration save command to: 192.168.2.25
    2022.06.02-15.20.21.337:  SET: 192.168.2.60 [OK]
    2022.06.02-15.20.21.343:  Send configuration save command to: 192.168.2.60
    2022.06.02-15.20.21.350:  SAVE TO FILE: 192.168.2.141 [OK]
    2022.06.02-15.20.21.357:  SAVE TO FILE: 192.168.2.25 [OK]
    2022.06.02-15.20.21.363:  SAVE TO FILE: 192.168.2.60 [OK]

3.) Start X-channel streaming of 6 inputs

.. code-block:: shell-session

    --streaming --host MASTER IP, SLAVE1 IP, SLAVE2 IP, --format=wav --dir=NAME
    --limit=SAMPLES

    rpsa_client.exe -s -h 192.168.2.141,192.168.2.60,192.168.2.25 -f wav -d ./acq -l 10000000 -v

    2022.06.02-15.25.00.795:  Connected: 192.168.2.141
    2022.06.02-15.25.00.798:  Connected: 192.168.2.25
    2022.06.02-15.25.00.804:  Connected: 192.168.2.60
    2022.06.02-15.25.00.907:  Send stop command to master board 192.168.2.141
    2022.06.02-15.25.00.925:  Streaming stopped: 192.168.2.141 [OK]
    2022.06.02-15.25.01.32:  Send stop command to slave board 192.168.2.25
    2022.06.02-15.25.01.36:  Send stop command to slave board 192.168.2.60
    2022.06.02-15.25.01.37:  Streaming stopped: 192.168.2.25 [OK]
    2022.06.02-15.25.01.45:  Streaming stopped: 192.168.2.60 [OK]
    2022.06.02-15.25.01.156:  Send start command to slave board: 192.168.2.25
    2022.06.02-15.25.01.169:  Send start command to slave board: 192.168.2.60
    2022.06.02-15.25.01.286:  Streaming started: 192.168.2.25 TCP mode [OK]
    2022.06.02-15.25.01.307:  Streaming started: 192.168.2.60 TCP mode [OK]
    2022.06.02-15.25.01.407:  Send start command to master board: 192.168.2.141
    2022.06.02-15.25.01.542:  Streaming started: 192.168.2.141 TCP mode [OK]
    2022.06.02-15.25.01.639:  Send start ADC command to slave board: 192.168.2.25
    Run write to: ./1/data_file_192.168.2.25_2022-06-02_13-25-00.wav
    Run write to: ./1/data_file_192.168.2.60_2022-06-02_13-25-00.wav
    Run write to: ./1/data_file_192.168.2.141_2022-06-02_13-25-00.wav
    2022.06.02-15.25.01.659:  Send start ADC command to slave board: 192.168.2.60
    2022.06.02-15.25.01.660:  ADC is run: 192.168.2.25
    Available physical memory: 16260 Mb
    Used physical memory: 8130 Mb
    Available physical memory: 16260 Mb
    Used physical memory: 8130 Mb
    Available physical memory: 16260 Mb
    2022.06.02-15.25.01.741:  Connect 192.168.2.25
    2022.06.02-15.25.01.730:  ADC is run: 192.168.2.60
    Used physical memory: 8130 Mb
    2022.06.02-15.25.01.752:  Connect 192.168.2.141
    2022.06.02-15.25.01.764:  Connect 192.168.2.60
    2022.06.02-15.25.01.826:  Send start ADC command to master board: 192.168.2.141
    2022.06.02-15.25.01.834:  ADC is run: 192.168.2.141
    2022.06.02-15.25.04.402:  Error 192.168.2.25
    2022.06.02-15.25.04.408:  Error 192.168.2.141
    2022.06.02-15.25.04.410:  Error 192.168.2.60
    2022.06.02-15.25.04.415:  Send stop command to master board 192.168.2.141
    2022.06.02-15.25.04.420:  Streaming stopped: 192.168.2.141 [OK]
    2022.06.02-15.25.04.422:  Streaming stopped: 192.168.2.141 [OK]
    2022.06.02-15.25.04.526:  Send stop command to slave board 192.168.2.25
    2022.06.02-15.25.04.529:  Send stop command to slave board 192.168.2.60
    2022.06.02-15.25.04.530:  Streaming stopped: 192.168.2.25 [OK]
    2022.06.02-15.25.04.533:  Streaming stopped: 192.168.2.60 [OK]
    2022.06.02-15.25.04.536:  Streaming stopped: 192.168.2.25 [OK]
    2022.06.02-15.25.04.545:  Streaming stopped: 192.168.2.60 [OK]

    2022.06.02-15.25.04.635 Total time: 0:0:2.794
    =====================================================================================================================
    Host              | Bytes all         | Bandwidth         |    Samples CH1    |    Samples CH2    |      Lost        |
    +--------------------------------------------------------------------------------------------------------------------|
    192.168.2.141     | 38.188 Mb         | 13.668 MB/s       | 10010624          | 10010624          |                  |
                      +...................+...................+...................+...................+ 0                |
                      |Lost in UDP: 0                         |Lost in file: 0                        |                  |
                      +...................+...................+...................+...................+                  |
    192.168.2.25      | 38.188 Mb         | 13.668 MB/s       | 10010624          | 10010624          |                  |
                      +...................+...................+...................+...................+ 0                |
                      |Lost in UDP: 0                         |Lost in file: 0                        |                  |
                      +...................+...................+...................+...................+                  |
    192.168.2.60      | 38.188 Mb         | 13.668 MB/s       | 10010624          | 10010624          |                  |
                      +...................+...................+...................+...................+ 0                |
                      |Lost in UDP: 0                         |Lost in file: 0                        |                  |
                      +...................+...................+...................+...................+                  |
    =====================================================================================================================


4.) Drag .wav files from /acq to `Audacity <https://www.audacityteam.org>`__ to observe acquired data

.. figure:: img/audacity_2.png
    :width: 80%

In this example 1kHz sinewave signal was connected to all 6 inputs.

.. _com_line_tools:

##################
Command-line tools
##################

.. Note::
   
    Command-line utilities must not be used in parallel with a WEB application.
   
    For correct operation of the acquire tool, it is mandatory that the correct FPGA image is loaded. Please note that some applications can change the FPGA image loaded.
    To load the FPGA image, open a terminal on the Red Pitaya and execute the following command:
    
    .. code-block:: shell-session

       cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

.. contents::
    :local:
    :backlinks: none
    :depth: 1   
    

.. _sig_gen_util:

========================
Signal generator utility
========================

The Red Pitaya signal generator can be controlled through the |generate| command line utility.


.. |generate| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/tree/master/Test/generate" target="_blank">generate</a>


.. tabs::

   .. group-tab:: OS version 0.99 or older

      .. code-block:: shell-session
    
        redpitaya> generate
        generate version 0.90-299-1278

        Usage: generate   channel amplitude frequency <type>

            channel     Channel to generate signal on [1, 2].
            amplitude   Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
            frequency   Signal frequency in Hz [0.0 - 6.2e+07].
            type        Signal type [sine, sqr, tri].

   .. group-tab:: OS version 1.00

      .. code-block:: shell-session
    
        redpitaya> generate
        generate version 1.00-35-25a03ad-25a03ad

        Usage: generate channel amplitude frequency <gain> <type> <end frequency> <calib>

            channel         Channel to generate signal on [1, 2].
            amplitude       Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
            frequency       Signal frequency in Hz [0.00 - 1.2e+08].
            gain            Gain output value [x1, x5] (default value x1).
            type            Signal type [sine, sqr, tri, sweep].
            end frequency   Sweep-to frequency in Hz [0.00 - 1.2e+08].
            calib           Disable calibration [-c]. By default calibration enabled


Performance of the signal generator differs from one Red Pitaya model to another. For more information, please refer to the :ref:`Red Pitaya boards comparison <rp-board-comp>`.

.. _sig_acq_util:

==========================
Signal acquisition utility
==========================

The signal from Red Pitaya can be acquired through the |acquire| command line utility. It will return raw samples from the ADC buffer to standard output with no calibration compensation. Usage instructions:

.. |acquire| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/tree/master/Test/acquire" target="_blank">acquire</a>

.. tabs::

    .. group-tab:: OS version 0.99 or older

        .. code-block:: shell-session

            redpitaya> acquire 
            acquire version 0.90-299-1278

            Usage: acquire  size <dec>

                size     Number of samples to acquire [0 - 16384].
                dec      Decimation [1,8,64,1024,8192,65536] (default=1).
        

        Example (acquire 1024 samples with decimation 8):
    
        .. code-block:: shell-session
            
            redpitaya> acquire 1024 8
                -148     -81
                -143     -84
                -139     -88
                -134     -82
                ...

    .. group-tab:: OS version 1.00

        .. code-block:: shell-session

            redpitaya> acquire 

            Usage: acquire [OPTION]... SIZE <DEC>

                --equalization  -e    Use equalization filter in FPGA (default: disabled).
                --shaping       -s    Use shaping filter in FPGA (default: disabled).
                --atten1=a      -1 a  Use Channel 1 attenuator setting a [1, 20] (default: 1).
                --atten2=a      -2 a  Use Channel 2 attenuator setting a [1, 20] (default: 1).
                --dc=c          -d c  Enable DC mode. Setting c use for channels [1, 2, B(Both channels)].
                                        By default, AC mode is turned on.
                --tr_ch=c       -t c  Enable trigger by channel. Setting c use for channels [1P, 1N, 2P, 2N, EP (external channel), EN (external channel)].
                                        P - positive edge, N -negative edge. By default trigger no set
                --tr_level=c    -l c  Set trigger level (default: 0).
                --version       -v    Print version info.
                --help          -h    Print this message.
                --hex           -x    Print value in hex.
                --volt          -o    Print value in volt.
                --no_reg        -r    Disable load registers config for DAC and ADC.
                --calib         -c    Disable calibration parameters
                    SIZE                Number of samples to acquire [0 - 16384].
                    DEC                 Decimation [1,2,4,8,16,...] (default: 1). Valid values are from 1 to 65536


        
        Example (acquire 1024 samples with decimation 8, ch1 with at 1:20, results displayed in voltage):

        .. code-block:: shell-session

            redpitaya> acquire 1024 8 -1 20 -o
                -0.175803   0.000977
                0.021975    0.001099
                -0.075693   0.000977
                -0.190453   0.001099
                0.004883    0.001221
                -0.046392   0.001099
                -0.200220   0.000977
                -0.014650   0.001099
                -0.019534   0.001099
                -0.195336   0.000977
                -0.041509   0.001099
                ...
        
The performance of the acquisition tool differs from one Red Pitaya model to another.
Please see the :ref:`Red Pitaya boards comparison <rp-board-comp>` for more information.

.. _monitor_util:

===============
Monitor utility
===============

Accessing system registers
==========================

The system registers can be accessed through the |monitor| utility. Usage instructions:
 
.. |monitor| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/tree/master/Test/monitor" target="_blank">monitor</a>

 
.. code-block:: shell-session
    
    redpitaya>  monitor
    monitor version 1.03-0-ab43ad0-ab43ad0

    Usage:
        read addr: address
        write addr: address value
        read analog mixed signals: -ams
        set slow DAC: -sdac AO0 AO1 AO2 AO3 [V]
        
Example (system register reading):
 
.. code-block:: shell-session
    
    redpitaya> monitor -ams
    #ID	        Desc            Raw	            Val
    0           Temp(0C-85C)    0x00000b12	    75.670
    1	        AI0(0-3.5V)     0x00000008	    0.014
    2	        AI1(0-3.5V)     0x00000017	    0.039
    3	        AI2(0-3.5V)     0x00000008	    0.014
    4	        AI3(0-3.5V)     0x00000006	    0.010
    5	        AI4(5V0)        0x000004f9	    3.800
    6	        VCCPINT(1V0)    0x0000055e	    1.006
    7	        VCCPAUX(1V8)    0x00000995	    1.797
    8	        VCCBRAM(1V0)    0x00000561	    1.009
    9           VCCINT(1V0)     0x00000561	    1.009
    10          VCCAUX(1V8)     0x00000997	    1.798
    11          VCCDDR(1V5)     0x00000806	    1.504
    12          AO0(0-1.8V)     0x0000000f	    0.173
    13          AO1(0-1.8V)     0x0000004e	    0.900
    14          AO2(0-1.8V)     0x00000075	    1.350
    15          AO3(0-1.8V)     0x0000009c	    1.800

You can find a more detailed description of the above mentioned pins :ref:`here <E1>`.
The –ams switch provides access to analog mixed signals including Zynq SoC temperature, auxiliary analog input reading, power supply voltages, and configured auxiliary analog output settings. The auxiliary analog outputs can be set through the monitor utility using the –sadc switch:
 
.. code-block:: shell-session
    
   redpitaya> monitor -sdac 0.9 0.8 0.7 0.6

Accessing FPGA registers
========================

Red Pitaya signal processing is based on two computational engines: the FPGA and the dual-core processor, in order to effectively split the tasks. Most of the high data rate signal processing is implemented within the FPGA building blocks. These blocks can be configured parametrically through registers. The FPGA registers are documented in the 
:ref:`Red Pitaya HDL memory map <fpga_094>` document. The registers can be accessed using the described monitor utility.
For example, the following sequence of monitor commands checks, modifies, and verifies the acquisition decimation parameter (at address 0x40100014):
 
.. code-block:: shell-session
    
    redpitaya> monitor 0x40100014 
    0x00000001
    redpitaya> 
    redpitaya> monitor 0x40100014 0x8
    redpitaya> monitor 0x40100014 
    0x00000008
    redpitaya>
    
.. note::
    
    The CPU algorithms communicate with the FPGA through these registers. Therefore, the user should be aware of a possible interference with Red Pitaya applications which are reading or acting upon these same FPGA registers. For simple tasks, however, the monitor utility can be used by high-level scripts (Bash, Python, MATLAB, etc.) to communicate directly with the FPGA if necessary.


.. _bode_util:

=============
Bode Analyzer
=============

The Bode Analyzer can be used from the console.

.. note::
   
   The preparation of the environment can be found in this :ref:`chapter<bode_app>`.

.. code-block:: console

   root@rp-f01c35:~# bode
   Too few arguments!

   Bode analyzer version 1.04-133-feaf63b43, compiled at Fri Jan 22 04:25:24 2021

   Usage:	bode [channel] [amplitude] [dc bias] [averaging] [count/steps] [start freq] [stop freq] [scale type]
   or
      bode -calib

      channel            Channel to generate signal on [1 / 2].
      amplitude          Signal amplitude in V [0 - 1, which means max 2Vpp].
      dc bias            DC bias/offset/component in V [0 - 1].
                        Max sum of amplitude and DC bias is (0-1]V.
      averaging          Number of samples per one measurement [>1].
      count/steps        Number of measurements [>2].
      start freq         Lower frequency limit in Hz [3 - 62.5e6].
      stop freq          Upper frequency limit in Hz [3 - 62.5e6].
      scale type         0 - linear, 1 - logarithmic.
      -calib             Starts calibration mode. The calibration values will be saved in:/tmp/ba_calib.data
   Output:	frequency [Hz], phase [deg], amplitude [dB]



To run the bode, you need to do 2 steps:

    #. Load the FPGA image of streaming

        .. code-block:: console

            root@rp-f01c35:/# cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    #. Launch a console application.

        .. code-block:: console

            root@rp-f09508:~# bode 1 1 0 1 10 1000 100000 0
            1000.00     0.00025    0.34855
            12000.00    0.00090    0.34481
            23000.00    0.00209    0.32803
            34000.00    0.00859    0.33696
            45000.00    0.00335    0.26568
            56000.00    -0.00580   0.38830
            67000.00    -0.01751   0.36922
            78000.00    0.00635    0.32767
            89000.00    0.00521    0.38478
            100000.00   -0.00933   0.36610

.. _lcr_util:

=========
LCR meter
=========

The LCR meter can be used from the console.

.. note::
   
   The preparation of the environment can be found in this :ref:`chapter<lrc_app>`.

.. code-block:: console

   root@rp-f01c35:~# lcr
   Too few arguments!

   LCR meter version 0.00-0000, compiled at Fri Aug 14 03:29:10 2020

   Usage:	lcr [freq] [r_shunt] 

      freq               Signal frequency used for measurement [ 100 , 1000, 10000 , 100000 ] Hz.
      r_shunt            Shunt resistor value in Ohms [ 10, 100, 1000, 10000, 100000, 1000000 ]. If set to 0, Automatic ranging is used.
                        Automatic ranging demands Extenson module.

   Output:	Frequency [Hz], |Z| [Ohm], P [deg], Ls [H], Cs [F], Rs [Ohm], Lp [H], Cp [F], Rp [Ohm], Q, D, Xs [H], Gp [S], Bp [S], |Y| [S], -P [deg]


To run the LCR meter, you need to do 2 steps:

    #. Load the FPGA image of streaming

        .. code-block:: console

            root@rp-f01c35:/# cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    #. Launch a console application.

        .. code-block:: console

            root@rp-f01c35:~# lcr 100 100000 -v
            Frequency       100 Hz
            Z       5.424000 kOmh
            Phase   1.364216 deg
            L(s)    205.533997 mH
            C(s)    -12.324000 uF
            R(s)    5.422000 kOmh
            L(p)    0.000000 H
            C(p)    0.000000 F
            R(p)    5.425000 kOmh
            Q       0.023815
            D       -41.991112
            X_s     129.141129
            G_p     0.000184
            B_p     0.000000
            |Y|     0.000184
            -P_Y    -1.364216 deg

.. _stream_util:

=====================
Streaming application
=====================

The server for streaming can be started not only using the web interface but also through the command line.

.. code-block:: console

    root@rp-f07167:/# streaming-server 
    Missing parameters: Configuration file
    Usage: streaming-server
	    -b run service in background
	    -c path to config file

To start the server, you need to do 3 steps:

    #. Load the FPGA image of streaming

        .. code-block:: console

            root@rp-f07167:/# cat /opt/redpitaya/fpga/fpga_streaming.bit > /dev/xdevcfg
            root@rp-f07167:/# /opt/redpitaya/sbin/mkoverlay.sh stream_app


    #. Prepare a configuration file.

    #. Launch a console application.

        .. code-block:: console

            root@rp-f07167:/# streaming-server -c /root/.streaming_config 
            streaming-server started
            Lost rate: 0 / 763 (0 %)
            Lost rate: 0 / 766 (0 %)
            Lost rate: 0 / 766 (0 %)
            Lost rate: 0 / 766 (0 %)

The configuration for streaming is automatically created and saved in the file: **/root/.streaming_config** during editing of the parameters in the web application.


.. note::

    Any changes to the web application will automatically modify the configuration file. If you want to save the configuration, then make a copy of the file.

.. note::

    The server can be started in the background. To do this, use the -b parameter. In this mode, the application can be used as a service at system startup. Service information from the application is saved in the syslog file (by default, the syslog is not installed on RP).

.. note::

    Streaming always creates two files:
    
        * The first stores streamed data
        * The second stores the data transfer report
	
.. note::

    Streaming app sources are available here: |streaming app|.
.. |streaming ap| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools/streaming_manager" target="_blank">streaming ap</a>

.. _led_util:

==========================
LED enable/disable utility
==========================

The Red Pitaya LED indications can be enabled or disabled through the led_control command-line utility. Disabling LEDs is important for applications where the noise level needs to be reduced to its minimum.

Usage instructions:

.. code-block:: shell-session

    root@rp-f09508:~# led_control

    Usage: led_control -y[=State] | -r[=State] | -e [=State]

        -y    9 Yellow LED. Responsible for the status of reading the memory card.
        -r    Red LED, which is responsible for the heartbeat.
        -e    LEDs on ethernet connector.

    Optional parameter:
        State = [Off | On]  Turns LEDs on or off


To disable the LEDs:

.. code-block:: shell-session

    root@rp-f09508:~# led_control -y=Off -e=Off -r=Off

To enable the LEDs:

.. code-block:: shell-session

    root@rp-f09508:~# led_control -y=On -e=On -r=On

======================================================
Other useful information related to command-line tools
======================================================

.. toctree::
   :maxdepth: 6
   
   clt_other

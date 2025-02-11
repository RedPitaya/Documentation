.. _com_line_tools:

##################
Command-line tools
##################

.. Note::

    Command-line utilities must not be used in parallel with a WEB application.

    For correct operation of the acquire, generate, and monitor tools, the correct FPGA image must be loaded. Please note that some applications can change the FPGA image loaded.
    To load the FPGA image, open a terminal on the Red Pitaya and execute the following command:

    .. tabs::

        .. group-tab:: OS version 1.04 or older

            .. code-block:: shell-session

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

        .. group-tab:: OS version 2.00

            .. code-block:: shell-session

                redpitaya> overlay.sh v0.94

.. contents::
    :local:
    :backlinks: none
    :depth: 1


.. _sig_gen_util:

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

                channel     Channel to generate a signal on [1, 2].
                amplitude   Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
                frequency   Signal frequency in Hz [0.0 - 6.2e+07].
                type        Signal type [sine, sqr, tri].

    .. group-tab:: OS version 1.00-1.04

        .. code-block:: shell-session

            redpitaya> generate
            generate version 1.00-35-25a03ad-25a03ad

            Usage: generate channel amplitude frequency <gain> <type> <end frequency> <calib>

                channel         Channel to generate a signal on [1, 2].
                amplitude       Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
                frequency       Signal frequency in Hz [0.00 - 1.2e+08].
                gain            Gain output value [x1, x5] (default value x1).
                type            Signal type [sine, sqr, tri, sweep].
                end frequency   Sweep-to frequency in Hz [0.00 - 1.2e+08].
                calib           Disable calibration [-c]. By default calibration enabled

    .. group-tab:: OS version 2.00

        .. code-block:: shell-session

            root@rp-f0a235:~# generate
            generate version 2.00-0-6181e0263

            Usage: generate   channel amplitude frequency <type> <end frequency> <calib> <debug>

                    channel         Channel to generate signal on [1, 2].
                    amplitude       Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
                    frequency       Signal frequency in Hz [0 - 62500000].
                    type            Signal type [sine, sqr, tri, sweep, dc].
                    end frequency   Sweep-to frequency in Hz [0 - 62500000].
                    calib           Disable calibration [-c]. By default calibration enabled.
                    debug           Debug FPGA registers [-d].

            Setting the frequency to 0 will disable the generator completely.


The performance of the signal generator differs from one Red Pitaya model to another. For more information, please refer to the :ref:`Red Pitaya boards comparison <rp-board-comp>`.


.. _sig_acq_util:

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

    .. group-tab:: OS version 1.00-1.04

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


    .. group-tab:: OS version 2.00

        .. code-block:: shell-session

            redpitaya> acquire
            acquire Version: 2.00-15-5e06f6363

            Usage: acquire [OPTION]... SIZE <DEC>

            --equalization  -e    Use equalization filter in FPGA (default: disabled).
            --shaping       -s    Use shaping filter in FPGA (default: disabled).
            --gain1=g       -1 g  Use Channel 1 gain setting g [lv, hv] (default: lv).
            --gain2=g       -2 g  Use Channel 2 gain setting g [lv, hv] (default: lv).
            --tr_ch=c       -t c  Enable trigger by channel. Setting c use for channels [1P, 1N, 2P, 2N, EP (external channel), EN (external channel)].
                                    P - positive edge, N -negative edge. By default trigger no set
            --tr_level=c    -l c  Set trigger level (default: 0).
            --version       -v    Print version info.
            --help          -h    Print this message.
            --hex           -x    Print value in hex.
            --volt          -o    Print value in volt.
            --calib         -c    Disable calibration parameters
            --hk            -k    Reset houskeeping (Reset state for GPIO). Default: disabled
                SIZE                Number of samples to acquire [0 - 16384].
                DEC                 Decimation [1,2,4,8,16,...] (default: 1). Valid values are from 1 to 65536


        Example (acquire 1024 samples with decimation 8, ch1 with at 1:20, results displayed in voltage):

        .. code-block:: shell-session

            redpitaya> acquire 1024 8 -1 lv -o
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

Monitor utility
===============

Accessing system registers
---------------------------

The system registers can be accessed through the |monitor| utility. Usage instructions:

.. |monitor| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/tree/master/Test/monitor" target="_blank">monitor</a>

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: shell-session

            redpitaya>  monitor
            monitor version 1.03-0-ab43ad0-ab43ad0

            Usage:
                read addr: address
                write addr: address value
                read analog mixed signals: -ams
                set slow DAC: -sdac AO0 AO1 AO2 AO3 [V]

    .. group-tab:: OS version 2.00

        .. code-block:: shell-session

            monitor version 2.00-15-5e06f6363

            Usage:
                read addr: address
                write addr: address value
                read analog mixed signals: -ams
                set slow DAC: -sdac AO0 AO1 AO2 AO3 [V]
                Show current profile: -p
                Show all profiles: -pa
                Print fpga version: -f
                Print model name: -n
                Print model id: -i


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

You can find a more detailed description of the above-mentioned pins :ref:`here <E1>`.
The -ams switch provides access to analog mixed signals including Zynq SoC temperature, auxiliary analog input reading, power supply voltages, and configured auxiliary analog output settings. The auxiliary analog outputs can be set through the monitor utility using the -SADC switch:

.. code-block:: shell-session

   redpitaya> monitor -sdac 0.9 0.8 0.7 0.6


Accessing FPGA registers
-------------------------

Red Pitaya signal processing is based on two computational engines: the FPGA and the dual-core processor, to effectively split the tasks. Most of the high data rate signal processing is implemented within the FPGA building blocks. These blocks can be configured parametrically through registers. The FPGA registers are documented in the
:ref:`Red Pitaya HDL memory map <fpga_registers>` document (please make sure to reference the correct OS version). The registers can be accessed using the described monitor utility.
For example, the following sequence of monitor commands checks modifies, and verifies the acquisition decimation parameter (at address 0x40100014):

.. code-block:: shell-session

    redpitaya> monitor 0x40100014
    0x00000001
    redpitaya>
    redpitaya> monitor 0x40100014 0x8
    redpitaya> monitor 0x40100014
    0x00000008
    redpitaya>

.. note::

    The CPU algorithms communicate with the FPGA through these registers. Therefore, the user should be aware of possible interference with Red Pitaya applications which are reading or acting upon these same FPGA registers. For simple tasks, however, the monitor utility can be used by high-level scripts (Bash, Python, MATLAB, etc.) to communicate directly with the FPGA if necessary.


.. _bode_util:

Bode Analyzer
=============

The Bode Analyzer can be used from the console.

.. note::

   The preparation of the environment can be found in this :ref:`chapter<bode_app>`.

.. code-block:: console

   Bode analyzer version 2.06-447, compiled at Wed Jan 15 06:40:40 2025

    Usage:  bode [channel] [amplitude] [dc bias] [averaging] [count/steps] [start freq] [stop freq] [scale type] [probe]
    or
            bode -calib

            channel            Channel to generate signal on [1 / 2].
            amplitude          Signal amplitude in V [0 - 1, which means max 2 Vpp].
            dc bias            DC bias/offset/component in V [0 - 1].
                            Max sum of amplitude and DC bias is (0-1] V.
            averaging          Number of samples per one measurement [>1].
            count/steps        Number of measurements [>2].
            start freq         Lower frequency limit in Hz [3 - 62.5e6].
            stop freq          Upper frequency limit in Hz [3 - 62.5e6].
            scale type         0 - linear, 1 - logarithmic.
            probe              Probe value [1-1000].
            -calib             Starts calibration mode. The calibration values will be saved in:/tmp/ba_calib.data
    Output: frequency [Hz], phase [deg], amplitude [dB]


To run the bode, you need to do 2 steps:

    #. Load the FPGA image of streaming

        .. tabs::

            .. group-tab:: OS version 1.04 or older

                .. code-block:: shell-session

                    redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

            .. group-tab:: OS version 2.00

                .. code-block:: shell-session

                    redpitaya> overlay.sh v0.94


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

LCR meter
=========

The LCR meter can be used from the console.

.. note::

   The preparation of the environment can be found in this :ref:`chapter<lrc_app>`.

.. code-block:: console

    root@rp-f0a235:~# lcr
    Too few arguments!

    LCR meter version 2.00-0, compiled at Sat Mar 30 05:03:52 2024

    Usage:  lcr freq r_shunt [-v]

            freq               Signal frequency used for measurement Hz.
            r_shunt            Shunt resistor value in Ohms [ 10, 100, 1000, 10000, 100000, 1000000 ]. If set to 0, Automatic ranging is used.
            -v                 Verbose mode
                            Automatic ranging demands Extenson module.
                            
    Output: Frequency [Hz], |Z| [Ohm], P [deg], Ls [H], Cs [F], Rs [Ohm], Lp [H], Cp [F], Rp [Ohm], Q, D, Xs [H], Gp [S], Bp [S], |Y| [S], -P [deg]


To run the LCR meter, perform the following three steps:

    #. When not using the :ref:`LCR meter extension shield <lrc_app>`. Connect the shunt resistor and the DUT (device under test) according to the schematic below:
    
        .. figure:: img/600px-Impedance_analyzer_manaul_R_Shunt.png
            :width: 600px
    
    #. Load the default FPGA image
    
        .. tabs::
    
            .. group-tab:: OS version 1.04 or older
    
                .. code-block:: shell-session
    
                    redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg
    
            .. group-tab:: OS version 2.00
    
                .. code-block:: shell-session
    
                    redpitaya> overlay.sh v0.94
    
    #. Launch the console application.
    
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

                .. code-block:: shell-session

                    redpitaya> cat /opt/redpitaya/fpga/fpga_streaming.bit > /dev/xdevcfg
                    redpitaya> /opt/redpitaya/sbin/mkoverlay.sh stream_app

            .. group-tab:: OS version 2.00

                .. code-block:: shell-session

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


.. _led_util:

LED enable/disable utility
==========================

The Red Pitaya LED indications can be enabled or disabled through the led_control command-line utility. Disabling LEDs is important for applications where the noise level needs to be reduced to its minimum.

Use instructions:

.. code-block:: shell-session

    root@rp-f09508:~# led_control

    Usage: led_control -y[=State] | -r[=State] | -e [=State]

        -y    9 Yellow LED. Responsible for the status of reading the memory card.
        -r    Red LED, which is responsible for the heartbeat.
        -e    LEDs on the ethernet connector.

    Optional parameter:
        State = [Off | On]  Turns LEDs on or off


To disable the LEDs:

.. code-block:: shell-session

    root@rp-f09508:~# led_control -y=Off -e=Off -r=Off

To enable the LEDs:

.. code-block:: shell-session

    root@rp-f09508:~# led_control -y=On -e=On -r=On


.. _calib_util:

Calibration utility
======================

Red Pitaya calibration can be accessed and configured throgh the command-line utility.

Usage instructions:

.. code-block:: shell-session

    root@rp-f0a235:~# calib
    calib version 2.05-404-9a0244437

    Usage: calib [OPTION]...

    OPTIONS:
     -r    Read calibration values from eeprom (to stdout).
           The -n flag has no effect. The system automatically determines the type of stored data.

     -w    Write calibration values to eeprom (from stdin).
           Possible combination of flags: -wn, -wf, -wfn, -wmn, -wfmn
	
     -f    Use factory address space.
     -d    Reset calibration values in eeprom from factory zone. WARNING: Saves automatic to a new format

     -i    Reset calibration values in eeprom by default
           Possible combination of flags: -in , -inf.

     -o    Converts the calibration from the user zone to the old calibration format. For ecosystem version 0.98

     -v    Produce verbose output.
     -h    Print this info.
     -x    Print in hex.
     -u    Print stored calibration in unified format.

     -m    Modify specific parameter in universal calibration
     -n    Flag for working with the new calibration storage format.

To properly calibrate the Red Pitaya using the *calib* utility, we need to understand the calibration format we are working with. There are 4 different types of calibration:

- The first three are used in 1.04 OS versions and depend on the Red Pitaya board model:
	- STEMlab 125-14 and 125-10
	- STEMlab 125-14 4-Input
	- SIGNALlab 250-12

   You can find the specifics |calib specs|.

- The new universal calibration used in OS versions 2.00 and above.

.. |calib specs| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/rp-api/api-hw-calib/src/calib_structs.h" target="_blank">here</a>

The Calibration API allows you to work with all types of structures, but the old ones only work in backward compatibility mode (so there are no problems when moving to OS version 2.0).


New calibration storage format
--------------------------------

.. note::

    To convert from the old format to the new, load calibration values from a file in the new format or perform one of the calibration resets.

Reset calibration values to factory defaults:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -dn

Reset calibration values to defaults:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -in

Print current calibration values:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -rv

Print current calibration values in the unified format:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -u

Save to a file:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -r > calib.txt

Load from a file:

.. code-block:: shell-session

    root@rp-f0a235:~# cat calib.txt | calib -wn


Old calibration storage format
--------------------------------

Convert calibration values to the old format:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -o

Reset calibration values to factory defaults:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -d

Reset calibration values to defaults:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -i

Print current calibration values:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -rv

Save to a file:

.. code-block:: shell-session

    root@rp-f0a235:~# calib -r > calib.txt

Load from a file:

.. code-block:: shell-session

    root@rp-f0a235:~# cat calib.txt | calib -w


Other useful information related to command-line tools
======================================================

.. toctree::
   :maxdepth: 6

   clt_other

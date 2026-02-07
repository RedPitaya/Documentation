.. _generate_util:

Signal generator utility
========================

The Red Pitaya signal generator can be controlled using the generate command line utility.

.. tabs::

    .. group-tab:: OS version 2.00 and higher

        .. code-block:: console

            root@rp-f0a235:~# generate
            generate version 2.07-494-d5436699b

            Usage: generate   channel amplitude frequency <type> <end frequency> <calib> <debug>

                    channel         Channel to generate signal on [1, 2].
                    amplitude       Peak-to-peak signal amplitude in Vpp [0.0 - 4.0].
                    frequency       Signal frequency in Hz [0 - 62500000].
                    type            Signal type [sine, sqr, tri, sweep, noise, dc].
                    end frequency   Sweep-to frequency in Hz [0 - 62500000].
                    calib           Disable calibration [-c]. By default calibration enabled.
                    debug           Debug FPGA registers [-d].

            Setting the frequency to 0 will disable the generator completely.

    .. group-tab:: OS version 1.00-1.04

        .. code-block:: console

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

    .. group-tab:: OS version 0.99 or older

        .. code-block:: console

            redpitaya> generate
            generate version 0.90-299-1278

            Usage: generate   channel amplitude frequency <type>

                channel     Channel to generate a signal on [1, 2].
                amplitude   Peak-to-peak signal amplitude in Vpp [0.0 - 2.0].
                frequency   Signal frequency in Hz [0.0 - 6.2e+07].
                type        Signal type [sine, sqr, tri].


To run the signal generation utility, perform the following steps:

#.  Load the FPGA image.

    .. tabs::

        .. group-tab:: OS version 2.00

            .. code-block:: console

                redpitaya> overlay.sh v0.94

        .. group-tab:: OS version 1.04 or older

            .. code-block:: console

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg


#.  Start the console application.

    .. code-block:: console

        redpitaya> generate 1 1 1000 sine
        redpitaya> generate 2 1 1000 sqr
        redpitaya> generate 1 1 1000 tri
        redpitaya> generate 2 1 1000 sweep 10000
        redpitaya> generate 1 1 1000 noise
        redpitaya> generate 2 1 1000 dc

Signal generator performance varies between Red Pitaya models. For more information please refer to the Red Pitaya :ref:`Original Gen <rp-board-comp-orig_gen>` or :ref:`Gen 2 <rp-board-comp-gen2>` comparison table.

|

Source code
-----------

The Red Pitaya GitHub repository contains the :rp-github:`source code for the generate utility <RedPitaya/tree/master/Test/generate>`.

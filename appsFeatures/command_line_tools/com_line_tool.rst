.. _com_line_tools:

##################
Command-line tools
##################

.. note::

    Command-line utilities must not be used in parallel with a WEB application.

    For correct operation of the acquire, generate, and monitor tools, the correct FPGA image must be loaded. Please note that running an application will change or reset the loaded FPGA image.
    To load the FPGA image, open a terminal on the Red Pitaya and execute the following command:

    .. tabs::

        .. group-tab:: OS version 1.04 or older

            .. code-block:: console

                redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

        .. group-tab:: OS version 2.00

            .. code-block:: console

                redpitaya> overlay.sh v0.94

.. toctree::
    :maxdepth: 1
   
    utils/generate_util.rst
    utils/acquire_util.rst
    utils/spectrum_util.rst
    utils/bode_util.rst
    utils/lcr_util.rst
    utils/daisy_util.rst
    utils/streaming_util.rst
    utils/monitor_util.rst
    utils/led_util.rst
    utils/calib_util.rst
    utils/updater_util.rst
    utils/e3_i2c_util.rst
    utils/other_util.rst


.. _daisy_util:

Daisy utility
=============

The Red Pitaya Daisy utility is a command-line tool that enables the synchronization of multiple Red Pitaya devices over SATA daisy chain connectors. The utility can be used to enable trigger and clock synchronization, set the trigger source mode, and configure the external trigger debouncer for acquisition and generation.

.. code-block:: console

    redpitaya> daisy_tool

    Usage: daisy_tool -e[=State] | -o[=State] | -t[=Mode] | -c[=Mode] | -a[1.0] | -g[1.0] |-d

        -e    Enables trigger sync over SATA daisy chain connectors.
        -c    Enables clock sync over SATA daisy chain connectors.
        -o    Turns GPION_0 into trigger output for selected source - acquisition or generation.
        -t    Sets the trigger source mode. ADC/DAC.
        -e    Enables clock and trigger sync over SATA daisy chain connectors.
        -a    Sets ext. trigger debouncer for acquisition in μs (Value must be positive).
        -g    Sets ext. trigger debouncer for generation in μs (Value must be positive).
        -d    Register debug mode.

    Example:
            ./daisy_tool -e=On -o=On -t=DAC -a2.2

    Optional parameter:
            State = [Off | On]  Turns On or Off
            Mode = [ADC | DAC]  Set ADC or DAC mode

    Notice: Application does not reset register settings when enabling modes.
            If the flag does not have a parameter, it returns the value from the register.




Source code
------------

The Red Pitaya GitHub repository contains the `source code for the daisy_tool utility <https://github.com/RedPitaya/RedPitaya/tree/master/Test/daisy_tool>`_.

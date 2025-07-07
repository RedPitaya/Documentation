

.. _calib_util:

Calibration utility
======================

Red Pitaya calibration can be accessed and configured using the command line utility.

Usage instructions:

.. code-block:: console

    redpitaya> calib
    calib version 2.07-494-d5436699b

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
        -e    Disables the ADC filter completely in the FPGA when the calibration is reset to default.

To properly calibrate the Red Pitaya using the *calib* utility, we need to understand the calibration format we are working with. There are 4 different types of calibration:

* The first three are used in 1.04 OS versions and depend on the Red Pitaya board model.
    
    * STEMlab 125-14 and 125-10.
    * STEMlab 125-14 4-Input.
    * SIGNALlab 250-12
    
    You can find the `calibration specifications here <https://github.com/RedPitaya/RedPitaya/blob/master/rp-api/api-hw-calib/src/calib_structs.h>`_.

* The new universal calibration used in OS versions 2.00 and higher.

The calibration API allows you to work with all types of structures, but the old ones only work in backward compatibility mode (so there are no problems when moving to OS version 2.0).


New calibration storage format
--------------------------------

.. note::

    To convert from the old format to the new, load calibration values from a file in the new format or perform one of the calibration resets.

Reset calibration values to factory defaults:

.. code-block:: console

    root@rp-f0a235:~# calib -dn

Reset calibration values to defaults:

.. code-block:: console

    root@rp-f0a235:~# calib -in

Print current calibration values:

.. code-block:: console

    root@rp-f0a235:~# calib -rv

Print current calibration values in the unified format:

.. code-block:: console

    root@rp-f0a235:~# calib -u

Save to a file:

.. code-block:: console

    root@rp-f0a235:~# calib -r > calib.txt

Load from a file:

.. code-block:: console

    root@rp-f0a235:~# cat calib.txt | calib -wn



Old calibration storage format
--------------------------------

Convert calibration values to the old format:

.. code-block:: console

    root@rp-f0a235:~# calib -o

Reset calibration values to factory defaults:

.. code-block:: console

    root@rp-f0a235:~# calib -d

Reset calibration values to defaults:

.. code-block:: console

    root@rp-f0a235:~# calib -i

Print current calibration values:

.. code-block:: console

    root@rp-f0a235:~# calib -rv

Save to a file:

.. code-block:: console

    root@rp-f0a235:~# calib -r > calib.txt

Load from a file:

.. code-block:: console

    root@rp-f0a235:~# cat calib.txt | calib -w


Source code
------------

The Red Pitaya GitHub repository contains the `source code for the calib utility <https://github.com/RedPitaya/RedPitaya/tree/master/Test/calib>`_.

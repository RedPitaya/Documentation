

.. _calib_util:

Calibration utility
======================

Red Pitaya calibration can be accessed and configured using the command line utility.

Usage instructions:

.. code-block:: console

    calib version 2.07-641-82b32cf71

    Usage: calib [OPTION]...

    OPTIONS:
            -r    Read calibration values from eeprom (to stdout).
                The -n flag has no effect. The system automatically determines the type of stored data.
                Examples: -r, -rf, -rv, -rvf, -rx, -rfx, -rvx, -rvfx.

            -w    Write calibration values to eeprom (from stdin).
                Examples: -w, -wf, -wn, -wfn, -wmn, -wfmn

            -d    Reset calibration values in eeprom from factory zone. (-n flag converts to new version 6 format)
                Examples: -d, -dn, -dn5, -dn6

            -i    Reset calibration values in eeprom by default
                Examples: -i, -if, -in, -inf, -in5, -inf5, -in6, -inf6, -ie, -ief, -ine, -inef, -ine5, -inef5, -ine6, -inef6.

            -o    Converts the calibration from the user zone to the old calibration format. For ecosystem versions 0.98 to 1.04.

            -b    Binary input and output mode. Works only with the -r and -w flags.
                (Example: calib -rb > backup.bin, cat backup.bin | calib -wb).

    Modifiers for output:
            -v    Produce verbose output.
            -h    Print this info.
            -x    Print in hex.
            -u    Print stored calibration in unified format.

    Modifiers for input:
            -f    Use factory address space.
            -m    Modify specific parameter in universal calibration
            -n    Flag for working with the new calibration storage format.
            -e    Disables the ADC filter completely in the FPGA when the calibration is reset to default.
            -5    Using version 5 of the parameters.
            -6    Using version 6 of the parameters.


    Calibration parameter versions:
            1 - Old version for boards: 125-14
            2 - Old version for boards: 250-12
            3 - Old version for boards: 125-14 4 channel
            4 - Old version for boards: 122-16
            5 - Universal calibration parameters. Used in all board versions. Calibration occurs in the API.
            6 - Universal calibration parameters. Used in all board versions. Calibration occurs in the FPGA.

To properly calibrate the Red Pitaya using the *calib* utility, we need to understand the calibration format we are working with. There are 4 different types of calibration:

* The first four are used in 1.04 OS versions and depend on the Red Pitaya board model.
    
    1. STEMlab 125-14 and 125-10.
    2. SIGNALlab 250-12.
    3. STEMlab 125-14 4-Input.
    4. SDRlab 122-16.

    You can find the :rp-github:`calibration specifications here <RedPitaya/blob/master/rp-api/api-hw-calib/src/calib_structs.h>`.

* The new universal calibration used in OS versions 2.00 and higher:

    5. Universal calibration parameters Version 5 - calibration occurs in the API.
    6. Universal calibration parameters Version 6 - calibration occurs in the FPGA.

The calibration API allows you to work with all types of structures, but the old ones only work in backward compatibility mode (so there are no problems when moving to OS version 2.0).


New calibration storage format
--------------------------------

Here are a few examples of how to use the *calib* utility with the new universal calibration format.

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

The Red Pitaya GitHub repository contains the :rp-github:`source code for the calib utility <RedPitaya/tree/master/Test/calib>`.

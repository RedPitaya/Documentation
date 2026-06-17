

.. _calib_util:

Calibration utility
======================

Red Pitaya calibration can be accessed and configured using the command line utility.

Usage instructions:

.. code-block:: console

    root@rp-f0ef2d:~# calib
    calib version 3.00-781-bc5ed07cd

    Usage: calib [OPTION]...

    OPTIONS:
            -r               Read calibration values from eeprom (to stdout).
                            The -n flag has no effect. The system automatically determines the type of stored data.
                            Examples: -r, -rf, -rv, -rvf, -rx, -rfx, -rvx, -rvfx.

            -w               Write calibration values to eeprom (from stdin).
                            Examples: -w, -wf, -wn, -wfn, -wmn, -wfmn

            -d               Reset calibration values in eeprom from factory zone. (-n flag converts to new version 5 format)
                            Conversion to version 6 is impossible, as the calibration will not be valid. The only solution is recalibration and using the -in6 flag for version 6.
                            Examples: -d, -dn

            -i               Reset calibration values in eeprom by default
                            Examples: -i, -if, -in, -inf, -in5, -inf5, -in6, -inf6, -ie, -ief, -ine, -inef, -ine5, -inef5, -ine6, -inef6.

            -o               Converts the calibration from the user zone to the old calibration format. For ecosystem versions 0.98 to 1.04.

            -b               Binary input and output mode. Works only with the -r and -w flags.
                            (Example: calib -rb > backup.bin, cat backup.bin | calib -wb).
            -s [FILE_NAME]   Displays information about the backup.
                            (Example: calib -s backup.bin, calib -s -u backup.bin, calib -s -v backup.bin

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

* **Old calibration**. The first four are used in 1.04 OS versions and depend on the Red Pitaya board model.
    
    1. STEMlab 125-14 and 125-10.
    2. SIGNALlab 250-12.
    3. STEMlab 125-14 4-Input.
    4. SDRlab 122-16.

    You can find the :rp-github:`calibration specifications here <RedPitaya/blob/master/rp-api/api-hw-calib/src/calib_structs.h>`.

* **New universal calibration** used in OS versions 2.00 and higher:

    5. Universal calibration parameters Version 5 - calibration occurs in the API.
    6. Universal calibration parameters Version 6 - calibration occurs in the FPGA.

The calibration API allows you to work with all types of structures, but the old ones only work in backward compatibility mode (so there are no problems when moving to OS version 2.0).

|

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

|

Calibration backup and restore
--------------------------------

The calibration application allows users to create a backup of the calibration parameters (factory calibration
or user settings) and restore calibration from a previously saved backup file. This makes it easy to preserve
calibration data across OS updates or to transfer settings between boards.

The *calib* utility provides the same functionality on the command line using the **-b** (binary mode) and
**-s** (backup information) flags.

Create a binary backup of the current calibration:

.. code-block:: console

    root@rp-f0ef2d:~# calib -rb > STEMlab_125-14_Pro_v2.0_v15_20260529_160442.bin

Create a binary backup of the factory calibration:

.. code-block:: console

    root@rp-f0ef2d:~# calib -rbf > STEMlab_125-14_Pro_v2.0_v15_factory.bin

Restore calibration from a binary backup:

.. code-block:: console

    root@rp-f0ef2d:~# cat STEMlab_125-14_Pro_v2.0_v15_20260529_160442.bin | calib -wb

Display backup file information (header only):

.. code-block:: console

    root@rp-f0ef2d:~# calib -s STEMlab_125-14_Pro_v2.0_v15_20260529_160442.bin
    === Backup Information ===
    File:          STEMlab_125-14_Pro_v2.0_v15_20260529_160442.bin
    File size:     282 bytes
    MD5 hash:      e6998f7beced9f69bb89f3b2b0c888b3
    Hash valid:    YES

    Board model:   STEMlab 125-14 Pro v2.0 (21)
    MAC address:   00:26:32:F0:EF:2D
    Created:       2026-05-29 16:04:42
    Calib. size:   194 bytes

Display backup file information including the stored calibration values in unified format:

.. code-block:: console

    root@rp-f0ef2d:~# calib -s -u STEMlab_125-14_Pro_v2.0_v15_20260529_160442.bin
    === Backup Information ===
    File:          STEMlab_125-14_Pro_v2.0_v15_20260529_160442.bin
    File size:     282 bytes
    MD5 hash:      e6998f7beced9f69bb89f3b2b0c888b3
    Hash valid:    YES

    Board model:   STEMlab 125-14 Pro v2.0 (21)
    MAC address:   00:26:32:F0:EF:2D
    Created:       2026-05-29 16:04:42
    Calib. size:   194 bytes

    dataStructureId: 6
    wpCheck: 10
    time stamp: 829589168 (0x317286B0)
    time stamp: 2026-04-15 17:26:08
    commit hash: 277ab6cc5

    fast_adc_count_1_1: 2

            Channel 1:
                    * baseScale: 1.000000:
                    * calibValue: 3047611:
                    * offset: -26:
                    * gainCalc: 1.135324:

                    * AA: 0 (0x0):
                    * BB: 0 (0x0):
                    * PP: 0 (0x0):
                    * KK: 16777215 (0xFFFFFF):
            Channel 2:
                    * baseScale: 1.000000:
                    * calibValue: 3043525:
                    * offset: 2:
                    * gainCalc: 1.133802:

                    * AA: 0 (0x0):
                    * BB: 0 (0x0):
                    * PP: 0 (0x0):
                    * KK: 16777215 (0xFFFFFF):
    fast_adc_count_1_20: 2

            Channel 1:
                    * baseScale: 1.000000:
                    * calibValue: 3913292:
                    * offset: -26:
                    * gainCalc: 1.457815:

                    * AA: 0 (0x0):
                    * BB: 0 (0x0):
                    * PP: 0 (0x0):
                    * KK: 16777215 (0xFFFFFF):
            Channel 2:
                    * baseScale: 1.000000:
                    * calibValue: 3916741:
                    * offset: 2:
                    * gainCalc: 1.459100:

                    * AA: 0 (0x0):
                    * BB: 0 (0x0):
                    * PP: 0 (0x0):
                    * KK: 16777215 (0xFFFFFF):
    fast_adc_count_1_1_ac: 0

    fast_adc_count_1_20_ac: 0

    fast_dac_count_x1 : 2

            Channel 1 :
                    * baseScale: 1.000000:
                    * calibValue: 2326677:
                    * offset: 286:
                    * gainCalc: 0.866755:

            Channel 2 :
                    * baseScale: 1.000000:
                    * calibValue: 2302037:
                    * offset: 312:
                    * gainCalc: 0.857576:

    fast_dac_count_x5 : 0

.. note::

    The ``-s`` flag can also be combined with ``-v`` to display the raw calibration values (``calib -s -v backup.bin``).

|

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

|

Source code
------------

The Red Pitaya GitHub repository contains the :rp-github:`source code for the calib utility <RedPitaya/tree/master/Test/calib>`.

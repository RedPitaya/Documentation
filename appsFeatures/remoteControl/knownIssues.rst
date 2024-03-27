.. _commands_known_issues:

Known SCPI & API issues and changes by OS version
###################################################

Here, you can find a list of known SCPI & API command issues and changes listed by the Red Pitaya OS release version.

If you are facing an issue with one of the examples, a command is not working, or your code does not work, we suggest checking the known issues list from the latest OS release to your current OS version for any applicable changes.

How to find all available SCPI commands per OS version?
========================================================

Use the ``SYSTem:Help?`` (IN DEV) SCPI command, which lists all available SCPI commands.

You can also find all SCPI commands that the board will accept depending on the Red Pitaya OS version here:

- Latest Beta OS: |all_os_scpi_commands|

For all other Red Pitaya OS versions, go to the link above and change the branch version to:

- 2.00-35 - Branch 2024.2 *(file ends in .cpp)*
- 2.00-30 - Branch 2024.1 *(file ends in .cpp)*
- 2.00-23 - Branch 2023.3 *(file ends in .cpp)*
- 2.00-18 - Branch 2023.2 *(file ends in .c)*
- 2.00-15 - Branch 2023.1 - |all_os_scpi_commands_2.00-15| *(file ends in .c)*
- 1.04-28 - Branch 2022.2 *(file ends in .c)*
- 1.04-18 - Branch 2022.1 *(file ends in .c)*

.. image:: img/All_os_scpi_commands.png
   :width: 500


.. |all_os_scpi_commands| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/scpi-server/src/scpi-commands.cpp" target="_blank">Red Pitaya GitHub - scpi-server/src/scpi-commands.cpp</a>

.. |all_os_scpi_commands_2.00-15| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/Release-2023.1/scpi-server/src/scpi-commands.c" target="_blank">Red Pitaya GitHub 2023.1- scpi-server/src/scpi-commands.c</a>

IN DEV
=======

New Commands
-------------

- Added DMA commands to return data as Numpy array (``rp_AcqAxiGetDataRawNP(channel, pos, np_buffer)``, ``rp_AcqAxiGetDataVNP``). Check */opt/redpitaya/lib/python/rp.py* on NB 261 or later for more options.
- Added acquisition commands to return data as Numpy array (``rp_AcqGetDataPosRaw``, ``rp_AcqGetDataPosVNP``, ``rp_AcqGetLatestDataRawNP``, etc.). Check */opt/redpitaya/lib/python/rp.py* on NB 261 or later for more options.

2.00-35
===========

Issues
----------

- Changed ``ACQ:TRig:EXT:LEV`` to ``TRig:EXT:LEV`` (generation and acquisition share this command).
- Changed ``DAISY:TRIG_O:ENable`` to ``DAISY:TRig:Out:ENable``
- Changed ``DAISY:TRIG_O:SOUR`` to ``DAISY:TRig:Out:SOUR``
- For all SCPI commands ``TRIG`` was renamed to ``TRig`` (does not affect the backwards compatibility).
- Renamed ``SOUR:TRIG:EXT:DEBouncerUs`` to ``SOUR:TRig:EXT:DEBouncer[:US]`` (the previous command was misleading - will not be reverted).
- Renamed ``ACQ:TRIG:EXT:DEBouncerUs`` to ``ACQ:TRig:EXT:DEBouncer[:US]`` (the previous command was misleading - will not be reverted).
- ``ACQ:SOUR<n>:DATA:Start:End?`` to ``ACQ:SOUR<n>:DATA:STArt:End?`` (backwards compatible with 2.00-23 and older)
- ``ACQ:SOUR<n>:DATA:Start:N?`` to ``ACQ:SOUR<n>:DATA:STArt:N?`` (backwards compatible with 2.00-23 and older)
- ``ACQ:SOUR<n>:DATA:Last:N?`` to ``ACQ:SOUR<n>:DATA:LATest:N?`` (backwards compatible with 2.00-23 and older)

- ``SOUR<n>:TRIG:SOUR?`` - stuck in an infinite loop, does not return
- ``SOUR<n>:FUNC?``, ``SOUR<n>:VOLT?``, ``SOUR<n>:Sweep:STAT?``, ``SOUR<n>:Sweep:FREQ:START?`` - all return in format "None\r\n<actual value>\r\n" (the next command ending in ``?`` will return in multiple lines, creating unexpected returns)

New Commands
--------------

- ``SYSTem:Help?`` - displays all available SCPI commands
- **SWEEP** SCPI commands (Sweep Mode Extended)
- **PLL** SCPI commands (SIGNALlab 250-12 only)
- ``SOUR<n>:FREQ:FIX:Direct <frequency>`` - change the frequency setting directly in the FPGA
- ``SOUR<n>:LOAD <load_mode>`` - Select output load (50 Ohm or INF) for SIGNALlab 250-12


2.00-30
===========

Issues
---------

.. note::

    **TEMPORARY CHANGE OF COMMANDS**
    We realized this command renaming is not backwards compatible, so we will be reverting it to the old version with the next OS update.

- For all SCPI commands ``TRIG`` was renamed to ``TRig``(does not affect the backwards compatibility).

Reanmed commands:

- ``ACQ:SOUR<n>:DATA:STA:END?`` to ``ACQ:SOUR<n>:DATA:Start:End?``
- ``ACQ:SOUR<n>:DATA:STA:N?`` to ``ACQ:SOUR<n>:DATA:Start:N?``
- ``ACQ:SOUR<n>:DATA:OLD:N?`` to ``ACQ:SOUR<n>:DATA:Old:N?`` (does not affect the backwards compatibility).
- ``ACQ:SOUR<n>:DATA:LAT:N?`` to ``ACQ:SOUR<n>:DATA:Last:N?``
- ``ACQ:DATA:UNITS`` to ``ACQ:DATA:Units`` (does not affect the backwards compatibility)
- ``SOUR:TRIG:EXT:DEBouncerUs`` to ``SOUR:TRig:EXT:DEBouncer[:US]`` (the previous command was misleading - will not be reverted).
- ``ACQ:TRIG:EXT:DEBouncerUs`` to ``ACQ:TRig:EXT:DEBouncer[:US]`` (the previous command was misleading - will not be reverted).
- ``UART:READ#`` to ``UART:READ#?``
- ``I2C:Smbus:Read#`` to ``I2C:Smbus:Read#?``
- ``I2C:Smbus:Read#:Word`` to ``I2C:Smbus:Read#:Word?``
- ``I2C:Smbus:Read#:Buffer#`` to ``I2C:Smbus:Read#:Buffer#?``
- ``I2C:IOctl:Read:Buffer#`` to ``I2C:IOctl:Read:Buffer#?``

New commands
--------------

- ``ACQ:DEC:F <decimation_ext>`` command - better version of ``ACQ:DEC`` command.
- **CAN** commands


2.00-23
===========

Issues
---------

- Deep Memory Acquisition does not work on SDRlab 122-16 (upgrade to 2.00-30).


New commands
--------------

- Python API buffer commands:

    - ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)``
    - ``rp_deleteBuffer(<buffer>)``
                       


2.00-18
===========

Issues
---------

- Deep Memory Acquisition only works on STEMlab 125-14.
- Removed ``DAISY:ENable <state>``- functionality replaced by ``DAISY:SYNC:TRIG <state>`` and ``DAISY:SYNC:CLK <state>`` commands.



New commands
--------------

- **Board Control Commands**:

    - ``SYSTem:TIME <hours>,<minutes>,<seconds>``
    - ``SYSTem:TIME?``
    - ``SYSTem:DATE <year>,<month>,<day>``
    - ``SYSTem:DATE?``
    - ``SYSTem:BRD:ID?``
    - ``SYSTem:BRD:Name?``

- **Daisy chain clocks and triggers**:

    - ``DAISY:SYNC:TRIG <state>``
    - ``DAISY:SYNC:TRIG?``
    - ``DAISY:SYNC:CLK <state>``
    - ``DAISY:SYNC:CLK?``

- **Rise and Fall time API commands**:

    - ``rp_GenRiseTime(rp_channel_t channel, float time)``
    - ``rp_GenGetRiseTime(rp_channel_t channel, float *time)``
    - ``rp_GenFallTime(rp_channel_t channel, float time)``
    - ``rp_GenGetFallTime(rp_channel_t channel, float *time)``

- **Last and Init Burst value**:

    - ``SOUR<n>:BURS:LASTValue <amplitude>`` 
    - ``SOUR<n>:BURS:LASTValue?``
    - ``SOUR<n>:INITValue <amplitude>``
    - ``SOUR<n>:INITValue?``

- **Sweep API commands**
- **Deep Memory Acquisition (DMA)** commands
- ``SPI:SETtings:CSMODE <cs_mode>`` command - sets the default value of the CS pin upon boot



2.00-15
===========

Issues
---------

- ``SPI:SET:CSMODE`` and ``SPI:SET:CSMODE?`` do not work.
- X-channel SCPI control buggy.


New commands
--------------

- **Daisy chain clocks and triggers**:

    - ``DAISY:ENable <state>``
    - ``DAISY:ENable?``
    - ``DAISY:TRIG_O:ENable <state>``
    - ``DAISY:TRIG_O:ENable?``
    - ``DAISY:TRIG_O:SOUR <mode>``
    - ``DAISY:TRIG_O:SOUR?``

- **External Debounce Filter commands**:

    - ``SOUR:TRig:EXT:DEBouncerUs <utime>``
    - ``SOUR:TRig:EXT:DEBouncerUs?``
    - ``ACQ:TRig:EXT:DEBouncerUs <value>``
    - ``ACQ:TRig:EXT:DEBouncerUs?``

- ``ACQ:TRig:FILL?`` command - checks whether the acquisition buffer is full.



1.04-28
===========

Issues
---------

- ``SOUR:TRIG:INT`` command does not work. It is supposed to synchronously trigger both outputs, but is ignored. Use ``SOUR<n>:TRIG:INT`` to trigger individual outputs seperately.
- ``ACQ:SOUR<n>:STA:END?`` does not work.


New commands
--------------

- NA


1.04-18 and older
==================

This is as far as our testing archives reach, for older versions, we suggest consulting the |Changelog| for specific Board versions (The link leads to STEMlab 125-14 changelog).

.. |Changelog| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/CHANGELOG.md" target="_blank">Red Pitaya GitHub CHANGELOG</a>







.. _commands_known_issues:

Known SCPI & API issues and changes by OS version
###################################################

Here, you can find a list of known SCPI & API command issues and changes listed by the Red Pitaya OS release version.

If you are facing an issue with one of the examples, a command is not working, or your code does not work, we suggest checking the known issues list from the latest OS release to your current OS version for any applicable changes.


2.00-30
===========

Issues
---------

- For all SCPI commands ``TRIG`` was renamed to ``TRig``.
- Renamed ``ACQ:SOUR<n>:DATA:STA:END?`` to ``ACQ:SOUR<n>:DATA:Start:End?``
- Renamed ``ACQ:SOUR<n>:DATA:STA:N?`` to ``ACQ:SOUR<n>:DATA:Start:N?``
- Renamed ``ACQ:SOUR<n>:DATA:OLD:N?`` to ``ACQ:SOUR<n>:DATA:Old:N?``
- Renamed ``ACQ:SOUR<n>:DATA:LAT:N?`` to ``ACQ:SOUR<n>:DATA:Last:N?``
- Renamed ``ACQ:DATA:UNITS`` to ``ACQ:DATA:Units``


New commands
--------------

- Added ``ACQ:DEC:F <decimation_ext>`` command. This is a better version of ``ACQ:DEC`` command
- Added ``ACQ:DEC:F?``
- Added **CAN** commands


2.00-23
===========

Issues
---------

- Deep Memory Acquisition does not work on SDRlab 122-16 (upgrade to 2.00-30).


New commands
--------------

- Added Python API buffer commands:

    - ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)``
    - ``rp_deleteBuffer(<buffer>)``
                       


2.00-18
===========

Issues
---------

- Deep Memory Acquisition only works on STEMlab 125-14.


New commands
--------------

- Added **Board Control Commands**:

    - ``SYSTem:TIME <hours>,<minutes>,<seconds>``
    - ``SYSTem:TIME?``
    - ``SYSTem:DATE <year>,<month>,<day>``
    - ``SYSTem:DATE?``
    - ``SYSTem:BRD:ID?``
    - ``SYSTem:BRD:Name?``

- Added **Daisy chain clocks and triggers**:

    - ``DAISY:SYNC:TRIG <state>``
    - ``DAISY:SYNC:TRIG?``
    - ``DAISY:SYNC:CLK <state>``
    - ``DAISY:SYNC:CLK?``
   
- Removed **Daisy chain clocks and triggers**:

    - ``DAISY:ENable <state>``
    - ``DAISY:ENable?``

- Added **Rise and Fall time API commands**:

    - ``rp_GenRiseTime(rp_channel_t channel, float time)``
    - ``rp_GenGetRiseTime(rp_channel_t channel, float *time)``
    - ``rp_GenFallTime(rp_channel_t channel, float time)``
    - ``rp_GenGetFallTime(rp_channel_t channel, float *time)``

- Added **Last and Init Burst value**:

    - ``SOUR<n>:BURS:LASTValue <amplitude>`` 
    - ``SOUR<n>:BURS:LASTValue?``
    - ``SOUR<n>:INITValue <amplitude>``
    - ``SOUR<n>:INITValue?``

- Added **Sweep API commands**
- Added **Deep Memory Acquisition** commands
- Added ``SPI:SETtings:CSMODE <cs_mode>`` and ``SPI:SETtings:CSMODE?`` commands



2.00-15
===========

Issues
---------

- ``SPI:SET:CSMODE`` and ``SPI:SET:CSMODE?`` do not work.
- X-channel SCPI control buggy.


New commands
--------------

- Added **Daisy chain clocks and triggers**:

    - ``DAISY:ENable <state>``
    - ``DAISY:ENable?``
    - ``DAISY:TRIG_O:ENable <state>``
    - ``DAISY:TRIG_O:ENable?``
    - ``DAISY:TRIG_O:SOUR <mode>``
    - ``DAISY:TRIG_O:SOUR?``

- Added **External Debounce Filter commands**:

    - ``SOUR:TRig:EXT:DEBouncer[:US] <utime>``
    - ``SOUR:TRig:EXT:DEBouncer[:US]?``
    - ``ACQ:TRig:EXT:DEBouncer:[US] <value>``
    - ``ACQ:TRig:EXT:DEBouncer[:US]?``

- Added ``ACQ:TRig:FILL?`` command, which checks whether the acquisition buffer is full.



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

This is as far as our testing archives reach, for older versions, we suggest consulting the GitHub Changelog for specific Board versions:



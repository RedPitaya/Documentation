.. _playback&record:

#######################################
RF Signal Recording and Playback script
#######################################

RF Signal Record and Playback script captures RF signal pulses from Red Pitaya's analog inputs (IN1/IN2) and immediately replays them on the corresponding outputs (OUT1/OUT2). It leverages **Deep Memory Acquisition** for high-speed recording and **Deep Memory Generation** for precise playback.

Once installed, the application is set to start automatically at boot. The application is controlled through the configuration file located in the */opt/redpitaya/bin/* directory.


How it works
============

1. **Acquisition**: Each channel independently monitors its input for trigger conditions
2. **Recording**: When triggered, captures the signal using DMA for minimal latency
3. **Generation**: Immediately replays the captured signal with configurable burst patterns
4. **Loop**: Continues indefinitely until stopped


Features
========

- **Dual Channel Processing**: Independent IN1→OUT1 and IN2→OUT2 signal recording/playback
- **Deep Memory Mode**: High-speed acquisition using Red Pitaya's DMA capabilities
- **Split Trigger Mode**: Isolated trigger handling for each channel
- **Configurable Parameters**: Flexible trigger levels, buffer sizes, and burst patterns
- **Real-time Operation**: Low-latency signal processing with threaded architecture
- **Auto-start**: Automatic startup on Red Pitaya boot


.. note::

    This application is not meant to be used in parallel with the Red Pitaya WEB interface. As most processing resources is taken by the *Record and Play* application, the Web interface is severly slowed down. 

Requirements
============

**Hardware**

- Any Red Pitaya device
- Properly terminated analog inputs/outputs (50 Ω impedance matching)

**Software**

- Red Pitaya Linux 2.07 or higher
- Nightly Build 637 or higher

.. warning::

    This application consumes significant system resources and **cannot run simultaneously** with the Red Pitaya Web Interface. The web interface will be severely slowed down or unresponsive.

Please make sure that Red Pitaya inputs and outputs are properly terminated (matched impedance). Failure to do so may lead to undefined behaviour of the *Record and Playback* application due to the 
`ringing <https://incompliancemag.com/circuit-theory-model-of-ringing-on-a-transmission-line/>`_ on the `transmission line <https://en.wikipedia.org/wiki/Transmission_line>`_.
Red Pitaya fast analog inputs have input impedance of 1 MΩ. The fast analog outputs have output impedace of 50 Ω.


Installation
============

Quick Start
-----------

1. Connect to your Red Pitaya via SSH
2. Clone the repository: ``git clone https://github.com/RedPitaya/rec_and_play.git``
3. Enable running scripts: ``chmod +x ./rec_and_play/setup.sh``
4. Run setup: ``cd rec_and_play && ./setup.sh``
5. Reboot Red Pitaya
6. Done! Application starts automatically on boot


Option A: Automatic Setup (Recommended)
----------------------------------------

1.  Establish :ref:`SSH <ssh>` connection with your Red Pitaya
#.  Download the :rp-github:`rec_and_play GitHub Repository <rec_and_play/tree/master>` to the Red Pitaya.

    .. code-block:: bash

        cd /root
        git clone https://github.com/RedPitaya/rec_and_play.git rap
        cd rap

#.  Make sure all the scripts are executable and run the setup.

    .. code-block:: bash

        chmod +x setup.sh
        ./setup.sh

#.  Reboot Red Pitaya.

    .. code-block:: bash

        reboot


Option B: Manual Setup
-----------------------

1.  Establish :ref:`SSH <ssh>` connection with your Red Pitaya
#.  Download the :rp-github:`rec_and_play GitHub Repository <rec_and_play/tree/master>` to the Red Pitaya.

    .. code-block:: bash

        cd /root
        git clone https://github.com/RedPitaya/rec_and_play.git rap

    Alternatively, download the repository to your computer and copy the code to the Red Pitaya through the SCP command:

    .. code-block:: bash

        scp -r /<path-to-downloaded-repository>/rec_and_play root@rp-xxxxxx.local:/root

#.  Move to the *Record and Play* directory on the Red Pitaya.

    .. code-block:: bash

        cd /root/rap

#.  Enter read-write mode and copy the scripts into the */opt/redpitaya/bin* folder.

    .. code-block:: bash

        rw
        cp -f ./main.py /opt/redpitaya/bin/
        cp -f ./config.ini /opt/redpitaya/bin/

#.  (Optional) Add to startup by editing ``/opt/redpitaya/sbin/startup.sh`` and adding:

    .. code-block:: bash

        export PYTHONPATH=/opt/redpitaya/lib/python/:$PYTHONPATH
        /opt/redpitaya/bin/main.py

#.  Reboot Red Pitaya.

    .. code-block:: bash

        reboot


Configuration
=============

The *Record and Play* application uses the configuration file (config.ini) located in */opt/redpitaya/bin/* directory.
Each channel (ADC/DAC) is configured independently.

**Acquisition Settings (ADC)**

.. list-table::
    :widths: 20 40 20 10
    :header-rows: 1

    * - Parameter
      - Description
      - Values
      - Unit
    * - trigger_level
      - Voltage threshold for triggering
      - -1.0 to 1.0
      - Volts
    * - trigger_mode
      - Trigger condition
      - CH1_PE, CH1_NE, CH2_PE, CH2_NE
      - \-
    * - buffer_time
      - Recording duration
      - 1-30
      - µs


**Generation Settings (DAC)**

.. list-table::
    :widths: 20 40 30 10
    :header-rows: 1

    * - Parameter
      - Description
      - Values
      - Unit
    * - signal_source
      - Input channel to record
      - IN1, IN2
      - \-
    * - count_burst
      - Cycles per burst (NCYC)
      - ≥1
      - count
    * - repetition
      - Number of bursts (NOR)
      - ≥1
      - count
    * - repetition_delay
      - Delay between bursts
      - ≥ (buffer_time × count_burst + 1)
      - µs


Sample Configuration
--------------------

To change the settings, either edit the *config.ini* file in */opt/redpitaya/bin/* directly, or edit the *config.ini* file in the *record and play* directory and run the *setup.sh* script again.
For the changes to take effect, *main.py* must be restarted (either by rebooting the Red Pitaya or by killing the process and starting it again).

Example of "config.ini":

.. code-block:: ini

    [ADC1]
    ; IN1 Trigger Level in volts
    trigger_level=0.1
    ; Trigger source (Values: CH1_PE, CH1_NE)
    trigger_mode=CH1_PE
    ; Record signal Buffer size in microseconds (min 1 µs)
    buffer_time=20

    [ADC2]
    ; IN2 Trigger Level in volts
    trigger_level=0.1
    ; Trigger source (Values: CH2_PE, CH2_NE)
    trigger_mode=CH2_PE
    ; Record signal Buffer size in microseconds (min 1 µs)
    buffer_time=20

    [DAC1]
    ; OUT1 Gen signal from source (IN1, IN2). Which input to use for recording data.
    signal_source=IN1
    ; Number of signal repetitions without delays (NCYC - number of cycles/periods in a single burst).
    count_burst=1
    ; Number of repetitions with delay (NOR - Number of Repetitions/Bursts). Each repetition includes `count_burst` (NCYC) recordings without delay.
    repetition=3
    ; Delay between repetitions.
    ; If there is a "repetition" number of repetitions, then the minimum allowed delay must be no less than:
    ; buffer_time * count_burst + 1 µS
    ; Otherwise the signal may break. If there are no repetitions, the value is ignored
    ; For example. buffer_time = 20, count_burst=2. repetition_delay = 20 * 2 + 1 = 41 µS
    repetition_delay=50

    [DAC2]
    ; OUT2 Gen signal from source (IN1, IN2). Which input to use for recording data.
    signal_source=IN2
    ; Number of signal repetitions without delays (NCYC - number of cycles/periods in a single burst).
    count_burst=1
    ; Number of repetitions with delay (NOR - Number of Repetitions/Bursts). Each repetition includes `count_burst` (NCYC) recordings without delay.
    repetition=3
    ; Delay between repetitions.
    ; If there is a "repetition" number of repetitions, then the minimum allowed delay must be no less than:
    ; buffer_time * count_burst + 1 µS
    ; Otherwise the signal may break. If there are no repetitions, the value is ignored
    ; For example. buffer_time = 20, count_burst=2. repetition_delay = 20 * 2 + 1 = 41 µS
    repetition_delay=50

.. note::

    - **Cross-channel routing** is supported but untested (e.g., IN1 to OUT2)
    - **Buffer sizes** should be identical for both channels
    - **Timing constraints** must be respected to avoid signal corruption


Usage
=====

Starting the Application
-------------------------

The application starts automatically on boot if installed with ``setup.sh``. For manual start:

.. code-block:: bash

    cd /opt/redpitaya/bin
    python3 main.py


Monitoring Operation
--------------------

- Check system logs for status messages
- Use ``top`` or ``htop`` to monitor CPU usage
- Application runs indefinitely until interrupted


Stopping the Application
-------------------------

**Temporary Stop** - To stop the application until the next boot:

- Press ``Ctrl+C`` in the terminal, or
- Kill the process in ``top`` (write ``k`` and the PID of the process)

    .. figure:: img/Rec_and_play_top_kill.png
        :alt: Top command and kill PID
        :align: center
        :width: 800px

**Permanent Disable** - First stop the application, then:

1. Remove it from the ``startup.sh`` script located in */opt/redpitaya/sbin* directory (you may have to enter ``rw`` mode). 
2. Either delete or comment the following lines of code:

    .. code-block:: bash

        # Here you can specify commands for autorun at system startup
        export PYTHONPATH=/opt/redpitaya/lib/python/:$PYTHONPATH
        /opt/redpitaya/bin/main.py

3. You can also remove the *main.py* and *config.ini* from */opt/redpitaya/bin*.


Troubleshooting
===============

Common Issues
-------------

**Error setting split trigger**

- Ensure you're using compatible Red Pitaya OS version
- Check system resources aren't exhausted

**Invalid buffer size**

- Verify ``buffer_time`` is between 1-30 µs
- Ensure integer values in configuration

**No signal output**

- Check input signal levels and trigger settings
- Verify proper impedance termination (50 Ω)
- Confirm ``signal_source`` configuration

**System slowdown**

- This is normal - application uses most system resources
- Web interface will be unresponsive during operation

Performance Tuning
------------------

- Reduce ``buffer_time`` for faster response
- Adjust ``repetition_delay`` to prevent signal overlap
- Monitor CPU usage with ``top`` command
- Reduce the value of ``LOOP_DELAY`` to achieve faster trigger checking


FAQ
===

**Q: Can I use this with the Web Interface?**

A: No, this application consumes all processing resources and will make the web interface unresponsive.

**Q: What's the maximum buffer size?**

A: 30 µs maximum, limited by Red Pitaya's DMA capabilities.

**Q: Can I route IN1 to OUT2?**

A: Yes, but this configuration is untested. Use ``signal_source=IN1`` in DAC2 section.

**Q: How do I change trigger sensitivity?**

A: Adjust ``trigger_level`` in ADC sections (range: -1.0 to 1.0 Volts).

**Q: Why does the signal break up?**

A: Usually due to insufficient ``repetition_delay``. Ensure it's ≥ (buffer_time × count_burst + 1) µs.


Disable the Record and Play
============================

Once the *Record and Play* application is set up, it will start each time Red Pitaya boots. Here is how you can disable the process.

1. **One time disable** - to stop the application until the next boot use the ``top`` command inside Red Pitaya Linux and ``kill`` the *main.py* process. By entering the PID of the process, the Linux will kill it.
  
    .. figure:: img/Rec_and_play_top.png
        :alt: Top command and kill PID
        :align: center
        :width: 800px

    .. figure:: img/Rec_and_play_top_kill.png
        :alt: Top command and kill PID
        :align: center
        :width: 800px

    .. figure:: img/Rec_and_play_top_kill_signal.png
        :alt: Top command and kill PID
        :align: center
        :width: 800px

2. **Full disable** - First kill the *main.py* process as described in the point above. Then head to the "/opt/redpitaya/sbin" directory and find the **startup.sh** script (you may have to enter *rw* mode). Either delete or comment the following lines of code.
  
    .. code-block:: bash

        # Here you can specify commands for autorun at system startup
        export PYTHONPATH=/opt/redpitaya/lib/python/:$PYTHONPATH
        /opt/redpitaya/bin/main.py

    Afterwards, you can also remove the *main.py* and *config.ini* from */opt/redpitaya/bin*.


Source code
===========

The :rp-github:`Playback and Record source code <rec_and_play/tree/master>` is available on our GitHub.

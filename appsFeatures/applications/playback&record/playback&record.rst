.. _playback&record:

#######################################
RF Signal Recording and Playback script
#######################################

RF Signal Record and Playback script records signal pulses acquired on either IN1 and IN2 and repeats them on OUT1 acording to the configuration file.
Deep Memory Acquisition and Generation are used to record and playback the captured signals.

Once installed, the application is set to start automatically at boot. The application is controlled through the configuration file located in the */opt/redpitaya/bin/* directory.

.. note::

    This application is not meant to be used in parallel with the Red Pitaya WEB interface. As most processing resources is taken by the *Record and Play* application, the Web interface is severly slowed down. 

Setup
=====

The application requires the following OS version:

    * **IN DEV**.
    * Nightly Build 466 (or higher) together with Red Pitaya Linux 2.06 (or higher).

Please make sure that Red Pitaya inputs and outputs are properly terminated (matched impedance). Failure to do so may lead to undefined behaviour of the *Record and Playback* application due to the `ringing <https://incompliancemag.com/circuit-theory-model-of-ringing-on-a-transmission-line/>`_ on the `transmission line <https://en.wikipedia.org/wiki/Transmission_line>`.
Red Pitaya fast analog inputs have input impedance of 1 MΩ. The fast analog outputs have output impedace of 50 Ω.

Installation steps
-------------------

1.  Establish :ref:`SSH <ssh>` connection with your Red Pitaya
#.  Download the |rec_and_play| GitHub Repository to the Red Pitaya.

    .. code-block:: bash

        cd /root
        git clone https://github.com/RedPitaya/rec_and_play.git rap

    Alternatively, download the repository to your computer and copy the code to the Red Pitaya through the SCP command:

    .. code-block:: bash

        scp -r /<path-to-downloaded-repository>/rec_and_play root@rp-xxxxxx.local:/root

#.  Move to the *Record and Play* directory on the Red Pitaya.

    .. code-block:: bash

        cd /root/rap

#.  Make sure all the scripts are executable (use the ``chmod`` commnad).

    .. code-block:: bash

        chmod +x setup.sh config.ini main.py

#.  For automatic setup execute the setup script.

    .. code-block:: bash

        ./setup.sh

#.  For manual installation enter read-write mode and copy the scripts into the */opt/redpitaya/bin* folder.

    .. code-block:: bash

        rw
        cp -f ./main.py /opt/redpitaya/bin/
        cp -f ./config.ini /opt/redpitaya/bin/
    
#. In either case the application is now set up and will start automatically at boot.
#.  To change the settings, edit the configuration file which is located in */opt/redpitaya/bin/config.ini*.
#.  Reboot the Red Pitaya.


.. |rec_and_play| raw:: html

    <a href="https://github.com/RedPitaya/rec_and_play/tree/master" target="_blank">rec_and_play</a>


Configuration
=============

The *Record and Play* application settings are specified in the configuration file (config.ini) located in */opt/redpitaya/bin/* directory.
The settings are split into acquisition (ADC) and generation (DAC):

**Acquisition (ADC)**

    * *Trigger level* (in Volts).
    * *Trigger source* (CH1_PE, CH1_NE, CH2_PE, CH2_NE).
    * *Record buffer lenght* (uses Deep Memory Acquisition) in microseconds (between 1 and 30 µs).

**Generation (DAC)**

    * *Signal generation source channel (IN1 or IN2)* - which input channel should be generated/repeated on OUT1.
    * *Number of Cycles (NCYC)* - Number of Cycles/Periods in one burst/repetition (without any delay between them).
    * *Number of Repetitions (NOR)* - Number of repeated bursts (with delay between them). Each burst includes a number of repetitions without delay.
    * *Delay between repetitions (PERIOD)* - Delay between repetitions in microseconds (µs). The minimum value must be no less than ("Record buffer lenght" * NCYC + 1) µS.

To change the settings, either edit the *config.ini* file in */opt/redpitaya/bin/* directly, or edit the *config.ini* file in the *record and play* directory and run the *setup.sh* script again.
For the changes to take effect, *main.py* must be restarted (either by rebooting the Red Pitaya or by killing the process and starting it again).

Example of "config.ini":

.. code-block::

    [ADC]
    ; Trigger Level in volts
    trigger_level=0.1
    ; Trigger source (Values: CH1_PE, CH1_NE, CH2_PE, CH2_NE)
    trigger_mode=CH1_PE
    ; Record signal Buffer size in microseconds (min 1 µs)
    buffer_time=20

    [DAC]
    ; Gen signal from source (IN1, IN2). Which input to use for recording data.
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
    repetition_delay=21


Disable the Record and Play
===========================

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

The `Playback and Record source code <https://github.com/RedPitaya/rec_and_play/tree/master>`_ is available on our GitHub.

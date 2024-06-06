.. _intro_gen_acq:

Introduction to data acquisition and generation with Red Pitaya
*******************************************************************

In this section we will discuss all the options available for generating and acquiring data with Red Pitaya, from the simplest to the most advanced. We will also discuss the limitations of each mode and possible implementation issues.

.. note::

   Some boards like :ref:`SDRlab 122-16<top_122_16>` have AC coupling on inputs and outputs, which may limit the available acquisition and generation frequency range.

Ordered from simplest to most complex:

- `Oscilloscope and other applications`_
- `SCPI commands`_
- `API commands (C, Python)`_
- `Deep Memory Acquisition (DMA)`_
- `Streaming application`_
- `Custom acquisition and generatiron (FPGA)`_


Oscilloscope and other applications
======================================

The easiest way to acquire data is to use the pre-built applications such as oscilloscope, spectrum analyser, bode analyser, etc. that are accessible through the web interface.
Use this option if you want to use Red Pitaya as a software-defined instrument and rarely need to download data to your computer and process it (usually screenshots and CSV data tables are sufficient).

Data from each channel is captured in a 16384 sample buffer, processed and displayed in the web interface.
The data can currently only be extracted from the application at the user's request. Remote data acquisition by an application other than :ref:`Data stream control<streaming_top>` is not currently available.

The same applies to data generation options - applications such as oscilloscope and spectrum analyzer also have signal generator capabilities so that both inputs and outputs can be used simultaneously.
The signal generator can generate a predefined waveform, such as sine, square, saw up, saw down, etc. or act as an `arbitrary waveform generator <https://en.wikipedia.org/wiki/Arbitrary_waveform_generator>`_.
The signal generator includes *burst* and *sweep* generation capabilities.

To use the AWG functionality, a 16384 sample long waveform representing one period of a custom signal is uploaded via the :ref:`ARB manager application<arb_manager_app>` in CSV format.
The uploaded custom waveform can be selected from the *Waveform Type* dropdown menu. There are a few things to keep in mind when creating a custom waveform. Read more about this in the `SCPI commands`_ section.

For more information on the applications and how they work, click here:

- :ref:`Red Pitaya applications<all_apps>`
- Application source code is available on our `GitHub <https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools
>`_.



SCPI commands
================

To remotely control the Red Pitaya from a Python, MATLAB or LabVIEW program running on your computer, and to acquire data from the Red Pitaya to your computer for further processing, use the SCPI commands.
The code is executed on a computer and string commands are sent between Red Pitaya and your computer via `socket communication <https://en.wikipedia.org/wiki/Network_socket>`_. Once the SCPI commands reach Red Pitaya, they are interpreted and an appropriate C API function is executed in the background.

.. note::

   **Never** use the oscilloscope or other web applications while the SCPI server is running. This may cause unpredictable behaviour of the SCPI commands.


SCPI Acquisition
-------------------

For proper data acquisition using SCPI commands, a trigger condition must be specified, otherwise the data returned may be invalid or corrupted, as the FPGA can acquire data much faster than the Linux operating system can read it from the FPGA registers.

After the capture is started and the first trigger condition is met, 16384 samples are captured on each of the Red Pitaya input channels and stored in a *circular memory buffer*. The *circular memory buffer* stores 16384 samples. The trigger position is at a random sample within the *circular memory buffer*:

.. figure:: img/Circ_mem_buff.png
   :width: 600
   :align: center

The *circular memory buffer* is then converted into a 16384 sample long *data buffer* with the trigger position in the middle of the buffer (at the position of the 8192nd sample). It is important to distinguish between the *circular memory buffer* and the *data buffer*. Most of the SCPI commands refer to the *data buffer* and its position, but there are commands that refer to the position within the *circular memory buffer*. The data pointer commands always refer to the position of the *circular memory buffer*.

.. note::

   **Circular memory buffer != Data buffer**

   The trigger position inside the *circular memory buffer* depends on the start of the acquisition and can be considered random, while the trigger position inside the *data buffer* is fixed to the 8192nd sample.
   The *circular memory buffer* is generally not visible to the user. The *data buffer* is what the user gets when they request data.

The *data buffer* is converted to a string and sent to the computer on request. There it can be converted back to a floating-point format. The acquisition must be restarted before further data can be acquired, resulting in a dead time between two successive data acquisitions.

To set up the trigger correctly, the following settings must be made:

- Trigger level
- Trigger channel - IN1, IN2 or External. IN3 and IN4 are also available on the 4-input STEMlab 125-14.
- Trigger delay - see explanation below

When acquiring data via SCPI commands, the triggering moment is in the middle of the *data buffer* (8192nd sample). This means that half the data is acquired before the trigger (samples between 0 and 8192) and half the data is acquired after the trigger (samples between 8193 and 16383). By changing the Trigger Delay parameter, you can either capture more data before the trigger event (by specifying a negative trigger delay, where the maximum is -8192) or capture more data after the trigger event (by specifying a positive trigger delay). The situation is illustrated below:

.. figure:: img/Python_buff.png
   :width: 800
   :align: center

Data can be acquired in the following ways:

- Read the entire *data buffer* (``ACQ:SOUR<n>:DATA?``)
- Read the oldest samples in the *data buffer* (``ACQ:SOUR<n>:DATA:Old:N? <size>``)
- Read the latest samples in the *data buffer* (``ACQ:SOUR<n>:DATA:LATest:N? <size>``)
- Read samples relative to trigger condition from *data buffer* (``ACQ:SOUR<n>:DATA:TRig? <size>,<t_pos>``)
- Read a number of samples from start position to end position from the *circular memory buffer* (``ACQ:SOUR<n>:DATA:STArt:End?``)
- Read a number of samples from start position out of the *circular memory buffer* (``ACQ:SOUR<n>:DATA:STArt:N?``)

Variable buffer lengths can be achieved by using the `Deep Memory Acquisition (DMA)`_ mode.

General tips for programming with acquisition SCPI commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Always check your Red Pitaya OS version, as not all commands are compatible with all OS versions. The command release version can be found in the :ref:`Ecosystem column of the command table<command_list>`.
- The :ref:`SCPI code examples<examples>` are intended to run on the latest version of the Red Pitaya OS.
- Start with the ``ACQ:RST`` command.
- Then set the capture parameters.
- Set the trigger settings.
- Start the capture (``ACQ:START``).
- Make sure there is enough time for Red Pitaya to update half of the data buffer (at the current decimation) before the trigger condition arrives. This avoids situations where the first half of the signal frequency in the first part of the buffer is different from the second half.
- Check that the trigger condition is met and that the data buffer is full.
- Send a data request.
- To acquire another data buffer, restart the acquisition (``ACQ:START``). Note that the acquisition parameters remain the same until Red Pitaya is restarted or the ``ACQ:RST`` command is executed.


SCPI generation
------------------

Red Pitaya's SCPI generation commands can be divided into four sections:

- Continuous signal generation
- Burst signal generation
- Sweep signal generation
- Arbitrary Waveform Generation

The general functionality is similar in all sections, but each section has a few special cases that need to be mentioned.

Continuous signal generation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We will start with continuous signal generation, which is the easiest to understand. First we define the signal parameters:

- Waveform type (sine, square, triangle, saw up, saw down, etc.)
- Frequency [Hz] - between 1 Hz and 50 MHz
- Amplitude [V] - unidirectional amplitude referenced to GND between +-1 V.

.. note::

   The limitations are written for STEMlab 125-14 and may be different for other board models.

These are the minimum parameters required to generate a continuous signal. There are other parameters, but for the sake of simplicity we will skip them.

Next we set the generator trigger source, which defines how and from where our generator will be triggered. This can be set to either internal (activated manually with a code command) or external positive or negative edge (triggered by an external trigger signal on pin DIO0_P on the :ref:`E1 extension connector<e1>`).

The external trigger signal passes through a debounce filter when it enters the FPGA, which is set to 500 microseconds by default. This value can be changed using the ``SOUR:TRig:EXT:DEBouncer[:US]`` command.

All that remains is to trigger the signal generation, but this is where the tricky part comes in. Normally you would just trigger the generation and that would be it, but with Red Pitaya we need to enable the output first and then trigger the generation.

- ``OUTPUT<n>:STATE ON`` - enables the specified output
- ``SOUR<n>:TRig:INT`` - triggers the specified output generation.

To enable both outputs simultaneously, use the following commands

- ``OUTPUT:STATE ON`` - enables both outputs
- ``SOUR:TRig:INT`` - triggers generation on both outputs

Of course, the second command is not necessary if the trigger source is configured to the external trigger.

.. note::

   **Generation trigger != Acquisition trigger**
   Generation and acquisition triggers are completely different and have separate logic behind them.


Burst signal generation
~~~~~~~~~~~~~~~~~~~~~~~~~~

Burst signals are very similar to continuous signals. The main difference between the two is that burst signals are typically finite (they end after a certain period of time). To fully describe them, we need to know a few more parameters in addition to those used for continuous signals:

- Number of cycles (NCYC) - number of signal periods in a burst
- Number of repetitions (NOR) - number of successive bursts
- Period [µs] - the time between the start of one burst and the start of the next (in microseconds).

These and the parameters for defining continuous signals are the minimum parameters required to generate any burst signal. There are other parameters, but for the sake of simplicity we will leave them out.

Besides defining new parameters, we also need to switch the Red Pitaya to burst mode instead of continuous mode, which we do with the following command:

- ``SOUR<n>:BURS:STAT BURST``

The last thing we need to do to generate a burst signal is to trigger it. See the section on `Continuous Signal Generation` for more information.

.. note::

   Switch the oscilloscope trigger to *normal* mode when measuring burst signals.

As mentioned above, burst signals tend to last for a limited time after being triggered, but it is possible to set up continuous burst signal generation. To do this, set the Red Pitaya to the maximum possible NOR value (65536).

The other thing to watch out for with burst generation is sequential triggering. We must be careful not to trigger another generation on the same channel after we are sure that the previous burst has ended. Otherwise, the Red Pitaya may superimpose the two bursts.


Sweep signal generation
~~~~~~~~~~~~~~~~~~~~~~~~~

Sweep signals are continuous signals that change frequency between two set frequency values in a specified time. We use the continuous signal parameters together with

- Sweep start frequency [Hz]
- Sweep end frequency [Hz]
- Sweep time [µs] - how long it takes the sweep signal to move from the start to the end frequency.

These are the minimum parameters required to generate any sweep signal. There are other parameters, but for the sake of simplicity we will ignore them.

The sweep mode is switched on manually with the following command:

- ``SOUR<n>:SWeep:STATE ON``

When the sweep mode is stopped, the generator does not return to its initial state, but instead generates a continuous signal at the frequency of the last sweep mode step. For example, suppose we had a sweep between 1 kHz and 10 kHz lasting 1 second. We decide to stop sweep generation and execute the command. At the moment the command is executed, the sweep is generating an 8.5 kHz signal, which will continue to be generated as a continuous signal when the sweep mode is switched off.


Arbitrary waveform signal generation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The final generation option is the Arbitrary Waveform Generator (AWG), which generates a user-defined custom signal waveform. The Red Pitaya expects the user to pass a 16384 sample long waveform representing one period of the custom signal. The voltage levels should be within the output limits (+-1 V), otherwise Red Pitaya will normalise the entire waveform.

The custom period is passed to Red Pitaya with the following SCPI command:

- ``SOUR<n>:TRAC:DATA:DATA <array>``

By default, the AWG is a continuous signal and requires us to define the same basic parameters (amplitude and frequency). To enable the AWG, we pass the ARBITRARY keyword as the waveform type when selecting the waveform:

- ``SOUR<n>:FUNC ARBITRARY``

There are a number of tricks and questions that we need to be aware of when using the Arbitrary Waveform Generator.

**What happens if we have more than one signal period in the AWG buffer?**.

Consider the following example. We define a custom waveform buffer of 16384 samples containing two sine periods. We pass this buffer to Red Pitaya, specify the frequency as 10 kHz, the amplitude as 1 V and generate the signal.

When we measure the generated signal, the actual output frequency has changed - we get a 20 kHz sine wave. What is happening?
The explanation is quite simple, we are generating two sine wave periods with a frequency of 10 kHz, resulting in a 20 kHz sine wave.

To calculate the actual output frequency we can use the following formula:

.. math::

   f_{output} = f_{buff}\cdot\frac{N_{buff}}{N_{period}}

Where :math:`f_{output}` is the actual output frequency, :math:`f_{buff}` is the frequency of the whole buffer (passed to Red Pitaya as a parameter), :math:`N_{buff}` is the total number of samples in the numpy buffer (16384), and :math:`N_{period}` is the number of samples a signal period takes in the numpy buffer.

It is possible to force Red Pitaya to generate frequency pulses higher than 50 MHz using the AWG.

.. note::

   Scenarios where the calculated output frequency exceeds 50 MHz should be avoided if possible, as this can lead to unpredictable results due to Red Pitaya not having enough points to create a nice waveform.

**What happens if less than 16384 samples are passed?**.

**Avoid passing less than 16384 samples to Red Pitaya, as this may lead to unpredictable results.** In this case, the result is similar to the example above. Suppose we define a custom waveform buffer of 8192 samples containing one sine period. We pass this buffer to Red Pitaya and specify the frequency as 10 kHz, the amplitude as 1 V and generate the signal. The actual output is a 20 kHz sine wave.

Here the waveform is duplicated within the buffer (the read pointer moves through the waveform twice as fast).


General tips for programming with generation SCPI commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Always check your Red Pitaya OS version, as not all commands are compatible with all OS versions. The command release version can be found in the :ref:`Ecosystem column of the command table<command_list>`.
- The :ref:`SCPI code examples<examples>` are intended to run on the latest version of the Red Pitaya OS.
- Start with the ``GEN:RST`` command.
- Set contiuous signal parameters.
- Optionally, switch to burst mode and set the burst signal parameters.
- Optionally, switch to sweep mode and set the sweep signal parameters.
- Set the generator trigger settings.
- Enable the outputs.
- Trigger the outputs.
- Remember that Red Pitaya remembers the settings, so to repeat the same signal at a later time, only the triggering needs to be done (there is no need to redefine the whole generated signal). Alternatively, you can change only certain parameters.
- By default, Red Pitaya is set to generate a 1kHz sine wave with an amplitude of 1 V. 

More information about the SCPI server can be found here:

- :ref:`Installation instructions<scpi_commands>`
- :ref:`Complete table of SCPI commands<command_list>`
- :ref:`SCPI examples<examples>`


API commands (C, Python)
==========================

Another way to control the Red Pitaya is to use the C and Python API commands that run on the Red Pitaya's Linux OS. The advantage over the SCPI commands is that the API commands are faster because there is no need to convert the data into strings, send it over the Ethernet and then reconstruct it. In addition, you have full access to the Linux operating system, which means you can configure programs to run directly at boot time, customise data interpretation, or write your own drivers to enhance the existing code. Finally, you have direct access to the FPGA's registry space, making it much easier to write your own software.

The Python API commands are the same as the C API commands, as they are simply a Python front-end to the C commands. You can run Python code directly on Red Pitaya starting with Red Pitaya 2.00-30 OS (out of the box).

The overall functionality is exactly the same as with the SCPI commands, with the exception of using functions instead of string commands and the fact that there are more commands available that have not yet received their SCPI versions.

One thing to note here is that deep memory acquisition of long sequences of data can be speeded up by using a C or Python program to acquire the data and then establishing a TCP connection to the computer to achieve a much faster transfer than using the SCPI commands. This requires custom code to establish the connection, transmit the data to the computer, and receive the data from a program such as MATLAB, where it can be processed. 

All information about running C and Python programs can be found here:

- :ref:`C & Python API commands<API_commands>`
- `GitHub API source code <https://github.com/RedPitaya/RedPitaya/tree/master/rp-api>`_


Streaming application
========================

For those looking for continuous data acquisition, check out :ref:`the streaming application<streaming_top>` (also known as "data stream control"). It allows continuous data acquisition from one or both of Red Pitaya's inputs directly to a file on a computer. The data can be captured indefinitely, but there are speed limitations and currently no triggering options. 
The total data flow at the inputs (IN1 and IN2) must not exceed 20 MB/s when streaming directly to a computer or 10 MB/s when streaming to the SD card. More details and limitations are available :ref:`here<streaming_top>`.

There are two ways to stream data. Either via Ethernet to a *bin*, *tdms* or *wav* file on a computer or to the Red Pitaya's SD card. The streaming parameters can also be controlled from a desktop client application. If multiple boards are on the same network (such as when using the :ref:`X-channel system<x-ch_streaming>`), they can all be controlled simultaneously from the client application.

All information about the streaming application is available from the links below:

- :ref:`Streaming application<streaming_top>`
- `GitHub source code <https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools/streaming_manager>`_


Deep Memory Acquisition (DMA)
================================

.. note:: 

   Deep memory acquisition is available on Red Pitaya OS versions 2.00-23 and later.

Deep memory acquisition is a special type of data acquisition that allows the user to stream data directly into Red Pitaya's DDR3 RAM at full sampling speed of 125 Msps (depending on board model).
The buffer length is variable and can be specified by the user, but cannot exceed the size of the allocated RAM region. The amount of dedicated RAM can be increased by the user, but it is recommended to leave at least 100 MB
of DDR for proper operation of the Linux OS. Deep memory acquisition is based on the `AXI protocol (AXI DMA and AXI4-Stream) <https://support.xilinx.com/s/article/1053914?language=en_US>`_ (double the acronym for double the meaning).

Once the acquisition is complete, Red Pitaya needs some time to transfer the entire file to the computer (RAM needs to be cleared) before the acquisition can be reset.
DMA can be configured using SCPI, Python API and C API commands. The triggering options are also the same.

To increase the speed of transferring the DMA data to the computer with SCPI, the data should be acquired in binary format (``ACQ:DATA:FORMAT BIN``).

All information on DMA is available from the links below:

- :ref:`Deep Memory Acquisition<deepMemoryAcq>`


Custom acquisition and generatiron (FPGA)
=============================================

The final option for data acquisition and generation is to re-program and customise the FPGA image to create new methods or extend existing functionality. Red Pitaya is an open source platform, so the software can be fine-tuned for specific applications. Customisation can also be done by the Red Pitaya team on request.

- `Red Pitaya ecosystem Github repository <https://github.com/RedPitaya/RedPitaya>`_
- `Red Pitaya FPGA Github repository <https://github.com/RedPitaya/RedPitaya-FPGA>`_
- :ref:`Red Pitaya customization services<customization>`



`Back to top <Introduction to data acquisition and generation with Red Pitaya>`_

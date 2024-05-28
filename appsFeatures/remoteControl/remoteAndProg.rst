####################################
Programming and remote-control tools
####################################

Here you will find all the tools and examples you need to program and control your Red Pitaya. This section includes the following chapters

- **SCPI Server** - How to set up an SCPI server on your Red Pitaya and control it remotely from Python, MATLAB or LabVIEW?
- **C and Python Applications** - How to run C and Python programs directly on the Linux OS of your Red Pitaya board.
- **JupyterLab** - How to use the JupyterLab application to create interactive documents with Python code.
- **Deep Memory Acquisition** - How to acquire data directly into DDR RAM with variable buffer sizes at full speed.
- **List of Supported SCPI & API Commands** - A list of all the SCPI and API commands available on the Red Pitaya, with a short description of each command and the OS version in which the command was first introduced.
- **Examples** - Code examples for SCPI and API covering everything from LED control to data acquisition and generation to digital communication interfaces.
- **Known SCPI & API Issues and Changes by OS Version** - Is your code not working as intended? Check this section for known command issues or release dates of newer commands.

.. toctree::
   :maxdepth: 1

   scpi
   API_scripts
   jupyter/Jupyter
   deepMemoryAcquisition
   command_list
   examples_top
   knownIssues


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
- `Deep Memory Acquistion`_
- `Streaming application`_
- `Custom acquisition and generatiron (FPGA)`_


Oscilloscope and other applications
======================================

The easiest way to acquire data is to use the pre-built applications such as oscilloscope, spectrum analyser, bode analyser, etc. that are accessible through the web interface. Use this option if you want to use Red Pitaya as a software-defined instrument and rarely need to download the data to your computer and process it (usually screenshots and CSV data tables are sufficient).

Data from each channel is captured in a 16384 sample long buffer, processed, and displayed in the web interface. The data can currently only be extracted from the application at the user's request. Remote data acquisition by any application other than :ref:`Data stream control<streaming_top>` is not currently available.

The same goes for the data generation options - applications like oscilloscope and spectrum analyzer also feature signal generator capabilities, so both inputs and outputs can be utilized at the same time. The signal generator can generate a predefined waveform, like sine, square, saw up, saw down, etc. , or function as an `arbitrary waveform generator<https://en.wikipedia.org/wiki/Arbitrary_waveform_generator>`_. The signal generator includes *burst* and *sweep* generation capabilities.

To use the AWG functionality, a 16384 sample long waveform, which represents one period of a custom signal, is uploaded via the :ref:`ARB manager application<arp_manager_app>` in a CSV format. The uploaded custom waveform can be selected from the *waveform type* dropdown menu. There are some things to watch out for when creating a custom waveform. Read more about them in the `SCPI commands`_ section.

More information regarding the applications and theri functionalty is available here:

- :ref:`Red Pitaya applications<all_apps>`
- Application source code is available on our `GitHub<GitHub-apps>`_.
    
.. _GitHub-apps: https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools



SCPI commands
================

To remotely control the Red Pitaya from a Python, MATLAB or LabVIEW program running on your computer, and to acquire data from the Red Pitaya to your computer for further processing, use the SCPI commands.
The code is executed on a computer and string commands are sent between Red Pitaya and your computer via `socket communication<https://en.wikipedia.org/wiki/Network_socket>`_. Once the SCPI commands reach Red Pitaya, they are interpreted and an appropriate C API function is executed in the background.

.. note::

   **Never** use the oscilloscope or other web applications while the SCPI server is running. This can cause unpredictable behaviour of the SCPI commands.


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

- Read the entire *data buffer* (ACQ:SOUR<n>:DATA?)
- Read the oldest samples in the *data buffer* (ACQ:SOUR<n>:DATA:Old:N? <size>)
- Read the latest samples in the *data buffer* (ACQ:SOUR<n>:DATA:LATest:N? <size>)
- Read samples relative to trigger condition from *data buffer* (ACQ:SOUR<n>:DATA:TRig? <size>,<t_pos>)
- Read a number of samples from start position to end position from the *circular memory buffer* (ACQ:SOUR<n>:DATA:STArt:End?)
- Read a number of samples from start position out of the *circular memory buffer* (ACQ:SOUR<n>:DATA:STArt:N?)

Variable buffer lengths can be achieved by using the `Deep Memory Acquisition (DMA)`_ mode.

**General tips for programming with acquisition SCPI commands**

- Always check your Red Pitaya OS version, as not all commands are compatible with all OS versions. The command release version can be found in the :ref:`Ecosystem column of the command table<command_list>`.
- The :ref:`SCPI code examples<examples>` are intended to run on the latest version of the Red Pitaya OS.
- Start with the ACQ:RST command.
- Then set the capture parameters.
- Set the trigger settings.
- Start the capture (ACQ:START).
- Make sure there is enough time for Red Pitaya to update half the data buffer (at the current decimation) before the trigger condition arrives. This avoids situations where the first half of the signal frequency in the first part of the buffer is different from the second half.
- Check that the trigger condition is met and that the data buffer is full.
- Send a data request.
- To acquire another data buffer, restart the acquisition (ACQ:START). Note that the acquisition parameters remain the same until Red Pitaya is restarted or the ACQ:RST command is executed.


SCPI generation
------------------




**General tips for programming with generation SCPI commands**

- Always check your Red Pitaya OS version, as not all commands are compatible with all OS versions. The command release version can be found in the :ref:`Ecosystem column of the command table<command_list>`.
- The :ref:`SCPI code examples<examples>` are intended to run on the latest version of the Red Pitaya OS.
- Start with the GEN:RST command.

- Then set the capture parameters.
- Set the trigger settings.
- Start the capture (ACQ:START).
- Make sure there is enough time for Red Pitaya to update half the data buffer (at the current decimation) before the trigger condition arrives. This avoids situations where the first half of the signal frequency in the first part of the buffer is different from the second half.
- Check that the trigger condition is met and that the data buffer is full.
- Send a data request.
- To acquire another data buffer, restart the acquisition (ACQ:START). Note that the acquisition parameters remain the same until Red Pitaya is restarted or the ACQ:RST command is executed.



More information about the SCPI server can be found here:

- :ref:`Installation instructions<scpi_commands>`
- :ref:`Complete table of SCPI commands<command_list>`
- :ref:`SCPI examples<examples>`


API commands (C, Python)
==========================

Another way to control the Red Pitaya is to use the C and Python API commands that run on the Red Pitaya's Linux OS. The advantage over the SCPI commands is that the API commands are faster because there is no need to convert the data into strings, send it over the Ethernet and then reconstruct it. In addition, you have full access to the Linux operating system, which means you can configure programs to run directly at boot time, customise data interpretation, or write your own drivers to enhance the existing code. Finally, you have direct access to the FPGA's registry space, making it much easier to write your own software.

The Python API commands are the same as the C API commands, as they are just a Python front-end to the C commands. You can run Python code directly on Red Pitaya starting with Red Pitaya 2.00-30 OS (out of the box).

Otherwise, the overall functionality is almost exactly the same as via the SCPI commands, but there are a few commands that have not yet received their SCPI versions.

One thing to note here is that deep memory acquisition of long sequences of data can be speeded up by acquiring the data using a C or Python program and then establishing a TCP connection to the computer to achieve a much faster transfer than using the SCPI commands. This requires custom code to establish the connection, transmit the data to the computer, and receive the data from a program such as MATLAB, where it can be processed. 

All information about running C and Python programs can be found here:

- :ref:`C & Python API commands<API_commands>`
- `GitHub API source code<https://github.com/RedPitaya/RedPitaya/tree/master/rp-api>`_


Streaming application
-----------------------

For those looking for continuous data acquisition, check out :ref:`the streaming application<streaming_top>` (also known as "data stream control"). It allows continuous data acquisition from one or both of Red Pitaya's inputs directly to a file on a computer. The data can be captured indefinitely, but there are speed limitations and currently no triggering options. 
The total data flow at the inputs (IN1 and IN2) must not exceed 20 MB/s when streaming directly to a computer or 10 MB/s when streaming to the SD card. More details and limitations are available :ref:`here<streaming_top>`.

There are two ways to stream the data. Either via Ethernet to a *bin*, *tdms* or *wav* file on a computer or to the Red Pitaya's SD card. The streaming parameters can also be controlled from a desktop client application. If multiple boards are on the same network (like when using the :ref:`X-channel system<x-ch_streaming>`), they can all be controlled simultaneously from the client application.

All information on the streaming application is available on the links below:

- :ref:`Streaming application<streaming_top>`
- `GitHub source code<https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools/streaming_manager>`_


Deep Memory Acquisition (DMA)
------------------------------

Deep memory acquisition is a special type of data acquisition that allows the user to stream data directly into Red Pitaya's DDR3 RAM at the full sampling speed of 125 Msps (depends on the board model). The buffer length is variable and can be specifed by the user, but cannot exceed the allocated RAM region size. The dedicated RAM memory can be increased by the user, but it is recommended to leave at least 100 MB of the DDR for the proper operation of the Linux OS. The deep memory acquisition relies on the `AXI protocol (AXI DMA and AXI4-Stream)<https://support.xilinx.com/s/article/1053914?language=en_US>`_ (twice the acronym double the meaning).

After the acquisition is complete, Red Pitaya needs some time to transfer the whole file to the computer (the RAM must be emptied) before the acquisition can be reset.
The DMA can be configured through SCPI, Python API, and C API commands. The triggering capabilities are also the same.

All information on the DMA is available on the links below:

- :ref:`Deep Memory Acquisition<deepMemoryAcq>`

The deep memory acquision is available on Red Pitaya OS versions 2.00-23 and newer.


Custom acquisition and generatiron (FPGA)
-------------------------------------------

The final option for data acquisition and generation is reprogramming and customizing the FPGA image to create new methods or expand the existing functionality. Red Pitaya is open-source platform, so the software can be fine tuned to specific applications. Customization can also be performed by the Red Pitaya team on request. 

- `Red Pitaya FPGA Github repository<https://github.com/RedPitaya/RedPitaya-FPGA>`_
- :ref:`Red Pitaya customization services<customization>`


Generation options
====================

How can I generate data with Red Pitaya?
------------------------------------------------

Here are all possible generation options on the Red Pitaya (please be aware of AC coupling limitations on SDRlab 122-16):

   - **Oscilloscope application** - basic waveform generation. More info :ref:`here <osc_app>`.
   - **SCPI commands (Python, MATLAB, LabVIEW)**, remote control from computer - can generate basic waveforms as well as custom/arbitrary waveforms (defined in a 16384 sample-long buffer which represents one period of the signal - the frequency is calculated for the whole buffer). More details :ref:`here <scpi_commands>`.
   - **API commands (C, Python)**, on-board program - same functionality as standard SCPI commands, but generally faster and includes the benefit of possible direct communication with the FPGA. More info :ref:`here <API_commands>`.
   - **Custom/user-defined (FPGA reprogramming)** - Red Pitaya is open-source, so anyone has the option of reprogramming the FPGA image to customise the functionality.



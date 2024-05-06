####################################
Programming and remote-control tools
####################################

Here you will find all the tools and examples you need to program and control your Red Pitaya. This section contains the following chapters

- **SCPI Server** - How to set up an SCPI server on your Red Pitaya and control it remotely from Python, MATLAB or LabVIEW?
- **C and Python Applications** - How to run C and Python programs directly on the Linux OS of your Red Pitaya board.
- **JupyterLab** - How to use the JupyterLab application to create interactive documents with Python code.
- **Deep Memory Acquisition** - How to acquire data directly into DDR RAM with variable buffer sizes at full speed?
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
******************************************************************

In this section we will discuss all the options available for generating and acquiring data with Red Pitaya, from the simplest to the most advanced. We will also discuss the limitations of each mode and possible implementation issues.

Acquisition options
====================

Ordered from simplest to most complex:

- `Oscilloscope and other applications`_
- `SCPI data acquisition`_
- `API command acquisition (C, Python)`_
- `Deep Memory Acquistion`_
- `Streaming application`_
- `Custom Acquisition (FPGA)`_


Oscilloscope and other applications
------------------------------------------

The easiest way to acquire data is to use the pre-built applications such as oscilloscope, spectrum analyser, bode analyser, etc. that are accessible through the web interface. Use this option if you want to use Red Pitaya as a software-defined instrument and rarely need to download the data to your computer and process it (usually screenshots and CSV data tables are sufficient).

The data is captured in 16384 sample buffers and then processed depending on the instrument before being displayed in the web interface. The data can currently only be extracted from the application at the user's request. Remote data acquisition by any application other than :ref:`Data stream control <streaming_top>` is not currently available.

Please refer to :ref:`specific applications <all_apps>` for more information.
Application source code is available on our GitHub here <GitHub-apps>.
    
.. _GitHub-apps: https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools


SCPI data acquisition
------------------------

To remotely control the Red Pitaya from a Python, MATLAB or LabVIEW program running on your computer, and to acquire data from the Red Pitaya to your computer for further processing, use the SCPI commands.
The code is executed on a computer and string commands are sent between Red Pitaya and your computer via |socket communication|. Once the SCPI commands reach Red Pitaya, they are interpreted and an appropriate C API function is executed in the background.

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

Variable buffer lengths can be achieved by using the Deep Memory Acquisition mode.


**General tips for programming with acquisition SCPI commands

- Always check your Red Pitaya OS version, as not all commands are compatible with all OS versions. The command release version can be found in the :ref:`Ecosystem column of the command table <command_list>`.
- The :ref:`SCPI code examples <examples>` are intended to run on the latest version of the Red Pitaya OS.
- Start with the ACQ:RST command.
- Then set the capture parameters.
- Set the trigger settings.
- Start the capture (ACQ:START).
- Make sure there is enough time for Red Pitaya to update half the data buffer (at the current decimation) before the trigger condition arrives. This avoids situations where the first half of the signal frequency in the first part of the buffer is different from the second half.
- Check that the trigger condition is met and that the data buffer is full.
- Send a data request.
- To acquire another data buffer, restart the acquisition (ACQ:START). Note that the acquisition parameters remain the same until Red Pitaya is restarted or the ACQ:RST command is executed.

.. note::

   **Never** use the oscilloscope or other web applications while the SCPI server is running. This can cause unpredictable behaviour of the SCPI commands.


More information about the SCPI server can be found here:

- :ref:`Installation instructions <scpi_commands>`
- :ref:`Complete table of SCPI commands <command_list>`
- :ref:`SCPI examples <examples>`


API command acquisition (C, Python)
-------------------------------------

Another way to control the Red Pitaya is to use the C and Python API commands that run on the Red Pitaya's Linux OS. The advantage over the SCPI commands is that the API commands are faster because there is no need to convert the data into strings, send it over the Ethernet and then reconstruct it. In addition, you have full access to the Linux operating system, which means you can configure programs to run directly at boot time, customise data interpretation, or write your own drivers to enhance the existing code. Finally, you have direct access to the FPGA's registry space, making it much easier to write your own software.

The Python API commands are the same as the C API commands, as they are just a Python front-end to the C commands. You can run Python code directly on Red Pitaya starting with Red Pitaya 2.00-30 OS (out of the box).

Otherwise, the overall functionality is almost exactly the same as via the SCPI commands, but there are a few commands that have not yet received their SCPI versions.

One thing to note here is that deep memory acquisition of long sequences of data can be speeded up by acquiring the data using a C or Python program and then establishing a TCP connection to the computer to achieve a much faster transfer than using the SCPI commands. This requires custom code to establish the connection, transmit the data to the computer, and receive the data from a program such as MATLAB, where it can be processed. 

All information about running C and Python programs can be found here:

- :ref:`C & Python API commands <API_commands>`
- GitHub API source code <https://github.com/RedPitaya/RedPitaya/tree/master/rp-api>`_


Streaming application
-----------------------

For those looking for continuous data acquisition, check out :ref:`the streaming application <streaming_top>` (also known as "data stream control"). It allows continuous data acquisition from one or both of Red Pitaya's inputs directly to a file on a computer. The data can be captured indefinitely, but there are speed limitations and currently no triggering options. 
The total data flow at the inputs (IN1 and IN2) must not exceed 20 MB/s when streaming directly to a computer or 10 MB/s when streaming to the SD card. More details and limitations are available :ref:`here <streaming_top>`.

There are two ways to stream the data. Either via Ethernet to a *bin*, *tdms* or *wav* file on a computer or to the Red Pitaya's SD card. The streaming parameters can also be controlled from a desktop client application. If multiple boards are on the same network (like when using the :ref:`X-channel system <x-ch_streaming>`), they can all be controlled simultaneously from the client application.

All information about running C and Python programs can be found here:

- :ref:`Streaming application <streaming_top>`
- GitHub source code <https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools/streaming_manager>`_


Deep Memory Acquisition
------------------------



   - **Deep Memory (AXI mode)** *(only OS 2.00-23 – latest Beta)* – Long sequence triggered data acquisition. The data can be acquired at different speeds (up to 125 MHz), and it is saved directly into the DDR RAM. The buffer length can be specified by the user but must not exceed 256 MB for both channels. After the acquisition is complete, Red Pitaya needs some time to transfer the whole file to the computer (the RAM must be emptied) before the acquisition can be reset. Functions exactly the same as **API commands**. More details are available :ref:`here <deepMemoryAcq>`.
   -	**Custom Acquisition (FPGA)** – Red Pitaya is open-source so any mode above can be customized by the user to tune it to their specific application.


.. |socket communication| raw:: html

   <a href="https://en.wikipedia.org/wiki/Network_socket" target="_blank">socket communication</a>

How can I generate data with Red Pitaya?
------------------------------------------------

Here are all possible generation options on the Red Pitaya (please be aware of AC coupling limitations on SDRlab 122-16):

   - **Oscilloscope application** - basic waveform generation. More info :ref:`here <osc_app>`.
   - **SCPI commands (Python, MATLAB, LabVIEW)**, remote control from computer - can generate basic waveforms as well as custom/arbitrary waveforms (defined in a 16384 sample-long buffer which represents one period of the signal - the frequency is calculated for the whole buffer). More details :ref:`here <scpi_commands>`.
   - **API commands (C, Python)**, on-board program - same functionality as standard SCPI commands, but generally faster and includes the benefit of possible direct communication with the FPGA. More info :ref:`here <API_commands>`.
   - **Custom/user-defined (FPGA reprogramming)** - Red Pitaya is open-source, so anyone has the option of reprogramming the FPGA image to customise the functionality.



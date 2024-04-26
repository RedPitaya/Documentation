####################################
Programming and remote-control tools
####################################

Here are all the tools and examples for programming and controlling your Red Pitaya. This section has the following chapters:

- **SCPI server** - How to set up an SCPI server on your Red Pitaya and remotely control it through Python, MATLAB, or LabVIEW?
- **C and Python Applications** - How to run C and Python programs directly on the Linux OS of your Red Pitaya board?
- **JupyterLab** - How to use the JupyterLab application to create interactive documents with Python code?
- **Deep Memory Acquisition** - How to acquire data directly into the DDR RAM with variable buffer sizes at full speed?
- **List of supported SCPI & API commands** - The list of all available SCPI and API commands available on the Red Pitaya with a short description of each command and version of the OS that the command was first introduced in
- **Examples** - Code examples for SCPI and API covering everything from controlling the LEDs to data acquisition and generation to digital communication interfaces.
- **Known SCPI & API issues and changes by OS version** - Is your code not working as intended? Check this section for known command issues or release dates of newer commands.

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

In this section we will discuss all the available options for generating and acquiring data with Red Pitaya from the simplest to the most advanced. We will also discuss what are the limitations of each mode and possible problems with implementation

Acquisition options
====================

Ordered from simplest to most complex:

- `Oscilloscope and other applications`_
- `SCPI data acquisition`_
- `API commands (C, Python)`_
- `Deep Memory Acquistion`_
- `Streaming application`_
- `Custom Acquisition (FPGA)`_


Oscilloscope and other applications
------------------------------------------

The simplest method to acquire data is to use the pre-built applications like oscilloscope, spectrum analyzer, bode analyzer, etc., that are accessible through the web interface. 






There are multiple approaches to acquiring data with Red Pitaya. Here is a quick description of each possiblity:

   - **Oscilloscope application** – The data is acquired at full speed, but all the limitations of a standard oscilloscope apply (currently, the data can only be extracted upon user request via the application. Remote data collection is currently impossible). More info :ref:`here <osc_app>`.
   - **SCPI data acquisition (Python, MATLAB, LabVIEW)** – Triggered data acquisition. The data is acquired in 16384 sample-long buffers. The code is executed on a computer, and string commands are sent to the Red Pitaya via |socket communication|. Data is acquired on the Red Pitaya and then sent back as a string that can be converted to a floating-point format. Trigger can be set to either IN1, IN2, or External (also IN3 and IN4 for STEMlab 125-14 4-Input). Trigger level can be specified. The acquisition must be restarted before a new “data buffer” can be acquired. There is a dead time between capturing two consecutive buffers where data is not saved. More details :ref:`here <scpi_commands>`.
   - **API commands (C, Python)** – Functions exactly the same as SCPI data acquisition, but it is faster since everything is running on the Red Pitaya board itself (the code is executed on the board). More info :ref:`here <API_commands>`.
   - **Streaming application** – Continuous data acquisition. The data is streamed from one or both inputs directly to a file on a computer. The data can be acquired indefinitely, but there are speed limitations. 
The total data flow at the inputs (IN1 and IN2) must not exceed 20 MB/s when streaming directly to a computer or 10 MB/s when streaming to the SD card. More details on the limitations are available :ref:`here <streaming_top>`.
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



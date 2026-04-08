
# FPGA

##. FPGA register access

    Kar se tiče ARMa, so dostopi do BRAM še hitrejši kot do DDR. (Če se prav spomnim) Zynq PS dostope do BRAM tretira enako kot DDR, samo da se preadresira na drug kontroler. Ker pa je BRAM v bistvu on board spomin, je zelo hiter - dosti manjše latence. 

    "Single read" registrov je pa seveda dosti počasnejši, ker vsako branje ustvari nekaj overhead-a.

##. FPGA Ethernet

    The Ethernet should be accessible but you have to use the baremetal connection - double check this with Jure and Črt.

    žal ne gre. Ethernet je integriran v PS del.

    Mogoče bi se dalo kaj narediti, će bi imel kam priklopit še kak dodatni PHY in ga potem krmilit iz PL pinov. Ampak to je potem že potrebna HW sprememba na redpitayi.

    Možna bi bila implementacija dodatnega PHY direktno na E3 konektor hitre differencialne linije

    CLAUDE SONNET 4.5>>>
    No, baremetal FPGA Ethernet connection without Linux is not practically possible with Red Pitaya.
    Here's why:

    1. Ethernet MAC Controller Architecture
    The Zynq 7020 SoC on Red Pitaya has its Ethernet MAC controller hardwired in the Processing System (PS) block, not in the Programmable Logic (PL/FPGA). The PS runs the ARM Cortex-A9 processors, which require an operating system (Linux) to manage the Ethernet peripheral drivers.

    2. What You Would Need for Baremetal Ethernet
    To achieve baremetal FPGA Ethernet, you would need:

    An Ethernet MAC IP core implemented in the FPGA fabric (PL)
    A PHY interface to connect the FPGA MAC to the physical Ethernet PHY chip
    Custom FPGA logic to handle all Ethernet packet processing
    3. Red Pitaya Hardware Limitations
    The Red Pitaya board's Ethernet PHY chip is physically connected only to the PS Ethernet MAC, not to the PL. There are no GPIO or high-speed serial connections between the FPGA fabric and the Ethernet PHY that would allow you to bypass the PS.

    4. Theoretical Workarounds (Not Practical)
    You could theoretically:

    Implement a completely new Ethernet MAC and PHY in the FPGA and connect it to the extension connector pins, but this would require external hardware and would be extremely complex
    Use a baremetal application on the ARM processor (without full Linux), but this still isn't pure "FPGA" control
    Conclusion
    Red Pitaya's architecture fundamentally requires the Linux operating system running on the ARM processors to handle Ethernet communication. The Ethernet hardware is not accessible directly from the FPGA fabric.
    <<<

##.  Missing from FPGA docs:

    - Building Vivado project from scratch (without using the automated scripts) - should work on any Vivado version
    - Constraint files for all boards (.xdc) and which FPGA part is used (aka board file)
    - Building FPGA on Gen 2 boards - za Z10 Gen2 ni treba narediti nič posebnega. Za Z20 Gen2 moraš buildat MODEL=Z20_G2 . Razlika je zaradi E3 konektorja

##.  FPGA examples:

    - Create a basic project (together with Vivado IP cores):
        - ADC frontend
        - DAC frontend
        - PS
        - DAISY connection
        - Signals (IOs, GPIOs, LEDs)
        - DDR interface
        - E3 connection

    Constraint files for boards

    GPIOs and LEDs:

    - LED blink
    - Knight rider
    - PWM on GPIOs
    - Simple UART
    - Simple SPI
    - Board to board connection and communication
    - E3 B2B fast connection

    RF INs:

    - Turn on LED when RF In is more than X Volts
    - Connecting RF INs to GPIOs
    - Capturing data on a trigger
    - Capturing data when trigger + RF IN2 is more than X Volts
    - Decimation
    - Moving average

    RF OUTs:

    - Simple generation on RF OUTs
    - Set bits on RF OUT with GPIOs
    - Generating a sine wave
    - PWM on OUTs (GPIOs)
    - Chainging amplitude
    - Changing frequency
    - Changing phase
    - AWG

    RF IOs:

    - Loopback connection between RF INs and OUTs
    - Adding a delay between RF IN and OUT
    - Simple filter
    - Generate PWM of IN1

    - Frequency counter
    - Simple PID controller on RF INs/OUTs
    - IQ modulation/demodulation
    - Simple Lock-In amplifier

    Interfacing with C++ and Python:
    
    - Creating an FPGA register
    - Reading and writing from registers
    - Stopwatch
    - Interfacing with DDR

    In the prj section of the Github repository https://github.com/RedPitaya/RedPitaya-FPGA, there is a frequency counter. 
    There is an IP in the core section called axis_red_pitaya_dac_v1.0. This appears to take one combined output from a DDS 
    Complier that is configured to create a multiplexed Cosine and SIne output and outputs one to DAC port A and another to 
    DAC port B. 

    It would be useful if the IP could take any two waveforms one from one DDS complier and another from a separate DDS complier. 
    The waveform that could be quite different in nature could be directed to DAC port A or DAC port B as desired. 

    My interests are around the developments of signal processing chains based on Zynq/RedPitaya.
    Example : acquisition of multi-channels, preprocessing in the FPGA, then streaming of I/Q data where I can do Radar / Sonar processing. 

##.  Update the custom component to include 4-Input option and show how to create a pass-through for the ADC and DAC data.



# HARDWARE

##. Current limits - Need to check the FPGA settings (config file) for E3 diff pair current and voltage limits

##. Differential pair voltage levels, comment on resistor values for S1 Link and Orient USB-C lines - these also need to be updated.



# SOFTWARE

##.  UART supports 115200 or higher and CS8. Other settings need a rebuild of the server.

    g_settings.c_cflag &= ~CSIZE;
    g_settings.c_cflag |= CS8 | CLOCAL | CREAD;             /* 8 bits /
    g_settings.c_cflag &= ~CRTSCTS;                         // Disable flow control
    g_settings.c_iflag &= ~(IXON | IXOFF | IXANY);          // Disable XON/XOFF flow control both input & output
    g_settings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // Non Cannonical mode
    g_settings.c_iflag &= ~ICRNL;
    g_settings.c_oflag &= ~OPOST; / raw output */

    g_settings.c_lflag = 0;     //  enable raw input instead of canonical,
    g_settings.c_cc[VMIN] = 1;  // Read at least 1 character
    cfsetspeed(&g_settings, UART_RATE);
    tcsetattr(uart_fd, TCSANOW, &g_settings);

    Rebuilding the server - You need to change the settings in main.cpp and recompile using "make scpi". But it's best not to mess around with it unnecessarily. Not many people really need this functionality, and it's not guaranteed to work reliably. Plus, not all modes are supported by UART.

##. Starting and logging measurements:

    https://forum.redpitaya.com/viewtopic.php?t=27488&sid=2cf977ce7f7246648d40434b21271377


# SCPI & API

##. SCPI BIN mode improvements.

    These commands set the data transfer mode in BIN mode. They do not affect the ASCI mode.
    Now the byte order is big-endian, it also remains the default.
    I added little-endian support, the same as used on RP.
    This allowed us to get rid of data conversion.

    I also worked out the logic of working with memory when transferring data from RP to the client.
    The changes affected both the normal mode and AXI.
    So both modes need to be checked.

    In normal mode, byte order affects BIN - (RAW/VOLT)

    There are some nuances in AXI mode
    There can be 6 types of flag combinations in AXI:
    - (RAW/BIN/BEND) - The data is not copied from memory, but requires transformation.
    - (RAW/BIN/LEND) - Data is not copied from memory, sent as is. (maximum data transfer rate).
    - (RAW/ASCII) - The data is not copied from memory, but requires transformation. (Excessive amount of data as the data is in text format)
    - (VOLT/BIN/BEND) - Data is copied from memory and requires transformation.
    - (VOLT/BIN/LEND) - Data is copied from memory. No conversion is required, but requires enough RAM for an intermediate buffer.
    - (VOLT/ASCII) - Data is copied and formatted. (The slowest data transfer method)

    We have an example that works in any BIN mode, but it can be modified.
    https://github.com/RedPitaya/RedPitaya-Examples/blob/dev/python/acquire_trigger_posedge_axi_bigbuffer.py
    This example shows that transferring a large amount of data requires an interactive data request, since the intermediate buffer on SCPI can be limited by the size of free RAM memory.
    After optimization in RAW mode, you can request the entire buffer. For example, you can request 128MB of data at once.
    For VOLT mode, we still have to request data in portions.

    I also increased the size of the data to read.
    If you read 4096 bytes, the transfer is quite slow.
    https://github.com/RedPitaya/RedPitaya-Examples/commit/95bec06cb4c42e522e696cdd7aa44f2079c45c5b

    On my side I checked the tests. For me, transferring 32MB of data in LEND/RAW/BIN mode took 1-2 seconds.

##.  Simple lessons on Data acquisition and generation - C++ & Python API commands.

##. Move the code examples to GitHub and only link them in the documentation - much easier maintenance.

##. New SCPI server settings. Connecting to Arduino (UART, WiFi, etc.). Create block schemes, etc. Describe the new functionality.


# APPLICATIONS

##.  Update Deep Memory Generation and DAC streaming. Account for the SIGNALlab and update the documentation to mention that as long as the data fits into the DDR, it can be generated at the maximum rate of the board. 
    For example, on the 125-14, you can generate at 125 MS/s as long as the data fits into the DDR. If you want to generate longer waveforms, you need to reduce the sampling rate.

##.  Decoding the Streaming data from the computer on a custom application. How is stream data encoded and how to decode it. - rpsa client, streaming server

##.  Commands to remotely start/stop the stream - explanation so users can perform this on their own - check the rpsa.client code on GitHub for example.

# FORMATING



# LINKS



# OTHER

##. System integrator guide. Add a guide for system integrators who want to use Red Pitaya in their products. This can include information on how to interface with the hardware, how to use the APIs, and best practices for integration.
    Information like open ports on the System

##. Include the Question list information into the docs.

##. GitHub examples:

    Looking at the examples, it looks like we'll have a merge conflict since we've made changes to the main branch.
    Also, I think we should add the ecosystem version it runs on to the title of each example. This is because we currently have a separate repository and no direct connection to the ecosystem version.

    And most likely, you need to add this:
    import lib.redpitaya_scpi as scpi

    https://github.com/RedPitaya/RedPitaya-Examples/tree/dev/python

    Specify the versions of examples (Red Pitaya OS)
    Red Pitaya.
    Python is the simplest there, so I'm not sure there will be any compatibility issues.
    Again, we're not responsible for the client's Python installation.
    If anyone uses older versions of the ecosystem, you need to specify that such and such an example will work with version 2.0-35, and new examples only with 2.07-50, permissible.
    In one folder with examples for the generator there can be examples for the old OS and the new OS




#### Update #####

FPGA testi za simulacijo ob releaseu novega OS - OBVEZNI TESTI pred releasom OS.

Potrebne neke obvezne simulacije za delovanje FPGA.


# eMMC boot image creation

POPIS eMMC

SD kartica daš v pitayo in staraš - startaš uboot in ustaviš

Pogledaš če vidi eMMC - vržeš ven SD akrtico

EMMC vidiš kot Must storage in vpišeš gor kot da bi bil USB ključek




# E3 SW

Add an option to deactivate watchdog timer with a combination of P_ON button.

Add changelog file.

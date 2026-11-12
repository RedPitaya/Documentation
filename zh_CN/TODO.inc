
# FPGA

##. FPGA register access

    As for ARM, accesses to BRAM are even faster than to DDR. (If I remember correctly) Zynq PS treats accesses to BRAM the same as DDR, only it is redirected to a different controller. But since BRAM is essentially on-board memory, it is very fast - much lower latency.
    "Single read" of registers is of course much slower, because each read creates some overhead.

##. FPGA Ethernet

    The Ethernet should be accessible but you have to use the baremetal connection.

    Unfortunately it doesn't work on the normal FPGA + Linux configuration. Ethernet is integrated into the PS part.
    Maybe something could be done if there was a place to connect an additional PHY and then control it from the PL pins. But that would require a HW change on the redpitaya.
    It would be possible to implement an additional PHY directly on the E3 connector of the fast differential line

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

##. AMS - XADC registers are not used (comment them out). We are using Linux driver directly to read the slow analog inputs. The DACs are driven throguh there.




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

##. Are returned values calibrated? How to return uncalibrated values?

    For VOLTS there are two modes:

    If calibration was performed on a FPGA, version 6 parameters; the returned voltage data is always calibrated.
    If other calibration versions are used, you can return the values to volts without calibration.

    For RAW values:

    Same for RAW. For version 6, uncalibrated data can be obtained only by disabling calibration in the EEPROM.



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

##. Add the following explanation to the generation intro:

    I have found the reason behind the original problem. It is quite simple actually (see the attached picture for the explanation). Here is the description:

    Since we are generating a continuous signal, the signal generates continuously regardless of the state of the output (after the trigger it does not matter whether the output is on or off).
    Output turned ON/OFF affects the signal on the actual OUT1 port, but not the internal signal generation in the FPGA. Turning the output OFF after generating the signal will cut the signal on the actual output, but will not stop the internal generation. Think of it as switching the output to High-Z mode. The FPGA will continue to generate the signal.
    Generator reset will clear all settings and stop the generation of the continuous signal, which explains why it solves the problem here and produces the expected output.
    Without generator reset, the sequence is as follows:
    First iteration, we setup the generator and trigger the generation. Since there was no previous signal generated, the acquired data is as expected.
    Second and further iterations, we turn off the output (internally, the FPGA still generates the signal) and we reconfigure the generator to exactly the same specs. There is another important aspect here corelated to triggering itself, which I will explain later on.
    Then we start the acquisition and specify the trigger as "immediate acquisition trigger".
    Since the output is turned off at this point, the acquisition starts capturing data without the output signal present, resulting in a short zero data line in the results (see the trig_now picture).
    Then the output is turned ON, resulting in the output immediately jumping to whatever state it was in (not necessarily starting at 0).
    The generation continuous for a short time before the Generator trigger command arrives (non-zero network and processing delay). The generator trigger does the following:
    Immediately resets the internal waveform generation counter to 0 - starting the generation from 0.
    Applies any configured settings to the waveform (change in amplitude, frequency waveform, etc.)
    Since the settings are the same, the trigger will only reset the read pointer of the arbitrary waveform generation to the start of the internally saved waveform (since this is a sine waveform, the first sample is always 0), resulting in the jump in the waveform.
    This can clearly be seen by setting the trigger level to a non-zero value and setting the acquisition trigger to CH1_PE. This actually shows that the acquisition triggers before the actual jump in value. So, this is not a glitch in acquisition or data collection, but rather a reset of the generation.
    With generator reset, the FPGA resets the generation completely in between iterations, so the generation starts with the trigger and not with turning on the output on the second and later generations.
    This behaviour is visible since we are generating a continuous waveform and would not be so obvious with a burst waveform generation.


    A few other important but easily missed things that can be relevant:

    SOUR:TRig:INT command will reset the generated waveform to the start and clear the generator read counter (resets the FPGA generation), while SOUR:TRig:INT:ONLY will apply the generator trigger, but will NOT reset the generator read counter, resulting in a smooth transition between different settings (for example changing frequency of the generated signal on the fly)

##.  Simple lessons on Data acquisition and generation - C++ & Python API commands.

##. Move the code examples to GitHub and only link them in the documentation - much easier maintenance.

##. New SCPI server settings. Connecting to Arduino (UART, WiFi, etc.). Create block schemes, etc. Describe the new functionality.

##. Command table cleanup and per-command detail sections.

    The current command tables mix three distinct types of entries that should be handled differently:

    1. **Truly deprecated commands** (e.g. Python list-based acquisition functions replaced by NumPy buffer variants):
       Move these out of the main table into a collapsed ``.. dropdown::`` section (from sphinx-design) at the
       bottom of each functional group, styled with ``:color: warning``. The dropdown is collapsed by default,
       keeping the main table clean while preserving legacy information for users on older OS versions.

    2. **Version-additive variants** (e.g. ``ACQ:DEC`` vs ``ACQ:DEC:CH<n>`` for split trigger mode):
       These coexist and are NOT replacements. Keep them in the same table but add a thin visual separator row
       between the base command and its per-version additions to make the grouping visually clear.

    3. **Board-limited commands** (e.g. SIGNALlab 250-12 only, STEMlab 125-14 4-Input only):
       No structural change needed — description column already handles this adequately.

    Priority: start with (1) as it requires no new files, no link changes, and immediately reduces main-table clutter.
    The ``.. dropdown::`` directive requires the ``sphinx-design`` extension (check conf.py).

##. Per-command prose sections and GitHub example linking.

    Within each existing ``commands-*.rst`` file, add a short prose section above each logical command group
    (e.g. one section for the entire decimation group, not one per command). The section should explain
    *behaviour and intent* — how the commands relate, when to use which variant, and key constraints or gotchas.
    Do NOT duplicate parameter ranges or types already present in the "Parameter options" block.

    Link to runnable code on GitHub rather than embedding code blocks in the docs. This way examples can be
    tested and updated without touching RST files. Link to the **folder level** where possible, or use a
    version-tagged permalink rather than ``main``/``master`` to avoid link rot:

    ``https://github.com/RedPitaya/RedPitaya-Examples/tree/v2.07-48/python/acquisition/``

    The resulting three-layer structure per command group:

    - **Table** — quick syntax lookup (existing, unchanged)
    - **Prose section** — behaviour, intent, relationships between commands (new, short)
    - **GitHub link** — runnable examples (external, no maintenance burden in docs)

##. New acquisition functions based on interrupts. These functions avoid the usual polling method and instead rely on interrupts to signal when the trigger condition is met and when the data is ready.
    This allows for more efficient data acquisition, as the CPU can perform other tasks while waiting for the trigger condition to be met. The functions block the thread execution until the interrupt condition is met
    or when the timeout is reached. While not directly allowing for non-blocking acquisition, they can be used in a separate thread to achieve a similar effect.

##. Add Logic Analyzer commands to the documentation. The base is there, but most commands are missing.

##. Add calibration commands to the documentation (C++ and Python API).

##. Add link to system info change of DMM memory to the DMM docs (changing reserved memory)

##. DMG - For one-pack mode, the data-pack must be at least twice the size of the number of samples in the generated waveform otherwise the waveform will not be generated correctly.
          The waveform must still fit inside the DDR memory.

        To avoid problems with flat regions between generated waveforms (very small buffer), increase the buffer size to 128-256 kB. One-pack mode eliminates unnecessary data transfer over the network, but the logic of two buffers still remains. Essentially, after the first buffer is generated, we swap the address for the second buffer with the first. Due to the slow speed of swapping buffers, we experience some delay in signal generation.
        To avoid this delay, the buffer needs to be large enough. Alternatively, the FPGA can be modified to allow the one-pack mode to operate inside the FPGA itself (independent of RAM)

        When streaming data in 8-bit mode, the data only has 256 possible values, which can lead to flat regions in the generated wavefrom (conversion from float to int8). Especially if the waveform itself is very long (for example a single sine wave in a 1 MSample buffer). When generating such a waveform, 
        it will likely have a small flat zero region in the middle of the sine wave.

##. DMA - trigger delay: It works the same as in normal mode. The buffer is circular. Data is written in a loop. As soon as a trigger occurs, the number of samples after the trigger specified in the delay is written.

    We get a pointer to the trigger sample.

    https://github.com/RedPitaya/RedPitaya-Examples/blob/main/C/axi.cpp#L98

    There is also a function
    /**
    Returns current position of AXI ADC write pointer.
    @param channel channel index
    @param pos Write pointer position
    @return If the function is successful, the return value is RP_OK.
    If the function is unsuccessful, the return value is any of RP_E* values ​​that indicate an error.
    /
    int rp_AcqAxiGetWritePointer(rp_channel_t channel, uint32_t pos);
    The difference between them should be equal to trigger delay


    Use the write pointer instead of the trigger pointer when looking to return data in the correct chronological order when trig_dly != samples_per_channel.




# APPLICATIONS

##.  Update Deep Memory Generation and DAC streaming. Account for the SIGNALlab and update the documentation to mention that as long as the data fits into the DDR, it can be generated at the maximum rate of the board. 
    For example, on the 125-14, you can generate at 125 MS/s as long as the data fits into the DDR. If you want to generate longer waveforms, you need to reduce the sampling rate.

##.  Decoding the Streaming data from the computer on a custom application. How is stream data encoded and how to decode it. - rpsa client, streaming server

##.  Commands to remotely start/stop the stream - explanation so users can perform this on their own - check the rpsa.client code on GitHub for example.

##.  VNA - add specifications: Bandwidth, measurement types (s-parameters, TDR/time domain, crosstalk (NEXT/FEXT)), diffferential pair support, return loss/insertion loss, port count, calibration support, accessories, software.
     Check the VNA specifications and find the specified parameters to publish.
     RF bandwidth is 300 kHz-60 MHz, S11/S21 measurements, 1 port, calibration support (manual Red Pitaya hardware calibration and software VNA calibration), 

##. SA - revise the measurements for SA for different boards



# QUICKSTART

##. Alucase Gen 2 update - add info on backdrilling the Gen 2 alu case to get access to different parts of the Red Pitaya board (for example, DIN holes, etc.). Pictures!



# FORMATING



# LINKS



# OTHER

##. System integrator guide. Add a guide for system integrators who want to use Red Pitaya in their products. This can include information on how to interface with the hardware, how to use the APIs, and best practices for integration.
    Information like open ports on the System

##. Include the Question list information into the docs.

##. GitHub examples:

    Also, I think we should add the ecosystem version it runs on to the title of each example. This is because we currently have a separate repository and no direct connection to the ecosystem version.


    https://github.com/RedPitaya/RedPitaya-Examples/tree/dev/python

    Specify the versions of examples (Red Pitaya OS)
    Red Pitaya.
    Python is the simplest there, so I'm not sure there will be any compatibility issues.
    Again, we're not responsible for the client's Python installation.
    If anyone uses older versions of the ecosystem, you need to specify that such and such an example will work with version 2.0-35, and new examples only with 2.07-50, permissible.
    In one folder with examples for the generator there can be examples for the old OS and the new OS

##. Update Nightly Build instructions (on the server) to reflect the latest changes.




#### Update #####

FPGA tests for simulation at the release of a new OS - MANDATORY TESTS before the release of the OS.

Some mandatory simulations are needed for the operation of the FPGA.







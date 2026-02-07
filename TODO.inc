

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




# HARDWARE

##. Current limits - Need to check the FPGA settings (config file) for E3 diff pair current and voltage limits

##.  Add Calibration section to hardware docs of each board - linking to the calib command line tool and the calibration util. Add a special calibration page which includes links all the options.

##.  Add output coupling to technical documentation tables



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

##. Invalid EEPROM values

    The new NB (680 and higher) display a warning icon if the EEPROM value is invalid.

##. Synchronising multiple SIGNALlab 250-12 boards:

    There are three steps to synchronising multiple 250-12 units:
    
    1. Connect an external 10 MHz reference clock to the SMA connector in the back.
    2. Connect the external trigger signal to the middle BNC connector
    3. Start the PLL synchronisation on the SIGNALlab boards by running the following commands: https://redpitaya.readthedocs.io/en/latest/appsFeatures/remoteControl/command_list/commands-pll.html#phase-locked-loop

    The easiest would be to have the C++ or Python API script executed during the boot, by adding it to the stratup.sh routine: https://redpitaya.readthedocs.io/en/latest/appsFeatures/remoteControl/API_scripts.html#running-applications-at-boot

##. Kernel Panic

    Happens when a program corrupts memory or accesses invalid memory. This can be due to bugs in the program, hardware issues, or conflicts between different software components.
    Please reinstall the latest version of the official Red Pitaya OS and check if the problem persists. If it does, please contact us.



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

##.  Converting RAW to Volts and plotting on the computer.

    It all depends on the board you're capturing on. If you're using a 125-14 board, you need to divide the values ​​by 8192.
    If the resolution is different, divide accordingly. Keep in mind that the RAW data is likely uncalibrated.

##.  Simple lessons on Data acquisition and generation - C++ & Python API commands.

##. Move the code examples to GitHub and only link them in the documentation - much easier maintenance.

##. New SCPI server settings. Connecting to Arduino (UART, WiFi, etc.). Create block schemes, etc. Describe the new functionality.

##. Debug files from inside Red Pitaya: Run the following script /opt/redpitaya/sbin/scripts/bug_report.sh


# APPLICATIONS

##.  LA API does not crash on STEMlab 125-10 with the latest OS - software issues

##. Calibration - Calibration is now performed without the FPGA filter. Filter must be calibrated separately.
    Proper calibration proceedure:
        1. Reset frequency calibration filter to default values
        2. Perform DC calibration
        3. Perform frequency calibration
        4. Perform DC calibration again to account for the frequency calibration changes

    Gen 2 boards do not use the FPGA equalisation filter for calibration - it is disabled by default (do not frequency calibrate Gen 2 boards).

##.  Oscilloscope - I added an implicit feature to scopegenpro: if you select a channel, hold Shift, and turn the wheel, you can scale along the Y axis.
    Also, selecting the cursor on the left changes the active channel.

    Update the application docs with the new functionality:
    - Interpolation
    - Tracing

##.  Info buttom - system settings. Being able to enter the actual Sampling Rate of the External clock into the GUI. Currently the GUI assumes that I am clocking my RP with a 122.880 MS/s clock. 
    I am using the EXT Clock version of the 16 bits ADC board (STEM-122). In terms of precision, I would appreciate if I could enter up to a very high resolution (i.e. 80.12345678 MHz). 
    This feature is quite important to me because currently all the Measurement Parameters in the GUI are calculated assuming the sampling clock is 122.880 MS/s.

    The clock rate setting in the system menu has been improved.
    This setting overrides the value in the profile, and all applications and modules will use this value instead of the default.

##.  Decoding the Streaming data from the computer on a custom application. How is stream data encoded and how to decode it. - rpsa client, streaming server

##.  Commands to remotely start/stop the stream - explanation so users can perform this on their own - check the rpsa.client code on GitHub for example.

##.  Running multiple applications:

    Technically, you can run the oscilloscope and Jupyter.
    But you need to be careful.
    Running one web module in exclusive mode is done to avoid conflicts with the FPGA. This limitation is artificial.
    You can run Jupyter and the oscilloscope, but keep in mind that Jupyter code must not interfere with the oscilloscope and must not reboot the FPGA (otherwise, the board will most likely freeze).
    The initialization code must also be modified.

    See the screenshot
    https://drive.google.com/file/d/18QP0DO ... sp=sharing

    This function initializes memory access, but does not reset the settings in the FPGA.
    rp.rp_InitReset(False)

    It is also possible to execute code from the console simultaneously with the oscilloscope.

##.  SDR on macOS and Red Pitaya

    Software Defined Radio (SDR) clients on macOS expect a specific connection protocol and device profile. Red Pitaya's SDRLab (and the SDR applications provided for Red Pitaya) expose HPSDR/Metis-compatible streams (Hermes/Metis protocol) and also can be accessed by clients that support ExtIO/plug‑ins or by using a bridge that translates the Red Pitaya stream to a more widely supported interface. On macOS the ecosystem is smaller than on Windows/Linux and compatibility depends on the exact client supporting Hermes/Metis or having a plugin/bridge. Because you’re not an SDR stack expert (and that helps me explain things better!), here’s the practical background and options.

    Short summary of likely issues you’re seeing

    Many Mac SDR clients (SDR++, Gqrx, SparkSDR/Spark++) don’t natively speak Hermes/Metis. They either need an ExtIO-like plugin (Windows), a native Hermes client, or a network bridge.
    SparkSDR expecting Hermes2 Lite or different server handshake can fail to find the Red Pitaya if the server’s handshake/version differs.
    Inconsistent behavior (works once, then crashes) often points to mismatched protocol versions, unstable/old client builds, or a network/OS-level websocket/socket issue on macOS.
    SDR++ currently lacks a built-in Hermes/Metis connector plugin by default on macOS (as you noted).
    What you can try — practical options (ordered easiest → advanced)

    Use a Hermes/Metis-capable client that’s known to work with Red Pitaya (recommended)
    PowerSDR mRX (Windows) and ghpsdr3-alex (Linux) are known to work reliably. On macOS you can run a Linux VM or use a remote Linux PC to host ghpsdr3-alex or a Hermes bridge and then connect macOS SDR clients to that.
    Link with more info: https://redpitaya.readthedocs.io/en/lat ... tx_rx.html (section lists compatible clients)
    Run ghpsdr3-alex or Hermes server on a Linux machine (or VM) and use it as a network bridge
    Install ghpsdr3-alex on a Linux host (or a Linux VM on your Mac). Configure it to connect to the Red Pitaya (Hermes/Metis) and it will act as a server that many clients can connect to. This avoids protocol mismatch on macOS clients.
    Red Pitaya notes and client list: https://pavel-demin.github.io/red-pitaya-notes/ and the HPSDR/Metis protocol docs: https://raw.githubusercontent.com/TAPR/ ... _V1.33.pdf
    Use a Windows VM or small Windows machine to run PowerSDR or ExtIO bridge, then stream audio/IQ to macOS
    PowerSDR with the Red Pitaya/HAMlab edition is known to work. You can run it in a Windows VM (Parallels/VMware/VirtualBox) and then either do remote desktop or stream the IQ to macOS. This is clunkier but often works when mac-native clients fail.
    PowerSDR download and setup: https://redpitaya.readthedocs.io/en/lat ... tx_rx.html (PowerSDR mRX PS link and setup steps)
    Use a dedicated Hermes→SoapySDR / Hermes→RTLSDR bridge or write a small bridge to expose a SoapySDR or network sink
    SDR++ supports SoapySDR backends. If you can run a bridge that exposes Red Pitaya’s Hermes/Metis stream via SoapySDR, SDR++ can use it. There isn’t an official Hermes→Soapy bridge in the Red Pitaya docs, but community tools or a small wrapper (using libmetis or ghpsdr3 code) can be made to re-publish IQ as Soapy or as a local virtual device.
    If you want to go down this route I can sketch how to build a Hermes→Soapy bridge (requires building SoapySDR plugin skeleton and using libmetis/udp client to receive IQ). Warning: this is advanced and requires Linux/macOS build toolchain knowledge.
    HPSDR/Metis protocol doc: https://raw.githubusercontent.com/TAPR/ ... _V1.33.pdf
    Try Spark++ / SparkSDR troubleshooting (quick checks)
    Confirm the Red Pitaya SDR application is running and exposing the Metis/Hermes server on the expected port (default Hermes/Metis port commonly 4010/50000 depending on server). Use netstat/lsof to verify listening ports.
    Ensure firewall/websocket settings on your macOS allow the outgoing connection. macOS content/privacy settings sometimes block websockets (see known issues in docs).
    Try different Hermes models in Spark (Hermes, Hermes Lite 2) — version mismatch can break discovery. If one model worked once, check the server logs on Red Pitaya to capture the handshake. Reproduce with logging enabled in Spark.
    Reinstalling may not help if crash is caused by mismatched protocol or corrupted configuration file — try clearing Spark’s config/preferences between reinstalls.
    Red Pitaya known issues and connection notes: https://redpitaya.readthedocs.io/en/lat ... ssues.html
    Use Gqrx with an intermediary (if Gqrx unstable connecting directly)
    Gqrx can be used if you run a Soapy/OsmoSDR backend that presents the Red Pitaya as a local device. Same bridge idea as for SDR++.
    Which approach I recommend first

    If you want the least development overhead: run ghpsdr3-alex or a small Linux VM on your Mac or a nearby Linux box, connect it to the Red Pitaya (Hermes/Metis), and then use an SDR client on macOS that can talk to ghpsdr3-alex or use remote display. This has the best chance of stable operation.
    If you prefer SDR++ specifically: create or use a Hermes→SoapySDR bridge so SDR++ can see Red Pitaya as a Soapy device. I can help draft the bridge steps or point to community code if available.


    Helpful links (from our docs and community):
    Red Pitaya SDR transceiver / receiver docs and list of compatible clients: https://redpitaya.readthedocs.io/en/lat ... tx_rx.html
    HPSDR / Metis protocol (how Hermes speaks): https://raw.githubusercontent.com/TAPR/ ... _V1.33.pdf
    Pavel Demin’s Red Pitaya Notes (community SDR tools & instructions): https://pavel-demin.github.io/red-pitaya-notes/
    Known software issues (mac direct connection, websockets): https://redpitaya.readthedocs.io/en/lat ... ssues.html



# FORMATING

##.  Fix the spacing in between Index links. Index should have depth 1 and not 2 - makes it easier for users to read.



# OTHER

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



POPIS eMMC

SD kartica daš v pitayo in staraš - startaš uboot in ustaviš

Pogledaš če vidi eMMC - vržeš ven SD akrtico

EMMC vidiš kot Must storage in vpišeš gor kot da bi bil USB ključek




E3 SW

Popravi E3 SW za deaktivacijo watchdog timerja.

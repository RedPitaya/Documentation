
1. FPGA register access

    Kar se tiče ARMa, so dostopi do BRAM še hitrejši kot do DDR. (Če se prav spomnim) Zynq PS dostope do BRAM tretira enako kot DDR, samo da se preadresira na drug kontroler. Ker pa je BRAM v bistvu on board spomin, je zelo hiter - dosti manjše latence. 

    "Single read" registrov je pa seveda dosti počasnejši, ker vsako branje ustvari nekaj overhead-a.

2. Include the Question list information into the docs.

3. FPGA Ethernet

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

4. Calibration - no 50 Ohm termination for calibrating Gen 2 boards. Calibration is performed without the FPGA filter. Filter must be calibrated separately.

5. Current limits - +5 V depends on the FPGA current (it will be hard to get more than 1 A). Also depends on the specific usecase. The FPGA + periphery eat about 1.5 A, the host can also eat 1.5 A.
                    Need to check the FPGA settings (config file) for E3 diff pair current and voltage limits
                    3V3 and -5V need to be checked.

6. Update datasheets with the following information:
    Add colums with Parameters/Items, Units, specifications

    - Environment specifications:
        Operating Environmental Conditions:     - Temperature - 0-55 degrees
                                                - Humidity - < 90%RH
        Storage Environmental Conditions:       - Temperature - -20-85 degrees
                                                - Humidity - < 90%RH
    - Basic:
        Size (L x W x H) in mm

7. SCPI BIN mode improvements.

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

8. GitHub examples:

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
    
9. Letter of Volatility - add the wipe command for EEPROM user space. Done - add to docs.

    SIZE=$(cat /sys/devices/soc0/axi/e0004000.i2c/i2c-0/0-0050/eeprom | wc -c)
    dd if=/dev/zero of=/sys/devices/soc0/axi/e0004000.i2c/i2c-0/0-0050/eeprom bs=1 count=$SIZE

10. Oscilloscope - I added an implicit feature to scopegenpro: if you select a channel, hold Shift, and turn the wheel, you can scale along the Y axis.
    Also, selecting the cursor on the left changes the active channel.

    Update the application docs with the new functionality:
    - Interpolation
    - Tracing

11. Being able to enter the actual Sampling Rate of the External clock into the GUI. Currently the GUI assumes that I am clocking my RP with a 122.880 MS/s clock. 
    I am using the EXT Clock version of the 16 bits ADC board (STEM-122). In terms of precision, I would appreciate if I could enter up to a very high resolution (i.e. 80.12345678 MHz). 
    This feature is quite important to me because currently all the Measurement Parameters in the GUI are calculated assuming the sampling clock is 122.880 MS/s.

    The clock rate setting in the system menu has been improved.
    This setting overrides the value in the profile, and all applications and modules will use this value instead of the default.

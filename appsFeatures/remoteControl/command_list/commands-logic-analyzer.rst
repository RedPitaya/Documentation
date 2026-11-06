.. _commands_logic_analyzer:

###################
Logic Analyzer
###################

Logic Analyzer (LA) commands allow interaction with the Logic Analyzer functionality on the Red Pitaya platform. They enable users to configure, start, stop, 
and retrieve data from the GPIO pins using the Logic Analyzer.



Functionality overview
========================

The Logic Analyzer is currently controllable only on the API level. It works through the ``CLAController`` and ``CLACallback`` classes, which provide methods 
for configuring the analyzer, setting triggers, starting and stopping data acquisition, and retrieving captured data. The data is captured and saved in the 
``OutputPacket`` structure.

* ``CLACallback`` is a callback interface for controlling the response to Logic Analyzer events. It is called whenever the data is captured by the FPGA, a block 
  of data is uploaded by the user, has been decoded, or after the board has finished decoding the captured data.
* ``CLAController`` is the main interface for controlling the Logic Analyzer. It provides methods for configuring the analyzer, setting triggers, starting and 
  stopping data acquisition, and retrieving captured data.

|

Important notes
================

The SCPI column is intentionally empty, as there are no SCPI commands for the Logic Analyzer yet. The C++ functions are in the ``rp_la`` namespace. The Python functions have the same
names and arguments as the C++ ones, except for the differences listed below:

* NumPy buffer functions (``getDataNP``, ``getUnpackedRLEDataNP``, ``decodeNP``, ``printRLENP``) take the NumPy array only; its size is determined automatically.
* ``wait(timeoutMs)`` returns ``True`` on timeout in Python, while C++ returns the result through the ``isTimeout`` pointer argument.
* Functions that return decoded data (``getDecodedData``, ``decode``, ``decodeNP``) return a list of dictionaries (one per ``OutputPacket``) in Python.
* Callbacks are implemented by inheriting from ``rp_la.CLACallback`` and passing the object to ``setDelegate(callback.__disown__())``.

|

Code examples
=================

Here are some examples of how to use the Logic analyzer commands on Red Pitaya:

* :ref:`Digital communication examples <examples_digcom>`.

|

Parameters and command tables
=============================

Output packet format
-----------------------

The decoders return the decoded data as a list of ``OutputPacket`` structures (``rp_la::OutputPacket``). Each packet describes one recognized block of the decoded protocol 
(for example a UART byte, an I2C address or a CAN CRC). In Python, each packet is a dictionary with the same keys as the structure members (e.g., ``decode[index]['control']``).

.. list-table::
    :widths: 18 14 68
    :header-rows: 1

    * - Member
      - Type
      - Description
    * - ``line_name``
      - string
      - Name of the protocol line the data was decoded from (for example RX, TX, MOSI, MISO, SDA). Only lines specified in the decoder settings are listed.
    * - ``control``
      - uint8
      - Data identifier. Use it with ``getAnnotation(decoder, control)`` to get the text annotation of the packet, or ``getAnnotationList(decoder)`` to get all annotations of the decoder.
    * - ``data``
      - uint32
      - Data contained in the protocol block (for example ID, DATA, CRC).
    * - ``bitsInPack``
      - float
      - Number of recognized data bits. A multiple of 0.5 (0, 0.5, 1, 1.5, 2, ...).
    * - ``sampleStart``
      - double
      - Start position of the block in samples (0 = first sample, 1 = second sample, ...). The value is not an integer, since the bit width can be non-integer depending on the protocol.
    * - ``length``
      - double
      - Length of the recognized block in samples.

Example of reading the packets in Python:

.. code-block:: python

    decode = rp_cla.getDecodedData("UART")
    for packet in decode:
        print(rp_cla.getAnnotation(rp_la.LA_DECODER_UART, packet['control']), "=", packet)

|

CLAController commands
-----------------------

``CLAController`` is the main interface for configuring the Logic Analyzer, running the capture and retrieving or decoding data.

**Parameter options:**

- ``<la_decoder> = {LA_DECODER_NONE, LA_DECODER_CAN, LA_DECODER_I2C, LA_DECODER_SPI, LA_DECODER_UART}`` (Logic Analyzer decoder type). Default ``LA_DECODER_NONE``
- ``<la_trigger> = {LA_ERROR, LA_NONE, LA_LOW, LA_HIGH, LA_RISING, LA_FALLING, LA_RISING_OR_FALLING}`` (Logic Analyzer trigger type). Default ``LA_NONE``
- ``<la_trig_channel> = {LA_T_CHANNEL_1, ... , LA_T_CHANNEL_8}`` (Logic Analyzer trigger channel number).
- ``<la_mode> = {LA_BASIC, LA_PRO}`` (Logic Analyzer mode). ``LA_BASIC`` is used without an external logic analyzer unit, ``LA_PRO`` when the extension module is connected.

**Available Jupyter and API macros:**

- *(Future OS release)*


**Setup and trigger**

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``CLAController()``
        | Python: ``CLAController()``
      - Creates the controller object. Release the resources with ``del`` in Python.
      - 3.00-57 and up
    * -
      - | C++: ``bool initFpga()``
        | Python: ``initFpga()``
      - Initializes the FPGA registers and the reserved memory area.
      - 3.00-57 and up
    * -
      - | C++: ``void setMode(la_Mode_t mode)``
        | Python: ``setMode(mode)``
      - Sets the operating mode with or without an external unit. Affects only data capture from the FPGA.
      - 3.00-57 and up
    * -
      - | C++: ``void setTrigger(la_Trigger_Channel_t channel, la_Trigger_Mode_t mode)``
        | Python: ``setTrigger(channel, mode)``
      - Sets the trigger for the FPGA. Valid channels are 0 to 7 (``LA_T_CHANNEL_1`` to ``LA_T_CHANNEL_8``). ``LA_RISING``, ``LA_FALLING`` and ``LA_RISING_OR_FALLING`` can be used on one line only.
        ``LA_LOW`` and ``LA_HIGH`` can be combined with an edge trigger (e.g., in SPI: CS = ``LA_LOW``, CLK = ``LA_RISING_OR_FALLING``).
      - 3.00-57 and up
    * -
      - | C++: ``la_Trigger_Mode_t getTrigger(la_Trigger_Channel_t channel)``
        | Python: ``getTrigger(channel)``
      - Returns the trigger setting for the specified channel.
      - 3.00-57 and up
    * -
      - | C++: ``bool isNoTriggers()``
        | Python: ``isNoTriggers()``
      - Returns true if triggers on all channels are set to ``LA_NONE``.
      - 3.00-57 and up
    * -
      - | C++: ``void resetTriggers()``
        | Python: ``resetTriggers()``
      - Sets triggers on all channels to ``LA_NONE``.
      - 3.00-57 and up
    * -
      - | C++: ``bool softwareTrigger()``
        | Python: ``softwareTrigger()``
      - Sends a trigger signal to the FPGA. Only makes sense during data capture on the FPGA, when the user wants to stop waiting for the trigger.
      - 3.00-57 and up

|

**Acquisition settings**

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``bool setEnableRLE(bool enable)``
        | Python: ``setEnableRLE(enable)``
      - Enables recording the data in the FPGA in RLE format; otherwise the data is recorded through DMA without compression. Decoders only work with RLE data.
        RLE: ``data[i]`` = sample count + 1, ``data[i+1]`` = GPIO data (8 bits = 8 lines). No RLE: ``data[i]`` = sample *i*.
      - 3.00-57 and up
    * -
      - | C++: ``bool isRLEEnable()``
        | Python: ``isRLEEnable()``
      - Returns whether RLE mode is enabled.
      - 3.00-57 and up
    * -
      - | C++: ``void setDecimation(uint32_t decimation)``
        | Python: ``setDecimation(decimation)``
      - Sets the decimation used when capturing data with the FPGA.
      - 3.00-57 and up
    * -
      - | C++: ``uint32_t getDecimation()``
        | Python: ``getDecimation()``
      - Returns the decimation.
      - 3.00-57 and up
    * -
      - | C++: ``void setPreTriggerSamples(uint32_t value)``
        | Python: ``setPreTriggerSamples(value)``
      - Sets the number of samples the FPGA must write before the trigger.
      - 3.00-57 and up
    * -
      - | C++: ``uint32_t getPreTriggerSamples()``
        | Python: ``getPreTriggerSamples()``
      - Returns the number of pre-trigger samples.
      - 3.00-57 and up
    * -
      - | C++: ``void setPostTriggerSamples(uint32_t value)``
        | Python: ``setPostTriggerSamples(value)``
      - Sets the number of samples the FPGA records after the trigger.
      - 3.00-57 and up
    * -
      - | C++: ``uint32_t getPostTriggerSamples()``
        | Python: ``getPostTriggerSamples()``
      - Returns the number of post-trigger samples.
      - 3.00-57 and up
    * -
      - | C++: ``uint32_t getDMAMemorySize()``
        | Python: ``getDMAMemorySize()``
      - Returns the size of the reserved DMA memory in bytes. Without compression 1 sample equals 1 byte. With RLE the amount of data depends on the signal (for 1 MB of memory: 512k samples in the worst case, 131M samples in the best case).
        Take this into account when setting the pre/post trigger samples, as the buffer is circular and the data can overlap.
      - 3.00-57 and up

|

**Decoders**

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``bool addDecoder(std::string name, la_Decoder_t decoder)``
        | Python: ``addDecoder(name, decoder)``
      - Adds a decoder of the specified type under the specified name.
      - 3.00-57 and up
    * -
      - | C++: ``std::vector<std::string> getDecoders()``
        | Python: ``getDecoders()``
      - Returns the list of decoder names added by the user.
      - 3.00-57 and up
    * -
      - | C++: ``bool isDecoderExist(std::string name)``
        | Python: ``isDecoderExist(name)``
      - Checks if the specified decoder is installed.
      - 3.00-57 and up
    * -
      - | C++: ``la_Decoder_t getDecoderType(std::string name)``
        | Python: ``getDecoderType(name)``
      - Returns the decoder type for the specified name.
      - 3.00-57 and up
    * -
      - | C++: ``void setDecoderEnable(std::string name, bool enable)``
        | Python: ``setDecoderEnable(name, enable)``
      - Enables or disables the decoder. A disabled decoder is not used to decode data after a capture or after loading data.
      - 3.00-57 and up
    * -
      - | C++: ``bool getDecoderEnable(std::string name)``
        | Python: ``getDecoderEnable(name)``
      - Returns the decoder status (enabled or disabled).
      - 3.00-57 and up
    * -
      - | C++: ``bool removeDecoder(std::string name)``
        | Python: ``removeDecoder(name)``
      - Removes the specified decoder.
      - 3.00-57 and up
    * -
      - | C++: ``void removeAllDecoders()``
        | Python: ``removeAllDecoders()``
      - Removes all decoders.
      - 3.00-57 and up
    * -
      - | C++: ``std::vector<OutputPacket> getDecodedData(std::string name)``
        | Python: ``getDecodedData(name)``
      - Returns the decoded data of the specified decoder. See `Output packet format`_.
      - 3.00-57 and up
    * -
      - | C++: ``bool setDecoderSettings(std::string name, std::string json)``
        | Python: ``setDecoderSettings(name, json)``
      - Sets the settings of the specified decoder in JSON format.
      - 3.00-57 and up
    * -
      - | C++: ``std::string getDecoderSettings(std::string name)``
        | Python: ``getDecoderSettings(name)``
      - Returns the settings of the specified decoder in JSON format.
      - 3.00-57 and up
    * -
      - | C++: ``std::string getDefaultSettings(la_Decoder_t decoder)``
        | Python: ``getDefaultSettings(decoder)``
      - Returns the default settings of the specified decoder type. Each decoder has its own set of keys.
      - 3.00-57 and up
    * -
      - | C++: ``bool setDecoderSettingsUInt(std::string name, std::string key, uint32_t value)``
        | Python: ``setDecoderSettingsUInt(name, key, value)``
      - Sets an unsigned integer setting of the decoder by key. Keys are taken from the JSON settings. Returns false if the key is not found.
      - 3.00-57 and up
    * -
      - | C++: ``bool setDecoderSettingsFloat(std::string name, std::string key, float value)``
        | Python: ``setDecoderSettingsFloat(name, key, value)``
      - Sets a float setting of the decoder by key. Returns false if the key is not found.
      - 3.00-57 and up
    * -
      - | C++: ``bool setDecoderSettingsString(std::string name, std::string key, std::string value)``
        | Python: ``setDecoderSettingsString(name, key, value)``
      - Sets a string setting of the decoder by key. Returns false if the key is not found.
      - 3.00-57 and up
    * -
      - | C++: ``bool getDecoderSettingsUInt(std::string name, std::string key, uint32_t* value)``
        | Python: ``getDecoderSettingsUInt(name, key)``
      - Returns the unsigned integer setting for the specified key. Returns false if the key is not found.
      - 3.00-57 and up
    * -
      - | C++: ``bool getDecoderSettingsFloat(std::string name, std::string key, float* value)``
        | Python: ``getDecoderSettingsFloat(name, key)``
      - Returns the float setting for the specified key. Returns false if the key is not found.
      - 3.00-57 and up
    * -
      - | C++: ``bool getDecoderSettingsString(std::string name, std::string key, std::string* value)``
        | Python: ``getDecoderSettingsString(name, key)``
      - Returns the string setting for the specified key. Returns false if the key is not found.
      - 3.00-57 and up
    * -
      - | C++: ``std::map<uint8_t, std::string> getAnnotationList(la_Decoder_t decoder)``
        | Python: ``getAnnotationList(decoder)``
      - Returns all annotations (control value to text) of the specified decoder type.
      - 3.00-57 and up
    * -
      - | C++: ``std::string getAnnotation(la_Decoder_t decoder, uint8_t control)``
        | Python: ``getAnnotation(decoder, control)``
      - Returns the annotation text for the ``control`` value of an ``OutputPacket``.
      - 3.00-57 and up

|

**Capture, decode and data access**

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``void setDelegate(CLACallback* callbacks)``
        | Python: ``setDelegate(callback.__disown__())``
      - Sets the object with the callback functions. See `CLACallback commands`_.
      - 3.00-57 and up
    * -
      - | C++: ``void removeDelegate()``
        | Python: ``removeDelegate()``
      - Removes the callback object.
      - 3.00-57 and up
    * -
      - | C++: ``bool isCaptureRun()``
        | Python: ``isCaptureRun()``
      - Shows whether data capture is running.
      - 3.00-57 and up
    * -
      - | C++: ``void runAsync(uint32_t timeoutMs)``
        | Python: ``runAsync(timeoutMs)``
      - Starts capturing data from the FPGA asynchronously and decodes the captured data. A timeout of 0 means no timeout.
      - 3.00-57 and up
    * -
      - | C++: ``void runAsync(std::vector<uint8_t> data, bool isRLE, uint64_t triggerSamplePosition)``
        | Python: ``runAsync(data, isRLE, triggerSamplePosition)``
      - Asynchronously decodes user data.
      - 3.00-57 and up
    * -
      - | C++: ``void decodeAsync()``
        | Python: ``decodeAsync()``
      - Asynchronously decodes data captured with the FPGA or loaded with ``loadFromFile``.
      - 3.00-57 and up
    * -
      - | C++: ``void wait(uint32_t timeoutMs, bool* isTimeout)``
        | Python: ``wait(timeoutMs)``
      - Waits for the asynchronous function to complete or time out. Python returns ``True`` on timeout.
      - 3.00-57 and up
    * -
      - | C++: ``std::vector<OutputPacket> decode(std::string name)``
        | Python: ``decode(name)``
      - Synchronous decoding of the data with the specified decoder. A copy of the decoder with its settings is used, so the decoder itself is not changed. Callback functions are not called.
      - 3.00-57 and up
    * -
      - | C++: ``std::vector<OutputPacket> decodeNP(la_Decoder_t decoder, std::string json_settings, uint8_t* np_buffer, int size)``
        | Python: ``decodeNP(decoder, json_settings, np_buffer)``
      - Synchronously decodes the data from a NumPy buffer with the specified decoder type and JSON settings. Callback functions are not called.
      - 3.00-57 and up
    * -
      - | C++: ``bool saveCaptureDataToFile(std::string file)``
        | Python: ``saveCaptureDataToFile(file)``
      - Saves the data from the buffer to a file.
      - 3.00-57 and up
    * -
      - | C++: ``bool loadFromFile(std::string file, bool isRLE, uint64_t triggerSamplePosition)``
        | Python: ``loadFromFile(file, isRLE, triggerSamplePosition)``
      - Loads the data from a file into the analyzer buffer, without decoding.
      - 3.00-57 and up
    * -
      - | C++: ``bool loadFromFileAndDecode(std::string file, bool isRLE, uint64_t triggerSamplePosition)``
        | Python: ``loadFromFileAndDecode(file, isRLE, triggerSamplePosition)``
      - Loads the data from a file into the analyzer buffer and decodes it. Loading and decoding are asynchronous.
      - 3.00-57 and up
    * -
      - | C++: ``uint32_t getCapturedDataSize()``
        | Python: ``getCapturedDataSize()``
      - Returns the number of bytes captured by the FPGA or loaded from the user data array.
      - 3.00-57 and up
    * -
      - | C++: ``uint64_t getCapturedSamples()``
        | Python: ``getCapturedSamples()``
      - Returns the number of samples captured by the FPGA or loaded from the user data array (also calculated from RLE).
      - 3.00-57 and up
    * -
      - | C++: ``uint32_t getDataNP(uint8_t* np_buffer, int size)``
        | Python: ``getDataNP(np_buffer)``
      - Returns the data from the buffer into a NumPy array. Returns the number of samples.
      - 3.00-57 and up
    * -
      - | C++: ``uint64_t getUnpackedRLEDataNP(uint8_t* np_buffer, int size)``
        | Python: ``getUnpackedRLEDataNP(np_buffer)``
      - Returns the unpacked RLE data into a NumPy array. Size the array with ``getCapturedSamples()``. Nothing is returned if RLE is not used.
      - 3.00-57 and up
    * -
      - | C++: ``void printRLE(bool useHex)``
        | Python: ``printRLE(useHex)``
      - Prints the RLE data.
      - 3.00-57 and up
    * -
      - | C++: ``void printRLENP(uint8_t* np_buffer, int size, bool useHex)``
        | Python: ``printRLENP(np_buffer, useHex)``
      - Prints the RLE data from a NumPy buffer.
      - 3.00-57 and up

|

CLACallback commands
-----------------------

``CLACallback`` is the callback interface. Inherit from it and override the functions you need, then register the object with ``setDelegate``. The callbacks are not called by the synchronous ``decode`` functions.

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``void captureStatus(CLAController* controller, bool isTimeout, uint32_t numBytes, uint64_t numSamples, uint64_t preTriggerSamples, uint64_t postTriggerSamples)``
        | Python: ``captureStatus(self, controller, isTimeout, bytes, samples, preTrig, postTrig)``
      - Called after data is captured on the FPGA (after ``runAsync(timeoutMs)``).
      - 3.00-57 and up
    * -
      - | C++: ``void decodeStatus(CLAController* controller, uint32_t numBytes, uint64_t numSamples, uint64_t preTriggerSamples, uint64_t postTriggerSamples)``
        | Python: ``decodeStatus(self, controller, bytes, samples, preTrig, postTrig)``
      - Called after a block of data uploaded by the user has been decoded (after ``loadFromFileAndDecode``).
      - 3.00-57 and up
    * -
      - | C++: ``void decodeDone(CLAController* controller, std::string name)``
        | Python: ``decodeDone(self, controller, name)``
      - Called after each of the configured decoders has finished decoding.
      - 3.00-57 and up

|

* :ref:`Back to top <commands_logic_analyzer>`
* :ref:`Back to command list <command_list>`


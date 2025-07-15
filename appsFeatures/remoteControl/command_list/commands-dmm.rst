
.. _commands_dmm:

#################################
Deep Memory Mode (DMM)
#################################

.. contents:: Deem memory mode command index
   :local:
   :depth: 2
   :backlinks: top

|

.. _commands_dma:

===============================
Deep Memory Acquisition (DMA)
===============================

-------------
DMA settings
-------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<byte> = {0...}`` in bytes
- ``<decimation> = {1, 2, 4, 8, 16, 17, 18, 19, ..., 65534, 65535, 65536}`` Default: ``1``
- ``<decimated_data_num> = {value in samples}`` Default: ``0``
- ``<pos> = {position inside circular buffer in samples}``
- ``<enable> = {ON, OFF}`` Default: ``OFF``
- ``<address> = {byte}`` Address of reserved memory
- ``<size> = {byte}`` Size of buffer in bytes. Default: 2 MB
- ``<samples> = {sample}`` Size of the acquisition buffer in samples. Default: 2 MB
- ``<units> = {RAW, VOLTS}`` Default: ``VOLTS``

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``


+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| SCPI                                                      | API, Jupyter                                                                                                               | DESCRIPTION                                                                     |  ECOSYSTEM         |
+===========================================================+============================================================================================================================+=================================================================================+====================+
| | ``ACQ:AXI:START?`` > ``<byte>``                         | | C: ``rp_AcqAxiGetMemoryRegion(uint32_t *_start, uint32_t *_size)``                                                       | | Returns the start address of the Deep Memory region.                          | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | API: Also returns the size of the memory region.                              |                    |
| | ``ACQ:AXI:START?`` > ``16777216``                       | | Python: ``rp_AcqAxiGetMemoryRegion()``                                                                                   | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SIZE?`` > ``<byte>``                          | | C: ``rp_AcqAxiGetMemoryRegion(uint32_t *_start, uint32_t *_size)``                                                       | | Get size of reserved memory for Deep Memory mode.                             | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | **API:** Also returns the start address of the memory region.                 |                    |
| | ``ACQ:AXI:SIZE?`` > ``2097152``                         | | Python: ``rp_AcqAxiGetMemoryRegion()``                                                                                   | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:ENable <enable>``                     | | C: ``rp_AcqAxiEnable(rp_channel_t channel, bool enable)``                                                                | Enables the specified acquisition channel in the Deep Memory Acquisition.       | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          |                                                                                 |                    |
| | ``ACQ:AXI:SOUR1:ENable ON``                             | | Python: ``rp_AcqAxiEnable(<channel>, <enable>)``                                                                         |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC <decimation>``                            | | C: ``rp_AcqAxiSetDecimationFactor(uint32_t decimation)``                                                                 | Sets the decimation used for acquiring signals in the Deep Memory Mode.         | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          |                                                                                 |                    |
| | ``ACQ:AXI:DEC 4``                                       | | Python: ``rp_AcqAxiSetDecimationFactor(<decimation>)``                                                                   |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC?`` > ``<decimation>``                     | | C: ``rp_AcqAxiGetDecimationFactor(uint32_t *decimation)``                                                                | Returns the decimation used for acquiring signals in the Deep Memory Mode.      | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          |                                                                                 |                    |
| | ``ACQ:AXI:DEC?`` > ``1``                                | | Python: ``rp_AcqAxiGetDecimationFactor()``                                                                               |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC:CH<n> <decimation>``                      | | C: ``rp_AcqAxiSetDecimationFactorCh(rp_channel_t channel, uint32_t decimation)``                                         | | Sets the decimation used for acquiring signals in the Deep Memory Mode.       | 2.05-37 and up     |
| | Example:                                                | |                                                                                                                          | | Used only in split trigger mode                                               |                    |
| | ``ACQ:AXI:DEC:CH1 4``                                   | | Python: ``rp_AcqAxiSetDecimationFactorCh(<channel>, <decimation>)``                                                      |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DEC:CH<n>?`` > ``<decimation>``               | | C: ``rp_AcqAxiGetDecimationFactorCh(rp_channel_t channel, uint32_t *decimation)``                                        | | Returns the decimation used for acquiring signals in the Deep Memory Mode.    | 2.05-37 and up     |
| | Example:                                                | |                                                                                                                          | | Used only in split trigger mode                                               |                    |
| | ``ACQ:AXI:DEC:CH1?`` > ``1``                            | | Python: ``rp_AcqAxiGetDecimationFactorCh(<channel>)``                                                                    |                                                                                 |                    |
| |                                                         | |                                                                                                                          |                                                                                 |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Dly <decimated_data_num>``       | | C: ``rp_AcqAxiSetTriggerDelay(rp_channel_t channel, int32_t decimated_data_num)``                                        | | Sets the number of decimated data after the trigger is                        | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | written into memory.                                                          |                    |
| | ``ACQ:AXI:SOUR1:Trig:Dly 2314``                         | | Python: ``rp_AcqAxiSetTriggerDelay(<channel>, <decimated_data_num>)``                                                    | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Dly?`` > ``<decimated_data_num>``| | C: ``rp_AcqAxiGetTriggerDelay(rp_channel_t channel, int32_t *decimated_data_num)``                                       | | Returns the number of decimated data after the trigger is                     | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | written into memory.                                                          |                    |
| | ``ACQ:AXI:SOUR1:Trig:Dly?`` > ``2314``                  | | Python: ``rp_AcqAxiGetTriggerDelay(<channel>)``                                                                          | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:SET:Buffer <address>,<size>``         | | C: ``rp_AcqAxiSetBufferSamples(rp_channel_t channel, uint32_t address, uint32_t samples)``                               | | Sets the Deep Memory buffer address and size in samples.                      | 2.00-18 and up     |
| | Example:                                                | |    ``rp_AcqAxiSetBufferBytes(rp_channel_t channel, uint32_t address, uint32_t size)``                                    | | Buffer size must be a multiple of 2.                                          |                    |
| | ``ACQ:AXI:SOUR<n>:SET:Buffer 16777216,512``             | | Python: ``rp_AcqAxiSetBufferSamples(<channel>, <address>, <samples>)``                                                   | |                                                                               |                    |
| |                                                         | |         ``rp_AcqAxiSetBufferBytes(<channel>, <address>, <size>)``                                                        | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DATA:UNITS <units>``                          | | C: - (see ``rp_AcqAxiGetDataV`` and ``rp_AcqAxiGetDataRaw``)                                                             | | Select units in which the acquired data will be returned.                     | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | For API commands the units are selected with the get data function.           |                    |
| | ``ACQ:AXI:DATA:UNITS RAW``                              | | Python: - (see ``rp_AcqAxiGetDataV`` and ``rp_AcqAxiGetDataRaw``)                                                        | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:DATA:UNITS?`` > ``<units>``                   | | C: - (see ``rp_AcqAxiGetDataV`` and ``rp_AcqAxiGetDataRaw``)                                                             | | Get units in which the acquired data will be returned.                        | 2.00-18 and up     |
| | Example:                                                | |                                                                                                                          | | For API commands the units are selected with the get data function.           |                    |
| | ``ACQ:AXI:DATA:UNITS?`` > ``RAW``                       | | Python: - (see ``rp_AcqAxiGetDataV`` and ``rp_AcqAxiGetDataRaw``)                                                        | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | - (NA)                                                  | | C: - (look for *malloc* function online)                                                                                 | | Performs memory allocation and returns the requested buffer.                  | 2.00-18 - 2.04-35  |
| |                                                         | |                                                                                                                          | | - ``<maxChannels>`` - how many channels will be acquired                      |                    |
| |                                                         | | Python: ``rp_createBuffer(<maxChannels>, <length>, <initInt16>, <initDouble>, <initFloat>)``                             | | - ``<enght>`` - length of the buffer in samples (max 16384)                   |                    |
| |                                                         | |                                                                                                                          | | - ``<initInt16>, <initDouble>, <initFloat>`` - buffer sample type, set one    |                    |
| |                                                         | |                                                                                                                          | |   to ``true``, others are ``false``.                                          |                    |
| |                                                         | |                                                                                                                          | | For Python API specifically. Replaced by functions returning NumPy buffers.   |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | - (NA)                                                  | | C: - (look for *free* function online)                                                                                   | | Free the allocated resources.                                                 | 2.00-18 - 2.04-35  |
| |                                                         | |                                                                                                                          | | - ``<buffer>`` - buffer to be released/freed                                  |                    |
| |                                                         | | Python: ``rp_deleteBuffer(<buffer>)``                                                                                    | | For Python API specifically.                                                  |                    |
| |                                                         | |                                                                                                                          | | Replaced by functions returning NumPy buffers.                                |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+



----------------
DMA data read
----------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<count> = {value in samples}`` Default: ``0``
- ``<pos> = {samples}`` Position inside circular buffer in samples
- ``<size> = {samples}`` Size of acquired data in samples
- ``<buffer>`` Array to store the data into. For Python API use ``rp_createBuffer`` and for C API use *malloc*.

*STEMlab 125-14 4-Input only (additional):*

- ``<n> = {3,4}`` (set channel IN3, or IN4)

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``

*STEMlab 125-14 4-Input only (additional):*

- Fast analog channels - ``RP_CH_3, RP_CH_4``


+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| SCPI                                               | API, Jupyter                                                                                                               | DESCRIPTION                                                                     |  ECOSYSTEM         |
+====================================================+============================================================================================================================+=================================================================================+====================+
| | ``ACQ:AXI:SOUR<n>:TRIG:FILL?``                   | | C: ``rp_AcqAxiGetBufferFillState(rp_channel_t channel, bool* state)``                                                    | Indicates whether the Deep Memory Acquisition buffer is full of data.           | 2.00-18 and up     |
| | Example:                                         | |                                                                                                                          |                                                                                 |                    |
| | ``ACQ:AXI:SOUR1:TRIG:FILL?`` > ``1``             | | Python: ``rp_AcqAxiGetBufferFillState(<channel>)``                                                                       |                                                                                 |                    |
| |                                                  | |                                                                                                                          |                                                                                 |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Write:Pos?`` > ``<pos>``       | | C: ``rp_AcqAxiGetWritePointer(rp_channel_t channel, uint32_t* pos)``                                                     | | Returns current position of the Deep Memory Acquisition write pointer.        | 2.00-18 and up     |
| | Example:                                         | |                                                                                                                          | |                                                                               |                    |
| | ``ACQ:AXI:SOUR1:Write:Pos?`` > ``1024``          | | Python: ``rp_AcqAxiGetWritePointer(<channel>)``                                                                          | |                                                                               |                    |
| |                                                  | |                                                                                                                          | |                                                                               |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:Trig:Pos?`` > ``<pos>``        | | C: ``rp_AcqAxiGetWritePointerAtTrig(rp_channel_t channel, uint32_t* pos)``                                               | | Returns position of Deep Memory Acquisition write pointer at time when        | 2.00-18 and up     |
| | Example:                                         | |                                                                                                                          | | the trigger arrived.                                                          |                    |
| | ``ACQ:AXI:SOUR1:Trig:Pos?`` > ``512``            | | Python: ``rp_AcqAxiGetWritePointerAtTrig(<channel>)``                                                                    | |                                                                               |                    |
| |                                                  | |                                                                                                                          | |                                                                               |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ``ACQ:AXI:SOUR<n>:DATA:Start:N? <pos>,<size>``   | | C: ``rp_AcqAxiGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer)``                              | | Read ``count`` samples from the ``pos`` position onwards.                     | 2.00-18 and up     |
| | Example:                                         | |    ``rp_AcqAxiGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer)``                         | | **SCPI:** Returns the value as a text array of values or a byte array.        |                    |
| | ``ACQ:AXI:SOUR1:DATA:Start:N? 20,3`` >           | | Python: ``rp_AcqAxiGetDataV(<channel>, <pos>, <size>, <buffer>)``                                                        | | Depending on the ``ACQ:AXI:DATA:UNITS`` setting.                              |                    |
| | ``{1.2,3.2,-1.2}``                               | |         ``rp_AcqAxiGetDataRaw(<channel>, <pos>, <size>, <buffer>)``                                                      | | **API:** Returns the Deep Memory buffer in specified units from specified     |                    |
| |                                                  | |                                                                                                                          | | position and desired size.                                                    |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ''                                               | | Python: ``rp_AcqAxiGetDataVNP(<channel>, <pos>, <np_buffer>)`` (Numpy buffer ``dtype=np.float32``)                       | | Copies the captured DMA buffer data into the passed NumPy buffer from ``pos`` | 2.05-37 and up     |
| |                                                  | |         ``rp_AcqAxiGetDataRawNP(<channel>, <pos>, <np_buffer>)`` (Numpy buffer ``dtype=np.int16``)                       | | onwards. The length of the copied data matches the ``np_buffer`` length.      |                    |
| |                                                  | |                                                                                                                          | | Numpy buffer must have the specified ``dtype`` format.                        |                    |
| |                                                  | |                                                                                                                          | | Faster than the Python functions above.                                       |                    |
| |                                                  | |                                                                                                                          | |                                                                               |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | ''                                               | | Python: ``rp_AcqAxiGetDataRawDirect(<channel>, <pos>, <size>)``                                                          | | Returns a memory region without copying data (the fastest method).            | IN DEV             |
| |                                                  | |                                                                                                                          | | Use ``frombuffer`` function to extract the data.                              |                    |
| |                                                  | |                                                                                                                          | |                                                                               |                    |
| |                                                  | |                                                                                                                          | |                                                                               |                    |
| |                                                  | |                                                                                                                          | |                                                                               |                    |
+----------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+



.. _commands_dmg:

===============================
Deep Memory Generation (DMG)
===============================

-------------
DMG settings
-------------

**Parameter options:**

- ``<n> = {1,2}`` (set channel IN1 or IN2)
- ``<byte> = {0...}`` in bytes
- ``<decimation> = {1, 2, 4, 8, 16, 17, 18, 19, ..., 65534, 65535, 65536}`` Default: ``1``
- ``<enable> = {True, False}`` Default: ``False``
- ``<start>, <end> = {byte}`` Start and end address of reserved memory

**Available Jupyter and API macros:**

- Fast analog channels - ``RP_CH_1, RP_CH_2``


+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| SCPI                                                      | API, Jupyter                                                                                                               | DESCRIPTION                                                                     |  ECOSYSTEM         |
+===========================================================+============================================================================================================================+=================================================================================+====================+
| | -                                                       | | C: ``rp_GenAxiReserveMemory(rp_channel_t channel, uint32_t start, uint32_t end)``                                        | | Reserve an allocated area within the Deep Memory region for generation        | IN-DEV             |
| |                                                         | |                                                                                                                          | | (number of Bytes).                                                            |                    |
| |                                                         | | Python: ``rp_GenAxiReserveMemory(<channel>, <start>, <end>)``                                                            | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | -                                                       | | C: ``rp_GenAxiReleaseMemory(rp_channel_t channel)``                                                                      | | Release the reserved generation memory in the Deep Memory region.             | IN-DEV             |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
| |                                                         | | Python: ``rp_GenAxiReleaseMemory(<channel>)``                                                                            | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | -                                                       | | C: ``rp_GenAxiSetEnable(rp_channel_t channel, bool enable)``                                                             | | Enables the Deep Memory Generation for the specified channel.                 | IN-DEV             |
| |                                                         | |                                                                                                                          | | Memory region must be reserved beforehand.                                    |                    |
| |                                                         | | Python: ``rp_GenAxiSetEnable(<channel>, <enable>)``                                                                      | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | -                                                       | | C: ``rp_GenAxiGetEnable(rp_channel_t channel, bool* enable)``                                                            | | Retrieves the enable state of the Deep Memory Generation for the specified    | IN-DEV             |
| |                                                         | |                                                                                                                          | | channel.                                                                      |                    |
| |                                                         | | Python: ``rp_GenAxiGetEnable(<channel>)``                                                                                | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | -                                                       | | C: ``rp_GenAxiSetDecimationFactor(rp_channel_t channel, uint32_t decimation)``                                           | | Sets the Data Delay Mode value (generation decimation) for Deep Memory        | IN-DEV             |
| |                                                         | |                                                                                                                          | | Generation. Each sample remains on the DAC for ``<decimation>`` clock cycles, |                    |
| |                                                         | | Python: ``rp_GenAxiSetDecimationFactor(<channel>, <decimation>)``                                                        | | effectively reducing the output sample rate.                                  |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | -                                                       | | C: ``rp_GenAxiGetDecimationFactor(rp_channel_t channel, uint32_t* decimation)``                                          | | Retrieves the Data Delay Mode value (generation decimation) for Deep Memory   | IN-DEV             |
| |                                                         | |                                                                                                                          | | Generation.                                                                   |                    |
| |                                                         | | Python: ``rp_GenAxiGetDecimationFactor(<channel>)``                                                                      | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | -                                                       | | C: ``rp_GenAxiWriteWaveform(rp_channel_t channel, float* buffer, uint32_t length)``                                      | | Copies data from the NumPy buffer into the Deep Memory Generation region. The | IN-DEV             |
| |                                                         | |                                                                                                                          | | data must be in float format and the length of the buffer must be half the    |                    |
| |                                                         | | Python: ``rp_GenAxiWriteWaveform(<channel>, <np_buffer>)``                                                               | | reserved DMG region (each float is converted into two int16). Values should   |                    |
| |                                                         | |                                                                                                                          | | be within full scale output range (±1 V).                                     |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+
| | -                                                       | | C: ``rp_GenSetAmplitudeAndOffsetOrigin(rp_channel_t channel)``                                                           | | Applies the DAC calibration values to the DMG waveform.                       | IN-DEV             |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
| |                                                         | | Python: ``rp_GenSetAmplitudeAndOffsetOrigin(<channel>)``                                                                 | |                                                                               |                    |
| |                                                         | |                                                                                                                          | |                                                                               |                    |
+-----------------------------------------------------------+----------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_dmm>`
* :ref:`Back to command list <command_list>`

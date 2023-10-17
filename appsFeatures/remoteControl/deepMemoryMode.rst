.. _axiMode:
.. _deepMemoryMode:

###################
Deep Memory Mode
###################

Description
===============

The Deep Memory mode allows you to set a buffer of any size (The buffer must be a multiple of 64 bytes) for capturing data from the ADC. Data is written directly to RAM.
The Deep Memory mode relies on the |AXI protocol|. Consequently, the functions to work with the Deep Memory mode are named after it.

.. |AXI protocol| raw:: html

   <a href="https://support.xilinx.com/s/article/1053914?language=en_US" target="_blank">AXI protocol</a>

**Features**

- Deep Memory mode can work in parallel with regular data capture mode in v0.94, only work with triggers is common.
- By default, the maximum size of two buffers (1 and 2 channels) is set to 2 MB.
- Deep Memory mode can run at maximum ADC speed.
- Deep Memory can assign only one buffer, thereby allocating all memory to only one channel.


Required hardware
===================

- Red Pitaya device (except STEMlab 125-14 4-Input)
- FPGA v0.94


Functionality
========================

By default, 2 MB of the DDR RAM are reserved for the Deep Memory mode. The DDR memory allocated to the Deep Mode can be configured through the **reg* parameter to a maximum of 256 MB. The :ref:`device tree ecosystem <ecosystem>` must be rebuilt after changing this parameter.

**Changing Reserved Memory**

In the **dtraw.dts** configure the following lines:

.. code-block:: c

   buffer@1000000 {
      phandle = <0x39>;
      reg = <0x1000000 0x200000>;
   };

The first parameter in **reg** is *start address (0x1000000)* and the second one is the *region size (0x200000)*.

.. note::

   Please note that the more memory you allocate to the Deep Memory Mode, the slower Red Pitaya Linux OS will function as the RAM resources between the two are shared. The memory allocated to the Deep Memory mode is reserved, so Linux cannot use it.

Here is a representation of how the Deep Memory mode data saving functions:

.. img:: img/Deep Memory.png

TThe reserved memory region is located between **ADC_AXI_START** and **ADC_AXI_END** addresses, which are macros for the first and last/end addresses and are automatically configured by the ecosystem. The data is saved in 32-bit chunks (4 Bytes per sample). The **ADC_AXI_START** points to the start of the first Byte (of the first sample), and **ADC_AXI_END** points to the first Byte (of the last sample) of DDR reserved for the Deep Memory Mode.

The memory region can capture data from a single channel (the whole memory is allocated to a single channel), or it can be split between both input channels (CH1 (IN1) and CH2 (IN2)) by passing the following parameters to the *rp_AcqAxiSetBuffer()* function:

   - Captured channel number (*RP_CH_1* or *RP_CH_2*)
   - Start address
   - Number of samples (to be captured)

In the example below, the memory region is split between both channels, where 1024 samples are captured on each channel.

The **Mid Address** in the picture above represents the starting point of the Channel 2 buffer inside the reserved Deep Memory region and is usually set to *(ADC_AXI_START + ADC_AXI_END)/2* (both channels can capture the same amount of data).

Once the acquisition is complete, the data is acquired through the *rp_AcqAxiGetDataRaw* function by passing the following parameters:

   - Channel number
   - Address of triggering moment (by using the *rp_AcqAxiGetWritePointerAtTrig* function)
   - Data size
   - Location where to store the data (start address of buffer)

.. note::

   Depending on the size of the acquired data and how much DDR memory is reserved for the Deep Memory Mode the data transfer from DDR might take a while.

Once finished, please do not forget to free any resources and reserved memory locations. Otherwise, the performance of Red Pitaya can decrease over time.



API functions
=================
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| API                                                                               | DESCRIPTION                                                                    |
+===================================================================================+================================================================================+
| | C: ``rp_AcqAxiGetMemoryRegion(uint32_t* _start,``                               | | Returns the start and end address of the memory region. This can also be     |
| | ~                           ``uint32_t* _size)``                                | | achieved by displaying values of ``ADC_AXI_START`` and ``ADC_AXI_END``       |
| |                                                                                 | | marcors.                                                                     |
| | Python: ``rp_AcqAxiGetMemoryRegion()``                                          | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiGetBufferFillState(rp_channel_t channel,``                        | | Indicates whether the Deep Memory buffer was full of data.                   |
| | ~                              ``bool* state)``                                 | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiGetBufferFillState(channel)``                                | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiSetDecimationFactor(uint32_t decimation)``                        | | Sets the decimation used at acquiring signal for Deep Memory Mode.           |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiSetDecimationFactor(decimation)``                            | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiGetDecimationFactor(uint32_t* decimation)``                       | | Returns the decimation used for acquiring signal for Deep Memory Mode.       |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiGetDecimationFactor()``                                      | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiSetTriggerDelay(rp_channel_t channel,``                           | | Sets the number of decimated data after trigger written into memory.         |
| | ~                           ``int32_t decimated_data_num)``                     | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiSetTriggerDelay(channel, decimated_data_num)``               | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiGetTriggerDelay(rp_channel_t channel,``                           | | Returns the number of decimated data after trigger written into memory.      |
| | ~                           ``int32_t* decimated_data_num)``                    | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiGetTriggerDelay(channel)``                                   | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiGetWritePointer(rp_channel_t channel,``                           | | Returns current position of Deep Memory write pointer.                       |
| | ~                           ``uint32_t* pos)``                                  | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiGetWritePointer(channel)``                                   | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiGetWritePointerAtTrig(rp_channel_t channel,``                     | | Returns position of Deep Memory write pointer at time when trigger arrived.  |
| | ~                                 ``uint32_t* pos)``                            | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiGetWritePointerAtTrig(channel)``                             | |                                                                              |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiEnable(rp_channel_t channel,``                                    | | Sets the Deep Memory enable state.                                           |
| | ~                  ``bool enable)``                                             | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiEnable(channel, enable)``                                    | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiGetDataRaw(rp_channel_t channel,``                                | | Returns the Deep Memory buffer                                               |
| | ~                      ``uint32_t pos,``                                        | | in RAW units from specified position and desired size.                       |
| | ~                      ``uint32_t* size,``                                      | |                                                                              |
| | ~                      ``int16_t* buffer)``                                     | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiGetDataRaw(channel, pos, size, buffer)``                     | |                                                                              |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiGetDataV(rp_channel_t channel,``                                  | | Returns the Deep Memory buffer                                               |
| | ~                    ``uint32_t pos,``                                          | | in Volt units from specified position and desired size.                      |
| | ~                    ``uint32_t* size,``                                        | |                                                                              |
| | ~                    ``float* buffer)``                                         | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiGetDataV(channel, pos, size, buffer)``                       | |                                                                              |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiSetBufferSamples(rp_channel_t channel,``                          | | Sets the Deep Memory buffer address and size in samples.                     |
| | ~                            ``uint32_t address,``                              | |                                                                              |
| | ~                            ``uint32_t samples)``                              | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiSetBufferSamples(channel, address, samples)``                | |                                                                              |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| | C: ``rp_AcqAxiSetBufferBytes(rp_channel_t channel,``                            | | Sets the Deep Memory buffer address and size in Bytes.                       |
| | ~                          ``uint32_t address,``                                | |                                                                              |
| | ~                          ``uint32_t size)``                                   | |                                                                              |
| |                                                                                 | |                                                                              |
| | Python: ``rp_AcqAxiSetBufferBytes(channel, address, size)``                     | |                                                                              |
| |                                                                                 | |                                                                              |
| |                                                                                 | |                                                                              |
+-----------------------------------------------------------------------------------+--------------------------------------------------------------------------------+

.. note::

   All functions have an "int" return value. If the returned value is 0 (equal to *RP_OK*), then the function executed successfully.

   The Python functions are just wrappers that call the corresponding C function. Consequently, they always return an array where the first element represents whether a function was successful (or not), and the other elements represent the expected return values.


Additional information about function parameters is in this file:
   
   |RP_H|


.. |RP_H| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya/blob/master/rp-api/api/include/redpitaya/rp.h" target="_blank">Functions info</a>


Code Examples
================


C
---

The example shows how to use capturing data into two 1024-byte buffers. Please note that checking whether a function was successful is not necessary.

.. code-block:: c

   /* Red Pitaya C API example Acquiring a signal from a buffer
   * This application acquires a signal on a specific channel */

   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
   #include "rp.h"

   #define DATA_SIZE 1024

   int main(int argc, char **argv)
   {
      /* Initialise Red Pitaya */
      if (rp_InitReset(false) != RP_OK) {
         fprintf(stderr, "Rp api init failed!\n");
         return -1;
      }

      /* Set decimation for both channels */
      if (rp_AcqAxiSetDecimationFactor(RP_CH_1, RP_DEC_1) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetDecimationFactor RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetDecimationFactor(RP_CH_2, RP_DEC_1) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetDecimationFactor RP_CH_2 failed!\n");
         return -1;
      }

      /* Set trigger delay for both channels */
      if (rp_AcqAxiSetTriggerDelay(RP_CH_1, DATA_SIZE  )  != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetTriggerDelay RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetTriggerDelay(RP_CH_2, DATA_SIZE  ) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetTriggerDelay RP_CH_2 failed!\n");
         return -1;
      }

      /* 
      Set-up the Channel 1 and channel 2 buffers to each work with half the available memory space.
      ADC_AXI_START is a macro for the first address in the DEEP/AXI memory region.
      ADC_AXI_END is a macro for the last/end address in the DEEP/AXI memory region.
      */
      if (rp_AcqAxiSetBuffer(RP_CH_1, ADC_AXI_START, DATA_SIZE) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetBuffer RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetBuffer(RP_CH_2, (ADC_AXI_END + ADC_AXI_START) / 2, DATA_SIZE) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetBuffer RP_CH_2 failed!\n");
         return -1;
      }

      /* Enable DEEP mode on both channels */
      if (rp_AcqAxiEnable(RP_CH_1, true)) {
         fprintf(stderr, "rp_AcqAxiEnable RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiEnable(RP_CH_2, true)) {
         fprintf(stderr, "rp_AcqAxiEnable RP_CH_2 failed!\n");
         return -1;
      }

      /* Specify the acquisition trigger */
      rp_AcqSetTriggerLevel(RP_T_CH_1,0);

      /* Start the acquisition */
      if (rp_AcqStart() != RP_OK) {
         fprintf(stderr, "rp_AcqStart failed!\n");
         return -1;
      }

      /* Specify trigger source */
      rp_AcqSetTriggerSrc(RP_TRIG_SRC_CHA_PE);
      rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;

      /* Wait for the triggering moment */
      while(1){
         rp_AcqGetTriggerState(&state);
         if(state == RP_TRIG_STATE_TRIGGERED){
               sleep(1);
               break;
         }
      }

      /* Wait until both buggers are full/data is acquired */
      bool fillState = false;
      while (!fillState) {
         if (rp_AcqAxiGetBufferFillState(RP_CH_1, &fillState) != RP_OK) {
               fprintf(stderr, "rp_AcqAxiGetBufferFillState RP_CH_1 failed!\n");
               return -1;
         }
      }

      /* Stop the acquisition */
      rp_AcqStop();

      /* Get write pointer on the triggering location */
      uint32_t posChA,posChB;
      rp_AcqAxiGetWritePointerAtTrig(RP_CH_1,&posChA);
      rp_AcqAxiGetWritePointerAtTrig(RP_CH_2,&posChB);

      /* Allocate memory for the data */
      int16_t *buff1 = (uint16_t *)malloc(DATA_SIZE * sizeof(int16_t));
      int16_t *buff2 = (uint16_t *)malloc(DATA_SIZE * sizeof(int16_t));

      /* Pass the write pointer value at trigger to get data. */
      uint32_t size1 = DATA_SIZE;
      uint32_t size2 = DATA_SIZE;
      rp_AcqAxiGetDataRaw(RP_CH_1, posChA, &size1, buff1);
      rp_AcqAxiGetDataRaw(RP_CH_2, posChB, &size2, buff2);

      /* Print data */
      for (int i = 0; i < DATA_SIZE; i++) {
         printf("%d\t%d\n", buff1[i], buff2[i]);
      }

      /* Releasing resources */
      rp_AcqAxiEnable(RP_CH_1, false);
      rp_AcqAxiEnable(RP_CH_2, false);
      rp_Release();
      free(buff1);
      free(buff2);
      return 0;
   }

.. note::

   Instructions on how to compile the code are :ref:`here <comC>`.


Python (On-board)
-------------------

**Under construction...**

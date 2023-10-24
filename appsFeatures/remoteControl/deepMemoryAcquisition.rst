.. _axiMode:
.. _deepMemoryAcq:

##############################
Deep Memory Acquisition (DMA)
##############################

Description
===============

The Deep Memory Acquisition allows you to set a buffer of any size (The buffer must be a multiple of 64 bytes) for capturing data from the ADC. Data is written directly to RAM.
The DMA relies on the |AXI protocol|. Consequently, the functions to work with the DMA are named after it.

.. |AXI protocol| raw:: html

   <a href="https://support.xilinx.com/s/article/1053914?language=en_US" target="_blank">AXI protocol</a>

**Features**

- Deep Memory Acquisition can work in parallel with regular data capture mode in v0.94, only work with triggers is common.
- By default, the maximum size of two buffers (1 and 2 channels) is set to 2 MB.
- Deep Memory Acquisition can run at maximum ADC speed.
- Deep Memory can be assigned to only one buffer, thereby allocating all memory to only one channel.


Required hardware
===================

- Red Pitaya device (except STEMlab 125-14 4-Input)
- FPGA v0.94


Functionality
========================

By default, 2 MB of the DDR RAM are reserved for the Deep Memory Acquisition. The DDR memory allocated to the DMA can be configured through the **reg** parameter to a maximum of 256 MB. The :ref:`device tree ecosystem <ecosystem>` must be rebuilt after changing this parameter.

**Changing Reserved Memory**

In the **dtraw.dts** configure the following lines:

.. code-block:: c

   buffer@1000000 {
      phandle = <0x39>;
      reg = <0x1000000 0x200000>;
   };

The first parameter in **reg** is *start address (0x1000000)* and the second one is the *region size (0x200000)*.

.. note::

   Please note that the more memory you allocate to the DMA, the slower Red Pitaya Linux OS will function as the RAM resources between the two are shared. The memory allocated to the DMA is reserved, so Linux cannot use it.

Here is a representation of how the DMA data saving functions:

.. figure:: img/Deep_Memory.png
   :align: center
   :width: 700

TThe reserved memory region is located between **ADC_AXI_START** and **ADC_AXI_END** addresses, which are macros for the first and last/end addresses and are automatically configured by the ecosystem. The data is saved in 32-bit chunks (4 Bytes per sample). The **ADC_AXI_START** points to the start of the first Byte (of the first sample), and **ADC_AXI_END** points to the first Byte (of the last sample) of DDR reserved for the DMA.

The memory region can capture data from a single channel (the whole memory is allocated to a single channel), or it can be split between both input channels (CH1 (IN1) and CH2 (IN2)) by passing the following parameters to the *rp_AcqAxiSetBuffer()* function:

   - Captured channel number (*RP_CH_1* or *RP_CH_2*)
   - Start address
   - Number of samples (to be captured)

In the example below, the memory region is split between both channels, where 1024 samples are captured on each channel.

The **Mid Address** in the picture above represents the starting point of the Channel 2 buffer inside the reserved DMA region and is usually set to *(ADC_AXI_START + ADC_AXI_END)/2* (both channels can capture the same amount of data).

Once the acquisition is complete, the data is acquired through the *rp_AcqAxiGetDataRaw* function by passing the following parameters:

   - Channel number
   - Address of triggering moment (by using the *rp_AcqAxiGetWritePointerAtTrig* function)
   - Data size
   - Location where to store the data (start address of buffer)

.. note::

   Depending on the size of the acquired data and how much DDR memory is reserved for the Deep Memory Acquisition the data transfer from DDR might take a while.

Once finished, please do not forget to free any resources and reserved memory locations. Otherwise, the performance of Red Pitaya can decrease over time.



API functions
=================

Check the :ref:`DMA section under the SCPI commands <scpi_dma>`.


API Code Examples
===================

Check the :ref:`DMA section under the examples <examples>`.


Code - C API
-------------

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
      ADC_AXI_START is a macro for the first address in the Deep Memory Acquisition region.
      ADC_AXI_END is a macro for the last/end address in the DMA region.
      */
      if (rp_AcqAxiSetBuffer(RP_CH_1, ADC_AXI_START, DATA_SIZE) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetBuffer RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetBuffer(RP_CH_2, (ADC_AXI_END + ADC_AXI_START) / 2, DATA_SIZE) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetBuffer RP_CH_2 failed!\n");
         return -1;
      }

      /* Enable DMA on both channels */
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


Code - Python API
-------------------

**Under construction...**

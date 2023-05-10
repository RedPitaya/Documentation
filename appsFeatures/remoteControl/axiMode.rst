.. _axiMode:

AXI mode
########

Description
***********

The axi mode will allow you to set a buffer of any size (The buffer must be a multiple of 64 bytes) for capturing data from the ADC. Data is written directly to RAM.

**Features**

- Axi mode can work in parallel with regular data capture mode in 0.94, only work with triggers is common.
- By default, the maximum size of two buffers (1 and 2 channels) can be a maximum of 1.5 MB.
- Axi mode can run at maximum ADC speed.
- AXI can assign only one buffer, thereby allocating all memory to only 1 channel.

Required hardware
*****************

- Red Pitaya device
- FPGA v0.94

API functions
*************

+---------------------------------------+--------------------------------------------------------------------------------+
| API                                   | DESCRIPTION                                                                    |
+=======================================+================================================================================+
| ``rp_AcqAxiGetBufferFillState``       | | Indicates whether the ADC AXI buffer was full of data.                       |
|                                       | |                                                                              |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+
| ``rp_AcqAxiSetDecimationFactor``      | | Sets the decimation used at acquiring signal for AXI.                        |
|                                       | |                                                                              |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+
| ``rp_AcqAxiSetTriggerDelay``          | | Sets the number of decimated data after trigger written into memory.         |
|                                       | |                                                                              |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+
| ``rp_AcqAxiGetWritePointer``          | | Returns current position of AXI ADC write pointer.                           |
|                                       | |                                                                              |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+
| ``rp_AcqAxiGetWritePointerAtTrig``    | | Returns position of AXI ADC write pointer at time when trigger arrived.      |
|                                       | |                                                                              |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+
| ``rp_AcqAxiEnable``                   | | Sets the AXI enable state.                                                   |
|                                       | |                                                                              |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+
| ``rp_AcqAxiGetDataRaw``               | | Returns the AXI ADC buffer                                                   |
|                                       | | in raw units from specified position and desired size.                       |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+
| ``rp_AcqAxiGetDataV``                 | | Returns the AXI ADC buffer                                                   |
|                                       | | in Volt units from specified position and desired size.                      |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+
| ``rp_AcqAxiSetBuffer``                | | Sets the AXI ADC buffer address and size in samples.                         |
|                                       | |                                                                              |
|                                       | |                                                                              |
|                                       | |                                                                              |
+---------------------------------------+--------------------------------------------------------------------------------+

Additional information about function parameters is in this file:
   
   |RP_H|


.. |RP_H| raw:: html

   <a href="https://github.com/RedPitaya/RedPitaya/blob/master/rp-api/api/include/redpitaya/rp.h" target="_blank">Functions info</a>

Example
********

The example shows how to use capturing data into two 1024 byte buffers.

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

      if (rp_InitReset(false) != RP_OK) {
         fprintf(stderr, "Rp api init failed!\n");
         return -1;
      }

      if (rp_AcqAxiSetDecimationFactor(RP_CH_1, RP_DEC_1) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetDecimationFactor RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetDecimationFactor(RP_CH_2, RP_DEC_1) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetDecimationFactor RP_CH_2 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetTriggerDelay(RP_CH_1, DATA_SIZE  )  != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetTriggerDelay RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetTriggerDelay(RP_CH_2, DATA_SIZE  ) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetTriggerDelay RP_CH_2 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetBuffer(RP_CH_1, ADC_AXI_START, DATA_SIZE) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetBuffer RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiSetBuffer(RP_CH_2, (ADC_AXI_END + ADC_AXI_START) / 2, DATA_SIZE) != RP_OK) {
         fprintf(stderr, "rp_AcqAxiSetBuffer RP_CH_2 failed!\n");
         return -1;
      }
      if (rp_AcqAxiEnable(RP_CH_1, true)) {
         fprintf(stderr, "rp_AcqAxiEnable RP_CH_1 failed!\n");
         return -1;
      }
      if (rp_AcqAxiEnable(RP_CH_2, true)) {
         fprintf(stderr, "rp_AcqAxiEnable RP_CH_2 failed!\n");
         return -1;
      }

      rp_AcqSetTriggerLevel(RP_T_CH_1,0);

      if (rp_AcqStart() != RP_OK) {
         fprintf(stderr, "rp_AcqStart failed!\n");
         return -1;
      }

      rp_AcqSetTriggerSrc(RP_TRIG_SRC_CHA_PE);
      rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;

      while(1){
         rp_AcqGetTriggerState(&state);
         if(state == RP_TRIG_STATE_TRIGGERED){
               sleep(1);
               break;
         }
      }

      bool fillState = false;
      while (!fillState) {
         if (rp_AcqAxiGetBufferFillState(RP_CH_1, &fillState) != RP_OK) {
               fprintf(stderr, "rp_AcqAxiGetBufferFillState RP_CH_1 failed!\n");
               return -1;
         }
      }
      rp_AcqStop();

      uint32_t posChA,posChB;
      rp_AcqAxiGetWritePointerAtTrig(RP_CH_1,&posChA);
      rp_AcqAxiGetWritePointerAtTrig(RP_CH_2,&posChB);

      int16_t *buff1 = (uint16_t *)malloc(DATA_SIZE * sizeof(int16_t));
      int16_t *buff2 = (uint16_t *)malloc(DATA_SIZE * sizeof(int16_t));

      uint32_t size1 = DATA_SIZE;
      uint32_t size2 = DATA_SIZE;
      rp_AcqAxiGetDataRaw(RP_CH_1, posChA, &size1, buff1);
      rp_AcqAxiGetDataRaw(RP_CH_2, posChB, &size2, buff2);

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

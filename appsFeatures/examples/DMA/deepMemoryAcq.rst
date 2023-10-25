.. _deepMemoryAcq_example:

Deep Memory Acquisition
########################

Description
============

The example shows how to capture data into two 1024-byte buffers using the Deep Memory Acquisition. DMA can work in parallel with starndard SCPI acquisition.


Required hardware
==================

  -   Red Pitaya device
  -   Signal (function) generator


Wiring example for STEMlab 125-14:

.. figure:: img/DMA_temp.png



SCPI Code Examples
====================

**Coming soon...**


API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead, the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information are :ref:`here <comC>`.


Code - C API
---------------

Please note that checking whether a function was successful is not necessary.

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


Code - Python API
-------------------

.. code-block:: python

    #!/usr/bin/python3
    """Example of DMA acquisition of 1024-samples of data on both channels"""
    
    import time
    import rp
    
    DATA_SIZE = 1024
    
    dec = rp.RP_DEC_1
    trig_lvl = 0.2
    
    # Initialize the interface
    rp.rp_Init()
    
    
    ### Setting up DMA ###
    # Get Memory region
    memoryRegion = rp.rp_AcqAxiGetMemoryRegion()
    print(f"Memory Region: {memoryRegion}")
    start = memoryRegion[1]
    size = memoryRegion[2]
    
    
    # Set decimation
    rp.rp_AcqAxiSetDecimationFactor(dec)
    
    # Set trigger delay for both channels
    rp.rp_AcqAxiSetTriggerDelay(rp.RP_CH_1, DATA_SIZE)
    rp.rp_AcqAxiSetTriggerDelay(rp.RP_CH_2, DATA_SIZE)
    
    # Set-up the Channel 1 and channel 2 buffers to each work with half the available memory space.
    # - ADC_AXI_START is a macro for the first address in the Deep Memory Acquisition region.
    # - ADC_AXI_END is a macro for the last/end address in the DMA region.
    
    rp.rp_AcqAxiSetBufferSamples(rp.RP_CH_1, start, DATA_SIZE)
    rp.rp_AcqAxiSetBufferSamples(rp.RP_CH_2, int(start + size/2), DATA_SIZE)
    
    # Enable DMA on both channels
    rp.rp_AcqAxiEnable(rp.RP_CH_1, True)
    rp.rp_AcqAxiEnable(rp.RP_CH_2, True)
    
    # Specify the acquisition trigger
    rp.rp_AcqSetTriggerLevel(rp.RP_T_CH_1, trig_lvl)
    
    
    ### Acquisition ###
    # Start the DMA acquisition
    rp.rp_AcqStart()
    print("DMA started")
    
    # Specify trigger source
    rp.rp_AcqSetTriggerSrc(rp.RP_TRIG_SRC_CHA_PE)
    state = rp.RP_TRIG_STATE_TRIGGERED
    
    # Wait for the triggering moment
    while 1:
        state = rp.rp_AcqGetTriggerState()[1]
        if state == rp.RP_TRIG_STATE_TRIGGERED:
            print("Triggered")
            time.sleep(1)
            break
    
    # Wait until both buggers are full/data is acquired
    fillState = False
    print(type(rp.rp_AcqAxiGetBufferFillState(rp.RP_CH_1)[1]))
    
    while not fillState:
        fillState = rp.rp_AcqAxiGetBufferFillState(rp.RP_CH_1)[1]
    print("DMA buffer full")
    
    # Stop the acquisition
    rp.rp_AcqStop()
    print("DMA stopped")
    
    # Get write pointer on the triggering location
    posChA = rp.rp_AcqAxiGetWritePointerAtTrig(rp.RP_CH_1)[1]
    posChB = rp.rp_AcqAxiGetWritePointerAtTrig(rp.RP_CH_2)[1]
    
    # Allocate memory for the data
    buff1 = rp.i16Buffer(DATA_SIZE)
    buff2 = rp.i16Buffer(DATA_SIZE)
    
    # Pass the write pointer value at trigger to get data. */
    rp.rp_AcqAxiGetDataRaw(rp.RP_CH_1, posChA, DATA_SIZE, buff1.cast())
    rp.rp_AcqAxiGetDataRaw(rp.RP_CH_2, posChB, DATA_SIZE, buff2.cast())
    
    # Print data
    print()
    print(" CH 1    CH 2")
    for i in range(0, DATA_SIZE):
        print(f"{buff1[i]:5d}  {buff2[i]:5d}")
    
    
    ### Releasing resources ###
    print("\nReleasing resources\n")
    rp.rp_AcqAxiEnable(rp.RP_CH_1, False)
    rp.rp_AcqAxiEnable(rp.RP_CH_2, False)
    
    rp.rp_Release()

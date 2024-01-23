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

- Any Red Pitaya device
- FPGA v0.94


Functionality
========================

Here is a representation of how the DMA data saving functions:

.. figure:: img/Deep_Memory.png
   :align: center
   :width: 700

For easier explanation, the start and end addresses of the DMA buffer are labeled as **ADC_AXI_START** and **ADC_AXI_END**. The data is saved in 32-bit chunks (4 Bytes per sample). The **ADC_AXI_START** points to the start of the first Byte of the first sample, and **ADC_AXI_END** points to the first Byte of the last sample of DDR reserved for the DMA. The size of the whole buffer is **ADC_AXI_SIZE**. All the labels are just for representation and do not reference any macros.

The starting address of the DMA buffer (**ADC_AXI_START**) and the size of the DMA buffer (**ADC_AXI_SIZE**) are acquired through the **rp_AcqAxiGetMemoryRegion** function.

The memory region can capture data from a single channel (the whole memory is allocated to a single channel), or it can be split between both input channels (CH1 (IN1) and CH2 (IN2)) by passing the following parameters to the *rp_AcqAxiSetBuffer()* function:

   - Captured channel number (*RP_CH_1* or *RP_CH_2*)
   - Start address
   - Number of samples (to be captured)

In the example below, the memory region is split between both channels, where 1024 samples are captured on each channel.

The **Mid Address** in the picture above represents the starting point of the *Channel 2 buffer* inside the reserved DMA region and is set to *ADC_AXI_START + (ADC_AXI_SIZE/2)* (both channels can capture the same amount of data).

Once the acquisition is complete, the data is acquired through the *rp_AcqAxiGetDataRaw* or *rp_AcqAxiGetDataV* functions by passing the following parameters:

   - Channel number
   - Address of triggering moment (by using the *rp_AcqAxiGetWritePointerAtTrig* function)
   - Data size
   - Location where to store the data (start address of buffer). An integer buffer is used to store RAW values and a float buffer for values in Volts.

.. note::

   Depending on the size of the acquired data and how much DDR memory is reserved for the Deep Memory Acquisition, the data transfer from DDR might take a while.

Once finished, please do not forget to free the resources and reserved memory locations. Otherwise, the performance of your Red Pitaya can decrease over time.


Changing reserved memory
=============================

By default, 2 MB of the DDR RAM are reserved for the Deep Memory Acquisition. The DDR memory allocated to the DMA can be configured through the **reg** parameter. Afterwards, you must **rebuild the device tree** and **restart** the Red Pitaya for this change to take effect.

The maximum memory allocation is restricted to the size of the board's DDR (512 MB for STEMlab 125-14). However, DMA and Linux share the DDR resources, so allocating too many to the DMA may result in decreased performance. To prevent problems, we recommend leaving 100 MB of the DDR for the Linux, resulting in a maximum DMA region of 412 MB (for STEMlab 125-14).

1.   Establish an :ref:`SSH <ssh>` connection.
2.   Enable writing permissions and open the **dtraw.dts** file.

     .. code-block:: console

         root@rp-f066c8:~# rw
         root@rp-f066c8:~# nano /opt/redpitaya/dts/$(monitor -f)/dtraw.dts

3.   Search the file for the "buffer" keyword and configure the following lines:

     .. code-block:: default

         buffer@1000000 {
             phandle = <0x39>;
             reg = <0x1000000 0x200000>;
         };

     The first parameter in **reg** is *start address (0x1000000)*, and the second is the *region size (0x200000)*.

4.   Finally, rebuild the tree and restart the board.

    .. code-block:: console

       root@rp-f066c8:~# cd /opt/redpitaya/dts/$(monitor -f)/
       root@rp-f066c8:~# dtc -I dts -O dtb ./dtraw.dts -o devicetree.dtb
       root@rp-f066c8:~# reboot

.. note::

   To prevent performance decrease problems, we recommend leaving at least 100 MB of the DDR for the proper operation of the Linux OS. The maximal recommended DMA region size is 412 MB for STEMlab 125-14 and SDRlab 122-16 and 924 MB for SIGNALlab 250-12.


API functions
=================

Check the :ref:`DMA section under the commands' list <commands_dma>`.


API Code Examples
===================

Check the :ref:`DMA section under the examples <examples>`.


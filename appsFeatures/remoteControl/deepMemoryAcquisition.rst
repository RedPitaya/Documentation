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


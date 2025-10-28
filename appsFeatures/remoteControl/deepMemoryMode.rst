
.. _deepMemoryMode:

#######################
Deep Memory Mode (DMM)
#######################

Deep Memory Mode (DMM) encompasses the Deep Memory Acquisition (DMA) and the Deep Memory Generation (DMG). It enables the user to utilize the full potential of Red Pitaya's DDR3 RAM for data acquisition and generation. The Deep Memory Acquisition allows for high-speed data capture, 
while the Deep Memory Generation enables the generation of complex waveforms with extended memory capabilities.

All Deep Memory Mode features use direct memory access (commonly labelled with DMA) to the Red Pitaya's DDR3 RAM, allowing for high-speed data transfer and processing. The allocated RAM region is also referred to as the DMM region.

.. contents::
   :local:
   :backlinks: top

|

.. _deepMemoryAcq:

Deep Memory Acquisition (DMA)
==============================

Description
-----------

Deep memory acquisition is a special type of data acquisition that allows the user to stream data directly into Red Pitaya's DDR3 RAM at full sampling speed of 125 MS/s (depending on board model).
The buffer length is variable and can be specified by the user (must be a multiple of 64 Bytes), but cannot exceed the size of the allocated RAM region. The amount of dedicated RAM can be increased by the user, but it is recommended to leave at least 100 MB
of DDR for proper operation of the Linux OS. Deep memory acquisition is based on the `AXI protocol (AXI DMA and AXI4-Stream)`_. The Deep Memory Acuisition uses Direct Memory Access (double the acronym for double the meaning).

Once the acquisition is complete, Red Pitaya needs some time to transfer the entire file to the computer (RAM needs to be cleared) before the acquisition can be reset.
DMA can be configured using SCPI, Python API and C API commands.

**Features**

* Deep Memory Acquisition can work in parallel with regular data capture mode in v0.94 FPGA, only the triggers are common for both modes.
* By default, the RAM memory reagion allocated for the DMM is set to 32 MB (maximum space to capture data from all input channels).
* Deep Memory Acquisition can run at maximum ADC speed.
* The reserved memory can be assigned to only one buffer, thereby allocating all memory to a single one channel.


Required hardware
------------------

* Any Red Pitaya device.


Required software
------------------

* Red Pitaya OS 2.00-18 or higher.
* FPGA v0.94 image.


Functionality
-----------------

Here is a representation of how the DMA data saving functions:

.. figure:: img/Deep_Memory.png
    :align: center
    :width: 700

For easier explanation, the start and end addresses of the DMA buffer are labeled as **ADC_AXI_START** and **ADC_AXI_END**. The data is saved in 32-bit chunks (4 Bytes per sample). The **ADC_AXI_START** points to the start of the first Byte of the first sample, and **ADC_AXI_END** points to the first Byte of the last sample of DDR reserved for the DMA. 
The size of the whole buffer is **ADC_AXI_SIZE**. All the labels are just for representation and do not reference any macros.

The starting address of the DMA buffer (**ADC_AXI_START**) and the size of the DMA buffer (**ADC_AXI_SIZE**) are acquired through the **rp_AcqAxiGetMemoryRegion** function.

The memory region can capture data from a single channel (the whole memory is allocated to a single channel), or it can be split between multiple input channels (CH1 (IN1) and CH2 (IN2)) (also CH3 and CH4 on *STEMlab 125-14 4-Input*) by passing the following parameters to the *rp_AcqAxiSetBuffer()* function:

    * Captured channel number (*RP_CH_1* or *RP_CH_2*) (also *RP_CH_3* or *RP_CH_4* for *STEMlab 125-14 4-Input*).
    * Start address.
    * Number of samples (to be captured).

In the example below, the memory region is split between both channels, where 1024 samples are captured on each channel.

The **Mid Address** in the picture above represents the starting point of the *Channel 2 buffer* inside the reserved DMM region and is set to *ADC_AXI_START + (ADC_AXI_SIZE/2)* (both channels can capture the same amount of data).

Once the acquisition is complete, the data is acquired through the *rp_AcqAxiGetDataRaw* or *rp_AcqAxiGetDataV* functions by passing the following parameters:

    * Channel number.
    * Address of triggering moment (by using the ``rp_AcqAxiGetWritePointerAtTrig`` function).
    * Data size.
    * Location where to store the data (start address of buffer). An integer buffer is used to store RAW values and a float buffer for values in Volts.

.. note::

    Depending on the size of the acquired data and how much DDR memory is reserved for the Deep Memory Acquisition, the data transfer from DDR might take a while.
    Here are a few tips to speed things up:

    * SCPI commands - acquire the data in binary format (``ACQ:DATA:FORMAT BIN``) - for long data buffers we recommend capturing the data on the Red Pitaya board itself (C or Python API) and then establishing a TCP connection with the Red Pitaya board to transfer the data to the computer. 
      The SCPI performs a string conversion before the transfer and then converts the string back to data on the other side, which slows the transfer a lot.
    * Python API:

        * Use the new functions ``rp_AcqAxiGetDataRawNP(channel, pos, np_buffer)`` and ``rp_AcqAxiGetDataVNP(channel, pos, np_buffer)`` that return the data as a Numpy buffer directly.
        * The fastest possible acquisition is achieved by using the ``rp_AcqAxiGetDataRawDirect(channel, pos, size)``, which returns the data without copying it to a Numpy buffer.

    * Python or C API - to transfer the data to the computer establish a `websocket TCP connection`_ with the Red Pitaya and transfer the data over the socket. This is much faster than using the SCPI commands as we avoid the overhead of string conversion.

Once finished, please do not forget to free the resources and reserved memory locations. Otherwise, the performance of your Red Pitaya can decrease over time.


.. _deepMemoryGen:

Deep Memory Generation (DMG)
==============================


Description
-----------

Deep memory generation is a special type of data generation that allows the user to stream data directly from Red Pitaya's DDR3 RAM to the fast analog outputs.
The buffer length is variable and can be specified by the user (at least 128 Bytes), but cannot exceed the size of the allocated DMM region. The amount of dedicated RAM can be increased by the user, but it is recommended to leave at least 100 MB
of DDR for proper operation of the Linux OS. Deep memory generation is based on the `AXI protocol (AXI DMA and AXI4-Stream)`_.

The generation frequency depends on the length of the DMG buffer size and decimation. The output waveform is generated at the full speed (125 MHz), but the maximum generation frequency (1.953 MHz) is limited by the minimum buffer size (if we consider a single period per buffer).

DMG can be configured using Python API and C API commands. We will add SCPI command support in the future.

**Features**

* Deep Memory Generation can generate custom waveforms with variable buffer length.
* By default, the RAM memory region allocated for the DMM is set to 32 MB (maximum space to store data for all output channels).
* Deep Memory Generations runs at maximum DAC speed, but the output frequency of continuous signals depends on the buffer contents.
* The reserved memory can be assigned to only one buffer, thereby allocating all memory to a single output channel.


Required hardware
------------------

* Any Red Pitaya device.


Required software
------------------

* Red Pitaya OS IN-DEV or higher.
* FPGA v0.94 image.


Functionality
-----------------

The Deep Memory Generation (DMG) uses the same reserved memory region as the Deep Memory Acquisition (DMA). The DMG can be used to generate complex waveforms with extended memory capabilities, allowing for longer and more detailed signals.
The functionality is similar to the DMA, but instead of capturing data, it generates data from the reserved memory region and streams it to the DAC outputs.

* The minimum buffer size is 64 samples (256 bytes). This results in a maximum continuous output frequency of 1.953 MHz (if we consider one period per buffer).
* Buffer start addresses must be multiples of 4096 (DDR page size).

.. TODO finish this section - create relevant pictures



.. _DMM_change_reserved_memory: 

Changing reserved memory
=========================

The default memory region for the Deep Memory Mode is set to 32 MB, which is enough for most applications. However, if you need more memory for your application, you can increase the size of the reserved region in the device tree file. The device tree file is located in the **/opt/redpitaya/dts/$(monitor -f)** directory.
The device tree file is a binary file that describes the hardware configuration of the Red Pitaya board. It is used by the Linux kernel to configure the hardware at boot time.
The DDR memory allocated to the DMM can be configured through the **reg** parameter. Afterwards, you must **rebuild the device tree** and **restart** the Red Pitaya for this change to take effect.

.. note::

    The reserved region is shared between the Deep Memory Acquisition and Deep Memory Generation. If you are using both features, the total size of the reserved region must be less than the size of the allocated memory region. 

The maximum memory allocation is restricted to the size of the board's DDR (512 MB for STEMlab 125-14). However, DMM and Linux share the DDR resources, so allocating too much resources to the DMM may result in decreased performance. To prevent problems, we recommend leaving at least 100 MB of the DDR for the Linux, resulting in a maximum DMM region of 412 MB (for STEMlab 125-14).

1. Establish an :ref:`SSH <ssh>` connection.
2. Enable writing permissions and open the **dtraw.dts** file.

    .. code-block:: console

        root@rp-f066c8:~# rw
        root@rp-f066c8:~# nano /opt/redpitaya/dts/$(monitor -f)/dtraw.dts

3. Search the file for the "buffer" keyword and configure the following lines:

    .. code-block:: default

        buffer@1000000 {
            phandle = <0x39>;
            reg = <0x1000000 0x2000000>;
        };

    The first parameter in **reg** is *start address (0x1000000)* (hexa address where the deep memory region starts), and the second is the *region size (0x2000000)* (32 MiB). Leave the start address the same and change the region size to suit your program needs. The values are in hexadecimal format.

    Here is a calculation example for a 32 MiB region:

    .. math::

        32 MiB = 32 \cdot 1 MiB = 32 \cdot 1024 \cdot 1024 Bytes = 2^{25} Bytes = 0x2000000

    .. note::

        1 MiB = 1024·1024 Bytes = :math:`2^{20}` Bytes = 1048576 Bytes.
        We are using Mebibytes (MiB) instead of Megabytes (MB) to avoid confusion with the decimal system.

4. Finally, rebuild the tree and restart the board.

    .. code-block:: console

        root@rp-f066c8:~# cd /opt/redpitaya/dts/$(monitor -f)/
        root@rp-f066c8:~# dtc -I dts -O dtb ./dtraw.dts -o devicetree.dtb
        root@rp-f066c8:~# reboot

.. note::

    To prevent performance decrease problems, we recommend leaving at least 100 MB of the DDR for the proper operation of the Linux OS. The maximal recommended DMM region size is 412 MB for STEMlab 125-14 and SDRlab 122-16 and 924 MB for SIGNALlab 250-12.


Checking the reserved memory
----------------------------

The easiest way to check the reserved memory region is to use the :ref:`monitor command line utiliy <monitor_util>`. The utility will display the reserved memory region start address, end address, and size in bytes. Here is an example of the command and the output:

.. code-block:: console

    redpitaya> monitor -r
    Reserved memory:
        start:  0x1000000 (16777216)
        end:    0x3000000 (50331648)
        size:   0x2000000 (33554432) 32768 kB


API functions
===============

Check the :ref:`DMA and DMG sections under the commands' list <commands_dmm>`.


API Code Examples
===================

Check the :ref:`DMA and DMG sections under the examples <examples>`.





.. links and references


.. _websocket TCP connection: https://www.geeksforgeeks.org/web-tech/what-is-web-socket-and-how-it-is-different-from-the-http/

.. _AXI protocol (AXI DMA and AXI4-Stream): https://adaptivesupport.amd.com/s/article/1053914?language=en_US

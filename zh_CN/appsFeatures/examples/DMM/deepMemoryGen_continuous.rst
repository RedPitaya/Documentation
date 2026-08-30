.. _deepMemoryGen_example:

深度内存生成（连续）
###################################

描述
============

本示例演示如何使用深度内存生成（DMG）从两个包含 64 个采样点（256 字节）的缓冲区生成连续信号。DMG 可以与其他 API/SCPI 命令并行使用，但不应与标准生成并行使用，因为两种输出波形会合并。

限制：

* 缓冲区最小大小为 64 个采样点（256 字节）。如果每个缓冲区包含一个周期，则最高连续输出频率为 1.953 MHz。
* 缓冲区起始地址必须是 4096 的倍数（DDR 页大小）。

有关深度内存生成的更多信息，请参阅 :ref:`深度内存生成 <deepMemoryGen>` 章节。

所需硬件
==================

* Red Pitaya 设备。


所需软件
==================

* IN-DEV（Nightly build 2.07-528 或更高版本）。

.. .. include:: ../sw_requirement.inc

SCPI 代码示例
====================

.. note::

    深度内存生成的 SCPI 命令目前尚不可用，未来将会添加。

.. Code - MATLAB®
.. ---------------

.. .. include:: ../matlab.inc

.. .. code-block:: matlab





.. Code - Python
.. ---------------

.. .. code-block:: python


.. .. include:: ../python_scpi_note.inc

API 代码示例
====================

.. include:: ../c_code_note.inc


代码 - C++ API
---------------

.. code-block:: cpp

    /* Red Pitaya C++ API example Generating continuous signal via DMG
    * This application generates a specific signal */

    #include <math.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    #include "rp.h"
    #include "rp_asg_axi.h"
    
    int main(int argc, char **argv) {

        // Data size in samples (16 bit)
        uint32_t bufferSize = 128;              // Should be twice the actual number of samples
        uint32_t dec_factor = 1;
        uint32_t num_buffers = 2;               // Either 1 or 2
        
        // Start addresses of buffers must be multiple of 4096 (DDR page size)
        uint32_t min_addr_diff = 4096;
    
        // Initialize the interface
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Rp api init failed!\n");
            return 1;
        }
        
        // Reset generator
        rp_GenReset();

        /* Setting up the Deep Memory Generation (DMG) */
        uint32_t dac_axi_start, dac_axi_size;

        // Get the reserved memory region start and size
        if (rp_AcqAxiGetMemoryRegion(&dac_axi_start, &dac_axi_size) != RP_OK) {
            fprintf(stderr, "Error get memory!\n");
            return 1;
        }

        // Lower the buffer size to the available memory size (if needed)
        uint32_t dmg_min_size = (uint32_t) (ceil((float) bufferSize / (float) min_addr_diff) * (float) min_addr_diff * (float) num_buffers);
        printf("Buffer size: %d\n", bufferSize);
        printf("Minimum size: %d\n", dmg_min_size);
        
        if (dmg_min_size > dac_axi_size) {
            printf("Buffer size is too large, reducing to available memory size\n");
            bufferSize = dac_axi_size / num_buffers;
            printf("Buffer size reduced to %d\n", bufferSize);
        }

        // Calculate the start address for both channels
        uint32_t gen1_start_addr = dac_axi_start;
        uint32_t gen2_start_addr = gen1_start_addr + dmg_min_size/2;
        
        // Reserve memory for the generator
        printf("Reserved memory for OUT1 Start: %x Size: %x End: %x\n", gen1_start_addr, bufferSize, gen1_start_addr + bufferSize);

        if (rp_GenAxiReserveMemory(RP_CH_1, gen1_start_addr, gen1_start_addr + bufferSize) != RP_OK) {
            fprintf(stderr, "Error setting address for DMG mode for OUT1\n");
            return 1;
        }

        printf("Reserved memory for OUT2 Start: %x Size: %x End: %x\n", gen2_start_addr, bufferSize, gen2_start_addr + bufferSize);

        if (rp_GenAxiReserveMemory(RP_CH_2, gen2_start_addr, gen2_start_addr + bufferSize) != RP_OK) {
            fprintf(stderr, "Error setting address for DMG mode for OUT2\n");
            return 1;
        }
        
        
        // Set decimation factor for both channels
        if (rp_GenAxiSetDecimationFactor(RP_CH_1, dec_factor) != RP_OK) {
            fprintf(stderr, "Error setting decimation for generator OUT1\n");
            return 1;
        }

        if (rp_GenAxiSetDecimationFactor(RP_CH_2, dec_factor) != RP_OK) {
            fprintf(stderr, "Error setting decimation for generator OUT2\n");
            return 1;
        }
        
        // Enable DMG mode for both channels
        if (rp_GenAxiSetEnable(RP_CH_1, true) != RP_OK) {
            fprintf(stderr, "Error enable axi mode for OUT1\n");
            return 1;
        }

        if (rp_GenAxiSetEnable(RP_CH_2, true) != RP_OK) {
            fprintf(stderr, "Error enable axi mode for OUT2\n");
            return 1;
        }
        
        // Define output waveform for both channels
        bufferSize /= 2;                // Samples are float32 which is 4 bytes, int16 is 2 bytes
        
        float *t = (float *)malloc(bufferSize * sizeof(float));
        float *x = (float *)malloc(bufferSize * sizeof(float));
        
        for (uint32_t i = 1; i < bufferSize; i++) {
            t[i] = (2 * M_PI) / bufferSize * i;
        }
        
        for (uint32_t i = 0; i < bufferSize; ++i) {
            x[i] = sin(t[i]) + ((1.0 / 3.0) * sin(t[i] * 3));
        }
        
        // Configure calibration and offset
        rp_GenSetAmplitudeAndOffsetOrigin(RP_CH_1);
        rp_GenAxiWriteWaveform(RP_CH_1, x, bufferSize);

        rp_GenSetAmplitudeAndOffsetOrigin(RP_CH_2);
        rp_GenAxiWriteWaveform(RP_CH_2, x, bufferSize);

        rp_GenOutEnableSync(true);
        rp_GenSynchronise();
        

        // Release resources
        free(t);
        free(x);
        
        rp_Release();
        
        return 0;
    }


代码 - Python API
-------------------

.. code-block:: python

    #!/usr/bin/python3
    """Example of DMG continuous generation on both channels"""

    import time
    import math
    import numpy as np
    from rp_overlay import overlay
    import rp

    ## Data size in samples 16 bit

    bufferSize = 128                # Should be twice the actual number of samples
    dec_factor = 1
    num_buffers = 2                 # Either 1 or 2

    # Start addresses of buffers must be multiple of 4096 (DDR page size)
    min_addr_diff = 4096


    # Load v0.94 FPGA image
    fpga = overlay()
    
    # Initialize the interface
    rp.rp_Init()

    ### Setting up DMG ###
    # Get Memory region
    memory = rp.rp_AcqAxiGetMemoryRegion()
    if (memory[0] != rp.RP_OK):
        print("Error accessing reserved memory")
        exit(1)

    dma_start_address = memory[1]
    dma_full_size = memory[2]
    print(f"Reserved memory Start: {dma_start_address:x} Size: {dma_full_size:x}\n")

    # Lower the buffer size to the available memory size
    dma_min_size = int(math.ceil(bufferSize/min_addr_diff) * min_addr_diff * num_buffers)

    if (dma_min_size > dma_full_size):
        print("Buffer size is too large, reducing to available memory size")
        bufferSize = int(dma_full_size / num_buffers)
        print(f"Buffer size reduced to {bufferSize}")

    # Calculate the start address for the second channel
    gen1_start_address = dma_start_address
    gen2_start_address = int(dma_start_address + dma_min_size/2)

    # Reserve memory for the generator
    if (rp.rp_GenAxiReserveMemory(rp.RP_CH_1, gen1_start_address, gen1_start_address + bufferSize) != rp.RP_OK):
        print("Error setting address for DMA mode for OUT1")
        exit(1)
    print(f"Reserved memory for OUT1 Start: {gen1_start_address:x} Size: {bufferSize:x} End: {gen1_start_address + bufferSize:x}\n")

    if (rp.rp_GenAxiReserveMemory(rp.RP_CH_2, gen2_start_address, gen2_start_address + bufferSize) != rp.RP_OK):
        print("Error setting address for DMA mode for OUT2")
        exit(1)
    print(f"Reserved memory for OUT2 Start: {gen2_start_address:x} End: {gen2_start_address + bufferSize:x}\n")

    # Set decimation factor
    if (rp.rp_GenAxiSetDecimationFactor(rp.RP_CH_1, dec_factor) != rp.RP_OK):
        print("Error setting decimation for generator OUT1")
        exit(1)
        
    if (rp.rp_GenAxiSetDecimationFactor(rp.RP_CH_2, dec_factor) != rp.RP_OK):
        print("Error setting decimation for generator OUT2")
        exit(1)

    # Enable DMG mode for OUT1
    if (rp.rp_GenAxiSetEnable(rp.RP_CH_1, True) != rp.RP_OK):
        print("Error enable axi mode for OUT1")
        exit(1)
    if (rp.rp_GenAxiSetEnable(rp.RP_CH_2, True) != rp.RP_OK):
        print("Error enable axi mode for OUT2")
        exit(1)

    # Define output waveform for OUT1 and OUT2
    bufferSize = int(bufferSize / 2)            # Samples are float32 which is 4 bytes, int16 is 2 bytes
    t = np.linspace(0, 2*np.pi, bufferSize, endpoint=False, dtype=np.float32)
    x = np.sin(t) + (1/3) * np.sin(3*t)

    # Configure calibration and offset
    rp.rp_GenSetAmplitudeAndOffsetOrigin(rp.RP_CH_1)
    rp.rp_GenAxiWriteWaveform(rp.RP_CH_1, x)

    rp.rp_GenSetAmplitudeAndOffsetOrigin(rp.RP_CH_2)
    rp.rp_GenAxiWriteWaveform(rp.RP_CH_2, x)

    # Generate the waveform
    rp.rp_GenOutEnableSync(True)
    rp.rp_GenSynchronise()

    rp.rp_Release()

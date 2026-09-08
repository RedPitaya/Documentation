
深度内存生成（突发）
###################################

描述
============

本示例演示如何使用深度内存生成（DMG）从一个包含 64 个采样点（256 字节）的缓冲区生成突发信号。DMG 可以与其他 API/SCPI 命令并行使用，但不应与标准生成并行使用，因为两种输出波形会合并。

限制：

* 缓冲区最小大小为 64 个采样点（256 字节）。这会产生最高 1.953 MHz 的连续输出频率。
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

    /* Red Pitaya C++ API example Generating continuous signal via DMA
    * This application generates a specific signal */

    #include <math.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    #include "rp.h"
    #include "rp_asg_axi.h"
    
    int main(int argc, char **argv) {

        // Select channel
        rp_channel_t channel = RP_CH_1;

        // Data size in samples (16 bit)
        uint32_t bufferSize = 4096;             // Should be twice the actual number of samples
        uint32_t dec_factor = 1;
        uint32_t num_buffers = 1;
        
        uint32_t ncyc = 2;
        uint32_t nor = 2;
        uint32_t period = 100;

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

        // Calculate the start address
        uint32_t gen1_start_addr = dac_axi_start;
        
        // Reserve memory for the generator
        printf("Reserved memory for OUT1 Start: %x Size: %x End: %x\n", gen1_start_addr, bufferSize, gen1_start_addr + bufferSize);

        if (rp_GenAxiReserveMemory(channel, gen1_start_addr, gen1_start_addr + bufferSize) != RP_OK) {
            fprintf(stderr, "Error setting address for DMG mode for OUT1\n");
            return 1;
        }
        
        // Set decimation factor
        if (rp_GenAxiSetDecimationFactor(channel, dec_factor) != RP_OK) {
            fprintf(stderr, "Error setting decimation for generator OUT1\n");
            return 1;
        }
        
        // Enable DMG mode
        if (rp_GenAxiSetEnable(channel, true) != RP_OK) {
            fprintf(stderr, "Error enable axi mode for OUT1\n");
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
        rp_GenSetAmplitudeAndOffsetOrigin(channel);

        // Set burst parameters
        rp_GenMode(channel, RP_GEN_MODE_BURST);
        rp_GenBurstCount(channel, ncyc);
        rp_GenBurstRepetitions(channel, nor);
        rp_GenBurstPeriod(channel, period);
        rp_GenAxiWriteWaveform(channel, x, bufferSize);

        rp_GenOutEnable(channel);
        rp_GenTriggerOnly(channel);
        
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
    """Example of DMG burst generation on one channel"""

    import time
    import math
    import numpy as np
    from rp_overlay import overlay
    import rp

    ## Data size in samples 16 bit
    channel = rp.RP_CH_1
    bufferSize = 4096                   # Should be twice the actual number of samples
    dec_factor = 1

    ncyc = 2
    nor = 2
    period = 100                        # in microseconds

    # Load v0.94 FPGA image
    fpga = overlay()

    # Initialize the interface
    rp.rp_Init()


    ### Setting up DMG ###
    # Get Memory region
    memory = rp.rp_AcqAxiGetMemoryRegion()
    if (memory[0] != rp.RP_OK):
        print("Error get reserved memory")
        exit(1)

    dmg_start_address = memory[1]
    dmg_full_size = memory[2]

    # Lower the buffer size to the available memory size (if needed)
    if (dmg_full_size < bufferSize):
        bufferSize = dmg_full_size

    # Reserve memory for the generator
    if (rp.rp_GenAxiReserveMemory(channel, dmg_start_address, dmg_start_address + bufferSize) != rp.RP_OK):
        print("Error setting address for dmg mode for OUT1")
        exit(1)

    # Set decimation factor
    if (rp.rp_GenAxiSetDecimationFactor(channel, dec_factor) != rp.RP_OK):
        print("Error setting decimation for generator")
        exit(1)

    # Enable DMG mode
    if (rp.rp_GenAxiSetEnable(channel, True) != rp.RP_OK):
        print("Error enable axi mode for OUT1")
        exit(1)

    # Define output waveform
    bufferSize = int(bufferSize / 2)

    t = np.linspace(0, 2*np.pi, bufferSize, endpoint=False, dtype=np.float32)
    x = np.sin(t) + (1/3) * np.sin(3*t)

    rp.rp_GenSetAmplitudeAndOffsetOrigin(channel)
    rp.rp_GenMode(channel, rp.RP_GEN_MODE_BURST)
    rp.rp_GenBurstCount(channel, int(ncyc))
    rp.rp_GenBurstRepetitions(channel, int(nor))
    rp.rp_GenBurstPeriod(channel, int(period))

    rp.rp_GenAxiWriteWaveform(channel, x)

    # Generate waveform
    rp.rp_GenOutEnable(channel)
    rp.rp_GenTriggerOnly(channel)

    # Release resources
    rp.rp_Release()


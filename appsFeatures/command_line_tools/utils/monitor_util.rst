.. _monitor_util:

Monitor utility
===============

Accessing system registers
---------------------------

The system and FPGA registers can be accessed through the monitor utility. Usage instructions:

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: console

            redpitaya>  monitor
            monitor version 1.03-0-ab43ad0-ab43ad0

            Usage:
                read addr: address
                write addr: address value
                read analog mixed signals: -ams
                set slow DAC: -sdac AO0 AO1 AO2 AO3 [V]

    .. group-tab:: OS version 2.00

        .. code-block:: console

            redpitaya> monitor
            monitor version 2.07-501-e1eff7e0a

            Usage:
                    read addr: address
                    write addr: address value
                    read analog mixed signals: -ams
                    set slow DAC: -sdac AO0 AO1 AO2 AO3 [V]
                    Clock frequency meter: -c
                    Print fpga version: -f
                    Print model name: -n
                    Print model id: -i
                    Print Housekeeping regset: -ph
                    Print Oscilloscope regset: -posc
                    Print Arbitrary Signal Generator regset: -pasg
                    Print Analog Mixed Signals regset: -pams
                    Print Daisy Chain regset: -pdaisy
                    Reserved memory for DMA: -r


Example (reading system registers):

.. code-block:: console

    redpitaya> monitor -ams
    #ID	        Desc            Raw	            Val
    0           Temp(0C-85C)    0x00000b12	    75.670
    1	        AI0(0-3.5V)     0x00000008	    0.014
    2	        AI1(0-3.5V)     0x00000017	    0.039
    3	        AI2(0-3.5V)     0x00000008	    0.014
    4	        AI3(0-3.5V)     0x00000006	    0.010
    5	        AI4(5V0)        0x000004f9	    3.800
    6	        VCCPINT(1V0)    0x0000055e	    1.006
    7	        VCCPAUX(1V8)    0x00000995	    1.797
    8	        VCCBRAM(1V0)    0x00000561	    1.009
    9           VCCINT(1V0)     0x00000561	    1.009
    10          VCCAUX(1V8)     0x00000997	    1.798
    11          VCCDDR(1V5)     0x00000806	    1.504
    12          AO0(0-1.8V)     0x0000000f	    0.173
    13          AO1(0-1.8V)     0x0000004e	    0.900
    14          AO2(0-1.8V)     0x00000075	    1.350
    15          AO3(0-1.8V)     0x0000009c	    1.800

A more detailed description of the above pins can be found :ref:`here <E1_orig_gen>`.
The -ams switch provides access to mixed analog signals including Zynq SoC temperature, auxiliary analog input reading, power supply voltages and configured auxiliary analog output settings. The auxiliary analog outputs can be set through the monitor utility using the -SADC switch:

.. code-block:: console

   redpitaya> monitor -sdac 0.9 0.8 0.7 0.6

.. note::

    The expected VCCDDR voltage is 1.35 V for boards with 1 GB of RAM (SIGNALlab 250-12 and STEMlab 125-14 Pro Z7020 Gen 2) and 1.5 V for all other boards.


Accessing FPGA registers
-------------------------

Red Pitaya's signal processing is based on two computing engines, the FPGA and the dual-core processor, to effectively share the tasks. Most of the high data rate signal processing is implemented in the FPGA building blocks. These blocks can be configured parametrically using registers.
The FPGA registers are documented in the :ref:`Red Pitaya HDL memory map <fpga_registers>` document (please make sure to reference the correct OS version). The registers can be accessed using the monitor utility described above.
For example, the following sequence of monitor commands checks, modifies and verifies the acquisition decimation parameter (at address 0x40100014):

.. code-block:: console

    redpitaya> monitor 0x40100014
    0x00000001
    redpitaya>
    redpitaya> monitor 0x40100014 0x8
    redpitaya> monitor 0x40100014
    0x00000008
    redpitaya>

.. note::

    The CPU algorithms communicate with the FPGA via these registers. Therefore, the user should be aware of possible interference with Red Pitaya applications that read or write to the same FPGA registers. However, for simple tasks, the monitor utility can be used by high-level scripts (Bash, Python, MATLAB, etc.) to communicate directly with the FPGA if necessary.


Source code
-----------

The Red Pitaya GitHub repository contains the `source code for the monitor utility <https://github.com/RedPitaya/RedPitaya/tree/master/Test/monitor>`_.

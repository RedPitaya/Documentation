.. _fpga_advanced:

###########################################
Advanced FPGA Topics
###########################################

This section covers advanced topics for Red Pitaya FPGA development, including boot loading configuration, advanced loading scenarios, JTAG programming, FPGA simulation, device tree configuration, and hardware signal mapping.

These topics are intended for developers who need to:

- Set up automatic FPGA loading at boot
- Configure custom FPGA bitstreams with device trees
- Program FPGA directly via JTAG for rapid development
- Simulate and verify FPGA designs before hardware deployment
- Create custom device tree configurations
- Understand physical pin connections and signal routing
- Integrate custom hardware peripherals
- Debug hardware-software interfaces
- Configure PS (Processing System) peripherals
- Implement complex FPGA workflows

.. toctree::
    :maxdepth: 1

    fpga_boot_loading.rst
    fpga_advanced_loading.rst
    jtag_programming.rst
    simulation.rst
    device_tree.rst
    signal_mapping.rst

.. _fpga_advanced:

###########################################
Advanced FPGA Topics
###########################################

This section covers advanced topics for Red Pitaya FPGA development beyond basic project creation and modification. These topics are essential for production deployment, 
hardware integration, and advanced debugging workflows.

**What you'll find here:**

* **FPGA Boot Loading** - Configure automatic FPGA bitstream loading at system boot
* **Advanced FPGA Loading** - Overlay system for runtime FPGA switching and management
* **JTAG Programming** - Direct FPGA programming via JTAG for rapid prototyping and debugging
* **Device Tree Configuration** - Create and modify device trees for custom peripherals and hardware configurations
* **Signal Mapping** - Hardware pin assignments, XADC inputs, GPIO connections, and physical signal routing

.. toctree::
    :maxdepth: 1

    fpga_boot_loading.rst
    fpga_advanced_loading.rst
    jtag_programming.rst
    device_tree.rst
    signal_mapping.rst

.. _fpga_intro:

###########################################
Introduction to Red Pitaya FPGA Development
###########################################

Understanding the Red Pitaya Architecture
==========================================

Red Pitaya software is composed of two main parts working together:

1. **FPGA Image** - Hardware logic running on the Xilinx Zynq FPGA that handles high-speed signal processing, data acquisition, and generation (also called the Programmable Logic (PL) side)
2. **Linux Operating System** - Software running on the ARM processor with drivers for interfacing with the FPGA (also called the Processing System (PS) side)

The FPGA and ARM processor are integrated into a single Xilinx Zynq System-on-Chip (SoC), allowing seamless communication between hardware and software components.

|

Required Development Tools
===========================

FPGA development for Red Pitaya requires specific versions of Xilinx tools:

Xilinx Vivado 2020.1
--------------------

**What it is:** Vivado is the primary development environment for creating and modifying FPGA designs. It includes:

* HDL editor for writing Verilog/VHDL code
* Block diagram editor for graphical design
* Synthesis and implementation tools
* Simulation environment
* Bitstream generation

**When you need it:** Always required for any FPGA development work.

Xilinx SDK 2019.1
-----------------

**What it is:** The Software Development Kit (SDK) is used for developing C/C++ applications that run on the ARM processor and interface with your FPGA design.

**When you need it:** Only required if you're modifying the software running on the ARM processor (drivers, APIs, custom applications). If you're only changing 
the FPGA logic and using existing software, you don't need SDK.

|

What You Can Accomplish
========================

Depending on your project goals, you can:

**Modify FPGA Design Only**

* Change signal processing algorithms
* Add new hardware peripherals
* Modify timing and data paths
* Customize existing Red Pitaya projects
* **Tools needed:** Vivado only

**Modify ARM Software Only**

* Change application logic
* Add new software features
* Modify APIs and drivers
* **Tools needed:** SDK only (using existing FPGA bitstreams)

**Full Custom Development**

* Create entirely new FPGA designs
* Develop matching software drivers
* Integrate custom hardware peripherals
* **Tools needed:** Both Vivado and SDK

|

Development Workflow Overview
==============================

The typical FPGA development workflow follows these steps:

1. **Setup Environment** - Install Vivado (and SDK if needed)
2. **Create/Modify Project** - Start with existing project or create new one
3. **Design** - Write HDL code or modify block diagrams
4. **Simulate** - Verify logic with behavioral simulation (critical step!)
5. **Synthesize** - Convert HDL to hardware gates
6. **Implement** - Place and route design on FPGA
7. **Generate Bitstream** - Create FPGA binary file
8. **Test on Hardware** - Load to Red Pitaya and verify
9. **Integrate Software** - Create/update drivers and applications (if needed)

|

Next Steps
==========

Now that you understand the architecture and tools, proceed with:

1. **Install Vivado** - Set up your development environment
2. **Install SDK** (optional) - If you need to modify ARM software
3. **Create Your First Project** - Follow the project creation guide
4. **Learn Simulation** - Essential for efficient development

The following sections will guide you through each step in detail.

|

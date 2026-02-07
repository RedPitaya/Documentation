.. _fpga_top:

###############
FPGA section
###############

This section describes how to build and modify the FPGA design for Red Pitaya boards. It is intended for users who want to create their own FPGA projects or modify existing ones using Xilinx Vivado.

**Prerequisites:** Basic knowledge of digital logic design, Verilog/VHDL, and familiarity with Xilinx Vivado development environment. Experience with Linux command line is helpful.

|

===========================================
Navigating the FPGA Documentation
===========================================

**For beginners - recommended reading order:**

1. :ref:`Getting Started <fpga_programming_environment>` - Install Vivado and SDK, create your first project, learn simulation (**Critical: includes simulation guide**)
2. :ref:`FPGA Tutorials <fpga_tutorials_top>` - Step-by-step tutorials for common FPGA tasks (**Coming soon**)
3. :ref:`FPGA Projects <fpga_projects>` - Explore available projects and repository structure
4. :ref:`Advanced Topics <fpga_advanced>` - Boot loading, JTAG programming, device trees (as needed)
5. :ref:`Registers <fpga_registers>` - Register maps for your specific OS version (reference material)

**For experienced users - quick access:**

* Modifying existing projects? → Start with :ref:`Getting Started <fpga_programming_environment>`
* Looking for project examples? → Go to :ref:`FPGA Projects <fpga_projects>`
* Setting up simulation? → See :ref:`Simulation <fpga_simulation>` in Getting Started
* Step-by-step guides? → Check :ref:`FPGA Tutorials <fpga_tutorials_top>` (coming soon)
* Need register addresses? → Check :ref:`Registers <fpga_registers>` for your OS version
* Advanced configurations? → See :ref:`Advanced Topics <fpga_advanced>`

|

===========================================
Typical FPGA Development Workflow
===========================================

**1. Environment Setup**

* Install Xilinx Vivado 2020.1 (required for building FPGA images)
* Install Xilinx SDK 2019.1 (required if modifying ARM software)
* Clone the Red Pitaya FPGA repository
* Familiarize yourself with the repository structure

**2. Choose Your Starting Point**

* **Modify existing project:** Start with a standard project (v0.94, streaming, axi4lite) and customize
* **Create new project:** Use an existing project as template, modify functionality
* **Add custom IP:** Integrate your own Verilog/VHDL modules into existing design

**3. Development Cycle**

a. **Design:** Modify RTL code or block diagram in Vivado
b. **Simulate:** Run behavioral simulation to verify logic and catch errors early (**Essential step - saves hours of debugging**)
c. **Synthesize:** Run synthesis to check for errors and resource usage
d. **Implement:** Place and route the design
e. **Generate bitstream:** Create the FPGA binary file (.bit)
f. **Test:** Load bitstream to Red Pitaya and verify functionality

.. note::

   **Why simulation is critical:** Simulating your design catches logical errors, timing issues, and functionality problems in minutes, whereas deploying to hardware and debugging can take hours. 
   Always simulate before synthesis, especially when learning FPGA development.

**4. Integration**

* Create or modify device tree if adding new peripherals
* Update software drivers/APIs to interface with new FPGA functionality
* Document register maps and usage

**5. Deployment**

* Copy bitstream to Red Pitaya
* Load at runtime using the ``overlay`` system
* Configure automatic loading at boot (optional)

|

======================
What's in each section
======================

* **Getting Started** - Vivado/SDK installation, project creation, simulation setup, FPGA reprogramming basics
* **FPGA Tutorials** - Step-by-step guides for common FPGA development tasks (coming soon)
* **FPGA Projects** - Available projects (v0.94, streaming, mercury, etc.), repository structure, project descriptions
* **Registers** - Memory-mapped register addresses and descriptions by OS version
* **Advanced Topics** - Boot configuration, JTAG programming, device trees, signal mapping

.. toctree::
    :maxdepth: 1

    getting_started/top.rst
    projects/top.rst
    advanced/top.rst
    regset/top.rst
..    fpga_tutorials/top.rst


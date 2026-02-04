
.. _fpga_programming_environment:

###########################################
Getting Started with FPGA Development
###########################################

This section guides you through setting up your FPGA development environment and creating your first Red Pitaya FPGA project. You'll install the necessary tools (Vivado 2020.1 and SDK 2019.1), learn to build and modify projects, simulate designs, and load bitstreams to your board.

**What you'll find here:**

* **Introduction** - Understand Red Pitaya FPGA architecture, required tools, and development workflow
* **Vivado Installation** - Install Xilinx Vivado 2020.1 for FPGA development
* **SDK Installation** - Install Xilinx SDK 2019.1 for ARM software development (optional)
* **Project Creation** - Create your first FPGA project from scratch
* **Modify Existing Projects** - Learn to customize existing Red Pitaya projects
* **Simulation** - Verify your designs with behavioral simulation before hardware deployment
* **Reprogram FPGA** - Load bitstreams to Red Pitaya and test your designs
* **Copy Projects** - Set up project templates and workflows
* **SDK Project Creation** - Create ARM software projects that interface with your FPGA design

.. toctree::
    :maxdepth: 1

    intro.rst
    vivado_install.rst
    sdk_install.rst
    project_creation.rst
    modify_project.rst
    simulation.rst
    reprogram_fpga.rst
    copy_project.rst
    project_creation_sdk.rst
..    new_project.rst


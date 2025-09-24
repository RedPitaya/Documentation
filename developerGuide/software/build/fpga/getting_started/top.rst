
.. _fpga_programming_environment:

###########################################
Red Pitaya FPGA programming environment
###########################################

Red Pitaya software is composed of two parts, the FPGA image and the Linux operating system with drivers for interfacing with the FPGA running on the ARM processor. The FPGA image is built using Vivado 2020.1, which is a development environment for Xilinx FPGAs. 
To make the interface between the FPGA and the ARM processor easier, the Xilinx Vivado Software Development Kit 2019.1 (SDK for short) is used.

Depending on your project goal, you may need to modify the FPGA design or the software running on the ARM processor. This also means that you may not need to install all the necessary software tools. 
If you are only interested in modifying the existing FPGA design, you will only need Vivado. If you want to modify the software running on the ARM processor, you will also need the Xilinx Vivado SDK.

The following sections will guide you through the installation of the necessary software and the creation of a simple FPGA project.

.. toctree::
    :maxdepth: 1

    vivado_install.rst
    project_creation.rst
    modify_project.rst
    reprogram_fpga.rst
    copy_project.rst
    project_creation_sdk.rst
..    sdk_install.rst
..    new_project.rst



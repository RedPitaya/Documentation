.. _fpga_tutorials_top:

#########################
FPGA Tutorials
#########################

The FPGA tutorials are a set of step-by-step guides that walk you through the process of creating and deploying FPGA applications using the Red Pitaya FPGA project as framework.
Each tutorial focuses on a specific aspect of FPGA development, from basic project setup to advanced signal processing techniques.

The tutorials are designed to be accessible to both beginners and experienced FPGA developers, providing clear instructions and explanations to help you understand the concepts
and techniques involved in FPGA development. However, we will not be deep diving into timing and other advanced topics in these tutorials, as they are meant to be an introduction 
to FPGA development using the Red Pitaya FPGA project.

**Recomended flow for new users:**

Start by going through the "Base Project" tutorial, where we will set up a basic FPGA project for Red Pitaya, which will be used as a foundation for the other tutorials.
Afterwards, follow the tutorials in the order they are presented, as they build upon each other and will help you understand the different aspects of FPGA development.

.. note::

    The code in the FPGA projects may not be fully optimized for performance. The focus is on clarity and educational value rather than achieving the best possible performance.

.. toctree::
    :maxdepth: 1

    configure_fpga
    base_project/top
    rf_inputs/top
..    gpio_led/top
..    rf_output/top
..    rf_input_output/top
..    SW_interface/top

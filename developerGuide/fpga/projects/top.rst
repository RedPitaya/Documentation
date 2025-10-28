.. _fpga_projects:

########################
FPGA projects
########################

This section contains information about various FPGA projects available for Red Pitaya. Each project is designed to demonstrate different functionalities and capabilities of the FPGA hardware.

.. contents:: Index
    :backlinks: top

|

FPGA repository
==================

Before we jump to the projects, let's take a look at the |FPGA GitHub repository| structure.

The repository contains multiple FPGA projects, with either generic functionality or specific functionality related to a particular application.

* Code common to all projects, which mostly contains reusable modules, is directly in the top directory.
* Project-specific code is located inside the ``prj/<project_name>/`` directories.


.. |ug895| replace:: Vivado System-Level Design Entry
.. _ug895: https://www.xilinx.com/support/documentation/sw_manuals/xilinx2017_2/ug895-vivado-system-level-design-entry.pdf


+-------------------+------------------------------------------------------------------+
| Path              | Contents                                                         |
+===================+==================================================================+
| ``archive/``      | Archive of old FPGA bit files compressed in .xz format           |
+-------------------+------------------------------------------------------------------+
| ``brd/``          | Board files (|ug895|_)                                           |
+-------------------+------------------------------------------------------------------+
| ``doc/``          | Documentation (block diagrams, address space, ...)               |
+-------------------+------------------------------------------------------------------+
| ``dts/``          | Device tree source include files                                 |
+-------------------+------------------------------------------------------------------+
| ``ip/``           | Third party IP, for now, Zynq block diagrams                     |
+-------------------+------------------------------------------------------------------+
| ``prj/name``      | Project `name` specific code                                     |
+-------------------+------------------------------------------------------------------+
| ``rtl/``          | Verilog (SystemVerilog) *Register-Transfer Level*                |
+-------------------+------------------------------------------------------------------+
| ``sdc/``          | *Synopsys Design Constraints* contains Xilinx design constraints |
+-------------------+------------------------------------------------------------------+
| ``sim/``          | Simulation scripts                                               |
+-------------------+------------------------------------------------------------------+
| ``tbn/``          | Verilog (SystemVerilog) *test bench*                             |
+-------------------+------------------------------------------------------------------+
| ``Makefile``      | Main Makefile, used to run FPGA-related tools                    |
+-------------------+------------------------------------------------------------------+
| ``*.tcl``         | TCL scripts to be run inside FPGA tools                          |
+-------------------+------------------------------------------------------------------+
| ``*.rst``         | ReStructuredText files for documentation                         |
+-------------------+------------------------------------------------------------------+

|


FPGA projects
====================

All existing projects have either generic functionality or specific functionality related to a particular application as described in the "Application" column.

We recommend using the **0.94** as the *default project*.


+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+
| Project name      | Description                                                            | Application                      | Status             |
+===================+========================================================================+==================================+====================+
| 0.94              | | The core project that contains most of the available functionality.  | | Oscilloscope                   | Active             |
|                   | | Also the core for all future development.                            | | Signal generator               |                    |
|                   | |                                                                      | | Arbitrary waveform generator   |                    |
|                   | | Main improvements over 0.93:                                         | | Spectrum analyzer              |                    |
|                   | | 1. The CDC (clock domain crossing) code on the custom CPU bus was    | | Bode analyzer                  |                    |
|                   | |    removed. Instead, the CDC for the GP0 port, which was already     | | Impedance analyzer             |                    |
|                   | |    available in the PS, was used. This improves speed and            | | LCR meter                      |                    |
|                   | |    reliability, while reducing RTL complexity.                       | | JupyterLab                     |                    |
|                   | | 2. A bug in the generator that caused a value increment was fixed;   | |                                |                    |
|                   | |    this should improve the generated frequencies near the half-      | |                                |                    |
|                   | |    sampling rate.                                                    | |                                |                    |
|                   | | 3. The XADC custom RTL wrapper was replaced with the Xilinx AXI      | |                                |                    |
|                   | |    XADC. This enables the use of the Linux driver with IIO streaming | |                                |                    |
|                   | |    support.                                                          | |                                |                    |
+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+
| stream_app        | | 1. Streaming of ADC and DAC data to and from DDR3 memory buffers.    | | Data stream control            | Active             |
|                   | | 2. Streaming of GPIO inputs and outputs to/from DDR3 memory buffers. | | (streaming application)        |                    |
+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+
| logic             | | The DMA is used to transfer data to the main DDR3 RAM. The ADC and   | Logic analyzer                   | Active             |
|                   | | DAC code is unfinished.                                              |                                  |                    |
+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+
| 0.93              | | The original Red Pitaya FPGA release with all original bugs.         |                                  | Legacy             |
|                   | | For deprecated application backward compatibility only.              |                                  |                    |
+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+
| classic           | | 1. Most of the code is rewritten in SystemVerilog.                   |                                  | Legacy             |
|                   | | 2. The GPIO and LED registers were removed from the housekeeping     |                                  |                    |
|                   | |    section; instead, the GPIO controller inside the PL is used. This |                                  |                    |
|                   | |    allows Linux kernel features to be used for GPIO (IRQ, SPI, I2C   |                                  |                    |
|                   | |    and 1-Wire) and LEDs (triggers).                                  |                                  |                    |
+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+
| axi4lite          | | This image is intended for testing various AXI4 bus implementations. |                                  | Legacy             |
|                   | | It contains a Vivado Integrated Logic Analyser (ILA) for observing   |                                  |                    |
|                   | | and reviewing the performance of the bus implementation.             |                                  |                    |
+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+
| tft               | | The TFT FPGA image supports connection to TFT displays, with         |                                  | Legacy             |
|                   | | instructions available :ref:`here <tft_displays>`. Compatible with   |                                  |                    |
|                   | | 0.97 and 0.98 OS versions.                                           |                                  |                    |
+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+
| mercury           | | The old image used by Jupyter Notebook application. Replaced by      | Jupyter Notebook                 | Legacy             |
|                   | | :ref:`Python API commands <C&Py_API>` in the latest OS versions.     |                                  |                    |
|                   | |                                                                      |                                  |                    |
+-------------------+------------------------------------------------------------------------+----------------------------------+--------------------+

|


In-depth project descriptions
==============================

.. toctree::
   :maxdepth: 1

   v0_94.rst
..   stream_app.rst
..   logic.rst


Board compatibility
=====================

Not all projects are compatible with all Red Pitaya boards. The table below shows the compatibility of each project with the different board versions.

The following table shows which projects are available on which boards.

.. include:: fpga_project_table.inc

+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| Build name        | Build Project Flag  | STEMlab 125-10 |br|       | SIGNALlab 250-12  | SDRlab 122-16             | STEMlab 125-14 4-Input    |
|                   |                     | STEMlab 125-14 |br|       |                   |                           |                           |
|                   |                     | STEMlab 125-14-Z7020 |br| |                   |                           |                           |
|                   |                     |                           |                   |                           |                           |
+===================+=====================+===========================+===================+===========================+===========================+
| 0.94              | v0.94               | X                         |                   | X                         | X                         |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| 0.94_250          | v0.94_250           |                           | X                 |                           |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| stream_app        | stream_app          | X                         |                   | X                         |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| stream_app_250    | stream_app_250      |                           | X                 |                           |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| logic             | logic               | X                         |                   |                           |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| logic_250         | logic_250           |                           | X                 |                           |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| tft               | tft                 | X                         |                   |                           |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| axi4lite          | axi4lite            | X                         |                   |                           |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| classic           | classic             | X                         |                   |                           |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+
| mercury           | mercury             | X                         |                   |                           |                           |
+-------------------+---------------------+---------------------------+-------------------+---------------------------+---------------------------+


.. substitutions


.. |FPGA GitHub repository| replace:: `FPGA GitHub repository <https://github.com/RedPitaya/RedPitaya-FPGA>`__

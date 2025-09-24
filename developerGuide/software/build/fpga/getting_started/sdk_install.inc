
.. _fpga_install_vivado_sdk:

#####################################
Installation of Vivado SDK 2019.1
#####################################

This installation tutorial is intended for anyone who wants to use the FPGA while also modifying the software running on the ARM processor of the Red Pitaya board.

.. contents:: index
    :backlinks: top

|

.. TODO add the instructions

Requirements
=============



Download Vivado SDK 2019.1
============================


















################## PREVIOUS PROJECT ###########################




The following build instructions were tested on Ubuntu 20.04.
It is important to install the correct Vivado and SDK versions as the projects and scripts are made for those versions and may return errors during the build.

.. note::

    Please note that the FPGA code is located in a separate repository from the ecosystem on our GitHub page:

        * Ecosystem: |ecosystem|
        * FPGA: |FPGA|

    Running the ":ref:`Makefile.x86 <dev_tree_xil>`" will download the necessary files from the RedPitaya/RedPitaya-FPGA repository.

    For building the FPGA image for different boards please see the :ref:`Buildprocess <buildprocess>`.


.. |ecosystem| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya" target="_blank">RedPitaya/RedPitaya</a>


.. |FPGA| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya-FPGA" target="_blank">RedPitaya/RedPitaya-FPGA</a>




Libraries used by ModelSim-Altera
=====================================

Install libraries:

.. code-block:: shell-session

    # apt-get install unixodbc unixodbc-dev libncurses-dev libzmq3-dev libxext6 libasound2 libxml2 libx11-6 libxtst6 libedit-dev libxft-dev libxi6 libx11-6:i386 libxau6:i386 libxdmcp6:i386 libxext6:i386 libxft-dev:i386 libxrender-dev:i386 libxt6:i386 libxtst6:i386




Xilinx Vivado SDK development environments 2019.1
==================================================

.. note::

    Please note that it might be necessary to download the **Full installer** as the **Web installer** might give an *Installer outdated* warning and refuse to proceed with the installation process.

Xilinx SDK is available from the |SDK download page|.


.. |SDK download page| raw:: html

    <a href="https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vitis/archive-sdk.html" target="_blank">Xilinx downloads page</a>





.. _dev_tree_xil:

Device Tree Xilinx
==================

FPGA build requires a repository with a device tree from Xilinx.
You can prepare it by running the command:

.. code-block:: shell-session

    $ make -f Makefile.x86 devicetree

.. note::

    The file can be manually uploaded.

    .. code-block:: shell-session

        curl -L https://github.com/Xilinx/device-tree-xlnx/archive/xilinx-v2017.2.tar.gz/ -o device-tree-xlnx-xilinx-v2017.2.tar.gz

   Extract the .tar.gz to */<redpitaya path>/tmp/device-tree-xlnx-xilinx-v2017.2*.



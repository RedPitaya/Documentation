.. _dev_guide_hardware:

Hardware
########

This section provides comprehensive hardware documentation for all Red Pitaya products, including detailed specifications, schematics, known issues, and comparison tables.


Understanding Product Names
============================

Red Pitaya board names follow a consistent format: **[Sampling Rate]-[Input Resolution]**

For example:

* **STEMlab 125-14** = 125 MSps sampling rate, 14-bit input resolution
* **SDRlab 122-16** = 122.88 MSps sampling rate, 16-bit input resolution  
* **SIGNALlab 250-12** = 250 MSps sampling rate, 12-bit input resolution

Additional suffixes indicate variants:

* **PRO** = Professional features (internal/external clock switching, external QSPI & eMMC booting, expanded connectivity)
* **Z7020** = Zynq 7020 FPGA (double the logic capacity of standard Zynq 7010)
* **4-Input** = Four input channels instead of two
* **LN** = Low Noise variant
* **EXT** = External clock capability

|

Understanding Generations
===========================

Red Pitaya products are organized into two distinct hardware generations. **These generations are kept separate to distinguish the newer boards with improved features and capabilities.**

Gen 2 vs Original Generation
------------------------------

**Why are they different?**

Gen 2 boards feature significant hardware improvements over the original generation:

* **Improved analog frontend** - Reduced noise and crosstalk, better SFDR performance
* **USB-C connectivity** - Replaces Micro USB for power and console (Gen 2 requires 5V, 3A vs Original's 5V, 2A)
* **Enhanced output capabilities** - ±2 V @ Hi-Z load and ±1 V @ 50 Ω load vs ±1 V on original boards
* **No power-on glitching** - Outputs remain stable during boot
* **OS requirements** - Gen 2 requires OS version 2.07-43 or higher; Original works with older versions (see :ref:`OS Version Compatibility <os_compatibility>`)

**PRO models add:**

* Internal/external clock switching
* E3 add-on board with STM32 microcontroller (power, watchdog, boot control)
* eMMC and QSPI booting options

**When choosing a board:**

* **Choose Gen 2** if you need the latest hardware improvements, lower noise, and better analog performance
* **Choose Original Gen** if you need specific models like SDRlab 122-16 (16-bit ADC) or SIGNALlab 250-12 (250 MS/s, BNC connectors, AC/DC coupling)

For detailed comparison, see the :ref:`Gen 2 comparison table <rp-board-comp-gen2>` and :ref:`Original Gen comparison table <rp-board-comp-orig_gen>`.

|


Identify Your Board
===================

To ensure compatibility with software and accessories, it's important to identify which Red Pitaya board you have. This section provides guides to help you determine your board 
model based on physical characteristics, serial numbers, and other identifiers.

* :ref:`Identify your board model <ID_guide>` - A comprehensive guide to help you identify your Red Pitaya board model.

|

Products
=========

In this section, you can find information about all existing Red Pitaya products, including the second generation of Red Pitaya boards, the original generation of 
Red Pitaya boards, extension modules, discontinued and obsolete products.


Second generation boards
-------------------------

The second generation of Red Pitaya boards is designed to provide enhanced performance and features compared to the original generation. 

.. toctree::
    :maxdepth: 1

    GEN2/125-14_Gen2/top.rst
    GEN2/125-14_Gen2_Pro/top.rst
    GEN2/125-14_Gen2_Z7020_Pro/top.rst
    GEN2/65-16_TI/top.rst
    GEN2/125-14_TI/top.rst
    GEN2/faq/faq.rst

.. note::

    The second generation products differ from the original generation even if the name itself is similar.


Original boards
----------------

The original generation of Red Pitaya boards.

.. toctree::
    :maxdepth: 1

    ORIG_GEN/125-14/top.rst
    ORIG_GEN/125-14_EXT/top.rst
    ORIG_GEN/125-14_LN/top.rst
    ORIG_GEN/125-14_4IN/top.rst
    ORIG_GEN/125-14_Z7020/top.rst
    ORIG_GEN/125-14_MULTI/top.rst
    ORIG_GEN/122-16/top.rst
    ORIG_GEN/122-16_EXT/top.rst
    ORIG_GEN/250-12/top.rst


Extension modules
------------------

.. toctree::
    :maxdepth: 1

    ext_modules/sensor_ext/sensor_ext.rst
    ext_modules/click_shield/click_shield.rst
    ext_modules/lcr_ext/lcr_ext.rst
    ext_modules/logic_ext/logic_ext.rst
    ext_modules/impedance_transformer/impedance_transformer.rst
    ext_modules/e3_ext/e3_hardware.rst
    ext_modules/extent_template/extent_template.rst


Discontinued
--------------

Discontinued boards and extensions are no longer manufactured, but are still supported by the Red Pitaya software.

.. toctree::
    :maxdepth: 1

    ORIG_GEN/125-10/top.rst


Obsolete
---------

Obsolete boards and extensions are no longer manufactured, and are not supported by the current Red Pitaya software.
The last working software version is listed under each product.

.. toctree::
    :maxdepth: 1

    ext_modules/sdr_module/sdr_module.rst

|

Specifications & Comparisons
==============================

General hardware specifications
--------------------------------

This section includes general hardware specifications for each generation of Red Pitaya products.

.. toctree::
    :maxdepth: 1
    
    GEN2/hw_specs/hw_specs.rst
    ORIG_GEN/hw_specs/hw_specs.rst



Product comparison tables
--------------------------

Product comparison tables provide a detailed overview of the differences between various Red Pitaya products, including specifications, features, and capabilities.

.. toctree::
    :maxdepth: 1

    GEN2/compares/vs.rst
    ORIG_GEN/compares/vs.rst



Known hardware issues
=======================

This section lists known hardware issues for each generation of Red Pitaya products.

.. toctree::
    :maxdepth: 1

    GEN2/known_hw_issues/known_hw_issues.rst
    ORIG_GEN/known_hw_issues/known_hw_issues.rst



Certificates
=============

Here you can find and download certificates for Red Pitaya products.

.. toctree::
    :maxdepth: 1
    
    cets.rst

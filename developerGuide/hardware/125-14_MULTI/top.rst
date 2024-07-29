.. _top_125_14_MULTI:

###################################
Red Pitaya X-Channel System
###################################

The Red Pitaya X-Channel system consists of multiple Low-Noise STEMlab 125-14 devices that are modified for clock and trigger synchronisation and also comes with SATA synchronisation cables and software that supports multi-channel RF signal acquisition and generation.

Red Pitaya X-Channel system consists of:

* one PRIMARY Low-Noise STEMlab 125-14 device, a standard Low-Noise STEMlab 125-14 device that provides clock and trigger signals to other SECONDARY Low-Noise STEMlab 125-14 devices.
* one or multiple SECONDARY Low-Noise STEMlab 125-14 devices, that are modified in a way that they can receive clock and trigger signals from a PRIMARY device and distribute them to the next SECONDARY device. These are marked with an “S” sticker.

The PRIMARY device provides a clock and trigger over the SATA S1 connector that is then connected to the S2 of the SECONDARY 1 board. SECONDARY 1 then passes the clock forward to SECONDARY 2, SECONDARY 2 to SECONDARY 3, and so on (SECONDARY N to SECONDARY N+1). This way, we can achieve clock and trigger synchronisation of all boards in the system.

For more information about the software, please refer to: :ref:`X-Channel streaming <x-ch_streaming>`.

.. note::
    
    We recommend using :ref:`OS 2.00-23 or higher <prepareSD>` for the X-channel system.

    - With 2.00 OS both the PRIMARY and the SECONDARY devices use the SAME OS!
    - With 1.04 OS the PRIMARY and SECONDARY boards use DIFFERENT OS!


Setup
=========

.. figure:: img/Primary-and-secondary.png
    :width: 800

#.  Connect all Red Pitayas to the same network via ethernet cables (switch or router that is connected to the client PC).

.. note::

    Make sure that your network has enough throughput for all the data you are about to stream. It is also recommended to use a dedicated network only for the X-channel system.


#.  Connect the SATA cables between the PRIMARY and SECONDARY devices.

    PRIMARY SATA S1 -> SECONDARY 1 SATA S2
    SECONDARY 1 SATA S1 -> SECONDARY 2 SATA S2
    SECONDARY 2 SATA S1 -> SECONDARY 3 SATA S2
    ...


Pinout
===========

.. figure:: ../125-14/img/Red_Pitaya_pinout.jpg
    :width: 700


Technical specifications (one board)
------------------------------------

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Basic**                                                               |
    +====================================+====================================+
    | Processor                          | DUAL CORE ARM CORTEX A9            |
    +------------------------------------+------------------------------------+
    | FPGA                               | FPGA Xilinx Zynq 7010 SOC          |
    +------------------------------------+------------------------------------+
    | RAM                                | 512 MB (4 Gb)                      |
    +------------------------------------+------------------------------------+
    | System memory                      | Micro SD up to 32 GB               |
    +------------------------------------+------------------------------------+
    | Console connection                 | Micro USB                          |
    +------------------------------------+------------------------------------+
    | Power connector                    | Micro USB                          |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Power consumption                  | 5 V, 2 A max                       |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Connectivity**                                                        |
    +====================================+====================================+
    | Ethernet                           | 1 Gbit                             |
    +------------------------------------+------------------------------------+
    | USB                                | USB 2.0                            |
    +------------------------------------+------------------------------------+
    | Wi-Fi                              | requires Wi-Fi dongle              |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **RF inputs**                                                           |
    +====================================+====================================+
    | RF input channels                  | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 125 MS/s                           |
    +------------------------------------+------------------------------------+
    | ADC resolution                     | 14 bit                             |
    +------------------------------------+------------------------------------+
    | Input impedance                    | 1 MΩ / 10 pF                       |
    +------------------------------------+------------------------------------+
    | Full scale voltage range           | ±1 V (LV) and ±20 V (HV)           |
    +------------------------------------+------------------------------------+
    | Input coupling                     | DC                                 |
    +------------------------------------+------------------------------------+
    | Absolute max. Input voltage range  | 30 V                               |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Input ESD protection               | Yes                                |
    +------------------------------------+------------------------------------+
    | Overload protection                | Protection diodes                  |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | DC - 60 MHz                        |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **RF outputs**                                                          |
    +====================================+====================================+
    | RF output channels                 | 2                                  |
    +------------------------------------+------------------------------------+
    | Sample rate                        | 125 MS/s                           |
    +------------------------------------+------------------------------------+
    | DAC resolution                     | 14 bit                             |
    +------------------------------------+------------------------------------+
    | Load impedance                     | 50 Ω                               |
    +------------------------------------+------------------------------------+
    | Voltage range                      | ±1 V                               |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Short circuit protection           | Yes                                |
    |                                    |                                    |
    +------------------------------------+------------------------------------+
    | Connector type                     | SMA                                |
    +------------------------------------+------------------------------------+
    | Output slew rate                   | 2 V / 10 ns                        |
    +------------------------------------+------------------------------------+
    | Bandwidth                          | DC - 50 MHz                        |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Extension connector**                                                 | 
    +====================================+====================================+
    | Digital IOs                        | 22                                 |
    +------------------------------------+------------------------------------+
    | Analog inputs                      | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog input voltage range         | 0 – 3.5 V                          |
    +------------------------------------+------------------------------------+
    | Analog input resolution            | 12 bits                            |
    +------------------------------------+------------------------------------+
    | Analog input sample rate           | 100 kS/s                           |
    +------------------------------------+------------------------------------+
    | Analog outputs                     | 4                                  |
    +------------------------------------+------------------------------------+
    | Analog output voltage range        | 0 – 1.8 V                          |
    +------------------------------------+------------------------------------+
    | Analog output resolution           | 8 bits                             |
    +------------------------------------+------------------------------------+
    | Analog output sample rate          | ≲ 3.2 MS/s                         |
    +------------------------------------+------------------------------------+
    | Analog output bandwidth            | ≈ 160 kHz                          |
    +------------------------------------+------------------------------------+
    | Communication interfaces           | I2C, SPI, UART, CAN                |
    +------------------------------------+------------------------------------+
    | Available voltages                 | +5 V, +3.3 V, -4 V                 |
    +------------------------------------+------------------------------------+
    | External ADC clock                 |  Yes                               |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+------------------------------------+
    | **Synchronisation**                                                     |
    +====================================+====================================+
    | Trigger input                      | Through extension connector        |
    +------------------------------------+------------------------------------+
    | Daisy chain connection             | Over SATA connection               |
    |                                    | (up to 500 Mbps)                   |
    +------------------------------------+------------------------------------+
    | Ref. clock input                   | N/A                                |
    +------------------------------------+------------------------------------+

|

.. table::
    :widths: 40 40

    +------------------------------------+-------------------------------------------+
    | **More**                                                                       |
    +====================================+===========================================+
    | Options                            | 4-Ch IN + 4-Ch OUT                        |
    |                                    +-------------------------------------------+
    |                                    | 6-Ch IN + 6-Ch OUT                        |
    |                                    +-------------------------------------------+
    |                                    | (2*x)-Ch IN + (2*x)-Ch OUT; (3 < x < 8)   |
    |                                    +-------------------------------------------+
    |                                    | 16-Ch IN + 16-Ch OUT                      |
    +------------------------------------+-------------------------------------------+


.. note::

    For more information, please refer to the :ref:`Product comparison table <rp-board-comp>` and :ref:`STEMlab 125-14 Low-Noise <top_125_14_LN>`.



Other specifications
=====================

For all other specifications please refer to standard :ref:`STEMlab 125-14 specs <top_125_14>`.


FAQ
=====

Comparison between Red Pitaya X-channel System and Click Shield synchronisation?
---------------------------------------------------------------------------------

The comparison between :ref:`Red Pitaya X-Channel System and Red Pitaya Click Shield Synchronisation is available here <click_shield_Q&A>`.


Can a different Red Pitaya STEMlab 125-14 unit be used as a primary device in the X-channel system?
--------------------------------------------------------------------------------------------------------

Yes, you can use any version of the STEMlab 125-14 as the primary device. This includes:

- STEMlab 125-14 LN
- STEMlab 125-14 LN Z7020
- STEMlab 125-14 4-Input
- STEMlab 125-14 Ext Clk (Please note that an external clock must be provided)


Can I boot the secondary/external clock devices without the external clock present?
---------------------------------------------------------------------------------------

The official Red Pitaya OS will not boot without providing an external clock as it relies on reading the FPGA register map, which is available if the ADC clock is present.
However, by modifying the software, the Linux OS itself can boot even without the external clock present, but please note it will crash when trying to read from the FPGA without the external clock present.



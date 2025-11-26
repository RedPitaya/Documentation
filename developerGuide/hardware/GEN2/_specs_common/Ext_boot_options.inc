
The |E3| on the |STEMlab 125-14 PRO Gen 2| and |STEMlab 125-14 PRO Z7020 Gen 2| provides pins for connecting **external QSPI** (SFSPI pins) or **eMMC** (EMMC pins) storage devices.

These storage chips should be located on an external module (for example, the :ref:`E3 Add-on board <E3_HW>`).

For information on how to configure the boot mode, please refer to the :ref:`External Booting Options <SW_ext_boot>` section.

Boot Mode Selection
~~~~~~~~~~~~~~~~~~~

.. note::

    More information regarding booting the Red Pitaya board from external storage will be provided in future documentation updates.

|

E3 Boot Interface Pins
~~~~~~~~~~~~~~~~~~~~~~~

**QSPI Flash Pins (SFSPI):**

.. table::
    :widths: 15 35 35 15

    +----------+------------------------+------------------------+-------------------+
    | **Pin**  | **Signal**             | **FPGA Pin**           | **Description**   |
    +==========+========================+========================+===================+
    | 28       | SFSPI_IO3              | A6 (PS_MIO5_500)       | Data line 3       |
    +----------+------------------------+------------------------+-------------------+
    | 30       | SFSPI_IO2              | B7 (PS_MIO4_500)       | Data line 2       |
    +----------+------------------------+------------------------+-------------------+
    | 32       | SFSPI_IO1              | D6 (PS_MIO3_500)       | Data line 1       |
    +----------+------------------------+------------------------+-------------------+
    | 34       | SFSPI_IO0              | B8 (PS_MIO2_500)       | Data line 0       |
    +----------+------------------------+------------------------+-------------------+
    | 36       | SFSPI_CS#              | A7 (PS_MIO1_500)       | Chip select       |
    +----------+------------------------+------------------------+-------------------+
    | 38       | SFSPI_SCK              | A5 (PS_MIO6_500)       | Clock             |
    +----------+------------------------+------------------------+-------------------+

|

**eMMC Pins:**

.. table::
    :widths: 15 35 35 15

    +----------+------------------------+------------------------+-------------------+
    | **Pin**  | **Signal**             | **FPGA Pin**           | **Description**   |
    +==========+========================+========================+===================+
    | 10       | EMMC_CMD               | C17 (PS_MIO41_501)     | Command line      |
    +----------+------------------------+------------------------+-------------------+
    | 12       | EMMC_DAT3              | B15 (PS_MIO45_501)     | Data line 3       |
    +----------+------------------------+------------------------+-------------------+
    | 14       | EMMC_DAT2              | F13 (PS_MIO44_501)     | Data line 2       |
    +----------+------------------------+------------------------+-------------------+
    | 18       | EMMC_DAT1              | A9 (PS_MIO43_501)      | Data line 1       |
    +----------+------------------------+------------------------+-------------------+
    | 20       | EMMC_DAT0              | E12 (PS_MIO42_501)     | Data line 0       |
    +----------+------------------------+------------------------+-------------------+
    | 24       | EMMC_CLK               | D14 (PS_MIO40_501)     | Clock             |
    +----------+------------------------+------------------------+-------------------+

|

**Control & Power Pins:**

.. table::
    :widths: 15 35 35 15

    +----------+------------------------+------------------------+-------------------+
    | **Pin**  | **Signal**             | **FPGA Pin**           | **Description**   |
    +==========+========================+========================+===================+
    | 2        | E3_SHDN                | E6 (PS_MIO0_500)       | Module shutdown   |
    +----------+------------------------+------------------------+-------------------+
    | 4        | E3_WDT_KICK            | D8 (PS_MIO7_500)       | Watchdog kick     |
    +----------+------------------------+------------------------+-------------------+
    | 6        | SDIO_SEL [#f4]_        | D16 (PS_MIO46_501)     | Boot mode select  |
    +----------+------------------------+------------------------+-------------------+
    | 39, 40   | +5V                    | \-                     | Power supply      |
    +----------+------------------------+------------------------+-------------------+

|


.. note::

    More information regarding booting the Red Pitaya board from external storage will be provided in future documentation updates.

.. _signal_mapping:

###################
Signal Mapping
###################

This section describes the physical connections between Red Pitaya's FPGA pins and external connectors, including XADC analog inputs, GPIO pins, and LEDs. These mappings are defined in the device tree and are essential for understanding how to interface with Red Pitaya hardware.

.. seealso::

    For information about device tree configuration and loading, see :ref:`device_tree`.

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

**********************************
XADC Analog Inputs
**********************************

Red Pitaya provides four analog inputs (AI0-AI3) mapped through the XADC (Xilinx Analog-to-Digital Converter). These inputs are accessible via the Linux IIO (Industrial I/O) subsystem.

Physical Connections
==========================

+--------+----------+---------+-----------------------+--------------------+------------------+
| E2     | ZYNQ p/n | XADC in | IIO filename          | Measurement target | Full scale range |
+========+==========+=========+=======================+====================+==================+
| AI0    | B19/A20  | AD8     | in_voltage11_raw      | general purpose    | 3.50 V           |
+--------+----------+---------+-----------------------+--------------------+------------------+
| AI1    | C20/B20  | AD0     | in_voltage9_raw       | general purpose    | 3.50 V           |
+--------+----------+---------+-----------------------+--------------------+------------------+
| AI2    | E17/D18  | AD1     | in_voltage10_raw      | general purpose    | 3.50 V           |
+--------+----------+---------+-----------------------+--------------------+------------------+
| AI3    | E18/E19  | AD9     | in_voltage12_raw      | general purpose    | 3.50 V           |
+--------+----------+---------+-----------------------+--------------------+------------------+
|        | K9 /L10  | AD      | in_voltage8_vpvn_raw  | 5V power supply    | 6.10 V           |
+--------+----------+---------+-----------------------+--------------------+------------------+

The input range is 0 - 3.5 V by default (unipolar mode).

|

Bipolar Mode Configuration
============================

.. tabs::

    .. group-tab:: Gen 2

        For bipolar operation (±3.5 V), resistor R255 must be removed, and **Ext. com. mode** pin must be connected to a 0.5-1 V voltage reference.

        .. figure:: ../getting_started/img/device_tree/XADC_R255.png
            :align: center
            :width: 800

        Afterwards, open the Red Pitaya v0.94 (or v0.94_250 for SIGNALlab 250-12) FPGA project. In the block diagram, the XADC wizard has a setting in the 
        Channel Sequencer page to switch the XADCs to bipolar mode. After rebuilding the FPGA, the values are read as 12-bit 2's complement values.

    .. group-tab:: Original Generation

        For bipolar operation (±3.5 V), resistor R273 must be removed, and **Ext. com. mode** pin must be connected to a 0.5-1 V voltage reference.

        .. figure:: ../getting_started/img/device_tree/XADC_R273.png
            :align: center
            :width: 800
        
        Afterwards, open the Red Pitaya v0.94 (or v0.94_250 for SIGNALlab 250-12) FPGA project. In the block diagram, the XADC wizard has a setting in the 
        Channel Sequencer page to switch the XADCs to bipolar mode. After rebuilding the FPGA, the values are read as 12-bit 2's complement values.

|

Voltage Dividers
==========================

The XADC inputs use voltage dividers to scale input voltages to the safe range for the ADC.

5V Power Supply
--------------------

The fourth XADC input (AD) is connected to a voltage divider for measuring the internal 5V power supply voltage:

.. code-block:: console

                           +-----------------0  Vout
              -----------  |  -----------
    Vin  0----| 56.0 kΩ |--+--| 4.99 kΩ |----0  GND
              -----------     -----------

.. math::

    ratio = \frac{4.99 k\Omega}{56.0 k\Omega +4.99 k\Omega} = 0.0818

    range = \frac{0.5 V}{ratio} = 6.11 V


Slow Analog Inputs
------------------------------------

The ADC inputs connected to the slow analog inputs have an input voltage range of ±0.5 V. Resistor dividers are used to scale the input voltage range to ±3.5 V:

.. code-block:: console

                           +-----------------0  Vout
              -----------  |  -----------
    Vin  0----| 30.0 kΩ |--+--| 4.99 kΩ |----0  GND
              -----------     -----------

.. math::

    ratio = \frac{4.99 k\Omega}{30.0 k\Omega + 4.99  k\Omega} = 0.143

    range = \frac{0.5 V}{ratio} = 3.50 V

|

Reading XADC Values
==========================

XADC values can be read from Linux userspace through the IIO interface:

.. code-block:: bash

    # Read raw ADC value
    cat /sys/bus/iio/devices/iio:device0/in_voltage9_raw
    
    # Read voltage scale
    cat /sys/bus/iio/devices/iio:device0/in_voltage9_scale
    
    # Calculate actual voltage: raw_value * scale

.. note::

    The scale factor converts raw ADC readings to millivolts. Remember to account for the voltage divider ratios when calculating actual input voltages.

|

**********************************
GPIO and LEDs
**********************************

Red Pitaya's GPIO pins and LEDs can be controlled from Linux userspace via ``sysfs``. The handling depends on whether the pins are connected to the PS (Processing System) or the PL (Programmable Logic). 
The device tree defines which pins are managed by the PS and which are in the PL.

MIO vs PL/EMIO
==========================

- **MIO (Multiplexed I/O)**: Pins directly controlled by PS, accessed via standard GPIO ``sysfs`` interface. Each pin has a few multiplexed functions selectable via pinctrl overlays. 
  The drivers for Linux are provided by AMD/Xilinx.

- **PL/EMIO**: Pins controlled by FPGA logic, require FPGA design to define access method (e.g., custom AXI GPIO peripheral). Access method depends on FPGA implementation. 
  If the pin signals in the FPGA sources are wired to EMIO, they can be accessed via the PS GPIO interface.

.. warning::

    The LEDs and GPIOs directly connected to the PS are accessible only if the FPGA is not loaded or if the FPGA code does not change the signal state. 
    Be aware that changing these signals when the FPGA is loaded can cause unpredictable behavior.

|

GPIO Pin Assignment
==========================

The following tables show the complete GPIO pin mapping for Red Pitaya.

PL/EMIO Pins
--------------------

+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| FPGA    | Connector  | GPIO               | MIO/EMIO index   | ``sysfs`` index              | Comments, LED color, dedicated meaning    |
+=========+============+====================+==================+==============================+===========================================+
|         |            |                    |                  |                              | Green = *Power Good* status               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
|         |            |                    |                  |                              | Blue = FPGA programming *DONE*            |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``M15`` | E1         | ``exp_n_io [7]``   | ``EMIO[23]``     | ``906+54+[23] = 983``        | DIO7_N                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``J16`` | E1         | ``exp_n_io [6]``   | ``EMIO[22]``     | ``906+54+[22] = 982``        | DIO6_N                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``L17`` | E1         | ``exp_n_io [5]``   | ``EMIO[21]``     | ``906+54+[21] = 981``        | DIO5_N                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``L15`` | E1         | ``exp_n_io [4]``   | ``EMIO[20]``     | ``906+54+[20] = 980``        | DIO4_N                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``K18`` | E1         | ``exp_n_io [3]``   | ``EMIO[19]``     | ``906+54+[19] = 979``        | DIO3_N                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``H18`` | E1         | ``exp_n_io [2]``   | ``EMIO[18]``     | ``906+54+[18] = 978``        | DIO2_N                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``H17`` | E1         | ``exp_n_io [1]``   | ``EMIO[17]``     | ``906+54+[17] = 977``        | DIO1_N                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``G18`` | E1         | ``exp_n_io [0]``   | ``EMIO[16]``     | ``906+54+[16] = 976``        | DIO0_N                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``M14`` | E1         | ``exp_p_io [7]``   | ``EMIO[15]``     | ``906+54+[15] = 975``        | DIO7_P                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``K16`` | E1         | ``exp_p_io [6]``   | ``EMIO[14]``     | ``906+54+[14] = 974``        | DIO6_P                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``L16`` | E1         | ``exp_p_io [5]``   | ``EMIO[13]``     | ``906+54+[13] = 973``        | DIO5_P                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``L14`` | E1         | ``exp_p_io [4]``   | ``EMIO[12]``     | ``906+54+[12] = 972``        | DIO4_P                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``K17`` | E1         | ``exp_p_io [3]``   | ``EMIO[11]``     | ``906+54+[11] = 971``        | DIO3_P                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``J18`` | E1         | ``exp_p_io [2]``   | ``EMIO[10]``     | ``906+54+[10] = 970``        | DIO2_P                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``H16`` | E1         | ``exp_p_io [1]``   | ``EMIO[9]``      | ``906+54+[ 9] = 969``        | DIO1_P                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``G17`` | E1         | ``exp_p_io [0]``   | ``EMIO[8]``      | ``906+54+[ 8] = 968``        | DIO0_P                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``J14`` |            | LED ``[7]``        | ``EMIO[7]``      | ``906+54+[ 7] = 967``        | Orange LED7                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``J15`` |            | LED ``[6]``        | ``EMIO[6]``      | ``906+54+[ 6] = 966``        | Orange LED6                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``G14`` |            | LED ``[5]``        | ``EMIO[5]``      | ``906+54+[ 5] = 965``        | Orange LED5                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``K14`` |            | LED ``[4]``        | ``EMIO[4]``      | ``906+54+[ 4] = 964``        | Orange LED4                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``H15`` |            | LED ``[3]``        | ``EMIO[3]``      | ``906+54+[ 3] = 963``        | Orange LED3                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``G15`` |            | LED ``[2]``        | ``EMIO[2]``      | ``906+54+[ 2] = 962``        | Orange LED2                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``F17`` |            | LED ``[1]``        | ``EMIO[1]``      | ``906+54+[ 1] = 961``        | Orange LED1                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``F16`` |            | LED ``[0]``        | ``EMIO[0]``      | ``906+54+[ 0] = 960``        | Orange LED0                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+

|

PS MIO Pins
--------------------

+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| FPGA    | Connector  | GPIO               | MIO/EMIO index   | ``sysfs`` index              | Comments, LED color, dedicated meaning    |
+=========+============+====================+==================+==============================+===========================================+
|         |            | LED ``[8]``        |  ``MIO[ 0]``     | ``906+   [ 0]   = 906``      | Orange = SD card access                   |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
|         |            | LED ``[9]``        |  ``MIO[ 7]``     | ``906+   [ 7]   = 913``      | Red    = CPU heartbeat                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``D5``  | ``E2[ 7]`` | UART1_TX           |  ``MIO[ 8]``     | ``906+   [ 8]   = 914``      | Output only                               |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``B5``  | ``E2[ 8]`` | UART1_RX           |  ``MIO[ 9]``     | ``906+   [ 9]   = 915``      | [#f1]_                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``E9``  | ``E2[ 3]`` | SPI1_MOSI          |  ``MIO[10]``     | ``906+   [10]   = 916``      | [#f1]_                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``C6``  | ``E2[ 4]`` | SPI1_MISO          |  ``MIO[11]``     | ``906+   [11]   = 917``      | [#f1]_                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``D9``  | ``E2[ 5]`` | SPI1_SCK           |  ``MIO[12]``     | ``906+   [12]   = 918``      | [#f1]_                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``E8``  | ``E2[ 6]`` | SPI1_CS#           |  ``MIO[13]``     | ``906+   [13]   = 919``      | [#f1]_                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``B13`` | ``E2[ 9]`` | I2C0_SCL           |  ``MIO[50]``     | ``906+   [50]   = 956``      | [#f1]_                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+
| ``B9``  | ``E2[10]`` | I2C0_SDA           |  ``MIO[51]``     | ``906+   [51]   = 957``      | [#f1]_                                    |
+---------+------------+--------------------+------------------+------------------------------+-------------------------------------------+

.. [#f1] Requires ``pinctrl`` changes to be active.

|

Linux Sysfs Access
==========================

LEDs can be controlled from Linux userspace using the sysfs interface:

.. code-block:: bash

    # Enable LED heartbeat trigger
    echo heartbeat > /sys/class/leds/led0/trigger
    
    # Set LED brightness (0 = off, 1 = on)
    echo 1 > /sys/class/leds/led0/brightness
    
    # Turn off LED
    echo 0 > /sys/class/leds/led0/brightness

For GPIO pins, use the GPIO sysfs interface:

.. code-block:: bash

    # Export GPIO pin
    echo 960 > /sys/class/gpio/export
    
    # Set direction (out or in)
    echo out > /sys/class/gpio/gpio960/direction
    
    # Set value (0 or 1)
    echo 1 > /sys/class/gpio/gpio960/value
    
    # Read value
    cat /sys/class/gpio/gpio960/value
    
    # Unexport when done
    echo 960 > /sys/class/gpio/unexport

|

**********************************
PS Pinctrl Overlays
**********************************

Red Pitaya provides device tree overlay files that allow you to repurpose PS MIO signals. These overlays modify the pinctrl configuration to reassign pins from their default functions (SPI, I2C, UART) to GPIO.

Available Overlays
==========================

.. table:: PS Pinctrl Overlay Files
    :widths: 30 70

    +-------------------+------------------------------------------------------------------+
    | Overlay File      | Description                                                      |
    +===================+==================================================================+
    | spi2gpio.dtsi     | Reassigns SPI1 signals to GPIO (MOSI, MISO, SCLK, CS)            |
    +-------------------+------------------------------------------------------------------+
    | i2c2gpio.dtsi     | Reassigns I2C0 signals to GPIO (SDA, SCL)                        |
    +-------------------+------------------------------------------------------------------+
    | uart2gpio.dtsi    | Reassigns UART1 signals to GPIO (TX, RX)                         |
    +-------------------+------------------------------------------------------------------+
    | miso2gpio.dtsi    | Reassigns only MISO signal to GPIO (keeps other SPI1 pins)       |
    +-------------------+------------------------------------------------------------------+

These overlay files are typically included in the project's device tree source when specific signal configurations are needed.

|

**********************************
SPI Configuration Example
**********************************

The SPI interface on Red Pitaya can be configured through the device tree. A common example is changing the CS (Chip Select) polarity.

By default, the CS state is HIGH (inactive) on all Red Pitaya boards. To set the default value to LOW (active), modify the device tree:

1.  **Open the device tree source file:**

    .. code-block:: console

        root@rp-f01c3d:~# rw
        root@rp-f01c3d:~# nano /opt/redpitaya/dts/$(monitor -f)/dtraw.dts

2.  **Find the SPI device** node ``spidev@0`` and add the ``spi-cs-high`` property:

    .. code-block:: dts

        spidev@0 {
            compatible = "spidev";
            reg = <0>;
            spi-max-frequency = <50000000>;
            spi-cs-high;  /* Add this line */
        };

3.  **Recompile and reboot:**

    .. code-block:: console

        root@rp-f01c3d:~# cd /opt/redpitaya/dts/$(monitor -f)/
        root@rp-f01c3d:~# dtc -I dts -O dtb ./dtraw.dts -o devicetree.dtb
        root@rp-f01c3d:~# reboot

.. note::

    The settings are applied only after the device tree is loaded. When the board starts up, the CS value is in the HIGH state but will change to LOW after the boot is complete.

.. note::

    You can also switch the SPI CS mode at runtime through the Red Pitaya API:
    
    * ``rp_SPI_GetCSMode``
    * ``rp_SPI_SetCSMode``
    
    See the :ref:`hw api <command_list>` command reference for more details.

|

**********************************
Troubleshooting
**********************************

GPIO/LED Access Issues
================================

**Error: Permission denied when accessing sysfs**

- **Cause**: Insufficient permissions or SELinux restrictions
- **Solution**:

    - Run commands as root or use sudo
    - Check file permissions in /sys/class/gpio/ or /sys/class/leds/

**Error: GPIO already exported**

- **Cause**: GPIO pin already exported by another process or previous session
- **Solution**:

    - Unexport the GPIO: ``echo <pin_number> > /sys/class/gpio/unexport``
    - Check for other processes using the GPIO: ``lsof | grep gpio``

**Symptom: GPIO changes don't affect hardware**

- **Cause**: FPGA is loaded and controlling the pins
- **Solution**:

    - Unload FPGA or use FPGA that doesn't control these pins
    - Use appropriate MIO pins instead of EMIO pins if PS control is needed

|

XADC Reading Issues
================================

**Error: IIO device not found**

- **Cause**: XADC not enabled in device tree or driver not loaded
- **Solution**:

    - Verify xadc node exists in device tree
    - Check if IIO driver is loaded: ``lsmod | grep xilinx``
    - Verify device appears in /sys/bus/iio/devices/

**Symptom: Incorrect voltage readings**

- **Cause**: Wrong scaling factor or voltage divider calculation
- **Solution**:

    - Verify using correct formula for input type (5V supply vs general purpose)
    - Check if bipolar mode resistor R273 (original) or R255 (Gen 2) is present/removed as expected
    - Calibrate readings against known reference voltage

|

**********************************
Additional Resources
**********************************

- :ref:`device_tree` - Device tree configuration and compilation
- :ref:`fpga_install_sdk` - SDK installation and HSI tool usage
- :ref:`overlay_util` - Quick reference for overlay script
- :ref:`fpga_advanced_loading` - Comprehensive overlay script guide
- `Linux IIO Documentation <https://www.kernel.org/doc/html/latest/driver-api/iio/index.html>`_ - Industrial I/O subsystem documentation
- `GPIO Sysfs Interface <https://www.kernel.org/doc/Documentation/gpio/sysfs.txt>`_ - Kernel GPIO interface documentation

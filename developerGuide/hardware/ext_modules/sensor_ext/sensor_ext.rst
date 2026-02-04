.. _sensor_extension_module:

#########################
Sensor extension module
#########################


Description
=============

The Sensor extension board redirects the digital and analog pins of the Red Pitaya so that Groove sensors are easily connected. It also has the same pinout as Arduino shields.

.. figure:: img/Sensor-Extension-Module.jpg
  :width: 500

|

Each Groove connector connects to the power (3V3), ground, and two digital or analog pins. As Red Pitaya only has four analog inputs, some pins overlap. You can control the connector pins and the sensors attached by reading data from either digital or analog pins.

Code examples of controlling the digital and analog inputs and outputs are available :ref:`here <examples>`.

Getting started with electronics is way more fun and engaging when you have loads of sensors you can use straight away. Whether you want to measure temperature, vibration, movement, etc.,
we have an extension module compatible with **Grove** modules from |Seeed-Grove|. All you need to do is select the desired module, find the correct connector, and get going with your project.

.. figure:: img/extension_module_and_sensors.png
  :width: 500

|

Want to use an Arduino Uno shield? They can be plugged directly into the Sensor extension board. The extension module can also be powered from the external power supply using a micro USB cable.

A set of nine Jumpers can reconnect certain extension module connectors to different :ref:`E1 <E1_orig_gen>` or :ref:`E2 <E2_orig_gen>` pins or change power supply settings.
For example, with J1 and J3, you can set the shield power source (VCC) to either an external power supply or get the power from Red Pitaya.
A full schematic of the extension module is available below.

.. note::

    The extension module is available for purchase from the Red Pitaya |redpitaya-store|.


Connectors and Jumpers
=========================

The black connectors on the sides are compatible with Arduino, the white connectors on the front provide analog inputs, and the two rows of beige connectors at the centre provide digital I/O, UART, I2C, or analog outputs. On the bottom, there are connectors to the Red Pitaya board.


Grove module connectors
--------------------------

These are dedicated connectors compatible with `Grove modules <https://wiki.seeedstudio.com/Grove_System/>`_.

There are six connector types available:

* **AI** Analog input (0 - 3.3 V)
* **AO** Analog output
* **I2C** (3.3 V)
* **UART** (3.3 V)
* **DIO** Digital input/output (3.3 V, not 5 V tolerant)

+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
| **Connector**       | CN0       | CN1       | CN2       | CN3       | CN4       | CN5       | CN6       | CN7       | CN8       | CN9       | CN10      | CN11      | CN12      |
+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
| **Groove Pin\Type** | AI        | AI        | AI        | AO        | I2C       | I2C       | I2C       | UART      | DIO       | DIO       | DIO       | DIO       | DIO       |
+=====================+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+
| ``1``               | AI0       | AI1       | AI2       | AO0       | SCL       | SCL       | SCL       | RX        | IO8       | IO6       | IO4       | IO2       | IO0       |
+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
| ``2``               | AI1       | AI2       | AI3       | AO1       | SDA       | SDA       | SDA       | TX        | IO9       | IO7       | IO5       | IO3       | IO1       |
+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
| ``3``               | VCC       | VCC       | VCC       | VCC       | VCC       | VCC       | VCC       | VCC       | VCC       | VCC       | VCC       | VCC       | VCC       |
+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
| ``4``               | GND       | GND       | GND       | GND       | GND       | GND       | GND       | GND       | GND       | GND       | GND       | GND       | GND       |
+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+

|

Arduino shield compatible connectors
--------------------------------------

This set of connectors is partially compatible with the Arduino shield connector.

+--------------+-----------+-------------------+
| **Function** |  **Pin**  | **Comment**       |
+==============+===========+===================+
| IO0          | 1         | D[0]              |
+--------------+-----------+-------------------+
| IO1          | 2         | D[1]              |
+--------------+-----------+-------------------+
| IO2          | 3         | D[2]              |
+--------------+-----------+-------------------+
| IO3          | 4         | D[3]              |
+--------------+-----------+-------------------+
| IO4          | 5         | D[4]              |
+--------------+-----------+-------------------+
| IO5          | 6         | D[5]              |
+--------------+-----------+-------------------+
| IO6          | 7         | D[6]              |
+--------------+-----------+-------------------+
| IO7          | 8         | D[7]              |
+--------------+-----------+-------------------+

|

+--------------+-----------+-------------------+
| **Function** |  **Pin**  | **Comment**       |
+==============+===========+===================+
| IO8          | 1         | D[8]              |
+--------------+-----------+-------------------+
| IO9          | 2         | D[9]              |
+--------------+-----------+-------------------+
| IO10         | 3         | D[10]             |
+--------------+-----------+-------------------+
| IO11         | 4         | D[11]             |
+--------------+-----------+-------------------+
| IO12         | 5         | D[12]             |
+--------------+-----------+-------------------+
| IO13         | 6         | D[13]             |
+--------------+-----------+-------------------+
| GND          | 7         |                   |
+--------------+-----------+-------------------+
| AREF         | 8         | NC                |
+--------------+-----------+-------------------+
| SDA          | 9         | I2C_SDA           |
+--------------+-----------+-------------------+
| SCL          | 0         | I2C_SCL           |
+--------------+-----------+-------------------+

|

+--------------+-----------+-------------------+
| **Function** |  **Pin**  | **Comment**       |
+==============+===========+===================+
| A6           | 1         | NC                |
+--------------+-----------+-------------------+
| A7           | 2         | NC                |
+--------------+-----------+-------------------+
| Reset        | 3         | NC                |
+--------------+-----------+-------------------+
| +3.3 V       | 4         |                   |
+--------------+-----------+-------------------+
| +5.0 V       | 5         |                   |
+--------------+-----------+-------------------+
| GND          | 6         |                   |
+--------------+-----------+-------------------+
| GND          | 7         |                   |
+--------------+-----------+-------------------+
| +VIN         | 8         | NC                |
+--------------+-----------+-------------------+

|

Jumpers
---------

+----------------+------------------+---------------------+--------------------+
| **Jumper Num** |  **Output Pin**  | **Position 1**      | **Position 2**     |
+================+==================+=====================+====================+
| J1             | +5V_SEL          | +5V_EXT             | +5V (Red Pitaya)   |
+----------------+------------------+---------------------+--------------------+
| J2             | VCC              | +3V3_SEL            | +5V_SEL            |
+----------------+------------------+---------------------+--------------------+
| J3             | +3V3_SEL         | +3V3 (Red Pitaya)   | +3V3_LDO           |
+----------------+------------------+---------------------+--------------------+
| J4             | IO13             | SPI_SCK             | DIO5_N             |
+----------------+------------------+---------------------+--------------------+
| J5             | IO12             | SPI_MISO            | DIO4_N             |
+----------------+------------------+---------------------+--------------------+
| J6             | IO11             | SPI_MOSI            | DIO3_N             |
+----------------+------------------+---------------------+--------------------+
| J7             | IO6              | SPI_CS              | DIO2_N             |
+----------------+------------------+---------------------+--------------------+
| J8             | IO1              | UART_TX             | DIO1_P             |
+----------------+------------------+---------------------+--------------------+
| J9             | IO0              | UART_RX             | DIO0_P             |
+----------------+------------------+---------------------+--------------------+

|

Schematics
============

* `Schematics_Sensor_Shield.pdf <https://downloads.redpitaya.com/doc/Schematics/Schematics_Sensor_Shield.pdf>`_.


Examples of Groove Sensor
==========================


Sensors
---------

========================================================================================    ============
Sensor information                                                                          Connector
========================================================================================    ============
**Analog**
|Seeed-temp|                                                                                AI
|Seeed-motion|                                                                              DIO
|Seeed-touch|                                                                               DIO
|Seeed-button|                                                                              DIO
|Seeed-switch|                                                                              DIO
**Digital**
|Seeed-tilt|                                                                                DIO
|Seeed-potentiometer|                                                                       AI
`Light sensor <http://wiki.seeed.cc/Grove-Light_Sensor>`_                                   AI
`Air quality sensor <https://wiki.seeedstudio.com/Grove-Air_Quality_Sensor_v1.3>`_          AI
`Vibration sensor <https://wiki.seeedstudio.com/Grove-Piezo_Vibration_Sensor>`_             AI
`Moisture sensor <https://wiki.seeedstudio.com/Grove-Moisture_Sensor>`_                     AI
`Water sensor <https://wiki.seeedstudio.com/Grove-Water_Sensor>`_                           AI
`Alcohol sensor <https://wiki.seeedstudio.com/Grove-Alcohol_Sensor>`_                       AI
Barometer ``not supported at the moment``                                                   I2C
`Sound sensor <http://wiki.seeed.cc/Grove-Sound_Sensor>`_                                   AI
`UV sensor <https://wiki.seeedstudio.com/Grove-UV_Sensor>`_                                 AI
Accelerometer ``not supported at the moment``                                               I2C
========================================================================================    ============

|

========================================================================================    ============
Actuators                                                                                   Connector
========================================================================================    ============
`Relay <https://wiki.seeedstudio.com/Grove-Relay>`_                                         DIO
========================================================================================    ============

|

========================================================================================    ============
Indicators                                                                                  Connector
========================================================================================    ============
`Buzzer <https://wiki.seeedstudio.com/Grove-Buzzer>`_                                       DIO
`LED <https://www.seeedstudio.com/grove-led-p-767.html?cPath=156_157>`_                     DIO
|seven_segment_display|                                                                     Digital pins
`LED bar <https://wiki.seeedstudio.com/Grove-LED_Bar>`_                                     Digital pins
`Groove LCD <https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight>`_                        Digital pins
LCD                                                                                         Digital pins
========================================================================================    ============


.. |seven_segment_display| replace:: `7 segment display <https://www.seeedstudio.com/Grove-0-54-Red-Dual-Alphanumeric-Display-p-4031.html?queryID=817e144e20d72ab54938d8288d8f4155&objectID=4031&indexName=bazaar_retailer_products>`__



Code Examples
===============

Example code of how to control the sensors is available here:

- :ref:`Sensor code examples <examples>`




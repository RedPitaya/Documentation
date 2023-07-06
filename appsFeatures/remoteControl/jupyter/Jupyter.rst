#################
Jupyter Notebook
#################

The Jupyter Notebook is an open-source web application that allows you to create and share documents that contain live code, equations, visualizations, explanatory text, and direct control or monitor hardware.
Uses include: data cleaning and transformation, numerical simulation, statistical modeling, machine learning, and much more.

********
Features
********

- In-browser editing of code, with automatic syntax highlighting, indentation, and tab completion/introspection.
- The ability to execute code from the browser, with the results of computations attached to the code which generated 
  them. 
- Displaying the result of computation using rich media representations, such as HTML, LaTeX, PNG, SVG, etc. For 
  example, publication-quality figures rendered by the |matplotlib| library can be included
  inline.
- In-browser editing for rich text using the |Markdown| markup 
  language, which can provide commentary for the code, is not limited to plain text.
- The ability to easily include mathematical notation within markdown cells using LaTeX, and rendered natively by 
  |MathJax|


.. |matplotlib| raw:: html

    <a href="https://matplotlib.org/" target="_blank">matplotlib</a>
    
.. |Markdown| raw:: html

    <a href="https://daringfireball.net/projects/markdown/syntax" target="_blank">Markdown</a>
    
.. |MathJax| raw:: html

    <a href="https://www.mathjax.org/" target="_blank">MathJax</a>


==================
Notebook documents
==================

Notebook documents contain the inputs and outputs of an interactive session as well as additional text that 
accompanies the code but is not meant for execution. In this way, notebook files can serve as a complete computational
record of a session, interleaving executable code with explanatory text, mathematics, and rich representations of
resulting objects. These documents are internal |JSON| files and are saved with 
the *.ipynb* extension. Since JSON is a plain text format, they can be version-controlled and shared with colleagues.

.. |JSON| raw:: html

    <a href="https://en.wikipedia.org/wiki/JSON" target="_blank">JSON</a>


Notebooks may be exported to a range of static formats, including HTML (for example, for blog posts), 
reStructuredText, LaTeX, PDF, and slide shows, via the |nbconvert| command.

.. |nbconvert| raw:: html

    <a href="https://nbconvert.readthedocs.io/en/latest/" target="_blank">nbconvert</a>

Furthermore, any *.ipynb* notebook document available from a public URL can be shared via the Jupyter Notebook Viewer (nbviewer). This service loads the notebook document from the URL and renders it as a static web page. The results may thus be shared with a colleague, or as a public blog post, without other users needing to install the Jupyter notebook themselves. In effect, nbviewer is simply nbconvert as a web service, so you can do your own static conversions with nbconvert without relying on nbviewer.


***************************
Hardware – Extension module
***************************

Although the usage of the Jupyter notebook does not require any additional hardware except the RedPitaya board, getting started with electronics is way more fun and interesting when you have loads of sensors that you can put to good use straight away. Whether you want to measure temperature, vibration, movement, etc., we have an extension module compatible with **Grove** modules from |Seeed®|. All you need to do is to select the desired module, find the correct connector, and get going with your project. We have also placed the Arduino shield headers on the extension module.

.. figure:: img/extension_module_and_sensors.png

The headers enable you to directly connect a variety of different Arduino Uno shields. There is a wide range of Arduino Uno shields. The extension module can be powered from the external power supply via a micro USB connector.
A set of nine JUMPERS is used for reconnecting certain extension module connectors to different :ref:`E1 <E1>` or :ref:`E2 <E2>` pins or changing power supply settings. For example, with J1 and J3, you can set the source of VCC-external or from Red Pitaya. A full schematic of the extension module is available on our website.

.. note:: 

    The extension module is available for purchase from Red Pitaya |store|.
    
.. |Seeed®| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove_System/" target="_blank">Seeed®</a>
    
.. |store| raw:: html

    <a href="https://redpitaya.com/shop/" target="_blank">store</a>
    
==========
Connectors
==========

The black connectors on the sides are compatible with Arduino. The white connectors on the front provide analog inputs, and there are two rows of grey connectors at the centre which provide digital I/O, UART, I2C, or analog outputs. On the bottom, there are connectors to the Red Pitaya board.

.. figure:: img/extension_module.png

~~~~~~~~~~~~~~~~~~~~~~~
Grove module connectors
~~~~~~~~~~~~~~~~~~~~~~~

These are dedicated connectors compatible with |Grove modules|.

.. |Grove modules| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove_System/" target="_blank">Grove modules</a>

There are six connector types available:

* **AI** Analog input (0 - 3.3 V)
* **AO** Analog output
* **I2C** (3.3 V)
* **UART** (3.3 V)
* **DIO** Digital input/output (3.3 V, not 5 V tolerant)

+-------+------+------+------+------+------+------+------+------+------+------+------+------+------+
| conn. | CN0  | CN1  | CN2  | CN3  | CN4  | CN5  | CN6  | CN7  | CN8  | CN9  | CN10 | CN11 | CN12 |
+-------+------+------+------+------+------+------+------+------+------+------+------+------+------+
| type  | AI   | AI   | AI   | AO   | I2C  | I2C  | I2C  | UART | DIO  | DIO  | DIO  | DIO  | DIO  |
+=======+======+======+======+======+======+======+======+======+======+======+======+======+======+
| ``1`` | AI0  | AI1  | AI2  | AO0  | SCL  | SCL  | SCL  | RX   | IO8  | IO6  | IO4  | IO2  | IO0  |
+-------+------+------+------+------+------+------+------+------+------+------+------+------+------+
| ``2`` | AI1  | AI2  | AI3  | AO1  | SDA  | SDA  | SDA  | TX   | IO9  | IO7  | IO5  | IO3  | IO1  |
+-------+------+------+------+------+------+------+------+------+------+------+------+------+------+
| ``3`` | VCC  | VCC  | VCC  | VCC  | VCC  | VCC  | VCC  | VCC  | VCC  | VCC  | VCC  | VCC  | VCC  |
+-------+------+------+------+------+------+------+------+------+------+------+------+------+------+
| ``4`` | GND  | GND  | GND  | GND  | GND  | GND  | GND  | GND  | GND  | GND  | GND  | GND  | GND  |
+-------+------+------+------+------+------+------+------+------+------+------+------+------+------+

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Arduino shield compatible connectors
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This set of connectors is partially compatible with the Arduino shield connector.

+----------+-------+---------------+
| function |  pin  | comment       |
+==========+=======+===============+
| IO0      | ``1`` | D[0]          |
+----------+-------+---------------+
| IO1      | ``2`` | D[1]          |
+----------+-------+---------------+
| IO2      | ``3`` | D[2]          |
+----------+-------+---------------+
| IO3      | ``4`` | D[3]          |
+----------+-------+---------------+
| IO4      | ``5`` | D[4]          |
+----------+-------+---------------+
| IO5      | ``6`` | D[5]          |
+----------+-------+---------------+
| IO6      | ``7`` | D[6]          |
+----------+-------+---------------+
| IO7      | ``8`` | D[7]          |
+----------+-------+---------------+

+----------+--------+---------------+
| function |   pin  | comment       |
+==========+========+===============+
| IO8      |  ``1`` | D[8]          |
+----------+--------+---------------+
| IO9      |  ``2`` | D[9]          |
+----------+--------+---------------+
| IO10     |  ``3`` | D[10]         |
+----------+--------+---------------+
| IO11     |  ``4`` | D[11]         |
+----------+--------+---------------+
| IO12     |  ``5`` | D[12]         |
+----------+--------+---------------+
| IO13     |  ``6`` | D[13]         |
+----------+--------+---------------+
| GND      |  ``7`` |               |
+----------+--------+---------------+
| AREF     |  ``8`` | not connected |
+----------+--------+---------------+
| SDA      |  ``9`` | I2C_SDA       |
+----------+--------+---------------+
| SCL      | ``10`` | I2C_SCL       |
+----------+--------+---------------+

+----------+-------+---------------+
| function |  pin  | comment       |
+==========+=======+===============+
| A6       | ``1`` | not connected |
+----------+-------+---------------+
| A7       | ``2`` | not connected |
+----------+-------+---------------+
| Reset    | ``3`` | not connected |
+----------+-------+---------------+
| +3.3 V   | ``4`` |               |
+----------+-------+---------------+
| +5.0 V   | ``5`` |               |
+----------+-------+---------------+
| GND      | ``6`` |               |
+----------+-------+---------------+
| GND      | ``7`` |               |
+----------+-------+---------------+
| +VIN     | ``8`` | not connected |
+----------+-------+---------------+


*******
Sensors
*******

========================================================================================    ============
Sensor information                                                                          Connector
========================================================================================    ============
|Temperature sensor|                                                                        AI
|Motion sensor|                                                                             DIO
|Touch sensor|                                                                              DIO
|Button|                                                                                    DIO
|Switch|                                                                                    DIO
Digital
|Tilt|                                                                                      DIO
|Potentiometer|                                                                             AI
|Light sensor|                                                                              AI
|Air quality sensor|                                                                        AI
|Vibration sensor|                                                                          AI
|Moisture sensor|                                                                           AI
|Water sensor|                                                                              AI
|Alcohol sensor|                                                                            AI
Barometer ``not supported at the moment``                                                   I2C
|Sound sensor|                                                                              AI
|UV sensor|                                                                                 AI
Accelerometer ``not supported at the moment``                                               I2C
========================================================================================    ============

.. |Temperature sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Sensor_temperature" target="_blank">Temperature sensor</a>

.. |Motion sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor" target="_blank">Motion sensor</a>

.. |Touch sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Touch_Sensor" target="_blank">Touch sensor</a>

.. |Button| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Button" target="_blank">Button</a>
    
.. |Switch| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Switch-P" target="_blank">Switch</a>
    
.. |Tilt| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Tilt_Switch" target="_blank">Tilt</a>
    
.. |Potentiometer| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Slide_Potentiometer" target="_blank">Potentiometer</a>
    
.. |Light sensor| raw:: html

    <a href="http://wiki.seeed.cc/Grove-Light_Sensor" target="_blank">Light sensor</a>

.. |Air quality sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Air_Quality_Sensor_v1.3" target="_blank">Air quality sensor</a>
    
.. |Vibration sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Piezo_Vibration_Sensor" target="_blank">Vibration sensor</a>
    
.. |Moisture sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Moisture_Sensor" target="_blank">Moisture sensor</a>
    
.. |Water sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Water_Sensor" target="_blank">Water sensor</a>
    
.. |Barometer| raw:: html

    <a href="" target="_blank">Barometer</a>
    
.. |Alcohol sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Alcohol_Sensor" target="_blank">Alcohol sensor</a>
    
.. |Sound sensor| raw:: html

    <a href="http://wiki.seeed.cc/Grove-Sound_Sensor" target="_blank">Sound sensor</a>

.. |UV sensor| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-UV_Sensor" target="_blank">UV sensor</a>

.. |Accelerometer| raw:: html

    <a href="" target="_blank">Accelerometer</a>

========================================================================================    ============
Actuators                                                                                   Connector
========================================================================================    ============
|Relay|                                                                                     DIO
========================================================================================    ============

.. |Relay| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Relay" target="_blank">Relay</a>

========================================================================================    ============
Indicators                                                                                  Connector
========================================================================================    ============
|Buzzer|                                                                                    DIO
|LED|                                                                                       DIO
|7 segment display|                                                                         Digital pins
|LED bar|                                                                                   Digital pins
|Groove LCD|                                                                                Digital pins
LCD                                                                                         Digital pins
========================================================================================    ============

.. |Buzzer| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-Buzzer" target="_blank">Buzzer</a>

.. |LED| raw:: html

    <a href="https://www.seeedstudio.com/grove-led-p-767.html?cPath=156_157" target="_blank">LED</a>
    
.. |7 segment display| raw:: html

    <a href="https://www.seeedstudio.com/Grove-0-54-Red-Dual-Alphanumeric-Display-p-4031.html?queryID=817e144e20d72ab54938d8288d8f4155&objectID=4031&indexName=bazaar_retailer_products" target="_blank">7 segment display</a>
    
.. |LED bar| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-LED_Bar" target="_blank">LED bar</a>
    
.. |Groove LCD| raw:: html

    <a href="https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight" target="_blank">Groove LCD</a>



********
Examples
********

1. |Drive LEDs|
2. |Control GPIOs|
3. |Write slow analog I/Os|
4. |Read slow analog I/Os|
5. Generator:

    #. |Generate periodic sine wave|
    #. |Generate periodic arbitrary signal|
    #. |Two synchronized generators|
    #. |Burst mode|

6. Oscilloscope:

    #. |Forced trigger|
    #. |Level trigger|
    #. |Two synchronized channels|
    #. |Synchronized with generator|

7. Demo applications using widgets:

    #. |Generator|
    #. |Oscilloscope|

8. Grove sensors

    #. |Temperature sensor example|
    #. |Home heating automation|
   
.. |Drive LEDs| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/led.ipynb" target="_blank">Drive LEDs</a>
    
.. |Control GPIOs| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/gpio.ipynb" target="_blank">Control GPIOs</a>

.. |Write slow analog I/Os| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/analog_output.ipynb" target="_blank">Write slow analog I/Os</a>

.. |Read slow analog I/Os| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/analog_input.ipynb" target="_blank">Read slow analog I/Os</a>

.. |Generate periodic sine wave| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/gen_sine_signal.ipynb" target="_blank">Generate periodic sine wave</a>

.. |Generate periodic arbitrary signal| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/gen_arbitrary_signal.ipynb" target="_blank">Generate periodic arbitrary signal</a>

.. |Two synchronized generators| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/gen_sync_two_channel.ipynb" target="_blank">Two synchronized generators</a>

.. |Burst mode| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/gen_bursts.ipynb" target="_blank">Burst mode</a>

.. |Forced trigger| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/osc_trigger_forced.ipynb" target="_blank">Forced trigger</a>

.. |Level trigger| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/osc_trigger_level.ipynb" target="_blank">Level trigger</a>
    
.. |Two synchronized channels| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/osc_sync_two_channel.ipynb" target="_blank">Two synchronized channels</a>

.. |Synchronized with generator| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/osc_sync_with_gen.ipynb" target="_blank">Synchronized with generator</a>

.. |Generator| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/generator_widget.ipynb" target="_blank">Generator</a>

.. |Oscilloscope| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/oscilloscope_widget.ipynb" target="_blank">Oscilloscope</a>

.. |Temperature sensor example| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/exam_temp.ipynb" target="_blank">Temperature sensor</a>

.. |Home heating automation| raw:: html

    <a href="https://github.com/RedPitaya/jupyter/blob/9f3cfd3e20c2b4ddae8bdc1762ed6154f917f3ff/examples/home_automation.ipynb" target="_blank">Home heating automation</a>

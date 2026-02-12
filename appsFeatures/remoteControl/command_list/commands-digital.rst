
.. _commands_digital:

==============
LEDs and GPIOs
==============

Functionality overview
------------------------

Digital I/O commands control Red Pitaya's LEDs and GPIO pins on the extension connector. These commands allow you to read digital inputs, 
set digital outputs, and control the onboard LEDs for status indication or custom applications.


Important notes
----------------

* SDRlab 122-16 and STEMlab 125-14 4-Input have 10-bit DIO registers instead of 8-bit.
* GPIO pins are 3.3V logic level - do not apply higher voltages.
* Remember to set pin direction (IN/OUT) before use.


Code examples
-----------------

Here are some examples of how to use the digital I/O commands on Red Pitaya:

* :ref:`Digital examples <examples_digital>`.


Parameters and command table
-----------------------------

**Parameter options:**

- ``<dir> = {OUT,IN}``
- ``<gpio> = {{DIO0_P...DIO7_P}, {DIO0_N...DIO7_N}}``
- ``<led> = {LED0...LED7}``
- ``<pin> = {gpio, led}``
- ``<state> = {0,1}``
- ``<reg_state> = {0b00000000}`` - One LED/DIO per bit.  *(10 bit DIO register on SDRlab and STEMlab 4-Input)*
- ``<reg_direction> = {0b00000000}`` - One DIO per bit.  *(10 bit DIO register on SDRlab and STEMlab 4-Input)*


**Available Jupyter and API macros:**

- States - ``RP_LOW, RP_HIGH``
- Directions - ``RP_IN, RP_OUT``
- LEDs - ``RP_LED0, RP_LED1, ..., RP_LED7``
- DIOx_P - ``RP_DIO0_P, RP_DIO1_P, ..., RP_DIO7_P`` *Goes up to 9 on SDRlab and STEMlab 4-Input*
- DIOx_N - ``RP_DIO0_N, RP_DIO1_N, ..., RP_DIO7_N`` *Goes up to 9 on SDRlab and STEMlab 4-Input*


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| SCPI                                  | API, Jupyter                                                                       | DESCRIPTION                                                                       |  ECOSYSTEM         |
+=======================================+====================================================================================+===================================================================================+====================+
| | ``DIG:RST``                         | | C++: ``rp_DpinReset()``                                                          | | Sets digital pins to default values. Pins DIO1_P - DIO7_P,                      | 1.04-18 and up     |
| | Examples:                           | |                                                                                  | | RP_DIO0_N - RP_DIO7_N are set all INPUT and to LOW. LEDs are set to LOW/OFF.    |                    |
| | ``DIG:RST``                         | | Python: ``rp_DpinReset()``                                                       | |                                                                                 |                    |
| |                                     | |                                                                                  | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN:DIR <dir>,<gpio>``        | | C++: ``rp_DpinSetDirection(rp_dpin_t pin, rp_pinDirection_t direction)``         | Set the direction of digital pins to output or input.                             | 1.04-18 and up     |
| | Examples:                           | |                                                                                  |                                                                                   |                    |
| | ``DIG:PIN:DIR OUT,DIO0_N``          | | Python: ``rp_DpinSetDirection(<pin>, <direction>)``                              |                                                                                   |                    |
| | ``DIG:PIN:DIR IN,DIO1_P``           | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN:DIR? <gpio>``             | | C++: ``rp_DpinGetDirection(rp_dpin_t pin, rp_pinDirection_t* direction)``        | Get digital input output pin direction.                                           | 1.04-18 and up     |
| | Examples:                           | |                                                                                  |                                                                                   |                    |
| | ``DIG:PIN:DIR? DIO0_N`` > ``OUT``   | | Python: ``rp_DpinGetDirection(<pin>)``                                           |                                                                                   |                    |
| | ``DIG:PIN:DIR? DIO1_P`` > ``IN``    | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN <pin>,<state>``           | | C++: ``rp_DpinSetState(rp_dpin_t pin, rp_pinState_t state)``                     | | Set the state of digital outputs to 1 (HIGH) or 0 (LOW).                        | 1.04-18 and up     |
| | Examples:                           | |                                                                                  | | Returns a 1 (HIGH) if the pin is floating.                                      |                    |
| | ``DIG:PIN DIO0_N,1``                | | Python: ``rp_DpinSetState(<pin>, <state>)``                                      | |                                                                                 |                    |
| | ``DIG:PIN LED2,1``                  | |                                                                                  | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | ``DIG:PIN? <pin>`` > ``<state>``    | | C++: ``rp_DpinGetState(rp_dpin_t pin, rp_pinState_t* state)``                    | Get state of digital inputs and outputs.                                          | 1.04-18 and up     |
| | Examples:                           | |                                                                                  |                                                                                   |                    |
| | ``DIG:PIN? DIO0_N``  > ``1``        | | Python: ``rp_DpinGetState(<pin>)``                                               |                                                                                   |                    |
| | ``DIG:PIN? LED2``  > ``0``          | |                                                                                  |                                                                                   |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C++: ``rp_LEDSetState(uint32_t reg_state)``                                      | | Set the state of the 8-bit LED register. Each bit corresponds to the state      | 1.04-18 and up     |
| |                                     | |                                                                                  | | of one LED.                                                                     |                    |
| |                                     | | Python: ``rp_LEDSetState(<reg_state>)``                                          | |                                                                                 |                    |
| |                                     | |                                                                                  | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C++: ``rp_LEDGetState(uint32_t *reg_state)``                                     | | Get the state of the 8-bit LED register. Each bit corresponds to the state      | 1.04-18 and up     |
| |                                     | |                                                                                  | | of one LED.                                                                     |                    |
| |                                     | | Python: ``rp_LEDGetState()``                                                     | |                                                                                 |                    |
| |                                     | |                                                                                  | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C++: ``rp_GPIOnSetDirection(uint32_t reg_direction)``                            | | Set the state of the DIO_N or DIO_P direction register. Each bit corresponds    | 1.04-18 and up     |
| |                                     | |      ``rp_GPIOnSetDirection(uint32_t reg_direction)``                            | | to the direction of one DIO_N or DIO_P pin.                                     |                    |
| |                                     | | Python: ``rp_GPIOnSetDirection(<reg_direction>)``                                | |                                                                                 |                    |
| |                                     | |         ``rp_GPIOpSetDirection(<reg_direction>)``                                | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C++: ``rp_GPIOnGetDirection(uint32_t *reg_direction)``                           | | Get the state of the DIO_N or DIO_P direction register. Each bit corresponds    | 1.04-18 and up     |
| |                                     | |      ``rp_GPIOpGetDirection(uint32_t *reg_direction)``                           | | to the direction of one DIO_N or DIO_P pin.                                     |                    |
| |                                     | | Python: ``rp_GPIOnGetDirection()``                                               | |                                                                                 |                    |
| |                                     | |         ``rp_GPIOpGetDirection()``                                               | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C++: ``rp_GPIOnSetState(uint32_t reg_state)``                                    | | Set the state of the DIO_N or DIO_P state register. Each bit corresponds        | 1.04-18 and up     |
| |                                     | |      ``rp_GPIOpSetState(uint32_t reg_state)``                                    | | to the state of one DIO_N or DIO_P pin.                                         |                    |
| |                                     | | Python: ``rp_GPIOnSetState(<reg_state>)``                                        | |                                                                                 |                    |
| |                                     | |         ``rp_GPIOpSetState(<reg_state>)``                                        | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+
| | -                                   | | C++: ``rp_GPIOnGetState(uint32_t *state)``                                       | | Get the state of the DIO_N or DIO_P state register. Each bit corresponds        | 1.04-18 and up     |
| |                                     | |      ``rp_GPIOpGetState(uint32_t *state)``                                       | | to the state of one DIO_N or DIO_P pin.                                         |                    |
| |                                     | | Python: ``rp_GPIOnGetState()``                                                   | |                                                                                 |                    |
| |                                     | |         ``rp_GPIOpGetState()``                                                   | |                                                                                 |                    |
+---------------------------------------+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+--------------------+

|

* :ref:`Back to top <commands_digital>`
* :ref:`Back to command list <command_list>`

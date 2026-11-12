
.. _commands_digital:

==============
LED 与 GPIO
==============

功能概述
------------------------

数字 I/O 命令控制扩展连接器上的 Red Pitaya LED 和 GPIO 引脚。这些命令可读取数字输入、设置数字输出，并控制板载 LED 以指示状态或用于自定义应用。


重要说明
----------------

* Zynq 7020 板卡使用 10 位宽 DIO 寄存器，而不是 8 位宽寄存器。
* GPIO 引脚为 3.3V 逻辑电平（TTL），不要施加更高电压。
* 使用前请记得设置引脚方向（IN/OUT）。


代码示例
-----------------

以下是如何在 Red Pitaya 上使用数字 I/O 命令的示例：

* :ref:`Digital examples <examples_digital>`.


参数与命令表
-----------------------------

**参数选项：**

- ``<dir> = {OUT,IN}``
- ``<gpio> = {{DIO0_P...DIO7_P}, {DIO0_N...DIO7_N}}``
- ``<led> = {LED0...LED7}``
- ``<pin> = {gpio, led}``
- ``<state> = {0,1}``
- ``<reg_state> = {0b00000000}`` - One LED/DIO per bit.  *(10 bit DIO register on Zynq 7020 boards)*
- ``<reg_direction> = {0b00000000}`` - One DIO per bit.  *(10 bit DIO register on Zynq 7020 boards)*


**可用的 Jupyter 和 API 宏：**

- States - ``RP_LOW, RP_HIGH``
- Directions - ``RP_IN, RP_OUT``
- LEDs - ``RP_LED0, RP_LED1, ..., RP_LED7``
- DIOx_P - ``RP_DIO0_P, RP_DIO1_P, ..., RP_DIO7_P`` *Zynq 7020 板卡上可扩展至 9*
- DIOx_N - ``RP_DIO0_N, RP_DIO1_N, ..., RP_DIO7_N`` *Zynq 7020 板卡上可扩展至 9*


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 39 84 83 20
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 说明
      - ECOSYSTEM
    * - ``DIG:RST`` |br| Examples: |br| ``DIG:RST``
      - C++: ``rp_DpinReset()`` |br| Python: ``rp_DpinReset()``
      - 将数字引脚设置为默认值。DIO1_P - DIO7_P、 |br| RP_DIO0_N - RP_DIO7_N 全部设置为 INPUT 和 LOW。LED 设置为 LOW/OFF。
      - 1.04-18 and up
    * - ``DIG:PIN:DIR <dir>,<gpio>`` |br| Examples: |br| ``DIG:PIN:DIR OUT,DIO0_N`` |br| ``DIG:PIN:DIR IN,DIO1_P``
      - C++: ``rp_DpinSetDirection(rp_dpin_t pin, rp_pinDirection_t direction)`` |br| Python: ``rp_DpinSetDirection(<pin>, <direction>)``
      - 将数字引脚方向设置为输出或输入。
      - 1.04-18 and up
    * - ``DIG:PIN:DIR? <gpio>`` |br| Examples: |br| ``DIG:PIN:DIR? DIO0_N`` > ``OUT`` |br| ``DIG:PIN:DIR? DIO1_P`` > ``IN``
      - C++: ``rp_DpinGetDirection(rp_dpin_t pin, rp_pinDirection_t* direction)`` |br| Python: ``rp_DpinGetDirection(<pin>)``
      - 获取数字输入输出引脚方向。
      - 1.04-18 and up
    * - ``DIG:PIN <pin>,<state>`` |br| Examples: |br| ``DIG:PIN DIO0_N,1`` |br| ``DIG:PIN LED2,1``
      - C++: ``rp_DpinSetState(rp_dpin_t pin, rp_pinState_t state)`` |br| Python: ``rp_DpinSetState(<pin>, <state>)``
      - 将数字输出状态设置为 1（HIGH）或 0（LOW）。 |br| 如果引脚悬空，则返回 1（HIGH）。
      - 1.04-18 and up
    * - ``DIG:PIN? <pin>`` > ``<state>`` |br| Examples: |br| ``DIG:PIN? DIO0_N``  > ``1`` |br| ``DIG:PIN? LED2``  > ``0``
      - C++: ``rp_DpinGetState(rp_dpin_t pin, rp_pinState_t* state)`` |br| Python: ``rp_DpinGetState(<pin>)``
      - 获取数字输入和输出的状态。
      - 1.04-18 and up
    * - -
      - C++: ``rp_LEDSetState(uint32_t reg_state)`` |br| Python: ``rp_LEDSetState(<reg_state>)``
      - 设置 8 位 LED 寄存器的状态。每个位对应一个 LED 的状态。
      - 1.04-18 and up
    * - -
      - C++: ``rp_LEDGetState(uint32_t *reg_state)`` |br| Python: ``rp_LEDGetState()``
      - 获取 8 位 LED 寄存器的状态。每个位对应一个 LED 的状态。
      - 1.04-18 and up
    * - -
      - C++: ``rp_GPIOnSetDirection(uint32_t reg_direction)`` |br| ``rp_GPIOnSetDirection(uint32_t reg_direction)`` |br| Python: ``rp_GPIOnSetDirection(<reg_direction>)`` |br| ``rp_GPIOpSetDirection(<reg_direction>)``
      - 设置 DIO_N 或 DIO_P 方向寄存器的状态。每个位对应一个 DIO_N 或 DIO_P 引脚的方向。
      - 1.04-18 and up
    * - -
      - C++: ``rp_GPIOnGetDirection(uint32_t *reg_direction)`` |br| ``rp_GPIOpGetDirection(uint32_t *reg_direction)`` |br| Python: ``rp_GPIOnGetDirection()`` |br| ``rp_GPIOpGetDirection()``
      - 获取 DIO_N 或 DIO_P 方向寄存器的状态。每个位对应一个 DIO_N 或 DIO_P 引脚的方向。
      - 1.04-18 and up
    * - -
      - C++: ``rp_GPIOnSetState(uint32_t reg_state)`` |br| ``rp_GPIOpSetState(uint32_t reg_state)`` |br| Python: ``rp_GPIOnSetState(<reg_state>)`` |br| ``rp_GPIOpSetState(<reg_state>)``
      - 设置 DIO_N 或 DIO_P 状态寄存器的状态。每个位对应一个 DIO_N 或 DIO_P 引脚的状态。
      - 1.04-18 and up
    * - -
      - C++: ``rp_GPIOnGetState(uint32_t *state)`` |br| ``rp_GPIOpGetState(uint32_t *state)`` |br| Python: ``rp_GPIOnGetState()`` |br| ``rp_GPIOpGetState()``
      - 获取 DIO_N 或 DIO_P 状态寄存器的状态。每个位对应一个 DIO_N 或 DIO_P 引脚的状态。
      - 1.04-18 and up

|

* :ref:`Back to top <commands_digital>`
* :ref:`Back to command list <command_list>`

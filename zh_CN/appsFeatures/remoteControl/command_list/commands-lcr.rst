
.. _commands_lcr:

========
LCR mode
========

功能概览
------------------------

LCR 模式命令允许将 Red Pitaya 用作 LCR 表进行阻抗测量。这些命令支持测量电感（L）、 
电容（C）和电阻（R），支持串联和并联配置，并可选配外部 LCR 扩展模块。


重要说明
----------------

* 为获得准确测量结果，需要使用合适的信号幅度和频率。
* 外接 LCR 扩展模块可改善测量范围和精度。
* Shunt resistor selection affects measurement sensitivity.


代码示例
-----------------

[待添加 - LCR 测量专用示例]

|

参数与命令表
-----------------------------

**参数选项：**

- ``<enable> = {OFF, ON}``  默认值： ``ON``
- ``<mode> = {SERIES, PARALLEL}``  默认值： ``SERIES``
- ``<ext_mode> = {LCR_EXT, CUSTOM}``  默认值： ``LCR_EXT``
- ``<ext_module_shunt> = {S10, S100, S1k, S10k, S100k, S1M}``  默认值： ``S10``
- ``<frequency> = {0 ... 62.5e6}``（单位：Hertz）。默认值： ``1000``
- ``<amplitude> = {-1 ... 1}``（单位：Volts）。默认值： ``0.5``
- ``<offset> = {-1 ... 1}``（单位：Volts）。默认值： ``0``
- ``<shunt> = {1 ... 100000000}``（单位：Hertz）。默认值： ``100``
- ``<json>`` JSON 格式的测量结果

**可用的 Jupyter 和 API 宏：**

- *(未来 OS 版本)*


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 43 66 85 20
    :header-rows: 1

    * - SCPI
      - API、Jupyter
      - 描述
      - 适用版本
    * - ``LCR:START`` |br| 示例： |br| ``LCR:START``
      - C++: ``lcrApp_LcrRun()`` |br| Python:
      - 启动 LCR 处理线程并将设置重置为默认值。 |br| 启动线程后需要设置发生器。
      - 2.05-37 and up
    * - ``LCR:START:GEN`` |br| 示例： |br| ``LCR:START:GEN``
      - C++: ``lcrApp_LcrReset()`` |br| Python:
      - 使用指定设置启动 OUT1 上的发生器。
      - 2.05-37 and up
    * - ``LCR:STOP`` |br| 示例： |br| ``LCR:STOP``
      - C++: ``lcrApp_LcrStop()`` |br| Python:
      - 停止 LCR 线程。
      - 2.05-37 and up
    * - ``LCR:RESET`` |br| 示例： |br| ``LCR:RESET``
      - C++: ``lcrApp_LcrReset()`` |br| Python:
      - 重置 LCR API 中的默认设置。
      - 2.05-37 and up
    * - ``LCR:MEASURE?`` > ``<json>`` |br| 示例： |br| ``LCR:MEASURE?`` > ``{...}``
      - C++: ``lcrApp_LcrCopyParams(lcr_main_data_t *data)`` |br| Python:
      - 返回最近处理数据的计算结果（JSON 格式）。
      - 2.05-37 and up
    * - ``LCR:FREQ <frequency>`` |br| 示例： |br| ``LCR:FREQ 1000``
      - C++: ``lcrApp_LcrSetFrequency(float frequency)`` |br| Python:
      - 设置发生器频率。 |br| 要应用所有设置，必须调用启动发生器的命令。
      - 2.05-37 and up
    * - ``LCR:FREQ?`` > ``<frequency>`` |br| 示例： |br| ``LCR:FREQ?`` > ``1000``
      - C++: ``lcrApp_LcrGetFrequency(float *frequency)`` |br| Python:
      - 返回发生器当前频率设置。
      - 2.05-37 and up
    * - ``LCR:VOLT <amplitude>`` |br| 示例： |br| ``LCR:VOLT 1000``
      - C++: ``lcrApp_LcrSetAmplitude(float volt)`` |br| Python:
      - 设置发生器幅度。 默认值为 0.5V。 |br| 可设置最高 1V 的值。  但需要注意，使用 LCR 时 |br| 跳线应处于 Hi-Z 位置。 |br| 因此，幅度大于 0.5 的值对于大多数测量都 |br| 不正确。
      - 2.05-37 and up
    * - ``LCR:VOLT?`` > ``<amplitude>`` |br| 示例： |br| ``LCR:VOLT?`` > ``1000``
      - C++: ``lcrApp_LcrGetAmplitude(float *volt)`` |br| Python:
      - 返回当前幅度设置。
      - 2.05-37 and up
    * - ``LCR:VOLT:OFFS <offset>`` |br| 示例： |br| ``LCR:VOLT:OFFS 0``
      - C++: ``lcrApp_LcrSetOffset(float offset)`` |br| Python:
      - 设置发生器信号偏移。
      - 2.05-37 and up
    * - ``LCR:VOLT:OFFS?`` > ``<offset>`` |br| 示例： |br| ``LCR:VOLT:OFFS?`` > ``0``
      - C++: ``lcrApp_LcrGetOffset(float *offset)`` |br| Python:
      - 返回发生器信号偏移。
      - 2.05-37 and up
    * - ``LCR:SHUNT <ext_module_shunt>`` |br| 示例： |br| ``LCR:SHUNT S10``
      - C++: ``lcrApp_LcrSetShunt(lcr_shunt_t shunt)`` |br| Python:
      - 设置 LCR 扩展板上的分流电阻。
      - 2.05-37 and up
    * - ``LCR:SHUNT?`` > ``<ext_module_shunt>`` |br| 示例： |br| ``LCR:SHUNT?`` > ``S10``
      - C++: ``lcrApp_LcrGetShunt(lcr_shunt_t *shunt)`` |br| Python:
      - 返回当前分流值，包括 AUTO 分流模式。
      - 2.05-37 and up
    * - ``LCR:SHUNT:CUSTOM <shunt>`` |br| 示例： |br| ``LCR:SHUNT:CUSTOM 10``
      - C++: ``lcrApp_LcrSetCustomShunt(int shunt)`` |br| Python:
      - 未使用扩展板时设置分流值。
      - 2.05-37 and up
    * - ``LCR:SHUNT:CUSTOM?`` > ``<shunt>`` |br| 示例： |br| ``LCR:SHUNT:CUSTOM?`` > ``10``
      - C++: ``lcrApp_LcrGetCustomShunt(int *shunt)`` |br| Python:
      - 未使用扩展板时设置分流值。
      - 2.05-37 and up
    * - ``LCR:SHUNT:MODE <ext_mode>`` |br| 示例： |br| ``LCR:SHUNT:MODE LCR_EXT``
      - C++: ``lcrApp_LcrSetShuntMode(lcr_shunt_mode_t shunt_mode)`` |br| Python:
      - 设置使用模式：使用或不使用扩展板。 |br| 必须在启动 LCR 前设置。
      - 2.05-37 and up
    * - ``LCR:SHUNT:MODE?`` > ``<ext_mode>`` |br| 示例： |br| ``LCR:SHUNT:MODE?`` > ``LCR_EXT``
      - C++: ``lcrApp_LcrGetShuntMode(lcr_shunt_mode_t *shunt_mode)`` |br| Python:
      - 返回当前分流操作模式。
      - 2.05-37 and up
    * - ``LCR:SHUNT:AUTO <enable>`` |br| 示例： |br| ``LCR:SHUNT:AUTO OFF``
      - C++: ``lcrApp_LcrSetShuntIsAuto(bool isShuntAuto)`` |br| Python:
      - 启用或禁用扩展板的自动分流选择模式。
      - 2.05-37 and up
    * - ``LCR:CIRCUIT <mode>`` |br| 示例： |br| ``LCR:CIRCUIT SERIES``
      - C++: ``lcrApp_LcrSetMeasSeries(bool series)`` |br| Python:
      - 将测量模式设置为串联或并联。影响参数：L、C、R。
      - 2.05-37 and up
    * - ``LCR:CIRCUIT?`` > ``<mode>`` |br| 示例： |br| ``LCR:CIRCUIT?`` > ``SERIES``
      - C++: ``lcrApp_LcrGetMeasSeries(bool *series)`` |br| Python:
      - 返回测量模式。
      - 2.05-37 and up
    * - ``LCR:EXT:MODULE?`` > ``<enable>`` |br| 示例： |br| ``LCR:EXT:MODULE?`` > ``ON``
      - C++: ``lcrApp_LcrIsModuleConnected(bool *state)`` |br| Python:
      - 返回扩展板状态。 |br| 如果值为 ON，则表示板卡已连接。
      - 2.05-37 and up

|

* :ref:`Back to top <commands_lcr>`
* :ref:`Back to command list <command_list>`

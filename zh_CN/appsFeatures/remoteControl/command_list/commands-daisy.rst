
.. _commands_daisy:

===============================
菊链时钟与触发器
===============================

功能概述
------------------------

菊链命令用于配置通过扩展连接器连接的多个 Red Pitaya 板卡之间的时钟和触发共享。这样可以实现多板同步采集与信号生成，从而扩展通道数量，并在多个单元之间进行同步测量。


重要说明
----------------

* 需要在板卡之间建立硬件菊链连接。
* 合适的线缆长度和阻抗匹配对信号完整性至关重要。
* 时钟分配会影响可达到的最大同步精度。


代码示例
-----------------

以下是使用菊链同步的一些示例：

* :ref:`多板同步示例 <examples_multiboard_sync>`。


参数与命令表
-----------------------------

**参数选项：**

- ``<state> = {OFF, ON}``
- ``<mode> = {ADC, DAC}``
- ``<enable> = {true, false}``

**可用的 Jupyter 和 API 宏：**

- 共享触发源 - ``OUT_TR_ADC, OUT_TR_DAC``


.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 43 84 108 31
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - 描述
      - 适用版本
    * - ``DAISY:ENable <state>`` |br| 示例：|br| ``DAISY:ENable ON``
      - C++: ``rp_SetEnableDaisyChainSync`` |br| Python: ~
      - 启用通过 SATA 菊链连接器进行的时钟和触发同步。 |br| 主板触发后，触发信号将通过 SATA 连接器转发到从板， |br| 从板可使用带有 EXT_NE 选择器的 rp_GenTriggerSource 检测该触发信号。 |br| 请注意，通过 SATA 接收的触发信号会与来自 GPIO 的外部触发信号执行 OR 运算。
      - 仅适用于 2.00-15
    * - ``DAISY:ENable?`` > ``<state>`` |br| 示例：|br| ``DAISY:ENable?`` > ``ON``
      - C++: ``rp_GetEnableDaisyChainSync`` |br| Python: ~
      - 返回当前 SATA 菊链模式的状态。
      - 仅适用于 2.00-15
    * - ``DAISY:SYNC:TRIG <state>`` |br| 示例：|br| ``DAISY:SYNC:TRIG ON``
      - C++: ``rp_SetEnableDaisyChainTrigSync(bool enable)`` |br| Python:  ``rp_SetEnableDaisyChainTrigSync(<enable>)``
      - 启用通过 SATA 菊链连接器进行的触发同步。主板触发后， |br| 触发信号将通过 SATA 连接器转发到从板， |br| 从板可使用 EXT_NE 选择器检测该触发信号。
      - 2.00-18 及更高版本
    * - ``DAISY:SYNC:TRIG?`` > ``<state>`` |br| 示例：|br| ``DAISY:SYNC:TRIG?`` > ``ON``
      - C++: ``rp_GetEnableDaisyChainTrigSync(bool *status)`` |br| Python: ``rp_GetEnableDaisyChainTrigSync()``
      - 返回当前使用菊链的触发同步状态。
      - 2.00-18 及更高版本
    * - ``DAISY:SYNC:CLK <state>`` |br| 示例：|br| ``DAISY:SYNC:CLK ON``
      - C++: ``rp_SetEnableDiasyChainClockSync(bool enable)`` |br| Python: ``rp_SetEnableDiasyChainClockSync(<enable>)``
      - 启用通过 SATA 菊链连接器进行的时钟同步。 |br| 主板将开始为从单元生成时钟，并依次传递下去。
      - 2.00-18 及更高版本
    * - ``DAISY:SYNC:CLK?`` > ``<state>`` |br| 示例：|br| ``DAISY:SYNC:CLK?`` > ``ON``
      - C++: ``rp_GetEnableDiasyChainClockSync(bool *state)`` |br| Python: ``rp_GetEnableDiasyChainClockSync()``
      - 返回当前 SATA 菊链模式的状态。
      - 2.00-18 及更高版本
    * - ``DAISY:TRIG_O:ENable <state>`` |br| 示例：|br| ``DAISY:TRIG_O:ENable ON``
      - C++: ``rp_SetDpinEnableTrigOutput(bool enable)`` |br| Python: ``rp_SetDpinEnableTrigOutput(<enable>)``
      - 将 DIO0_N 设为所选源（采集或生成）的触发输出。
      - 2.00-15 - 2.00-30
    * - ``DAISY:TRig:Out:ENable <state>`` |br| 示例：|br| ``DAISY:TRig:Out:ENable ON``
      - C++: ``rp_SetDpinEnableTrigOutput(bool enable)`` |br| Python: ``rp_SetDpinEnableTrigOutput(<enable>)``
      - 将 DIO0_N 设为所选源（采集或生成）的触发输出。
      - 2.04-35 及更高版本
    * - ``DAISY:TRIG_O:ENable?`` > ``<state>`` |br| 示例：|br| ``DAISY:TRIG_O:ENable?`` > ``ON``
      - C++: ``rp_GetDpinEnableTrigOutput(bool *state)`` |br| Python: ``rp_GetDpinEnableTrigOutput()``
      - 返回 DIO0_N 的当前模式状态。如果为 true，则该引脚模式作为源工作。
      - 2.00-15 - 2.00-30
    * - ``DAISY:TRig:Out:ENable?`` > ``<state>`` |br| 示例：|br| ``DAISY:TRig:Out:ENable?`` > ``ON``
      - C++: ``rp_GetDpinEnableTrigOutput(bool *state)`` |br| Python: ``rp_GetDpinEnableTrigOutput()``
      - 返回 DIO0_N 的当前模式状态。如果为 true，则该引脚模式作为源工作。
      - 2.04-35 及更高版本
    * - ``DAISY:TRIG_O:SOUR <mode>`` |br| 示例：|br| ``DAISY:TRIG_O:SOUR DAC``
      - C++: ``rp_SetSourceTrigOutput(rp_outTiggerMode_t mode)`` |br| Python: ``rp_SetSourceTrigOutput(<mode>)``
      - 设置触发源模式 ADC/DAC。
      - 2.00-15 - 2.00-30
    * - ``DAISY:TRig:Out:SOUR <mode>`` |br| 示例：|br| ``DAISY:TRig:Out:SOUR DAC``
      - C++: ``rp_SetSourceTrigOutput(rp_outTiggerMode_t mode)`` |br| Python: ``rp_SetSourceTrigOutput(<mode>)``
      - 设置触发源模式 ADC/DAC。
      - 2.04-35 及更高版本
    * - ``DAISY:TRIG_O:SOUR?`` > ``<mode>`` |br| 示例：|br| ``DAISY:TRIG_O:SOUR?`` > ``DAC``
      - C++: ``rp_GetSourceTrigOutput(rp_outTiggerMode_t *mode)`` |br| Python: ``rp_GetSourceTrigOutput()``
      - 返回触发源模式。
      - 2.00-15 - 2.00-30
    * - ``DAISY:TRig:Out:SOUR?`` > ``<mode>`` |br| 示例：|br| ``DAISY:TRig:Out:SOUR?`` > ``DAC``
      - C++: ``rp_GetSourceTrigOutput(rp_outTiggerMode_t *mode)`` |br| Python: ``rp_GetSourceTrigOutput()``
      - 返回触发源模式。
      - 2.04-35 及更高版本


.. note::

   菊链命令用于配合 :ref:`X 通道系统 <x-ch_streaming>` 和 :ref:`Red Pitaya Click Shield 扩展板 <click_shield>` 工作。

.. note::

   SATA 连接器和 DIO0_P（外部触发引脚）的触发信号会在软件中执行 OR 运算。
   生成和采集触发沿会在信号合并后生效，并根据 ``DAISY:TRig:Out:SOUR <mode>`` 命令触发 DAC 或 ADC。

|

* :ref:`返回顶部 <commands_daisy>`
* :ref:`返回命令列表 <command_list>`

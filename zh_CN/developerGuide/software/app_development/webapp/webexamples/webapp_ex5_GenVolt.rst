.. _webApp_example_genVolt:

###################
生成电压
###################

本示例演示如何使用 Red Pitaya 的快速模拟输出生成模拟电压信号。
你将学习如何通过 Web 界面控制信号频率、幅度和波形，并将生成的信号施加到慢速模拟输入，以验证测量结果。

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

概述
=========

此应用在 Red Pitaya 输出通道上生成可配置的电压信号，并允许你通过 Web 界面实时调整其特性。

**关键概念：**

* 使用 Red Pitaya API 生成模拟信号
* 控制信号参数（频率、幅度、波形）
* 使用信号发生器 API
* 设置直流偏置以调节信号

**硬件：**

* 输出通道 1（OUT1）生成信号
* 可连接到慢速模拟输入（AI0-AI3）进行验证

|

准备工作
==============

基础示例
-------------------

本示例基于 :ref:`从慢速输入读取模拟电压 <webApp_example_ReadSlowAnalogVoltage>`。
请将该示例作为基础应用，因为它提供了使用单台设备验证生成电压的最简单方法。

|

信号范围注意事项
----------------------------

**发生器规格：**

* Red Pitaya 发生器范围：-1 V 至 +1 V
* 慢速模拟输入范围：0 V 至 3.3 V

**使信号兼容：**

* 将直流偏置设置为 +0.5 V
* 将最大幅度限制为 0.5 V
* 结果信号范围：0 V 至 1 V（与慢速模拟输入兼容）

**范围计算：**

幅度为 0.5 V 时：(-0.5 V 至 +0.5 V) + 0.5 V 偏置 = 0 V 至 1 V 输出

|

实现前端
===========================

HTML 结构
---------------

在 ``index.html`` 中添加三个控制块，分别用于频率、幅度和波形：

**频率控制：**

.. code-block:: html

    <div id='frequency_setup'>
        <div>Frequency: Hz</div>
        <input id='frequency_set' type="range" size="2" value="1" min="1" max="20">
    </div>

* 范围：1 Hz 至 20 Hz
* 默认值：1 Hz

**幅度控制：**

.. code-block:: html

    <div id='amplitude_setup'>
        <div>Amplitude: V</div>
        <input id='amplitude_set' type="range" step="0.01" size="2" value="0.5" min="0" max="0.5">
    </div>

* 范围：0 V 至 0.5 V
* 默认值：0.5 V
* 步进：0.01 V（10 mV 精度）

**波形选择：**

.. code-block:: html

    <div id='waveform_setup'>
        <div>Waveform</div>
        <select size="1" id="waveform_set">
            <option selected value="0">Sine</option>
            <option value="1">Sawtooth</option>
            <option value="2">Square</option>
        </select>
    </div>

|

JavaScript 实现
--------------------------

在 ``app.js`` 中添加三个新函数来处理参数变化：

设置频率
^^^^^^^^^^^^^^^^^^

.. code-block:: javascript

    APP.setFrequency = function() {
        APP.frequency = $('#frequency_set').val();
        var local = {};
        local['FREQUENCY'] = { value: APP.frequency };
        APP.ws.send(JSON.stringify({ parameters: local }));
        $('#frequency_value').text(APP.frequency);
    };

此函数将：

1. 从滑块读取频率值
2. 创建包含新频率的参数对象
3. 通过 WebSocket 将其发送到后端
4. 更新显示以显示当前频率

设置幅度
^^^^^^^^^^^^^^^^^^

.. code-block:: javascript

    APP.setAmplitude = function() {
        APP.amplitude = $('#amplitude_set').val();
        var local = {};
        local['AMPLITUDE'] = { value: APP.amplitude };
        APP.ws.send(JSON.stringify({ parameters: local }));
        $('#amplitude_value').text(APP.amplitude);
    };

设置波形
^^^^^^^^^^^^^^^^^

.. code-block:: javascript

    APP.setWaveform = function() {
        APP.waveform = $('#waveform_set').val();
        console.log('Set to ' + APP.waveform);
        var local = {};
        local['WAVEFORM'] = { value: APP.waveform };
        APP.ws.send(JSON.stringify({ parameters: local }));
    };

|

实现后端
==========================

参数声明
-----------------------

在 ``main.cpp`` 中声明三个参数以控制发生器：

**频率参数：**

.. code-block:: c

    CIntParameter FREQUENCY("FREQUENCY", CBaseParameter::RW, 1, 0, 1, 20);

* 参数名称："FREQUENCY"
* 访问权限：读/写
* 默认值：1 Hz
* 最小值：1 Hz
* 最大值：20 Hz

**幅度参数：**

.. code-block:: c

    CFloatParameter AMPLITUDE("AMPLITUDE", CBaseParameter::RW, 0.5, 0, 0, 0.5);

* 参数名称："AMPLITUDE"
* 访问权限：读/写
* 默认值：0.5 V
* 最小值：0 V
* 最大值：0.5 V（受限以确保加偏置后输出为 0-1V）

**波形参数：**

.. code-block:: c

    CIntParameter WAVEFORM("WAVEFORM", CBaseParameter::RW, 0, 0, 0, 2);

* 参数名称："WAVEFORM"
* 访问权限：读/写
* 默认值：0（正弦波）
* 最小值：0
* 最大值：2

**波形值：**

.. list-table::
    :header-rows: 1

    * - 值
      - 描述
    * - 0
      - 正弦波
    * - 1
      - 锯齿波
    * - 2
      - 方波

|

发生器配置函数
---------------------------------

创建 **set_generator_config()** 函数以配置输出信号。

设置频率
^^^^^^^^^^^^^^^^^^

.. code-block:: c

    rp_GenFreq(RP_CH_1, FREQUENCY.Value());

设置输出通道 1（RP_CH_1）上的信号频率。

设置直流偏置
^^^^^^^^^^^^^^^^^^

.. code-block:: c

    rp_GenOffset(RP_CH_1, 0.5);

将信号平移到正电压范围（0 V 至 1 V）需要设置 +0.5 V 偏置，这使其能够兼容无法读取负电压的模拟输入。

设置幅度
^^^^^^^^^^^^^^^^^^

.. code-block:: c

    rp_GenAmp(RP_CH_1, AMPLITUDE.Value());

设置信号的峰峰值幅度。

设置波形
^^^^^^^^^^^^^^^^^

.. code-block:: c

    if (WAVEFORM.Value() == 0)
    {
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
    }
    else if (WAVEFORM.Value() == 1)
    {
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_RAMP_UP);
    }
    else if (WAVEFORM.Value() == 2)
    {
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SQUARE);
    }

**可用波形类型：**

* **RP_WAVEFORM_SINE** - 正弦波
* **RP_WAVEFORM_SQUARE** - 方波
* **RP_WAVEFORM_TRIANGLE** - 三角波
* **RP_WAVEFORM_RAMP_UP** - 锯齿波（上升斜坡）
* **RP_WAVEFORM_RAMP_DOWN** - 反向锯齿波（下降斜坡）
* **RP_WAVEFORM_DC** - 直流信号
* **RP_WAVEFORM_PWM** - PWM 信号
* **RP_WAVEFORM_ARBITRARY** - 用户定义波形

|

应用生命周期
----------------------

在 **rp_app_init()** 中初始化发生器
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c

    set_generator_config();
    rp_GenOutEnable(RP_CH_1);
    rp_GenResetTrigger(RP_CH_1);

**步骤：**

1. 使用默认设置配置发生器
2. 启用输出通道
3. 重置触发器以开始生成

在 **rp_app_exit()** 中禁用发生器
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c

    rp_GenOutDisable(RP_CH_1);

应用退出时始终禁用发生器，以防止持续生成信号。

在 **OnNewParams()** 中更新参数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c

    FREQUENCY.Update();
    AMPLITUDE.Update();
    WAVEFORM.Update();

当前端的任意参数发生变化时，在后端更新该参数，并调用 **set_generator_config()** 重新配置发生器。

|

Red Pitaya 发生器 API
==========================

关键 API 函数
------------------

**rp_GenFreq()**

设置信号频率。

**语法：**

.. code-block:: c

    int rp_GenFreq(rp_channel_t channel, float frequency);

**参数：**

* **channel** - 输出通道（RP_CH_1 或 RP_CH_2）
* **frequency** - 频率，单位为 Hz

**rp_GenAmp()**

设置信号幅度（峰峰值）。

**语法：**

.. code-block:: c

    int rp_GenAmp(rp_channel_t channel, float amplitude);

**参数：**

* **channel** - 输出通道
* **amplitude** - 幅度，单位为伏特

**rp_GenOffset()**

设置直流偏置电压。

**语法：**

.. code-block:: c

    int rp_GenOffset(rp_channel_t channel, float offset);

**参数：**

* **channel** - 输出通道
* **offset** - 偏置，单位为伏特

**rp_GenWaveform()**

设置波形类型。

**语法：**

.. code-block:: c

    int rp_GenWaveform(rp_channel_t channel, rp_waveform_t waveform);

**参数：**

* **channel** - 输出通道
* **waveform** - 波形类型常量

**rp_GenOutEnable() / rp_GenOutDisable()**

启用或禁用信号输出。

**语法：**

.. code-block:: c

    int rp_GenOutEnable(rp_channel_t channel);
    int rp_GenOutDisable(rp_channel_t channel);

**参数：**

* **channel** - 输出通道

**rp_GenResetTrigger()**

重置触发器并开始生成信号。

**语法：**

.. code-block:: c

    int rp_GenResetTrigger(rp_channel_t channel);

**参数：**

* **channel** - 输出通道

|

测试应用
========================

硬件设置
---------------

**选项 1：回环验证（本示例推荐）**

1. 使用跳线将 OUT1 连接到 AI0
2. 这样即可通过基础示例的模拟输入读取信号，验证生成的信号
3. 更改发生器参数时，电压读数会随之更新

**选项 2：示波器验证**

1. 将 OUT1 连接到示波器探头
2. 直接观察信号特性
3. 通过目测验证频率、幅度和波形

|

应用测试
--------------------

1. 编译并启动应用
2. **测试频率：**
   
   * 将频率滑块从 1 Hz 移动到 20 Hz
   * 观察电压读数以不同速率变化（使用回环时）
   * 在示波器上验证频率

3. **测试幅度：**
   
   * 将幅度滑块从 0 V 移动到 0.5 V
   * 观察电压读数范围变化（使用回环时）
   * 在示波器上验证幅度

4. **测试波形：**
   
   * 选择不同波形（正弦波、锯齿波、方波）
   * 观察不同的电压模式（使用回环且刷新足够快时）
   * 在示波器上验证波形形状

|

理解信号兼容性
===================================

为什么将幅度限制为 0.5V？
------------------------------

发生器可以生成 -1 V 至 +1 V 的信号，但模拟输入只能读取 0 V 至 3.3 V。

**不加偏置：**

* 0.5 V 幅度生成：-0.5 V 至 +0.5 V
* 问题：模拟输入无法读取负电压
* 结果：信号在 0 V 处被削波

**加 +0.5 V 偏置：**

* 相同的 0.5 V 幅度变为：0 V 至 +1 V
* 解决方案：整个信号现在都处于可读取范围内
* 结果：获得无削波的纯净信号

**计算示例：**

.. code-block:: none

    Generator output = (Amplitude × sin(ωt)) + Offset

    With Amplitude = 0.5 V, Offset = 0.5 V:

    Minimum: (0.5 V × -1) + 0.5 V = 0 V
    Maximum: (0.5 V × +1) + 0.5 V = 1 V

    Range: 0 V to 1 V ✓ (within AI readable range)

|

扩展此示例
=======================

可能的增强功能
----------------------

* **双通道生成** - 使用不同信号独立控制 OUT1 和 OUT2
* **相位控制** - 在通道之间添加相位偏置以实现高级信号生成
* **任意波形** - 使用数组定义自定义波形形状
* **频率扫描** - 自动扫描一定范围的频率
* **突发模式** - 生成具有指定次数和周期的信号突发
* **更高频率范围** - 将频率范围扩展到 kHz 或 MHz
* **调制** - 实现 AM 或 FM 调制
* **同步** - 将信号生成与采集同步

|

后续步骤
===========

可以通过以下教程在此示例基础上继续学习：

* :ref:`使用图形读取电压 <webApp_example_SlowVoltage_Graph>` - 实时可视化生成的信号
* :ref:`带增益和偏置的电压 <webApp_example_SlowVoltage_Graph_Offset>` - 对测量应用信号调节
* 信号采集示例 - 使用示波器捕获并分析生成的信号

|

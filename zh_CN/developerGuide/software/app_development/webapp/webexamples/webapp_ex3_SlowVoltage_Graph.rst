.. _webApp_example_SlowVoltage_Graph:

###################################################
读取慢速输入的模拟电压并绘图
###################################################

本示例在基础电压读取示例上增加实时绘图功能。您将学习如何连续采样模拟输入、高效缓冲数据，并随时间可视化电压测量值。

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

概述
=========

本应用连续读取 Red Pitaya 某个慢速模拟输入引脚的电压，并在实时图形上绘制测量值。

**核心概念：**

* 按设定间隔连续采集信号
* 数据缓冲与管理
* 使用 jquery.flot.js 实时可视化图形
* 堆叠信号以高效处理数据

**硬件：**

 :ref:`E2 扩展连接器 <E2_orig_gen>` 上的四个慢速模拟输入引脚（AI0-AI3）均可用于电压测量。

|

前置条件
==============

基础示例
-------------------

本示例建立在 :ref:`从慢速输入读取模拟电压 <webApp_example_ReadSlowAnalogVoltage>` 的基础上。
继续前请确保理解该示例。

所需库
-------------------

* **jquery.flot.js** - 用于绘制图形
* **pako.js** - 用于解压数据
* **jquery** - 用于 DOM 操作

|

实现前端
===========================

包含所需库
---------------------------

将以下脚本添加到 ``index.html``：

.. code-block:: html

    <script src="js/jquery-2.1.3.min.js"></script>
    <script src="js/jquery.flot.js"></script>
    <script src="js/pako.js"></script>
    <script src="js/app.js"></script>

|

HTML 结构
---------------

添加图形占位符以显示电压曲线：

.. code-block:: html

    <div id='placeholder'></div>

也可以保留基础示例中的数值显示：

.. code-block:: html

    <div id='value'></div>

|

JavaScript 实现
--------------------------

使用信号堆栈缓冲数据
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

修改 **APP.ws.onmessage()** 回调以缓冲传入数据。数据到达速度快于处理速度，因此需要先堆叠数据，再定期处理。

.. code-block:: javascript

    APP.ws.onmessage = function(ev) {
        // Decompress incoming data
        var data = new Uint8Array(ev.data);
        var inflate = pako.inflate(data);
        var text = String.fromCharCode.apply(null, new Uint8Array(inflate));
        var receive = JSON.parse(text);

        // Push signals to stack for later processing
        if (receive.signals) {
            APP.signalStack.push(receive.signals);
        }
    };

**为什么使用信号堆栈？**

* 数据持续从后端到达
* 处理和渲染图形需要时间
* 堆栈可防止处理期间数据丢失
* 支持按受控间隔批量处理


信号处理与图形更新
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    **APP.signalHandler()** 每 15ms 调用一次 **APP.processSignals()** 函数，以处理堆叠数据并更新图形：

.. code-block:: javascript

    APP.processSignals = function(new_signals) {
        var pointArr = [];
        var voltage;

        for (sig_name in new_signals) {
            // Skip empty signals
            if (new_signals[sig_name].size == 0) continue;

            // Build array of points for plotting
            var points = [];
            for (var i = 0; i < new_signals[sig_name].size; i++) {
                points.push([i, new_signals[sig_name].value[i]]);
            }

            pointArr.push(points);

            // Get the most recent value for numeric display
            voltage = new_signals[sig_name].value[new_signals[sig_name].size - 1];
        }

        // Update numeric display
        $('#value').text(parseFloat(voltage).toFixed(2) + "V");

        // Update graph
        APP.plot.setData(pointArr);
        APP.plot.resize();
        APP.plot.setupGrid();
        APP.plot.draw();
    };

**处理流程：**

1. 遍历数据中的所有信号
2. 将信号值转换为点数组 [index, value]
3. 使用最新值更新数字电压显示
4. 使用新的数据点更新 Flot 图形
5. 重绘图形以显示变化

|

实现后端
==========================

信号声明
-------------------

在 ``main.cpp`` 中声明一个具有更大缓冲区的全局信号，以传输连续数据：

.. code-block:: c

    CFloatSignal VOLTAGE("VOLTAGE", SIGNAL_SIZE_DEFAULT, 0.0f);

**与基础示例的主要区别：**

* **SIGNAL_SIZE_DEFAULT** 现在应设置为 **1024**
* 这意味着将向 Web UI 传输 1024 个数据点
* 创建电压测量值的滚动窗口

|

设置​​信号更新间隔
--------------------------------

在 **rp_app_init()** 中配置后端发送数据的频率：

.. code-block:: c

    CDataManager::GetInstance()->SetSignalInterval(SIGNAL_UPDATE_INTERVAL);

**SIGNAL_UPDATE_INTERVAL** 是一个常量（通常为 10ms），用于确定调用 **UpdateSignals()** 的频率。

|

连续信号更新
---------------------------

实现 **UpdateSignals()** 函数以连续读取和缓冲电压数据：

.. code-block:: c

    void UpdateSignals(void) {
        float val;
        
        // Read voltage from analog input pin 0
        rp_AIpinGetValue(0, &val);
        
        // Remove oldest measurement from buffer
        g_data.erase(g_data.begin());
        
        // Add new measurement to end of buffer
        g_data.push_back(val * GAIN.Value());
        
        // Write entire buffer to signal for transmission
        for(int i = 0; i < SIGNAL_SIZE_DEFAULT; i++) 
        {
            VOLTAGE[i] = g_data[i];
        }
    }

**数据流：**

1. 从 AI 引脚 0 读取当前电压
2. 从数据向量移除最旧值（创建滑动窗口）
3. 将新值追加到向量末尾
4. 将整个缓冲区复制到 VOLTAGE 信号
5. 信号会自动传输到前端

|

数据缓冲区管理
-----------------------

声明全局数据向量以缓冲测量值：

.. code-block:: c

    std::vector<float> g_data;

在 **rp_app_init()** 中初始化缓冲区：

.. code-block:: c

    // Initialize buffer with zeros
    g_data.resize(SIGNAL_SIZE_DEFAULT, 0.0f);

这会创建滑动窗口缓冲区：

* 始终包含最近的 1024 个测量值
* 新测量值到达时移除最旧的测量值
* 保持缓冲区大小恒定

|

理解数据流
=============================

完整信号采集周期
-----------------------------------

1. 后端定时器触发（每隔 SIGNAL_UPDATE_INTERVAL ms）
2. **调用 UpdateSignals()** → 读取 AI 引脚
3. **更新数据缓冲区** → 移除旧值，添加新值
4. **传输信号** → 将整个缓冲区发送到前端
5. **前端接收数据** → 通过 WebSocket 压缩传输
6. **堆叠数据** → 推送到 signalStack 数组
7. 信号处理器触发（每隔 15ms）
8. **处理信号** → 提取值并构建点数组
9. **更新图形** → Flot 使用新数据重绘

|

连续采集与按需采集
-------------------------

**基础示例（按需采集）：**

* 用户点击按钮 → 后端读取一次 → 传输单个值

**绘图示例（连续采集）：**

* 后端按固定间隔自动读取
* 连续传输多个值
* 前端显示滚动图形

|

图形可视化
====================

Flot 图形初始化
--------------------------

在 **APP.init()** 或类似函数中初始化 Flot 图形：

.. code-block:: javascript

    APP.plot = $.plot("#placeholder", [[]], {
        series: {
            lines: { show: true },
            points: { show: false }
        },
        xaxis: {
            min: 0,
            max: SIGNAL_SIZE_DEFAULT
        },
        yaxis: {
            min: 0,
            max: 3.3  // AI voltage range
        }
    });

|

信号处理程序设置
---------------------

设置周期性信号处理：

.. code-block:: javascript

    APP.signalHandler = function() {
        if (APP.signalStack.length > 0) {
            APP.processSignals(APP.signalStack[0]);
            APP.signalStack.splice(0, 1);  // Remove processed signal
        }
    };

    // Call every 15ms
    setInterval(APP.signalHandler, 15);

|

测试应用
========================

硬件设置
---------------

1. 将电压源（0-3.3 V）连接到模拟输入引脚之一（例如 AI0）
2. 要进行动态测试，请使用信号发生器或电位器
3. 确保正确接地

|

应用测试
--------------------

1. 编译并启动应用
2. 打开 Web 界面
3. **验证连续更新：**
   
   * 图形应显示滚动波形
   * 数值应持续更新
   
4. **测试不同电压：**
   
   * 调节电压源
   * 实时观察图形响应
   * 验证显示电压与输入电压一致

5. **测试图形性能：**
   
* 检查更新是否流畅（无卡顿）
   * 验证数据未被丢弃
   * 监控 CPU 使用率

|

性能注意事项
===========================

更新间隔调优
-----------------------

**SIGNAL_UPDATE_INTERVAL（后端）：**

* 过快：CPU 使用率高，并产生不必要的数据传输
* 过慢：时间分辨率低，图形不流畅
* 建议值：根据应用场景设置为 10-50 ms

**信号处理器间隔（前端）：**

* 过快：浏览器 CPU 使用率高，并增加渲染开销
* 过慢：显示延迟；如果数据到达速度快于处理速度，还可能导致堆栈溢出
* 建议值：15-30 ms

|

缓冲区大小优化
-------------------------

**SIGNAL_SIZE_DEFAULT：**

* 缓冲区更大：历史数据更多、可视化更平滑，但需要更多内存和带宽
* 缓冲区更小：历史数据更少、开销更低、更新更快
* 建议值：根据需求设置为 512-2048 个点

|

扩展本示例
=======================

可能的增强
----------------------

* **多通道** - 在同一图形或不同图形上绘制多个 AI 引脚
* **缩放和平移** - 添加 Flot 缩放/平移插件进行详细分析
* **数据导出** - 将采集数据保存为 CSV 或 JSON 文件
* **触发模式** - 根据电压阈值启动/停止采集
* **统计** - 显示最小值/最大值/平均值
* **频率分析** - 添加 FFT 以显示频率分量
* **可调时间尺度** - 动态更改时间窗口
* **自动缩放** - 根据信号幅度自动调整 Y 轴范围

|

后续步骤
===========

使用以下教程在本示例基础上继续学习：

* :ref:`带增益和偏移的电压 <webApp_example_SlowVoltage_Graph_Offset>` - 添加信号调理控件
* :ref:`生成电压 <webApp_example_genVolt>` - 生成用于测试的信号
* 高级绘图示例 - 多个图形、光标和测量

|

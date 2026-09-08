.. _webApp_example_SlowVoltage:

##############################################
从慢速模拟输入读取模拟电压
##############################################

本示例演示如何从 Red Pitaya 的慢速模拟输入引脚读取电压，并在 Web 界面中显示数值。
你将学习如何处理信号、触发按需测量，以及处理 WebSocket 通信中的数据压缩。

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

概述
=========

此应用从 :ref:`E2 扩展连接器 <E2_orig_gen>` 上的一个慢速模拟输入（AI）引脚读取电压，并在 Web 界面中显示。

**核心概念：**

* 使用 Red Pitaya API 读取模拟输入引脚
* 使用信号传输测量数据
* 处理压缩数据传输
* 从 UI 触发测量

**硬件：**

E2 连接器上的四个慢速模拟输入引脚（AI0-AI3）中的任意一个都可用于电压测量。

|

前置条件
==============

所需库
-------------------

本示例需要 **pako.js** 库来解压通过 WebSocket 传输的数据。

|

实现前端
===========================

引入所需库
---------------------------

将以下脚本添加到 ``index.html`` 中：

.. code-block:: html

    <script src="js/jquery-2.1.3.min.js"></script>
    <script src="js/pako.js"></script>
    <script src="js/app.js"></script>

|

HTML 结构
---------------

添加一个用于显示电压读数的区域：

.. code-block:: html

    <div id='value'></div>

添加一个用于触发电压读取的按钮：

.. code-block:: html

    <button id='read_button'>Read</button>

|

JavaScript 实现
--------------------------

处理接收数据
^^^^^^^^^^^^^^^^^^^^^^^

修改 ``app.js`` 中的 **APP.ws.onmessage()** 回调，以处理压缩的信号数据：

.. code-block:: javascript

    APP.ws.onmessage = function(ev) {
        // Decompress incoming data
        var data = new Uint8Array(ev.data);
        var inflate = pako.inflate(data);
        var text = String.fromCharCode.apply(null, new Uint8Array(inflate));
        var receive = JSON.parse(text);

        // Process signals if present
        if (receive.signals) {
            APP.processSignals(receive.signals);
        }
    };

**数据流：**

1. 从 WebSocket 接收压缩的二进制数据
2. 使用 pako.inflate() 解压
3. 转换为字符串并解析 JSON
4. 提取并处理信号


处理信号
^^^^^^^^^^^^^^^^^^^

实现 **APP.processSignals()** 函数以提取并显示电压值：

.. code-block:: javascript

    APP.processSignals = function(new_signals) {
        var voltage;

        for (sig_name in new_signals) {
            // Skip empty signals
            if (new_signals[sig_name].size == 0) continue;

            // Get the last (most recent) value
            voltage = new_signals[sig_name].value[new_signals[sig_name].size - 1];

            // Display voltage with 2 decimal places
            $('#value').text(parseFloat(voltage).toFixed(2) + "V");
        }
    };


触发测量
^^^^^^^^^^^^^^^^^^^^^^^^^

实现 **APP.readValue()**，以从后端请求电压读数：

.. code-block:: javascript

    APP.readValue = function() {
        var local = {};
        local['READ_VALUE'] = { value: true };
        APP.ws.send(JSON.stringify({ parameters: local }));
    };

将此函数连接到按钮点击事件：

.. code-block:: javascript

    $('#read_button').click(function() {
        APP.readValue();
    });

|

实现后端
==========================

信号声明
-------------------

在 ``main.cpp`` 中声明一个用于传输电压数据的全局信号：

.. code-block:: c

    CFloatSignal VOLTAGE("VOLTAGE", SIGNAL_SIZE_DEFAULT, 0.0f);

**信号参数：**

* **"VOLTAGE"** - 信号名称（必须与前端匹配）
* **SIGNAL_SIZE_DEFAULT** - 数据点数量（单次读数设为 1）
* **0.0f** - 每次测量的默认值

.. note::

    **SIGNAL_SIZE_DEFAULT** 决定传输的测量数量。本示例只需要当前读数，因此将其设为 1。

|

参数声明
----------------------

声明一个用于触发电压读取的参数：

.. code-block:: c

    CBooleanParameter READ_VALUE("READ_VALUE", CBaseParameter::RW, false, 0);

**参数属性：**

* **"READ_VALUE"** - 参数名称（必须与前端匹配）
* **CBaseParameter::RW** - 读/写访问权限
* **false** - 默认值（未触发）
* **0** - 无特殊标志

此参数充当触发器：当前端将其设为 true 时，后端读取电压。

|

读取模拟输入
---------------------

在 **OnNewParams()** 中更新参数，并在触发时读取电压：

.. code-block:: c

    void OnNewParams(void) {
        // Update parameter from frontend
        READ_VALUE.Update();

        // Check if read was requested
        if (READ_VALUE.Value() == true) {
            float val;

            // Read voltage from analog input pin 0
            rp_AIpinGetValue(0, &val);

            // Write value to signal (will be transmitted to frontend)
            VOLTAGE[0] = val;

            // Reset trigger parameter
            READ_VALUE.Set(false);
        }
    }

**处理流程：**

1. **更新参数** - 从 Nginx 获取最新的 READ_VALUE
2. **检查触发器** - 确认是否请求了读取（value == true）
3. **读取电压** - 使用 rp_AIpinGetValue() 从 AI pin 0 读取
4. **存入信号** - 将值写入 VOLTAGE 信号数组
5. **重置触发器** - 将 READ_VALUE 设回 false，以便下一次请求

|

Red Pitaya API 函数
--------------------------

**rp_AIpinGetValue()**

从慢速模拟输入引脚读取电压。

**语法：**

.. code-block:: c

    int rp_AIpinGetValue(int pin, float *value);

**参数：**

* **int pin** - 引脚编号（AI0-AI3 对应 0-3）
* **float \*value** - 用于存储电压值的指针

**返回值：**

* 成功时返回 **RP_OK**
* 失败时返回错误代码

**电压范围：**

* 通常为 0 V 至 3.3 V
* 确切范围可能因 Red Pitaya 型号而异

|

理解数据流
=============================

请求-响应周期
-----------------------

1. **用户点击“Read”按钮** → 前端触发读取
2. **前端发送 READ_VALUE 参数** → 通过 WebSocket 将其设为 true
3. **后端接收参数** → Nginx 调用 OnNewParams()
4. **后端读取模拟引脚** → 使用 rp_AIpinGetValue() 获取电压值
5. **后端将值存入信号** → VOLTAGE 信号更新为新值
6. **信号传输到前端** → 压缩后通过 WebSocket 发送
7. **前端解压数据** → 使用 pako.js 解压
8. **前端处理信号** → 提取电压值
9. **前端显示值** → 使用格式化后的电压更新 HTML 元素


为什么要压缩？
-----------------

WebSocket 数据压缩可以：

* **减少带宽占用** - 压缩数据消耗更少的网络资源
* **提高传输速度** - 更小的数据包传输更快
* **支持更大的数据数组** - 更高效地发送更多数据点

对于包含大量数据点的信号（例如绘图示例中的信号），这一点尤为重要。

|

测试应用
========================

硬件设置
---------------

1. 将电压源（0-3.3 V）连接到 E2 连接器上的一个模拟输入引脚
2. 使用 AI0（引脚 0），或修改代码以使用 AI1-AI3
3. 确保电压源与 Red Pitaya 之间正确接地

**电压源选项：**

* 实验室电源（设为 0-3.3 V）
* 连接在 3.3 V 与 GND 之间的电位器
* 另一块 Red Pitaya 的输出引脚
* 带分压器的电池

|

应用测试
--------------------

1. **编译并部署** 应用到 Red Pitaya
2. **在浏览器中打开 Web 界面**
3. **点击“Read”按钮**
4. **确认电压** 值显示在屏幕上
5. **改变输入电压** 并再次点击“Read”，确认数值已更新
6. **测试边界情况：**
   
   * 0 V 输入（连接到 GND）
   * 3.3 V 输入（连接到 3.3 V 电源）
   * 中间范围的电压

|

故障排除
----------------

**未显示电压：**

* 检查 WebSocket 连接是否已建立
* 确认 pako.js 库已加载
* 检查浏览器控制台中的 JavaScript 错误
* 确保 READ_VALUE 参数正在发送

**电压读数不正确：**

* 使用万用表确认输入电压
* 检查代码中的引脚编号是否与实际连接相符
* 确保正确接地
* 检查连接是否松动

**按钮无响应：**

* 确认已绑定按钮点击处理程序
* 检查 JavaScript 控制台中的错误
* 点击前确保 WebSocket 已打开

|

扩展本示例
=======================

可能的增强
----------------------

* **连续读取** - 改为按时间间隔自动读取，而不是按需读取
* **多通道** - 同时读取全部四个 AI 引脚并显示所有值
* **绘图可视化** - 绘制随时间变化的电压（参见 :ref:`带绘图的电压示例 <webApp_example_ReadSlowAnalogVoltage_Graph>`）
* **最小值/最大值跟踪** - 显示随时间变化的电压范围
* **告警阈值** - 对超出范围的电压触发警告
* **数据记录** - 将带时间戳的电压读数保存到文件
* **校准** - 添加偏移和增益校正以提高准确性

|

后续步骤
===========

可通过以下教程在本示例基础上继续学习：

* :ref:`使用绘图读取电压 <webApp_example_SlowVoltage_Graph>` - 添加实时绘图
* :ref:`带增益和偏移的电压 <webApp_example_SlowVoltage_Graph_Offset>` - 添加信号调理
* :ref:`生成电压 <webApp_example_genVolt>` - 了解模拟输出

|

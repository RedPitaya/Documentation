.. _webApp_example_LED:

###################################
使用按钮控制 LED 示例
###################################

本教程演示如何使用参数通过 Web 界面控制 Red Pitaya 的板载 LED。
您将学习前后端通信和通过 Red Pitaya API 控制硬件的基础知识。

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

概述
=========

本示例创建一个简单 Web 应用，其中的按钮可切换 Red Pitaya 某个 LED 的开关状态。
本应用演示：

* 创建交互式 UI 元素（按钮）
* 将参数从前端发送到后端
* 通过 Red Pitaya API 控制硬件外设
* 根据硬件状态更新 UI

|

前置条件
==============

FPGA 配置
-------------------

Red Pitaya API 需要 v0.94 FPGA 比特流来控制 LED。启动应用前请加载该比特流：

.. tabs::

    .. group-tab:: OS 2.00 或更高版本

        OS 2.00 引入了使用 **overlay.sh** 脚本的新 FPGA 加载系统，该脚本会同时加载 FPGA 二进制文件和设备 overlay。文件格式从 |xlinx_doc| 发生了变化。

        .. code-block:: shell-session

            redpitaya> overlay.sh v0.94

    .. group-tab:: OS 1.04 或更早版本

        .. code-block:: shell-session

            redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

.. |xlinx_doc| raw:: html

    <a href="https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18841847/Solution+ZynqMP+PL+Programming#SolutionZynqMPPLProgramming-BitstreamFormat" target="_blank">bit 转 bin</a>

.. note::

    运行与硬件交互的应用前，务必加载正确的 FPGA 镜像。

|

实现前端
===========================

HTML 结构
---------------

将以下元素添加到 `index.html` 文件：

**LED 控制按钮：**

.. code-block:: html

    <button id='led_state'>Turn on</button>

**LED 状态指示器：**

.. code-block:: html

    <div id='led_off'>LED Off</div>
    <div id='led_on'>LED On</div>

.. note::

    默认隐藏 **led_on** div，因为应用启动时 LED 处于关闭状态。

|

CSS 样式
------------

在 `css/style.css` 中添加样式以提供视觉反馈：

.. code-block:: css

    #led_off {
        color: #F00;  /* Red text for OFF state */
    }

    #led_on {
        display: none;  /* Hidden by default */
        color: #0F0;    /* Green text for ON state */
    }

    #led_state {
        margin-top: 20px;
        padding: 10px;
    }

|

JavaScript 逻辑
-----------------

在 `js/app.js` 中实现按钮点击处理程序和 LED 状态管理：


初始化 LED 状态
^^^^^^^^^^^^^^^^^^^^^

.. code-block:: javascript

    APP.led_state = false;


按钮点击处理程序
^^^^^^^^^^^^^^^^^^^^^

添加以下代码以切换 LED 状态并更新 UI：

.. code-block:: javascript

    $('#led_state').click(function() {
        // Toggle local LED state
        if (APP.led_state == true) {
            $('#led_on').hide();
            $('#led_off').show();
            APP.led_state = false;
        }
        else {
            $('#led_off').hide();
            $('#led_on').show();
            APP.led_state = true;
        }

        // Send current LED state to backend
        var local = {};
        local['LED_STATE'] = { value: APP.led_state };
        APP.ws.send(JSON.stringify({ parameters: local }));
    });

.. important::

    参数名 **LED_STATE** 必须在前端和后端完全一致。名称保持一致对正常通信至关重要。

|

实现后端
==========================

控制器位置
--------------------

后端控制器代码位于：

.. code-block:: text

    src/main.cpp

|

参数声明
----------------------

声明全局参数以接收前端发送的 LED 状态：

.. code-block:: c

    CBooleanParameter ledState("LED_STATE", CBaseParameter::RW, false, 0);

**参数结构：**

* **"LED_STATE"** - 参数名称（必须与前端匹配）
* **CBaseParameter::RW** - 访问模式（读/写）
* **false** - 初始值
* **0** - FPGA 更新标志

.. note::

    **参数类型：**
    
    * **CBooleanParameter** - 布尔值
    * **CIntParameter** - 整数值
    * **CFloatParameter** - 浮点值
    
    选择与 JavaScript 变量类型匹配的类型。

|

处理参数更新
---------------------------

在 **OnNewParams()** 函数中更新和处理参数；每当前端发送新参数时都会调用该函数。
发送新参数：

.. code-block:: c

    void OnNewParams(void) {
        // Update parameter from Nginx
        ledState.Update();
        
        // Control LED based on parameter value
        if (ledState.Value() == false) {
            rp_DpinSetState(RP_LED0, RP_LOW);
        }
        else {
            rp_DpinSetState(RP_LED0, RP_HIGH);
        }
    }

**工作原理：**

1. **ledState.Update()** - 使用参数名从 Nginx 获取最新值
2. **ledState.Value()** - 返回当前参数值
3. **rp_DpinSetState()** - 用于设置引脚状态的 Red Pitaya API 函数

|

Red Pitaya API 函数
--------------------------

**rp_DpinSetState()**

设置数字引脚或 LED 的状态。

**参数：**

* **rp_dpin_t pin** - 引脚标识符（LED 或数字引脚）
* **rp_pinState_t state** - 所需状态

**可用 LED：**

Red Pitaya 有 8 个可控制的 LED：

* **RP_LED0** 到 **RP_LED7**

**LED 状态：**

* **RP_HIGH** - LED 开启
* **RP_LOW** - LED 关闭

|

初始化与清理
---------------------------

在 **rp_app_init()** 中初始化 Red Pitaya API：

.. code-block:: c

    int rp_app_init(void) {
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
        return 0;
    }

在 **rp_app_exit()** 中释放资源：

.. code-block:: c

    int rp_app_exit(void) {
        rp_Release();
        return 0;
    }

|

构建与测试
=====================

编译应用
-------------------------

进入应用目录并进行编译：

.. code-block:: shell-session

    $ cd /opt/redpitaya/www/apps/myLedApp/
    $ make INSTALL_DIR=/opt/redpitaya


测试应用
---------------------

1. 打开 Web 浏览器并访问 Red Pitaya 的 IP 地址
2. 从应用菜单启动应用
3. 单击“Turn on”按钮
4. Red Pitaya 板卡上的 **RP_LED0** 应亮起
5. 按钮文本和状态指示器应更新
6. 再次单击以关闭 LED

|

后续步骤
===========

了解参数通信后，可以扩展此示例：

* 同时控制多个 LED
* 使用 PWM 添加 LED 亮度控制
* 创建 LED 模式或动画
* 将 LED 控制与其他外设结合

探索更高级的示例：

* :ref:`读取模拟电压 <webApp_example_SlowVoltage>` - 了解信号
* :ref:`生成电压 <webApp_example_genVolt>` - 控制模拟输出

|

.. _webApp_example_Simple:

####################
完整 Web 示例
####################

概述
=========

本示例提供一个完整、可直接使用的 Web 应用，演示常见的 Red Pitaya Web 开发
模式。这是理解完整应用结构的良好起点。

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

下载
=========

下载完整项目：

`Red Pitaya Web 应用示例（OS 2.0） <https://downloads.redpitaya.com/doc/Examples/RP_WEB_app_example_2.0.zip>`_

|

包含内容
================

本示例演示：

**输入字段处理**
    将数据发送到后端处理的交互式表单元素

**后端逻辑集成**
    前后端之间完整的参数处理

**数组数据传输**
    传输和接收数据数组的示例（随机数生成）

**完整应用结构**
    所有必需文件均已妥善组织（HTML、CSS、JavaScript、C++ 控制器）

|

演示的功能
======================

前端功能
------------------

* HTML 表单输入
* 实时数据显示
* WebSocket 通信
* 数据可视化
* 用户交互处理

后端功能
-----------------

* 参数处理
* 信号生成
* 数据数组管理
* 随机数据生成示例
* 正确的初始化和清理

|

使用本示例
===================

安装
-------------

1. 下载并解压 ZIP 文件
2. 将解压后的文件夹复制到 Red Pitaya 的 `/opt/redpitaya/www/apps/`
3. 编译后端：

   .. code-block:: shell-session

       $ cd /opt/redpitaya/www/apps/<example_folder>/
       $ make INSTALL_DIR=/opt/redpitaya

4. 访问 Red Pitaya Web 界面
5. 应用应出现在应用列表中

|

从示例中学习
--------------------------

本示例用于学习和修改。可以重点探索以下方面：

**HTML 结构** (`index.html`)
    查看表单元素和显示区域的组织方式

**JavaScript 逻辑** (`js/app.js`)
    了解 WebSocket 通信和数据处理

**控制器代码** (`src/main.cpp`)
    学习参数和信号管理

**样式** (`css/style.css`)
    查看专业的 CSS 组织方式

|

自定义
==============

将本示例作为自己应用的模板：

1. **修改 UI** - 更改 HTML 和 CSS 以满足需求
2. **添加参数** - 扩展参数列表以控制硬件
3. **实现逻辑** - 用自己的算法替换随机数据生成
4. **逐步测试** - 进行小幅修改并频繁测试

|

相关示例
=================

理解此完整示例后，可以进一步探索以下专题：

* :ref:`LED 控制 <webApp_example_LED>` - 简单参数处理
* :ref:`模拟电压读取 <webApp_example_SlowVoltage>` - 操作信号
* :ref:`电压生成 <webApp_example_GenVolt>` - 控制模拟输出
* :ref:`Nginx 请求 <webApp_example_Nginx>` - 高级服务端操作

|

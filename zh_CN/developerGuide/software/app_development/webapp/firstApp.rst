.. _webApp_firstWebApp:

###########################
创建您的第一个 Web 应用
###########################

本指南将带您从零创建一个基本的 Red Pitaya Web 应用。开始前，请按照 :ref:`SSH 连接指南 <ssh>` 配置开发环境。
还建议阅读 :ref:`系统概述 <webApp_sysOver>` 以了解应用架构。

.. contents:: 目录
    :local:
    :depth: 1
    :backlinks: top

|

前置条件
=============

开发环境
------------------------

所需软件和访问权限：

* 连接到 Red Pitaya 的 SSH（:ref:`SSH 连接指南 <ssh>`）
* 已配置开发环境（参见 :ref:`设置开发环境 <ssh>`）
* 了解 Red Pitaya 的前端/后端架构

|

初始设置
--------------

步骤 1：通过 SSH 连接
^^^^^^^^^^^^^^^^^^^^^^^^^

通过 SSH 连接到 Red Pitaya，并使文件系统可写：

.. code-block:: shell-session

    $ rw

步骤 2：安装 Git
^^^^^^^^^^^^^^^^^^^^^

安装 Git 以进行版本控制并克隆 Red Pitaya 仓库：

.. code-block:: shell-session

    # apt-get install git

步骤 3：配置 Git
^^^^^^^^^^^^^^^^^^^^^^^

设置 Git 身份信息：

.. code-block:: shell-session

    $ git config --global user.name "Your Name"
    $ git config --global user.email "your.email@example.com"

将 ``Your Name`` 和 ``your.email@example.com`` 替换为您的实际信息。

步骤 4：克隆 Red Pitaya 仓库
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

下载包含示例应用的 Red Pitaya 项目：

.. code-block:: shell-session

    $ cd /root/
    $ git clone https://github.com/RedPitaya/RedPitaya-Examples.git

示例应用位于 `/root/RedPitaya-Examples/web-tutorial/`。

|

了解文件结构
==================================

Red Pitaya 目录结构
--------------------------------

应用开发的关键目录：

**应用位置**

    .. code-block:: text

        /opt/redpitaya/www/apps/

    所有用户应用都存储在此处，便于访问和管理。

**FPGA 镜像**

    .. code-block:: text

        /opt/redpitaya/fpga/

    可用的 FPGA 比特流文件。

**库**

    .. code-block:: text

        /opt/redpitaya/lib/

    用于与应用链接的共享库。

|

应用文件夹结构
-----------------------------

每个应用都在同一目录中包含前端和后端文件，结构如下：

.. code-block:: text

    myFirstApp/
    ├── index.html          # Main HTML page
    ├── css/
    │   └── style.css       # Application styles
    ├── js/
    │   ├── jquery-2.1.3.min.js
    │   └── app.js          # JavaScript application logic
    ├── info/
    │   ├── info.json       # Application metadata
    │   └── icon.png        # Application icon
    ├── src/
    │   └── main.cpp        # Backend C/C++ source code
    ├── fpga.conf           # FPGA configuration (OS 1.04 and older)
    ├── fpga.sh             # FPGA loader script (OS 2.00 and newer)
    └── Makefile            # Build configuration

.. important::

    文件夹名称定义应用的唯一 ID。请选择一个不含空格且具有描述性的名称。

|

创建应用
===========================

步骤 1：复制模板
---------------------------

进入 apps 目录并复制模板：

.. code-block:: shell-session

    $ cd /opt/redpitaya/www/apps
    $ cp -r /root/RedPitaya-Examples/web-tutorial/1.template ./myFirstApp
    $ cd myFirstApp


步骤 2：配置应用元数据
----------------------------------------

编辑 `/info/info.json`，设置应用名称和描述：

.. code-block:: json

    {
        "name": "My First App",
        "version": "0.91-BUILD_NUMBER",
        "revision": "REVISION",
        "description": "This is my first application for Red Pitaya."
    }

也可以将 `/info/icon.png` 替换为自己的应用图标。

|

配置前端
==========================

HTML 结构
---------------

编辑 `index.html`，设置应用标题和结构：

.. code-block:: html

    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta http-equiv="content-type" content="text/html; charset=utf-8"></meta>
        <title>My First Application</title>
        <link rel="stylesheet" href="css/style.css">
        <script src="js/jquery-2.1.3.min.js"></script>
        <script src="js/app.js"></script>
    </head>
    <body>
        <div id='hello_message'>
            Connecting...
        </div>
    </body>
    </html>

|

CSS 样式
------------

在 `css/style.css` 中自定义外观：

.. code-block:: css

    html,
    body {
        width: 100%;
        height: 100%;
    }

    body {
        color: #cdcccc;
        overflow: auto;
        margin: 0;
    }

    #hello_message {
        width: 500px;
        height: 250px;
        margin: 0 auto;
        background-color: #333333;
        text-align: center;
        padding-top: 100px;
        font-size: 24px;
    }

|

JavaScript 应用逻辑
-----------------------------

编辑 `js/app.js` 实现应用逻辑。


配置应用 ID
^^^^^^^^^^^^^^^^^^^^^^^^^

更新应用 ID，使其与文件夹名称一致。将：

.. code-block:: javascript

    APP.config.app_id = '1.template';

改为：

.. code-block:: javascript

    APP.config.app_id = 'myFirstApp';


了解启动序列
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**APP.startApp()** 是应用入口，它会：

1. 发送请求加载应用状态
2. 如果状态不是 "OK"，则重试
3. 就绪后调用 **APP.connectWebSocket()**


WebSocket 连接
^^^^^^^^^^^^^^^^^^^^^

应用通过 WebSocket 与 Red Pitaya 通信：

.. code-block:: javascript

    if (window.WebSocket) {
        APP.ws = new WebSocket(APP.config.socket_url);
        APP.ws.binaryType = "arraybuffer";
    } else if (window.MozWebSocket) {
        APP.ws = new MozWebSocket(APP.config.socket_url);
        APP.ws.binaryType = "arraybuffer";
    } else {
        console.log('Browser does not support WebSocket');
    }

    if (APP.ws) {
        APP.ws.onopen = function() {
            $('#hello_message').text("Hello, Red Pitaya!");
            console.log('Socket opened');
        };

        APP.ws.onclose = function() {
            console.log('Socket closed');
        };

        APP.ws.onerror = function(ev) {
            $('#hello_message').text("Connection error");
            console.log('Websocket error: ', ev);
        };

        APP.ws.onmessage = function(ev) {
            console.log('Message received');
        };
    }


WebSocket 回调
^^^^^^^^^^^^^^^^^^^^

四个关键回调用于处理 WebSocket 事件：

* **APP.ws.onopen()** - 连接成功打开时调用
* **APP.ws.onclose()** - 连接关闭时调用
* **APP.ws.onerror()** - 发生连接错误时调用
* **APP.ws.onmessage()** - 从后端接收到消息时调用

|

配置后端
=========================

后端概述
-----------------

后端是一个编译为共享库（`controller.so`）的 C/C++ 应用，用于控制 Red Pitaya 硬件。
源代码位于 `src/` 文件夹中。

|

必需函数
-------------------

主文件必须实现由 Nginx 调用的 11 个必需函数：

.. code-block:: c

    const char *rp_app_desc(void)                     // Returns application description
    int rp_app_init(void)                             // Called when application starts
    int rp_app_exit(void)                             // Called when application closes
    int rp_set_params(rp_app_params_t *p, int len)    // Sets parameters from frontend
    int rp_get_params(rp_app_params_t **p)            // Gets parameters for frontend
    int rp_get_signals(float ***s, int *sig_num, int *sig_len)  // Gets signals for frontend
    void UpdateSignals(void)                          // Updates signals at set interval
    void UpdateParams(void)                           // Updates parameters at set interval
    void OnNewParams(void)                            // Called when parameters change
    void OnNewSignals(void)                           // Called when signals change
    void PostUpdateSignals(void)                      // Post-processing after signal update

这些函数为 Nginx 与硬件控制逻辑之间提供接口。

|

FPGA 配置
-------------------

.. tabs::

    .. group-tab:: OS 2.00 及更高版本

        使用 `fpga.sh` 脚本加载 FPGA 镜像。`fpga.conf` 文件已弃用。

    .. group-tab:: OS 1.04 及更早版本

        `fpga.conf` 文件指定启动时加载的 FPGA 镜像。FPGA 镜像位于 `/opt/redpitaya/fpga/`。

.. note::

    OS 2.00 更改了 FPGA 加载方法。`xdevcfg` 方法不再适用于较新的 Linux 内核。
    详情请参见 :ref:`添加按钮控制 LED <webApp_example_LED>`。

|

编译应用
============================

构建过程
--------------

使用提供的 Makefile 在 Red Pitaya 上编译应用：

.. code-block:: shell-session

    $ cd /opt/redpitaya/www/apps/myFirstApp/
    $ make INSTALL_DIR=/opt/redpitaya

构建过程会创建 `controller.so`，应用启动时由 Nginx 加载该文件。


测试应用
-------------------------

1. 打开 Web 浏览器并访问 Red Pitaya 的 IP 地址
2. 应用应出现在应用列表中
3. 单击应用以启动它
4. WebSocket 连接成功后，“Connecting...”消息应变为“Hello, Red Pitaya!”

.. note::

    **何时重新编译：**
    
    * 修改 `src/` 中的 C/C++ 源文件后
    * 初次复制模板后
    
    **无需重新编译：**
    
    * 修改 HTML、CSS 或 JavaScript 文件后
    * 只需刷新浏览器即可查看前端更改

|

后续步骤
===========

现在基本应用已经运行，请探索以下示例以了解更高级的功能：

* :ref:`添加按钮控制 LED <webApp_example_LED>` - 了解参数处理
* :ref:`Web 应用示例 <webApp_Examples>` - 更复杂的示例

详细 API 文档请参阅 :rp-github:`Web 教程示例 <RedPitaya-Examples/tree/dev/web-tutorial>` 仓库。

|

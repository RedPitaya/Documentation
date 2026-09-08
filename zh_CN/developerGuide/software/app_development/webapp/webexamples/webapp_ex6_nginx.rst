.. _webApp_example_nginx:

###################################
Nginx 请求与 Lua 集成
###################################

本示例演示如何通过 Nginx 请求执行系统命令并访问文件系统。
你将学习如何使用 Lua 脚本创建自定义 Nginx location，从而将 Web 应用扩展到标准 WebSocket API 之外。

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

概述
=========

此应用使用 Nginx location 块和 Lua 脚本与 Red Pitaya 文件系统交互，从而创建简单的文件管理器。

**关键概念：**

* 自定义 Nginx location 块
* 在 Nginx 配置中使用 Lua 脚本
* 带参数的 HTTP GET 请求
* 从 Web 应用执行系统命令
* 浏览和导航文件系统

**安全警告：**

本示例展示的功能强大，如果安全措施不当可能带来风险。在生产应用中始终要验证并清理输入。

|

准备工作
==============

基础示例
-------------------

将 :ref:`创建第一个应用 <firstApp>` 作为本示例的基础，因为它提供了基本应用结构。

所需知识
-------------------

* 对 Nginx 配置有基本了解
* 熟悉 HTTP GET 请求
* 了解 Lua 脚本基本概念（有帮助但非必需）

|

实现前端
===========================

HTML 结构
---------------

在 ``index.html`` 中创建用于显示文件系统内容的容器：

.. code-block:: html

    <div id="file_system"></div>

此 div 将动态填充文件和文件夹。

|

JavaScript 实现
--------------------------

打开目录
^^^^^^^^^^^^^^^^^^^^

在 ``app.js`` 中添加 **APP.openDir()** 函数以请求目录内容：

.. code-block:: javascript

    APP.openDir = function(dir) {
        $.get('/ngx_app_test?dir=' + dir).done(function(msg) {
            var ngx_files = msg.split("\n"); 
            APP.printFiles(ngx_files);
        });
    };

**工作原理：**

1. **$.get()** 向 ``/ngx_app_test`` location 发送 HTTP GET 请求
2. **dir 参数** 指定要列出的目录
3. 服务器响应时执行 **done()** 回调
4. 按换行符拆分响应以获取各个文件/文件夹
5. 调用 **APP.printFiles()** 显示结果

显示文件
^^^^^^^^^^^^^^^^^

实现 **APP.printFiles()** 以创建交互式文件/文件夹元素：

.. code-block:: javascript

    APP.printFiles = function(files) {
        // Clear previous content
        $('.child').remove();
        
        // Create elements for each file/folder
        for (var i = 0; i < files.length; i++) {
            if (files[i] != "") {
                div = document.createElement('div');
                div.id = files[i] + "/";
                div.className = 'child';
                
                if (i == 0)
                    div.innerHTML = '..';  // Parent directory link
                else
                    div.innerHTML = '' + files[i].split("/").pop() + '';
                
                // Attach click handler to navigate
                div.firstElementChild.onclick = function() {            
                    APP.openDir(this.parentNode.id);
                }
                
                file_system.appendChild(div);
            }
        }
    };

**处理流程：**

1. **移除旧内容** - 删除 class 为 'child' 的元素
2. **遍历文件** - 为每个项目创建 div
3. **设置元素属性：**
   
   * ID：项目的完整路径
   * Class：'child'，便于稍后删除
   * innerHTML：显示名称（仅文件名）

4. **附加点击处理器** - 点击时导航到文件夹
5. **特殊处理** - 第一项是表示父目录的 ".."

初始化文件浏览器
^^^^^^^^^^^^^^^^^^^^^^^^

在 **APP.ws.onopen()** 回调中，连接建立时打开根目录：

.. code-block:: javascript

    APP.ws.onopen = function() {
        APP.openDir("/");
    };

|

实现后端
==========================

Nginx 配置文件
--------------------------

在项目中创建文件 ``nginx.conf``，内容如下：

Location 块结构
^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: nginx

    location /ngx_app_test {
        add_header 'Access-Control-Allow-Origin' '*';
        add_header 'Access-Control-Allow-Credentials' 'true';
        add_header 'Access-Control-Allow-Methods' 'GET, POST, OPTIONS';
        add_header 'Access-Control-Allow-Headers' 'DNT,X-Mx-ReqToken,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type';
        add_header 'Content-type' 'text/plain; charset=utf-8'; 

        content_by_lua '
            local args = ngx.req.get_uri_args()
            if args.dir then
                os.execute("(dirname "..args.dir.." && ls -d "..args.dir.."*) > /tmp/ngx_file_system");
                local handle = io.open("/tmp/ngx_file_system", "r");
                local res = handle:read("*all");
                io.close(handle);
                ngx.say(res);
            end        
        ';
    }

**配置解析：**

标头部分
^^^^^^^^^^^^^^^

.. code-block:: nginx

    add_header 'Access-Control-Allow-Origin' '*';
    add_header 'Access-Control-Allow-Credentials' 'true';
    add_header 'Access-Control-Allow-Methods' 'GET, POST, OPTIONS';
    add_header 'Access-Control-Allow-Headers' 'DNT,X-Mx-ReqToken,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type';
    add_header 'Content-type' 'text/plain; charset=utf-8';

**用途：**

* **Access-Control 标头** - 启用 CORS（跨源资源共享）
* **Content-type** - 指定采用 UTF-8 编码的纯文本响应

Lua 脚本部分
^^^^^^^^^^^^^^^^^^^

.. code-block:: lua

    local args = ngx.req.get_uri_args()
    if args.dir then
        os.execute("(dirname "..args.dir.." && ls -d "..args.dir.."*) > /tmp/ngx_file_system");
        local handle = io.open("/tmp/ngx_file_system", "r");
        local res = handle:read("*all");
        io.close(handle);
        ngx.say(res);
    end

**逐步执行：**

1. **获取 URI 参数** - 从 GET 请求提取参数
2. **检查 dir 参数** - 确认已提供目录路径
3. **执行 shell 命令：**
   
   * ``dirname`` - 获取父目录
   * ``ls -d`` - 列出目录内容
   * ``> /tmp/ngx_file_system`` - 将输出保存到临时文件

4. **读取结果** - 打开临时文件并读取内容
5. **关闭文件句柄** - 清理资源
6. **发送响应** - 将文件列表返回给客户端

|

理解 Shell 命令
=================================

命令解析
------------------

.. code-block:: bash

    (dirname /path/to/dir && ls -d /path/to/dir*) > /tmp/ngx_file_system

**组成部分：**

1. **dirname /path/to/dir** - 返回父目录路径
2. **&&** - 第一条命令成功时执行下一条
3. **ls -d /path/to/dir\*** - 列出目录中的所有项目
4. **> /tmp/ngx_file_system** - 将输出重定向到文件

**示例输出：**

.. code-block:: none

    /home/user
    /home/user/documents
    /home/user/downloads
    /home/user/pictures

|

安全注意事项
========================

潜在风险
----------------

**命令注入：**

当前实现会将用户输入直接传递给 shell 命令，这很危险：

.. code-block:: lua

    os.execute("... "..args.dir.." ...")  -- UNSAFE!

**漏洞：** 类似 ``/home; rm -rf /`` 的恶意输入可能执行危险命令。

|

保护应用安全
--------------------------

**输入验证：**

.. code-block:: lua

    -- Validate directory path
    local function is_safe_path(path)
        -- Only allow alphanumeric, /, -, _, .
        return string.match(path, "^[%w%/%-%_.]+$") ~= nil
    end

    local args = ngx.req.get_uri_args()
    if args.dir and is_safe_path(args.dir) then
        -- Safe to proceed
    end

**路径限制：**

.. code-block:: lua

    -- Restrict to specific directories
    local allowed_paths = {"/home/", "/tmp/", "/opt/app/"}
    local function is_allowed_path(path)
        for _, allowed in ipairs(allowed_paths) do
            if string.sub(path, 1, #allowed) == allowed then
                return true
            end
        end
        return false
    end

**改用 Lua 文件操作：**

.. code-block:: lua

    -- Safer: Use Lua's file system operations instead of shell
    local lfs = require("lfs")
    for file in lfs.dir(directory) do
        -- Process files safely
    end

|

部署 Nginx 配置
===============================

配置文件位置
-----------------------------

1. 将 ``nginx.conf`` 复制到 Red Pitaya 上的适当位置
2. 典型路径：``/opt/redpitaya/www/apps/your_app/nginx.conf``

|

应用配置
--------------------

**方法 1：重启（最简单）**

.. code-block:: shell-session

    # reboot

**方法 2：重新加载 Nginx（无需停机）**

.. code-block:: shell-session

    # nginx -s reload

**方法 3：重启 Nginx 服务**

.. code-block:: shell-session

    # systemctl restart nginx

|

测试应用
========================

应用测试
--------------------

1. 将应用 **部署** 到 Red Pitaya
2. **重启或重新加载** Nginx 以应用配置
3. 在浏览器中**打开 Web 界面**
4. **确认根目录** 自动加载
5. **测试导航：**
   
   * 点击文件夹名称进入其中
   * 点击 ".." 返回父目录
   * 确认文件和文件夹名称显示正确

6. **检查浏览器控制台** 是否有错误

|

故障排除
----------------

**未显示文件：**

* 检查 Nginx 配置是否已加载：``nginx -T | grep ngx_app_test``
* 确认 Nginx 中已启用 Lua 模块
* 检查浏览器控制台中的 HTTP 错误
* 直接测试端点：``http://rp-ip/ngx_app_test?dir=/``

**权限错误：**

* Nginx 以特定用户运行（通常为 nobody 或 nginx）
* 确认该用户对目录具有读取权限
* 检查 Nginx 错误日志：``tail -f /var/log/nginx/error.log``

**Lua 错误：**

* 检查 Nginx 错误日志中的 Lua 脚本错误
* 确认 Lua 语法正确
* 如可能，单独测试 Lua 代码

|

理解 Nginx + Lua
==========================

为什么使用 Nginx location？
----------------------------

**优点：**

* **直接访问文件系统** - 无需后端控制器即可读写文件
* **执行系统命令** - 运行 shell 脚本和实用程序
* **HTTP API 端点** - 轻松创建 RESTful API
* **高性能** - Nginx 高效处理请求
* **灵活路由** - 创建自定义 URL 模式

**适用场景：**

* 文件上传/下载
* 系统信息查询
* 管理任务
* 与外部工具集成
* 不适合 WebSocket 模型的自定义 API

|

Nginx 中的 Lua
---------------

**OpenResty/lua-nginx-module 提供：**

* 访问 Nginx 请求/响应对象
* 非阻塞 I/O 操作
* 访问请求参数、标头和正文
* 向其他服务发起 HTTP 请求
* 文件系统操作

**常用 Lua Nginx API 函数：**

* ``ngx.req.get_uri_args()`` - 获取查询参数
* ``ngx.say()`` - 发送响应
* ``ngx.print()`` - 发送响应（不换行）
* ``ngx.var.request_uri`` - 获取当前 URI
* ``ngx.req.get_headers()`` - 获取请求标头

|

扩展此示例
=======================

可能的增强功能
----------------------

* **文件上传** - 增加向 Red Pitaya 上传文件的功能
* **文件下载** - 启用从 Red Pitaya 下载文件
* **文件操作** - 创建、删除、重命名文件/文件夹
* **文件预览** - 显示文本文件内容
* **搜索功能** - 按名称或内容搜索文件
* **权限显示** - 显示文件权限和所有者
* **文件大小信息** - 显示文件大小和时间戳
* **面包屑导航** - 显示带可点击分段的当前路径
* **安全性** - 添加身份验证和输入验证
* **图标** - 添加文件类型图标以改善用户体验

|

高级集成
----------------------

* **数据库访问** - 连接 SQLite、MySQL、PostgreSQL
* **JSON API** - 创建 RESTful API 端点
* **WebSocket 代理** - 代理 WebSocket 连接
* **负载均衡** - 在服务之间分配请求
* **缓存** - 使用 Nginx 实现响应缓存
* **身份验证** - 添加 OAuth、JWT 或基本身份验证

|

后续步骤
===========

进一步了解 Nginx 和 Lua：

* **Nginx 文档** - https://nginx.org/en/docs/
* **OpenResty** - https://openresty.org/
* **lua-nginx-module** - https://github.com/openresty/lua-nginx-module
* **Lua 编程** - https://www.lua.org/manual/5.1/

相关教程：

* 服务器端文件处理
* 高级 HTTP API 开发
* 与外部服务集成

|

.. _webApp_example_nginx:

###################################
Nginx Requests and Lua Integration
###################################

This example demonstrates how to execute system commands and access the file system through Nginx requests. 
You'll learn how to create custom Nginx locations with Lua scripting to extend your web application beyond 
the standard WebSocket API.

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

Overview
=========

This application creates a simple file manager using Nginx location blocks and Lua scripting to interact 
with Red Pitaya's file system.

**Key concepts:**

* Custom Nginx location blocks
* Lua scripting within Nginx configuration
* HTTP GET requests with parameters
* Executing system commands from web applications
* File system browsing and navigation

**Security warning:**

This example demonstrates powerful capabilities that can pose security risks if not properly secured. Always 
validate and sanitize inputs in production applications.

|

Prerequisites
==============

Foundation example
-------------------

Take :ref:`Creating first app <firstApp>` as the foundation for this example, as it provides the basic application 
structure.

Required knowledge
-------------------

* Basic understanding of Nginx configuration
* Familiarity with HTTP GET requests
* Basic Lua scripting concepts (helpful but not required)

|

Implementing the Frontend
===========================

HTML structure
---------------

Create a container to display file system contents in ``index.html``:

.. code-block:: html

    <div id="file_system"></div>

This div will be populated dynamically with files and folders.

|

JavaScript implementation
--------------------------

Opening directories
^^^^^^^^^^^^^^^^^^^^

Add the **APP.openDir()** function to ``app.js`` to request directory contents:

.. code-block:: javascript

    APP.openDir = function(dir) {
        $.get('/ngx_app_test?dir=' + dir).done(function(msg) {
            var ngx_files = msg.split("\n"); 
            APP.printFiles(ngx_files);
        });
    };

**How it works:**

1. **$.get()** sends HTTP GET request to ``/ngx_app_test`` location
2. **dir parameter** specifies which directory to list
3. **done()** callback executes when server responds
4. **Split response** by newlines to get individual files/folders
5. **Call APP.printFiles()** to display results

Displaying files
^^^^^^^^^^^^^^^^^

Implement **APP.printFiles()** to create interactive file/folder elements:

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

**Process flow:**

1. **Remove old content** - Delete elements with class 'child'
2. **Iterate through files** - Create div for each item
3. **Set element properties:**
   
   * ID: Full path to item
   * Class: 'child' for easy removal later
   * innerHTML: Display name (filename only)

4. **Attach click handler** - Navigate to folder when clicked
5. **Special handling** - First item is ".." for parent directory

Initialize file browser
^^^^^^^^^^^^^^^^^^^^^^^^

In **APP.ws.onopen()** callback, open the root directory on connection:

.. code-block:: javascript

    APP.ws.onopen = function() {
        APP.openDir("/");
    };

|

Implementing the Backend
==========================

Nginx configuration file
--------------------------

Create a new file ``nginx.conf`` in your project with the following content:

Location block structure
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

**Configuration breakdown:**

Headers section
^^^^^^^^^^^^^^^

.. code-block:: nginx

    add_header 'Access-Control-Allow-Origin' '*';
    add_header 'Access-Control-Allow-Credentials' 'true';
    add_header 'Access-Control-Allow-Methods' 'GET, POST, OPTIONS';
    add_header 'Access-Control-Allow-Headers' 'DNT,X-Mx-ReqToken,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type';
    add_header 'Content-type' 'text/plain; charset=utf-8';

**Purpose:**

* **Access-Control headers** - Enable CORS (Cross-Origin Resource Sharing)
* **Content-type** - Specify plain text response with UTF-8 encoding

Lua script section
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

**Step-by-step execution:**

1. **Get URI arguments** - Extract parameters from GET request
2. **Check for dir parameter** - Verify directory path was provided
3. **Execute shell command:**
   
   * ``dirname`` - Get parent directory
   * ``ls -d`` - List directory contents
   * ``> /tmp/ngx_file_system`` - Save output to temporary file

4. **Read results** - Open temp file and read contents
5. **Close file handle** - Clean up resources
6. **Send response** - Return file list to client

|

Understanding the Shell Command
=================================

Command breakdown
------------------

.. code-block:: bash

    (dirname /path/to/dir && ls -d /path/to/dir*) > /tmp/ngx_file_system

**Components:**

1. **dirname /path/to/dir** - Returns parent directory path
2. **&&** - Execute next command if first succeeds
3. **ls -d /path/to/dir\*** - List all items in directory
4. **> /tmp/ngx_file_system** - Redirect output to file

**Example output:**

.. code-block:: none

    /home/user
    /home/user/documents
    /home/user/downloads
    /home/user/pictures

|

Security Considerations
========================

Potential risks
----------------

**Command injection:**

The current implementation directly passes user input to shell commands, which is dangerous:

.. code-block:: lua

    os.execute("... "..args.dir.." ...")  -- UNSAFE!

**Vulnerability:** Malicious input like ``/home; rm -rf /`` could execute dangerous commands.

|

Securing the application
--------------------------

**Input validation:**

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

**Path restrictions:**

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

**Use Lua file operations instead:**

.. code-block:: lua

    -- Safer: Use Lua's file system operations instead of shell
    local lfs = require("lfs")
    for file in lfs.dir(directory) do
        -- Process files safely
    end

|

Deploying Nginx Configuration
===============================

Configuration file placement
-----------------------------

1. Copy your ``nginx.conf`` to the appropriate location on Red Pitaya
2. Typical path: ``/opt/redpitaya/www/apps/your_app/nginx.conf``

|

Apply configuration
--------------------

**Method 1: Reboot (simplest)**

.. code-block:: shell-session

    # reboot

**Method 2: Reload Nginx (no downtime)**

.. code-block:: shell-session

    # nginx -s reload

**Method 3: Restart Nginx service**

.. code-block:: shell-session

    # systemctl restart nginx

|

Testing the Application
========================

Application testing
--------------------

1. **Deploy application** to Red Pitaya
2. **Reboot or reload** Nginx to apply configuration
3. **Open web interface** in browser
4. **Verify root directory** loads automatically
5. **Test navigation:**
   
   * Click on folder names to enter them
   * Click ".." to go back to parent directory
   * Verify file and folder names display correctly

6. **Check browser console** for any errors

|

Troubleshooting
----------------

**No files displayed:**

* Check Nginx configuration is loaded: ``nginx -T | grep ngx_app_test``
* Verify Lua module is enabled in Nginx
* Check browser console for HTTP errors
* Test endpoint directly: ``http://rp-ip/ngx_app_test?dir=/``

**Permission errors:**

* Nginx runs as specific user (usually nobody or nginx)
* Verify user has read permissions on directories
* Check Nginx error log: ``tail -f /var/log/nginx/error.log``

**Lua errors:**

* Check Nginx error log for Lua script errors
* Verify Lua syntax is correct
* Test Lua code separately if possible

|

Understanding Nginx + Lua
==========================

Why use Nginx locations?
-------------------------

**Advantages:**

* **Direct file system access** - Read/write files without backend controller
* **Execute system commands** - Run shell scripts, utilities
* **HTTP API endpoints** - Create RESTful APIs easily
* **High performance** - Nginx handles requests efficiently
* **Flexible routing** - Create custom URL patterns

**When to use:**

* File uploads/downloads
* System information queries
* Administrative tasks
* Integration with external tools
* Custom APIs not fitting WebSocket model

|

Lua in Nginx
-------------

**OpenResty/lua-nginx-module provides:**

* Access to Nginx request/response objects
* Non-blocking I/O operations
* Access to request parameters, headers, body
* Ability to make HTTP requests to other services
* File system operations

**Common Lua Nginx API functions:**

* ``ngx.req.get_uri_args()`` - Get query parameters
* ``ngx.say()`` - Send response
* ``ngx.print()`` - Send response (no newline)
* ``ngx.var.request_uri`` - Get current URI
* ``ngx.req.get_headers()`` - Get request headers

|

Extending This Example
=======================

Possible enhancements
----------------------

* **File upload** - Add ability to upload files to Red Pitaya
* **File download** - Enable downloading files from Red Pitaya
* **File operations** - Create, delete, rename files/folders
* **File preview** - Display text file contents
* **Search functionality** - Search for files by name or content
* **Permissions display** - Show file permissions and ownership
* **File size information** - Display file sizes and timestamps
* **Breadcrumb navigation** - Show current path with clickable segments
* **Security** - Add authentication and input validation
* **Icons** - Add file type icons for better UX

|

Advanced integrations
----------------------

* **Database access** - Connect to SQLite, MySQL, PostgreSQL
* **JSON APIs** - Create RESTful API endpoints
* **WebSocket proxy** - Proxy WebSocket connections
* **Load balancing** - Distribute requests across services
* **Caching** - Implement response caching with Nginx
* **Authentication** - Add OAuth, JWT, or basic auth

|

Next Steps
===========

Learn more about Nginx and Lua:

* **Nginx documentation** - https://nginx.org/en/docs/
* **OpenResty** - https://openresty.org/
* **lua-nginx-module** - https://github.com/openresty/lua-nginx-module
* **Lua programming** - https://www.lua.org/manual/5.1/

Related tutorials:

* Server-side file processing
* Advanced HTTP API development
* Integration with external services

|

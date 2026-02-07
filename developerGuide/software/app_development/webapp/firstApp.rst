.. _webApp_firstWebApp:

###########################
Creating Your First Web App
###########################

This guide walks you through creating a basic Red Pitaya web application from scratch. Before starting, ensure you 
have configured your development environment following the :ref:`SSH connection guide <ssh>`. It's also recommended 
to read the :ref:`System Overview <webApp_sysOver>` to understand the application architecture.

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

Prerequisites
=============

Development environment
------------------------

Required software and access:

* SSH connection to Red Pitaya (:ref:`SSH connection guide <ssh>`)
* Development environment configured (see :ref:`Setting development environment <ssh>`)
* Understanding of Red Pitaya's frontend/backend architecture

|

Initial Setup
--------------

Step 1: Connect via SSH
^^^^^^^^^^^^^^^^^^^^^^^^^

Connect to your Red Pitaya via SSH and make the filesystem writable:

.. code-block:: shell-session

    $ rw

Step 2: Install Git
^^^^^^^^^^^^^^^^^^^^^

Install Git for version control and cloning the Red Pitaya repository:

.. code-block:: shell-session

    # apt-get install git

Step 3: Configure Git
^^^^^^^^^^^^^^^^^^^^^^^

Set up your Git identity:

.. code-block:: shell-session

    $ git config --global user.name "Your Name"
    $ git config --global user.email "your.email@example.com"

Replace "Your Name" and "your.email@example.com" with your actual information.

Step 4: Clone Red Pitaya repository
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Download the Red Pitaya project containing example applications:

.. code-block:: shell-session

    $ cd /root/
    $ git clone https://github.com/RedPitaya/RedPitaya-Examples.git

Example applications are located in `/root/RedPitaya-Examples/web-tutorial/`.

|

Understanding the File Structure
==================================

Red Pitaya directory structure
--------------------------------

Key directories for application development:

**Application location**

    .. code-block:: text

        /opt/redpitaya/www/apps/

    All user applications are stored here for easy access and management.

**FPGA images**

    .. code-block:: text

        /opt/redpitaya/fpga/

    Available FPGA bitstream files.

**Libraries**

    .. code-block:: text

        /opt/redpitaya/lib/

    Shared libraries for linking with your application.

|

Application folder structure
-----------------------------

Each application contains both frontend and backend files in a single directory with the following structure:

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

    The folder name defines your application's unique ID. Choose a descriptive name without spaces.

|

Creating Your Application
===========================

Step 1: Copy the template
---------------------------

Navigate to the apps directory and copy the template:

.. code-block:: shell-session

    $ cd /opt/redpitaya/www/apps
    $ cp -r /root/RedPitaya-Examples/web-tutorial/1.template ./myFirstApp
    $ cd myFirstApp


Step 2: Configure application metadata
----------------------------------------

Edit `/info/info.json` to set your application's name and description:

.. code-block:: json

    {
        "name": "My First App",
        "version": "0.91-BUILD_NUMBER",
        "revision": "REVISION",
        "description": "This is my first application for Red Pitaya."
    }

Optionally replace `/info/icon.png` with your own application icon.

|

Configuring the Frontend
==========================

HTML structure
---------------

Edit `index.html` to set your application title and structure:

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

CSS styling
------------

Customize the appearance in `css/style.css`:

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

JavaScript application logic
-----------------------------

Edit `js/app.js` to implement your application logic.


Configure application ID
^^^^^^^^^^^^^^^^^^^^^^^^^

Update the application ID to match your folder name. Change:

.. code-block:: javascript

    APP.config.app_id = '1.template';

To:

.. code-block:: javascript

    APP.config.app_id = 'myFirstApp';


Understanding the startup sequence
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**APP.startApp()** is the entry point that:

1. Sends requests to load application status
2. Retries if status is not "OK"
3. Calls **APP.connectWebSocket()** when ready


WebSocket connection
^^^^^^^^^^^^^^^^^^^^^

The application establishes WebSocket communication with Red Pitaya:

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


WebSocket callbacks
^^^^^^^^^^^^^^^^^^^^

Four essential callbacks handle WebSocket events:

* **APP.ws.onopen()** - Called when connection successfully opens
* **APP.ws.onclose()** - Called when connection closes
* **APP.ws.onerror()** - Called when connection error occurs
* **APP.ws.onmessage()** - Called when message is received from backend

|

Configuring the Backend
=========================

Backend overview
-----------------

The backend is a C/C++ application compiled into a shared library (`controller.so`) that controls Red Pitaya hardware. 
Source code is located in the `src/` folder.

|

Required functions
-------------------

Your main file must implement 11 mandatory functions called by Nginx:

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

These functions provide the interface between Nginx and your hardware control logic.

|

FPGA configuration
-------------------

.. tabs::

    .. group-tab:: OS 2.00 and higher

        Use the `fpga.sh` script to load FPGA images. The `fpga.conf` file is deprecated.

    .. group-tab:: OS 1.04 and older

        The `fpga.conf` file specifies which FPGA image to load at startup. FPGA images are located in `/opt/redpitaya/fpga/`.

.. note::

    The FPGA loading method changed in OS 2.00. The `xdevcfg` method no longer works with newer Linux kernels. 
    See :ref:`Add a button to control LED <webApp_example_LED>` for details.

|

Compiling Your Application
============================

Build process
--------------

Compile your application on Red Pitaya using the provided Makefile:

.. code-block:: shell-session

    $ cd /opt/redpitaya/www/apps/myFirstApp/
    $ make INSTALL_DIR=/opt/redpitaya

The build process creates `controller.so`, which Nginx loads when the application starts.


Testing your application
-------------------------

1. Open a web browser and navigate to your Red Pitaya's IP address
2. Your application should appear in the application list
3. Click on the application to launch it
4. The "Connecting..." message should change to "Hello, Red Pitaya!" when the WebSocket connects

.. note::

    **When to recompile:**
    
    * After modifying C/C++ source files in `src/`
    * After initial template copy
    
    **No recompilation needed:**
    
    * After changing HTML, CSS, or JavaScript files
    * Simply refresh your browser to see frontend changes

|

Next Steps
===========

Now that you have a basic application running, explore the examples to learn more advanced features:

* :ref:`Add a button to control LED <webApp_example_LED>` - Learn parameter handling
* :ref:`Web Application Examples <webApp_Examples>` - More complex examples

For detailed API documentation, refer to the :rp-github:`Web Tutorial Example <RedPitaya-Examples/tree/dev/web-tutorial>` repository.

|

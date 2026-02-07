.. _webApp_example_Simple:

####################
Complete Web Example
####################

Overview
=========

This example provides a complete, ready-to-use web application demonstrating common Red Pitaya web development 
patterns. It's an excellent starting point for understanding the full application structure.

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

Download
=========

Download the complete project:

`Red Pitaya Web App Example (OS 2.0) <https://downloads.redpitaya.com/doc/Examples/RP_WEB_app_example_2.0.zip>`_

|

What's Included
================

The example demonstrates:

**Input field handling**
    Interactive form elements that send data to the backend for processing

**Backend logic integration**
    Complete parameter handling between frontend and backend

**Array data transmission**
    Example of transmitting and receiving arrays of data (random number generation)

**Complete application structure**
    All required files properly organized (HTML, CSS, JavaScript, C++ controller)

|

Features Demonstrated
======================

Frontend features
------------------

* HTML form inputs
* Real-time data display
* WebSocket communication
* Data visualization
* User interaction handling

Backend features
-----------------

* Parameter processing
* Signal generation
* Data array management
* Random data generation example
* Proper initialization and cleanup

|

Using This Example
===================

Installation
-------------

1. Download and extract the ZIP file
2. Copy the extracted folder to `/opt/redpitaya/www/apps/` on your Red Pitaya
3. Compile the backend:

   .. code-block:: shell-session

       $ cd /opt/redpitaya/www/apps/<example_folder>/
       $ make INSTALL_DIR=/opt/redpitaya

4. Access your Red Pitaya web interface
5. The application should appear in the application list

|

Learning from the example
--------------------------

This example is designed to be studied and modified. Key areas to explore:

**HTML structure** (`index.html`)
    See how form elements and display areas are organized

**JavaScript logic** (`js/app.js`)
    Understand WebSocket communication and data handling

**Controller code** (`src/main.cpp`)
    Learn parameter and signal management

**Styling** (`css/style.css`)
    View professional CSS organization

|

Customization
==============

Use this example as a template for your own applications:

1. **Modify the UI** - Change HTML and CSS to match your needs
2. **Add parameters** - Extend the parameter list for your hardware control
3. **Implement your logic** - Replace random data generation with your algorithms
4. **Test incrementally** - Make small changes and test frequently

|

Related Examples
=================

After understanding this complete example, explore specific topics:

* :ref:`LED control <webApp_example_LED>` - Simple parameter handling
* :ref:`Analog voltage reading <webApp_example_SlowVoltage>` - Working with signals
* :ref:`Voltage generation <webApp_example_GenVolt>` - Controlling analog outputs
* :ref:`Nginx requests <webApp_example_Nginx>` - Advanced server-side operations

|

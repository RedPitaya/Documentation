.. _webApp_example_SlowVoltage:

##############################################
Reading Analog Voltage from Slow Analog Inputs
##############################################

This example demonstrates how to read voltage from Red Pitaya's slow analog input pins and display the values 
in a web interface. You'll learn how to work with signals, trigger on-demand measurements, and handle data 
compression in WebSocket communication.

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

Overview
=========

This application reads voltage from one of the slow analog input (AI) pins on the :ref:`E2 extension connector <E2_orig_gen>` 
and displays it in the web interface.

**Key concepts:**

* Reading analog input pins using Red Pitaya API
* Working with signals to transmit measurement data
* Handling compressed data transmission
* Triggering measurements from the UI

**Hardware:**

Any of the four slow analog input pins (AI0-AI3) on the E2 connector can be used for voltage measurement.

|

Prerequisites
==============

Required libraries
-------------------

This example requires the **pako.js** library for decompressing data transmitted over WebSocket.

|

Implementing the Frontend
===========================

Include required libraries
---------------------------

Add the following scripts to your ``index.html``:

.. code-block:: html

    <script src="js/jquery-2.1.3.min.js"></script>
    <script src="js/pako.js"></script>
    <script src="js/app.js"></script>

|

HTML structure
---------------

Add a display area for the voltage reading:

.. code-block:: html

    <div id='value'></div>

Add a button to trigger voltage reading:

.. code-block:: html

    <button id='read_button'>Read</button>

|

JavaScript implementation
--------------------------

Handling incoming data
^^^^^^^^^^^^^^^^^^^^^^^

Modify the **APP.ws.onmessage()** callback in ``app.js`` to handle compressed signal data:

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

**Data flow:**

1. Receive compressed binary data from WebSocket
2. Decompress using pako.inflate()
3. Convert to string and parse JSON
4. Extract and process signals


Processing signals
^^^^^^^^^^^^^^^^^^^

Implement the **APP.processSignals()** function to extract and display voltage values:

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


Triggering measurements
^^^^^^^^^^^^^^^^^^^^^^^^^

Implement **APP.readValue()** to request a voltage reading from the backend:

.. code-block:: javascript

    APP.readValue = function() {
        var local = {};
        local['READ_VALUE'] = { value: true };
        APP.ws.send(JSON.stringify({ parameters: local }));
    };

Connect this function to the button click event:

.. code-block:: javascript

    $('#read_button').click(function() {
        APP.readValue();
    });

|

Implementing the Backend
==========================

Signal declaration
-------------------

In ``main.cpp``, declare a global signal to transmit voltage data:

.. code-block:: c

    CFloatSignal VOLTAGE("VOLTAGE", SIGNAL_SIZE_DEFAULT, 0.0f);

**Signal parameters:**

* **"VOLTAGE"** - Signal name (must match frontend)
* **SIGNAL_SIZE_DEFAULT** - Number of data points (set to 1 for single readings)
* **0.0f** - Default value for each measurement

.. note::

    **SIGNAL_SIZE_DEFAULT** determines how many measurements are transmitted. For this example, set it to 1 
    since we only need the current reading.

|

Parameter declaration
----------------------

Declare a parameter to trigger voltage reading:

.. code-block:: c

    CBooleanParameter READ_VALUE("READ_VALUE", CBaseParameter::RW, false, 0);

**Parameter properties:**

* **"READ_VALUE"** - Parameter name (must match frontend)
* **CBaseParameter::RW** - Read/Write access
* **false** - Default value (not triggered)
* **0** - No special flags

This parameter acts as a trigger - when set to true by the frontend, the backend reads the voltage.

|

Reading analog input
---------------------

Update the parameter in **OnNewParams()** and read voltage when triggered:

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

**Process flow:**

1. **Update parameter** - Get the latest READ_VALUE from Nginx
2. **Check trigger** - See if reading was requested (value == true)
3. **Read voltage** - Use rp_AIpinGetValue() to read from AI pin 0
4. **Store in signal** - Write value to VOLTAGE signal array
5. **Reset trigger** - Set READ_VALUE back to false for next request

|

Red Pitaya API functions
--------------------------

**rp_AIpinGetValue()**

Reads voltage from a slow analog input pin.

**Syntax:**

.. code-block:: c

    int rp_AIpinGetValue(int pin, float *value);

**Arguments:**

* **int pin** - Pin number (0-3 for AI0-AI3)
* **float \*value** - Pointer to store the voltage value

**Returns:**

* **RP_OK** on success
* Error code on failure

**Voltage range:**

* Typically 0 V to 3.3 V range
* Exact range may vary by Red Pitaya model

|

Understanding the Data Flow
=============================

Request-response cycle
-----------------------

1. **User clicks "Read" button** → Frontend triggers reading
2. **Frontend sends READ_VALUE parameter** → Set to true via WebSocket
3. **Backend receives parameter** → OnNewParams() is called by Nginx
4. **Backend reads analog pin** → Gets voltage value using rp_AIpinGetValue()
5. **Backend stores in signal** → VOLTAGE signal updated with new value
6. **Signal transmitted to frontend** → Compressed and sent via WebSocket
7. **Frontend decompresses data** → Uses pako.js to decompress
8. **Frontend processes signal** → Extracts voltage value
9. **Frontend displays value** → Updates HTML element with formatted voltage


Why compression?
-----------------

WebSocket data is compressed to:

* **Reduce bandwidth usage** - Compressed data uses less network resources
* **Improve transmission speed** - Smaller packets transmit faster
* **Allow larger data arrays** - Can send more data points efficiently

This is especially important for signals with many data points (like in the graph example).

|

Testing the Application
========================

Hardware setup
---------------

1. Connect a voltage source (0-3.3 V) to one of the analog input pins on the E2 connector
2. Use AI0 (pin 0) or modify the code to use AI1-AI3
3. Ensure proper grounding between voltage source and Red Pitaya

**Voltage source options:**

* Laboratory power supply (set to 0-3.3 V)
* Potentiometer between 3.3 V and GND
* Another Red Pitaya output pin
* Battery with voltage divider

|

Application testing
--------------------

1. **Compile and deploy** your application to Red Pitaya
2. **Open the web interface** in your browser
3. **Click the "Read" button**
4. **Verify the voltage** value appears on screen
5. **Change input voltage** and click "Read" again to verify updates
6. **Test edge cases:**
   
   * 0 V input (connect to GND)
   * 3.3 V input (connect to 3.3 V supply)
   * Mid-range voltages

|

Troubleshooting
----------------

**No voltage displayed:**

* Check WebSocket connection is established
* Verify pako.js library is loaded
* Check browser console for JavaScript errors
* Ensure READ_VALUE parameter is being sent

**Incorrect voltage readings:**

* Verify input voltage with multimeter
* Check pin number in code matches physical connection
* Ensure proper grounding
* Check for loose connections

**Button not responding:**

* Verify button click handler is attached
* Check JavaScript console for errors
* Ensure WebSocket is open before clicking

|

Extending This Example
=======================

Possible enhancements
----------------------

* **Continuous reading** - Modify to read automatically at intervals instead of on-demand
* **Multiple channels** - Read from all four AI pins simultaneously and display all values
* **Graph visualization** - Plot voltage over time (see :ref:`voltage with graph example <webApp_example_ReadSlowAnalogVoltage_Graph>`)
* **Min/max tracking** - Display voltage range over time
* **Alert thresholds** - Trigger warnings for out-of-range voltages
* **Data logging** - Save voltage readings to file with timestamps
* **Calibration** - Add offset and gain correction for improved accuracy

|

Next Steps
===========

Build upon this example with these tutorials:

* :ref:`Reading voltage with graph <webApp_example_SlowVoltage_Graph>` - Add real-time graphing
* :ref:`Voltage with gain and offset <webApp_example_SlowVoltage_Graph_Offset>` - Add signal conditioning
* :ref:`Generating voltage <webApp_example_genVolt>` - Learn about analog outputs

|

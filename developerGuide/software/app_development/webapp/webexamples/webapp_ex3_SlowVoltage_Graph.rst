.. _webApp_example_SlowVoltage_Graph:

###################################################
Reading Analog Voltage from Slow Inputs with Graph
###################################################

This example extends the basic voltage reading example by adding real-time graphing capabilities. You'll learn 
how to continuously sample analog inputs, buffer data efficiently, and visualize voltage measurements over time.

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

Overview
=========

This application continuously reads voltage from one of Red Pitaya's slow analog input pins and plots the 
measurements on a real-time graph.

**Key concepts:**

* Continuous signal acquisition at defined intervals
* Data buffering and management
* Real-time graph visualization using jquery.flot.js
* Signal stacking for efficient data processing

**Hardware:**

Any of the four slow analog input pins (AI0-AI3) on the :ref:`E2 extension connector <E2_orig_gen>` can be 
used for voltage measurement.

|

Prerequisites
==============

Foundation example
-------------------

This example builds upon :ref:`Reading analog voltage from slow inputs <webApp_example_ReadSlowAnalogVoltage>`. 
Make sure you understand that example before proceeding.

Required libraries
-------------------

* **jquery.flot.js** - For drawing graphs
* **pako.js** - For data decompression
* **jquery** - For DOM manipulation

|

Implementing the Frontend
===========================

Include required libraries
---------------------------

Add the following scripts to your ``index.html``:

.. code-block:: html

    <script src="js/jquery-2.1.3.min.js"></script>
    <script src="js/jquery.flot.js"></script>
    <script src="js/pako.js"></script>
    <script src="js/app.js"></script>


HTML structure
---------------

Add a graph placeholder to display the voltage plot:

.. code-block:: html

    <div id='placeholder'></div>

You can also keep the numeric display from the basic example:

.. code-block:: html

    <div id='value'></div>


JavaScript implementation
--------------------------

Data buffering with signal stack
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Modify the **APP.ws.onmessage()** callback to buffer incoming data. Data arrives faster than we can process 
it, so we need to stack it first and then process it periodically.

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

**Why use a signal stack?**

* Data arrives continuously from the backend
* Processing and rendering graphs takes time
* Stack prevents data loss during processing
* Allows batch processing at controlled intervals


Signal processing and graph update
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The **APP.processSignals()** function is called every 15ms by **APP.signalHandler()** to process stacked data 
and update the graph:

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

**Process flow:**

1. Iterate through all signals in the data
2. Convert signal values to point arrays [index, value]
3. Update the numeric voltage display with the latest value
4. Update the Flot graph with new data points
5. Redraw the graph to show changes

|

Implementing the Backend
==========================

Signal declaration
-------------------

In ``main.cpp``, declare a global signal with a larger buffer to transmit continuous data:

.. code-block:: c

    CFloatSignal VOLTAGE("VOLTAGE", SIGNAL_SIZE_DEFAULT, 0.0f);

**Key difference from basic example:**

* **SIGNAL_SIZE_DEFAULT** should now be set to **1024**
* This means 1024 data points will be transmitted to the web UI
* Creates a scrolling window of voltage measurements


Setting signal update interval
--------------------------------

In **rp_app_init()**, configure how often the backend sends data:

.. code-block:: c

    CDataManager::GetInstance()->SetSignalInterval(SIGNAL_UPDATE_INTERVAL);

**SIGNAL_UPDATE_INTERVAL** is a constant (typically 10ms) that determines how often **UpdateSignals()** is called.


Continuous signal updates
---------------------------

Implement the **UpdateSignals()** function to continuously read and buffer voltage data:

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

**Data flow:**

1. Read current voltage from AI pin 0
2. Remove the oldest value from the data vector (creates sliding window)
3. Append the new value to the end of the vector
4. Copy entire buffer to the VOLTAGE signal
5. Signal is automatically transmitted to frontend


Data buffer management
-----------------------

Declare a global data vector to buffer measurements:

.. code-block:: c

    std::vector<float> g_data;

Initialize the buffer in **rp_app_init()**:

.. code-block:: c

    // Initialize buffer with zeros
    g_data.resize(SIGNAL_SIZE_DEFAULT, 0.0f);

This creates a sliding window buffer:

* Always contains the most recent 1024 measurements
* Oldest measurement is removed when new one arrives
* Maintains constant buffer size

|

Understanding the Data Flow
=============================

Complete signal acquisition cycle
-----------------------------------

1. **Backend timer fires** (every SIGNAL_UPDATE_INTERVAL ms)
2. **UpdateSignals() is called** → Reads AI pin
3. **Data buffer updated** → Old value removed, new value added
4. **Signal transmitted** → Entire buffer sent to frontend
5. **Frontend receives data** → Compressed via WebSocket
6. **Data stacked** → Pushed to signalStack array
7. **Signal handler fires** (every 15ms)
8. **Process signals** → Extract values, build point arrays
9. **Graph updated** → Flot redraws with new data

Continuous vs on-demand
-------------------------

**Basic example (on-demand):**

* User clicks button → Backend reads once → Single value transmitted

**Graph example (continuous):**

* Backend reads automatically at intervals
* Multiple values transmitted continuously
* Frontend displays scrolling graph

|

Graph Visualization
====================

Flot graph initialization
--------------------------

Initialize the Flot plot in your **APP.init()** or similar function:

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

Signal handler setup
---------------------

Set up periodic signal processing:

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

Testing the Application
========================

Hardware setup
---------------

1. Connect a voltage source (0-3.3 V) to one of the analog input pins (e.g., AI0)
2. For dynamic testing, use a signal generator or potentiometer
3. Ensure proper grounding

Application testing
--------------------

1. Compile and start your application
2. Open the web interface
3. **Verify continuous updates:**
   
   * Graph should show a scrolling waveform
   * Numeric value should update continuously
   
4. **Test with varying voltage:**
   
   * Adjust your voltage source
   * Observe graph response in real-time
   * Verify displayed voltage matches input

5. **Test graph performance:**
   
   * Check for smooth updates (no stuttering)
   * Verify data is not being dropped
   * Monitor CPU usage

|

Performance Considerations
===========================

Update interval tuning
-----------------------

**SIGNAL_UPDATE_INTERVAL (backend):**

* Too fast: High CPU usage, unnecessary data transmission
* Too slow: Poor time resolution, choppy graphs
* Recommended: 10-50 ms depending on application

**Signal handler interval (frontend):**

* Too fast: High browser CPU usage, rendering overhead
* Too slow: Display lag, stack overflow if data arrives faster than processed
* Recommended: 15-30 ms

Buffer size optimization
-------------------------

**SIGNAL_SIZE_DEFAULT:**

* Larger buffer: More history, smoother visualization, higher memory/bandwidth
* Smaller buffer: Less history, lower overhead, faster updates
* Recommended: 512-2048 points depending on requirements


Extending This Example
=======================

Possible enhancements
----------------------

* **Multiple channels** - Plot multiple AI pins on the same or separate graphs
* **Zoom and pan** - Add Flot zoom/pan plugins for detailed analysis
* **Data export** - Save captured data to CSV or JSON files
* **Trigger mode** - Start/stop acquisition based on voltage thresholds
* **Statistics** - Display min/max/average values
* **Frequency analysis** - Add FFT to show frequency components
* **Adjustable time scale** - Change the time window dynamically
* **Auto-scaling** - Automatically adjust Y-axis range based on signal amplitude

|

Next Steps
===========

Build upon this example with these tutorials:

* :ref:`Voltage with gain and offset <webApp_example_SlowVoltage_Graph_Offset>` - Add signal conditioning controls
* :ref:`Generating voltage <webApp_example_genVolt>` - Generate signals to test with
* Advanced graphing examples - Multiple plots, cursors, measurements

.. _webApp_example_SlowVoltage_Graph_Offset:

#####################################################################
Reading Analog Voltage from Slow Inputs with Graph, Gain, and Offset
#####################################################################

This example extends the voltage graphing application by adding signal conditioning controls. You'll learn how 
to apply gain and offset adjustments to analog measurements, allowing you to scale and shift signals for better 
visualization and analysis.

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

Overview
=========

This application adds gain and offset controls to the voltage graphing example, demonstrating how UI parameters 
can be applied to signal processing in the backend.

**Key concepts:**

* Signal conditioning with gain and offset
* Real-time parameter updates affecting signal processing
* Scaling signals for improved visualization
* Backend signal manipulation before transmission

**Hardware:**

Any of the four slow analog input pins (AI0-AI3) on the :ref:`E2 extension connector <E2_orig_gen>` can be 
used for voltage measurement.

|

Prerequisites
==============

Foundation example
-------------------

This example builds upon :ref:`Reading analog voltage from slow inputs with graph <webApp_example_ReadSlowAnalogVoltage_Graph>`. 
Make sure you understand that example before proceeding.

Understanding gain and offset
-------------------------------

**Gain:**

* Multiplies the signal amplitude
* Useful for amplifying small signals
* Formula: ``Output = Input × Gain``
* Range: 1 to 100 (1x to 100x amplification)

**Offset:**

* Adds a constant voltage to the signal
* Shifts the signal up or down
* Formula: ``Output = Input + Offset``
* Range: 0V to 5V

**Combined formula:**

.. code-block:: none

    Output = (Input × Gain) + Offset

|

Implementing the Frontend
===========================

HTML structure
---------------

Add gain and offset control blocks to ``index.html``:

**Gain control:**

.. code-block:: html

    <div id='gain_setup'>
        <div>Gain: </div>
        <input id='gain_set' type="range" size="2" value="1" min="1" max="100">
    </div>

* Range: 1 to 100 (1x to 100x amplification)
* Default: 1 (no amplification)
* Integer values

**Offset control:**

.. code-block:: html

    <div id='offset_setup'>
        <div>Offset: </div>
        <input id='offset_set' type="range" size="2" value="0" min="0" max="5" step="0.1">
    </div>

* Range: 0V to 5V
* Default: 0V (no offset)
* Step: 0.1V precision

|

JavaScript implementation
--------------------------

Setting gain
^^^^^^^^^^^^^

Add the **APP.setGain()** function to ``app.js``:

.. code-block:: javascript

    APP.setGain = function() {
        APP.gain = $('#gain_set').val();
        var local = {};
        local['GAIN'] = { value: APP.gain };
        APP.ws.send(JSON.stringify({ parameters: local }));
        $('#gain_value').text(APP.gain);
    };

Connect to the gain slider:

.. code-block:: javascript

    $('#gain_set').on('input', function() {
        APP.setGain();
    });

Setting offset
^^^^^^^^^^^^^^^

Add the **APP.setOffset()** function to ``app.js``:

.. code-block:: javascript

    APP.setOffset = function() {
        APP.offset = $('#offset_set').val();
        var local = {};
        local['OFFSET'] = { value: APP.offset };
        APP.ws.send(JSON.stringify({ parameters: local }));
        $('#offset_value').text(APP.offset);
    };

Connect to the offset slider:

.. code-block:: javascript

    $('#offset_set').on('input', function() {
        APP.setOffset();
    });

|

Implementing the Backend
==========================

Parameter declarations
-----------------------

In ``main.cpp``, add two new parameters for gain and offset:

**Gain parameter:**

.. code-block:: c

    CIntParameter GAIN("GAIN", CBaseParameter::RW, 1, 0, 1, 100);

* Parameter name: "GAIN"
* Access: Read/Write
* Default value: 1 (no amplification)
* Minimum: 1 (1x)
* Maximum: 100 (100x amplification)

**Offset parameter:**

.. code-block:: c

    CFloatParameter OFFSET("OFFSET", CBaseParameter::RW, 0.0, 0, 0.0, 5.0);

* Parameter name: "OFFSET"
* Access: Read/Write
* Default value: 0.0V (no offset)
* Minimum: 0.0V
* Maximum: 5.0V

|

Parameter updates
------------------

Update parameters in **OnNewParams()** function:

.. code-block:: c

    void OnNewParams(void) {
        GAIN.Update();
        OFFSET.Update();
    }

|

Applying signal conditioning
------------------------------

Modify the **UpdateSignals()** function to apply gain and offset when writing to the signal:

.. code-block:: c

    void UpdateSignals(void) {
        float val;
        
        // Read voltage from analog input pin 0
        rp_AIpinGetValue(0, &val);
        
        // Remove oldest measurement from buffer
        g_data.erase(g_data.begin());
        
        // Add new measurement to end of buffer
        g_data.push_back(val);
        
        // Write entire buffer to signal with gain and offset applied
        for(int i = 0; i < SIGNAL_SIZE_DEFAULT; i++) 
        {
            VOLTAGE[i] = (g_data[i] * GAIN.Value()) + OFFSET.Value();
        }
    }

**Key changes from the basic graph example:**

* Raw data is stored in ``g_data`` without modification
* Gain and offset are applied only when writing to the VOLTAGE signal
* This allows changing gain/offset without losing raw data

|

Understanding Signal Conditioning
===================================

Why use gain?
--------------

**Problem scenario:**

Small voltage signals (e.g., 0-0.1 V) are difficult to see on a graph scaled to 0-3.3 V.

**Solution:**

Apply gain to amplify the signal for better visualization:

* With 10x gain: 0-0.1 V becomes 0-1.0 V on the display
* With 100x gain: 0-0.1 V becomes 0-10 V on the display (clipped at graph limits)

**Example:**

.. code-block:: none

    Raw signal: 0.05 V
    With gain = 10: 0.05 V × 10 = 0.5 V (displayed)
    With gain = 50: 0.05 V × 50 = 2.5 V (displayed)

|

Why use offset?
----------------

**Problem scenario:**

A signal varies between 1.5 V and 1.6 V. On a 0-3.3 V scale, the variation is barely visible.

**Solution:**

Apply offset to shift the signal baseline:

* Subtract 1.5 V offset: Signal now appears to vary from 0 V to 0.1 V
* Combined with 10x gain: Signal varies from 0 V to 1.0 V (clear visualization)

.. note::
    
    In this example, offset is added (positive), not subtracted. To center a signal around 0 V, you would
    need negative offset capability.

|

Combined gain and offset
--------------------------

**Application order matters:**

This example applies: ``Output = (Input × Gain) + Offset``

**Example:**

.. code-block:: none

    Raw signal: 0.5 V
    Gain: 2x
    Offset: +0.5 V
    
    Result: (0.5 V × 2) + 0.5 V = 1.5 V

|

Data Flow with Signal Conditioning
====================================

Signal processing pipeline
---------------------------

1. **Read AI pin** → Raw voltage value (e.g., 0.123 V)
2. **Store in buffer** → Raw value saved to g_data vector
3. **Apply gain** → Multiply by GAIN parameter (e.g., × 10 = 1.23 V)
4. **Apply offset** → Add OFFSET parameter (e.g., + 0.5 V = 1.73 V)
5. **Write to signal** → Conditioned value stored in VOLTAGE array
6. **Transmit** → Signal sent to frontend
7. **Display** → Graph shows conditioned voltage (1.73V)

|

Preserving raw data
--------------------

**Important design choice:**

Raw data is stored in ``g_data`` without gain/offset applied. This allows:

* Changing gain/offset without losing information
* Re-processing historical data with new parameters
* Accurate raw data logging if needed

|

Testing the Application
========================

Hardware setup
---------------

1. Connect a voltage source to one of the analog input pins (e.g., AI0)
2. Use a source with small variations for best demonstration of gain/offset effects
3. Recommended: potentiometer or low-amplitude signal generator

|

Application testing
--------------------

**Test gain functionality:**

1. Connect a low voltage signal (e.g., 0.1 V)
2. Observe it may be hard to see on the graph
3. Increase gain to 10x
4. Verify signal is now clearly visible (displayed as 1.0 V)
5. Continue increasing gain and observe amplification

**Test offset functionality:**

1. Connect a stable voltage (e.g., 1.5 V)
2. Note the baseline position on the graph
3. Add offset of +1.0 V
4. Verify the displayed signal shifts up by 1.0 V (shows as 2.5 V)

**Test combined effects:**

1. Start with a small AC signal (e.g., 0.05 V peak-to-peak at 1.5 V DC)
2. Apply gain = 20 to amplify the AC component
3. Apply offset to shift the entire signal
4. Observe both amplification and shifting effects

**Monitor for clipping:**

* With high gain, signals may exceed display range
* Values above 3.3 V (or graph Y-axis max) will be clipped
* Reduce gain or adjust offset if clipping occurs

|

Practical Use Cases
=====================

Amplifying sensor signals
---------------------------

**Scenario:** Temperature sensor outputs 0-100mV for 0-100°C

**Solution:**

* Apply gain = 33 to scale 0-100 mV to 0-3.3 V
* Full sensor range now uses full display range
* Improved visualization and resolution

|

Centering AC signals
---------------------

**Scenario:** AC signal varies ±0.1 V around 1.65 V DC

**Challenge:** This example only supports positive offset

**Workaround:**

* Use gain to amplify AC component
* Offset limited to positive values only
* For true centering, negative offset would be needed (feature enhancement)

|

Dynamic range adjustment
-------------------------

**Scenario:** Signal amplitude varies over time

**Solution:**

* Increase gain when signal is small
* Decrease gain when signal is large
* Manually adjust or implement auto-ranging

|

Extending This Example
=======================

Possible enhancements
----------------------

* **Negative offset** - Support offset range from -5 V to +5 V for centering signals
* **Auto-scaling** - Automatically adjust gain to fit signal in display range
* **Offset calibration** - Add "zero" button to set current value as baseline
* **Gain presets** - Quick buttons for common gain values (1x, 10x, 100x)
* **Display units** - Convert to engineering units (mV, μV) based on gain
* **Raw data view** - Toggle between raw and conditioned signal display
* **Multiple channels** - Independent gain/offset per channel
* **Filtering** - Add low-pass, high-pass, or band-pass filters

|

Next Steps
===========

Build upon this example with these tutorials:

* :ref:`Generating voltage <webApp_example_genVolt>` - Create test signals with known amplitudes
* Advanced signal processing - FFT, filtering, statistics
* Data acquisition examples - Triggered capture with signal conditioning

|

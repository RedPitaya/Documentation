.. _webApp_example_genVolt:

###################
Generating Voltage
###################

This example demonstrates how to generate analog voltage signals using Red Pitaya's fast analog outputs. 
You'll learn how to control signal frequency, amplitude, and waveform from a web interface and apply 
the generated signal to slow analog inputs for measurement verification.

Overview
=========

This application generates a configurable voltage signal on Red Pitaya's output channel and allows you to 
adjust its characteristics in real-time through the web interface.

**Key concepts:**

* Generating analog signals using Red Pitaya API
* Controlling signal parameters (frequency, amplitude, waveform)
* Working with the signal generator API
* Setting DC offset for signal conditioning

**Hardware:**

* Output channel 1 (OUT1) generates the signal
* Can be connected to slow analog input (AI0-AI3) for verification


Prerequisites
==============

Foundation example
-------------------

This example builds upon :ref:`Reading analog voltage from slow inputs <webApp_example_ReadSlowAnalogVoltage>`. 
Use that example as the base application, as it provides the simplest way to verify the generated voltage using 
one device.

Signal range considerations
----------------------------

**Generator specifications:**

* Red Pitaya generator range: -1 V to +1 V
* Slow analog input range: 0 V to 3.3 V

**To make signals compatible:**

* Set DC offset to +0.5 V
* Limit maximum amplitude to 0.5 V
* Resulting signal range: 0 V to 1 V (compatible with slow analog inputs)

**Range calculation:**

With 0.5 V amplitude: (-0.5 V to +0.5 V) + 0.5 V offset = 0 V to 1 V output



Implementing the Frontend
===========================

HTML structure
---------------

Add three control blocks to ``index.html`` for frequency, amplitude, and waveform:

**Frequency control:**

.. code-block:: html

    <div id='frequency_setup'>
        <div>Frequency: Hz</div>
        <input id='frequency_set' type="range" size="2" value="1" min="1" max="20">
    </div>

* Range: 1 Hz to 20 Hz
* Default: 1 Hz

**Amplitude control:**

.. code-block:: html

    <div id='amplitude_setup'>
        <div>Amplitude: V</div>
        <input id='amplitude_set' type="range" step="0.01" size="2" value="0.5" min="0" max="0.5">
    </div>

* Range: 0 V to 0.5 V
* Default: 0.5 V
* Step: 0.01 V (10 mV precision)

**Waveform selection:**

.. code-block:: html

    <div id='waveform_setup'>
        <div>Waveform</div>
        <select size="1" id="waveform_set">
            <option selected value="0">Sine</option>
            <option value="1">Sawtooth</option>
            <option value="2">Square</option>
        </select>
    </div>


JavaScript implementation
--------------------------

Add three new functions to ``app.js`` to handle parameter changes:

Setting frequency
^^^^^^^^^^^^^^^^^^

.. code-block:: javascript

    APP.setFrequency = function() {
        APP.frequency = $('#frequency_set').val();
        var local = {};
        local['FREQUENCY'] = { value: APP.frequency };
        APP.ws.send(JSON.stringify({ parameters: local }));
        $('#frequency_value').text(APP.frequency);
    };

This function:

1. Reads the frequency value from the slider
2. Creates a parameter object with the new frequency
3. Sends it to the backend via WebSocket
4. Updates the display to show the current frequency

Setting amplitude
^^^^^^^^^^^^^^^^^^

.. code-block:: javascript

    APP.setAmplitude = function() {
        APP.amplitude = $('#amplitude_set').val();
        var local = {};
        local['AMPLITUDE'] = { value: APP.amplitude };
        APP.ws.send(JSON.stringify({ parameters: local }));
        $('#amplitude_value').text(APP.amplitude);
    };

Setting waveform
^^^^^^^^^^^^^^^^^

.. code-block:: javascript

    APP.setWaveform = function() {
        APP.waveform = $('#waveform_set').val();
        console.log('Set to ' + APP.waveform);
        var local = {};
        local['WAVEFORM'] = { value: APP.waveform };
        APP.ws.send(JSON.stringify({ parameters: local }));
    };



Implementing the Backend
==========================

Parameter declarations
-----------------------

In ``main.cpp``, declare three parameters to control the generator:

**Frequency parameter:**

.. code-block:: c

    CIntParameter FREQUENCY("FREQUENCY", CBaseParameter::RW, 1, 0, 1, 20);

* Parameter name: "FREQUENCY"
* Access: Read/Write
* Default value: 1 Hz
* Minimum: 1 Hz
* Maximum: 20 Hz

**Amplitude parameter:**

.. code-block:: c

    CFloatParameter AMPLITUDE("AMPLITUDE", CBaseParameter::RW, 0.5, 0, 0, 0.5);

* Parameter name: "AMPLITUDE"
* Access: Read/Write
* Default value: 0.5 V
* Minimum: 0 V
* Maximum: 0.5 V (limited to ensure 0-1V output with offset)

**Waveform parameter:**

.. code-block:: c

    CIntParameter WAVEFORM("WAVEFORM", CBaseParameter::RW, 0, 0, 0, 2);

* Parameter name: "WAVEFORM"
* Access: Read/Write
* Default value: 0 (Sine)
* Minimum: 0
* Maximum: 2

**Waveform values:**

===== =============
Value Description
===== =============
0     Sine
1     Sawtooth
2     Square
===== =============


Generator configuration function
---------------------------------

Create a **set_generator_config()** function to configure the output signal.

Setting frequency
^^^^^^^^^^^^^^^^^^

.. code-block:: c

    rp_GenFreq(RP_CH_1, FREQUENCY.Value());

Sets the signal frequency on output channel 1 (RP_CH_1).

Setting DC offset
^^^^^^^^^^^^^^^^^^

.. code-block:: c

    rp_GenOffset(RP_CH_1, 0.5);

A +0.5 V offset is crucial to shift the signal into the positive voltage range (0 V to 1 V), making it compatible 
with analog inputs that cannot read negative voltages.

Setting amplitude
^^^^^^^^^^^^^^^^^^

.. code-block:: c

    rp_GenAmp(RP_CH_1, AMPLITUDE.Value());

Sets the peak-to-peak amplitude of the signal.

Setting waveform
^^^^^^^^^^^^^^^^^

.. code-block:: c

    if (WAVEFORM.Value() == 0)
    {
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
    }
    else if (WAVEFORM.Value() == 1)
    {
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_RAMP_UP);
    }
    else if (WAVEFORM.Value() == 2)
    {
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SQUARE);
    }

**Available waveform types:**

* **RP_WAVEFORM_SINE** - Sine wave
* **RP_WAVEFORM_SQUARE** - Square wave
* **RP_WAVEFORM_TRIANGLE** - Triangle wave
* **RP_WAVEFORM_RAMP_UP** - Sawtooth (rising ramp)
* **RP_WAVEFORM_RAMP_DOWN** - Reversed sawtooth (falling ramp)
* **RP_WAVEFORM_DC** - DC signal
* **RP_WAVEFORM_PWM** - PWM signal
* **RP_WAVEFORM_ARBITRARY** - User-defined waveform


Application lifecycle
----------------------

Initialize generator in **rp_app_init()**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c

    set_generator_config();
    rp_GenOutEnable(RP_CH_1);
    rp_GenResetTrigger(RP_CH_1);

**Steps:**

1. Configure generator with default settings
2. Enable the output channel
3. Reset the trigger to start generation

Disable generator in **rp_app_exit()**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c

    rp_GenOutDisable(RP_CH_1);

Always disable the generator when the application exits to prevent continuous signal generation.

Update parameters in **OnNewParams()**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c

    FREQUENCY.Update();
    AMPLITUDE.Update();
    WAVEFORM.Update();

When any parameter changes from the frontend, update it in the backend and reconfigure the generator by calling 
**set_generator_config()**.


Red Pitaya Generator API
==========================

Key API functions
------------------

**rp_GenFreq()**

Sets the signal frequency.

**Syntax:**

.. code-block:: c

    int rp_GenFreq(rp_channel_t channel, float frequency);

**Arguments:**

* **channel** - Output channel (RP_CH_1 or RP_CH_2)
* **frequency** - Frequency in Hz

**rp_GenAmp()**

Sets the signal amplitude (peak-to-peak).

**Syntax:**

.. code-block:: c

    int rp_GenAmp(rp_channel_t channel, float amplitude);

**Arguments:**

* **channel** - Output channel
* **amplitude** - Amplitude in volts

**rp_GenOffset()**

Sets the DC offset voltage.

**Syntax:**

.. code-block:: c

    int rp_GenOffset(rp_channel_t channel, float offset);

**Arguments:**

* **channel** - Output channel
* **offset** - Offset in volts

**rp_GenWaveform()**

Sets the waveform type.

**Syntax:**

.. code-block:: c

    int rp_GenWaveform(rp_channel_t channel, rp_waveform_t waveform);

**Arguments:**

* **channel** - Output channel
* **waveform** - Waveform type constant

**rp_GenOutEnable() / rp_GenOutDisable()**

Enables or disables the signal output.

**Syntax:**

.. code-block:: c

    int rp_GenOutEnable(rp_channel_t channel);
    int rp_GenOutDisable(rp_channel_t channel);

**Arguments:**

* **channel** - Output channel

**rp_GenResetTrigger()**

Resets the trigger and starts signal generation.

**Syntax:**

.. code-block:: c

    int rp_GenResetTrigger(rp_channel_t channel);

**Arguments:**

* **channel** - Output channel


Testing the Application
========================

Hardware setup
---------------

**Option 1: Loopback verification (recommended for this example)**

1. Connect OUT1 to AI0 using a jumper wire
2. This allows you to verify the generated signal by reading it with the analog input from the base example
3. The voltage reading will update as you change generator parameters

**Option 2: Oscilloscope verification**

1. Connect OUT1 to an oscilloscope probe
2. Observe the signal characteristics directly
3. Verify frequency, amplitude, and waveform visually

Application testing
--------------------

1. Compile and start your application
2. **Test frequency:**
   
   * Move the frequency slider from 1 Hz to 20 Hz
   * Observe voltage reading changing at different rates (if using loopback)
   * Verify frequency on oscilloscope

3. **Test amplitude:**
   
   * Move the amplitude slider from 0 V to 0.5 V
   * Observe voltage reading range changes (if using loopback)
   * Verify amplitude on oscilloscope

4. **Test waveform:**
   
   * Select different waveforms (Sine, Sawtooth, Square)
   * Observe different voltage patterns (if using loopback with fast enough refresh)
   * Verify waveform shape on oscilloscope


Understanding Signal Compatibility
===================================

Why limit amplitude to 0.5V?
------------------------------

The generator can produce signals from -1 V to +1 V, but the analog inputs can only read 0 V to 3.3 V.

**Without offset:**

* 0.5 V amplitude generates: -0.5 V to +0.5 V
* Problem: Analog inputs cannot read negative voltages
* Result: Signal is clipped at 0 V

**With +0.5 V offset:**

* Same 0.5 V amplitude becomes: 0 V to +1 V
* Solution: Entire signal is now in the readable range
* Result: Clean signal without clipping

**Example calculation:**

.. code-block:: none

    Generator output = (Amplitude × sin(ωt)) + Offset

    With Amplitude = 0.5 V, Offset = 0.5 V:

    Minimum: (0.5 V × -1) + 0.5 V = 0 V
    Maximum: (0.5 V × +1) + 0.5 V = 1 V

    Range: 0 V to 1 V ✓ (within AI readable range)


Extending This Example
=======================

Possible enhancements
----------------------

* **Dual channel generation** - Control both OUT1 and OUT2 independently with different signals
* **Phase control** - Add phase offset between channels for advanced signal generation
* **Arbitrary waveforms** - Define custom waveform shapes using arrays
* **Frequency sweep** - Automatically sweep through a range of frequencies
* **Burst mode** - Generate signal bursts with defined count and period
* **Higher frequency range** - Extend frequency range to kHz or MHz
* **Modulation** - Implement AM or FM modulation
* **Synchronization** - Synchronize generation with acquisition


Next Steps
===========

Build upon this example with these tutorials:

* :ref:`Reading voltage with graph <webApp_example_SlowVoltage_Graph>` - Visualize generated signals in real-time
* :ref:`Voltage with gain and offset <webApp_example_SlowVoltage_Graph_Offset>` - Apply signal conditioning to measurements
* Signal acquisition examples - Capture and analyze generated signals using the oscilloscope

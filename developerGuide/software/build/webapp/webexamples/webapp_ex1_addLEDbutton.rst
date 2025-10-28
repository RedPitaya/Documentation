.. _webApp_example_LED:

###################################
Controlling LED with Button Example
###################################

This tutorial demonstrates how to control Red Pitaya's onboard LEDs through a web interface using parameters. 
You'll learn the fundamentals of frontend-backend communication and hardware control through the Red Pitaya API.

Overview
=========

This example creates a simple web application with a button that toggles one of Red Pitaya's LEDs on and off. 
The application demonstrates:

* Creating interactive UI elements (buttons)
* Sending parameters from frontend to backend
* Controlling hardware peripherals through the Red Pitaya API
* Updating UI based on hardware state

Prerequisites
==============

FPGA configuration
-------------------

The Red Pitaya API requires the v0.94 FPGA bitstream to control LEDs. Load it before starting your application:

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: shell-session

            redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    .. group-tab:: OS version 2.00 or newer

        OS 2.00 introduced a new FPGA loading system using the **overlay.sh** script, which loads both the 
        FPGA binary and device overlays. The file format changed from |xlinx_doc|.

        .. code-block:: shell-session

            redpitaya> overlay.sh v0.94

.. |xlinx_doc| raw:: html

    <a href="https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18841847/Solution+ZynqMP+PL+Programming#SolutionZynqMPPLProgramming-BitstreamFormat" target="_blank">bit to bin</a>

.. note::

    Always load the correct FPGA image before running applications that interact with hardware.


Implementing the Frontend
===========================

HTML structure
---------------

Add these elements to your `index.html` file:

**LED control button:**

.. code-block:: html

    <button id='led_state'>Turn on</button>

**LED status indicators:**

.. code-block:: html

    <div id='led_off'>LED Off</div>
    <div id='led_on'>LED On</div>

.. note::

    The **led_on** div is hidden by default since LEDs are off when the application starts.


CSS styling
------------

Add styles to `css/style.css` for visual feedback:

.. code-block:: css

    #led_off {
        color: #F00;  /* Red text for OFF state */
    }

    #led_on {
        display: none;  /* Hidden by default */
        color: #0F0;    /* Green text for ON state */
    }

    #led_state {
        margin-top: 20px;
        padding: 10px;
    }


JavaScript logic
-----------------

In `js/app.js`, implement the button click handler and LED state management:


Initialize LED state
^^^^^^^^^^^^^^^^^^^^^

.. code-block:: javascript

    APP.led_state = false;


Button click handler
^^^^^^^^^^^^^^^^^^^^^

Add the following code to toggle the LED state and update the UI:

.. code-block:: javascript

    $('#led_state').click(function() {
        // Toggle local LED state
        if (APP.led_state == true) {
            $('#led_on').hide();
            $('#led_off').show();
            APP.led_state = false;
        }
        else {
            $('#led_off').hide();
            $('#led_on').show();
            APP.led_state = true;
        }

        // Send current LED state to backend
        var local = {};
        local['LED_STATE'] = { value: APP.led_state };
        APP.ws.send(JSON.stringify({ parameters: local }));
    });

.. important::

    The parameter name **LED_STATE** must match exactly between frontend and backend. Consistency in naming 
    is critical for proper communication.


Implementing the Backend
==========================

Controller location
--------------------

The backend controller code is located in:

.. code-block:: text

    src/main.cpp


Parameter declaration
----------------------

Declare a global parameter to receive the LED state from the frontend:

.. code-block:: c

    CBooleanParameter ledState("LED_STATE", CBaseParameter::RW, false, 0);

**Parameter structure:**

* **"LED_STATE"** - Parameter name (must match frontend)
* **CBaseParameter::RW** - Access mode (Read/Write)
* **false** - Initial value
* **0** - FPGA update flag

.. note::

    **Parameter types:**
    
    * **CBooleanParameter** - for boolean values
    * **CIntParameter** - for integer values
    * **CFloatParameter** - for floating-point values
    
    Choose the type that matches your JavaScript variable type.


Handling parameter updates
---------------------------

Update and process the parameter in the **OnNewParams()** function, which is called whenever the frontend 
sends new parameters:

.. code-block:: c

    void OnNewParams(void) {
        // Update parameter from Nginx
        ledState.Update();
        
        // Control LED based on parameter value
        if (ledState.Value() == false) {
            rp_DpinSetState(RP_LED0, RP_LOW);
        }
        else {
            rp_DpinSetState(RP_LED0, RP_HIGH);
        }
    }

**How it works:**

1. **ledState.Update()** - Retrieves the latest value from Nginx using the parameter name
2. **ledState.Value()** - Returns the current parameter value
3. **rp_DpinSetState()** - Red Pitaya API function to set pin state


Red Pitaya API functions
--------------------------

**rp_DpinSetState()**

Sets the state of a digital pin or LED.

**Arguments:**

* **rp_dpin_t pin** - Pin identifier (LED or digital pin)
* **rp_pinState_t state** - Desired state

**Available LEDs:**

Red Pitaya has 8 controllable LEDs:

* **RP_LED0** through **RP_LED7**

**LED states:**

* **RP_HIGH** - LED on
* **RP_LOW** - LED off


Initialization and cleanup
---------------------------

Initialize the Red Pitaya API in **rp_app_init()**:

.. code-block:: c

    int rp_app_init(void) {
        if (rp_Init() != RP_OK) {
            fprintf(stderr, "Red Pitaya API init failed!\n");
            return EXIT_FAILURE;
        }
        return 0;
    }

Release resources in **rp_app_exit()**:

.. code-block:: c

    int rp_app_exit(void) {
        rp_Release();
        return 0;
    }


Building and Testing
=====================

Compile the application
-------------------------

Navigate to your application directory and compile:

.. code-block:: shell-session

    $ cd /opt/redpitaya/www/apps/myLedApp/
    $ make INSTALL_DIR=/opt/redpitaya


Test the application
---------------------

1. Open a web browser and navigate to your Red Pitaya's IP address
2. Launch your application from the application menu
3. Click the "Turn on" button
4. **RP_LED0** on the Red Pitaya board should illuminate
5. The button text and status indicator should update
6. Click again to turn the LED off


Next Steps
===========

Now that you understand parameter communication, you can extend this example:

* Control multiple LEDs simultaneously
* Add LED brightness control using PWM
* Create LED patterns or animations
* Combine LED control with other peripherals

Explore more advanced examples:

* :ref:`Reading analog voltage <webApp_example_SlowVoltage>` - Learn about signals
* :ref:`Generating voltage <webApp_example_genVolt>` - Control analog outputs

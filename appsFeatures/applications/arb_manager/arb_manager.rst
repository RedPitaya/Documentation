.. _arb_manager_app:

Arbitrary Waveform Manager
#############################

The Arbitrary Waveform Manager is an upgrade to the Signal Generator Application, which comes as a part of the :ref:`Oscilloscope and Signal Generator <osc_app>` and the :ref:`Spectrum Analyzer <spec_anal_app>` applications, bringing to life arbitrary waveform generation. This excellent utility, previously exclusive to SCPI and API commands is now available in the form of Arbitray Waveform Manager application.

Arbitrary Waveform Manager is available on all Red Pitaya boards with the exception of STEMlab 125-14 4-Input version (does not have fast analog outputs).

Features
===========

- Upload one period of a custom waveform to Red Pitaya
- Generate custom waveforms from Oscilloscope and Spectrum Analyzer applications

.. figure:: img/ARB_manager_controls.png
    :width: 1000

#. **Upload:** Button to upload a CSV file with custom waveform.
#. **Signal name and colour:** Change custom signal name and waveform colour.
#. **Delete waveform:** Delete custom waveform.


Uploading custom waveforms
============================

To upload a custom signal to Arbitrary waveform generator follow the setps below.

#. Open Arbitrary Waveform Manager

   .. figure:: img/ARB_manager.png
       :width: 1000

#. Click on the **Upload** button and upload a **CSV** file containing one period of a custom signal with 16384 samples/points.
#. Wait for the signal to appear on the screen.
#. Configure waveform name and colour. To change the name click into the name field, to change the colour click into the colour field. The color can be selected from the screen with the eyedropper tool or configured through the colour manager utility that pops up.

    .. figure:: img/ARB_manager_recolour.png
       :width: 1000 
#. Exit ARB Manager and open Oscilloscope or Spectrum Analyzer. Custom waveforms should appear in the *Waveform Type* drop-down menu. They can easily be distinguished from the standard waveforms through the custom font colours which match the waveform colours set in the ARB Manager.

    .. figure:: img/ARB_Osc_waveforms.png
        :width: 300

Example code for creating a custom waveform
--------------------------------------------

Here is an example of Python code for creating a custom waveform.

.. code-block:: python
    
    #!/usr/bin/env python3
    
    import numpy as np
    import pandas as pd
    from matplotlib import pyplot as plt
    
    N = 16384                               # Number of samples
    t = np.linspace(0, 1, N)*2*np.pi
    
    x = np.sin(t) + 1/3*np.sin(3*t)         # Custom wavefrom definition
    y = 1/2*np.sin(t) + 1/4*np.sin(4*t)
    
    plt.plot(t, x, t, y)                    # Double-check with plot
    plt.title('Custom waveform')
    plt.show()
    
    # Port waveforms to CSV fromat
    pd.DataFrame(x).to_csv('arb_waveform1.csv', index=False, header=False, float_format=np.float64)
    pd.DataFrame(y).to_csv('arb_waveform2.csv', index=False, header=False, float_format=np.float64)
  

Source code
=============

The |arb_manager_source_code| is available on our GitHub.

.. |arb_manager_source_code| raw:: html

  <a href="https://github.com/RedPitaya/RedPitaya/tree/master/apps-tools/arb_manager" target="_blank">Arbitrary Waveform Manager source code</a>






.. _calibration_app:

###########
Calibration
###########

To open the Calibration application click on **System Tools** and then select **Calibration**.

.. image:: img/Main_menu_system.jpg
    :align: center
    :scale: 40 %

.. image:: img/Calibration_app_menu.jpg
    :align: center
    :scale: 40 %


When the Calibration application opens, you will see four options:

.. image:: img/Calibration_api.png
    :align: center
    :scale: 100 %

***************
DC Calibration
***************

With the DC calibration, you can fine-tune Red Pitaya's ADCs and DACs.


Auto DC calibration
====================

.. insert Auto DC calibration

Auto DC calibration will guide you step-by-step through the calibration process and is the option we recommend for beginners.

Step-by-step guide:



Manual DC calibration
======================

Manual DC calibration will let you do the calibration manually and fine-tune all the variables.
Apart from calibration, this option will also allow you to identify any parasitics on your measurement lines.

.. image:: img/DC_manual.jpg
    :align: center
    :scale: 80 %

* **RESET**:
    * **DEFAULT** - remove the calibration parameters
    * **FACTORY** - reset the board to the factory calibration parameters
* **APPLY** the calibration - save the DC offset in the system settings
* **CLOSE** the calibration

When closing the application without saving the values the followng prompt will appear:

.. image:: img/Calib_save.png
    :align: center
    :scale: 100 %



ADC calibration parameters
---------------------------

.. image:: img/DC_manual_ADC.jpg
    :align: center
    :scale: 100 %

1. **Voltage measurements** (Mean, minimum, maximum, and peak-to-peak). Displayed in the graph with the corresponding colour.
#. **Sine wave detection**. Detects wheter a sine wave is present on the channel. The "x8" indicates how many periods were detected.
#. **ADC Offset**. Change the offset by the number in the middle. The amount can be selected from the dropdown menu.
#. **ADC Gain**. Change the gain by the number in the middle. The amount can be selected from the dropdown menu.
#. **LV/HV**. Select the calibration voltage range. Should be the same as the input jumpers.
#. **LAST/AVG**. Select either the last or average voltage measurements.
#. **Decimation**. Select the decimation from the dorpdown menu.


DAC calibration parameters
---------------------------

.. image:: img/DC_manual_DAC.jpg
    :align: center
    :scale: 100 %

1. **ON/OFF**. Turn the specified output ON or OFF.
#. **DAC settings**. Change the output waveform (type), frequency, amplitude, and offset. Currently only the waveform (type) can be changed.
#. **DAC Offset**. Change the offset by the number in the middle. The amount can be selected from the dropdown menu.
#. **DAC Gain**. Change the gain by the number in the middle. The amount can be selected from the dropdown menu.


**********************
Frequency calibration
**********************

Auto Frequency calibration
===========================

Auto Frequency calibration will guide you step-by-step through the calibration process and is the option we recommend for beginners.


Manual Frequency calibration
=============================

Manual Frequency calibration will let you do the calibration manually and fine-tune all the variables.
Apart from calibration, this option will also allow you to identify any parasitics on your measurement lines.


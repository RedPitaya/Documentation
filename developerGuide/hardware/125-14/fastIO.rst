.. _anain:

#############
Analog inputs
#############

The Red Pitaya board analog front-end features 2 fast analog inputs. 


**********************
General Specifications
**********************
    
+---------------------------------+-----------------------------------------------+
| Number of channels              | 2                                             |
+---------------------------------+-----------------------------------------------+
| Sample rate                     | 125 Msps                                      |
+---------------------------------+-----------------------------------------------+
| ADC resolution                  | 14 bits                                       |
+---------------------------------+-----------------------------------------------+
| Input coupling                  | DC                                            |
+---------------------------------+-----------------------------------------------+
| | **Absolute maximum input**    | **30 V (S) (1500 V ESD)**                     |
| | **voltage rating**            |                                               |
+---------------------------------+-----------------------------------------------+
| Overload protection             | protection diodes                             |
|                                 | (under the input voltage rating conditions)   |
+---------------------------------+-----------------------------------------------+
| Connector type                  | SMA                                           |
+---------------------------------+-----------------------------------------------+
| Input stage voltage ranges      | | LV (±1 V)                                   |
|                                 | | HV (±20 V)                                  |
+---------------------------------+-----------------------------------------------+
| Bandwidth                       | 50 MHz (3 dB)                                 |
+---------------------------------+-----------------------------------------------+
    
    .. note::
    
       The overload protection is valid for low-frequency signals. For input signals that contain frequency components beyond 1 kHz, the full-scale value defines the maximum admissible input voltage.
    

    .. note::
    
        The SMA connectors on the cables connected to Red Pitaya must correspond to the standard MIL­C­39012. The central pin must be of suitable length, otherwise, the SMA connector installed in Red Pitaya will mechanically damage the SMA connector.
        The central pin of the SMA connector on Red Pitaya will lose contact with the board and the board will not be possible to repair due to the mechanical damage (separation of the pad from the board).



.. _jumper_pos:

=======
Jumpers
=======

Voltage ranges are set by input jumpers, as shown here:

.. figure:: Jumper_settings.png 


Gain can be adjusted independently for both input channels. The adjustment is done by bridging the jumpers located behind the corresponding input SMA connector.
     
.. figure:: Jumper_settings_photo.png
            
    Jumper setting
    
    - The left setting (LV) adjusts to ± 1 V full scale.
    - The right setting (HV) adjusts to ± 20 V full scale.


.. warning::
    
    Jumper settings are limited to the described positions. Any other configuration or use of different jumper types may damage the product and void the warranty.

==================
Jumper orientation
==================

Jumper position can affect the measurements taken with Red Pitaya. The jumpers are internally connected with a small metal plate, which acts as a capacitor and has an effect on the overall capacitance, which in turn affects the input impedance. If the jumpers are moved from an incorrect to a correct position, a calibration is highly recommended.


1) The position of the jumper bumps must be as indicated in this image.

    .. figure:: Jumper_position_Note.png


2) The metallic part of the jumper should look toward the PCB so that it is not visible once the jumpers are installed. Here is an example on the STEMlab 125-14 4-Input:

    .. figure:: Jumper_position_4IN_0.png

    .. figure:: Jumper_position_4IN_1.png


Incorrect placement of the jumpers can cause overshooting or undercutting of the front part of the acquired square-type signals, as shown in the picture below.

.. figure:: Jumper_position_wrong_signal.jpg

    As it can be observed, **if the jumpers are not placed correctly, the step response becomes under-compensated.**


With the correct placement of the jumper pins, that same waveform looks much better.

.. figure:: Jumper_position_right_signal.jpg



======================
Input stage schematics
======================

.. figure:: Fast_analog_inputs_sch.png
        
    Fast analog inputs schematics

========
Coupling
========

Fast analog inputs are **DC coupled**. Input impedance is given in the picture below. 

.. figure:: Input_impedance_of_fast_analog_inputs.png
       
    The input impedance of fast analog inputs

=========
Bandwidth
=========

+---------------------------------+-----------------------------------------------+
| Bandwidth                       | 50 MHz (3 dB)                                 |
+---------------------------------+-----------------------------------------------+
    
In the picture below, the Frequency Response - Bandwidth of fast analog inputs is shown. Measurements are taken using an |Agilent 33250A| signal generator as a reference. The measured signal is acquired using :ref:`remote control (SCPI commands) <scpiCommand>`. An amplitude voltage is extracted from the acquired signal and compared to the reference signal amplitude.
        
.. figure:: Bandwidth_of_Fast_Analog_Inputs.png
        
    The bandwidth of fast analog inputs
        
Because of the maximum sampling rate of 125 MS/s when measuring signals above 10 MHz, we have used sin(x)/x interpolation to get more accurate results of Vpp voltage and, with that, more accurate measurements of analog bandwidth. When measuring signals above 10 MHz, similar results should be obtained without interpolation or directly with an Oscilloscope application and P2P measurements.
        
Notice: When making measurements without interpolation, you need to extract the maximum and minimum of the acquired signal using a complete 16k buffer. When using P2P measurements on an oscilloscope, you need to take the maximum value shown as a measurement result. An example of sin(x)/x interpolation for a 40 MHz signal is shown in the picture below (right).
        
.. note::
        
    In the picture, only 10 samples of 16k buffer are shown to represent a few periods of 40 MHz signal.
        
.. figure:: Sin(x)x_Interpolation.png   
        
    Sin(x)/x Interpolation
   
===========
Input noise
===========

Measurements refer to a high gain (LV +/-1 V) jumper setting, with limited environmental noise, inputs and outputs terminated, output signals disabled, and the PCB grounded through SMA ground. Measurements are performed on 16k continuous samples at full rate (125 MS/s). (Typical full bandwidth std(Vn) < 0.5 mV). The noise spectrum shown in the picture below (right) is calculated using FFT analysis on N = 16384 samples sampled at Fs = 125E6 MS/s.
    
.. figure:: Noise_distribution.png
        
    Noise distribution 
        
.. figure:: Noise_level.png
        
    Noise level
        
=======================
Input channel isolation
=======================
    
Typical performance:
    - 65 dB @ 10 kHz
    - 50 dB @ 100 kHz
    - 55 dB @ 1 M
    - 55 dB @ 10 MHz
    - 52 dB @ 20 MHz
    - 48 dB @ 30 MHz
    - 44 dB @ 40 MHz
    - 40 dB @ 50 MHz

Crosstalk is measured with a high gain (LV) jumper setting on both channels. The SMA connectors not involved in the measurement are terminated.
    
=========
Harmonics
=========
       
- at -3 dBFS: typical performance < -45 dBc 
- at -20 dBFS: typical performance < -60 dBc 
       
Measurements refer to the LV jumper setting, inputs matched and outputs terminated, outputs signal disabled, and PCB grounded through SMA ground.
    
=============================
Spurious frequency components
=============================

- Typically < -90 dBFS 
    
Measurements refer to the LV jumper setting, inputs, and outputs terminated, outputs signal disabled, and the PCB grounded through SMA ground. In the pictures below, typical performances of Red Pitaya fast analog inputs are shown. For the reference signal generation, we have used the |Agilent 33250A| Signal generator. For the reference spectrum measurements of the generated signal, we have used the |Agilent E4404B| Spectrum analyzer.  The same signal is acquired with the **Red Pitaya board and FFT analysis** is performed. Results are shown in the figures below, where Red Pitaya measurements are on the right. 

Measurements refer to the LV jumper setting, inputs, and outputs terminated, outputs signal disabled, and the PCB grounded through SMA ground.

.. figure:: Measurement_setup.png
            
    Measurement setup
    
=================
Reference signals
=================

    #. Reference signal: -20 dBm, 2 MHz

       .. figure:: -20dBm_2MHz_RP_AG.png
       
            Reference Signal: -20 dBm 2 MHz
    
    #. Reference signal: -20 dBm, 10 MHz
       
       .. figure::   -20dBm_10MHz_RP_AG.png

            Reference Signal: -20 dBm 10 MHz
            
    #. Reference signal: -20 dBm, 30 MHz
      
       .. figure:: -20dBm_30MHz_RP_AG.png

            Reference Signal: -20 dBm 30 MHz
            
    #. Reference signal: 0  dBm, 2 MHz
  
       .. figure:: 0dBm_2MHz_RP_AG.png

            Reference Signal: 0 dBm 2 MHz
            
    #. Reference signal: 0 dBm, 10 MHz
  
       .. figure:: 0dBm_10MHz_RP_AG.png

            Reference Signal: 0 dBm 10 MHz
            
    #. Reference signal: 0 dBm, 30 MHz
  
       .. figure:: 0dBm_30MHz_RP_AG.png

            Reference Signal: 0 dBm 30 MHz
            
    #. Reference signal: -3 dBFS, 2 MHz
  
       .. figure:: -3dBFS_2MHZ_RP_AG.png

            Reference Signal: -3 dBFS 2 MHz
            
    #. Reference signal: -3 dBFS, 10 MHz
  
       .. figure:: -3dBFS_10MHZ_RP_AG.png

            Reference Signal: -3 dBFS 10 MHz
            
    #. Reference signal: -3 dBFS, 30 MHz
  
       .. figure:: -3dBFS_30MHZ_RP_AG.png
       
          Reference Signal: -3 dBFS 30 MHz
            
Due to the natural distribution of the electrical characteristics of the analog inputs and outputs, their offsets and gains will differ slightly across various Red Pitaya boards and may change over time. The calibration coefficients are stored in EEPROM on the Red Pitaya and can be accessed and modified with the calibration utility:
    
===============
DC offset error
===============

- <5 % Full Scale 
 
==========
Gain error
==========

- < 3% (at LV jumper setting), <10% (at HV jumper setting) 
    
Further corrections can be applied through more precise gain and DC offset :ref:`calibration <calib>`.  
        
        
.. |Agilent 33250A| raw:: html

    <a href="http://www.keysight.com/en/pd-1000000803%3Aepsg%3Apro-pn-33250A/function-arbitrary-waveform-generator-80-mhz?cc=US&lc=eng" target="_blank">Agilent 33250A</a>
        
.. |Agilent E4404B| raw:: html

    <a href="https://www.keysight.com/us/en/product/E4404B/esae-spectrum-analyzer-9-khz-to-67-ghz.html" target="_blank">Agilent E4404B</a>



.. _calib:

*************************
Analog inputs calibration
*************************

Calibration processes can be performed using the :ref:`Calibration app <calibration_app>`.
or using the **calib** :ref:`command line utility <com_line_tools>`. When performing calibration with the
:ref:`Calibration app <calibration_app>`, just select *Settings -> Calibration* and follow the instructions.

- Calibration using **calib** utility
    
Start your Red Pitaya and connect to it via a terminal.

.. code-block:: shell-session
   
   redpitaya> calib
 
    Usage: calib [OPTION]...
    
    OPTIONS:
     -r    Read calibration values from EEPROM (to stdout).
     -w    Write calibration values to EEPROM (from stdin).
     -f    Use factory address space.
     -d    Reset calibration values in EEPROM with factory defaults.
     -v    Produce verbose output.
     -h    Print this info.

The EEPROM is a non-volatile memory, therefore the calibration coefficients will not change during Red Pitaya power cycles, nor will they change with software upgrades via Bazaar or with manual modifications of the SD card content. 
An example of calibration parameters readout from EEPROM with verbose output:

.. code-block:: shell-session
   
   redpitaya> calib -r -v
   FE_CH1_FS_G_HI = 45870551      # IN1 gain coefficient for LV (± 1V range)  jumper configuration.
   FE_CH2_FS_G_HI = 45870551      # IN2 gain coefficient for LV (± 1V range)  jumper configuration.
   FE_CH1_FS_G_LO = 1016267064    # IN1 gain coefficient for HV (± 20V range) jumper configuration.
   FE_CH2_FS_G_LO = 1016267064    # IN2 gain coefficient for HV (± 20V range) jumper configuration.
   FE_CH1_DC_offs = 78            # IN1 DC offset  in ADC samples.
   FE_CH2_DC_offs = 25            # IN2 DC offset  in ADC samples.
   BE_CH1_FS = 42755331           # OUT1 gain coefficient.
   BE_CH2_FS = 42755331           # OUT2 gain coefficient.
   BE_CH1_DC_offs = -150          # OUT1 DC offset in DAC samples.
   BE_CH2_DC_offs = -150          # OUT2 DC offset in DAC samples.

An example of the same calibration parameters readout from EEPROM with non-verbose output, suitable for editing within scripts:

.. code-block:: shell-session

    redpitaya> calib -r
           45870551            45870551          1016267064          1016267064

You can write the changed calibration parameters using the ``calib -w`` command:

1. In the command line (terminal), type calib-w.
#. Press enter.
#. Paste or write new calibration parameters.
#. Press enter.

.. code-block:: shell-session
   
   redpitaya> calib -w
      
              40000000           45870551          1016267064          1016267064                  78                  25            42755331            42755331                -150                -150

Should you bring the calibration vector to an undesired state, you can always reset it to factory defaults using the following command:

.. code-block:: shell-session
   
   redpitaya> calib -d

The DC offset calibration parameter can be obtained as the average of the acquired signal at grounded input. A reference voltage source and an old version of an oscilloscope application can be used to calculate the gain parameter. Start the Oscilloscope app, connect the reference voltage to the desired input, and take measurements. Change the gain calibration parameter using the instructions above, reload the Oscilloscope application, and make measurements again with new calibration parameters. Gain parameters can be optimized by repeating the calibration and measurement steps.

In the table below, typical results after calibration are shown.

=========================== =============== ===========
Parameter                   Jumper settings Value
=========================== =============== ===========
DC GAIN ACCURACY @ 122 kS/s LV              0.2%
DC OFFSET @ 122 kS/s        LV              ± 0.5 mV
DC GAIN ACCURACY @ 122 kS/s HV              0.5%
DC OFFSET @ 122 kS/s        HV              ± 5 mV
=========================== =============== ===========

AC gain accuracy can be extracted from Frequency response - Bandwidth.

.. figure:: 800px-Bandwidth_of_Fast_Analog_Inputs.png


##############
Analog outputs
##############

The Red Pitaya board analog front-end features two fast analog outputs.

**********************
General Specifications
**********************

+---------------------------------+-----------------------------------------------+
| Number of channels              | 2                                             |
+---------------------------------+-----------------------------------------------+
| Sample rate                     | 125 Msps                                      |
+---------------------------------+-----------------------------------------------+
| DAC resolution                  | 14 bits                                       |
+---------------------------------+-----------------------------------------------+
| Output coupling                 | DC                                            |
+---------------------------------+-----------------------------------------------+
| Load impedance                  | 50 Ω                                          |
+---------------------------------+-----------------------------------------------+
| Full scale power                | > 9 dBm                                       |
+---------------------------------+-----------------------------------------------+
| Connector type                  | SMA                                           |
+---------------------------------+-----------------------------------------------+
| Output slew rate limit          | 200 V/us                                      |
+---------------------------------+-----------------------------------------------+
| Bandwidth                       | 50 MHz (3 dB)                                 |
+---------------------------------+-----------------------------------------------+


.. note::

    The output channels are designed to drive 50 Ω loads. Terminate outputs when channels are not used. Connect a 50 Ω parallel load (SMA Tee junction) in high-impedance load applications.

.. note::

    The typical power level with 1 MHz sine is 9.5 dBm. Output power is subject to slew rate limitations.
    
.. note::

    The SMA connectors on the cables connected to Red Pitaya must correspond to the standard MIL­C­39012. The central pin must be of a suitable length, otherwise, the SMA connector, installed on the Red Pitaya, will mechanically damage the SMA connector. The central pin of the SMA connector on the Red Pitaya will lose contact with the board and the board will not be possible to repair due to the mechanical damage (separation of the pad from the board).
    
.. figure:: Outputs.png
       
    Output channel Output voltage range: ± 1 V
        
The output stage is shown in the picture below.
    
.. figure:: Outputs_stage.png
       
    Output channel schematics
           
================
Output impedance
================

The impedance of the output channels (output amplifier and filter) is shown in the figure below.
    
.. figure:: Output_impedance.png
    
    Output impedance

=========
Bandwidth
=========

+---------------------------------+-----------------------------------------------+
| Bandwidth                       | 50 MHz (3 dB)                                 |
+---------------------------------+-----------------------------------------------+

Bandwidth measurements are shown in the picture below. Measurements are taken with the |Agilent MSO7104B| oscilloscope for each frequency step (10 Hz – 60 MHz) of the measured signal. The Red Pitaya board OUT1 is used with 0 dBm output power. The second output channel and both input channels are terminated with 50 Ohm termination. The Oscilloscope ground is used to ground the Red Pitaya board. The oscilloscope input must be set to 50 Ohm input impedance.

.. figure:: Fast_Analog_Outputs_Bandwidt.png


=========
Harmonics
=========

Typical performance: (at 8 dBm) 
       - -51 dBc @ 1 MHz
       - -49 dBc @ 10 MHz
       - -48 dBc @ 20 MHz
       - -53 dBc @ 45 MHz 

===============
DC offset error
===============

- < 5% FS 

==========
Gain error
==========

- < 5% 
    
Further corrections can be applied through more precise gain and DC offset calibration.


.. |Agilent MSO7104B| raw:: html

    <a href="http://www.keysight.com/en/pdx-x201799-pn-MSO7104B/mixed-signal-oscilloscope-1-ghz-4-analog-plus-16-digital-channels?pm=spc&nid=-32535.1150174&cc=SI&lc=eng" target="_blank">Agilent MSO7104B</a>


*************************
Analog output calibration
*************************

Calibration is performed in a noise-controlled environment. Inputs' and outputs' gains are calibrated with 0.02% and 0.003% DC reference voltage standards. Input gain calibration is performed in a medium-sized timebase range. The Red Pitaya is a non-shielded device, and its input/output ground is not connected to the earth's ground, as is the case in most classical oscilloscopes. To achieve the calibration results given below, Red Pitaya must be grounded and shielded.

.. Table: Typical specification after calibration

================= ==========
Parameter         Value
================= ==========
DC GAIN ACCURACY  0.4%
DC OFFSET         ± 4 mV
RIPPLE(@ 0.5V DC) 0.4 mVpp
================= ==========

    Typical specifications after calibration



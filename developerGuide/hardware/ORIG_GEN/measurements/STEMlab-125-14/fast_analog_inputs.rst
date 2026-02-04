.. _measurements_orig_gen_inputs:

###########################
Fast Analog Inputs
###########################

This page contains detailed specifications and performance measurements for Original Generation fast analog inputs.

.. contents::
   :local:
   :depth: 2
   :backlinks: none

|

The STEMlab 125-14 board analog front-end features 2 fast analog inputs. 


General Specifications
=======================

+---------------------------------+-----------------------------------------------+
| Number of channels              | 2                                             |
+---------------------------------+-----------------------------------------------+
| Sample rate                     | 125 Msps                                      |
+---------------------------------+-----------------------------------------------+
| ADC resolution                  | 14 bits                                       |
+---------------------------------+-----------------------------------------------+
| Input coupling                  | DC                                            |
+---------------------------------+-----------------------------------------------+
| | **Absolute maximum input**    | | **LV: 6 V (1500 V ESD)**                    |
| | **voltage rating**            | | **HV: 30 V (1500 V ESD)**                   |
+---------------------------------+-----------------------------------------------+
| Overload protection             | Protection diodes                             |
|                                 | (under the input voltage rating conditions)   |
+---------------------------------+-----------------------------------------------+
| Connector type                  | SMA                                           |
+---------------------------------+-----------------------------------------------+
| Input stage voltage ranges [#]_ | | LV (±1 V)                                   |
|                                 | | HV (±20 V)                                  |
+---------------------------------+-----------------------------------------------+
| Bandwidth                       | 50 MHz (-3 dB)                                |
+---------------------------------+-----------------------------------------------+

.. [#] Measurement performance is specified within this range. 

    .. note::
    
       Overload protection applies to low frequency signals. For input signals containing frequency components above 1 kHz, where capacitor divider comes into play, the full scale value defines the maximum permissible input voltage.

    .. note::
    
        The SMA connectors on the cables connected to Red Pitaya must comply with the MILC39012 standard. The centre pin must be of suitable length, otherwise the SMA connector installed in Red Pitaya will mechanically damage the SMA connector.
        The centre pin of the SMA connector on Red Pitaya will lose contact with the board and the board will not be repairable due to the mechanical damage (separation of the pad from the board).




Input stage schematics
------------------------

.. figure:: img/schematics/Fast_analog_inputs_sch.png
    :width: 1200
        
    Fast analog inputs schematics


Input coupling
------------------

Fast analog inputs are **DC coupled**. Input impedance is given in the picture below. 

.. figure:: img/RF_inputs/Input_impedance_of_fast_analog_inputs.png
    :width: 1000
       
    The input impedance of fast analog inputs


Input bandwidth
----------------

+---------------------------------+-----------------------------------------------+
| Bandwidth                       | 50 MHz (-3 dB)                                |
+---------------------------------+-----------------------------------------------+
    
In the picture below, the Frequency Response - Bandwidth of fast analog inputs is shown. Measurements are taken using an |Agilent 33250A| signal generator as a reference. The measured signal is acquired using :ref:`remote control commands <command_list>`. An amplitude voltage is extracted from the acquired signal and compared to the reference signal amplitude.
        
.. figure:: img/RF_inputs/Bandwidth_of_Fast_Analog_Inputs.png
    :width: 1000
        
    The bandwidth of fast analog inputs
        
Because of the maximum sampling rate of 125 MS/s when measuring signals above 10 MHz, we have used sin(x)/x interpolation to get more accurate results of Vpp voltage and, 
with that, more accurate measurements of analog bandwidth. When measuring signals above 10 MHz, similar results should be obtained without interpolation or directly with an Oscilloscope application and P2P measurements.
        
Notice: When making measurements without interpolation, you need to extract the maximum and minimum of the acquired signal using a complete 16k buffer.
When using P2P measurements on an oscilloscope, you need to take the maximum value shown as a measurement result. An example of sin(x)/x interpolation for a 40 MHz signal is shown in the picture below (right).
        
.. note::
        
    In the picture, only 10 samples of 16k buffer are shown to represent a few periods of 40 MHz signal.
        
.. figure:: img/RF_inputs/Sin(x)x_Interpolation.png
    :width: 1000
        
    Sin(x)/x Interpolation
   

Input noise
---------------

Measurements refer to a high gain (LV ±1 V) jumper setting, with limited environmental noise, inputs and outputs terminated, output signals disabled, and the PCB grounded through SMA ground.
Measurements are performed on 16k continuous samples at full rate (125 MS/s). (Typical full bandwidth std(Vn) < 0.5 mV). The noise spectrum shown in the picture below (right) is calculated using FFT analysis on N = 16384 samples sampled at Fs = 125E6 MS/s.
    
.. figure:: img/RF_inputs/Noise_distribution.png
    :width: 1200
        
    Noise distribution 
        
.. figure:: img/RF_inputs/Noise_level.png
    :width: 1200
        
    Noise level
        

Input crosstalk
-------------------------

Crosstalk measurements were performed between input channels 1 and 2 for both LV and HV modes.

+------------------------------------+------------------+------------------+------------------+------------------+
|                                    | **Up to 30 MHz**                    | **Above 30 MHz**                    |
+------------------------------------+------------------+------------------+------------------+------------------+
| |br|                               | |br|             | |br|             | |br|             | |br|             |
| **IN1 \ IN2**                      | **LV**           | **HV**           | **LV**           | **HV**           |
+------------------------------------+------------------+------------------+------------------+------------------+
| **LV**                             | >55 dB           | >60 dB           | 40 dB            | 40 dB            |
+------------------------------------+------------------+------------------+------------------+------------------+
| **HV**                             | >40 dB           | >50 dB           | 35 dB            | 35 dB            |
+------------------------------------+------------------+------------------+------------------+------------------+
| |br|                               | |br|             | |br|             | |br|             | |br|             |
| **IN2 \ IN1**                      | **LV**           | **HV**           | **LV**           | **HV**           |
+------------------------------------+------------------+------------------+------------------+------------------+
| **LV**                             | >55 dB           | 50 dB            | 40 dB            | 40 dB            |
+------------------------------------+------------------+------------------+------------------+------------------+
| **HV**                             | >55 dB           | >50 dB           | >40 dB           | >35 dB           |
+------------------------------------+------------------+------------------+------------------+------------------+


Typical performance:

    * 65 dB @ 10 kHz
    * 50 dB @ 100 kHz
    * 55 dB @ 1 M
    * 55 dB @ 10 MHz
    * 52 dB @ 20 MHz
    * 48 dB @ 30 MHz
    * 44 dB @ 40 MHz
    * 40 dB @ 50 MHz

The typical performance characteristics were measured on LV jumper setting on both channels. The SMA connectors not involved in the measurement are terminated.
    

Input harmonics
----------------

+------------------------------------+------------------------------------+
| Amplitude                          | Harmonics                          |
+====================================+====================================+
| -3 dBFS                            | -45 dBc                            |
+------------------------------------+------------------------------------+
| -20 dBFS                           | -60 dBc                            |
+------------------------------------+------------------------------------+ 
       
The typical measurements refer to the LV jumper setting, inputs matched and outputs terminated, outputs signal disabled, and PCB grounded through SMA ground.


Input SFDR
-------------------------------

+---------------------------------+-----------------------------------------------+
| Input SFDR                      | < -90 dBFS                                    |
+---------------------------------+-----------------------------------------------+
    
Measurements refer to the LV jumper setting, inputs, and outputs terminated, outputs signal disabled, and the PCB grounded through SMA ground.
In the pictures below, typical performances of Red Pitaya fast analog inputs are shown. For the reference signal generation, we have used the |Agilent 33250A| Signal generator.
For the reference spectrum measurements of the generated signal, we have used the |Agilent E4404B| Spectrum analyzer.  The same signal is acquired with the **Red Pitaya board and FFT analysis** is performed.
Results are shown in the figures below, where Red Pitaya measurements are on the right.

.. figure:: img/RF_inputs/Measurement_setup.png
    :width: 800
            
    Measurement setup
    

Reference signals
------------------

    #. Reference signal: -20 dBm, 2 MHz

        .. figure:: img/RF_inputs/-20dBm_2MHz_RP_AG.png
            :width: 1200
    
    #. Reference signal: -20 dBm, 10 MHz
       
        .. figure::   img/RF_inputs/-20dBm_10MHz_RP_AG.png
            :width: 1200
            
    #. Reference signal: -20 dBm, 30 MHz
      
        .. figure:: img/RF_inputs/-20dBm_30MHz_RP_AG.png
            :width: 1200
            
    #. Reference signal: 0 dBm, 2 MHz
  
        .. figure:: img/RF_inputs/0dBm_2MHz_RP_AG.png
            :width: 1200
            
    #. Reference signal: 0 dBm, 10 MHz
  
        .. figure:: img/RF_inputs/0dBm_10MHz_RP_AG.png
            :width: 1200
            
    #. Reference signal: 0 dBm, 30 MHz
  
        .. figure:: img/RF_inputs/0dBm_30MHz_RP_AG.png
            :width: 1200
            
    #. Reference signal: -3 dBFS, 2 MHz
  
        .. figure:: img/RF_inputs/-3dBFS_2MHZ_RP_AG.png
            :width: 1200
            
    #. Reference signal: -3 dBFS, 10 MHz
  
        .. figure:: img/RF_inputs/-3dBFS_10MHZ_RP_AG.png
            :width: 1200
            
    #. Reference signal: -3 dBFS, 30 MHz
  
        .. figure:: img/RF_inputs/-3dBFS_30MHZ_RP_AG.png
            :width: 1200
            
Due to the natural distribution of the electrical characteristics of the analog inputs and outputs, their offsets and gains will differ slightly across various Red Pitaya boards and may change over time. The calibration coefficients are stored in EEPROM on the Red Pitaya and can be accessed and modified with the calibration utility:
    

Input DC offset error
----------------------

+---------------------------------+-----------------------------------------------+
| DC offset error                 | < 5% FS                                       |
+---------------------------------+-----------------------------------------------+
 

Input gain error
-----------------

+------------------------------------+------------------------------------+
| Jumper settings                    | Gain error                         |
+====================================+====================================+
| LV                                 | <3%                                |
+------------------------------------+------------------------------------+
| HV                                 | <10%                               |
+------------------------------------+------------------------------------+ 
    
Further corrections can be applied through more precise gain and DC offset :ref:`calibration <calib>`.  
        
        
.. |Agilent 33250A| raw:: html

    <a href="http://www.keysight.com/en/pd-1000000803%3Aepsg%3Apro-pn-33250A/function-arbitrary-waveform-generator-80-mhz?cc=US&lc=eng" target="_blank">Agilent 33250A</a>
        
.. |Agilent E4404B| raw:: html

    <a href="https://www.keysight.com/us/en/product/E4404B/esae-spectrum-analyzer-9-khz-to-67-ghz.html" target="_blank">Agilent E4404B</a>



.. _calib:


Analog inputs calibration
============================

Calibration processes can be performed using the :ref:`Calibration application <calibration_app>` or using the **calib** :ref:`command line utility <com_line_tools>`.
To calibrate the Red Pitaya using the :ref:`Calibration application <calibration_app>`, simply select *System -> Calibration* and follow the instructions.

**Calibration using calib utility**
    
Start your Red Pitaya and connect to it via :ref:`SSH <ssh>`.

.. code-block:: shell-session
   
    root@rp-xxxxxx:~# calib
    calib version 2.00-0-f6ded7198
    
    Usage: calib [OPTION]...
    
    OPTIONS:
     -r    Read calibration values from eeprom (to stdout).
           The -n flag has no effect. The system automatically determines the type of stored data.
    
     -w    Write calibration values to eeprom (from stdin).
           Possible combination of flags: -wn, -wf, -wfn, -wmn, -wfmn
    
     -f    Use factory address space.
     -d    Reset calibration values in eeprom from factory zone. WARNING: Saves automatic to a new format
    
     -i    Reset calibration values in eeprom by default
           Possible combination of flags: -in , -inf.
    
     -o    Converts the calibration from the user zone to the old calibration format. For ecosystem version 0.98
    
     -v    Produce verbose output.
     -h    Print this info.
     -x    Print in hex.
     -u    Print stored calibration in unified format.
    
     -m    Modify specific parameter in universal calibration
     -n    Flag for working with the new calibration storage format.

The EEPROM is a non-volatile memory, so the calibration coefficients will not change during Red Pitaya power cycles, software upgrades via Bazaar, or manual changes to the contents of the SD card. 
An example of reading calibration parameters from the EEPROM with verbose output:

.. code-block:: shell-session

    root@rp-xxxxxx:~# calib -r -v
    dataStructureId = 5
    wpCheck = 53
    count = 28
    DAC Ch1 Gain (1) = 2674690              # OUT1 gain coefficient
    DAC Ch1 Offset (2) = -69                # OUT1 DC offset 
    DAC Ch2 Gain (3) = 2692407              # OUT2 gain coefficient
    DAC Ch2 Offset (4) = -94                # OUT2 DC offset
    ADC Ch1 Gain 1/1 (9) = 2817122          # IN1 gain coefficient for LV (±1V range)  jumper configuration
    ADC Ch1 Offset 1/1 (10) = -159          # IN1 DC offset for LV (±1V range)  jumper configuration
    ADC Ch2 Gain 1/1 (11) = 2811646         # IN2 gain coefficient for LV (±1V range)  jumper configuration
    ADC Ch2 Offset 1/1 (12) = -126          # IN2 DC offset for LV (±1V range)  jumper configuration
    ADC Ch1 Gain 1/20 (17) = 3113286        # IN1 gain coefficient for HV (±20V range) jumper configuration
    ADC Ch1 Offset 1/20 (18) = -186         # IN1 DC offset for HV (±20V range) jumper configuration
    ADC Ch2 Gain 1/20 (19) = 3115407        # IN2 gain coefficient for HV (±20V range) jumper configuration
    ADC Ch2 Offset 1/20 (20) = -148         # IN2 DC offset for HV (±20V range) jumper configuration
    ADC Ch1 AA 1/1 (33) = 32147             # IN1 FPGA filter coefficient AA for LV
    ADC Ch1 BB 1/1 (34) = 276423            # IN1 FPGA filter coefficient BB for LV
    ADC Ch1 PP 1/1 (35) = 9830              # IN1 FPGA filter coefficient PP for LV
    ADC Ch1 KK 1/1 (36) = 14260634          # IN1 FPGA filter coefficient KK for LV
    ADC Ch2 AA 1/1 (37) = 32147             # IN2 FPGA filter coefficient AA for LV
    ADC Ch2 BB 1/1 (38) = 276423            # IN2 FPGA filter coefficient BB for LV
    ADC Ch2 PP 1/1 (39) = 9830              # IN2 FPGA filter coefficient PP for LV
    ADC Ch2 KK 1/1 (40) = 14260634          # IN2 FPGA filter coefficient KK for LV
    ADC Ch1 AA 1/20 (49) = 16901            # IN1 FPGA filter coefficient AA for HV
    ADC Ch1 BB 1/20 (50) = 193419           # IN1 FPGA filter coefficient BB for HV
    ADC Ch1 PP 1/20 (51) = 9830             # IN1 FPGA filter coefficient PP for HV
    ADC Ch1 KK 1/20 (52) = 14260634         # IN1 FPGA filter coefficient KK for HV
    ADC Ch2 AA 1/20 (53) = 16901            # IN2 FPGA filter coefficient AA for HV
    ADC Ch2 BB 1/20 (54) = 193419           # IN2 FPGA filter coefficient BB for HV
    ADC Ch2 PP 1/20 (55) = 9830             # IN2 FPGA filter coefficient PP for HV
    ADC Ch2 KK 1/20 (56) = 14260634         # IN2 FPGA filter coefficient KK for HV

An example of reading the same calibration parameters from EEPROM with non-verbose output, suitable for editing within scripts:

.. code-block:: shell-session

    root@rp-xxxxxx:~# calib -r
                        1             2674690                   2                 -69                   3             2692407
                        4                 -94                   9             2817122                  10                -159
                       11             2811646                  12                -126                  17             3113286
                       18                -186                  19             3115407                  20                -148
                       33               32147                  34              276423                  35                9830
                       36            14260634                  37               32147                  38              276423
                       39                9830                  40            14260634                  49               16901
                       50              193419                  51                9830                  52            14260634
                       53               16901                  54              193419                  55                9830
                       56            14260634

You can write the changed calibration parameters using the ``calib -w`` command:

1. In the command line (terminal), type calib -w.
#. Press enter.
#. Paste or write new calibration parameters.
#. Press enter.

.. code-block:: shell-session
   
    root@rp-xxxxxx:~# calib -wn
                        1             2674690                   2                 -69                   3             2692407
                        4                 -94                   9             2817122                  10                -159
                       11             2811646                  12                -126                  17             3113286
                       18                -186                  19             3115407                  20                -148
                       33               32147                  34              276423                  35                9830
                       36            14260634                  37               32147                  38              276423
                       39                9830                  40            14260634                  49               16901
                       50              193419                  51                9830                  52            14260634
                       53               16901                  54              193419                  55                9830

Should you bring the calibration vector to an undesired state, you can always reset it to factory defaults using the following command:

.. code-block:: shell-session
   
   redpitaya> calib -d

The DC offset calibration parameter can be obtained as the average of the signal acquired with the input grounded.

The calibration parameters can be changed with the :ref:`Calibration Tool <calib_util>`. Alternatively, a reference voltage source and the oscilloscope application can be used to calculate the gain parameter.
Start the oscilloscope application, connect the reference voltage to the desired input and take measurements.
Change the gain calibration parameters as described above, reload the oscilloscope application and take measurements again with the new calibration parameters.
The gain parameters can be optimised by repeating the calibration and measurement steps.

The table below shows typical results after calibration.

=========================== =============== ===========
Parameter                   Jumper settings Value
=========================== =============== ===========
DC GAIN ACCURACY @ 122 kS/s LV              0.2%
DC OFFSET @ 122 kS/s        LV              ±0.5 mV
DC GAIN ACCURACY @ 122 kS/s HV              0.5%
DC OFFSET @ 122 kS/s        HV              ±5 mV
=========================== =============== ===========

AC gain accuracy can be extracted from Frequency response - Bandwidth.

.. figure:: img/RF_inputs/Bandwidth_of_Fast_Analog_Inputs.png
    :width: 1000


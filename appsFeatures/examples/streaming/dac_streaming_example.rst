.. _stream_dac_example:

#########################
DAC streaming example
#########################

This example demonstrates how to generate a custom sine wave signal on the DAC outputs using the command line client. 
This tutorial covers the complete workflow from creating a waveform to streaming it to the Red Pitaya.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Prerequisites
**************

Before starting this example, ensure you have:

* Red Pitaya board with OS version 2.07-43 or newer
* :ref:`Command line client <stream_command_client>` installed on your computer
* Enough :ref:`DMM memory <deepMemoryMode>` reserved for DAC streaming (at least 100 MB recommended)
* Python 3 with numpy and scipy.io.wavfile libraries (for waveform creation)
* :ref:`SSH access <ssh>` to your Red Pitaya board

|

Overview
*********

This example will guide you through:

1. Creating a custom sine wave waveform in Python
2. Establishing SSH connection to Red Pitaya
3. Loading the FPGA and starting the streaming application
4. Configuring the DAC streaming parameters
5. Starting the DAC streaming

The example uses the **one-pack mode** for maximum performance, where the entire waveform fits in the DMM memory.

|

Step-by-step tutorial
**********************

Step 1: Create a custom waveform
==================================

Create a Python script to generate a sine wave signal with 1024 samples. This waveform will be saved as a WAV file.

.. code-block:: python

    import numpy as np
    from scipy.io import wavfile
    import matplotlib.pyplot as plt

    # Waveform parameters
    N = 1024                                        # Number of samples in a period
    num_periods = 1                                 # Number of periods in the signal
    num_bits = 16
    max_val = 2**(num_bits-1) - 1                   #  32767
    min_val = -2**(num_bits-1)                      # -32768

    # Generate sine wave
    t = np.linspace(0, 1, N*num_periods)*2*np.pi
    y = np.sin(num_periods*t)*max_val               # FPGA divides the signal by 4

    # Convert to signed 16-bit integers
    y_signed16 = np.int16(y)

    # Optional: Plot to verify waveform
    plt.plot(y_signed16)
    plt.title('Custom waveform')
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.show()

    # Save as WAV file
    sample_rate = 44100                             # (Doesn't matter) Standard audio sample rate
    wavfile.write('arb_waveform_signed16.wav', sample_rate, y_signed16)
    
    print(f"Waveform created with {len(y_signed16)} samples")
    print(f"File size: {len(y_signed16) * 2} bytes")

Save this script as ``create_waveform.py`` and run it:

.. code-block:: console

    python create_waveform.py

This will create ``arb_waveform_signed16.wav`` in your current directory.

|

Step 2: Establish SSH connection
==================================

Connect to your Red Pitaya board using SSH. Replace ``<IP_ADDRESS>`` with your Red Pitaya's IP address or use the ``.local`` address.

.. code-block:: console

    ssh root@<IP_ADDRESS or .LOCAL_ADDRESS>

For example:

.. code-block:: console

    ssh root@192.168.1.100
    # or
    ssh root@rp-f0xxxx.local

The default password is ``root``.

|

Step 3: Load FPGA and start streaming application
===================================================

Once connected via SSH, load the streaming FPGA image and start the streaming server:

.. code-block:: console

    redpitaya> overlay.sh stream_app
    redpitaya> streaming-server

You should see LED 2 turn on and LED 0 blinking, indicating the streaming application is running.

.. note::

    Keep this SSH terminal open. The streaming server must be running for the next steps.

|

Step 4: Get and edit the configuration file
=============================================

Open a new terminal or command prompt window on your computer (don't close the SSH session). Navigate to the directory where the command line client is installed.

**Download the configuration file:**

.. code-block:: console

    computer> .\rpsa_client.exe -c -g F

The configuration file will be downloaded to the ``configs`` folder of the command line client.

|

**Edit the configuration file:**

Open the downloaded configuration file (usually named something like ``streaming_config.json``) with your favorite text editor. Edit the DAC streaming parameters as follows:

.. code-block:: json

    {
        "adc_streaming" : 
        {
            "adc_decimation" : 125,
            "adc_pass_mode" : "NET",
            "channel_ac_dc_1" : "DC",
            "channel_ac_dc_2" : "DC",
            "channel_ac_dc_3" : "DC",
            "channel_ac_dc_4" : "DC",
            "channel_attenuator_1" : "A_1_1",
            "channel_attenuator_2" : "A_1_1",
            "channel_attenuator_3" : "A_1_1",
            "channel_attenuator_4" : "A_1_1",
            "channel_state_1" : "OFF",
            "channel_state_2" : "OFF",
            "channel_state_3" : "OFF",
            "channel_state_4" : "OFF",
            "data_type_sd" : "RAW",
            "format_sd" : "BIN",
            "resolution" : "BIT_16",
            "samples_limit_sd" : 0,
            "use_calib" : "ON"
        },
        "dac_streaming" : 
        {
            "channel_gain_1" : "X1",
            "channel_gain_2" : "X1",
            "dac_pass_mode" : "DAC_NET",
            "dac_rate" : 125000000,
            "file_sd" : "arb_waveform_signed16.wav",
            "file_type_sd" : "WAV",
            "repeat" : "DAC_REP_ON",
            "repeatCount" : 1
        },
        "memory_manager" : 
        {
            "adc_size" : 0,
            "block_size" : 8388608,
            "dac_size" : 104857600,
            "gpio_size" : 0
        }
    }

Key parameters explained:

* ``dac_rate: 125000000`` - 125 MHz output rate (maximum performance)
* ``block_size: 8388608`` - 8 MiB (8,388,608 bytes)
* ``dac_size: 104857600`` - 100 MiB (104,857,600 bytes) reserved for DAC
* ``repeat: "DAC_REP_ON"`` - Enable repetition
* ``repeatCount: 1`` - Generate once

.. note::

    1 MiB = 1024×1024 Bytes = 2^20 Bytes = 1,048,576 Bytes. We are using Mebibytes (MiB) instead of Megabytes (MB) to avoid confusion with the decimal system.

Save the edited configuration file as ``config_dac.json``.

|

**Upload the configuration file:**

Upload the edited configuration file to the Red Pitaya board:

.. code-block:: console

    computer> .\rpsa_client.exe -c -s F -f .\configs\config_dac.json

|

Step 5: Start the DAC streaming
=================================

Now start the DAC streaming using the command line client. The DAC streaming will generate the sine wave signal on OUT1.

.. code-block:: console

    computer> .\rpsa_client.exe -o -f wav -d <path_to_wav_file>\arb_waveform_signed16.wav -r inf

Replace ``<path_to_wav_file>`` with the actual path to your WAV file.

For example:

.. code-block:: console

    computer> .\rpsa_client.exe -o -f wav -d C:\Users\YourName\Documents\arb_waveform_signed16.wav -r inf

Parameters explained:

* ``-o`` - Output (DAC streaming mode)
* ``-f wav`` - WAV file format
* ``-d <path>`` - Path to the data file
* ``-r inf`` - Repeat infinitely

|

Step 6: Verify the output
===========================

You can now verify the sine wave output on OUT1 using:

* An oscilloscope connected to the output
* The Red Pitaya Oscilloscope application
* A spectrum analyzer

The output should be a clean sine wave at the frequency determined by:

.. math::

    f_{out} = \frac{dac\_rate}{N} = \frac{125,000,000}{1024} \approx 122,070 \text{ Hz}

|

Step 7: Stop the streaming
============================

To stop the DAC streaming, press ``Ctrl+C`` in the command line client terminal.

|

Troubleshooting
****************

Waveform not generated
========================

**Problem:** No output signal

**Solutions:**

1. Verify the streaming server is running on Red Pitaya
2. Check that the configuration file was uploaded successfully
3. Ensure the WAV file path is correct
4. Verify sufficient memory is allocated (``dac_size`` in config)
5. Check that the waveform file is not corrupted

|

Data loss or unstable signal
==============================

**Problem:** Signal has glitches or discontinuities

**Solutions:**

1. **Ensure the waveform fits completely in reserved DDR memory** (file size < dac_size)
   
   * When the waveform fits entirely in the reserved region, Red Pitaya can generate data at full speed (125 MSps)
   * If the file is larger than the reserved region, it will be continuously streamed to the board, significantly reducing performance and maximum output sampling speed
   * This is the most effective way to avoid glitches and achieve optimal performance

2. Reduce the ``dac_rate`` if using true streaming mode
3. Increase ``block_size`` to 8 MB
4. Ensure the waveform has at least 1024 samples
5. Check network stability

|

Configuration errors
=====================

**Problem:** Configuration file rejected

**Solutions:**

1. Validate JSON syntax using a JSON validator
2. Check all parameter values are within valid ranges
3. Ensure memory allocations don't exceed reserved DMM size
4. Verify file paths and names are correct

|

Variations and extensions
***************************

Multiple periods
=================

To generate multiple periods of the sine wave, modify the Python script:

.. code-block:: python

    num_periods = 10                                # 10 periods
    t = np.linspace(0, num_periods, N*num_periods)*2*np.pi
    y = np.sin(t)*max_val

|

Different waveforms
====================

Generate other waveforms by modifying the generation equation:

**Square wave:**

.. code-block:: python

    y = np.sign(np.sin(num_periods*t))*max_val

**Sawtooth wave:**

.. code-block:: python

    from scipy import signal
    y = signal.sawtooth(num_periods*t)*max_val

**Triangle wave:**

.. code-block:: python

    from scipy import signal
    y = signal.sawtooth(num_periods*t, width=0.5)*max_val

|

Two-channel output
===================

Create a WAV file with two channels to use both OUT1 and OUT2:

.. code-block:: python

    # Generate two different waveforms
    y1 = np.sin(num_periods*t)*max_val              # OUT1: sine
    y2 = np.sin(2*num_periods*t)*max_val            # OUT2: sine at 2x frequency
    
    # Stack as stereo (2 channels)
    y_stereo = np.column_stack((y1, y2)).astype(np.int16)
    
    wavfile.write('stereo_waveform.wav', sample_rate, y_stereo)

|

Next steps
***********

* Experiment with different waveforms and parameters
* Learn about :ref:`DAC Configuration <stream_dac_config>` for more control options
* Review :ref:`Data Generation Limitations <stream_dac_limitations>` to understand performance boundaries
* Try combining with :ref:`ADC streaming <stream_adc_config>` to create a signal processing loop
* Explore :ref:`Advanced Configuration <stream_advanced_config>` for fine-tuning

.. _all_apps:

############
Applications
############

All Red Pitaya applications are web-based and don't require the installation of any native software. Users can access them via a browser using their smartphone, tablet or a PC running any popular operating system (macOS, Linux, Windows, Android, and iOS). All official applications are accessible through the :ref:`main web interface <quickstart_connect>`.

This section provides comprehensive guides for all available Red Pitaya applications:

**Basic Measurement & Analysis:**

* **Oscilloscope & Signal Generator** - 2-channel oscilloscope and waveform generator for signal analysis and generation
* **Spectrum Analyzer** - Frequency domain analysis and FFT measurements
* **Logic Analyzer** - Digital signal capture and protocol analysis
* **Arbitrary Waveform Manager** - Create and manage custom waveforms

**Advanced Measurement Tools:**

* **Bode Analyzer** - Frequency response and gain/phase measurements
* **Impedance Analyzer** - Complex impedance measurements across frequencies
* **LCR Meter** - Inductance, capacitance, and resistance measurements
* **Vector Network Analyzer (VNA)** - S-parameter measurements and RF characterization

**Data Acquisition & RF:**

* **Data Stream Control** - High-speed continuous data streaming to PC
* **Playback & Record** - Save and replay signals from file
* **SDR Transceiver** - Software-defined radio transmit and receive

**Advanced Applications:**

* **PyRPL** - Python-based quantum optics and feedback control
* **Marketplace** - Browse and install community-developed applications

When installing 3rd party applications for Red Pitaya, some additional steps might be required. Please consult the installation guide provided by the application authors. 
For offline application installation, please see the :ref:`Developers Guide manual application installation <manual_app_install>`.

.. toctree::
   :maxdepth: 1

   oscSigGen/osc.rst
   arb_manager/arb_manager.rst
   spectrum/spectrum.rst
   logic/logic.rst
   bode/bode.rst
   impedance/impedance.rst
   lcr_meter/lcr_meter.rst
   streaming/top.rst
   playback&record/playback&record.rst
   sdr_tx_rx/sdr_tx_rx.rst
   vna/appVNA.rst
   pyrpl/pyrpl.rst
   marketplace/marketplace.rst



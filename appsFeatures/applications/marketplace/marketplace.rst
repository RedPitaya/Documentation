.. _marketplace:

################################
Marketplace and contributed apps
################################

==========
Overview
==========

Red Pitaya supports a wide range of community-developed applications created by researchers, developers, and enthusiasts worldwide. These third-party applications extend Red Pitaya's capabilities for specialized use cases in scientific research, RF communications, control systems, and more.

**Important Information:**

.. note::

    **For OS 2.07-43 and newer:** The Application Marketplace is no longer available. All unique applications will slowly be migrated to the official Red Pitaya OS and made accessible from the main web interface.

.. note::

    **For older OS versions (pre-2.07-43):** The Application Marketplace remains accessible but most applications require updates for OS 2.00+ compatibility. Check individual application pages for compatibility information.

**Getting Community Applications:**

Community applications are not distributed through the marketplace anymore. To install community applications:

1. Visit the application's community page (linked in each section below)
2. Follow the installation instructions provided by the application author
3. Contact the application author for support, bug reports, or feature requests

.. note:: 

   Applications developed by the Red Pitaya community are not distributed, maintained, or tested by the Red Pitaya team. Our team accepts no responsibility for third-party applications. For feedback, bug reports, or support, please contact the project authors directly.


=========================
Available Applications
=========================

The following community applications are documented here. Each application page includes a link to the developer's repository or website where you can find installation instructions and source code.

**Application Compatibility Overview:**

The table below provides compatibility information for community applications. Check individual application pages for detailed requirements and installation instructions.

.. table::
    :widths: 30 40 15 15

    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | **Application**                       | **Description**                                                            | **OS 2.00+**       | Status                  |
    +=======================================+============================================================================+====================+=========================+
    | |br|                                                                                                                                                              |
    | **Data Acquisition & Streaming**                                                                                                                                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | DAQ Server                            | High-speed continuous data acquisition (15.625 MS/s) with multi-board sync | Custom OS image    | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | |br|                                                                                                                                                              |
    | **RF & Communications**                                                                                                                                           |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | SDR (Pavel Demin)                     | Software-defined radio transceiver                                         | Yes [#f1]_         | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | VNA (Pavel Demin)                     | Vector network analyzer for RF measurements                                | Yes [#f1]_         | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | WSPR (Pavel Demin)                    | Weak Signal Propagation Reporter for amateur radio                         | Custom OS image    | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | RadioBox                              | Multi-mode radio transceiver                                               | No                 | Abandoned               |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Radar                                 | Open-source radar system with Raspberry Pi integration                     | No                 | Not maintained          |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | |br|                                                                                                                                                              |
    | **Control Systems & Signal Processing**                                                                                                                           |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | PyRPL (Leonhard Neuhaus)              | Quantum optics lock-in amplifiers, digital filters, and feedback control   | Yes                | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Linien                                | Laser lock-in                                                              | Yes                | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Lock-in + PID (Marcelo Luda)          | Lock-in amplifier with PID controller                                      | Yes                | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | DSP Sandbox (Pau Gomez)               | Digital signal processing development environment                          | Custom image       | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | LTI DSP Workbench (DashPi)            | Linear time-invariant system analysis                                      | No                 | Not maintained          |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | |br|                                                                                                                                                              |
    | **Analysis Tools**                                                                                                                                                |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Power Analysis                        | Power consumption and efficiency measurement                               | No                 | Abandoned               |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Frequency Response Analyzer           | Frequency response measurements and analysis                               | Yes                | Ported to official OS   |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Impedance Analyzer                    | Complex impedance measurement tool                                         | Yes                | Ported to official OS   |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Multi-Pulse Height Analyzer           | Nuclear spectroscopy pulse analysis                                        | Custom image       | Active                  |
    | (Pavel Demin)                         |                                                                            |                    |                         |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | |br|                                                                                                                                                              |
    | **Scientific Research**                                                                                                                                           |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | OCRA                                  | Open-source MRI console for real-time acquisition                          | Check docs         | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | EPICS                                 | Experimental Physics and Industrial Control System integration             | Check docs         | Active                  |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Qt-Based Tools                        | Qt framework applications for Red Pitaya                                   | No                 | Not maintained          |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+
    | Tesla Coil Driver                     | Musical Tesla coil control system                                          | No                 | Not maintained          |
    +---------------------------------------+----------------------------------------------------------------------------+--------------------+-------------------------+

.. rubric:: Footnotes

.. [#f1] Pavel Demin's SDR and VNA applications are accessible both in the :ref:`official Red Pitaya OS <sdr_tx_rx_apps>` (ported versions that may not be up to date) as well as a part of his custom alpine OS image (latest version).

.. note::

   Compatibility status is based on last known information. Please check the individual application documentation pages for the most current compatibility information and installation instructions.


====================================
Marketplace Access (Legacy)
====================================

**For users running OS versions older than 2.07-43:**

The Application Marketplace can still be accessed through the Red Pitaya web interface. To use the marketplace:

1. **Ensure internet connectivity:** Red Pitaya must have access to the internet, otherwise the Marketplace will fail to open.

   .. figure:: img/Marketplace_fail_connect.png
      :width: 600

2. **Connect to the internet:**
   
   - Connect via :ref:`Wi-Fi <wireless>` or :ref:`ethernet cable to your router <LAN>`
   - Alternatively, configure network passthrough if :ref:`directly connected to a computer <dir_cab_connect>` (requires advanced networking knowledge)




====================================
Application Documentation
====================================

.. toctree::
    :maxdepth: 2
    
    daq_server.rst
    sdr.rst
    vna.rst
    wspr.rst
    radiobox.rst
    radar.rst
    PyRPL.rst
    linien.rst
    Lock-in.rst
    dsp.rst
    lti.rst
    power_anal/power_anal.rst
    freq_res_anal/freq_res_anal.rst
    impedance_anal/impedance.rst
    multi_pulse_anal.rst
    ocra.rst
    epics.rst
    qt.rst
    tesla.rst

|

.. note::

    The code for some third-party applications available on the Red Pitaya marketplace can be found in the :rp-github:`Red Pitaya GitHub repository - deprecated applications <RedPitaya/tree/master/deprecated>`, under the `deprecated` directory. 
    However, not all applications are hosted there, and some may have their own separate repositories maintained by the original developers.

   The applications listed above are developed and maintained by third-party developers. For support, bug reports, or feature requests, please contact the respective application authors directly using the links provided on each application's documentation page.



















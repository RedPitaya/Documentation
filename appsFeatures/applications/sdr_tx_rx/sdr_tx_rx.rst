.. _sdr_tx_rx_apps:

SDR applications
################

.. note:: 

    The obsolete Red Pitaya SDR module was moved :ref:`here <sdr_module>`.

The Red Pitaya SDR applications allow you to use the Red Pitaya board as a Software Defined Radio. The following applications are available in the official Red Pitaya OS:

- SDR Transceiver compatible with HPSDR
- SDR Receiver compatible with HPSDR
- SDR Transceiver

The instructions in this section refer to operating the applications above on the official Red Pitaya OS.

.. note::
    
    The applications listed above are third-party applications, as they are ported directly from Pavel Demin's Alpine Linux image. Please note that we synchronise the applications with each official Red Pitaya OS release, so they may not reflect the latest community updates.
    For access to the latest community updates, please check the |red_pitaya_notes|.


.. |red_pitaya_notes| raw:: html

   <a href="https://github.com/pavel-demin/red-pitaya-notes" target="_blank">Pavel Demin's Red Pitaya Notes GitHub</a>


SDR Transceiver compatible with HPSDR
=====================================

The `High Performance Software Defined Radio <https://openhpsdr.org/>`_ (HPSDR) project is an open source hardware and software project that develops a modular Software Defined Radio (SDR) for use by radio amateurs and short wave listeners.

This version of the SDR transceiver makes it usable with the software developed by the HPSDR project and other SDR programs that support the HPSDR/Metis communication protocol.

This SDR transceiver emulates a HPSDR transceiver similar to Hermes with a network interface, two receivers and one transmitter.

The HPSDR/Metis communication protocol is described in the following documents:

- `Metis - How it works <https://raw.githubusercontent.com/TAPR/OpenHPSDR-SVN/master/Metis/Documentation/Metis-%20How%20it%20works_V1.33.pdf>`_
- `HPSDR - USB Data Protocol <https://github.com/TAPR/OpenHPSDR-SVN/raw/master/Documentation/USB_protocol_V1.58.doc>`_


Software
--------

The HPSDR compatible SDR transceiver should work with most programs that support the HPSDR/Metis communication protocol:

- `PowerSDR mRX PS <https://openhpsdr.org/wiki/index.php?title=PowerSDR>`_ which can be downloaded from this `link <https://github.com/TAPR/OpenHPSDR-PowerSDR/releases>`_.
- `QUISK <https://james.ahlstrom.name/quisk>`_ with the ``hermes/quisk_conf.py`` configuration file.
- `ghpsdr3-alex <https://napan.ca/ghpsdr3>`_ distributed client-server system.
- `openHPSDR Android application <https://play.google.com/store/apps/details?id=org.g0orx.openhpsdr>`_ described in more detail at `this link <https://g0orx.blogspot.be/2015/01/openhpsdr-android-application.html>`_.
- `Java desktop application <https://g0orx.blogspot.co.uk/2015/04/java-desktop-application-based-on.html>`_ based on the openHPSDR Android Application

.. note::

    Please note that the aforementioned programs are open-source third-party software that is not maintained by the Red Pitaya team. While these programs were previously working on Red Pitaya, the project developers may not be maintaining them anymore. For the most current information, please refer to the respective project pages.  


Getting started
---------------

To start the HPSDR compatible SDR transceiver open the application on the Red Pitaya web interface and connect to the Red Pitaya board using the HPSDR compatible software.


Configuring inputs and outputs
-------------------------------

The ``sdr-transceiver-hpsdr`` program running on the Red Pitaya board expects six command line arguments:

.. code-block:: bash

    sdr-transceiver-hpsdr 1 2 2 2 1 2

The first four arguments are for the receivers (RX1, RX2, RX3, RX4), where 1 corresponds to IN1 and 2 corresponds to IN2.

The last two arguments are for the outputs (OUT1, OUT2), where 1 corresponds to the TX signal and 2 corresponds to the envelope signal.

For example, to send the TX signal to OUT2, the corresponding line in start.sh should be edited and the last argument should be set to 1:

.. code-block:: bash

    sdr-transceiver-hpsdr 1 2 2 2 1 1

In the official Red Pitaya OS the start.sh script is located in:

- ``/opt/redpitaya/www/apps/sdr-transceiver-hpsdr`` directory on **STEMlab 125-14**.
- ``/opt/redpitaya/www/apps/sdr-transceiver-122-88`` directory on **SDRlab 122-16**.


More information
----------------

For more information on hardware connections, software configuration, and other details, please refer to the Red Pitaya Notes. Please select the appropriate version of the Red Pitaya board:

- `STEMlab 125-14 SDR transceiver HPSDR <https://pavel-demin.github.io/red-pitaya-notes/sdr-transceiver-hpsdr/>`_
- `SDRlab 122-16 SDR transceiver HPSDR <https://pavel-demin.github.io/red-pitaya-notes/sdr-transceiver-122-88/>`_


SDR Receiver compatible with HPSDR
=====================================

This version of the Red Pitaya SDR receiver emulates:

- **STEMlab 125-14**: a single `Hermes <https://openhpsdr.org/hermes.php>`_ module with eight receivers. It may be useful for projects that require eight receivers compatible with the programs that support the HPSDR/Metis communication protocol.
- **SDRlab 122-16**: two `Hermes <https://openhpsdr.org/hermes.php>`_ modules with eight receivers. It may be useful for projects that require sixteen receivers compatible with the programs that support the HPSDR/Metis communication protocol.

The HPSDR/Metis communication protocol is described in the following documents:

- `Metis - How it works <https://raw.githubusercontent.com/TAPR/OpenHPSDR-SVN/master/Metis/Documentation/Metis-%20How%20it%20works_V1.33.pdf>`_
- `HPSDR - USB Data Protocol <https://github.com/TAPR/OpenHPSDR-SVN/raw/master/Documentation/USB_protocol_V1.58.doc>`_

Software
--------

The HPSDR compatible SDR receiver should work with most programs that support the HPSDR/Metis communication protocol:

- `PowerSDR mRX PS <https://openhpsdr.org/wiki/index.php?title=PowerSDR>`_ which can be downloaded from this `link <https://github.com/TAPR/OpenHPSDR-PowerSDR/releases>`_.
- `QUISK <https://james.ahlstrom.name/quisk>`_ with the ``hermes/quisk_conf.py`` configuration file.
- `ghpsdr3-alex <https://napan.ca/ghpsdr3>`_ distributed client-server system.
- `openHPSDR Android application <https://play.google.com/store/apps/details?id=org.g0orx.openhpsdr>`_ described in more detail at `this link <https://g0orx.blogspot.be/2015/01/openhpsdr-android-application.html>`_.
- `Java desktop application <https://g0orx.blogspot.co.uk/2015/04/java-desktop-application-based-on.html>`_ based on the openHPSDR Android Application

.. note::

    Please note that the aforementioned programs are open-source third-party software that is not maintained by the Red Pitaya team. While these programs were previously working on Red Pitaya, the project developers may not be maintaining them anymore. For the most current information, please refer to the respective project pages.  


Getting started
---------------

To start the HPSDR compatible SDR receiver open the application on the Red Pitaya web interface and connect to the Red Pitaya board using the HPSDR compatible software.

To run a CW Skimmer Server and Revers Beacon Network Aggregator, see the links in the next chapter.


More information
----------------

For more information on hardware connections, software configuration, and other details, please refer to the Red Pitaya Notes. Please select the appropriate version of the Red Pitaya board:

- `STEMlab 125-14 SDR receiver HPSDR <https://pavel-demin.github.io/red-pitaya-notes/sdr-receiver-hpsdr/>`_
- `SDRlab 122-16 SDR receiver HPSDR <https://pavel-demin.github.io/red-pitaya-notes/sdr-receiver-hpsdr-122-88/>`_



SDR transceiver
===============

The SDR transceiver consists of two SDR receivers and of two SDR transmitters.

.. tabs::

    .. tab:: STEMlab 125-14

        The implementation of the SDR receivers is quite straightforward:

            - An antenna is connected to one of the high-impedance analog inputs.
            - The on-board ADC (125 MS/s sampling frequency, 14-bit resolution) digitizes the RF signal from the antenna.
            - The data coming from the ADC is processed by a in-phase/quadrature (I/Q) digital down-converter (DDC) running on the Red Pitaya's FPGA.

        The SDR receiver is described in more details at this link.

        The SDR transmitters consist of the similar blocks but arranged in an opposite order:

            - The I/Q data is processed by a digital up-converter (DUC) running on the Red Pitaya's FPGA.
            - The on-board DAC (125 MS/s sampling frequency, 14-bit resolution) outputs RF signal.
            - An antenna is connected to one of the analog outputs.

        The tunable frequency range covers from 0 Hz to 60 MHz.

        The I/Q data rate is configurable and five settings are available: 20, 50, 100, 250, 500 and 1250 kSPS.

    .. tab:: SDRlab 122-16

        The implementation of the SDR receivers is quite straightforward:

            - An antenna is connected to one of the high-impedance analog inputs.
            - The on-board ADC (122.88 MS/s sampling frequency, 16-bit resolution) digitizes the RF signal from the antenna.
            - The data coming from the ADC is processed by a in-phase/quadrature (I/Q) digital down-converter (DDC) running on the Red Pitaya's FPGA.

        The SDR transmitters consist of the similar blocks but arranged in an opposite order:

            - The I/Q data is processed by a digital up-converter (DUC) running on the Red Pitaya's FPGA.
            - The on-board DAC (122.88 MS/s sampling frequency, 14-bit resolution) outputs RF signal.
            - An antenna is connected to one of the analog outputs.

        The tunable frequency range covers from 0 Hz to 60 MHz.

        The I/Q data rate is configurable and five settings are available: 24, 48, 96, 192, 384, 768 and 1536 kSPS.


Getting started with GNU Radio
------------------------------

#. Connect an antenna to the IN1 connector on the Red Pitaya board.
#. Open the SDR Transceiver application on the Red Pitaya board.
#. Install `GNU Radio <https://www.gnuradio.org/>`_
#. Clone the source code repository:

    .. code-block:: bash

        git clone https://github.com/pavel-demin/red-pitaya-notes

#. Run `GNU Radio Companion <https://wiki.gnuradio.org/index.php/GNURadioCompanion>`_ and open AM transceiver flow graph:

    .. code-block:: bash
        
        cd red-pitaya-notes/projects/sdr_transceiver_122_88/gnuradio
        export GRC_BLOCKS_PATH=.
        gnuradio-companion trx_am.grc

Getting started with SDR# and HDSDR
-----------------------------------

#. Connect an antenna to the IN1 connector on the Red Pitaya board.
#. Open the SDR Transceiver application on the Red Pitaya board.
#. Download and install `SDR# <https://www.dropbox.com/sh/5fy49wae6xwxa8a/AAAdAcU238cppWziK4xPRIADa/sdr/sdrsharp_v1.0.0.1361_with_plugins.zip?dl=1>`_ or `HDSDR <https://www.hdsdr.de/>`_.
#. Download `pre-built ExtIO plug-in <https://www.dropbox.com/scl/fi/pl8gfjn2ay267or1zkohu/extio_red_pitaya.dll?rlkey=zhmv6qktymfeno8bdap94noq9&dl=1>`_ for SDR# and HDSDR.
#. Copy ``extio_red_pitaya.dll`` into the SDR# or HDSDR installation directory.
#. Start SDR# or HDSDR.
#. Select Red Pitaya from the Source list in SDR# or from the Options [F7] → Select Input menu in HDSDR.
#. Press Configure icon in SDR# or press SDR-Device [F8] button in HDSDR, then enter the IP address of the Red Pitaya board and set ADC sample rate to 122.88 MSPS.
#. Press Play icon in SDR# or press Start [F2] button in HDSDR.


More information
----------------

For more information on hardware connections, software configuration, and other details, please refer to the Red Pitaya Notes. Please select the appropriate version of the Red Pitaya board:

- `STEMlab 125-14 SDR transceiver <https://pavel-demin.github.io/red-pitaya-notes/sdr-transceiver/>`_
- `SDRlab 122-16 SDR transceiver <https://pavel-demin.github.io/red-pitaya-notes/sdr-transceiver-122-88/>`_


Author & Source
===============

.. admonition:: Credits

    | The original developer of the SDR applications for Red Pitaya in this section is Pavel Demin.
    | Repositories used by our builds:

        *   `Red Pitaya Notes <https://pavel-demin.github.io/red-pitaya-notes/>`_

Pavel Demin has developed several other SDR applications that are compatible with the Red Pitaya board. These applications are available in the Pavel Demin's Alpine Linux OS image.
For more information on these applications, please refer to the `Red Pitaya Notes <https://pavel-demin.github.io/red-pitaya-notes/>`_.

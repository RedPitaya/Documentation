################################
Marketplace and contributed apps
################################

********
Overview
********

More Red Pitaya applications can be obtained from the Red Pitaya marketplace that is
accessible through the Red Pitaya WEB interface or from other websites where Red
Pitaya community members share code or complete software packages that can be
installed and run-on Red Pitaya hardware platforms.
Notice that applications developed by the Red Pitaya community are not distributed or
tested by the Red Pitaya team and that our team doesn’t take any responsibilities about.
If you’d like to share feedback, report bugs or need help on contributed projects, apps
and software, we highly recommend contacting project authors.

.. toctree::
   :maxdepth: 2

   sdr.rst
   vna.rst
   PyRPL.rst
   Lock-in.rst
   dsp.rst
   pid.rst
   ocra.rst
   power_anal.rst
   freq_res_anal.rst



******************
Impedance analyzer
******************

The Impedance analyzer application enables measurements of
Impedance, Phase and other parameters of the selected DUT (Device Under Test).
Measurements can be performed in the **Frequency sweep** mode
with 1Hz frequency resolution or in the **Measurements sweep** mode
with the desired number of measurements at constant frequency.
The selectable frequency range is from 1Hz to 60MHz,
although the recommended frequency range is up to 1MHz.
The impedance range is from 0.1 Ohm to 10 Mohm.
When using the Impedance analyzer application with the LCR Extension module,
insert 0 in the shunt resistor field.

.. figure:: LCR_2.png

Impedance analyzer application enables measurements of Impedance,
Phase and other parameters of selected DUT (Device Under Test).
Measurements can be performed in *Frequency sweep* mode
with 1Hz of frequency resolution or in *Measurements sweep* mode
with desired numbers of measurement at constant frequency.
Selectable frequency range is from 1Hz to 60MHz,
although the recommended frequency range is up to 1MHz*.
Impedance range is from 0.1 Ohm – 10 MOhm*.
When using Impedance analyzer application with LCR Extension module
insert 0 in the shunt resistor field.

.. note::

   Impedance range is dependent on the selected frequency and maximum accuracy
   and suitable measurement can not be performed at all frequencies and impedance ranges.
   Impedance range is given in picture bellow. Range for Capacitors or Inductors
   can be extrapolated from given picture. Basic accuracy of the Impedance analyzer is 5%.
   Impedance analyzer application is calibrated for 1 m Kelvin probes.
   More accurate measurements can be performed in Measurement sweep at constant frequency.

.. figure:: LCR_range.png

When using Impedance analyzer application optimal results are achieved wheni
the Red Pitaya GND is connected to your mains EARTH lead as is shown below.
We also recommend shielding of Red Pitaya and LCR extension module.

.. figure:: 600px-E_module_connection.png

On pictures below are shown comparison measurements of the selected DUT.
Measurements are taken with Red Pitaya and Keysight precision LCR meter.
From this plots you can extract basic Red Pitaya accuracy.

.. note::

    Red Pitaya LCR meter/Impedance analyzer are not certificated for certain accuracy or range.

.. figure:: 300px-LCR_100R.png
.. figure:: 300px-LCR_100K.png
.. figure:: 300px-LCR_1M.png

Impedance analyzer application can be used without LCR Extension module
using manual setting of shunt resistor. This option is described below.

.. note::

   You will need to change ``C_cable`` parameter in the code when using your setup.

.. figure:: 600px-Impedance_analyzer_manaul_R_Shunt.png

.. note::

   Impedance analyzer application is available on Red Pitaya marketplace.

*****************
LTI DSP Workbench
*****************

This application will model a physical system,
turning the Red Pitaya board into almost any linear system
that can be included into a measuring and control circuitry.
The modeling of the physical system is done by simulating
the system H(z) transfer function with the Red Pitaya board.
In the application there are some predefined H(z) functions
which will help you describe/simulate the desired system.
Changing the parameters of the H(z) transfer function
is done quickly through the application’s web interface.

More about this application can be fund here:

   http://blog.redpitaya.com/physical-system-modelling/

.. note::

   LTI DSP workbench application is available on Red Pitaya marketplace.

*****************************************************
Multichannel Pulse Height Analyzer – (by Pavel Demin)
*****************************************************

The Multichannel Pulse Height Analyzer (MCPHA) is an instrument used for the analysis of electrical signals
in the form of pulses of varying heights which may come from different sensors and similar.
The pulse signals are acquired where the number of pulses
of each height is saved and the histogram plot is given
where the X axis represents the pulses’ amplitude,
and the Y axis represents the number of pulses.
With the Red Pitaya board, you can acquire pulses
whose period can be in the range from 1us to 1s.

More about this application can be found here:

   http://pavel-demin.github.io/red-pitaya-notes/mcpha/


*****************************************************
Multiband WSPR transceiver – (by Pavel Demin)
*****************************************************

WSPR implements a protocol designed for probing potential propagation paths
with low-power transmissions.

You can find more about the WSPR transceiver software on the link:

   http://pavel-demin.github.io/red-pitaya-notes/


****************************
RadioBox - (by Urlich Habel)
****************************

The RadioBox is a complete transmitter and receiver done in the FPGA.
You can directly connect an antenna at the SMA RF In 2 port for receiving.
At the SMA RF Out 2 port you can listen to the demodulated signal.
The transmitter does it at the same time on the SMA In/Out 1 connectors.
When an external SDR-software is desired, you can select the Linux AC97 sound driver
as stereo channels in both directions to feed the FPGA or to grab the data streams.
To connect a SDR you can set the two AC97 channels to the I- and Q-signals of the QMIXers modulation.

More details about the project can be found at the Wiki of RadioBox at the following link: 

   https://github.com/DF4IAH/RedPitaya_RadioBox/wiki

.. note::

   RadioBox application is available on Red Pitaya marketplace.

****************************
Open source Red Pitaya Radar
****************************

Radar using Red Pitaya for RF and Raspberry Pi 3 / 4 for quad-core signal processing. Initially
used for ionospheric imaging at HF but via frequency translation could be used at microwave
and other frequencies.

More about PiRadar can be found here:

   https://www.scivision.dev/open-source-radar/

   https://github.com/space-physics/piradar


*********************************************
EPICS driver for Red Pitaya (by Andraz Pozar)
*********************************************

EPICS driver support for Red Pitaya based on asynPortDriver. This module is to be run on the
Red Pitaya itself.

More about EPICS driver can be found here:

   https://github.com/AustralianSynchrotron/redpitaya-epics

****************************************************
Qt GUI application on Red Pitaya (by Primoz Beltram)
****************************************************

Purpose of this project is to demonstrate usage of Qt GUI application on Red Piatya Zynq based
system. Such system becomes standalone, portable, battery power-supply system.

More information can be found here:

   https://github.com/pbeltram/redpitaya_gui


**********
Teslameter
**********

EMC or electromagnetic compatibility is the property of the equipment
telling us about the devices' emission of unwanted electromagnetic energy
and how they behave in an interfered environment.
It also tells us what effects the emitted energy induces.
This application is used for measuring the magnetic field
that is part of unintended or unwanted electromagnetic emissions.
When using this application, an additional front-end is needed
where the application (trough gain parameters) can be adjusted to the users of front-ends.

More about this application can be found here:

   https://dl.dropboxusercontent.com/s/6akk0nzebsa93u6/EMC%26Teslameter_doc.pdf







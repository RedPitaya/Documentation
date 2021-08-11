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

#######################
Fast analog IO (Gen 2)
#######################

.. note::

    **This page is currently under construction.** All relevant information will be added before the official Gen 2 release.
    Please check back later for updates.

.. contents:: **Index**
   :local:
   :backlinks: none

|

.. warning::

    All inputs and outputs available through SMA connectors share a common ground connected to the power supply ground.


*************************
Analog inputs
*************************



General Specifications
=======================



Jumpers
----------



Jumper orientation
----------------------

The position of the jumpers can affect the measurements taken by the Red Pitaya. The jumpers are internally connected to a small metal plate which acts as a capacitor and affects the overall capacitance which in turn affects the input impedance.
If the jumpers are moved from an incorrect to a correct position, calibration is strongly recommended as the input capacitance depends on jumper settings and may vary between positions.


1. The position of the jumper bumps must be as shown in the diagram. Due to the non-symmetrical nature of the jumpers and their latches, we advise installing them with the latch on the outer side to avoid any issues with difficult-to-remove jumpers.

    .. figure:: img/jumpers/Jumper_position_Note.png


2. Once installed, the jumper should be positioned so that the metal part is not visible. Please refer to the example on the STEMlab 125-14 4 input for guidance.

    .. figure:: img/jumpers/Jumper_position_4IN_0.png
        :align: center
        :width: 700 px

    .. figure:: img/jumpers/Jumper_position_4IN_1.png
        :align: center
        :width: 700 px

Incorrect jumper placement can cause the front part of the acquired square wave signals to be overshot or undercut. This is shown in the figure below.

.. figure:: img/jumpers/Jumper_position_wrong_signal.jpg
    :width: 800

    As can be seen, **if the jumpers are not set correctly, the step response will be under-compensated.**.

With the jumper pins correctly placed, the same waveform looks much better.

.. figure:: img/jumpers/Jumper_position_correct_signal.jpg
    :width: 800







Analog inputs calibration
============================



****************
Analog outputs
****************



Analog output calibration
==========================



.. note::

    The information provided by Red Pitaya d.o.o. is believed to be accurate and reliable. However, no liability is accepted for its use. Please note that the contents may be subject to change without prior notice. 




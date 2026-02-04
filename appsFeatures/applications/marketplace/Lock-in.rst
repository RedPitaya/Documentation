.. _lockInPID_app:

*******************************
Lock-in + PID (by Marcelo Luda)
*******************************

**Lock-in+PID** is an application for the Red Pitaya STEMlab 125-14 board that implements an Oscilloscope application and a Lock-in amplifier. It's based on |release 0.95 scope|.

A Proportional-Integral-derivative controller (PID controller) is a control loop feedback mechanism (controller) commonly used in industrial control systems. 
A PID controller continuously calculates an error value as the difference between a desired set point and a measured process variable and applies a correction based on proportional, 
integral, and derivative terms (sometimes denoted P, I, and D), which give their name to the controller type. The MIMO PID controller consists of four standard PID controllers with 
P, I, and D parameter settings and integrator reset control. The output of each controller is summed with the output of the arbitrary signal generator. 

More about this project can be found here:

- |Lock-in + PID|

.. note::

   The Lock-in + PID application is available on the Red Pitaya marketplace.
   
   
.. |release 0.95 scope| raw:: html
 
   <a href="https://github.com/RedPitaya/RedPitaya/tree/release-v0.95/apps-free/scope" target="_blank">relese 0.95 of the scope application</a>
    
.. |Lock-in + PID| raw:: html
 
   <a href="https://github.com/marceluda/rp_lock-in_pid/tree/gh-pages" target="_blank">Lock-in + PID</a>

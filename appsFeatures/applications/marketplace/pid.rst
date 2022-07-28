**************
PID controller
**************

A proportional–integral–derivative controller (PID controller) is a control loop feedback mechanism (controller) commonly used in industrial control systems. A PID controller continuously calculates an error value as the difference between a desired set point and a measured process variable and applies a correction based on proportional, integral, and derivative terms (sometimes denoted P, I, and D), which give their name to the controller type. The MIMO PID controller consists of four standard PID controllers with P, I, and D parameter settings and integrator reset control. The output of each controller is summed with the output of the arbitrary signal generator. The PID can be controlled through FPGA registers that are described inside the PID controller section of the FPGA register map.

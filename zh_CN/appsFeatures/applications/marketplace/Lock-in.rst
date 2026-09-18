.. _lockInPID_app:

****************************************
Lock-in + PID（Marcelo Luda 开发）
****************************************

**Lock-in+PID** 是一款面向 Red Pitaya STEMlab 125-14 板卡的应用，实现了示波器和锁相放大器功能。它基于 |release 0.95 scope|。

比例—积分—微分控制器（PID 控制器）是工业控制系统中常用的控制环路反馈机制（控制器）。
PID 控制器持续计算期望设定值与测得过程变量之间的差值，并根据比例、积分和微分项（有时记为 P、I 和 D）进行校正，该类控制器也因此得名。
MIMO PID 控制器由四个标准 PID 控制器组成，提供 P、I、D 参数设置和积分器复位控制。每个控制器的输出与任意信号发生器的输出相加。

有关此项目的更多信息见此：

- |Lock-in + PID|

.. note::

   Lock-in + PID 应用可在 Red Pitaya Marketplace 中获取。
   
   
.. |release 0.95 scope| raw:: html
 
   <a href="https://github.com/RedPitaya/RedPitaya/tree/release-v0.95/apps-free/scope" target="_blank">示波器应用 release 0.95</a>
    
.. |Lock-in + PID| raw:: html
 
   <a href="https://github.com/marceluda/rp_lock-in_pid/tree/gh-pages" target="_blank">Lock-in + PID</a>

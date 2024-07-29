.. _can_example:

CAN (HW api)
######################

Description
============

This example demonstrates communication using the Red Pitaya CAN interface. The code below sends CAN frames between CAN0 and CAN1 interface.

- CAN0 - TX == DIO7_N, RX == DIO7_P
- CAN1 - TX == DIO6_N, RX == DIO6_P

  
Required hardware
==================

    - Red Pitaya
    - 2x CAN controllers

.. figure:: ../general_img/RedPitaya_general.png

  
SCPI Code Examples
====================

.. note::

  This code is written for **2.00-35 or higher OS**. For older OS versions, please check when specific commands were released (a note is added to each command introduced in 2.00 or higher verisons).


Code - MATLAB®
---------------

The code is written in MATLAB. In the code, we use SCPI commands and TCP client communication. Copy the code from below into the MATLAB editor, save the project, and hit the "Run" button.

**Coming soon**
.. .. code-block:: matlab
    


Code - Python
---------------

.. **Using just SCPI commands:**

**Coming soon**

.. .. code-block:: python


.. note::

    The Python functions are accessible with the latest version of the |redpitaya_scpi| document available on our GitHub.
    The functions represent a quality-of-life improvement as they combine the SCPI commands in an optimal order and also check for improper user inputs. The code should function at approximately the same speed without them.

    For further information on functions please consult the |redpitaya_scpi| code.

.. |redpitaya_scpi| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>


API Code Examples
====================

.. note::

    The API code examples don't require the use of the SCPI server. Instead, the code should be compiled and executed on the Red Pitaya itself (inside Linux OS).
    Instructions on how to compile the code and other useful information are :ref:`here <comC>`.


Code - C++
-------------

.. note::

    Although the C++ code examples don't require the use of the SCPI server, we have included them here to demonstrate how the same functionality can be achieved with different programming languages. 
    Instructions on how to compile the code are :ref:`here <comC>`.


.. .. code-block:: cpp


Code - Python API
-------------------

.. .. code-block:: python

   
    


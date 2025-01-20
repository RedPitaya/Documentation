.. _pyrpl:

#######################
PyPRL
#######################

The application is based on the `official PyRPL GitHub repository <https://github.com/pyrpl-fpga/pyrpl>`_ developed by Leonard Neuhaus

For more information, see the `official documentation <https://pyrpl.readthedocs.io/en/latest/>`


What do I need before I start?
==============================

1. PyPRL application requirements:

    -   Windows, MacOS (arm64 for pre-built app) or Linux-based personal computer (PC).

2. The application is designed for Red Pitaya board models:

    -   **STEMlab 125-14**
    -   **STEMlab 125-14 Low Noise**
    -   **STEMlab 125-14 Z7020**
    -   **STEMlab 125-10 (DISCONTINUED)** (not confirmed but should work)

..  note::

    The PyRPL will not work on **SDRlab 122-16** and **SIGNALlab 250-12** without modifications to the source code. The neccessary changes include:
    
    - modification to the FPGA code to make it compatible with the specific board (change in the xdc files).
    - changes in the software to recognize the board model and load the correct FPGA image.

    PyRPL is incompatible with **STEMlab 125-14 4-Input** board model.


Install & run PyRPL
===================

There are two ways to run the application:

    -   Download the `pre-built application <https://downloads.redpitaya.com/downloads/Clients/pyrpl/>`_ for the appropriate platform
    -   Run source code from the repository: `rp_pyrpl_github <https://github.com/RedPitaya/pyrpl>`_


.. note::

    We recommend using the precompiled application from the link above on Red Pitaya OS versions 2.00 and above. Running the source code from the repository currently requires a special setup as it is designed to work with Python 3.6, which is outdated.
    The community is working on updating the application to work with Python 3.10 and above. The latest information can be found on the `official PyRPL GitHub repository <https://github.com/pyrpl-fpga/pyrpl>`_

Here is a link to a demonstration video by Leonard Neuhaus: |pyrpl_video|

.. |pyrpl_video| raw:: html

    <a href="https://www.youtube.com/watch?v=WnFkz1adhgs" target="_blank">PyRPL video</a>


Author & Source
===============

.. admonition:: Credits

    | The original developer of the PyRPL application for Red Pitaya is Leonard Neuhaus.
    | Repositories used by our builds:

        *   `Red Pitaya Notes <https://pavel-demin.github.io/red-pitaya-notes/>`_

Pavel Demin has developed several other SDR applications that are compatible with the Red Pitaya board. These applications are available in the Pavel Demin's Alpine Linux OS image.
For more information on these applications, please refer to the `Red Pitaya Notes <https://pavel-demin.github.io/red-pitaya-notes/>`_.


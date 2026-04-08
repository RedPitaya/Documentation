.. _pyrpl:

#######################
PyPRL
#######################

The application is based on the `official PyRPL GitHub repository <https://github.com/pyrpl-fpga/pyrpl>`_ developed by Leonard Neuhaus

For more information, see the `official documentation <https://pyrpl.readthedocs.io/en/latest/>`_.


What do I need before I start?
==============================

1.  PyPRL application requirements:

    * Windows, MacOS (arm64 for pre-built app) or Linux-based personal computer (PC).

#.  The application is designed for Red Pitaya board models:

    * **STEMlab 125-14 Gen 2 boards**
    * **STEMlab 125-14 Original Gen boards** (with exception of 4-Input)
    * **STEMlab 125-10 (discontinued)** (not confirmed but should work)

..  note::

    PyRPL will not work on **SDRlab 122-16**, **SIGNALlab 250-12** and **STEMlab 125-14 4-Input**.


Compatibility
===================

Here is a summary of the compatibility of the PyRPL application with different Red Pitaya board models and OS versions:

+-----------------------------+----------------------------------------+----------------------------------------+
|                             | "Official" Version                     | Community Version                      |
+=============================+========================================+========================================+
| Board Model                 | | STEMlab 125-14 Gen 2 boards          | | STEMlab 125-14 Original Gen boards   |
|                             | | STEMlab 125-14 Original Gen boards   |                                        |
+-----------------------------+----------------------------------------+----------------------------------------+
| OS Version                  | OS 2.00 or higher                      | OS 2.00 or higher                      |
+-----------------------------+----------------------------------------+----------------------------------------+
| Features                    | | Compiled clients for 3.00 OS         | | May not work on 2.00 OS              |
|                             | | Clients backwards compatible         | |                                      |
|                             | | Some features not up to date         |                                        |
+-----------------------------+----------------------------------------+----------------------------------------+

.. note::

    We recommend using the latest **community version** as it is continuously improving. Howerver, as of currently, the community version does not yet support:

    * Gen 2 boards

    The community version is being actively developed and these features are expected to be added in the near future.


Install & run PyRPL
===================

There are multiple ways to run the application:

1. Download the `pre-built application <https://downloads.redpitaya.com/downloads/Clients/pyrpl/>`_ for the appropriate platform (updated and compiled by the Red Pitaya team).
#. Run source code from the repository: :rp-github:`Red Pitaya PyRPL GitHub <pyrpl>` (version we use for the compiled application)
#. Use the community version of the application |PyRPL|


Here is a link to a demonstration video by Leonard Neuhaus: |pyrpl_video|

.. |pyrpl_video| raw:: html

    <a href="https://www.youtube.com/watch?v=WnFkz1adhgs" target="_blank">PyRPL video</a>




Author & Source
===============

.. admonition:: Credits

    | The original developer of the PyRPL application for Red Pitaya is Leonard Neuhaus. The repository is currently maintained by the PyRPL community lead by *michaelcroquette* and *peteasa*.
    | Repositories used by our builds:

        * `PyRPL GitHub <https://github.com/pyrpl-fpga/pyrpl>`_

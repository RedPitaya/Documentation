.. _programming:

####################################
Programming and remote-control tools
####################################

Control your Red Pitaya remotely from your PC or develop custom applications that run directly on the board. This section provides documentation for programmers, researchers, and engineers who need automated control, custom signal processing, or integration into larger systems.

**Available approaches:**

* **SCPI Server** - Remote control from MATLAB, LabVIEW, or Python using industry-standard commands over TCP/IP. No on-board programming required.
* **C++ and Python API** - Develop applications that run directly on Red Pitaya's Linux OS for maximum performance and real-time processing.
* **JupyterLab** - Interactive Python environment for prototyping and analysis with notebook-style documentation.
* **Deep Memory Mode** - Acquire and generate signals using the full DDR3 RAM (up to 512 MB) at full sampling rates.

**Support resources:**

* Complete command reference for SCPI and API commands with OS version compatibility
* Ready-to-run code examples covering signal acquisition, generation, I/O control, and communication interfaces
* Known issues and changes by OS version for troubleshooting

.. toctree::
    :maxdepth: 1

    scpi
    API_scripts
    jupyter/Jupyter
    deepMemoryMode
    command_list
    examples_top
    knownIssues

.. _cpp_make_install:

######################################
C++ Compiler and Make Utility Setup
######################################

This guide covers installing the C++ compiler (MinGW-w64) and make utility on Windows using Chocolatey package manager. These tools are essential for:

- Compiling C++ examples from the Red Pitaya streaming library
- Building C/C++ applications for Red Pitaya
- Running Makefiles for automated build processes
- FPGA project generation and builds

.. note::

    **Linux/macOS users:** These tools are typically pre-installed or available through your system's package manager (``apt``, ``yum``, ``brew``). This guide focuses on Windows installation.

|

Prerequisites
=============

- Windows 10/11 with administrator access
- PowerShell or Windows Command Prompt

|

Installing Chocolatey Package Manager
======================================

Chocolatey is a package manager for Windows that simplifies software installation via command line.

Official installation guide: |Chocolatey-Install|

Quick installation:

1.  Open PowerShell as **Administrator** (right-click PowerShell → "Run as administrator")

2.  Run the installation command:

    .. code-block:: powershell

        Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

3.  Wait for the installation to complete. You should see a success message.

4.  Verify installation:

    .. code-block:: powershell

        choco --version

    You should see the Chocolatey version number (e.g., ``2.3.0``).

.. note::

    After Chocolatey installation, you may need to close and reopen PowerShell for the ``choco`` command to be recognized.

|

Installing MinGW-w64 (C++ Compiler)
====================================

MinGW-w64 provides the GCC compiler suite for Windows, including ``g++`` for C++ compilation.

Installation via Chocolatey:

.. code-block:: powershell

    choco install mingw -y

This installs:

- ``gcc`` - C compiler
- ``g++`` - C++ compiler  
- ``gdb`` - GNU debugger
- Standard C/C++ libraries and headers

**Verify installation:**

.. code-block:: powershell

    g++ --version

You should see output similar to:

.. code-block:: none

    g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders) 14.2.0
    Copyright (C) 2024 Free Software Foundation, Inc.

**Test compilation:**

Create a simple test file ``test.cpp``:

.. code-block:: cpp

    #include <iostream>
    int main() {
        std::cout << "C++ compiler works!" << std::endl;
        return 0;
    }

Compile and run:

.. code-block:: powershell

    g++ test.cpp -o test.exe
    .\test.exe

You should see ``C++ compiler works!`` printed to the console.

|

Installing Make Utility
========================

The ``make`` utility automates build processes by reading Makefiles that define compilation rules and dependencies.

Installation via Chocolatey:

.. code-block:: powershell

    choco install make -y

**Verify installation:**

.. code-block:: powershell

    make --version

You should see output similar to:

.. code-block:: none

    GNU Make 4.4.1
    Built for Windows32
    Copyright (C) 1988-2023 Free Software Foundation, Inc.

**Test make:**

Create a simple ``Makefile``:

.. code-block:: makefile

    hello:
    	@echo "Make utility works!"

Run:

.. code-block:: powershell

    make hello

You should see ``Make utility works!`` printed to the console.

.. note::

    Makefiles require **TAB characters** for indentation, not spaces. Make sure your text editor is configured to use tabs when editing Makefiles.

|

Environment Variables
=====================

Chocolatey automatically adds the installed tools to your system PATH during installation. If the commands are not recognized:

1.  Close and reopen your terminal/PowerShell
2.  Check that the installation directories are in PATH:

    .. code-block:: powershell

        $env:PATH -split ';' | Select-String -Pattern 'mingw|make'

3.  If still not working, log out and log back in to Windows

|

Using the Tools
===============

Compiling Red Pitaya Streaming Examples
----------------------------------------

The Red Pitaya C++ streaming examples can now be compiled:

.. code-block:: powershell

    # Navigate to examples directory
    cd C:\path\to\RedPitaya-Examples\C\API_Examples\Streaming

    # Compile an example
    g++ -std=c++20 -o stream_adc_1.exe stream_adc_1.cpp -I..\..\..\include -L..\..\..\lib -lrp-streaming


Building with Makefiles
-----------------------

For projects with Makefiles:

.. code-block:: powershell

    # Build project
    make

    # Clean build artifacts
    make clean

    # Build specific target
    make target_name


FPGA Project Generation
-----------------------

For FPGA development (see :ref:`FPGA Getting Started <fpga_top>`), the make utility is used to generate Vivado projects:

.. code-block:: powershell

    # Generate FPGA project
    cd C:\path\to\RedPitaya\fpga\prj\v0.94
    make project

|

Alternative Installation Methods
=================================

Manual MinGW-w64 Installation
------------------------------

If you prefer not to use Chocolatey:

#. Download MinGW-w64 from: |MinGW-Download|
#. Run the installer and follow the setup wizard
#. Manually add the ``bin`` directory to your system PATH:
   
   - Right-click "This PC" → Properties → Advanced system settings
   - Click "Environment Variables"
   - Edit the "Path" variable under "System variables"
   - Add the MinGW-w64 ``bin`` directory (e.g., ``C:\mingw64\bin``)


Manual Make Installation
------------------------

If you prefer not to use Chocolatey:

#. Download Make from: |Make-Download|
#. Extract to a location like ``C:\Program Files\Make``
#. Add the directory to your system PATH (see steps above)

|

Troubleshooting
===============

Command not found after installation
-------------------------------------

#.  Close and reopen your terminal/PowerShell
#.  Verify PATH includes the tool directories:

    .. code-block:: powershell

        $env:PATH

#.  Log out and log back in to Windows
#.  Reboot if the issue persists


Compilation errors with streaming library
------------------------------------------

Ensure you have:

#. Downloaded the complete Red Pitaya streaming client package
#. The streaming library files (``rp-streaming.dll``, headers) are accessible
#. Correct include paths (``-I``) and library paths (``-L``) in your compile command


Make complains about missing separator
---------------------------------------

This usually means spaces are used instead of tabs in the Makefile. Configure your editor to use tabs for indentation in Makefiles.


Chocolatey installation fails
------------------------------

#. Ensure you're running PowerShell as Administrator
#. Check your internet connection
#. Try running the installation command again
#. Check if antivirus software is blocking the installation

|

Related Documentation
=====================

- :ref:`WSL Setup <wsl_setup>` - Alternative Linux environment on Windows
- :ref:`FPGA Getting Started <fpga_top>` - Using make for FPGA project generation  
- :ref:`Streaming Examples <examples_streaming>` - C++ streaming API examples

.. |Chocolatey-Install| raw:: html

    <a href="https://chocolatey.org/install" target="_blank">Chocolatey Installation Guide</a>

.. |MinGW-Download| raw:: html

    <a href="https://www.mingw-w64.org/downloads/" target="_blank">MinGW-w64 Downloads</a>

.. |Make-Download| raw:: html

    <a href="https://gnuwin32.sourceforge.net/packages/make.htm" target="_blank">GNU Make for Windows</a>

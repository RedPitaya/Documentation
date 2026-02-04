.. _wsl_setup:

##################################
Windows Subsystem for Linux Setup
##################################

The Windows Subsystem for Linux (WSL) provides a Linux environment directly on Windows, which is useful for Red Pitaya development tasks such as:

- Accessing the serial console with ``minicom``
- Building and compiling software
- Running Linux-based development tools
- Accessing USB devices (including the Red Pitaya SD card)

This guide covers installing WSL, configuring it for optimal performance, and setting up USB device access.

Prerequisites
=============

- Windows 10 version 2004 and higher (Build 19041 and higher) or Windows 11
- Administrator access to your Windows system

Basic WSL Installation
======================

Microsoft provides comprehensive installation instructions. We recommend installing the latest available Ubuntu LTS version.

- |WSL| - Official Microsoft WSL installation guide

Quick installation (recommended):

1.  Open PowerShell or Windows Command Prompt as **Administrator**
2.  Run the installation command:

    .. code-block:: powershell

        wsl --install

3.  Restart your computer when prompted
4.  After restart, a Linux terminal will open to complete the Ubuntu setup
5.  Create a username and password for your Linux environment

.. note::

    The default WSL installation uses WSL 2, which provides better performance and full system call compatibility.


USB Device Access Setup
========================

To connect USB devices (like the Red Pitaya's serial console or SD card reader) to WSL, you need to install ``usbipd-win``.

- |WSL-USB| - Official Microsoft USB device connection guide

Installing ``usbipd-win``
-------------------------

1.  Open PowerShell or Windows Command Prompt as **Administrator**
2.  Install using ``winget``:

    .. code-block:: powershell

        winget install usbipd

Alternatively, download and install from the |usbipd-releases| page.

Installing Linux tools
----------------------

In your WSL terminal, install the required Linux tools:

.. code-block:: bash

    sudo apt update
    sudo apt install linux-tools-generic hwdata minicom
    sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20


WSL Configuration (.wslconfig)
==============================

To optimize WSL for Red Pitaya development, especially for USB device access, you should configure WSL settings using a ``.wslconfig`` file.

Creating the .wslconfig file
-----------------------------

The ``.wslconfig`` file should be placed in your Windows user directory: ``C:\Users\<YourUsername>\.wslconfig``

.. note::

    This file affects **all** WSL 2 distributions running on your machine.

Recommended configuration
-------------------------

Create or edit ``C:\Users\<YourUsername>\.wslconfig`` with the following content:

.. code-block:: ini

    [wsl2]
    dnsTunneling=true
    networkingMode=mirrored

Configuration explanation:

- **dnsTunneling=true** - Improves DNS resolution by tunneling DNS queries through Windows. This helps resolve network connectivity issues.
- **networkingMode=mirrored** - Mirrors the network interfaces from Windows to WSL, providing better network compatibility and allowing WSL to access devices on the local network more easily. This is particularly useful for USB device passthrough and accessing the Red Pitaya over the network.

.. important::

    After creating or modifying the ``.wslconfig`` file, you must restart WSL for the changes to take effect:

    .. code-block:: powershell

        wsl --shutdown

    Then restart your WSL distribution normally.


Additional configuration options
--------------------------------

You can add additional settings to optimize WSL for your needs. Here are some common options:

.. code-block:: ini

    [wsl2]
    dnsTunneling=true
    networkingMode=mirrored
    
    # Memory allocation (default is 50% of total RAM)
    memory=8GB
    
    # Number of processors (default is all processors)
    processors=4
    
    # Swap space
    swap=4GB
    
    # Enable nested virtualization (for running VMs in WSL)
    nestedVirtualization=true

For a complete list of configuration options, see the |WSL-config| page.


Verifying the installation
===========================

To verify that WSL is installed correctly:

1.  Open a PowerShell or Windows Command Prompt window
2.  Run:

    .. code-block:: powershell

        wsl --list --verbose

    You should see your installed Linux distribution with version 2:

    .. code-block:: none

        NAME            STATE           VERSION
        * Ubuntu        Running         2

3.  Start WSL:

    .. code-block:: powershell

        wsl

4. You should now be in a Linux terminal where you can run Linux commands.


Next steps
==========

Now that WSL is set up, you can:

- Use it to access the :ref:`Red Pitaya serial console <console>`
- Install development tools for building Red Pitaya software
- Access the Red Pitaya SD card contents from your Windows machine


Troubleshooting
===============

WSL is not starting
-------------------

1.  Make sure virtualization is enabled in your BIOS/UEFI
2.  Check that the Windows Hypervisor Platform is enabled:

    - Open "Turn Windows features on or off"
    - Enable "Virtual Machine Platform" and "Windows Subsystem for Linux"
    - Restart your computer

USB device not appearing in WSL
--------------------------------

1. Make sure the device is bound and attached using ``usbipd``
2. Check that the Linux tools are installed correctly in WSL
3. Verify the .wslconfig settings are applied (restart WSL after changes)

Network connectivity issues
---------------------------

1. Check your .wslconfig file has ``dnsTunneling=true`` and ``networkingMode=mirrored``
2. Restart WSL with ``wsl --shutdown`` and start it again
3. In WSL, try updating DNS settings in ``/etc/resolv.conf``


.. |WSL| raw:: html

    <a href="https://learn.microsoft.com/en-us/windows/wsl/install" target="_blank">Windows Subsystem for Linux Installation Guide</a>

.. |WSL-USB| raw:: html

    <a href="https://learn.microsoft.com/en-us/windows/wsl/connect-usb" target="_blank">Connect USB devices to WSL</a>

.. |WSL-config| raw:: html

    <a href="https://learn.microsoft.com/en-us/windows/wsl/wsl-config" target="_blank">WSL Configuration Documentation</a>

.. |usbipd-releases| raw:: html

    <a href="https://github.com/dorssel/usbipd-win/releases" target="_blank">usbipd-win releases</a>

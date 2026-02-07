.. _sw_dev_intro:

##################################################
Introduction to Red Pitaya Software Development
##################################################

1. Understanding Red Pitaya Software Architecture
==================================================

Red Pitaya runs a complete Linux operating system (based on Debian) on its ARM Cortex-A9 processor. The software stack consists of:

* **Linux Kernel** - Modified kernel with custom drivers for FPGA communication and peripherals
* **System Libraries** - Standard Linux libraries plus Red Pitaya-specific APIs
* **Applications** - Web-based applications, command-line tools, and background services
* **FPGA Interface** - Drivers and APIs for communicating with the FPGA hardware

This architecture allows you to:

* Develop standard Linux applications
* Create custom APIs and drivers
* Build web-based user interfaces
* Integrate with existing Linux tools and frameworks

|

2. Development Approaches
==========================

Application Development
-----------------------

Develop applications that run on Red Pitaya using the provided APIs:

* **C/C++ API** - Native performance, direct hardware access
* **Python API** - Rapid prototyping, easier development
* **Web Applications** - Browser-based user interfaces
* **Streaming Applications** - High-speed data transfer to PC

**Best for:** Creating custom measurement tools, automation scripts, data acquisition applications

System Development
------------------

Modify or rebuild the Red Pitaya operating system and ecosystem:

* **Ecosystem Building** - Compile the entire Red Pitaya OS from source
* **Debian Packages** - Create installable software packages
* **Custom Images** - Build modified OS images for deployment

**Best for:** Custom OS configurations, system integrations, production deployments

Configuration & Integration
---------------------------

Configure and extend Red Pitaya's capabilities:

* **Network Configuration** - Wi-Fi, Ethernet, custom network setups
* **Peripheral Integration** - GPIO, SPI, I2C interfaces
* **Hardware Add-ons** - TFT displays, custom hardware
* **Remote Deployment** - Automated software updates and management

**Best for:** System administration, hardware integration, deployment automation

|

3. Development Workflow
========================

Typical Application Development
--------------------------------

1. **Access Red Pitaya** - Connect via SSH or serial console
2. **Choose Your API** - C for performance, Python for ease
3. **Develop & Test** - Write code, test on device
4. **Deploy** - Copy to Red Pitaya or build into package

Typical System Development
---------------------------

1. **Set Up Build Environment** - Clone repositories, install dependencies
2. **Modify Components** - Change ecosystem, applications, or kernel
3. **Build** - Compile the modified components
4. **Test** - Deploy to Red Pitaya and verify
5. **Package** - Create Debian packages or SD card images

|

4. Prerequisites
=================

**For Application Development:**

* Basic Linux command line knowledge
* Programming experience (C, C++, or Python)
* Understanding of signal processing concepts
* SSH client for remote access

**For System Development:**

* Advanced Linux knowledge
* Experience with build systems (Make, CMake)
* Understanding of Debian package management
* Cross-compilation experience helpful

|

5. Getting Help
================

* **API Documentation** - Refer to C/Python API guides for function references
* **Examples** - Study example code in the Applications & Features section
* **Known Issues** - Check troubleshooting section for common problems
* **Community** - Red Pitaya forum for community support

|

6. Next Steps
==============

* **New to Red Pitaya?** Start with Getting Started → Console Access
* **Building applications?** Go to Application Development section
* **Modifying the OS?** See System Development section
* **Configuring hardware?** Check Configuration section

|

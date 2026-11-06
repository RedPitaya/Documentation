.. _dev_guide_software:

Software
########

This section covers software development for Red Pitaya, from basic console access to building custom applications and modifying the operating system. 
Whether you're developing measurement tools, integrating hardware peripherals, or compiling the OS from source, you'll find comprehensive guides organized by development task.

**What you'll find here:**

* **Introduction** - Understand Red Pitaya software architecture, development approaches, and workflows
* **Getting Started** - Establish console access via SSH or serial connection
* **Autostart and Boot Configuration** - Load FPGA images, run programs, and configure services at startup
* **Application Development** - Build applications using C++/Python APIs, streaming, and web interfaces
* **System Development** - Compile the OS ecosystem, create Debian packages, and build custom images
* **Configuration & Integration** - Set up networking, GPIO, SPI, displays, and remote deployment
* **Security Considerations** - User accounts, permissions, and safe deployment practices
* **Troubleshooting** - Known software issues and workarounds

.. toctree::
    :maxdepth: 1

    intro.rst
    getting_started/getting_started.rst
    autostart.rst
    app_development/app_development.rst
    system_development/system_development.rst
    configuration/configuration.rst
    security.rst
    troubleshooting/troubleshooting.rst




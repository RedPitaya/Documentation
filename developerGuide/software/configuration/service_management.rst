.. _service_management:

####################
Service Management
####################

Red Pitaya uses systemd for managing background services. This guide covers how to control system services, which is useful for optimizing performance, troubleshooting, and customizing 
system behavior.

.. contents:: Table of contents
    :local:
    :backlinks: top

|

Overview
*********

Red Pitaya runs several background services that provide various functionalities. Understanding how to manage these services allows you to:

* Optimize system performance for specific tasks
* Troubleshoot service-related issues
* Customize which services run at startup
* Free up system resources when needed

|

Red Pitaya Services
********************

The main Red Pitaya system services include:

.. list-table::
   :widths: 30 70
   :header-rows: 1

   * - Service Name
     - Description
   * - ``redpitaya_nginx``
     - Customized Nginx web server for Red Pitaya web interface and applications
   * - ``redpitaya_e3_controller``
     - Service that detects whether an external board is connected to the E3 slot (only active on Gen 2 PRO boards)
   * - ``redpitaya_startup``
     - Service for running Red Pitaya startup scripts

.. note::

    To see all installed Red Pitaya services (including inactive ones), use:
    
    .. code-block:: bash
    
        systemctl list-units "redpitaya*" --no-pager --all

For additional system services and details, see the :ref:`Build Red Pitaya OS <SW_build_os>` documentation.

.. important::

    **Web Interface (Nginx) and SCPI Server Exclusivity**
    
    The ``redpitaya_nginx`` web interface and the SCPI server (``/opt/redpitaya/bin/monitor``) cannot run simultaneously. They both access the same hardware resources, which causes conflicts.
    
    * **Before starting SCPI:** Stop the Nginx service with ``systemctl stop redpitaya_nginx``
    * **Before starting web interface:** Stop any running SCPI server instances
    
    For more details, see the :ref:`SCPI Server documentation <scpi_commands>`.

|

Basic Service Commands
***********************

All service management commands require SSH access to Red Pitaya. See :ref:`SSH Access <ssh>` for connection instructions.

Start a Service
================

Start a service immediately:

.. code-block:: bash

    systemctl start <service_name>

Example:

.. code-block:: bash

    systemctl start redpitaya_nginx

The service starts immediately but will not automatically start on next boot unless enabled.

|

Stop a Service
===============

Stop a running service immediately:

.. code-block:: bash

    systemctl stop <service_name>

Example:

.. code-block:: bash

    systemctl stop redpitaya_nginx

The service stops immediately but may restart on next boot if it's enabled.

|

Enable Service on Boot
=======================

Configure a service to start automatically at boot:

.. code-block:: bash

    systemctl enable <service_name>

Example:

.. code-block:: bash

    systemctl enable redpitaya_scpi

.. note::

    This command only configures startup behavior. To also start the service immediately:
    
    .. code-block:: bash
    
        systemctl enable redpitaya_nginx
        systemctl start redpitaya_nginx

|

Disable Service on Boot
=========================

Prevent a service from starting automatically at boot:

.. code-block:: bash

    systemctl disable <service_name>

Example:

.. code-block:: bash

    systemctl disable redpitaya_nginx

.. note::

    This command only affects startup behavior. To also stop the currently running service:
    
    .. code-block:: bash
    
        systemctl disable redpitaya_nginx
        systemctl stop redpitaya_nginx

|

Check Service Status
=====================

View the current status of a service:

.. code-block:: bash

    systemctl status <service_name>

Example output for a running service:

.. code-block:: text

    ● redpitaya_nginx.service - Red Pitaya Nginx Web Server
         Loaded: loaded (/etc/systemd/system/redpitaya_nginx.service; enabled)
         Active: active (running) since Wed 2026-02-05 10:23:15 UTC; 2h ago
       Main PID: 1234 (nginx)
          Tasks: 5
         Memory: 12.3M
         CGroup: /system.slice/redpitaya_nginx.service

Example output for a stopped service:

.. code-block:: text

    ● redpitaya_nginx.service - Red Pitaya Nginx Web Server
         Loaded: loaded (/etc/systemd/system/redpitaya_nginx.service; disabled)
         Active: inactive (dead)

Press ``q`` to exit the status view.

|

Restart a Service
==================

Restart a service (stop and start):

.. code-block:: bash

    systemctl restart <service_name>

This is useful after configuration changes or to clear service state issues.

|

List All Services
==================

View all Red Pitaya services and their status:

.. code-block:: bash

    systemctl list-units "redpitaya*" --no-pager

Example output:

.. code-block:: text

    UNIT                            LOAD   ACTIVE   SUB     DESCRIPTION
    redpitaya_e3_controller.service loaded inactive dead    Service for an application that detects...
    redpitaya_nginx.service         loaded active   running Customized Nginx web server for Red Pitaya...
    redpitaya_startup.service       loaded inactive dead    Service for startup script Red Pitaya

|

Common Use Cases
*****************

Disable Web Interface for Performance
=======================================

When running performance-critical applications (like high-speed streaming), disable the web interface to free up resources:

.. code-block:: bash

    systemctl stop redpitaya_nginx
    systemctl disable redpitaya_nginx

To restore:

.. code-block:: bash

    systemctl enable redpitaya_nginx
    systemctl start redpitaya_nginx

**Use cases:** 
* High-speed data streaming (:ref:`See streaming optimization <streaming_performance_optimization>`)
* CPU-intensive signal processing
* Minimizing network bandwidth usage

|

Running SCPI Server Manually
==============================

If you need :ref:`SCPI command <scpi_commands>` access, the SCPI server can be started manually in the terminal.

.. warning::

    **The SCPI server and Nginx web interface cannot run at the same time.** They access the same hardware resources and will cause conflicts.

For temporary SCPI usage, stop the web interface (it will restart on next boot):

.. code-block:: bash

    systemctl stop redpitaya_nginx
    /opt/redpitaya/bin/monitor &

The ``&`` runs the command in the background, allowing continued terminal use.

.. note::

    If you want SCPI to start automatically at boot instead of the web interface, see :ref:`Starting SCPI server at boot time <scpi_boot_time>` in the SCPI documentation.

**Use cases:**
* Remote instrument control via :ref:`SCPI commands <scpi_commands>`
* Automated testing and measurement
* Integration with test equipment

For complete SCPI setup, command reference, and examples, see the :ref:`SCPI Server documentation <scpi_commands>`.

|

Running Custom Commands at Boot
=================================

The startup script (``/opt/redpitaya/sbin/startup.sh``) can be used to run custom commands at every boot. This is useful for tasks that need to execute after the system starts, but should not be managed as systemd services.

.. note::

    **Use `enable`/`disable` for permanent service configuration**
    
    To permanently prevent a service from starting at boot, simply run ``systemctl disable <service_name>`` once. This configuration persists across reboots without needing the startup script.
    
    The startup script is for running commands that need to execute at boot, not for managing service enable/disable state.

**Example use case:** Automatically start SCPI server at boot

1. Edit the startup script:

   .. code-block:: bash

       nano /opt/redpitaya/sbin/startup.sh

2. Add commands at the end of the file:

   .. code-block:: bash

       # Start SCPI server automatically
       /opt/redpitaya/bin/monitor &

3. Save and exit (``Ctrl+X``, ``Y``, ``Enter``)

The commands will run automatically at every boot.

|

Troubleshooting
****************

Service Won't Start
====================

If a service fails to start:

1. Check the service status for error messages:

   .. code-block:: bash

       systemctl status <service_name>

2. View detailed logs:

   .. code-block:: bash

       journalctl -u <service_name> -n 50

3. Check if another instance is already running:

   .. code-block:: bash

       ps aux | grep <service_name>

|

Service Keeps Restarting
=========================

If a service automatically restarts after being stopped, it may be configured for automatic restart:

1. Check the service configuration:

   .. code-block:: bash

       systemctl cat <service_name>

2. Look for ``Restart=`` settings in the service file

3. Disable the service to prevent automatic restarts:

   .. code-block:: bash

       systemctl disable <service_name>
       systemctl stop <service_name>

|

Changes Don't Persist After Reboot
====================================

If service state doesn't persist:

1. Ensure you used ``enable``/``disable`` commands, not just ``start``/``stop``

2. Verify the change took effect:

   .. code-block:: bash

       systemctl is-enabled <service_name>

|

Related Topics
***************

* :ref:`SSH Access <ssh>` - Required for service management
* :ref:`Build Red Pitaya OS <SW_build_os>` - Complete service list and systemd details
* :ref:`Streaming Performance Optimization <streaming_performance_optimization>` - Streaming-specific service optimization
* :ref:`Network Configuration <sw_network>` - Network service configuration

|

Additional Resources
*********************

* `systemd documentation <https://www.freedesktop.org/software/systemd/man/systemctl.html>`_ - Official systemd/systemctl reference
* :ref:`Known Software Issues <known_sw_issues>` - Common service-related problems
* `Red Pitaya Forum <https://forum.redpitaya.com>`_ - Community support for service issues

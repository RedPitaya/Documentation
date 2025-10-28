.. _SW_comp_Streaming:

###############################################
Compiling Streaming client applications
###############################################

Red Pitaya's streaming application supports two types of clients:

- **Console client** - Command-line interface for streaming data
- **Desktop client** - Graphical user interface (Qt-based) for streaming data

Pre-built client applications are provided with each firmware release. However, you can customize and rebuild these clients according to your requirements.

This guide explains how to build both client types using Qt Creator.


Prerequisites
==============

Before building the streaming clients, ensure you have the following installed:

- CMake 3.18 or higher
- Qt 5.15.2 with QtCharts module
- GCC 9 or higher
- Operating System: Windows or Ubuntu

.. note::

    Download Qt development tools from the `official Qt website <https://www.qt.io/download-dev>`_. 
    During installation, ensure you select the QtCharts module as an additional package.


Building with Qt Creator
=========================

Qt Creator provides an integrated development environment for building and modifying the streaming clients.


Opening the project
---------------------

1. Launch Qt Creator
2. Open the CMakeLists.txt file as a project
3. Navigate to: ``./apps-tools/streaming_manager/src/CMakeLists.txt``

.. figure:: qt/qt1.png   
   :align: center

After opening the project, you will see that only the server and console client are available for building by default.

.. figure:: qt/qt2.png   
   :align: center


Enabling the desktop client build
------------------------------------

The desktop client (Qt GUI application) is disabled by default. To enable it:

1. Open the project settings in Qt Creator
2. Locate the CMake configuration options
3. Enable the checkbox for: **BUILD_RPSA_CLIENT_QT**

.. figure:: qt/qt3.png   
   :align: center

Once enabled, the desktop client will become available as a build target.

.. figure:: qt/qt4.png   
   :align: center


Building the clients
----------------------

After configuring the build options:

1. Select the desired build target (console client or desktop client)
2. Click the build button in Qt Creator
3. The compiled binaries will be available in the build output directory


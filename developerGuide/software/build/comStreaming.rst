.. _comStreaming:

###################################################
Compiling and running Streaming client applications
###################################################

You can use the console client or the desktop client to connect to the streaming application. When releasing firmware images, we build client applications in parallel, but you can improve them yourself.

Requirements
==============

* CMake 3.18
* QT 5.15.2
* GCC 9 and higher
* Windows or Ubuntu

.. note::

    You can download QT development tools from the `official site <https://www.qt.io/download>`_. When installing, you must specify an additional package QtCharts.


Build with QT Creator
=========================

Client applications are easy to develop with QtCreator. To do this, just run the application and open the CMakeLists.txt file as a project.
The CMakeLists.txt file is located along the path: ./apps-tools/streaming_manager/src

.. figure:: qt/qt1.png   
   :align: center


In this case, a project will open in which only the server and the console client will be available for assembly.

.. figure:: qt/qt2.png   
   :align: center


By default, the project for building the desktop version is not active, to enable it you need to go to the project settings and check the box next to the parameter: BUILD_RPSA_CLIENT_QT.

.. figure:: qt/qt3.png   
   :align: center


After that, the ability to build a project for desktop systems will be available.

.. figure:: qt/qt4.png   
   :align: center


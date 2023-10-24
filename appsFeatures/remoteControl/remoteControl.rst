.. _remoteControl:

SCPI server (MATLAB, LabVIEW, Scilab or Python)
##################################################

.. https://owncloud.redpitaya.com/index.php/apps/files/?dir=%2FWEB%20page%2Fapps%2FSCPI

.. figure:: img/SCPI_web_lr.png

The Red Pitaya board can be controlled remotely over a LAN or wireless interface using MATLAB, LabVIEW, Scilab, or Python via the Red Pitaya SCPI (Standard Commands for Programmable Instrumentation) list of commands. The SCPI interface/environment is commonly used to control T&M instruments for development, research, or test automation purposes. SCPI uses a set of SCPI commands that are recognised by the instruments to enable specific actions to be taken (e.g., acquiring data from fast analog inputs, generating signals, and controlling other peripheries of the Red Pitaya platform). The SCPI commands are extremely useful when complex signal analysis is required. An SW environment such as MATLAB provides powerful data analysis tools and SCPI commands simple access to raw data acquired on the Red Pitaya board.

**Features**

- Quickly write control routines and programs using MATLAB, LabVIEW, Scilab, or Python.
- Use powerful data analysis tools like MATLAB, LabVIEW, Scilab, or Python to analyse raw signals acquired by the Red Pitaya board.
- Write testing scripts and routines.
- Incorporate your Red Pitaya and LabVIEW into testing and production lines.
- Take quick measurements directly on your PC.

***********
Quick start
***********

Start the SCPI server. This is done simply by clicking on the SCPI server icon and starting the SCPI server. When the SCPI server is started, the IP address of your board will be shown. This IP address must be entered into your scripts. Starting the SCPI server can also be done manually via Terminal (see below).

To run an example, follow the instructions below:

#. Go to your Red Pitaya main page and select the SCPI server in the Development section.

   .. figure:: img/scpi-homepage.png

   .. figure:: img/scpi-development.png

#. Start the SCPI server by selecting the RUN button. Please note the IP of your Red Pitaya (192.168.178.100) board as it will be needed to connect to your board.

   .. figure:: img/scpi-app-run.png

   .. figure:: img/scpi-app-stop.png

#. Follow the instructions below suitable for your environment.

   .. note::

      It is not possible to run SCPI commands or programs in parallel with web applications.
      
.. contents::
    :local:
    :backlinks: none
    :depth: 1

======
MATLAB
======

#. Open MATLAB on your computer.
#. In the MATLAB workspace, paste the code from the :ref:`blink <blink>` tutorial example.
#. Replace the IP in the example with the IP of your Red Pitaya board.
#. Hit RUN or F5 on your keyboard to run the code.

More examples of how to control Red Pitaya from MATLAB can be found :ref:`here <examples>`.


======
Python
======

The |PyVISA| library, in combination with the |PyVISA-py| backend, is used.

To install them, do:

.. |PyVISA| raw:: html

    <a href="https://pyvisa.readthedocs.io/en/latest/" target="_blank">PyVISA</a>
    

.. |PyVISA-py| raw:: html

    <a href="https://pyvisa.readthedocs.io/projects/pyvisa-py/en/latest/" target="_blank">PyVISA-py</a>


.. code-block:: shell-session
   
   $ sudo pip3 install pyvisa pyvisa-py

.. note::
   
   To run the examples, you need Python version 3. Before running, double-check the Python versions. If the system has Python version 2.7, this version will be used by default.

   .. code-block:: shell-session

      $ python --version
      Python 2.7.17
         
      Then, in order to run the examples, specify explicitly the Python version.
         
   .. code-block:: shell-session
         
      $ python3.5 blink.py 192.168.178.108

#. Open the :ref:`blink <blink>` tutorial and copy the code to your favourite text editor.
#. Save the file to your working folder as ``blink.py``, for example, ``examples_py``.
   Copy and save the |redpitaya_scpi.py| script in the same folder as the ``blink.py`` example (in our case, ``examples_py``). 

   .. note::

      The ``redpitaya_scpi.py`` script is a standard script needed to establish the connection between your PC and the Red Pitaya board. The execution of your script will fail without this script being in the same folder as your Python script.

   .. figure:: img/scpi-examples.png

#. Open the Terminal and navigate to the folder containing your Python script (``examples_py``), then type: ``Python blink.py IP``, passing a Red Pitaya IP as an argument when calling an execution of the ``blink.py`` example. An example is given below, where ``192.168.178.108`` is the IP of the Red Pitaya board.

   .. code-block:: shell-session

      cd /home/zumy/Desktop/exmples_py
      python blink.py 192.168.178.108

   .. figure:: img/scpi-example-cli.png

More examples of how to control Red Pitaya from MATLAB can be found :ref:`here <examples>`.

   .. note::
   
      Python examples can also be run directly from the RP device itself. To do so, first start the SCPI server and then use the local device IP: ``127.0.0.1``


.. |redpitaya_scpi.py| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>


=======
LabVIEW
=======

To install the Red Pitaya LabVIEW driver, download the `Red_Pitaya_LabVIEW_Driver&Examples.zip <https://downloads.redpitaya.com/downloads/Clients/labview/Red_Pitaya_LabVIEW_Driver%26Examples.zip>`_ file.
Unpack it and copy the Red Pitaya folder to your LabVIEW installation ``instr.lib`` folder, e.g. ``C:/Program Files/National Instruments/LabVIEW 2010/instr.lib``. When using the 64-bit LabVIEW version (mostly paid), Or here : ``C:/Program Files (x86)/National Instruments/LabVIEW 2020/instr.lib`` when using the 32-bit LabVIEW version, like the free Community Edition.

The Red Pitaya driver should appear after restarting LabVIEW in **Block Diagram -> Instrument I/O -> Instr Drivers -> RedPitaya**. Depending on your settings, instrument I/O may be hidden. Please consult LabVIEW Help on how to activate or deactivate those categories. You can access example VIs by going to:

#. Help -> Find Examples...
#. select the Search tab
#. In the Enter keyword(s) field, type **RedPitaya**. 

More examples of how to control Red Pitaya from LabVIEW can be found :ref:`here <examples>`.

======
SCILAB
======

To use the SCPI commands, you will need to set up Scilab sockets. The procedure is described below.

#. Go to the |Scilab download page| and download and install Scilab for your OS.
#. Go to the |Scilab toolbox| and download the basic socket function for Scilab.
#. Go to the extracted Scilab folder, then to the folder named ``contrib``.
#. Copy the socket_toolbox zip file to the contrib folder.
#. Extract the socket_toolbox zip file inside the contrib folder.
#. We no longer require the socket_toolbox zip file, so remove it.
#. Go to the socket_toolbox folder.
#. Open loader.sce with your Scilab and press RUN (grey run button on SCILAB editor GUI).

These last two steps must be executed each time you start Scilab. To install, you must have an internet connection. Running the examples is the same as on MATLAB.

#. In the MATLAB workspace, paste the code from the :ref:`blink <blink>` tutorial example.
#. Replace the IP in the example with the IP of your Red Pitaya board.
#. Press RUN to run the code.

Different code examples can be found :ref:`here <examples>`.

.. |Scilab download page| raw:: html

    <a href="http://www.scilab.org/download/" target="_blank">Scilab download page</a>

.. |Scilab toolbox| raw:: html

    <a href="https://atoms.scilab.org/toolboxes/socket_toolbox" target="_blank">Scilab socket toolbox page</a>

.. note::

   Communicating with an SCPI server and working with web-based instruments at the same time can diminish the performance of your Red Pitaya. This is because the same resource is used for both tasks.

*****************************
Starting SCPI server manually
*****************************

Assuming you have successfully connected to your Red Pitaya board using :ref:`these instructions <faqConnected>` these instructions, remotely connect using Putty on Windows machines or with :ref:`SSH <ssh>` using Terminal on UNIX (macOSX/Linux) machines.

Connect to your Red Pitaya board via the terminal on a Linux machine and start the SCPI server with the following command:

.. code-block:: shell-session

   systemctl start redpitaya_scpi &

.. figure:: img/scpi-ssh.png


.. include:: SCPI_commands.inc


.. _examples:

********
Examples
********

In the list below you will find examples of remote control and C algorithms. These examples cover all basic Red Pitaya functionalities, such as:

    - signal generation
    - signal acquisition
    - digital I/O control
    - communication protocols

You can edit and change them according to your needs and develop customized programs and routines.

.. toctree::
   :maxdepth: 1

   ../examples/scpi_examples


Additional examples: :ref:`ABCLED`

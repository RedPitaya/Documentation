.. _scpi:

SCPI server (MATLAB, LabVIEW, Scilab or Python)
##################################################

.. https://owncloud.redpitaya.com/index.php/apps/files/?dir=%2FWEB%20page%2Fapps%2FSCPI

.. figure:: img/SCPI_web_lr.png

|

The Red Pitaya board can be controlled remotely over a LAN or wireless interface using MATLAB, LabVIEW, Scilab, or Python via the Red Pitaya SCPI (Standard Commands for Programmable Instrumentation) list of commands. The SCPI interface/environment is commonly used to control T&M instruments for development, research, or test automation. SCPI uses a set of commands recognised by the instruments to enable specific actions (e.g., acquiring data from fast analog inputs, generating signals, and controlling other peripheries of the Red Pitaya platform). The SCPI commands are extremely useful when complex signal analysis is required. A SW environment such as MATLAB that provides powerful data analysis tools is a perfect combination for the SCPI commands' simple access to raw data acquired on the Red Pitaya board.

**Features**

- Quickly write control routines and programs using MATLAB, LabVIEW, Scilab, or Python.
- Use powerful data analysis tools like MATLAB, LabVIEW, Scilab, or Python to analyse raw signals acquired by the Red Pitaya board.
- Write testing scripts and routines.
- Incorporate your Red Pitaya and LabVIEW into testing and production lines.
- Take quick measurements directly on your PC.

|

***********
Quick start
***********

To initiate the SCPI server, just click on the SCPI server icon. Once the SCPI server is operational, your board's IP address will be displayed. This IP address should be incorporated into your scripts. Alternatively, you can manually commence the SCPI server using the Terminal (refer to the instructions below).

To run an example, follow the instructions below:

#.  Go to your Red Pitaya web interface and select the SCPI server in the *Development* section.

    .. figure:: img/scpi-homepage.png

    |

    .. figure:: img/scpi-development.png


#.  Start the SCPI server by selecting the RUN button. Please note the IP of your Red Pitaya (192.168.178.100) board as it will be needed to connect to your board.

    .. figure:: img/scpi-app-run.png

    |

    .. figure:: img/scpi-app-stop.png


#.  Follow the instructions below suitable for your environment.

    .. note::

        Please refrain from running the SCPI server in parallel with other web applications like the Oscilloscope as it may result in undefined behaviour of both the application and the SCPI program.
      
.. contents::
    :local:
    :backlinks: none
    :depth: 1

|

======
MATLAB
======

#.  Open MATLAB on your computer.
#.  In the MATLAB workspace, paste the code from the :ref:`blink <blink>` tutorial example.
#.  Replace the IP in the example with the IP of your Red Pitaya board.
#.  Hit RUN or F5 on your keyboard to run the code.

More examples of how to control Red Pitaya from MATLAB can be found :ref:`here <examples>`.

|

======
Python
======

The |PyVISA| library, in combination with the |PyVISA-py| backend, is used.

To install them, do:

.. |PyVISA| raw:: html

    <a href="https://pyvisa.readthedocs.io/en/latest/" target="_blank">PyVISA</a>
    

.. |PyVISA-py| raw:: html

    <a href="https://pyvisa.readthedocs.io/projects/pyvisa-py/en/latest/" target="_blank">PyVISA-py</a>


.. tabs::

    .. tab:: Linux

        .. code-block:: shell-session
   
            $ sudo pip3 install pyvisa pyvisa-py

    .. tab:: Windows

        .. code-block:: shell-session
   
            $ pip install pyvisa pyvisa-py

.. note::
   
   To run the examples, you need Python version 3.10 or higher. Before running, please, double-check the Python versions.

   .. code-block:: shell-session

       $ python --version
       Python 3.10.6

   On Windows, you can use **py** instead of **python** in the command line.

   In case mulitple Python versions are installed on the computer, please specify explicitly the Python version.

   .. code-block:: shell-session
         
       $ python3.10 blink.py

|

#.  Open the :ref:`blink <blink>` tutorial and copy the code to your favourite text editor.

    |

#.  Save the file to your working folder as ``blink.py``, for example, ``examples_py``.
    Copy and save the |redpitaya_scpi.py| script in the same folder as the ``blink.py`` example (in our case, ``examples_py``). 

    .. note::

       The ``redpitaya_scpi.py`` script is a standard script needed to establish the connection between your PC and the Red Pitaya board. The execution of your script will fail without this script being in the same folder as your Python script.

    .. figure:: img/scpi-examples.png

    |

#.  Open the Terminal and navigate to the folder containing your Python script (``examples_py``), then type: ``Python blink.py IP``, passing a Red Pitaya IP as an argument when calling an execution of the ``blink.py`` example. An example is given below, where ``192.168.178.108`` is the IP of the Red Pitaya board.

    .. code-block:: shell-session

        cd /home/zumy/Desktop/exmples_py
        python blink.py 192.168.178.108

    .. figure:: img/scpi-example-cli.png


More examples of how to control Red Pitaya from MATLAB can be found :ref:`here <examples>`.

.. note::
   
   Python examples can also be run directly from the RP device itself. To do so, first start the SCPI server and then use the local device IP: ``127.0.0.1``


.. |redpitaya_scpi.py| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>

|

=======
LabVIEW
=======

To install the Red Pitaya LabVIEW driver, download the `Red_Pitaya_LabVIEW_Driver&Examples.zip <https://downloads.redpitaya.com/downloads/Clients/labview/Red_Pitaya_LabVIEW_Driver%26Examples.zip>`_ file.
Unpack it and copy the Red Pitaya folder to your LabVIEW installation ``instr.lib`` folder, e.g. ``C:/Program Files/National Instruments/LabVIEW 2010/instr.lib``. When using the 64-bit LabVIEW version (mostly paid), Or here : ``C:/Program Files (x86)/National Instruments/LabVIEW 2020/instr.lib`` when using the 32-bit LabVIEW version, like the free Community Edition.

The Red Pitaya driver should appear after restarting LabVIEW in **Block Diagram -> Instrument I/O -> Instr Drivers -> RedPitaya**. Depending on your settings, instrument I/O may be hidden. Please consult LabVIEW Help on how to activate or deactivate those categories. You can access example VIs by going to:

#.  Help -> Find Examples...
#.  select the Search tab
#.  In the Enter keyword(s) field, type **RedPitaya**. 

More examples of how to control Red Pitaya from LabVIEW can be found :ref:`here <examples>`.

|

======
SCILAB
======

To use the SCPI commands, you will need to set up Scilab sockets. The procedure is described below.

#.  Go to the |Scilab download page| and download and install Scilab for your OS.
#.  Go to the |Scilab toolbox| and download the basic socket function for Scilab.
#.  Go to the extracted Scilab folder, then to the folder named ``contrib``.
#.  Copy the socket_toolbox zip file to the contrib folder.
#.  Extract the socket_toolbox zip file inside the contrib folder.
#.  We no longer require the socket_toolbox zip file, so remove it.
#.  Go to the socket_toolbox folder.
#.  Open loader.sce with your Scilab and press RUN (grey run button on SCILAB editor GUI).


These last two steps must be executed each time you start Scilab. To install, you must have an internet connection. Running the examples is the same as on MATLAB.

#.  In the MATLAB workspace, paste the code from the :ref:`blink <blink>` tutorial example.
#.  Replace the IP in the example with the IP of your Red Pitaya board.
#.  Press RUN to run the code.

Different code examples can be found :ref:`here <examples>`.

.. |Scilab download page| raw:: html

    <a href="http://www.scilab.org/download/" target="_blank">Scilab download page</a>

.. |Scilab toolbox| raw:: html

    <a href="https://atoms.scilab.org/toolboxes/socket_toolbox" target="_blank">Scilab socket toolbox page</a>

.. note::

   Communicating with an SCPI server and working with web-based instruments at the same time can diminish the performance of your Red Pitaya. This is because the same resource is used for both tasks.

|

*****************************
Starting SCPI server manually
*****************************

1. Connect to your Red Pitaya through :ref:`SSH <ssh>`.

2. Start the SCPI server with the following command:

    .. code-block:: shell-session

        systemctl start redpitaya_scpi &

    .. figure:: img/scpi-ssh.png

.. note::

    Please make sure that the "default" *v0.94* FPGA image is loaded. With OS versions 2.00-23 or higher, exectue the following command:

   .. figure:: scpi-run2.png

   To see the server logs when executing commands:

   .. code-block::

      RP:LOGmode CONSOLE



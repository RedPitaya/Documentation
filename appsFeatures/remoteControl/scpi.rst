.. _scpi_commands:

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


#.  Start the SCPI server by selecting the RUN button. Please note the IP of your Red Pitaya (in our case, 192.168.178.100) board, as it will be needed to establish a socket communication with your board. Alternatively, you can use the *"rp-xxxxxx.local"* address instead of the IP address.

    .. figure:: img/scpi-app-run.png

    |

    .. figure:: img/scpi-app-stop.png


#.  Follow the instructions below depending on the OS environment of your computer.

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

**Requirements and Setup**

The basic MATLAB installation already has everything you need to control your Red Pitaya. However, we recommend installing the *Signal Processing* and
*Instrumentat control* toolboxes, which might come in handy.

**Running code**

#.  Open MATLAB on your computer.
#.  In the MATLAB workspace, paste the code from the :ref:`blink <blink>` tutorial example.
#.  Replace the IP in the example with the IP of your Red Pitaya board or the *"rp-xxxxxx.local"* address.
#.  Hit *RUN* or the *F5* key on your keyboard to run the code.

More examples of controlling Red Pitaya through MATLAB can be found :ref:`here <examples>`.

|

======
Python
======

**Requirements and Setup**

Here are the requirements for setting up a Python environment to remotely control your Red Pitaya. Here we present setting up the environment in |VSCode|, due to high adaptability and easily expandable functionality.

1.  Python version 3.10 or higher. Link to |python_main|.
    During the installation process, do not forget to check the **Add python.exe to PATH** box!

    .. insert picture

2.  Install a coding environment. We recommend using |VSCode|, since it has a lot of functionality and can easily be extended.

    .. insert picture

3.  Install appropriate extensions for your coding environment (*Python Extension Pack* and *Better Comments* are a good combination for VS Code).

    .. 
4.  Setup or create a new |workspace|. Here are some |tutorials| for Visual Studio Code.

5.  Choose a Python interpreter.
    
    .. add picture

6.  Optionally, create a |venv|.

7.  Ensure that the Python packages are up to date and install following Python libraries:

    - pyvisa pyvisa-py (|PyVISA| library, in combination with the |PyVISA-py| backend)
    - numpy
    - matplotlib

    .. tabs::

    .. tab:: Linux

        .. code-block:: shell-session
   
            $ sudo pip3 install pyvisa pyvisa-py numpy matplotlib

    .. tab:: Windows

        .. code-block:: shell-session
   
            $ pip install pyvisa pyvisa-py numpy matplotlib


8.  Windows users must enable "Running Scripts" option. It should be located in **Settings > Update&Security > For developers** under the **Power Shell** section (or google "How to enable running scripts on Windows 10/11").

9.  Double-check the Python verision and reselect the Python interpreter if necessary (See step 5).

    .. code-block:: shell-session

       $ python --version
       Python 3.10.6

    On Windows, you can use **py** instead of **python** in the command line.

10. Downaload and save the |redpitaya_scpi.py| library into the VS Code workspace folder/directory. This library must be in the same folder as the python scripts.

11. Create a new python file with the following code.

    .. code-block:: python

        import numpy as np

        print("Hello world!\n")

    Once saved, check how the NumPy library is displayed. If it is underlined in yellow the current Python environment does not have the libraries installed correctly.

12. Run the test file. There should be no errors or warnings displayed in the terminal ("Hello world!" is printed).

    .. add picture



.. |PyVISA| raw:: html

    <a href="https://pyvisa.readthedocs.io/en/latest/" target="_blank">PyVISA</a>
    
.. |PyVISA-py| raw:: html

    <a href="https://pyvisa.readthedocs.io/projects/pyvisa-py/en/latest/" target="_blank">PyVISA-py</a>

.. |python_main| raw:: html

    <a href="https://www.python.org/downloads/" target="_blank">Python download webpage</a>

.. |VSCode| raw:: html

    <a href="https://code.visualstudio.com/" target="_blank">Visual Studio Code</a>

.. |workspace| raw:: html

    <a href="https://code.visualstudio.com/docs/editor/workspaces" target="_blank">workspace</a>

.. |tutorials| raw:: html

    <a href="https://code.visualstudio.com/docs/getstarted/introvideos" target="_blank">tutorials</a>

.. |venv| raw:: html

    <a href="https://code.visualstudio.com/docs/python/environments" target="_blank">virtual environment</a>

.. |redpitaya_scpi.py| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/blob/master/Examples/python/redpitaya_scpi.py" target="_blank">redpitaya_scpi.py</a>


**Running code**

1.  Open the :ref:`blink <blink>` tutorial and copy the code to your favourite text editor.

    |

2.  Save the file to your working folder as ``blink.py``. Make sure that **redpitaya_scpi.py** is located next to it.

    .. note::

       The ``redpitaya_scpi.py`` library is a standard script needed to establish the connection between your PC and the Red Pitaya board. The execution of your code will fail without this library being in the same folder as your Python code.

    .. figure:: img/scpi-examples.png

    |

3.  Edit ``blink.py`` so that the *IP* variable contains the IP or the "rp-xxxxxx.local" address of your Red Pitaya.

4.  Run the ``blink.py``. Either select the left arrow in the VS Code or open the Terminal and navigate to the folder containing your Python script (``examples_py``), then type: ``python blink.py``

    .. code-block:: shell-session

        cd /home/Miha/Desktop/
        python blink.py


More examples of how to control Red Pitaya with Python can be found :ref:`here <examples>`.

.. note::
   
   Python examples can also be run directly from the RP device itself. To do so, first start the SCPI server and then use the local device IP: ``127.0.0.1``

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

   .. figure:: img/scpi-run2.png

   To see the server logs when executing commands:

   .. code-block::

      RP:LOGmode CONSOLE



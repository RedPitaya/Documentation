.. _fpga_reprogramming:

########################
Reprogramming the FPGA
########################

In this section we will discuss how to reprogram the FPGA on the Red Pitaya board with a new FPGA image that we created in the previous sections.


Prerequisites
====================

* FPGA bitstream file (``.bit``) or binary bitstream file (``.bit.bin``).
* Red Pitaya board :ref:`powered and connected to the local network <quickstart_connect>`.


FPGA reprogramming steps
=========================

Due to a change in the FPGA programming method made by AMD/Xilinx between Ubuntu versions 16.04 LTS (Red Pitaya OS 1.04) and 22.04 (Red Pitaya OS 2.00), there are two different methods to reprogram the FPGA, depending on the OS version you are using.
Please select the appropriate tab below for your OS version.

When executing the code, please pay attention to the ``redpitaya>`` keyword:

* **Commands with "redpitaya>" prefix** - should be executed inside Red Pitaya Linux OS after establishing an :ref:`SSH <ssh>` connection.
* **Commands without the prefix** - should be executed in your computer's local terminal or command prompt.


.. tabs::

    .. tab:: OS version 1.04 or older

        **Windows** - Please change the forward slashes to backward slashes.

        1. Open **Terminal or CMD** and navigate to the *.bit* file location (**<FPGA_repository>/prj/<project_name>/project/redpitaya.runs/impl_1**).

            .. code-block:: bash
        
                cd <Path/to/RedPitaya/repository>/prj/v0.94/project/redpitaya.runs/impl_1

        #. Send the file *.bit* to the Red Pitaya using the ``scp`` command. The bitstream name is the same as the top module name  (*red_pitaya_top.bit*).

            .. code-block:: bash

                scp red_pitaya_top.bit root@rp-xxxxxx.local:/root

        #. Establish an :ref:`SSH <ssh>` communication with Red Pitaya and check if *red_pitaya_top.bit* is in the *root* directory.

            .. code-block:: bash

                redpitaya> cd
                redpitaya> ls

        #. Load the *red_pitaya_top.bit* to **xdevcfg** with

            .. code-block:: bash

                redpitaya> cat red_pitaya_top.bit > /dev/xdevcfg


    .. tab:: OS version 2.00 or higher

        The 2.00 OS uses a new mechanism of loading the FPGA. The process will depend on whether you are using Linux or Windows as the ``echo`` command functinality differs bewteen the two.

        Please note that you need to change the forward slashes to backward slashes on Windows.

        1. On Windows, open **Vivado** and use the **Vivado TCL console** to navigate to the *.bit* file location.

           On Linux, open the **Terminal** and go to the *.bit* file location.

           .. code-block:: bash

               cd <Path/to/RedPitaya/repository>/prj/<project_name>/project/redpitaya.runs/impl_1

        2. **Create a .bif file** (for example, *red_pitaya_top.bif*) and use it to generate a binary bitstream file (*red_pitaya_top.bit.bin*)

           **Windows (Vivado TCL console or Vivado HSL Command Prompt):**

           .. code-block:: bash

               echo all:{ red_pitaya_top.bit } >  red_pitaya_top.bif
               bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

           **Linux:**

           .. code-block:: bash

               echo -n "all:{ red_pitaya_top.bit }" >  red_pitaya_top.bif
               bootgen -image red_pitaya_top.bif -arch zynq -process_bitstream bin -o red_pitaya_top.bit.bin -w

        3. Using the **Command prompt or Terminal**, send the newly created *.bit.bin* file to the Red Pitaya using the ``scp`` command.

           .. code-block:: bash
   
               scp red_pitaya_top.bit.bin root@rp-xxxxxx.local:/root

        4. Establish an :ref:`SSH <ssh>` communication with Red Pitaya and check if *red_pitaya_top.bit.bin* is in the *root* directory.

           .. code-block:: bash

                redpitaya> cd
                redpitaya> ls

        5. Load the *red_pitaya_top.bit.bin* image using the ``fpgautil`` command:

           .. code-block:: bash

               redpitaya> fpgautil -b red_pitaya_top.bit.bin


.. note:: 

    The following error will occur if the bitstream and the board are incompatible.

    .. code-block:: bash

        sh: 1: echo: echo: I/O error
        BIN FILE loading through FPGA manager failed

    Please check that :ref:`correct flags were used during project creation <fpga_create_project>`.



Confirming FPGA rewrite
-------------------------

There are several ways to confirm that the FPGA has been successfully reprogrammed. The simplest ones include confirming the LED indicator or an ID register, both of which must be defined in the custom FPGA design.

Example of checking a custom FPGA register using the ``monitor`` command line tool:

.. code-block:: bash

    monitor 0x40300050

The command above should return the value of the ID register ``0xfeedbacc`` (:ref:`Adding a custom component tutorial <fpga_tutorial_cust_comp>`).



Reprogram FPGA at device boot
-------------------------------

Normally, the FPGA reprogramming lasts until one of the following events occurs:

1. The device is powered off or reset.
#. A new FPGA image is loaded into the device (openning web applications, reloading the web interface, etc.).
#. The FPGA configuration is changed through software.

To **load a custom FPGA image at every device boot**, make a Bash script and place it into the ``/etc/profile.d`` directory.

.. tabs::

    .. tab:: OS version 1.04 or older

        .. code-block:: bash

            #!/bin/bash
            cat /root/red_pitaya_top.bit > /dev/xdevcfg

    .. tab:: OS version 2.00 or higher

        .. code-block:: bash

            #!/bin/bash
            fpgautil -b red_pitaya_top.bit.bin

Use the following script to **replace the default Red Pitaya v0.94 FPGA image** with a custom one. This will automatically load the custom FPGA image at device boot and also replace the FPGA image of applications that usually use the v0.94 project.

.. code-block:: bash

    #!/bin/bash

    BITSTREAM=$1
    MODEL=$(/opt/redpitaya/bin/monitor -f)
    PROJ=v0.94

    # Enable read write priviliges
    mount -o rw,remount $PATH_REDPITAYA

    # Check if the backup file already exists
    if [ ! -f "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin" ]; then
        # Create backup of original fpga.bit.bin
        cp "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin" "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin"
    fi

    if [ $# -eq 0 ]
    then
        # Original file overwrites fpga.bit.bin
        cp -f "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga_orig.bit.bin" "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin"
        conf="Restored original fpga.bit.bin"
    else
        # fpga.bit.bin replaced with custom image
        cp -f "$(realpath $1)" "/opt/redpitaya/fpga/$MODEL/$PROJ/fpga.bit.bin"
        conf="fpga.bit.bin overwritten with $BITSTREAM"
    fi

    mount -o ro,remount $PATH_REDPITAYA
    echo "$conf"


1. The script should be copied to the Red Pitaya board (``scp``) and made executable (``chmod +x``).
#. The script has one optional parameter (the path to the custom FPGA bitstream file).

    * If provided, this path will be used to replace the default FPGA image with the custom one. At the same time, a backup of the original FPGA image will be created (if it does not already exist).
    * If not provided, the original FPGA image will be restored from the backup.

    Example of replacing the default FPGA image with a custom one:

    .. code-block:: console

        ./replace_fpga.sh /path/to/custom_fpga.bit

    Reverting the original FPGA image:

    .. code-block:: console

        ./replace_fpga.sh

#. Red Pitaya should be restarted to load the new FPGA image.

    .. code-block:: console

        reboot

#. Please note that this will **replace** the original FPGA image. To **revert to the original FPGA image**, run the script without any parameters as none of the methods in the next chapter will work.



Reverting to original FPGA image
==================================

If you want to roll back to the official Red Pitaya FPGA program, run the following command:

.. tabs::

    .. group-tab:: OS version 1.04 or older

        .. code-block:: shell-session

            redpitaya> cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg

    .. group-tab:: OS version 2.00 or newer

        .. code-block:: shell-session

            redpitaya> overlay.sh v0.94

or simply restart your Red Pitaya.



.. substitutions:

.. |batch_file_topic_1| raw:: html

    <a href="https://superuser.com/questions/601282/%cc%81-is-not-recognized-as-an-internal-or-external-command" target="_blank">́╗┐' is not recognized as an internal or external command</a>

.. |batch_file_topic_2| raw:: html

    <a href="https://devblogs.microsoft.com/oldnewthing/20210726-00/?p=105483" target="_blank">Diagnosing why your batch file prints a garbage character, one character, and nothing more</a>

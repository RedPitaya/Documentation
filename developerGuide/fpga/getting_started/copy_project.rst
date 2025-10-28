.. _fpga_copy_project:

###################################
Creating a copy for a new project
###################################

Each of the projects and tutorials has it's own directory, which is forcibly cleared each time a "new" project with the same name is created.

For example, running the following command:

.. code-block:: bash

    make project PRJ=v0.94 MODEL=Z10

When the project already exists (perhaps it is just the LED blink project or a new custom FPGA image). Will revert everything in the
v0.94 project located in the **RedPitaya-FPGA/prj/v0.94** directory back to the original state, which can cause problems when project backups
or multiple project versions are required.

Here is how you can separate create a separate project folder that contains all the code of the normal v0.94 project:

#. Create a new folder called "New_Project" in **RedPitaya-FPGA/prj/**.
#. Copy all files from **RedPitaya-FPGA/prj/v0.94** into the newly created folder.
#. Add or copy any existing *VHDL* or *Verilog* files to the "New_project/rtl" directory.
#. Create a new folder named **tbn** inside the *New_project* directory. This is where any testbench files should be placed.
#. Make a copy of the **red_pitaya_vivado_project_Z10.tcl** script from the **RedPitaya-FPGA** directory and rename it to **new_project.tcl**.

#. If the **new_project.tcl** is located in a different directory, edit the following lines of code:

    .. code-block:: bash

        cd prj/$prj_name                    → cd <new_path_to_project>/$prj_name
        set path_brd ./../brd               → set path_brd <path_to_brd_directory>/brd
        set path_sdc ../../sdc              → set path_sdc <path_to_sdc_directory>/sdc
        add_files  ../../$path_rtl          → add_files  <path_to_rtl_directory>/$path_rtl

    Add a new **tbn** variable

    .. code-block:: bash

        set path_tbn tbn

    And the simulation files after the *add_files $path_bd* line:

    .. code-block:: bash

        add_files -fileset sim_1 -norecurse $path_tbn/red_pitaya_proc_tb.vhd

    Short description of each directory:

    - **brd** directory contains board information files (.xml)
    - **sdc** contains the constraints files (*.xdc*)
    - **rtl** contains source files
    - **tbn** cointains simulation files (also called testbench)

#. Finally, we can create a new project by running the following code:

    .. code-block:: bash

        make project 

        vivado -source New_projct.tcl -tclargs <PRJ_project_flag>

#. If everything is set up correctly, you can run a **Generate Bitstream** command in Vivado to check if the project is working as expected.

.. _fpga_simulation:


.. !! Verify and add pictures where needed

#############################
FPGA Simulation
#############################

Simulation is a critical part of FPGA development that allows you to verify your design's functionality before deploying to hardware. 
This guide covers setting up and running simulations for Red Pitaya FPGA projects using ModelSim.

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

**********************************
Overview
**********************************

Why Simulate?
=============

**Advantages of simulation:**

- **Faster debugging** - Find and fix issues in minutes instead of hours
- **Verify before hardware** - Test functionality without FPGA programming
- **Test edge cases** - Simulate conditions difficult to reproduce on hardware
- **Waveform analysis** - Observe internal signals not accessible on hardware
- **Regression testing** - Automated verification of design changes
- **Documentation** - Generate waveforms for technical documentation

**When to simulate:**

- Before first hardware implementation
- After any significant design changes
- When debugging unexpected hardware behavior
- For automated testing in CI/CD pipelines
- To verify timing and signal integrity

|

Simulation vs. Hardware Testing
================================

.. list-table::
    :header-rows: 1
    :widths: 40 30 30

    * - Aspect
      - Simulation
      - Hardware
    * - **Speed**
      - Slower (complex designs can take hours)
      - Real-time operation
    * - **Visibility**
      - All internal signals visible
      - Only external pins accessible (unless using ILA)
    * - **Cost**
      - Free (software only)
      - Requires hardware, power, equipment
    * - **Setup**
      - Quick (edit code, simulate)
      - Slower (build, program, connect)
    * - **Accuracy**
      - Depends on model fidelity
      - Real-world behavior
    * - **Debugging**
      - Easy (rewind, inspect any signal)
      - Limited (real-time only)

**Best practice:** Simulate first, then verify on hardware.

|

**********************************
Simulation Tools
**********************************

Available Simulators
====================

Red Pitaya FPGA projects support multiple simulation tools:

ModelSim (Recommended)
----------------------

**ModelSim-Altera Starter Edition** - Free version from Intel/Altera

**Advantages:**

- Free to use
- Fast compilation and simulation
- Excellent waveform viewer
- Well-documented
- Industry-standard tool

**Limitations:**

- Limited to 10,000 lines of code (sufficient for most Red Pitaya modules)
- Linux version only (use WSL on Windows)

**Download** `ModelSim-Altera Starter Edition 20.1.1 <https://www.intel.com/content/www/us/en/software-kit/750666/modelsim-intel-fpgas-standard-edition-software-version-20-1-1.html>`_

Vivado Simulator (XSIM)
------------------------

**Built into Vivado** - No separate installation needed

**Advantages:**

- Integrated with Vivado IDE
- No installation required
- Direct project integration

**Limitations:**

- Slower than ModelSim for complex designs
- Waveform viewer less feature-rich
- Command-line usage less convenient

Questa Sim (Commercial)
-----------------------

**Professional version** - Paid license required

**Advantages:**

- Advanced debugging features
- Better performance on large designs
- Full SystemVerilog support

**Use case:** Production environments with complex verification needs

|

**********************************
ModelSim Installation
**********************************

Prerequisites
=============

**System requirements:**

- **OS:** Ubuntu 18.04/20.04 or newer (use WSL on Windows)
- **RAM:** 4 GB minimum, 8 GB recommended
- **Disk space:** 2 GB for ModelSim installation
- **Display:** X11 server for GUI (Windows users: VcXsrv or Xming)

|

Step 1: Download ModelSim
==========================

1. Visit Intel FPGA download page:
   
   https://www.intel.com/content/www/us/en/software-kit/750666/modelsim-intel-fpgas-standard-edition-software-version-20-1-1.html

2. Select **ModelSim-Intel® FPGAs Standard Edition Software Version 20.1.1**

3. Choose **Individual Files** tab

4. Download **ModelSim-Intel® FPGA Edition (includes Starter Edition)**
   
   - File: ``ModelSimSetup-20.1.1.720-linux.run``
   - Size: ~1.5 GB

.. note::

    Account registration may be required. It's free for Starter Edition.

|

Step 2: Install on Ubuntu/Linux
================================

**Make installer executable:**

.. code-block:: bash

    chmod +x ModelSimSetup-20.1.1.720-linux.run

**Run installer:**

.. code-block:: bash

    ./ModelSimSetup-20.1.1.720-linux.run

**Follow installation wizard:**

1. Accept license agreement
2. Choose installation directory (default: ``$HOME/intelFPGA/20.1``)
3. Select **ModelSim - Intel FPGA Starter Edition**
4. Complete installation

**Default installation path:**

.. code-block:: text

    $HOME/intelFPGA/20.1/modelsim_ase/

|

Step 3: Post-Installation Setup (Ubuntu)
=========================================

**Fix path issue:**

Ubuntu installation doesn't create the expected ``linux_rh60`` symlink. Create it manually:

.. code-block:: bash

    cd $HOME/intelFPGA/20.1/modelsim_ase/
    ln -s linux linux_rh60

**Install required 32-bit libraries:**

.. code-block:: bash

    sudo dpkg --add-architecture i386
    sudo apt-get update
    sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
    sudo apt-get install libxft2:i386 libxext6:i386 libxtst6:i386

**Add to PATH (optional but recommended):**

Edit ``~/.bashrc``:

.. code-block:: bash

    nano ~/.bashrc

Add at the end:

.. code-block:: bash

    # ModelSim
    export PATH=$HOME/intelFPGA/20.1/modelsim_ase/bin:$PATH

Save and reload:

.. code-block:: bash

    source ~/.bashrc

|

Step 4: Verify Installation
============================

**Check ModelSim version:**

.. code-block:: bash

    vsim -version

**Expected output:**

.. code-block:: text

    Model Technology ModelSim - Intel FPGA Starter Edition vsim 2020.1 Simulator 2020.02 Feb 28 2020
    Linux 4.15.0-135-generic #139-Ubuntu SMP Mon Jan 18 17:38:24 UTC 2021 x86_64

**Test GUI launch:**

.. code-block:: bash

    vsim &

ModelSim GUI should open. Close it after verifying.

|

Windows Installation (via WSL)
===============================

**Install WSL2:**

.. code-block:: powershell

    # Run in PowerShell as Administrator
    wsl --install -d Ubuntu-20.04

**Install X Server for GUI:**

1. Download and install **VcXsrv** or **Xming**
2. Launch X Server with default settings
3. In WSL, set DISPLAY:

   .. code-block:: bash
   
       echo 'export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '"'"'{print $2}'"'"'):0' >> ~/.bashrc
       source ~/.bashrc

**Follow Ubuntu installation steps above**

|

Troubleshooting Installation
=============================

**"vsim: command not found"**

.. code-block:: bash

    # Add to PATH manually
    export PATH=$HOME/intelFPGA/20.1/modelsim_ase/bin:$PATH

**"libxft.so.2: cannot open shared object file"**

.. code-block:: bash

    sudo apt-get install libxft2:i386

**GUI doesn't appear (WSL)**

.. code-block:: bash

    # Check X Server is running on Windows
    # Verify DISPLAY variable
    echo $DISPLAY
    
    # Test with simple app
    sudo apt-get install x11-apps
    xeyes

**"License file not found"**

Starter Edition should work without license. If prompted:

.. code-block:: bash

    # Set license variable (Starter Edition uses built-in license)
    export LM_LICENSE_FILE=$HOME/intelFPGA/20.1/modelsim_ase/license.dat

|

**********************************
Running Simulations
**********************************

Simulation Workflow
===================

**Basic workflow:**

1. Navigate to simulation directory
2. Choose testbench to run
3. Compile design files
4. Run simulation
5. View waveforms
6. Analyze results

|

Red Pitaya Simulation Structure
================================

**Simulation directory:**

.. code-block:: text

    RedPitaya-FPGA/
    └── fpga/
        └── sim/
            ├── Makefile              # Main simulation control
            ├── rtl_sim.tcl           # ModelSim configuration
            ├── top_tb.sv             # Top-level testbench
            ├── top_tb.tcl            # Waveform configuration
            ├── axi4_if.sv            # AXI bus testbench
            ├── axi4_slave_tb.sv      # AXI slave testbench
            └── ...                   # Other testbenches

**Navigate to simulation directory:**

.. code-block:: bash

    cd RedPitaya-FPGA/fpga/sim

|

Basic Simulation Commands
==========================

**Run simulation without waveform:**

.. code-block:: bash

    make top_tb

This compiles and runs the simulation, displaying results in terminal.

**Run simulation with waveform window:**

.. code-block:: bash

    make top_tb WAV=1

Opens ModelSim GUI with waveform viewer and pre-configured signal groups.

**Run with custom simulation time:**

.. code-block:: bash

    make top_tb SIM_TIME=1us

Default simulation time can be overridden.

**Clean simulation files:**

.. code-block:: bash

    make clean

Removes compiled libraries and simulation artifacts.

|

Available Testbenches
=====================

**Common testbenches in Red Pitaya FPGA:**

.. list-table::
    :header-rows: 1
    :widths: 30 70

    * - Testbench
      - Description
    * - ``top_tb``
      - Top-level system testbench (complete FPGA)
    * - ``axi4_slave_tb``
      - AXI4 slave interface testbench
    * - ``axi4_if``
      - AXI4 master/slave communication testbench
    * - ``red_pitaya_scope_tb``
      - Oscilloscope module testbench
    * - ``red_pitaya_asg_tb``
      - Arbitrary signal generator testbench

.. note::

    Available testbenches depend on your Red Pitaya FPGA version. Check ``fpga/sim/`` for complete list.

|

Understanding Simulation Output
================================

**Console output during simulation:**

.. code-block:: text

    # Compilation phase
    vlog -work work ../rtl/red_pitaya_top.sv
    Model Technology ModelSim - Intel FPGA Starter Edition vlog 2020.1 Compiler 2020.02 Feb 28 2020
    -- Compiling module red_pitaya_top
    
    # Elaboration phase  
    vsim -t 1ps -L work work.top_tb
    
    # Simulation run
    # Time: 0 ns  Iteration: 0  Instance: /top_tb
    # ** Note: Reset asserted
    #    Time: 100 ns  Iteration: 0  Instance: /top_tb
    # ** Note: Data written: 0xDEADBEEF
    #    Time: 1000 ns  Iteration: 0  Instance: /top_tb

**Successful simulation ends with:**

.. code-block:: text

    # ** Note: Simulation finished
    #    Time: 10000 ns  Iteration: 0  Instance: /top_tb
    # Success: Simulation completed without errors

**Errors appear as:**

.. code-block:: text

    # ** Error: Assertion failed at address 0x1000
    #    Time: 5000 ns  Iteration: 0  Instance: /top_tb
    # Break in Module top_tb at top_tb.sv line 123

|


**********************************
Waveform Analysis
**********************************

Opening Waveform Viewer
=======================

**Automatic opening (with WAV=1):**

.. code-block:: bash

    make top_tb WAV=1

**Manual opening in ModelSim:**

1. Launch ModelSim: ``vsim &``
2. File → Open → Select workspace directory
3. View → Wave window

|

Waveform Configuration Scripts
===============================

Many testbenches include ``.tcl`` scripts to organize waveforms:

**Example: ``top_tb.tcl``**

.. code-block:: tcl

    # Add clock and reset
    add wave -noupdate -divider {Clock and Reset}
    add wave -format Logic /top_tb/clk
    add wave -format Logic /top_tb/rstn
    
    # Add AXI signals
    add wave -noupdate -divider {AXI Interface}
    add wave -format Literal -radix hexadecimal /top_tb/axi_awaddr
    add wave -format Logic /top_tb/axi_awvalid
    add wave -format Logic /top_tb/axi_awready
    
    # Add ADC data
    add wave -noupdate -divider {ADC Data}
    add wave -format Literal -radix decimal /top_tb/adc_dat_a
    add wave -format Literal -radix decimal /top_tb/adc_dat_b

**These scripts automatically run when you use** ``WAV=1``

|

Reading Waveforms
=================

**Basic waveform elements:**

.. code-block:: text

    Signal Name         │ Waveform
    ────────────────────┼───────────────────────────────
    clk                 │  ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐
                        │ ─┘ └─┘ └─┘ └─┘ └─┘ └─
    rstn                │ ────┐
                        │     └──────────────────────
    data[15:0]          │ XXXX│ 0xABCD │ 0x1234 │XXXX
                        │     ▼        ▼        ▼

**Signal states:**

- **High (1):** Logic high
- **Low (0):** Logic low
- **X:** Unknown/uninitialized
- **Z:** High impedance (tri-state)
- **Transitions:** Rising/falling edges

**Radix options:**

- **Binary:** 0b1010_1100
- **Hexadecimal:** 0xAC (most common)
- **Decimal:** 172
- **Unsigned/Signed:** Interpretation of value

|

Waveform Navigation
===================

**Zoom controls:**

- **Zoom In:** Ctrl + Plus or mouse wheel
- **Zoom Out:** Ctrl + Minus
- **Zoom Full:** F (fit all time)
- **Zoom Range:** Select time range, press Z

**Cursors and measurements:**

1. **Main cursor (yellow):** Click on waveform
2. **Add reference cursor:** Right-click → Insert Cursor
3. **Measure time delta:** Distance between cursors shows Δt

**Signal grouping:**

- Create groups for related signals (e.g., "AXI Bus", "ADC Interface")
- Collapse/expand groups to manage visibility
- Scripts like ``top_tb.tcl`` pre-organize signals

|

Exporting Waveforms
===================

**Save waveform view:**

.. code-block:: tcl

    # In ModelSim TCL console
    write format wave -window .main_pane.wave.interior.cs.body.pw.wf simulation.vcd

**Export as image:**

1. View → Wave window
2. File → Print
3. Select "Print to File"
4. Choose format (PNG, PDF, PostScript)

|


**********************************
Creating Custom Testbenches
**********************************

Testbench Structure
===================

**Basic SystemVerilog testbench template:**

.. code-block:: systemverilog

    `timescale 1ns / 1ps
    
    module my_module_tb;
    
        //----------------------------------------------------------------------
        // Parameters
        //----------------------------------------------------------------------
        parameter CLK_PERIOD = 8;  // 125 MHz = 8 ns period
        parameter DATA_WIDTH = 14;
        
        //----------------------------------------------------------------------
        // Signals
        //----------------------------------------------------------------------
        logic                   clk;
        logic                   rstn;
        logic [DATA_WIDTH-1:0]  data_in;
        logic [DATA_WIDTH-1:0]  data_out;
        logic                   valid;
        
        //----------------------------------------------------------------------
        // DUT (Device Under Test) Instantiation
        //----------------------------------------------------------------------
        my_module #(
            .DATA_WIDTH (DATA_WIDTH)
        ) dut (
            .clk      (clk),
            .rstn     (rstn),
            .data_i   (data_in),
            .data_o   (data_out),
            .valid_o  (valid)
        );
        
        //----------------------------------------------------------------------
        // Clock Generation
        //----------------------------------------------------------------------
        initial begin
            clk = 1'b0;
            forever #(CLK_PERIOD/2) clk = ~clk;
        end
        
        //----------------------------------------------------------------------
        // Reset Generation
        //----------------------------------------------------------------------
        initial begin
            rstn = 1'b0;
            repeat(10) @(posedge clk);
            rstn = 1'b1;
        end
        
        //----------------------------------------------------------------------
        // Test Stimulus
        //----------------------------------------------------------------------
        initial begin
            // Initialize signals
            data_in = '0;
            
            // Wait for reset deassertion
            wait(rstn == 1'b1);
            @(posedge clk);
            
            // Apply test vectors
            for (int i = 0; i < 100; i++) begin
                @(posedge clk);
                data_in = $random;
            end
            
            // Wait some cycles
            repeat(10) @(posedge clk);
            
            // Finish simulation
            $display("Simulation completed successfully");
            $finish;
        end
        
        //----------------------------------------------------------------------
        // Waveform Dump (for viewing in ModelSim)
        //----------------------------------------------------------------------
        initial begin
            $dumpfile("my_module_tb.vcd");
            $dumpvars(0, my_module_tb);
        end
        
        //----------------------------------------------------------------------
        // Assertions and Checks
        //----------------------------------------------------------------------
        // Check that output never goes X
        always @(posedge clk) begin
            if (rstn && valid) begin
                if ($isunknown(data_out)) begin
                    $error("Output contains X values at time %t", $time);
                    $stop;
                end
            end
        end
        
    endmodule

|

Essential Testbench Components
===============================

Clock Generation
----------------

**125 MHz clock (Red Pitaya's main clock):**

.. code-block:: systemverilog

    parameter CLK_PERIOD = 8;  // 8 ns = 125 MHz
    
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

**Multiple clocks:**

.. code-block:: systemverilog

    // Fast clock: 250 MHz
    initial begin
        clk_fast = 0;
        forever #2 clk_fast = ~clk_fast;  // 4 ns period
    end
    
    // Slow clock: 10 MHz
    initial begin
        clk_slow = 0;
        forever #50 clk_slow = ~clk_slow;  // 100 ns period
    end

Reset Handling
--------------

**Proper reset sequence:**

.. code-block:: systemverilog

    initial begin
        rstn = 0;
        
        // Wait several clock cycles
        repeat(10) @(posedge clk);
        
        // Deassert reset
        rstn = 1;
        
        $display("Reset released at time %t", $time);
    end

**With both sync and async reset:**

.. code-block:: systemverilog

    initial begin
        rst_async = 1;  // Active high
        rst_sync  = 1;
        
        #100;  // Async reset
        rst_async = 0;
        
        repeat(5) @(posedge clk);
        rst_sync = 0;  // Sync reset release
    end

Stimulus Generation
-------------------

**Pattern generators:**

.. code-block:: systemverilog

    // Counter pattern
    initial begin
        wait(rstn);
        for (int i = 0; i < 256; i++) begin
            @(posedge clk);
            data_in = i;
        end
    end
    
    // Random pattern
    initial begin
        wait(rstn);
        repeat(1000) begin
            @(posedge clk);
            data_in = $random;
        end
    end
    
    // From file
    initial begin
        integer file;
        file = $fopen("test_vectors.txt", "r");
        while (!$feof(file)) begin
            @(posedge clk);
            $fscanf(file, "%h", data_in);
        end
        $fclose(file);
    end

Result Checking
---------------

**Assertions:**

.. code-block:: systemverilog

    // Immediate assertion (combinational)
    assert (data_out <= MAX_VALUE) else
        $error("Output exceeded maximum at time %t", $time);
    
    // Concurrent assertion (sequential)
    property valid_data;
        @(posedge clk) disable iff (!rstn)
        valid |-> (data_out inside {[0:MAX_VALUE]});
    endproperty
    assert property (valid_data);

**Self-checking testbench:**

.. code-block:: systemverilog

    // Expected vs. actual comparison
    logic [15:0] expected;
    
    always @(posedge clk) begin
        if (valid) begin
            expected = calculate_expected(data_in);
            if (data_out !== expected) begin
                $error("Mismatch: expected=%h, got=%h at time=%t", 
                       expected, data_out, $time);
                error_count++;
            end
        end
    end
    
    // Final report
    final begin
        if (error_count == 0)
            $display("PASS: All tests passed");
        else
            $display("FAIL: %0d errors detected", error_count);
    end

|

Adding Testbench to Makefile
=============================

**Edit ``fpga/sim/Makefile``:**

.. code-block:: makefile

    # Add your testbench to TARGETS
    TARGETS = top_tb axi4_slave_tb my_module_tb
    
    # Add compilation rule
    my_module_tb: $(RTL_SRC) my_module_tb.sv
    	@echo "Compiling my_module_tb..."
    	vlog -work work ../rtl/my_module.sv
    	vlog -work work my_module_tb.sv
    	vsim -c -do "run -all; quit" work.my_module_tb

**Run your testbench:**

.. code-block:: bash

    make my_module_tb

|


**********************************
Advanced Simulation Techniques
**********************************

Using Tasks and Functions
==========================

**Reusable test procedures:**

.. code-block:: systemverilog

    // Task for AXI write transaction
    task automatic axi_write(
        input  [31:0] addr,
        input  [31:0] data
    );
        @(posedge clk);
        axi_awaddr  = addr;
        axi_wdata   = data;
        axi_awvalid = 1;
        axi_wvalid  = 1;
        
        wait(axi_awready && axi_wready);
        @(posedge clk);
        axi_awvalid = 0;
        axi_wvalid  = 0;
    endtask
    
    // Use in testbench
    initial begin
        wait(rstn);
        axi_write(32'h1000, 32'hDEADBEEF);
        axi_write(32'h1004, 32'hCAFEBABE);
    end

**Function for calculations:**

.. code-block:: systemverilog

    function automatic [15:0] calculate_crc(
        input [7:0] data
    );
        logic [15:0] crc;
        // CRC calculation logic
        return crc;
    endfunction

|

Code Coverage
=============

**Enable coverage collection:**

.. code-block:: bash

    # Compile with coverage
    vlog -cover sbceft my_module.sv
    
    # Simulate with coverage
    vsim -coverage my_module_tb
    
    # View coverage report
    coverage report -file coverage.txt

**Coverage types:**

- **Statement:** Lines of code executed
- **Branch:** Decision paths taken
- **Condition:** Boolean expressions evaluated
- **Expression:** Sub-expressions evaluated
- **FSM:** State machine transitions
- **Toggle:** Signal bit transitions

|

Constrained Random Testing
===========================

**SystemVerilog randomization:**

.. code-block:: systemverilog

    class axi_transaction;
        rand bit [31:0] addr;
        rand bit [31:0] data;
        
        // Constraints
        constraint addr_range {
            addr inside {[32'h4000_0000:32'h4FFF_FFFF]};
            addr[1:0] == 2'b00;  // Word-aligned
        }
        
        constraint data_values {
            data dist {
                [0:100]       := 70,  // 70% in 0-100
                [101:1000]    := 20,  // 20% in 101-1000
                [1001:$]      := 10   // 10% above 1000
            };
        }
    endclass
    
    // Generate random transactions
    axi_transaction tr = new();
    repeat(100) begin
        assert(tr.randomize());
        axi_write(tr.addr, tr.data);
    end

|

Performance Profiling
======================

**Measure throughput:**

.. code-block:: systemverilog

    integer cycle_count = 0;
    integer data_count = 0;
    
    always @(posedge clk) begin
        cycle_count++;
        if (valid) data_count++;
    end
    
    final begin
        real throughput;
        throughput = real'(data_count) / real'(cycle_count) * 100.0;
        $display("Throughput: %0.2f%%", throughput);
    end

**Timing measurements:**

.. code-block:: systemverilog

    time start_time, end_time, delta_time;
    
    initial begin
        wait(start_event);
        start_time = $time;
        
        wait(end_event);
        end_time = $time;
        
        delta_time = end_time - start_time;
        $display("Latency: %0t", delta_time);
    end

|


**********************************
Troubleshooting Simulations
**********************************

Common Compilation Errors
==========================

**"Module not found"**

.. code-block:: text

    ** Error: (vlog-2110) Illegal reference to module 'my_module'.

**Solution:**

.. code-block:: bash

    # Ensure RTL file is compiled before testbench
    vlog -work work ../rtl/my_module.sv
    vlog -work work my_module_tb.sv

**"Undeclared identifier"**

.. code-block:: text

    ** Error: (vlog-2730) Undefined variable: 'signal_name'.

**Solution:** Check signal declarations, typos, or scope issues.

**"Syntax error"**

.. code-block:: text

    ** Error: (vlog-13069) Near ";": syntax error, unexpected ';'.

**Solution:** Check for missing semicolons, commas, or mismatched parentheses.

|

Runtime Errors
==============

**X (Unknown) Propagation**

.. code-block:: text

    ** Warning: NUMERIC_STD."=": metavalue detected, returning FALSE

**Causes:**

- Uninitialized registers
- Missing reset
- Combinational loops

**Debug:**

.. code-block:: systemverilog

    // Add initialization
    initial begin
        my_signal = 0;
    end
    
    // Check for X values
    always @(posedge clk) begin
        if ($isunknown(my_signal)) begin
            $error("X detected in my_signal at time %t", $time);
        end
    end

**Infinite Loops**

.. code-block:: text

    # ** Fatal: (vsim-3421) Value 0 is too small for time precision (1ps).

**Solution:** Add time delays in initial/always blocks:

.. code-block:: systemverilog

    // BAD - infinite zero-delay loop
    initial begin
        while (condition) begin
            // No time advance!
        end
    end
    
    // GOOD - proper time advance
    initial begin
        while (condition) begin
            #10;  // Or @(posedge clk)
        end
    end

|

Memory Issues
=============

**"Out of memory"**

**Solutions:**

- Reduce simulation time
- Limit waveform dump scope
- Increase system RAM
- Close unnecessary programs

**Selective waveform dumping:**

.. code-block:: systemverilog

    initial begin
        // Only dump specific module
        $dumpfile("waves.vcd");
        $dumpvars(1, my_module_tb.dut);  // Depth 1, only DUT
    end

|

Assertion Failures
==================

**Handle assertion failures gracefully:**

.. code-block:: systemverilog

    assert property (@(posedge clk) valid |-> data_ready) else
        $error("Data not ready when valid asserted at time %t", $time);
    
    // Continue simulation despite failures
    $assertkill;  // In initial block to prevent simulation stop

|


**********************************
Best Practices
**********************************

Simulation Strategy
===================

**1. Start Simple**

- Test individual modules before integrating
- Use simple stimulus first, then increase complexity
- Verify basic functionality before edge cases

**2. Modular Testbenches**

- Create reusable verification components
- Use tasks/functions for common operations
- Separate stimulus generation from checking

**3. Comprehensive Testing**

- Test reset conditions
- Test boundary values (min, max)
- Test error conditions and edge cases
- Use random testing for coverage

**4. Documentation**

- Comment testbench structure and purpose
- Document test scenarios
- Keep waveform configuration scripts
- Maintain expected results documentation

|

Code Organization
=================

**Recommended directory structure:**

.. code-block:: text

    fpga/
    └── sim/
        ├── Makefile              # Build automation
        ├── rtl_sim.tcl           # ModelSim config
        ├── tb/                   # Testbenches
        │   ├── top_tb.sv
        │   ├── module_tb.sv
        │   └── ...
        ├── waves/                # Waveform scripts
        │   ├── top_tb.tcl
        │   └── ...
        └── vectors/              # Test vectors
            ├── input_data.txt
            └── expected_output.txt

**Naming conventions:**

- Testbenches: ``<module>_tb.sv``
- Waveform scripts: ``<module>_tb.tcl``
- Test vectors: ``<module>_vectors.txt``

|

Debugging Workflow
==================

**When simulation fails:**

1. **Read error messages carefully** - Line numbers and descriptions
2. **Check recent changes** - What was modified?
3. **Simplify stimulus** - Reduce to minimum failing case
4. **Add debug prints** - $display statements
5. **Examine waveforms** - Look for unexpected signal values
6. **Check assumptions** - Verify reset, clock, timing
7. **Isolate problem** - Test submodules individually

**Debug printing:**

.. code-block:: systemverilog

    // Conditional debug messages
    `ifdef DEBUG
        $display("DEBUG: addr=%h data=%h at time=%t", addr, data, $time);
    `endif
    
    // Compile with: vlog +define+DEBUG

|

Simulation Performance
======================

**Optimize simulation speed:**

- Compile with optimization flags: ``vlog -O5``
- Limit waveform dump scope
- Use shorter simulation times during development
- Disable unnecessary assertions
- Use ``-novopt`` flag carefully (may slow down)

**Parallel simulations:**

.. code-block:: bash

    # Run multiple testbenches in parallel
    make top_tb &
    make axi4_tb &
    make scope_tb &
    wait

|


********************************************
Integration with Red Pitaya Development
********************************************

Simulating Red Pitaya Modules
==============================

**Example: Oscilloscope module**

.. code-block:: bash

    cd RedPitaya-FPGA/fpga/sim
    
    # Simulate oscilloscope with waveforms
    make red_pitaya_scope_tb WAV=1

**Example: Signal generator**

.. code-block:: bash

    make red_pitaya_asg_tb WAV=1

|

Vivado Integration
==================

**Run simulation from Vivado:**

1. Open project in Vivado
2. Flow Navigator → Simulation → Run Simulation
3. Select **Run Behavioral Simulation**
4. Vivado launches XSIM with waveforms

**Note:** Red Pitaya Makefiles use ModelSim by default. To use XSIM, modify simulation scripts.

|

CI/CD Integration
=================

**Automated testing in CI pipeline:**

.. code-block:: bash

    #!/bin/bash
    # ci_test_simulation.sh
    
    cd fpga/sim
    
    # Run all testbenches
    for tb in top_tb axi4_slave_tb; do
        echo "Running $tb..."
        make $tb > ${tb}.log 2>&1
        
        if grep -q "Error" ${tb}.log; then
            echo "FAIL: $tb"
            exit 1
        else
            echo "PASS: $tb"
        fi
    done
    
    echo "All simulations passed"
    exit 0

**GitLab CI example:**

.. code-block:: yaml

    simulate:
      stage: test
      script:
        - source /opt/intelFPGA/20.1/modelsim_ase/settings.sh
        - cd fpga/sim
        - make top_tb
        - make axi4_slave_tb
      artifacts:
        when: always
        paths:
          - fpga/sim/*.log
          - fpga/sim/*.vcd

|


**********************************
Related Documentation
**********************************

**FPGA Development:**

- :ref:`fpga_create_project` - Creating FPGA projects
- :ref:`fpga_modify_project` - Modifying existing projects
- :ref:`fpga_jtag_programming` - Programming via JTAG
- :ref:`fpga_reprogramming` - Programming via SSH

**Advanced Topics:**

- :ref:`device_tree` - Device tree configuration
- :ref:`signal_mapping` - Hardware connections

**External Resources:**

- `ModelSim User Manual <https://ww1.microchip.com/downloads/aemdocuments/documents/fpga/ProductDocuments/UserGuides/modelsim_user_v11p7.pdf>`_
- `SystemVerilog for Verification <https://www.chipverify.com/systemverilog/systemverilog-tutorial>`_
- `Vivado Simulator User Guide (UG900) <https://www.xilinx.com/support/documents/sw_manuals/xilinx2022_1/ug900-vivado-logic-simulation.pdf>`_

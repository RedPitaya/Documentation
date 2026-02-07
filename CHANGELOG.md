---
orphan: true
---

# Change Log

All notable changes to this project will be documented in this file.

## February 2026 - Update 1

**Major updates:**

- **Streaming application documentation completely reorganized:**

  - Split into four main sections: Configuration, Usage, Advanced, and Reference.
  - Added new web interface streaming documentation.
  - Added multiboard streaming setup guide.
  - New streaming API examples and quickstart guide.
  - Added DAC streaming examples.
  - Improved technical details and limitations documentation.

- **Software documentation restructured:**

  - Reorganized into: Getting Started, Configuration, App Development, System Development, and Troubleshooting.
  - New "Getting Started" section with console access, SSH, and WSL setup guides.
  - New "Configuration" section consolidating GPIO, network, SPI, TFT, and remote deployment.
  - Separated "App Development" from "System Development".
  - Created dedicated troubleshooting section with OS compatibility guide.

- **New documentation added:**

  - Service management guide (systemd services, starting/stopping services, boot configuration).
  - C++ compiler and Make utility setup for Windows (MinGW-w64, Chocolatey).
  - WSL (Windows Subsystem for Linux) setup guide for development.
  - Board identification guide with visual reference images for all Red Pitaya models.
  - Advanced SD card preparation instructions.
  - Matplotlib update script for fixing NumPy 2.x compatibility issues.

- **Hardware documentation improvements:**

  - Reorganized hardware measurements into dedicated folders for each board model.
  - Moved fast analog input/output measurements from hw_specs to separate measurement sections.
  - Improved Gen 2 FAQ with new images (JP5 position, fast differential pairs).
  - Updated Gen 2 hardware specifications page structure.

- **Marketplace applications:**

  - Added Linien (laser spectroscopy and frequency stabilization) application documentation.
  - Removed deprecated PID application documentation.
  - Updated documentation for multiple marketplace apps (LTI, DAQ server, DSP, etc.).

- **Quick Start improvements:**

  - New board identification guide with visual references for all models.
  - Enhanced troubleshooting section with Balena Etcher error images.
  - Advanced SD card preparation instructions including partition management.
  - Updated board sticker reference images.
  - Browser address bar example image added.

**Minor updates:**

- Reorganized FPGA documentation (moved simulation guide, added intro page).
- Added new FPGA register set for 4-input boards (v0.94_cs2_4input).
- Updated command line utility documentation across all tools.
- Improved Logic Analyzer and CAN examples.
- Updated SCPI and API command documentation.
- Enhanced multichannel synchronization documentation.
- Updated QSPI eMMC module documentation.
- Sensor extension module documentation updates.
- Fixed various image paths and references throughout documentation.
- Grammar and syntax improvements across multiple pages.
- Updated calibration and network manager documentation.
- Improved remote control and Jupyter notebook documentation.

**File structure changes:**

- Moved webapp documentation from `build/webapp/` to `app_development/webapp/`.
- Relocated console and SSH documentation to `getting_started/`.
- Moved network, GPIO, SPI, TFT configuration to `configuration/` folder.
- Reorganized E3 software documentation into `system_development/e3_software/`.
- Moved known software issues to `troubleshooting/known_issues/`.
- Restructured streaming application documentation with new folder hierarchy.
- Relocated hardware measurements to board-specific folders.

**Links affected:**

- All links to streaming application pages (complete restructure with new paths).
- Links to software build/configuration pages (moved to new folder structure).
- Links to console/SSH documentation (relocated to getting_started).
- Links to hardware measurements (moved from hw_specs to measurements folders).
- Links to webapp development docs (new path structure).
- Links to E3 board software documentation (new organization).
- Deprecated PID marketplace application links.

## December 2025 - Update 1

**Updates:**

- Released OS version 2025.2 documentation.
- Added FPGA register sets for release 2.07-48 (all board variants).
- Updated SD card preparation instructions for latest OS version.
- Minor SCPI command updates (Board, DMM commands).

## November 2025 - Update 1

**Major updates:**

- **Gen 2 hardware documentation reorganized:**

  - Complete restructure of all Gen 2 board documentation pages (125-14 Gen2, 125-14 Gen2 Pro, 125-14 Gen2 Z7020 Pro, 125-14 TI, 65-16 TI).
  - Created common specification includes for Gen 2 boards (E1/E2/E3 connectors, boot options, sync connectors, power supply, slow analog I/O, external ADC clock).
  - Added new board images and pinout diagrams for all Gen 2 models.
  - Added TI board images (front and side views).
  - Improved Gen 2 fast I/O documentation with new schematics.
  - Updated Gen 2 comparison table.

- **Calibration documentation expanded:**

  - Significantly expanded calibration procedures and documentation.

- **FPGA documentation updates:**

  - Added new register sets for release 2.07-48 (streaming app, v0.94 registers for all board variants).
  - Updated register documentation for 2.00-18 release.
  - Added "use last sample value" register functionality.
  - Updated FPGA device tree and JTAG programming documentation.

- **New SCPI commands:**

  - Added DMA/GEN commands.
  - Added SOUR<n>:RISE:TIME, SOUR<n>:FALL:TIME commands and queries for signal generation.

**Minor updates:**

- Updated SD card preparation instructions (release 2025.2).
- Updated command line utilities documentation (acquire, spectrum).
- Updated click shield examples documentation.
- Updated DMM SCPI commands.
- Added board identification SCPI command.
- Improved CSS styling for better documentation readability.
- Updated streaming application documentation.
- Updated external booting instructions for E3 board.
- Fixed various links throughout documentation.
- Updated intro and index pages.
- Minor fixes to software and FPGA documentation structure.

**Links affected:**

- Gen 2 board documentation pages (complete restructure with new common includes).

## July 2025 - Update 2

**Major updates:**

- Updated streaming application documentation.
- Separated Multichannel synchronisation (click shield and X-channel) into a separate section.
- DAC streaming added.
- Deep memory generation instructions added.
- Combined Deep Memory Acquisition and Deep Memory Generation into a single section called Deep Memory Mode.
- Added functionality overview for the commands under each command table section (currently only for SPI). Looking to expand this to all commands in the future.
- Gen 2 supported features and apps.
- Added links to measurements under each board model docs.
- Added TI board documentation.
- Gen 2 FAQ section added.
- Additional Gen 2 measurements and improvements over Original Gen boards.

**Minor updates:**

- Text align set to justify for better readability.
- Updated LCR meter docs style and grammar.
- Renamed E3 add-on module to QSPI eMMC module.
- Minor update to streaming application command line util.
- Added examples on Deep Memory Acquisition comparison and Deep Memory Generation.
- Added clarification on OS updater process check.
- Documented new functionality in System Info section.
- Updated measurements for Original Gen boards.
- Separated QSPI eMMC module into its own section.
- Updated intro with new messaging.
- Single reactor ignition on the doc bugs.
- Clarified Nightly Build installation instructions.
- Updated Gen 2 board names.
- Added new troubleshooting section to FAQ.
- Added Python SCPI library explanation.
- Syntax and grammar fixes.

**Links affected:**

- X-channel streaming page doesn't exist anymore - it is now a part of "multichannel synchronisation" page.
- Links to Deep Memory Acquisition page - renamed to "Deep Memory Mode".
- Links to Deep Memory Acquisition examples.

## July 2025 - Update 1

**Changes:**

- Added 65-16 TI, 125-14 TI to Gen 2 comparison table.
- TI boards added to the tree.
- Output jitter measurements added to Gen 2.

## April 2025 - Update 2

**Major updates:**

- 404 page added to reroute old broken links.
- Gen 2 fast analog inputs and output measurements added.
- Gen 2 heatmap images added.
- Updated certification page with new certificates and downloadable PDFs.

**Minor updates:**

- Fixed and updated Original Gen specifications.
- Updated and clarified E3 add-on board instructions.
- Updated Gen 2 booting instructions.
- Fixed Sphinx dependency issues with the documentation build process.
- Added changelog.

**Links affected:**

- Added redirects for broken links from *April 2025 - Update 1*.
- None.

## April 2025 - Update 1

**Major updates:**

- Partial Gen 2 board documentation added.
- E3 add-on module documentation added.
- Added E3 I2C controller and ecosystem updater command line utilities.
- Reorganized the prepare SD card section to be more user-friendly and added instructions for installing Nightly builds.
- OS updater tool documentation added.
- OS update options section added.
- Network manager docs updated and merged with instructions for different connections (WiFi, Ethernet, etc.).
- Impedance transformer extension docs added.
- Updated the external clock specs.
- 4-Input external reference clock option added.

**Minor updates:**

- Reorganized the FAQ section and added a common troubleshooting guide.
- Updated and fixed internal links.
- Playback and record docs update.
- Updated command line utilities.
- Reorganized the API and SCPI command structure (advancing towards a separate page for each command).
- Removed Scilab from SCPI command list (the command structure is similar to MATLAB).
- Fixed a mistake in FPGA pin number labelling of the I2C pins for Original Gen boards - the pin description was correct, but the pin numbering was switched.
- Moved pictures into img folders.
- Ate one Red Pitaya fruit (it was delicious).
- Removed title numbering for level 4 and higher titles.
- Added index links to the registers.

**Broken links:**

- Links to all Red Pitaya board docs - specific boards, jumpers, extension connectors, etc. (separated into Original Gen and Gen 2 boards) including extension module links (click shield, etc.). Will try to relink all old links to the Original Gen hardware documentation page.
- Links to specific command line tools (acquire, generate, monitor) (moved into a separete directory).
- Links to specific SCPI commands on the command list (command list broken into separate pages).
- Links to specific system tools (moved into a separate directory).
- Quickstart connect (types of connections) (moved under the network manager section).

## February 2025 - Update 1

**Major updates:**

- Playback and record application.
- Updated Logic analyzer application docs.
- Added docs on SDR apps.
- Fixed and updated MATLAB example code.
- Added new examples for acquisition (split trigger).
- Fixed I2C, SPI and UART examples.
- New examples:

  - Split trigger acquisition.
  - Logic Analyzer decoding examples.

- Added new commands to the command list.
- Documented new software bugs.

**Minor updates:**

- Moved the obsolete HAMlab and power SDR to hardware => extension platforms and linked old HAMlab docs.
- Clarified modification instructions for external clock.
- Additional notes on 3rd party apps to marketplace.
- Updated PyRPL application docs.
- Author note added to VNA.
- Updated external clock requirements.
- Updated library section in C&Python API.
- Added required hardware and software notes to examples.
- Expanded the FAQ section.
- Grammar fixes and minor bug fixes.

**Links affected:**

- Specific code examples as I have changed the names of example files to sync them with the headings and make the file names readable. Links to examples top and e.g. acquisition examples top are unaffected.
- SDR application (old HAMlab docs) as I have moved it elsewhere

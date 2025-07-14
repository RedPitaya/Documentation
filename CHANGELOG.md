---
orphan: true
---

# Change Log

All notable changes to this project will be documented in this file.

## July 2025 - Update 1

**Major updates:**

- Updated streaming application documentation.
- Separated Multichannel synchronisation (click shield and X-channel) into a separate section.
- DAC streaming added.
- Deep memory generation instructions added.
- Combined Deep Memory Acquisition and Deep Memory Generation into a single section called Deep Memory Mode.
- Added functionality overview for the commands under each command table section (currently only for SPI). Looking to expand this to all commands in the future.
- Gen 2 supported features and apps.
- Added links to measurements under each board model docs.
- Added TItanium board documentation.
- Gen 2 FAQ section added.
- Additional Gen 2 measurements and improvements over Gen 1 boards.

**Minor updates:**

- Text align set to justify for better readability.
- Updated LCR meter docs style and grammar.
- Renamed E3 add-on module to QSPI eMMC module.
- Minor update to streaming application command line util.
- Added examples on Deep Memory Acquisition comparison and Deep Memory Generation.
- Added clarification on OS updater process check.
- Documented new functionality in System Info section.
- Updated measurements for Gen 1 boards.
- Separated QSPI eMMC module into its own section.
- Updated intro with new messaging.
- Clarified Nightly Build installation instructions.
- Updated Gen 2 board names.
- Added new troubleshooting section to FAQ.

**Links affected:**

- Links to streaming application docs.
- Links to Deep Memory Acquisition page.

## April 2025 - Update 2

**Major updates:**

- 404 page added to reroute old broken links.
- Gen 2 fast analog inputs and output measurements added.
- Gen 2 heatmap images added.
- Updated certification page with new certificates and downloadable PDFs.

**Minor updates:**

- Fixed and updated Gen 1 specifications.
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
- Fixed a mistake in FPGA pin number labelling of the I2C pins for Gen 1 boards - the pin description was correct, but the pin numbering was switched.
- Moved pictures into img folders.
- Ate one Red Pitaya fruit (it was delicious).
- Removed title numbering for level 4 and higher titles.
- Added index links to the registers.

**Broken links:**

- Links to all Red Pitaya board docs - specific boards, jumpers, extension connectors, etc. (separated into Gen 1 and Gen 2 boards) including extension module links (click shield, etc.). Will try to relink all old links to the gen 1 hardware documentation page.
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

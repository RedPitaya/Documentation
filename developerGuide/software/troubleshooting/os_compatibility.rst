.. _os_compatibility:

###########################
OS Version Compatibility
###########################

This page provides information about official Red Pitaya OS version compatibility with different hardware generations and instructions for running older OS versions on newer hardware.

.. contents::
   :local:
   :backlinks: none

|


Recommended OS Versions
========================

**Gen 2 boards** (STEMlab 125-14 Gen 2, PRO variants, TI variants):

* **Required**: OS version 2.07-43 or higher
* **TI boards**: NOT compatible with older OS versions - attempting to run older versions may cause malfunction or damage

**Original Generation boards** (STEMlab 125-14, SDRlab 122-16, SIGNALlab 250-12, etc.):

* **Compatible**: All OS versions (0.9, 1.04, 2.00+)
* **Recommended**: Latest stable OS version for best performance and features

|


Running Older OS Versions on Gen 2 Boards
==========================================

.. warning::

    **TI boards are NOT compatible with OS versions older than 2.07-43** due to fundamental hardware changes. Attempting to run older OS versions on TI boards may lead to malfunction or permanent damage.

Boards that include the "Gen 2" designation in their name (e.g., STEMlab 125-14 Gen 2, STEMlab 125-14 PRO Gen 2, STEMlab 125-14 PRO Z7020 Gen 2) are technically backwards compatible with some older OS versions. 

However, running older OS versions on Gen 2 boards is **strongly discouraged** due to:

* Lack of support for new hardware features (E3 connector)
* Potential calibration problems
* No official support for this configuration

|

OS 2.00 Versions (Older than 2.07-43)
---------------------------------------

**Issue**: These OS versions include a board-ID checking mechanism that prevents booting on Gen 2 hardware.

**Workaround** (unsupported):

To bypass the board-ID check, you must modify the boot scripts. This requires:

1. Modifying |u-boot.script| boot script to skip board ID verification (or add Gen 2 IDs)
2. Rebuilding the boot script and flashing it to the SD card
3. Testing thoroughly before production use
4. Understanding that you're running an unsupported configuration

.. warning::

    Red Pitaya does not provide official support for this configuration. Proceed at your own risk.

.. |u-boot.script| replace:: :rp-github:`u-boot.script <RedPitaya/blob/master/patches/u-boot/u-boot.script>`

|

OS 1.04 and Earlier
--------------------

**Compatibility**: These OS versions do not include board-ID checks and will boot on Gen 2 hardware without modification.

**Critical Issue - Calibration Format**:

OS 1.04 and earlier use an older calibration format that is incompatible with Gen 2's calibration data. 

**Required steps before downgrading**:

1. **Back up your current calibration** (OS 2.07-43+)
2. **Revert calibration format** to the older format compatible with OS 1.04 using the :ref:`Calibration command line utility <calib_util>`.
3. **Then** install the older OS version
4. **Test thoroughly** - analog I/O performance may differ

.. danger::

    If you install OS 1.04 without reverting the calibration format first, your analog inputs and outputs will not measure correctly.

|

Custom OS Builds
-----------------

**Custom OS builds** that do not check for board-ID may run on Gen 2 hardware:

* Must be tested thoroughly on target hardware
* Should ensure compatibility with Gen 2 calibration format if using official calibration
* May not support all Gen 2-specific features (E3 connector, external clock, etc.)
* Are not officially supported by Red Pitaya

|


Why Gen 2 Requires Newer OS Versions
======================================

Quite simply, since we introduced automatic board identification in 2.00 OS, the older OS version will not recognize newer board ID versions. Thus, failing to boot.
The other reasons are listed below:

**Hardware improvements requiring OS support:**

* E3 add-on board support (additinal GPIOs, QSPI and eMMC boot options)
* A few pinout changes on non-critical peripheral units (different pin assignments for S1 and S2 connectors)
* Improved analog hardware changes non-compatible with old auto-calibration scripts

**Software improvements requiring OS support:**

* Different calibration format in EEPROM
* Different board ID versions

**TI variants have even more fundamental changes:**

* Different ADC/DAC chips with different characteristics
* Modified analog signal chain
* Requires completely different FPGA bitstreams and software drivers

This is why older OS versions cannot properly support Gen 2 hardware - they simply don't have the drivers, calibration data, or configuration needed for the new hardware.

|


Getting Help
=============

If you need to run older OS versions for legacy application compatibility:

1. **Consider updating your application** to work with the latest OS instead
2. **Contact Red Pitaya support** to :ref:`discuss your specific use case <report_problem>`
3. **Use Original Generation hardware** if you must run old OS versions

For OS update instructions and official OS downloads, see:

* :ref:`OS Update Guide <os_update>`
* `Red Pitaya Downloads <https://redpitaya.com/downloads/>`_

|

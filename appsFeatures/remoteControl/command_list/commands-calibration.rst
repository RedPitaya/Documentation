.. _commands_calib:

##############
Calibration
##############

.. contents:: Calibration command index
   :local:
   :depth: 2
   :backlinks: top

|

Functionality overview
=======================

The calibration API (``rp_hw_calib``) reads, modifies and writes the calibration data stored in the Red Pitaya EEPROM. The calibration contains the gain and offset values of the fast analog inputs 
(for each channel, LV (1:1) and HV (1:20) jumper setting, and DC and AC coupling), the gain and offset values of the fast analog outputs (x1 and x5 gain modes) and the coefficients of the 
FPGA input filters. The data is loaded from the EEPROM when the library is initialized, kept in memory and used by the acquisition and generation APIs.

The calibration is controllable only on the API level (C++ and Python). There are no SCPI commands for the calibration.

The calibration data is stored in the :ref:`rp_calib_params_t <calib_params_struct>` structure. The functions are grouped as follows:

* **Initialization and information** - initialize the library and read the calibration version, limits and default values.
* **Reading calibration values** - read the gain, offset and filter values for a specific channel and mode.
* **EEPROM access** - read the raw EEPROM content, convert it to the calibration structure and print it.
* **Writing and resetting** - write calibration parameters to the EEPROM, set them temporarily in memory, or reset them to default or factory values.

|

Important notes
=================

.. warning::

    Writing to the EEPROM changes the calibration of the board. Incorrect values result in wrong acquisition and generation values. Make a backup of the current calibration with 
    ``rp_GetCalibrationSettings()`` before writing, and restore it with ``rp_CalibrationWriteParams()`` if needed. Writing to the factory zone (``use_factory_zone = true``) 
    overwrites the factory calibration and should only be done if you know exactly what you are doing. **The factory zone is write protected and cannot be changed by normal means.**

* The functions that write to the EEPROM (``rp_CalibrationWriteParams``, ``rp_CalibrationWriteParamsEx``, ``rp_CalibrationReset``, ``rp_CalibrationFactoryReset``) are marked as 
  :ref:`danger zone <calib_danger_zone>` in the examples.
* ``rp_CalibrationSetParams`` only changes the calibration values in memory. They are lost after the library is released or the board is rebooted.
* The calibration settings are cached after the first read from the EEPROM. 
* The calibration library must be initialized with ``rp_CalibInit()`` before any other calibration function is used.
* All functions return a status code (``rp_calib_error``). In Python, the functions with output arguments return a tuple, where the first element is the status code and the remaining elements are the 
  output values (e.g., ``(status, gain, offset)``). The functions with structure outputs (marked with *struct* in the tables) require a structure object created with the ``new_p_*`` functions.

|

Code examples
===============

Basic Python example for reading the calibration values:

.. code-block:: python

    import rp
    import rp_hw_calib

    rp.rp_Init()
    rp_hw_calib.rp_CalibInit()

    # LV calibration of channel 1, DC coupling: (status, gain, offset)
    status, gain, offset = rp_hw_calib.rp_CalibGetFastADCCalibValue(0, 0)
    print(f"LV ADC[1]: Gain = {gain}, Offset = {offset}")

    # Backup of the whole calibration
    backup = rp_hw_calib.rp_GetCalibrationSettings()

    rp.rp_Release()

|

.. _calib_params_struct:

Parameters and command tables
=============================

**Parameter options:**

- ``<channel> = {RP_CH_1_CALIB, RP_CH_2_CALIB, RP_CH_3_CALIB, RP_CH_4_CALIB}`` (values 0 to 3). Channel selection. Number of available channels depends on the board model.
- ``<gain_mode> = {RP_GAIN_CALIB_1X, RP_GAIN_CALIB_5X}`` (values 0 and 1). Generator gain mode.
- ``<ac_dc_mode> = {RP_DC_CALIB, RP_AC_CALIB}`` (values 0 and 1). Input coupling mode.
- ``<filter_mode> = {RP_HW_CFM_KEEP, RP_HW_CFM_DEFAULT, RP_HW_CFM_ZERO}`` (values 0, 1, 2). Filter behavior on calibration reset:

    * ``RP_HW_CFM_KEEP`` - keeps the filter values currently loaded from the EEPROM.
    * ``RP_HW_CFM_DEFAULT`` - sets the default filter values (for new boards this is often the disabled filter).
    * ``RP_HW_CFM_ZERO`` - sets the values equivalent to a disabled filter.

- ``<rp_calib_error>`` - status code:

    * ``RP_HW_CALIB_OK`` (0) - operation completed successfully.
    * ``RP_HW_CALIB_ERE`` (1) - error reading from the EEPROM.
    * ``RP_HW_CALIB_EWE`` (2) - error writing to the EEPROM.
    * ``RP_HW_CALIB_ENI`` (3) - calibration values not initialized.
    * ``RP_HW_CALIB_EDM`` (4) - board model detection error.
    * ``RP_HW_CALIB_ECH`` (5) - invalid channel parameter.
    * ``RP_HW_CALIB_EIP`` (6) - invalid parameter.
    * ``RP_HW_CALIB_EA`` (7) - adjust error.
    * ``RP_HW_CALIB_UC`` (8) - unknown calibration.

- ``<version>`` - calibration data structure version (``RP_HW_PACK_ID_V1`` to ``RP_HW_PACK_ID_V6``):

    * ``V1`` (1) - 125-14 boards, ``V2`` (2) - 250-12 boards, ``V3`` (3) - 125-14 4-Input boards, ``V4`` (4) - 122-16 boards.
    * ``V5`` (5) - universal calibration, ``V6`` (6) - universal calibration using the FPGA. Only ``V5`` and ``V6`` (and higher) can be used with a new-format reset.

The SCPI column is intentionally empty, as there are no SCPI commands for the calibration yet. The C++ and Python functions have the same names; Python differences are described in the 
`Important notes`_.

|

**Calibration structures**

.. list-table::
    :widths: 25 20 55
    :header-rows: 1

    * - Structure
      - Member
      - Description
    * - ``rp_calib_params_t``
      - ``dataStructureId``, ``wpCheck``
      - Data structure identifier and write protection check.
    * -
      - ``timeStamp``, ``hash_commit``
      - Time of the calibration (seconds since 01-01-2000 00:00:00) and commit hash of the calibration software.
    * -
      - ``fast_adc_1_1[4]``, ``fast_adc_filter_1_1[4]``
      - Input calibration (``channel_calib_t``) and FPGA filter coefficients (``channel_filter_t``) for the LV (1:1) jumper setting, per channel.
    * -
      - ``fast_adc_1_20[4]``, ``fast_adc_filter_1_20[4]``
      - Input calibration and FPGA filter coefficients for the HV (1:20) jumper setting, per channel.
    * -
      - ``fast_adc_1_1_ac[4]``, ``fast_adc_1_20_ac[4]``
      - Input calibration for AC coupling (LV and HV).
    * -
      - ``fast_dac_x1[2]``, ``fast_dac_x5[2]``
      - Output calibration for the x1 and x5 (250-12 only) generator gain modes.
    * -
      - ``fast_adc_count_*``, ``fast_dac_count_*``
      - Number of valid channels in the respective arrays.
    * - ``channel_calib_t``
      - ``baseScale``, ``calibValue``, ``offset``, ``gainCalc``
      - Base scaling factor, calibration value, offset and calculated gain of a channel.
    * - ``channel_filter_t``
      - ``aa``, ``bb``, ``pp``, ``kk``
      - FPGA filter coefficients.
    * - ``uint_gain_calib_t``
      - ``gain``, ``base``, ``precision``, ``offset``
      - Integer (RAW) representation of the gain calibration.

In Python, the arrays inside the structures are accessed with ``cCalibArr_getitem(array, index)`` and ``cCalibArr_setitem(array, index, value)`` (channel calibration) or ``cFilterArr_getitem`` / 
``cFilterArr_setitem`` (filters). Structures used as output arguments are created with ``new_p_channel_filter_t()``, ``new_p_uint_gain_calib_t()`` and ``new_p_rp_calib_params_t()``.

|

**Initialization and information**

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``rp_calib_error rp_CalibInit()``
        | Python: ``rp_CalibInit()``
      - Initializes the calibration library.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibInitSpecific(rp_HPeModels_t model)``
        | Python: ``rp_CalibInitSpecific(model)``
      - Initializes the calibration library for a specific board model.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_GetCalibrationVersion(uint8_t* version)``
        | Python: ``rp_GetCalibrationVersion()``
      - Returns the version of the loaded calibration. Python returns ``(status, version)``.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_params_t rp_GetCalibrationSettings()``
        | Python: ``rp_GetCalibrationSettings()``
      - Returns the current calibration settings. The settings are cached after the first read from the EEPROM.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_params_t rp_GetDefaultCalibrationSettings()``
        | Python: ``rp_GetDefaultCalibrationSettings()``
      - Returns the default calibration settings.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_params_t rp_GetDefaultUniCalibrationSettings()``
        | Python: ``rp_GetDefaultUniCalibrationSettings()``
      - Returns the default calibration settings in the new (universal) format.
      - 3.00-57 and up
    * -
      - | C++: ``uint32_t rp_CalibGetMaxSizeEepromData()``
        | Python: ``rp_CalibGetMaxSizeEepromData()``
      - Returns the maximum size of the calibration data stored in the EEPROM in bytes.
      - 3.00-57 and up
    * -
      - | C++: ``uint32_t rp_CalibGetMaxSizeEepromDataUnify()``
        | Python: ``rp_CalibGetMaxSizeEepromDataUnify()``
      - Returns the maximum size of the calibration data stored in the EEPROM in bytes when using the unified (universal) format.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_GetNameOfUniversalId(uint16_t id, std::string* name)``
        | Python: ``rp_GetNameOfUniversalId(id)``
      - Returns the name of the universal calibration parameter with the specified ID. Python returns ``(status, name)``.
      - 3.00-57 and up

|

**Reading calibration values**

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``rp_calib_error rp_CalibGetFastADCCalibValue(rp_channel_calib_t channel, rp_acq_ac_dc_mode_calib_t mode, double* gain, int32_t* offset)``
        | Python: ``rp_CalibGetFastADCCalibValue(channel, mode)``
      - Returns the input gain and offset (floating point) for the LV (1:1) jumper setting. Python returns ``(status, gain, offset)``.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibGetFastADCCalibValueI(rp_channel_calib_t channel, rp_acq_ac_dc_mode_calib_t mode, uint_gain_calib_t* calib)``
        | Python: ``rp_CalibGetFastADCCalibValueI(channel, mode, calib)``
      - Returns the input calibration (integer, RAW) for the LV (1:1) jumper setting in a *struct*. Python: ``calib = new_p_uint_gain_calib_t()``.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibGetFastADCCalibValue_1_20(rp_channel_calib_t channel, rp_acq_ac_dc_mode_calib_t mode, double* gain, int32_t* offset)``
        | Python: ``rp_CalibGetFastADCCalibValue_1_20(channel, mode)``
      - Returns the input gain and offset (floating point) for the HV (1:20) jumper setting. Python returns ``(status, gain, offset)``.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibGetFastADCCalibValue_1_20I(rp_channel_calib_t channel, rp_acq_ac_dc_mode_calib_t mode, uint_gain_calib_t* calib)``
        | Python: ``rp_CalibGetFastADCCalibValue_1_20I(channel, mode, calib)``
      - Returns the input calibration (integer, RAW) for the HV (1:20) jumper setting in a *struct*.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibGetFastDACCalibValue(rp_channel_calib_t channel, rp_gen_gain_calib_t gain_mode, double* gain, int32_t* offset)``
        | Python: ``rp_CalibGetFastDACCalibValue(channel, gain_mode)``
      - Returns the output gain and offset (floating point). Python returns ``(status, gain, offset)``.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibGetFastDACCalibValueI(rp_channel_calib_t channel, rp_gen_gain_calib_t gain_mode, uint_gain_calib_t* calib)``
        | Python: ``rp_CalibGetFastDACCalibValueI(channel, gain_mode, calib)``
      - Returns the output calibration (integer, RAW) in a *struct*.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibGetFastADCFilter(rp_channel_calib_t channel, channel_filter_t* out)``
        | Python: ``rp_CalibGetFastADCFilter(channel, out)``
      - Returns the FPGA input filter coefficients (AA, BB, PP, KK) for the LV (1:1) jumper setting in a *struct*. Python: ``out = new_p_channel_filter_t()``.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibGetFastADCFilter_1_20(rp_channel_calib_t channel, channel_filter_t* out)``
        | Python: ``rp_CalibGetFastADCFilter_1_20(channel, out)``
      - Returns the FPGA input filter coefficients (AA, BB, PP, KK) for the HV (1:20) jumper setting in a *struct*.
      - 3.00-57 and up

|

**EEPROM access and conversion**

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``rp_calib_error rp_CalibGetEEPROM(uint8_t** data, uint16_t* size, bool use_factory_zone)``
        | Python: ``rp_CalibGetEEPROM(use_factory_zone)``
      - Returns the raw EEPROM calibration data. Python returns ``(status, data_pointer, size)``. Read the data with ``uint8Arr_frompointer(data_pointer)``.
      - 3.00-57 and up
    * -
      - | C++: *(not available)*
        | Python: ``rp_CalibGetEEPROMNP(use_factory_zone)``
      - Python helper. Returns the raw EEPROM data as a NumPy array. Returns ``(status, np_array)``.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibConvertEEPROM(uint8_t* data, uint16_t size, rp_calib_params_t* calib)``
        | Python: ``rp_CalibConvertEEPROM(data, calib)``
      - Converts the raw EEPROM data to the calibration structure. Python: ``data`` is a NumPy ``uint8`` array and ``calib = new_p_rp_calib_params_t()``.
      - 3.00-57 and up
    * -
      - | C++: *(not available)*
        | Python: ``rp_CalibConvertEEPROMNP(data_array)``
      - Python helper. Converts a NumPy ``uint8`` array (or list) of the EEPROM data to the calibration structure. Returns ``(status, calib)``.
      - 3.00-57 and up
    * -
      - | C++: *(not available)*
        | Python: ``rp_CalibGetAndConvertNP(use_factory_zone)``
      - Python helper. Reads the EEPROM and converts it to the calibration structure in one call. Returns ``(status, calib)``.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibConvertToOld(rp_calib_params_t* calib)``
        | Python: ``rp_CalibConvertToOld(calib)``
      - Converts the calibration structure to the legacy format.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibPrint(rp_calib_params_t* calib)``
        | Python: ``rp_CalibPrint(calib)``
      - Prints the calibration information of the specified calibration structure.
      - 3.00-57 and up

|

.. _calib_danger_zone:

**Writing and resetting calibration (danger zone)**

.. list-table::
    :widths: 18 30 38 14
    :header-rows: 1

    * - SCPI
      - API, Jupyter
      - DESCRIPTION
      - ECOSYSTEM
    * -
      - | C++: ``rp_calib_error rp_CalibrationSetParams(rp_calib_params_t calib_params)``
        | Python: ``rp_CalibrationSetParams(calib_params)``
      - Sets the calibration parameters in memory only (without writing to the EEPROM).
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibrationWriteParams(rp_calib_params_t calib_params, bool use_factory_zone)``
        | Python: ``rp_CalibrationWriteParams(calib_params, use_factory_zone)``
      - Writes the calibration parameters to the EEPROM (user zone, or factory zone if ``use_factory_zone`` is true).
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibrationWriteParamsEx(rp_calib_params_t calib_params, bool use_factory_zone)``
        | Python: ``rp_CalibrationWriteParamsEx(calib_params, use_factory_zone)``
      - Writes the calibration parameters to the EEPROM without recalculation.
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibrationReset(bool use_factory_zone, bool is_new_format, rp_calib_filter_mode mode, uint8_t version)``
        | Python: ``rp_CalibrationReset(use_factory_zone, is_new_format, mode, version)``
      - Resets the calibration to default values. ``mode`` sets the filter behavior (see ``<filter_mode>``). ``version`` is the new-format version (``RP_HW_PACK_ID_V5`` or higher).
      - 3.00-57 and up
    * -
      - | C++: ``rp_calib_error rp_CalibrationFactoryReset(bool convert_to_new)``
        | Python: ``rp_CalibrationFactoryReset(convert_to_new)``
      - Copies the factory calibration to the user EEPROM zone, optionally converting it to the new format.
      - 3.00-57 and up

|

* :ref:`Back to top <commands_calib>`
* :ref:`Back to command list <command_list>`


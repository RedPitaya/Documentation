.. _profiles_util:

Profiles 工具
======================

Profiles 工具允许用户查看板卡信息，并管理当前板卡型号的用户自定义设置。该工具可用于查看当前配置档案、列出所有可用配置档案，以及读取或写入当前板卡修订版的用户自定义设置。

.. note::

    Profiles 工具面向高级用户和开发者，用于在具有不同采集和生成功能限制的定制 Red Pitaya 板卡上自定义 Red Pitaya 板卡的行为。

使用说明：

.. tabs::

    .. group-tab:: OS 版本 3.00 及更高

        .. code-block:: console

            root@rp-f0b1cb:~# profiles
            profiles version 3.00-809-bce7a0397

            Usage:
                    -p      : Show current profile
                    -pa     : Show all profiles
                    -f      : Print fpga version
                    -n      : Print model name
                    -i      : Print model id
                    -c      : Checking the validity of the model in EEPROM
                    -v KEY  : Print value from profile by key
                            Keys:
                                    osc_rate        : OSC base rate
                                    fast_adc_bits   : HW ADC bits
                                    fast_adc_fs     : HW ADC full scale
                                    fast_dac_fs     : HW DAC full scale
                                    is_dac_50ohm    : Support 50 ohm load mode for DAC
                                    is_daisy_clock_sync     : Synchronization via daisy chain
                                    gpio_n  : Number of GPIO channels N
                                    gpio_p  : Number of GPIO channels P
                                    e3      : Availability of E3 connector
                                    e3_gpio : Availability of E3 GPIO
                                    e3_qspi : Availability of E3 QSPI
                    -w KEY VALUE    : Writes a user-defined value for the current board revision.
                    -r KEY  : Removes a user-defined setting.
                            Keys:
                                    fast_adc_rate
                                    fast_dac_rate
                                    spec_max_rate
                                    adc_low_pass
                                    dac_low_pass
                                    gen_min_speed
                                    gen_max_speed
                    -t <key>,<key>,...: Print pivot table
                            <key> - Can be an exact value or as a substring.
                            Keys:
                                    all - All parameters
                                    model - ID of board
                                    fpga_path - Path to FPGA bitstream
                                    zynq - Zynq CPU type 0 - 7010,1 - 7020
                                    osc_rate - Oscillator Rate (Hz)
                                    f_adc_fs - Fast ADC full scale (V)
                                    f_adc_rate - Fast ADC rate (Hz)
                                    f_adc_is_sign - Signed value for Fast ADC
                                    f_adc_bits - Number of bits in Fast ADC
                                    f_adc_count - Number of channels in Fast ADC
                                    f_adc_gain - Gain in Fast ADC
                                    f_is_dac - Fast DAC present
                                    f_dac_fs - Fast DAC full scale (V)
                                    f_dac_rate - Fast DAC rate (Hz)
                                    f_dac_is_sign - Signed value for Fast DAC
                                    f_dac_bits - Number of bits in Fast DAC
                                    f_dac_count - Number of channels in Fast DAC
                                    f_dac_gain - Gain in Fast DAC
                                    is_hv_lv - There is a 1:1 and 1:20 divider on the board
                                    is_ac_dc - AD/DC switches are present
                                    s_adc_count - Number of slow ADC channels
                                    s_adc_fs - Slow ADC full scale (V)
                                    s_adc_bits - Number of bits in Slow ADC
                                    s_adc_is_sign - Signed value for Slow ADC
                                    s_dac_count - Number of slow DAC channels
                                    s_dac_fs - Slow DAC full scale (V)
                                    s_dac_bits - Number of bits in Slow DAC
                                    s_dac_is_sign - Signed value for Slow DAC
                                    is_dac_x5 - There is a x5 amplifier on the DAC
                                    is_f_calib - Fast DAC/ADC calibration capability is available
                                    is_pll_control - PLL control is present
                                    is_f_adc_filter - Filter for Fast ADC is available
                                    is_f_dac_t_prot - Overheat protection for Fast DAC is available
                                    is_att_controller - Divider controller available
                                    is_ext_trig_lev - External trigger level setting is present
                                    is_ext_trig_fs - Full scale for external trigger
                                    is_ext_trig_is_sign - Signed value at the external trigger level
                                    spec_max_rate - Maximum frequency value for spectrum analyzer
                                    adc_low_pass - Value of the low-pass filter for the ADC.
                                    dac_low_pass - Value of the low-pass filter for the DAC.
                                    is_daisy_clock_sync - Synchronization via daisy chain
                                    is_dma_094 - DMA mode is available in FPGA 0.94
                                    is_dac_50ohm - Support 50 ohm load mode for DAC
                                    is_split_trig - Support split trigger mode
                                    gpio_count - Number of GPIO outputs
                                    ram - Maximum amount of RAM
                                    is_e3 - High-speed E3 connector is present
                                    is_e3_hs_gpio - High-speed E3 connector for GPIO is present
                                    is_e3_hs_rate - Rate in E3 HS gpio
                                    is_e3_qspi - QSPI is present in E3
                                    is_fpga_calib - Fast ADC Calibration on FPGA
                                    is_fast_adc_16b_mode - Fast ADC 16-bit data mode on FPGA
                                    is_xstreaming - X-Streaming mode
                                    gen_min_speed - Minimum allowable frequency for the generator
                                    gen_max_speed - Maximum allowable frequency for the generator


用户自定义值
--------------------

可以修改以下用户自定义值：

* **fast_adc_rate** - 快速 ADC 采样率。
* **fast_dac_rate** - 快速 DAC 采样率。
* **spec_max_rate** - 频谱分析仪的最大频率值。
* **adc_low_pass** - ADC 低通滤波器值。
* **dac_low_pass** - DAC 低通滤波器值。
* **gen_min_speed** - 发生器允许的最小频率。
* **gen_max_speed** - 发生器允许的最大频率。

.. note::

    这些值均表示示波器、频谱分析仪和信号发生器应用的软件限制。更改这些值**不会**改变板卡的硬件限制。

以下示例将 ADC 低通滤波器限制设置为 125 MHz：

.. code-block:: console

    profiles -w adc_low_pass 125000000

|

源代码
------------

Red Pitaya GitHub 仓库包含 :rp-github:`Profiles 工具源代码 <RedPitaya/tree/master/tools/profiles>`。

|

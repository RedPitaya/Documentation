
.. _commands_board:

======================
板卡控制命令
======================

功能概览
------------------------

板卡控制命令提供 Red Pitaya 板卡的一般信息，例如 ID、版本和日期/时间设置。它们允许设置板卡运行方式的一般参数，包括日志模式和错误处理。这些命令对于管理板卡配置并确保其正常运行至关重要。

这些命令应在应用程序初始化阶段启动时执行一次。


重要说明
----------------

*   ``RP:RET_ON_ERROR <bool>`` 命令是非标准 SCPI 命令功能，可启用用于兼容旧版 SCPI 客户端的特殊模式。启用此模式后，如果执行查询命令时发生错误，服务器将返回带有分隔符 "\r\n" 的空数据，从而避免 SCPI 数据或参数请求在 Red Pitaya 端发生错误时陷入无限等待返回的循环。这有助于维持与依赖此行为的旧系统的兼容性。


代码示例
-----------------

由于这些命令用于一次性设置，因此不提供专门的代码示例。


参数与命令表
-----------------------------

**参数选项：**

- ``<year> = {1900, ...}`` 默认值： ``OS release date and time``
- ``<bool> = {OFF, ON}`` 默认值： ``OFF``
- ``<month> = {1, 12}``
- ``<day> = {1, 31}``
- ``<hours> = {0, 23}``
- ``<minutes> = {0, 59}``
- ``<seconds> = {0, 59}``
- ``<log_mode> = {OFF, CONSOLE, SYSLOG}``
- ``<board_id> = {0, 15}``
- ``<enable> = {true, false}``
- ``<errorCode> = {RP_OK, RP_EOED, RP_EOMD, RP_ECMD, RP_EMMD, RP_EUMD, RP_EOOR, RP_ELID, RP_EMRO, RP_EWIP, RP_EPN, RP_UIA, RP_FCA,``
- ``<errorCode> =  RP_RCA, RP_BTS, RP_EIPV, RP_EUF, RP_ENN, RP_EFOB, RP_EFCB, RP_EABA, RP_EFRB, RP_EFWB, RP_EMNC, RP_NOTS}``

**可用的 Jupyter 和 API 宏：**

Red Pitaya 状态和错误：

- ``RP_OK`` - 确定
- ``RP_EOED`` - 打开 EEPROM 设备失败。
- ``RP_EOMD`` - 打开内存设备失败。
- ``RP_ECMD`` - 关闭内存设备失败。
- ``RP_EMMD`` - 映射内存设备失败。
- ``RP_EUMD`` - 取消映射内存设备失败。
- ``RP_EOOR`` - 值超出范围。
- ``RP_ELID`` - LED 输入方向无效。
- ``RP_EMRO`` - 不允许修改只读字段。
- ``RP_EWIP`` - 写入输入引脚无效。
- ``RP_EPN`` - 引脚编号无效。
- ``RP_UIA`` - 输入参数未初始化。
- ``RP_FCA`` - 查找校准参数失败。
- ``RP_RCA`` - 读取校准参数失败。
- ``RP_BTS`` - 缓冲区太小
- ``RP_EIPV`` - 参数值无效
- ``RP_EUF`` - 不支持的功能
- ``RP_ENN`` - 数据未规范化
- ``RP_EFOB`` - 打开总线失败
- ``RP_EFCB`` - 关闭总线失败
- ``RP_EABA`` - 获取总线访问权限失败
- ``RP_EFRB`` - 从总线读取失败
- ``RP_EFWB`` - 写入总线失败

..    - ``RP_EMNC`` -
..    - ``RP_NOTS`` -

.. tabularcolumns:: |p{50mm}|p{50mm}|p{60mm}|p{30mm}|

.. list-table::
    :widths: 54 51 59 24
    :header-rows: 1

    * - SCPI
      - API、Jupyter                                      |
      - 描述                                                       |
      - 适用版本             |
    * - ``RP:LOGmode <log_mode>`` |br| 示例：                                          | | |br| ``RP:LOGmode SYSLOG``
      - -
      - 启用 scpi-server 日志输出模式。                      | 1.04-18 及更高版
      - 
    * - ``RP:RET_ON_ERROR <bool>`` |br| 示例：                                          | | |br| ``RP:RET_ON_ERROR ON``
      - N/A |br| | 旧版
      - 启用用于兼容性的特殊模式                | 2.07-43 及更高版本         | |br| SCPI 客户端。启用此模式后，     |                        | |br| 如果执行查询命令时发生错误，          |                        | |br| 服务器将返回带有分隔符 "\r\n" 的空数据|                        |
      - 
    * - ``SYSTem:TIME <hours>,<minutes>,<seconds>`` |br| 示例：                                          | | |br| ``SYSTem:TIME 16,12,45`` |br| ``SYST:TIME 11,23,01``
      - -
      - 设置板卡时间。                               | 2.00-18 和 2.00-36
      - 
    * - ``SYSTem:TIME "<hours>:<minutes>:<seconds>"`` |br| 示例：                                          | | |br| ``SYSTem:TIME "16:12:45"`` |br| ``SYST:TIME "11:23:01"``
      - -
      - 设置板卡时间。                               | 2.05-37 及更高版本
      - 
    * - ``SYSTem:TIME?`` > ``time`` |br| 示例：                                          | | |br| ``SYSTem:TIME?`` > ``16:12:45`` |br| ``SYST:TIME?`` > ``11:23:01``
      - -
      - 返回板卡当前时间。                    | 2.00-18 及更高版本         |
      - 
    * - ``SYSTem:DATE <year>,<month>,<day>`` |br| 示例：                                          | | |br| ``SYSTem:DATE 2023,04,04`` |br| ``SYST:DATE 2002,12,29``
      - -
      - 设置板卡日期。                               | 2.00-18 和 2.00-36
      - 
    * - ``SYSTem:DATE "<year>-<month>-<day>"`` |br| 示例：                                          | | |br| ``SYSTem:DATE "2023-04-04"`` |br| ``SYST:DATE "2002-12-29"``
      - -
      - 设置板卡日期。                               | 2.05-37 及更高版本
      - 
    * - ``SYSTem:DATE?`` > ``date`` |br| 示例：                                          | | |br| ``SYSTem:DATE?`` > ``2023-04-04`` |br| ``SYST:DATE?`` > ``2002-12-29``
      - -
      - 返回板卡当前日期。                    | 2.00-18 及更高版本         |
      - 
    * - ``SYSTem:BRD:ID?`` > ``<board_id>`` |br| 示例：                                          | | |br| ``SYSTem:BRD:ID?`` > ``1``
      - C++: ``rp_IdGetID(uint32_t *id)`` |br| Python: ``rp_IdGetID()``
      - 返回 Red Pitaya 板卡 ID。                          | 2.00-18 及更
      - 版本         |
    * - ``SYSTem:BRD:Name?`` > ``board name`` |br| 示例：                                          | | |br| ``SYSTem:BRD:Name?`` > ``STEMlab 125-14 v1.0``
      - C++: ``const char* rp_GetVersion()`` |br| Python: ``rp_GetVersion()``
      - 返回 Red Pitaya 板卡版本。                     | 2.00-18 及更高版本
      - 
    * - ``SYSTem:VERSion?`` > ``OS version`` |br| 示例：                                          | | |br| ``SYSTem:VERSion?`` > ``2.07-651``
      - C++: - |br| Python: -
      - 返回 Red Pitaya OS 版本。                        | 2.07-48 及更高版
      - 
    * - ``SYSTem:Help?`` > ``<List of SCPI commands>`` |br| 示例：                                          | | |br| ``SYSTem:Help?`` > ``*CLS\n*ESE\n...``
      - - |br| | SC
      - 返回所有命令的列表                          | 2.04-35 及更高版本 |br| I 服务器可以处理的命令。                       |
      - 
    * - -
      - C++: ``rp_IdGetDNA(uint64_t *dna)`` |br| Python: ``rp_IdGetDNA()``
      - 返回 FPGA 芯片的唯一 DNA 代码。             | 2.00-18 及更高版本
      - 
    * - -
      - C++: ``const char* rp_GetError(int errorCode)`` |br| Python: ``rp_GetError(<errorCode>)``
      - 返回输入错误代码的描述。          | 2.00-18 及更高版本         |
      - 
    * - -
      - C++: ``rp_EnableDigitalLoop(bool enable)`` |br| Python: ``rp_EnableDigitalLoop(<enable>)``
      - 启用/禁用数字环路（FPGA 内部        | 2.00-18 及更高版本         | |br| 快速模拟输入与输出之间的连接）。     |                        |
      - 

|

* :ref:`返回顶部 <commands_board>`
* :ref:`返回命令列表 <command_list>`

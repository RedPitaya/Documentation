.. _programming:

####################################
编程与远程控制工具
####################################

从 PC 远程控制 Red Pitaya，或开发直接在板卡上运行的自定义应用。本节面向需要自动化控制、自定义信号处理或将 Red Pitaya 集成到更大系统中的程序员、研究人员和工程师。

**可用方法：**

* **SCPI Server** - 通过 TCP/IP 使用行业标准命令，从 MATLAB、LabVIEW 或 Python 进行远程控制。无需板载编程。
* **C++ 和 Python API** - 开发直接运行在 Red Pitaya Linux OS 上的应用，以获得最高性能和实时处理能力。
* **JupyterLab** - 用于原型设计和分析的交互式 Python 环境，配合 notebook 风格文档。
* **Deep Memory Mode** - 使用完整 DDR3 RAM（最高 512 MB）及完整采样率采集和生成信号。

**支持资源：**

* 完整的 SCPI 和 API 命令参考，以及 OS 版本兼容性说明
* 可直接运行的代码示例，涵盖信号采集、信号生成、I/O 控制和通信接口
* 按 OS 版本整理的已知问题和变更说明，便于故障排查

.. toctree::
    :maxdepth: 1

    scpi
    API_scripts
    jupyter/Jupyter
    deepMemoryMode
    command_list
    examples_top
    knownIssues

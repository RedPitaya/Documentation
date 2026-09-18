.. _pyrpl:

#######################
PyRPL
#######################

该应用基于 Leonard Neuhaus 开发的 `PyRPL 官方 GitHub 仓库 <https://github.com/pyrpl-fpga/pyrpl>`_。

更多信息请参阅 `官方文档 <https://pyrpl.readthedocs.io/en/latest/>`_。


开始前需要什么？
==============================

1.  PyRPL 应用需求：

    * Windows、MacOS（预构建应用使用 arm64）或基于 Linux 的个人计算机（PC）。

#. 该应用适用于以下 Red Pitaya 板卡型号：

    * **STEMlab 125-14 Gen 2 板卡**
    * **STEMlab 125-14 Original Gen 板卡** （4-Input 除外）
    * **STEMlab 125-10（已停产）** （未确认，但应该可以工作）

..  note::

    PyRPL 无法在 **SDRlab 122-16**、**SIGNALlab 250-12** 和 **STEMlab 125-14 4-Input** 上运行。


兼容性
===================

下面汇总了 PyRPL 应用与不同 Red Pitaya 板卡型号及 OS 版本的兼容性：

.. list-table::
    :header-rows: 1
    :widths: 1 2 2

    * -
      - “官方”版本
      - 社区版本
    * - 板卡型号
      - STEMlab 125-14 Gen 2 板卡
        STEMlab 125-14 Original Gen 板卡
      - STEMlab 125-14 Original Gen 板卡
    * - OS 版本
      - OS 2.00 或更高版本
      - OS 2.00 或更高版本
    * - 功能
      - 针对 3.00 OS 编译的客户端
        客户端向后兼容
        部分功能不是最新版本
      - 可能无法在 2.00 OS 上运行

.. note::

    我们建议使用最新的 **社区版本**，因为它在持续改进。不过，目前社区版本尚不支持：

    * Gen 2 板卡

    社区版本正在积极开发中，预计这些功能将在不久后加入。


安装并运行 PyRPL
===================

运行该应用有多种方式：

1. 下载适用于相应平台的 `预构建应用 <https://downloads.redpitaya.com/downloads/Clients/pyrpl/>`_ （由 Red Pitaya 团队更新和编译）。
#. 运行仓库中的源代码：:rp-github:`Red Pitaya PyRPL GitHub <pyrpl>` （我们用于编译应用的版本）。
#. 使用应用的社区版本 |PyRPL|


以下是 Leonard Neuhaus 制作的演示视频链接：|pyrpl_video|

.. |pyrpl_video| raw:: html

    <a href="https://www.youtube.com/watch?v=WnFkz1adhgs" target="_blank">PyRPL video</a>




作者和源代码
===============

.. admonition:: 致谢

    | Red Pitaya PyRPL 应用的原始开发者是 Leonard Neuhaus。目前该仓库由 PyRPL 社区维护，负责人为 *michaelcroquette* 和 *peteasa*。
    | 我们构建时使用的仓库：

        * `PyRPL GitHub <https://github.com/pyrpl-fpga/pyrpl>`_

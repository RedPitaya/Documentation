# 中文翻译变更记录

## 2026-08-29 — 批次 001

- 锁定 Read the Docs `latest` 对应的官方 revision。
- 建立英文缓存、中文工作树、进度清单、术语表与自动检查框架。
- 完整翻译站点入口、产品介绍、快速入门入口、“开始前需要准备什么？”和“连接 Red Pitaya”页面。
- 将 Sphinx 文档语言设为 `zh_CN`，并本地化图、表、代码清单和章节编号名称。
- 修复上游 `osc.rst` 一处七列表格仅声明六个列宽的构建错误；该修复可独立回馈上游。
- 建立外链检查基线：已记录 24 个 broken、2 个 timeout 和 8 个 redirect；第三方限流项留待增量复查。

## 2026-08-29 — 批次 002

- 完整翻译“更新 Red Pitaya OS”页面。
- 完整翻译亚克力外壳与铝合金外壳组装页面，保留全部图片与硬件引用。
- 完整翻译故障排除入口及正常状态 LED 对照表，保留七步排查 toctree。
- 扩充外壳装配、状态指示和构建版本相关术语。
- 完整翻译故障排除步骤 1、5、7，覆盖 OS/固件更新、硬件连接与高级排查。
- 完整翻译故障排除步骤 2、3、4、6；至此七步故障排除主路径全部中文化。
- 保留 PowerShell 命令、启动消息、主机名、IP/MAC、Sphinx 引用及下载目标原文。

## 2026-08-29 — 批次 003

- 完整翻译 SD 卡准备页面，包括通用安装流程以及 Windows、Linux、macOS 写卡步骤。
- 保留 OS 下载 URL、MD5、镜像文件名、`dd`、UI 按钮文字、图片和平台锚点原文。
- 完整翻译板卡识别指南，覆盖第二代与初代全部主要型号、变体和外观识别特征。
- 完整翻译散热器接口安装页面，保留尺寸图、安装图片、螺钉规格和温度安全警告。

## 2026-08-29 — 批次 004

- 完整翻译 QSPI eMMC 扩展板连接、安装、开关机和启动选项页面。
- 保留 E3、P-ON、QSPI、eMMC、GPIO、板卡型号与软硬件章节 label/ref 原文。
- 完整翻译 eMMC 刷写指南，覆盖看门狗禁用、U-boot UMS、镜像写入、QSPI 引导加载程序和 eMMC 启动。
- 保留 `ums 0 mmc 0`、`reset`、`flashcp`、`boot.bin`、设备节点和控制台输出原文。
- 完整翻译开发者指南总入口及 Hardware、Software、FPGA 三个分区入口，建立技术文档中文导航骨架。
- FPGA 工具链对照表改为等价 `list-table`，避免中文字符宽度破坏 RST 网格表。
- 完整翻译 Software 开发简介与入门导航，以及 FPGA 开发入门导航。
- 完整翻译 Software 的应用程序开发、系统开发、配置与集成、故障排除四个分区入口。
- 完整翻译 FPGA 教程、高级主题和寄存器三个一级入口。

## 2026-08-29 — 批次 005

- 完整翻译 FPGA Projects 入口及 v0.94、stream_app、logic、barebones、fsbl 五个项目说明页。
- 保留 FPGA 模块名、信号名、寄存器地址、Make 命令、DTS 路径、label/ref 和图片指令原文。
- 将 Projects 页三张网格表转换为等价 ``list-table``，避免中文字符宽度破坏 RST 表格结构。
- 完整翻译 FPGA 项目工作流、Vivado SDK/Vitis 占位指南，以及 RF 输入和移动平均教程入口页。
- 本批采用三个独立子 Agent 并行初译，由主流程统一校正术语、表格结构并执行严格构建验收。

## 2026-08-29 — 批次 006

- 完整翻译 FPGA 开发简介、Vivado 安装导航和“从零开始创建项目”指南。
- 完整翻译 Vivado/Vitis 2025.1 设备树生成流程，保留 DTS 节点、属性、Make 命令和产物路径原文。
- 完整翻译 2.00-15 至 3.00-57 以及开发中版本的九个 FPGA 寄存器映射导航页。
- 保留全部 label/ref、toctree、URL、文件名、变量、型号标识、代码块和工具版本。
- 使用三个 Luna 子 Agent 并行处理互不重叠的正文，由主流程统一登记、静态检查和全量构建。

## 2026-08-29 — 批次 007

- 完整翻译设备树总指南、2020.1 旧版设备树流程和 FPGA 启动时加载指南。
- 完整翻译 FPGA 配置教程、Base Project 教程和 FPGA 重编程指南。
- 完整翻译 Vivado 2025.1、Vivado 2020.1 安装正文以及 Vivado 项目创建指南。
- 完整翻译 FPGA 信号映射指南，保留信号名、管脚名、HDL/DTS 标识符和代码块原文。
- 新增 ``scripts/check_structure.py``，自动比对已翻译页面与上游的 URL、label、ref/doc、include、图片、下载目标和 toctree 条目。
- 将结构一致性检查接入 ``scripts/check_all.sh``，作为每批构建前的自动门禁。

## 2026-08-29 — 批次 008

- 完整翻译修改现有 FPGA 项目、SDK 安装和 FPGA 仿真三篇大型入门指南。
- 完整翻译高级 FPGA 加载和 JTAG 编程指南，保留命令、TCL、DTS、控制台输出及硬件信号原文。
- 完整翻译 3.00-57 当前版本的 v0.94、stream_app、stream_app_250 三篇寄存器映射。
- 逐表翻译寄存器说明，保留地址、位域名、寄存器标识和数值；将中文宽度易损表格等价转换为 ``list-table``。
- 结构检查新增代码块正文和内联代码字面量对比，防止命令、路径、变量及 HDL/DTS 示例被误改。

## 2026-08-29 — 批次 009

- 完整翻译 3.00-57 当前版本的四通道 streaming、STEMlab 250-12 v0.94 和 4-Input CS2 v0.94 三篇寄存器映射。
- 逐项翻译 GPIO、触发、采集、AXI、DMA、PID、AMS、RLE、时间戳与菊花链相关寄存器说明。
- 保留全部地址、位域、寄存器与信号标识符、公式、数值、路径、引用和代码原文。
- 将中文宽度易损的寄存器网格表完整转换为等价 ``list-table``，并执行未翻译扫描、结构一致性检查与严格 Sphinx 构建。
- 本批继续采用三个 Luna 子 Agent 分页并行，主流程对不完整交稿实施退回重做和统一验收。

## 2026-08-29 — 批次 010

- 完整翻译 OS 2.07-48 对应的 v0.94、stream_app 和 stream_app_250 三篇历史版本寄存器映射。
- 对照 3.00-57 中文术语逐项核验旧版地址、位域与寄存器差异，未将新版本内容回填到旧版本。
- 将全部中文宽度易损网格表转换为等价 ``list-table``，保留公式、技术标识符、数值和引用。
- 并行初稿中发现的漏译、孤立表格边界和损坏单元格均未计入进度；改由独立重建和主流程扫描验收。

## 2026-08-29 — 批次 011

- 完整翻译 OS 2.07-48 的四通道 streaming 与 STEMlab 250-12 v0.94 寄存器映射，补齐该版本主要寄存器页面。
- 完整翻译开发中版本的 4-Input CS2 v0.94 寄存器映射，保留其专属 label/ref 和版本差异。
- 将全部网格表转换为等价 ``list-table``，清理孤立边界和单元格内残留表格标记。
- 对触发、阈值、DMA、AXI、缓冲区、突发、计数器和指针说明执行多轮英文残留扫描与返修。

## 2026-08-29 — 批次 012

- 完整翻译开发中版本的 stream_app、stream_app_250 和 stream_app_4ch 三篇寄存器映射。
- 保留 ``in_dev`` 专属 label/ref、新增寄存器、位域、公式与版本差异。
- 将全部网格表转换为等价 ``list-table``，清理转换遗留的孤立竖线和旧表格边界。
- 纠正公式变量被误译的问题，确保 ``out = (data*scale)/0x2000 + offset`` 与上游一致。
- 对计数器、DMA 缓冲区、触发、采集及数据流说明执行主流程英文残留复核。

## 2026-08-29 — 批次 013

- 完整翻译开发中版本的 v0.94 与 STEMlab 250-12 v0.94 两篇超大型寄存器映射。
- 完整翻译 OS 2.05-37 的四通道 streaming 寄存器映射。
- 将大型寄存器网格表转换为等价 ``list-table``，保留 ``in_dev`` 新增地址、位域、label/ref 和公式。
- 恢复被误译的官方型号 ``STEMlab 125-14 4-Input``，并加入术语表作为不可翻译产品标识。
- 清理孤立表格边界、中英混合说明及公式变量误译，执行宽词表和结构一致性复核。

## 2026-08-29 — 批次 014

- 完整翻译 OS 2.05-37 的 v0.94、STEMlab 250-12 v0.94 和 stream_app 三篇寄存器映射。
- 逐项保留 2.05-37 特有寄存器，并排除后续 2.07-48 才引入的地址与扩展功能。
- 将全部寄存器网格表转换为等价 ``list-table``，保留地址、位域、R/W、公式、型号和 Sphinx 引用。
- 清理 DMA、缓冲区、位数和计数器说明中的漏译，以及转换产生的孤立表格边界。

## 2026-08-29 — 批次 015

- 完整翻译 OS 2.05-37 的 stream_app_250，至此该版本主要寄存器页面全部中文化。
- 完整翻译 OS 2.04-35 的 stream_app 与 stream_app_4ch 两篇寄存器映射。
- 将所有网格表转换为等价 ``list-table``，保留地址、位域、R/W、公式与版本差异。
- 新增十六进制技术令牌一致性门禁，防止误引入其他 OS 版本的寄存器、地址或常量。
- 修复公式变量 ``offset`` 误译、采样数漏译及触发选择器表格边界问题。

## 2026-08-30 — 批次 016

- 停止逐版本整页重译历史寄存器文档，保留已完成成果；未验收的中间稿继续标记为 ``todo``。
- 新增 SHA-256、英文行级相似度与 unified diff 复用工具，以及可审计的复用工作流说明。
- 通过完全相同英文哈希复用 4 篇 streaming 页面；通过仅标题装饰线差异的安全模式复用 3 篇页面。
- 完整翻译 Gen2 通用硬件规格、C++ 构建安装指南和采集/生成原理介绍三篇非重复正文。
- 保留命令、代码块、型号、器件名、单位、公式、label/ref 和图片路径，并清理孤立 substitution 标记。
- 历史寄存器后续仅按已验收候选的英文 diff 翻译新增或变化块；Agent 优先投入 Hardware、Software 与 Applications。

## 2026-08-30 — 批次 017

- 完整翻译高级 SD 卡操作与故障排除 FAQ，至此 Quick Start 21 篇全部中文化。
- 完整翻译 Software 安全指南与 Applications 支持功能/应用总览。
- 审阅 2.00-18 与已验收 streaming 页的英文 unified diff，并以 diff SHA-256 锁定后复用三篇中文稿；仅翻译新增 label 与变化字段。
- 新增用户可见的 Quick Start、Hardware、Software、FPGA Current、Core Applications、Examples/Archive 自动里程碑报告。
- 停止人工修复低优先级历史寄存器；旧型号 Hardware 中断稿保留为 ``todo``，Agent 槽位转向当前高价值正文。

## 2026-08-30 — 批次 018

- 完整翻译 STEMlab 125-14 Gen 2 当前板卡页、串行控制台入门页，以及 Oscilloscope 与 Signal Generator 核心应用页。
- 保留命令、代码、型号、器件名、单位、图片路径和 Sphinx label/ref，仅翻译可见标题、说明、规格和交叉引用文字。
- 将板卡与应用规格表转换为可维护的 ``list-table``，集中修复中文标点邻接内联标记、标题装饰线和指令选项结构。
- 历史寄存器页面继续暂停人工处理；本批 3 篇均为非重复、高学习价值的当前正文。

## 2026-08-30 — 批次 019

- 完整翻译 STEMlab 125-14 PRO Gen 2 当前板卡与 Software 网络配置两篇高价值开发文档。
- 完整翻译 Spectrum、Bode、LCR Meter、Impedance Analyzer、Logic Analyzer 五个核心应用及 Streaming 主入口。
- 完整翻译远程控制与 C++/Python 应用两个入口页，保留 toctree、include、label/ref target、命令、代码、路径和 URL。
- 将易受中文宽度影响的规格网格表转换为等价 ``list-table``，集中修复页面顶层缩进、内联标记邻接和缺失页头结构。
- 本批共登记 10 篇非重复核心正文；历史寄存器、Examples 与 Archive 均未占用翻译槽位。

## 2026-08-30 — 批次 020

- 完整翻译 STEMlab 125-14 PRO Z7020 Gen 2 当前板卡、Software 服务管理和 SCPI 远程控制三篇大型核心正文。
- 完整翻译 Streaming 使用与配置入口、Web 界面、ADC 配置、本地流传输、Red Pitaya Linux 客户端和桌面客户端 API。
- 保留命令、代码块、SCPI 指令、systemd unit、配置键值、路径、URL、型号、单位、label/ref target 与图片路径。
- 集中修复 SCPI 中文网格表、Z7020 E3 连接器脚注以及 ADC 保存模式漏译，未通过集中验收的 Agent 初稿不计入进度。
- 本批登记 10 篇当前核心页面；历史寄存器、Examples 与 Archive 继续冻结。

## 2026-08-30 — 批次 021

- 按新的 STEMlab 125-10-first 顺序，完整翻译 125-10 主硬件页、Original Gen 通用规格、六型号比较、硬件与软件已知问题及 System Info。
- 完整翻译适用于 125-10 的校准与 Overlay 工具、阻抗变换器扩展板，并逐项核验 ADC/DAC、E1/E2、供电、接口、限制与兼容性。
- 完整翻译采集/发生主线：``acquire``、``generate``、采样与抽取、阈值触发采集；保留所有代码、API、命令、变量、数值和路径。
- 完整翻译当前 Streaming 的 DAC 与内存配置，重点保留 125-10 双通道 DAC 与 256 MB 内存环境相关语义。
- 将 125-10 主页面三张表、六型号比较表及采样/抽取数据表重写为等价 ``list-table``，集中返修 Agent 漏译、错误 URL 和 RST 警告。
- 本批登记 15 篇，全部属于新优先级 1–4；其他板型、非核心 Applications、历史寄存器与归档保持暂停。

## 2026-08-30 — 批次 022

- 依据官方 Original Generation 支持表中 STEMlab 125-10 的 ``Streaming = Y``，完整翻译当前 Streaming 命令行客户端、限制、技术细节、高级配置、性能优化、Raspberry Pi 客户端和参考入口。
- 转入优先级 5，完整翻译 SCPI 命令入口、C++/Python API 入口、Deep Memory Mode、远程控制已知问题和采集命令全集。
- 将 ``commands-acq.rst`` 的五张超宽网格表机械转换为等价 ``list-table``，逐单元格翻译 DESCRIPTION、ECOSYSTEM、触发、抽取、缓冲和数据读取说明，同时保持 SCPI/C++/Python/Jupyter 标识不变。
- 多轮集中验收拒绝了仅翻译概述或后半漏译的初稿，最终将本批疑似英文正文收敛至 0，并修复所有中文内联标记警告。
- 本批登记 12 篇，全部属于适用于 125-10 的优先级 4–5；其他板型、非核心 Applications、历史寄存器与归档继续暂停。

## 2026-08-30 — 批次 023

- 依据官方 Original Generation 支持矩阵中 STEMlab 125-10 的 SCPI 与 C++/Python API 支持状态，完整翻译信号发生、板级控制、模拟 I/O 和数字 I/O 四篇命令参考。
- 将四页固定宽度网格表转换为等价 ``list-table``，逐条翻译 DESCRIPTION、适用版本、参数和行为说明，保留 SCPI 命令、API 签名、参数、常量与示例代码。
- 集中修复 Agent 初稿误译的 ``RP_OK``、``rp_gen_*_t``、``<mode>``、``LASTValue`` 等技术令牌，并拒绝登记仅翻译概述而保留英文表格的部分稿。
- 本批四篇均属于适用于 STEMlab 125-10 的优先级 5；历史寄存器、其他板型、非核心 Applications 与批量 Examples 继续暂停。

## 2026-08-30 — 批次 024

- 完整翻译适用于 STEMlab 125-10 的 SCPI 初始化、Deep Memory、I²C 与 SPI 四篇命令参考，继续推进优先级 5 远程控制/API 主线。
- 将 Deep Memory、I²C、SPI 和初始化页的固定宽度命令表转换为等价 ``list-table``，完整翻译 DMA/DMG、SMBus、IOCTL、SPI 模式、缓冲区与传输行为说明。
- 保留 SCPI 命令、C++/Python API、设备路径、参数、常量、单位、label/ref 和 URL，并集中修复中文邻接行内字面量导致的严格构建警告。
- 本批登记四篇高价值当前正文；历史寄存器、其他板型、非核心 Applications 与批量 Examples 继续暂停。

## 2026-08-30 — 批次 025

- 完整翻译 STEMlab 125-10 可通过 E1/E2 与扩展模块使用的 CAN、Logic Analyzer、LCR 三篇 SCPI/API 命令参考。
- 将三页命令网格表转换为等价 ``list-table``，逐条翻译 CAN 位定时、控制器状态、套接字、过滤器、收发帧、时间戳，以及逻辑分析和 LCR 测量命令说明。
- 保留 SCPI/C++/Python 标识、CAN 状态与错误码、设备参数、公式、单位、label/ref 和 URL，并修复行内字面量与中文标点邻接警告。
- 本批三篇均属于优先级 5；历史寄存器、其他板型、非核心 Applications 与批量 Examples 继续暂停。

## 2026-08-30 — 批次 026

- 完整翻译适用于 STEMlab 125-10 的 Original Gen SATA Daisy-chain、UART 与 Status LEDs 三篇 SCPI/API 命令参考。
- 将三页固定宽度命令表转换为等价 ``list-table``，完整翻译时钟/触发同步、UART 格式与超时、MMC/Heartbeat/Ethernet LED 控制说明。
- 明确排除仅适用于 SIGNALlab 250-12 的 PLL 和温度保护页，不让其他型号专属内容占用当前翻译槽位。
- 保留命令、API 签名、设备路径、参数、label/ref 与版本令牌，并修复 UART 超时行内字面量和中文邻接警告。

## 2026-08-30 — 批次 027

- 回到优先级 2 Hardware，完整翻译与 STEMlab 125-10 E1/E2 及核心测量应用相关的 Sensor、Logic Analyzer、LCR 三篇扩展板硬件正文。
- 将 Sensor 与 Logic Analyzer 页的九张网格表转换或修复为宽度安全的 ``list-table``，完整保留引脚、协议、器件、图片、URL 与 Sphinx 引用。
- 完整翻译模块说明、包装清单、连接器、Arduino/Grove 兼容性、传感器分类、逻辑电平比较、安装连接和应用入口。
- 仅支持 STEMlab 125-14 的 SDR 模块和仅支持 Gen2 E3 的 eMMC/QSPI 模块继续后置。

## 2026-08-30 — 批次 028

- 转入 Software 主线，完整翻译适用于 STEMlab 125-10 的 SSH 入门、GPIO、SPI 配置与远程软件部署四篇当前正文。
- 覆盖 Windows/Linux/macOS SSH 连接、Overlay 加载、E1 GPIO 编号映射、sysfs/字符设备访问、E2 SPI 设备树和远程部署流程。
- 保留终端命令、代码块、路径、sysfs 节点、IP/URL、信号名、图片与 label/ref，并将 GPIO 映射表改为宽度安全的 ``list-table``。
- 集中清理 Agent 初稿中的中英混合句及 SPI/GPIO 说明漏译，最终将疑似英文正文收敛至 0。

## 2026-08-30 — 批次 029

- 完整翻译 WSL 开发环境、Debian/Ubuntu SD 卡镜像构建和 915 行 Ecosystem 构建指南，覆盖 Software 系统构建主线。
- 保留所有命令、脚本、路径、变量、版本、仓库 URL、代码块、tab 结构与 label/ref，完整翻译主机依赖、Vivado/SDK、chroot、FPGA/U-Boot/内核/用户空间组件流程。
- 增强简单网格表转换器，使其可在中文内容改变固定列宽后安全解析无跨列网格表；本批机械转换 Debian 四张和 Ecosystem 三张表。
- 集中修复大型页面分段翻译造成的嵌套 tabs 缩进、列表缩进、粗体邻接及混合英文残留，最终严格构建通过。

## 2026-08-30 — 批次 030

- 完整翻译适用于 STEMlab 125-10 的 Streaming 应用开发、WebApp 入口、首个 Web 应用教程和手动应用管理四篇 Software 正文。
- 覆盖 Qt Streaming 客户端构建、WebApp 架构入口、前后端文件结构、WebSocket、FPGA、C++ 编译、SD 卡/SCP/WinSCP 安装及故障排除。
- 保留 HTML/JavaScript/C++/JSON 代码、命令、路径、变量、键值、URL、图片、substitution 和 label/ref；恢复被误译的 C 代码注释以满足代码块完全一致门禁。
- Gen2 专属 OS 兼容性页继续后置，不占用本批 125-10 Software 学习主线。

## 2026-08-30 — 批次 031

- 完整翻译控制台访问入口、WebApp 系统架构和适用于 Original Gen E2 的 SPI TFT/触摸显示配置三篇 Software 正文。
- 覆盖 SSH/串口导航、前后端/Nginx/WebSocket 生命周期，以及 TFT pinctrl、设备树、引脚映射、驱动、背光、触摸控制器和硬件修改。
- 保留命令、代码、设备树、路径、引脚/信号、产品名、URL、raw HTML、substitution、图片与 label/ref；仅为官方产品链接显示名增加静态检查白名单。
- 集中返修 WebApp 中英混合说明和 TFT 电源竞争条件漏译，并修复中文标点邻接行内 interpreted text 的严格构建警告。

## 2026-08-30 — 批次 032

- 完整翻译 Applications 总入口、官方精选应用入口、Streaming 高级功能入口与多板卡 Streaming 四篇高价值正文，使 Core Applications 达到 33/33。
- 多板卡页覆盖适用于 STEMlab 125-10 / Original Gen SATA 的网络拓扑、配置、发现、启动、性能优化、故障排除与数据丢失诊断。
- 保留命令、配置键、路径、端口、代码输出、公式、图片、URL 和 label/ref，并集中清理多板卡页遗留英文及粗体邻接警告。
- 本批属于优先级 4 当前 Streaming；历史寄存器、其他板型、非核心 Applications 和批量 Examples 继续暂停。

## 2026-08-30 — 批次 033

- 按优先级 2–3 完整翻译 Click Shield 硬件页，以及 STEMlab 125-10 通用的四篇 Acquisition 与四篇 Generation 示例，共九篇正文。
- 明确 STEMlab 125-10 / Original Gen 支持 Click Board、触发同步和 Click Shield 供电，但不支持该扩展板的外部时钟同步功能，避免套用其他型号能力。
- 覆盖即时采集、外部触发、分离触发、连续输出、突发输出和外部触发生成；保留全部代码、注释、API、命令、变量、路径、label/ref 与下载链接。
- 将 Click Shield 六张中文固定宽度表转换为等价 ``list-table``，集中修复初稿英文残留、note 缩进和表格宽度问题；其他型号、历史寄存器与非核心示例仍暂停。

## 2026-08-30 — 批次 034

- 按优先级 3 完整翻译 STEMlab 125-10 通用的四篇 Generation 与三篇 Acquisition/Generation 联动示例，共七篇正文。
- 覆盖任意波形、扫频、双通道同步/异步生成，以及同步输出采集和波形闭环验证，补齐当前采集—生成学习主线。
- 保留全部 C/Python/MATLAB/LabVIEW 代码与注释、SCPI/API、命令、变量、路径、label/ref、图片和下载链接。
- 主门禁补译任意波形缓冲区频率换算说明并修复 ``note`` 缩进；历史寄存器、其他板型和非核心示例继续暂停。

## 2026-08-30 — 批次 035

- 按优先级 4 完整翻译适用于 STEMlab 125-10、要求 OS 2.07 系列的 Streaming 示例入口、Quickstart、ADC/DAC CLI 与 ADC/DAC API 六篇正文。
- 覆盖服务器启动、DMM 配置、采样/输出速率、网络传输、文件转换、回调、缓冲管理、数据丢失诊断和性能调优。
- 保留 shell/C++/Python 代码及注释、终端输出、API、配置键、路径、变量、label/ref、URL 与下载链接。
- 主门禁二次清理短英文 UI/列表项，恢复误译 ASCII 代码块，修复 tabs 内容缩进及中文行内标记邻接；1308 行 Streaming API Reference 留作下一批独立处理。

## 2026-08-30 — 批次 036

- 按优先级 4 完整翻译 1308 行当前 Streaming API Reference，至此七篇 Streaming CLI/API 示例与参考页全部登记完成。
- 覆盖 ADCStreamClient、ADCCallback、DACStreamClient、DACCallback、连接/配置/播放/内存方法、事件回调及 ADCPack/ADCChannel 数据结构。
- 保留所有类名、方法签名、类型、配置键、代码块与注释、终端输出、路径、URL、label/ref 和技术取值。
- 按章节边界并行翻译后整页复核，集中补齐短方法说明、``:param:``/``:returns:`` 描述和表格单元格，严格 Dummy 构建通过。

## 2026-08-30 — 批次 037

- 按优先级 5 完整翻译适用于 STEMlab 125-10 的远程控制示例入口、JupyterLab 与慢速模拟 I/O 四篇 API 示例，共六篇页面。
- 覆盖 Python API 笔记本、模拟输入读取、模拟输出设置和交互式控制，并保留 MATLAB、LabVIEW、C/C++ 与 SCPI 示例代码。
- 保留全部命令、代码及注释、API、变量、路径、substitution、label/ref、URL 和下载链接；PLL 与温度保护因仅适用于 250-12 继续后置。
- 主门禁检查短英文说明并修正模拟 I/O 入口标题及中文标题下划线宽度，严格 Dummy 构建通过。

## 2026-08-30 — 批次 038

- 按优先级 5 完整翻译 STEMlab 125-10 通用的数字 I/O 入口、LED 闪烁、条形图、交互式条形图和按钮输入五篇 API 示例。
- 覆盖 GPIO 输出、输入读取、板载 LED、外部按钮及交互式控制，并准确保留 STEMlab 125-14/125-10 的接线范围说明。
- 保留全部 C/Python/MATLAB/LabVIEW 代码与注释、SCPI/API、GPIO/引脚名、命令、变量、路径、label/ref、URL 和下载链接。
- 主门禁检查短英文正文、代码块一致性与引脚标识，严格 Dummy 构建通过；通信接口示例留待下一批。

## 2026-08-30 — 批次 039

- 按优先级 5 完整翻译通信接口入口、三篇 I2C 与两篇 SPI API 示例，共六篇适用于 STEMlab 125-10 的页面。
- 覆盖内部 EEPROM、硬件 API、外部 ``ioctl``、SPI 回环和 SPI 硬件 API，并保留设备节点、模式、频率、地址及寄存器。
- 保留全部 MATLAB/Python/C 代码与注释、SCPI/API、命令、``/dev/i2c-*``、变量、路径、label/ref、URL 和下载链接。
- 明确排除仅适用于 SIGNALlab 250-12 的 I2C AC/DC 模式页；主门禁补译外部 I2C 的函数与 API 短说明，严格 Dummy 构建通过。

## 2026-08-30 — 批次 040

- 按优先级 5 完整翻译两篇 UART 与两篇 CAN 通信接口示例，共四篇适用于 STEMlab 125-10 的页面。
- 覆盖 UART TX/RX 回环、UART 硬件 API、FPGA 层 CAN 回环及双 CAN 外部总线通信；准确保留 CAN0/CAN1 与 DIO 引脚映射。
- 明确 CAN 回环无需外部收发器，而外部总线示例需要两块 MCP2542 Click 或等效 CAN 收发器及 DB-9 接线。
- 保留全部代码与注释、SCPI/API、SocketCAN 命令、设备路径、波特率、变量、label/ref、URL；主门禁补译 GND 安全提示并修复 note 缩进。

## 2026-08-30 — 批次 041

- 确认 STEMlab 125-10 专属 Hardware 已无未完成正文后，转入优先级 2 Software，完整翻译 WebApp 示例入口、LED 控制、慢速模拟电压和信号生成四篇页面。
- 覆盖前后端参数通信、WebSocket/JSON、Red Pitaya API、FPGA overlay、模拟输入读取与 OUT1 波形生成，形成可运行的 125-10 WebApp 学习路径。
- 保留 HTML/JavaScript/C/C++/CSS/JSON 代码与注释、命令、路径、变量、label/ref、URL；将波形值网格表转换为等价 ``list-table``。
- 主门禁纠正 LED 教程初稿的大量漏译，补齐短 API/UI 说明并验证代码块与严格 Dummy 构建。

## 2026-08-30 — 批次 042

- 按优先级 2 完整翻译适用于 STEMlab 125-10 的实时模拟曲线、增益/偏移、Nginx+Lua 与简单 WebApp 四篇 Software 示例。
- 覆盖连续信号缓冲、Flot 绘图、前后端更新周期、信号调理公式、Nginx location、Lua API、部署测试和安全输入校验。
- 保留 HTML/JavaScript/C/C++/CSS/JSON/Nginx/Lua 配置与代码注释、命令、路径、变量、label/ref 和 URL。
- 主门禁二次清理 Agent 遗漏的测试、性能调优、数据流与安装短句，修复标题/inline markup，严格 Dummy 构建通过。

## 2026-08-30 — 批次 043

- 完整翻译适用于 STEMlab 125-10 的 Deep Memory 入口、长记录采集、采集方式对比、突发生成和连续生成五篇示例。
- 覆盖 DMM/DMA 内存分配、缓冲区地址约束、触发、普通采集对比，以及 DMG 突发/连续输出模式和当前限制。
- 保留全部 C/Python/MATLAB 代码与注释、SCPI/API、配置键、地址、变量、路径、label/ref、URL 和下载链接。
- 主门禁补译两页 SCPI 尚不可用说明并修复 note 缩进，确认 125-10 属于 OS 2.00-30 起支持的“其他板卡型号”。

## 2026-08-30 — 批次 044

- 完整翻译 Logic Analyzer 示例入口，以及适用于 STEMlab 125-10 的 UART、SPI、I2C 三篇 FPGA 内部回环解码示例。
- 覆盖 Logic Analyzer Python API、协议解码参数、E1/E2 接线、SPI 实际时钟取整和 I2C 固定 400 kHz 限制。
- 保留全部 Python 代码与注释、API、命令、协议/引脚名、地址、变量、路径、include、label/ref 和 URL。
- 选页前排除仅适用于 STEMlab 125-14 LN 主/从套件或外部时钟型号的三篇多板同步页面，并用文件比较确认其中文树副本未被修改。

## 2026-08-30 — 批次 045

- 按优先级 3 完整翻译适用于 STEMlab 125-10 Logic Analyzer 扩展的 UART、SPI、I2C 文件解码与 FPGA 采集解码六篇示例。
- 与上一批内部回环示例组合后，三种协议均形成“内部回环、从文件解码、FPGA 实际采集解码”的完整学习路径。
- 保留全部 Python 代码与注释、API、协议/引脚名、采集文件格式、命令、变量、路径、label/ref、URL 和下载链接。
- 统一核对协议参数、硬件/软件要求、代码块和短英文残留；结构检查无差异，并通过全站严格 Dummy 与 HTML 构建。

## 2026-08-30 — 批次 046

- 按优先级 2 完整翻译系统工具入口、校准总览、DC 校准与频率校准四篇页面，补齐 STEMlab 125-10 所属 Original Generation 的 ADC/DAC 校准学习路径。
- 覆盖校准设备与阻抗条件、自动/手动 DC 校准、LV/HV 频率均衡、EEPROM 校准区备份恢复、滤波器系数和验证流程。
- 保留全部命令、公式、代码、数值与单位、型号、路径、变量、label/ref、URL 和真实 UI 固定标识；未将 STEMlab 125-14 的特定阻抗示例扩写为 125-10 参数。
- 主门禁补译遗漏的 Second Generation 流程标题和十六进制说明，确认疑似英文正文为零、结构无差异，并通过全站严格 Dummy 与 HTML 构建。

## 2026-08-30 — 批次 047

- 按优先级 2 与 4 完整翻译 Network Manager、Red Pitaya OS Update、命令行工具入口和 Streaming CLI 四篇适用于 STEMlab 125-10 的当前页面。
- 覆盖 LAN/DHCP/静态 IP/Wi-Fi 配置、OS 在线升级及故障状态、FPGA overlay 加载、Streaming 服务配置、后台运行与数据文件说明。
- 保留全部命令与终端输出、网络字段和占位符、IP/SSID/DNS、路径、文件名、FPGA image、OS 版本、label/ref、URL；准确保留 250-12 的 ``stream_app_250`` 特例。
- 主门禁恢复 Agent 遗失的网络字段 inline literal 标记，补译 OS tabs，并处理中文标点与 RST markup 邻接警告；结构无差异，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 048

- 按优先级 2、3、5 完整翻译频率校准 CLI、Ecosystem 更新 CLI、Monitor 寄存器工具与采集数据保存/复制四篇适用于 STEMlab 125-10 的页面。
- 覆盖自动/外部频率校准、Nightly Build 下载安装、系统与 FPGA 寄存器访问、模拟混合信号，以及 NFS、``/tmp``、SCP/SFTP/WinSCP 数据导出流程。
- 保留终端命令与原始帮助输出、参数、地址、寄存器名、路径、占位符、文件名、版本、数值/单位、label/ref、URL 和 substitution。
- 主门禁补译 Monitor 的 OS tabs，统一“生态系统”术语，并修复更新步骤中不完整的 MD5 校验和译文；疑似英文正文为零、结构无差异，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 049

- 按优先级 3 与 5 完整翻译 CAN 文件解码、CAN FPGA 采集和 Profiles CLI 三篇适用于 STEMlab 125-10 的 Acquisition/API 页面。
- 补齐 Logic Analyzer 的 CAN 学习路径，明确 FPGA 内部回环因共用数字引脚不可行，外部采集必须使用 MCP2542 Click 或等效 CAN 收发器。
- Profiles CLI 覆盖读取当前板卡 ADC/DAC、采样率、量程、GPIO、FPGA 路径与采集/生成软件限制，并保留修改自定义限制不会改变硬件能力的警告。
- 保留全部 Python 代码与注释、终端帮助输出、JSON/配置键、协议参数、文件名、路径、版本、label/ref/include/URL；主门禁统一 Profiles 与“配置档案”术语，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 050

- 完整翻译 Spectrum、Bode、LCR 三篇适用于 STEMlab 125-10 的官方核心测量命令行工具页面。
- 覆盖频谱窗口/平均/CSV 输出、Bode 校准与扫频、LCR 分流电阻接线、自动量程和阻抗参数，衔接已完成的核心应用说明与终端工作流。
- 保留全部命令、原始帮助及示例输出、参数、窗函数名、CSV 字段、公式符号、路径、版本、频率与单位、label/ref/URL；准确保留 LCR 自动量程需要扩展模块的条件。
- 对上游未完成的 “The spectrum utility” 碎片仅作等价翻译而未臆造内容；主门禁补译 Bode 的 OS tabs，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 051

- 按优先级 3 完整翻译 RF Signal Recording and Playback、Arbitrary Waveform Manager 与 LCR SCPI 示例三篇适用于 STEMlab 125-10 的采集/生成核心页面。
- 覆盖 DMM/DMA 录制回放、split trigger、自动启动与资源限制，16384 点归一化任意波形上传，以及扩展板/外部分流电阻两种 LCR 测量路径。
- 准确保留 50 Ω 阻抗匹配、±0.5 V 输入范围与 0.75 V 绝对最大值、波形独立幅度控制、MCP/SCPI/配置参数及 125-14 4-Input 排除条件。
- 保留全部命令、配置块和代码注释、路径、键、变量、公式、版本、数值单位、label/ref/URL；主门禁恢复 ``trigger_level`` inline literal 并清理应用名英文残留，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 052

- 在 125-10 严格主线待译页已不足三篇后，转入原文明示兼容 125-10 的下一层，完整翻译 VNA、PyRPL 与 OS Version Compatibility 三篇页面。
- VNA 覆盖桥接模块接线、Windows/Linux 客户端、校准与测量；PyRPL 保留 125-10“未确认，但应该可以工作”的准确限定；兼容性页明确 Original Generation 支持全部 OS 且推荐最新稳定版。
- 保留第三方维护声明、已停产状态、TI/Gen 2 旧系统损坏警告、unsupported 配置措辞、型号与版本、命令、路径、label/ref/raw substitution/URL，未将其他板型结论外推到 125-10。
- 将 PyRPL 固定宽度表转换为等价 ``list-table``；主门禁修正上游/初稿中的 PyPRL 拼写并补译 discontinued，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 053

- 在严格 125-10 主线完成后，按采集/测量学习价值完整翻译 Frequency Response Analyzer、Impedance Analyzer 与 Red Pitaya DAQ Server 三篇通用 Marketplace 页面。
- 覆盖 0–60 MHz 双通道 DUT 频响与 DFT、1 Hz–60 MHz/0.1 Ω–10 MΩ 阻抗测量、5% 基本精度，以及最高 15.625 MS/s 连续生成/采集与 SCPI/TCP 客户端。
- 准确保留前两页的 outdated 状态、Impedance Analyzer 自 OS 2.00-30 起转为官方支持、未认证声明、LCR 扩展板/外部分流电阻和 DAQ 多板同步说明，不推断未写明的板型支持。
- 修复上游未定义的 ``Impedance Analyzer`` 命名链接，改指向现有 ``impedance_app`` label，并在结构检查中登记该精确修复；主门禁同时纠正“LCR 表”为“LCR 测量仪”，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 054

- 按学习价值完整翻译 Power Analyzer、Multichannel Pulse Height Analyzer 与 LTI DSP Workbench 三篇 Marketplace 测量/控制页面；明确排除仅面向 STEMlab 125-14 的 OCRA。
- 覆盖功率/谐波采集界面的八个功能区、1 µs–1 s 脉冲高度直方图，以及使用 H(z) 传递函数模拟线性物理系统和 Web 参数调整。
- 准确保留 Power Analyzer 已停止主动维护、论文为斯洛文尼亚语，以及 LTI 当前维护状态不明、原开发者似乎停止维护、文档有限等原文限定。
- 保留技术名、路径、采样参数、H(z)、作者/产品名、label/ref/raw substitution/URL；主门禁补译遗漏的 MCPHA 页面标题，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 055

- 完整翻译 Open-source Red Pitaya Radar、RadioBox 与 Teslameter 三篇 Marketplace RF/FPGA/EMC 实验页面。
- 覆盖 Red Pitaya RF 前端与 Raspberry Pi 3/4 四核处理、HF 电离层成像与变频微波用途，FPGA 收发机的 AC97 双向 I/Q 数据流，以及外部前端辅助的非期望辐射磁场测量。
- 准确保留 RadioBox 作者已删除文档和 GitHub、官方无法继续提供信息或支持、仅剩 SourceForge 归档的警告；不推断三项应用未写明的板型或性能。
- 保留端口名、FPGA/SDR/AC97/I/Q/QMIXers/EMC、产品与作者名、label/ref/raw substitution/URL；主门禁补译 RadioBox 标题括注和 marketplace 正文，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 056

- 完整翻译 Marketplace 总览以及 EPICS、Qt GUI、WSPR、SDR 四篇系统集成/RF 通信页面，共五篇。
- 总览覆盖 OS 2.07-43 后应用市场下线、社区应用获取与第三方支持责任，以及数据采集、RF、控制、分析和科研应用的兼容性/维护状态全表。
- 补齐 asynPortDriver 板上运行、Zynq 独立便携 GUI、WSPR 低功率传播路径探测和 HDSDR/SDR#/PowerSDR/GNU Radio 软件无线电入口；不推断未写明的板型支持。
- 将总览宽网格表转换为等价 ``list-table`` 并保留全部行、脚注和 toctree；主门禁补译表内 Custom OS image、Active、Abandoned、Ported 等状态字段，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 057

- 在高优先级主线与 Marketplace 主体完成后，开始 125-10 兼容的 Click Shield 示例尾部，完整翻译 Click Board 总入口、Basic 分类、Button G、Cap Touch 与 Relay 五篇页面。
- 形成按钮/电容触摸数字输入与双继电器数字输出的基础学习路径，覆盖两个 mikroBUS 插槽选择、DIO 引脚和板载 LED/PWM 行为。
- 保留全部 C 代码及注释、``MIKROBUS``、DIO/引脚/API、命令、路径、产品名、label/ref/include/toctree/URL，代码块与上游字节一致。
- 主门禁复核五页短英文残留仅为产品/技术名称与代码注释，结构无差异，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 058

- 完整翻译 125-10 兼容的 Click Shield Sensor 分类入口与 Current、Light、Motion、Thermo 16 四篇示例，共五篇页面。
- 覆盖两个 mikroBUS 模拟输入映射、分流电阻电流换算、光强读取、``RP_DIO2_P``/``RP_DIO4_P`` 运动中断输入，以及 30 次采样平均温度显示。
- 保留全部 C 代码及注释、3.3 V/20 倍增益/公式/单位、MIKROBUS/AIN/DIO/引脚/API、命令、路径、官方 Click Board 产品名、label/ref/include/toctree/URL。
- 主门禁统一 Thermo 16 Click Board 产品名，确认代码块字节一致、结构无差异，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 059

- 完整翻译 125-10 兼容的 Click Shield Motor 与 Data 分类入口，以及 DC Motor、Vibro Motor、ISO ADC 3 三篇示例，共五篇页面。
- 覆盖 PWM/DIO 直流电机方向与速度控制、振动电机 PWM 驱动，以及基于 MCP3221 的 I²C 12 位模数转换与 ±250 mV 输入测量。
- 保留全部 C 代码及注释、设备路径、I²C 地址、公式、数值、MIKROBUS/PWM/DIO/API、命令、label/ref/include/toctree/URL；上游未给出的外部供电说明不作推断或补写。
- 主门禁统一 ISO ADC 3 Click Board 产品名，确认代码块字节一致、结构无差异，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 060

- 保留并验收并行产生的 I²C AC/DC 与三篇多板同步译文，共四篇；复核后将其明确归入非 125-10 后置成果，不计作 STEMlab 125-10 核心主线进展。
- I²C AC/DC 页面按原文限定于 SIGNALlab 250-12；多板同步页面准确保留外部时钟型号、SATA/Click Shield 两类布线、主从触发与同步采集条件，未将兼容性外推到标准 STEMlab 125-10。
- 保留全部 MATLAB/Python/C/C++ 代码及注释、SCPI/API 命令、设备路径、I²C 地址、变量、数值、label/ref/include/toctree/URL；修复中文标题下划线并恢复代码块中的原始空行。
- 主门禁确认疑似英文正文为 0、中文新增重复 label 为 0、结构差异为 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 061

- 在 125-10 核心主线完成后进入全站补齐阶段，完整翻译 E3 硬件/软件入口、QSPI eMMC 模块硬件与软件、外部启动五篇当前扩展链路页面；Software 里程碑由 37/40 提升至 40/40。
- 覆盖 STEMlab 125-14 Pro Gen 2/Z7020 Gen 2 兼容性、E3 引脚和高速差分对、QSPI/eMMC 启动介质、电源/安全关机/看门狗状态机、STM32L412 编程、Arduino IDE/STM32CubeProgrammer 配置及 I2C 控制。
- 准确保留 I2C1/UART 当前无物理连接器而不受支持、高速差分对仅限 Z7020 Pro Gen 2 等限制；未将 E3 功能外推到 STEMlab 125-10。
- 保留全部代码及注释、命令、路径、变量、引脚名、地址、数值、label/ref/toctree/URL/图片；将五张硬件网格表等价转换为 ``list-table``，并补译功能列表与图片替代文本。
- 主门禁确认疑似英文正文为 0、代码块字节一致、中文新增重复 label 为 0、结构差异为 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 062

- 完整翻译 STEMlab 125-14 Gen 2 测量入口、快速模拟输入、快速模拟输出、已知硬件问题与 FAQ 五篇当前 Hardware 页面。
- 覆盖统一测试条件、ADC/DAC 规格、带宽与平坦度、噪声、串扰、SFDR/SNR/THD/ENOB、校准入口、Gen 2 改进，以及时钟选择、同步、电源、E3/USB-C 和 Bank 13 引脚常见问题。
- 准确保留测试板为 STEMlab 125-14 PRO Z7020 Gen 2、同模拟前端适用范围、各衰减档和频段差异、已知问题影响型号与设计限制，未向 STEMlab 125-10 外推规格。
- 将输入、输出规格和 FAQ 网格表等价转换为 ``list-table``；保留型号、数值、单位、公式、引脚/信号名、label/ref/URL/图片，并补译表内 LED 描述与分辨率单位。
- 主门禁确认疑似英文正文为 0、中文新增重复 label 为 0、结构差异为 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 063

- 完整翻译 STEMlab 125-14 TI、STEMlab 65-16 TI 两篇 Gen 2 硬件主规格页及 Gen 2 型号对比页，共约 1400 行。
- 覆盖板卡功能、ADC/DAC/时钟/FPGA 信号链、快速参考、完整技术规格、器件清单、E1/E2 与 S1/S2 接口、GPIO、同步、供电、启动、校准、原理图资源以及全部型号对比字段。
- 准确保留 ADC3664/ADC3663、DAC2904、LMK03318、Zynq 7020 等器件及 14/16-bit、采样率、带宽、抖动和电平数据；不将 TI 型号规格外推到 STEMlab 125-10。
- 将 65-16 TI 快速参考/GPIO 表与型号对比表等价转换为 ``list-table``，125-14 TI 三张网格表按中文显示宽度重新对齐；保留型号、料号、引脚/信号名、数值、单位、label/ref/URL/下载/图片。
- 主门禁补齐首轮遗漏的 65-16 TI 规格和 GPIO 表，并统一器件标题与连接器链接显示文字；疑似英文正文为 0、中文新增重复 label 为 0、结构差异为 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 064

- 完整翻译已停用的 SDR Module/HAMlab 硬件文档、Hardware 认证资料，以及 Original Generation STEMlab 125-14 测量入口、快速模拟输入与快速模拟输出五篇页面。
- SDR 页面覆盖包装、接线、PowerSDR 配置、收发/示波器/信号发生器规格、前后面板、RF 安全、供电保险丝、接地、音频、CTRL/DATA 接口；准确保留停用状态和仅供参考限定。
- 测量页覆盖统一测试条件、ADC/DAC 规格、带宽、串扰、增益/偏移、校准应用与 ``calib`` 工具；认证页覆盖 CE/FCC、CB EMC/安全、RoHS/REACH/PFAS、冲突矿产和 NRTL 记录及下载。
- 将 SDR 页十张网格表等价转换为 ``list-table`` 并修复跨列标题；保留代码/控制台输出、型号、数值、单位、证书名、label/ref/URL/下载/图片，主门禁统一 PowerSDR、位、W 和采样点显示。
- 静态扫描为 Agilent E4404B 原始 HTML substitution 增加精确白名单；疑似英文正文为 0、中文新增重复 label 为 0、结构差异为 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 065

- 完整翻译 Original Generation 的 STEMlab 125-14、STEMlab 125-14 Z7020-LN 与 SIGNALlab 250-12 三篇大型硬件主规格页，共约 1950 行。
- 覆盖功能、快速参考、完整规格、信号链器件、E1/E2 与 SATA/USB 接口、GPIO、辅助 I/O、外部时钟/PLL、同步、供电、启动、校准、原理图和 3D 下载。
- 分别核验 125-14 的 Zynq 7010/Micro USB/16 GPIO/SATA、Z7020-LN 的线性电源/22 GPIO/停产状态，以及 250-12 的 12-bit 250 MS/s ADC、BNC、24 V/PoE、USB-C 和外部参考时钟，未跨型号混用规格。
- 将 Z7020-LN 五张表等价转换为 ``list-table``，修复 250-12 中文网格表及 line-block；保留型号、料号、引脚信号、数值单位、label/ref/URL/下载/图片/代码块。
- 主门禁补译 250-12 功能条目、两处 Pin 表头、125-14 电阻位置图注及连接器文字，并以精确结构白名单保留上游 ``Schematics`` 隐式链接对应的中文显式 ref；疑似英文正文为 0、结构差异为 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 066

- 一次补齐六篇 Original Generation 硬件变体页：SDRlab 122-16/External Clock，以及 STEMlab 125-14 4-Input、External Clock、Low Noise、X-Channel Secondary。
- 逐型号保留 122.88 MHz SDR 时钟与相位反转、外部时钟工厂预修改及无 LVDS 时钟时 FPGA 不工作、4-Input 四路输入且无 RF 输出、LN 线性模拟稳压器，以及 Secondary 从 SATA 接收 ADC 时钟且不可独立运行等关键限制。
- 覆盖完整规格、E1/E2 引脚、GPIO、器件、时钟电阻修改、同步、供电、性能说明、原理图/3D 下载和脚注；多张网格表按中文显示宽度重排或等价转换为 ``list-table``。
- 保留型号、料号、引脚信号、数值单位、label/ref/URL/下载/图片/代码块；主门禁补译 122-16 器件标题与最大输入电压表、LN 功能条目及 4-Input 分辨率单位。
- 为 4-Input 上游 ``Schematics`` 隐式链接对应的中文显式 ref 增加精确结构白名单；疑似英文正文为 0、中文新增重复 label 为 0、结构差异为 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 067

- 以当前文件哈希而非旧批次记录为准，发现并重新补齐 16 篇仍与上游英文完全相同的非寄存器页面；其中包含曾被记录为完成但译文未保留的 VNA、PyRPL 和 SDR 页面。
- 补齐 404、六篇 Marketplace 短页、SDR 收发器、Daisy/E3 I2C/LED 实用程序、多板同步、PLL/温度保护命令、自定义服务、扩展模块模板；Hardware 达到 39/39，所有非寄存器正文清空。
- 多板同步覆盖 Click Shield 与旧 X-Channel、Primary/Secondary 硬件限制、线缆方向、兼容性和流传输示例；SDR 页覆盖 HPSDR/Metis、Hermes、GNU Radio、SDR#/HDSDR 与 macOS 客户端限制。
- 保留全部命令帮助输出、代码块、参数、路径、变量、型号、数值、label/ref/URL/下载/图片；PLL 表等价转换为 ``list-table``，修复 SDR 内联链接和 Daisy 标题下划线。
- 清理约 5.0 GiB 可再生成的历史 ``build/`` 缓存，释放磁盘空间后重建；静态检查为 366/378、疑似英文正文 0、结构差异 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 068

- 按文件哈希和英文 diff 复用完成六篇历史寄存器页：2.04-35 的两篇既有进行中稿、由其机械派生的 2.00-30 两篇 ``v0.94``，以及 2.00-15 两篇 streaming 页面。
- 上游比较确认 2.00-30 与 2.04-35 的两组 ``v0.94`` 正文分别完全相同，中文稿仅替换版本 label/页首空行，不重复人工翻译表格。
- 清除早期 2.04 部分稿误混入的 2.05 新增寄存器：标准页排除 trigger protection clear、last-value/LFSR/noise-generator 块，250-12 页排除 ASG 0x70–0x84。
- 2.00-15 streaming 分别复用 2.00-23 普通页和 2.00-18/2.04-35 250 页，只按 diff 恢复版本专属 label、GPIO 大小写、访问属性与 primary/secondary 或 slave/master 语义。
- 地址、位域、R/W、代码、标识、数值、label/ref 均与对应 upstream 核验；静态检查 372/378、疑似英文正文 0、结构差异 0，严格 Dummy 与 HTML 构建通过。

## 2026-08-30 — 批次 069

- 使用已验收 2.04-35 中文稿和英文 diff 机械完成最后六篇历史 ``v0.94``：2.00-15、2.00-18、2.00-23 的标准版与 250-12 版；至此 378 篇全部登记完成。
- 2.00-18/2.00-23 仅移除对应上游不存在的 CAN0 0x34 块并修改版本 label；2.00-15 额外恢复 250-12 专属 ADC/DAC SPI 与温度保护字段，并删除后续版本字段。
- 逐页核对十六进制地址、位域、R、W、R/W、label/ref/code 计数；2.00-15 标准页地址 198、R 205、R/W 151，250-12 页地址 148、R 155、R/W 123，全部与 upstream 一致。
- 修正 2.00-18 标准页一段旧表格转换遗留的重复无地址位域，确认 2.00-18/2.00-23 地址和访问标识无数值漂移。
- 移除已完成示波器页的旧 ``NON_TRANSLATION_FIXES`` 例外，使覆盖率检查准确报告 378/378、待翻译 0；最终静态、结构、重复 label、严格 Dummy/HTML 和外链检查全部执行。

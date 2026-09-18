#!/usr/bin/env python3
"""Generate user-facing progress milestones from PROGRESS.tsv."""

from __future__ import annotations

import csv
import math
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]  # repository root
META = ROOT / "translations" / "zh_CN"
PROGRESS = META / "PROGRESS.tsv"
REPORT = META / "reports" / "milestones.md"
COMPLETED_STATUSES = {"draft", "reviewed", "done"}


def main() -> None:
    with PROGRESS.open(encoding="utf-8", newline="") as handle:
        rows = list(csv.DictReader(handle, delimiter="\t"))

    core_apps = {
        "appsFeatures/appsFeatures.rst",
        "appsFeatures/supportedFeaturesAndApps.rst",
        "appsFeatures/introAcqGen.rst",
        "appsFeatures/applications/apps-featured.rst",
        "appsFeatures/applications/oscSigGen/osc.rst",
        "appsFeatures/applications/spectrum/spectrum.rst",
        "appsFeatures/applications/bode/bode.rst",
        "appsFeatures/applications/lcr_meter/lcr_meter.rst",
        "appsFeatures/applications/impedance/impedance.rst",
        "appsFeatures/applications/logic/logic.rst",
        "appsFeatures/remoteControl/scpi.rst",
        "appsFeatures/remoteControl/API_scripts.rst",
        "appsFeatures/remoteControl/remoteAndProg.rst",
        "appsFeatures/remoteControl/command_list.rst",
    }
    core_apps.update(
        row["path"] for row in rows
        if row["path"].startswith("appsFeatures/applications/streaming/")
    )
    categories = {
        "Quick Start": lambda path: path.startswith("quickStart/"),
        "Hardware": lambda path: path.startswith("developerGuide/hardware/"),
        "Software": lambda path: path.startswith("developerGuide/software/"),
        "FPGA Current": lambda path: path.startswith("developerGuide/fpga/") and (
            "/regset/" not in path or "/regset/3.00-57/" in path
        ),
        "Core Applications": lambda path: path in core_apps,
        "Examples/Archive": lambda path: path.startswith("appsFeatures/examples/") or (
            "/regset/" in path and "/regset/3.00-57/" not in path
        ),
    }

    result = []
    for name, predicate in categories.items():
        selected = [row for row in rows if predicate(row["path"])]
        done = sum(row["status"] in COMPLETED_STATUSES for row in selected)
        result.append((name, done, len(selected)))

    total_done = sum(row["status"] in COMPLETED_STATUSES for row in rows)
    total = len(rows)
    core_remaining = sum(total_count - done for name, done, total_count in result if name != "Examples/Archive")
    full_remaining = total - total_done
    schedule_line = (
        "- 翻译范围已全部登记完成；后续工作为上游评审与增量维护。"
        if full_remaining == 0
        else "- 可学习核心站目标：优先选择各类别高价值子集，预计 12–18 批。"
    )
    lines = [
        "# 中文站里程碑",
        "",
        f"- 全站已登记：{total_done}/{total}（{total_done / total:.1%}）",
        f"- 核心类别保守工期：不超过 {math.ceil(core_remaining / 3)} 批（按每批最低 3 篇）",
        f"- 全站保守工期：不超过 {math.ceil(full_remaining / 3)} 批（未计哈希复用提速）",
        schedule_line,
        "",
        "| 里程碑 | 完成 | 总数 | 完成率 |",
        "|---|---:|---:|---:|",
    ]
    for name, done, total_count in result:
        lines.append(f"| {name} | {done} | {total_count} | {done / total_count:.1%} |")
    lines += [
        "",
        "## 口径",
        "",
        "- FPGA Current 包含非寄存器 FPGA 主干和当前 3.00-57 寄存器，不含旧 OS 与 in_dev 历史尾部。",
        "- Core Applications 包含常用功能入口、Oscilloscope、Spectrum、Bode、LCR/Impedance、Logic Analyzer、Streaming 与 SCPI/API 入口。",
        "- Examples/Archive 包含示例全集和非当前历史寄存器，仅在核心站后集中处理。",
    ]
    REPORT.parent.mkdir(parents=True, exist_ok=True)
    REPORT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(REPORT)


if __name__ == "__main__":
    main()

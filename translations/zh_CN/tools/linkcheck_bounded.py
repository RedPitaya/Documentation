#!/usr/bin/env python3
"""Run Sphinx linkcheck with a hard deadline and write a compact status report."""

from __future__ import annotations

import argparse
from collections import Counter
import json
from pathlib import Path
import sys
import subprocess


ROOT = Path(__file__).resolve().parents[3]  # repository root
META = ROOT / "translations" / "zh_CN"
OUTPUT = META / "build" / "linkcheck"
LOG = META / "reports" / "linkcheck-latest.log"
REPORT = META / "reports" / "linkcheck-latest.md"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--timeout", type=int, default=180, help="hard deadline in seconds")
    args = parser.parse_args()
    command = [
        sys.executable, "-m", "sphinx", "-E", "--keep-going",
        "-b", "linkcheck", str(ROOT / "zh_CN"), str(OUTPUT),
    ]
    timed_out = False
    try:
        result = subprocess.run(
            command, cwd=ROOT, text=True, stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT, timeout=args.timeout, check=False,
        )
        output, returncode = result.stdout, result.returncode
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        raw = exc.stdout or ""
        output = raw.decode(errors="replace") if isinstance(raw, bytes) else raw
        returncode = 124

    LOG.parent.mkdir(parents=True, exist_ok=True)
    LOG.write_text(output, encoding="utf-8")
    counts: Counter[str] = Counter()
    broken: list[dict[str, object]] = []
    output_json = OUTPUT / "output.json"
    if output_json.exists():
        for line in output_json.read_text(encoding="utf-8", errors="replace").splitlines():
            try:
                item = json.loads(line)
            except json.JSONDecodeError:
                continue
            counts[item.get("status", "unknown")] += 1
            if item.get("status") == "broken":
                broken.append(item)

    lines = [
        "# 最新限时外链检查", "",
        f"- 时间上限：{args.timeout} 秒",
        f"- 状态：{'超时（结果为部分扫描）' if timed_out else '完成'}",
        f"- 退出码：{returncode}",
        "- 状态计数：" + (", ".join(f"{k}={v}" for k, v in sorted(counts.items())) or "无结果"),
        "", "## Broken", "",
    ]
    lines.extend(
        f"- `{item.get('filename')}:{item.get('lineno')}` — {item.get('uri')} — {item.get('info', '')}"
        for item in broken
    )
    if not broken:
        lines.append("- 无")
    REPORT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(REPORT)
    return returncode


if __name__ == "__main__":
    raise SystemExit(main())

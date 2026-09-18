#!/usr/bin/env python3
from collections import Counter
import csv
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[3]  # repository root
META = ROOT / "translations" / "zh_CN"
SRC, ZH = ROOT, ROOT / "zh_CN"
REPORT = META / "reports" / "translation-check.md"
PROGRESS = META / "PROGRESS.tsv"
EXCLUDE = {".git", "zh_CN", "translations", "_build", "build"}
rst = sorted(p.relative_to(SRC) for p in SRC.rglob("*.rst") if not (EXCLUDE & set(p.relative_to(SRC).parts)))
NON_TRANSLATION_FIXES = set()
ENGLISH_ALLOWLIST = (
    "Content and privacy settings",
    "Content and Privacy Settings",
    "Content and Privacy",
    "Autoboot will start in 3...2...1... (Hit any key to stop)",
    "OpenBSD failed to start",
    "Flash from file",
    "Open With > Disk Image Writer",
    "Unified installer for FPGA & Adaptive SoC Tools",
    "AMD Unified installer for FPGA & Adaptive SoC Tools",
    "Name and Address verification",
    "Download and Install Now",
    "Language and Region settings",
    "Program and Debug",
    "This PC",
    "this GitHub solution",
    "Balena Etcher Error (0, h.requestMetadata) is not a function",
    "AND 模式",
    "Adafruit PiTFT 3.5\" Touch Screen for Raspberry Pi",
    "PiTFT - Assembled 480x320 3.5\" TFT+Touchscreen for Raspberry Pi",
    "PiTFT Plus 480x320 3.5\" TFT+Touchscreen for Raspberry Pi",
    "dirname /path/to/dir",
    "ls -d /path/to/dir\\*",
    "Agilent E4404B</a>",
)
missing = [p.as_posix() for p in rst if not (ZH / p).exists()]
unchanged = [p.as_posix() for p in rst if (ZH / p).exists() and ((SRC / p).read_bytes() == (ZH / p).read_bytes() or p.as_posix() in NON_TRANSLATION_FIXES)]

def collect_labels(tree):
    found = []
    for p in [q for q in list(tree.rglob("*.rst")) + list(tree.rglob("*.inc")) if not (EXCLUDE & set(q.relative_to(tree).parts))]:
        for n, line in enumerate(p.read_text("utf-8-sig", errors="replace").splitlines(), 1):
            m = re.match(r"^\.\.\s+_([^:]+):", line)
            if m:
                found.append((m.group(1), p.relative_to(tree).as_posix(), n))
    return found

labels = collect_labels(ZH)
upstream_counts = Counter(x[0] for x in collect_labels(SRC))
counts = Counter(x[0] for x in labels)
dupes = [x for x in labels if counts[x[0]] > 1]
new_dupes = [x for x in dupes if upstream_counts[x[0]] <= 1]

# Flag prose-like English lines only in files already changed; directives, links,
# code-ish lines and short headings are excluded to keep the report actionable.
suspects = []
for rel in rst:
    zp = ZH / rel
    if not zp.exists() or rel.as_posix() in unchanged:
        continue
    in_code = False
    for n, line in enumerate(zp.read_text("utf-8-sig", errors="replace").splitlines(), 1):
        s = line.strip()
        if re.match(r"^\.\.\s+(code-block|literalinclude|toctree)::", s):
            in_code = True
            continue
        if in_code and (not line or line[:1].isspace()):
            continue
        in_code = False
        if (len(s) >= 35 and re.search(r"\b(?:the|and|with|your|this|from|for|is|are|to)\b", s, re.I)
                and not s.startswith((".. ", ":", "http", "* :", "- :")) and "`" not in s):
            if not any(allowed in s for allowed in ENGLISH_ALLOWLIST):
                suspects.append((rel.as_posix(), n, s))

translated = len(rst) - len(unchanged) - len(missing)
with PROGRESS.open(encoding="utf-8", newline="") as handle:
    registered = {
        row["path"]
        for row in csv.DictReader(handle, delimiter="\t")
        if row["status"] in {"draft", "reviewed", "done"}
    }
changed_paths = {
    p.as_posix() for p in rst
    if (ZH / p).exists() and p.as_posix() not in unchanged
}
unregistered_changed = sorted(changed_paths - registered)
lines = [
    "# 翻译静态检查", "",
    f"- 官方 RST 页面：{len(rst)}",
    f"- 已登记完成页面：{len(registered)}",
    f"- 工作树中已修改页面：{translated}",
    f"- 已修改但未登记（进行中）：{len(unregistered_changed)}",
    f"- 与英文完全相同（待翻译）：{len(unchanged)}",
    f"- 中文树缺失页面：{len(missing)}",
    f"- 重复显式 label：{len(dupes)}（上游已有 {len(dupes) - len(new_dupes)}，中文新增 {len(new_dupes)}）",
    f"- 已修改页面中的疑似英文正文行：{len(suspects)}",
    "", "## 已修改但未登记", "",
]
lines += [f"- `{path}`" for path in unregistered_changed] or ["- 无"]
lines += ["", "## 疑似英文正文", ""]
lines += [f"- `{p}:{n}` — {s}" for p, n, s in suspects[:500]] or ["- 无"]
lines += ["", "## 重复 label", ""] + ([f"- `{name}` at `{p}:{n}`" for name, p, n in dupes] or ["- 无"])
REPORT.parent.mkdir(parents=True, exist_ok=True)
REPORT.write_text("\n".join(lines) + "\n", encoding="utf-8")
print(REPORT)
if missing or new_dupes or suspects:
    sys.exit(1)

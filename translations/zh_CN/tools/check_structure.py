#!/usr/bin/env python3
"""Compare non-translatable RST structure in translated pages with upstream."""

from collections import Counter
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[3]  # repository root
META = ROOT / "translations" / "zh_CN"
UPSTREAM = ROOT
ZH = ROOT / "zh_CN"
PROGRESS = META / "PROGRESS.tsv"
REPORT = META / "reports" / "structure-check.md"

# Translated section titles cannot serve as the original implicit hyperlink names.
# These explicit labels/refs preserve the same targets without changing navigation.
ALLOWED_ADDITIONS = {
    # The Chinese index carries a note pointing readers to the authoritative English docs.
    "index.rst": {
        "URL": Counter({"https://redpitaya.readthedocs.io/en/latest/": 1}),
    },
    # The upstream page uses an undefined named hyperlink. The translation
    # points to the existing official Impedance Analyzer label instead.
    "appsFeatures/applications/marketplace/impedance_anal/impedance.rst": {
        "ref/doc target": Counter({"impedance_app": 1}),
    },
    "developerGuide/hardware/ext_modules/sensor_ext/sensor_ext.rst": {
        # These are prose status notes styled as literals upstream, not code.
        "inline literal": Counter({"当前暂不支持": 2}),
    },
    "appsFeatures/introAcqGen.rst": {
        "label": Counter({
            "intro_oscilloscope_apps": 1,
            "intro_scpi_commands": 1,
            "intro_continuous_generation": 1,
            "intro_api_commands": 1,
            "intro_streaming": 1,
            "intro_dma": 1,
            "intro_custom_fpga": 1,
        }),
        "ref/doc target": Counter({
            "intro_oscilloscope_apps": 1,
            "intro_scpi_commands": 2,
            "intro_continuous_generation": 1,
            "intro_api_commands": 1,
            "intro_streaming": 1,
            "intro_dma": 2,
            "intro_custom_fpga": 1,
        }),
    },
    "developerGuide/fpga/getting_started/projects/project_creation.rst": {
        "label": Counter({
            "fpga_non_project_mode": 1,
            "fpga_project_mode": 1,
            "legacy_vivado_2020_1_compatibility": 1,
            "different_vivado_version": 1,
        }),
        "ref/doc target": Counter({
            "legacy_vivado_2020_1_compatibility": 1,
            "fpga_project_mode": 3,
            "different_vivado_version": 1,
            "fpga_non_project_mode": 1,
            "FPGA_project_flags": 1,
        }),
    },
    # The upstream grid table truncates eight :ref: roles before their closing
    # backticks.  The Chinese list-table repairs those links with their existing
    # labels instead of preserving invalid markup.
    "developerGuide/hardware/ORIG_GEN/compares/vs.rst": {
        "ref/doc target": Counter({
            "top_125_14": 1, "top_125_14_LN": 1, "top_125_14_Z7020_LN": 1,
            "top_125_14_4-IN": 1, "top_122_16": 1, "top_122_16_EXT": 1,
            "top_250_12": 1, "top_125_10": 1,
        }),
    },
    # The upstream grid tables use implicit `Schematics`_ links. Translated
    # headings change that implicit target name, so explicit refs preserve the
    # same existing section labels.
    "developerGuide/hardware/ORIG_GEN/125-14_Z7020/top.rst": {
        "ref/doc target": Counter({"schematics_125_14_Z7020": 1}),
    },
    "developerGuide/hardware/ORIG_GEN/250-12/top.rst": {
        "ref/doc target": Counter({"schematics_250_12": 1}),
    },
    "developerGuide/hardware/ORIG_GEN/125-14_4IN/top.rst": {
        "ref/doc target": Counter({"schematics_125_14_4_IN": 1}),
    },
}

ALLOWED_REMOVALS = {
    "developerGuide/hardware/ext_modules/sensor_ext/sensor_ext.rst": {
        "inline literal": Counter({"not supported at the moment": 2}),
    },
    "appsFeatures/applications/streaming/usage/stream_command_line.rst": {
        # This is prose styled as a literal in the source, not a command or
        # identifier; the Chinese translation intentionally removes the markup.
        "inline literal": Counter({"Network access troubleshooting": 1}),
    },
    "developerGuide/hardware/ORIG_GEN/compares/vs.rst": {
        "ref/doc target": Counter({
            "STEMlab 125-14               | :ref:": 1,
            "STEMlab 125-14 4-Input       | :ref:": 1,
            "SIGNALlab 250-12             | :ref:": 1,
            "STEMlab 125-14 LN            |                                    |                                    | :ref:": 1,
        }),
    },
}


def ref_targets(text: str) -> list[str]:
    targets = []
    for match in re.finditer(r":(?:ref|doc):`([^`]+)`", text):
        value = match.group(1)
        explicit = re.search(r"<([^<>]+)>\s*$", value)
        targets.append(explicit.group(1).strip() if explicit else value.strip())
    return targets


def toctree_entries(text: str) -> list[str]:
    entries = []
    lines = text.splitlines()
    for index, line in enumerate(lines):
        match = re.match(r"^(\s*)\.\.\s+toctree::\s*$", line)
        if not match:
            continue
        base_indent = len(match.group(1))
        for child in lines[index + 1 :]:
            if not child.strip():
                continue
            indent = len(child) - len(child.lstrip())
            if indent <= base_indent:
                break
            value = child.strip()
            if value.startswith(":"):
                continue
            explicit = re.search(r"<([^<>]+)>\s*$", value)
            entries.append(explicit.group(1).strip() if explicit else value)
    return entries


def code_blocks(text: str) -> list[str]:
    """Return normalized directive code bodies; prose outside code is ignored."""
    blocks = []
    lines = text.splitlines()
    index = 0
    while index < len(lines):
        match = re.match(r"^(\s*)\.\.\s+(?:code-block|sourcecode)::", lines[index])
        if not match:
            index += 1
            continue
        base_indent = len(match.group(1))
        index += 1
        body = []
        body_started = False
        while index < len(lines):
            line = lines[index]
            if not line.strip():
                if body_started:
                    body.append("")
                index += 1
                continue
            indent = len(line) - len(line.lstrip())
            if indent <= base_indent:
                break
            stripped = line.strip()
            if not body_started and stripped.startswith(":"):
                index += 1
                continue
            body_started = True
            body.append(line[base_indent + 1 :])
            index += 1
        while body and body[-1] == "":
            body.pop()
        blocks.append("\n".join(body))
    return blocks


def structure(text: str) -> dict[str, Counter]:
    patterns = {
        "URL": r"https?://[^\s>`\)\]）]+",
        "label": r"^\.\.\s+_([^:]+):",
        "include": r"^\s*\.\.\s+(?:include|literalinclude)::\s*(\S+)",
        "image": r"^\s*\.\.\s+(?:image|figure)::\s*(\S+)",
        "download": r":download:`[^`<]*<([^>]+)>`",
        "inline literal": r"(?<!`)``([^`\n]+)``(?!`)",
        # Register maps frequently differ only in numeric addresses. Comparing
        # every hexadecimal token prevents a translation from accidentally
        # importing registers or constants from another documentation release.
        "hex token": r"(?<![A-Za-z0-9_])0x[0-9A-Fa-f]+(?![A-Za-z0-9_])",
    }
    result = {
        name: Counter(re.findall(pattern, text, re.MULTILINE))
        for name, pattern in patterns.items()
    }
    result["ref/doc target"] = Counter(ref_targets(text))
    result["toctree entry"] = Counter(toctree_entries(text))
    result["code block"] = Counter(code_blocks(text))
    return result


def translated_pages() -> list[str]:
    pages = []
    for line in PROGRESS.read_text("utf-8").splitlines()[1:]:
        columns = line.split("\t")
        if len(columns) >= 2 and columns[1] != "todo":
            pages.append(columns[0])
    return pages


problems = []
pages = translated_pages()
for relative in pages:
    source = UPSTREAM / relative
    translated = ZH / relative
    if not source.exists() or not translated.exists():
        problems.append((relative, "file", "missing source or translation"))
        continue
    source_text = source.read_text("utf-8-sig", errors="replace")
    translated_text = translated.read_text("utf-8-sig", errors="replace")
    source_structure = structure(source_text)
    translated_structure = structure(translated_text)
    for kind in source_structure:
        expected_source = source_structure[kind] - ALLOWED_REMOVALS.get(relative, {}).get(kind, Counter())
        allowed = ALLOWED_ADDITIONS.get(relative, {}).get(kind, Counter())
        if kind == "inline literal":
            # Adding literal markup around an unchanged identifier is safe; changing
            # or removing an upstream literal remains an error.
            added_markup = translated_structure[kind] - source_structure[kind]
            allowed += Counter({value: count for value, count in added_markup.items() if value in source_text})
        adjusted_translated = translated_structure[kind] - allowed
        if expected_source != adjusted_translated:
            missing = expected_source - adjusted_translated
            added = adjusted_translated - expected_source
            detail = f"missing={dict(missing)}; added={dict(added)}"
            problems.append((relative, kind, detail))

lines = [
    "# RST 结构一致性检查",
    "",
    f"- 已检查翻译页面：{len(pages)}",
    f"- 结构差异：{len(problems)}",
    "",
    "## 差异",
    "",
]
if problems:
    lines.extend(f"- `{page}` [{kind}] — {detail}" for page, kind, detail in problems)
else:
    lines.append("- 无")
REPORT.write_text("\n".join(lines) + "\n", encoding="utf-8")
print(REPORT)
sys.exit(1 if problems else 0)

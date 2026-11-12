#!/usr/bin/env python3
"""Find exact and near-duplicate upstream pages for translation reuse."""

from __future__ import annotations

import csv
import hashlib
from collections import defaultdict
from difflib import SequenceMatcher
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]  # repository root
META = ROOT / "translations" / "zh_CN"
SOURCE = ROOT
PROGRESS = META / "PROGRESS.tsv"
REPORT_TSV = META / "reports" / "reuse-candidates.tsv"
REPORT_MD = META / "reports" / "reuse-candidates.md"


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def lines(path: Path) -> list[str]:
    return path.read_text("utf-8-sig", errors="replace").splitlines()


def progress() -> tuple[list[str], list[str]]:
    done: list[str] = []
    todo: list[str] = []
    with PROGRESS.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle, delimiter="\t"):
            (done if row["status"] == "draft" else todo).append(row["path"])
    return done, todo


def overlap(a: list[str], b: list[str]) -> tuple[float, int, int, int]:
    matcher = SequenceMatcher(None, a, b, autojunk=False)
    equal = sum(block.size for block in matcher.get_matching_blocks())
    return matcher.ratio(), equal, len(a) - equal, len(b) - equal


def main() -> None:
    done, todo = progress()
    done_hashes: dict[str, list[str]] = defaultdict(list)
    done_by_name: dict[str, list[str]] = defaultdict(list)
    done_lines: dict[str, list[str]] = {}
    for relative in done:
        path = SOURCE / relative
        done_hashes[digest(path)].append(relative)
        done_by_name[path.name].append(relative)
        done_lines[relative] = lines(path)

    rows: list[dict[str, str]] = []
    for relative in todo:
        path = SOURCE / relative
        source_hash = digest(path)
        exact = done_hashes.get(source_hash, [])
        candidates = exact or done_by_name.get(path.name, [])
        if not candidates:
            continue
        source_lines = lines(path)
        scored = []
        for candidate in candidates:
            ratio, equal, removed, added = overlap(source_lines, done_lines[candidate])
            scored.append((ratio, equal, removed, added, candidate))
        ratio, equal, removed, added, candidate = max(scored)
        rows.append(
            {
                "todo_path": relative,
                "source_sha256": source_hash,
                "candidate_path": candidate,
                "candidate_sha256": digest(SOURCE / candidate),
                "exact": "yes" if source_hash == digest(SOURCE / candidate) else "no",
                "similarity": f"{ratio:.6f}",
                "unchanged_lines": str(equal),
                "todo_only_lines": str(removed),
                "candidate_only_lines": str(added),
            }
        )

    rows.sort(key=lambda row: (row["exact"] != "yes", -float(row["similarity"]), row["todo_path"]))
    REPORT_TSV.parent.mkdir(parents=True, exist_ok=True)
    fieldnames = list(rows[0]) if rows else [
        "todo_path", "source_sha256", "candidate_path", "candidate_sha256",
        "exact", "similarity", "unchanged_lines", "todo_only_lines", "candidate_only_lines",
    ]
    with REPORT_TSV.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, delimiter="\t", fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)

    exact_count = sum(row["exact"] == "yes" for row in rows)
    near_count = sum(row["exact"] == "no" and float(row["similarity"]) >= 0.85 for row in rows)
    body = [
        "# 翻译复用候选",
        "",
        f"- 已完成英文源：{len(done)}",
        f"- 待处理英文源：{len(todo)}",
        f"- 完全相同、可直接复用：{exact_count}",
        f"- 相似度不低于 85%：{near_count}",
        "",
        "| 待处理页面 | 已验收候选 | 完全相同 | 相似度 | 未变化行 | 待处理独有行 |",
        "|---|---|---:|---:|---:|---:|",
    ]
    for row in rows:
        if row["exact"] == "yes" or float(row["similarity"]) >= 0.75:
            body.append(
                f"| `{row['todo_path']}` | `{row['candidate_path']}` | {row['exact']} | "
                f"{float(row['similarity']):.1%} | {row['unchanged_lines']} | {row['todo_only_lines']} |"
            )
    REPORT_MD.write_text("\n".join(body) + "\n", encoding="utf-8")
    print(REPORT_TSV)
    print(REPORT_MD)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Reuse a translation after an English unified diff has been reviewed."""

from __future__ import annotations

import argparse
import csv
import difflib
import hashlib
import shutil
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]  # repository root
META = ROOT / "translations" / "zh_CN"
SOURCE = ROOT
TRANSLATED = ROOT / "zh_CN"
PROGRESS = META / "PROGRESS.tsv"


def approved() -> set[str]:
    with PROGRESS.open(encoding="utf-8", newline="") as handle:
        return {row["path"] for row in csv.DictReader(handle, delimiter="\t") if row["status"] == "draft"}


def diff(candidate: str, target: str) -> str:
    old = (SOURCE / candidate).read_text("utf-8-sig", errors="replace").splitlines(keepends=True)
    new = (SOURCE / target).read_text("utf-8-sig", errors="replace").splitlines(keepends=True)
    return "".join(difflib.unified_diff(old, new, fromfile=candidate, tofile=target, n=3))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("candidate_path")
    parser.add_argument("target_path")
    parser.add_argument("--approved-diff-sha256")
    args = parser.parse_args()
    if args.candidate_path not in approved():
        raise SystemExit("candidate is not an approved draft")
    content = diff(args.candidate_path, args.target_path)
    checksum = hashlib.sha256(content.encode()).hexdigest()
    print(f"diff_sha256={checksum}")
    if not args.approved_diff_sha256:
        print("review with reuse_diff.py, then rerun with --approved-diff-sha256")
        return
    if checksum != args.approved_diff_sha256:
        raise SystemExit("English diff changed since review")
    shutil.copyfile(TRANSLATED / args.candidate_path, TRANSLATED / args.target_path)
    print(f"reused reviewed diff {args.candidate_path} -> {args.target_path}")


if __name__ == "__main__":
    main()

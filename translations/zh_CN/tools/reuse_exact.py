#!/usr/bin/env python3
"""Reuse an approved translation when two upstream files are byte-identical."""

from __future__ import annotations

import argparse
import csv
import difflib
import hashlib
import re
import shutil
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]  # repository root
META = ROOT / "translations" / "zh_CN"
SOURCE = ROOT
TRANSLATED = ROOT / "zh_CN"
PROGRESS = META / "PROGRESS.tsv"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def approved_paths() -> set[str]:
    with PROGRESS.open(encoding="utf-8", newline="") as handle:
        return {
            row["path"]
            for row in csv.DictReader(handle, delimiter="\t")
            if row["status"] == "draft"
        }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("candidate_path", help="approved translated page")
    parser.add_argument("target_path", help="todo page with identical upstream bytes")
    parser.add_argument(
        "--allow-adornment-only-diff",
        action="store_true",
        help="also allow differences consisting only of RST heading adornment lines",
    )
    args = parser.parse_args()

    if args.candidate_path not in approved_paths():
        raise SystemExit(f"candidate is not approved in PROGRESS.tsv: {args.candidate_path}")
    candidate_source = SOURCE / args.candidate_path
    target_source = SOURCE / args.target_path
    candidate_translation = TRANSLATED / args.candidate_path
    target_translation = TRANSLATED / args.target_path
    hashes_match = sha256(candidate_source) == sha256(target_source)
    if not hashes_match:
        if not args.allow_adornment_only_diff:
            raise SystemExit("upstream SHA-256 mismatch; use reuse_diff.py instead")
        candidate_lines = candidate_source.read_text("utf-8-sig").splitlines()
        target_lines = target_source.read_text("utf-8-sig").splitlines()
        changed: list[str] = []
        for line in difflib.ndiff(candidate_lines, target_lines):
            if line.startswith(("- ", "+ ")):
                changed.append(line[2:])
        adornment = re.compile(r"^[=~^#*+\-`:'\".]{3,}$")
        if not changed or any(not adornment.fullmatch(line) for line in changed):
            raise SystemExit("non-adornment English differences found; use reuse_diff.py")
    if not candidate_translation.is_file() or not target_translation.is_file():
        raise SystemExit("candidate or target translation path is missing")
    shutil.copyfile(candidate_translation, target_translation)
    print(f"reused {args.candidate_path} -> {args.target_path}")
    print(f"sha256={sha256(target_source)}")
    print(f"mode={'exact' if hashes_match else 'adornment-only-diff'}")


if __name__ == "__main__":
    main()

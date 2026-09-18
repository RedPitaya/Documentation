#!/usr/bin/env python3
"""Print the authoritative English diff between a todo page and reuse candidate."""

from __future__ import annotations

import argparse
import difflib
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]  # repository root
META = ROOT / "translations" / "zh_CN"
SOURCE = ROOT


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("todo_path")
    parser.add_argument("candidate_path")
    parser.add_argument("--context", type=int, default=3)
    args = parser.parse_args()
    todo = (SOURCE / args.todo_path).read_text("utf-8-sig", errors="replace").splitlines(keepends=True)
    candidate = (SOURCE / args.candidate_path).read_text("utf-8-sig", errors="replace").splitlines(keepends=True)
    print("".join(difflib.unified_diff(
        candidate,
        todo,
        fromfile=args.candidate_path,
        tofile=args.todo_path,
        n=args.context,
    )), end="")


if __name__ == "__main__":
    main()

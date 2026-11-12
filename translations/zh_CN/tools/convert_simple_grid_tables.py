#!/usr/bin/env python3
"""Convert simple, non-spanning RST grid tables to width-safe list-tables."""

from __future__ import annotations

import argparse
from pathlib import Path
import re


BORDER = re.compile(r"^\+(?:[-=]+\+)+$")


def convert(lines: list[str]) -> tuple[list[str], int]:
    output: list[str] = []
    converted = 0
    index = 0
    while index < len(lines):
        if not BORDER.match(lines[index]):
            output.append(lines[index])
            index += 1
            continue
        start = index
        end = index + 1
        while end < len(lines) and (BORDER.match(lines[end]) or lines[end].startswith("|")):
            end += 1
        block = lines[start:end]
        borders = [line for line in block if BORDER.match(line)]
        if len(borders) < 2:
            output.extend(block)
            index = end
            continue
        positions = [pos for pos, char in enumerate(block[0]) if char == "+"]
        column_count = len(positions) - 1
        fallback_split = column_count >= 2 and all(
            len(line.split("|")[1:-1]) == column_count
            for line in block if line.startswith("|")
        )
        if column_count < 2 or (
            any(len(line) <= positions[-1] for line in block if line.startswith("|"))
            and not fallback_split
        ):
            output.extend(block)
            index = end
            continue

        rows: list[list[str]] = []
        current = [[] for _ in range(column_count)]
        header_rows = 0
        for line in block[1:]:
            if line.startswith("|"):
                split_cells = line.split("|")[1:-1] if fallback_split else None
                for column in range(column_count):
                    piece = (
                        split_cells[column].strip()
                        if split_cells is not None
                        else line[positions[column] + 1 : positions[column + 1]].strip()
                    )
                    if piece.startswith("| "):
                        piece = piece[2:].strip()
                    if piece == "|":
                        piece = ""
                    if piece:
                        current[column].append(piece)
                continue
            if BORDER.match(line):
                if any(current):
                    rows.append([" |br| ".join(parts) for parts in current])
                    current = [[] for _ in range(column_count)]
                if "=" in line:
                    header_rows = len(rows)

        if not rows:
            output.extend(block)
            index = end
            continue
        widths = [positions[i + 1] - positions[i] - 1 for i in range(column_count)]
        output.extend([".. list-table::", "    :widths: " + " ".join(map(str, widths))])
        if header_rows:
            output.append(f"    :header-rows: {header_rows}")
        output.append("")
        for row in rows:
            output.append("    * - " + row[0])
            output.extend("      - " + cell for cell in row[1:])
        converted += 1
        index = end
    return output, converted


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("path", type=Path)
    args = parser.parse_args()
    original = args.path.read_text(encoding="utf-8").splitlines()
    updated, count = convert(original)
    if not count:
        raise SystemExit("no convertible tables found")
    args.path.write_text("\n".join(updated) + "\n", encoding="utf-8")
    print(f"converted {count} table(s): {args.path}")


if __name__ == "__main__":
    main()

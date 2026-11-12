#!/usr/bin/env python3
"""List Chinese pages whose English source changed since the revision they were translated from.

For every row in PROGRESS.tsv this compares the recorded `upstream_revision` with the current
HEAD of the English tree (the repository root) using `git diff`, and reports the pages that
need a sync pass. With --diff it also writes each page's unified diff to reports/sync/<page>.diff,
which is exactly the input prompts/sync_upstream.md asks for.

Usage:
    python3 sync_status.py [--diff] [--ref <git ref>]

--ref   compare against this ref instead of HEAD (e.g. upstream/master before merging)
"""
import csv, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
META = ROOT / "translations" / "zh_CN"
PROGRESS = META / "PROGRESS.tsv"
OUT = META / "reports" / "sync"

def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, text=True, capture_output=True)

def main():
    args = sys.argv[1:]
    want_diff = "--diff" in args
    ref = args[args.index("--ref") + 1] if "--ref" in args else "HEAD"
    rows = list(csv.DictReader(PROGRESS.open(encoding="utf-8"), delimiter="\t"))
    stale, missing, removed = [], [], []
    for row in rows:
        page, rev = row["path"], row["upstream_revision"]
        if not rev:
            missing.append(page); continue
        if not (ROOT / page).exists():
            removed.append(page); continue
        r = git("diff", "--quiet", rev, ref, "--", page)
        if r.returncode == 1:
            stat = git("diff", "--numstat", rev, ref, "--", page).stdout.split()
            stale.append((page, rev[:7], stat[0] if stat else "?", stat[1] if len(stat) > 1 else "?"))
            if want_diff:
                OUT.mkdir(parents=True, exist_ok=True)
                (OUT / (page.replace("/", "__") + ".diff")).write_text(
                    git("diff", rev, ref, "--", page).stdout, encoding="utf-8")
        elif r.returncode > 1:
            print("git error for", page, r.stderr.strip(), file=sys.stderr)
    # English pages that exist upstream but have no row at all
    known = {r["path"] for r in rows}
    new_pages = [p for p in git("ls-files", "*.rst").stdout.split("\n")
                 if p and not p.startswith(("zh_CN/", "translations/")) and p not in known]

    print(f"compared against {ref}")
    print(f"\n{len(stale)} page(s) changed upstream since they were translated:")
    for page, rev, add, dele in stale:
        print(f"  {page}  (from {rev}, +{add}/-{dele})")
    if removed:
        print(f"\n{len(removed)} page(s) removed upstream (delete the zh_CN copy and the PROGRESS row):")
        for p in removed: print("  " + p)
    if new_pages:
        print(f"\n{len(new_pages)} new English page(s) without a PROGRESS row:")
        for p in new_pages: print("  " + p)
    if missing:
        print(f"\n{len(missing)} row(s) have no upstream_revision recorded:")
        for p in missing: print("  " + p)
    if want_diff and stale:
        print(f"\ndiffs written to {OUT}")

if __name__ == "__main__":
    main()

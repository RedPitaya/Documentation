#!/usr/bin/env python3
"""Build a replace_labels.py plan from OCR output and a label glossary.

Usage:
    make_plan.py ocr_results.json glossary.tsv out_dir plan.json [--only list.txt]

ocr_results.json  output of the `ocr` tool (one entry per image, boxes in pixels)
glossary.tsv      two or three tab-separated columns: <english label> <chinese label> [image path filter]
                  The English column is matched case-insensitively against each OCR box after
                  trimming punctuation. A third column restricts the rule to files whose path
                  contains that substring (use it when the same word needs different translations).
out_dir           where translated images are written (same relative path as the source)
plan.json         written plan, feed it to replace_labels.py
--only list.txt   optional newline-separated list of image paths to include (others are skipped)

Boxes with no glossary match are left untouched, so a partly translated glossary produces a
partly translated image; check the "unmatched" report printed at the end and extend the glossary.
"""
import csv, json, os, re, sys

def norm(t):
    return re.sub(r'[\s:.,;()\[\]]+', ' ', t).strip().lower()

def merge_lines(boxes):
    """Merge vertically stacked OCR lines into one block so multi-line labels match a
    single glossary entry ("Direct USB" + "connection" -> "Direct USB connection").
    Two boxes merge when they overlap horizontally and the vertical gap is less than
    0.8x the line height. The merged text joins the lines with a space."""
    boxes = sorted(boxes, key=lambda b: (b['y'], b['x']))
    merged = []
    for b in boxes:
        b = dict(b)
        for m in merged:
            h = max(m['h'], b['h'])
            overlap_x = min(m['x'] + m['w'], b['x'] + b['w']) - max(m['x'], b['x'])
            gap_y = b['y'] - (m['y'] + m['h'])
            if overlap_x > 0.3 * min(m['w'], b['w']) and -0.2 * h < gap_y < 0.8 * h and abs(m['h'] - b['h']) < 0.6 * h:
                x0 = min(m['x'], b['x']); x1 = max(m['x'] + m['w'], b['x'] + b['w'])
                y1 = b['y'] + b['h']
                m.update(x=x0, w=x1 - x0, h=y1 - m['y'], text=m['text'] + ' ' + b['text'], lines=m.get('lines', 1) + 1)
                b = None; break
        if b is not None:
            merged.append(b)
    return merged

def main():
    args = sys.argv[1:]
    only = None
    if '--only' in args:
        i = args.index('--only'); only = set(l.strip() for l in open(args[i+1]) if l.strip()); del args[i:i+2]
    ocr_path, gloss_path, out_dir, plan_path = args
    rules = []
    with open(gloss_path, encoding='utf-8') as f:
        for row in csv.reader(f, delimiter='\t'):
            if len(row) < 2: continue   # comment lines have no tab; a '#' label (code comment) is valid
            rules.append((norm(row[0]), row[1].strip(), row[2].strip() if len(row) > 2 else ''))
    plan, unmatched = [], {}
    for entry in json.load(open(ocr_path)):
        src = entry['file']
        if only is not None and not any(src.endswith(o) for o in only): continue
        labels = []
        # try merged multi-line blocks first, then fall back to single lines
        merged = [m for m in merge_lines(entry['boxes']) if m.get('lines', 1) > 1]
        singles = entry['boxes']
        taken = []  # rects already replaced by a matched multi-line block

        def lookup(text):
            key = norm(text)
            for en, zh, flt in rules:
                if en == key and (not flt or flt in src): return zh
            return None

        for b in merged:
            hit = lookup(b['text'])
            if hit is not None:
                labels.append({'x': b['x'], 'y': b['y'], 'w': b['w'], 'h': b['h'], 'text': hit, 'lines': b['lines']})
                taken.append((b['x'], b['y'], b['x'] + b['w'], b['y'] + b['h']))
        for b in singles:
            cx, cy = b['x'] + b['w'] / 2, b['y'] + b['h'] / 2
            if any(x0 <= cx <= x1 and y0 <= cy <= y1 for x0, y0, x1, y1 in taken):
                continue  # covered by a merged block that already matched
            hit = lookup(b['text'])
            if hit is None:
                if only is not None: unmatched.setdefault(src, []).append(b['text'])
                continue
            lab = {'x': b['x'], 'y': b['y'], 'w': b['w'], 'h': b['h'], 'text': hit}
            if b['text'].lstrip().startswith(('#', '-', '+', '*')):
                lab['align'] = 'left'   # code comments / list items keep their left edge
            labels.append(lab)
        if labels:
            rel = src.split('/zh_CN/', 1)[1] if '/zh_CN/' in src else os.path.basename(src)
            dst = os.path.join(out_dir, rel); os.makedirs(os.path.dirname(dst), exist_ok=True)
            plan.append({'src': src, 'dst': dst, 'labels': labels})
    json.dump(plan, open(plan_path, 'w'), ensure_ascii=False, indent=1)
    print(f'{len(plan)} images planned -> {plan_path}')
    for src, texts in unmatched.items():
        print('UNMATCHED', src.split('/zh_CN/')[-1], '|', ' | '.join(texts))

if __name__ == '__main__':
    main()

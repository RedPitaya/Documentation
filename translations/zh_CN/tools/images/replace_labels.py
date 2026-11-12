#!/usr/bin/env python3
"""In-place label replacement for documentation images.

Usage: replace_labels.py plan.json
plan.json: [{"src": path, "dst": path, "labels": [{"x","y","w","h","text"}]}]
Each label box (pixel coords, top-left origin) is filled with the sampled
background colour and the Chinese text is drawn centred in the box using the
dominant text colour of the original region.
"""
import json, sys, statistics
from PIL import Image, ImageDraw, ImageFont

FONTS = ["/System/Library/Fonts/STHeiti Medium.ttc",
         "/System/Library/Fonts/Hiragino Sans GB.ttc"]

def font_at(size):
    for f in FONTS:
        try:
            return ImageFont.truetype(f, size)
        except Exception:
            pass
    raise SystemExit("no CJK font")

def sample_bg(im, x0, y0, x1, y1):
    """Most common colour inside the box (quantised to 8 levels per channel).
    Text pixels are a minority, so the mode is the surface the text sits on,
    which also works for labels printed on arrows or coloured blocks."""
    from collections import Counter
    px = im.load(); cnt = Counter(); acc = {}
    for x in range(x0, x1):
        for y in range(y0, y1):
            c = px[x, y][:3]; q = (c[0] >> 5, c[1] >> 5, c[2] >> 5)
            cnt[q] += 1; acc.setdefault(q, []).append(c)
    if not cnt: return (255, 255, 255)
    q = cnt.most_common(1)[0][0]; pts = acc[q]
    exact, n = Counter(pts).most_common(1)[0]
    if n >= 0.15 * len(pts):      # flat colour surface: use the exact dominant colour
        return tuple(exact)
    return tuple(int(statistics.median(c[i] for c in pts)) for i in range(3))

def sample_fg(im, x0, y0, x1, y1, bg):
    """Colour in the box farthest from the background (the text colour)."""
    px = im.load(); best = bg; bestd = -1
    for x in range(x0, x1, 2):
        for y in range(y0, y1, 2):
            c = px[x, y][:3]
            d = sum((c[i] - bg[i]) ** 2 for i in range(3))
            if d > bestd: bestd, best = d, c
    return best if bestd > 3 * 40 ** 2 else (0, 0, 0)

def fit_font(draw, text, box_w, box_h, lines=1):
    # a block that held N English lines should get a font about one line tall
    size = max(8, int(box_h / max(1, lines) * 0.85))
    while size > 8:
        f = font_at(size)
        b = draw.textbbox((0, 0), text, font=f)
        if b[2] - b[0] <= box_w * 1.15 and b[3] - b[1] <= box_h * 1.05:
            return f, b
        size -= 1
    f = font_at(size); return f, draw.textbbox((0, 0), text, font=f)

def process(item):
    im = Image.open(item["src"]).convert("RGBA")
    d = ImageDraw.Draw(im)
    pad = 2
    boxes = []
    for lb in item["labels"]:
        x0 = int(lb["x"]) - pad; y0 = int(lb["y"]) - pad
        x1 = int(lb["x"] + lb["w"]) + pad; y1 = int(lb["y"] + lb["h"]) + pad
        x0, y0 = max(0, x0), max(0, y0); x1, y1 = min(im.width, x1), min(im.height, y1)
        bg = sample_bg(im, x0, y0, x1, y1)
        fg = lb.get("color") or sample_fg(im, x0, y0, x1, y1, bg)
        boxes.append((lb, x0, y0, x1, y1, bg, fg))
    # pass 1: erase every label first, so a later box never wipes an earlier text
    for lb, x0, y0, x1, y1, bg, fg in boxes:
        d.rectangle([x0, y0, x1, y1], fill=bg + (255,))
    # pass 2: draw the translations
    for lb, x0, y0, x1, y1, bg, fg in boxes:
        bw, bh = x1 - x0, y1 - y0
        # a tall narrow box held vertical (rotated) text: render rotated 90 degrees
        vertical = lb.get("rotate") or (bh > 1.8 * bw and len(lb["text"]) > 1)
        if vertical:
            f, b = fit_font(d, lb["text"], bh, bw, lb.get("lines", 1))
            tw, th = b[2] - b[0], b[3] - b[1]
            tile = Image.new("RGBA", (tw + 4, th + 4), bg + (0,))
            ImageDraw.Draw(tile).text((2 - b[0], 2 - b[1]), lb["text"], font=f, fill=tuple(fg) + (255,))
            tile = tile.rotate(90 if lb.get("rotate", "ccw") != "cw" else -90, expand=True)
            im.alpha_composite(tile, ((x0 + x1) // 2 - tile.width // 2, (y0 + y1) // 2 - tile.height // 2))
            d = ImageDraw.Draw(im)
            continue
        f, b = fit_font(d, lb["text"], bw, bh, lb.get("lines", 1))
        tw, th = b[2] - b[0], b[3] - b[1]
        cx, cy = (x0 + x1) // 2, (y0 + y1) // 2
        anchor = lb.get("align", "center")
        tx = x0 - b[0] if anchor == "left" else cx - tw // 2 - b[0]
        d.text((tx, cy - th // 2 - b[1]), lb["text"], font=f, fill=tuple(fg) + (255,))
    out = im.convert("RGB") if item["dst"].lower().endswith((".jpg", ".jpeg")) else im
    out.save(item["dst"])
    return item["dst"]

if __name__ == "__main__":
    plan = json.load(open(sys.argv[1]))
    for it in plan:
        print("wrote", process(it))

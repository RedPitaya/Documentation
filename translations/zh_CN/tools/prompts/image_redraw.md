# 提示词：用生图模型重绘带文字的图片（兜底方案）

只在 `images/replace_labels.py` 原位替换效果不可接受时使用（例如文字压在渐变或照片上、文字是弧形、标签太密）。
生图会改变原图像素，分辨率通常下降，产品照片和丝印可能失真，所以它是兜底而不是首选。

## 用 Codex CLI（ChatGPT 订阅额度）

```bash
printf '%s' "$(cat prompt.txt)" | codex exec --skip-git-repo-check -s workspace-write -C ./out -i ./original.png
```

`-i` 是可变长参数，提示词必须走标准输入，否则会被当成图片路径吞掉。

## prompt.txt 模板

```
You have an image generation tool. Recreate the attached technical diagram with the same layout,
the same objects in the same positions, white background and the same aspect ratio (W:H = <填写>).
The ONLY change: replace every English label with the Simplified Chinese label from this list,
keeping each label at the same position, size and colour, in a clean sans-serif font:

- "Direct USB connection" -> "直接 USB 连接"
- "<英文>" -> "<中文>"

Do not add, remove or restyle anything else. Use the image generation tool, then copy the generated
PNG into the current working directory as <文件名>_zh.png and print its absolute path.
```

## 验收标准

- 布局、对象、颜色与原图一致，无多余黑边或水印
- 中文标签位置、大小与原英文一致，无错字
- 分辨率不低于原图的 80%，否则用 `-c` 指定更高输出尺寸或改回原位替换
- 产品照片上的丝印、接口标识没有变成乱码；如果变了，这张图不要用生图，改为只替换文字

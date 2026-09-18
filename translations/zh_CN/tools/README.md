# 中文翻译工具与流程

这个目录是 Red Pitaya 文档简体中文版的“工作台”：说明汉化是怎么做的，并提供脚本和提示词，
让任何人（或任何 AI 助手）都能在上游英文更新后，用同一套方法把中文版跟上。

## 1. 仓库布局

```
<repo>/                      上游英文文档（原样，不改）
<repo>/zh_CN/                中文文档树，目录结构、文件名、图片路径与英文一一对应
<repo>/zh_CN/.readthedocs.yaml   Read the Docs 用的独立配置（路径相对仓库根目录写成 zh_CN/...）
<repo>/translations/zh_CN/   翻译的“账本”和工具，不参与文档构建
    PROGRESS.tsv             每页状态：路径、status、优先级、翻译所依据的上游 commit、备注
    TERMINOLOGY.tsv          术语表，翻译时必须遵守
    REVISION.md              当前锁定的上游版本
    CHANGELOG.md             每批次改了什么
    reports/                 脚本生成的检查报告
    tools/                   本目录
```

## 2. 汉化原理

**文本**：每个英文 `.rst` 在 `zh_CN/` 下有一个同名中文文件。只翻译自然语言，所有 RST 指令、
label、`:ref:` 目标、替换符、代码块、路径、数值、寄存器地址、图片引用一律保持原样，
所以中文页和英文页在 Sphinx 眼里结构完全一致，交叉引用照常工作，也方便用 diff 核对。

**图片**：三档处理，按顺序尝试，能用前一档就不用后一档。

1. **不动**：软件界面截图、终端截图、板卡照片上的丝印。界面本身是英文，翻译截图反而误导读者。
2. **原位替换文字**（首选）：示意图、流程图、标注图里的英文标签，用 `images/` 下的工具
   识别文字位置，把标签区域用背景色盖掉，再用系统中文字体写上译文。像素级保留原图的其他部分，
   分辨率不变，可批量处理，不消耗任何模型额度。
3. **生图模型重绘**（兜底）：只有当文字压在渐变或照片上、标签是弧形或密集到无法逐个替换时才用。
   见 `prompts/image_redraw.md`。生图会降低分辨率、改变细节，用之前先看效果。

**版本对齐**：`PROGRESS.tsv` 记录每一页是根据哪个上游 commit 翻译的。上游更新后，
只需要比对该 commit 到最新 master 的 diff，就知道哪些中文页需要动、动哪几段。

## 3. 首次翻译一页

1. 从 `PROGRESS.tsv` 找一个 `todo` 的页面。
2. 把 `prompts/translate_page.md` 的内容加上英文原文交给 AI，或者自己翻译。
3. 存到 `zh_CN/` 对应路径。
4. 运行检查（见第 5 节），全部通过后把 `PROGRESS.tsv` 里该行改成 `draft`，
   `upstream_revision` 填当前上游 commit。
5. 人工审阅后改成 `reviewed` 或 `done`。

历史版本页面（例如各 OS 版本的寄存器表）大量重复，用 `reuse_analysis.py` 找到已完成的相似页，
按 `../REUSE_WORKFLOW.md` 复用，不要从头翻。

## 4. 上游更新后同步

```bash
git fetch upstream                       # upstream = https://github.com/RedPitaya/Documentation.git
git merge upstream/master                # zh_CN/ 与上游不冲突，合并只带来英文侧的改动
python3 translations/zh_CN/tools/sync_status.py   # 列出自各页登记的 commit 以来英文改过的页面，并输出 diff
```

对每个列出的页面：把 diff、现有中文页和术语表一起交给 AI，用 `prompts/sync_upstream.md` 的提示词，
只改 diff 涉及的段落。删除的图片同步从 `zh_CN/.../img/` 删掉；新增的图片先复制英文版，
再按第 6 节决定是否汉化。完成后更新 `PROGRESS.tsv` 的 `upstream_revision`，在 `CHANGELOG.md` 记一笔。

## 5. 检查与构建

```bash
python3 -m pip install -r zh_CN/requirements.txt -r zh_CN/.readthedocs-requirements.txt
bash translations/zh_CN/tools/check_all.sh
```

`check_all.sh` 依次运行：

- `check_translation.py`：找出仍是英文或漏译的页面，写到 `reports/translation-check.md`
- `check_structure.py`：比对中英文页面的 label、ref、代码块、十六进制常量等结构是否一致
- 严格模式 Sphinx 构建（`-W`，任何警告都算失败）

其他脚本：

| 脚本 | 用途 |
| --- | --- |
| `reuse_analysis.py` | 按英文文件哈希和行相似度找可复用的已翻译页 |
| `reuse_diff.py` | 打印两份英文页面的 unified diff，作为复用时的翻译依据 |
| `reuse_exact.py` / `reuse_reviewed_diff.py` | 把已审阅的译文机械复用到相同/近似页面 |
| `convert_simple_grid_tables.py` | 把简单 grid 表转成 list-table，避免中文宽度撑坏表格 |
| `linkcheck_bounded.py` | 带超时的外链检查 |
| `milestones.py` | 从 `PROGRESS.tsv` 生成进度里程碑 |

## 6. 图片汉化

工具在 `images/`：

| 文件 | 用途 |
| --- | --- |
| `ocr.swift` | macOS Vision OCR，输出每张图里每行文字的内容、置信度和像素坐标（JSON） |
| `make_plan.py` | 用 OCR 结果 + `glossary.tsv` 生成替换计划；自动把上下相邻的多行标签合并成一个块 |
| `replace_labels.py` | 执行计划：取框内最常见颜色做背景盖住英文，按原文字颜色写入中文，字号按框高自适应 |
| `glossary.tsv` | 图片标签词表，第三列可按路径限定某条翻译只用于某些图 |

流程：

```bash
cd translations/zh_CN/tools/images
swiftc -O -o ocr ocr.swift                                  # 只需一次，需要 Xcode 命令行工具
./ocr $(list of images) > ocr_results.json                  # 图片路径用绝对路径
python3 make_plan.py ocr_results.json glossary.tsv /tmp/preview plan.json --only list.txt
python3 replace_labels.py plan.json                          # 需要 Pillow
```

`make_plan.py` 会打印每张图里没匹配到词表的英文行（`UNMATCHED`），把需要翻译的补进 `glossary.tsv`
再跑一次。先输出到预览目录逐张过目，满意后再复制回 `zh_CN/.../img/` 覆盖英文图。

选图原则：只处理示意图、流程图、带标注线的照片。软件截图不翻。板卡丝印（IN1、OUT2、E1、JTAG）不翻。
产品名、型号、SSID、命令、函数名保留英文。

经验与限制：

- 窄高的框会自动按竖排（旋转 90°）写入；文字压在照片上的，背景取样可能不准，这种图逐张过目。
- 低分辨率图（宽度 < 700 px）OCR 容易识别错，先用 Pillow 放大 3 倍再识别，坐标除以 3 写回。
- `ocr.swift` 用 ImageIO 读取原始像素，不应用 EXIF/PNG 旋转元数据，坐标系与 Pillow 一致；若改用 NSImage 会得到旋转后的坐标。
- 等宽字体排版的 ASCII 结构图（如 FPGA 模块框图）不翻译，换成中文会破坏对齐，按“代码不翻”处理。
- 词表键会做归一化：小写、去掉 : . , ; ( ) [ ]；以 `#`、`-`、`+`、`*` 开头的原文按左对齐写入。

## 7. 提示词

`prompts/` 下三份，可直接粘给 Claude、GPT、Codex 等：

- `translate_page.md`：首次翻译一页
- `sync_upstream.md`：上游更新后按 diff 增量同步
- `image_redraw.md`：生图模型重绘带文字图片的兜底方案

## 8. 发布

中文版托管在 Read the Docs：项目 `redpitaya-zh-cn`，配置文件路径设为 `zh_CN/.readthedocs.yaml`，
默认分支 `codex/zh-cn-translation`。仓库已配置 GitHub webhook（仓库 Settings → Webhooks，
指向 Read the Docs 的 `/api/v2/webhook/redpitaya-zh-cn/...`），推送到该分支会自动触发构建；
若构建没有自动开始，到 Read the Docs 项目的“集成”页查看投递记录或手动 Rebuild。

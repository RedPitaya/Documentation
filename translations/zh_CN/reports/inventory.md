# 官方源范围盘点

- RST 页面：378
- include 文件：52
- 图片资源：797
- 全部文件（不含 `.git`）：1276
- RST 行数：126,191
- include/literalinclude 指令：259
- 显式 label：451
- `:ref:`/`:doc:` 引用：1352

## RST 页面分布

| 顶层目录 | 页面数 |
|---|---:|
| `(root)` | 3 |
| `appsFeatures` | 184 |
| `customization` | 1 |
| `developerGuide` | 169 |
| `quickStart` | 21 |

## 结构与治理发现

- Sphinx 根文档为 `index.rst`，配置为 `conf.py`。
- 主体板块为 Quick Start、Applications and Features、Developer’s guide、Customization。
- 仓库中未发现 LICENSE/COPYING、CONTRIBUTING 或贡献模板；提交前需向上游确认许可与本地化策略。

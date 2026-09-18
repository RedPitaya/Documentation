# Red Pitaya 官方文档中文翻译

本目录记录 `RedPitaya/Documentation` 简体中文 RST/Sphinx 文档的翻译进度、术语和验证结果。正式中文文档源位于仓库根目录的 `zh_CN/`。

## 目录

- 仓库根目录：官方英文源，固定基线见 `REVISION.md`。
- `../../zh_CN/`：保留官方目录结构的中文贡献工作树；图片、include、label、ref、命令与路径保持原样。
- `reports/`：翻译覆盖、结构与构建检查报告。
- `PROGRESS.tsv`：逐页状态清单；状态为 `todo`、`draft`、`reviewed` 或 `done`。
- `TERMINOLOGY.tsv`：统一术语表。
- `CHANGELOG.md`：中文工程的分批变更记录。

## 快速验证

```bash
python3 -m sphinx -W --keep-going -b html zh_CN build/html
python3 -m sphinx -W --keep-going -b linkcheck zh_CN build/linkcheck
```

依赖版本与官方一致，见仓库根目录的 `requirements.txt`。更新翻译前应先核对 Read the Docs `latest` 构建 revision。

## 翻译约定

完整翻译标题、正文、图题、表格可见文本和 admonition 内容。不翻译命令、代码、路径、变量、Sphinx label/ref 目标、URL 与下载文件名。产品名、接口名及 API 标识按术语表处理。每批至少运行静态检查和 HTML 构建；联网条件允许时再运行 `linkcheck`。

## 上游许可状态

截至锁定 revision，仓库根目录未包含 `LICENSE`、`COPYING`、`CONTRIBUTING` 或贡献模板。正式提交前必须向 Red Pitaya 确认文档许可与中文本地化接收方式；该事项记录为上游阻塞项，但不阻碍本地翻译和技术验证。

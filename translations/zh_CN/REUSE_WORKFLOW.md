# 中文翻译复用工作流

历史版本或重复页面不再逐页从头重译。

1. 运行 `python3 scripts/reuse_analysis.py`，按上游英文文件的 SHA-256 和行级相似度寻找已验收候选。
2. `exact=yes` 时，复用候选中文稿，仅调整目标文件必须不同的 label、ref 或 toctree 路径；随后执行结构检查。
3. 非完全相同时，运行：

   ```bash
   python3 scripts/reuse_diff.py <待处理英文路径> <已验收候选英文路径>
   ```

   以 unified diff 为权威，只翻译新增或变化的英文块；删除候选版本独有块。
   审阅完成后可用 `reuse_reviewed_diff.py` 记录该 diff 的 SHA-256；只有传入相同的
   `--approved-diff-sha256` 时才会机械复用候选中文稿，之后必须逐项翻译差异块。
4. 禁止根据较新版本记忆补写寄存器。地址、十六进制常量、权限、位域和公式必须以目标英文源为准。
5. 页面只有在翻译检查、结构检查（含 hex-token）、`git diff --check` 和 strict Sphinx 构建全部通过后才能登记为 `draft`。

Hardware、Software、Applications 等非重复正文优先交给翻译 Agent；历史寄存器页面只在存在明确复用计划时处理。

#!/usr/bin/env bash
# 一键运行全部静态检查和严格构建。
# 用法：在仓库任意位置执行  bash translations/zh_CN/tools/check_all.sh
# 需要先安装依赖：python3 -m pip install -r zh_CN/requirements.txt -r zh_CN/.readthedocs-requirements.txt
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
TOOLS="$ROOT/translations/zh_CN/tools"
PY="${PYTHON:-python3}"
cd "$ROOT"
"$PY" "$TOOLS/check_translation.py"
"$PY" "$TOOLS/check_structure.py"
"$PY" -m sphinx -T -W --keep-going -b dummy -D language=zh_CN zh_CN translations/zh_CN/build/dummy
echo "all checks passed"

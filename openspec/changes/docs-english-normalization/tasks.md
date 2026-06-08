# Tasks

## 1. 扫描 Docs 文档语言状态

- 目标：定位 `Docs/` 下含中文或非 ASCII 残留的文档。
- 影响范围：`Docs/**/*.md`。
- 实施思路：使用 PowerShell 与正则统计 CJK 汉字、非 ASCII 字符数量。
- 验证方法：输出每个文档的 `Han` 与 `NonAscii` 计数。

## 2. 翻译中文架构报告

- 目标：将 `Docs/ArchitectureOptimizationReport.md` 改为英文。
- 影响范围：`Docs/ArchitectureOptimizationReport.md`。
- 实施思路：保持原章节、表格、证据、建议路径、验证方法，翻译正文与标题。
- 验证方法：扫描该文件，确认 CJK 汉字计数为 0。

## 3. 清理 Docs 非 ASCII 标点

- 目标：清理 `Docs/` 中无必要的非 ASCII 标点。
- 影响范围：`Docs/RelatedKnowledge/QStyle.md`。
- 实施思路：将全角 URL 分隔标点替换为 ASCII `:`。
- 验证方法：扫描该文件，确认非 ASCII 计数为 0。

## 4. 执行整体文档验证

- 目标：确认 `Docs/` 下文档已统一为英文。
- 影响范围：`Docs/**/*.md`。
- 实施思路：重新统计 CJK 与非 ASCII 字符。
- 验证方法：`Docs/` 下 Markdown 文档 CJK 计数总和为 0；非 ASCII 残留为 0。

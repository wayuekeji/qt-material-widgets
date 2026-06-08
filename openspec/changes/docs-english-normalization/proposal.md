# Docs English Normalization

## 动机

`Docs/` 当前同时存在英文文档与中文架构报告，文档语言不一致，降低外部消费者、CI 文档检查与长期维护的一致性。

## 目标边界

- 将 `Docs/` 下 Markdown 文档统一为英文。
- 保留现有文档结构、事实、技术判断与路径引用。
- 清理 `Docs/` 文档中的非 ASCII 标点残留。
- 不修改源码、构建系统、README、OpenSpec 既有变更。

## 非目标

- 不重写架构结论。
- 不补齐缺失 API 文档。
- 不归档既有 OpenSpec change。
- 不引入文档生成器或新的 lint 工具。

## 方案设计

1. 扫描 `Docs/` 下文档文件，定位中文或非 ASCII 内容。
2. 将中文架构报告翻译为英文，保持章节编号与证据链不变。
3. 将零散非 ASCII 标点替换为 ASCII 形式。
4. 使用正则验证 `Docs/` 文档中不再存在 CJK 字符。

## Decisions

- D1: 本次只治理 `Docs/`，不要求 `openspec/` 同步英文化，因为 OpenSpec 是项目事实源，当前用户需求限定为 `Docs/`。
- D2: 翻译采用语义等价策略，保留原始优先级、建议路径与验证方法。
- D3: 对已经是 ASCII-only 的文档不做格式化改写，避免无关 diff。

## 风险清单

- 非阻断风险：翻译可能引入术语差异。缓解方式：保留 `Interface`、`Implementation`、`Module`、`Resource Pack` 等既有架构术语。
- 未检测到阻断级风险。

## ADDED Requirements

### Requirement: Docs 文档语言一致性

`Docs/` 下的 Markdown 文档 SHALL 使用英文作为正文语言。

#### Scenario: Docs 文档不含中文正文

- **WHEN** 维护者扫描 `Docs/` 下 Markdown 文档
- **THEN** 文档内容 MUST NOT 包含 CJK 汉字正文
- **AND** 既有路径、命令、API 名称与技术术语 MUST 保持可追溯

#### Scenario: 已有英文文档保持稳定

- **WHEN** 某个 `Docs/` 文档已经是英文或 ASCII-only
- **THEN** 本次变更 MUST NOT 对其进行无关重排、重写或格式化

### Requirement: Docs 非 ASCII 残留治理

`Docs/` 下 Markdown 文档 MUST 避免无必要的非 ASCII 标点或字符。

#### Scenario: 文档存在非 ASCII 标点

- **WHEN** 非 ASCII 字符只用于标点且存在 ASCII 等价形式
- **THEN** 该字符 MUST 被替换为 ASCII 等价形式

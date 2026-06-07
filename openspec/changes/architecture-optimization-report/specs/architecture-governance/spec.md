# Delta Spec

## ADDED Requirements

### Requirement: 项目必须保存优化分析报告

本次变更 MUST 在仓库文档目录中保存一份项目优化分析报告，报告内容 MUST 来自 `openspec/project.md`、现有 OpenSpec 变更与项目代码。

#### Scenario: 报告文件存在

- GIVEN 本次分析完成
- WHEN 检查仓库文档目录
- THEN `Docs/ArchitectureOptimizationReport.md` MUST 存在
- AND 该文件 MUST 记录当前项目可优化方向

#### Scenario: 报告引用事实来源

- GIVEN 报告列出一个优化点
- WHEN 审查该优化点
- THEN 该优化点 SHALL 指向相关文件、目录或规范事实
- AND 该优化点 MUST NOT 依赖未验证的外部假设

### Requirement: 优化点必须可执行

报告中的每个主要优化点 MUST 包含问题、证据、建议路径、优先级与验证方法。

#### Scenario: 优化点可拆分为后续任务

- GIVEN 一个报告中的主要优化点
- WHEN 后续需要进入实现阶段
- THEN 该优化点 SHALL 能拆分为独立 OpenSpec 变更或任务
- AND 其验证方法 SHALL 能用于判断实现是否达成目标

### Requirement: 分析范围必须覆盖核心工程面

报告 MUST 覆盖构建分发、公共接口、实现分层、示例层、测试 CI、文档治理六类工程面。

#### Scenario: 审查报告覆盖范围

- GIVEN 报告已经生成
- WHEN 审查章节结构
- THEN 报告 MUST 包含构建分发分析
- AND 报告 MUST 包含公共接口分析
- AND 报告 MUST 包含实现分层分析
- AND 报告 MUST 包含示例层分析
- AND 报告 MUST 包含测试与 CI 分析
- AND 报告 MUST 包含文档治理分析

## MODIFIED Requirements

### Requirement: OpenSpec 变更必须先于文档交付

文档型工程分析也 MUST 进入 OpenSpec 变更目录，以便后续归档与追踪。

#### Scenario: 文档型需求进入实施

- GIVEN 用户提出项目分析并保存文档的需求
- WHEN 未发现阻断级风险
- THEN 系统 SHALL 先创建 proposal、Delta Spec 与 tasks
- AND 系统 SHALL 自动进入报告生成阶段

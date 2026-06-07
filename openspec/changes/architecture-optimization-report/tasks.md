# 任务清单

## Task 1：扫描构建与分发模型

### 目标

识别 CMake、qmake、安装导出、包配置和示例消费方式中的优化点。

### 影响范围

- `CMakeLists.txt`
- `components/CMakeLists.txt`
- `examples/CMakeLists.txt`
- `cmake/QtMaterialWidgetsConfig.cmake.in`
- `qt-material-widgets.pro`
- `components/components.pro`

### 实施思路

静态审查主构建入口、库 target、导出 target、安装规则、qmake 维护状态与 README 接入说明之间的一致性。

### 验证方法

确认报告包含构建与分发章节，并为每个主要问题记录文件证据与后续验证命令。

## Task 2：扫描公共接口与实现泄漏

### 目标

识别安装头、公共 include 结构、私有头依赖、实验态接口暴露和命名债务。

### 影响范围

- `include/qmetarial/**`
- `components/*_p.h`
- `components/*_internal.*`
- `components/materiallib/**`

### 实施思路

统计公共头与私有头，检查公共头中的 include 关系、导出宏、未实现或未安装接口差异。

### 验证方法

确认报告包含公共接口章节，并列出可由脚本或编译验证的检查方式。

## Task 3：扫描实现层、资源层与示例层

### 目标

识别 Core、Widgets、Examples 的职责分布、资源依赖和示例重复代码中的优化点。

### 影响范围

- `components/materiallib/**`
- `components/resources.qrc`
- `examples/**`
- `examples/examples.qrc`

### 实施思路

审查核心基础能力、具体控件、资源注册、示例设置编辑器和运行时复制逻辑，评估模块深度、局部性与调用方杠杆。

### 验证方法

确认报告包含实现分层、资源和示例章节，并记录后续可回归验证方式。

## Task 4：扫描测试、CI 与文档治理

### 目标

识别自动化测试、持续集成、API 文档、README 与 OpenSpec 治理缺口。

### 影响范围

- `Docs/**`
- `README.md`
- `.github/**`
- `openspec/**`

### 实施思路

检查测试目录、CI 工作流、文档完整度、现有 OpenSpec 变更和缺失的 ADR/CONTEXT。

### 验证方法

确认报告包含测试、CI、文档治理章节，并给出优先级路线图。

## Task 5：保存优化分析报告并验证

### 目标

将分析结果保存到仓库文档，并确认与 Delta Spec 一致。

### 影响范围

- `Docs/ArchitectureOptimizationReport.md`

### 实施思路

生成结构化 Markdown 报告，包含摘要、证据、优化项、优先级路线图与后续 OpenSpec 拆分建议。

### 验证方法

检查报告文件存在；检查报告包含六类工程面；检查每个主要优化点包含问题、证据、建议路径、优先级与验证方法。

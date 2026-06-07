# Delta Spec

## MODIFIED Requirements

### Requirement: 公共 API 必须与私有实现隔离

项目的公共头文件 MUST 只暴露稳定、语义正确的公共 Interface，不得包含已知错误属性声明或与包语义不一致的导出宏。

#### Scenario: Qt 属性写方法正确

- GIVEN `QtMaterialProgress` 暴露 `backgroundColor` 属性
- WHEN 调用方通过 Qt meta-object 写入该属性
- THEN 写入操作 MUST 调用 `setBackgroundColor`
- AND MUST NOT 错误调用 `setProgressColor`

#### Scenario: 导出宏具备包语义

- GIVEN 一个安装后可见的公共类声明
- WHEN 审查其导出宏
- THEN 该类 SHALL 使用 `QTMATERIALWIDGETS_EXPORT`
- AND 该宏 SHALL 基于 `QTMATERIALWIDGETS_LIBRARY` 选择导出或导入

### Requirement: 项目必须提供标准 CMake 包接入能力

该项目 MUST 以稳定、可安装、可导出的方式向外部项目提供 `CMake` 接入能力，并在文档和样例中优先呈现该路径。

#### Scenario: README 推荐标准接入

- GIVEN 调用方阅读 README
- WHEN 查找 CMake 接入方式
- THEN README MUST 推荐 `find_package(QtMaterialWidgets CONFIG REQUIRED)`
- AND README MUST 推荐链接 `QtMaterialWidgets::Widgets`
- AND README MUST NOT 将手工指定 `.lib/.so` 作为主路径

#### Scenario: 最小 consumer 样例

- GIVEN 库已安装到一个 CMake prefix
- WHEN 构建 `examples/consumer`
- THEN consumer SHALL 只通过 `find_package` 与 `QtMaterialWidgets::Widgets` 接入
- AND consumer MUST NOT 直接引用仓库内部构建目录或源目录

## ADDED Requirements

### Requirement: P0 优化必须具备本地验证证据

每个 P0 优化 MUST 至少通过静态检查、构建验证或 consumer 构建验证之一证明行为达成。

#### Scenario: 首批 P0 优化验证

- GIVEN 公共 Interface 与 README 已修改
- WHEN 执行本地验证
- THEN 主库 target MUST 构建通过
- AND 安装后 consumer MUST 配置与构建通过
- AND OpenSpec 变更 MUST 通过严格校验

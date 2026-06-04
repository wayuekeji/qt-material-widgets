# Delta Spec

## ADDED Requirements

### Requirement: 项目必须提供标准 CMake 包接入能力

该项目 MUST 以稳定、可安装、可导出的方式向外部项目提供 `CMake` 接入能力。

#### Scenario: 外部项目通过 find_package 接入

- GIVEN 调用方项目已安装该库
- WHEN 调用方执行 `find_package(... CONFIG REQUIRED)` 并链接公开 target
- THEN 调用方 SHALL 无需手工指定 `.lib/.so` 文件路径
- AND 调用方 SHALL 无需手工拼接头文件目录

#### Scenario: 示例程序消费公开 target

- GIVEN 仓库内存在示例程序
- WHEN 示例程序参与构建
- THEN 示例程序 MUST 通过公开 target 链接库
- AND 示例程序 MUST NOT 直接依赖构建目录中的平台产物路径

### Requirement: 公共 API 必须与私有实现隔离

项目的公共头文件 MUST 只暴露稳定 API，不得泄漏私有实现结构。

#### Scenario: 公共头检查

- GIVEN 一个安装后可见的公共头文件
- WHEN 审查其 `#include` 与类型暴露
- THEN 该头文件 MUST NOT 直接包含私有 `_p.h` 头
- AND 该头文件 MUST NOT 要求调用方感知内部实现目录

#### Scenario: 实验态组件管理

- GIVEN 一个组件尚未完成、仅有空壳或存在已知结构缺陷
- WHEN 该组件未达到稳定对外标准
- THEN 该组件 MUST NOT 默认作为稳定公共 API 导出

### Requirement: 项目必须建立清晰的分层边界

项目 MUST 在 Core、Widgets、Examples 三类职责之间建立边界。

#### Scenario: Core 与 Widgets 分层

- GIVEN 主题、样式、动画等基础能力
- WHEN 组织模块结构
- THEN 这些能力 SHALL 归属于基础能力层
- AND 具体控件 SHALL 通过该基础层复用机制

#### Scenario: Examples 边界

- GIVEN 示例程序存在
- WHEN 示例程序组织依赖关系
- THEN 示例程序 MUST 作为公共 API 的消费者
- AND 示例程序 MUST NOT 成为公共 API 设计的前提条件

### Requirement: 项目必须具备基础验证闭环

项目 MUST 为构建、接入、行为三类能力建立最小验证闭环。

#### Scenario: 构建验证

- GIVEN 项目进行版本演进
- WHEN 执行持续集成
- THEN 系统 SHALL 验证主支持平台和主支持 Qt 版本的构建结果

#### Scenario: 接入验证

- GIVEN 项目声明支持 `find_package` 与源码接入
- WHEN 变更构建脚本
- THEN 系统 SHALL 至少验证一种安装接入路径和一种源码接入路径

#### Scenario: 行为验证

- GIVEN 项目为控件库
- WHEN 组件功能发生改动
- THEN 系统 SHOULD 通过 `QTest` 或等价方式验证关键交互行为

## MODIFIED Requirements

### Requirement: 构建系统支持策略必须明确主次

项目当前同时包含 `CMake` 与 `qmake`，后续支持策略 MUST 明确主支持路径与降级规则。

#### Scenario: 主构建系统

- GIVEN 两套构建系统并存
- WHEN 项目定义事实来源
- THEN `CMake` SHALL 作为主支持构建系统

#### Scenario: qmake 保留条件

- GIVEN 项目继续保留 `qmake`
- WHEN 宣称其可用
- THEN `qmake` MUST 具有最小可验证闭环
- AND 若闭环无法维持，则 SHOULD 降级为非主支持路径

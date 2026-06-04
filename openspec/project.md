# 项目基线

## 项目名称

`qt-material-widgets`

## 项目定位

该项目是一个基于 `Qt Widgets` 的 `Material Design` 风格桌面 UI 组件库仓库，面向 Qt 应用提供可复用的界面组件、主题样式与演示程序。

项目当前不是业务应用，也不是插件系统，而是一个“共享库 + 示例程序 + 静态资源”的基础设施型 GUI 仓库。

## 技术栈

- 语言：`C++17`
- GUI 框架：`Qt Widgets`
- 依赖模块：`Qt Core`、`Qt Gui`、`Qt Widgets`、`Qt StateMachine`
- 构建系统：`CMake`、`qmake`
- 资源形式：`qrc` 内嵌字体、SVG 图标、示例资源
- 目标平台：当前仓库文档声明覆盖 `Windows`、`Linux`、`Android`、`macOS`

## 当前目录结构

- `components/`
  - 组件实现、私有头、内部样式与资源
- `include/qmetarial/`
  - 对外头文件
- `examples/`
  - 示例应用、组件配置页、`.ui` 表单
- `fonts/`
  - 内嵌字体资源
- `gifs/`
  - README 演示素材
- `Docs/`
  - 文档草稿与知识记录

## 当前构建形态

- 根 `CMakeLists.txt` 以子目录方式组织 `components` 与 `examples`
- `components` 当前构建为 `SHARED` 动态库
- `examples` 当前依赖构建目录中的库产物路径，而不是标准包导出目标
- `qmake` 与 `CMake` 并行维护，但当前以 `CMake` 为主路径

## 当前架构边界

### 公共层

- 对外公开组件头文件
- 对外公开主题、样式、动画相关基础类

### 实现层

- 各组件 `.cpp`
- `_p.h` 私有实现
- `_internal.h/.cpp` 内部辅助逻辑

### 演示层

- `examples` 示例应用
- 每个组件对应的设置编辑器与展示页

## 当前已识别问题

### 分发与接入

- 缺少标准安装导出能力
- 缺少 `find_package` 可消费的 `Config.cmake`
- 示例程序直接链接构建目录中的平台产物路径
- 对外目标名 `components` 语义弱，不适合作为稳定消费接口

### API 与封装

- 公共头存在私有实现泄漏
- 对外目录名 `qmetarial` 存在拼写错误
- 部分头文件处于空壳或实验态，但已经暴露到公共接口面

### 工程治理

- 自动化测试缺失
- CI 缺失
- API 文档未成型
- README 与代码实现状态存在偏差

## 后续演进原则

1. 先完成“可分发、可接入、可验证”，再扩充组件数量。
2. 公共 API 必须与私有实现隔离，禁止继续扩大泄漏面。
3. 构建系统以 `CMake` 为主事实来源，`qmake` 仅在有验证闭环时继续维护。
4. 示例程序仅作为演示与回归验证载体，不得反向污染库的安装与包结构。

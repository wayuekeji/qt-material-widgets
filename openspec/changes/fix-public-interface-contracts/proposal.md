# 变更提案：修正公共 Interface 与标准接入说明

## 动机

`Docs/ArchitectureOptimizationReport.md` 的 P0 项指出，当前项目已经具备 `QtMaterialWidgets::Widgets` 的 CMake package 雏形，但公共 Interface 与文档仍存在明确缺陷：

- `QtMaterialProgress::backgroundColor` 的 Qt 属性写方法声明错误。
- 公共导出宏仍使用泛化的 `COMPONENTS_EXPORT`，与包名和目标名不一致。
- README 和旧 Docs 仍把手工指定 include 目录与 `.lib/.so` 路径作为主要接入方式。
- 仓库缺少最小外部 consumer 样例，无法沉淀 `find_package` 接入验证。

这些问题直接影响外部调用方对库 Interface 的理解与验证。

## 目标边界

1. 修正已证实的公共头属性声明错误。
2. 将公共导出宏收敛为 `QTMATERIALWIDGETS_EXPORT`。
3. 保留构建行为不变，继续导出 `QtMaterialWidgets::Widgets`。
4. 增加最小 CMake consumer 样例，用作安装后接入验证模板。
5. 校准 README 与 Docs 中的主接入路径。

## 非目标

1. 本次不迁移 `include/qmetarial` 目录名。
2. 本次不删除空壳头文件。
3. 本次不重构 experimental/stub 控件分级。
4. 本次不调整 qmake 支持策略。
5. 本次不引入完整 CI 矩阵。

## 方案设计

### 1. 公共属性修正

将 `include/qmetarial/qtmaterialprogress.h` 中 `backgroundColor` 属性的 `WRITE` 从 `setProgressColor` 修正为 `setBackgroundColor`。

### 2. 导出宏语义收敛

在 `components_global.h` 中定义包语义宏：

```cpp
QTMATERIALWIDGETS_EXPORT
```

并将公共头中的类导出声明改为该宏。CMake 编译定义同步从 `COMPONENTS_LIBRARY` 改为 `QTMATERIALWIDGETS_LIBRARY`。

### 3. 标准 CMake 接入说明

README 主路径改为：

```cmake
find_package(QtMaterialWidgets CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE QtMaterialWidgets::Widgets)
```

旧的手工 `.lib/.so` 链接说明不再作为推荐路径。

### 4. 最小 consumer 样例

新增 `examples/consumer/CMakeLists.txt` 与 `examples/consumer/main.cpp`，只消费安装后的 `QtMaterialWidgets::Widgets`，不直接引用仓库内部路径。

## 决策记录

### Decision 1

本次只修正宏语义，不重命名物理 include 目录。

原因：

- `qmetarial` 目录迁移会影响所有 include 路径，适合单独 Spec。
- 当前 P0 目标是消除明确错误并提升接入可验证性。

### Decision 2

保留 `components` 二进制输出名。

原因：

- 产物命名治理属于 CMake target 语义优化，应与源码清单治理一起处理。
- 本次重点是公共 Interface 和文档接入路径。

### Decision 3

consumer 样例放在 `examples/consumer`，但不默认加入主构建。

原因：

- 该样例用于安装后外部消费验证。
- 默认加入主构建会破坏其“外部 consumer”语义。

## 风险清单

### 风险 1：导出宏重命名影响未扫描到的内部引用

- 影响：编译失败。
- 结论：非阻断。
- 策略：保留 `COMPONENTS_EXPORT` 兼容别名，并执行 Release 构建验证。

### 风险 2：README 与旧 Docs 修改改变用户接入认知

- 影响：手工链接用户需要迁移到 CMake package。
- 结论：非阻断。
- 策略：保留源码方式接入说明，明确手工链接不再是主路径。

### 风险 3：consumer 样例需要先安装库

- 影响：不能直接在仓库主构建中验证。
- 结论：非阻断。
- 策略：通过临时安装前缀执行 `find_package` consumer 构建验证。

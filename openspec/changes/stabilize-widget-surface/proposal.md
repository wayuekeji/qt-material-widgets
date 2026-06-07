# 变更提案：稳定与实验 Widget Surface 分级

## 动机

`Docs/ArchitectureOptimizationReport.md` 的 P0-03 指出，当前稳定安装 Interface 中混入了实验态或存根控件：

- `QtMaterialMenu` 公开类只有构造与析构，Implementation 基本为空。
- `QtMaterialSteps` 公共头直接记录已知布局缺陷，Implementation 使用文件级 `static int currentWidth`，多实例存在状态污染风险。
- `QtMaterialComboBox` 当前仍处于 work in progress，且 `paintEvent` 中反复创建 delegate，Implementation 不适合进入稳定安装 Interface。

这些 Module 可以继续保留在源码和示例中，但不应被默认安装为稳定公共 Interface。

## 目标边界

1. 建立稳定、实验、存根、未实现的 Widget Surface 文档。
2. 将 `QtMaterialComboBox`、`QtMaterialSteps`、`QtMaterialMenu` 从默认安装头中移除。
3. 保持源码构建和示例构建不被破坏。
4. 保持已安装稳定控件可通过 `QtMaterialWidgets::Widgets` 消费。

## 非目标

1. 本次不删除 `QtMaterialComboBox`、`QtMaterialSteps`、`QtMaterialMenu` 源码。
2. 本次不修复这些实验/存根控件的内部实现。
3. 本次不迁移 `include/qmetarial` 目录名。
4. 本次不引入完整测试框架。

## 方案设计

### 1. Surface 分级

新增 `Docs/ComponentSurface.md`，按以下状态维护控件：

- `stable`：默认安装，作为稳定公共 Interface。
- `experimental`：源码与示例保留，但不默认安装。
- `stub`：源码可能存在，但 Interface 不完整，不默认安装。
- `not implemented`：仅作为路线图记录。

### 2. 默认安装面收敛

更新 `components/CMakeLists.txt` 的 `QTMATERIALWIDGETS_INSTALLED_HEADERS` 排除列表：

- `qtmaterialcombobox.h`
- `qtmaterialsteps.h`
- `qtmaterialmenu.h`

已有空壳头排除保持不变。

### 3. README 状态校准

README 的组件状态说明必须与安装面一致：

- `ComboBox` 标记为 experimental / work in progress。
- `Menu` 标记为 stub。
- `Steps` 标记为 experimental。
- 已安装稳定控件保持在 implemented 列表。

## 决策记录

### Decision 1

实验/存根控件先从安装面移除，而不是直接删除源码。

原因：

- 示例仍可作为开发与回归载体。
- 删除源码会扩大本次变更范围，并影响后续修复这些控件。

### Decision 2

分级文档落到 `Docs/ComponentSurface.md`。

原因：

- 该文档描述仓库当前交付面，不适合埋在 README 长表格中。
- 后续每次控件晋级或降级都可以独立更新该文件。

### Decision 3

本次不为 experimental/stub 新建单独 CMake target。

原因：

- 当前优先目标是安装 Interface 收敛。
- target 拆分属于后续 CMake 源清单与 target 治理。

## 风险清单

### 风险 1：外部用户已直接包含实验/存根头

- 影响：安装后这些头不再可见。
- 结论：非阻断。
- 策略：这些 Module 尚未达到稳定标准，保留源码方式可继续内部开发。

### 风险 2：README 与实际安装面再次漂移

- 影响：调用方误判控件稳定性。
- 结论：非阻断。
- 策略：新增 `Docs/ComponentSurface.md` 作为状态清单，并在 README 引用。

### 风险 3：示例仍使用 experimental/stub 控件

- 影响：示例可能展示非稳定控件。
- 结论：非阻断。
- 策略：本次只要求安装面收敛；示例后续通过 demo harness 治理拆分。

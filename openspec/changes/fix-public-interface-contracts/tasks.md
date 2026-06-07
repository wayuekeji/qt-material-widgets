# 任务清单

## Task 1：修正 QtMaterialProgress 属性声明

### 目标

修正 `backgroundColor` Qt 属性的写方法，消除公共 Interface 明确错误。

### 影响范围

- `include/qmetarial/qtmaterialprogress.h`

### 实施思路

将 `Q_PROPERTY(QColor backgroundColor WRITE setProgressColor READ backgroundColor)` 改为 `WRITE setBackgroundColor`。

### 验证方法

构建 `QtMaterialWidgets` target；检查公共头中不再存在错误声明。

## Task 2：收敛公共导出宏命名

### 目标

让公共导出宏具备包语义，避免继续暴露 `components` 历史命名。

### 影响范围

- `include/qmetarial/components_global.h`
- `include/qmetarial/**/*.h`
- `components/CMakeLists.txt`

### 实施思路

新增 `QTMATERIALWIDGETS_EXPORT` 与 `QTMATERIALWIDGETS_LIBRARY`，公共类声明使用新宏；保留 `COMPONENTS_EXPORT` 作为过渡别名。

### 验证方法

构建 `QtMaterialWidgets` target；检查公共头类声明使用 `QTMATERIALWIDGETS_EXPORT`。

## Task 3：新增最小 consumer 样例

### 目标

沉淀安装后 `find_package` 接入验证模板。

### 影响范围

- `examples/consumer/CMakeLists.txt`
- `examples/consumer/main.cpp`

### 实施思路

创建一个最小 Qt Widgets 应用，只包含公共头并链接 `QtMaterialWidgets::Widgets`。

### 验证方法

安装库到临时 prefix；用 `CMAKE_PREFIX_PATH` 配置并构建 consumer。

## Task 4：校准 README 与旧 Docs 接入说明

### 目标

让文档主路径与实际 CMake package 能力一致。

### 影响范围

- `README.md`
- `Docs/TODO.md`

### 实施思路

README 改为优先展示 `find_package` 接入；旧 TODO 改为历史问题已由 CMake package 路径承接。

### 验证方法

静态检查文档包含 `find_package(QtMaterialWidgets CONFIG REQUIRED)` 和 `QtMaterialWidgets::Widgets`，且不再把手工 `.lib/.so` 链接作为主推荐路径。

# 任务清单

## Task 1：新增 typed ThemeColor Interface

### 目标

让默认主题 key 成为显式公共 Interface。

### 影响范围

- `include/qmetarial/lib/qtmaterialtheme.h`
- `components/materiallib/qtmaterialtheme.cpp`

### 实施思路

新增 `Material::ThemeColor`、`Material::themeColorKey`，并为 `QtMaterialTheme` 增加 typed overload。

### 验证方法

构建主库；consumer 使用 `Material::ThemeColor::Primary1` 编译通过。

## Task 2：为 QtMaterialStyle 增加 typed overload

### 目标

让控件和调用方可以通过 style 单例使用 typed theme key。

### 影响范围

- `include/qmetarial/lib/qtmaterialstyle.h`
- `components/materiallib/qtmaterialstyle.cpp`

### 实施思路

新增 `themeColor(Material::ThemeColor key)` overload，内部转发到 `QtMaterialTheme::getColor(key)`。

### 验证方法

consumer 调用 `QtMaterialStyle::instance().themeColor(Material::ThemeColor::Canvas)` 编译通过。

## Task 3：迁移内部 themeColor 调用

### 目标

减少 Implementation 对字符串 key 的依赖。

### 影响范围

- `components/**/*.cpp`

### 实施思路

将 `QtMaterialStyle::instance().themeColor("primary1")` 等默认 key 调用改为 typed key。

### 验证方法

静态搜索 `components/**` 中不存在 `themeColor("`；主库构建通过。

## Task 4：更新文档与 consumer 覆盖

### 目标

让推荐路径有可见文档与最小编译覆盖。

### 影响范围

- `Docs/ComponentSurface.md`
- `examples/consumer/main.cpp`

### 实施思路

文档记录 typed theme key；consumer 调用 typed theme API。

### 验证方法

安装后 consumer 通过 `find_package` 构建通过。

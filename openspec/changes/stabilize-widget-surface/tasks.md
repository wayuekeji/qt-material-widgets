# 任务清单

## Task 1：建立 Component Surface 文档

### 目标

记录 stable、experimental、stub、not implemented 控件清单。

### 影响范围

- `Docs/ComponentSurface.md`
- `README.md`

### 实施思路

新增独立文档并在 README 状态段落中引用。将 `ComboBox` 和 `Steps` 标记为 experimental，将 `Menu` 标记为 stub。

### 验证方法

静态检查文档存在且包含四类状态；README 引用该文档。

## Task 2：收敛默认安装头

### 目标

确保默认安装面只包含 stable 控件与基础能力头。

### 影响范围

- `components/CMakeLists.txt`

### 实施思路

在 `QTMATERIALWIDGETS_INSTALLED_HEADERS` 排除列表中加入 `qtmaterialcombobox.h`、`qtmaterialsteps.h`、`qtmaterialmenu.h`。

### 验证方法

安装到临时 prefix；检查安装 include 目录不存在这三个头。

## Task 3：验证源码构建与外部消费

### 目标

确认安装面收敛不破坏主库构建和稳定 consumer。

### 影响范围

- 主库 target
- `examples/consumer`

### 实施思路

构建主库、安装到临时 prefix，再构建最小 consumer。

### 验证方法

`QtMaterialWidgets` Release 构建通过；`examples/consumer` 通过安装 prefix 配置并构建。

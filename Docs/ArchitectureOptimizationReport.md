# 项目优化分析报告

日期：2026-06-06

## 1. 分析范围

本报告只基于项目内事实：

- `openspec/project.md`
- `openspec/changes/**`
- 根 `CMakeLists.txt`、`components/CMakeLists.txt`、`examples/CMakeLists.txt`
- `qt-material-widgets.pro`、`components/components.pro`、`examples/examples.pro`
- `include/qmetarial/**`
- `components/**`
- `examples/**`
- `Docs/**`

当前仓库缺少以下治理资产：

- 未发现实体 `AGENTS.md`
- 未发现 `openspec/specs/**/spec.md`
- 未发现 `CONTEXT.md`
- 未发现 ADR 目录
- 未发现 `tests/`
- 未发现 `.github/workflows/`

下文使用 `Module`、`Interface`、`Implementation`、`Depth`、`Seam`、`Adapter`、`Leverage`、`Locality` 描述架构问题。

## 2. 当前基线

项目定位是 `Qt Widgets` 的 Material Design 组件库，当前已经具备基础库构建能力，并已开始补齐 CMake 包导出：

- 根构建通过 `QTMATERIALWIDGETS_BUILD_EXAMPLES` 控制示例构建。
- `components/CMakeLists.txt` 已创建 `QtMaterialWidgets::Widgets` alias。
- 已存在 `install(TARGETS)`、`install(EXPORT)`、`QtMaterialWidgetsConfig.cmake.in` 和版本文件生成。
- 示例 CMake 已通过 `QtMaterialWidgets::Widgets` 链接库。

本次验证结果：

- `cmake -S . -B %TEMP%/qt-material-widgets-codex-report-build -DQTMATERIALWIDGETS_BUILD_EXAMPLES=OFF` 通过。
- `cmake --build %TEMP%/qt-material-widgets-codex-report-build --config Release --target QtMaterialWidgets` 通过。
- `cmake -S . -B %TEMP%/qt-material-widgets-codex-report-build-examples -DQTMATERIALWIDGETS_BUILD_EXAMPLES=ON` 通过。
- `cmake --build %TEMP%/qt-material-widgets-codex-report-build-examples --config Release --target examples` 通过。
- 构建过程出现 `MSB8029` 临时目录警告和 `pwsh.exe` 环境提示，但目标产物生成成功。

## 3. 优先级路线图

| 优先级 | 优化方向 | 目标 |
| --- | --- | --- |
| P0 | 接入文档与包验证闭环 | 让外部项目能按标准方式消费库 |
| P0 | 公共 Interface 缺陷治理 | 修正错误属性、命名债务、空壳头暴露 |
| P0 | 稳定/实验 Module 分级 | 防止未成熟控件继续污染稳定 Interface |
| P1 | Theme/Icon/Resource Module 深化 | 提升主题与资源访问的 Locality 和 Leverage |
| P1 | 示例层 Module 收敛 | 降低重复设置编辑器和手写注册的维护成本 |
| P1 | CMake 源清单与 target 治理 | 降低构建隐式行为 |
| P2 | 测试与 CI 基线 | 建立可回归验证链路 |
| P2 | 文档与 OpenSpec 治理 | 让规范、文档、实现保持一致 |
| P2 | qmake 支持策略 | 降级或补齐验证闭环 |

## 4. 优化点

### P0-01：接入文档与包验证闭环不一致

问题：

项目已经具备标准 CMake package 雏形，但 README 和旧 Docs 仍把手工指定 include 目录与 `.lib/.so` 路径作为主要接入路径。调用方看到的 Interface 与实际推荐路径不一致。

证据：

- `components/CMakeLists.txt` 已存在 `QtMaterialWidgets::Widgets`、`install(EXPORT)`、`QtMaterialWidgetsConfig.cmake` 生成。
- `cmake/QtMaterialWidgetsConfig.cmake.in` 已包含 `find_dependency(Qt...)` 与 targets 导入。
- `README.md` 仍示例 `target_include_directories(... /path/to/dynamic-lib/include/)` 和直接链接 `components.lib/components.so`。
- `Docs/TODO.md` 仍记录“不知道如何作为 static/dynamic library 使用”的旧问题。

建议路径：

1. 把 README 主路径改为 `find_package(QtMaterialWidgets CONFIG REQUIRED)` + `target_link_libraries(... QtMaterialWidgets::Widgets)`。
2. 增加最小 consumer 示例工程，验证 install 后消费。
3. 将直接链接 `.lib/.so` 文档降级为历史说明或删除。
4. 在 CI 中加入安装后 `find_package` smoke test。

验证方法：

- `cmake --install` 到临时前缀。
- 新建最小 Qt Widgets consumer。
- 仅通过 `CMAKE_PREFIX_PATH` 查找并链接 `QtMaterialWidgets::Widgets`。
- consumer 编译通过，且无需手工添加库文件路径。

### P0-02：公共 Interface 存在明确缺陷

问题：

公共头没有直接包含 `_p.h` 或 `_internal.h`，但仍存在错误属性声明、命名债务、泛化导出宏和空壳头文件。这些都属于稳定 Interface 污染。

证据：

- `include/qmetarial/qtmaterialprogress.h`：`backgroundColor` 的 `WRITE` 误写为 `setProgressColor`，应为 `setBackgroundColor`。
- `include/qmetarial/qtmaterialpaper.h`、`qtmaterialtable.h`、`qtmateriallist.h`、`qtmateriallistitem.h` 只有 include guard，当前 CMake 安装阶段又显式排除这些头。
- 公共目录名为 `include/qmetarial`，`openspec/project.md` 已记录拼写错误。
- 导出宏为 `COMPONENTS_EXPORT`，与包名 `QtMaterialWidgets` 不一致。

建议路径：

1. 立即修正 `QtMaterialProgress::backgroundColor` 属性写方法。
2. 建立公共头审计清单：稳定、实验、移除、内部。
3. 将空壳头从稳定 Interface 中移除，或迁入实验区。
4. 规划 `qmetarial` 到正确 include 命名的迁移。
5. 将 `COMPONENTS_EXPORT` 收敛为包语义导出宏。

验证方法：

- 执行公共头独立编译测试。
- 用 Qt meta-object 检查 `backgroundColor` 写入是否调用 `setBackgroundColor`。
- 安装后只包含公开头，不依赖 `components/` 内私有头。

### P0-03：稳定 Module 与实验 Module 未分级

问题：

部分控件已经进入公共头和示例，但 Implementation 仍偏空壳或实验态。当前 Interface 让调用方误以为它们已稳定。

证据：

- `QtMaterialMenu` 公开类只有构造和析构，Implementation 基本为空。
- `QtMaterialSteps` 公开头内直接声明已知布局缺陷，并写有 TODO。
- `QtMaterialSteps` Implementation 使用文件级 `static int currentWidth`，多实例之间存在状态污染风险。
- `QtMaterialComboBox::paintEvent` 内每次绘制都 `setItemDelegate(new QtMaterialComboBoxDelegate(this))`，Implementation 行为不适合进入稳定 Interface。

建议路径：

1. 给每个控件打状态标签：stable、experimental、stub、removed。
2. stable 才进入安装头与 README 已实现列表。
3. experimental 保留源码与示例，但不作为稳定包 Interface。
4. stub 类优先删除或补齐，禁止继续作为公开消费入口。

验证方法：

- 公共安装头与 README 已实现列表一致。
- experimental/stub 不被默认安装。
- 对 stable 控件执行最小构造、属性设置、paint smoke test。

### P1-01：Theme/Icon/Resource Module 过浅

问题：

主题颜色、图标路径、字体注册集中在 `QtMaterialTheme` 和 `QtMaterialStyle`，但 Interface 要调用方理解字符串 key、庞大枚举和资源路径约定。Module 的 Depth 不足，Leverage 偏低；错误也缺少强约束。

证据：

- `include/qmetarial/lib/qtmaterialtheme.h` 约 301 行，包含大量颜色枚举。
- `QtMaterialThemePrivate` 用 `QHash<QString, QColor>` 存储颜色。
- `QtMaterialTheme::getColor` 找不到 key 时仅 `qWarning()` 并返回无效 `QColor()`。
- `QtMaterialTheme::icon(QString category, QString icon)` 通过字符串拼接 `:/icons/icons/.../ic_..._24px.svg`。
- `QtMaterialStylePrivate::init` 隐式注册 Roboto 字体并创建默认主题。

建议路径：

1. 将主题 token、颜色表、图标索引从手写业务逻辑中分离为资源 registry。
2. 对主题 key 与图标 key 建立可验证 Interface，减少任意字符串调用。
3. 对缺失资源改为 fail-fast 或显式错误对象，不静默返回无效颜色。
4. 保持 `QtMaterialStyle` 对调用方的 Interface 小而稳定，把资源加载细节留在 Implementation。

验证方法：

- 单测覆盖已知 theme token、缺失 token、已知 icon、缺失 icon。
- 启动时验证资源 registry 完整性。
- 修改一处资源映射不需要改多个控件调用点。

### P1-02：资源包体积与加载策略缺少分层

问题：

当前核心库无条件内嵌大量图标和字体，资源 Interface 是“全部打进库”。这对只使用少量控件的调用方缺少 Leverage，也无法按需裁剪。

证据：

- `components/resources.qrc` 包含 967 个 `<file>` 条目。
- 其中 961 个是图标条目，6 个是 Roboto 字体条目。
- `QtMaterialTheme::icon` 依赖这些资源全部存在。

建议路径：

1. 拆分基础字体资源、核心控件图标资源、完整 Material icon pack。
2. 为资源包建立可选 CMake option 或独立 resource target。
3. 默认包只包含控件必需资源，完整图标包按需启用。
4. 给资源缺失提供测试和诊断信息。

验证方法：

- 默认构建与完整资源构建产物大小可比较。
- 所有 stable 控件在默认资源包下可运行。
- 调用完整 icon pack 中非核心图标时，只有启用对应包才成功。

### P1-03：示例层重复度高，验证价值偏低

问题：

示例层作为消费者是必要的，但当前每个控件各自维护设置编辑器、布局搭建、`setupForm`、颜色选择和信号连接。该层 Module 较浅，重复 Implementation 分散，后续扩展控件会继续复制模式。

证据：

- `examples/` 有 25 个头、26 个 cpp、20 个 `.ui`。
- 多数 `*settingseditor.cpp` 重复创建 settings widget、canvas、layout、`setupForm`、`updateWidget`。
- `examples/mainwindow.cpp` 手写 include、手写实例化、手写 `QMap<QString, QWidget*>` 注册页面。
- `tabssettingseditor.cpp` 使用 `SLOT([](int a) { ... })` 字符串写法，能编译但不是有效的 Qt slot 设计。

建议路径：

1. 提取示例页注册表，让新增示例只声明名称和构造逻辑。
2. 提取设置页骨架 Module，集中处理 settings/canvas 布局。
3. 统一颜色选择、禁用状态、主题开关等重复操作。
4. 将示例从“手工演示”提升为 smoke test 载体。

验证方法：

- 新增一个示例页无需修改 `MainWindow` 多处 include 与实例化。
- stable 控件示例可批量构造。
- 示例启动 smoke test 能覆盖页面注册完整性。

### P1-04：CMake 源清单与 target 语义仍有隐式行为

问题：

CMake package 已开始成型，但源码收集和 target 命名仍有历史痕迹。当前 Interface 是 `QtMaterialWidgets::Widgets`，但产物名仍是 `components`，内部源码通过 `file(GLOB)` 自动收集，构建可预测性不足。

证据：

- `components/CMakeLists.txt` 使用 `file(GLOB THELIB "materiallib/*")`、`file(GLOB COMPONENTSHEADER "*.h")`、`file(GLOB COMPONENTSSOURCE "*.cpp")`。
- `examples/CMakeLists.txt` 也使用 `file(GLOB HEADER "*.h")`、`file(GLOB RSOURCE "*.cpp")`、`file(GLOB UI "*.ui")`。
- `set_target_properties(... OUTPUT_NAME components)` 与包名 `QtMaterialWidgets` 不一致。
- `components` 子目录自身调用 `project(components)`，target 与包语义不完全一致。

建议路径：

1. 用显式 `target_sources` 替代无 `CONFIGURE_DEPENDS` 的 `file(GLOB)`。
2. 统一 target、输出产物、导出命名策略。
3. 将内部 Core target 明确标注为私有 Implementation target。
4. 给示例 target 使用更明确的名称，例如 demo 或 examples app。

验证方法：

- 新增/删除源文件时，CMake diff 明确体现变更。
- 安装导出的 targets 文件不暴露内部 Implementation target。
- 下游只感知 `QtMaterialWidgets::Widgets`。

### P2-01：测试与 CI 缺失

问题：

当前库能构建，但没有自动化验证保证 Interface 行为、资源可用性、包接入和示例启动。没有 CI 时，跨 Qt5/Qt6、Windows/Linux 的声明无法持续可信。

证据：

- 未发现 `tests/`。
- 未发现 `.github/workflows/`。
- 未发现 `enable_testing`、`add_test`、`QTest`。
- `openspec/project.md` 已记录自动化测试与 CI 缺失。

建议路径：

1. 建立 `tests/`，先覆盖 `QtMaterialProgress`、`QtMaterialTheme`、`QtMaterialStyle`、资源加载。
2. 增加 CMake package consumer test。
3. 增加示例构造 smoke test。
4. 建立 Windows/Linux + Qt5/Qt6 构建矩阵。

验证方法：

- `ctest --output-on-failure` 可执行。
- CI 至少覆盖 Release 构建、安装、consumer 编译。
- 每个 P0 Interface 修复都有回归测试。

### P2-02：文档与 OpenSpec 治理未闭环

问题：

项目文档存在，但状态分散，且未形成生效规范目录。OpenSpec change 中已有 roadmap，但缺少归档后的 `openspec/specs/**/spec.md` 作为长期事实来源。

证据：

- `Docs/API.md` 基本为空章节。
- `Docs/TODO.md` 仍停留在旧的手工链接问题。
- `Docs/RelatedKnowledge/OpaquePointer.md` 和 `QStyle.md` 是知识草稿，未转化为项目决策。
- 未发现 `openspec/specs/**/spec.md`。
- 未发现 ADR 与 `CONTEXT.md`。

建议路径：

1. 归档已完成的 OpenSpec 变更，形成生效 spec。
2. 建立 `CONTEXT.md`，定义项目领域词：Core、Widgets、Examples、Theme、Resource Pack、Demo Page 等。
3. 建立 ADR 目录，记录 qmake 支持级别、include 命名迁移、资源包拆分等决策。
4. 用生成式或半自动方式补齐 API 文档，但必须以公共头为事实来源。

验证方法：

- `openspec/specs/**/spec.md` 存在并覆盖当前治理规则。
- README、Docs/API、OpenSpec 的接入方式一致。
- 每个重大架构选择能在 ADR 中找到决策记录。

### P2-03：qmake 支持策略需要降级或验证

问题：

项目声明同时支持 CMake 和 qmake，但 qmake 路径仍直接依赖构建目录产物，且配置停留在 `c++11`。这与 `openspec/project.md` 中 CMake 为主事实来源、C++17 技术栈的设定不一致。

证据：

- `qt-material-widgets.pro` 仍以 subdirs 方式同时构建 `components examples`。
- `examples/examples.pro` 在 Windows/Unix 下直接链接 `$$top_builddir/components` 产物。
- `components/components.pro` 使用 `CONFIG += c++11`，而项目基线是 C++17。
- README 明确表示 qmake 首次构建存在奇怪问题并推荐 CMake。

建议路径：

1. 决策 qmake 是主支持、兼容支持还是历史支持。
2. 若保留，补齐 qmake 最小 CI 与外部接入样例。
3. 若不保留，从 README 主路径移除 qmake，并在 OpenSpec/ADR 中说明降级原因。
4. 避免 qmake 示例继续反向依赖构建目录细节。

验证方法：

- qmake 路径有独立构建验证。
- qmake 示例不要求调用方手工拼接库产物路径。
- qmake 标准与 CMake 主路径的 C++ 版本一致，或明确声明差异。

## 5. 后续 OpenSpec 拆分建议

建议按以下顺序拆分后续变更：

1. `fix-public-interface-contracts`：修正 `QtMaterialProgress` 属性、空壳头、导出宏命名。
2. `consumer-package-smoke-test`：新增安装后 consumer 验证与 README 接入修正。
3. `stabilize-widget-surface`：建立 stable/experimental/stub 分级。
4. `theme-resource-module-deepening`：治理 Theme/Icon/Resource Module。
5. `demo-harness-consolidation`：收敛示例页注册与重复设置编辑器。
6. `test-ci-baseline`：补齐 QTest、ctest、CI 矩阵。
7. `qmake-support-policy`：记录并执行 qmake 支持策略。

## 6. 结论

当前最高价值优化不是继续扩充控件数量，而是先把库的消费 Interface、稳定 Module 范围、资源 Module、测试 CI 和文档规范闭环建立起来。

项目已经具备 CMake package 的雏形，下一步应把“可构建”推进到“可安装、可消费、可验证、可治理”。P0 项完成前，不建议继续扩大公开控件面。

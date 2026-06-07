# 变更提案：深化 Theme Key Interface

## 动机

`Docs/ArchitectureOptimizationReport.md` 的 P1-01 指出，当前主题颜色访问主要依赖字符串 key：

- `QtMaterialTheme::getColor(const QString &key)`
- `QtMaterialTheme::setColor(const QString &key, ...)`
- `QtMaterialStyle::themeColor(const QString &key)`

控件 Implementation 中大量散落 `"primary1"`、`"accent3"`、`"disabled"` 等字符串字面量。调用方和维护者必须记住隐式 key 集合，Interface 偏浅，错误只能在运行期以 `qWarning()` 暴露。

## 目标边界

1. 新增 `Material::ThemeColor` typed key。
2. 为 `QtMaterialTheme` 和 `QtMaterialStyle` 增加 typed overload。
3. 保留现有字符串 API 以避免破坏外部调用方。
4. 将库内部主题颜色读取迁移到 typed key。
5. 在 consumer 样例中覆盖 typed key 消费路径。

## 非目标

1. 本次不拆分资源包。
2. 本次不重构完整 Material color palette。
3. 本次不移除字符串 API。
4. 本次不改变默认主题颜色值。
5. 本次不引入完整 QTest 框架。

## 方案设计

### 1. Typed Theme Key

在 `Material` namespace 中新增：

```cpp
enum class ThemeColor {
    Primary1,
    Primary2,
    Primary3,
    Accent1,
    Accent2,
    Accent3,
    Text,
    AlternateText,
    Canvas,
    Border,
    Disabled,
    Disabled2,
    Disabled3
};
```

新增 `themeColorKey(ThemeColor key)` 作为 typed key 到 legacy 字符串 key 的唯一映射点。

### 2. Theme 与 Style overload

`QtMaterialTheme` 新增：

```cpp
QColor getColor(Material::ThemeColor key) const;
void setColor(Material::ThemeColor key, const QColor &color);
void setColor(Material::ThemeColor key, Material::Color color);
```

`QtMaterialStyle` 新增：

```cpp
QColor themeColor(Material::ThemeColor key) const;
```

### 3. 内部调用迁移

库内部 `QtMaterialStyle::instance().themeColor("...")` 迁移为 typed key。字符串 API 保留给外部兼容与临时扩展。

## 决策记录

### Decision 1

使用 `enum class ThemeColor`，而不是继续扩展字符串常量。

原因：

- typed key 能让编译器参与校验。
- key 集合成为公共 Interface 的显式一部分。

### Decision 2

保留 legacy 字符串 API。

原因：

- 当前外部用户可能已经使用自定义主题 key。
- 本次目标是加深 Interface，不是做破坏性迁移。

### Decision 3

本次不处理 icon key typed 化。

原因：

- 图标分类与 961 个资源条目相关，适合后续资源 registry 变更。
- 主题 key 集合较小，可以先形成可验证收益。

## 风险清单

### 风险 1：内部迁移遗漏字符串调用点

- 影响：仍存在部分浅 Interface 使用。
- 结论：非阻断。
- 策略：用 `rg 'themeColor\\(\"' components` 验证库内部残留。

### 风险 2：typed key 映射错误

- 影响：默认颜色行为改变。
- 结论：非阻断。
- 策略：保留原字符串值映射，并通过 consumer 构建覆盖 typed API。

### 风险 3：外部调用方仍使用字符串 API

- 影响：无法完全消除运行期字符串错误。
- 结论：非阻断。
- 策略：文档标记 typed overload 为推荐路径，后续再评估废弃策略。

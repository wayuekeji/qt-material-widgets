# Delta Spec

## ADDED Requirements

### Requirement: Theme key 必须具备 typed Interface

项目 MUST 为默认主题颜色提供 typed key Interface，避免调用方必须记忆字符串 key。

#### Scenario: 调用方读取 typed theme color

- GIVEN 调用方包含 `lib/qtmaterialtheme.h`
- WHEN 调用 `QtMaterialTheme::getColor(Material::ThemeColor::Primary1)`
- THEN 调用方 SHALL 获得与 legacy key `"primary1"` 相同的颜色

#### Scenario: 调用方写入 typed theme color

- GIVEN 调用方持有 `QtMaterialTheme`
- WHEN 调用 `setColor(Material::ThemeColor::Accent1, QColor(...))`
- THEN 后续通过 typed key 读取 SHALL 返回该颜色

#### Scenario: Style 提供 typed theme color

- GIVEN 调用方使用 `QtMaterialStyle::instance()`
- WHEN 调用 `themeColor(Material::ThemeColor::Canvas)`
- THEN 调用方 SHALL 获得默认 canvas 颜色

### Requirement: 内部主题访问应优先使用 typed key

库内部 Implementation MUST 使用 `Material::ThemeColor` overload 访问默认主题颜色。

#### Scenario: 内部 themeColor 字符串调用检查

- GIVEN 本次变更完成
- WHEN 静态搜索 `components/**` 中的 `themeColor("`
- THEN 不应存在库内部默认主题颜色读取调用

## MODIFIED Requirements

### Requirement: 公共 API 必须与私有实现隔离

主题颜色 key 集合 SHALL 作为公共 Interface 显式暴露，而不是仅隐含在 Implementation 字符串中。

#### Scenario: ThemeColor 枚举公开

- GIVEN 调用方包含安装后的 `lib/qtmaterialtheme.h`
- WHEN 编译使用 `Material::ThemeColor::Primary1`
- THEN 编译 MUST 成功

#### Scenario: legacy 字符串 API 兼容

- GIVEN 旧调用方使用 `getColor(QString)` 或 `setColor(QString, ...)`
- WHEN 本次变更后重新编译
- THEN 旧调用方 SHALL 继续编译

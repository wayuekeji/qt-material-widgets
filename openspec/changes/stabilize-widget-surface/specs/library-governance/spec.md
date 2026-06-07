# Delta Spec

## ADDED Requirements

### Requirement: Widget Surface 必须分级

项目 MUST 维护当前 Widget Surface 状态清单，将控件划分为 stable、experimental、stub、not implemented。

#### Scenario: Surface 文档存在

- GIVEN 项目已经识别稳定与非稳定控件
- WHEN 审查文档目录
- THEN `Docs/ComponentSurface.md` MUST 存在
- AND 该文档 MUST 列出 stable、experimental、stub、not implemented 四类控件

#### Scenario: 非稳定控件不默认安装

- GIVEN 一个控件被标记为 experimental 或 stub
- WHEN 执行默认安装
- THEN 该控件公共头 MUST NOT 出现在安装 include 目录
- AND 该控件 MAY 继续保留在源码和示例中

## MODIFIED Requirements

### Requirement: 公共 API 必须与私有实现隔离

项目的默认安装公共 Interface MUST 只包含 stable 控件和基础能力头；未达到稳定标准的控件不得默认安装。

#### Scenario: 安装头检查

- GIVEN `QtMaterialComboBox` 被标记为 experimental
- AND `QtMaterialSteps` 被标记为 experimental
- AND `QtMaterialMenu` 被标记为 stub
- WHEN 执行 `cmake --install`
- THEN 安装 include 目录 MUST NOT 包含 `qtmaterialcombobox.h`
- AND MUST NOT 包含 `qtmaterialsteps.h`
- AND MUST NOT 包含 `qtmaterialmenu.h`

### Requirement: README 必须反映当前交付面

README MUST 区分已实现稳定控件与实验/存根控件。

#### Scenario: README 状态校准

- GIVEN 调用方查看 README 的组件状态
- WHEN 查找 `ComboBox`、`Steps`、`Menu`
- THEN README SHALL NOT 将这些控件列为 stable implemented
- AND README SHALL 引用 `Docs/ComponentSurface.md` 作为详细状态清单

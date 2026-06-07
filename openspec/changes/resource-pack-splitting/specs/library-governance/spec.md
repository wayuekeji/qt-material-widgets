## ADDED Requirements

### Requirement: Default Core Resource Pack

The library SHALL provide a default core resource pack that contains all resources required by stable widgets.

#### Scenario: Stable widgets build without full icon pack

- **GIVEN** `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK` is disabled
- **WHEN** the library target is configured and built
- **THEN** `QtMaterialWidgets` SHALL build successfully
- **AND** stable widgets SHALL have their required font, checkbox, and radio-button resources available

### Requirement: Optional Full Icon Pack

The CMake build MUST expose an option named `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK`.

#### Scenario: Full icon pack enabled

- **GIVEN** `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK` is enabled
- **WHEN** the library target is configured and built
- **THEN** the full Material icon catalog SHALL be compiled into the resource system

#### Scenario: Full icon pack disabled

- **GIVEN** `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK` is disabled
- **WHEN** the library target is configured and built
- **THEN** non-core Material icons SHALL NOT be compiled into the default core resource pack

### Requirement: Resource Policy Documentation

The project documentation SHALL state that arbitrary Material icons require the full icon pack option.

#### Scenario: Consumer needs arbitrary icons

- **GIVEN** a downstream consumer uses `QtMaterialTheme::icon(category, icon)` for icons outside the core pack
- **WHEN** they read the component surface documentation
- **THEN** the documentation SHALL instruct them to enable `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK`

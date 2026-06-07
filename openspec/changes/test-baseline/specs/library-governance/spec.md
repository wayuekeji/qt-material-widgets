## ADDED Requirements

### Requirement: CTest Baseline

The CMake build SHALL expose tests through standard CTest integration when `BUILD_TESTING` is enabled.

#### Scenario: Tests are configured

- **GIVEN** the project is configured with `BUILD_TESTING=ON`
- **WHEN** CMake generation completes
- **THEN** at least one test SHALL be registered with CTest

### Requirement: Public API Regression Smoke Test

The test baseline MUST verify at least one public meta-object property regression.

#### Scenario: Progress background color is writable

- **GIVEN** a `QtMaterialProgress` instance
- **WHEN** the `backgroundColor` property is written through Qt meta-object APIs
- **THEN** the property SHALL update through `setBackgroundColor`

### Requirement: Theme And Resource Smoke Test

The test baseline MUST verify typed theme access and core resource availability.

#### Scenario: Typed theme color is set and read

- **GIVEN** a `QtMaterialTheme`
- **WHEN** `Material::ThemeColor::Accent1` is set through the typed API
- **THEN** the same color SHALL be returned through the typed API

#### Scenario: Core resources are available

- **GIVEN** the default core resource pack
- **WHEN** tests check required font and icon resources
- **THEN** Roboto regular, checkbox, and demo message resources SHALL be present

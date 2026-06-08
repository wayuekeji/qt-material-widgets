## MODIFIED Requirements

### Requirement: GitHub Actions CMake CI

The GitHub Actions CI workflow SHALL validate the supported CMake delivery path on Windows and Ubuntu using Qt 6.6.3.

The CI workflow MUST install only Qt archives that are valid for the selected Qt version and platform.

The CI workflow MUST install the Qt `qtscxml` archive when using Qt 6.6.3 because it provides the `Qt6StateMachine` CMake package required by the library.

The CI workflow MUST configure the project with:

- `QTMATERIALWIDGETS_BUILD_EXAMPLES=ON`
- `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK=OFF`
- `BUILD_TESTING=ON`

The CI workflow MUST run the following verification stages:

- CMake configure
- CMake build
- CTest execution
- examples target build
- CMake install
- installed-package consumer configure through `CMAKE_PREFIX_PATH`
- installed-package consumer build

#### Scenario: Qt installation uses valid archives

- **GIVEN** the CI matrix selects Qt 6.6.3
- **WHEN** the workflow installs Qt
- **THEN** it SHALL NOT request a non-existent `qtstatemachine` module archive
- **AND** it SHALL request the valid `qtscxml` module archive
- **AND** the installed Qt package SHALL provide `Qt::StateMachine` for CMake configuration

#### Scenario: Supported CMake path remains verified

- **GIVEN** Qt installation succeeds
- **WHEN** the CI workflow continues
- **THEN** CMake configure, build, CTest, install, and installed consumer build SHALL remain part of the workflow

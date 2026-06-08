## Requirements

### Requirement: Supported Build System

The project SHALL treat CMake as the supported source of truth for build, package, install, test, and downstream integration behavior.

qmake MAY remain in the repository for legacy local experimentation, but qmake MUST NOT be part of the supported package or CI contract unless a dedicated validation path is added.

#### Scenario: Consumers use the supported integration path

- **GIVEN** a downstream CMake project wants to consume the library
- **WHEN** it configures against an installed package prefix
- **THEN** it SHALL use `find_package(QtMaterialWidgets CONFIG REQUIRED)`
- **AND** it SHALL link `QtMaterialWidgets::Widgets`

### Requirement: Supported Qt Version

The supported CMake package path SHALL target Qt 6.

The project MUST NOT claim Qt 5 support unless Qt 5 is included in the automated CI contract.

#### Scenario: Qt support is declared

- **GIVEN** the project declares supported Qt versions
- **WHEN** CI is evaluated
- **THEN** every declared supported Qt major version SHALL have an automated build verification path

### Requirement: GitHub Actions CMake CI

The GitHub Actions CI workflow SHALL validate the supported CMake delivery path on Windows, Ubuntu, and macOS using Qt 6.

The default CI build SHALL configure with:

- `QTMATERIALWIDGETS_BUILD_EXAMPLES=ON`
- `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK=OFF`
- `BUILD_TESTING=ON`

The CI workflow MUST install the Qt `qtscxml` archive because it provides the `Qt6StateMachine` CMake package required by the library.

The default CI build MUST run:

- CMake configure
- CMake build
- CTest execution
- examples target build
- CMake install
- installed-package consumer configure through `CMAKE_PREFIX_PATH`
- installed-package consumer build

At least one Linux CI path MUST run the installed-package consumer executable with `QT_QPA_PLATFORM=offscreen`.

#### Scenario: Supported platforms are verified

- **GIVEN** the project declares Windows, Linux, and macOS desktop support
- **WHEN** CI runs
- **THEN** Windows, Ubuntu, and macOS jobs SHALL validate the CMake package path

#### Scenario: Installed consumer runs on Linux

- **GIVEN** the package is installed by CI on Linux
- **WHEN** the consumer project is configured and built against the installed prefix
- **THEN** the consumer executable SHALL run successfully with `QT_QPA_PLATFORM=offscreen`

### Requirement: Minimal Dependency Configuration

The CI workflow SHALL include a minimal CMake configuration that disables examples and tests.

The minimal configuration MUST verify that the library can build and install without forcing example or test targets into the dependency build.

The minimal configuration MUST verify that an installed-package consumer can still configure and build against the minimal installation.

The minimal configuration MUST install the same Qt archives required by the library, including `qtscxml`.

#### Scenario: Library dependency build remains minimal

- **GIVEN** the project is configured with `QTMATERIALWIDGETS_BUILD_EXAMPLES=OFF` and `BUILD_TESTING=OFF`
- **WHEN** the project builds and installs
- **THEN** example targets SHALL NOT be registered
- **AND** test targets SHALL NOT be registered
- **AND** the installed-package consumer SHALL still configure and build

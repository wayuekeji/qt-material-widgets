## ADDED Requirements

### Requirement: macOS CI Coverage

The GitHub Actions CI workflow SHALL include a macOS job for the supported CMake package path while the project declares macOS as a target platform.

The macOS job MUST install all Qt archives required by the library, including `qtscxml` for `Qt6StateMachine`.

The macOS job MUST run only when the workflow is manually triggered.

#### Scenario: macOS package path is verified

- **GIVEN** the project declares macOS desktop support
- **WHEN** CI is manually triggered
- **THEN** a macOS job SHALL configure, build, test, install, and build the installed-package consumer

### Requirement: Windows Compiler ABI

The GitHub Actions CI workflow SHALL configure Windows CMake builds in an MSVC compiler environment when using the `win64_msvc2019_64` Qt archive.

#### Scenario: Windows build does not mix MinGW with MSVC Qt

- **GIVEN** Windows CI installs Qt with `arch: win64_msvc2019_64`
- **WHEN** CMake configures with the Ninja generator
- **THEN** CMake SHALL detect an MSVC compiler
- **AND** linking SHALL NOT use MinGW `ld` against MSVC Qt libraries

### Requirement: Minimal CMake Configuration CI

The GitHub Actions CI workflow SHALL include a minimal dependency-build job with examples and tests disabled.

The minimal dependency-build job MUST install `qtscxml` so CMake can resolve `Qt6StateMachine`.

The minimal dependency-build job MUST run only when the workflow is manually triggered.

#### Scenario: Examples and tests are not forced into dependency builds

- **GIVEN** the project is configured with `QTMATERIALWIDGETS_BUILD_EXAMPLES=OFF` and `BUILD_TESTING=OFF`
- **WHEN** the manually triggered minimal CI job builds the project
- **THEN** the library SHALL build successfully
- **AND** examples SHALL NOT be registered as build targets
- **AND** tests SHALL NOT be registered as build targets
- **AND** an installed-package consumer SHALL configure and build successfully

### Requirement: Installed Consumer Runtime Smoke

The GitHub Actions CI workflow SHALL run the installed-package consumer executable on Linux using the offscreen Qt platform.

The Linux consumer runtime smoke MUST run only when the workflow is manually triggered.

#### Scenario: Installed consumer starts on Linux

- **GIVEN** Linux CI has installed the package and built the consumer
- **WHEN** manually triggered Linux CI runs the consumer executable with `QT_QPA_PLATFORM=offscreen`
- **THEN** the process SHALL exit successfully

## MODIFIED Requirements

### Requirement: Supported Qt Version

The supported CMake package path SHALL target Qt 6.

The project MUST NOT advertise Qt 5 support unless Qt 5 is added to the automated CI contract.

#### Scenario: Qt version support is enforceable

- **GIVEN** the CMake package path is configured in CI
- **WHEN** Qt is discovered
- **THEN** CI SHALL use Qt 6
- **AND** CMake files SHALL NOT preserve an unverified Qt5 support branch as part of the supported path

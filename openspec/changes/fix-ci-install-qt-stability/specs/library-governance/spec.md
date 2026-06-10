## MODIFIED Requirements

### Requirement: GitHub Actions CMake CI

The GitHub Actions CI workflow SHALL validate the supported CMake delivery path on Windows, Ubuntu, and macOS using Qt 6.

Push and pull-request CI MUST run the Windows CMake package path automatically.

Ubuntu and macOS CMake package path jobs MUST run only when the workflow is manually triggered.

The default CI build SHALL configure with:

- `QTMATERIALWIDGETS_BUILD_EXAMPLES=ON`
- `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK=OFF`
- `BUILD_TESTING=ON`

The CI workflow MUST install the Qt `qtscxml` archive because it provides the `Qt6StateMachine` CMake package required by the library.

The CI workflow MUST NOT depend on `install-qt-action` cache entries for correctness.

The Windows CI workflow MUST enter an MSVC compiler environment before installing or configuring the `win64_msvc2019_64` Qt archive.

The default CI build MUST run:

- CMake configure
- CMake build
- CTest execution
- examples target build
- CMake install
- installed-package consumer configure through `CMAKE_PREFIX_PATH`
- installed-package consumer build

At least one manually triggered Linux CI path MUST run the installed-package consumer executable with `QT_QPA_PLATFORM=offscreen`.

#### Scenario: Supported platforms are verified

- **GIVEN** the project declares Windows, Linux, and macOS desktop support
- **WHEN** push or pull-request CI runs
- **THEN** the Windows job SHALL validate the CMake package path

#### Scenario: Manual CI validates extended platforms

- **GIVEN** the project declares Windows, Linux, and macOS desktop support
- **WHEN** the CI workflow is manually triggered
- **THEN** Windows, Ubuntu, and macOS jobs SHALL validate the CMake package path

#### Scenario: Windows Qt ABI matches compiler

- **GIVEN** Windows CI installs the `win64_msvc2019_64` Qt archive
- **WHEN** the Qt archive is installed and CMake configures with Ninja
- **THEN** the compiler environment SHALL expose MSVC `cl`
- **AND** the build SHALL NOT use MinGW `g++` or `ld` against MSVC Qt libraries

#### Scenario: Qt installation does not depend on stale cache

- **GIVEN** CI installs Qt through `jurplel/install-qt-action`
- **WHEN** the workflow is evaluated
- **THEN** Qt installation SHALL NOT require an Actions cache hit to succeed

#### Scenario: Installed consumer runs on Linux

- **GIVEN** the package is installed by CI on Linux
- **WHEN** the consumer project is configured and built against the installed prefix
- **THEN** the consumer executable SHALL run successfully with `QT_QPA_PLATFORM=offscreen`

### Requirement: GitHub Release Automation

The project SHALL provide a manually triggered GitHub Actions workflow that publishes GitHub Releases for the supported CMake package path.

The release workflow MUST accept an explicit version input and derive a release tag from that input.

The release workflow MUST reject malformed release versions.

The release workflow MUST NOT overwrite an existing git tag or GitHub Release.

The release workflow MUST NOT depend on `install-qt-action` cache entries for correctness.

The Windows release package job MUST enter an MSVC compiler environment before installing or configuring the `win64_msvc2019_64` Qt archive.

#### Scenario: Manual release creates a tagged GitHub Release

- **GIVEN** a maintainer starts the release workflow with version `1.2.3`
- **WHEN** all release build jobs pass
- **THEN** the workflow SHALL create tag `v1.2.3`
- **AND** it SHALL create a GitHub Release named `v1.2.3`
- **AND** it SHALL upload every platform package produced by the workflow

#### Scenario: Existing release is protected

- **GIVEN** tag `v1.2.3` or release `v1.2.3` already exists
- **WHEN** a maintainer starts the release workflow with version `1.2.3`
- **THEN** the workflow MUST fail before creating or uploading release assets

#### Scenario: Release Qt installation does not depend on stale cache

- **GIVEN** a release package job installs Qt through `jurplel/install-qt-action`
- **WHEN** the workflow is evaluated
- **THEN** Qt installation SHALL NOT require an Actions cache hit to succeed

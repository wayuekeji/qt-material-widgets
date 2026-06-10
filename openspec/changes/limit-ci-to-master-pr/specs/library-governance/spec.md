## MODIFIED Requirements

### Requirement: GitHub Actions CMake CI

The GitHub Actions CI workflow SHALL validate the supported CMake delivery path on Windows using Qt 6.

The CI workflow MUST trigger only for `pull_request` events targeting the `master` branch.

The CI workflow MUST NOT trigger for direct pushes, pull requests targeting non-`master` branches, or manual `workflow_dispatch` events.

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

#### Scenario: Pull request to master runs CI

- **GIVEN** a pull request targets `master`
- **WHEN** GitHub evaluates `.github/workflows/ci.yml`
- **THEN** the CI workflow SHALL run
- **AND** the Windows job SHALL validate the CMake package path

#### Scenario: Non-master events do not run CI

- **GIVEN** an event is a direct push, manual dispatch, or pull request targeting a branch other than `master`
- **WHEN** GitHub evaluates `.github/workflows/ci.yml`
- **THEN** the CI workflow SHALL NOT run

#### Scenario: Windows Qt ABI matches compiler

- **GIVEN** Windows CI installs the `win64_msvc2019_64` Qt archive
- **WHEN** the Qt archive is installed and CMake configures with Ninja
- **THEN** the compiler environment SHALL expose MSVC `cl`
- **AND** the build SHALL NOT use MinGW `g++` or `ld` against MSVC Qt libraries

#### Scenario: Qt installation does not depend on stale cache

- **GIVEN** CI installs Qt through `jurplel/install-qt-action`
- **WHEN** the workflow is evaluated
- **THEN** Qt installation SHALL NOT require an Actions cache hit to succeed

### Requirement: Minimal Dependency Configuration

Minimal dependency configuration validation MUST NOT be part of `.github/workflows/ci.yml` under the pull-request-only trigger policy.

A future workflow MAY reintroduce minimal dependency validation if it has an explicit trigger contract.

#### Scenario: CI does not expose unreachable minimal jobs

- **GIVEN** `.github/workflows/ci.yml` is limited to pull requests targeting `master`
- **WHEN** the workflow is inspected
- **THEN** it SHALL NOT contain jobs that can only run on `workflow_dispatch`

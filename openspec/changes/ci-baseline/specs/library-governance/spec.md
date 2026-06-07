## ADDED Requirements

### Requirement: Supported CMake CI Baseline

The project SHALL provide an automated CI workflow for the supported CMake build and package path.

#### Scenario: Release build is validated on supported CI hosts

- **GIVEN** a pull request or push runs repository CI
- **WHEN** the CI workflow executes
- **THEN** it MUST configure and build the project in Release mode on Windows and Linux
- **AND** it MUST use the supported CMake path
- **AND** it MUST not require qmake.

#### Scenario: Tests are part of CI

- **GIVEN** the project is configured with standard CMake testing enabled
- **WHEN** CI completes the build
- **THEN** it MUST run `ctest --output-on-failure`
- **AND** test failure MUST fail the CI job.

#### Scenario: Package consumption is validated after install

- **GIVEN** CI has built the library
- **WHEN** CI installs the package to a local prefix
- **THEN** it MUST configure and build the downstream consumer example using `CMAKE_PREFIX_PATH`
- **AND** the consumer MUST link through `QtMaterialWidgets::Widgets`
- **AND** the consumer MUST not link directly to build-tree artifacts.

#### Scenario: Example application remains buildable

- **GIVEN** examples are enabled in CI
- **WHEN** CI builds the repository
- **THEN** the example application target MUST compile successfully.

### Requirement: CI Governance Documentation

The project SHALL document the CI baseline as a durable architecture decision and current verification gate.

#### Scenario: Maintainer checks verification expectations

- **GIVEN** a maintainer reads project context or ADR documents
- **WHEN** they inspect verification gates
- **THEN** the CI baseline MUST be listed alongside local OpenSpec, CMake, install, consumer, and CTest gates.

## ADDED Requirements

### Requirement: CMake Is The Supported Build Interface

Project documentation SHALL identify CMake as the supported build, package, and downstream integration interface.

#### Scenario: Downstream user reads integration docs

- **GIVEN** a downstream user wants to consume the library
- **WHEN** they read the README
- **THEN** the documented supported integration path SHALL use `find_package(QtMaterialWidgets CONFIG REQUIRED)`
- **AND** link `QtMaterialWidgets::Widgets`

### Requirement: qmake Is Legacy

Project documentation MUST describe qmake as legacy and unverified, not as a supported package interface.

#### Scenario: User looks for qmake support

- **GIVEN** a user searches the README for qmake
- **WHEN** they find the qmake section
- **THEN** it SHALL state that qmake is legacy and not covered by the verified support contract

### Requirement: qmake Policy ADR

The repository SHALL contain an ADR recording the qmake support decision.

#### Scenario: Maintainer checks build-system policy

- **GIVEN** a maintainer needs the qmake support decision
- **WHEN** they inspect `docs/adr`
- **THEN** an ADR SHALL explain that CMake is the source of truth and qmake is legacy

### Requirement: qmake Language Baseline

Existing qmake files MUST NOT advertise an older C++ standard than the project baseline.

#### Scenario: qmake file declares C++ standard

- **GIVEN** a `.pro` file declares a C++ standard
- **WHEN** the declaration is inspected
- **THEN** it SHALL use `c++17`

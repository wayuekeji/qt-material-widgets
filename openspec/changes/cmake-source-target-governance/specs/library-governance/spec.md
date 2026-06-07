## ADDED Requirements

### Requirement: Explicit CMake Source Lists

The CMake build MUST declare component and example source inputs explicitly instead of using directory-wide `file(GLOB)` collection.

#### Scenario: Source addition is review-visible

- **GIVEN** a new C++ source file is added under `components` or `examples`
- **WHEN** it must be built by the CMake target
- **THEN** a source-list file SHALL require an explicit edit

### Requirement: Stable Export Target

The package export target SHALL remain `QtMaterialWidgets::Widgets`.

#### Scenario: Consumer links installed package

- **GIVEN** the package has been installed
- **WHEN** a downstream CMake consumer calls `find_package(QtMaterialWidgets CONFIG REQUIRED)`
- **THEN** it SHALL link against `QtMaterialWidgets::Widgets`

### Requirement: Package-Named Binary Artifact

The CMake-built shared library artifact SHALL use the package name `QtMaterialWidgets`.

#### Scenario: Library artifact is generated

- **GIVEN** the CMake library target is built
- **WHEN** the build emits the shared library artifact
- **THEN** the artifact basename SHALL be `QtMaterialWidgets`

### Requirement: qmake Policy Boundary

This change MUST NOT rewrite qmake source lists.

#### Scenario: qmake remains legacy

- **GIVEN** qmake files exist in the repository
- **WHEN** this change is applied
- **THEN** qmake source-list policy SHALL remain deferred to a dedicated qmake support change

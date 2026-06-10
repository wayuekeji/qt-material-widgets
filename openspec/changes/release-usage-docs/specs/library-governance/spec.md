## ADDED Requirements

### Requirement: Release Usage Documentation

The project SHALL provide English documentation for consuming GitHub Release assets.

The release usage documentation MUST describe release assets as platform-specific CMake install prefixes.

The release usage documentation MUST show downstream CMake consumption through `CMAKE_PREFIX_PATH`, `find_package(QtMaterialWidgets CONFIG REQUIRED)`, and `QtMaterialWidgets::Widgets`.

The release usage documentation MUST state that release assets do not bundle the Qt runtime for downstream applications.

The README MUST link to the release usage documentation from the supported CMake package usage area.

#### Scenario: User consumes a release archive

- **GIVEN** a user downloads a release archive for their platform
- **WHEN** they read the release usage documentation
- **THEN** they SHALL know which directory to pass to `CMAKE_PREFIX_PATH`
- **AND** they SHALL know which CMake package and target to use
- **AND** they SHALL understand that Qt runtime deployment is their application responsibility

#### Scenario: README exposes release instructions

- **GIVEN** a user reads the README usage section
- **WHEN** they want to consume prebuilt release artifacts
- **THEN** the README SHALL link to the release usage documentation

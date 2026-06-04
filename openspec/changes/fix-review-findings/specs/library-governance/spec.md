# Delta Spec

## ADDED Requirements

### Requirement: Example targets must not leak into downstream consumers by default

The project MUST keep example application targets disabled by default when the repository is consumed as a subproject.

#### Scenario: Top-level build keeps example defaults

- GIVEN the repository is configured as the top-level project
- WHEN no explicit example option override is provided
- THEN the build SHALL enable examples by default

#### Scenario: Subproject consumption isolates examples

- GIVEN the repository is configured through `add_subdirectory(...)` or `FetchContent`
- WHEN no explicit example option override is provided
- THEN the build MUST NOT create example targets by default

### Requirement: Internal static implementation targets must be safe for shared-library linkage

Any internal static target that is linked into an exported shared library MUST be configured for position independent code on toolchains that require it.

#### Scenario: Core target links into exported shared library

- GIVEN `QtMaterialWidgetsCore` is linked into `QtMaterialWidgets`
- WHEN the project is built on Linux or macOS
- THEN the shared library link step SHALL succeed without requiring downstream patches

# ADR 0001: qmake Support Policy

## Status

Accepted

## Context

The repository still contains qmake `.pro` files, but the verified delivery path is CMake:

- `QtMaterialWidgets::Widgets` is exported through the CMake package.
- Install and downstream consumption are validated through `find_package(QtMaterialWidgets CONFIG REQUIRED)`.
- Resource-pack selection is implemented as a CMake option.
- Source-list governance is implemented in CMake source lists.
- The test baseline is exposed through CTest.

qmake does not currently cover those contracts.

## Decision

CMake is the source of truth for build, package, install, tests, and downstream integration.

qmake is legacy and unverified. `.pro` files may remain for local source-tree experimentation, but they are not a supported package or consumer integration interface.

## Consequences

- Public documentation must route supported users to CMake.
- qmake must not be described as co-equal with CMake.
- Future qmake work requires a dedicated validation path before support can be upgraded.
- Existing qmake files should not advertise an older C++ standard than the project baseline.

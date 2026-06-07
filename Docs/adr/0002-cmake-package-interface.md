# ADR 0002: CMake Package Interface

## Status

Accepted

## Context

The library must be consumable by downstream CMake projects without manually wiring include directories or platform-specific library paths.

The verified consumer path installs the package and then uses `find_package(QtMaterialWidgets CONFIG REQUIRED)`.

## Decision

The supported package Interface is the exported CMake target:

```cmake
QtMaterialWidgets::Widgets
```

Downstream consumers should link that target instead of linking a raw `.lib`, `.dll`, `.so`, or build-directory artifact.

## Consequences

- Package docs must prefer `find_package` and `QtMaterialWidgets::Widgets`.
- Build output may change as long as the exported target remains stable.
- Consumer smoke tests must continue to validate installed-package usage.

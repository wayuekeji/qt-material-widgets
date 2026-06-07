# ADR 0004: Resource Pack Split

## Status

Accepted

## Context

The original resource file embedded the full Material icon catalog into the default library. Stable widgets require only a small subset of fonts and icons.

## Decision

Resources are split into:

- `resources_core.qrc`: default fonts and required core/demo icons.
- `resources_full_icons.qrc`: optional full Material icon catalog.

The full icon pack is enabled with:

```cmake
QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK=ON
```

Resources are compiled into the final `QtMaterialWidgets` shared library so qrc paths are available to consumers at runtime.

## Consequences

- Default builds are smaller.
- Consumers using arbitrary `QtMaterialTheme::icon(category, icon)` entries must enable the full icon pack.
- Resource availability must be covered by tests.

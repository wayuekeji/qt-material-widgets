# Resource Pack Splitting

## Motivation

The core library currently embeds the full Material icon catalog through `components/resources.qrc`. The resource file contains hundreds of SVG entries while stable widgets only require a small fixed subset at runtime.

This increases the default binary footprint and makes resource loading an all-or-nothing behavior.

## Scope

- Split required runtime resources from the optional full Material icon pack.
- Add a CMake option to include the full icon pack only when requested.
- Keep stable widgets functional with the default resource pack.
- Document the resource-pack policy for downstream consumers.

## Non-Goals

- No icon registry redesign.
- No public icon API removal.
- No qmake resource policy change in this slice.
- No changes to widget behavior outside resource availability.

## Design

The build will use two qrc files:

- `resources_core.qrc`: Roboto fonts and the small icon subset required by stable widgets and current demo smoke usage.
- `resources_full_icons.qrc`: the remaining Material icon catalog.

`QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK` controls whether the optional icon qrc is linked into `QtMaterialWidgetsCore`.

Default behavior is conservative for package size: the full icon pack is disabled unless explicitly enabled.

## Decisions

- The core resource pack includes fonts, checkbox icons, radio button icons, the combobox arrow used by source-level experimental builds, and the demo icons currently used by examples.
- The original `resources.qrc` remains in the repository as a legacy aggregate source, but CMake no longer uses it.
- Missing non-core icons remain observable through existing `QIcon` behavior; fail-fast icon registry work is deferred to a later Theme/Icon change.

## Risks

- Consumers that depended on arbitrary `QtMaterialTheme::icon(category, icon)` entries from the default build must enable `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK`.
- qmake still references the legacy aggregate resource file. That path is not updated in this change.

No blocking risk was detected.

# CMake Source Target Governance

## Motivation

The CMake build still relies on directory-wide `file(GLOB)` collection for library and examples sources. This hides source additions from review and makes generated build inputs depend on the current filesystem rather than explicit project intent.

The shared library target is exported as `QtMaterialWidgets::Widgets`, but its output artifact is still named `components`, which keeps an implementation-era name in the delivery surface.

## Scope

- Replace CMake source/header `file(GLOB)` usage in `components` and `examples` with explicit source-list files.
- Keep resource-pack selection controlled by the existing qrc option.
- Rename the CMake-built shared library output from `components` to `QtMaterialWidgets`.
- Keep the exported consumer target `QtMaterialWidgets::Widgets`.

## Non-Goals

- No qmake source-list rewrite.
- No source file movement.
- No public C++ API change.
- No include-directory migration from `qmetarial`.

## Design

Add source-list include files:

- `components/sources.cmake`
- `examples/sources.cmake`

Each file defines named lists for implementation sources, private headers, public headers, and UI files. `CMakeLists.txt` files consume those lists directly.

The public export target remains `QtMaterialWidgets::Widgets`, while the installed binary artifact uses the package name `QtMaterialWidgets`.

## Decisions

- Source-list files are used to keep target declarations readable.
- Installed-header exclusion policy remains unchanged.
- `resources_core.qrc` and `resources_full_icons.qrc` remain selected in `components/CMakeLists.txt` because they are build-option dependent.
- qmake keeps its legacy behavior until the separate qmake support policy change.

## Risks

- New source files now require explicit source-list edits. This is intended and improves reviewability.
- Downstream consumers that manually link `components.lib` or `components.dll` will need to use the supported CMake package target. The documented Interface is `QtMaterialWidgets::Widgets`.

No blocking risk was detected.

# Project Context

## Purpose

`qt-material-widgets` is a Qt Widgets component library that provides Material Design inspired desktop widgets, theme helpers, resources, examples, and package integration.

It is not a business application and not a plugin host.

## Source Of Truth

- Active specifications: `openspec/specs/**/spec.md`
- Active changes: `openspec/changes/<change-name>/`
- Durable architecture decisions: `docs/adr/`
- Public component status: `Docs/ComponentSurface.md`
- Build/package behavior: CMake files

OpenSpec changes track proposed or active behavior changes. ADRs capture accepted architecture decisions that should remain understandable after a change is archived.

## Vocabulary

- Core: internal support library code under `components/materiallib`, including theme, style, ripple, transition, and checkable base behavior.
- Widgets: public Qt widget classes such as `QtMaterialProgress`, `QtMaterialTabs`, and `QtMaterialTextField`.
- Public Header: installed header under `include/qmetarial`.
- Private Header: implementation header under `components`, usually `_p.h` or `_internal.h`.
- Theme: color and style access through `QtMaterialTheme`, `QtMaterialStyle`, and typed `Material::ThemeColor` keys.
- Resource Pack: qrc bundle embedded into `QtMaterialWidgets`, split into a default core pack and an optional full Material icon pack.
- Component Surface: classification of widgets as stable, experimental, stub, or not implemented.
- Demo Page: an example application page registered through `examples/demopageregistry.*`.
- Consumer: downstream project that uses `find_package(QtMaterialWidgets CONFIG REQUIRED)` and links `QtMaterialWidgets::Widgets`.
- CMake Package: installed package config and exported target under `lib/cmake/QtMaterialWidgets`.
- qmake: legacy, unverified source-tree build files. qmake is not the supported package or consumer integration path.
- Test Baseline: CTest/QTest smoke tests enabled through standard `BUILD_TESTING`.

## Architecture Boundaries

- Public package interface is `QtMaterialWidgets::Widgets`.
- CMake is the supported build, package, install, test, and consumer integration path.
- Stable widgets may be installed by default.
- Experimental and stub widgets may remain in source and demos but must not be installed as stable package Interface.
- Resources must be linked into the final shared library so consumers can access qrc paths at runtime.
- Examples are consumers and smoke surfaces; they must not define package behavior.
- Tests verify stable public behavior and resource availability through public headers and exported targets.

## Current Verification Gates

- `openspec validate --all --strict`
- CMake Release build of `QtMaterialWidgets`
- `cmake --install` followed by consumer build using `CMAKE_PREFIX_PATH`
- `ctest --output-on-failure` with `BUILD_TESTING=ON`
- Examples Release build when demo behavior changes
- GitHub Actions CI for Windows/Linux CMake Release build, CTest, examples, install, and consumer build

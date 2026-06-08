# Project Optimization Analysis Report

Date: 2026-06-06

## 1. Analysis Scope

This report is based only on facts inside the repository:

- `openspec/project.md`
- `openspec/changes/**`
- root `CMakeLists.txt`, `components/CMakeLists.txt`, `examples/CMakeLists.txt`
- `qt-material-widgets.pro`, `components/components.pro`, `examples/examples.pro`
- `include/qmetarial/**`
- `components/**`
- `examples/**`
- `Docs/**`

The repository currently lacks the following governance assets:

- No physical `AGENTS.md` found
- No `openspec/specs/**/spec.md` found
- No `CONTEXT.md` found
- No ADR directory found
- No `tests/` found
- No `.github/workflows/` found

The following sections use `Module`, `Interface`, `Implementation`, `Depth`, `Seam`, `Adapter`, `Leverage`, and `Locality` to describe architecture issues.

## 2. Current Baseline

The project is positioned as a Material Design component library for `Qt Widgets`. It already has basic library build capability and has started to add CMake package export support:

- The root build controls example builds through `QTMATERIALWIDGETS_BUILD_EXAMPLES`.
- `components/CMakeLists.txt` creates the `QtMaterialWidgets::Widgets` alias.
- `install(TARGETS)`, `install(EXPORT)`, `QtMaterialWidgetsConfig.cmake.in`, and version file generation already exist.
- The example CMake build links the library through `QtMaterialWidgets::Widgets`.

Validation results from this pass:

- `cmake -S . -B %TEMP%/qt-material-widgets-codex-report-build -DQTMATERIALWIDGETS_BUILD_EXAMPLES=OFF` passed.
- `cmake --build %TEMP%/qt-material-widgets-codex-report-build --config Release --target QtMaterialWidgets` passed.
- `cmake -S . -B %TEMP%/qt-material-widgets-codex-report-build-examples -DQTMATERIALWIDGETS_BUILD_EXAMPLES=ON` passed.
- `cmake --build %TEMP%/qt-material-widgets-codex-report-build-examples --config Release --target examples` passed.
- The build emitted an `MSB8029` temporary-directory warning and a `pwsh.exe` environment notice, but the target artifacts were generated successfully.

## 3. Priority Roadmap

| Priority | Optimization Area | Goal |
| --- | --- | --- |
| P0 | Consumer documentation and package validation loop | Allow external projects to consume the library through standard mechanisms |
| P0 | Public Interface defect governance | Fix incorrect properties, naming debt, and exposed shell headers |
| P0 | Stable/experimental Module classification | Prevent immature widgets from polluting the stable Interface |
| P1 | Theme/Icon/Resource Module deepening | Improve Locality and Leverage for theme and resource access |
| P1 | Example-layer Module consolidation | Reduce duplicated settings editors and hand-written registration |
| P1 | CMake source list and target governance | Reduce implicit build behavior |
| P2 | Test and CI baseline | Establish regression validation |
| P2 | Documentation and OpenSpec governance | Keep specifications, documentation, and implementation aligned |
| P2 | qmake support policy | Downgrade support or add a validation loop |

## 4. Optimization Points

### P0-01: Consumer Documentation and Package Validation Loop Are Inconsistent

Issue:

The project already has the outline of a standard CMake package, but README and older Docs still present manually specified include directories and `.lib/.so` paths as the primary consumption path. The Interface seen by consumers does not match the actual recommended path.

Evidence:

- `components/CMakeLists.txt` already contains `QtMaterialWidgets::Widgets`, `install(EXPORT)`, and `QtMaterialWidgetsConfig.cmake` generation.
- `cmake/QtMaterialWidgetsConfig.cmake.in` already contains `find_dependency(Qt...)` and target import logic.
- `README.md` still shows `target_include_directories(... /path/to/dynamic-lib/include/)` and direct linking to `components.lib/components.so`.
- `Docs/TODO.md` still records the old question about how to use the project as a static or dynamic library.

Recommended path:

1. Change the main README path to `find_package(QtMaterialWidgets CONFIG REQUIRED)` plus `target_link_libraries(... QtMaterialWidgets::Widgets)`.
2. Add a minimal consumer example project that verifies consumption after installation.
3. Downgrade direct `.lib/.so` linking documentation to historical notes or remove it.
4. Add an installed-package `find_package` smoke test to CI.

Validation method:

- Run `cmake --install` into a temporary prefix.
- Create a minimal Qt Widgets consumer.
- Find and link `QtMaterialWidgets::Widgets` only through `CMAKE_PREFIX_PATH`.
- Verify the consumer builds without manually adding library file paths.

### P0-02: The Public Interface Contains Clear Defects

Issue:

Public headers do not directly include `_p.h` or `_internal.h`, but the stable Interface still contains an incorrect property declaration, naming debt, a generic export macro, and shell headers. These are all forms of stable Interface pollution.

Evidence:

- `include/qmetarial/qtmaterialprogress.h`: the `backgroundColor` `WRITE` accessor is incorrectly set to `setProgressColor`; it should be `setBackgroundColor`.
- `include/qmetarial/qtmaterialpaper.h`, `qtmaterialtable.h`, `qtmateriallist.h`, and `qtmateriallistitem.h` contain only include guards, and the current CMake install phase explicitly excludes those headers.
- The public include directory is named `include/qmetarial`; `openspec/project.md` already records this spelling error.
- The export macro is `COMPONENTS_EXPORT`, which does not match the package name `QtMaterialWidgets`.

Recommended path:

1. Fix the `QtMaterialProgress::backgroundColor` property writer immediately.
2. Establish a public-header audit list: stable, experimental, removed, and internal.
3. Remove shell headers from the stable Interface or move them into an experimental area.
4. Plan the migration from `qmetarial` to the correct include namespace.
5. Converge `COMPONENTS_EXPORT` into a package-semantic export macro.

Validation method:

- Run independent compile tests for public headers.
- Use Qt meta-object checks to verify that writing `backgroundColor` calls `setBackgroundColor`.
- After installation, include only public headers and avoid any dependency on private headers under `components/`.

### P0-03: Stable and Experimental Modules Are Not Classified

Issue:

Some widgets have entered public headers and examples while their Implementation is still shell-like or experimental. The current Interface makes consumers believe they are stable.

Evidence:

- `QtMaterialMenu` exposes a public class with only construction and destruction, while the Implementation is mostly empty.
- `QtMaterialSteps` declares a known layout defect directly in its public header and contains a TODO.
- `QtMaterialSteps` Implementation uses file-level `static int currentWidth`, creating cross-instance state pollution risk.
- `QtMaterialComboBox::paintEvent` calls `setItemDelegate(new QtMaterialComboBoxDelegate(this))` on every paint, which is not suitable behavior for a stable Interface.

Recommended path:

1. Assign a status label to each widget: stable, experimental, stub, or removed.
2. Install only stable widgets and list only stable widgets as implemented in README.
3. Keep experimental widgets in source and examples, but do not expose them as stable package Interface.
4. Delete or complete stub classes first; they must not remain public consumption entry points.

Validation method:

- Installed public headers match the README implemented-widget list.
- Experimental and stub widgets are not installed by default.
- Stable widgets pass minimal construction, property setting, and paint smoke tests.

### P1-01: Theme/Icon/Resource Module Is Too Shallow

Issue:

Theme colors, icon paths, and font registration are concentrated in `QtMaterialTheme` and `QtMaterialStyle`, but the Interface requires callers to understand string keys, a large enum set, and resource path conventions. The Module lacks Depth and has low Leverage; errors also lack strong constraints.

Evidence:

- `include/qmetarial/lib/qtmaterialtheme.h` is about 301 lines and contains many color enums.
- `QtMaterialThemePrivate` stores colors in `QHash<QString, QColor>`.
- `QtMaterialTheme::getColor` only calls `qWarning()` and returns an invalid `QColor()` when a key is missing.
- `QtMaterialTheme::icon(QString category, QString icon)` builds `:/icons/icons/.../ic_..._24px.svg` through string concatenation.
- `QtMaterialStylePrivate::init` implicitly registers the Roboto font and creates the default theme.

Recommended path:

1. Separate theme tokens, color tables, and icon indexes from hand-written business logic into a resource registry.
2. Build a verifiable Interface for theme keys and icon keys, reducing arbitrary string calls.
3. Change missing resources to fail-fast behavior or explicit error objects instead of silently returning invalid colors.
4. Keep the `QtMaterialStyle` Interface small and stable, leaving resource loading details in the Implementation.

Validation method:

- Unit tests cover known theme tokens, missing tokens, known icons, and missing icons.
- Startup validates resource registry completeness.
- Updating one resource mapping does not require editing multiple widget call sites.

### P1-02: Resource Package Size and Loading Strategy Lack Layering

Issue:

The core library currently embeds a large number of icons and fonts unconditionally. The resource Interface is effectively "bundle everything into the library". This gives little Leverage to consumers that use only a small subset of widgets and cannot support on-demand trimming.

Evidence:

- `components/resources.qrc` contains 967 `<file>` entries.
- 961 entries are icons and 6 entries are Roboto font files.
- `QtMaterialTheme::icon` depends on all these resources being present.

Recommended path:

1. Split base font resources, core widget icon resources, and the full Material icon pack.
2. Create optional CMake options or independent resource targets for resource packs.
3. Include only resources required by core widgets in the default package, and enable the full icon pack on demand.
4. Provide tests and diagnostics for missing resources.

Validation method:

- Default build and full-resource build artifact sizes can be compared.
- All stable widgets run with the default resource package.
- Non-core icons from the full icon pack succeed only when the corresponding package is enabled.

### P1-03: The Example Layer Has High Duplication and Low Validation Value

Issue:

The example layer is necessary as a consumer, but each widget currently maintains its own settings editor, layout construction, `setupForm`, color selection, and signal connections. This layer is a shallow Module with duplicated Implementation scattered across the tree; adding widgets will continue copying the same pattern.

Evidence:

- `examples/` contains 25 headers, 26 cpp files, and 20 `.ui` files.
- Most `*settingseditor.cpp` files repeat creation of settings widgets, canvas widgets, layouts, `setupForm`, and `updateWidget`.
- `examples/mainwindow.cpp` manually includes headers, manually instantiates pages, and manually registers pages through `QMap<QString, QWidget*>`.
- `tabssettingseditor.cpp` uses a string-form `SLOT([](int a) { ... })`, which can compile but is not a valid Qt slot design.

Recommended path:

1. Extract an example page registry so adding an example only declares its name and construction logic.
2. Extract a settings-page skeleton Module to centralize the settings/canvas layout.
3. Unify repeated color selection, disabled-state toggling, theme switching, and similar operations.
4. Elevate examples from "manual demo" to smoke-test carriers.

Validation method:

- Adding one example page does not require modifying multiple includes and instantiations in `MainWindow`.
- Stable widget examples can be constructed in batch.
- Example startup smoke tests cover page registry completeness.

### P1-04: CMake Source Lists and Target Semantics Still Have Implicit Behavior

Issue:

The CMake package has started to take shape, but source collection and target naming still carry historical behavior. The current Interface is `QtMaterialWidgets::Widgets`, but the artifact name is still `components`, and internal source files are auto-collected through `file(GLOB)`, reducing build predictability.

Evidence:

- `components/CMakeLists.txt` uses `file(GLOB THELIB "materiallib/*")`, `file(GLOB COMPONENTSHEADER "*.h")`, and `file(GLOB COMPONENTSSOURCE "*.cpp")`.
- `examples/CMakeLists.txt` also uses `file(GLOB HEADER "*.h")`, `file(GLOB RSOURCE "*.cpp")`, and `file(GLOB UI "*.ui")`.
- `set_target_properties(... OUTPUT_NAME components)` does not match the package name `QtMaterialWidgets`.
- The `components` subdirectory calls `project(components)` itself, so target semantics and package semantics are not fully aligned.

Recommended path:

1. Replace `file(GLOB)` without `CONFIGURE_DEPENDS` with explicit `target_sources`.
2. Unify target, output artifact, and export naming strategy.
3. Clearly mark internal Core targets as private Implementation targets.
4. Give the example target a clearer name, such as demo or examples app.

Validation method:

- Adding or removing source files is reflected explicitly in the CMake diff.
- Installed exported targets do not expose private Implementation targets.
- Downstream consumers only see `QtMaterialWidgets::Widgets`.

### P2-01: Tests and CI Are Missing

Issue:

The library can build, but there is no automated validation for Interface behavior, resource availability, package consumption, or example startup. Without CI, the declared support for Qt5/Qt6 and Windows/Linux cannot remain trustworthy.

Evidence:

- No `tests/` directory found.
- No `.github/workflows/` found.
- No `enable_testing`, `add_test`, or `QTest` found.
- `openspec/project.md` already records missing automated tests and missing CI.

Recommended path:

1. Establish `tests/`, first covering `QtMaterialProgress`, `QtMaterialTheme`, `QtMaterialStyle`, and resource loading.
2. Add a CMake package consumer test.
3. Add an example construction smoke test.
4. Establish a Windows/Linux plus Qt5/Qt6 build matrix.

Validation method:

- `ctest --output-on-failure` can run.
- CI covers at least Release build, installation, and consumer compilation.
- Every P0 Interface fix has a regression test.

### P2-02: Documentation and OpenSpec Governance Are Not Closed

Issue:

Project documents exist, but their status is scattered, and there is no effective spec directory. OpenSpec changes already contain a roadmap, but there is no archived `openspec/specs/**/spec.md` as the long-term source of truth.

Evidence:

- `Docs/API.md` contains mostly empty sections.
- `Docs/TODO.md` still reflects the old manual-linking problem.
- `Docs/RelatedKnowledge/OpaquePointer.md` and `QStyle.md` are knowledge drafts and have not been converted into project decisions.
- No `openspec/specs/**/spec.md` found.
- No ADR and `CONTEXT.md` found.

Recommended path:

1. Archive completed OpenSpec changes to form active specs.
2. Establish `CONTEXT.md` and define domain terms: Core, Widgets, Examples, Theme, Resource Pack, Demo Page, and related concepts.
3. Establish an ADR directory and record decisions such as qmake support level, include-name migration, and resource-pack splitting.
4. Fill API documentation through generated or semi-automated methods, but public headers must remain the source of truth.

Validation method:

- `openspec/specs/**/spec.md` exists and covers current governance rules.
- README, Docs/API, and OpenSpec use the same consumption path.
- Every major architecture choice has a corresponding ADR decision record.

### P2-03: qmake Support Policy Needs Downgrade or Validation

Issue:

The project claims support for both CMake and qmake, but the qmake path still directly depends on build-directory artifacts, and its configuration remains at `c++11`. This conflicts with the `openspec/project.md` position that CMake is the primary source of truth and C++17 is the technical baseline.

Evidence:

- `qt-material-widgets.pro` still builds `components examples` through `subdirs`.
- `examples/examples.pro` directly links artifacts under `$$top_builddir/components` on Windows and Unix.
- `components/components.pro` uses `CONFIG += c++11`, while the project baseline is C++17.
- README explicitly states that the first qmake build has unusual issues and recommends CMake.

Recommended path:

1. Decide whether qmake is primary support, compatibility support, or historical support.
2. If qmake is retained, add minimal qmake CI and an external consumption example.
3. If qmake is not retained, remove qmake from the README main path and document the downgrade reason in OpenSpec/ADR.
4. Prevent qmake examples from continuing to depend on build-directory details.

Validation method:

- The qmake path has independent build validation.
- qmake examples do not require consumers to manually assemble library artifact paths.
- qmake uses the same C++ version as the CMake main path, or the difference is explicitly documented.

## 5. Suggested Follow-up OpenSpec Split

Recommended follow-up changes, in order:

1. `fix-public-interface-contracts`: fix the `QtMaterialProgress` property, shell headers, and export macro naming.
2. `consumer-package-smoke-test`: add installed-package consumer validation and fix README consumption docs.
3. `stabilize-widget-surface`: establish stable/experimental/stub classification.
4. `theme-resource-module-deepening`: govern the Theme/Icon/Resource Module.
5. `demo-harness-consolidation`: consolidate example page registration and duplicated settings editors.
6. `test-ci-baseline`: add QTest, ctest, and a CI matrix.
7. `qmake-support-policy`: record and execute the qmake support policy.

## 6. Conclusion

The highest-value optimization is not to add more widgets, but to first close the loop around the consumer Interface, stable Module scope, Resource Module, tests, CI, and documentation governance.

The project already has the outline of a CMake package. The next step should move from "buildable" to "installable, consumable, verifiable, and governable". Before the P0 items are complete, expanding the public widget surface is not recommended.

# Proposal: Fix Review Findings In CMake Packaging

## Motivation

The current packaging refactor introduced two regressions:

1. `QtMaterialWidgetsCore` was split into a static library and then linked into a shared library without guaranteeing position independent code on non-Windows toolchains.
2. Example targets are enabled by default even when this repository is consumed as a subproject, which leaks demo build targets into downstream consumers.

These regressions directly affect correctness of cross-platform builds and boundary control of the library package.

## Goals

1. Keep `examples` enabled by default only for top-level builds.
2. Guarantee that the internal Core target can be linked into the exported shared library on Linux and macOS.
3. Preserve the existing `find_package(QtMaterialWidgets CONFIG REQUIRED)` consumption path.

## Non-Goals

1. No broader target restructuring beyond the two review findings.
2. No rename of exported package names or include directories.
3. No changes to qmake support in this patch.

## Design

### 1. Top-level gated examples

Use `PROJECT_IS_TOP_LEVEL` to define the default of `QTMATERIALWIDGETS_BUILD_EXAMPLES`.

Effect:

- Direct repository builds still compile the demo by default.
- `add_subdirectory(...)` and `FetchContent` consumers no longer inherit demo targets unless they opt in explicitly.

### 2. PIC-safe Core target

Keep `QtMaterialWidgetsCore` as a static implementation target, but explicitly enable `POSITION_INDEPENDENT_CODE`.

Effect:

- Non-Windows linkers can safely link Core objects into the exported shared library.
- The current target topology remains intact.

## Decisions

### Decision 1

Do not switch Core to `OBJECT` in this patch.

Reason:

- The review finding is solved by enabling PIC.
- This keeps the change minimal and avoids unnecessary packaging side effects.

### Decision 2

Use top-level detection for example defaults instead of forcing examples off globally.

Reason:

- The repository still benefits from local demo builds during direct development.
- Downstream consumers should not pay that cost implicitly.

## Risks

### Risk 1: Older CMake behavior around `PROJECT_IS_TOP_LEVEL`

- Impact: example default logic depends on modern CMake behavior.
- Mitigation: repository already requires CMake 3.22, where this variable is available.

### Risk 2: Downstream projects relying on implicit example generation

- Impact: consumers that accidentally depended on demo targets will need to opt in.
- Conclusion: acceptable and aligned with package boundary expectations.

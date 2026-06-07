# Test Baseline

## Motivation

The project has no executable test target, no CTest entry point, and no automated regression coverage for public API fixes already made during the optimization work.

A minimal QTest baseline is required before deeper refactoring continues.

## Scope

- Enable standard CTest integration through CMake.
- Add a minimal QTest executable.
- Cover theme typed token access, core resource availability, and `QtMaterialProgress::backgroundColor` meta-object writability.
- Keep the test target focused on stable package behavior.

## Non-Goals

- No CI workflow in this slice.
- No exhaustive widget rendering tests.
- No visual regression harness.
- No qmake test integration.

## Design

The root CMake build will include `CTest`. When `BUILD_TESTING` is enabled, `tests/` is added.

The test executable links `QtMaterialWidgets::Widgets`, `Qt::Widgets`, and `Qt::Test`. On Windows, the built library DLL is copied next to the test executable to keep local CTest execution self-contained.

## Decisions

- Use standard `BUILD_TESTING` rather than a custom test option.
- Start with one smoke executable to keep the baseline fast and stable.
- Use offscreen Qt platform during CTest execution to avoid requiring an interactive desktop.

## Risks

- Qt Test must be available in the local Qt installation when `BUILD_TESTING` is enabled.

No blocking risk was detected.

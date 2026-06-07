# ADR 0006: Test Baseline

## Status

Accepted

## Context

The repository had no executable test target or CTest entry point. Recent package, theme, resource, and public property changes need a regression baseline.

## Decision

The project uses standard CMake `BUILD_TESTING` and CTest.

The initial QTest smoke target verifies:

- typed theme key set/read behavior
- core resource availability
- `QtMaterialProgress::backgroundColor` meta-object writability

## Consequences

- CMake test configuration requires Qt Test.
- Public API and resource regressions have an executable gate.
- Future shared behavior changes should extend the test baseline before broad refactors.

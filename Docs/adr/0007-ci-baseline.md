# ADR 0007: CI Baseline

## Status

Accepted

## Context

The project has a supported CMake package path, a QTest/CTest smoke baseline, an example application, and an installed-package consumer project. These checks were local only, so package export, resource registration, example build, or test regressions could land without automated repository feedback.

qmake remains legacy and unverified. CI must reinforce the supported path instead of expanding the legacy surface.

## Decision

The repository uses GitHub Actions as the initial CI baseline for the supported CMake path.

The CI matrix covers:

- Windows latest runner
- Ubuntu latest runner
- Qt 6.6.3
- Release CMake configure/build
- `ctest --output-on-failure`
- examples target build
- `cmake --install`
- installed-package consumer build through `CMAKE_PREFIX_PATH`

The full icon pack remains disabled in CI by default so the default resource-pack contract is continuously exercised.

## Consequences

- CMake package consumption is verified after installation, not only from the build tree.
- The supported path has automated Windows/Linux coverage.
- qmake remains outside the CI contract until a separate decision promotes or removes it.
- Runtime GUI launch smoke remains a future extension.

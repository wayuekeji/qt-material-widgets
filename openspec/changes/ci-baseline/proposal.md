# CI Baseline

## Motivation

The project now has a CTest smoke baseline, installable CMake package metadata, an example application, and an install-after-build consumer smoke project. These gates are still local only. Without repository CI, regressions in package export, resource registration, tests, or examples can enter the main branch unnoticed.

## Goals

- Add a GitHub Actions CI workflow for the supported CMake path.
- Verify Release library build, CTest smoke tests, examples build, install step, and installed-package consumer build.
- Cover Windows and Linux because the project claims cross-platform Qt Widgets consumption.
- Keep CI aligned with the current qmake policy: qmake remains legacy and unverified.
- Record the CI decision in durable project documentation.

## Non-Goals

- No runtime widget behavior changes.
- No qmake CI enablement.
- No Qt5 matrix until the supported CMake/Qt6 path is stable in CI.
- No release publishing or binary packaging.

## Design

The workflow uses GitHub Actions with a two-OS matrix:

- `windows-latest`
- `ubuntu-latest`

Each job installs Qt 6 through the standard Qt setup action, configures the project with CMake, builds the Release target, runs CTest, builds the examples target, installs the package to a local prefix, and configures/builds `examples/consumer` using only `CMAKE_PREFIX_PATH`.

The workflow intentionally disables the full icon pack by default to exercise the default resource-pack contract.

## Decisions

- CI validates the supported CMake package path only.
- CI uses Qt 6.6.3 as the initial pinned version.
- CI treats examples as build-time smoke coverage, not as a runtime GUI launch gate.
- CI verifies install consumption through `examples/consumer`, not through direct build-tree linking.

## Risks

- External GitHub Actions dependencies may change or have transient availability issues.
- GUI runtime launch smoke is not covered yet.
- Qt5 remains unverified by CI despite historical README references.

No blocking-level risk is detected because this change only adds verification infrastructure and documentation.

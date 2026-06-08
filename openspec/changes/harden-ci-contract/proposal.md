# Harden CI Contract

## Motivation

The project has a CI baseline, but the contract is still underspecified and incomplete:

- `openspec/specs/library-governance/spec.md` does not exist as a long-lived source of truth.
- The project baseline declares macOS as a target platform, but CI only covers Windows and Ubuntu.
- The default CI path builds examples and tests, but there is no minimal dependency-build path.
- The installed-package consumer is built but not executed.
- Qt5 appears in CMake discovery paths but is not validated by CI.

## Goals

- Add a long-lived library-governance spec that captures the CI contract.
- Extend the supported CI matrix to macOS.
- Add a minimal CMake job with examples and tests disabled.
- Run the installed-package consumer executable on Linux with offscreen Qt.
- Resolve Qt5 ambiguity by making Qt6 the supported CMake package path.

## Non-Goals

- No Android CI.
- No qmake CI.
- No full icon pack CI expansion.
- No broad widget behavior test expansion.
- No release packaging or artifact publishing.

## Design

The main CI job will use an explicit matrix of supported Qt6 desktop runners:

- Ubuntu latest with `gcc_64`
- Windows latest with `win64_msvc2019_64`
- macOS Intel with `clang_64`

The default job keeps the current build flags and adds a Linux-only consumer smoke run.

A separate Ubuntu minimal job configures with `QTMATERIALWIDGETS_BUILD_EXAMPLES=OFF` and `BUILD_TESTING=OFF`, builds and installs the library, asserts that example/test targets are absent, and then builds the installed-package consumer.

CMake files will be normalized to Qt6-only discovery and target usage. This removes the unverified Qt5 support path instead of expanding the CI matrix to a legacy major version.

## Decisions

- Qt6 is the only supported Qt major version.
- macOS CI uses an explicit Intel runner because the Qt 6.6.3 desktop archive selected by CI is `clang_64`.
- Minimal dependency validation runs on Ubuntu only to keep feedback time bounded while still verifying the dependency contract.
- Consumer runtime smoke runs on Linux only because it can run deterministically with `QT_QPA_PLATFORM=offscreen`.

## Risks

- macOS hosted runner labels can change over time; the explicit Intel label must be maintained with the GitHub Actions runner fleet.
- Removing Qt5 discovery may break unverified local Qt5 builds. This is intentional because Qt5 is not part of the support contract.
- Consumer runtime smoke only proves startup-level integration, not full widget behavior.

No blocking-level risk detected.

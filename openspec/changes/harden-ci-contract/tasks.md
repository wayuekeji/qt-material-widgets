# Tasks

## 1. Add library governance baseline spec

- Goal: Create the long-lived OpenSpec source of truth for build, CI, platform, minimal configuration, consumer, and Qt version support.
- Impact: `openspec/specs/library-governance/spec.md`.
- Implementation: Add requirements for CMake support, Qt6 support, default CI, Linux consumer runtime smoke, and minimal dependency configuration.
- Verification: Run `openspec validate harden-ci-contract --strict`.

## 2. Extend default CI matrix

- Goal: Add macOS while preserving Windows and Ubuntu default verification.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Replace the simple OS matrix with explicit runner/archive rows for Ubuntu, Windows, and macOS Intel; pass the archive through `install-qt-action`; install `qtscxml` for `Qt6StateMachine`.
- Verification: Parse workflow YAML and inspect matrix entries.

## 3. Add Linux consumer runtime smoke

- Goal: Prove the installed package can start a downstream executable, not only compile one.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Add a Linux-only step that runs `build-consumer/qt-material-widgets-consumer` with `QT_QPA_PLATFORM=offscreen` and installed library path.
- Verification: Inspect workflow and run local command where the compiler environment permits.

## 4. Add minimal dependency CI job

- Goal: Verify examples and tests are not forced into dependency builds.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Add a Ubuntu minimal job with `QTMATERIALWIDGETS_BUILD_EXAMPLES=OFF` and `BUILD_TESTING=OFF`, install `qtscxml`, build/install the library, assert target absence, then build the installed-package consumer.
- Verification: Parse workflow YAML and inspect minimal configure flags and target checks.

## 5. Resolve Qt5 support ambiguity

- Goal: Remove unverified Qt5 support commitment from the CMake-supported path.
- Impact: CMake files under root, components, examples, tests, consumer, and package config template.
- Implementation: Replace Qt5/Qt6 discovery branches with Qt6-only `find_package` and `Qt6::` targets.
- Verification: Search for `Qt5` and `QT_VERSION_MAJOR` in supported CMake files and run OpenSpec validation.

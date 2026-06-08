# Fix CI Qt Install

## Motivation

The GitHub Actions CI workflow initially failed before CMake configuration because it asked `jurplel/install-qt-action` to install the invalid `qtstatemachine` archive for Qt 6.6.3.

After removing that invalid archive, CMake configuration fails because the base Qt installation does not provide `Qt6StateMachine`. For Qt 6.6.3 desktop packages, the valid archive that provides the `Qt6StateMachine` CMake package is `qtscxml`.

## Goals

- Restore the GitHub Actions CI workflow so it can install Qt with the archive required by `Qt6StateMachine` and reach the CMake verification pipeline.
- Preserve the existing supported CI contract: Windows, Ubuntu, Qt 6.6.3, Release CMake build, CTest, examples build, install, and installed-package consumer build.
- Keep the fix minimal and scoped to the failing install step.

## Non-Goals

- No macOS or Android CI expansion.
- No Qt5 matrix expansion.
- No qmake validation.
- No broad test coverage expansion.
- No package interface redesign.

## Design

Replace the invalid `qtstatemachine` module request with the valid `qtscxml` module request in `.github/workflows/ci.yml`.

The project still requires `Qt::StateMachine` at CMake level. That requirement remains in `components/CMakeLists.txt` and package config generation. CI installs `qtscxml` so the `Qt6StateMachine` CMake package is present.

## Decisions

- Install `qtscxml` for Qt 6.6.3 because it provides `Qt6StateMachine`.
- Keep `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK=OFF` so CI continues to validate the default resource pack contract.
- Keep the current matrix unchanged because the observed failure is installer module selection, not platform coverage.

## Risks

- If a future Qt version changes the archive that provides `Qt6StateMachine`, the matrix must be updated with the verified module name.
- Local verification cannot fully reproduce GitHub hosted runner installation without executing the workflow remotely.

No blocking-level risk detected.

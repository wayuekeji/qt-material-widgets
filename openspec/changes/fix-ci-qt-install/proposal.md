# Fix CI Qt Install

## Motivation

The GitHub Actions CI workflow currently fails before CMake configuration. Both Windows and Ubuntu jobs stop at the `Install Qt` step because the workflow asks `jurplel/install-qt-action` to install the `qtstatemachine` archive for Qt 6.6.3.

For Qt 6.6.3 desktop packages, `StateMachine` is available as part of the base Qt installation and is not listed as a separately installable module archive. Requesting the missing module makes the external installer fail and prevents the supported CMake verification path from running.

## Goals

- Restore the GitHub Actions CI workflow so it can install Qt and reach the CMake verification pipeline.
- Preserve the existing supported CI contract: Windows, Ubuntu, Qt 6.6.3, Release CMake build, CTest, examples build, install, and installed-package consumer build.
- Keep the fix minimal and scoped to the failing install step.

## Non-Goals

- No macOS or Android CI expansion.
- No Qt5 matrix expansion.
- No qmake validation.
- No broad test coverage expansion.
- No package interface redesign.

## Design

Remove the invalid `qtstatemachine` module request from `.github/workflows/ci.yml`.

The project still requires `Qt::StateMachine` at CMake level. That requirement remains in `components/CMakeLists.txt` and package config generation. CI relies on the base Qt 6.6.3 desktop package to provide the `StateMachine` CMake package.

## Decisions

- Use the base Qt 6.6.3 desktop installation without extra modules.
- Keep `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK=OFF` so CI continues to validate the default resource pack contract.
- Keep the current matrix unchanged because the observed failure is installer module selection, not platform coverage.

## Risks

- If a future Qt version moves `StateMachine` into a separately installable archive, the matrix version must be updated with an explicit verified module name.
- Local verification cannot fully reproduce GitHub hosted runner installation without executing the workflow remotely.

No blocking-level risk detected.

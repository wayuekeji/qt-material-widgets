# Tasks

## 1. Fix Qt installation in CI

- Goal: Replace the invalid Qt module archive request with the valid archive that provides `Qt6StateMachine`.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Set `modules: qtscxml` on the `jurplel/install-qt-action@v4` step.
- Verification: Use `aqtinstall` module listing for Qt 6.6.3 Windows, Linux, and macOS to confirm `qtscxml` is a valid archive name and `qtstatemachine` is not.

## 2. Verify CI contract remains intact

- Goal: Ensure the fix does not weaken the existing CMake verification pipeline.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Preserve the current matrix, configure flags, build, CTest, install, and consumer steps.
- Verification: Inspect the workflow and run local CMake configure where the environment permits. If local compiler environment is unavailable, document that limitation and rely on workflow/static verification plus Qt archive verification.

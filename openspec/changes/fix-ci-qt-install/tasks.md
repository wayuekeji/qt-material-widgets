# Tasks

## 1. Fix Qt installation in CI

- Goal: Remove the invalid Qt module archive request that prevents GitHub Actions from installing Qt 6.6.3.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Delete the `modules: qtstatemachine` input from the `jurplel/install-qt-action@v4` step.
- Verification: Use `aqtinstall` module listing for Qt 6.6.3 Windows and Linux to confirm `qtstatemachine` is not a valid archive name, and inspect the workflow to confirm the invalid input is absent.

## 2. Verify CI contract remains intact

- Goal: Ensure the fix does not weaken the existing CMake verification pipeline.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Preserve the current matrix, configure flags, build, CTest, install, and consumer steps.
- Verification: Inspect the workflow and run local CMake configure where the environment permits. If local compiler environment is unavailable, document that limitation and rely on workflow/static verification plus Qt archive verification.

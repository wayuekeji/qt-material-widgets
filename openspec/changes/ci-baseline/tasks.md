# Tasks

## 1. Add GitHub Actions CMake CI

- **Goal:** Add automated CI for the supported CMake path.
- **Impact Scope:** `.github/workflows/ci.yml`
- **Implementation:** Create a Windows/Linux matrix that installs Qt 6, configures Release CMake with examples and tests enabled, builds, runs CTest, installs, and builds `examples/consumer` through `CMAKE_PREFIX_PATH`.
- **Verification:** Inspect the workflow for required gates and run local CMake/CTest smoke commands where possible.

## 2. Record CI governance

- **Goal:** Make CI expectations durable after the OpenSpec change is archived.
- **Impact Scope:** `CONTEXT.md`, `docs/adr/`, `.github/copilot-instructions.md`
- **Implementation:** Add a CI ADR, list it in the ADR index, update current verification gates, and align Copilot instructions with the current CMake/qmake support policy.
- **Verification:** Confirm the ADR index links the new decision and project context lists GitHub Actions CI.

## 3. Validate OpenSpec and local gates

- **Goal:** Prove the new specification and existing executable smoke tests remain valid.
- **Impact Scope:** OpenSpec metadata and local build/test outputs.
- **Implementation:** Run `openspec validate --all --strict`, static workflow checks, `git diff --check`, and local CTest smoke verification.
- **Verification:** All commands pass or any non-blocking environment warnings are explicitly recorded.

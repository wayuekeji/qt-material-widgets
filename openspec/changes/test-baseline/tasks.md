# Tasks

## 1. Add CTest entry point

- Status: Completed.
- Goal: Let CMake expose test execution through CTest.
- Impact: `CMakeLists.txt`, `tests/CMakeLists.txt`.
- Implementation: Include `CTest` at the root and add `tests/` when `BUILD_TESTING` is enabled.
- Verification: `ctest -N` lists the smoke test.

## 2. Add QTest smoke executable

- Status: Completed.
- Goal: Cover public API and resource regressions.
- Impact: `tests/qtmaterialwidgets_smoke_test.cpp`.
- Implementation: Add tests for typed theme API, core resources, and `QtMaterialProgress::backgroundColor` meta-object writes.
- Verification: The test executable builds and runs through CTest.

## 3. Validate

- Status: Completed.
- Goal: Prove the test baseline is integrated.
- Impact: Build and test outputs.
- Implementation: Run OpenSpec validation, configure with `BUILD_TESTING=ON`, build the smoke test, and run `ctest --output-on-failure`.
- Verification: All commands succeed.

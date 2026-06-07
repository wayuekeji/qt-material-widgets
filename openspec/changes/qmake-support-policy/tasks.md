# Tasks

## 1. Update public build documentation

- Status: Completed.
- Goal: Make CMake the only supported integration path in public docs.
- Impact: `README.md`.
- Implementation: Replace broad qmake/CMake support language with a CMake-supported, qmake-legacy policy.
- Verification: README states `find_package(QtMaterialWidgets CONFIG REQUIRED)` and `QtMaterialWidgets::Widgets` as the supported path, and qmake as legacy.

## 2. Add ADR

- Status: Completed.
- Goal: Persist the build-system support decision.
- Impact: `docs/adr/0001-qmake-support-policy.md`.
- Implementation: Record context, decision, consequences, and verification boundary.
- Verification: ADR exists and states CMake is source of truth while qmake is legacy.

## 3. Mark qmake files as legacy

- Status: Completed.
- Goal: Prevent `.pro` files from implying equal support.
- Impact: `qt-material-widgets.pro`, `components/components.pro`, `examples/examples.pro`.
- Implementation: Add legacy comments and update qmake C++ standard declarations to `c++17`.
- Verification: `rg 'c\\+\\+11|legacy|CMake' *.pro components/*.pro examples/*.pro` shows no stale `c++11` and explicit legacy comments.

## 4. Validate

- Status: Completed.
- Goal: Ensure policy changes do not break the supported CMake path.
- Impact: OpenSpec and CMake build/test outputs.
- Implementation: Run OpenSpec validation and the supported CMake test baseline.
- Verification: `openspec validate --all --strict` and `ctest --output-on-failure` pass.

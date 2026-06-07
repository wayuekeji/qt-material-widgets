# Tasks

## 1. Add explicit component source lists

- Status: Completed.
- Goal: Remove implicit source discovery from the component CMake build.
- Impact: `components/sources.cmake`, `components/CMakeLists.txt`.
- Implementation: Define explicit component implementation, private-header, public-header, and lib-header lists and consume them in target declarations and install rules.
- Verification: `rg 'file\\(GLOB' components/CMakeLists.txt components/sources.cmake` finds no match.

## 2. Add explicit examples source lists

- Status: Completed.
- Goal: Remove implicit source discovery from the examples CMake build.
- Impact: `examples/sources.cmake`, `examples/CMakeLists.txt`.
- Implementation: Define explicit example source, header, and UI lists and consume them in executable declarations.
- Verification: `rg 'file\\(GLOB' examples/CMakeLists.txt examples/sources.cmake` finds no match.

## 3. Align CMake artifact name

- Status: Completed.
- Goal: Stop emitting `components` as the CMake package library basename.
- Impact: `components/CMakeLists.txt`, examples DLL copy, install output.
- Implementation: Set `OUTPUT_NAME QtMaterialWidgets` while preserving `EXPORT_NAME Widgets` and alias `QtMaterialWidgets::Widgets`.
- Verification: Build output contains `QtMaterialWidgets.dll` or platform-equivalent and installed consumer links `QtMaterialWidgets::Widgets`.

## 4. Validate build and package consumption

- Status: Completed.
- Goal: Prove the explicit lists and artifact rename did not break supported CMake paths.
- Impact: Build/install outputs.
- Implementation: Run OpenSpec validation, build library, install package, build consumer, and build examples.
- Verification: All commands succeed.

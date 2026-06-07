# Tasks

## 1. Split qrc resources

- Status: Completed.
- Goal: Create a small core qrc and an optional full-icon qrc.
- Impact: `components/resources_core.qrc`, `components/resources_full_icons.qrc`, CMake resource inputs.
- Implementation: Generate the new qrc files from `components/resources.qrc`, placing required fonts and core icons in the core pack and remaining Material icons in the full pack.
- Verification: Count qrc file entries and confirm the core pack is materially smaller than the legacy aggregate pack.

## 2. Add CMake option

- Status: Completed.
- Goal: Make the full Material icon pack opt-in.
- Impact: `components/CMakeLists.txt`.
- Implementation: Add `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK` and append `resources_full_icons.qrc` only when the option is enabled.
- Verification: Configure and build once with the option disabled and once with it enabled.

## 3. Document resource policy

- Status: Completed.
- Goal: Make downstream behavior explicit.
- Impact: `Docs/ComponentSurface.md`.
- Implementation: Add a resource-pack section describing core resources and the full icon option.
- Verification: Review documentation for the option name and expected consumer action.

## 4. Run package smoke validation

- Status: Completed.
- Goal: Prove installed-package consumption still works.
- Impact: Build/install output and `examples/consumer`.
- Implementation: Build, install to a temporary prefix, and build the consumer example through `find_package`.
- Verification: `openspec validate --all --strict`, CMake build/install, and consumer build succeed.

# Tasks

## 1. Add release usage documentation spec

- Goal: Define the user-facing release documentation contract.
- Impact: `openspec/changes/release-usage-docs/**`.
- Implementation: Add proposal, delta spec, and tasks for release archive consumption documentation.
- Verification: Run `openspec validate release-usage-docs --strict`.

## 2. Add English release usage guide

- Goal: Explain how downstream users consume release archives.
- Impact: `Docs/ReleaseUsage.md`.
- Implementation: Document asset selection, extraction, install-prefix layout, CMake configuration, target linkage, runtime handling, and troubleshooting.
- Verification: Static check that the document mentions `CMAKE_PREFIX_PATH`, `find_package(QtMaterialWidgets CONFIG REQUIRED)`, `QtMaterialWidgets::Widgets`, platform assets, and Qt runtime responsibility.

## 3. Link release guide from README

- Goal: Make the release usage guide discoverable.
- Impact: `README.md`.
- Implementation: Add a concise sentence under CMake package usage linking to `Docs/ReleaseUsage.md`.
- Verification: Static check that README links to `Docs/ReleaseUsage.md`.

## 4. Run validation gates

- Goal: Confirm OpenSpec and documentation checks pass.
- Impact: OpenSpec and Markdown documentation.
- Implementation: Run OpenSpec validation and static documentation assertions.
- Verification: `openspec validate --all --strict`; static assertions pass; `git diff --check` passes.

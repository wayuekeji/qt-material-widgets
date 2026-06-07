# qmake Support Policy

## Motivation

The project documentation still claims broad qmake and CMake support, but the verified integration path is now the exported CMake package. qmake files remain in the repository, yet they are not covered by the new package smoke tests, CTest baseline, source-list governance, or resource-pack options.

Leaving qmake as a co-equal path creates an inaccurate public contract.

## Scope

- Document CMake as the only supported integration and verification path.
- Downgrade qmake to legacy, source-tree-only status.
- Record the decision in an ADR.
- Mark `.pro` files as legacy and align their C++ language flag with the project baseline.

## Non-Goals

- No qmake package export implementation.
- No qmake CI matrix.
- No qmake install/consumer smoke test.
- No removal of `.pro` files in this slice.

## Design

The README will present CMake as the supported path. qmake documentation will become a legacy note, not an integration recipe.

The ADR records why qmake is not a supported distribution surface: it bypasses the current CMake package target, install/export rules, resource-pack option, explicit source lists, and CTest validation.

## Decisions

- qmake is legacy and unverified.
- CMake is the source of truth for package delivery.
- `.pro` files remain for historical/local experimentation only.
- qmake files use C++17 where they declare a language standard.

## Risks

- Users manually relying on qmake will no longer see it documented as supported.
- qmake files may still drift because they are intentionally outside the verified build contract.

No blocking risk was detected.

# Tasks

## 1. Add project context

- Status: Completed.
- Goal: Define domain vocabulary and architecture boundaries.
- Impact: `CONTEXT.md`.
- Implementation: Document Core, Widgets, Theme, Resource Pack, Component Surface, Demo Page, Consumer, CMake package, tests, and governance source-of-truth rules.
- Verification: `CONTEXT.md` exists and contains the required terms.

## 2. Add ADR index

- Status: Completed.
- Goal: Make architecture decisions discoverable.
- Impact: `docs/adr/README.md`.
- Implementation: List accepted ADRs with short summaries.
- Verification: ADR index includes qmake, CMake package, component surface, resource packs, CMake source governance, and test baseline.

## 3. Add missing ADRs

- Status: Completed.
- Goal: Persist major optimization decisions.
- Impact: `docs/adr/*.md`.
- Implementation: Add accepted ADRs for CMake package interface, component surface, resource packs, CMake source governance, and test baseline.
- Verification: `rg 'Status|Decision|Consequences' docs/adr` finds these sections across ADRs.

## 4. Validate

- Status: Completed.
- Goal: Prove docs governance artifacts match the spec.
- Impact: OpenSpec and static docs checks.
- Implementation: Run OpenSpec validation and term/ADR search checks.
- Verification: All checks succeed.

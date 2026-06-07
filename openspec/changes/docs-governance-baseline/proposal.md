# Docs Governance Baseline

## Motivation

The optimization report identified that the repository had no `CONTEXT.md` and no ADR directory. Several architecture decisions have now been made: CMake package interface, stable widget surface, resource-pack split, explicit CMake source lists, CTest baseline, and qmake legacy status.

Those decisions need stable documentation outside transient change proposals.

## Scope

- Add a project `CONTEXT.md` with domain vocabulary and ownership boundaries.
- Add an ADR index.
- Add ADRs for the major architecture decisions made during the optimization sequence.
- Keep OpenSpec changes as the change-tracking layer, while ADRs capture durable decisions.

## Non-Goals

- No full API reference generation.
- No OpenSpec archive execution in this slice.
- No documentation site tooling.

## Design

`CONTEXT.md` defines project vocabulary for future agents and maintainers. `docs/adr/` stores durable decisions with status, context, decision, and consequences.

The ADR set will cover:

- CMake package interface.
- Public widget surface classification.
- Resource-pack split.
- CMake source-list and artifact naming governance.
- Test baseline.

The existing qmake ADR remains ADR 0001.

## Decisions

- Keep ADRs short and operational.
- Treat CMake as the build/package source of truth.
- Treat `Docs/ComponentSurface.md` as the public surface status document.
- Treat OpenSpec changes as proposed/active change records until archived.

## Risks

- ADRs can drift if future changes skip documentation updates.

No blocking risk was detected.

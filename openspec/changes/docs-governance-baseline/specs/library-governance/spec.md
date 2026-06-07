## ADDED Requirements

### Requirement: Project Context Document

The repository SHALL contain a `CONTEXT.md` file defining project vocabulary and architecture boundaries.

#### Scenario: Maintainer needs domain vocabulary

- **GIVEN** a maintainer or agent needs project terms
- **WHEN** they inspect the repository root
- **THEN** `CONTEXT.md` SHALL define terms including Core, Widgets, Theme, Resource Pack, Component Surface, Demo Page, and Consumer

### Requirement: ADR Index

The repository SHALL contain an ADR index under `docs/adr`.

#### Scenario: Maintainer needs decisions

- **GIVEN** a maintainer wants durable architecture decisions
- **WHEN** they inspect `docs/adr/README.md`
- **THEN** it SHALL list accepted ADRs and their subjects

### Requirement: Durable Architecture Decisions

Major build, package, resource, testing, and public-surface decisions MUST be recorded as ADRs.

#### Scenario: Decision trace exists

- **GIVEN** the current optimized architecture
- **WHEN** a maintainer checks ADRs
- **THEN** ADRs SHALL record decisions for qmake support, CMake package interface, component surface, resource packs, CMake source governance, and test baseline

### Requirement: Documentation Governance Boundary

Documentation SHALL distinguish durable ADR decisions from active OpenSpec change records.

#### Scenario: Maintainer chooses where to edit

- **GIVEN** a maintainer is changing future behavior
- **WHEN** they read `CONTEXT.md`
- **THEN** it SHALL state that OpenSpec changes track active changes and ADRs capture durable decisions

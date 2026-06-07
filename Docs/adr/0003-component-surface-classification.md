# ADR 0003: Component Surface Classification

## Status

Accepted

## Context

Some public headers represented stable widgets, while others were experimental, stubs, or empty shells. Installing all headers by default made incomplete modules look supported.

## Decision

Widgets are classified in `Docs/ComponentSurface.md` as:

- stable
- experimental
- stub
- not implemented

Only stable widgets are installed by default as part of the CMake package Interface.

## Consequences

- Experimental and stub widgets may remain in source and examples.
- Stable package headers must match the documented component surface.
- New widgets must be classified before they are added to the installed Interface.

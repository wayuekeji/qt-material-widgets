# ADR 0005: CMake Source And Artifact Governance

## Status

Accepted

## Context

Directory-wide CMake `file(GLOB)` source collection made source additions implicit. The CMake package target was `QtMaterialWidgets::Widgets`, while the generated artifact used the historical `components` basename.

## Decision

CMake source inputs are listed explicitly in:

- `components/sources.cmake`
- `examples/sources.cmake`

The built shared library artifact basename is `QtMaterialWidgets`.

The exported consumer target remains `QtMaterialWidgets::Widgets`.

## Consequences

- Source additions require explicit source-list edits.
- Reviewers can see build-surface changes in diffs.
- Consumers should remain insulated from artifact naming through the exported target.

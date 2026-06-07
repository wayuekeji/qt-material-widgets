# Demo Page Registry

## Motivation

`examples/mainwindow.cpp` currently owns every demo page include, construction expression, title mapping, and stack registration. This makes the demo shell a high-churn file whenever pages are added, removed, or reclassified.

The demo layer should expose a single registry for page metadata and factories.

## Scope

- Add a demo page registry module under `examples/`.
- Move demo page includes and factory construction out of `MainWindow`.
- Keep the rendered demo page list and page order unchanged.
- Preserve existing editor implementations.

## Non-Goals

- No settings editor form refactor.
- No UI redesign.
- No public library API change.
- No removal of experimental or stub demo pages in this slice.

## Design

Create `DemoPageDefinition` with:

- `title`
- `factory`

Expose `demoPageDefinitions()` returning the ordered page list. `MainWindow` will consume the registry and only manage shell layout, navigation list, and stacked widget switching.

## Decisions

- Use `std::function<QWidget *()>` factories because pages are QWidget subclasses with default constructors.
- Keep order identical to the current `QMap` sorted output, not declaration order, to avoid visual churn.
- Keep ownership unchanged: pages are added to `QStackedLayout`, which reparents widgets into the main window hierarchy.

## Risks

- The examples target still uses `file(GLOB)`, so new source files are picked up automatically today. Explicit source-list governance is deferred to the CMake source-list change.

No blocking risk was detected.

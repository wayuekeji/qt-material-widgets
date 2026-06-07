# Tasks

## 1. Add registry module

- Status: Completed.
- Goal: Centralize demo page titles and factories.
- Impact: `examples/demopageregistry.h`, `examples/demopageregistry.cpp`.
- Implementation: Define `DemoPageDefinition` and `demoPageDefinitions()` with the current page order and factories.
- Verification: Confirm the registry contains the same page titles as the previous visible order.

## 2. Refactor MainWindow

- Status: Completed.
- Goal: Make `MainWindow` consume the registry instead of owning page construction.
- Impact: `examples/mainwindow.cpp`.
- Implementation: Remove direct settings editor includes and `QMap` construction; iterate over registry definitions and switch by row.
- Verification: Build the examples target.

## 3. Validate

- Status: Completed.
- Goal: Prove the spec and demo app remain valid.
- Impact: OpenSpec and examples build.
- Implementation: Run OpenSpec validation and a Release examples build.
- Verification: `openspec validate --all --strict` and `cmake --build ... --target examples` succeed.

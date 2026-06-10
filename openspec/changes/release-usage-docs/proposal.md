# Release Usage Documentation

## Motivation

The project now has a GitHub Release workflow that publishes platform-specific archives, but user-facing documentation does not explain how to consume those archives.

The README explains source builds and CMake package consumption, but it does not describe release asset names, archive layout, platform ABI expectations, `CMAKE_PREFIX_PATH`, or runtime library handling.

## Goals

- Add an English document that explains how to use GitHub Release assets.
- Document the supported release asset model as a CMake install prefix.
- Show concrete CMake consumer commands and `CMakeLists.txt` usage.
- Explain platform and runtime constraints.
- Link the release usage document from README.

## Non-Goals

- No change to release workflow behavior.
- No installer or runtime deployment implementation.
- No qmake usage documentation.
- No Android release usage documentation.

## Design

Add `Docs/ReleaseUsage.md` as the dedicated user-facing English guide for release artifacts.

The document will describe:

- Which release asset to download for each desktop platform.
- How to extract the archive.
- How to identify the CMake install prefix.
- How to configure a downstream CMake project with `CMAKE_PREFIX_PATH`.
- How to link `QtMaterialWidgets::Widgets`.
- What the release archive includes and does not include.
- Runtime library handling for Windows, Linux, and macOS.
- Common troubleshooting checks.

README will add a short link under the CMake package usage section so users can find the release-specific guide without overloading the main page.

## Decisions

- Keep the detailed release instructions in `Docs/ReleaseUsage.md`.
- Keep README concise and link to the detailed document.
- Treat release assets as platform-specific CMake install prefixes.
- Explicitly state that Qt runtime deployment remains the consuming application's responsibility.

## Risks

- Runtime deployment details vary by downstream application packaging strategy.
- Release asset names are coupled to the current workflow naming convention.

No blocking-level risk detected.

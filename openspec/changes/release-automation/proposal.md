# Release Automation

## Motivation

The project already validates the supported CMake package path in CI, but release publishing is still manual. This creates a gap between verified installable outputs and the artifacts that downstream consumers can download from GitHub Releases.

QualityManagement uses a self-hosted runner for release because it builds a Windows business application installer with private submodules, preinstalled SDKs, and local runner environment files. This project is a reusable Qt Widgets library with a standard CMake install surface, so the release path should stay reproducible on GitHub-hosted runners unless a future hard dependency proves otherwise.

## Goals

- Add a manually triggered GitHub Actions release workflow.
- Use GitHub-hosted runners for Windows, Ubuntu, and macOS package artifacts.
- Build the supported Qt6 CMake path in Release mode.
- Run tests, build examples, install the package, and build the installed-package consumer before publishing.
- Package the CMake install prefix as downloadable release assets.
- Create a GitHub Release from an explicit version input.

## Non-Goals

- No self-hosted runner release path.
- No qmake release packaging.
- No Android release artifact.
- No code signing, notarization, installer generation, or private SDK integration.
- No bundled downstream application runtime deployment beyond the library install prefix.

## Design

The release workflow is triggered by `workflow_dispatch` with a required `version` input. The workflow normalizes versions such as `1.2.3` to tag `v1.2.3`, rejects malformed values, and refuses to overwrite an existing tag or release.

The release build runs on GitHub-hosted runners:

- `windows-latest` with Qt archive `win64_msvc2019_64`
- `ubuntu-latest` with Qt archive `gcc_64`
- `macos-15-intel` with Qt archive `clang_64`

Each matrix job installs Qt 6.6.3 with `qtscxml`, configures the CMake Release build with examples and tests enabled, builds the project, runs CTest, builds examples, installs to a clean prefix, configures and builds `examples/consumer` through `CMAKE_PREFIX_PATH`, then archives the install prefix as a platform-specific package.

The publish job downloads all platform packages after every matrix job succeeds. It creates an annotated git tag on the triggering commit, creates a GitHub Release, uploads all package assets, and leaves the release as non-draft. If any creation or upload step fails after a release is created, the workflow deletes the partial release and tag to avoid a broken public release surface.

## Decisions

- Use GitHub-hosted runners by default because current release dependencies are public and reproducible.
- Keep release manual-only to preserve explicit version control.
- Publish install-prefix archives instead of OS installers because the project is a library package, not an end-user application.
- Keep the same Qt version and required Qt archive contract as CI: Qt 6.6.3 plus `qtscxml`.
- Use GitHub REST API from PowerShell instead of adding a release marketplace action.
- Use artifact upload/download only as an internal handoff between release jobs.
- Reject existing tag or release names rather than overwriting.

## Risks

- GitHub-hosted runner labels and preinstalled tools can change over time.
- macOS Intel runner availability must be maintained while using the `clang_64` Qt archive.
- Assets contain the library install prefix and examples installed by CMake, but do not bundle every Qt runtime dependency for standalone application execution.
- If future releases require signing, notarization, private SDKs, or hardware-bound tools, this design must be revisited.

No blocking-level risk detected.

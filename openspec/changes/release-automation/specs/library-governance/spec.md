## ADDED Requirements

### Requirement: GitHub Release Automation

The project SHALL provide a manually triggered GitHub Actions workflow that publishes GitHub Releases for the supported CMake package path.

The release workflow MUST accept an explicit version input and derive a release tag from that input.

The release workflow MUST reject malformed release versions.

The release workflow MUST NOT overwrite an existing git tag or GitHub Release.

#### Scenario: Manual release creates a tagged GitHub Release

- **GIVEN** a maintainer starts the release workflow with version `1.2.3`
- **WHEN** all release build jobs pass
- **THEN** the workflow SHALL create tag `v1.2.3`
- **AND** it SHALL create a GitHub Release named `v1.2.3`
- **AND** it SHALL upload every platform package produced by the workflow

#### Scenario: Existing release is protected

- **GIVEN** tag `v1.2.3` or release `v1.2.3` already exists
- **WHEN** a maintainer starts the release workflow with version `1.2.3`
- **THEN** the workflow MUST fail before creating or uploading release assets

### Requirement: GitHub-Hosted Release Runners

The release workflow SHALL use GitHub-hosted runners by default.

The release workflow MUST NOT depend on self-hosted runner labels, local environment files, or machine-level SDK paths.

#### Scenario: Release does not require a self-hosted machine

- **GIVEN** the release workflow is inspected
- **WHEN** runner selection is evaluated
- **THEN** every release build job SHALL use a GitHub-hosted runner label
- **AND** no release job SHALL use `self-hosted`

### Requirement: Release Package Verification

Each release package job SHALL validate the supported CMake package path before producing an asset.

Each release package job MUST configure the project with:

- `QTMATERIALWIDGETS_BUILD_EXAMPLES=ON`
- `QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK=OFF`
- `BUILD_TESTING=ON`

Each release package job MUST run:

- CMake configure
- CMake build
- CTest execution
- examples target build
- CMake install
- installed-package consumer configure through `CMAKE_PREFIX_PATH`
- installed-package consumer build

The release workflow MUST install the Qt `qtscxml` archive because it provides the `Qt6StateMachine` CMake package required by the library.

#### Scenario: Package asset is produced only after install consumption succeeds

- **GIVEN** a release package job builds a platform package
- **WHEN** the package asset is archived
- **THEN** the installed package SHALL already have been consumed by `examples/consumer` through `CMAKE_PREFIX_PATH`
- **AND** CTest SHALL already have passed for that job

### Requirement: Release Assets

The release workflow SHALL publish one package asset per supported desktop release runner.

Each release asset name MUST include the release tag and platform identifier.

The release asset contents MUST come from the CMake install prefix, not from the raw build tree.

#### Scenario: Platform assets are uploaded

- **GIVEN** release version `1.2.3`
- **WHEN** the release workflow succeeds
- **THEN** the GitHub Release SHALL include Windows, Ubuntu, and macOS package archives
- **AND** each package archive SHALL be derived from the platform job install prefix

# Tasks

## 1. Add release governance spec

- Goal: Define the release automation contract before changing workflow behavior.
- Impact: `openspec/changes/release-automation/proposal.md`, `openspec/changes/release-automation/specs/library-governance/spec.md`, `openspec/changes/release-automation/tasks.md`.
- Implementation: Add requirements for manual release triggering, GitHub-hosted runners, package verification, and release assets.
- Verification: Run `openspec validate release-automation --strict`.

## 2. Add GitHub Actions release workflow

- Goal: Build and publish platform install-prefix packages from GitHub-hosted runners.
- Impact: `.github/workflows/release.yml`.
- Implementation: Add a manual `workflow_dispatch` workflow with version validation, Windows/Ubuntu/macOS matrix package jobs, Qt 6.6.3 `qtscxml` setup, CMake build/test/install/consumer validation, package archive creation, artifact handoff, and GitHub Release publishing.
- Verification: Parse the workflow as YAML and inspect that no job uses `self-hosted`, the matrix covers Windows/Ubuntu/macOS, and the required build/test/install/consumer steps exist.

## 3. Validate release workflow contract

- Goal: Prove the workflow matches the OpenSpec release contract.
- Impact: OpenSpec and workflow file.
- Implementation: Run OpenSpec validation and static workflow checks for trigger, permissions, runner labels, Qt archive setup, release asset names, and overwrite protection.
- Verification: `openspec validate --all --strict`; static assertions over `.github/workflows/release.yml` pass.

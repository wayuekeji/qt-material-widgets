# Tasks

## 1. Define Qt installation hardening contract

- Goal: Capture the CI failure mode and required workflow behavior.
- Impact: `openspec/changes/fix-ci-install-qt-stability/**`.
- Implementation: Add modified requirements for deterministic Qt installation, no install-qt cache dependency, and Windows MSVC setup before Qt installation.
- Verification: Run `openspec validate fix-ci-install-qt-stability --strict`.

## 2. Harden CI Qt installation

- Goal: Fix `ci.yml` failure during `Install Qt`.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Move Windows `Setup MSVC` before `Install Qt`; disable `install-qt-action` cache in all CI Qt installation steps.
- Verification: Parse workflow YAML and assert Windows setup precedes Qt install, `cache: false` is used, `qtscxml` remains present, and no supported build/test/install/consumer step is removed.

## 3. Harden release Qt installation

- Goal: Prevent release packaging from hitting the same Qt install failure mode.
- Impact: `.github/workflows/release.yml`.
- Implementation: Move Windows `Setup MSVC` before `Install Qt`; disable `install-qt-action` cache in release package jobs.
- Verification: Parse workflow YAML and assert Windows setup precedes Qt install, `cache: false` is used, and release package verification steps remain present.

## 4. Run validation gates

- Goal: Prove the workflow changes match OpenSpec and remain structurally valid.
- Impact: OpenSpec and GitHub Actions workflows.
- Implementation: Run OpenSpec validation, YAML parsing, static workflow assertions, and whitespace checks.
- Verification: `openspec validate --all --strict`; static workflow assertions pass; `git diff --check` passes.

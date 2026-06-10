# Tasks

## 1. Define CI trigger policy

- Goal: Capture the new CI trigger contract.
- Impact: `openspec/changes/limit-ci-to-master-pr/**`.
- Implementation: Add proposal, delta spec, and tasks for pull-request-only CI targeting `master`.
- Verification: Run `openspec validate limit-ci-to-master-pr --strict`.

## 2. Restrict CI trigger

- Goal: Ensure CI runs only for pull requests targeting `master`.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Replace push, unrestricted pull request, and manual dispatch triggers with `pull_request.branches: [master]`.
- Verification: Parse workflow YAML and assert only `pull_request` targeting `master` remains.

## 3. Remove unreachable manual jobs

- Goal: Avoid dead CI configuration after removing `workflow_dispatch`.
- Impact: `.github/workflows/ci.yml`.
- Implementation: Remove jobs guarded by `if: github.event_name == 'workflow_dispatch'`.
- Verification: Static check that no job references `workflow_dispatch` and the remaining Windows job still runs configure, build, CTest, examples, install, and consumer build.

## 4. Run validation gates

- Goal: Prove OpenSpec and workflow structure are valid.
- Impact: OpenSpec and CI workflow.
- Implementation: Run OpenSpec validation, YAML parsing, static workflow assertions, and whitespace checks.
- Verification: `openspec validate --all --strict`; static workflow assertions pass; `git diff --check` passes.

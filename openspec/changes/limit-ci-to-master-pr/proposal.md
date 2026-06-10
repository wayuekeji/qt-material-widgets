# Limit CI To Master Pull Requests

## Motivation

The current CI workflow runs on pushes to `main`/`master`, all pull requests, and manual `workflow_dispatch`. The requested policy is stricter: CI should run only when a pull request targets `master`.

This reduces unnecessary GitHub Actions usage and makes the CI contract match the repository's protected integration branch.

## Goals

- Change `.github/workflows/ci.yml` so it triggers only on `pull_request` events targeting `master`.
- Remove CI trigger paths for push and manual dispatch.
- Remove CI jobs that only existed for manual dispatch because they become unreachable under the new trigger policy.
- Preserve the default Windows CMake package verification path for pull requests to `master`.

## Non-Goals

- No change to release automation.
- No change to CMake build flags in the remaining CI job.
- No change to Qt version or required Qt modules.
- No change to tests, examples, install, or consumer verification steps in the remaining CI job.

## Design

The CI workflow `on` block will be reduced to:

```yaml
on:
  pull_request:
    branches:
      - master
```

The default Windows job remains because it is the automatic package-path gate. It continues to configure with examples and tests enabled, run CTest, build examples, install the package, and build the installed-package consumer.

The previous `workflow_dispatch`-only Ubuntu/macOS extended job and Ubuntu minimal job will be removed from `ci.yml`, because the workflow can no longer be manually triggered and those jobs would otherwise be dead configuration.

## Decisions

- `master` is the only CI target branch.
- CI no longer runs on direct pushes.
- CI no longer has manual dispatch jobs.
- Release workflow remains separate and manually triggered.

## Risks

- Direct pushes to `master` will no longer receive CI from this workflow.
- Ubuntu, macOS, and minimal dependency checks will no longer run through `ci.yml`.
- Platform coverage shifts to release packaging or any future dedicated workflows.

No blocking-level risk detected.

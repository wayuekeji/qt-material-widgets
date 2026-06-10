# Fix CI Qt Installation Stability

## Motivation

The Windows CI workflow fails during the `Install Qt` step. The provided GitHub Actions log reaches the `install-qt-action` cache-hit path and then exits with failure, before the project CMake configure step starts.

The current workflow also sets up the MSVC developer environment after installing Qt, while the long-lived governance spec requires the Windows CI workflow to use an MSVC compiler environment when installing the `win64_msvc2019_64` Qt archive.

## Goals

- Make CI Qt installation deterministic instead of depending on a potentially stale or corrupted `install-qt-action` cache entry.
- Enter the MSVC developer environment before installing the Windows MSVC Qt archive.
- Apply the same Qt installation hardening to release packaging jobs so release does not inherit the same failure mode.

## Non-Goals

- No change to supported Qt version.
- No change to Qt module selection; `qtscxml` remains required.
- No switch to self-hosted runners.
- No change to CMake package behavior.

## Design

The workflow will keep `jurplel/install-qt-action@v4` but disable its cache. Qt installation is part of the correctness path; the cache is only a speed optimization and should not be a single point of failure.

Windows jobs will run `ilammy/msvc-dev-cmd@v1` before `Install Qt`, so the job environment is aligned with the `win64_msvc2019_64` Qt archive before Qt installation and CMake configuration.

The release workflow uses the same Qt action and Windows archive, so it receives the same ordering and cache hardening.

## Decisions

- Prefer deterministic Qt installation over cached Qt installation.
- Keep `qtscxml` because the library requires `Qt6StateMachine`.
- Keep GitHub-hosted runners.
- Harden both CI and release workflows because they share the same Qt installation mechanism.

## Risks

- CI and release runs may take longer because Qt is not restored from cache.
- If Qt upstream availability changes, the workflow will fail at install time instead of using an old cached copy. This is acceptable because release correctness requires reproducible dependency acquisition.

No blocking-level risk detected.

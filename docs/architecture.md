# Architecture Overview

## Goal

Provide a small, easy-to-build version-control system focused on text-only files. The system emphasizes a small storage footprint (diff-based storage), a simple linked-list-like version history, and an approachable CLI plus an interactive Windows batch menu.

## High-level Overview

This project implements a minimal version-control system that supports repository initialization, committing text files (stored as diffs), viewing version history, comparing versions, and checking out (restoring) previous states. It targets Windows users (PowerShell + batch menu) but also builds on POSIX flows (WSL, Linux, macOS).

## Main Components

- `CLI` (`src/cli`): command parsing and mapping to operations (`init`, `commit`, `log`, `diff`, `checkout`).
- `Core` (`src/core`): core algorithms and data structures for versions, diffs, patches, and repo state.
- `Storage` (`src/storage`): file and metadata management (reading/writing `versions.txt`, blobs, and diffs).
- `Interactive Wrapper`: `dsa-unified.bat` — a 15-option menu that invokes the CLI for user workflows.
- `Setup`: `Setup.ps1` and `Setup.bat` to check prerequisites, create `build/`, compile, and optionally run tests.

## Data Model & Version History

- Repository: a directory (default `./repo`) containing metadata and stored diffs/blobs.
- Versions: each commit writes a metadata entry (ID/hash, timestamp, message) to `versions.txt` and stores associated diffs/blobs.
- History: logically a sequence (linked-list-like) of versions; each version references predecessor(s) and can be reconstructed by applying diffs.

Storing diffs instead of full copies reduces disk usage for text files that change incrementally.

## Storage Layout (important files)

- `versions.txt` — plain-text chronological list of version metadata.
- Blob/Diff files — stored alongside the repo; names reference version IDs or sequence numbers.
- `.active_repo` — tracks the active repository used by the batch menu.

## Typical Operation Flow

1. `init` — create repository directory and initial metadata files.
2. `commit <file>` — compute diff against last version, store diff and append metadata.
3. `log` — read `versions.txt` and display IDs, timestamps and messages.
4. `diff v1 v2` — load stored information and compute/display textual differences.
5. `checkout id` — reconstruct file(s) for that version by applying diffs/patches.

## How to Build & Run (Windows — PowerShell)

Recommended (automatic): use the PowerShell setup script which detects tools and builds the project.

1) From the project root (PowerShell):

```powershell
.\n+```

2) To auto-build non-interactively (recommended):

```powershell
.\Setup.ps1 -AutoBuild
```

3) After a successful build the executable will be at `build\main.exe`. Launch the interactive menu:

```powershell
.\dsa-unified.bat
```

4) Or call the CLI directly:

```powershell
.\build\main.exe init
.\build\main.exe commit .\notes.txt
.\build\main.exe log
```

## Manual Build with `g++` (MinGW-w64)

If you have `g++` in PATH (MinGW-w64), run the following from the project root (PowerShell):

```powershell
g++ -std=c++17 -O2 -Wall -Wextra -I ./src -o .\build\main.exe `
	src\main.cpp src\cli\parser.cpp src\cli\commands.cpp `
	src\core\utils.cpp src\core\diff.cpp src\core\patch.cpp `
	src\core\repo.cpp src\core\version.cpp src\core\crypto.cpp `
	src\storage\file_manager.cpp src\storage\metadata.cpp
```

(In PowerShell you can join into a single line or use backtick for continuation.)

## Build with Make / Scripts (WSL / MSYS / Linux / macOS)

- `make` — available if you use MSYS2 or WSL; the repository includes a `Makefile` with test targets and `clean`.
- `scripts/build.sh` — runs `cmake` + `make` (use on POSIX environments).
- `scripts/run_tests.sh` — compiles and runs unit tests on POSIX environments.

## Running Tests

- Using Make (MSYS/WSL):
	- `make test_utils` / `make test_diff` / `make test_repo` / `make test_crypto`
- On POSIX: `bash scripts/run_tests.sh`

## Troubleshooting

- g++ not found: install MinGW-w64 and add the `bin` directory to your PATH, or use WSL and install `build-essential`.
- PowerShell execution policy: if `Setup.ps1` is blocked, run PowerShell as Administrator and use `Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process` then rerun the script.
- If `build\main.exe` is missing: inspect the output from `Setup.ps1` or re-run the manual `g++` command.

## Design Notes

- Simplicity and teaching value: small codebase and clear flow for learning how diffs/patches and version metadata combine into a working VCS.
- Space efficiency: using diffs minimizes storage for successive edits to text files.

---

File updated: `docs/architecture.md` — includes architecture summary and step-by-step build/run instructions for Windows and POSIX environments.

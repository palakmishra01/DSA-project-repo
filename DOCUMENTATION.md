# DSA-project-repo — Complete Documentation

**Lightweight C++ version-control CLI with Windows batch interface**

---

## Table of Contents

1. [Project Overview](#project-overview)
2. [Quick Start](#quick-start)
3. [Setup & Installation](#setup--installation)
4. [Running the Project](#running-the-project)
5. [Menu Reference (Unified Interface)](#menu-reference-unified-interface)
6. [CLI Commands](#cli-commands)
7. [Multi-Repository Management](#multi-repository-management)
8. [Troubleshooting](#troubleshooting)
9. [Quick Reference / Cheat-Sheet](#quick-reference--cheat-sheet)

---

## Project Overview

This is a demonstration of a lightweight version-control system built in C++ with a Windows batch interface. It provides:

- **Version control**: commit files, view history, compare versions, restore previous commits
- **Multi-repository support**: manage multiple independent repositories with the `--repo` flag
- **Interactive menu**: `dsa-unified.bat` provides an easy-to-use menu interface
- **CLI interface**: Use `./build/main.exe` directly for command-line operations

**Key features:**
- Initialize repositories
- Commit files with automatic diff generation
- View commit history with timestamps and hashes
- Compare versions and inspect diffs
- Restore (checkout) previous versions
- Multi-repository support with `--repo` flag
- Interactive Windows batch menu (15 menu options)
- Cross-platform CLI interface

---

## Quick Start

### Fastest Setup (1 minute)

**PowerShell users:**
```powershell
Set-Location 'C:\path\to\DSA-project-repo'
.\Setup.ps1 -AutoBuild
```

**Command Prompt / Batch users:**
```cmd
cd C:\path\to\DSA-project-repo
Setup.bat
```

### Launch the Interactive Menu

```powershell
.\dsa-unified.bat
```

### Quick Test Flow

1. Menu option **5** → Initialize repository
2. Menu option **12** → Create a new file (type content, end with `END`)
3. Menu option **6** → Commit the file
4. Menu option **7** → View version history

---

## Setup & Installation

### Prerequisites

You need:
1. **C++ Compiler**: MinGW-w64 (g++) or MSVC or WSL
2. **PowerShell 5.1+** (comes with Windows 10+) — for Setup.ps1
3. **Git** (for cloning the repo) — https://git-scm.com/

### Installation Steps

#### Step 1: Clone Repository

```powershell
git clone https://github.com/palakmishra01/DSA-project-repo
cd DSA-project-repo
```

#### Step 2: Verify Prerequisites

Check for g++:
```powershell
g++ --version
```

If not found, install MinGW-w64 from https://www.mingw-w64.org/

#### Step 3: Build the Project

**Option A - Automatic (Recommended):**

PowerShell:
```powershell
.\Setup.ps1 -AutoBuild
```

Batch:
```cmd
Setup.bat
```

**Option B - Manual with g++:**

```powershell
g++ -std=c++17 -O2 -Wall -Wextra -I ./src -o .\build\main.exe `
  src\main.cpp `
  src\cli\parser.cpp `
  src\cli\commands.cpp `
  src\core\utils.cpp `
  src\core\diff.cpp `
  src\core\patch.cpp `
  src\core\repo.cpp `
  src\core\version.cpp `
  src\core\crypto.cpp `
  src\storage\file_manager.cpp `
  src\storage\metadata.cpp
```

**Option C - Using Makefile:**

```powershell
make
```

#### Step 4: Verify Build

```powershell
dir .\build\main.exe
```

Expected: Executable file listed.

#### Step 5: Test CLI

```powershell
.\build\main.exe --repo .\repo init
.\build\main.exe log
```

Expected: Repository initialized message, then empty or existing version history.

---

## Running the Project

### Interactive Menu (Recommended)

```powershell
.\dsa-unified.bat
```

This opens a 15-option menu organized into three sections:
- **Options 1-4**: Repository management (create/list/switch/delete)
- **Options 5-10**: Version control (init/commit/log/diff/checkout/view)
- **Options 11-14**: Utilities (demo files/create file/edit/custom commands)
- **Option 15**: Exit

### Direct CLI Usage

```powershell
# Initialize repository
.\build\main.exe init

# Commit a file
.\build\main.exe commit .\notes.txt

# View history
.\build\main.exe log

# Compare versions
.\build\main.exe diff 0 1

# Restore a version
.\build\main.exe checkout 1
```

---

## Menu Reference (Unified Interface)

The `dsa-unified.bat` script presents a unified menu. Here's what each option does:

### Section 1: Repository Management (1-4)

| Option | Name | Description |
|--------|------|-------------|
| **1** | Create New Repository | Create a named repository (e.g., `project1`, `backup`) |
| **2** | List All Repositories | Show all repos with version counts |
| **3** | Switch Repository | Change the active repository |
| **4** | Delete Repository | Permanently delete a repository (with confirmation) |

**Example:**
```
Choose: 1
Enter repo name: project1
✅ Repository created successfully!
```

### Section 2: Version Control (5-10)

| Option | Name | Description |
|--------|------|-------------|
| **5** | Initialize Repository | Initialize the active repo (creates structure) |
| **6** | Commit a File | Save a file as a new version |
| **7** | Show Version History | Display all commits with details |
| **8** | Compare Versions | Show diff between two versions |
| **9** | Restore a Version | Check out (restore) an old version |
| **10** | View Repository Contents | List files in the active repo directory |

**Example:**
```
Choose: 6
Enter file path: .\mynotes.txt
✅ Committed version 1 with X diff lines.
```

### Section 3: Utilities (11-14)

| Option | Name | Description |
|--------|------|-------------|
| **11** | Create Demo Files | Create `demo_v1.txt`, `demo_v2.txt`, `demo_v3.txt` |
| **12** | Create New File | Type content in terminal (end with `END`) |
| **13** | Edit File in Notepad | Open file in Notepad for editing |
| **14** | Run Command Directly | Execute custom `./build/main.exe` command |

**Example - Menu 12:**
```
Choose: 12
Enter filename: mynotes.txt
Enter content (type END on new line to finish):
Hello, World!
This is my first version.
END
✅ File created: mynotes.txt
```

### Exit (15)

```
Choose: 15
Exit program
```

---

## CLI Commands

Use `./build/main.exe` directly for command-line operations.

### Syntax

```
./build/main.exe [--repo <path>] <command> [arguments]
```

### Commands

#### `init`
Initialize a repository.

```powershell
.\build\main.exe init
.\build\main.exe --repo .\project1 init
```

#### `commit <file>`
Commit a file as a new version.

```powershell
.\build\main.exe commit .\notes.txt
.\build\main.exe --repo .\project1 commit .\file.txt
```

#### `log`
View commit history.

```powershell
.\build\main.exe log
.\build\main.exe --repo .\project1 log
```

Output example:
```
Version log:
------------------------------------------------------------
Version 0:
  Timestamp : 2025-11-14 10:30:15
  Hash      : 513667672
  Diff file : ./repo/diff_0.txt
  Preview   : First version content
------------------------------------------------------------
Version 1:
  Timestamp : 2025-11-14 10:31:20
  Hash      : 326988226
  Diff file : ./repo/diff_1.txt
  Preview   : Updated content
------------------------------------------------------------
```

#### `diff <version1> <version2>`
Compare two versions.

```powershell
.\build\main.exe diff 0 1
.\build\main.exe --repo .\project1 diff 1 2
```

Output example:
```
Diff between versions 0 and 1:
- Old line from version 0
+ New line from version 1
```

#### `checkout <versionID>`
Restore a previous version.

```powershell
.\build\main.exe checkout 0
.\build\main.exe --repo .\project1 checkout 1
```

This creates `./repo/current_version.txt` with the restored content.

---

## Multi-Repository Management

### Overview

You can manage multiple independent repositories. The active repository is tracked in `.active_repo` at the project root.

### Creating Multiple Repositories

**Using the menu:**
```
Menu 1: Create New Repository
Enter name: project1
✅ Created

Menu 1: Create New Repository
Enter name: project2
✅ Created
```

**Using CLI directly:**
```powershell
.\build\main.exe --repo .\project1 init
.\build\main.exe --repo .\project2 init
```

### How Active Repository Works

- **Active repo config**: `.active_repo` file in project root
- **When to use**: When operating from the menu, actions apply to the active repo
- **Switching repos**: Menu option 3 changes the active repo

Example `.active_repo` content:
```
.\project1
```

### Using `--repo` Flag

Bypass the menu and target any repository directly:

```powershell
# Work with project1
.\build\main.exe --repo .\project1 init
.\build\main.exe --repo .\project1 commit .\file.txt
.\build\main.exe --repo .\project1 log

# Work with project2
.\build\main.exe --repo .\project2 commit .\report.txt
.\build\main.exe --repo .\project2 log
```

Both repositories maintain independent version histories.

### Example Workflow

```powershell
# Create two repos
.\build\main.exe --repo .\backup init
.\build\main.exe --repo .\current init

# Work in backup
.\build\main.exe --repo .\backup commit .\snapshot.txt

# Work in current
Set-Content -Path .\work.txt -Value "Version 1"
.\build\main.exe --repo .\current commit .\work.txt

# Update current
Set-Content -Path .\work.txt -Value "Version 2"
.\build\main.exe --repo .\current commit .\work.txt

# View both histories
.\build\main.exe --repo .\backup log
.\build\main.exe --repo .\current log
```

### Repository Structure

After creating multiple repos:

```
DSA-project-repo/
├── repo/              ← Default repository
│   ├── versions.txt
│   └── diff_*.txt
├── project1/          ← Named repository 1
│   ├── versions.txt
│   └── diff_*.txt
├── project2/          ← Named repository 2
│   ├── versions.txt
│   └── diff_*.txt
├── .active_repo       ← Current active repo (contains ./project1)
├── dsa-unified.bat
└── build/
    └── main.exe
```

### Multi-Repo Tips

- Use `--repo ./` (relative path) with `./` or `.\ ` prefix on Windows
- Use absolute paths if needed: `.\build\main.exe --repo C:\full\path\to\repo log`
- List repos with Menu 2 to confirm names and version counts
- Delete repos with Menu 4 (with confirmation prompt)

---

## File Creation & Editing

### Menu 12: Create New File (Type in Terminal)

Best for quick, small files.

**Steps:**
1. Choose Menu 12
2. Enter filename (e.g., `notes.txt`)
3. Type content line by line
4. Type `END` on a new line to finish
5. File created in project root

**Example:**
```
Choose: 12
Enter filename: mynotes.txt
Enter content (type END to finish):
Line 1
Line 2
Line 3
END
✅ File created: mynotes.txt
```

### Menu 13: Edit File in Notepad

Best for longer edits or binary-safe editing.

**Steps:**
1. Choose Menu 13
2. Enter filename (e.g., `myfile.txt`)
3. Notepad opens
4. Edit content
5. Save (Ctrl+S) and close (Alt+F4)
6. File persisted automatically

**Example:**
```
Choose: 13
Enter filename: myfile.txt
Opening myfile.txt in Notepad...
(Notepad window opens)
(You edit and save)
✅ File saved.
```

### After Creating/Editing

Always commit your file to save a version:

```
Menu 6: Commit a File
Enter file path: .\mynotes.txt
✅ Committed version 1 with X diff lines.
```

---

## Where Data is Stored

### Default Repository

Files stored under `./repo/`:
- `versions.txt` — metadata (tab-separated: id, timestamp, hash, diffPath)
- `diff_0.txt`, `diff_1.txt`, etc. — diffs for each version
- `current_version.txt` — created by checkout command

### Named Repositories

Each repo stored in its own folder:
```
./project1/
  ├── versions.txt
  ├── diff_0.txt
  ├── diff_1.txt
  └── ...

./project2/
  ├── versions.txt
  ├── diff_0.txt
  └── ...
```

### Config Files

- `.active_repo` — current active repository path
- `project-config.json` — build configuration (machine-readable)

---

## Troubleshooting

### "g++ command not found"

**Problem:** Compiler not installed or not in PATH.

**Solution:**
1. Install MinGW-w64: https://www.mingw-w64.org/
2. Add to System PATH: `C:\Program Files\mingw-w64\...\bin`
3. Restart PowerShell/Command Prompt
4. Verify: `g++ --version`

**Alternative:** Use WSL (Windows Subsystem for Linux)
```powershell
wsl --install Ubuntu
wsl
apt update && apt install -y g++
```

---

### "build\main.exe not created after build"

**Problem:** Build failed or directory missing.

**Solution:**
1. Create build directory: `mkdir build`
2. Check for compiler errors in build output
3. Verify source files exist: `dir src`
4. Rebuild: `.\Setup.ps1 -AutoBuild` or run g++ command again

---

### "Cannot run Setup.ps1" / "Script execution disabled"

**Problem:** PowerShell execution policy blocks the script.

**Solution (run PowerShell as Administrator):**

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
.\Setup.ps1 -AutoBuild
```

Or bypass without changing policy:

```powershell
powershell -ExecutionPolicy Bypass -File Setup.ps1 -AutoBuild
```

---

### "File not found" when committing

**Problem:** File path incorrect or file doesn't exist.

**Solution:**
1. Create file first (Menu 12 or Menu 13)
2. Use correct path: `.\filename.txt` (with `.\` prefix on Windows)
3. Verify file exists: `dir .\yourfile.txt`
4. Check current directory: `Get-Location`

---

### "No versions found" in log

**Problem:** Repository not initialized or no commits made.

**Solution:**
1. Initialize repo: Menu 5 or `.\build\main.exe init`
2. Create a file: Menu 12 or `Set-Content -Path .\file.txt -Value "content"`
3. Commit: Menu 6 or `.\build\main.exe commit .\file.txt`
4. View log: Menu 7 or `.\build\main.exe log`

---

### "Repository not found" with `--repo`

**Problem:** Incorrect repo path or repo doesn't exist.

**Solution:**
1. Use correct relative path: `.\repo_name` or `./repo_name`
2. Initialize the repo first: `.\build\main.exe --repo .\myrepo init`
3. Verify repo exists: `dir` (should show repo folder)
4. Check exact name (List Repos with Menu 2)

---

### CLI test failed or errors

**Problem:** CLI runs but produces unexpected output.

**Solution:**
1. Ensure you're in project root: `Get-Location`
2. Verify executable exists: `dir .\build\main.exe`
3. Test basic command: `.\build\main.exe --repo .\repo log`
4. Check permissions on project root folder
5. Re-run build: `.\Setup.ps1 -AutoBuild`

---

## Quick Reference / Cheat-Sheet

### Automated Setup

```powershell
.\Setup.ps1 -AutoBuild              # PowerShell auto-setup
.\Setup.ps1 -AutoBuild -SkipTests   # Skip tests
.\Setup.ps1 -Help                   # Show help

Setup.bat                           # Batch auto-setup
```

### Menu Quick Reference

| Task | Menu | Then |
|------|------|------|
| Create repo | 1 | Enter repo name |
| List repos | 2 | View all repos |
| Switch repo | 3 | Enter repo name |
| Delete repo | 4 | Confirm deletion |
| Initialize | 5 | Nothing (creates structure) |
| Commit file | 6 | Enter file path |
| View history | 7 | See all versions |
| Compare | 8 | Enter two version IDs |
| Restore | 9 | Enter version ID |
| View contents | 10 | See repo files |
| Demo files | 11 | Creates 3 demo files |
| Create file | 12 | Type lines, end with END |
| Edit file | 13 | Opens Notepad |
| Run command | 14 | Enter custom command |
| Exit | 15 | Close menu |

### Common CLI Commands

```powershell
# Basic operations
.\build\main.exe init                          # Initialize default repo
.\build\main.exe commit .\file.txt             # Commit a file
.\build\main.exe log                           # View history
.\build\main.exe diff 0 1                      # Compare versions 0 and 1
.\build\main.exe checkout 0                    # Restore version 0

# Multi-repo operations
.\build\main.exe --repo .\project1 init        # Initialize project1
.\build\main.exe --repo .\project1 commit .\f.txt
.\build\main.exe --repo .\project1 log
.\build\main.exe --repo .\project2 commit .\f.txt
```

### Workflow Scenarios

**Scenario 1: Single Repo, Create → Commit → View**
```
5 (Init) → 12 (Create file) → 6 (Commit) → 7 (View history)
```

**Scenario 2: Multi-Repo, Two Projects**
```
1 (Create project1) → 1 (Create project2) → 3 (Switch to project2)
→ 5 (Init) → 12 (Create file) → 6 (Commit) → 7 (View)
```

**Scenario 3: Edit → Commit → Compare**
```
13 (Edit file in Notepad) → 6 (Commit) → 8 (Compare) → Enter versions
```

**Scenario 4: Demo Test**
```
11 (Create demo files) → 6 (Commit demo_v1.txt) → 6 (Commit demo_v2.txt) → 7 (Log)
```

### File Structure After Setup

```
DSA-project-repo/
├── build/
│   └── main.exe              ← Compiled CLI
├── repo/                     ← Default repo (created at runtime)
│   ├── versions.txt
│   └── diff_*.txt
├── src/                      ← Source code
│   ├── main.cpp
│   ├── cli/
│   ├── core/
│   └── storage/
├── tests/                    ← Unit tests
├── project-config.json       ← Configuration
├── Setup.ps1                 ← PowerShell setup
├── Setup.bat                 ← Batch setup
├── dsa-unified.bat           ← Interactive menu
├── DOCUMENTATION.md          ← This file
└── (other files)
```

### Configuration Files

- **project-config.json** — Build settings, compiler flags, source files, environment requirements
- **.active_repo** — Current active repository path (created at runtime)
- **versions.txt** — Version metadata in each repo folder

---

## Next Steps

1. **Run setup**: `.\Setup.ps1 -AutoBuild` or `Setup.bat`
2. **Launch menu**: `.\dsa-unified.bat`
3. **Create repository**: Menu option 1
4. **Create file**: Menu option 12
5. **Commit**: Menu option 6
6. **View history**: Menu option 7
7. **Explore advanced features**: Options 8-14

---

## Summary

| Task | How |
|------|-----|
| **Setup** | `.\Setup.ps1 -AutoBuild` or `Setup.bat` |
| **Interactive menu** | `.\dsa-unified.bat` |
| **CLI** | `.\build\main.exe [--repo <path>] <command>` |
| **Create repo** | Menu 1 or `.\build\main.exe --repo .\name init` |
| **Commit file** | Menu 6 or `.\build\main.exe commit .\file.txt` |
| **View history** | Menu 7 or `.\build\main.exe log` |
| **Compare** | Menu 8 or `.\build\main.exe diff 0 1` |
| **Restore** | Menu 9 or `.\build\main.exe checkout 1` |

---

## License

MIT

## Repository

https://github.com/palakmishra01/DSA-project-repo

---

**Happy versioning!** 🚀

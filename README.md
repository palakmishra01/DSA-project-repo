# DSA-project-repo

**A lightweight C++ version-control CLI with interactive Windows batch interface**

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B17-brightgreen)
![Platform](https://img.shields.io/badge/platform-Windows-0078d4)
![License](https://img.shields.io/badge/license-MIT-green)

---

##  Overview

This project demonstrates a simple but functional version-control system built in C++. It allows you to:

- **Initialize repositories** — Create version-controlled project folders
- **Commit files** — Save snapshots of your work with automatic diffs
- **View history** — See all commits with timestamps and hashes
- **Compare versions** — Inspect what changed between commits
- **Restore versions** — Go back to any previous version
- **Multi-repo support** — Manage multiple independent repositories
- **Interactive menu** — Easy-to-use batch interface with 15 options
- **CLI interface** — Use commands directly for advanced workflows

---

##  Quick Start (1 minute)

### 1. Clone & Enter Project

```powershell
git clone https://github.com/palakmishra01/DSA-project-repo
cd DSA-project-repo
```

### 2. Run Setup

**PowerShell (Recommended):**
```powershell
.\Setup.ps1 -AutoBuild
```

**Command Prompt:**
```cmd
Setup.bat
```

### 3. Launch Interactive Menu

```powershell
.\dsa-unified.bat
```

### 4. Try It Out

1. Menu option **5**  Initialize repository
2. Menu option **12**  Create a file (type content, end with `END`)
3. Menu option **6**  Commit the file
4. Menu option **7**  View history

**Done!** 

---

##  Requirements

- **C++ Compiler**: MinGW-w64 (g++), MSVC, or WSL
- **PowerShell 5.1+** (comes with Windows 10+)
- **Git** (for cloning)

---

##  Full Documentation

All detailed documentation is in a single comprehensive file:

** [Read DOCUMENTATION.md](DOCUMENTATION.md)** for:
- Complete setup & installation guide
- All 15 menu options explained
- CLI commands with examples
- Multi-repository workflows
- Troubleshooting guide
- Quick reference & cheat-sheet

---

##  Interactive Menu Overview

The unified interface provides **15 options**:

| Menu | Option | Description |
|------|--------|-------------|
| **1-4** | Repository Management | Create, list, switch, delete repos |
| **5** | Init | Initialize a new repository |
| **6** | Commit | Save a file snapshot |
| **7** | Log | View commit history |
| **8** | Diff | Compare two versions |
| **9** | Checkout | Restore a previous version |
| **10** | View | Browse a specific version |
| **11** | Demo Files | Create sample files |
| **12** | Create File | Type content directly (end with `END`) |
| **13** | Edit File | Open file in Notepad |
| **14** | Run Command | Execute custom CLI command |
| **15** | Exit | Close menu |

**Launch with:**
```powershell
.\dsa-unified.bat
```

---

##  CLI Commands

Use the compiled executable directly:

```powershell
# Initialize
.\build\main.exe init

# Commit a file
.\build\main.exe commit .\notes.txt

# View history
.\build\main.exe log

# Compare versions
.\build\main.exe diff 0 1

# Restore a version
.\build\main.exe checkout 1

# Multi-repo (use --repo flag)
.\build\main.exe --repo .\project1 init
.\build\main.exe --repo .\project1 log
```

---

##  Project Structure

```
DSA-project-repo/
 src/                     C++ source code
    main.cpp
    cli/                Command parser & executor
    core/               Core versioning logic
    storage/            File & metadata management
 tests/                  Unit tests (test_*.cpp)
 build/                  Compiled executable (main.exe)
 repo/                   Default repository (created at runtime)
 DOCUMENTATION.md        Complete guide (782 lines)
 README.md               This file
 project-config.json     Build configuration
 Setup.ps1               PowerShell auto-setup
 Setup.bat               Batch auto-setup
 dsa-unified.bat         Interactive menu (15 options)
```

---

##  Installation Options

### Option A: Automatic Setup (Recommended)

**PowerShell:**
```powershell
.\Setup.ps1 -AutoBuild
```

**Command Prompt:**
```cmd
Setup.bat
```

### Option B: Manual Build with g++

```powershell
g++ -std=c++17 -O2 -Wall -Wextra -I ./src -o .\build\main.exe `
  src\main.cpp src\cli\parser.cpp src\cli\commands.cpp `
  src\core\utils.cpp src\core\diff.cpp src\core\patch.cpp `
  src\core\repo.cpp src\core\version.cpp src\core\crypto.cpp `
  src\storage\file_manager.cpp src\storage\metadata.cpp
```

### Option C: Using Makefile

```powershell
make
```

---

##  Key Features

 **Version Control** — Commit, view history, compare, restore  
 **Multi-Repository** — Manage multiple independent repos with `--repo`  
 **Interactive Menu** — 15-option user-friendly batch interface  
 **CLI Interface** — Direct command-line access for power users  
 **Auto Diffs** — Automatic diff generation on each commit  
 **Timestamps & Hashes** — Track when and what changed  
 **Persistence** — Versions stored in `versions.txt`  
 **Cross-Platform** — Batch for Windows, also works with WSL/Linux/macOS  

---

##  Example Workflows

### Single Repository

```
Initialize  Create file  Commit  View history  Compare  Restore
```

### Multiple Repositories

```
Create repo1  Create repo2  Switch  Commit  Switch  Compare
```

---

##  Troubleshooting

### g++ not found?
- Install MinGW-w64: https://www.mingw-w64.org/
- Add to PATH and restart PowerShell

### Setup script fails?
- Run with admin privileges
- Check all source files exist in `src/`
- See DOCUMENTATION.md for detailed troubleshooting

### CLI test fails?
- Verify you're in project root: `Get-Location`
- Check `build\main.exe` exists: `dir .\build\main.exe`
- Re-run setup: `.\Setup.ps1 -AutoBuild`

---

##  Use Cases

- **Learning version control concepts** — Understand how Git-like systems work
- **Testing workflows** — Practice commit, diff, and restore operations
- **Multi-project management** — Maintain separate version histories
- **Backup & recovery** — Create snapshots and restore previous versions
- **Experimental changes** — Work safely in isolated repositories

---

##  Configuration Files

- **project-config.json** — Machine-readable build settings
- **.active_repo** — Tracks current active repository (created at runtime)
- **versions.txt** — Version metadata in each repository folder

---

##  License

MIT License — See LICENSE file for details

---

##  Links

- **Repository:** https://github.com/lokeshkaria14/DSA-project-repo
- **Full Documentation:** [DOCUMENTATION.md](DOCUMENTATION.md)
- **Configuration:** [project-config.json](project-config.json)

---

##  Next Steps

1. **Read this README** 
2. **Run Setup:** `.\Setup.ps1 -AutoBuild` or `Setup.bat`
3. **Launch Menu:** `.\dsa-unified.bat`
4. **Learn More:** Open [DOCUMENTATION.md](DOCUMENTATION.md)

---

**Happy versioning!** 


@echo off
REM DSA-project-repo Setup Script (Batch Version)
REM This script automates the setup process for new users

setlocal enabledelayedexpansion
chcp 65001 >nul

set PROJECT_ROOT=%~dp0
cd /d "%PROJECT_ROOT%"

echo.
echo ================================
echo  DSA-project-repo Setup
echo ================================
echo.

REM Check if g++ is available
echo [1/5] Checking compiler...
g++ --version >nul 2>&1
if errorlevel 1 (
    echo [WARNING] g++ not found in PATH
    echo Please install MinGW-w64 from: https://www.mingw-w64.org/
    echo.
    set COMPILER_FOUND=0
) else (
    echo [OK] g++ compiler found
    set COMPILER_FOUND=1
)

REM Create build directory if not exists
echo [2/5] Checking build directory...
if not exist "build\" (
    mkdir build
    echo [OK] Created build directory
) else (
    echo [OK] build directory exists
)

REM Build the project
echo [3/5] Building project...
if %COMPILER_FOUND% equ 0 (
    echo [ERROR] Cannot build without compiler
    echo Please install MinGW-w64 first
    pause
    exit /b 1
)

echo Building: .\build\main.exe
g++ -std=c++17 -O2 -Wall -Wextra -I .\src ^
    -o .\build\main.exe ^
    src\main.cpp ^
    src\cli\parser.cpp ^
    src\cli\commands.cpp ^
    src\core\utils.cpp ^
    src\core\diff.cpp ^
    src\core\patch.cpp ^
    src\core\repo.cpp ^
    src\core\version.cpp ^
    src\core\crypto.cpp ^
    src\storage\file_manager.cpp ^
    src\storage\metadata.cpp

if errorlevel 1 (
    echo [ERROR] Build failed!
    pause
    exit /b 1
) else (
    echo [OK] Build successful
)

REM Verify executable exists
echo [4/5] Verifying executable...
if exist "build\main.exe" (
    echo [OK] main.exe created successfully
) else (
    echo [ERROR] main.exe not found after build
    pause
    exit /b 1
)

REM Test the CLI
echo [5/5] Testing CLI...
echo Running: .\build\main.exe --repo .\repo init
.\build\main.exe --repo .\repo init

if errorlevel 1 (
    echo [WARNING] CLI test completed with exit code !errorlevel!
) else (
    echo [OK] CLI test passed
)

echo.
echo ================================
echo  Setup Complete!
echo ================================
echo.
echo Next steps:
echo   1. Run the interactive menu:
echo      .\dsa-unified.bat
echo.
echo   2. Create a test repository (Menu option 1)
echo   3. Create a test file (Menu option 12)
echo   4. Commit and explore features
echo.
echo For detailed instructions, see ALL_INSTRUCTIONS.md
echo.

setlocal disabledelayedexpansion
pause

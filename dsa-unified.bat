@echo off
REM DSA Version Control - Unified Interface
REM Combines Repository Manager + Interactive CLI in one script
REM This script forces the working directory to the script location (project root)

:: Resolve the project root to the script directory
set "PROJECT_ROOT=%~dp0"
pushd "%PROJECT_ROOT%" >nul 2>&1
if errorlevel 1 (
    echo Failed to change to project directory: %PROJECT_ROOT%
    pause
    exit /b 1
)

:: enable delayed expansion to safely expand variables inside code blocks
setlocal EnableDelayedExpansion

:: Config file to store active repo
set "CONFIG_FILE=%PROJECT_ROOT%.active_repo"
set "ACTIVE_REPO=.\repo"

:: Load active repo from config file if it exists
if exist "%CONFIG_FILE%" (
    for /f "delims=" %%i in ('type "%CONFIG_FILE%"') do set "ACTIVE_REPO=%%i"
)

:main_menu
cls
echo.
echo ╔════════════════════════════════════════════════════════════════╗
echo ║    DSA Version Control - Unified Interface                    ║
echo ╚════════════════════════════════════════════════════════════════╝
echo.
echo Active Repository: !ACTIVE_REPO!
echo Current Directory: %CD%
echo.
echo ┌────────────────────────────────────────────────────────────────┐
echo │                     MAIN MENU                                  │
echo └────────────────────────────────────────────────────────────────┘
echo.
echo Repository Management:
echo   1. Create New Repository
echo   2. List All Repositories
echo   3. Switch Repository
echo   4. Delete Repository
echo.
echo Version Control Operations (on active repo):
echo   5. Initialize Repository
echo   6. Commit a File
echo   7. Show Version History
echo   8. Compare Versions (Diff)
echo   9. Restore a Version (Checkout)
echo  10. View Repository Contents
echo.
echo Utilities:
echo  11. Create Demo Files
echo  12. Create New File
echo  13. Edit File in Notepad
echo  14. Run Command Directly
echo.
echo  15. Exit
echo.
set /p choice="Enter your choice (1-15): "

if "%choice%"=="1" goto create_repo
if "%choice%"=="2" goto list_repos
if "%choice%"=="3" goto switch_repo
if "%choice%"=="4" goto delete_repo
if "%choice%"=="5" goto init_repo
if "%choice%"=="6" goto commit_file
if "%choice%"=="7" goto show_log
if "%choice%"=="8" goto show_diff
if "%choice%"=="9" goto checkout_version
if "%choice%"=="10" goto view_repo
if "%choice%"=="11" goto create_demo
if "%choice%"=="12" goto create_file
if "%choice%"=="13" goto edit_file
if "%choice%"=="14" goto run_command
if "%choice%"=="15" goto exit_script

echo.
echo Invalid choice. Please enter 1-15.
pause
goto main_menu

REM ========================================================================
REM REPOSITORY MANAGEMENT SECTION
REM ========================================================================

:create_repo
echo.
set /p repo_name="Enter new repository name (e.g., project1, backup, v2): "

if "%repo_name%"=="" (
    echo Repository name cannot be empty.
    pause
    goto main_menu
)

set "repo_path=.\!repo_name!"
echo.
echo Creating repository at: !repo_path!
echo.
.\build\main.exe --repo "!repo_path!" init

if errorlevel 0 (
    echo.
    echo ✅ Repository created successfully!
    echo Setting !repo_name! as active repository...
    echo !repo_path! > "%CONFIG_FILE%"
    set "ACTIVE_REPO=!repo_path!"
)
echo.
pause
goto main_menu

:list_repos
echo.
echo Available repositories:
echo.
set "count=0"
for /d %%d in (*repo*) do (
    if exist "%%d\versions.txt" (
        set /a count+=1
        echo !count!. %%d
        for /f "tokens=1" %%v in ('findstr /c:"." "%%d\versions.txt" 2^>nul ^| find /c /v ""') do (
            echo    (Contains ~%%v versions^)
        )
    )
)

if %count% equ 0 (
    echo No repositories found. Create one with option 1.
)

echo.
pause
goto main_menu

:switch_repo
echo.
set /p repo_name="Enter repository name to switch to (e.g., project1): "
set "repo_path=.\!repo_name!"

if not exist "!repo_path!" (
    echo ❌ Repository not found: !repo_path!
    pause
    goto main_menu
)

echo Switching to repository: !repo_path!
echo !repo_path! > "%CONFIG_FILE%"
set "ACTIVE_REPO=!repo_path!"
echo ✅ Active repository updated.
echo.
pause
goto main_menu

:delete_repo
echo.
echo ⚠️  WARNING: This will permanently delete a repository and all its versions.
echo.
set /p repo_name="Enter repository name to delete (or press Enter to cancel): "

if "%repo_name%"=="" (
    echo Cancelled.
    pause
    goto main_menu
)

set "repo_path=.\!repo_name!"

if not exist "!repo_path!" (
    echo Repository not found: !repo_path!
    pause
    goto main_menu
)

echo.
set /p confirm="Are you sure you want to delete !repo_path!? (yes/no): "

if /i "!confirm!"=="yes" (
    goto do_delete
) else (
    echo Deletion cancelled.
    pause
    goto main_menu
)

:do_delete
echo Deleting "!repo_path!"...
rmdir /s /q "!repo_path!"
if errorlevel 1 (
    echo ❌ Failed to delete repository.
    pause
    goto main_menu
) else (
    echo ✅ Repository deleted.
)

if /i "!ACTIVE_REPO!"=="!repo_path!" (
    echo Active repo was deleted. Switching to default (.\repo)...
    echo .\repo > "%CONFIG_FILE%"
    set "ACTIVE_REPO=.\repo"
)

echo.
pause
goto main_menu

REM ========================================================================
REM VERSION CONTROL SECTION
REM ========================================================================

:init_repo
echo.
set /p repo_path="Enter repository path (default: !ACTIVE_REPO!): "
if "%repo_path%"=="" (
    set "repo_path=!ACTIVE_REPO!"
)
echo Initializing repository at !repo_path!...
echo.
.\build\main.exe --repo "!repo_path!" init
echo.
pause
goto main_menu

:commit_file
echo.
set /p filepath="Enter file path to commit (e.g., .\myfile.txt): "
if exist "!filepath!" (
    echo Committing file: !filepath! to !ACTIVE_REPO!
    echo.
    .\build\main.exe --repo "!ACTIVE_REPO!" commit "!filepath!"
) else if exist "%PROJECT_ROOT%!filepath!" (
    echo Committing file: %PROJECT_ROOT%!filepath! to !ACTIVE_REPO!
    echo.
    .\build\main.exe --repo "!ACTIVE_REPO!" commit "%PROJECT_ROOT%!filepath!"
) else (
    echo ❌ File not found: !filepath!
)
echo.
pause
goto main_menu

:show_log
echo.
echo Showing version history for: !ACTIVE_REPO!
echo.
.\build\main.exe --repo "!ACTIVE_REPO!" log
echo.
pause
goto main_menu

:show_diff
echo.
set /p v1="Enter first version ID: "
set /p v2="Enter second version ID: "
echo.
echo Comparing versions !v1! and !v2! in !ACTIVE_REPO!...
echo.
.\build\main.exe --repo "!ACTIVE_REPO!" diff "!v1!" "!v2!"
echo.
pause
goto main_menu

:checkout_version
echo.
echo ┌────────────────────────────────────────────────────────────────┐
echo │              Restore/Rollback Version                          │
echo └────────────────────────────────────────────────────────────────┘
echo.
echo Choose restore option:
echo   1. View version (Checkout - display only)
echo   2. Rollback version (Save to file)
echo.
set /p restore_choice="Enter your choice (1-2): "

if "%restore_choice%"=="1" goto checkout_view
if "%restore_choice%"=="2" goto rollback_save

echo Invalid choice. Returning to main menu.
pause
goto main_menu

:checkout_view
echo.
set /p vid="Enter version ID to view: "
echo Checking out version !vid! from !ACTIVE_REPO!...
echo.
.\build\main.exe --repo "!ACTIVE_REPO!" checkout !vid!
echo.
pause
goto main_menu

:rollback_save
echo.
set /p vid="Enter version ID to rollback to: "
set /p outfile="Enter output file path (e.g., restored.txt): "
echo.
echo Rolling back to version !vid! from !ACTIVE_REPO!...
echo.
.\build\main.exe --repo "!ACTIVE_REPO!" rollback !vid! "!outfile!"
echo.
pause
goto main_menu

:view_repo
echo.
echo Repository structure for: !ACTIVE_REPO!
echo.
if exist "!ACTIVE_REPO!" (
    dir /b "!ACTIVE_REPO!"
) else (
    echo Repository directory not found: !ACTIVE_REPO!
)
echo.
pause
goto main_menu

REM ========================================================================
REM UTILITY SECTION
REM ========================================================================

:create_demo
echo.
echo Creating demo files in %PROJECT_ROOT% ...
(
  echo Hello, this is the first version!
  echo Let's test the version control system.
  echo This is version 1.
) > "%PROJECT_ROOT%demo_v1.txt"
(
  echo Hello, this is the second version!
  echo Another update here.
) > "%PROJECT_ROOT%demo_v2.txt"
(
  echo Hello, this is the third version!
  echo More changes.
) > "%PROJECT_ROOT%demo_v3.txt"
echo ✅ Created demo_v1.txt, demo_v2.txt, demo_v3.txt
echo.
pause
goto main_menu

:create_file
echo.
set /p filename="Enter filename to create (e.g., myfile.txt): "
echo.
echo Enter file content below (type "END" on a new line when done):
echo.
set "filepath=%PROJECT_ROOT%!filename!"
:: create/overwrite the file
> "!filepath!" (call )
:read_line
set /p "line="
if /i "!line!"=="END" goto finish_content
>> "!filepath!" echo(!line!
goto read_line
:finish_content
echo.
echo ✅ File created: !filepath!
echo.
pause
goto main_menu

:edit_file
echo.
set /p filename="Enter filename to edit (e.g., myfile.txt): "
set "filepath=%PROJECT_ROOT%!filename!"
if exist "!filepath!" (
    echo Opening !filepath! in Notepad...
    echo.
    notepad "!filepath!"
    echo.
    echo ✅ File saved.
) else (
    echo ❌ File not found: !filepath!
    echo Expected location: !filepath!
)
echo.
pause
goto main_menu

:run_command
echo.
set /p cmd="Enter full command (e.g., .\build\main.exe --repo !ACTIVE_REPO! log): "
echo.
!cmd!
echo.
pause
goto main_menu

:exit_script
echo.
echo Exiting DSA Version Control. Goodbye!
echo.
exit /b 0

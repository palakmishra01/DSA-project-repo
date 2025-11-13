# DSA-project-repo Setup Script
# This script reads project-config.json and guides users through setup

param(
    [switch]$AutoBuild = $false,
    [switch]$SkipTests = $false,
    [switch]$Help = $false
)

# Color output functions
function Write-Success { Write-Host $args -ForegroundColor Green }
function Write-Error { Write-Host $args -ForegroundColor Red }
function Write-Warning { Write-Host $args -ForegroundColor Yellow }
function Write-Info { Write-Host $args -ForegroundColor Cyan }

if ($Help) {
    Write-Info "DSA-project-repo Setup Script"
    Write-Host ""
    Write-Host "Usage: .\Setup.ps1 [Options]"
    Write-Host ""
    Write-Host "Options:"
    Write-Host "  -AutoBuild   : Automatically build without prompting"
    Write-Host "  -SkipTests   : Skip running tests after build"
    Write-Host "  -Help        : Show this help message"
    Write-Host ""
    Write-Host "Examples:"
    Write-Host "  .\Setup.ps1                  # Interactive setup"
    Write-Host "  .\Setup.ps1 -AutoBuild       # Auto-build with prompts"
    Write-Host "  .\Setup.ps1 -AutoBuild -SkipTests  # Full automation"
    exit 0
}

# Load config file
Write-Info "Loading project configuration..."
$configPath = ".\project-config.json"

if (-not (Test-Path $configPath)) {
    Write-Error "ERROR: project-config.json not found!"
    Write-Host "Make sure you are in the project root directory."
    exit 1
}

$config = Get-Content $configPath | ConvertFrom-Json
Write-Success "✓ Configuration loaded"

# Display project info
Write-Info "`n=== PROJECT INFORMATION ==="
Write-Host "Name:       $($config.project.name)"
Write-Host "Version:    $($config.project.version)"
Write-Host "Description: $($config.project.description)"
Write-Host "Author:     $($config.project.author)"

# Check prerequisites
Write-Info "`n=== CHECKING PREREQUISITES ==="

# Check for g++
$gppCheck = $null
try {
    $gppCheck = g++ --version 2>$null
    if ($gppCheck) {
        Write-Success "✓ g++ compiler found"
        Write-Host "  Version: $($gppCheck[0])"
    }
} catch {
    Write-Warning "⚠ g++ compiler not found in PATH"
    Write-Host "  Install MinGW-w64 from: https://www.mingw-w64.org/"
    Write-Host "  Or use: choco install mingw (if you have Chocolatey)"
}

# Check for build directory
Write-Info "`nChecking build directory..."
if (-not (Test-Path ".\build")) {
    Write-Warning "⚠ build directory does not exist"
    New-Item -ItemType Directory -Path ".\build" -Force | Out-Null
    Write-Success "✓ Created build directory"
} else {
    Write-Success "✓ build directory exists"
}

# Display build information
Write-Info "`n=== BUILD INFORMATION ==="
Write-Host "Compiler:    $($config.build.compiler)"
Write-Host "C++ Standard: $($config.build.cppStandard)"
Write-Host "Optimization: -$($config.build.optimizationLevel)"
Write-Host "Output:      $($config.build.outputPath)"
Write-Host "Source files: $($config.build.sourceFiles.Count) files"

# Build decision
Write-Info "`n=== BUILD STEP ==="
$shouldBuild = $AutoBuild

if (-not $AutoBuild) {
    $response = Read-Host "Do you want to build the project now? (Y/N)"
    $shouldBuild = $response -match '^[Yy]$'
}

if ($shouldBuild) {
    Write-Info "`nBuilding project..."
    
    # Construct build command from config
    $sourceFiles = $config.build.sourceFiles -join ' '
    $flags = $config.build.flags -join ' '
    $buildCmd = "$($config.build.compiler) $flags -I $($config.build.headerIncludePath) -o $($config.build.outputPath) $sourceFiles"
    
    Write-Host "Build command: $buildCmd`n"
    
    # Execute build
    Invoke-Expression $buildCmd
    
    if ($LASTEXITCODE -eq 0) {
        Write-Success "✓ Build successful!"
        
        # Verify executable
        if (Test-Path $($config.build.outputPath)) {
            $exeSize = (Get-Item $($config.build.outputPath)).Length / 1KB
            Write-Success "✓ Executable created ($([Math]::Round($exeSize, 2)) KB)"
        }
    } else {
        Write-Error "✗ Build failed! Check error messages above."
        exit 1
    }
} else {
    Write-Warning "Build skipped. You can build manually later:"
    Write-Host "  $($config.quickStart.step3.command)"
}

# Testing
if (-not $SkipTests -and (Test-Path ".\tests")) {
    Write-Info "`n=== TESTING ==="
    
    $response = Read-Host "Do you want to run unit tests? (Y/N)"
    if ($response -match '^[Yy]$') {
        Write-Info "Building and running tests..."
        $testCount = 0
        
        foreach ($testFile in $config.build.testFiles) {
            if (Test-Path $testFile) {
                $testName = [System.IO.Path]::GetFileNameWithoutExtension($testFile)
                $testExe = ".\tests\$testName"
                
                Write-Host "`nRunning test: $testName..."
                
                # Build test
                $buildTestCmd = "g++ $testFile -I .\src -o $testExe"
                Invoke-Expression $buildTestCmd
                
                if ($LASTEXITCODE -eq 0) {
                    # Run test
                    & $testExe
                    if ($LASTEXITCODE -eq 0) {
                        Write-Success "  ✓ $testName passed"
                        $testCount++
                    } else {
                        Write-Error "  ✗ $testName failed"
                    }
                } else {
                    Write-Error "  ✗ Failed to build $testName"
                }
            }
        }
        
        Write-Success "`n✓ Tests completed ($testCount passed)"
    }
}

# Next steps
Write-Info "`n=== SETUP COMPLETE ==="
Write-Success "✓ Your project is ready!"
Write-Host ""
Write-Host "Next steps:"
Write-Host "  1. Read README.md for project overview"
Write-Host "  2. Run the interactive menu:"
Write-Host "     .\dsa-unified.bat"
Write-Host "  3. Initialize a test repository (Menu option 1)"
Write-Host "  4. Create a test file (Menu option 12)"
Write-Host "  5. Commit and explore features"
Write-Host ""
Write-Host "For detailed information, see ALL_INSTRUCTIONS.md"
Write-Host ""

# Quick test option
$response = Read-Host "Would you like to test the CLI now? (Y/N)"
if ($response -match '^[Yy]$') {
    Write-Info "`nTesting CLI..."
    Write-Host "Running: .\build\main.exe --repo .\repo init`n"
    & ".\build\main.exe" --repo ".\repo" init
    
    if ($LASTEXITCODE -eq 0) {
        Write-Success "`n✓ CLI test successful!"
        Write-Host ""
        Write-Host "Run .\dsa-unified.bat to launch the interactive menu"
    } else {
        Write-Error "`n✗ CLI test failed"
    }
}

Write-Host ""

@echo off
setlocal

REM Set build directory
set "BUILD_DIR=build"

REM Function to clean the build directory
:clean_build_dir
echo Cleaning build directory...
if exist "%BUILD_DIR%" (
    rmdir /s /q "%BUILD_DIR%"
)
mkdir "%BUILD_DIR%"
goto :eof

REM Function to configure and build the project
:build_project
echo Configuring project with CMake...
cmake -S . -B %BUILD_DIR%
if errorlevel 1 (
    echo CMake configuration failed!
    exit /b 1
)

echo Building project...
cmake --build %BUILD_DIR%
if errorlevel 1 (
    echo Build failed!
    exit /b 1
)
goto :eof

REM Function to run the project
:run_project
if exist "%BUILD_DIR%\Liminal.exe" (
    echo Running the project...
    "%BUILD_DIR%\Liminal.exe"
) else (
    echo Build failed or executable not found!
)
goto :eof

REM Main logic starts here
echo Windows detected
call :clean_build_dir
call :build_project
call :run_project

endlocal

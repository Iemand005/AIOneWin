@echo off
setlocal

set SRC_DIR=%~dp0AIOne
set BUILD_DIR=%~dp0build\AIOneUWP
for /f "tokens=2*" %%A in ('reg query "HKLM\SOFTWARE\Microsoft\Windows Kits\Installed Roots" /v KitsRoot10') do set WindowsSdkDir=%%B

cmake -S "%SRC_DIR%" -B "%BUILD_DIR%" -G "Visual Studio 18 2026" -A x64 -DAIONE_UWP=ON -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0.22621.0 -DCMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION=10.0.22621.0 -DCMAKE_VS_WINDOWS_TARGET_PLATFORM_MIN_VERSION=10.0.17763.0

if errorlevel 1 exit /b 1

cmake --build "%BUILD_DIR%" --config Debug

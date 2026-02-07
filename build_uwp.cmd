@echo off
setlocal

set SRC_DIR=%~dp0AIOne
set BUILD_DIR=%~dp0build\AIOneUWP

cmake -S "%SRC_DIR%" -B "%BUILD_DIR%" -A x64 -DCMAKE_SYSTEM_NAME=WindowsStore

if errorlevel 1 exit /b 1

cmake --build "%BUILD_DIR%" --config Debug

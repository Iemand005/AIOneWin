@echo off
setlocal

set SRC_DIR=%~dp0AIOne
set BUILD_DIR=%~dp0build\AIOneUWP

cmake -S "%SRC_DIR%" -B "%BUILD_DIR%" -G "Visual Studio 18 2026" -A x64 -DAIONE_UWP=true -DLLAMA_UWP=true

if errorlevel 1 exit /b 1

cmake --build "%BUILD_DIR%" --config Debug

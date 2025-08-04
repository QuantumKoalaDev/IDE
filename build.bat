@echo off

if exist build (
    rmdir /s /q build
)

mkdir build

echo [*] Configuring...
cmake -S "%cd%" -B "%cd%\build" -G "Visual Studio 17 2022" -A x64

echo [*] Building...
cmake --build "%cd%\build" --config Debug

echo [✓] Done

pause
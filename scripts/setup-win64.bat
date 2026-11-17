@echo off
rem Installs MSYS2 packages needed to build lasmIDE on Windows and creates CONFIG.INI.
rem Requires MSYS2 in C:\msys64 (https://www.msys2.org).
cd /d "%~dp0.."
if not exist C:\msys64\usr\bin\bash.exe (
    echo MSYS2 not found in C:\msys64
    exit /b 1
)
C:\msys64\usr\bin\bash.exe -lc "pacman -S --needed --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-pkgconf mingw-w64-x86_64-gtk3 mingw-w64-x86_64-gtksourceview3"
if not exist CONFIG.INI copy CONFIG.INI.default CONFIG.INI
if not exist include\invoke.inc echo WARNING: include\invoke.inc is missing (see include\README.md)
echo Done. Add C:\msys64\mingw64\bin to PATH, then run scripts\build-win64.bat

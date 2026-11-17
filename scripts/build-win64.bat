@echo off
rem Builds lasmWin64.exe (same commands as the old build.bat). Run with MSYS2 mingw64\bin in PATH.
cd /d "%~dp0.."
uasm64 -c -win64 -Zp8 -Zi -nologo main.asm
if errorlevel 1 exit /b 1
for /f "delims=" %%i in (pkg-config --libs gtk+-3.0 cairo gthread-2.0 gtksourceview-3.0 gobject-2.0 gmodule-no-export-2.0) do set PKGLIBS=%%i
gcc -s -o lasmWin64.exe main.obj %PKGLIBS%
if errorlevel 1 exit /b 1
echo Built lasmWin64.exe

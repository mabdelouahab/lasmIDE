# lasmIDE (Linux Assembly IDE)

A small IDE for assembly programming, written in assembly (UASM) on top of
GTK 3, GtkSourceView and Cairo. It started as a Linux-only tool and was later
ported to Windows (64-bit). The GTK bindings live in `muasm/` (hand-written
macros and prototypes).

Forum thread: https://masm32.com/board/index.php?topic=10000

## Requirements

| | Linux | Windows 64-bit |
|---|---|---|
| Assembler | `uasm` in PATH | `uasm64.exe` in PATH or in this folder |
| Linker | gcc | gcc from MSYS2 mingw64 |
| Libraries | gtk+-3.0, gtksourceview-3.0, vte-2.91, cairo | same, from MSYS2 (no VTE: `wterminal.inc` is used instead) |
| Other | `include/invoke.inc` (see `include/README.md`) | same |

UASM: https://github.com/Terraspace/UASM

## Build

Linux:

    scripts/setup-linux.sh     # once: installs dependencies, creates CONFIG.INI
    scripts/build-linux.sh     # produces ./lasm
    ./lasm                     # run from this folder

Windows (MSYS2 in `C:\msys64`):

    scripts\setup-win64.bat    # once
    scripts\build-win64.bat    # produces lasmWin64.exe

`CONFIG.INI` is per-user and ignored by git; it is created from
`CONFIG.INI.default`. The GTK DLLs are no longer stored in the repository:
they come from MSYS2 (`C:\msys64\mingw64\bin`).

## Layout

- `main.asm`, `main.inc`: entry point and includes
- `*.wedg`, `*.glade`: dialogs and window definitions
- `muasm/`: GTK / GLib / Cairo / libc bindings for UASM
- `langs/`, `Icons/`, `templates/`: syntax files, icons, project templates
- `projects/`: sample projects
- `lasm.aprj`, `lasmWin64.aprj`: lasmIDE project files for lasmIDE itself

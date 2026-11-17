#!/usr/bin/env bash
# Builds ./lasm  (same commands as lasm.aprj)
set -e
cd "$(dirname "$0")/.."
uasm -elf64 main.asm
gcc -o lasm main.o -fno-pie -no-pie -rdynamic \
    $(pkg-config --libs vte-2.91 gtk+-3.0 cairo gthread-2.0 gtksourceview-3.0 gobject-2.0 gmodule-no-export-2.0)
echo "Built ./lasm   (run it from this folder: ./lasm)"

#!/usr/bin/env bash
# Installs build dependencies (Debian/Ubuntu, Arch, Fedora) and creates CONFIG.INI.
set -e
cd "$(dirname "$0")/.."

if command -v apt-get >/dev/null; then
    sudo apt-get install -y build-essential pkg-config libgtk-3-dev \
        libgtksourceview-3.0-dev libvte-2.91-dev libcairo2-dev
elif command -v pacman >/dev/null; then
    sudo pacman -S --needed base-devel pkgconf gtk3 gtksourceview3 vte3 cairo
elif command -v dnf >/dev/null; then
    sudo dnf install -y gcc pkgconf-pkg-config gtk3-devel gtksourceview3-devel \
        vte291-devel cairo-devel
else
    echo "Unknown distribution: install gcc, pkg-config and the development"
    echo "packages of gtk+-3.0, gtksourceview-3.0, vte-2.91 and cairo manually."
fi

command -v uasm >/dev/null || echo "WARNING: 'uasm' not found in PATH (see README.md)."
[ -f include/invoke.inc ] || echo "WARNING: include/invoke.inc is missing (see include/README.md)."

[ -f CONFIG.INI ] || cp CONFIG.INI.default CONFIG.INI
echo "Done."

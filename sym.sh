#!/bin/sh
# usage: ./sym.sh ./prog 0x40159f [0x4014e4 ...]
# prints proc+offset (nearest preceding symbol; only PUBLIC procs/labels exist in the symbol table)
prog="$1"; shift
for a in "$@"; do
  t=$(printf '%016x' "$a")
  r=$(nm -n "$prog" | awk -v T="$t" '$2 ~ /^[TtWw]$/ { if (("x" $1) <= ("x" T)) { n=$3; b=$1 } else exit } END { if (n != "") print n, b }')
  if [ -z "$r" ]; then echo "$a  (no symbol)"; continue; fi
  n=${r% *}; b=${r#* }
  printf '%s  %s+0x%x\n' "$a" "$n" $(( a - 0x$b ))
  addr2line -e "$prog" "$a" 2>/dev/null | grep -v '^??' | sed 's/^/      /'
done

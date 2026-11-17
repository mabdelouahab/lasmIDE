# include/

`main.inc` expects `include/invoke.inc` here: the author's own `invoke`
macro, written because UASM's built-in one had problems with stack alignment
and with calls that pass floating point arguments.

Copy `invoke.inc` into this folder before building.

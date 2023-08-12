@echo off
set OLDPATH=%PATH%

set PATH=C:\MASM611\BIN;C:\MASM611\BINR

ml ultima.asm

set PATH=%OLDPATH%
set OLDPATH=

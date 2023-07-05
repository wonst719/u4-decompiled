@echo off
set OLDPATH=%PATH%

set PATH=%PATH%;C:\MASM611\BIN

rem call C:\C600\BIN\MSCVARS.BAT
call C:\MSVC\BIN\MSVCVARS.BAT

\tools\turboc20\make > log.txt

set PATH=%OLDPATH%
set OLDPATH=

type log.txt

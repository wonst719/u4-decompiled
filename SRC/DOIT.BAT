@echo off
set OLDPATH=%PATH%

set MSC=\tools\msc400
set PATH=%MSC%;\tools;%PATH%
set INCLUDE=%MSC%\INCLUDE
set LIB=%MSC%\LIB

\tools\turboc20\make > log.txt

set PATH=%OLDPATH%
set OLDPATH=

type log.txt
echo on

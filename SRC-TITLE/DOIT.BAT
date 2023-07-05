@echo off
set OLDPATH=%PATH%

set MSC4=\TOOLS\MSC400
set PATH=%PATH%;\tools;%MSC4%
set INCLUDE=%MSC4%\INCLUDE
set LIB=%MSC4%\LIB
set CFLAGS=/Ox /Zp /Gc
set AS=\TOOLS\MASM611

echo START > log.txt

del *.obj
del title_0.exe

MSC %CFLAGS% title_x; >> log.txt
MSC %CFLAGS% file; >> log.txt
MSC %CFLAGS% title_0; >> log.txt
MSC %CFLAGS% u4_cdda; >> log.txt
%AS% /Mx /w2 /v GRAPH; >> log.txt
rem pause
%AS% /Mx /w2 /v CDDA; >> log.txt
%AS% /Mx BEEP; >> log.txt
%AS% /Mx INFLATE; >> log.txt
%AS% /Mx LOW; >> log.txt
MSC %CFLAGS% title_1;
%AS% /Mx UTIL2; >> log.txt
%AS% /Mx VAR; >> log.txt

%AS% /Mx DATA; >> log.txt
%AS% /Mx ERRMSG; >> log.txt
REM MSC %CFLAGS% data; >> log.txt
REM MSC %CFLAGS% errmsg; >> log.txt

rem temporary
LINK531 /MAP title_x file title_0 graph beep inflate low title_1 util2 cdda u4_cdda VAR  %LIB%\binmode data errmsg; >> log.txt
del title_0.exe
ren title_x.exe title_0.exe

set PATH=%OLDPATH%
set OLDPATH=

@echo off
set OLDPATH=%PATH%

set PATH=%PATH%;C:\MASM611\BIN

rem call C:\C600\BIN\MSCVARS.BAT
call C:\MSVC\BIN\MSVCVARS.BAT

set CFLAGS=/Ox /Os /Zp /Gc /c
set AS=\TOOLS\MASM611
set CL=CL
set LINK=\TOOLS\LINK531

echo START > log.txt

del *.obj
del title_0.exe

%CL% %CFLAGS% title_x.c >> log.txt
%CL% %CFLAGS% file.c >> log.txt
%CL% %CFLAGS% title_0.c >> log.txt
%CL% %CFLAGS% u4_cdda.c >> log.txt
%AS% /Mx /w2 /v GRAPH; >> log.txt
rem pause
%AS% /Mx /w2 /v CDDA; >> log.txt
%AS% /Mx BEEP; >> log.txt
%AS% /Mx INFLATE; >> log.txt
%AS% /Mx LOW; >> log.txt
%CL% %CFLAGS% title_1.c >> log.txt
%AS% /Mx UTIL2; >> log.txt
%AS% /Mx VAR; >> log.txt

%AS% /Mx DATA; >> log.txt
%AS% /Mx ERRMSG; >> log.txt
REM %CL% %CFLAGS% data.c >> log.txt
REM %CL% %CFLAGS% errmsg.c >> log.txt

rem temporary
%LINK% /MAP title_x file title_0 graph beep inflate low title_1 util2 cdda u4_cdda VAR  %LIB%\binmode data errmsg; >> log.txt
del title_0.exe
ren title_x.exe title_0.exe

set PATH=%OLDPATH%
set OLDPATH=

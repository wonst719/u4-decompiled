@echo off
set OLDPATH=%PATH%

set MSC4=\TOOLS\MSC400
set PATH=%PATH%;%MSC4%;C:\MASM611\BIN
set INCLUDE=%MSC4%\INCLUDE
set LIB=%MSC4%\LIB
set CFLAGS=/Ox /Zp /Gc
set AS=\TOOLS\MASM611
set CL=MSC
set LINK=\TOOLS\LINK531

rem #Doesn't work#
rem set CFLAGS=/Ox /Os /Zp /Gc /c
rem set AS=\TOOLS\MASM611
rem set CL=CL
rem set LINK=\TOOLS\LINK531

echo START > log.txt

del *.obj
del title_0.exe

%CL% %CFLAGS% title_x; >> log.txt
%CL% %CFLAGS% file; >> log.txt
%CL% %CFLAGS% title_0; >> log.txt
%CL% %CFLAGS% u4_cdda; >> log.txt
%AS% /Mx /w2 /v GRAPH; >> log.txt
rem pause
%AS% /Mx /w2 /v CDDA; >> log.txt
%AS% /Mx BEEP; >> log.txt
%AS% /Mx INFLATE; >> log.txt
%AS% /Mx LOW; >> log.txt
%CL% %CFLAGS% title_1;
%AS% /Mx UTIL2; >> log.txt
%AS% /Mx VAR; >> log.txt

%AS% /Mx DATA; >> log.txt
%AS% /Mx ERRMSG; >> log.txt
REM %CL% %CFLAGS% data; >> log.txt
REM %CL% %CFLAGS% errmsg; >> log.txt

rem temporary
%LINK% /MAP title_x file title_0 graph beep inflate low title_1 util2 cdda u4_cdda VAR  %LIB%\binmode data errmsg; >> log.txt
del title_0.exe
ren title_x.exe title_0.exe

set PATH=%OLDPATH%
set OLDPATH=

@ECHO ON
SET OLDPATH=%PATH%
cd C:\openssl-1.0.1e
if %errorlevel% NEQ 0 goto ERRORCLEANUP
set VisualStudioVersion=12.0
REM Now do 32 bit by setting environment to MSVC 32 bit
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\vcvars32.bat"
REM debug 32 first
call perl Configure debug-VC-WIN32 
call ms\do_nasm
nmake -f ms\nt.mak clean
rem removing a compiler flag that causes the compiler to barf on a warning
perl -pi.bak -e "s#-WX##g;" ms\nt.mak
nmake -f ms\nt.mak 
if %errorlevel% NEQ 0 goto ERRORCLEANUP
REM now do release mode
call perl Configure VC-WIN32 
call ms\do_nasm
nmake -f ms\nt.mak clean
nmake -f ms\nt.mak 
if %errorlevel% NEQ 0 goto ERRORCLEANUP
REM put back the path
set PATH=%OLDPATH%
echo All finished!
pause
goto EOF
:ERRORCLEANUP
echo Something went wrong, please check the directories in this batch file!
pause
:EOF

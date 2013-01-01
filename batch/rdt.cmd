@echo off & setlocal

:: Remote Desktop Connector

set REMOTE_HOST=%1
set REMOTE_PORT=%2
set LOCAL_HOST=localhost
set LOCAL_PORT=13389
set SSH_CLIENT=C:\Software\PuTTY\putty.exe
set SSH_SERVER=user@host
set RDT_CLIENT=mstsc.exe

if "%REMOTE_HOST%" == "" goto :EOF
if "%REMOTE_PORT%" == "" set REMOTE_PORT=3389

echo -------------- Remote Desktop Connector --------------
echo Trying to connect to %REMOTE_HOST%:%REMOTE_PORT% via %SSH_SERVER%...

:CHECK_LOCAL_PORT
echo Proposed Local Port: %LOCAL_PORT%...
netstat -a -n -p TCP | findstr ":%LOCAL_PORT%"
if %ERRORLEVEL% equ 0 goto FIND_FREE_LOCAL_PORT
netstat -a -n -p TCPv6 | findstr ":%LOCAL_PORT%"
if %ERRORLEVEL% equ 0 goto FIND_FREE_LOCAL_PORT
goto CONNECT

:FIND_FREE_LOCAL_PORT
:: Use local port in range of 20000 ~ 52767
echo The port is in use!
set /a LOCAL_PORT=%RANDOM% + 20000
goto CHECK_LOCAL_PORT

:CONNECT
echo Starting SSH Port Forwarding...
start %SSH_CLIENT% -N -L %LOCAL_PORT%:%REMOTE_HOST%:%REMOTE_PORT% "%SSH_SERVER%"

echo Starting Microsoft Terminal Service Client...
start %RDT_CLIENT% /v:%LOCAL_HOST%:%LOCAL_PORT% /admin

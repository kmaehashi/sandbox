@echo off

set VPN_CONNECTION=Connection_Name
set NETWORK_PEER_IP=192.168.100.1
set NETWORK_DRIVE_SHARE=kenichi
set NETWORK_DRIVE_LETTER=U:

:: ----------------------------------- ::
echo VPN ^& Network Drive Service
echo.

:: ----------------------------------- ::
echo --- Unmounting Network Drive ---
net use %NETWORK_DRIVE_LETTER% /delete

:: ----------------------------------- ::
echo --- Disconnecting ---
start /wait rasphone -h "%VPN_CONNECTION%"

:: ----------------------------------- ::
echo --- Reconnecting ---
start /wait rasphone -d "%VPN_CONNECTION%"
ping %NETWORK_PEER_IP%

:: ----------------------------------- ::
echo --- Mounting Network Drive ---
net use %NETWORK_DRIVE_LETTER% /delete 2>nul
ping %NETWORK_PEER_IP% >nul
net use %NETWORK_DRIVE_LETTER% "\\%NETWORK_PEER_IP%\%NETWORK_DRIVE_SHARE%" || net use %NETWORK_DRIVE_LETTER% "\\%NETWORK_PEER_IP%\%NETWORK_DRIVE_SHARE%"

:: ----------------------------------- ::
echo Done!

pause

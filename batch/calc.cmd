@echo off

setlocal
if "%1" equ "" goto USAGE

set /a ANS=%*
echo.%ANS%
goto :EOF

:USAGE
echo Command Line Calculator
echo Type "set /?" for syntax options.

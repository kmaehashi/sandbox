@echo off & setlocal

:: Variable Expansion Examples

set VARNAME=HOGE

set DATA_%VARNAME%=Hello, world!
call :GET_VALUE DATA_%VARNAME%

echo `call :GET_VALUE DATA_HOGE` = %VALUE%

pause
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:GET_VALUE
:: 指定された変数の値を返却します。
:: @returns VALUE 指定された変数の値を返します。

	call :GET_VALUE_VALUE %%%1%%
	goto :EOF

	:GET_VALUE_VALUE
		set VALUE=%*
		goto :EOF

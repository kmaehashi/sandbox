@echo off

call :GET_SQL_DATE
echo %SQL_DATE%

pause
goto :EOF


:GET_SQL_DATE
:: 現在の日付を SQL 形式でを返します。
:: 日本語環境でのみ正しく動作します。
:: @return SQL_DATE

	set SQL_DATE=%DATE:~0,4%-%DATE:~5,2%-%DATE:~8,2%

	goto :EOF

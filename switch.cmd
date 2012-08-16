@echo off

set DATA=hoge

call :_SWITCH "%DATA%" ^
	case foobar:	CALL_ENGLISH ^
	case hoge:	CALL_JAPANESE ^
	default:	CALL_DEFAULT

pause
goto :EOF

:CALL_ENGLISH
echo Hello!
goto :EOF

:CALL_JAPANESE
echo Ç±ÇÒÇ…ÇøÇÕÇ±ÇÒÇ…ÇøÇÕÅI
goto :EOF

:CALL_DEFAULT
echo sweet syntax sugar, isn't it?
goto :EOF


::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:_SWITCH
:: Provides SWITCH syntax.

	:_SWITCH_LOOP_START
		if "%~2" == "default:" (
			call :%~3
			goto :EOF
		)

		if not "%~2" == "case" (
			goto :EOF
		)

		if "%~3" == "%~1:" (
			call :%~4
			goto :EOF
		)

		shift /2 & shift /2 & shift /2
		goto :_SWITCH_LOOP_START
	:_SWITCH_LOOP_END

	goto :EOF

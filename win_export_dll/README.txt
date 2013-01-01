cl /LD msg.c user32.lib setupapi.lib
dumpbin /exports msg.dll
rundll32.exe msg.dll,_MyMsgBox@16 Hello,World!

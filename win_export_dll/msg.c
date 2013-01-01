#include <windows.h>
#include <Setupapi.h>

__declspec(dllexport) void CALLBACK MyMsgBox(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {
	// MessageBox( hwnd, lpszCmdLine, "ƒ^ƒCƒgƒ‹", MB_OK );
	CM_Request_Device_EjectW(NULL, NULL, NULL, NULL, NULL);
}

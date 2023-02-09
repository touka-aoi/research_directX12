#include <Windows.h>
#include <debugapi.h>
#include <iostream>

using namespace std;


// WINDOW PROCEDURE
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// QUIT_MESSAGE
	if (msg == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	OutputDebugStringW(L"[INFO] : Show window Test\n");
	return 0;
}

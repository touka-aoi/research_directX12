#include "stdafx.h"
#include "WinApplication.h"

#define WINDOW_WIDTH 1920
#define WINDOWS_HEIGHT 1080

int WinApplication::Run(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = (WNDPROC)WindowProc; //プロシージャの指定
	windowClass.lpszClassName = L"DX12Sample"; //クラス名指定
	windowClass.hInstance = hInstance; //ハンドルの取得

	RegisterClassEx(&windowClass); // クラス登録

	RECT windowRect = { 0, 0, WINDOW_WIDTH, WINDOWS_HEIGHT }; // クライアントサイズ
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE); //ウィンドウサイズへ調整

	//ウィンドウオブジェクトの作成
	HWND hwnd = CreateWindow(
		windowClass.lpszClassName, //クラス名
		L"DX12Sample",
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, //表示座標
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, //親ウィンドウ
		nullptr, //メニュー
		hInstance, //アプリケーションハンドル
		nullptr //追加param
	);

	// DirectX Init
	// ここにDirectXのInit()

	ShowWindow(hwnd, nCmdShow);


	// Main loop
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		// Process any messages in the queue.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// ここにDIrectXオブジェクトの削除

	// Return this part of the WM_QUIT message to Windows.
	return static_cast<char>(msg.wParam);
}

LRESULT CALLBACK WinApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
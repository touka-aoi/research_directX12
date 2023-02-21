#include "stdafx.h"
#include "WinApplication.h"

HWND WinApplication::m_hwnd = nullptr;

int WinApplication::Run(D3D12Touka* pTouka, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = (WNDPROC)WindowProc; //プロシージャの指定
	windowClass.lpszClassName = L"DX12Sample"; //クラス名指定
	windowClass.hInstance = hInstance; //ハンドルの取得

	RegisterClassEx(&windowClass); // クラス登録

	RECT windowRect = { 0, 0, static_cast<LONG>(pTouka->GetWidth()), static_cast<LONG>(pTouka->GetHeight())}; // クライアントサイズ
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE); //ウィンドウサイズへ調整

	//ウィンドウオブジェクトの作成
	m_hwnd = CreateWindow(
		windowClass.lpszClassName, //クラス名
		pTouka->GetTitle(),
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, //表示座標
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, //親ウィンドウ
		nullptr, //メニュー
		hInstance, //アプリケーションハンドル
		pTouka //追加param
	);

	// DirectX Init
	pTouka->OnInit();
	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)pTouka);

	ShowWindow(m_hwnd, nCmdShow);

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
	// DXクラスポインタを取得
	D3D12Touka* pTouka = reinterpret_cast<D3D12Touka*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		if (pTouka)
		{
			pTouka->OnRender();
			
		}
		return 0;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}
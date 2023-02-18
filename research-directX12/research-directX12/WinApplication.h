#pragma once

#include "D3D12Touka.h"

class D3D12Touka;

class WinApplication
{
public:
    static int Run(D3D12Touka* pTouka, HINSTANCE hInstance, int nCmdShow); // 開始関数
    static HWND GetHwnd() { return m_hwnd; } // アクセサ

protected:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // ウィンドウプロシージャ

private:
    static HWND m_hwnd;
};
